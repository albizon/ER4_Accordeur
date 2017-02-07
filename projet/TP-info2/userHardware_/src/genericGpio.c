/*
 * genericGpio.c
 *
 * Created: 03/02/2017 13:33:18
 *  Author: simon
 */ 
 
 #include "genericGpio.h"
 
 void digitalToggleGeneric(uint32_t *pin)
 {
	char tmp = digitalRead_gpioGeneric(pin);
	if(!digitalRead_gpioGeneric(pin)) {digitalWrite_gpioGeneric(pin, LOW);}
	else {digitalWrite_gpioGeneric(pin, HIGH);}
 }
