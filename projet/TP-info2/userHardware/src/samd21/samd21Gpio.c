/*
 * samd21Gpio.c
 *
 * Created: 03/02/2017 13:33:34
 *  Author: simon
 */ 


 #include "samd21Gpio.h"
 
void pinConfig_gpioGeneric(uint32_t *pin, uint32_t mode)
{
	uint8_t port = pin[0]&0xFF;
	uint8_t numBit = pin[1]&0xFF;
	uint8_t _mode=mode&0xFF;
	//verification des arguments.
	if(port > 1) return;
	if(numBit > 31) return;
	//
	switch(_mode)
	{
		case DISABLE: //pullen = 0 - inen = 0 - dir = 0
			PORT->Group[port].DIRCLR.reg = 1 << numBit;
			PORT->Group[port].PINCFG[numBit].reg = 0;
			break;
		case OUTPUT: //pullen = 0 - inen = 0 - dir = 1
			PORT->Group[port].DIRSET.reg = 1 << numBit;
			PORT->Group[port].OUTCLR.reg = 1 << numBit;
			PORT->Group[port].PINCFG[numBit].reg = 0;
			break;
		case INPUT: //pullen = 0 - inen = 1 - dir = 0
			PORT->Group[port].DIRCLR.reg = 1 << numBit;
			PORT->Group[port].PINCFG[numBit].reg = 0x2;
			break;
		case INPUT_PULLUP: //pullen = 1 - inen = 1 - dir = 0
			PORT->Group[port].DIRCLR.reg = 1 << numBit;
			PORT->Group[port].OUTSET.reg = 1 << numBit;
			PORT->Group[port].PINCFG[numBit].reg = 0x6;
			break;
		case INPUT_PULLDOWN: //pullen = 1 - inen = 1 - dir = 0
			PORT->Group[port].DIRCLR.reg = 1 << numBit;
			PORT->Group[port].OUTCLR.reg = 1 << numBit;
			PORT->Group[port].PINCFG[numBit].reg = 0x6;
			break;
		default:
			break;
	}
}

void digitalWrite_gpioGeneric(uint32_t *pin, uint32_t level)
{
	uint8_t port = pin[0]&0xFF;
	uint8_t numBit = pin[1]&0xFF;
	if(port > 1) return;
	if(numBit > 31) return;
	
	if(value)
		PORT->Group[port].OUTSET.reg = 1 << numBit;
	else
		PORT->Group[port].OUTCLR.reg = 1 << numBit;
}

uint8_t digitalRead_gpioGeneric(uint32_t *pin)
{
	uint8_t port = pin[0]&0xFF;
	uint8_t numBit = pin[1]&0xFF;
	if(port > 1) return 0xFF;
	if(numBit > 31) return 0xFF;
	if (PORT->Group[port].IN.reg & (1 << numBit))
		return 1;
	return 0;
}

void pinMux_gpioSamd21(uint32_t *pin, uint32_t config)
{
	uint8_t port = pin[0]&0xFF;
	uint8_t numBit = pin[1]&0xFF;
	uint8_t _config=config&0xFF;
	//verification des arguments.
	if(port > 1) return;
	if(numBit > 31) return;
	if(_config > 7) return;

	const unsigned char numReg = numBit >> 1;
	//recupere la configuration de 2 broches paires et impaires
	int reg = PORT->Group[port].PMUX[numReg].reg;
	//le numero de bit est impaire?
	if(numBit & 1)
	{
		//supprime la config. impaire.
		reg &= 0xF;
		//mets à jour la configuration
		reg |= (_config) << 4;
	} else {
		//supprime la config. paire.
		reg &= 0xF0;
		//mets à jour la configuration
		reg |= (_config);
	}
	//mets à jour le registre
	PORT->Group[port].PMUX[numReg].reg = reg;
	//valide le multiplexage de la broche
    PORT->Group[port].PINCFG[numBit].reg |= 0x01 ;
}
