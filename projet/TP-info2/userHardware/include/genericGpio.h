/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 03/02/17
* Version : 2.0
*/



#ifndef GENERICGPIO_H_
#define GENERICGPIO_H_

#ifndef USE_SAMD21
	#include "samd21Gpio.h"
	#include "sam.h"
#endif

#define LOW 0
#define HIGH 1

void pinConfig_gpioGeneric(uint32_t *pin, uint32_t mode);

void digitalWrite_gpioGeneric(uint32_t *pin, uint32_t level);

uint8_t digitalRead_gpioGeneric(uint32_t *pin);

void digitalToggleGeneric(uint32_t *pin);




#endif /* GENERICGPIO_H_ */