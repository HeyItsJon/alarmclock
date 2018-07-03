/*******************************************************************************

FILE: DS1305.c

%Header: %
 GEtypedefs.h
 DS1305.h
 HardwareProfile.h
 spi.h
 SN7447.h
 xc.h

DESCRIPTION:
 This file contains the functions used in conjunction with the DS1305 RTC.
 
 ***** NOTE *****
 The DS1305 supports SPI modes 1 and 3.

%History:  %
12/15/2012  Jon Altenburger     Initial version
02/25/2014  Jon Altenburger     Fixed issue preventing Alarm1 from triggering
                                Masked Alarm1 DAY register
                                Set Alarm1 SECONDS to zero every Alarm1 update
 
*******************************************************************************/

#include "GEtypedefs.h"
#include "DS1305.h"
#include "HardwareProfile.h"
#include "spi.h"
#include "SN7447.h"
#include <xc.h>

/*******************************************************************************
FUNCTION NAME: InitializeDS1305(void)

DESCRIPTION:
 Initializes the DS1305 real-time clock.  The function:
    - Sets the Control Register to 0x07
        - Starts the oscillator
        - Turns off write protect
        - Enables interrupts on the INT0 and INT1 pins
    - Sets the time to 12:00AM
    - Sets the alarm to 12:00PM
    - Sets Alarm 0 to trigger every minute

PARAMETERS:
 none

RETURN VALUE:
 none

RE-ENTRANT: no
*******************************************************************************/
void InitializeDS1305(void)
{
    // Create "time" variables to set the time and alarm
    time u8TempTime;
    time u8TempAlarm;
	
    // 12:00AM
    u8TempTime.u8Hours = TWELVE_AM;
    u8TempTime.u8Minutes = _ZERO;
    // 12:00PM
    u8TempAlarm.u8Hours = TWELVE_PM;
    u8TempAlarm.u8Minutes = _ZERO;
	
    // Set Control Register
    //  Control<7> = 0 - Activates oscillator
    //  Control<6> = 0 - Disable write protect
    //  Control<5-3> - Don't care
    //  Control<2> = 1 - Map Alarm 0 interrupt to INT0 pin and Alarm 1 interrupt
    //                   to INT1 pin
    //  Control<1> = 1 - Enable Alarm 0 interrupt
    //  Control<0> = 1 - Enable Alarm 1 interrupt
    // Clear WP bit
    DS1305_CS = 1;
    WriteSPI(WRITE_CONTROL);
    WriteSPI(0x00);
    DS1305_CS = 0;
    __delay_ms(DS1305_DELAY);

    // Set the Control register to desired state
    DS1305_CS = 1;
    WriteSPI(WRITE_CONTROL);
    WriteSPI(0x07);
    DS1305_CS = 0;
    __delay_ms(DS1305_DELAY);
    
    // Set time to 12:00AM
    SetTime(u8TempTime);
    
    // Mask Alarm1 DAY register
    DS1305_CS = 1;
    WriteSPI(WRITE_ALARM1_DAY);
    WriteSPI(MASK);
    DS1305_CS = 0;
    __delay_ms(DS1305_DELAY);

    // Set Alarm 0 to 12:00PM
    SetAlarm1(u8TempAlarm);
    
    // Set Alarm 0 to trigger every minute
    DS1305_CS = 1;
    WriteSPI(WRITE_ALARM0_SECONDS);
    WriteSPI(0x00);
    DS1305_CS = 0;
    __delay_ms(DS1305_DELAY);
    
    DS1305_CS = 1;
    WriteSPI(WRITE_ALARM0_MINUTES);
    WriteSPI(MASK);
    DS1305_CS = 0;
    __delay_ms(DS1305_DELAY);
    
    DS1305_CS = 1;
    WriteSPI(WRITE_ALARM0_HOURS);
    WriteSPI(MASK);
    DS1305_CS = 0;
    __delay_ms(DS1305_DELAY);
    
    DS1305_CS = 1;
    WriteSPI(WRITE_ALARM0_DAY);
    WriteSPI(MASK);
    DS1305_CS = 0;
    __delay_ms(DS1305_DELAY);
}

/*******************************************************************************
FUNCTION NAME: SetTime(time u8Time)

DESCRIPTION:
 Sets the time in the DS1305.  Assumes 12-hour mode.

PARAMETERS:
 u8Time		The time the time of day is set to.  Includes AM/PM information.

RETURN VALUE:
 none

RE-ENTRANT: no
*******************************************************************************/
void SetTime(time u8Time)
{
    // Write the passed values directly to the hours and minutes registers
	
    // Hours
    DS1305_CS = 1;
    WriteSPI(WRITE_TIME_HOURS);
    WriteSPI(u8Time.u8Hours);
    DS1305_CS = 0;
    __delay_ms(DS1305_DELAY);
	
    // Minutes
    DS1305_CS = 1;
    WriteSPI(WRITE_TIME_MINUTES);
    WriteSPI(u8Time.u8Minutes);
    DS1305_CS = 0;
    __delay_ms(DS1305_DELAY);

    // Seconds
    DS1305_CS = 1;
    WriteSPI(WRITE_TIME_SECONDS);
    WriteSPI(0x00);
    DS1305_CS = 0;
    __delay_ms(DS1305_DELAY);
    
    // Set the display
    DisplayTime(u8Time);
}

/*******************************************************************************
FUNCTION NAME: SetAlarm1(u8Time)

DESCRIPTION:
 Sets Alarm 1 of the DS1305.

PARAMETERS:
 u8Time		The time Alarm 1 is set to.  Includes AM/PM information.

RETURN VALUE:
 none

RE-ENTRANT: no
*******************************************************************************/
void SetAlarm1(time u8Time)
{
    // Write the passed values directly to the alarm registers
	
    // Hours
    DS1305_CS = 1;
    WriteSPI(WRITE_ALARM1_HOURS);
    WriteSPI(u8Time.u8Hours);
    DS1305_CS = 0;
    __delay_ms(DS1305_DELAY);
	
    //Minutes
    DS1305_CS = 1;
    WriteSPI(WRITE_ALARM1_MINUTES);
    WriteSPI(u8Time.u8Minutes);
    DS1305_CS = 0;
    __delay_ms(DS1305_DELAY);

    // Seconds
    DS1305_CS = 1;
    WriteSPI(WRITE_ALARM1_SECONDS);
    WriteSPI(0x00);
    DS1305_CS = 0;
    __delay_ms(DS1305_DELAY);
}