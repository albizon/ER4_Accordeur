/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/

#include "externalFlashMemory.h"




void initExternalFlash(void)
{
	initSpi();
	initCircuitFlash();
}




uint32_t reallocExternalFlash(uint32_t address, uint32_t lastSize, uint32_t newSize)
{
	freeExternalFlash(address, lastSize);
	return allocExternalFlash(newSize);
}

