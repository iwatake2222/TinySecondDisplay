/*
 * myVideo.h
 *
 * Created: 2016-03-05 2:23:04 AM
 *  Author: take-iwiw
 */ 


#ifndef MYVIDEO_H_
#define MYVIDEO_H_

#define VIDEO_LINE_BUFFER_SIZE (128*4)

void videoInit();
void setVideoArea(uint8_t x0, uint8_t y0, uint8_t width, uint8_t height);
void startFrame();
// return actual frame time[ms]
uint16_t stopFrame();
uint8_t* getLineBuffer();
void drawLineBuffer(uint8_t lineNum);
void drawPixel(uint8_t dataHigh, uint8_t dataLow);



#endif /* MYVIDEO_H_ */