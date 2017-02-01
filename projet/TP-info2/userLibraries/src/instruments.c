
/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 25/01/17
* Version : 1.0
*/


#include "instruments.h"
#include "define.h"





/*
* Overview : permet de reconnaitre un instrument à partir de son enveloppe spectrale
* Author : BIZON Alexis
* Params :  -const float *env -> enveloppe à étudier
*			-const struct Instrument *listInstru -> liste des instruments connu
* Return : struct Instrument -> instrument reconnu
*/
struct Instrument getInstru(const struct floatSingleArray *env, const struct InstrumentSingleArray *listInstru)
{
	int nbInstrus = lengthInstrumentSingleArray(listInstru);
	int instruOk = FALSE;
	int i=0;
	int nbHarmoniquesOK =0;
	float coefH=0;
	float relativeCurrentH =0;
	int delta=1;
	struct Instrument instru;
	
	int size = sizeof(env);
	
	for(int i=1; i<size; i++)
	{
		if(env->array[i]==0) delta++;
	}
	while(instruOk == FALSE && i<nbInstrus)
	{
		//coefH=listInstru[i].harmoniquesAmplitudes[1]*PURCENT_TO_SCALAIRE/env[delta];
		for(int j=0; j<17; j++)
		{
			//relativeCurrentH = listInstru[i].harmoniquesAmplitudes[j];
			//if(relativeCurrentH !=0) {if(relativeCurrentH)}
		}
		i++;
	}
	if(instruOk==FALSE){instru.isKnowInstrument=FALSE;}
	return instru;
}

envAreKnowInstrument(const struct floatDoubleArray *inEnv, struct floatDoubleArray *outEnv, const struct InstrumentSingleArray *listInstru)
{
	struct Instrument *tempInstru;
	for(int i = 0; i<inEnv->sizeDimX; i++)
	{
		&tempInstru = getInstru(inEnv->array[i], listInstru);
		if(tempInstru->isKnowInstrument==TRUE){pushBackfloatDoubleArray(outEnv, inEnv->array[i]);}
	}
	free(tempInstru);
}


/*
* Overview : perment de reconnaitre la fréquence de la note jouée par un instrument
* Author : BIZON Alexis
* Params :  -const float *env -> enveloppe à étudier
*			-const float deltaFreq -> Espacement en Hz entre les différentes raies de l'enveloppe
* Return : float -> fréquence de la note jouée
*/
float getFreqPlay(const struct floatSingleArray *env, const float deltaFreq)
{
	int delta=1;
	int size = lengthfloatSingleArray(env);
	for(int i=1; i<size; i++)
	{
		if(env->array[i]==0) delta++;
	}
	return (float)delta*deltaFreq;	
}


/*
* Overview : perment de récupérer l'amplitude de la note
* Author : BIZON Alexis
* Params :  -const float *env -> enveloppe à étudier
*			-const float deltaFreq -> Espacement en Hz entre les différentes raies de l'enveloppe
* Return : float -> amplitude de la note en dB
*/
float getLevelPlay(const struct floatSingleArray *env, const float deltaFreq)
{
	int delta=1;
	int size = lengthfloatSingleArray(env);
	for(int i=1; i<size; i++)
	{
		if(env->array[i]==0) delta++;
	}
	return 20*log10(env->array[delta]);	
}


/*
* Overview : permet de créer l'enveloppe spectrale d'un instrument pour une note d'une certaine fréquence
* Author : BIZON Alexis
* Params :  -const float freqNote -> fréquence de la note à jouer
*			-const struct Instrument instru -> instrument devant jouer la note
*			-float *env -> enveloppe spectrale à envoyer sur le DAC
* Return : none
*/
void getEnveloppe(const float freqNote, const struct Instrument instru, struct floatSingleArray *env)
{
	
}

