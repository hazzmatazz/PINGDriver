#include "System.h"
#include "interrupts.h"
#include "timers.h"  // Needed for the interrupt service routine.
#include "spi.h"

void initializeInterrupts(void)
{
    globalInterruptDisable();
    peripheralInterruptDisable();
    clearAllFlags();
    
    // Enable the Timer1 gate interrupt and the overflow interrupt
    TMR1GIE = 1;
    TMR1IE = 1;
    
    // Enable the MSSP interrupt
    SSP1IE = 1;
        
    globalInterruptEnable();
    peripheralInterruptEnable();
}

// Clears all of the relevant flags
void clearAllFlags(void)
{
    TMR1GIF = 0;
    SSP1IF = 0;
    TMR1IF = 0;
}

void globalInterruptDisable(void)
{
    TMR1GIE = 0;
    GIE = 0;    
}

void globalInterruptEnable(void)
{
    clearAllFlags();
    TMR1GIE = 1;
    GIE = 1;
}

void peripheralInterruptDisable(void)
{
    PEIE = 0;
}

void peripheralInterruptEnable(void)
{
    // Enable the interrupts
    PEIE = 1;
    IOCIE = 1;
}

void interrupt interruptManager(void)
{
    if (TMR1GIE == 1 && TMR1GIF == 1)
    {
        // Timer 1 gate interrupt enabled and the flag is set
        timer1GateInterrupt();
    }
    
    if (SSP1IE == 1 && SSP1IF == 1)
    {
        spiInterrupt();
    }
}