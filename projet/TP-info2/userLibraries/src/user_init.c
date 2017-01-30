#include "define.h"
#include "user_init.h"


void setup()//Fonction d'initialisation
{
	SystemInit();//Initialisation des paramètres systèmes
	redirectPrintf(PRINTF_OLED);//On redirige les instructions de la fonction printf sur l'afficheur OLED
	OLEDInit(1);//On initialise notre afficheur OLED avec aucune image
	ADCInit(); // initialisation de l'adc
	initFreq(); // initialisation du fréquencemètre
	// Initialisation des leds d'aide à l'accordage :
	pinMode(PORTA, 12, OUTPUT); 
	pinMode(PORTA, 13, OUTPUT);
	pinMode(PORTA, 15, OUTPUT);
}
