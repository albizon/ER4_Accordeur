#include "redirectPrintf.h"
#include "oled.h"
#include "serial.h"

//valeur par defaut: OLED.
int printfRedir = PRINTF_OLED;

void redirectPrintf(unsigned int config)
{
	if(config>2) return;
	printfRedir = config;
}

/* Lien avec stdio pour utilisation avec printf */
int __attribute__((weak))
_write (int file, const char *ptr, int len)
{
	int i = 0;
	//verification que c'est bien la sortie standard
	if(file != 1) return -1;
	if(printfRedir == PRINTF_OLED)
	{
		for(i=0;i<len;i++) OLEDPrintChar(ptr[i]);
	} else if(printfRedir == PRINTF_SERIAL) {
		for(i=0;i<len;i++) SERIALPutchar(ptr[i]);
	}	
	return i;
}
