/*
 * IUT de Nantes
 * Created by : Mr. Métayer Simon & Mr. Bizon Alexis
 */ 

#include "define.h"

	

int main(void)
{
	float freq = 394;
	char note = 0;
	char degre = 0;
	float plage = 1.0;
	setup();//Fonction d'initialisation
	displayTitle();
	while(1)
	{
		//freq=getFreq();
		note = noteSolver(freq);
		degre = degreSolver(freq);//Valeur contenant le degre de la note
		char acc = accord(note, degre, freq, plage);
		switch (acc){
			case LOW_FREQ:
				digitalWrite(PORTA, 12,0);
				digitalWrite(PORTA, 13,1);
				digitalWrite(PORTA, 15,1);
			break;
			case OK_FREQ:
				digitalWrite(PORTA, 13,0);
				digitalWrite(PORTA, 12,1);
				digitalWrite(PORTA, 15,1);
			break;
			case HIGH_FREQ:
				digitalWrite(PORTA, 15,0);
				digitalWrite(PORTA, 12,1);
				digitalWrite(PORTA, 13,1);
			break;
			default:
			break;
		}
		displayFrequence(freq);
		displayNote(note);
		displayDegre(degre);
	}
	
	return 0;//Le programme renvoit 0x0000 si l'execution c'est correctement terminée
}
