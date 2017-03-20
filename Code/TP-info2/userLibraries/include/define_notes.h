/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 23/01/17
* Version : 1.0
*/

  #ifndef DEFINE_NOTE_H
  #define DEFINE_NOTE_H
  
  	#include <math.h>
  
  	
	//Definition du LA 440 de base (seule constante de notre accordeur)
  	#define LA_440_FREQ 440	
	
	/* Definition calculatoire des notes du 3eme octave à partir du la 440
	* Calcul effectué : 440*(2^(demiton/12))
	* Le demiton étant relatif au LA 440 
	* Exemple : le FA étant 4 demitons avant le LA on obtient -4
	* On obtient donc la fréquence 349,23Hz
	*/
	#define DO_3_FREQ		(LA_440_FREQ * pow(2.00, ((-9.00)/12.00)))
	#define REb_3_FREQ		(LA_440_FREQ * pow(2.00, ((-8.00)/12.00)))
	#define RE_3_FREQ		(LA_440_FREQ * pow(2.00, ((-7.00)/12.00)))
	#define MIb_3_FREQ		(LA_440_FREQ * pow(2.00, ((-6.00)/12.00)))
	#define MI_3_FREQ		(LA_440_FREQ * pow(2.00, ((-5.00)/12.00)))
	#define FA_3_FREQ		(LA_440_FREQ * pow(2.00, ((-4.00)/12.00)))
	#define SOLb_3_FREQ		(LA_440_FREQ * pow(2.00, ((-3.00)/12.00)))
	#define SOL_3_FREQ		(LA_440_FREQ * pow(2.00, ((-2.00)/12.00)))
	#define LAb_3_FREQ		(LA_440_FREQ * pow(2.00, ((-1.00)/12)))
	#define LA_3_FREQ		LA_440_FREQ
	#define SIb_3_FREQ		(LA_440_FREQ * pow(2.00, (1.00/12.00)))
	#define SI_3_FREQ		(LA_440_FREQ * pow(2.00, (2.00/12.00)))
	
	
	/* Definition calculatoire conditionnelle des notes pour n'importe quel octave/degré
	* Calcul effectué : noteDegré3*(2^(octave/12))
	* ici octave est l'octave souhaité et noteDegré3 est la note référence calculée ci dessus
	* Exemple : en utilisant DO(5) on obtient la fréquence du DO 5 ieme octave soit 1046,50Hz 
	* Tout ceci juste avec pour seule constante le LA 440
	*/
	#define DO(a)		(DO_3_FREQ		*	pow(2.00, ((a)-3.00)))
	#define REb(a)		(REb_3_FREQ		*	pow(2.00, ((a)-3.00)))
	#define RE(a)		(RE_3_FREQ		*	pow(2.00, ((a)-3.00)))
	#define MIb(a)		(MIb_3_FREQ		*	pow(2.00, ((a)-3.00)))
	#define MI(a)		(MI_3_FREQ		*	pow(2.00, ((a)-3.00)))
	#define FA(a)		(FA_3_FREQ		*	pow(2.00, ((a)-3.00)))
	#define SOLb(a)		(SOLb_3_FREQ		*	pow(2.00, ((a)-3.00)))
	#define SOL(a)		(SOL_3_FREQ		*	pow(2.00, ((a)-3.00)))
	#define LAb(a)		(LAb_3_FREQ		*	pow(2.00, ((a)-3.00)))
	#define LA(a)		(LA_3_FREQ		*	pow(2.00, ((a)-3.00)))
	#define SIb(a)		(SIb_3_FREQ		*	pow(2.00, ((a)-3.00)))
	#define SI(a)		(SI_3_FREQ		*	pow(2.00, ((a)-3.00)))
	
	
	// Définition d'un numéro associé à chaque note pour manipuler les notes
	#define NUM_DO		1
	#define NUM_REb		2
	#define NUM_RE		3
	#define NUM_MIb		4
	#define NUM_MI		5
	#define NUM_FA		6
	#define NUM_SOLb	7
	#define NUM_SOL		8
	#define NUM_LAb		9
	#define NUM_LA		10
	#define NUM_SIb		11
  	#define NUM_SI		12
  
  #endif
