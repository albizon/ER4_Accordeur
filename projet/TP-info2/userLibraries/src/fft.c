/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 28/01/17
* Version : 2.0
*/ 

#include "define.h"
#include "fft.h"
#include "samd21Adc.h"
#include "samd21Gpio.h"

#define ADCTABSIZE 4096 //Taille du tableau de l'ADC
#define dt 0.00002261 //pas d'échantillonnage temporel : 22.61 us
float df=1/(dt*ADCTABSIZE); // pas d'échantillonnage fréquentiel : 10.7979Hz

float freq_fondamental=0; // contient la fréquence du fondamental

int16_t real[ADCTABSIZE]; // TABLEAU PRINCIPAL DE CALCUL
int16_t imag[ADCTABSIZE]; // Tableau des imaginaires de la FFT
int16_t temp=0; // Une valeur temporaire
int16_t tempAdc=0; // valeur tampon pour le moyennage par 10 des valeurs de l'ADC

void FFTInit()
{
		__disable_irq(); //On annule les IT momentannément
	/* INIT ADC */
		uint32_t args[2] = {PORTB, 8};
		pinMux_gpioSamd21(args, CONFIG_B);
		uint32_t arg[2] = {PORTB, 9};
		pinMux_gpioSamd21(arg, CONFIG_B);
		uint32_t args2[3] = {F8MHZ, SAMD21_ADC_VREF_INT1V,0};
		init_adc(args2);
	/* TIMER DE l'ADC */
		// TIMER TC3 de période 22.61us
			TCinitClock(F48MHZ,3); // Initialisation de l'horloge à 48MHz pour le timer TC3
			TC3->COUNT16.CTRLA.reg= (0x5<<8); // intialisation d'un prescaler de '101' soit une division par 64 donc 0.75Mhz
			TC3->COUNT16.CTRLBSET.reg=0x1; // Initialisation du timer en décrémentation
			TC3->COUNT16.COUNT.reg=(17); // Chargement du compteur
			TC3->COUNT16.INTFLAG.reg=0x1; // Validation de l'overflow
			TC3->COUNT16.CTRLA.reg |=2; // Démarrage du timer
			//validation du timer sur overflow
			TC3->COUNT16.INTENSET.reg = 1 ;
			//validation NVIC
			NVIC_EnableIRQ ( TC3_IRQn ) ;
			//priorité (si plusieurs its...)
			NVIC_SetPriority ( TC3_IRQn , 1 ) ;
	/* INIT FFT */
		// TIMER TC4 à 1MHz
			TCinitClock(F48MHZ,4); // Initialisation de l'horloge à 48MHz pour le timer TC4
			TC4->COUNT16.CTRLA.reg= (0x7<<8); // intialisation d'un prescaler de '111' soit une division par 1024
			TC4->COUNT16.CTRLBSET.reg=0x1; // Initialisation du timer en décrémentation
			TC4->COUNT16.COUNT.reg= 46875; // Chargement du compteur pour 1 seconde
			TC4->COUNT16.INTFLAG.reg=0x1; // Validation de l'overflow
			TC4->COUNT16.CTRLA.reg |=2; // Démarrage du timer

			//validation du timer sur overflow
			TC4->COUNT16.INTENSET.reg = 1 ;
			//validation NVIC 
			NVIC_EnableIRQ ( TC4_IRQn ) ;
			//priorité (si plusieurs its...)
			NVIC_SetPriority ( TC4_IRQn , 2 ) ;
		
		OLEDClear(); // On nettoie l'afficheur
	
		__enable_irq(); // On réautorise les interuptions
		
}

