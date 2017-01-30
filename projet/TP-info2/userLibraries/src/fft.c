#include "define.h"
#include "fft.h"
#include "note.h"

/*
En entrée : 
  N : nombre de points en puissance de 2,
  R, I : tableaux de N points contenant les parties réelles (R) et imaginaires (I) du signal d'entrée. Pour un signal réel, I doit être initialisé à 0.
  inverse : booléen qui indique si le calcul est une transformée directe (False) ou inverse (True).
En sortie : 
  R,I : tableaux qui contiennent les parties réelles et imaginaires de la transformée de FOURIER directe ou inverse calculée.
  Type RESULD : Array [0..1023] Of Real ;
*/

float *_adcReal;
float *_real;
float *_imag;
int _deltaT;
int _deltaF;
int _size;
	
void fft(int inverse, float *R, float *I)
{
	int N=0;
	if(sizeof(&R)>sizeof(&I)) {N = sizeof(&I);}
	else {N = sizeof(&R);}
  const float PI = 3.141592 ;
  const float UFL = 1.0E-38 ;
  const float OVF = 1.0E38 ;
  int N1,N2,J,K,M,L1,L2,L,I5,IJ;
  float T1,T2,W1,W2,U1,U2,Z1,Z2;
  
  if (inverse==TRUE)
  {
      for (IJ=0; IJ<(N-1);IJ++)
      {
        R[IJ] = R[IJ]/N;
		I[IJ] = I[IJ]/N;
      }
  }
  
  M = arrondi(log(N)/log(2)) ;
	N2 = N / 2 ;
	N1 = N-1 ;
	J = 1 ;
  
  for (IJ=0; (IJ<N1) ; IJ++)
  {
  	if (IJ<J)
         {
		T1 = R[J-1] ;
		T2 = I[J-1] ;
		R[J-1] = R[IJ-1] ;
		I[J-1] = I[IJ-1] ;
		R[IJ-1] = T1 ;
		I[IJ-1] = T2 ;
         }
         K = N2 ;
         do {
			J = J - K ;
			K =K / 2 ;
         } while (K<J);
         J = J+K ;
  }
  
  for  (L=1; L<M; L++ )
  {
	L1 = trunc(exp(L*log(2))) ;
	L2 = L1 / 2 ;
	U1 = 1 ;
	U2 = 0 ;
	W1 = cos(PI/L2) ;
	W2 = 0-sin(PI/L2) ;
	if (inverse==TRUE)  W2 = 0-W2 ;
	for (J=1; J<L2; J++ )
	{
		IJ = J ;
		do{
                   I5 = IJ+L2 ;
                   T1 = R[I5-1]*U1-I[I5-1]*U2 ;
                   T2 = R[I5-1]*U2+I[I5-1]*U1 ;
                   R[I5-1] = R[IJ-1] - T1 ;
                   I[I5-1] = I[IJ-1] - T2 ;
                   R[IJ-1] = R[IJ-1] + T1 ;
                   I[IJ-1] = I[IJ-1] + T2 ;
                   IJ = IJ + L1 ;
                } while( IJ>=N) ;
             
                Z1 =U1*W1-U2*W2 ;
             
                if (abs(Z1)>OVF)
                {
					if (Z1>0) Z1 = OVF;
					else Z1 = 0-OVF ;
                }
             
                if (abs(Z1)<UFL)
                {
					Z1 = 0 ;
					Z2 = U1*W2+U2*W1 ;
                }
             
		if (abs(Z2)>OVF) 
		{
			if (Z2>0) Z2 = OVF;
			else Z2 = 0-OVF ;
		}
             
		if (abs(Z2)<UFL) 
		{
			Z1 = 0 ;
			U1 = Z1 ;
		}
             
		U2 = Z2 ;
	}
  }  
}


