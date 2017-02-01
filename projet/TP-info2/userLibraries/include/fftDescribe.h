/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 25/01/17
* Version : 1.0
*/


#ifndef __FFTDESCRIBE_H__
#define __FFTDESCRIBE_H__

#include "define.h"

typedef struct floatSingleArray{
  float* array;
  int size;
}struct;

typedef struct floatDoubleArray{
  float** array;
  int sizeDimX;
  int sizeDimY;
}struct;

int length(floatSingleArray vect){
  return vect->size;
}

int length(floatDoubleArray vect){
  return (vect->sizeDimX*vect->sizeDimY);
}


floatSingleArray* realloc (floatSingleArray *vect, const int size)
{
  float *tempPtr;
  tempPtr = realloc(vect->array, size);
  if(tempPtr==NULL){free(vect->array);}
  else{vect->array = tempPtr;}
  vect->size=size;
}

floatDoubleArray* realloc (floatDoubleArray *vect, const int *size)
{
  float *tempPtr;
  tempPtr = realloc(vect->array, size[0]*sizeof(vect->*array));
  if(tempPtr==NULL){free(vect->array);}
  else{vect->array = tempPtr;}
  vect->sizeDimX=size;
  
  for(int i=0 ; i < size[0] ; i++)
	{
		tempPtr = realloc(*envs->array, size[1] * sizeof(vect->**array));
		if(tempPtr == NULL) free(vect->array[i]);
		else  vect->array[i] = tempPtr; 
		vect->sizeDimY=size[1];
}
}

/*
* Overview : Conversion d'un nombre complexe de la forme a + j*b vers la forme mod*exp(j*arg)
* Author : BIZON Alexis
* Params :  -const float *real -> partie réelle du nombre complexe à traiter
*			-const float *imag -> partie imaginaire du nombre complexe à traiter
*			-float *mod -> module du nombre complexe traité
*			-float *arg -> argument du nombre complexe traité
* Return : none
*/
void complexLinearToComplexExponential(const floatSingleArray *real, const floatSingleArray *imag, floatSingleArray *mod, floatSingleArray *arg);


/*
* Overview : Conversion d'un nombre complexe de la forme mod*exp(j*arg) vers la forme a + j*b
* Author : BIZON Alexis
* Params :  -const float mod -> module du nombre complexe à traiter
*			-const float arg -> argument du nombre complexe à traiter
*			-float *real -> partie réelle du nombre complexe traité 
*			-float *imag -> partie imaginaire du nombre complexe traité
* Return : none
*/
void complexExponentialToComplexLinear(const floatSingleArray *mod, const floatSingleArray *arg, floatSingleArray *real, floatSingleArray *imag);


/*
* Overview : Sépare les enveloppes spectrales présentent dans une fft en fonction de l'argument présent sur chaques raies
* Author : BIZON Alexis
* Params :  -const float *mod -> module du nombre complexe à traiter
*			-const float *arg -> argument du nombre complexe à traiter
*			-float **envs -> tableau des enveloppes différenciées par leur argument
* Return : none
*/
void extractEnveloppes(const floatSingleArray *mod, const floatSingleArray *arg, floatDoubleArray **envs);




#endif
