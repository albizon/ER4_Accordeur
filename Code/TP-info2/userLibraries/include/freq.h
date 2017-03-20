/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 23/01/17
* Version : 1.0
*/

#ifndef __FREQ_H__
#define __FREQ_H__


/*
* Overview : Initialisation du fréquencemètre
* Author : BIZON Alexis
* Params : none
* Return : none
*/
void initFreq();

/*
* Overview : Récupération de la dèrnière valeur de fréquence mesurée par le fréquencemètre
* Author : BIZON Alexis
* Params : none
* Return : float : freq -> valleure de la fréquence en Hz
*/
float getFreq();

#endif