void adcFFTInit(int deltaT) // deltaT en us
{
	ADCInit();
	_deltaT=deltaT;
	// TIMER TC3 à 1MHz
	TCinitClock(F48MHZ,3); // Initialisation de l'horloge à 1MHz pour le timer TC3
	TC3->COUNT16.CTRLA.reg= (0x4<<8); // intialisation d'un prescaler de '100' soit une division par 16 donc 1/16 de 48Mhz
	TC3->COUNT16.CTRLBSET.reg=0x1; // Initialisation du timer en décrémentation
	TC3->COUNT16.COUNT.reg=(_deltaT*3); // Chargement du compteur
	TC3->COUNT16.INTFLAG.reg=0x1; // Validation de l'overflow
	TC3->COUNT16.CTRLA.reg |=2; // Démarrage du timer
	
	//validation du timer sur overflow
	TC3->COUNT16.INTENSET.reg = 1 ;
	//validation NVIC
	NVIC_EnableIRQ ( TC3_IRQn ) ;
	//priorité (si plusieurs its...)
	NVIC_SetPriority ( TC3_IRQn , 2 ) ;
}

void FFTInit(int deltaF)
{
	_deltaF=deltaF;
	_size=(_deltaF*1000)/_deltaT;
	
	float *tempPtr;
	
	tempPtr = malloc(_size * sizeof(*_real));
	if(tempPtr == NULL) {free(_real);}
	else {_real = tempPtr;}
		
	tempPtr = malloc(_size * sizeof(*_imag));
	if(tempPtr == NULL) {free(_imag);}
	else {_imag = tempPtr;}
		
	tempPtr = malloc(_size * sizeof(*_adcReal));
	if(tempPtr == NULL) {free(_adcReal);}
	else {_adcReal = tempPtr;}
		
	// TIMER TC4 à 1MHz
	TCinitClock(F1MHZ,4); // Initialisation de l'horloge à 1MHz pour le timer TC4
	TC4->COUNT16.CTRLA.reg= (0x0<<8); // intialisation d'un prescaler de '000' soit une division par 1 donc 1/1 de 1Mhz
	TC4->COUNT16.CTRLBSET.reg=0x1; // Initialisation du timer en décrémentation
	TC4->COUNT16.COUNT.reg=_deltaF; // Chargement du compteur
	TC4->COUNT16.INTFLAG.reg=0x1; // Validation de l'overflow
	TC4->COUNT16.CTRLA.reg |=2; // Démarrage du timer

	//validation du timer sur overflow
	TC4->COUNT16.INTENSET.reg = 1 ;
	//validation NVIC
	NVIC_EnableIRQ ( TC4_IRQn ) ;
	//priorité (si plusieurs its...)
	NVIC_SetPriority ( TC4_IRQn , 3 ) ;
	
}

void TC3_Handler ( ) // Récupération périodique des valeurs de l'ADC
{	
	__disable_irq();
	TC3->COUNT16.COUNT.reg=(_deltaT*3); // Chargement du compteur
	
	static int i=0;
	_adcReal[i]=(float)ADCRead(ADC_MIC)*(3.3/4096.00);
	if (i==_size) i=0;
	else i++;
	
	TC3->COUNT16.INTFLAG.reg = 1 ;
	__enable_irq();
}void TC4_Handler ( ) // FFT périodique
{
	__disable_irq();
	TC4->COUNT16.COUNT.reg=_deltaF; // Chargement du compteur
	
	memcpy(_real,_adcReal,_size);
	fft(FALSE,_real,_imag);

	TC4->COUNT16.INTFLAG.reg = 1 ;
	__enable_irq();
}void getTabsFFT(float *real,float *imag){	float *tempPtr;
	
	tempPtr = malloc(_size * sizeof(*real));
	if(tempPtr == NULL) {free(real);}
	else {real = tempPtr;}
		
	tempPtr = malloc(_size * sizeof(*imag));
	if(tempPtr == NULL) {free(imag);}
	else {imag = tempPtr;}			memcpy(_real,real,_size);	memcpy(_imag,imag,_size);}


