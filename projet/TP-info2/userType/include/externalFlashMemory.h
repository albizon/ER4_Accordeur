/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/

#ifndef __EXTERNALFLASHMEMORY_H__
#define __EXTERNALFLASHMEMORY_H__

#define AT25DF081A //utilisation de la puce AT25DF081A pour la mémoire flash externe

#define MNIMUM_SIZE_IN_FLASH_MEMORY 4096//taille minimum d'allocation en octet

uint32_t __flashMemoryMap[FLASH_SIZE/MINIMUM_SIZE_IN_FLASH_MEMORY];


void initSpi(void);

void initSecondaryFlash(void);

void initExternalFlash(void);

void writeExternalFlash_uint32(uint32_t address, uint32_t val);

uint32_t readExternalFlash_uint32(uint32_t address);

uint32_t allocExternalFlash(uint32_t size);

void freeExternalFlash(uint32_t address, uint32_t size);

uint32_t reallocExternalFlash(uint32_t address, uint32_t lastSize, uint32_t newSize);

#endif