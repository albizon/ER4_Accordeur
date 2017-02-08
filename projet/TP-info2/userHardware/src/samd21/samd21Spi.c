/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/

#include "samd21Spi.h"
#include "sam.h"
#include "genericGpio.h"

void init_spi(void *interface,
				uint32_t *args)/*
								args[0] = port CS
								args[1] = numBit CS
								
								args[2] = port MOSI
								args[3] = numBit MOSI
								args[4] = cofig MOSI
								
								args[5] = port MISO
								args[6] = numBit MISO
								args[7] = cofig MISO
								
								args[8] = port SCK
								args[9] = numBit SCK
								args[10] = cofig SCK
								
								args[11] = mode spi
								args[12] = DOPO config
								args[13] = DIPO config
								*/
{
	Sercom* sercomInterface = interface;
	uint32_t ar[2] ={args[0],args[1]};
	pinConfig_gpioGeneric(ar ,OUTPUT);// pin CS
	uint32_t ar1[2] = {args[2],args[3]};
	uint32_t ar2[2] = {args[5],args[6]};
	uint32_t ar3[2] = {args[8],args[9]};
	pinMux_gpioSamd21(ar1,args[3]); //pin MOSI
	pinMux_gpioSamd21(ar2,args[7]); //pin MISO
	pinMux_gpioSamd21(ar3,args[10]); //pin SCK
	
	digitalWrite_gpioGeneric(ar,HIGH);            //chip unselect.
	
	uint8_t pmMask;
	uint8_t gclkMask;
	
	switch(sercomInterface){
		case SERCOM0:
			pmMask = 0x04;
			gclkMask = 0x14;
		break;
		case SERCOM1:
			pmMask = 0x08;
			gclkMask = 0x15;
		break;
		case SERCOM2:
			pmMask = 0x10;
			gclkMask = 0x16;
		break;
		case SERCOM3:
			pmMask = 0x20;
			gclkMask = 0x17;
		break;
		case SERCOM4:
			pmMask = 0x40;
			gclkMask = 0x18;
		break;
		case SERCOM5:
			pmMask = 0x80;
			gclkMask = 0x19;
		break;
	//Power Management.
	PM->APBCMASK.reg |= pmMask;
	
	//horloge: generateur 0 (48MHz)
	GCLK->CLKCTRL.reg = 1 <<14 | //enable
						F48MHZ << 8 | //generator
						gclkMask;
	
	//config SPI:
	sercomInterface->CTRLA.bit.SWRST = 1;
	while ( sercomInterface->CTRLA.bit.SWRST || sercomInterface->SYNCBUSY.bit.SWRST );
	sercomInterface->CTRLA.reg =	1 << 29 | //CPOL
						args[13] << 20 | //DIPO
						args[12] << 16 | //DOPO
						args[11] << 2;    //Mode 
	interface->CTRLB.reg = 0;//1 << 13; //MSSEN (Master Slave Select Enable) <=> Chip Select matériel
	interface->BAUD.reg = 0; // p.427 (synchronous) => Fbaud=Fref/(2*(baud+1)) => Fref=48MHz => FBaud = 24MHz
	//validation spi
	interface->CTRLA.reg |= 0x02;
}


void writeByte_spi(void *interface, uint32_t *args, uint8_t byte)
{
	Sercom* sercomInterface = interface;
	uint32_t ar[2] ={args[0],args[1]};
	digitalWrite_gpioGeneric(ar,LOW);            //chip select.
	sercomInterface->DATA.reg = (byte);        //envoi octet
	while(! sercomInterface->INTFLAG.bit.TXC);       //attente fin transmission
	digitalWrite_gpioGeneric(ar,HIGH);            //chip unselect.
}

void writeBytes_spi(void *interface, uint32_t *args, uint8_t *bytes, uint32_t length)
{
	Sercom* sercomInterface = interface;
	uint32_t ar[2] ={args[0],args[1]};
	digitalWrite_gpioGeneric(ar,LOW);            //chip select.
	for(uint32_t i=0; i<length-1; i++)
	{
		sercomInterface->DATA.reg = (bytes[i]);        //envoi octet courant
		while(!(sercomInterface->INTFLAG.reg & 0x01));   //attente que Data Register Empty flag passe a 1
	}
	sercomInterface->DATA.reg = (bytes[length]);        //envoi dernier octet
	while(! sercomInterface->INTFLAG.bit.TXC);       //attente fin transmission
	digitalWrite_gpioGeneric(ar,HIGH);            //chip unselect.
}

uint8_t readByte_spi(void *interface, uint32_t *args)
{
	Sercom* sercomInterface = interface;
	uint32_t ar[2] ={args[0],args[1]};
	digitalWrite_gpioGeneric(ar,LOW);            //chip select.
	while(!(sercomInterface->INTFLAG.bit.RXC));
	uint8_t tmp = sercomInterface->DATA.reg;
	digitalWrite_gpioGeneric(ar,HIGH);            //chip unselect.
	return tmp;
}

void readBytes_spi(void *interface, uint32_t *args, uint8_t *bytes, uint32_t length)
{
	Sercom* sercomInterface = interface;
	uint32_t ar[2] ={args[0],args[1]};
	digitalWrite_gpioGeneric(ar,LOW);            //chip select.
	for(uint32_t i =0; i<length; i++)
	{
		while(!(sercomInterface->INTFLAG.bit.RXC));
		bytes[i] = sercomInterface->DATA.reg;		
	}
	digitalWrite_gpioGeneric(ar,HIGH);            //chip unselect.
}
