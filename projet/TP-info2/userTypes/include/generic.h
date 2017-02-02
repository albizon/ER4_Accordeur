/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 25/01/17
* Version : 2.0
*/


#ifndef __GENERIC_H__
#define __GENERIC_H__

#define MEMORY_MODE_RAM 1//Ecriture du tableau dans la ram
#define MEMORY_MODE_FLASH_SAMD21 2//Ecriture du tableau dans la flash d'un samd21

#define START_ADDRESS_FLASH_MEMORY 128//Adresse de la première case où l'on peut écrire

#define FLASH_SIZE 4096//taille de la mémoire flash en octet

#define MNIMUM_SIZE_IN_FLASH_MEMORY 128//taille minimum d'allocation en octet

uint32_t __flashMemoryMap[FLASH_SIZE/MINIMUM_SIZE_IN_FLASH_MEMORY];

////////////////////////////////////////////////////////////////////////////FUNCTIONS////////////////////


void writeFlash_uint32(uint32_t address, uint32_t val);

uint32_t readFlash_uint32(uint32_t address);

uint32_t allocFlash(uint32_t size);

void freeFlash(uint32_t address, uint32_t size);

uint32_t reallocFlash(uint32_t address, uint32_t lastSize, , uint32_t newSize);

#endif