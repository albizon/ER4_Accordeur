/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 25/01/17
* Version : 1.0
*/


#ifndef __INSTRUMENTS_H__
#define __INSTRUMENTS_H__

#include <string.h>


#define DELAY 1
#define ATTACK 2
#define HOLD 3
#define DECAY 4
#define SUSTAIN 5
#define RELEASE 6

typedef struct Instrument
{
	char *name;//Nom de l'instrument
	int nameSize;//Nombre de caractères dans le nom
	char isMIDIInstrument;//Dit si l'instrument fait parti de la norme MIDI
	char codeMIDI;//Code MIDI de l'instrument
	char isKnowInstrument;//Définit si il s'agit d'un instrument connu ou non
	
	int nbHarmoniques;//Nombre d'harmoniques dans le signal
	float harmoniquesAmplitudes[17]; //Amplitude relative des harmoniques du signal par rapport au fondamental en % ([0]-> Valeure moyenne; [1]-> fondammental)
	

	
	float delay; //durée entre le début de la note et le début de l'attaque en seconde
	float attack;//durée de la montée de la note jusqu'à so maximum en seconde
	float hold ;//durée où la note reste à son maximum en seconde
	float decay;//durée de descente de la note aprés le maximum vers le maintient en seconde
	float sustain;//amplitude relative de la note pendant sa pèriode de maintient par rapport au maximum en %
	float release;//durée de descente de la note jusqu'à zero aprés relachement de la note en seconde
};

typedef struct InstrumentSingleArray
{
	struct Instrument *array;
	int size;
};


int lengthInstrumentSingleArray(struct InstrumentSingleArray *vect)
{
	return vect->size;
}

struct InstrumentSingleArray* reallocInstrumentSingleArray(struct InstrumentSingleArray *vect, int size)
{
	struct InstrumentSingleArray *tmpPtr;
	struct Instrument *tmpIns;
		
	tmpPtr = realloc(vect, size*sizeof(&tmpIns));
	if(tmpPtr == NULL){free(vect);}
	else{vect=tmpPtr;}
	vect->size = size;
	
	free(tmpIns);
	free(tmpPtr);
	
	return vect;
}

/*
* Overview : permet de reconnaitre un instrument à partir de son enveloppe spectrale
* Author : BIZON Alexis
* Params :  -const float *env -> enveloppe à étudier
*			-const struct Instrument *listInstru -> liste des instruments connu
* Return : struct Instrument -> instrument reconnu
*/
//struct Instrument getInstru(const struct floatSingleArray *env, const struct InstrumentSingleArray *listInstru);


/*
* Overview : perment de reconnaitre la fréquence de la note jouée par un instrument
* Author : BIZON Alexis
* Params :  -const float *env -> enveloppe à étudier
*			-const float deltaFreq -> Espacement en Hz entre les différentes raies de l'enveloppe
* Return : float -> fréquence de la note jouée
*/
//float getFreqPlay(const struct floatSingleArray *env, const float deltaFreq);


/*
* Overview : perment de récupérer l'amplitude de la note
* Author : BIZON Alexis
* Params :  -const float *env -> enveloppe à étudier
*			-const float deltaFreq -> Espacement en Hz entre les différentes raies de l'enveloppe
* Return : float -> amplitude de la note en dB
*/
//float getLevelPlay(const struct floatSingleArray *env, const float deltaFreq);


/*
* Overview : permet de créer l'enveloppe spectrale d'un instrument pour une note d'une certaine fréquence
* Author : BIZON Alexis
* Params :  -const float freqNote -> fréquence de la note à jouer
*			-const struct Instrument instru -> instrument devant jouer la note
*			-float *env -> enveloppe spectrale à envoyer sur le DAC
* Return : none
*/
//void getEnveloppe(const float freqNote, const struct Instrument instru, struct floatSingleArray *env);


#endif
