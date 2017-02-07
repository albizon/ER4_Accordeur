/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 02/02/17
* Version : 2.0
*/


#ifndef __GENERIC_H__
#define __GENERIC_H__

#include "externalFlashMemory.h"
#include "externalRamMemory.h"

#define AT25DF081A //utilisation de la puce AT25DF081A pour la mémoire flash externe
#define 23LCV1024 //utilisation de la puce 23LCV1024 pour mémoire ram externe

#ifndef USE_SAMD21//Si utilisation d'un SAMD21
	#include "sam.h"
	//External flash memory
	#define SERCOM_FOR_EXTERNALFLASH SERCOM5//Port Sercom sur lequelle est branchée la flash externe
	#define ARGS_FOR_EXTERNALFLASH_INIT {/*Port broche SS*/PORTA,/*Bit broche SS*/13,/*Port broche MOSI*/PORTB,/*Bit broche MOSI*/16,/*Config broche MOSI*/CONFIG_C,/*Port broche MISO*/PORTB,/*Bit broche MISO*/22,/*Config broche MISO*/CONFIG_D,/*Port broche SCK*/PORTB,/*Bit broche SCK*/23,/*Config broche SCK*/CONFIG_D,/*SPI Mode maitre*/CONFIG_DSAMD21_SPI_MASTER_MODE,/*Config registre DIPO, voir samd21Spi_define.h*/SAMD21_SPI_DIPO_0,/*Config registre DOPO, voir samd21Spi_define.h*/SAMD21_SPI_DOPO_012}
	#define ARGGS_FOR_EXTERNALFLASH_OPS {/*Port broche SS*/PORTA,/*Bit broche SS*/13}
	//External ram memory
	#define SERCOM_FOR_EXTERNALRAM SERCOM4//Port Sercom sur lequelle est branchée la ram externe
	#define ARGS_FOR_EXTERNALRAM_INIT {/*Port broche SS*/PORTA,/*Bit broche SS*/13,/*Port broche MOSI*/PORTB,/*Bit broche MOSI*/16,/*Config broche MOSI*/CONFIG_C,/*Port broche MISO*/PORTB,/*Bit broche MISO*/22,/*Config broche MISO*/CONFIG_D,/*Port broche SCK*/PORTB,/*Bit broche SCK*/23,/*Config broche SCK*/CONFIG_D,/*SPI Mode maitre*/CONFIG_DSAMD21_SPI_MASTER_MODE,/*Config registre DIPO, voir samd21Spi_define.h*/SAMD21_SPI_DIPO_0,/*Config registre DOPO, voir samd21Spi_define.h*/SAMD21_SPI_DOPO_012}
	#define ARGGS_FOR_EXTERNALRAM_OPS {/*Port broche SS*/PORTA,/*Bit broche SS*/13}
#endif

#define USE_INTERNAL_RAM 1//Ecriture du tableau dans la ram interne
#define USE_EXTERNAL_FLASH 2//Ecriture du tableau dans la flash externe
#define USE_INTERNAL_FLASH 3//Ecriture du tableau dans la flash interne
#define USE_EXTERNAL_RAM 4//Ecriture du tableau dans la ram externe
#define USE_NOT_MEMORY 0//N'utilise pas de mémoire



////////////////////////////////////////////////////////////////////////////FUNCTIONS////////////////////


/*
* Overview : Convertit un uint32_t en un tableau de 4 uint8_t
* Author : BIZON Alexis
* Params :  -uint32_t in ->la valeur à convertir
*			-uint8_t *out ->Le tableau avec les valeurs converties
* Return : none
*/
void _4BytesTo1Byte(uint32_t in, uint8_t *out);


/*
* Overview : Convertit un tableau de 4 uint8_t en un uint32_t
* Author : BIZON Alexis
* Params : 	-uint8_t *in ->Le tableau avec les valeurs à convertir
* Return : uint32_t -> La valeur convertie
*/
uint32_t _1BytesTo4Byte(uint8_t *in);


/*
* Overview : Ecrit un uint32_t dans une case mémoire à une adresse spécifiée, et dans une mémoire spécifiée
* Author : BIZON Alexis
* Params :  -uint32_t address ->adresse où placer la valeur
*			-uint32_t val ->Valeur à écrire
*			-uint8_t device ->Dans quelle mémoire écrire la valeur
* Return : none
*/
void writeMemory(uint32_t address, uint32_t val, uint8_t device);


/*
* Overview : Lit un uint32_t dans une case mémoire à une adresse spécifiée, et dans une mémoire spécifiée
* Author : BIZON Alexis
* Params :  -uint32_t address ->adresse où est placer la valeur
*			-uint8_t device ->Dans quelle mémoire est écrite la valeur
* Return : uint32_t -> Valeur lu
*/
uint32_t readMemory(uint32_t address, uint8_t device);


/*
* Overview : Alloue une case mémoire d'une taille donnée dans une mémoire donnée
* Author : BIZON Alexis
* Params :  -uint32_t size ->taille de la mémoire à allouer
*			-uint8_t device ->Dans quelle mémoire placer la case
* Return : uint32_t -> adresse de la première case mémoire allouée
*/
uint32_t allocMemory(uint32_t size, uint8_t device);


/*
* Overview : libère une case mémoire d'une taille donnée, à une adresse donnée dans une mémoire donnée
* Author : BIZON Alexis
* Params :  -uint32_t address ->address de la première case mémoire à effacer
*			-uint32_t size ->nombre de cases mémoires à effacer
*			-uint8_t device ->Dans quelle mémoire libérer la case
* Return : none
*/
void freeMemory(uint32_t address, uint32_t size, uint8_t device);


/*
* Overview : réalloue une nouvelle taille mémoire pour une dite variable en supprimant l'ancienne case et en en créant une nouvelle, en renvoyant la ouvelle adresse de cette case mémoire
* Author : BIZON Alexis
* Params :  -uint32_t address ->address de la première case mémoire à effacer
*			-uint32_t lastSize ->nombre de cases mémoires à effacer
*			-uint32_t newSize ->nombre de cases mémoires à réafecter
*			-uint8_t device ->Dans quelle mémoire libérer et allouer la case
* Return : uint32_t -> adresse de la première case mémoire nouvellement allouée
*/
uint32_t reallocMemory(uint32_t address, uint32_t lastSize, uint32_t newSize, uint8_t device);

#endif
