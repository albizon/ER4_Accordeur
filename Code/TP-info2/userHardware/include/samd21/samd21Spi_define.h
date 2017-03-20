#ifndef _SAMD21SPI_DEFINE_H_
#define _SAMD21SPI_DEFINE_H_

/////////////////////////////////////////////////////////////////SPI MODE//////////////////////////////////////

#define SAMD21_SPI_MASTER_MODE 0x03 //Spi en mode maitre
#define SAMD21_SPI_SLAVE_MODE 0x02 //Spi en mode esclave

//////////////////////////////////////////////////////DOPO REGISTER CONFIG///////////////////////////////////////////////////////////

//Mode maitre, DO->MOSI
//Mode esclave, DO->MISO

#define SAMD21_SPI_DOPO_012 0x0 //DO -> PAD[0] / SCK -> PAD[1]
#define SAMD21_SPI_DOPO_231 0x1 //DO -> PAD[2] / SCK -> PAD[3]
#define SAMD21_SPI_DOPO_312 0x2 //DO -> PAD[3] / SCK -> PAD[1]
#define SAMD21_SPI_DOPO_031 0x3 //DO -> PAD[0] / SCK -> PAD[3]

////////////////////////////////////////////////////DIPO REGISTER CONFIG/////////////////////////////////////////////////////////

//Mode maitre, DI->MISO
//Mode esclave, DI->MOSI

#define SAMD21_SPI_DIPO_0 0x0 //DI -> PAD[0]
#define SAMD21_SPI_DIPO_1 0x1 //DI -> PAD[1]
#define SAMD21_SPI_DIPO_2 0x2 //DI -> PAD[2]
#define SAMD21_SPI_DIPO_3 0x3 //DI -> PAD[3]

////////////////////////////////////////////////////////POWER MANAGER MASK////////////////////////////////////

#define SAMD21_PM_MASK_SERCOM0 0x04
#define SAMD21_PM_MASK_SERCOM1 0x08
#define SAMD21_PM_MASK_SERCOM2 0x10
#define SAMD21_PM_MASK_SERCOM3 0x20
#define SAMD21_PM_MASK_SERCOM4 0x40
#define SAMD21_PM_MASK_SERCOM5 0x80

////////////////////////////////////////////////////////GENERAL CLOCK MASK/////////////////////////////////////

#define SAMD21_GCLK_MASK_SERCOM0 0x14
#define SAMD21_GCLK_MASK_SERCOM1 0x15
#define SAMD21_GCLK_MASK_SERCOM2 0x16
#define SAMD21_GCLK_MASK_SERCOM3 0x17
#define SAMD21_GCLK_MASK_SERCOM4 0x18
#define SAMD21_GCLK_MASK_SERCOM5 0x19

#endif
