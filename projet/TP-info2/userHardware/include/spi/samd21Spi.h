/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/

#ifndef __SAMD21SPI_H__
#define __SAMD21SPI_H__


	#include "sam.h"
	#include "pinAccess.h"
	#include "pinMux.h"
	#include "clock.h"
	
	
	#define SERCOM_EXTERNAL_FLASH_MEMORY SERCOM5
	
	//MISO//
	#define SERCOM_EXTERNAL_FLASH_MEMORY_MISO_PIN 16
	#define SERCOM_EXTERNAL_FLASH_MEMORY_MISO_PORT PORTB
	#define SERCOM_EXTERNAL_FLASH_MEMORY_MISO_CONFIG CONFIG_C
	
	//MOSI//
	#define SERCOM_EXTERNAL_FLASH_MEMORY_MOSI_PIN 22
	#define SERCOM_EXTERNAL_FLASH_MEMORY_MOSI_PORT PORTB
	#define SERCOM_EXTERNAL_FLASH_MEMORY_MOSI_CONFIG CONFIG_D
	
	//SCK//
	#define SERCOM_EXTERNAL_FLASH_MEMORY_SCK_PIN 23
	#define SERCOM_EXTERNAL_FLASH_MEMORY_SCK_PORT PORTB
	#define SERCOM_EXTERNAL_FLASH_MEMORY_SCK_CONFIG CONFIG_D
	
	//CS//
	#define SERCOM_EXTERNAL_FLASH_MEMORY_CS_PIN 13
	#define SERCOM_EXTERNAL_FLASH_MEMORY_CS_PORT PORTA
	

void initSamd21Spi(void);

void writeByteSamd21Spi(uint8_t byte);

void writeBytesSamd21Spi(uint8_t *bytes, uint32_t length);

uint8_t readByteSamd21Spi(void);

void readBytesSamd21Spi(uint8_t *bytes, uint32_t *length);

#endif
