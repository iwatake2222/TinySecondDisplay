/*
 * myVideo.h
 *
 * Created: 2016-03-05 2:23:04 AM
 *  Author: take-iwiw
 */ 


#ifndef MYVIDEO_H_
#define MYVIDEO_H_


/***
 * Const values
 ***/
#define SUPPORT_LINE_BUFFER
#ifdef SUPPORT_LINE_BUFFER
#define VIDEO_LINE_BUFFER_SIZE (128*4)
#endif

/***
 * Enum definitions
 ***/

/***
 * Struct definitions
 ***/

/***
 * External APIs
 ***/
void videoInit();
void setVideoArea(uint8_t x0, uint8_t y0, uint8_t width, uint8_t height);
void startFrame();
uint16_t stopFrame();	// return actual frame time[ms]
void drawPixel(uint8_t dataHigh, uint8_t dataLow);

#ifdef SUPPORT_LINE_BUFFER
uint8_t* getLineBuffer();
void drawLineBuffer(uint8_t lineNum);
#endif

#endif /* MYVIDEO_H_ */