#ifndef __DEFINE_H__
#define __DEFINE_H__
	
	#include "sam.h"
	#include "adc.h"
    #include "dac.h"
	#include "eic.h"
	//#include "clock.h"
	#include "oled.h"
	#include "pinAccess.h"
	#include "pinMux.h"
	#include "redirectPrintf.h"
	#include "serial.h"
	#include "timer.h"
	#include <math.h>
	
	#include "fft.h"
	#include "display.h"
	#include "freq.h"
	#include "user_init.h"
	#include "note.h"
	#include "define_note.h"
	
	#define LA_440_FREQ 440
	
	#define DO_3_FREQ		(LA_440_FREQ * pow(2.00, ((-9)/12)))
	#define REb_3_FREQ		(LA_440_FREQ * pow(2.00, ((-8)/12)))
	#define RE_3_FREQ		(LA_440_FREQ * pow(2.00, ((-7)/12)))
	#define MIb_3_FREQ		(LA_440_FREQ * pow(2.00, ((-6)/12)))
	#define MI_3_FREQ		(LA_440_FREQ * pow(2.00, ((-5)/12)))
	#define FA_3_FREQ		(LA_440_FREQ * pow(2.00, ((-4)/12)))
	#define SOLb_3_FREQ		(LA_440_FREQ * pow(2.00, ((-3)/12)))
	#define SOL_3_FREQ		(LA_440_FREQ * pow(2.00, ((-2)/12)))
	#define LAb_3_FREQ		(LA_440_FREQ * pow(2.00, ((-1)/12)))
	#define LA_3_FREQ		LA_440_FREQ
	#define SIb_3_FREQ		(LA_440_FREQ * pow(2.00, (1/12)))
	#define SI_3_FREQ		(LA_440_FREQ * pow(2.00, (2/12)))

	#define DO(a)		(DO_3_FREQ		*	pow(2.00, ( (a) -3)))
	#define REb(a)		(REb_3_FREQ		*	pow(2.00, ((a)-3)))
	#define RE(a)		(RE_3_FREQ		*	pow(2.00, ((a)-3)))
	#define MIb(a)		(MIb_3_FREQ		*	pow(2.00, ((a)-3)))
	#define MI(a)		(MI_3_FREQ		*	pow(2.00, ((a)-3)))
	#define FA(a)		(FA_3_FREQ		*	pow(2.00, ((a)-3)))
	#define SOLb(a)		(SOLb_3_FREQ	*	pow(2.00, ((a)-3)))
	#define SOL(a)		(SOL_3_FREQ		*	pow(2.00, ((a)-3)))
	#define LAb(a)		(LAb_3_FREQ		*	pow(2.00, ((a)-3)))
	#define LA(a)		(LA_3_FREQ		*	pow(2.00, ((a)-3)))
	#define SIb(a)		(SIb_3_FREQ		*	pow(2.00, ((a)-3)))
	#define SI(a)		(SI_3_FREQ		*	pow(2.00, ((a)-3)))
	
	
	
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
	
	#define LOW_FREQ	1
	#define OK_FREQ		2
	#define HIGH_FREQ	3
	
#endif
