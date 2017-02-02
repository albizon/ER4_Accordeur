/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/


#include "generic.h"

void writeFlash_uint32(uint32_t address, uint32_t val)
{
	
}

uint32_t readFlash_uint32(uint32_t address)
{
	
}

uint32_t allocFlash(uint32_t size)
{
	
}

void freeFlash(uint32_t address, uint32_t size)
{
	
}

uint32_t reallocFlash(uint32_t address, uint32_t lastSize, , uint32_t newSize)
{
	freeFlash(address, lastSize);
	return allocFlash(newSize);
}
