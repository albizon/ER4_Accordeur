/*
 * IUT de Nantes
 * Created by : Mr. Métayer Simon & Mr. Bizon Alexis
 * Date : 23/01/17
 * Version : 1.0
 */ 

#include "define.h"

	

int main(void)//fonction principale du programme
{
	float freq = 394;//contient la fréquence mesurée de la note
	char note = 0;//contient la note calculée à partir de la fréquence, voir les différentes valeurs dans define.h
	char degre = 0;//contient le degré, ou l'octave de la note calculée à partir de la fréqence
	float plage = 1.0;//spécifie l'erreur autorisée en hertz entre la fréquence mesurée et la fréquence réelle correspondant à la note
	setup();//Fonction d'initialisation
	displayTitle();//affiche le titre du projet en haut de l'écran OLED
	while(1)
	{
		//freq=getFreq();//Récupère la fréquence mesurée par le fréquencemètre
		note = noteSolver(freq);//permet de déterminer la note correspondant à la fréquence mesurée
		degre = degreSolver(freq);//permet de déterminer le degré ou l'octave correspondant à la fréquence mesurée
		char acc = accord(note, degre, freq, plage);//Permet de déterminer si la note est acoordée, trop basse ou trop haute
		switch (acc){//Test de la valeur renvoyée par la fonction précédente
			case LOW_FREQ://Si la fréquence est trop basse
				//On allume la première led de la carte d'extension et on éteind les autres
				digitalWrite(PORTA, 12,0);
				digitalWrite(PORTA, 13,1);
				digitalWrite(PORTA, 15,1);
			break;
			case OK_FREQ://Si la fréquence est dans la plage d'erreur autorisée
				//On allume la seconde led de la carte d'extension et on éteind les autres
				digitalWrite(PORTA, 13,0);
				digitalWrite(PORTA, 12,1);
				digitalWrite(PORTA, 15,1);
			break;
			case HIGH_FREQ://Si la fréquence est trop haute
				//On allume la troisième led de la carte d'extension et on éteind les autres
				digitalWrite(PORTA, 15,0);
				digitalWrite(PORTA, 12,1);
				digitalWrite(PORTA, 13,1);
			break;
			default://par défaut on ne fait rien
			break;
		}
		displayFrequence(freq);//On affiche la fréquence sur l'afficheur OLED
		displayNote(note);//On affiche la note sur l'afficheur OLED
		displayDegre(degre);//On affiche le degré sur l'afficheur OLED
	}
	
	return 0;//Le programme renvoit 0x0000 si l'execution c'est correctement terminée
}
