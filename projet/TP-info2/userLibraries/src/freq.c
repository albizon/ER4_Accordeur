#include "define.h"
#include "freq.h"

float __freq;

void initFreq()
{
	// EIC pour la détection du passage en zéro de notre signal sinusoidal
	pinMode(PORTB, 15, INPUT_PULLUP);//configuration de pb 15 en entrée
	pinMux(PORTB, 15, CONFIG_A);// pb 15 sur l'eic
	EICInitClock(F32KHZ);// initialisation de la source d'horloge por l'eic
	EICConfig(15,1,LOW);// configuration de l'eic 15 en detection de niveau bas avec filtre
	NVIC_EnableIRQ(EIC_IRQn);// acivation des interuptions sur EIC
	
	// TIMER TC3 à 1MHz
	TCinitClock(F1MHZ,3); // Initialisation de l'horloge à 1MHz pour le timer TC3
	TC3->COUNT16.CTRLA.reg= (0x3<<8); // intialisation d'un prescaler de '011' soit une division par 8 donc 1/8 de Mhz
	TC3->COUNT16.CTRLBSET.reg=0x0; // Initialisation du timer en incrémentation
	TC3->COUNT16.COUNT.reg=0; // Chargement du compteur
	TC3->COUNT16.INTFLAG.reg=0x1; // Validation de l'overflow
	TC3->COUNT16.CTRLA.reg |=2; // Démarrage du timer
	//TC3->COUNT16.INTENSET.reg=1; // Validation locale des interruptions provoquée par TC3
	//NVIC_EnableIRQ(TC3_IRQn); // Validation NVIC du timer TC3 pour les interruptions
	//NVIC_SetPriority(TC3_IRQn,0); // Priorité de 1 pour les interruptions du timer TC3
}

void EIC_Handler()
{
	static char countOn;
	if((EIC->INTFLAG.reg & (1<<15)) && (!countOn)) // Si on ne compte pas
	{
		countOn =1;
		TC3->COUNT16.COUNT.reg=0; // RAZ du compteur
		EIC->INTFLAG.reg |= 1<<15; // RAZ de la détection EIC
	}
	else if((EIC->INTFLAG.reg & (1<<15)) && (countOn)) // Si on était en train de compter
	{
		countOn =0;
		__freq = (float)(1/((TC3->COUNT16.COUNT.reg)*(0.000008))) ; // 1/(x*8us) 
		EIC->INTFLAG.reg |= 1<<15; // RAZ de la détection EIC
	}
}

float getFreq()
{
	return __freq;
}