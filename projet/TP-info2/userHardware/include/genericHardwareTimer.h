/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 03/02/17
* Version : 2.0
*/

#ifndef __GENERICHARDWARETIMER_H__
#define __GENERICHARDWARETIMER_H__

#ifndef USE_SAMD21
	#include "samd21HardwareTimer.h"
#endif

	void arm_hardwareTimer(void *timer, uint32_t *args);

#endif