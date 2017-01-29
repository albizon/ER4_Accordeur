/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 25/01/17
* Version : 1.0
*/



#include "fftDescribe.h"
#include <math.h>



/*
* Overview : Conversion d'un nombre complexe de la forme a + j*b vers la forme mod*exp(j*arg)
* Author : BIZON Alexis
* Params :  -const float *real -> partie réelle du nombre complexe à traiter
*			-const float *imag -> partie imaginaire du nombre complexe à traiter
*			-float *mod -> module du nombre complexe traité
*			-float *arg -> argument du nombre complexe traité
* Return : none
*/
void complexLinearToComplexExponential(const float *real, const float *imag, float *mod, float *arg)
{
	
	if(sizeof(&real)>sizeof(&imag)) int size = sizeof(&imag);
	else int size = sizeof(&real);
	
	float *tempPtr;
	
	tempPtr = malloc(size * sizeof(*mod));
	if(tempPtr == NULL) free(mod);
	else mod = tempPtr;
	
	tempPtr = malloc(size * sizeof(*arg));
	if(tempPtr == NULL) free(arg);
	else arg = tempPtr;

	float module=0;
	float argument=0;
	
	for(int i=0; i<size; i++)
	{
		module = sqrt((real[i] * real[i]) + (imag[i] * imag[i]));
		argument = imag[i]/real[i];
		argument = arctan(argument);
		&mod[i]=module;
		&arg[i]=argument;
	}
}

/*
* Overview : Conversion d'un nombre complexe de la forme mod*exp(j*arg) vers la forme a + j*b
* Author : BIZON Alexis
* Params :  -const float mod -> module du nombre complexe à traiter
*			-const float arg -> argument du nombre complexe à traiter
*			-float *real -> partie réelle du nombre complexe traité 
*			-float *imag -> partie imaginaire du nombre complexe traité
* Return : none
*/
void complexExponentialToComplexLinear(const float *mod, const float *arg, float *real, float *imag)
{
	if(sizeof(&mod)>sizeof(&arg)) int size = sizeof(&arg);
	else int size = sizeof(&mod);
	
	float *tempPtr;
	
	tempPtr = malloc(size * sizeof(*real));
	if(tempPtr == NULL) free(real);
	else real = tempPtr;
	
	tempPtr = malloc(size * sizeof(*imag));
	if(tempPtr == NULL) free(imag);
	else imag = tempPtr;

	float a=0;
	float b=0;
	
	for(int i=0; i<size; i++)
	{
		a = mod[i]*cos(arg[i]);
		b = mod[i]*sin(arg[i]);
		&real[i]=a;
		&imag[i]=b;
	}
}

/*
* Overview : Sépare les enveloppes spectrales présentent dans une fft en fonction de l'argument présent sur chaques raies
* Author : BIZON Alexis
* Params :  -const float *mod -> module du nombre complexe à traiter
*			-const float *arg -> argument du nombre complexe à traiter
*			-float **envs -> tableau des enveloppes différenciées par leur argument
* Return : none
*/
void extractEnveloppes(const float *mod, const float *arg, float **envs)
{
	if(sizeof(&mod)>sizeof(&arg)) int size = sizeof(&arg);
	else int size = sizeof(&mod);
	
	float *tempPtr;
	
	float *args;
	
	tempPtr = malloc(size * sizeof(*args));
	if(tempPtr == NULL) free(args);
	else args = tempPtr;
	
	int nbDiffArgs = 0;
	
	for(int i =0; i<size; i++)
	{
		int diff =TRUE;
		for(int j =0; j<nbDiffArgs; j++) if (&arg== args[j]) diff=FALSE;
		if(diff == TRUE)args[nbDiffArgs++] = &arg;
	}
	
	
	tempPtr = malloc(nbDiffArgs * sizeof(*envs));
	if(tempPtr == NULL) free(envs);
	else envs = tempPtr;
	
	for(int i=0 ; i < nbDiffArgs ; i++)
	{
		tempPtr[i] = malloc(size * sizeof(*(envs[i])));
		if(tempPtr[i] == NULL)free(envs[i]);
		else envs[i] = tempPtr;
	}
	
	for(int i =0; i<nbDiffArgs; i++)
	{
		for(int j =0; j<size; j++)
		{
			if(arg[j] == args[i]) envs[i][j] = mod[j];
			else envs[i][j] =0;
		}
	}
	free(args);
}
