/*
 * lcdST7735R_SPI.h
 *
 * Created: 2016-03-03 11:14:45 PM
 *  Author: take-iwiw
 */ 


#ifndef LCDST7735R_SPI_H_
#define LCDST7735R_SPI_H_

#include "../spi/spi.h"

void lcdST7735R_init();
// actual x1, y1 is -1 smaller
void lcdST7735R_fillRect(uint16_t color, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) ;
void lcdST7735R_setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void lcdST7735R_setRasterHorizontal();
void lcdST7735R_setRasterVertical();

void lcdST7735R_startSendBurstData();
void lcdST7735R_stopSendBurstData();
//void startSendBurstData(uint8_t dataHigh, uint8_t dataLow)
#define lcdST7735R_sendBurstData(dataHigh, dataLow) {spiSend(dataHigh); spiSend(dataLow);}
void lcdST7735R_pauseSendBurstData();
void lcdST7735R_restartSendBurstData();

// for text output
void lcdST7735R_putchar(char c);
void lcdST7735R_setCurPos(uint8_t textX, uint8_t textY);
void lcdST7735R_saveCurPos();
void lcdST7735R_loadCurPos();

// for bitmap output



#endif /* LCDST7735R_SPI_H_ */