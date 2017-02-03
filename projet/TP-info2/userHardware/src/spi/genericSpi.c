/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/

#include "genericSpi.h"

void initSpi(void)
{
	#ifndef USE_SAMD21
		initSamd21Spi();
	#endif
}

void writeByteSpi(uint8_t byte)
{
	#ifndef USE_SAMD21
		writeByteSamd21Spi();
	#endif
}

void writeBytesSpi(uint8_t *bytes, uint32_t length)
{
	#ifndef USE_SAMD21
		writeSamd21Spi();
	#endif
}

uint8_t readByteSpi(void)
{
	#ifndef USE_SAMD21
		readByteSamd21Spi();
	#endif
}

void readBytesSpi(uint8_t *bytes, uint32_t *length)
{
	#ifndef USE_SAMD21
		readBytesSamd21Spi();
	#endif
}