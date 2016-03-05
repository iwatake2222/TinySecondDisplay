/*
 * spi.h
 *
 * Created: 2016-03-03 11:42:14 PM
 *  Author: take-iwiw
 */ 


#ifndef SPI_H_
#define SPI_H_

#define SPI_MODE0 0
#define SPI_MODE1 1
#define SPI_MODE2 2
#define SPI_MODE3 3
#define SPI_DIV_4 0
#define SPI_DIV_16 1
#define SPI_DIV_64 2
#define SPI_DIV_128 3
#define SPI_SPEED_1X 0
#define SPI_SPEED_2X 1


void spiOpen(uint8_t isLsbFirst, uint8_t isMaster, uint8_t mode, uint8_t div, uint8_t isDouble);
void spiClose();
void spiSend(uint8_t data);
uint8_t spiRecv();
uint8_t spiSendRecv(uint8_t data);


#endif /* SPI_H_ */