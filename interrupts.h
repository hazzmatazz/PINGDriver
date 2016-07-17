/* 
 * File:   interrupts.h
 * Author: Shane
 *
 * Created on July 10, 2016, 10:31 AM
 */

#ifndef INTERRUPTS_H
#define	INTERRUPTS_H

#ifdef	__cplusplus
extern "C" {
#endif

void initializeInterrupts(void);
void clearAllFlags(void);
void globalInterruptDisable(void);
void globalInterruptEnable(void);
void peripheralInterruptDisable(void);
void peripheralInterruptEnable(void);

void interrupt interruptManager(void);


#ifdef	__cplusplus
}
#endif

#endif	/* INTERRUPTS_H */

