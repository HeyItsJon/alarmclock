/*******************************************************************************

FILE: HardwareProfile.c

%Header: %
 GEtypedefs.h
 HardwareProfile.h
 DS1305.h
 spi.h
 SN7447.h
 xc.h

DESCRIPTION:
This file contains the general use functions used in the alarm clock project.

%History:  %
02/24/2013   Jon Altenburger     Initial version
 
*******************************************************************************/

#include "GEtypedefs.h"
#include "HardwareProfile.h"
#include "DS1305.h"
#include "spi.h"
#include "SN7447.h"
#include <xc.h>

/*******************************************************************************
FUNCTION NAME: u8IncrementMinute(u8Time)

DESCRIPTION:
 Increments the pasted time by one minute and returns that value.

PARAMETERS:
 u8Time		The time to increment

RETURN VALUE:
 The incremented time in the form of a time struct

RE-ENTRANT: no
*******************************************************************************/
time u8IncrementMinute(time u8Time)
{
    // If xx:59, fo to yy:00
    if (u8Time.u8Minutes == FIFTY_NINE)
    {
        // Roll over to the next hour
        u8Time.u8Minutes = _ZERO;
        u8Time = u8IncrementHour(u8Time);
    }
    // If xx:09, go to xx:10
    else if (u8Time.u8Minutes == NINE)
    {
        u8Time.u8Minutes = TEN;
    }
    // If xx:19, go to xx:20
    else if (u8Time.u8Minutes == NINETEEN)
    {
        u8Time.u8Minutes = TWENTY;
    }
    // If xx:29, go to xx:30
    else if (u8Time.u8Minutes == TWENTY_NINE)
    {
        u8Time.u8Minutes = THIRTY;
    }
    // If xx:39, go to xx:40
    else if (u8Time.u8Minutes == THIRTY_NINE)
    {
        u8Time.u8Minutes = FORTY;
    }
    // If xx:49, go to xx:50
    else if (u8Time.u8Minutes == FORTY_NINE)
    {
        u8Time.u8Minutes = FIFTY;
    }
    else
    {
        u8Time.u8Minutes++;
    }

    return u8Time;
}

/*******************************************************************************
FUNCTION NAME: u8IncrementHour(u8Time)

DESCRIPTION:
 Increments the pasted time by one hour and returns that value.

PARAMETERS:
 u8Time		The time to increment

RETURN VALUE:
 The incremented time in the form of a time struct

RE-ENTRANT: no
*******************************************************************************/
time u8IncrementHour(time u8Time)
{
    // If it's 11:00AM, go to 12:00PM
    if (u8Time.u8Hours == ELEVEN_AM)
    {
        u8Time.u8Hours = TWELVE_PM;
    }
    // If it's 11:00PM, go to 12:00AM
    else if (u8Time.u8Hours == ELEVEN_PM)
    {
        u8Time.u8Hours = TWELVE_AM;
    }
    // If it's 9:00AM, go to 10:00AM
    else if (u8Time.u8Hours == NINE_AM)
    {
        u8Time.u8Hours = TEN_AM;
    }
    // If it's 9:00PM, go to 10:00PM
    else if (u8Time.u8Hours == NINE_PM)
    {
        u8Time.u8Hours = TEN_PM;
    }
    // If it's 12:00AM, go to 1:00AM
    else if (u8Time.u8Hours == TWELVE_AM)
    {
        u8Time.u8Hours = ONE_AM;
    }
    // If it's 12:00PM, go to 1:00PM
    else if (u8Time.u8Hours == TWELVE_PM)
    {
        u8Time.u8Hours = ONE_PM;
    }
    // Otherwise, just increment the hours
    else
    {
        u8Time.u8Hours++;
    }

    return u8Time;
}

/*******************************************************************************
FUNCTION NAME: InitializeSystem(void)

DESCRIPTION:
 Initializes the MCU

PARAMETERS:
 none
 
RETURN VALUE:
 none

RE-ENTRANT: no
*******************************************************************************/
void InitializeSystem(void)
{
    // OSCCON register
    // 4MHz internal oscillator
    IRCF0 = CLEAR;
    IRCF1 = SET;
    IRCF2 = SET;

    // OPTION register
    INTEDG = CLEAR; // Interrupt on falling edge on pin RB0

    // ANSEL and ANSELH registers
    // All I/O pins are digital I/O
    ANSEL = 0;
    ANSELH = 0;

    // TRIS and PORT register
    // Set I/O function and intialize output ports
    // LED display
    // Must do these first!!
    SN7447_HOURS_TRIS = OUTPUT;
    SN7447_HOURS = CLEAR;

    SN7447_MINUTES_TRIS = OUTPUT;
    SN7447_MINUTES = CLEAR;

    PM_LED_TRIS = OUTPUT;
    PM_LED = CLEAR;

    // SPI
    SCK_TRIS = OUTPUT;
    SDI_TRIS = INPUT;
    SDO_TRIS = OUTPUT;

    // DS1305 interface
    DS1305_INT1_TRIS = INPUT;

    DS1305_CS_TRIS = OUTPUT;
    DS1305_CS = LOW;

    // Input buttons
    TIME_BUTTON_TRIS = INPUT;
    ALARM_BUTTON_TRIS = INPUT;
    HOUR_BUTTON_TRIS = INPUT;
    MINUTE_BUTTON_TRIS = INPUT;

    // INTCON register
    GIE = SET; // Enable global interrupts
    INTF = CLEAR;  // Clear interrupt flag before enabling
    INTE = SET; // Enable external interrupt on RB0
}

/*******************************************************************************
FUNCTION NAME: time_int(void)

DESCRIPTION:
 Interrupt service routine.  Triggers on RB0 external interrupts.

PARAMETERS:
 none

RETURN VALUE:
 none

RE-ENTRANT: no
*******************************************************************************/
void interrupt time_int(void)
{
    // External interrupt from DS1305 triggered
    if (INTF == SET)
    {
        time u8Time;
        U8 u8TempData = 0;

        // Clear the DS1305 Interrupt flag by reading Alarm0 Day register
        // Read a register to avoid changing something accidently
        DS1305_CS = 1;
        WriteSPI(READ_ALARM0_DAY);
        u8TempData = u8ReadSPI();
        DS1305_CS = 0;
        __delay_ms(DS1305_DELAY);

        // Delay one more millisecond before clearing the Alarm1 flag
        __delay_ms(1);

        // Read Alarm1 register in case there was an alarm
        DS1305_CS = 1;
        WriteSPI(READ_ALARM1_DAY);
        u8TempData = u8ReadSPI();
        DS1305_CS = 0;
        __delay_ms(DS1305_DELAY);
	
        // Read the time from the DS1305
        DS1305_CS = 1;
        WriteSPI(READ_TIME_HOURS);
        u8Time.u8Hours = u8ReadSPI();
        DS1305_CS = 0;
        __delay_ms(DS1305_DELAY);
        
        DS1305_CS = 1;
        WriteSPI(READ_TIME_MINUTES);
        u8Time.u8Minutes = u8ReadSPI();
        DS1305_CS = 0;
        __delay_ms(DS1305_DELAY);

        // Display the new time
        DisplayTime(u8Time);

        // Clear the interrupt flag
        INTF = CLEAR;
    }
}