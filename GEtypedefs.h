/*******************************************************************************

FILE: GEtypedefs.h

%Header: %
 none

DESCRIPTION:
 This header file contains the variable typedefs for the HI-TECH and MPLAB
 compilers as defined by the GE Software Coding Standards (GE2017-9411).  Also
 includes common definitions that are useful for any project.

Copyright (c) 2012 - General Electric Corporation - All rights reserved.

%History:  %
 Mar 23, 2012   -   Initial version
 May 21, 2012   -   Added "Common definitions" section; added ON, OFF, TRUE,
                    FALSE definitions; updated description
 Jun 20, 2012   -   Added SET and CLEAR definitions; updated description
 Dec 18, 2012	-	Added more useful definitions
 
*******************************************************************************/

#ifndef GEtypedefs_H
#define GEtypedefs_H

typedef unsigned char   U8;
typedef char            I8;

typedef unsigned int    U16;
typedef int             I16;

typedef unsigned long   U32;
typedef long            I32;

typedef float           F32;

typedef double          F64;

typedef unsigned char   Bool;

// Common definitions
#define ON      	1
#define OFF     	0
#define TRUE    	1
#define FALSE   	0
#define SET     	1
#define CLEAR   	0
#define INPUT		1 // For TRIS registers
#define OUTPUT		0 // For TRIS registers
#define HIGH		1
#define LOW			0
#define NOT_PUSHED	1 // For buttons with pull-up resistors
#define PUSHED		0 // For buttons with pull-up resistors
#define ENABLE		1
#define DISABLE		0

#endif