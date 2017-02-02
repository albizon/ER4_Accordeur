/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 25/01/17
* Version : 2.0
*/


#ifndef __INSTRUMENTS_H__
#define __INSTRUMENTS_H__

#include "userEnvelope.h"
#include "userEnvelopeArray.h"
#include "userInstrument.h"
#include "userInstrumentArray.h"


#define DELAY 1
#define ATTACK 2
#define HOLD 3
#define DECAY 4
#define SUSTAIN 5
#define RELEASE 6




/*
* Overview : permet de reconnaitre un instrument à partir de son enveloppe spectrale
* Author : BIZON Alexis
* Params :  -const float *env -> enveloppe à étudier
*			-const struct Instrument *listInstru -> liste des instruments connu
* Return : struct Instrument -> instrument reconnu
*/
void getInstru(userEnvelope *env, userInstrumentArray *listInstru);


/*
* Overview : perment de reconnaitre la fréquence de la note jouée par un instrument
* Author : BIZON Alexis
* Params : const userEnvelope *env -> enveloppe à étudier
* Return : float -> fréquence de la note jouée
*/
float getFreqPlay(const userEnvelope *env);


/*
* Overview : perment de récupérer l'amplitude de la note
* Author : BIZON Alexis
* Params : const userEnvelope *env -> enveloppe à étudier
* Return : float -> amplitude de la note en dB
*/
float getLevelPlay(const userEnvelope *env);


/*
* Overview : permet de créer l'enveloppe spectrale d'un instrument pour une note d'une certaine fréquence
* Author : BIZON Alexis
* Params :  -const float freqNote -> fréquence de la note à jouer
*			-const struct Instrument instru -> instrument devant jouer la note
*			-float *env -> enveloppe spectrale à envoyer sur le DAC
* Return : none
*/
//void getEnveloppe(const float freqNote, const struct Instrument instru, struct floatSingleArray *env);


#endif
