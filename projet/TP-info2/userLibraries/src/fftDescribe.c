/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 25/01/17
* Version : 1.0
*/

#include "fftDescribe.h"




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

void extractOneEnvelope(userComplexArray *complexVect, userEnvelope *env, uint8_t nbHarm, float deltaFreq)
{
	resize_userEnvelope(env, nbHarm);
	uint32_t spectreSize = getSize_userComplexArray(complexVect);
	uint8_t fondIsFind = FALSE;
	uint32_t i =1;
	uint32_t indexFond = 0;
	
	setMod_userEnvelope(userEnvelope env, INDEX_OFFSET, getArg_userComplexArray(complexVect, 0));
	
	while((i<spectreSize) && (fondIsFind==FALSE))
	{
		if(getArg_userComplexArray(complexVect, i)!=0)
		{
			fondIsFind = TRUE;
			indexFond = i;
		}
		i++
	}
	
	if(fondIsFind==TRUE)
	{
		setMod_userEnvelope(userEnvelope env, INDEX_FONDAMENTAL, getArg_userComplexArray(complexVect, i));
		setFreqFond_userEnvelope(env, i*deltaFreq);
		for(uint8_t j=0; j<nbHarm; j++)
		{
			if((j*i)=<spectreSize)
			{
				setMod_userEnvelope(userEnvelope env, j, getArg_userComplexArray(complexVect, (i*j)));
			}
		}
	}
	
}
