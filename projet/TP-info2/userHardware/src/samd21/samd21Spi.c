/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/

#include "samd21Spi.h"
#include "sam.h"

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
								*/
{
	pinConfig_gpioGeneric({args[0];args[1]} ,OUTPUT);// pin CS
	pinMux_gpioSamd21(args[2],args[3],args[3]); //pin MOSI
	pinMux_gpioSamd21(args[5],args[6],args[7]); //pin MISO
	pinMux_gpioSamd21(args[8],args[9],args[10]); //pin SCK
	
	digitalWrite_gpioGeneric({args[0]; args[1]},HIGH);            //chip unselect.
	
	uint8_t pmMask;
	uint8_t gclkMask;
	
	switch(interface){
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
	interface->CTRLA.bit.SWRST = 1;
	while ( interface->CTRLA.bit.SWRST || interface->SYNCBUSY.bit.SWRST );
	interface->CTRLA.reg =	1 << 29 | //CPOL
						1 << 16 | //DOPO = 1 => pad1=SS=PORTA.17 - pad2=DO=PORT.A.18 - pad3=SCK=PORTA.19
						3 << 2;    //Mode Master
	interface->CTRLB.reg = 0;//1 << 13; //MSSEN (Master Slave Select Enable) <=> Chip Select matériel
	interface->BAUD.reg = 0; // p.427 (synchronous) => Fbaud=Fref/(2*(baud+1)) => Fref=48MHz => FBaud = 24MHz
	//validation spi
	interface->CTRLA.reg |= 0x02;
}


void writeByte_spi(void *interface, uint32_t *args, uint8_t byte)
{
	digitalWrite_gpioGeneric({args[0]; args[1]},LOW);            //chip select.
	interface->DATA.reg = (byte);        //envoi octet
	while(! interface->INTFLAG.bit.TXC);       //attente fin transmission
	digitalWrite_gpioGeneric({args[0]; args[1]},HIGH);            //chip unselect.
}

void writeBytes_spi(void *interface, uint32_t *args, uint8_t *bytes, uint32_t length)
{
	digitalWrite_gpioGeneric({args[0]; args[1]},LOW);            //chip select.
	for(uint32_t i=0; i<length-1; i++)
	{
		interface->DATA.reg = (bytes[i]);        //envoi octet courant
		while(!(interface->INTFLAG.reg & 0x01));   //attente que Data Register Empty flag passe a 1
	}
	interface->DATA.reg = (bytes[length]);        //envoi dernier octet
	while(! interface->INTFLAG.bit.TXC);       //attente fin transmission
	digitalWrite_gpioGeneric({args[0]; args[1]},HIGH);            //chip unselect.
}

uint8_t readByte_spi(void *interface, uint32_t *args)
{
	digitalWrite_gpioGeneric({args[0]; args[1]},LOW);            //chip select.
	while(!(interface->INTFLAG.bit.SSL));
	uint8_t tmp = interface->DATA.reg;
	digitalWrite_gpioGeneric({args[0]; args[1]},HIGH);            //chip unselect.
	return tmp;
}

void readBytes_spi(void *interface, uint32_t *args, uint8_t *bytes, uint32_t *length, uint32_t maxLength)
{
	&length =0;
	digitalWrite_gpioGeneric({args[0]; args[1]},LOW);            //chip select.
	while(! interface->INTFLAG.bit.TXC && length<maxLength)
	{
		while(!(interface->INTFLAG.bit.SSL));
		bytes[&length] = interface->DATA.reg;
		&length++;
		
	}
	digitalWrite_gpioGeneric({args[0]; args[1]},HIGH);            //chip unselect.
}