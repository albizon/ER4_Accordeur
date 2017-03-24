#include "sam.h"
#include "timer.h"

int TCinitClock(int source, int timerId)
{
	int result = 0;
	if((source > 4) ||(timerId > 7)) result = 1;
	else {
		//arguments Ok.
		//1: Power Management
		PM->APBCMASK.reg |= 1<<(timerId+8);
	
		//2: Clock source
		const static int timerToCLkId[] = {0x1A,0x1A,0x1B,0x1B,0x1C,0x1C,0x1D,0x1D};
		GCLK->CLKCTRL.reg = 1 <<14 | //enable
							source << 8 | //generator
							timerToCLkId[timerId];
	}
	return result;
}

