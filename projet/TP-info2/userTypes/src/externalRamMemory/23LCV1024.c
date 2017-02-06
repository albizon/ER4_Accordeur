#include "23LCV1024.h"



void __write23LCV1024Byte(uint8_t byte, uint32_t address)
{
  uint8_t trame[5];
  trame[0]= 23LCV1024_WRITE;
  trame[1] = address & 0xFF;
  trame[2] = (address & 0xFF00)<<8;
  trame[3] = (address & 0xFF0000)<<16;
  trame[4] = byte;
  writeBytes_spi(SERCOM_EXTERNAL_RAM, {SS_PORT_EXTERNAL_RAM;SS_BIT_EXTERNAL_RAM}, trame, 5);
}

uint8_t __read23LCV1024Byte(uint32_t address)
{
  uint8_t trame[4];
  trame[0]= 23LCV1024_READ;
  trame[1] = address & 0xFF;
  trame[2] = (address & 0xFF00)<<8;
  trame[3] = (address & 0xFF0000)<<16;
  writeBytes_spi(void *interface, uint32_t *args, trame, 4);
  return readByte_spi(SERCOM_EXTERNAL_RAM, {SS_PORT_EXTERNAL_RAM;SS_BIT_EXTERNAL_RAM});
}


void initCircuitRam(void)
{
  
}


void writeExternalRam_uint32(uint32_t address, uint32_t val)
{
  __write23LCV1024Byte((val & 0xFF), (address*4));
  __write23LCV1024Byte(((val & 0xFF00)<<8), (address*4+1));
  __write23LCV1024Byte(((val & 0xFF0000)<<16), (address*4+2));
  __write23LCV1024Byte(((val & 0xFF000000)<<24), (address*4+3));
}

uint32_t readExternalRam_uint32(uint32_t address)
{
  uint32_t tmp =0;
  tmp = __read23LCV1024Byte(address*4);
  tmp |= __read23LCV1024Byte(address*4+1)<<8;
  tmp |= __read23LCV1024Byte(address*4+2)<<16;
  tmp |= __read23LCV1024Byte(address*4+3)<<24;
  return tmp;
}

uint32_t allocExternalRam(uint32_t size)
{
  
}

void freeExternalRam(uint32_t address, uint32_t size)
{
  
}
