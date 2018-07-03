/*******************************************************************************

FILE: spi.h

%Header: %
GEtypedefs.h

DESCRIPTION:

This header file provides the function prototype and defintions for the file
spi.c.  These two files intialize the SPI module in any 8-bit mid-range PIC MCU.
 
Copyright (c) 2002 – General Electric Corporation - All rights reserved.
%History: %
7/25/2012   Jon Altenburger     Initial version
10/5/2012   Jon Altenburger     Updated to just use one SPI port.  A future
                                update will be made if two SPI ports are needed
                                or to expand it beyond just 8-bit MCUs.
*******************************************************************************/

#ifndef SPI_H
#define SPI_H

#ifndef GEtypedefs_H
#include "GEtypedefs.h"
#endif

// Function prototype
void SPIInit(U8, U8);
void WriteSPI(U8);
U8 u8ReadSPI(void);

// Mode defintions
// MSSP Mode
#define MASTER_FOSC_4   0x00
#define MASTER_FOSC_16  0x01
#define MASTER_FOSC_64  0x02
#define MASTER_TMR2_2   0x03
#define SLAVE_SS_ON     0x04
#define SLAVE_SS_OFF    0x05
// SPI Mode
#define MODE_00         0
#define MODE_01         1
#define MODE_10         2
#define MODE_11         3

#endif