/*
 * myCommon.h
 *
 * Created: 2016-03-02 7:37:55 PM
 *  Author: take-iwiw
 */ 


#ifndef MYCOMMON_H_
#define MYCOMMON_H_

#define F_CPU 16000000

#define SET_BIT(PORT, BIT) (PORT |=  (1<<BIT))
#define CLR_BIT(PORT, BIT) (PORT &= ~(1<<BIT))
#define SET_VAL(PORT, START_BIT, SIZE, VAL) (PORT = (PORT & ~(((1<<SIZE)-1) << START_BIT)) | (VAL << START_BIT))
#define IS_SET(PORT, BIT) ( (PORT&(1<<BIT)) == (1<<BIT) )


#endif /* MYCOMMON_H_ */