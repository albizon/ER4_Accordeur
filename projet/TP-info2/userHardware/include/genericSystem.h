/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 03/02/17
* Version : 2.0
*/

#ifndef __GENERICSYSTEM_H__
#define __GENERICSYSTEM_H__

#ifndef USE_SAMD21
	#include "samd21System.h"
#endif

void init_system(void *args);

void disable_ints(void);

void enable_ints(void);

#endif