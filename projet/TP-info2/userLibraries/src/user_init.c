#include "define.h"
#include "user_init.h"

/*
* Overview : fonction d'initialisation de tous ce qui est nécessaire au bon fonctionnement du programme
* Author : METAYER Simon
* Params : none
* Return : none
*/
void setup()
{
	SystemInit();//Initialisation des paramètres systèmes
	redirectPrintf(PRINTF_OLED);//On redirige les instructions de la fonction printf sur l'afficheur OLED
	OLEDInit(1);//On initialise notre afficheur OLED avec aucune image
	// initFreq(); // initialisation du fréquencemètre
	// Initialisation des leds d'aide à l'accordage :
	pinMode(PORTA, 12, OUTPUT); 
	pinMode(PORTA, 13, OUTPUT);
	pinMode(PORTA, 15, OUTPUT);
}
