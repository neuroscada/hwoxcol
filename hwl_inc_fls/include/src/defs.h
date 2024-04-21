/************************************************************************/
/*****     COPYRIGHT 2008-2014      HONEYWELL INTERNATIONAL SARL     ****/
/************************************************************************/

#ifndef defs_flag
#define defs_flag

/*
@(#)defs.h	main.SVR_MASTERPROJ_Integration.3
BEGIN_DOC
---------------------------------------------------------------------------
DEFS.H - user's system header file
---------------------------------------------------------------------------

DESCRIPTION:
    This is the ultimate in headers, and should be used for all system wide
    #defines and declarations.

    It defines
	UNIX system constants
	SN90 system constants and option flags
	wierd data types
	commonly used macros

*/

#include <stdio.h>
#include "system"
#include "src/lfns"
#include "src/platform"
#include "src/deprecate.h"

/*
------------------------------------------------------------------------
Specific operating system name, choose from:
    UNIX_VAT			Microport's System V/AT
    UNIX_V386			Microport's System V/386
    UNIX_SUPERTEAM_V_2		Honeywell's Superteam Unix V version VA80
    VMS_VAX			Digital's VMS on a VAX
    HP_UX			Hewlett Packard Unix version 8.0 (BSD)
------------------------------------------------------------------------
*/
#ifdef  VMS
#define VMS_VAX
#elif   defined(HP_UX)
#else
#define UNIX_V386
#endif


/*
------------------------------------------------------------------------
The rest of the definitions are self guided and DON'T need to be changed
from system to system.
------------------------------------------------------------------------
Generic operating system version and release:
    UNIX_SYSTEM_V_RELEASE_2	AT&T system V release 2 standard
    UNIX_SYSTEM_V_RELEASE_3	AT&T system V release 3 standard
    VMS_VERSION_5		Digital's VMS version 5
Dependancies on specific operating systems
    LFINDNULL			value returned by lfind(3)
    INT_EQ_SHORT		defined if int2==short (int2!=int)
    SWAP_BYTES			defined if int2's are stored lsb first
    SWAP_WORDS			defined if int4's are stored lsw first
------------------------------------------------------------------------
*/
#ifdef	UNIX_VAT		/* Microport's System V/AT */
#define	UNIX_SYSTEM_V_RELEASE_2	/* AT&T system V release 2 standard */
#define	LFINDNULL	-1	/* bug in microports unix */
#define SWAP_BYTES 	TRUE	/* switch on byte swapping routines */
#define SWAP_WORDS 	TRUE	/* switch on word swapping routines */
#endif

#ifdef 	UNIX_V386		/* Microport's System V/386 */
#define	UNIX_SYSTEM_V_RELEASE_3	/* AT&T system V release 3 standard */
#define	LFINDNULL	NULL	/* correct definition for unix */
#define INT_EQ_SHORT	TRUE	/* an int2==short */
#define SWAP_BYTES 	TRUE	/* switch on byte swapping routines */
#define SWAP_WORDS 	TRUE	/* switch on word swapping routines */
#endif

#ifdef 	UNIX_SUPERTEAM_V_2	/* Honeywell's Superteam Unix V version VA80 */
#define	UNIX_SYSTEM_V_RELEASE_2	/* AT&T system V release 2 standard */
#define	LFINDNULL	NULL	/* correct definition for unix */
#define INT_EQ_SHORT	TRUE	/* an int2==short */
#define B19200		B9600	/* define 19.2kb as 9600 for release 2 */
#define B38400		B9600	/* define 38.4kb as 9600 for release 2 */
#endif

#ifdef 	VMS_VAX			/* Digital's VMS */
#define	VMS_VERSION_5		/* Digital's VMS version 5 */
#define	LFINDNULL	NULL	/* correct definition for unix */
#define INT_EQ_SHORT	TRUE	/* an int2==short */
#define SWAP_BYTES 	TRUE	/* switch on byte swapping routines */
#define SWAP_WORDS 	TRUE	/* switch on word swapping routines */
#endif

#ifdef 	HP_UX			/* Hewlett packard's UNIX supports-> */
#define	UNIX_SYSTEM_V_RELEASE_3	/* AT&T system V release 3 standard */
#define	LFINDNULL	NULL	/* correct definition for unix */
#define INT_EQ_SHORT	TRUE	/* an int2==short */
#endif

#ifdef NT
#define	LFINDNULL	NULL	/* correct definition for unix */
#define INT_EQ_SHORT	TRUE	/* an int2==short */
#define SWAP_BYTES 	TRUE	/* switch on byte swapping routines */
#define SWAP_WORDS 	TRUE	/* switch on word swapping routines */
#define O_NDELAY	0x00	/* non-blocking I/O */
#endif

