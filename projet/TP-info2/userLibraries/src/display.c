#include "define.h"
#include "display.h"
#include <stdio.h>
#include <string.h>


void displayTitle()
{
	OLEDClear();
	OLEDSetLine(0);
	printf("Accordeur v1.0\n");
}

void displayNote(const char note)
{
	OLEDClearLine(3);
	OLEDSetLine(3);
	printf("Note  : ");
	switch (note){
	case NUM_DO :
		printf("Do\n");
	break;
	
	case NUM_REb :
		printf("Reb / Do#\n");
	break;
	
	case NUM_RE :
		printf("Re\n");
	break;
	
	case NUM_MIb :
		printf("Mib / Re#\n");
	break;
	
	case NUM_MI :
		printf("Mi\n");
	break;
	
	case NUM_FA :
		printf("Fa\n");
	break;
	
	case NUM_SOLb :
		printf("Solb / Fa#\n");
	break;
	
	case NUM_SOL :
		printf("Sol\n");
	break;
	
	case NUM_LAb :
		printf("Lab / Sol#\n");
	break;
	
	case NUM_LA :
		printf("La\n");
	break;
	
	case NUM_SIb :
		printf("Sib / La#\n");
	break;
	
	case NUM_SI :
		printf("Si\n");
	break;

	default:
		printf("inconnue\n");
	break;
	
	}
}

void displayFrequence(float freq)
{
	OLEDClearLine(1);
	OLEDSetLine(1);
	printf("Freq  : %.2f Hz\n", freq);
}

void displayDegre(char degre)
{
	OLEDClearLine(2);
	OLEDSetLine(2);
	printf("Degre : %d   \n",degre);
}



