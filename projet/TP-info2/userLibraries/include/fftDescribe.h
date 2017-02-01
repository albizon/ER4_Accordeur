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
};

typedef struct floatDoubleArray{
  float** array;
  int sizeDimX;
  int sizeDimY;
};

int lengthfloatSingleArray(struct floatSingleArray *vect){
  return vect->size;
}

int lengthfloatDoubleArray(struct floatDoubleArray *vect){
  return (vect->sizeDimX*vect->sizeDimY);
}


struct floatSingleArray* reallocfloatSingleArray (struct floatSingleArray *vect, const int size)
{
  float *tempPtr;
  tempPtr = realloc(vect->array, size);
  if(tempPtr==NULL){free(vect->array);}
  else{vect->array = tempPtr;}
  vect->size=size;
}

struct floatDoubleArray* reallocfloatDoubleArray (struct floatDoubleArray *vect, const int *size)
{
  float *tempPtr;
  tempPtr = realloc(vect->array, size[0]*sizeof(vect->array));
  if(tempPtr==NULL){free(vect->array);}
  else{vect->array = tempPtr;}
  vect->sizeDimX=size;
  
  for(int i=0 ; i < size[0] ; i++)
	{
		tempPtr = realloc(*vect->array, size[1] * sizeof(vect->array[i]));
		if(tempPtr == NULL) free(vect->array[i]);
		else  vect->array[i] = tempPtr; 
		vect->sizeDimY=size[1];
	}
}

void pushBackfloatDoubleArray(struct floatDoubleArray *vect, const struct floatSingleArray *line)
{
	struct floatDoubleArray *tmpArray;
	tmpArray = reallocfloatDoubleArray(tmpArray, (vect->sizeDimX)+1);
	for(int i = 0; i<vect->sizeDimX; i++)
	{
		tmpArray->array[i] = vect->array[i];
	}
	tmpArray->array[vect->sizeDimX]=line;
	vect= reallocfloatDoubleArray(vect, (vect->sizeDimX)+1);
	for(int i =0; i<(vect->sizeDimX)+1; i++)
	{
		vect->array[i] = tmpArray->array[i];
	}
	vect->sizeDimX++;
	free(tmpArray);
}

void pushBackfloatSingleArray(struct floatSingleArray *vect, const float line)
{
	struct floatSingleArray *tmpArray;
	tmpArray = reallocfloatSingleArray(tmpArray, lengthfloatSingleArray(vect)+1);
	for(int i = 0; i<lengthfloatSingleArray(vect); i++)
	{
		tmpArray->array[i] = vect->array[i];
	}
	tmpArray->array[vect->size]=line;
	vect= reallocfloatSingleArray(vect, lengthfloatSingleArray(vect)+1);
	for(int i =0; i<lengthfloatSingleArray(vect)+1; i++)
	{
		vect->array[i] = tmpArray->array[i];
	}
	vect->size++;
	free(tmpArray);
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
void complexLinearToComplexExponential(const struct floatSingleArray *real, const struct floatSingleArray *imag, struct floatSingleArray *mod, struct floatSingleArray *arg);


/*
* Overview : Conversion d'un nombre complexe de la forme mod*exp(j*arg) vers la forme a + j*b
* Author : BIZON Alexis
* Params :  -const float mod -> module du nombre complexe à traiter
*			-const float arg -> argument du nombre complexe à traiter
*			-float *real -> partie réelle du nombre complexe traité 
*			-float *imag -> partie imaginaire du nombre complexe traité
* Return : none
*/
void complexExponentialToComplexLinear(const struct floatSingleArray *mod, const struct floatSingleArray *arg, struct floatSingleArray *real, struct floatSingleArray *imag);


/*
* Overview : Sépare les enveloppes spectrales présentent dans une fft en fonction de l'argument présent sur chaques raies
* Author : BIZON Alexis
* Params :  -const float *mod -> module du nombre complexe à traiter
*			-const float *arg -> argument du nombre complexe à traiter
*			-float **envs -> tableau des enveloppes différenciées par leur argument
* Return : none
*/
void extractEnveloppes(const struct floatSingleArray *mod, const struct floatSingleArray *arg, struct floatDoubleArray **envs);




#endif