/*
------------------------------------------------------------------------
Dependancies on generic operating systems
    SIG_ERR			value returned by signal(2)
    noshare			VMS C declaration of non-sharable data
------------------------------------------------------------------------
*/
#ifdef	UNIX_SYSTEM_V_RELEASE_2
#define	SIG_ERR		(int(*)())-1
#define noshare
#endif

#ifdef	UNIX_SYSTEM_V_RELEASE_3
#define noshare
#endif

#ifdef	VMS_VERSION_5
#define sigset(x,y)  signal(x,y)
#ifndef SIG_ERR
/* This definition causes a problem on ALPHA, its already defined */
#define	SIG_ERR		(int(*)())-1
#endif
#endif

/*
------------------------------------------------------------------------
Defines macros to rename C routines callable from both C & FORTRAN
    eg datopn => datopn$ from C
                 DATOPN  from FORTRAN
------------------------------------------------------------------------
*/


#ifdef _WIN32
#ifndef WIN32
#define WIN32
#endif
#ifndef NT
#define NT
#endif

#ifndef _X86_
#define _X86_ 1
#endif
#endif /* _WIN32 */

#ifdef NT
#define WSA_VER MAKEWORD(2,2)
#ifdef WIN16
#include <windows.h>
#define _stdcall
#define __stdcall
#else
#include <windef.h>
#include <winnt.h>
#include <excpt.h>
#include <winbase.h>
#include <io.h>
#include <stddef.h>
#include <process.h>
#endif

#define pause()		SuspendThread(GetCurrentThread())
#define sigset(x,y)	signal(x,y)
#define sleep(t)	Sleep(1000*(t))

typedef int key_t;

#endif

/*
------------------------------------------------------------------------
Compiler flags, comment out to turn off:
------------------------------------------------------------------------
*/
#define PARANOID 	    		TRUE	/* switch on heavy checking */

/* #define SOFTWARE_PROTECTION_IMPLEMENTED TRUE /* perform dongle checks */
/* #define SOFTWARE_PROTECTION_WRITE_TRB TRUE   /* clear trb on failed check */
/* #define NO_DISPLAY_COMPRESS TRUE */ 	/* dont try to compress displays */

/*
------------------------------------------------------------------------
define a few of our own types
------------------------------------------------------------------------
*/

#include "hsctypes.h"

#define INT4_SZ		2	/* number of int2's per fortran int4 */
#define REAL_SZ		2	/* number of int2's per fortran real */
#define DBLE_SZ		4	/* number of int2's per fortran double */

#ifndef FAR
#define FAR
#endif
#ifndef CALLBACK
#define CALLBACK
#endif

/* standard simple definitions */
#ifndef TRUE
/* This is normally defined as 1, the redefinition causes a problem on ALPHA */
#define	TRUE		-1
#endif
#define FALSE		0
#define VALID   	1
#define INVALID 	0

#ifdef NT
#define PATH_SEPARATOR 	'\\'
#else
#define PATH_SEPARATOR 	'/'
#endif

/* system range definitions */
#undef  MAXINT8		// these are also defined in a windows header
#undef  MININT8
#define MAXINT8		((int8)(((uint8)-1) >> 1))
#define MAXINT4		((int4)(((uint4)-1) >> 1))
#define MAXUINT4	((uint4)(-1))
#define MAXINT2		((int2)(((uint2)-1) >> 1))
#define MAXUINT2	((uint2)(-1))
#define MININT8		((int8)(~MAXINT8))
#define MININT4		((int4)(~MAXINT4))
#define MINUINT4	((uint4)(0))
#define MININT2		((int2)(~MAXINT2))
#define MINUINT2	((uint2)(0))

// All data entry is done in double precision. This is acurate for all types except int8.
// For int8, there are rounding issues at full range and we need a different MAX and MIN
// to prevent incorrect data entry. We zero the bits lost to the exponent.
// Mantisa is 1.n so we loose 1 less bit than we think.
#define MAXINT8inDBLE	((int8)(MAXINT8 & ~0x3FF))
#define MININT8inDBLE	((int8)(MININT8 & ~0x3FF))
#define MAXINT8inREAL	((int8)(MAXINT8 & ~0x7FFFFFFFFF))
#define MININT8inREAL	((int8)(MININT8 & ~0x7FFFFFFFFF))
#define MAXINT4inREAL	((int4)(MAXINT4 & ~0x7F))
#define MININT4inREAL	((int4)(MININT4 & ~0x7F))

