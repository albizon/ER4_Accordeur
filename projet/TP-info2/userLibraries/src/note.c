/*
 * note.c
 *
 * Created: 23/01/2017 09:14:40
 *  Author: simon
 */ 

















#include "note.h"

/*
* Overview : Arrondi une variable de type double
* Author : METAYER Simon
* Params : const double val -> Valeur à arrondir
* Return : double -> Valeur arrondie
*/
double arrondi (const double val)
{
	return floor (val+0.5);//floor renvoyant une troncature, on ajoute 0.5 à la valeure envoyée pour avoir l'arrondi
} 


/*
* Overview : Conversion d'une fréquence vers la note corescpondante
* Author : METAYER Simon
* Params : const float freq -> fréquence à étudier
* Return : char -> Note trouvée (voir defineNote.h pour voir la correspondance des notes)
*/
char noteSolver(const float freq)
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


/*
* Overview : Affichage du titre du projet sur la première ligne de l'afficheur
* Author : METAYER Simon
* Params : none
* Return : none
*/
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



/*
* Overview : renvoi la fréquence d'une note à un octave défini
* Author : METAYER Simon
* Params :  -const char note -> note à convertir
*           -const char degre -> octave de la note à convertir
* Return : float -> fréquence calculée
*/
float getFreqNote(const char note, const char degre)
{
	switch (note){
//En fonction de la note demandée, on utilise les différents calculs définits dans defineNote.h qui nous renvoies la fréquence d'une note en fonction de son octave
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

/*
* Overview : Permet de savoir si l'instrument est accordé à la note donnée
* Author : METAYER SImon
* Params :  -const char note -> note correspondante calculée
*           -const char degre -> octave de la note correspondant calculé
*           -const float freq -> fréquence mesurée
*           -const float error -> erreur absolue autorisée entre la fréquence mesurée et la fréquence désirée en Hz
* Return : char -> état de l'accord (soit trop haut, soit OK, soit trop bas)
*/
char accorder(const char note, const char degre, const float freq, const float error)
{
	float freq_calcul = getFreqNote(note, degre);//récupère la fréquence parfaite de la note envoyée
	//Si on est sur la fréquence parfaite à +- l'erreur, l'instrument est accordé à cette note
	if(((freq_calcul-error)<freq)&&(freq<(freq_calcul+error))) return OK_FREQ;
	//Sinon si on est en dessous de la fréquence parfaite moins l'erreur, on est trop bas
	else if(freq<(freq_calcul-error)) return LOW_FREQ;
	//Sinon si on est au dessus de la fréquence parfaite plus l'erreur, on trop haut
	else if((freq_calcul+error)<freq) return HIGH_FREQ;
}


/*
* Overview : Calcul l'erreur absolue autorisée à partir d'une erreur relative, de la fréquence de base et du delta de fréquence de la fft 
* Author : BIZON Alexis
* Params :  -const float relativeError -> Erreur relative autorisée
*           -const float noteFreq -> Fréquence autour de laquelle l'erreur absolue sera calculée
*           -const float deltaFreq -> Espacement entre les raies de la fft en Hz
* Return : float -> Erreur absolue autorisée
*/
float calculAbsError(const float relativeError, const float noteFreq, const float deltaFreq=0)
{
	//L'erreur absolue vaut la fréquence multipliée par l'erreur relative en scalaire(erreur en % /100) + l'erreur introduite par l'imprésision de la fft
	return (noteFreq*relativeError POURCENT_TO_SCALAIRE)+deltaFreq;
}
