/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 25/01/17
* Version : 2.0
*/


#include "userComplexArray.h"
#include "math.h"


void setMemoryMode_userComplexArray(userComplexArray *vect, uint32_t memoryMode)
{
	vect = malloc(3*sizeof(&vect));
	vect[0]=memoryMode;
	vect[1]=1;
	vect[2]=HAVE_NOT_IMAGINARY;
	if(vect[0]==MEMORY_MODE_RAM) {vect[3] = malloc(vect[1]*vect[2]*sizeof(float));}
	else if(vect[0]==MEMORY_MODE_FLASH_SAMD21){ vect[3] = allocAddressFlash(vect[1]);}
}

void resize_userComplexArray(userComplexArray *vect, uint32_t size)
{
	if(vect[0]==MEMORY_MODE_RAM) {vect[3] = realloc(vect[3], size*vect[2]*sizeof(float));}
	else if(vect[0]==MEMORY_MODE_FLASH_SAMD21){vect[3]=reallocFlash(vect[3], vect[1], size);}
	vect[1]=size;
}

void haveImag_userComplexArray(userComplexArray *vect, int haveImag)
{
	if(vect[0]==MEMORY_MODE_RAM) {vect[3] = realloc(vect[3], vect[1]*vect[2]*sizeof(float));}
	else if(vect[0]==MEMORY_MODE_FLASH_SAMD21){vect[3]=reallocFlash(vect[3], vect[1]*vect[2], vect[1]*haveImage);}
	vect[2]=haveImag;
}

uint32_t getSize_userComplexArray(userComplexArray *vect)
{
	return vect[1];
}

void pushBack_userComplexArray(userComplexArray *vect, float imag, float real)
{
	if(vect[0]==MEMORY_MODE_RAM){
		
	}
	else if(vect[0]==MEMORY_MODE_FLASH_SAMD21){
		
	}
}

float getImag_userComplexArray(userComplexArray *vect, int i)
{
	if(vect[0]==MEMORY_MODE_RAM){
		return vect[3][vect[1]+i];
	}
	else if(vect[0]==MEMORY_MODE_FLASH_SAMD21){
		return readFlash_uint32(vect[2]+vect[1]+i);
	}
}

float getReal_userComplexArray(userComplexArray *vect, int i)
{
	if(vect[0]==MEMORY_MODE_RAM){
		return vect[3][i];
	}
	else if(vect[0]==MEMORY_MODE_FLASH_SAMD21){
		return readFlash_uint32(vect[2]+i);
	}
}

float getArg_userComplexArray(userComplexArray *vect, int i)
{
	float imag, real;
	if(vect[0]==MEMORY_MODE_RAM){
		imag = vect[3][vect[1]+i];
		real = vect[3][i];
	}
	else if(vect[0]==MEMORY_MODE_FLASH_SAMD21){
		imag = readFlash_uint32(vect[2]+vect[1]+i);
		real = readFlash_uint32(vect[2]+i);
	}
	
	return atan(imag/real);
}

float getMod_userComplexArray(userComplexArray *vect, int i)
{
	float imag, real;
	if(vect[0]==MEMORY_MODE_RAM){
		imag = vect[3][vect[1]+i];
		real = vect[3][i];
	}
	else if(vect[0]==MEMORY_MODE_FLASH_SAMD21){
		imag = readFlash_uint32(vect[2]+vect[1]+i);
		real = readFlash_uint32(vect[2]+i);
	}
	return sqrt((imag*imag)+(real*real));
}

void setImag_userComplexArray(userComplexArray *vect, int i, float imag)
{
	if(vect[0]==MEMORY_MODE_RAM){
		vect[3][vect[1]+i]=imag;
	}
	else if(vect[0]==MEMORY_MODE_FLASH_SAMD21){
		writeFlash_uint32(vect[2]+vect[1]+i, imag);
	}
}

void setReal_userComplexArray(userComplexArray *vect, int i, float real)
{
	if(vect[0]==MEMORY_MODE_RAM){
		vect[3][i] = real;
	}
	else if(vect[0]==MEMORY_MODE_FLASH_SAMD21){
		writeFlash_uint32(vect[2]+i, real);
	}
}

void setArg_userComplexArray(userComplexArray *vect, int i, float arg)
{
	float imag, real, mod;
	if(vect[0]==MEMORY_MODE_RAM){
		imag = vect[3][vect[1]+i];
		real = vect[3][i];
	}
	else if(vect[0]==MEMORY_MODE_FLASH_SAMD21){
		imag = readFlash_uint32(vect[2]+vect[1]+i);
		real = readFlash_uint32(vect[2]+i);
	}
	
	mod = sqrt((imag*imag)+(real*real));
	real = mod*cos(arg);
	imag = mod*sin(arg);
	
	if(vect[0]==MEMORY_MODE_RAM){
		vect[3][vect[1]+i]=imag;
		vect[3][i] = real;
	}
	else if(vect[0]==MEMORY_MODE_FLASH_SAMD21){
		writeFlash_uint32(vect[2]+vect[1]+i, imag);
		writeFlash_uint32(vect[2]+i, real);
	}
}

void setMod_userComplexArray(userComplexArray *vect, int i, float mod)
{
	float imag, real, arg;
	if(vect[0]==MEMORY_MODE_RAM){
		imag = vect[3][vect[1]+i];
		real = vect[3][i];
	}
	else if(vect[0]==MEMORY_MODE_FLASH_SAMD21){
		imag = readFlash_uint32(vect[2]+vect[1]+i);
		real = readFlash_uint32(vect[2]+i);
	}
	
	arg = atan(imag/real);
	real = mod*cos(arg);
	imag = mod*sin(arg);
	
	if(vect[0]==MEMORY_MODE_RAM){
		vect[3][vect[1]+i]=imag;
		vect[3][i] = real;
	}
	else if(vect[0]==MEMORY_MODE_FLASH_SAMD21){
		writeFlash_uint32(vect[2]+vect[1]+i, imag);
		writeFlash_uint32(vect[2]+i, real);
	}
}