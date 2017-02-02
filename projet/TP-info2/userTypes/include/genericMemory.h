/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/


#ifndef __GENERIC_H__
#define __GENERIC_H__

#include "externalFlashMemory.h"

#define USE_INTERNAL_RAM 1//Ecriture du tableau dans la ram interne
#define USE_EXTERNAL_FLASH 2//Ecriture du tableau dans la flash externe
#define USE_INTERNAL_FLASH 3//Ecriture du tableau dans la flash interne
#define USE_EXTERNAL_RAM 4//Ecriture du tableau dans la ram externe
#define USE_NOT_MEMORY 0//N'utilise pas de mémoire



////////////////////////////////////////////////////////////////////////////FUNCTIONS////////////////////

void _4BytesTo1Byte(uint32_t in, uint8_t *out);

uint32_t _1BytesTo4Byte(uint8_t *in);

void writeGeneric(uint32_t address, uint32_t val, uint8_t device);

uint32_t readGeneric(uint32_t address, uint8_t device);

uint32_t allocGeneric(uint32_t size, uint8_t device);

void freeGeneric(uint32_t address, uint32_t size, uint8_t device);

uint32_t reallocGeneric(uint32_t address, uint32_t lastSize, , uint32_t newSize, uint8_t device);

#endif