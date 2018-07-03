/*******************************************************************************

FILE: main.c

%Header: %
 HardwareProfile.h
 GEtypedefs.h
 DS1305.h
 SN7447.h
 spi.h
 xc.h

DESCRIPTION:

This file contains the main function used in the alarm clock project.

%History:  %
02/22/2013   Jon Altenburger     Initial version
 
*******************************************************************************/

#include "HardwareProfile.h"
#include "GEtypedefs.h"
#include "DS1305.h"
#include "SN7447.h"
#include "spi.h"
#include <xc.h>

// CONFIG BITS
__CONFIG(FOSC_INTRC_NOCLKOUT & WDTE_OFF & PWRTE_ON & MCLRE_OFF & CP_OFF & CPD_OFF & BOREN_OFF & IESO_OFF & FCMEN_OFF & LVP_OFF);
__CONFIG(BOR4V_BOR21V & WRT_OFF);

/*******************************************************************************
FUNCTION NAME: main(void)

DESCRIPTION:

 Main function of the alarm clock program.  Initializes the SPI port and the
 DS1305.  The function then enters an infinite loop and waits to sense button
 presses.  Holding down the TIME button and pressing the MINUTE or HOURS buttons
 will increment the time.  Holding down the ALARM button and doing the same will
 increment the alarm time.

PARAMETERS:
 none

RETURN VALUE:
 none

RE-ENTRANT: no
*******************************************************************************/
void main(void)
{
    // Create a holder for the time read from the DS1305
    time u8Time;
    // Placeholder to store dummy data to clear DS1305 interrupts
    U8 u8DummyData = 0;
        
    // Initialize the MCU
    InitializeSystem();
    // Initialize SPI
    SPIInit(MASTER_FOSC_4, MODE_01);
    // Initialize the DS1305
    InitializeDS1305();
    
    // Infinite loop
    while (1)
    {
        // TIME BUTTON PUSHED
        if (TIME_BUTTON == PUSHED)
        {
            // Disable interrupts
            GIE = CLEAR;

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

            // Poll the HOUR and MINUTE buttons while the TIME button is pushed
            while (TIME_BUTTON == PUSHED)
            {
                if (MINUTE_BUTTON == PUSHED)
                {
                    u8Time = u8IncrementMinute(u8Time);
                    DisplayTime(u8Time);
                    // Delay
                    __delay_ms(DEBOUNCE);
                }
                else if (HOUR_BUTTON == PUSHED)
                {
                    u8Time = u8IncrementHour(u8Time);
                    DisplayTime(u8Time);
                    // Delay
                    __delay_ms(DEBOUNCE);
                }
            }

            // Time button has been release
            // Set the new time in the DS1305
            SetTime(u8Time);

            // Clear the DS1305 Interrupt flag by reading Alarm0 Day register
            // Read a register to avoid changing something accidently
            DS1305_CS = 1;
            WriteSPI(READ_ALARM0_DAY);
            u8DummyData = u8ReadSPI();
            DS1305_CS = 0;
            __delay_ms(DS1305_DELAY);

            // Clear the INTF flag
            INTF = CLEAR;
            // Enable interrupts
            GIE = SET;
        }
        // ALARM BUTTON PUSHED
        else if (ALARM_BUTTON == PUSHED)
        {
            // Disable interrupts
            GIE = CLEAR;

            // Read Alarm1 from the DS1305
            DS1305_CS = 1;
            WriteSPI(READ_ALARM1_HOURS);
            u8Time.u8Hours = u8ReadSPI();
            DS1305_CS = 0;
            __delay_ms(DS1305_DELAY);

            DS1305_CS = 1;
            WriteSPI(READ_ALARM1_MINUTES);
            u8Time.u8Minutes = u8ReadSPI();
            DS1305_CS = 0;
            __delay_ms(DS1305_DELAY);

            // Display the alarm time
            DisplayTime(u8Time);

            // Poll the HOUR and MINUTE buttons while the ALARM button is pushed
            while (ALARM_BUTTON == PUSHED)
            {
                if (MINUTE_BUTTON == PUSHED)
                {
                    u8Time = u8IncrementMinute(u8Time);
                    DisplayTime(u8Time);
                    // Delay
                    __delay_ms(DEBOUNCE);
                }
                else if (HOUR_BUTTON == PUSHED)
                {
                    u8Time = u8IncrementHour(u8Time);
                    DisplayTime(u8Time);
                    // Delay
                    __delay_ms(DEBOUNCE);
                }
            }

            // Alarm button has been release
            // Set the new alarm time in the DS1305
            SetAlarm1(u8Time);

            // Read the current time from the DS1305
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
            
            // Display the time
            DisplayTime(u8Time);

            // Clear the DS1305 Interrupt flag by reading Alarm0 Day register
            // Read a register to avoid changing something accidently
            DS1305_CS = 1;
            WriteSPI(READ_ALARM0_DAY);
            u8DummyData = u8ReadSPI();
            DS1305_CS = 0;
            __delay_ms(DS1305_DELAY);

            // Clear the INTF flag
            INTF = CLEAR;
            // Enable interrupts
            GIE = SET;
        }
    }
}