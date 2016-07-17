/* 
 * File:   spi.h
 * Author: Shane
 *
 * Created on July 13, 2016, 8:35 PM
 */

#ifndef SPI_H
#define	SPI_H

#ifdef	__cplusplus
extern "C" {
#endif

    void initializeSpi(void);
    void spiInterrupt(void);
    void storeByteForTransfer(unsigned short);
    int storeWordForTransfer(unsigned int);
    
#define MAXBUFFERCOUNT 6
    short bufferCount;
    unsigned short dataBuffer[MAXBUFFERCOUNT];


#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */

