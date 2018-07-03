/*******************************************************************************

FILE: HardwareProfile.h

%Header: %
 GEtypedefs.h

DESCRIPTION:

This file contains the "time" struct, function prototypes, and MCU pin
definitions for the alarm clock project.

%History:  %
02/22/2013   Jon Altenburger     Initial version
 
*******************************************************************************/

#ifndef HARDWAREPROFILE_H
    #define HARDWAREPROFILE_H

    #include "GEtypedefs.h"

    // "time" struct that holds minutes and hours
    typedef struct
    {
        U8 u8Hours;
        U8 u8Minutes;
    } time;

    // Function prototypes
    void InitializeSystem(void);
    time u8IncrementMinute(time);
    time u8IncrementHour(time);
    void interrupt time_int(void);

    // Pin defitions
    // LED pin
    #define PM_LED_TRIS             TRISB7
    #define PM_LED                  RB7
    // SPI pins
    #define SCK_TRIS                TRISC3
    #define SDI_TRIS                TRISC4
    #define SDO_TRIS                TRISC5
    // DS1305 pins
    #define DS1305_INT1_TRIS        TRISB0
    #define DS1305_INT1             RB0
    #define DS1305_CS_TRIS          TRISC6
    #define DS1305_CS               RC6
    // SN7447 pins
    #define SN7447_HOURS_TRIS       TRISB
    #define SN7447_HOURS            PORTB
    #define SN7447_MINUTES_TRIS     TRISA
    #define SN7447_MINUTES          PORTA

    // Buttons
    #define TIME_BUTTON_TRIS        TRISC1
    #define TIME_BUTTON             RC1
    #define ALARM_BUTTON_TRIS       TRISC2
    #define ALARM_BUTTON            RC2
    #define HOUR_BUTTON_TRIS        TRISB1
    #define HOUR_BUTTON             RB1
    #define MINUTE_BUTTON_TRIS      TRISC7
    #define MINUTE_BUTTON           RC7

    // Delay function taken from pic.h
//    #pragma intrinsic(_delay)
//    extern void _delay(unsigned long);
    #define _XTAL_FREQ              4000000
    #define SPI_DELAY               10 // 10us
    #define DS1305_DELAY            1 // 1ms
    #define DEBOUNCE                200 // 200ms
    // NOTE: To use the macros below, YOU must have previously defined _XTAL_FREQ
//    #define __delay_us(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000000.0)))
//    #define __delay_ms(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000.0)))
	
#endif