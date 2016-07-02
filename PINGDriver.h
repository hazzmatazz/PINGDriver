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

    
uint16_t timerCount;

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

