/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/

#include "externalRamMemory.h"




void initExternalRam(void)
{
	#ifndef USE_SAMD21
	initSpi(SERCOM_EXTERNAL_RAM, {SS_PORT_EXTERNAL_RAM;
				      SS_BIT_EXTERNAL_RAM;
				      MOSI_PORT_EXTERNAL_RAM;
				      MOSI_BIT_EXTERNAL_RAM;
				      MOSI_CONFIG_EXTERNAL_RAM;
				      MISO_PORT_EXTERNAL_RAM;
				      MISO_BIT_EXTERNAL_RAM;
				      MISO_CONFIG_EXTERNAL_RAM;
				      SCK_PORT_EXTERNAL_RAM;
				      SCK_BIT_EXTERNAL_RAM;
				      SCK_CONFIG_EXTERNAL_RAM;
				      SAMD21_SPI_MASTER_MODE;
				      DIPO_EXTERNAL_RAM;
				     DOPO_EXTERNAL_RAM});
	#endif
	initCircuitRam();
}




uint32_t reallocExternalRam(uint32_t address, uint32_t lastSize, uint32_t newSize)
{
	freeExternalRam(address, lastSize);
	return allocExternalRam(newSize);
}
