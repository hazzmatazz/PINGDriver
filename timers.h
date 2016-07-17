/* 
 * File:   timers.h
 * Author: Shane
 *
 * Created on July 10, 2016, 4:20 PM
 */

#ifndef TIMERS_H
#define	TIMERS_H

#ifdef	__cplusplus
extern "C" {
#endif

void intializeTimers(void);

void TMR1_StopTimer(void);    
void TMR1_WriteTimer(int);
void TMR1_StartTimer(void);

void resetTimer(void);
int timer1Value(void);

void (*TMR1_InterruptHandler)(void);

void timer1GateInterrupt(void);


#ifdef	__cplusplus
}
#endif

#endif	/* TIMERS_H */


