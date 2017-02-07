/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/

#include "userInstrument.h"

/*typedef struct Instrument
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
};*/