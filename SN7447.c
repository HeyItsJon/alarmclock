/*******************************************************************************

FILE: SN7447.c

%Header: %
 SN7447.h
 GEtypedefs.h
 DS1305.h
 HardwareProfile.h
 xc.h

DESCRIPTION:

This file contains the functions used with the SN7447 7-segment LED driver.

%History:  %
02/06/2013   Jon Altenburger     Initial version
 
*******************************************************************************/

#include "SN7447.h"
#include "GEtypedefs.h"
#include "DS1305.h"
#include "HardwareProfile.h"
#include <xc.h>

/*******************************************************************************
FUNCTION NAME: DisplayTime(u8Time)

DESCRIPTION:
 Displays the time passed to the function on the 7-segment LEDs.

PARAMETERS:
 u8Time		The time to display.  Includes AM/PM information.

RETURN VALUE:
 none

RE-ENTRANT: no
*******************************************************************************/
void DisplayTime(time u8Time)
{
    U8 u8Temp = 0;

    // Display the hours
    // Display the ones digit of the hours first
    // Shift the hours over two bits to align with the PORTB output pins
    u8Temp = u8Time.u8Hours << 2;
    // Set PORTB equal to the result
    SN7447_HOURS = u8Temp;

    // Display the minutes
    // Set PORTA to the minutes
    SN7447_MINUTES = u8Time.u8Minutes;
}