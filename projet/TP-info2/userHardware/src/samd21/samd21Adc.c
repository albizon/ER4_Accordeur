/*
 * Samd21Adc.c
 *
 * Created: 03/02/2017 13:32:53
 *  Author: simon
 */ 

 
void init_adc(
				uint32_t *args)
								/*
								args[0] = clock source
								args[1] = ref
								args[2] = diviseur de fréquence							
								*/
{
	static uint8_t firstInit=TRUE;
	if(firstInit){
		//Power Management.
		PM->APBCMASK.reg |= 1 << 16; //ADC
		
		//horloge: generateur 3 (8MHz)
		GCLK->CLKCTRL.reg = 1 <<14 | //enable
							args[0] << 8 | //generator
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
		ADC->REFCTRL.reg |= args[1];		//référence de tension
		ADC->CTRLB.reg = 	args[2] << 8 |  //diviseur de fréquence
							0x1 << 0;		//mode différentiel
		ADC->CTRLA.reg |= 1<<1; //enable
		firstInit=FALSE;
	}
	
}

int16_t read_adc(
					uint32_t *args)
									/*
									args[0] = gain
									args[1] = ref negative
									args[2] = ref positive	
									*/
{
	uint32_t result;
	//choix du canal de conversion.
	ADC->INPUTCTRL.reg = 0x0 | 
						args[0] << 24 | //gain
						args[1] << 8 | //ref negative
						args[2] << 0;  //ref positive
						
	//RAZ flag de fin de conversion (avec un 1!)
	ADC->INTFLAG.reg = 0x1; //RAZ RESRDY
	//demande de conversion
	ADC->SWTRIG.reg = 1 << 1; //start.
	while(!(ADC->INTFLAG.bit.RESRDY)); //attente fin de conversion.
	result = ADC->RESULT.reg; //resultat sur 12 bits.
	
	return result;
}
