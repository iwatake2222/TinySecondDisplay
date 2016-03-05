/*
 * tinyDisplay.c
 *
 * Created: 2016-03-05 3:02:00 AM
 *  Author: take-iwiw
 */ 

#include <avr/io.h>
#include "../myCommon.h"
#include <util/delay.h>

#include "../myLibraries/myStdio.h"
#include "../myLibraries/myTimer.h"
#include "../myLibraries/myVideo.h"
#include "../color/colorRGB.h"

#define WIDTH 128
#define HEIGHT 80

void tinyDisplay()
{
	printPos("Tiny Display", 0, 0);
	uint8_t cnt = 0;
	while(1) {
		printDecPos(cnt++, 0, 1);
		setVideoArea(0, 30, WIDTH, HEIGHT);
		startFrame();
		for(uint8_t y = 0; y < HEIGHT; y++){
			for(uint8_t x = 0; x < WIDTH; x++){
				uint8_t dataHigh = getchar();
				uint8_t dataLow = getchar();
				drawPixel(dataHigh, dataLow);
			}
		}
		uint16_t time = stopFrame();
		//printDecPos(time, 0, 0);
		//printPos("msec", 4, 0);
	}
}
