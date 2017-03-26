#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

#define ADCTABSIZE 100
#define NbPointsParPeriodes 10
#define AMPLITUDE_MIN_FONDAMENTAL 30

float fondamental_real =0;
float fondamental_imag =0;
float freq_fondamental=0;

float adcTab[ADCTABSIZE];
int main()
{
    int i=0;
    printf("Hello world!\n");

    for ( i=0; i<ADCTABSIZE; i++){ adcTab[i]=100*sin((2.0 * 3.14 * i)/NbPointsParPeriodes);/* printf("%.0f ",x[i]); */}

    DFT_Detecteur_fondamental();

    //for (i=0;i<ADCTABSIZE;i++) printf("%.0f ",adcTab[i]);

    return 0;
}

void DFT_Detecteur_fondamental()
{
	int i,k;
	float arg,temp_real,temp_imag,amplitude;
	freq_fondamental=-1;
	for (i=0;i<ADCTABSIZE;i++)
	{
		temp_real = 0;
		temp_imag = 0;
		arg = - 2.0 * 3.141592654 * (float)i / (float)ADCTABSIZE;
		for (k=0;k<ADCTABSIZE;k++)
		{
			temp_real += (adcTab[k] * (float)cos(k * arg));
			temp_imag += (adcTab[k] * (float)sin(k * arg));
		}
		amplitude = sqrt((temp_real * temp_real)+(temp_imag * temp_imag ))/ (float)ADCTABSIZE ;
		freq_fondamental++;
		if (amplitude>AMPLITUDE_MIN_FONDAMENTAL)// si l'ampliude de la raie calculée est satisfaisante
		{
			// attribution des valeurs
			fondamental_real = temp_real / (float)ADCTABSIZE;
			fondamental_imag = temp_imag / (float)ADCTABSIZE;

			printf("mod  fondamental : %.0f ",sqrt(fondamental_real*fondamental_real+fondamental_imag*fondamental_imag));
			printf("freq fondamental : %.0f ",freq_fondamental);

			return 0;
		}
	}
}

