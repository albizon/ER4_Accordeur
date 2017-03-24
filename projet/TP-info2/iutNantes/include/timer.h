#ifndef __TIMER_H__
#define __TIMER_H__

//definition des sources d'horloge.
#include "clock.h"

//initialise la source d'horloge du timer 
//(ainsi que son alimentation).
// ***Attention: les timer n (pair) et n+1 (impair) ont
//               forcément la même source d'horloge!
// * TimerId: 0 à 7 (TC3 à TC7 notamment)
// * source: une des 4 fréquences ci-dessus
int TCinitClock(int source, int timerId);

#endif
