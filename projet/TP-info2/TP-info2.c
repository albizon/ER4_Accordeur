/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 23/01/17
* Version : 1.0
*/  

#include "define.h"	

void DFT(int dir,int m,double *x1,double *y1)
{
	long i,k;
	double arg;
	double cosarg,sinarg;
	double *x2=NULL,*y2=NULL;

	x2 = malloc(m*sizeof(double));
	y2 = malloc(m*sizeof(double));
	
	if (x2 == NULL || y2 == NULL) return(FALSE);

	for (i=0;i<m;i++) {
		x2[i] = 0;
		y2[i] = 0;
		arg = - dir * 2.0 * 3.141592654 * (double)i / (double)m;
		for (k=0;k<m;k++) {
			cosarg = cos(k * arg);
			sinarg = sin(k * arg);
			x2[i] += (x1[k] * cosarg - y1[k] * sinarg);
			y2[i] += (x1[k] * sinarg + y1[k] * cosarg);
		}
	}

	/* Copy the data back */
	if (dir == 1) {
		for (i=0;i<m;i++) {
			x1[i] = x2[i] / (double)m;
			y1[i] = y2[i] / (double)m;
		}
		} else {
		for (i=0;i<m;i++) {
			x1[i] = x2[i];
			y1[i] = y2[i];
		}
	}

	free(x2);
	free(y2);
}

int main(void)//fonction principale du programme
{
	float *user_real;
	float *user_imag;
	float *user_mod;
	float *user_arg;
	float df=1;
	float freq = 0; //contient la fréquence mesurée de la note
	char note = 0; //contient la note calculée à partir de la fréquence, voir les différentes valeurs dans define_notes.h
	char degre = 0; //contient le degré, ou l'octave de la note calculée à partir de la fréqence
	float relativeError = 1.0;//spécifie l'erreur relative autorisée en % entre la fréquence mesurée et la fréquence réelle correspondant à la note
	setup();//Fonction d'initialisation
	//FFTInit(1);
	//adcFFTInit(1);
	//displayTitle(); //affiche le titre du projet en haut de l'écran OLED
	while(1)
	{
		double *x1[1000];
		for (int i =0; i<1000; i++) x1[i]=sin( (2.0 * 3.14 * i)/100 );
		DFT(1,1000,x1,y1);
		
		
		
		
		
		
		//freq=getFreq(); //Récupère la fréquence mesurée par le fréquencemètre
		
		/*Acquisition*/
		/*getTabsFFT(user_real,user_imag);
		user_real[0]=1;
		user_imag[0]=1;
		complexLinearToComplexExponential(user_real,user_imag,user_mod,user_arg);
		freq=getFreqPlay(user_mod,df);*/
		
		/*Traitement*/
		/*note = noteSolver(freq); //permet de déterminer la note correspondant à la fréquence mesurée
		degre = degreSolver(freq); //permet de déterminer le degré ou l'octave correspondant à la fréquence mesurée
		char acc = accorder(note, degre, freq, calculAbsError(relativeError, freq,0));//Permet de déterminer si la note est acoordée, trop basse ou trop haute*/
		
		/*Affichage*/
		/*diplayLedIndicator(acc); // Allume les leds en fonciton de l'indicateur : trop bas / ok / trop haut
		displayFrequence(freq); //On affiche la fréquence sur l'afficheur OLED
		displayNote(note); //On affiche la note sur l'afficheur OLED
		displayDegre(degre); //On affiche le degré sur l'afficheur OLED*/
		
	}
	
	return 0; //Le programme renvoit 0x0000 si l'execution c'est correctement terminée
}






