#ifndef __DAC_H__
#define __DAC_H__

//utilisation du DAC (avec spi)
void DACInit();

//valeur sur 10 bits (bits au dessus ignorés).
void DACWrite(unsigned int val);

#endif
