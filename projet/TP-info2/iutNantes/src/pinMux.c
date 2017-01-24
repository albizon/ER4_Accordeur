#include "pinMux.h"
#include "sam.h"

void pinMux(unsigned char port,unsigned char numBit, unsigned char config)
{
	//verification des arguments.
	if(port > 1) return;
	if(numBit > 31) return;
	if(config > 7) return;

	const unsigned char numReg = numBit >> 1;
	//recupere la configuration de 2 broches paires et impaires
	int reg = PORT->Group[port].PMUX[numReg].reg;
	//le numero de bit est impaire?
	if(numBit & 1)
	{
		//supprime la config. impaire.
		reg &= 0xF;
		//mets à jour la configuration
		reg |= (config) << 4;
	} else {
		//supprime la config. paire.
		reg &= 0xF0;
		//mets à jour la configuration
		reg |= (config);
	}
	//mets à jour le registre
	PORT->Group[port].PMUX[numReg].reg = reg;
	//valide le multiplexage de la broche
    PORT->Group[port].PINCFG[numBit].reg |= 0x01 ;
}

