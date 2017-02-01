/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 25/01/17
* Version : 1.0
*/

#include "fftDescribe.h"


/*
* Overview : Conversion d'un nombre complexe de la forme a + j*b vers la forme mod*exp(j*arg)
* Author : BIZON Alexis
* Params :  -const float *real -> partie réelle du nombre complexe à traiter
*			-const float *imag -> partie imaginaire du nombre complexe à traiter
*			-float *mod -> module du nombre complexe traité
*			-float *arg -> argument du nombre complexe traité
* Return : none
*/
void complexLinearToComplexExponential(const struct floatSingleArray *real, const struct floatSingleArray *imag, struct floatSingleArray *mod, struct floatSingleArray *arg)
{
	__disable_irq();
	int size=0;
	if(lengthfloatSingleArray(real)>lengthfloatSingleArray(imag)) {size = lengthfloatSingleArray(imag);}
	else {size = lengthfloatSingleArray(real);}
	
	mod = reallocfloatSingleArray(mod, size);
	arg = reallocfloatSingleArray(arg, size);

	double module=0;
	float argument=0;
	
	for(int i=0; i<size; i++)
	{
		double re= pow(real->array[i],2);
		double im= pow(imag->array[i],2);
		module = re + im;
		module = (double)sqrt(module);
		argument = imag->array[i]/real->array[i];
		argument = atan(argument);
		mod->array[i]=(float)module;
		arg->array[i]=argument;
	}
	__enable_irq();
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
void complexExponentialToComplexLinear(const struct floatSingleArray *mod, const struct floatSingleArray *arg, struct floatSingleArray *real, struct floatSingleArray *imag)
{
	int size =0;
	if(lengthfloatSingleArray(mod)>lengthfloatSingleArray(arg)) {size = lengthfloatSingleArray(arg);}
	else {size = lengthfloatSingleArray(mod);}

	real = reallocfloatSingleArray(real, size);
	imag = reallocfloatSingleArray(imag, size);


	float a=0;
	float b=0;
	
	for(int i=0; i<size; i++)
	{
		a = mod->array[i]*cos(arg->array[i]);
		b = mod->array[i]*sin(arg->array[i]);
		real->array[i]=a;
		imag->array[i]=b;
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

void extractEnveloppes(const struct floatSingleArray *mod, const struct floatSingleArray *arg, struct floatDoubleArray **envs)
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
}
