/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/

#ifndef __SAMD21SPI_H__
#define __SAMD21SPI_H__

#include "samd21Spi.h"

void initSpi(void);

void writeByteSpi(uint8_t byte);

void writeBytesSpi(uint8_t *bytes, uint32_t length);

uint8_t readByteSpi(void);

void readBytesSpi(uint8_t *bytes, uint32_t *length);

#endif