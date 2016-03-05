/*
 * uart0.c
 *
 * Created: 2016-03-03 12:08:37 AM
 *  Author: take-iwiw
 *    Note: Asynchronous Normal mode fixed
 *          8bit, 2-bit stop bit, no parity
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../myCommon.h"

#include "uart0Config.h"
#include "uart0.h"

#ifndef UART_DOUBLE
#define UBRR0_CALC (F_CPU/16/UART0_BAUD - 1)
#else
#define UBRR0_CALC (F_CPU/8/UART0_BAUD - 1)
#endif

static volatile uint8_t s_usartRecvBuffer[SOFTWARE_BUFFER_SIZE];
static volatile uint8_t s_usartRecvWrite = 0;
static volatile uint8_t s_usartRecvRead = 0;
static volatile uint8_t s_usartSendBuffer[SOFTWARE_BUFFER_SIZE];
static volatile uint8_t s_usartSendWrite = 0;
static volatile uint8_t s_usartSendRead = 0;

static void uart0SendSetRegister();

void uart0Init()
{
	/* Set Baud Rate */
	UBRR0H = (uint8_t)(UBRR0_CALC>>8);
	UBRR0L = (uint8_t)UBRR0_CALC;
	
	// enable double speed
#ifdef UART_DOUBLE
	UCSR0A |= (1<<U2X0);
#endif
	/* Enable Tx, RX, Tx INT, Rx INT */
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0) | (1<<TXCIE0);

	/* Asynchronous, 2 stop bits */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void uart0Send( uint8_t data )
{
	while(((s_usartSendWrite + 1) & (SOFTWARE_BUFFER_SIZE-1)) == s_usartSendRead);
	s_usartSendBuffer[s_usartSendWrite++] = data;
	s_usartSendWrite &= (SOFTWARE_BUFFER_SIZE-1);
	if ( IS_SET(UCSR0A, UDRE0) ){
		uart0SendSetRegister();
	}
}

uint8_t isUart0Recved()
{
	return (s_usartRecvWrite != s_usartRecvRead);
}

uint8_t uart0Recv()
{
	while(s_usartRecvWrite == s_usartRecvRead);
	uint8_t data = s_usartRecvBuffer[s_usartRecvRead++];
	s_usartRecvRead &= (SOFTWARE_BUFFER_SIZE-1);
	return data;
}


static void uart0SendSetRegister()
{
	if (s_usartSendWrite != s_usartSendRead){
		UDR0 = s_usartSendBuffer[s_usartSendRead++];
		s_usartSendRead &= (SOFTWARE_BUFFER_SIZE-1);
	}
}

ISR(USART_TX_vect)
{
	uart0SendSetRegister();
}


ISR(USART_RX_vect)
{
	/* do not check buffer over flow */
	s_usartRecvBuffer[s_usartRecvWrite++] = UDR0;
	s_usartRecvWrite &= (SOFTWARE_BUFFER_SIZE-1);
}


ISR(USART_UDRE_vect)
{

}



