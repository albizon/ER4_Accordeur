#include "sam.h"
#include "adc.h"
#include "clock.h"
#include "pinMux.h"
#include "pinAccess.h"

int ADCInit() {
	//Power Management.
	PM->APBCMASK.reg |= 1 << 16; //ADC
	
	//horloge: generateur 3 (8MHz)
	GCLK->CLKCTRL.reg = 1 <<14 | //enable
						F8MHZ << 8 | //generator
						0x1E;	 //ADC
	//calibration d'usine:
	ADC->CALIB.reg =
		ADC_CALIB_BIAS_CAL(
			(*(uint32_t *)ADC_FUSES_BIASCAL_ADDR >> ADC_FUSES_BIASCAL_Pos)
		) |
		ADC_CALIB_LINEARITY_CAL(
			(*(uint64_t *)ADC_FUSES_LINEARITY_0_ADDR >> ADC_FUSES_LINEARITY_0_Pos)
	);

	//config ADC
	ADC->REFCTRL.reg |= 0x2; // ref analogique: 1/2 VDDANA
	ADC->CTRLB.reg = 1 << 8; // clk/8 (=> 1MHz)
	ADC->INPUTCTRL.reg =	0xF << 24 | //gain/2
							0x18 << 8 | //ref negative: GND
							0x7  << 0;  //ref positive: ADC AIN7 pin
	//démarrage de l'ADC.
	ADC->CTRLA.reg |= 1<<1; //enable
	return 0;	
}

int ADCRead(int canal)
{
	int result;
	if(canal > 0x1C) result = -1;
	else {
		//choix du canal de conversion.
		ADC->INPUTCTRL.reg = (ADC->INPUTCTRL.reg & ~0xF) | canal;
		//RAZ flag de fin de conversion (avec un 1!)
		ADC->INTFLAG.reg = 0x1; //RAZ RESRDY
		//demande de conversion
		ADC->SWTRIG.reg = 1 << 1; //start.
		while(!(ADC->INTFLAG.bit.RESRDY)); //attente fin de conversion.
		result = ADC->RESULT.reg; //resultat sur 12 bits.
	}
	return result;
}

