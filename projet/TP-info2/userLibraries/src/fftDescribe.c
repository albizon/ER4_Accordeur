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
* Params :  -const vector<float> real -> partie réelle du nombre complexe à traiter
*			-const vector<float> imag -> partie imaginaire du nombre complexe à traiter
*			-vector<float> *mod -> module du nombre complexe traité
*			-vector<float> *arg -> argument du nombre complexe traité
* Return : none
*/
void complexLinearToComplexExponential(const vector<float> real, const vector<float> imag, vector<float> *mod, vector<float> *arg)
{

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
void complexExponentialToComplexLinear(const vector<float> mod, const vector<float> arg, vector<float> *real, vector<float> *imag)
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
void extractEnveloppes(const vector<float> mod, const vector<float> arg, vector<vector<float>> *envs)
{

}
