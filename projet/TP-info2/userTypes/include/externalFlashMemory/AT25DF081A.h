/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/

#ifndef __AT25DF081A_H__
#define __AT25DF081A_H__

#include "genericSpi.h"
#include "AT25DF081A_define.h"
#include "externalFlashMemory.h"
#include "genericMemory.h"

void __writeAT25DF081AByte(uint8_t byte, uint32_t address);

uint8_t __readAT25DF081AByte(uint32_t address);

void __getBitmapAT25DF081A(uint32_t *bitmap);

void __setBitmapAT25DF081A(uint32_t *bitmap);


#endif