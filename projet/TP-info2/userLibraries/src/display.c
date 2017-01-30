/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 23/01/17
* Version : 1.0
*/

#include "define.h"
#include "display.h"
#include <stdio.h>
#include <string.h>

/*
* Overview : Affichage du titre du projet sur la première ligne de l'afficheur
* Author : METAYER Simon
* Params : none
* Return : none
*/
void displayTitle()
{
	OLEDClear();//Efface tous ce qu'il y a sur l'afficheur
	OLEDSetLine(0);//Se place sur la première ligne
	printf("Accordeur v1.0\n");//Ecrit le titre
}


/*
* Overview : Converti un code représentant la note en un texte contenant le nom de la note
* Author : BIZON Alexis
* Params :  const char: note ->Le code de la note;
            char*: str ->La chaine de caractères du nom de la note
* Return : none
*/
void noteToString(const char note, char* str)
{
	switch (note){ // Ecriture conditionnée par la note
	case NUM_DO : 
		strcpy(str, "Do");
	break;
	
	case NUM_REb :
		strcpy(str, "Reb / Do#");
	break;
	
	case NUM_RE :
		strcpy(str, "Re");
	break;
	
	case NUM_MIb :
		strcpy(str, "Mib / Re#");
	break;
	
	case NUM_MI :
		strcpy(str, "Mi");
	break;
	
	case NUM_FA :
		strcpy(str, "Fa");
	break;
	
	case NUM_SOLb :
		strcpy(str, "Solb / Fa#");
	break;
	
	case NUM_SOL :
		strcpy(str, "Sol");
	break;
	
	case NUM_LAb :
		strcpy(str, "Lab / Sol#");
	break;
	
	case NUM_LA :
		strcpy(str, "La");
	break;
	
	case NUM_SIb :
		strcpy(str, "Sib / La#");
	break;
	
	case NUM_SI :
		strcpy(str, "Si");
	break;

	default:
		strcpy(str, "Inconnue");
	break;	
	}
}


/*
* Overview : Affiche la note envoyée en paramètre
* Author : BIZON Alexis
* Params :  const char note ->La note à afficher
* Return : none
*/
void displayNote(const char note)
{
	OLEDClearLine(3); //Efface la quatrième ligne
	OLEDSetLine(3); //Se place sur la quatrième ligne
	printf("Note  : "); //Ecrit "note"
	switch (note){ //Ecriture conditionnée par la note
	case NUM_DO :
		printf("Do\n");
	break;
	
	case NUM_REb :
		printf("Reb / Do#\n");
	break;
	
	case NUM_RE :
		printf("Re\n");
	break;
	
	case NUM_MIb :
		printf("Mib / Re#\n");
	break;
	
	case NUM_MI :
		printf("Mi\n");
	break;
	
	case NUM_FA :
		printf("Fa\n");
	break;
	
	case NUM_SOLb :
		printf("Solb / Fa#\n");
	break;
	
	case NUM_SOL :
		printf("Sol\n");
	break;
	
	case NUM_LAb :
		printf("Lab / Sol#\n");
	break;
	
	case NUM_LA :
		printf("La\n");
	break;
	
	case NUM_SIb :
		printf("Sib / La#\n");
	break;
	
	case NUM_SI :
		printf("Si\n");
	break;

	default:
		printf("inconnue\n");
	break;
	
	}
}


/*
* Overview : Affiche la fréquence envoyée en paramètre
* Author : METAYER Simon
* Params :  float freq ->La fréquence à afficher
* Return : none
*/
void displayFrequence(float freq)
{
	OLEDClearLine(1);//Efface la seconde ligne
	OLEDSetLine(1);//Se place sur la seconde ligne
	printf("Freq  : %.2f Hz\n", freq);//Ecrit la fréquence envoyée en Hz avec deux chiffres aprés la virgule
}


/*
* Overview : Affiche le degré ou l'octave envoyée en paramètre
* Author : METAYER Simon
* Params :  char degre ->Le degré à afficher
* Return : none
*/
void displayDegre(char degre)
{
	OLEDClearLine(2); //Efface la troisième ligne
	OLEDSetLine(2); //Se place sur la troisième ligne
	printf("Degre : %d   \n",degre); //Ecrit le degré envoyé
}

/*
* Overview : Allume les leds d'aide à l'accordage en fonction de l'indicateur : trop bas / ok / trop haut
* Author : METAYER Simon
* Params :  char acc ->indicateur : trop bas / ok / trop haut
* Return : none
*/
void diplayLedIndicator(char acc) // Allume les leds en fonction de l'indicateur : trop bas / ok / trop haut
{
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

}