/* i/o lrns */
#define MIN_LRN			  1	/* first valid i/o LRN  */
#define LPT1_LRN		  6	/* 15 printers  */
#define DSDC_LRN		 21	/* Direct Station Network Components LRN */
#define CHN1_LRN		 51	/* 99 channels * 2 lrns */
#define RIPSD_LRN		300	/* Comms LRN used for Ripsd tracing */
#define CRT1_LRN		301	/* ?? stations  */
#define MAX_LRN 		(CRT1_LRN+NUM_CRTS-1) /* last valid i/o LRN  */

/* project range definitions */
#define MAX_NUMBER_LFNS 	NUM_LFNS	/* number of sn90 lfns */
#define MIN_FILE		1
#define MIN_LFN 		RUNLFN
#define MAX_ASCII_REC_SIZE	132	/* bytes */
#define DATA_LFN 		RUNLFN
#define DATA_REC_SIZE 		DISC_SSZ	/* bytes */
#define DATA_FILE_REL_PATH	"../data/data"
#define DEVICE_FILE_REL_PATH	"../data/device"
#define LOGFILE     		"/../data/log"
#define BACKUP_LFN 		BUPLFN
#define SPACES_PER_TAB		8

/* a few simple macros */

#ifndef min		/* defined for NT already */
#define min(a,b)  (((a)>(b))? (b) : (a))
#define max(a,b)  (((a)>(b))? (a) : (b))
#endif

#define __HILOBYTE
#define hibyte(int2ptr)             ((*(int2ptr) >> 8) & 0x00ff)
#define lobyte(int2ptr)             (*(int2ptr) & 0x00ff)

#define sthibyte(int2ptr,byte)      *(int2ptr) = (*(int2ptr) & 0x00ff) | ((byte)<<8)

#define stlobyte(int2ptr,byte)      *(int2ptr) = (*(int2ptr) & 0xff00) | ((byte) & 0xff)

#define ldint4(int2ptr)             (*(int4 *)(int2ptr))
#define stint4(int2ptr,int4val)     *(int4 *)(int2ptr) = (int4val)

#define lduint4(int2ptr)            (*(uint4 *)(int2ptr))
#define stuint4(int2ptr,uint4val)   *(uint4 *)(int2ptr) = (uint4val)

#define ldint8(int2ptr)             (*(int8 *)(int2ptr))
#define stint8(int2ptr,int8val)     *(int8 *)(int2ptr) = (int8val)

#define lduint8(int2ptr)            (*(uint8 *)(int2ptr))
#define stuint8(int2ptr,uint8val)   *(uint8 *)(int2ptr) = (uint8val)

#define ldreal(int2ptr)             (*(float *)(int2ptr))
#define streal(int2ptr,realval)     *(float *)(int2ptr) = (realval)

#define lddble(int2ptr)             (*(double *)(int2ptr))
#define stdble(int2ptr,dbleval)     *(double *)(int2ptr) = (dbleval)

#define hilong(int8val)             (((int8val) >> 32) & 0xffffffff)
#define lolong(int8val)             (((int8val)      ) & 0xffffffff)

#include "src/prototypes.h"
#include "src/points.h"
#include "src/dictionary.h"

// Macro for setting the locale so that references to the
// g_hsc_LocaleIsSet global variable are not littered throughout
// the code in the system. See clib\cstr\setlocal.c for more
// information.
#define HSC_SET_LOCALE	hsc_set_locale();

// Error macros
// Enterporse Model error check (ignore warnings)
#define CHECK_RETVAL(x) if (((x) == -1) && hsc_IsError(errno)) return -1;

// Stringify macros
#define STRINGIFY(x)        #x
#define STRINGIFY_VALUE(x)  STRINGIFY(x)
#define __LINESTR__         STRINGIFY_VALUE(__LINE__)

// Unique name macros
#define __HSC_UNIQUE_NAME(varname, line)    varname##line
#define _HSC_UNIQUE_NAME(varname, line)     __HSC_UNIQUE_NAME( varname, line )
#define HSC_UNIQUE_NAME(varname)            _HSC_UNIQUE_NAME( varname, __LINE__ )

// The POSIX name for this item is deprecated.
#define swab		_swab
#define strdup		_strdup
#define stricmp		_stricmp
#define strnicmp	_strnicmp
#define wcsicmp		_wcsicmp

/*
END_DOC
*/

#endif		/* end of defs_flag if */
/************************************************************************/
/*****     COPYRIGHT 2008-2014      HONEYWELL INTERNATIONAL SARL     ****/
/************************************************************************/
