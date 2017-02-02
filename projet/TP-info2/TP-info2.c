/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 23/01/17
* Version : 2.0
*/  

#include "define.h"	
#include "userComplexArray.h"
#include "userEnvelope.h"

#define USE_SAMD21

#define DIAPASON_IS_INSTRUMENT 0//Défini si un sinus pur est considéré comme un instrument

#define NB_HARMONIQUE_ETUDIES 17//

#define DELTA_FREQUENCE (float)1//Espacement en Hz entre chaques raies de la FFT
#define FREQUENCE_ECHANTILLONAGE (float)44100//Fréquence en Hz de l'échantillonage du signal audio

int main(void)//fonction principale du programme
{
	userComplexArray *userComplexTab;
	new_userComplexArray(userComplexTab);
	setMemoryMode_userComplexArray(userComplexTab, USE_EXTERNAL_FLASH);
	
	userEnvelope *userEnv;
	new_userEnvelope(userEnv);
	setMemoryMode_userEnvelope(userEnv, USE_INTERNAL_RAM);
	resize_userEnvelope(userEnv, (NB_HARMONIQUE_ETUDIES+1));
	
	float df=1000/DELTA_FREQUENCE;//Espacement en ms ente chaques fft
	float dt=1000000/FREQUENCE_ECHANTILLONAGE;//Espacement en us entre chaque acquisition sur l'adc
	float freq = 0; //contient la fréquence mesurée de la note
	char note = 0; //contient la note calculée à partir de la fréquence, voir les différentes valeurs dans define_notes.h
	char degre = 0; //contient le degré, ou l'octave de la note calculée à partir de la fréqence
	float relativeError = 1.0;//spécifie l'erreur relative autorisée en % entre la fréquence mesurée et la fréquence réelle correspondant à la note
	
	
	setup();//Fonction d'initialisation
	fftGeneralInit(dt, df);
	displayTitle(); //affiche le titre du projet en haut de l'écran OLED
	
	
	while(1)
	{		
		
		//freq=getFreq(); //Récupère la fréquence mesurée par le fréquencemètre
		
		/*Acquisition*/

		getTabsFFT(userComplexTab);
		extractOneEnvelope(userComplexTab, userEnv, (NB_HARMONIQUE_ETUDIES+1), DELTA_FREQUENCE);
		freq=getFreqPlay(user_mod,DELTA_FREQUENCE);
		
		/*Traitement*/
		note = noteSolver(freq); //permet de déterminer la note correspondant à la fréquence mesurée
		degre = degreSolver(freq); //permet de déterminer le degré ou l'octave correspondant à la fréquence mesurée
		char acc = accorder(note, degre, freq, calculAbsError(relativeError, freq, DELTA_FREQUENCE));//Permet de déterminer si la note est acoordée, trop basse ou trop haute
		
		/*Affichage*/
		diplayLedIndicator(acc); // Allume les leds en fonciton de l'indicateur : trop bas / ok / trop haut
		displayFrequence(freq); //On affiche la fréquence sur l'afficheur OLED
		displayNote(note); //On affiche la note sur l'afficheur OLED
		displayDegre(degre); //On affiche le degré sur l'afficheur OLED
		
	}
	
	return 0; //Le programme renvoit 0x0000 si l'execution c'est correctement terminée
}






