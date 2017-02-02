/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 25/01/17
* Version : 2.0
*/


#ifndef __GENERIC_H__
#define __GENERIC_H__

#define MEMORY_MODE_RAM 1
#define MEMORY_MODE_FLASH 2

#define FLASH_SIZE 4000000//taille de la mémoire flash en octet

#define MNIMUM_SIZE_IN_FLASH_MEMORY 128//taille minimum d'allocation en octet

uint32_t __flashMemoryMap[FLASH_SIZE/MINIMUM_SIZE_IN_FLASH_MEMORY];

void writeFlash_uint32(uint32_t address, uint32_t val);

uint32_t readFlash_uint32(uint32_t address);

uint32_t getAddressFlash(uint32_t size);

void freeFlash(uint32_t address, uint32_t size);

#endif