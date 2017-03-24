#include "dac.h"
#include "sam.h"
#include "pinAccess.h"
#include "pinMux.h"
#include "clock.h"

//on redéfinit le pointeur vers SERCOM1, pour éviter
//les cast vers le type SercomSpi à chaque fois.
SercomSpi *spi = (SercomSpi *)SERCOM1;

void DACInit()
{
	pinMode(PORTA,17,OUTPUT);
	//test accès SPI
	//pinMux(PORTA,17,CONFIG_C); //config C => SERCOM1 - pad 1
	pinMux(PORTA,18,CONFIG_C); //config C => SERCOM1 - pad 2
	pinMux(PORTA,19,CONFIG_C); //config C => SERCOM1 - pad 3

	//Power Management.
	PM->APBCMASK.reg |= 0x8; //sercom1
	
	//horloge: generateur 0 (48MHz)
	GCLK->CLKCTRL.reg = 1 <<14 | //enable
						F48MHZ << 8 | //generator
						0x15;	 //SERCOM1
	//config SPI:
	spi->CTRLA.bit.SWRST = 1;
	while ( spi->CTRLA.bit.SWRST || spi->SYNCBUSY.bit.SWRST );
	spi->CTRLA.reg =	1 << 29 | //CPOL
						1 << 16 | //DOPO = 1 => pad1=SS=PORTA.17 - pad2=DO=PORT.A.18 - pad3=SCK=PORTA.19
						3 << 2;    //Mode Master
	spi->CTRLB.reg = 0;//1 << 13; //MSSEN (Master Slave Select Enable) <=> Chip Select matériel
	spi->BAUD.reg = 1; // p.427 (synchronous) => Fbaud=Fref(2*(baud+1)) => Fref=8MHz => FBaud = 2MHz
	//validation spi
	spi->CTRLA.reg |= 0x02;
}

void DACWrite(unsigned int val)
{
	//4 bits de poids faibles inutiles
	//10 bits pour le DAC
	//2bits de poids fort pour le mode => 0=normal
	const unsigned int trame = (val << 4) & 0x3FFF;

	digitalWrite(PORTA,17,0);            //Chip select
	spi->DATA.reg = (trame >> 8);        //envoi octet poids fort.
	while(!(spi->INTFLAG.reg & 0x01));   //attente que Data Register Empty flag passe a 1
	spi->DATA.reg = (trame & 0xFF);      //envoi octet poids faible
	while(! spi->INTFLAG.bit.TXC);       //attente fin transmission
	digitalWrite(PORTA,17,1);            //chip select.
}

