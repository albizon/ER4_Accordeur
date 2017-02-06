/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/

#ifndef __EXTERNALRAMMEMORY_H__
#define __EXTERNALRAMMEMORY_H__



#define ALLOCATION_SIZE_IN_RAM_MEMORY 256//taille minimum d'allocation en octet

#ifndef USE_SAMD21

  #define SERCOM_EXTERNAL_RAM SERCOM4

  #define SS_PORT_EXTERNAL_RAM PORTB
  #define SS_BIT_EXTERNAL_RAM 10

  #define MOSI_PORT_EXTERNAL_RAM PORTB
  #define MOSI_BIT_EXTERNAL_RAM 2
  #define MOSI_CONFIG_EXTERNAL_RAM CONFIG_C

  #define MISO_PORT_EXTERNAL_RAM PORTB
  #define MISO_BIT_EXTERNAL_RAM 1
  #define MISO_CONFIG_EXTERNAL_RAM CONFIG_C

  #define SCK_PORT_EXTERNAL_RAM PORTB
  #define SCK_BIT_EXTERNAL_RAM  3
  #define SCK_CONFIG_EXTERNAL_RAM CONFIG_C

  #define DIPO_EXTERNAL_RAM SAMD21_SPI_DOPO_012
  #define DOPO_EXTERNAL_RAM SAMD21_SPI_DIPO_1

#endif

uint32_t __ramMemoryMap[BITMAP_SIZE/4];


void initCircuitRam(void);

void initExternalRam(void);

void writeExternalRam_uint32(uint32_t address, uint32_t val);

uint32_t readExternalRam_uint32(uint32_t address);

uint32_t allocExternalRam(uint32_t size);

void freeExternalRam(uint32_t address, uint32_t size);

uint32_t reallocExternalRam(uint32_t address, uint32_t lastSize, uint32_t newSize);

#endif
