/*******************************************************************************

FILE: DS1305.h

%Header: %
 GEtypedefs.h
 HardwareProfile.h

DESCRIPTION:
 This header file contains register and other definitions for the DS1305 real
 time clock.

%History:  %
12/15/2012   Jon Altenburger     Initial version
 
*******************************************************************************/

#ifndef DS1305_H

    #define DS1305_H

    #include "GEtypedefs.h"
    #include "HardwareProfile.h"
    
    /***** FUNCTION PROTOTYPES *****/
    void InitializeDS1305(void);
    void SetTime(time);
    void SetAlarm1(time);
    
    /***** REGISTER DEFINITIONS *****/
    // Read
    #define READ_TIME_SECONDS       0x00
    #define READ_TIME_MINUTES       0x01
    #define READ_TIME_HOURS         0x02
    #define READ_TIME_DAY           0x03
    #define READ_TIME_DATE          0x04
    #define READ_TIME_MONTH         0x05
    #define READ_TIME_YEAR          0x06
    #define READ_ALARM0_SECONDS     0x07
    #define READ_ALARM0_MINUTES     0x08
    #define READ_ALARM0_HOURS       0x09
    #define READ_ALARM0_DAY         0x0A
    #define READ_ALARM1_SECONDS     0x0B
    #define READ_ALARM1_MINUTES     0x0C
    #define READ_ALARM1_HOURS       0x0D
    #define READ_ALARM1_DAY         0x0E
    #define READ_CONTROL            0x0F
    #define READ_STATUS             0x10
    #define READ_TRICKLE_CHARGE     0x11
    // Write
    #define WRITE_TIME_SECONDS      0x80
    #define WRITE_TIME_MINUTES      0x81
    #define WRITE_TIME_HOURS        0x82
    #define WRITE_TIME_DAY          0x83
    #define WRITE_TIME_DATE         0x84
    #define WRITE_TIME_MONTH        0x85
    #define WRITE_TIME_YEAR         0x86
    #define WRITE_ALARM0_SECONDS    0x87
    #define WRITE_ALARM0_MINUTES    0x88
    #define WRITE_ALARM0_HOURS      0x89
    #define WRITE_ALARM0_DAY        0x8A
    #define WRITE_ALARM1_SECONDS    0x8B
    #define WRITE_ALARM1_MINUTES    0x8C
    #define WRITE_ALARM1_HOURS      0x8D
    #define WRITE_ALARM1_DAY        0x8E
    #define WRITE_CONTROL           0x8F
    #define WRITE_STATUS            0x90
    #define WRITE_TRICKLE_CHARGE    0x91
    
    /***** TIME DEFINITIONS *****/
    // Mask is used to disable a time (sec/min/hr/day) from an alarm
    #define MASK    0x80
    // "Zero" through "fifty nine" definitions
    // Valid for seconds, minutes, date (up to 31) and year
    #define _ZERO           0x00 // pic18f882.h already defines a "ZERO"
    #define ONE             0x01
    #define TWO             0x02
    #define THREE           0x03
    #define FOUR            0x04
    #define FIVE            0x05
    #define SIX             0x06
    #define SEVEN           0x07
    #define EIGHT           0x08
    #define NINE            0x09
    #define TEN             0x10
    #define ELEVEN          0x11
    #define TWELVE          0x12
    #define THIRTEEN        0x13
    #define FOURTEEN        0x14
    #define FIFTEEN         0x15
    #define SIXTEEN         0x16
    #define SEVENTEEN       0x17
    #define EIGHTEEN        0x18
    #define NINETEEN        0x19
    #define TWENTY          0x20
    #define TWENTY_ONE      0x21
    #define TWNETY_TWO      0x22
    #define TWENTY_THREE    0x23
    #define TWENRT_FOUR     0x24
    #define TWENTY_FIVE     0x25
    #define TWENTY_SIX      0x26
    #define TWENTY_SEVEN    0x27
    #define TWENTY_EIGHT    0x28
    #define TWENTY_NINE     0x29
    #define THIRTY          0x30
    #define THIRTY_ONE      0x31
    #define THIRTY_TWO      0x32
    #define THIRTY_THREE    0x33
    #define THIRTY_FOUR     0X34
    #define THIRTY_FIVE     0X35
    #define THIRTY_SIX      0X36
    #define THIRTY_SEVEN    0X37
    #define THIRTY_EIGHT    0X38
    #define THIRTY_NINE     0X39
    #define FORTY           0X40
    #define FORTY_ONE       0X41
    #define FORTY_TWO       0X42
    #define FORTY_THREE     0X43
    #define FORTY_FOUR      0X44
    #define FORTY_FIVE      0X45
    #define FORTY_SIX       0X46
    #define FORTY_SEVEN     0X47
    #define FORTY_EIGHT     0X48
    #define FORTY_NINE      0X49
    #define FIFTY           0X50
    #define FIFTY_ONE       0X51
    #define FIFTY_TWO       0X52
    #define FIFTY_THREE     0X53
    #define FIFTY_FOUR      0X54
    #define FIFTY_FIVE      0X55
    #define FIFTY_SIX       0X56
    #define FIFTY_SEVEN     0X57
    #define FIFTY_EIGHT     0X58
    #define FIFTY_NINE      0X59
    // Hours
    // Only definitions for 1-12 AM/PM are listed
    #define ONE_AM          0x41
    #define TWO_AM          0x42
    #define THREE_AM        0x43
    #define FOUR_AM         0x44
    #define FIVE_AM         0x45
    #define SIX_AM          0x46
    #define SEVEN_AM        0x47
    #define EIGHT_AM        0x48
    #define NINE_AM         0x49
    #define TEN_AM          0x50
    #define ELEVEN_AM       0x51
    #define TWELVE_AM       0x52
    #define ONE_PM          0x61
    #define TWO_PM          0x62
    #define THREE_PM        0x63
    #define FOUR_PM         0x64
    #define FIVE_PM         0x65
    #define SIX_PM          0x66
    #define SEVEN_PM        0x67
    #define EIGHT_PM        0x68
    #define NINE_PM         0x69
    #define TEN_PM          0x70
    #define ELEVEN_PM       0x71
    #define TWELVE_PM       0x72
    // Days
    #define SUNDAY          0x01
    #define MONDAY          0x02
    #define TUESDAY         0x03
    #define WEDNESDAY       0x04
    #define THURSDAY        0x05
    #define FRIDAY          0x06
    #define SATURDAY        0x07
    
#endif