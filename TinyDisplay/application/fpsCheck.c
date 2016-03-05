/*
 * fpsCheck.c
 *
 * Created: 2016-03-05 3:36:18 AM
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
#define HEIGHT 128

void fpsCheck()
{
	while(1) {
		setVideoArea(0, 0, WIDTH, HEIGHT);
		startFrame();
		for(uint8_t y = 0; y < HEIGHT; y++){
			for(uint8_t x = 0; x < WIDTH; x++){
				drawPixel(0x00, 0x1F);
			}
		}
		uint8_t time = stopFrame();
		printDecPos(1000/time, 0, 0);
	}
}

void fpsCheckWithBuffer()
{
	while(1) {
		setVideoArea(0, 0, WIDTH, HEIGHT);
		startFrame();
		for(uint8_t y = 0; y < HEIGHT; y++){
			uint8_t *buffer = getLineBuffer();
			for(uint8_t x = 0; x < WIDTH; x++){
				*buffer++ = 0x00;
				*buffer++ = 0x1F;
			}
			drawLineBuffer(1);
		}
		uint8_t time = stopFrame();
		printDecPos(1000/time, 0, 0);
	}
}
