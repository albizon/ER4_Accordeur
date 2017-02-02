/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/

#include "externalFlashMemory.h"
#include "sam.h"
#include "pinAccess.h"
#include "pinMux.h"
#include "clock.h"


SercomSpi *spiFlash = (SercomSpi *)SERCOM5;

void initSpi(void)
{
	/*
	pinMode(PORTA,13,OUTPUT);// pin CS
	pinMux(PORTB,22,CONFIG_D); //pin MOSI
	pinMux(PORTB,16,CONFIG_C); //pin MISO
	pinMux(PORTB,23,CONFIG_D); //pin SCK

	//Power Management.
	PM->APBCMASK.reg |= 0x8; //sercom1
	
	//horloge: generateur 0 (48MHz)
	GCLK->CLKCTRL.reg = 1 <<14 | //enable
						F48MHZ << 8 | //generator
						0x15;	 //SERCOM1
	//config SPI:
	spiFlash->CTRLA.bit.SWRST = 1;
	while ( spi->CTRLA.bit.SWRST || spi->SYNCBUSY.bit.SWRST );
	spiFlash->CTRLA.reg =	1 << 29 | //CPOL
						1 << 16 | //DOPO = 1 => pad1=SS=PORTA.17 - pad2=DO=PORT.A.18 - pad3=SCK=PORTA.19
						3 << 2;    //Mode Master
	spiFlash->CTRLB.reg = 0;//1 << 13; //MSSEN (Master Slave Select Enable) <=> Chip Select matériel
	spiFlash->BAUD.reg = 1; // p.427 (synchronous) => Fbaud=Fref(2*(baud+1)) => Fref=8MHz => FBaud = 2MHz
	//validation spi
	spiFlash->CTRLA.reg |= 0x02;*/
}

void initExternalFlash(void)
{
	initSpi();
	initSecondaryFlash();
}




uint32_t reallocExternalFlash(uint32_t address, uint32_t lastSize, uint32_t newSize)
{
	freeExternalFlash(address, lastSize);
	return allocExternalFlash(newSize);
}

