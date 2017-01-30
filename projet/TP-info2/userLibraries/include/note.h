/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 23/01/17
* Version : 1.0
*/


#ifndef NOTE_H_
#define NOTE_H_

#include "define.h"


/*
* Overview : Arrondi une variable de type double
* Author : METAYER Simon
* Params : const double val -> Valeur à arrondir
* Return : double -> Valeur arrondie
*/
double arrondi (const double val);


/*
* Overview : Conversion d'une fréquence vers la note corescpondante
* Author : METAYER Simon
* Params : const float freq -> fréquence à étudier
* Return : char -> Note trouvée (voir defineNote.h pour voir la correspondance des notes)
*/
char noteSolver(const float freq);


/*
* Overview : Affichage du titre du projet sur la première ligne de l'afficheur
* Author : METAYER Simon
* Params : none
* Return : none
*/
char degreSolver(float freq);


/*
* Overview : renvoi la fréquence d'une note à un octave défini
* Author : METAYER Simon
* Params :  -const char note -> note à convertir
*           -const char degre -> octave de la note à convertir
* Return : float -> fréquence calculée
*/
float getFreqNote(const char note, const char degre);


/*
* Overview : Permet de savoir si l'instrument est accordé à la note donnée
* Author : BIZON Alexis
* Params :  -const char note -> note correspondante calculée
*           -const char degre -> octave de la note correspondant calculé
*           -const float freq -> fréquence mesurée
*           -const float error -> erreur absolue autorisée entre la fréquence mesurée et la fréquence désirée en Hz
* Return : char -> état de l'accord (soit trop haut, soit OK, soit trop bas)
*/
char accorder(const char note, const char degre, const float freq, const float error);


/*
* Overview : Calcul l'erreur absolue autorisée à partir d'une erreur relative, de la fréquence de base et du delta de fréquence de la fft 
* Author : BIZON Alexis
* Params :  -const float relativeError -> Erreur relative autorisée
*           -const float noteFreq -> Fréquence autour de laquelle l'erreur absolue sera calculée
*           -const float deltaFreq -> Espacement entre les raies de la fft en Hz
* Return : float -> Erreur absolue autorisée
*/
float calculAbsError(const float relativeError, const float noteFreq, const float deltaFreq=0);



#endif /* NOTE_H_ */