void FFT_Detecteur_fondamental()
{
		int dir=1; // Paramètre de sens de la FFT (1=FFT et -1=FFT reverse) 
		int n=0; // Incrémenteur
		
	// ALGO FFT  //////////////////////////////////////////////////////////////////////////////////////////////////
		long binsize,i,i1,j,k,i2,l,l1,l2;
		float c1,c2,temp_real,temp_imag,t1,t2,u1,u2,z;
		
		/* Calcul du nombre de points */
		j = ADCTABSIZE ;
		i=0;
		do // calcul de la taille du tableau en 2^binsize sans reste
		{
			j /= 2;
			i++;
		}
		while(j>=2);
		binsize = i; // taille du tableau en 2^binsize sans reste
		
		/* inversion de bit */
		i2 = ADCTABSIZE >> 1;
		j = 0;
		for (i=0;i<(ADCTABSIZE-1);i++)
		{
			if (i < j)
			{
				temp_real = real[i];
				temp_imag = imag[i];
				real[i] = real[j];
				imag[i] = imag[j];
				real[j] = temp_real;
				imag[j] = temp_imag;
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
		for (l=0;l< binsize ;l++)
		{
			l1 = l2;
			l2 <<= 1;
			u1 = 1.0;
			u2 = 0.0;
			for (j=0;j<l1;j++)
			{
				for (i=j;i<ADCTABSIZE;i+=l2)
				{
					i1 = i + l1;
					t1 = u1 * real[i1] - u2 * imag[i1];
					t2 = u1 * imag[i1] + u2 * real[i1];
					real[i1] = real[i] - t1;
					imag[i1] = imag[i] - t2;
					real[i] += t1;
					imag[i] += t2;
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
			for (i=0;i<ADCTABSIZE;i++)
			{
				real[i] /= ADCTABSIZE;
				imag[i] /= ADCTABSIZE;
			}
		}
			
	// Calcul des raies en absolu /////////////////////////////////////////////////////////////////////////////////
		for(n=0;n<ADCTABSIZE;n++) 
		{
			temp=sqrt(((int32_t)real[n] * (int32_t)real[n])+((int32_t)imag[n] * (int32_t)imag[n] ));
			real[n] = temp;
		}
				
	// Calcul moyennage glissant sur 5 échantillons ////////////////////////////////////////////////////////////////
		for(n=4;n<ADCTABSIZE;n++)
		{	
			 real[n-4]=(real[n]+real[n-1]+real[n-2]+real[n-3]+real[n-4])/5; 
			 if (real[n-4]<=1) // On ne prend que les valeurs supérieures à 1 pour supprimer les lobs récalcitrants
			 {
				 real[n-4]=0;
			 }				
		}
		real[ADCTABSIZE-4]=(real[n]+real[n-1]+real[n-2]+real[n-3])/4;
		real[ADCTABSIZE-3]=(real[n]+real[n-1]+real[n-2])/3;
		real[ADCTABSIZE-2]=(real[n]+real[n-1])/2;
		real[ADCTABSIZE-1]=(real[n])/1;
		
	// Calcul dérivée ////////////////////////////////////////////////////////////////////////////////////////////
	// et détection du fondamental
		int16_t derivRaies1=0; // Valeur précédente
		int16_t derivRaies2=0;// Valeur actuelle
		freq_fondamental=0;
		n=0;
		int montee=0;
		do
		{
			n++;
			derivRaies2=(real[n+1]-real[n]);
			if (derivRaies2<2) derivRaies2=0;
			
			if (derivRaies2>derivRaies1) // si plus grand que celui d'avant alors on est en train de monter
			{
				montee=1;
			}
			if (montee==1 && derivRaies2<derivRaies1 ) // si on est en montée et qu'on redescent c'est qu'on a atteint le premier max
			{
				freq_fondamental=n*df/10;
			} 
						
			derivRaies1=derivRaies2;
		}
		while ((n<ADCTABSIZE-1) && freq_fondamental==(0)); // tant qu'on a pas balayé le tableau ou trouvé un max
}

void TC3_Handler() // Récupération périodique des valeurs de l'ADC toute les 22.61us
{	
	/* Pour la récupération des valeurs de l'ADC on triche un peu pour gagner en RAM et garder la précision de 1Hz
	On récupère les valeurs de l'ADC, et toute les 10valeurs, on fait la moyenne de ces 10 valeurs et on met la valeur moyenne
	dans le vrai tableau de réels. Cela revient a filtrer passe bas... 
	Ainsi on a un tableau de 4096 valeurs qui en contient en fait 40960.*/
	
	__disable_irq(); //On désactive les IT pendant le traitement ADC
		
	static int i=0; // Incrémenteur principal [0;ADCTABSIZE]
	static int j=0; // Incrépenteur secondaire [0;10]
	
	uint32_t tab[3] = {0,SAMD21_ADC_MUX_AIN2,SAMD21_ADC_MUX_AIN3};
	tempAdc+=read_adc(tab);
	
	if (j==10) // quand on en a 10
	{
		int k=0;
		/* FIFO = First In First Out, ainsi on obtient un tableau "glissant" */
		for(k=0;k<ADCTABSIZE;k++) real[k]=real[k+1]; // On décale tout le tableau vers la gauche pour le FIFO
		real[i] = tempAdc/10; // ON en fait la moyenne et on charge dans le tableau
		tempAdc=0;
		j=0;
		i++;
	}
	else j++;	
	if (i==ADCTABSIZE) i=0; // RAZ si on a balayé tout le tableau de réel

	TC3->COUNT16.INTFLAG.reg = 0x1 ; // On valide l'overflow
	TC3->COUNT16.COUNT.reg=17; // On recharge le compteur
	
	__enable_irq(); // On réautorise les IT
}

void TC4_Handler ( ) // FFT + code principal (appelé toute les secondes)
{
	
	__disable_irq(); // On désactive momentanément les IT pour ne pas être interrompu
	
	
	FFT_Detecteur_fondamental(); //On lance le calcul de FFT plus détection de fondamental
	
	char note = 0;//contient la note calculée à partir de la fréquence, voir les différentes valeurs dans define_notes.h
	char degre = 0;//contient le degré, ou l'octave de la note calculée à partir de la fréqence
	float relativeError = 1.0;//spécifie l'erreur relative autorisée en % entre la fréquence mesurée et la fréquence réelle correspondant à la note
	note = noteSolver(freq_fondamental);//permet de déterminer la note correspondant à la fréquence mesurée
	degre = degreSolver(freq_fondamental);//permet de déterminer le degré ou l'octave correspondant à la fréquence mesurée
	char acc = accorder(note, degre, freq_fondamental, calculAbsError(relativeError, freq_fondamental,1));//Permet de déterminer si la note est acoordée, trop basse ou trop haute
	diplayLedIndicator(acc); // Allume les leds en fonciton de l'indicateur : trop bas / ok / trop haut
	displayFrequence(freq_fondamental);//On affiche la fréquence sur l'afficheur OLED
	displayNote(note);//On affiche la note sur l'afficheur OLED
	displayDegre(degre);//On affiche le degré sur l'afficheur OLED
	
	TC4->COUNT16.INTFLAG.reg = 0x1 ; // On valide l'overflow
	TC4->COUNT16.COUNT.reg=46875; // On recharge le compteur
	
	__enable_irq(); // On réactive les IT
	
}
