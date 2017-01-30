/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 23/01/17
* Version : 1.0
*/  

#include "define.h"

	

int main(void)//fonction principale du programme
{
	float freq = 0;//contient la fréquence mesurée de la note
	char note = 0;//contient la note calculée à partir de la fréquence, voir les différentes valeurs dans define_notes.h
	char degre = 0;//contient le degré, ou l'octave de la note calculée à partir de la fréqence
	float relativeError = 1.0;//spécifie l'erreur relative autorisée en % entre la fréquence mesurée et la fréquence réelle correspondant à la note
	setup();//Fonction d'initialisation
	displayTitle();//affiche le titre du projet en haut de l'écran OLED
	while(1)
	{
		freq=getFreq();//Récupère la fréquence mesurée par le fréquencemètre
		note = noteSolver(freq);//permet de déterminer la note correspondant à la fréquence mesurée
		degre = degreSolver(freq);//permet de déterminer le degré ou l'octave correspondant à la fréquence mesurée
		char acc = accorder(note, degre, freq, calculAbsError(relativeError, freq,0));//Permet de déterminer si la note est acoordée, trop basse ou trop haute
		diplayLedIndicator(acc); // Allume les leds en fonciton de l'indicateur : trop bas / ok / trop haut
		displayFrequence(freq);//On affiche la fréquence sur l'afficheur OLED
		displayNote(note);//On affiche la note sur l'afficheur OLED
		displayDegre(degre);//On affiche le degré sur l'afficheur OLED
	}
	
	return 0;//Le programme renvoit 0x0000 si l'execution c'est correctement terminée
}
