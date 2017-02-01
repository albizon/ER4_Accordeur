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

floatSingleArray *_adcReal;
floatSingleArray *_real;
floatSingleArray *_imag;
int _deltaT;
int _deltaF;
int _size;

void fft(int inverse, floatSingleArray *real, floatSingleArray *imag)
//void FFT( complex double *x, , int N ) 
{
    
tabSize=length(real); // On récupère la taille du tableau
floatSingleArray *temp_real; 
temp_real = realloc(temp_real,tabSize);
	
	if (inverse == FALSE) // Si on veut faire une FFT
	{
		
		
		
		/*for ( int k = 0; k < tabSize; k++ ) 
		{
			temp_real-> array[k] = 0;
			
			for ( int j = 0; j < tabSize; j++ ) 
			{
				temp_real-> array[k] += real[j] ;
				imag     -> array[k] += cexp( 2.0 * I * M_PI * j * k / tabSize );
			}*/
	    }
	    for ( int k = 0; k < tabSize; k++ ) 
	    {
		   real-> array[k] =  temp_real[k];
	    }
	}
	else if (inverse == TRUE) // si on veut faire une FFT inverse
	{
		// ALGO FFT INVERSE
	}
	free( temp_real );
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
	
	__disable_irq();

	_real = realloc(_real, _size);
	_imag = realloc(_imag, _size);
	_adcReal = realloc(_adcReal, _size);
		
	__enable_irq();
		
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
	_adcReal->array[i]=(float)ADCRead(ADC_MIC)*(3.3/4096.00);
	if (i==_size) i=0;
	else i++;
	
	TC3->COUNT16.INTFLAG.reg = 1 ;
	__enable_irq();
}

void TC4_Handler ( ) // FFT périodique
{
	__disable_irq();
	TC4->COUNT16.COUNT.reg=_deltaF; // Chargement du compteur
	
	memcpy(_real,_adcReal,sizeof(_adcReal));
	fft(FALSE,_real,_imag);

	TC4->COUNT16.INTFLAG.reg = 1 ;
	__enable_irq();
}

void getTabsFFT(float *real,float *imag)
{
	__disable_irq();
	
	float *tempPtr;
	real = realloc(real, _size);
	imag = realloc(imag, _size);
		
	memcpy(_real,real,sizeof(_real));
	free(_real);
	memcpy(_imag,imag,sizeof(_imag));
	free(_imag);
	
	__enable_irq();
}





