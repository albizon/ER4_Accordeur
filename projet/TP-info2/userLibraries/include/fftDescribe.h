/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 25/01/17
* Version : 1.0
*/



#ifndef __FFTDESCRIBE_H__
#define __FFTDESCRIBE_H__

#include "define.h"
#include "fftDescribe.h"

typedef struct floatSingleArray{
  float* array;
  int size;
};

//struct floatSingleArray floatSingleArray;

typedef struct floatDoubleArray{
  float** array;
  int sizeDimX;
  int sizeDimY;
};

//struct floatSingleArray floatSingleArray;

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
