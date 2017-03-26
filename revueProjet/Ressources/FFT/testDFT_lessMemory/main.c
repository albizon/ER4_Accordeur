#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

#define Nb 512
#define NbPointsParPeriodes 10

#define ADCTABSIZE 100
#define FFTTABSIZE 10
#define ADC_MIC 5
#define AMPLITUDE_FILTRE 1

int dt;
int df;
int size;
int dir = 1; // 1 = fft et -1 = reverse fft

float *adcTab[ADCTABSIZE];
float real[FFTTABSIZE];
float imag[FFTTABSIZE];
//float *fftTab[2][FFTTABSIZE]; // en [0][x] les réels et en [1][x] les imaginaires

int main()
{
    int i=0;
    printf("Hello world!\n");
    float x[Nb];
    float y[Nb];
    for ( i=0; i<Nb; i++) x[i]=0;
    for ( i=0; i<Nb; i++) y[i]=0;

    x[5]=1;
    //for ( i=0; i<Nb; i++) x[i]=sin((2.0 * 3.14 * i)/NbPointsParPeriodes);

            for ( i=0; i<Nb; i++) printf("%.1f ",x[i]);
            printf("\n\n");
            for ( i=0; i<Nb; i++) printf("%.2f ",y[i]);
            printf("\n\n\n");

    DFT(-1,x,y);

            for ( i=0; i<Nb; i++) printf("%.2f ",x[i]);
            printf("\n\n");
            for ( i=0; i<Nb; i++) printf("%f ",y[i]);
            printf("\n\n\n");

    return 0;
}

/*
   This computes an in-place complex-to-complex FFT
   real and imag are the real and imaginary arrays
   dir =  1 gives forward transform
   dir = -1 gives reverse transform
*/
void DFT(short int dir,float *real,float *imag)
{
   long i,k,j;
   float arg;
   float cosarg,sinarg;
   float temp_real;
   float temp_imag;
   float amplitude=0;

	if (dir==1)
	{
	   int j=0;
	   for (i=0;i<ADCTABSIZE;i++) {
		  temp_real = 0;
		  temp_imag = 0;
		  arg = - dir * 2.0 * 3.141592654 * (float)i / (float)ADCTABSIZE;
		  for (k=0;k<ADCTABSIZE;k++) {
			 cosarg = cos(k * arg);
			 sinarg = sin(k * arg);
			 temp_real += (real[k] * cosarg - imag[k] * sinarg);
			 temp_imag += (real[k] * sinarg + imag[k] * cosarg);
		  }
		  amplitude = sqrt((real[i]*real[i])+(imag[i]+imag[i]));
		  //if (amplitude>=AMPLITUDE_FILTRE)// si l'ampliude de la raie calculée est satisfaisante
		  //{
			  // attribution des valeurs
			  real[i] = temp_real / (float)ADCTABSIZE;
			  imag[i] = temp_imag / (float)ADCTABSIZE;
		  //}
	   }
	}
}

