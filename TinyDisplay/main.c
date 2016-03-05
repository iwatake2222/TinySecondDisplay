/*
 * main.c
 *
 * Created: 2016-03-02 4:15:28 PM
 * Author : take-iwiw
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "myCommon.h"
#include <util/delay.h>

#include "./myLibraries/myStdio.h"
#include "./myLibraries/myTimer.h"
#include "./myLibraries/myVideo.h"
#include "./color/colorRGB.h"

static void init();

extern void tinyDisplay();
extern void fpsCheck();
extern void fpsCheckWithBuffer();
extern void moviePlayer();


int main(void)
{
	init();
	print("Hello");

	tinyDisplay();
	//fpsCheckWithBuffer();
	//moviePlayer();

	while(1);
	while(1){
		putchar(getchar());
	}

}

static void init()
{
	/* portInit */
	/*
	SET_BIT(DDRB, DDB5);
	CLR_BIT(PORTB, PORTB5);
	CLR_BIT(DDRB, DDB4);
	SET_BIT(PORTB, PORTB4);	
	*/

	timerInit();
	stdioInit();
	videoInit();
	
	sei();	//SET_BIT(SREG, SREG_I);
}

