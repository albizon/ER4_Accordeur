/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/

#ifndef __EXTERNALFLASHMEMORY_H__
#define __EXTERNALFLASHMEMORY_H__

#define AT25DF081A //utilisation de la puce AT25DF081A pour la mémoire flash externe

#ifndef AT25DF081A
	#include "AT25DF081A.h"
#endif

#include "stdint-gcc.h"
#include "genericMemory.h"



#ifndef USE_SAMD21//Si utilisation d'un SAMD21
	#include "sam.h"
#endif

#define BITMAP_SIZE 24914

#define ALLOCATION_SIZE_IN_FLASH_MEMORY 256//taille minimum d'allocation en octet

uint32_t __flashMemoryMap[BITMAP_SIZE/4];


void initCircuitFlash(uint32_t *args);

void initExternalFlash(void);

void writeExternalFlash_uint32(uint32_t address, uint32_t val);

uint32_t readExternalFlash_uint32(uint32_t address);

uint32_t allocExternalFlash(uint32_t size);

void freeExternalFlash(uint32_t address, uint32_t size);

uint32_t reallocExternalFlash(uint32_t address, uint32_t lastSize, uint32_t newSize);

#endif