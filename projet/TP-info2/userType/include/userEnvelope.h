/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/


#ifndef __USERENVELOPE_H__
#define __USERENVELOPE_H__

#include "genericMemory.h"

#define INDEX_FONDAMENTAL 1
#define INDEX_OFFSET 0

typedef uint32_t userEnvelope;


void new_userEnvelope(userEnvelope *vect);

void setMemoryMode_userEnvelope(userEnvelope *vect, uint8_t memoryMode);

void resize_userEnvelope(userEnvelope *vect, uint32_t size);

void getSize_userEnvelope(userEnvelope *vect);

void pushBack_userEnvelope(userEnvelope *vect, float mod);

float getMod_userEnvelope(userEnvelope *vect, uint32_t i);

float getFreqFond_userEnvelope(userEnvelope *vect);

void setMod_userEnvelope(userEnvelope *vect, uint32_t i, float mod);

void setFreqFond_userEnvelope(userEnvelope *vect, float freqFond);

#endif