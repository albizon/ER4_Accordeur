/*
 * note.c
 *
 * Created: 23/01/2017 09:14:40
 *  Author: simon
 */ 

#include "note.h"

double arrondi (double val) // Fonction arrondi
{
	return floor (val+0.5);
} 

char noteSolver(float freq)
{
	char rang;
	double tmp = arrondi((log10( pow( ((double)freq/LA_440_FREQ) , 12 ) ) / log10(2)));
	
	if (tmp<0)
	{
		 rang = (char)(0-tmp);
		 return rang =(char)((10-(rang % 12)));
	}
	else if (tmp>=0) 
	{
		rang = (char)tmp;
		return rang =(char)((((char)rang+10))%12);
	}
}

char degreSolver(float freq)
{
	char rang;
	double tmp = arrondi((log10( pow( ((double)freq/LA_440_FREQ) , 12 ) ) / log10(2)));
	if (tmp<0)
	{
		 rang  = (char)(0-tmp);
		 return 4-(char)arrondi((rang+10)/12);
	}
	else if (tmp>=0)
	{
		 rang = (char)tmp;
		 return (char)arrondi((rang+10)/12)+3;
	}
	
	
}

float getFreqNote(char note, char degre)
{
	switch (note){
		case NUM_DO :
			return DO(degre);
		break;
		case NUM_REb :
			return REb(degre);
		break;
		case NUM_RE :
			return RE(degre);
		break;
		case NUM_MIb :
			return MIb(degre);
		break;
		case NUM_MI :
			return MI(degre);
		break;
		case NUM_FA :
			return FA(degre);
		break;
		case NUM_SOLb :
			return SOLb(degre);
		break;
		case NUM_SOL :
			return SOL(degre);
		break;
		case NUM_LAb :
			return LAb(degre);
		break;
		case NUM_LA :
			return LA(degre);
		break;
		case NUM_SIb :
			return SIb(degre);
		break;
		case NUM_SI :
			return SI(degre);
		break;
		default :
			return 0;
		break;
	}
}

char accorder(char note, char degre, float freq, float plage)
{
	float freq_calcul = getFreqNote(note, degre);
	if(((freq_calcul-plage)<freq)&&(freq<(freq_calcul+plage))) return OK_FREQ;
	else if(freq<(freq_calcul+plage)) return LOW_FREQ;
	else if((freq_calcul-plage)<freq) return HIGH_FREQ;
}

float calculAbsError(float relativeError, float noteFreq)
{
	return noteFreq*relativeError/100;
}
