/*
 * uart0Config.h
 *
 * Created: 2016-03-03 5:47:21 PM
 *  Author: take-iwiw
 */ 


#ifndef UART0CONFIG_H_
#define UART0CONFIG_H_

#define UART_DOUBLE
//#define UART0_BAUD ((uint32_t)9600)

// for tinyDisplay
#define UART0_BAUD ((uint32_t)2000000)




// SOFTWARE_BUFFER_SIZE must be 2^x (i.e. 8, 16, 32,64, 128, 256)
#define SOFTWARE_BUFFER_SIZE  (256)


#endif /* UART0CONFIG_H_ */