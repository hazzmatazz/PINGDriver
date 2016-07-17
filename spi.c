// spi.c
// Shane Hazzard
// July 2016
#include "spi.h"
#include "System.h"
#include "PINGDriver.h"

void initializeSpi(void)
{
    // See register spreadsheet
    SSP1CON1 = 0x0;
    SSP1STAT = 0x0;
    SSP1CON1bits.SSPM = 0x4;
    SSP1CON3 = 0x0;
    SSP1CON1bits.SSPEN = 0x1;    
    // Assumes pin directions are set up.
    
    bufferCount = 0x0;
    for (int i=0; i<MAXBUFFERCOUNT; i++)
    {
        dataBuffer[i] = 0x0;
    }
}

void spiInterrupt(void)
{
    // We saw something!
    int command = SSP1BUF;  // Ignore it for now
    bufferCount--;
    if (bufferCount == 0)
    {
        // We transmitted out the last data point
        PINGDriverStatus.bufferEmpty = 1;
    }
    else
    {
        SSP1BUF = dataBuffer[bufferCount-1];
    }
}

void storeByteForTransfer(unsigned short data)
{
    dataBuffer[bufferCount] = data;
    bufferCount++;
    if (bufferCount == MAXBUFFERCOUNT)
    {
        // Get ready to write out some data!
        SSP1BUF = dataBuffer[bufferCount-1];
    }
}

int storeWordForTransfer(unsigned int data)
{
    // This should only ever be called if the buffer is empty
    // Returns 0 if the storage is OK and -1 if not.
    if (bufferCount == MAXBUFFERCOUNT)
    {
        return -1;
    }
    short buf = data & 0xFF;
    storeByteForTransfer(buf);
    buf = (data >> 8) & 0xFF;
    storeByteForTransfer(buf);
    PINGDriverStatus.bufferEmpty = 0;
    return 0;
    
}
