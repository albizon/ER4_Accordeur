#ifndef __SERIAL_H__
#define __SERIAL_H__

//init SERCOM3 pour communication série virtuelle via debug USB
//configuration 115200 bauds 8N1
void SERIALInit();

void SERIALPutchar(char txd);

void SERIALPutString(char *str);
#endif
