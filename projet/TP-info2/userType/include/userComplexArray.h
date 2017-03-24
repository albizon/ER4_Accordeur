/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/


#ifndef __USERCOMPLEXARRAY_H__
#define __USERCOMPLEXARRAY_H__

#include "genericMemory.h"
#include <math.h>

#define HAVE_IMAGINARY 2
#define HAVE_NOT_IMAGINARY 1


typedef uint32_t userComplexArray;

void new_userComplexArray(userComplexArray *vect);

void setMemoryMode_userComplexArray(userComplexArray *vect, uint8_t memoryMode);

void resize_userComplexArray(userComplexArray *vect, uint32_t size);

void haveImag_userComplexArray(userComplexArray *vect, uint8_t haveImag);

void pushBack_userComplexArray(userComplexArray *vect, float imag, float real);

float getImag_userComplexArray(userComplexArray *vect, uint32_t i);

float getReal_userComplexArray(userComplexArray *vect, uint32_t i);

float getArg_userComplexArray(userComplexArray *vect, uint32_t i);

float getMod_userComplexArray(userComplexArray *vect, uint32_t i);

void setImag_userComplexArray(userComplexArray *vect, uint32_t i, float imag);

void setReal_userComplexArray(userComplexArray *vect, uint32_t i, float real);

void setArg_userComplexArray(userComplexArray *vect, uint32_t i, float arg);

void setMod_userComplexArray(userComplexArray *vect, uint32_t i, float mod);

#endif