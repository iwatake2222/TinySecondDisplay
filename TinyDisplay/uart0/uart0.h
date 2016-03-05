/*
 * uart0.h
 *
 * Created: 2016-03-03 12:08:27 AM
 *  Author: take-iwiw
 */ 


#ifndef UART0_H_
#define UART0_H_


void uart0Init();
void uart0Send( uint8_t data );
uint8_t isUart0Recved();
uint8_t uart0Recv();


#endif /* UART0_H_ */