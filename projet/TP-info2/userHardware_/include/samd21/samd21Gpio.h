/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 03/02/17
* Version : 2.0
*/


#ifndef SAMD21GPIO_H_
#define SAMD21GPIO_H_

#include "genericGpio.h"
#include "samd21Gpio_define.h"
#include "sam.h"


void pinMux_gpioSamd21(uint32_t *pin, uint32_t config);


#endif /* SAMD21GPIO_H_ */