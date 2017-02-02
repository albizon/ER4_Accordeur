/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 25/01/17
* Version : 2.0
*/


#ifndef __USERCOMPLEXARRAY_H__
#define __USERCOMPLEXARRAY_H__

#include "generic.h"

#define HAVE_IMAGINARY 2
#define HAVE_NOT_IMAGINARY 1


typedef uint32_t userComplexArray;

void setMemoryMode_userComplexArray(userComplexArray *vect, uint32_t memoryMode, uint32_t maxSize);

void resize_userComplexArray(userComplexArray *vect, uint32_t size, uint32_t maxSize);

void haveImag_userComplexArray(userComplexArray *vect, int haveImag);

void pushBack_userCOmplexArray(userComplexArray *vect, float imag, float real);

float getImag_userComplexArray(userComplexArray *vect, int i);

float getReal_userComplexArray(userComplexArray *vect, int i);

float getArg_userComplexArray(userComplexArray *vect, int i);

float getMod_userComplexArray(userComplexArray *vect, int i);

void setImag_userComplexArray(userComplexArray *vect, int i, float imag);

void setReal_userComplexArray(userComplexArray *vect, int i, float real);

void setArg_userComplexArray(userComplexArray *vect, int i, float arg);

void setMod_userComplexArray(userComplexArray *vect, int i, float mod);

#endif