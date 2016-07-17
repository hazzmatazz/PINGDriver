/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 3.15.0
        Device            :  PIC16F18313
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.20
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

//#include "mcc_generated_files/mcc.h"
#include "System.h"
#include "interrupts.h"
#include "PINGDriver.h"
#include "timers.h"
#include "spi.h"

// Configuration bits
#pragma config CONFIG1 = 0x904
#pragma config CONFIG2 = 0x32E1
#pragma config CONFIG3 = 0x2003
#pragma config CONFIG4 = 0x0003

void initialize(void)
{
    // See spreadsheet for all initializations and config bits
    // "register_settings.xlsx"
    OSCFRQ = 0x6;
    OSCCON1 = 0x0;
    OSCCON2 = 0x0;
    OSCCON3 = 0x0;
    OSCEN = 0x64;
    INTCON = 0x0;   // Disable all interrupts
    
    // Set up the pin directions/types
    TRISA = 0x1F;
    ANSELA = 0x00;
    WPUA = 0x00;
    ODCONA = 0x00;
    SLRCONA = 0x00;
    INLVLA = 0x00;
    
    // Set up the peripherals
    globalInterruptDisable();
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCK = 0x00;   // Unlock PPS
    
    SSP1CLKPPS = 0x1;   // CLK on RA1
    SSP1DATPPS = 0x2;   // MOSI on RA2
    SSP1SSPPS = 0x0;    // SS on RA0
    RA5PPS = 0x19;      // MISO on RA5
    T1GPPS = 0x4;       // Timer1 Gate on RA4
    
    // Lock the PPS
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCK = 0x1;
    
    globalInterruptEnable();
    intializeTimers();
    initializeInterrupts();    
    initializeSpi();
    

}

void takeReading(void)
{
    // Prevent interrupts
    globalInterruptDisable();
    // Drive the Timer Pin high, then low, then tri-state   
    RA4 = 0;    // Clear RA4
    TRISA4 = 0;  // Enable RA4 to be an output
    RA4 = 1;    // Set RA4
    // Instruction clock is 4 MHz. Need to keep this true for 5us
    // Loop below to put a delay in
    for (int i=0; i<1; i++)
    {
        // Just wait
    }
    RA4 = 0;                            // Clear RA4 ()
    TRISA4 = 1;                         // Return to an input state
    resetTimer();                       // Clear the timer, enable interrupts, and start it.
    PINGDriverStatus.takingReading = 1; // Say that we're taking a reading.
    
}
/*
                         Main application
 */
void main(void)
{
    // initialize the device
    initialize();
  
    resetTimer();
    int val = 0;
    // Clear the buffer valid (forces a reading to be taken at the beginning of the loop)
    PINGDriverStatus.bufferEmpty = 1;
    PINGDriverStatus.takingReading = 0;
    
    summedTimerCount = 0x00000000;
    int loopCount = MAXREADINGCOUNT;
    
    minTimerCount = 0xFFFF;
    maxTimerCount = 0x0000;
    
    while(1)
    {
        if (PINGDriverStatus.bufferEmpty == 0)
        {
            continue; // Just wait            
        }
        
        if (PINGDriverStatus.takingReading)
        {
            // Just wait
            continue;
        }
        
        // We aren't taking a reading and the buffer is empty        
        // If the loop count is terminal, then process the data and send it out. Otherwise, take a reading        
        if (loopCount > 0)
        {
            takeReading();
            loopCount--;    // Decrement the loop count
        }
        else
        {
            // Process the data
            // This allows me to take the average pretty easily.
            summedTimerCount = summedTimerCount >> READINGDIVIDER;
            int result = storeWordForTransfer(summedTimerCount&0xFFFF);
            result = storeWordForTransfer(minTimerCount);
            result = storeWordForTransfer(maxTimerCount);
            // Result is just for debugging for now.
            
            // Reset things
            summedTimerCount = 0x00000000;
            loopCount = MAXREADINGCOUNT;
            minTimerCount = 0xFFFF;
            maxTimerCount = 0x0000;
        }
    }
    TMR1_StopTimer();
}


/**
 End of File
*/