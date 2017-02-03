/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 25/01/17
* Version : 2.0
*/

#include "define.h"




/*
* Overview : Sépare les enveloppes spectrales présentent dans une fft en fonction de l'argument présent sur chaques raies
* Author : BIZON Alexis
* Params :  -const float *mod -> module du nombre complexe à traiter
*			-const float *arg -> argument du nombre complexe à traiter
*			-float **envs -> tableau des enveloppes différenciées par leur argument
* Return : none
*/

/*void extractEnveloppes(const struct floatSingleArray *mod, const struct floatSingleArray *arg, struct floatDoubleArray **envs)
{
	int size = 0;
	if(lengthfloatSingleArray(mod)>lengthfloatSingleArray(arg)) {size = lengthfloatSingleArray(arg);}
	else {size = lengthfloatSingleArray(mod);}
	
	float *tempPtr;
	
	float *args;
	
	tempPtr = realloc(args, size * sizeof(*args));
	if(tempPtr == NULL) free(args);
	else args = tempPtr;
	
	int nbDiffArgs = 0;
	
	for(int i =0; i<size; i++)
	{
		int diff =TRUE;
		for(int j =0; j<nbDiffArgs; j++) {if (arg->array[i] == args[j]) {diff=FALSE;}}
		if(diff == TRUE)args[nbDiffArgs++] = arg->array[i];
	}
	float s[2] = {nbDiffArgs, size};
	envs = reallocfloatDoubleArray(envs, s);
	
	for(int i =0; i<nbDiffArgs; i++)
	{
		for(int j =0; j<size; j++)
		{
			//if(arg->array[j] == args[i]) envs->array[i][j] = mod->array[j];
			//else envs->array[i][j] =0;
		}
	}
	free(args);
}*/