/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/


#ifndef __USERCOMPLEXINTEGER16ARRAY_H__
#define __USERCOMPLEXINTEGER16ARRAY_H__

#include "genericMemory.h"
#include "userComplexArray.h"
#include <math.h>

#define HAVE_IMAGINARY 2
#define HAVE_NOT_IMAGINARY 1


typedef uint32_t userComplexInteger16Array;

void new_userComplexInteger16Array(userComplexArray *vect);

void setMemoryMode_userComplexInteger16Array(userComplexArray *vect, uint8_t memoryMode);

void resize_userComplexInteger16Array(userComplexArray *vect, uint32_t size);

void haveImag_userComplexInteger16Array(userComplexArray *vect, uint8_t haveImag);

void pushBack_userComplexInteger16Array(userComplexArray *vect, uint16_t imag, uint16_t real);

uint16_t getImag_userComplexInteger16Array(userComplexArray *vect, uint32_t i);

uint16_t getReal_userComplexInteger16Array(userComplexArray *vect, uint32_t i);

uint16_t getArg_userComplexInteger16Array(userComplexArray *vect, uint32_t i);

uint16_t getMod_userComplexInteger16Array(userComplexArray *vect, uint32_t i);

void setImag_userComplexInteger16Array(userComplexArray *vect, uint32_t i, uint16_t imag);

void setReal_userComplexInteger16Array(userComplexArray *vect, uint32_t i, uint16_t real);

void setArg_userComplexInteger16Array(userComplexArray *vect, uint32_t i, uint16_t arg);

void setMod_userComplexInteger16Array(userComplexArray *vect, uint32_t i, uint16_t mod);

#endif
