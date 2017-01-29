/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 23/01/17
* Version : 1.0
*/


#ifndef NOTE_H_
#define NOTE_H_

#include "define.h"

double arrondi (double val);
char noteSolver(float freq);
char degreSolver(float freq);
float getFreqNote(char note, char degre);
char accorder(char note, char degre, float freq, float plage);
float calculAbsError(float relativeError, float noteFreq);



#endif /* NOTE_H_ */
