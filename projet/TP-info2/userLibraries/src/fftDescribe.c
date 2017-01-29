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
* Params :  -const vector<float> real -> partie réelle du nombre complexe à traiter
*			-const vector<float> imag -> partie imaginaire du nombre complexe à traiter
*			-vector<float> *mod -> module du nombre complexe traité
*			-vector<float> *arg -> argument du nombre complexe traité
* Return : none
*/
void complexLinearToComplexExponential(const float *real, const float *imag, float *mod, float *arg)
{
	
	if(sizeof(&real)>sizeof(&imag)) int size = sizeof(&imag);
	else int size = sizeof(&real);
	
	float *tempPtr;
	
	tempPtr = realloc(mod, size);
	if(tempPtr == NULL)free(mod);
	else mod = tempPtr;
	
	tempPtr = realloc(arg, size);
	if(tempPtr == NULL)free(arg);
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
* Params :  -const vector<float> mod -> module du nombre complexe à traiter
*			-const vector<float> arg -> argument du nombre complexe à traiter
*			-vector<float> *real -> partie réelle du nombre complexe traité 
*			-vector<float> *imag -> partie imaginaire du nombre complexe traité
* Return : none
*/
void complexExponentialToComplexLinear(const float *mod, const float *arg, float *real, float *imag)
{

}

/*
* Overview : Sépare les enveloppes spectrales présentent dans une fft en fonction de l'argument présent sur chaques raies
* Author : BIZON Alexis
* Params :  -const vector<float> mod -> module du nombre complexe à traiter
*			-const vector<float> arg -> argument du nombre complexe à traiter
*			-vector<vector<float>> *envs -> tableau des enveloppes différenciées par leur argument
* Return : none
*/
void extractEnveloppes(const float *mod, const float *arg, float **envs)
{

}
