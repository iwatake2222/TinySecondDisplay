/*
 * spi.c
 *
 * Created: 2016-03-03 11:47:45 PM
 *  Author: take-iwiw
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../myCommon.h"
#include "spiConfig.h"
#include "spi.h"


static uint8_t s_isUsing = 0;
static volatile uint8_t s_spiRecvBuffer[SOFTWARE_BUFFER_SIZE];
static volatile uint8_t s_spiRecvWrite = 0;
static volatile uint8_t s_spiRecvRead = 0;
static volatile uint8_t *sp_spiSendBuffer;
static volatile uint8_t s_spiSendWrite = 0;
static volatile uint8_t s_spiSendRead = 0;



void spiOpen(uint8_t isLsbFirst, uint8_t isMaster, uint8_t mode, uint8_t div, uint8_t isDouble)
{
	while(s_isUsing != 0);
	s_isUsing = 1;
	
	SET_BIT(SPI_DDR, SPI_MOSI_BIT);
	CLR_BIT(SPI_DDR, SPI_MISO_BIT);
	SET_BIT(SPI_DDR, SPI_SCK_BIT);
	
	uint8_t spcr = (1<<SPE) | ((isLsbFirst!=0)<<DORD) | ((isMaster!=0)<<MSTR) | (mode<<CPHA) | div;

	SPCR = spcr;
	SPSR |= (isDouble == 0 ? 0 : 1);
}

void spiClose()
{
	s_isUsing = 0;
}

static void uart0SendSetRegister()
{
	s_spiRecvBuffer[s_spiRecvWrite++] = SPDR;
	if (s_spiSendWrite != s_spiSendRead){
		SPDR = sp_spiSendBuffer[s_spiSendRead++];
	} else {
		SPCR &= ~(1<<SPIE);		
		s_spiSendRead = 0;
		s_spiSendWrite = 0;
	}

}

// seems interrupt handler is heavy (stack store). but, it happens every 8 clock
void spiSendBurst(uint8_t *data, uint8_t size)
{
	if( size > SOFTWARE_BUFFER_SIZE) return;
	
	//uint8_t dummy = SPSR; dummy = SPDR;	// clear SPIF not to cause Interrupt when set SPIE
	while( s_spiSendWrite != 0);
	sp_spiSendBuffer = data;
	SPCR |= (1<<SPIE);
	s_spiSendWrite = size;
	s_spiSendRead = 0;
	s_spiRecvWrite = 0;
	s_spiRecvRead = 0;
	uart0SendSetRegister();
}

void waitBurstEnd()
{
	while( s_spiSendWrite != 0);
}


void spiSend(uint8_t data)
{
	while( s_spiSendWrite != 0);
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
}

uint8_t spiRecv()
{
	while( s_spiSendWrite != 0);
	uint8_t data;
	SPDR = 0;
	while(!(SPSR & (1<<SPIF)));
	data = SPDR;
	return data;
}

uint8_t spiSendRecv(uint8_t data)
{
	while( s_spiSendWrite != 0);
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	data = SPDR;
	return data;
}


ISR(SPI_STC_vect)
{
	uart0SendSetRegister();
}
