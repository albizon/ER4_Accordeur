/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 03/02/17
* Version : 2.0
*/

#include "samd21System.h"

void init_system(void *args)
{
	SystemInit();
}

void disable_ints(void)
{
	__disable_irq();
}

void enable_ints(void)
{
	__enable_irq();
}