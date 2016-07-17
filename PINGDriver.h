/* 
 * File:   PINGDriver.h
 * Author: Shane
 *
 * Created on July 1, 2016, 6:21 AM
 */

#ifndef PINGDRIVER_H
#define	PINGDRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif

    
unsigned long summedTimerCount;
unsigned int minTimerCount;
unsigned int maxTimerCount;

struct {
    unsigned int bufferEmpty : 1;
    unsigned int takingReading : 1;
} PINGDriverStatus;

// READINGDIVIDER should be 2^count
// Makes it easy to sum up then divide down
#define READINGDIVIDER 1
#define MAXREADINGCOUNT 1<<READINGDIVIDER

typedef enum 
{
    TimerReady, TimerCounting, TimerDone, TimerError
} TimerStatus;

TimerStatus timerValueStatus;

// Interrupt to the Raspberry Pi is low-true and on RA0
// Assert is an AND operation and Deassert is an OR operation
#define DEASSERT_INTERRUPT 0x01
#define ASSERT_INTERRUPT 0xFE

#ifdef	__cplusplus
}
#endif

#endif	/* PINGDRIVER_H */

