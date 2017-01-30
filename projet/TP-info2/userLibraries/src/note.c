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
* Overview : Conversion d'une fréquence vers la note correspondante la plus proche
* Author : METAYER Simon
* Params : const float freq -> fréquence à étudier
* Return : char -> Note trouvée (voir defineNote.h pour voir la correspondance des notes)
*/
char noteSolver(const float freq)
{
	char note; // Initialisation de la variable contenant la note trouvée

	/* Calcul de la note associé à la fréquence envoyée :
	* f = 440 * 2^{note/12}  <=> n= log10( (f/440)^12 ) / log10(2)
	* On obtient une "note à virgule" qu'il suffis d'arrondir à l'unité pour trouver de quelle note on est le plus proche
	* En revanche la note peut etre négative ici car elle est centrée autour du LA 440
	* Ex : un Ré 293,66Hz sera calculé comme étant un -7 
	*/
	double note_tmp = arrondi((log10( pow( ((double)freq/LA_440_FREQ) , 12 ) ) / log10(2)));
	
	// On met en forme la valeur obtenur précédemment pour la rendre relative à un octave
	if (note_tmp<0) // Si la note est négative
	{
		 note = (char)(0-note_tmp); // On en prend la valeur absolue
		 return note =(char)((10-(note % 12))); // Permet d'obtenir la note relative à un octave (du DO au SI)
	}
	else if (note_tmp>=0) // Si la note est positive
	{
		note = (char)note_tmp; // On en prend la valeur absolue
		return note =(char)((((char)note+10))%12); // Permet d'obtenir la note relative à un octave (du DO au SI)
	}
}


/*
* Overview : Conversion d'une fréquence vers la note correspondante
* Author : METAYER Simon
* Params : const float freq -> fréquence à étudier
* Return : char -> Degré/octave trouvé
*/
char degreSolver(float freq)
{
	char note;
	/* Calcul de la note associé à la fréquence envoyée :
	* f = 440 * 2^{note/12}  <=> n= log10( (f/440)^12 ) / log10(2)
	* On obtient une "note à virgule" qu'il suffis d'arrondir à l'unité pour trouver de quelle note on est le plus proche
	* En revanche la note peut etre négative ici car elle est centrée autour du LA 440
	* Ex : un Ré 293,66Hz sera calculé comme étant un -7 
	*/
	double note_tmp = arrondi((log10( pow( ((double)freq/LA_440_FREQ) , 12 ) ) / log10(2)));
	
	if (note_tmp<0) // Si la note est négative
	{
		 note  = (char)(0-note_tmp); // On prend la valeur absolue de la note
		 return 4-(char)arrondi((note+10)/12); // Permet d'obtenir le degré/octave relatif à la note détecté
	}
	else if (note_tmp>=0) // Si la note est positive
	{
		 note = (char)note_tmp; // On prend la valeur absolue de la note
		 return (char)arrondi((note+10)/12)+3; // Permet d'obtenir le degré/octave relatif à la note détecté
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
float calculAbsError(const float relativeError, const float noteFreq, const float deltaFreq)
{
	//L'erreur absolue vaut la fréquence multipliée par l'erreur relative en scalaire(erreur en % /100) + l'erreur introduite par l'imprésision de la fft
	return (noteFreq*relativeError POURCENT_TO_SCALAIRE)+deltaFreq;
}
