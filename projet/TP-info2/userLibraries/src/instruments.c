
/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 25/01/17
* Version : 1.0
*/


#include "instruments.h"





/*
* Overview : permet de reconnaitre un instrument à partir de son enveloppe spectrale
* Author : BIZON Alexis
* Params :  -vector<float> const& env -> enveloppe à étudier
*			-vector<struct Instrument> const& listInstru -> liste des instruments connu
* Return : struct Instrument -> instrument reconnu
*/
struct Instrument getInstru(vector<float> const& env, vector<struct Instrument> const& listInstru)
{
  
}


/*
* Overview : perment de reconnaitre la fréquence de la note jouée par un instrument
* Author : BIZON Alexis
* Params :  -vector<float> const& env -> enveloppe à étudier
*			-struct Instrument instru -> instrument ayant été identifié comme étant la source de la note
* Return : float -> fréquence de la note jouée
*/
float getFreqPlay(vector<float> const& env, struct Instrument instru)
{
  
}


/*
* Overview : permet de créer l'enveloppe spectrale d'un instrument pour une note d'une certaine fréquence
* Author : BIZON Alexis
* Params :  -float freqNote -> fréquence de la note à jouer
*			-struct Instrument instru -> instrument devant jouer la note
* Return : vector<float> -> enveloppe spectrale à envoyer sur le DAC
*/
vector<float> getEnveloppe(float freqNote, struct Instrument instru)
{
  
}

