/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/

#ifndef __SAMD21SPI_H__
#define __SAMD21SPI_H__

#ifndef USE_SAMD21
	#include "samd21Spi.h"
#endif

void init_spi(void *interface, uint32_t *args);

void writeByte_spi(void *interface, uint32_t *args, uint8_t byte);

void writeBytes_spi(void *interface, uint32_t *args, uint8_t *bytes, uint32_t length);

uint8_t readByte_spi(void *interface, uint32_t *args);

void readBytes_spi(void *interface, uint32_t *args, uint8_t *bytes, uint32_t *length);

#endif