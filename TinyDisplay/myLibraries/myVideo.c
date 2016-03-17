/*
 * myVideo.c
 *
 * Created: 2016-03-05 2:22:51 AM
 *  Author: take-iwiw
 */ 
#include <avr/io.h>
#include "../myCommon.h"
#include "myRetarget.h"
#include "myVideo.h"
#include "myTimer.h"

#ifdef USE_LCD_ST7735R_VIDEO
#include "../lcdST7735R_SPI/lcdST7735R_SPI.h"
#endif

/*** Internal Const Values ***/

/*** Internal Static Variables ***/
static uint8_t s_width;
static uint8_t s_height;
static uint8_t s_currentLine;
static uint16_t s_frameStartTimeMS;
#ifdef SUPPORT_LINE_BUFFER
static uint8_t s_buffer[VIDEO_LINE_BUFFER_SIZE];
#endif

/*** Internal Function Declarations ***/
/*** External Function Defines ***/
void videoInit()
{
#ifdef USE_LCD_ST7735R_VIDEO
	lcdST7735R_init();
#endif
}

void setVideoArea(uint8_t x0, uint8_t y0, uint8_t width, uint8_t height)
{
	s_width = width;
	s_height = height;
#ifdef USE_LCD_ST7735R_VIDEO
	lcdST7735R_setAddrWindow(x0, y0, x0 + width, y0 + height);
#endif
}

void startFrame()
{
	s_currentLine = 0;
	s_frameStartTimeMS = getTimeMS();
#ifdef USE_LCD_ST7735R_VIDEO
	lcdST7735R_startSendBurstData();
#endif
}

uint16_t stopFrame()
{
#ifdef USE_LCD_ST7735R_VIDEO
	lcdST7735R_stopSendBurstData();
#endif
	// check if frame skip happens
	uint16_t frameEndTimeMS = getTimeMS();
	uint16_t realFrameTime;
	if(frameEndTimeMS > s_frameStartTimeMS) {
		realFrameTime = (frameEndTimeMS - s_frameStartTimeMS)&0xffff;
		} else {
		realFrameTime = ((65535 - s_frameStartTimeMS) + frameEndTimeMS + 1)&0xffff;	// to avoid using more than 16bit
	}
	return realFrameTime;
}

void drawPixel(uint8_t dataHigh, uint8_t dataLow)
{
#ifdef USE_LCD_ST7735R_VIDEO
	lcdST7735R_sendBurstData(dataHigh, dataLow);
#endif
}

#ifdef SUPPORT_LINE_BUFFER
void drawLineBuffer(uint8_t lineNum)
{
#ifdef USE_LCD_ST7735R_VIDEO
	//lcdST7735R_restartSendBurstData();
#endif

	uint8_t* buffer = s_buffer;
	for(uint8_t x = 0; x < s_width; x++ ) {
		drawPixel(*buffer++, *buffer++);
	}
	s_currentLine+=lineNum;
	
#ifdef USE_LCD_ST7735R_VIDEO
	//lcdST7735R_pauseSendBurstData();
#endif
}

uint8_t* getLineBuffer()
{
	return s_buffer;
}
#endif

/*** Internal Function Definitions ***/
