/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/

#include "externalRamMemory.h"




void initExternalRam(void)
{
	initSpi();
	initCircuitRam();
}




uint32_t reallocExternalRam(uint32_t address, uint32_t lastSize, uint32_t newSize)
{
	freeExternalRam(address, lastSize);
	return allocExternalRam(newSize);
}