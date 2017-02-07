/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/

#include "userEnvelope.h"


void new_userEnvelope(userEnvelope *vect)
{
	vect = malloc(4*sizeof(&vect));
	vect[0]=USE_NOT_MEMORY;
	vect[1]=1;
	vect[2]=0;
}

void setMemoryMode_userEnvelope(userEnvelope *vect, uint8_t memoryMode)
{
	freeMemory(vect[3], vect[1], vect[0]);
	vect[3] = allocMemory(vect[1]*vect[2], memoryMode);
	vect[0]=memoryMode;
}

void resize_userEnvelope(userEnvelope *vect, uint32_t size)
{
	vect[3] = reallocMemory(vect[3], vect[1]*vect[2], size*vect[2], vect[0]);
	vect[1]=size;
}

void getSize_userEnvelope(userEnvelope *vect)
{
	return vect[1];
}

void pushBack_userEnvelope(userEnvelope *vect, float mod)
{
	
}


float getMod_userEnvelope(userEnvelope *vect, uint32_t i)
{
	return readMemory((vect[3]+i), vect[0]);
}

float getFreqFond_userEnvelope(userEnvelope *vect)
{
	return vect[2];
}

void setMod_userEnvelope(userEnvelope *vect, uint32_t i, float mod)
{
	writeMemory((vect[3]+i), mod, vect[0]);
}

void setFreqFond_userEnvelope(userEnvelope *vect, float freqFond)
{
	vect[2] = freqFond;
}