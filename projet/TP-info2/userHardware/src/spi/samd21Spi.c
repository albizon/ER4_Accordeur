/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/

#include "samd21Spi.h"


SercomSpi *spiFlash = (SercomSpi *)USES_SERCOM_PORT_EXTERNAL_FLASH_MEMORY;

#if USES_SERCOM_PORT_EXTERNAL_FLASH_MEMORY==SERCOM0
	#define SERCOM_FLASH_EXTERNAL_PM 0x04
	#define SERCOM_FLASH_EXTERNAL_GCLK 0x14
#endif

#if USES_SERCOM_PORT_EXTERNAL_FLASH_MEMORY==SERCOM1
	#define SERCOM_FLASH_EXTERNAL_PM 0x08
	#define SERCOM_FLASH_EXTERNAL_GCLK 0x15
#endif

#if USES_SERCOM_PORT_EXTERNAL_FLASH_MEMORY==SERCOM2
	#define SERCOM_FLASH_EXTERNAL_PM 0x10
	#define SERCOM_FLASH_EXTERNAL_GCLK 0x16
#endif

#if USES_SERCOM_PORT_EXTERNAL_FLASH_MEMORY==SERCOM3
	#define SERCOM_FLASH_EXTERNAL_PM 0x20
	#define SERCOM_FLASH_EXTERNAL_GCLK 0x17
#endif

#if USES_SERCOM_PORT_EXTERNAL_FLASH_MEMORY==SERCOM4
	#define SERCOM_FLASH_EXTERNAL_PM 0x40
	#define SERCOM_FLASH_EXTERNAL_GCLK 0x18
#endif

#if USES_SERCOM_PORT_EXTERNAL_FLASH_MEMORY==SERCOM5
	#define SERCOM_FLASH_EXTERNAL_PM 0x80
	#define SERCOM_FLASH_EXTERNAL_GCLK 0x19
#endif


void initSamd21Spi(void)
{
	pinMode(SERCOM_EXTERNAL_FLASH_MEMORY_CS_PORT,SERCOM_EXTERNAL_FLASH_MEMORY_CS_PIN,OUTPUT);// pin CS
	pinMux(SERCOM_EXTERNAL_FLASH_MEMORY_MOSI_PORT,SERCOM_EXTERNAL_FLASH_MEMORY_MOSI_PIN,SERCOM_EXTERNAL_FLASH_MEMORY_MOSI_CONFIG); //pin MOSI
	pinMux(SERCOM_EXTERNAL_FLASH_MEMORY_MISO_PORT,SERCOM_EXTERNAL_FLASH_MEMORY_MISO_PIN,SERCOM_EXTERNAL_FLASH_MEMORY_MISO_CONFIG); //pin MISO
	pinMux(SERCOM_EXTERNAL_FLASH_MEMORY_SCK_PORT,SERCOM_EXTERNAL_FLASH_MEMORY_SCK_PIN,SERCOM_EXTERNAL_FLASH_MEMORY_SCK_CONFIG); //pin SCK
	
	digitalWrite(SERCOM_EXTERNAL_FLASH_MEMORY_CS_PORT,SERCOM_EXTERNAL_FLASH_MEMORY_CS_PIN,1);            //chip unselect.
	
	
	//Power Management.
	PM->APBCMASK.reg |= SERCOM_FLASH_EXTERNAL_PM;
	
	//horloge: generateur 0 (48MHz)
	GCLK->CLKCTRL.reg = 1 <<14 | //enable
						F48MHZ << 8 | //generator
						SERCOM_FLASH_EXTERNAL_GCLK;
	
	//config SPI:
	spiFlash->CTRLA.bit.SWRST = 1;
	while ( spi->CTRLA.bit.SWRST || spi->SYNCBUSY.bit.SWRST );
	spiFlash->CTRLA.reg =	1 << 29 | //CPOL
						1 << 16 | //DOPO = 1 => pad1=SS=PORTA.17 - pad2=DO=PORT.A.18 - pad3=SCK=PORTA.19
						3 << 2;    //Mode Master
	spiFlash->CTRLB.reg = 0;//1 << 13; //MSSEN (Master Slave Select Enable) <=> Chip Select matériel
	spiFlash->BAUD.reg = 0; // p.427 (synchronous) => Fbaud=Fref/(2*(baud+1)) => Fref=48MHz => FBaud = 24MHz
	//validation spi
	spiFlash->CTRLA.reg |= 0x02;
}


void writeByteSamd21Spi(uint8_t byte)
{
	digitalWrite(SERCOM_EXTERNAL_FLASH_MEMORY_CS_PORT,SERCOM_EXTERNAL_FLASH_MEMORY_CS_PIN,0);            //Chip select
	spiFlash->DATA.reg = (byte);        //envoi octet
	while(! spiFlash->INTFLAG.bit.TXC);       //attente fin transmission
	digitalWrite(SERCOM_EXTERNAL_FLASH_MEMORY_CS_PORT,SERCOM_EXTERNAL_FLASH_MEMORY_CS_PIN,1);            //chip unselect.
}

void writeBytesSamd21Spi(uint8_t *bytes, uint32_t length)
{
	digitalWrite(SERCOM_EXTERNAL_FLASH_MEMORY_CS_PORT,SERCOM_EXTERNAL_FLASH_MEMORY_CS_PIN,0);
	for(uint32_t i=0; i<length-1; i++)
	{
		spiFlash->DATA.reg = (bytes[i]);        //envoi octet courant
		while(!(spi->INTFLAG.reg & 0x01));   //attente que Data Register Empty flag passe a 1
	}
	spiFlash->DATA.reg = (bytes[length]);        //envoi dernier octet
	while(! spiFlash->INTFLAG.bit.TXC);       //attente fin transmission
	digitalWrite(SERCOM_EXTERNAL_FLASH_MEMORY_CS_PORT,SERCOM_EXTERNAL_FLASH_MEMORY_CS_PIN,1); 
}

uint8_t readByteSamd21Spi(void)
{
	/*TODO*/
}

void readBytesSamd21Spi(uint8_t *bytes, uint32_t *length)
{
	/*TODO*/
}