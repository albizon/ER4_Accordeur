/*
 * note.h
 *
 * Created: 23/01/2017 09:14:27
 *  Author: simon
 */ 


#ifndef NOTE_H_
#define NOTE_H_

#include "define.h"

double arrondi (double val);
char noteSolver(float freq);
char degreSolver(float freq);
float getFreqNote(char note, char degre);
char accord(char note, char degre, float freq, float plage);



#endif /* NOTE_H_ */