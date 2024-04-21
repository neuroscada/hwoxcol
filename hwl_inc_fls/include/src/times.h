/************************************************************************/
/*****     COPYRIGHT 2008 - 2009      HONEYWELL INTERNATIONAL SARL      */ 
/************************************************************************/
#ifndef times_flag
#define times_flag 

#include "hsctypes.h"

/*
@(#)times.h	main.SVR_MASTERPROJ_Integration.1 
BEGIN_DOC
---------------------------------------------------------------------------
TIMES.H - for system time access
---------------------------------------------------------------------------
DESCRIPTION:
    Define some constants for accessing system time

    -----------------------------------------------------------------------
    NOTES - None
    -----------------------------------------------------------------------

DEFINITIONS:
*/

// number of seconds from the 
//  C base time of 1/1/1970 to our
//  Julian base date of 1/1/1981
#define CT_01_01_1981	347155200

// HSCTIME constatnts 
#define HT_MICRO_SECOND	(int8)(10)
#define HT_MILLI_SECOND	(int8)(1000*HT_MICRO_SECOND)
#define HT_SECOND	(int8)(1000*HT_MILLI_SECOND)
#define HT_MINUTE	(int8)(  60*HT_SECOND)
#define HT_HOUR		(int8)(  60*HT_MINUTE)
#define HT_DAY		(int8)(  24*HT_HOUR)
// number of 100 nanoseconds units from the 
//  HSCTIME base time of 1/1/1601 to the
//  C base date of 1/1/1970
#define HT_01_01_1970	(int8)116444736000000000
// number of 100 nanoseconds units from the 
//  HSCTIME base time of 1/1/1601 to our
//  Julian base date of 1/1/1981
#define HT_01_01_1981	(int8)(CT_01_01_1981*HT_SECOND+HT_01_01_1970)

/* HSC_TIMEZONEDATA - structure to store the state of the gettmz2 */
typedef struct tagHSC_TIMEZONEDATA {
	int8	lowerTime; 								// lower end of the time window
	int8	upperTime;								// upper end of the time window
	double	windowSizeMultiplier;   // Allow for shrinking window
	short	lowerBias;								// bias at the lower time
	short	upperBias;								// bias at the upper time
} HSC_TIMEZONEDATA;

#ifdef VMS	/* VMS to UNIX map */

#include	<time.h>

#define		tms		tbuffer

#define		tms_utime	proc_user_time
#define		tms_stime	proc_system_time

#elif defined(NT)

#else

#include	<sys/times.h>

#endif

/*
END_DOC
*/
#endif	/* end of conditional include times_flag */

/************************************************************************/
/*****     COPYRIGHT 2008 - 2009      HONEYWELL INTERNATIONAL SARL      */ 
/************************************************************************/
