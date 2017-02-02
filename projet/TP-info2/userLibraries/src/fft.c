
#include "define.h"

struct floatSingleArray * _adcReal;
struct floatSingleArray * _real;
struct floatSingleArray * _imag;
int _deltaT;
int _deltaF;
int _size;


void fft(short int dir,struct floatSingleArray *real,struct  floatSingleArray *imag)
{
   long  tabsize,bintabsize,i,i1,j,k,i2,l,l1,l2;
   float  temp_real,temp_imag,c1,c2,t1,t2,u1,u2,z;
	
	/* Calcul du nombre de points */
		tabsize = lengthfloatSingleArray(real); // On récupère la taille du tableau de réels
		j = tabsize ;
		i=0;
		do // calcul de la taille du tableau en 2^binsize sans reste
		{
			j /= 2;
			i++;
		}
		while(j>=2); 
		bintabsize = i; // taille du tableau en 2^binsize sans reste
   	/* Attribution de mémoire au tableau d'imaginaires */ 
		imag = reallocfloatSingleArray(imag,tabsize);
	/* inversion de bit */
		i2 = tabsize >> 1;
		j = 0;
		for (i=0;i<(tabsize-1);i++) 
		{
			if (i < j) 
			{
				temp_real = real->array[i];
				temp_imag = imag->array[i];
				real->array[i] = real->array[j];
				imag->array[i] = imag->array[j];
				real->array[j] = temp_real;
				imag->array[j] = temp_imag;
			}
			k = i2;
			while (k <= j)
			{
				j -= k;
				k >>= 1;
			}
			j += k;
		}
	/* Calcul de la FFT */
		c1 = -1.0;
		c2 = 0.0;
		l2 = 1;
		for (l=0;l< bintabsize ;l++) 
		{
			l1 = l2;
			l2 <<= 1;
			u1 = 1.0;
			u2 = 0.0;
			for (j=0;j<l1;j++) 
			{
				for (i=j;i<tabsize;i+=l2)
				{
					i1 = i + l1;
					t1 = u1 * real->array[i1] - u2 * imag->array[i1];
					t2 = u1 * imag->array[i1] + u2 * real->array[i1];
					real->array[i1] = real->array[i] - t1;
					imag->array[i1] = imag->array[i] - t2;
					real->array[i] += t1;
					imag->array[i] += t2;
				}
				z =  u1 * c1 - u2 * c2;
				u2 = u1 * c2 + u2 * c1;
				u1 = z;
			}
			c2 = sqrt((1.0 - c1) / 2.0);
			if (dir == 1)
			c2 = -c2;
			c1 = sqrt((1.0 + c1) / 2.0);
		}
		if (dir == 1) 
		{
			for (i=0;i<tabsize;i++)
			{
				real->array[i] /= tabsize;
				imag->array[i] /= tabsize;
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
	
	__disable_irq();

	_real = reallocfloatSingleArray(_real, _size);
	_imag = reallocfloatSingleArray(_imag, _size);
	_adcReal = reallocfloatSingleArray(_adcReal, _size);
		
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
	fft(1,_real,_imag);

	TC4->COUNT16.INTFLAG.reg = 1 ;
	__enable_irq();
}

void getTabsFFT(struct floatSingleArray *real,struct floatSingleArray *imag)
{
	__disable_irq();
	
	//float *tempPtr;
	real = reallocfloatSingleArray(real, _size);
	imag = reallocfloatSingleArray(imag, _size);
		
	memcpy(_real,real,lengthfloatSingleArray(_real));
	free(_real);
	memcpy(_imag,imag,lengthfloatSingleArray(_imag));
	free(_imag);
	
	__enable_irq();
}