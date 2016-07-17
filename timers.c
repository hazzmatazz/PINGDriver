#include <pic16f18313.h>

#include "System.h"
#include "PINGDriver.h"
#include "timers.h"
#include "interrupts.h"


void intializeTimers(void)
{
    // Configure the timer (see spreadsheet))
    T1CON = 0x0C;   
    
    // Configure the gate (polarity, etc.)
    T1GCON = 0xC0;
    
    
    TMR1ON = 1;    
}

void TMR1_StopTimer()
{
    TMR1ON = 0;
}

void TMR1_WriteTimer(int value)
{
    int state = TMR1ON;
    TMR1_StopTimer();
    TMR1H = value>>8;
    TMR1L = value&0xFF;
    TMR1ON = state;
}

void TMR1_StartTimer(void)
{
    TMR1ON = 1;
}

void resetTimer(void)
{
    TMR1_WriteTimer(0);         // Clear the timer
    globalInterruptEnable();    // Enable interrupts
    TMR1_StartTimer();      // Start the timer
}

int timer1Value(void)
{
    int value = (TMR1H<<8) | TMR1L;
    return value;
}

void timer1GateInterrupt(void)
{    
    globalInterruptDisable();                   // Disable interrupts
    unsigned int timerCount = timer1Value();    // Grab the timer value    
    summedTimerCount += timerCount;             // Increment the cumulative timer time.
    // Grab the min & max for statistics, in case I want to use them later.
    // Hell, I may just store up all of the raw data points for debug purposes...
    if (timerCount < minTimerCount)
    {
        minTimerCount = timerCount;
    }
    if (timerCount > maxTimerCount)
    {
        maxTimerCount = timerCount;
    }
    PINGDriverStatus.takingReading = 0;         // Let the rest of the system know that we are no longer taking a reading.    
    // The timer is restarted as part of the main loop.
}
