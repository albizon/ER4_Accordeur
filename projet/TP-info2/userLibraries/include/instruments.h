#ifndef __INSTRUMENTS_H__
#define __INSTRUMENTS_H__

#include <vector.h>
#include <string.h>


#define DELAY 1
#define ATTACK 2
#define HOLD 3
#define DECAY 4
#define SUSTAIN 5
#define RELEASE 6

struct Instrument
{
	string name;//Nom de l'instrument
	char isMIDIInstrument;//Dit si l'instrument fait parti de la norme MIDI
	char codeMIDI;//Code MIDI de l'instrument
	float H0 = 0;//Amplitude relative de la valeure moyenne du signal par rapport au fondamental en %
	float H1 = 100;//Amplitude relative du fondamental du signal par rapport au fondamental en %
	float H2;//Amplitude relative du second harmonique du signal par rapport au fondamental en %
	float H3;//Amplitude relative du troisième harmonique du signal par rapport au fondamental en %
	float H4;//Amplitude relative du quatrième harmonique du signal par rapport au fondamental en %
	float H5;//Amplitude relative du cinquième harmonique du signal par rapport au fondamental en %
	float H6;//Amplitude relative du sixième harmonique du signal par rapport au fondamental en %
	float H7;//Amplitude relative du septième harmonique du signal par rapport au fondamental en %
	float H8;//Amplitude relative du huitième harmonique du signal par rapport au fondamental en %
	float H9;//Amplitude relative du neuvième harmonique du signal par rapport au fondamental en %
	float H10;//Amplitude relative du dizième harmonique du signal par rapport au fondamental en %
	float H11;//Amplitude relative du onzième harmonique du signal par rapport au fondamental en %
	float H12;//Amplitude relative du douzième harmonique du signal par rapport au fondamental en %
	float H13;//Amplitude relative du treizième harmonique du signal par rapport au fondamental en %
	float H14;//Amplitude relative du quatorzième harmonique du signal par rapport au fondamental en %
	float H15;//Amplitude relative du quinzième harmonique du signal par rapport au fondamental en %
	float H16;//Amplitude relative du seizième harmonique du signal par rapport au fondamental en %
	
	float delay = 0;//durée entre le début de la note et le début de l'attaque en seconde
	float attack;//durée de la montée de la note jusqu'à so maximum en seconde
	float hold = 0;//durée où la note reste à son maximum en seconde
	float decay;//durée de descente de la note aprés le maximum vers le maintient en seconde
	float sustain;//amplitude relative de la note pendant sa pèriode de maintient par rapport au maximum en %
	float release;//durée de descente de la note jusqu'à zero aprés relachement de la note en seconde
};

struct Instrument getInstru(vector<float> const& env, vector<struct Instrument> const& listInstru);

float getFreqPlay(vector<float> const& env, struct Instrument instru);

vector<float> getEnveloppe(float freqNote, struct Instrument instru, char mode);//à revoir


#endif
