/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/

#ifndef __EXTERNALRAMMEMORY_H__
#define __EXTERNALRAMMEMORY_H__

#include "genericMemory.h"

#ifndef 23LCV1024
	#include "23LCV1024.h"
#endif

#define ALLOCATION_SIZE_IN_RAM_MEMORY 256//taille minimum d'allocation en octet


uint32_t __ramMemoryMap[BITMAP_SIZE/4];


void initCircuitRam(void);

void initExternalRam(void);

void writeExternalRam_uint32(uint32_t address, uint32_t val);

uint32_t readExternalRam_uint32(uint32_t address);

uint32_t allocExternalRam(uint32_t size);

void freeExternalRam(uint32_t address, uint32_t size);

uint32_t reallocExternalRam(uint32_t address, uint32_t lastSize, uint32_t newSize);

#endif
