/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/


#include "genericMemory.h"

void _4BytesTo1Byte(uint32_t in, uint8_t *out)
{
	out[0]=in&(0xFF<<0);
	out[1]=in&(0xFF<<8);
	out[2]=in&(0xFF<<16);
	out[3]=in&(0xFF<<24);
}

uint32_t _1BytesTo4Byte(uint8_t *in)
{
	return (in[3]<<24)|(in[2]<<16)|(in[1]<<8)|(in[0]<<0);
}

void writeGeneric(uint32_t address, uint32_t val, uint8_t device)
{
	switch(device){
		case USE_INTERNAL_RAM :
			&address = val;
		break;
		case USE_EXTERNAL_FLASH
			writeExternalFlash_uint32(address, val);
		break;
		case USE_INTERNAL_FLASH
		
		break;
		case USE_EXTERNAL_RAM
		
		break;
		default :
		
		break;
	}
}

uint32_t readGeneric(uint32_t address, uint8_t device)
{
	uint32_t tmp =0;
	
	switch(device){
		case USE_INTERNAL_RAM :
			tmp = &address;
		break;
		case USE_EXTERNAL_FLASH
		 tmp = readExternalFlash_uint32(address);
		break;
		case USE_INTERNAL_FLASH
			tmp = ;
		break;
		case USE_EXTERNAL_RAM
		 tmp = ;
		break;
		default :
		 tmp = ;
		break;
	}
	
	return tmp;
}

uint32_t allocGeneric(uint32_t size, uint8_t device)
{
	uint32_t tmp =0;
	
	switch(device){
		case USE_INTERNAL_RAM :
			tmp = malloc(size*sizeof(uint32_t));
		break;
		case USE_EXTERNAL_FLASH
			tmp = allocExternalFlash(size);
		break;
		case USE_INTERNAL_FLASH
			tmp = ;
		break;
		case USE_EXTERNAL_RAM
			tmp = ;
		break;
		default :
			tmp = ;
		break;
	}
	
	return tmp;
}

void freeGeneric(uint32_t address, uint32_t size, uint8_t device)
{
	switch(device){
		case USE_INTERNAL_RAM :
			free(address);
		break;
		case USE_EXTERNAL_FLASH
			freeExternalFlash(address, size);
		break;
		case USE_INTERNAL_FLASH
		
		break;
		case USE_EXTERNAL_RAM
		
		break;
		default :
		
		break;
	}
}

uint32_t reallocGeneric(uint32_t address, uint32_t lastSize, , uint32_t newSize, uint8_t device)
{
	uint32_t tmp =0;
	
	switch(device){
		case USE_INTERNAL_RAM :
			tmp = realloc(address, newSize*sizeof(uint32_t));
		break;
		case USE_EXTERNAL_FLASH
			tmp = reallocExternalFlash(address, lastSize, newSize);
		break;
		case USE_INTERNAL_FLASH
			tmp = ;
		break;
		case USE_EXTERNAL_RAM
			tmp = ;
		break;
		default :
			tmp = ;
		break;
	}
	
	return tmp;
}
