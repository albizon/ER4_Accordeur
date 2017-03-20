/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/

#include "AT25DF081A.h"


#ifndef AT25DF081A

void __writeAT25DF081AByte(uint8_t byte, uint32_t address)
{
	/*TODO*/
}

uint8_t __readAT25DF081AByte(uint32_t address)
{
	/*TODO*/
}

void __getBitmapAT25DF081A(uint32_t *bitmap)
{
	uint8_t tmp[BITMAP_SIZE];
	for(uint32_t i=0; i<BITMAP_SIZE; i++)
	{
		tmp[i]=__readAT25DF081AByte(BITMAP_ADDRESS+i);
	}
	uint8_t tmp2[4]
	for(uint32_t i=0; i<BITMAP_SIZE/4; i++)
	{
		tmp2[0] = tmp[4*i];
		tmp2[1] = tmp[4*i+1];
		tmp2[2] = tmp[4*i+2];
		tmp2[3] = tmp[4*i+3];
		bitmap[i] = _1BytesTo4Byte(tmp2);
	}
}

void __setBitmapAT25DF081A(uint32_t *bitmap)
{
	uint8_t tmp[BITMAP_SIZE];
	
	uint8_t tmp2[4];
	for(uint32_t i=0; i<BITMAP_SIZE/4; i++)
	{
		_4BytesTo1Byte(bitmap[i], tmp2);
		__writeAT25DF081AByte(tmp2[0], BITMAP_ADDRESS+(4*i));
		__writeAT25DF081AByte(tmp2[1], BITMAP_ADDRESS+(4*i+1));
		__writeAT25DF081AByte(tmp2[2], BITMAP_ADDRESS+(4*i+2));
		__writeAT25DF081AByte(tmp2[3], BITMAP_ADDRESS+(4*i+3));
	}
}

void initCircuitFlash(uint32_t *args)
{
	__getBitmapAT25DF081A(__flashMemoryMap);
}

void writeExternalFlash_uint32(uint32_t address, uint32_t val)
{
	uint8_t tmp[4];
	
	_4BytesTo1Byte(val, tmp);
	__writeAT25DF081AByte(tmp2[0], (address*4)+0);
	__writeAT25DF081AByte(tmp2[1], (address*4)+1);
	__writeAT25DF081AByte(tmp2[2], (address*4)+2);
	__writeAT25DF081AByte(tmp2[3], (address*4)+3);
}


uint32_t readExternalFlash_uint32(uint32_t address)
{
	uint8_t tmp[4];
	
	tmp[0]=__readAT25DF081AByte((address*4)+0);
	tmp[1]=__readAT25DF081AByte((address*4)+1);
	tmp[2]=__readAT25DF081AByte((address*4)+2);
	tmp[3]=__readAT25DF081AByte((address*4)+3);
	
	return _1BytesTo4Byte(tmp);
}


uint32_t allocExternalFlash(uint32_t size)
{
	uint32_t tmp =0;
	/*TODO*/
	__setBitmapAT25DF081A(__flashMemoryMap);
	return tmp;
}


void freeExternalFlash(uint32_t address, uint32_t size)
{
	uint32_t startAddress = address/ALLOCATION_SIZE_FLASH;
	uint32_t endAddress = startAddress+size;
	for(uint32_t i=startAddres; i<endAddress)
	{
		__flashMemoryMap[i]=i&(0x1<<i);/*TODO*/
	}
	__setBitmapAT25DF081A(__flashMemoryMap);
}

#endif
