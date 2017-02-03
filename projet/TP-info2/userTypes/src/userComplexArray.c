/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/


#include "userComplexArray.h"

void new_userComplexArray(userComplexArray *vect)
{
	vect = malloc(4*sizeof(&vect));
	vect[0]=USE_NOT_MEMORY;
	vect[1]=1;
	vect[2]=HAVE_NOT_IMAGINARY;
}

void setMemoryMode_userComplexArray(userComplexArray *vect, uint8_t memoryMode)
{
	freeGeneric(vect[3], vect[1], vect[0]);
	vect[3] = allocGeneric(vect[1]*vect[2], memoryMode);
	vect[0]=memoryMode;
}

void resize_userComplexArray(userComplexArray *vect, uint32_t size)
{
	vect[3] = reallocGeneric(vect[3], vect[1]*vect[2], size*vect[2], vect[0]);
	vect[1]=size;
}


void setHaveImag_userComplexArray(userComplexArray *vect, uint8_t haveImag)
{
	vect[3] = reallocGeneric(vect[3], vect[1]*vect[2], vect[1]*haveImag, vect[0]);
	vect[2]=haveImag;
}

uint8_t getHaveImag_userComplexArray(userComplexArray *vect)
{
	return vect[2]&0xFF;
}

uint32_t getSize_userComplexArray(userComplexArray *vect)
{
	return vect[1];
}

void pushBack_userComplexArray(userComplexArray *vect, float imag, float real)
{
	
}

float getImag_userComplexArray(userComplexArray *vect, uint32_t i)
{
	return readGeneric((vect[3]+vect[1]+i), vect[0]);
}

float getReal_userComplexArray(userComplexArray *vect, uint32_t i)
{
	return readGeneric((vect[3]+i), vect[0]);
}

float getArg_userComplexArray(userComplexArray *vect, uint32_t i)
{
	float imag = readGeneric((vect[3]+vect[1]+i), vect[0]);
	float real = readGeneric((vect[3]+i), vect[0]);
	
	return atan(imag/real);
}

float getMod_userComplexArray(userComplexArray *vect, uint32_t i)
{
	float imag = readGeneric((vect[3]+vect[1]+i), vect[0]);
	float real = readGeneric((vect[3]+i), vect[0]);
	
	return sqrt((imag*imag)+(real*real));
}

void setImag_userComplexArray(userComplexArray *vect, uint32_t i, float imag)
{
	writeGeneric((vect[3]+vect[1]+i), imag, vect[0]);
}

void setReal_userComplexArray(userComplexArray *vect, uint32_t i, float real)
{
	writeGeneric((vect[3]+i), real, vect[0]);
}

void setArg_userComplexArray(userComplexArray *vect, uint32_t i, float arg)
{
	float imag = readGeneric((vect[3]+vect[1]+i), vect[0]);
	float real = readGeneric((vect[3]+i), vect[0]);
	float mod;
	
	mod = sqrt((imag*imag)+(real*real));
	real = mod*cos(arg);
	imag = mod*sin(arg);
	
	writeGeneric((vect[3]+vect[1]+i), imag, vect[0]);
	writeGeneric((vect[3]+i), real, vect[0]);
}

void setMod_userComplexArray(userComplexArray *vect, uint32_t i, float mod)
{
	float imag = readGeneric((vect[3]+vect[1]+i), vect[0]);
	float real = readGeneric((vect[3]+i), vect[0]);
	float arg;
	
	arg = atan(imag/real);
	real = mod*cos(arg);
	imag = mod*sin(arg);
	
	writeGeneric((vect[3]+vect[1]+i), imag, vect[0]);
	writeGeneric((vect[3]+i), real, vect[0]);
}

void duplicate_userComplexArray(userComplexArray *in, userComplexArray *out)
{
	uint32_t size = getSize_userComplexArray(in);
	uint8_t imaginaryState = getHaveImag_userComplexArray(in);
	resize_userComplexArray(out, size);
	setHaveImag_userComplexArray(out, imaginaryState);
	for(int i =0; i<size; i++)
	{
		setImag_userComplexArray(in, i, getImag_userComplexArray(out, i));
		if(imaginaryState==HAVE_IMAGINARY){setReal_userComplexArray(in, i, getReal_userComplexArray(out, i));}
	}
}