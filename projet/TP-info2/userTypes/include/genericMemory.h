/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/


#ifndef __GENERIC_H__
#define __GENERIC_H__

#include "externalFlashMemory.h"
#include "externalRamMemory.h"

#define AT25DF081A //utilisation de la puce AT25DF081A pour la mémoire flash externe

#ifndef USE_SAMD21//Si utilisation d'un SAMD21
	#include "sam.h"
	#define SERCOM_FOR_EXTERNALFLASH SERCOM5
	#define ARGS_FOR_EXTERNALFLASH_INIT {PORTA;13;PORTB;16;CONFIG_C;PORTB;22;CONFIG_D;PORTB;23;CONFIG_D}
	#define ARGGS_FOR_EXTERNALFLASH_OPS {PORTA;13}
#endif

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

uint32_t reallocGeneric(uint32_t address, uint32_t lastSize, uint32_t newSize, uint8_t device);

#endif
