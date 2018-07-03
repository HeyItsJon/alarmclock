/*******************************************************************************

FILE: spi1.c

%Header: %
xc.h
GEtypedefs.h
spi.h

DESCRIPTION:

This file contains the initialization function to enable the MSSP SPI module in
a PIC MCU and write and read SPI functions.  The functions should be MCU
independent.  The user must only provide the MSSP mode the MCU will be used in
(Master with Fosc/4, Master with Fosc/16, Master with Fosc/64, Slave with SS,
Slave without SS) and which SPI mode the MCU will be used in (Mode 0,0,
Mode 0,1, Mode 1,0, Mode 1,1) using the defintions provided in the header file
spi.h.  This file also contains SPI read and write functions.

This function does not perform certain functions:
    * This function does not set or clear any TRIS or PORT bits
    * The Buffer Overwrite Enable bit (BOEN) is kept at its default value of 0
    * The SPI Data Input Sample bit (SMP) is kept at its default value of 0
    * This function does not enable the SSP interrupt
    
It is the user's responsibility to:
    * Set or clear the appropriate TRIS and PORT bits for SCK, SDI, SDO, and SS
    * Set GIE, PEIE, and SSP1IE if the SSP interrupt is desired
    * Change BOEN and SMP, if desired
    
(For use with common register definitions provided in the Microchip xc8
compiler)
 
Copyright (c) 2002 – General Electric Corporation - All rights reserved.
%History: %
7/25/2012   Jon Altenburger     Initial version
10/5/2012   Jon Altenburger     Updated to just use one SPI port.  A future
                                update will be made if two SPI ports are needed
                                or to expand it beyond just 8-bit MCUs.
12/18/2012  Jon Altenburger	Changed "SSPCON1" to "SSPCON" for more general
				compatibility
12/26/2012  Jon Altenburger	Make WriteSPI and u8ReadSPI functions functional
*******************************************************************************/

#include <xc.h>
#include "GEtypedefs.h"
#include "HardwareProfile.h"
#include "spi.h"

/*******************************************************************************
FUNCTION NAME: SPIInit
DESCRIPTION:
This function initializes the MSSP SPI module in a PIC MCU.  The function
should be independent of the MCU that is used.  The user must input the MSSP
mode the MCU will be used in (Master, Slave with SS, Slave without SS) and which
SPI mode the MCU will be used in (Mode 0,0, Mode 0,1, Mode 1,0, Mode 1,1) using
the defintions provided in the header file spi.h.

If using SSPCON2 or a MCU with SSPCON1, simply #define the desired module as
"SSPCON."

PARAMETERS:
u8SSPMode      in         The desired MSSP mode
u8SPIMode      in         The desired SPI mode

RETURN VALUE:
none
RE-ENTRANT:	no

NOTES:
For use with common register definitions provided in Microchip's xc8 compiler
*******************************************************************************/
void SPIInit(U8 u8SSPMode, U8 u8SPIMode)
{
    // Set MSSP mode
    // OR SSPCON with the selected mode
    SSPCON |= u8SSPMode;

    // Set SPI mode
    switch (u8SPIMode)
    {
        // SPI Mode 0,0
        case MODE_00:
            CKP = 0;
            CKE = 1;
            break;
        // SPI Mode 0,1
        case MODE_01:
            CKP = 0;
            CKE = 0;
            break;
        // SPI Mode 1,0
        case MODE_10:
            CKP = 1;
            CKE = 1;
            break;
        // SPI Mode 1,1
        case MODE_11:
            CKP = 1;
            CKE = 0;
            break;
        // SPI Mode 0,0 by default
        default:
            CKP = 0;
            CKE = 1;
    }
    
    // Enable SPI
    SSPEN = 1;
}

/*******************************************************************************
FUNCTION NAME: WriteSPI
DESCRIPTION:
This function is used to write to the SSPBUF register to transmit messages via
SPI.  The function checks the WCOL bit to ensure a write collision does not
occur.

PARAMETERS:
u8DataOut      in         Data being transmitted via SPI

RETURN VALUE:
none
RE-ENTRANT:	no

NOTES:
For use with common register definitions provided in Microchip's xc8 compiler
*******************************************************************************/
void WriteSPI(U8 u8DataOut)
{
    SSPBUF = u8DataOut;
    
    __delay_us(SPI_DELAY);
}

/*******************************************************************************
FUNCTION NAME: u8ReadSPI
DESCRIPTION:
This function is used to read data on the SSPBUF register.  This function
checks the BF bit to ensure there is data to read.

PARAMETERS:
none

RETURN VALUE:
If there is valid data, the function returns the contents of SSPBUF

RE-ENTRANT:	no

NOTES:
For use with common register definitions provided in Microchip's xc8 compiler
*******************************************************************************/
U8 u8ReadSPI(void)
{
    U8 u8DataIn = 0;

    // Send dummy data
    WriteSPI(0xAA);
	
    u8DataIn = SSPBUF;
    
    return u8DataIn;
}