/*
 * myStdio.h
 *
 * Created: 2016-03-02 9:47:59 PM
 *  Author: take-iwiw
 */ 


#ifndef MYSTDIO_H_
#define MYSTDIO_H_

void stdioInit();
char putchar(char c);
char getchar();
uint8_t getcharTry(char *c);
void print(const char *str);

void printDec(const uint8_t dec);
void printHex(const uint8_t hex);
void printDecPos(const uint8_t dec, const uint8_t x, const uint8_t y);


#endif /* MYSTDIO_H_ */