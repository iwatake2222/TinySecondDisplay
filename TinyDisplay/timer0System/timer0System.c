/*
 * timer0System.c
 *
 * Created: 2016-03-03 7:26:30 PM
 *  Author: take-iwiw
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../myCommon.h"
#include "timer0System.h"

// over flow happens every 65.536 sec
static volatile uint16_t s_cntTimer0_1ms = 0;

void timer0SystemInit()
{
	// CTC Mode without compare output
	TCCR0A = (0<<COM0A0) | (0<<COM0B0) | (2<<WGM00);
	// Div = 1/64
	TCCR0B = 0x03;
	// Compare match every 1 msec (1/ (64/16M) / 1000)
	OCR0A = F_CPU / 64 / 1000;
	// Enable Compare Match A Interrupt
	TIMSK0 = (1<<OCIE0A);
}

uint8_t timer0SystemGetTimeMS()
{
	return s_cntTimer0_1ms;
}



ISR(TIMER0_COMPA_vect)
{
	s_cntTimer0_1ms++;
	return;
}
