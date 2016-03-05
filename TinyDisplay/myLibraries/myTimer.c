/*
 * myTimer.c
 *
 * Created: 2016-03-03 7:33:53 PM
 *  Author: take-iwiw
 */ 

#include <avr/io.h>
#include "myRetarget.h"

#ifdef USE_TIMER0_SYSTEM
#include "../timer0System/timer0System.h"
#endif

volatile static uint16_t s_lastCntTimer0_1ms = 0;


void timerInit()
{
#ifdef USE_TIMER0_SYSTEM
	timer0SystemInit();
#endif

}

uint16_t getTimeMS()
{
#ifdef USE_TIMER0_SYSTEM
	return timer0SystemGetTimeMS();
#endif
	return 1;
}


uint16_t getIntervalTime()
{
	uint16_t now = getTimeMS();
	uint16_t previous = s_lastCntTimer0_1ms;
	s_lastCntTimer0_1ms = now;
	if(now > previous) {
		return (now - previous)&0xffff;
	} else {
		//return (1 << 16) - previous + now;
		return ((65535 - previous) + now + 1)&0xffff;	// to avoid using more than 16bit
	}
	
}
