#ifndef PROTOTYPES_FLAG
#define PROTOTYPES_FLAG

/************************************************************************/
/*****     COPYRIGHT 2008 - 2016    HONEYWELL INTERNATIONAL SARL     ****/
/************************************************************************/

/*
@(#)prototypes.h	main.SVR_MASTERPROJ_Integration.R0930_Int.19
BEGIN_DOC
---------------------------------------------------------------------------
prototypes.h - CLIB function prototypes
---------------------------------------------------------------------------
DESCRIPTION:
	This header file contains prototypes for all functions defined
	under CLIB.

    -----------------------------------------------------------------------
    NOTES - The _DECLARE macro is defined to optionally omit argument types
	    where necessary.
    -----------------------------------------------------------------------
*/

#ifndef _DECLARE
#ifdef NT
#define _DECLARE(formal_parameters) formal_parameters
#else
#define _DECLARE(formal_parameters) ()
#endif
#endif /* _DECLARE */

// definitions

#ifndef EXTERN_C
#ifdef __cplusplus
    #define EXTERN_C    extern "C"
#else
    #define EXTERN_C    extern
#endif
#endif

#ifndef STDCALL
#ifdef NT
    #define STDCALL    __stdcall
#else
    #define STDCALL
#endif
#endif

#ifndef FORTCALL
#ifdef NT
    #define FORTCALL	STDCALL
#else
    #define FORTCALL
#endif
#endif

#ifndef __cplusplus
#ifndef inline
#define inline __inline
#endif
#endif

#ifndef THREAD
#ifdef NT
    #define THREAD	__declspec(thread)
#else
    #define THREAD
#endif
#endif

#include "src/mzero.h"
#include "src/trbtbl_def"
#include "src/evtfil_def"
#include "src/notifhook_fun"
#include "src/dictionary.h"
#include "src/operid_def"
#include "src/times.h"
#include "src/deprecate.h"
#include "notifmngrtypes.h"
#include "src/sor_api_types.h"

// inline functions

// inline function to protect the initialization of a data structure
inline int hsc_Protected_Initialize(volatile long* lpLock, int CALLBACK InitializationRoutine(void))
{
    if (*lpLock==0)		/* do faster cached memory check first */
    {
	if (InterlockedCompareExchange(lpLock,1,0)==0)
	{
	    if (InitializationRoutine())
	    {
		InterlockedExchange(lpLock,0);
		return -1;
	    }
	    InterlockedExchange(lpLock,2);
	}
    }
    while (*lpLock==1)		/* wait for initialization to complete */
	Sleep(1);
    if (*lpLock!=2)		/* if initialization failed, then error */
    {
	errno = 39;		/* ENOLCK (not using symbol because caller may not have errno.h )*/
	return -1;
    }
    return 0;
}

// inline function to protect the initialization of a data structure.
// Allows pointer to argument to be passed to the initialization routine.
inline int hsc_Protected_Initialize_Ex(volatile long* lpLock, int CALLBACK InitializationRoutine(void*), void* ArgList)
{
    if (*lpLock==0)		/* do faster cached memory check first */
    {
	if (InterlockedCompareExchange(lpLock,1,0)==0)
	{
	    if (InitializationRoutine(ArgList))
	    {
		InterlockedExchange(lpLock,0);
		return -1;
	    }
	    InterlockedExchange(lpLock,2);
	}
    }
    while (*lpLock==1)		/* wait for initialization to complete */
	Sleep(1);
    if (*lpLock!=2)		/* if initialization failed, then error */
    {
	errno = 39;		/* ENOLCK (not using symbol because caller may not have errno.h )*/
	return -1;
    }
    return 0;
}

// inline function to protect the termination of a data structure
inline int hsc_Protected_Terminate(volatile long* lpLock, int CALLBACK TerminationRoutine(void))
{
    if (*lpLock==2)		/* do faster cached memory check first */
    {
	    if (InterlockedCompareExchange(lpLock,1,2)==2)
	    {
	        if (TerminationRoutine())
	        {
    	        InterlockedExchange(lpLock,2);
   	    	    return -1;
	        }
   		    InterlockedExchange(lpLock,0);
	    }
    }
    while (*lpLock==1)		/* wait for termination to complete */
    	Sleep(1);
    if (*lpLock!=0)		/* if termination failed, then error */
    {
	    errno = 39;		/* ENOLCK (not using symbol because caller may not have errno.h )*/
	    return -1;
    }
    return 0;
}

// inline function to protect the termination of a data structure.
// Allows pointer to argument to be passed to the termination routine.
inline int hsc_Protected_Terminate_Ex(volatile long* lpLock, int CALLBACK TerminationRoutine(void*), void* ArgList)
{
    if (*lpLock==2)		/* do faster cached memory check first */
    {
	    if (InterlockedCompareExchange(lpLock,1,2)==2)
	    {
	        if (TerminationRoutine(ArgList))
	        {
    	        InterlockedExchange(lpLock,2);
   	    	    return -1;
	        }
   		    InterlockedExchange(lpLock,0);
	    }
    }
    while (*lpLock==1)		/* wait for termination to complete */
    	Sleep(1);
    if (*lpLock!=0)		/* if termination failed, then error */
    {
	    errno = 39;		/* ENOLCK (not using symbol because caller may not have errno.h )*/
	    return -1;
    }
    return 0;
}

#define MINIMISE_BASE_PRIORITY	0x0100	// Add this to our server priority values to
					// indicate the process|thread priority pair
					// should minimise the process priority instead
					// or maximising it

// function protoypes
static int		addkey _DECLARE((int, struct keydesc*, int));
EXTERN_C void		addtime _DECLARE((HSCTIME*, HSCTIME*));
EXTERN_C void		addtm  _DECLARE((HSCTIME*, long, int));
EXTERN_C void		addtm2 _DECLARE((HSCTIME*, long, long, int));
EXTERN_C void		AdjustToInterval _DECLARE((HSCTIME*, int4));
EXTERN_C void		alpha _DECLARE((char*, short));
EXTERN_C void		arshft _DECLARE((short*, short*, short*, short*));
EXTERN_C short		asc2date _DECLARE((char*, short));
EXTERN_C float		asc2time _DECLARE((char*, short));
EXTERN_C double		asc2time2 _DECLARE((char*, short));
EXTERN_C void		asctm  _DECLARE((const HSCTIME*, char*, short));
EXTERN_C void		asctmraw  _DECLARE((const HSCTIME*, char*, short));
EXTERN_C void		asctmz _DECLARE((const HSCTIME*, short, char*, short));
EXTERN_C void		asctmd _DECLARE((const HSCTIME*, char*, short));
EXTERN_C void		asctmt _DECLARE((const HSCTIME*, char*, short));
EXTERN_C short		asctod _DECLARE((char*, short, short*, int4*));
EXTERN_C short		asctodh _DECLARE((char*, short, short*, int4*));
EXTERN_C short		asctof _DECLARE((char*, short, short*, short*, short*));
EXTERN_C short		asctoh _DECLARE((char*, short, short*, short*));
EXTERN_C short		asctoi _DECLARE((char*, short, short*, short*));
EXTERN_C short		asctoll _DECLARE((char*, short, short*, int8*));
EXTERN_C short		asctoo _DECLARE((char*, short, short*, short*));
EXTERN_C short		asctop _DECLARE((char*, short, short*, short*, short*));
EXTERN_C int		ascv _DECLARE((char*, int, int, union values*, int, int));
EXTERN_C void		ascvrt _DECLARE((char*, short, short*, short*, short*, short*, short*));
static int		aud_chk _DECLARE((int));
EXTERN_C short		avail_lrn _DECLARE((void));
EXTERN_C void		binren _DECLARE((short*, short*, short*, short*));
EXTERN_C void		binwrn _DECLARE((short*, short*, short*, short*));
EXTERN_C void		bldpath _DECLARE((char*, char*, char*, char*, char*));
EXTERN_C struct dir*	bldtree _DECLARE((char*));
EXTERN_C void		brkds _DECLARE((void));
EXTERN_C short		brken _DECLARE((void));

#ifdef NT
EXTERN_C int		brkintr _DECLARE((unsigned long));
#else
EXTERN_C void		brkintr _DECLARE((void));
#endif

EXTERN_C int		bsortcmp _DECLARE((short*, short*));
EXTERN_C int		bsortdir _DECLARE((char*, struct directives*));
EXTERN_C int		bsortin _DECLARE((char*, char*, unsigned long, int*));
EXTERN_C int		bsortout _DECLARE((char*, char*, int, int));
EXTERN_C long		btestx _DECLARE((unsigned short*, unsigned short*));
EXTERN_C int2 FORTCALL ACTIONW _DECLARE((int2*, int2*, int4*, int4*));
EXTERN_C void		CALLBACK c_almmsg_alarm _DECLARE((const char*, int2));
EXTERN_C void		CALLBACK c_almmsg_event _DECLARE((const char*));
EXTERN_C void       CALLBACK c_almmsg_event_stn _DECLARE((const char*,int2));
EXTERN_C void		CALLBACK c_almmsg_alarm_area _DECLARE((const char*, int2, const char*));
EXTERN_C void		CALLBACK c_almmsg_event_area _DECLARE((const char*, const char*));
EXTERN_C void		CALLBACK c_almmsg_alarm_area_holder _DECLARE((const char*, int2, const char*, int4));
EXTERN_C void		CALLBACK c_almmsg_event_area_holder _DECLARE((const char*, const char*, int4));
EXTERN_C char*		CALLBACK c_almmsg_format _DECLARE((const char*, const char*, const char*, const char*, const char*, const char*));
EXTERN_C char*		CALLBACK c_almmsg_format2 _DECLARE((const char*, const char*, const char*, const char*, const char*, const char*, const char*));
EXTERN_C char*		CALLBACK c_almmsg_format2_malloc _DECLARE((const char*, const char*, const char *, const char*, const char*, const char*, const char*));
EXTERN_C void		CALLBACK c_almmsg_format2_almevt _DECLARE((PEVTFIL, const char*, const char*, const char *, const char*, const char*, const char*, const char*, const char*));
EXTERN_C void		CALLBACK c_almmsg_alarm_subtyp _DECLARE((const char*, int2, int2));
EXTERN_C void		CALLBACK c_almmsg_event_subtyp _DECLARE((const char*, int2));
EXTERN_C void		CALLBACK c_almmsg_alarm_area_subtyp _DECLARE((const char*, int2, int2, const char*));
EXTERN_C void		CALLBACK c_almmsg_event_area_subtyp _DECLARE((const char*, int2, const char*));
EXTERN_C void       CALLBACK c_almmsg_flags_subtyp _DECLARE((const char *, int2, int2, int2, int2, int2));
EXTERN_C void		CALLBACK c_almmsg_area_flags_subtyp _DECLARE((const char*, int2, int2, const char*, int2, int2, int2));
EXTERN_C void		almmsg _DECLARE((const char*, int2));
EXTERN_C void		almmsgarea _DECLARE((const char*, int2, int2));
EXTERN_C void		almmsgarea2 _DECLARE((const char*, int2, const char*));
EXTERN_C void		almmsgholder _DECLARE((const char*, int2, int2, int4));
EXTERN_C void		almmsgholder2 _DECLARE((const char*, int2, const char*, int4));
EXTERN_C void		almmsgcardholder _DECLARE((const char*, int2, int2, double, int4));
EXTERN_C char*		almmsg_format _DECLARE((const char*, const char*, const char*, const char*, const char*, const char*));
EXTERN_C char*		almmsg_format2 _DECLARE((const char*, const char*, const char*, const char*, const char*, const char*, const char*));
EXTERN_C char*		almmsg_format2_malloc _DECLARE((const char*, const char*, const char*, const char*, const char*, const char*, const char*));
EXTERN_C void		almmsg_format2_almevt _DECLARE((PEVTFIL, const char*, const char*, const char*, const char*, const char*, const char*, const char*, const char*));
EXTERN_C void		almmsg_subtyp _DECLARE((const char*, int2, int2));
EXTERN_C void		almmsgarea_subtyp _DECLARE((const char*, int2, int2, int2));
EXTERN_C void		almmsgarea2_subtyp _DECLARE((const char*, int2, int2, const char*));
EXTERN_C void       almmsgflags_subtyp _DECLARE((const char*, int2, int2, int2, int2, int2));
EXTERN_C void		almmsgarea2flags_subtyp _DECLARE((const char*, int2, int2, const char*, int2, int2, int2));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_bad _DECLARE((PNTNUM16));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_badpar _DECLARE((PNTNUM16, PRMNUM));
EXTERN_C void		CALLBACK c_chrint _DECLARE((char*, int, int2*, int));
EXTERN_C int		CALLBACK c_copy _DECLARE((char*, char*, int));
EXTERN_C void		CALLBACK c_crttsk _DECLARE((char*, int, int, int, int2*));
EXTERN_C void FORTCALL  CNTROL      _DECLARE((PNTNUM*,PRMNUM*,float*,int2*));
EXTERN_C void FORTCALL  CNTROL2     _DECLARE((PNTNUM*,PRMNUM*,double*,int2*));
EXTERN_C void FORTCALL  CNTROLPRTY  _DECLARE((PNTNUM*,PRMNUM*,float*,int2*,int2*,int2*));
EXTERN_C void FORTCALL  CNTROL2PRTY _DECLARE((PNTNUM*,PRMNUM*,double*,int2*,int2*,int2*));
EXTERN_C void FORTCALL  DATAIO      _DECLARE((int2*,int2*,int2*,int2*,int2*,int2*,int2*,int2*,int2*));
EXTERN_C int4 FORTCALL  DATAIO4     _DECLARE((int4*,int4*,int4*,int4*,int4*,int2*,int4*,int4*));
EXTERN_C void FORTCALL  DATBIO      _DECLARE((int2*,int2*,int2*,int2*,int2*,int2*,int2*,int2*,int2*));
EXTERN_C int4 FORTCALL  DATBIO4     _DECLARE((int4*,int4*,int4*,int4*,int4*,int2*,int4*,int4*));
EXTERN_C int4 FORTCALL  DATWIO4     _DECLARE((int4*,int4*,int4*,int4*,int4*,int4*,int4*,int4*,int4*));
EXTERN_C int		CALLBACK c_dataio_close _DECLARE((int));
EXTERN_C int		CALLBACK c_dataio_dequeue _DECLARE((int, int, int2*, int));
EXTERN_C int		CALLBACK c_dataio_open _DECLARE((int));
EXTERN_C int		CALLBACK c_dataio_queue _DECLARE((int, int, int2*, int));
EXTERN_C int		CALLBACK c_dataio_reaabs _DECLARE((int, int, int, int2*, int));
EXTERN_C int		CALLBACK c_dataio_read _DECLARE((int, int, int, int2*, int));
EXTERN_C int		CALLBACK c_dataio_reaabs_blk _DECLARE((int, int, int, int, int2*, int));
EXTERN_C int		CALLBACK c_dataio_read_blk _DECLARE((int, int, int, int, int2*, int));
EXTERN_C int		CALLBACK c_dataio_read_newest _DECLARE((int, int*, int, int2*, int));
EXTERN_C int		CALLBACK c_dataio_read_oldest _DECLARE((int, int*, int, int2*, int));
EXTERN_C int		CALLBACK c_dataio_size _DECLARE((int, int*, int*));
EXTERN_C int		CALLBACK c_dataio_write _DECLARE((int, int, int, int2*, int));
EXTERN_C int		CALLBACK c_dataio_write_blk _DECLARE((int, int, int, int, int2*, int));
EXTERN_C int		CALLBACK c_dataio_write_newest _DECLARE((int, int*, int, int2*, int));
EXTERN_C int2		CALLBACK c_datclo _DECLARE((int));
EXTERN_C int2		CALLBACK c_datopn _DECLARE((int*, char*, int));
EXTERN_C int		CALLBACK c_deltsk _DECLARE((int));
EXTERN_C int		CALLBACK c_devget_by_lrn _DECLARE((int, struct devtbl*));
EXTERN_C int		CALLBACK c_devget_by_name _DECLARE((char*, struct devtbl*));
EXTERN_C int		CALLBACK c_devput_by_lrn _DECLARE((int, struct devtbl*));
EXTERN_C int		CALLBACK c_devput_by_name _DECLARE((char*, struct devtbl*));
EXTERN_C int2		c_dsphtml( int2 , char * );
EXTERN_C int		CALLBACK c_ex _DECLARE((char*));
EXTERN_C int		CALLBACK c_ex_nowait _DECLARE((char*));
EXTERN_C int		CALLBACK c_ex_full _DECLARE((char*, int));
EXTERN_C int		CALLBACK c_gbload _DECLARE((void));
EXTERN_C int		CALLBACK c_gbunload _DECLARE((void));
EXTERN_C int		CALLBACK c_gdbcnt _DECLARE((int2 *, int2 *, int2 *, int2 *, int2 *, double *));
EXTERN_C int2		CALLBACK c_getapp _DECLARE((char*, int, struct apptbl*));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_getch _DECLARE((PNTNUM16, uint2, char*, int));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_geti2 _DECLARE((PNTNUM16, uint2, int2*));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_geti4 _DECLARE((PNTNUM16, uint2, int4*));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_getrl _DECLARE((PNTNUM16, uint2, float*));
EXTERN_C int		CALLBACK c_getdat _DECLARE((int, int, int, int, int, int, int2*, int));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_gethst_date _DECLARE((int, int, float, int, PNTNUM16*, int, char*, float*));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_gethst_ofst _DECLARE((int, int, int, PNTNUM16*, int, char *, float *));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_gethstpar_date _DECLARE((int, int, float, int, PNTNUM16*, PRMNUM*, int, char*, float*));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_gethstpar_ofst _DECLARE((int, int, int, PNTNUM16*, PRMNUM*, int, char*, float*));
EXTERN_C int		CALLBACK c_gethstpar_date_2 _DECLARE((int, int, float, int, PNTNUM*, PRMNUM*, int, char*, float*));
EXTERN_C int		CALLBACK c_gethstpar_ofst_2 _DECLARE((int, int, int, PNTNUM*, PRMNUM*, int, char*, float*));
EXTERN_C int		CALLBACK c_getlrn _DECLARE((void));
EXTERN_C void		CALLBACK c_getlst _DECLARE((int2, float*, int2*));
EXTERN_C int		CALLBACK c_getpar _DECLARE((int, char*, int));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_getpnt _DECLARE((char*, PNTNUM16*));
EXTERN_C int2		CALLBACK c_getprm _DECLARE((int, int2*, int2*,int));
EXTERN_C int		CALLBACK c_getreq _DECLARE((int2 *));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_getval_asci _DECLARE((PNTNUM16, int, char*, int));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_getval_hist _DECLARE((PNTNUM16, int, int, float*));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_getval_numb _DECLARE((PNTNUM16, int, float*));
EXTERN_C void		CALLBACK c_givlst _DECLARE((int2, float*, int2*));
EXTERN_C int		CALLBACK c_gtoj _DECLARE((int, int, int));
EXTERN_C void		CALLBACK c_intchr _DECLARE((int2*, int, char*, int));
EXTERN_C void		CALLBACK c_jtog _DECLARE((int, int*, int*, int*));
EXTERN_C int		c_ll_cleanup _DECLARE((void));
EXTERN_C void		c_ll_getbypar _DECLARE((short*, short*, char*, short, char*, short));
EXTERN_C char*		c_ll_getstr _DECLARE((int, int, char*));
EXTERN_C int		CALLBACK c_lock_dir _DECLARE((int, int));
EXTERN_C int		CALLBACK c_lock_file _DECLARE((int, int, int));
EXTERN_C int		CALLBACK c_lock_rec _DECLARE((int, int, int, int));
EXTERN_C void		c_logmsg _DECLARE((char*, char*, char*, ...));
EXTERN_C int2		CALLBACK c_mkdir _DECLARE((char *path, int2, int));
EXTERN_C int		CALLBACK c_mmio _DECLARE((int, int, int, int, int, int, int2*, int));
EXTERN_C int		CALLBACK c_mmio_close _DECLARE((int));
EXTERN_C int		CALLBACK c_mmio_getoid _DECLARE((int, int, char*, int*));
EXTERN_C int		CALLBACK c_mmio_open _DECLARE((int));
EXTERN_C int		CALLBACK c_mmio_oprread _DECLARE((int, int, int2*, int));
EXTERN_C int		CALLBACK c_mmio_read _DECLARE((int, int, int, int, int, int2*, int));
EXTERN_C int		CALLBACK c_mmio_write _DECLARE((int, int2*, int));
EXTERN_C int		CALLBACK c_mmio2 _DECLARE((int, int, int, int, int, int, int, int2*, int));
EXTERN_C int		CALLBACK c_mmio2_read _DECLARE((int, int, int, int, int, int, int2*, int));
EXTERN_C int		CALLBACK c_mmio2_write _DECLARE((int, int, int2*, int));
EXTERN_C uint2		CALLBACK c_morerq _DECLARE((void));
EXTERN_C int		CALLBACK c_mzero _DECLARE((float *));
EXTERN_C int		CALLBACK c_oprerr _DECLARE((int, int));
EXTERN_C int		CALLBACK c_oprstr3 _DECLARE((int, int, uint2, const char*, int));
EXTERN_C int		CALLBACK c_oprstr_info _DECLARE((int, const char*));
EXTERN_C int		CALLBACK c_oprstr_message _DECLARE((int, const char*));
EXTERN_C int		CALLBACK c_oprstr_prompt _DECLARE((int, const char*, int));
EXTERN_C int		CALLBACK c_oprstr_prompth _DECLARE((int, const char*, int));
EXTERN_C int		CALLBACK c_oprstr_promptyn _DECLARE((int, const char*, int));
EXTERN_C int		CALLBACK c_oprstr_promptyn2 _DECLARE((int, int, const char*, int));
EXTERN_C char*		CALLBACK c_oprstr_response _DECLARE((int, const struct prm*));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_pcs _DECLARE((PNTNUM16, PRMNUM));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_pcsw _DECLARE((PNTNUM16, PRMNUM));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_pcps _DECLARE((PNTNUM16, PRMNUM));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_pcpsw _DECLARE((PNTNUM16, PRMNUM));
EXTERN_C int		CALLBACK c_pcs_2 _DECLARE((PNTNUM, PRMNUM));
EXTERN_C int		CALLBACK c_pcsw_2 _DECLARE((PNTNUM, PRMNUM));
EXTERN_C int		CALLBACK c_pcps_2 _DECLARE((PNTNUM, PRMNUM));
EXTERN_C int		CALLBACK c_pcpsw_2 _DECLARE((PNTNUM, PRMNUM));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_pps _DECLARE((PNTNUM16, int, int*));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_ppsw _DECLARE((PNTNUM16, int, int*));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_ppv _DECLARE((PNTNUM16, int, double));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_ppvw _DECLARE((PNTNUM16, int, double));
EXTERN_C int		CALLBACK c_pps_2 _DECLARE((PNTNUM, PRMNUM, int*));
EXTERN_C int		CALLBACK c_ppsw_2 _DECLARE((PNTNUM, PRMNUM, int*));
EXTERN_C int		CALLBACK c_ppv_2 _DECLARE((PNTNUM, PRMNUM, double));
EXTERN_C int		CALLBACK c_ppvw_2 _DECLARE((PNTNUM, PRMNUM, double));
EXTERN_C int		CALLBACK c_prsend_crt _DECLARE((int, char *));
EXTERN_C int		CALLBACK c_prsend_printer _DECLARE((int, char *));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_putch _DECLARE((PNTNUM16, uint2, char*));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_puthst_date _DECLARE((int, int, float, int, PNTNUM16*, PRMNUM*, int, char*, float*));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_puthst_ofst _DECLARE((int, int, int, PNTNUM16*, PRMNUM*, int, char*, float*));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_puti2 _DECLARE((PNTNUM16, uint2, int2));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_puti4 _DECLARE((PNTNUM16, uint2, int4));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_putrl _DECLARE((PNTNUM16, uint2, float));
EXTERN_C int		CALLBACK c_putdat _DECLARE((int, int, int, int, int, int, int2*, int));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_putval_asci _DECLARE((PNTNUM16, int, char*));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_putval_hist _DECLARE((PNTNUM16, int, int, float));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_putval_numb _DECLARE((PNTNUM16, int, float));
EXTERN_C int		CALLBACK c_rm _DECLARE((char*, int));
EXTERN_C uint2		CALLBACK c_rqcl _DECLARE((int2*, int, int));
EXTERN_C void		CALLBACK c_rqstsk _DECLARE((int, int, uint2*, int2, int2*, int));
EXTERN_C int2		CALLBACK c_rqtskb _DECLARE((int));
EXTERN_C int2		CALLBACK c_rqtskb_prm _DECLARE((int, int2*));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_scs _DECLARE((PNTNUM16, PRMNUM));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_scsw _DECLARE((PNTNUM16, PRMNUM));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_scps _DECLARE((PNTNUM16, PRMNUM));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_scpsw _DECLARE((PNTNUM16, PRMNUM));
EXTERN_C int		CALLBACK c_scs_2 _DECLARE((PNTNUM, PRMNUM));
EXTERN_C int		CALLBACK c_scsw_2 _DECLARE((PNTNUM, PRMNUM));
EXTERN_C int		CALLBACK c_scps_2 _DECLARE((PNTNUM, PRMNUM));
EXTERN_C int		CALLBACK c_scpsw_2 _DECLARE((PNTNUM, PRMNUM));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_sps _DECLARE((PNTNUM16, int));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_spsw _DECLARE((PNTNUM16, int));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_spv _DECLARE((PNTNUM16, int, double));
EXTERN_C PNT16_DEPRECATED int CALLBACK c_spvw _DECLARE((PNTNUM16, int, double));
EXTERN_C int		CALLBACK c_sps_2 _DECLARE((PNTNUM, PRMNUM));
EXTERN_C int		CALLBACK c_spsw_2 _DECLARE((PNTNUM, PRMNUM));
EXTERN_C int		CALLBACK c_spv_2 _DECLARE((PNTNUM, PRMNUM, double));
EXTERN_C int		CALLBACK c_spvw_2 _DECLARE((PNTNUM, PRMNUM, double));
EXTERN_C int		CALLBACK c_stcupd _DECLARE((int, int));
EXTERN_C int		CALLBACK c_tmstrt_single _DECLARE((int, int, int));
EXTERN_C int		CALLBACK c_tmstrt_cycle _DECLARE((int, int, int));
EXTERN_C void		CALLBACK c_tmstop _DECLARE((int));
EXTERN_C void		CALLBACK c_trm04 _DECLARE((int2));
EXTERN_C void		CALLBACK c_trmtsk _DECLARE((int2));
EXTERN_C int		CALLBACK c_tstskb _DECLARE((int));
EXTERN_C int		CALLBACK c_unlock_dir _DECLARE((int));
EXTERN_C int		CALLBACK c_unlock_file _DECLARE((int, int));
EXTERN_C int		CALLBACK c_unlock_rec _DECLARE((int, int, int));
EXTERN_C void		CALLBACK c_upper _DECLARE((char*));
EXTERN_C int		CALLBACK c_wdon _DECLARE((int));
EXTERN_C int		CALLBACK c_wdstrt _DECLARE((int, int));
EXTERN_C int2		CALLBACK c_wttskb _DECLARE((int));
EXTERN_C int		CALLBACK isdbmodified _DECLARE((void));
static int		check _DECLARE((int));
EXTERN_C int		check_arg _DECLARE((char*));
EXTERN_C int		checktapedrv();
EXTERN_C int		chn_lock _DECLARE((int, int*));
EXTERN_C void		chn_unlock _DECLARE((int, int));
EXTERN_C void		chrint	_DECLARE((char*, short, short*, short*));
EXTERN_C void		cl  _DECLARE((short*, short*));
EXTERN_C void		cl4 _DECLARE((short*, long*));
EXTERN_C void		ClearScreen _DECLARE((void));
EXTERN_C int		close_ok _DECLARE((int*));

#ifdef NT
EXTERN_C void		closedir _DECLARE((HANDLE));
#endif

EXTERN_C int		cmdxmt _DECLARE((char*));
EXTERN_C void		cmpres _DECLARE((short*, short*, short*, short*));
EXTERN_C int		cmr _DECLARE((char*, int));
EXTERN_C int		cnt_tmout _DECLARE((unsigned int, char*, int));
EXTERN_C void		comerr _DECLARE((short*, short*, short*, short*));
EXTERN_C void		c_comerr _DECLARE((int, int, int, int));
EXTERN_C void		comerupd _DECLARE((struct rtutbl*, int, int, int, int));
EXTERN_C short		compar _DECLARE((short*, short*));
EXTERN_C int		hsc_compare   _DECLARE((const char*,int,const char*,int));
EXTERN_C int		hsc_compare_i _DECLARE((const char*,int,const char*,int));
static int			confirm _DECLARE((struct dictinfo*, struct mkeydesc*, char));
EXTERN_C int		convpath _DECLARE((char*));
EXTERN_C int		convpathex _DECLARE((const char* origPath, char* newPath, int newPathLength));
static long			count _DECLARE((int));
EXTERN_C uint2		crc _DECLARE((int, unsigned char *, int));
EXTERN_C unsigned short	crc16 _DECLARE((unsigned char*, int, unsigned short));
EXTERN_C short		crgtsk _DECLARE((char*, short, short*, short*, char*, short, short*));
EXTERN_C int		crgtskxmt _DECLARE((char*, short, short, short, char*, short));
EXTERN_C short		crtiot _DECLARE((short*, short*));
EXTERN_C void		crttsk _DECLARE((char*, short, short*, short*, short*, short*, short*));
EXTERN_C void		ctofstr _DECLARE((const char*, char*, int));
EXTERN_C int		cvpath _DECLARE((char*, short));
EXTERN_C short		cwd _DECLARE((char*, short, short*));
EXTERN_C int		d_sock _DECLARE((unsigned short, int));
EXTERN_C int		d_sock_range _DECLARE((unsigned short, unsigned short, int));
EXTERN_C int		dat_block_read _DECLARE((long, long, long, char*, unsigned long));
EXTERN_C int		dat_block_write _DECLARE((long, long, long, char*, unsigned long));
EXTERN_C int		dat_file_open _DECLARE((short));
EXTERN_C void		datclo _DECLARE((short*, short*));
EXTERN_C long		datclo4 _DECLARE((long*));
EXTERN_C long		datclo_force _DECLARE((int));
EXTERN_C void		datcre _DECLARE((short*, char*, short, short*, short*));
EXTERN_C long		datcre4 _DECLARE((long*, char*, short, long*));
EXTERN_C short		datcreate _DECLARE((char*, short, char*, short));
EXTERN_C void		datdel _DECLARE((short*, char*, short, short*));
EXTERN_C long		datdel4 _DECLARE((char*, short));
EXTERN_C void		date _DECLARE((long*));
EXTERN_C void		dateof _DECLARE((short*, short*));
EXTERN_C FILETIME	DateToFiletime _DECLARE((DATE));
EXTERN_C void		DateToHsctime _DECLARE((DATE*,HSCTIME*));
EXTERN_C void		datget _DECLARE((short*, char*, short, short*, short*));
EXTERN_C long		datget4 _DECLARE((long*, char*, short, long*));
EXTERN_C void		datini _DECLARE((void));
EXTERN_C void		datopn _DECLARE((short*, char*, short, unsigned short*, short*));
EXTERN_C int4		datopn4 _DECLARE((long*, char*, short, unsigned long*));
EXTERN_C void		datopr _DECLARE((short*, char*, short, short*, short*));
EXTERN_C long		datopr4 _DECLARE((long*, char*, short, long*));
EXTERN_C void		datrea _DECLARE((short*, long*, short*, short*));
EXTERN_C long		datrea4 _DECLARE((long*, long*, short*));
EXTERN_C void		datren _DECLARE((short*, short*, short*, short*));
EXTERN_C long		datren2 _DECLARE((long*, long*, short*, BOOL));
EXTERN_C long		datren4 _DECLARE((long*, long*, short*));
EXTERN_C void		datrew _DECLARE((short*, short*));
EXTERN_C long		datrew4 _DECLARE((long*));
EXTERN_C void		datrmv _DECLARE((short*, short*));
EXTERN_C long		datrmv4 _DECLARE((long*));
EXTERN_C void		datrnm _DECLARE((char*, short, char*, short, short*));
EXTERN_C void		datwri _DECLARE((short*, long*, short*, short*));
EXTERN_C long		datwri4 _DECLARE((long*, long*, short*));
EXTERN_C void		datwrn _DECLARE((short*, short*, short*, short*));
EXTERN_C void		datwrt _DECLARE((short*, long*, short*, short*));
EXTERN_C long		datwrt4 _DECLARE((long*, long*, short*));
EXTERN_C long		datxmt _DECLARE((long*, long*, long*, long*, short*, long*, long*));
EXTERN_C long		datxmtex _DECLARE((long*, long*, long*, long*, short*, long*, long*, long*));
EXTERN_C int		db _DECLARE((void));
EXTERN_C short		db_lock _DECLARE((short*, short*, short*, short*));
EXTERN_C short		db_lockint		_DECLARE((short*));
EXTERN_C short		db_lockt _DECLARE((short*, short*, short*));
EXTERN_C short		db_unlock _DECLARE((short*, short*, short*));
EXTERN_C int		dbloaded _DECLARE((void));
EXTERN_C short		dbghr _DECLARE((short*, short*, short*));
EXTERN_C int		defaultrelease _DECLARE((void));
EXTERN_C int		delcchr _DECLARE((char*, int, char, char));
EXTERN_C int		delchr _DECLARE((char*, int, char));
static int		deldefn _DECLARE((int));
static int		deleted _DECLARE((long));
static int		delfree _DECLARE((long));
EXTERN_C void		DeltaFiletimeToHsctime _DECLARE((FILETIME*, HSCTIME*));
EXTERN_C void		DeltaHsctimeToFiletime _DECLARE((HSCTIME*, FILETIME*));
EXTERN_C void		DeltaHsctimeToRawtm _DECLARE((HSCTIME*, int4*));
EXTERN_C void		DeltaRawtmToHsctime _DECLARE((int4*, HSCTIME*));
EXTERN_C long		deltm _DECLARE((HSCTIME*, HSCTIME*));
EXTERN_C LONGLONG	deltm2 _DECLARE((HSCTIME*, HSCTIME*, int2));
EXTERN_C short		cmptm _DECLARE((HSCTIME*, HSCTIME*));
EXTERN_C struct dir*	deltree _DECLARE((struct dir*));
EXTERN_C short		deltsk _DECLARE((short*));
EXTERN_C short		devfmt _DECLARE((char*, short, short*));
EXTERN_C struct devtbl*	devget_lnk _DECLARE((int));
static int		dexpand _DECLARE((void));
EXTERN_C long		dget _DECLARE((short*));
EXTERN_C int		dhlww _DECLARE((short*, short*, short*, short*, short*));
EXTERN_C int		dhsf _DECLARE((short*, short*, short*, short*, short*));
EXTERN_C long		dir_downgrade _DECLARE((long*, unsigned short*, long*));
EXTERN_C long		dir_read _DECLARE((long*, long*, long*, long*, short*, long*));
EXTERN_C long		dir_size _DECLARE((short*));
EXTERN_C long		dir_type _DECLARE((short*,long*));
EXTERN_C long		dir_upgrade _DECLARE((unsigned short*, long*, long*, long*, long*));
EXTERN_C long		dir_write _DECLARE((long*, long*, long*, long*, long*));
EXTERN_C int		dl_psdt _DECLARE((void));
EXTERN_C short		dlgtsk _DECLARE((char*, short, short*));
EXTERN_C int		dlgtskxmt _DECLARE((char*, short, short));
EXTERN_C int		dll_init _DECLARE((void*, int, int));
EXTERN_C int		dllmain _DECLARE((void*, int, int));
static int		do_aud _DECLARE((char*, char*, long));
EXTERN_C int		do_open _DECLARE((char*, int, int, short, short*, int*));
EXTERN_C void		DoubleToHsctime _DECLARE((double*, HSCTIME*));
EXTERN_C short		dps6now _DECLARE((char*, short));
EXTERN_C void		dput _DECLARE((short*, long*));
EXTERN_C void		dsanod _DECLARE((char*, short));
EXTERN_C void		dspalm _DECLARE((short*, short*, short*, long*, short*, short*, char*, short, short*, long*));
EXTERN_C short		dspatr _DECLARE((short*, short*, short*));
EXTERN_C void		dspchk _DECLARE((short*, short*, short*, long*, short*, char*, short, short*));
EXTERN_C void		dspind _DECLARE((short*, short*, short*, long*, short*, float*, float*, float*, float*, float*));
EXTERN_C short		dsply_lrn _DECLARE((short*));
EXTERN_C void		dspmsg _DECLARE((short*, short*, short*, long*, short*, short*, char*, short, short*));
EXTERN_C int		dspnamcmp _DECLARE((char*, int, char*, int));
EXTERN_C int		dspnamncmp _DECLARE((char*, int, char*, int, int));
EXTERN_C void		dsppag _DECLARE((short*,short*,char*,short));
EXTERN_C int		dsppath _DECLARE((void));
EXTERN_C void		dsppb _DECLARE((short*, short*, short*, long*, short*, char*, short));
EXTERN_C void		dspscl _DECLARE((short*, short*, short*, long*, short*, float*, float*, float*, short*));
EXTERN_C void		dsptxt _DECLARE((short*, short*, short*, long*, short*, char*, short));
EXTERN_C int4		dsupdate _DECLARE((int4, int4, int4, int4, int2 *));
EXTERN_C short		dtoasc _DECLARE((char*, short, short*, short*));
EXTERN_C short		dumpen _DECLARE((void));
EXTERN_C short		dvclrn _DECLARE((char*, short));
EXTERN_C short		eauout _DECLARE((char*, short));
EXTERN_C int        ehmfilexmt _DECLARE((int, int4, int4));
EXTERN_C int		ehmhstxmt _DECLARE((char*, int4));
EXTERN_C int		eouout _DECLARE((int, char*, short));
EXTERN_C void		epsnrm _DECLARE((short*, short*));
EXTERN_C short		equal _DECLARE((char*, short, char*, short));
EXTERN_C short		equal_i _DECLARE((char*, short, char*, short));
EXTERN_C void		errmsg _DECLARE((int, int,...));
EXTERN_C short		errout _DECLARE((char*, short));
EXTERN_C short		evarchrcv _DECLARE((int,int,char*));
EXTERN_C short		evarchxmt _DECLARE((int,int,char*));
EXTERN_C void		ex _DECLARE((short*, char*, short, short*, short*));
static int  		extract _DECLARE((char*, char*, char*, int));
EXTERN_C void		favg _DECLARE((float*, float*, float*));
EXTERN_C float		fclamp _DECLARE((float*, float*));
EXTERN_C float		fcpuse _DECLARE((short*));
EXTERN_C void		fdec _DECLARE((float*));
EXTERN_C float		fget _DECLARE((short*));
EXTERN_C DATE		FiletimeToDate _DECLARE((FILETIME));
EXTERN_C void		FiletimeToHsctime _DECLARE((FILETIME*, HSCTIME*));
EXTERN_C short		filinf _DECLARE((char*, short, char*, short));
EXTERN_C void		fill _DECLARE((char*, short, char*, short, short*));
EXTERN_C short		filrea _DECLARE((short*));
EXTERN_C short		filwrt _DECLARE((short*, short*));
EXTERN_C int        filxmt _DECLARE((int, int, int));
EXTERN_C void		finc _DECLARE((float*));
EXTERN_C long		find_eol_rm_esc _DECLARE((char*, int, char*, short*));
EXTERN_C void		FloatToHsctime _DECLARE((float, HSCTIME*));
EXTERN_C int		findudcpar _DECLARE((int*, int*, int*, int*, int*));
static int		fixkey _DECLARE((void));
EXTERN_C void		flush_chn _DECLARE((int));
EXTERN_C int		forktsk _DECLARE((char*, int, int, char**, int));
EXTERN_C void		fput _DECLARE((short*, float*));
EXTERN_C int		freestorage _DECLARE((char**, unsigned int*));
static int		frkey _DECLARE((char**, char**, int, int));
EXTERN_C void		fromieee _DECLARE((short*, short*));
EXTERN_C void       fromieeedouble _DECLARE((short*, short*));
EXTERN_C void		fromlong		_DECLARE((short*, short*));
EXTERN_C short		fssize _DECLARE((char*, short, float*, float*));
EXTERN_C short		ftoasc _DECLARE((char*, short, short*, short*, short*));
EXTERN_C char*		ftocstr _DECLARE((char*, int, char*, int));
EXTERN_C void		ftofstr _DECLARE((char *, int, char *, int));
EXTERN_C int		g_par _DECLARE((int, int));
EXTERN_C char*		gbattach _DECLARE((int, char*, int));
EXTERN_C int		gbattach_nt _DECLARE((int));
EXTERN_C int		gbunattach_nt _DECLARE((void));
EXTERN_C int		gbld _DECLARE((void));
EXTERN_C void		gbload _DECLARE((short*));
EXTERN_C void		gbunload _DECLARE((short*));
EXTERN_C void		gbunload_nt _DECLARE((short*));
EXTERN_C void		gbload_nt _DECLARE((short*, int));
EXTERN_C int		get_defsem_semid _DECLARE((void));
EXTERN_C int		get_defsem_semno _DECLARE((short));
EXTERN_C int4		get_TraceId _DECLARE((void));;
EXTERN_C int4		new_TraceId _DECLARE((int,int));;
EXTERN_C void		set_TraceId _DECLARE((int4));
EXTERN_C int		get_file_no _DECLARE((char*));
EXTERN_C int		get_free_semnum _DECLARE((void));
EXTERN_C int		get_lic_size _DECLARE((int, int, int*));
EXTERN_C int		get_rec_len _DECLARE((char*, int, unsigned long*));
static struct keydesc*	getblank _DECLARE((void));
EXTERN_C void		getbyt _DECLARE((short*, short*, short*));
EXTERN_C void		getcom _DECLARE((short*, long*, short*, short*));
EXTERN_C short		getdat  _DECLARE((short*, short*, short*, short*, short*, unsigned short*, unsigned short*, short*));
EXTERN_C long		getdat4 _DECLARE((long*, long*, long*, long*, long*, long*, unsigned short*, long*));
EXTERN_C int		getdbkey _DECLARE((void));
EXTERN_C void		getfld _DECLARE((char*, short, char*, short, short*));
EXTERN_C void       getfld2 _DECLARE((char*, short, char*, short, short*, short*));

#ifdef NT
EXTERN_C short		getgid _DECLARE((void));
#endif

EXTERN_C struct hostent* gethost _DECLARE((char*));
EXTERN_C void		gethst _DECLARE((short*, short*, float*, short*, short*, PNTNUM*, char*, short, long*, short*));
EXTERN_C void		gethstpar _DECLARE((short*, short*, float*, short*, short*, PNTNUM*, PRMNUM*, char*, short, long*, short*));
EXTERN_C void		gethstpar1 _DECLARE((short*, short*, float*, short*, short*, PNTNUM*, PRMNUM*, char*, short, long*, short*, long*, long*, short*));
EXTERN_C short		getlrn _DECLARE((void));
EXTERN_C void		getFullPriority _DECLARE((int4, int4*, int4*));
EXTERN_C void		GetLocDateTime _DECLARE((HSCTIME* time, int2 bias, char* szDateTime, int2 strlen, int2 includeTime, int2 includeUS, int2 includeMS));
EXTERN_C void		GetLocDateTimeEx _DECLARE((HSCTIME* time, int2 bias, char* szDateTime, int2 strlen, int2 datetimeFunction, int2 includeMS, int2 includeUS, int2 showAMPM, int2* datetimeSeparator));
EXTERN_C void		GetMilliSecsFromHsctime _DECLARE((HSCTIME*, int2*));
EXTERN_C void		GetMicroSecsFromHsctime _DECLARE((HSCTIME*, int4*));
EXTERN_C void		GetDatePartFromHsctime _DECLARE((HSCTIME* pHscTime, HSCTIME* pHscDate));
EXTERN_C void		GetTimePartFromHsctime _DECLARE((HSCTIME* pHscTime, HSCTIME* pHscDate));
EXTERN_C int2 FORTCALL  GETPAG _DECLARE((int4*, int4*, int4*, int4*, int4*, char*, int2));
EXTERN_C short		getprm _DECLARE((short*, short*, short*, short*));
EXTERN_C short		getreq _DECLARE((short*));
EXTERN_C short		getrid _DECLARE((short*));
EXTERN_C int2		GetServerAPIerrno _DECLARE((void));
EXTERN_C int		getstorage _DECLARE((char**, unsigned int*, unsigned int));
EXTERN_C void		gettm  _DECLARE((HSCTIME*));
EXTERN_C int		gettmz _DECLARE((const HSCTIME*));
EXTERN_C int		gettmz2 _DECLARE((HSCTIME*, HSC_TIMEZONEDATA*,int));
EXTERN_C int		hsc_DoesThreadExist _DECLARE((int pid, int tid));
EXTERN_C int		hsc_getval_asci _DECLARE((PNTNUM, PRMNUM, char*, int));
EXTERN_C int		hsc_getval_hist _DECLARE((PNTNUM, PRMNUM, int, float*));
EXTERN_C int		hsc_getval_numb _DECLARE((PNTNUM, PRMNUM, float*));
EXTERN_C uint2		hsc_pas _DECLARE((uint2 rtu, uint2 address));
EXTERN_C uint2		hsc_pasw _DECLARE((uint2 rtu, uint2 address));
EXTERN_C uint2		hsc_sas _DECLARE((uint2 rtu, uint2 address));
EXTERN_C uint2		hsc_sasw _DECLARE((uint2 rtu, uint2 address));
EXTERN_C uint2		hsc_pds _DECLARE((uint2 rtu));
EXTERN_C uint2		hsc_pdsw _DECLARE((uint2 rtu));
EXTERN_C uint2		hsc_sds _DECLARE((uint2 rtu));
EXTERN_C uint2		hsc_sdsw _DECLARE((uint2 rtu));
EXTERN_C uint2		hsc_pps _DECLARE((PNTNUM, PRMNUM));
EXTERN_C uint2		hsc_ppsw _DECLARE((PNTNUM, PRMNUM));
EXTERN_C uint2		hsc_sps _DECLARE((PNTNUM, PRMNUM));
EXTERN_C uint2		hsc_spsw _DECLARE((PNTNUM, PRMNUM));
EXTERN_C uint2		hsc_ppas _DECLARE((PNTNUM, PRMNUM));
EXTERN_C uint2		hsc_ppasw _DECLARE((PNTNUM, PRMNUM));
EXTERN_C uint2		hsc_ppov _DECLARE((PNTNUM, PRMNUM));
EXTERN_C uint2		hsc_ppovw _DECLARE((PNTNUM, PRMNUM));
EXTERN_C uint2		hsc_ppv _DECLARE((PNTNUM, PRMNUM, double));
EXTERN_C uint2		hsc_ppvw _DECLARE((PNTNUM, PRMNUM, double));
EXTERN_C uint2		hsc_spv _DECLARE((PNTNUM, PRMNUM, double));
EXTERN_C uint2		hsc_spvw _DECLARE((PNTNUM, PRMNUM, double));
EXTERN_C uint2		hsc_ppve _DECLARE((PNTNUM, PRMNUM, double, int));
EXTERN_C uint2		hsc_ppvew _DECLARE((PNTNUM, PRMNUM, double, int));
EXTERN_C uint2		hsc_spve _DECLARE((PNTNUM, PRMNUM, double, int));
EXTERN_C uint2		hsc_spvew _DECLARE((PNTNUM, PRMNUM, double, int));
EXTERN_C int2		hsc_rtursptim _DECLARE((int2 rtu));
EXTERN_C void		getvol _DECLARE((char*, char*, short*, long*, long*));
EXTERN_C short		gifil _DECLARE((char*, short, short*, short*));
EXTERN_C int4		gpmain _DECLARE((int4*, int4*, int4*, int4*, int2*, int4*, int4*, int4*, int4*, int4*));
EXTERN_C int4 FORTCALL  GPMAIN _DECLARE((int4*, int4*, int4*, int4*, int2*, int4*, int4*, int4*, int4*, int4*));
EXTERN_C void		gregor _DECLARE((long*, short*));
EXTERN_C int 		hsc_AccessConfigLogin _DECLARE((char *, char *));
EXTERN_C HRESULT	hsc_add_comment _DECLARE((int2 nCrt, uint2 nCon, NOTIFCOOKIE nPublisherCookie, NOTIFCOOKIE nCookie, int8 nTransId, char*, char*, char*, BSTR, BOOL, __int64*, int*, BSTR*, long*, short*));
EXTERN_C HRESULT	hsc_add_link _DECLARE((short, long, __int64, char*, char*, char*, BSTR, BSTR));
EXTERN_C void		update_flags_for_dvm_alarm _DECLARE((__int64));
EXTERN_C int2		hsc_AdjustZone _DECLARE((int2 *, int2 *));
EXTERN_C int		hsc_area_desc _DECLARE((int, char*, int));
EXTERN_C int		hsc_area_name _DECLARE((int, char*, int));
EXTERN_C int		hsc_area_number _DECLARE((const char*));
EXTERN_C int		hsc_asset_to_area_number _DECLARE((const char*));
EXTERN_C int		hsc_callup_display _DECLARE((int2, char*));
EXTERN_C uint4		hsc_createpath _DECLARE((const char*));
EXTERN_C int		hsc_dsply_cancel _DECLARE((int, int));
EXTERN_C int		hsc_dsply_set_scrollbar _DECLARE((int, int, int, int, int, int));
EXTERN_C int		hsc_dsply_get_tskdfd  _DECLARE((int, int, int, int4*, int, int2*));
EXTERN_C int		hsc_dsply_set_tskdfd  _DECLARE((int, int, int, int4, int2, int2, int2, int2));
EXTERN_C int		hsc_dsply_get_dfdtbl  _DECLARE((int, int, int*, int2**));
EXTERN_C int 		hsc_dsply_IPSdata     _DECLARE((int,int,uchar[],int));
EXTERN_C int 		hsc_dsply_IPSdata_DLE _DECLARE((int,int,uchar[],int));
EXTERN_C PNTNUM		hsc_alarm2point _DECLARE((int4 *));
EXTERN_C PNTNUM		hsc_event2point _DECLARE((struct almevtfil *));
EXTERN_C int		hsc_nav_event_assoc_display _DECLARE((int2, struct almevtfil *));
EXTERN_C int		hsc_nav_event_cardholder_detail _DECLARE((int2, struct almevtfil *));
EXTERN_C HRESULT STDCALL HSC_CoInitialize _DECLARE((void*));
EXTERN_C HRESULT STDCALL HSC_CoInitializeEx _DECLARE((void*, DWORD));
EXTERN_C void    STDCALL HSC_CoUninitialize _DECLARE((void));
EXTERN_C int		hsc_nav_event_detail_display _DECLARE((int2, struct almevtfil *));
EXTERN_C int		hsc_nav_point_detail_display _DECLARE((int2, PNTNUM));
EXTERN_C int		hsc_nav_tag_detail_display _DECLARE((int2, char*, int));
EXTERN_C int		hsc_nav_point_assoc_display _DECLARE((int2, PNTNUM));
EXTERN_C int		hsc_delete_rm _DECLARE((int));
EXTERN_C int2		hsc_DoubleCompare _DECLARE((double, double, int));
EXTERN_C int		hsc_config_rm _DECLARE((int, int, int));
EXTERN_C int		hsc_convert_to_valid_area _DECLARE((int area));
EXTERN_C int		hsc_ErrorToQuality _DECLARE((int code));
EXTERN_C int		hsc_QualityToError _DECLARE((int quality));
EXTERN_C int		hsc_GdaErrorToxxStatus _DECLARE((GDAERR code));
EXTERN_C int		hsc_GdaErrorToQuality _DECLARE((GDAERR code));
EXTERN_C int		hsc_GdaErrorToError _DECLARE((GDAERR* pCode));
EXTERN_C BOOL		hsc_IsQualityStale _DECLARE((uint2 nRtu, WORD nQuality));
EXTERN_C int2		hsc_FloatCompare _DECLARE((float, float, int));
EXTERN_C int		hsc_FormProgIdList(int iType, char* szServerName, int timeout, enumlist** ppList);
EXTERN_C int		hsc_ResolveOPCProgID(WCHAR *wszProgId, WCHAR *wszServerName, LPCLSID pClsid);
EXTERN_C int		hsc_OPCenum_OnOPCServerNameChange(int2 recnum, int2 wordnum);
EXTERN_C int2		hsc_GetAcrnym _DECLARE(( struct Location *, char *));
EXTERN_C int2		hsc_GetCrtUser _DECLARE(( int , char * ));
EXTERN_C HRESULT	hsc_get_comments _DECLARE((int2 nCrt, uint2 nCon, NOTIFCOOKIE nPublisherCookie, int8 nTransId, __int64*, int*, BSTR*, long*, short*));
EXTERN_C char*		hsc_getwsaerrtext _DECLARE((unsigned int));

/* history APIs */
EXTERN_C int		hsc_history  _DECLARE((int, int, int, double, int, int, PNTNUM*, PRMNUM*, char*, HSCTIME*, int2*, float*, int4*));
EXTERN_C int		hsc_history1 _DECLARE((int, int, int, double, int, int, PNTNUM*, PRMNUM*, char*, HSCTIME*, int2*, float*, int4*));
EXTERN_C int		hsc_history2 _DECLARE((int, int, HSCTIME*, int, int, PNTNUM*, PRMNUM*, char*, HSCTIME*, int2*, float*, int4*));
EXTERN_C int		hsc_history2_offset _DECLARE((int, int, int, int, int, PNTNUM*, PRMNUM*, char*, HSCTIME*, int2*, float*, int4*));
EXTERN_C int		hsc_history4 _DECLARE((int4, int4, HSCTIME*, HSCTIME*, int4, int4, PNTNUM*, PRMNUM*, IDXNUM*, HSTARRAY**));

/* history helper routines */
EXTERN_C HRESULT	hsc_InitialiseHstArray _DECLARE((HSTARRAY**, int, int));
EXTERN_C HRESULT    hsc_ReallocHstArrayEx _DECLARE((HSTARRAY**, int, int, int));
EXTERN_C HRESULT	hsc_ReallocHstArray _DECLARE((HSTARRAY*, int));
EXTERN_C void		hsc_DestroyHstArray _DECLARE((HSTARRAY**, int));
EXTERN_C HSTARRAY*	hsc_CopyHstArray _DECLARE((HSTARRAY*, HSTARRAY*, int, int));
EXTERN_C HRESULT	hsc_CopyHstValue _DECLARE((HSTVALUE*, HSTVALUE*));
EXTERN_C char*		hsc_HstValueToString _DECLARE((char*, HSTVALUE*, size_t));
EXTERN_C void		hsc_PrintHstArrayToFile _DECLARE((HSTARRAY*, int));
EXTERN_C HSTVALUE*	hsc_SubtractHstValues _DECLARE((short, HSTVALUE*, HSTVALUE*, HSTVALUE*));
EXTERN_C HSTVALUE*	hsc_AddHstValues _DECLARE((short, HSTVALUE*, HSTVALUE*, HSTVALUE*));
EXTERN_C HSTVALUE*	hsc_HstValueMultiplyBy _DECLARE((HSTVALUE*, double, HSTVALUE*));
EXTERN_C void		hsc_FreeHistoryValueContents _DECLARE((HSTVALUE*));
EXTERN_C HRESULT	hsc_ReverseHstArray _DECLARE((HSTARRAY**, int));
EXTERN_C int		hsc_InterpolateHistory _DECLARE((int, HSCTIME*, HSCTIME*, int, int, int, HSTARRAY*, HSTARRAY**));
EXTERN_C HRESULT	hsc_InterpolateHstValue _DECLARE((short, HSTVALUE*, HSTVALUE*, double, HSTVALUE*));
EXTERN_C HRESULT	hsc_GetRequestTimes _DECLARE((HSCTIME*, HSCTIME*, int, int, int, int, double, int*, HSCTIME*, HSCTIME*));
EXTERN_C HRESULT	hsc_HstValueToFloat _DECLARE((HSTVALUE*, float*));
EXTERN_C HRESULT	hsc_MergeHstArrays _DECLARE((int, HSTARRAY*, HSTARRAY**, int));
EXTERN_C char*		hsc_TimeAsString _DECLARE((HSCTIME*, char*, size_t));
EXTERN_C HRESULT	hsc_TrimBoundingValues _DECLARE((HSCTIME*, HSCTIME*, int, int, HSTARRAY**));

/* HAT routines */
EXTERN_C BOOL		hsc_hat_pointfind _DECLARE((int, PNTNUM, PRMNUM, BOOL, BOOL, int*));
EXTERN_C int		hsc_hat_pointadd _DECLARE((int, PNTNUM, PRMNUM, int, int, int*));

EXTERN_C ULONGLONG	hsc_HSCTimeToLargeInt _DECLARE((HSCTIME* TimeStamp));
EXTERN_C BOOL		hsc_GetNotifSourceEntityName _DECLARE((PNTNUM nPoint, char *szSource, char *szSourceEntityName, int2 nSourceEntityNameLen));
EXTERN_C BOOL		hsc_GetNotifLocationTagName  _DECLARE((PNTNUM nPoint, PNTNUM nParent, char *szLocationTagName, int2 nLocationTagNameLen));
EXTERN_C BOOL		hsc_GetNotifLocationFullName _DECLARE((PNTNUM nPoint, PNTNUM nParent, char *szLocationFullName, int2 nLocationFullNameLen));
EXTERN_C BOOL		hsc_InsertSourceEntityName _DECLARE((struct almevtfil *pAlmEvtFil, PNTNUM nPoint));
EXTERN_C BOOL		hsc_InsertLocation _DECLARE((struct almevtfil *pAlmEvtFil, PNTNUM nPoint, PNTNUM nParent));
EXTERN_C BOOL		hsc_InsertEquipmentDetails _DECLARE((struct almevtfil *pAlmEvtFil, PNTNUM nPoint));
EXTERN_C int2		hsc_isLocalHost _DECLARE((int2));
EXTERN_C int		hsc_IsUrl _DECLARE((char*));
EXTERN_C int		hsc_IsHmiUrl _DECLARE((char*));
EXTERN_C int		hsc_IsName _DECLARE((char*, int));
EXTERN_C int		hsc_IsLocationWritable _DECLARE((short, short, short, short, short, short));
EXTERN_C BOOL		hsc_isValidHMIConnection _DECLARE((int4, char*));
EXTERN_C BOOL		hsc_isValidHMIConnectionBstr _DECLARE((int4, BSTR));
EXTERN_C int		hsc_isValidName _DECLARE((char*, int));
EXTERN_C int		hsc_isValidPointName _DECLARE((char*, int));
EXTERN_C int		hsc_makeValidPointName(char* pName, char cRep, int NameLen);
EXTERN_C int		hsc_isValidParamName _DECLARE((PNTNUM, char*, int));
EXTERN_C int		hsc_isValidParamNameGeneric _DECLARE((char*, int));
EXTERN_C int		hsc_isValidEntityName _DECLARE((char*, int, uint2));
EXTERN_C HSCTIME	hsc_LargeIntToHSCTime _DECLARE((ULONGLONG TimeInt));
EXTERN_C uint2		hsc_pcs _DECLARE((PNTNUM, PRMNUM));
EXTERN_C uint2		hsc_pcsw _DECLARE((PNTNUM, PRMNUM));
EXTERN_C uint2		hsc_pcps _DECLARE((PNTNUM, PRMNUM));
EXTERN_C uint2		hsc_pcpsw _DECLARE((PNTNUM, PRMNUM));
EXTERN_C int		hsc_procexists _DECLARE((char*));
EXTERN_C BOOL STDCALL   hsc_redirectlog_init _DECLARE(());
EXTERN_C void STDCALL   hsc_redirectlog_close _DECLARE(());
EXTERN_C void		hsc_refresh_crts _DECLARE((int2*));
EXTERN_C int		hsc_release _DECLARE((int));
EXTERN_C int2		hsc_get_system_area_number _DECLARE(());
EXTERN_C int		hsc_q_getnextitemsize _DECLARE((int, int*));
EXTERN_C int		hsc_q_getnumitems _DECLARE((int, int*));
EXTERN_C int		hsc_q_getusage _DECLARE((int));
EXTERN_C int		hsc_q_init _DECLARE((int, int, int));
EXTERN_C int		hsc_q_open _DECLARE((int, int, int));
EXTERN_C int		hsc_q_openex _DECLARE((int, int, int, int));
EXTERN_C int		hsc_q_read _DECLARE((int, char*, int));
EXTERN_C void		hsc_q_remove _DECLARE((int));
EXTERN_C int		hsc_q_reset _DECLARE((int, int, int));
EXTERN_C int		hsc_q_write _DECLARE((int, char*, int));
EXTERN_C uint2		hsc_scs _DECLARE((PNTNUM, PRMNUM));
EXTERN_C uint2		hsc_scsw _DECLARE((PNTNUM, PRMNUM));
EXTERN_C uint2		hsc_scps _DECLARE((PNTNUM, PRMNUM));
EXTERN_C uint2		hsc_scpsw _DECLARE((PNTNUM, PRMNUM));
EXTERN_C void		hsc_SetSecurityLevel4CRT _DECLARE((int2, int2, int2));
EXTERN_C BOOL		hsc_Server_LoadParanoidEnv _DECLARE((void));
EXTERN_C int 		hsc_Set_CMS_Access _DECLARE((void));
EXTERN_C void		hsc_set_locale _DECLARE((void));
EXTERN_C BOOL		hsc_SetPrivilege _DECLARE((HANDLE, char*, BOOL));
EXTERN_C int2		hsc_sort_areas _DECLARE((void));
EXTERN_C void		hsc_Sound_Audible_By_Area _DECLARE((int2, int2, int2, HSCTIME));
EXTERN_C void		hsc_Silence_Audible_By_Crt _DECLARE((int));
EXTERN_C void		hsc_Silence_Audible_All _DECLARE((void));
EXTERN_C void		hsc_Silence_Audible_All_From_Below _DECLARE((void));
EXTERN_C void		hsc_Silence_Audible_All_From_NotifSync _DECLARE((HSCTIME));
EXTERN_C void		hsc_Silence_Audible_All_By_Area _DECLARE((int2));
EXTERN_C void		hsc_silence_crt _DECLARE((int2));
EXTERN_C int        hsc_station_data_quality _DECLARE((PNTNUM,PRMNUM,GDAERR,int2,int4,BOOL,WORD*,DWORD*));
EXTERN_C int        hsc_station_data_quality_ex _DECLARE((int2,int2,int4,BOOL,BOOL,GDAERR,WORD*,DWORD*));
EXTERN_C int		hsc_task_ident _DECLARE((int,int,char*,int));
EXTERN_C int		hsc_my_task_ident _DECLARE((char*,int));
EXTERN_C void 		hsc_timer_begin _DECLARE((uint4*));
EXTERN_C int 		hsc_timer_end   _DECLARE((uint4*, uint4));
EXTERN_C int 		hsc_timer_diff  _DECLARE((uint4*,uint4*));
EXTERN_C int		hsc_uselog _DECLARE((void));
EXTERN_C int		hsc_dont_uselog _DECLARE((void));
EXTERN_C int2		hsc_min_since_midnight _DECLARE((void));
EXTERN_C int		hsc_validateRaiseStep _DECLARE((void));
EXTERN_C void		hsc_FormatUnixErrMsg _DECLARE((int errcode, char *out_msg, int bufsize));
EXTERN_C void		HsctimeToDate _DECLARE((HSCTIME*,DATE*));
EXTERN_C void		HsctimeToDateEx _DECLARE((HSCTIME*, int2, DATE*));
EXTERN_C void		HsctimeToFiletime _DECLARE((const HSCTIME*, FILETIME*));
EXTERN_C void		HsctimeToLocalHsctime _DECLARE((HSCTIME*, HSCTIME*));
EXTERN_C void		HsctimeAndBiasToLocalHsctime _DECLARE((HSCTIME*, int2, HSCTIME*));
EXTERN_C void		HsctimeToMilliseconds _DECLARE((HSCTIME*, double*));
EXTERN_C void		HsctimeToRawtm _DECLARE((HSCTIME*, int4*));
EXTERN_C void		HsctimeToSeconds _DECLARE((HSCTIME*, double*));
EXTERN_C void		HsctimeToInt8 _DECLARE((HSCTIME*, int8*));
EXTERN_C uint8		HsctimeToUint8 _DECLARE((HSCTIME));
EXTERN_C void		HsctimeToFloat _DECLARE((HSCTIME*, float*));
EXTERN_C void		HsctimeToDouble _DECLARE((HSCTIME*, double*));
EXTERN_C void		hstavg _DECLARE((short*, short*, long*, long*));
EXTERN_C void		hstclr _DECLARE((short*, long*));
EXTERN_C void		hstsetbad _DECLARE((short*, long*));
EXTERN_C void		hstclr2 _DECLARE((short*, long*, short));
EXTERN_C short		hstxmt _DECLARE((short*, short*, long*));
EXTERN_C short		htoasc _DECLARE((char*, short, short*, short*));
EXTERN_C int2		i2add _DECLARE((short*, short));
EXTERN_C int2		i2dec _DECLARE((short*));
EXTERN_C int2		i2inc _DECLARE((short*));
EXTERN_C int2		i2set _DECLARE((short*, short));
EXTERN_C int4		i4add _DECLARE((long*, long));
EXTERN_C int4		i4inc _DECLARE((long*));
EXTERN_C int4		i4dec _DECLARE((long*));
EXTERN_C int4		i4set _DECLARE((long*, long));
EXTERN_C int		i6add _DECLARE((long*, long*));
EXTERN_C int		i6sub _DECLARE((long*, long*));
EXTERN_C void		ialpha _DECLARE((short*, short*));
EXTERN_C unsigned long	iandx _DECLARE((unsigned short*, unsigned short*));
EXTERN_C long		ibclrx _DECLARE((unsigned short*, unsigned short*));
EXTERN_C unsigned long	ibits _DECLARE((unsigned long*, unsigned long*, unsigned long*));
EXTERN_C short		ibitsx _DECLARE((unsigned short*, unsigned short*, unsigned short*));
EXTERN_C unsigned short c_ibitsx _DECLARE((unsigned short, unsigned long, unsigned long));
EXTERN_C long		ibsetx _DECLARE((unsigned short*, unsigned short*));
EXTERN_C long		idbl _DECLARE((short*));
EXTERN_C long		ieorx _DECLARE((short*, short*));
EXTERN_C short		iequal _DECLARE((short*, short*, short*));
static int  		iexpand _DECLARE((long));
EXTERN_C void		ifill _DECLARE((short*, short*, short*));
static int  		inhere _DECLARE((char*));
EXTERN_C double		infdouble _DECLARE((void));
EXTERN_C float		inffloat _DECLARE((void));
EXTERN_C void		init_timezonedata _DECLARE((HSC_TIMEZONEDATA*));
EXTERN_C int		inschr _DECLARE((char*, int, char*, int, char, int));
EXTERN_C void		Int8ToHsctime _DECLARE((int8*, HSCTIME*));
EXTERN_C HSCTIME	Uint8ToHsctime _DECLARE((uint8));
EXTERN_C void		intchr _DECLARE((char*, short, short*, short*));
EXTERN_C void		interupt _DECLARE((int));
EXTERN_C short		intflg _DECLARE((int));
EXTERN_C void		inttm _DECLARE((HSCTIME*, short*, float*));
EXTERN_C void		inttm2 _DECLARE((HSCTIME*,int2*,float*,HSCTIME*));
EXTERN_C void		inttm3 _DECLARE((HSCTIME*, int2*, double*));
EXTERN_C void		inttm1m _DECLARE((HSCTIME*, short*, uint4*));
EXTERN_C void		inttm2m _DECLARE((HSCTIME*, short*, uint4*, HSCTIME*));
EXTERN_C void		inttm3m _DECLARE((HSCTIME*, short*, double*));
EXTERN_C int2		inttoip _DECLARE((int4, char*));
EXTERN_C int		ioctl _DECLARE((int, int, ...));
EXTERN_C long		iorx _DECLARE((short*, short*));
EXTERN_C int		CALLBACK IPS_chart_normalise _DECLARE((float *, int *, double, double, int));
EXTERN_C int		CALLBACK IPS_chart_set_data _DECLARE((int, int, int, int, int, int *));
EXTERN_C int		CALLBACK IPS_chart_set_real_x_axis _DECLARE((int, int, int, double, double));
EXTERN_C int		CALLBACK IPS_chart_set_real_y_axis _DECLARE((int, int, int, double, double));
EXTERN_C int		CALLBACK IPS_get_object_id _DECLARE((int, int, char *, int *));
EXTERN_C int		CALLBACK IPS_object_set_attribute _DECLARE((int, int, int, char *, char *));
EXTERN_C int2		iptoint _DECLARE((char*, int2, int2*, int4*));
EXTERN_C unsigned short	irot _DECLARE((unsigned short*, short*));
EXTERN_C unsigned long	irot4 _DECLARE((unsigned long*, short*));
EXTERN_C int		hsc_isblank _DECLARE((char *str, int2 len));
EXTERN_C unsigned short	ishftx _DECLARE((unsigned short*, short*));
EXTERN_C int		isinfdouble _DECLARE((double*));
EXTERN_C int		isinffloat _DECLARE((float*));
EXTERN_C int		isnandouble _DECLARE((double*));
EXTERN_C int		isnanfloat _DECLARE((float*));
EXTERN_C int		ispntalarm _DECLARE((int));
EXTERN_C int		isScanTask _DECLARE((int));
EXTERN_C short		itoasc _DECLARE((char*, short, short*, short*));
EXTERN_C char*		itos _DECLARE((int));
EXTERN_C void		iupper _DECLARE((short*, short*));
EXTERN_C void		jbclr  _DECLARE((unsigned short*, int));
EXTERN_C unsigned short	jbits  _DECLARE((unsigned short*, int, int));
EXTERN_C unsigned long	j4bits _DECLARE((unsigned short*, int, int));
EXTERN_C void		jbset  _DECLARE((unsigned short*, int));
EXTERN_C int		jbtest _DECLARE((unsigned short*, int));
EXTERN_C unsigned short	jbyte _DECLARE((unsigned short*, short*));
EXTERN_C int        mvjbits _DECLARE((unsigned short*, int, int, unsigned short*, int));
EXTERN_C int        mvxbits _DECLARE((unsigned short*, int, int, unsigned short*, int));
EXTERN_C short		julian _DECLARE((long*));
EXTERN_C int            jultm _DECLARE((HSCTIME*, short*, float*));
EXTERN_C int            jultm2 _DECLARE((HSCTIME*, short*, double*));
EXTERN_C DATE		JulianToDate _DECLARE((int, float));
EXTERN_C short		keepalive _DECLARE((void));
static int  		keycomp _DECLARE((char*, char*, int, int));
EXTERN_C void		keydel _DECLARE((char*, short, char*, short, char*, short, short*));
EXTERN_C void		keyrea _DECLARE((char*, short, char*, short, char*, short, short*));
EXTERN_C int		keystore _DECLARE((char*, char*, int, struct keydesc*));
EXTERN_C void		keywrt _DECLARE((char*, short, char*, short, char*, short, short*));
EXTERN_C void		kilintr _DECLARE((void));
EXTERN_C void		killintr _DECLARE((void));
EXTERN_C void		killtsk _DECLARE((struct trbtbl*));
EXTERN_C void		killx _DECLARE((short*));
EXTERN_C short		kiltsk _DECLARE((short*));
static int  		lastkey _DECLARE((char*));
EXTERN_C int		lfn2file _DECLARE((int));
EXTERN_C short		lfnok _DECLARE((short*));
EXTERN_C void		lftjst _DECLARE((char*, short, short*));
EXTERN_C int2		licencechk _DECLARE((short, unsigned short*));
EXTERN_C uint4		licencechk_ex _DECLARE((uint4, uint4*));
EXTERN_C void		linrpt _DECLARE((short*, short*, short*, short*, short*, short*, short*));
EXTERN_C int        linkname _DECLARE((char*, int, int, int, int));
EXTERN_C short		lnknok _DECLARE((void));
EXTERN_C void		LocalHsctimeToHsctime _DECLARE((HSCTIME*, HSCTIME*));
EXTERN_C int        localname _DECLARE((char*, int));
#ifdef NT
EXTERN_C void		LogMessage  _DECLARE((int, int, int, const char *, const char *, const char *,int		,const char *, ...));
EXTERN_C void		LogMessageV _DECLARE((int, int, int, const char *, const char *, const char *,int		,const char *, va_list args));
EXTERN_C void		LogDebugMsg _DECLARE((int, int, int, const char *, const char *, const char *,int		,const char *, ...));
#endif
EXTERN_C char*		lower _DECLARE((char*));
EXTERN_C void		lowercase _DECLARE((char*));
EXTERN_C unsigned char	lrc8 _DECLARE((unsigned char*, int));
EXTERN_C short		lrnok _DECLARE((short*));
EXTERN_C BOOL		MatchAccessRights _DECLARE((DWORD, int));
EXTERN_C BOOL		MatchDataType _DECLARE((VARTYPE, int, int));
EXTERN_C BOOL		MatchStringFilter _DECLARE((LPCWSTR, WCHAR *));
static int  		makekey _DECLARE((char*, char*));
static int  		man_up _DECLARE((char*));
EXTERN_C int4		max_def_utbnum _DECLARE((short*));
EXTERN_C int4		max_def_utbsiz _DECLARE((short*));
EXTERN_C int4		max_def_utbtyp _DECLARE((short*));
EXTERN_C int4		max_lic_acc _DECLARE((short*));
EXTERN_C int4		max_lic_acs _DECLARE((void));
EXTERN_C int4		max_lic_alg _DECLARE((short*));
EXTERN_C int4		max_lic_ana _DECLARE((short*));
EXTERN_C short		max_lic_arc _DECLARE((short*));
EXTERN_C int4		max_lic_chn _DECLARE((short*));
EXTERN_C int4		max_lic_crd _DECLARE((short*));
EXTERN_C int4		max_lic_dly _DECLARE((short*));
EXTERN_C int4		max_lic_dsp _DECLARE((short*));
EXTERN_C int4		max_lic_evt _DECLARE((short*));
EXTERN_C int4		max_lic_exc _DECLARE((short*));
EXTERN_C int4		max_lic_ext _DECLARE((short*));
EXTERN_C int4		max_lic_fst _DECLARE((short*));
EXTERN_C int4		max_lic_ggl _DECLARE((short*));
EXTERN_C int4		max_lic_grp _DECLARE((short*));
EXTERN_C int4		max_lic_hst _DECLARE((short*, short*));
EXTERN_C int4		max_lic_lacgrp _DECLARE((short*));
EXTERN_C int4		max_lic_lpt _DECLARE((short*));
EXTERN_C int4		max_lic_opr _DECLARE((short*));
EXTERN_C long		max_lic_pnt _DECLARE((void));
EXTERN_C int4		max_lic_rcp _DECLARE((short*));
EXTERN_C int4		max_lic_rpt _DECLARE((short*));
EXTERN_C int4		max_lic_rsp _DECLARE((short*));
EXTERN_C int4		max_lic_rtu _DECLARE((short*));
EXTERN_C int4		max_lic_sdl _DECLARE((short*));
EXTERN_C int4		max_lic_sha _DECLARE((short*));
EXTERN_C int4		max_lic_slglvl _DECLARE((short*));
EXTERN_C int4		max_lic_slgrpt _DECLARE((short*));
EXTERN_C int4		max_lic_slgspc _DECLARE((short*));
EXTERN_C int4		max_lic_slgtpd _DECLARE((short*));
EXTERN_C int4		max_lic_slgzon _DECLARE((short*));
EXTERN_C int4		max_lic_soe _DECLARE((short*));
EXTERN_C int4		max_lic_sta _DECLARE((short*));
EXTERN_C int4		max_lic_std _DECLARE((short*));
EXTERN_C int4		max_station _DECLARE((void));
EXTERN_C int4		max_lic_tnd _DECLARE((short*));
EXTERN_C int4		max_lic_ulplvl _DECLARE((short*));
EXTERN_C int4		max_lic_ulpspc _DECLARE((short*));
EXTERN_C int4		max_lic_ulptpd _DECLARE((short*));
EXTERN_C int4		max_lic_utbl _DECLARE((short*));
EXTERN_C int		memadr _DECLARE((short*));
EXTERN_C void		MillisecondsToHsctime _DECLARE((double*, HSCTIME*));
EXTERN_C unsigned char	mod256 _DECLARE((unsigned char*, int));
EXTERN_C long		modx _DECLARE((short*, short*));
EXTERN_C short		morerq _DECLARE((void));
EXTERN_C void		movbyt _DECLARE((short*, short*, short*, short*, short*));
EXTERN_C void		move _DECLARE((short*, short*, short*));
EXTERN_C long		mpool _DECLARE((short));
EXTERN_C int		msgget _DECLARE((int, int));
EXTERN_C int		msgrcv _DECLARE((int, struct message*, int, int, int));
EXTERN_C int		msgsnd _DECLARE((int, struct message*, int, int));
EXTERN_C long		msiday _DECLARE((HSCTIME*));
EXTERN_C void		mvbitx _DECLARE((unsigned short*, unsigned short*, unsigned short*, unsigned short*, unsigned short*));
EXTERN_C void       c_mvbitx _DECLARE((unsigned short, unsigned long, unsigned long, unsigned short*, unsigned long));
EXTERN_C short		name2len _DECLARE((char*));
EXTERN_C short		name2lfn _DECLARE((char*));
static int  		namelen _DECLARE((char*));
EXTERN_C double		nandouble _DECLARE((void));
EXTERN_C float		nanfloat _DECLARE((void));
EXTERN_C int2		nchars _DECLARE((char*, int2, int2*));
EXTERN_C int		netcmp _DECLARE((void*,int,void*));
EXTERN_C int		netexp _DECLARE((void*,int,void*));
EXTERN_C ulong		netcmp2 _DECLARE((const char* pInput, ulong nInputLen, char* pOutput, ulong nOutputLen));
EXTERN_C ulong		netexp2 _DECLARE((const char* pInput, ulong nInputLen, char* pOutput, ulong nOutputLen));
EXTERN_C ulong		netcmp3 _DECLARE((const char* pInput, ulong nInputLen, char* pOutput, ulong nOutputLen));
EXTERN_C ulong		netcmp3_maxsize _DECLARE((ulong nInputLen));
EXTERN_C ulong		netexp3 _DECLARE((const char* pInput, ulong nInputLen, char* pOutput, ulong nOutputLen));
static int  		newroot _DECLARE((char*, long, int, int));
EXTERN_C int		nips _DECLARE((struct thrd_prm*));
EXTERN_C void		no_floppy _DECLARE((void));
EXTERN_C int		none _DECLARE((void));
EXTERN_C int		not_end_of_text _DECLARE((char*, int));
EXTERN_C void		notransfer _DECLARE((void));
EXTERN_C void		nterr _DECLARE((int, int, const char*, const char*, const char*, ...));
EXTERN_C int		numeric_subpag _DECLARE((int, int));
EXTERN_C short		nuout _DECLARE((short*, char*, short));
EXTERN_C short		nxpath _DECLARE((char*, short, char*, short));
EXTERN_C short		nxtfld _DECLARE((char*, short, short*));
EXTERN_C int2		NxtPnt _DECLARE((int2*, PNTNUM*, PNTNUM*));
EXTERN_C int4 FORTCALL  OFFSETOF _DECLARE((void*, void*));
EXTERN_C void		on_alarm _DECLARE((void));
EXTERN_C void		on_pipe _DECLARE((void));
EXTERN_C unsigned char	onescomp _DECLARE((unsigned char*, int));
EXTERN_C int		open_dat_file _DECLARE((char*, long*, char*, short, unsigned long*, int));

#ifdef NT
EXTERN_C HANDLE		opendir _DECLARE((char*));
EXTERN_C struct _iobuf*	open_input_file _DECLARE((char*));
#else
EXTERN_C FILE*		open_input_file _DECLARE((char*));
#endif

EXTERN_C void		open_log _DECLARE((void));
EXTERN_C int		open_raw _DECLARE((int, int*));

EXTERN_C short		otoasc _DECLARE((char*, short, short*, short*));
EXTERN_C int		pcsi_io _DECLARE((int, int, int, unsigned char*, int));
EXTERN_C void		pcsiio _DECLARE((short*, short*, short*, short*, short*));
EXTERN_C int		p_close _DECLARE((int, int));
EXTERN_C int		p_flush _DECLARE((int));
EXTERN_C void*		p_getevt _DECLARE((int, int));
EXTERN_C int		p_open _DECLARE((int, int));
EXTERN_C int		p_read _DECLARE((int, int, char*, int, int));
EXTERN_C int		p_write _DECLARE((int, int, char*, int));
EXTERN_C int        peername _DECLARE((char*, int, int, int));
EXTERN_C double		pget _DECLARE((short*));
EXTERN_C void		pput _DECLARE((short*, double*));
EXTERN_C char*		prline _DECLARE((const unsigned char*, int));
EXTERN_C char*		prline2 _DECLARE((const unsigned char*, int));
EXTERN_C char*		prline4 _DECLARE((const unsigned char*, int));
EXTERN_C char*		prlinex _DECLARE((const unsigned char*, int, int, int));
EXTERN_C short		prmfnd _DECLARE((char*, short, short*));
EXTERN_C void		prof_togle _DECLARE((void));
EXTERN_C void		PrtFldWidths _DECLARE((int,int2*,int2*,int2*,int2*,int2*,int2*,int2*,int2*));
EXTERN_C short		prvfld _DECLARE((char*, short, short*));
EXTERN_C short		pswio _DECLARE((short*));
EXTERN_C short		ptoasc _DECLARE((char*, short, short*, short*, short*));
EXTERN_C void		putbyt _DECLARE((short*, short*, short*));
EXTERN_C void		putcom _DECLARE((short*, long*, short*, short*));
EXTERN_C short		putdat _DECLARE((short*, short*, short*, short*, short*, unsigned short*, unsigned short*, short*));
EXTERN_C long		putdat4 _DECLARE((long*, long*, long*, long*, long*, long*, unsigned short*, long*));
EXTERN_C long		putdatw4 _DECLARE((long*, long*, long*, long*, long*, long*, unsigned short*, long*, long*));
EXTERN_C void		puthst _DECLARE((short*, short*, float*, short*, short*, PNTNUM*, PRMNUM*, char*, short, long*, short*));
EXTERN_C short		putval _DECLARE((PNTNUM16*, PRMNUM*, uint2*, float*, ...));
EXTERN_C int		hsc_putval_numb_priority _DECLARE((PNTNUM point, PRMNUM param, float RealValue, int2 command, int2 residual));
EXTERN_C int		hsc_putval_numb _DECLARE((PNTNUM point, PRMNUM param, float RealValue));
EXTERN_C int		hsc_putval_asci _DECLARE((PNTNUM point, PRMNUM param, char *string));
EXTERN_C int		hsc_putval_hist _DECLARE((PNTNUM point, PRMNUM param, int offset, float RealValue));
EXTERN_C void		q_close _DECLARE((struct unix_queue*));
EXTERN_C char*		q_name _DECLARE((char*, char*));
EXTERN_C struct unix_queue* q_open _DECLARE((char*));
EXTERN_C int		q_reset _DECLARE((char*, int, int));
EXTERN_C int		q_seg_wrt _DECLARE((struct unix_queue*, char*, int, int));
EXTERN_C int		r12_rd _DECLARE((unsigned int, int, unsigned char*, int, int));
EXTERN_C int		r12_wrt _DECLARE((int, int, unsigned char*, int));
EXTERN_C void		rawtm _DECLARE((int4*));
EXTERN_C void		RawtmToHsctime _DECLARE((int4*, HSCTIME*));
static int  		rd_aud _DECLARE((int));
EXTERN_C void		rdpipe _DECLARE((void*));
EXTERN_C int		read_atd _DECLARE((int, int, char*, int, int));
EXTERN_C int		read_atdp _DECLARE((int, int, char*, int, int));
EXTERN_C int		read_exact _DECLARE((int, char*, int));
EXTERN_C int		read_exact_silent _DECLARE((int, char*, int));
EXTERN_C int		read_exact_silent_timeout _DECLARE((int, char*, int, int));
EXTERN_C int		read_n _DECLARE((int, int, char*, int));
EXTERN_C int		read_pcsi _DECLARE((int, int, char*, int));
EXTERN_C void		real_psw _DECLARE((int, short*, int));
EXTERN_C int		read_r12 _DECLARE((int, int, char*, int));
EXTERN_C int		read_tmout _DECLARE((unsigned int, int (*read_routine)(void), int, int, char*, int));
EXTERN_C struct dirent*	readdir _DECLARE((HANDLE));
EXTERN_C short		relsem _DECLARE((short*));
EXTERN_C short		ressem _DECLARE((short*, short*, short*));
EXTERN_C void		revrng _DECLARE((short*, float*, float*, float*, float*, float*));
EXTERN_C void		rgtfnd _DECLARE((char*, int2, int2*));
EXTERN_C void		rgtjst _DECLARE((char*, short, short*));
EXTERN_C short		rltml _DECLARE((short*));
EXTERN_C short		root_fstyp _DECLARE((void));
EXTERN_C void		RptFldWidths _DECLARE((int2*,int2*,int2*,int2*,int2*));
EXTERN_C short		rqcl _DECLARE((short*, short*, short*));
EXTERN_C void		rqcl_wake _DECLARE((void));
EXTERN_C short		rqgtsk _DECLARE((char*, short, short*));
EXTERN_C void		rqstsk _DECLARE((short*, short*, unsigned short*, ...));
EXTERN_C short		rqtskb _DECLARE((short*, short*,...));
EXTERN_C int		rqtskb2 _DECLARE((int, void*, int));
EXTERN_C int		rqtskb_ex _DECLARE((int, void*, int, int));
EXTERN_C int        rwflxmt _DECLARE((char*, int, int));
static int  		save _DECLARE((void));
EXTERN_C int		hsc_savval_numb _DECLARE((PNTNUM, PRMNUM, float));
EXTERN_C int		scriptcmd _DECLARE((int, int));
static int  		searchkey _DECLARE((char*));
EXTERN_C BOOL		SearchLocalAndPath(TCHAR*);
EXTERN_C void		SecondsToHsctime _DECLARE((double*, HSCTIME*));
EXTERN_C void		sed _DECLARE((char*, short, char*, short, char*, short));
EXTERN_C void		sem_tmout _DECLARE((int));
EXTERN_C int		semgt _DECLARE((int, int));
EXTERN_C void		semlck _DECLARE((int, int));
EXTERN_C char*		semnam _DECLARE((char*, int, int));
EXTERN_C int		semop1 _DECLARE((int, int, int, int));
EXTERN_C void		semset _DECLARE((int, int, int));
EXTERN_C void		semunlck _DECLARE((int, int));
EXTERN_C int 		set_debug _DECLARE((int type));
EXTERN_C int 		set_sa(SECURITY_ATTRIBUTES** psa);
EXTERN_C int 		set_secur _DECLARE((HANDLE h, int type));
EXTERN_C int		set_secur_bysid(HANDLE h, int type, PSID group,int access);
EXTERN_C int 		set_secur_ea_byname _DECLARE((char* groupName,char* objectName,int type,int accessMask,int inheritance,int accessMode));
EXTERN_C int    	set_svc_secur_SDDL _DECLARE((HANDLE hSvc, char *szObject));
EXTERN_C void		setobjcol _DECLARE((short*, short*, short*, short*));
EXTERN_C void		setobjlvl _DECLARE((short*, short*, short*, float*, float*, float*, float*, float*));
EXTERN_C void		setobjtxt _DECLARE((short*, short*, short*, char*, short));
EXTERN_C void		setobjval _DECLARE((short*, short*, short*, short*));
EXTERN_C int		setraw _DECLARE((int, struct devtbl*));
EXTERN_C short		settm _DECLARE((long*));
EXTERN_C int		setuxtm _DECLARE((struct timeval*));
EXTERN_C void		sig_exit _DECLARE((void));
EXTERN_C void		sig_onsrv _DECLARE((void));
EXTERN_C void		sig_onclt _DECLARE((void));
EXTERN_C void		SnapBackToInterval _DECLARE((HSCTIME*, int8));
EXTERN_C int		snd_u_fl _DECLARE((const char *path, int flag, int2 flag2));
EXTERN_C int		snd_u_fl_target _DECLARE((const char *path, int flag, int2 flag2, int target));
EXTERN_C int		snd_u_fl_target_status _DECLARE((const char *path, int flag, int2 flag2, int target, BOOL failLinks, int* pStatuses, int statusCount));
EXTERN_C void		snt_nips _DECLARE((struct thrd_prm*));
static int  		splitadd _DECLARE((char*, long, int));
static int  		splithigh _DECLARE((char*, long, int));
EXTERN_C void		splithost _DECLARE((char*, char*, char*));
static int  		splitlow _DECLARE((char*, long, int));
EXTERN_C void		splitpath _DECLARE((const char*, char*, char*));
EXTERN_C void		sptsk _DECLARE((short*, char*, short, short*, short*, short*, char*, short, char*, short, char*, short));
EXTERN_C int   		sqlitexmt _DECLARE((int id, int fn, char* update, int length));
EXTERN_C void		srch _DECLARE((char*, short, char*, short, short*));
EXTERN_C short		srchar _DECLARE((char*, short, char*, short, short*, short*));
EXTERN_C short		ssne _DECLARE((float*, float*));
EXTERN_C void		stats_sleep _DECLARE((int4*, float*, float*));
EXTERN_C void		stats_wakeup _DECLARE((void));
EXTERN_C short		stn_num _DECLARE((short*));
static void 		str_insert _DECLARE((char*, char*, char*));
EXTERN_C void		strip_space _DECLARE((char*, int2));
EXTERN_C void		strjstfy _DECLARE((char*, int));
EXTERN_C int		strrep _DECLARE((char*, int, char*, char*));
static int  		subsearch _DECLARE((char*));
EXTERN_C void		subtime _DECLARE((HSCTIME*, HSCTIME*));
EXTERN_C void		subtm  _DECLARE((HSCTIME*, long, int));
EXTERN_C void		subtm2 _DECLARE((HSCTIME*, long, long, int));

#ifdef NT
			/* swab is a standard runtime library function */
#else
EXTERN_C void		swab _DECLARE((char*, char*, int*));
#endif

EXTERN_C int		swb_cpy _DECLARE((char*, char*, unsigned int));
EXTERN_C void		tabexp _DECLARE((char*, int));
EXTERN_C int		task_busy _DECLARE((struct trbtbl*));
EXTERN_C short		tdccnt _DECLARE((float*, double*, short*, short*));
EXTERN_C short		tdceng _DECLARE((float*, double*, short*, short*));
EXTERN_C int		textchr _DECLARE((char*));
EXTERN_C void		textclr _DECLARE((void));
EXTERN_C int		textget _DECLARE((int, int, int, unsigned char*, int, unsigned char*, int));
EXTERN_C void		textins _DECLARE((void));
EXTERN_C int		textput _DECLARE((int, int, unsigned char*, int, unsigned char*, int));
EXTERN_C void		toieee _DECLARE((short*, short*));
EXTERN_C void       toieeedouble _DECLARE((short*, short*));
static int  		tokey _DECLARE((char**, char**, int, int));
EXTERN_C void		tolong _DECLARE((short*, short*));
EXTERN_C void       trace _DECLARE((int, int, char*, int));
EXTERN_C void       trace_ex _DECLARE((int, int, char*, int, int));
EXTERN_C void       trace_stats_update_explicit _DECLARE((int lrn, int bytes_read, int bytes_written, int idle_time, int busy_time, int resp_time, int resp_time_min, int resp_time_max, int resp_count));

static long 		transno _DECLARE((void));
EXTERN_C int		trap _DECLARE((int));
EXTERN_C void		trapen _DECLARE((int*,short*));

#ifdef	NT
EXTERN_C void		trm04 _DECLARE((short*, ...));
#else
EXTERN_C void		trm04 _DECLARE((short*, short*));
#endif

EXTERN_C void		trmtsk _DECLARE((short*, short*));
EXTERN_C void		trptsk _DECLARE((void));
EXTERN_C void		TruncateHsctime(HSCTIME* pHscTime, HSCTIME* pHscTimeTruncated, int2 units);
EXTERN_C void		tskclean _DECLARE((void));
EXTERN_C short		tstskb _DECLARE((short*));
EXTERN_C unsigned char	twoscomp _DECLARE((unsigned char*, int));
static int  		typlen _DECLARE((int));
EXTERN_C void		UnknownTimeAsHsctime _DECLARE((HSCTIME*));
EXTERN_C void		unixbuf _DECLARE((int, int, const char*, const char*, const char*, ...));
EXTERN_C void		unixerr _DECLARE((int, int, const char*, const char*, const char*, ...));
EXTERN_C void		unixmsg _DECLARE((int, int, const char*, const char*, const char*, ...));
EXTERN_C void		unixstack     _DECLARE((int, int, char*, char*, char*, ...));
EXTERN_C void		unixstack_ex  _DECLARE((int, int, char*, char*, CONTEXT*, char*, ...));
EXTERN_C void		unixstack_ex2 _DECLARE((int, int, char*, char*, CONTEXT*, int, char*, ...));
EXTERN_C void		update_links _DECLARE((struct link_data*,int,int,int));
EXTERN_C void		upper _DECLARE((char*, short));
EXTERN_C short		usrout _DECLARE((char*, short));
EXTERN_C short		vewreq _DECLARE((short*));
EXTERN_C void		virtual_psw _DECLARE((int, short*, int));
EXTERN_C void		virtual_psw_rpc _DECLARE((short*, int));
EXTERN_C short		vld _DECLARE((void*));
EXTERN_C short		vms_euout _DECLARE((int, char*, short));
EXTERN_C void		vmserr _DECLARE((int, int, char*, char*, char*, ...));
EXTERN_C void		vrfy _DECLARE((char*, short, char*, short, short*));
EXTERN_C void		vxprrm _DECLARE((short*, short*));
EXTERN_C short FORTCALL WAITN _DECLARE((short*, short*));
EXTERN_C short		waitr _DECLARE((short*));
EXTERN_C int		waitx _DECLARE((int,int));
EXTERN_C void  FORTCALL WAITX _DECLARE((short*,short*,short*));
EXTERN_C char*		where _DECLARE((char*));
static int 	    	wr_aud _DECLARE((int));
EXTERN_C int		write_n _DECLARE((int, int, char*, int));
EXTERN_C int		wrt_exact _DECLARE((int, const char*, int));
EXTERN_C void		wrtlog _DECLARE((int));
EXTERN_C short		wttskb _DECLARE((short*));
EXTERN_C void		xoff _DECLARE((void));
EXTERN_C void		xon _DECLARE((void));
EXTERN_C char		xor _DECLARE((unsigned char*, int));
EXTERN_C char		xorchk _DECLARE((unsigned char*, int, unsigned short));
EXTERN_C short		xpath _DECLARE((char*, short, char*, short));


//
// Operator Security Related calls
//
EXTERN_C int		hsc_sec_get_ClientHelper _DECLARE((void**));
EXTERN_C int		hsc_sec_release_ClientHelper _DECLARE((void*));
EXTERN_C int		hsc_sec_ValidateCredentials _DECLARE((char*, char*, char*));
EXTERN_C int		hsc_sec_AuthenticateCredentials _DECLARE((void*, unsigned int, char*, char*, char*));
EXTERN_C int		hsc_sec_ChangePassword _DECLARE((void*, unsigned int, char*, char*, char*, char*));
EXTERN_C int		hsc_operatorUpdateFullName _DECLARE((int));
EXTERN_C int2		hsc_oper_allowed_on_area _DECLARE((int2, int2, int2*));
EXTERN_C int		hsc_addOperatorTag _DECLARE((int));
EXTERN_C int		hsc_delOperatorTag _DECLARE((int));
EXTERN_C int		hsc_checkWinOperatorExists _DECLARE((char*, char*));
EXTERN_C int		hsc_getWinOperatorName _DECLARE((char*, char*, char*, int));
EXTERN_C int		hsc_getLdapOperatorName _DECLARE((char*, char*));
EXTERN_C void		hsc_constructOperatorIDa _DECLARE((char*, char*, char*, int));
EXTERN_C void		hsc_constructOperatorIDb _DECLARE((char*, char*, char*, int));
EXTERN_C int		hsc_getActorName _DECLARE((char*, int, int));
EXTERN_C int		hsc_getCRTOperatorNumber _DECLARE((int));
EXTERN_C int		hsc_getCRTOperatorID _DECLARE((char*, int, int));
EXTERN_C int		hsc_getLocalUserName _DECLARE((char*, int, int));
EXTERN_C int		hsc_getLocalUserNameCrt _DECLARE((char*, int, int));
EXTERN_C int		hsc_getLocalUserNameString _DECLARE((char*, int, char*));
EXTERN_C int		hsc_getOperatorID _DECLARE((char*, int, int));
EXTERN_C int		hsc_getOperatorFullName _DECLARE((char*, int, int));
EXTERN_C int		hsc_getOperatorRecordFromName  _DECLARE((const char *szOperatorName));
EXTERN_C int		hsc_getOperatorIsEnabled _DECLARE((int));
EXTERN_C int		hsc_getOperatorProfile _DECLARE((char *szOperatorProfile, int nSize, int nOper));

EXTERN_C int		hsc_IsOperidRecordAGroup _DECLARE((struct operid));
EXTERN_C int		hsc_IsOperidRecordAValidGroup _DECLARE((struct operid));
EXTERN_C int		hsc_DoesOperidAllowGroups _DECLARE((int));
EXTERN_C int		hsc_DoesOperRecAllowGroups _DECLARE((struct operid));
EXTERN_C int		CanLoginNow _DECLARE((struct operid));
EXTERN_C int		hsc_GetGroups4Operator _DECLARE((int2, char *, int **, int *));
EXTERN_C int *		hsc_DuplicateGroups _DECLARE((int cGroups, int* rgGroups));
EXTERN_C void		hsc_FreeGroups _DECLARE((int *));
EXTERN_C int		hsc_GetSOR4Operator _DECLARE((int nOperidRec, int *pnSecLvl, int *pnContLvl, int2 *poidpin,
			                              int2 *poidsmp[OIDSTASZ], int2 *poidcsmp[OIDCSTASZ], int2 *poidapm[MAPSZ*2],
			                              int2 *poidasg[MAPSZ], int2 *poidcsg[CMDTBLNM][MAPSZ]));
EXTERN_C int		hsc_GetSOR4Operator2 _DECLARE((int, int *, int *, int2 *, int2 *, int2 *, int2 *, int2 *, int2 *));
EXTERN_C int		hsc_GetSOR4Groups _DECLARE((int cGroups, int *rgOperidRecNo, int *pnSecLvl, int *pnContLvl,
			                            int2 *poidpin, int2 *poidsmp[OIDSTASZ], int2 *poidcsmp[OIDCSTASZ],
			                            int2 *poidapm[MAPSZ*2], int2 *poidasg[MAPSZ], int2 *poidcsg[CMDTBLNM][MAPSZ]));
EXTERN_C int		hsc_GetSecLvl4Operator _DECLARE((int, int *));
EXTERN_C int		hsc_GetSecLvl4Groups _DECLARE((int, int *, int *));
EXTERN_C int		hsc_GetContLvl4Operator _DECLARE((int, int *));
EXTERN_C int		hsc_GetContLvl4Groups _DECLARE((int, int *, int *));
EXTERN_C int		hsc_GetPrintInhibits4Operator _DECLARE((int, int *));
EXTERN_C int		hsc_GetPrintInhibits4Groups _DECLARE((int, int *, int *));
EXTERN_C int		hsc_GetIdleTimeout4Operator _DECLARE((int , int *));
EXTERN_C int		hsc_GetIdleTimeout4Groups _DECLARE((int , int *, int*));
EXTERN_C int		hsc_GetStartupPageBuffer4Operator _DECLARE((int , int2**));
EXTERN_C int		hsc_GetStartupPageBuffer4Groups _DECLARE((int , int *, int2**));
EXTERN_C int		hsc_FreeStartupPageBuffer _DECLARE((int2 **));
EXTERN_C int		hsc_GetAlarmTracker4Operator _DECLARE((int , int *));
EXTERN_C int		hsc_GetAlarmTracker4Groups _DECLARE((int , int *, int *));
EXTERN_C int		hsc_GetAlarmRoutingPriority4Operator _DECLARE((int , int *));
EXTERN_C int		hsc_GetAlarmRoutingPriority4Groups _DECLARE((int , int *, int *));
EXTERN_C int		hsc_GetDefaultView4OperatorOnCrt _DECLARE((int , int , char *, int));
EXTERN_C int		hsc_GetDefaultView4Operator _DECLARE((int , int , char *, int));
EXTERN_C int		hsc_GetDefaultView4Groups _DECLARE((int, int *, int, char *, int ));
EXTERN_C int		hsc_GetDefaultDashboard4OperatorOnCrt _DECLARE((int , char *, int));
EXTERN_C int		hsc_GetDefaultDashboard4Operator _DECLARE((int , char *, int));
EXTERN_C int		hsc_GetDefaultDashboard4Groups _DECLARE((int , int *, char *, int));
EXTERN_C int		hsc_CombineAlarmRoutingPriorities _DECLARE((int, int, int *));
EXTERN_C int		hsc_GetFullName4User _DECLARE((char *, char **));
EXTERN_C int		hsc_FreeFullName _DECLARE((char **));
EXTERN_C int		hsc_UpdateCrttblGroup _DECLARE((int));
EXTERN_C int		hsc_GetMaxNumberOfGroups _DECLARE((void));
EXTERN_C BOOL		hsc_IsMemberOfHA();
EXTERN_C BOOL		hsc_IsMemberOfGroup _DECLARE((char *, char *));
EXTERN_C int		getloginuseratlevel_emb _DECLARE((int2  *, int2));

EXTERN_C int		hsc_can_oper_token_access_server _DECLARE((HANDLE hToken, int *pfStatus));
EXTERN_C int		hsc_can_oper_token_access_points _DECLARE((HANDLE hToken, enum ECapabilityType requiredAccess, int numRequests, PNTNUM const* rgPoints, int* rgRequestStatus));
EXTERN_C int		hsc_can_station_access_server _DECLARE((int stationNo, int *pfStatus));
EXTERN_C int		hsc_can_station_access_points _DECLARE((int stationNo, enum ECapabilityType requiredAccess, int numRequests, PNTNUM const* rgPoints, int* rgRequestStatus));

EXTERN_C int		hsc_does_station_have_capability_for_area _DECLARE((int2 nStation, enum ECapabilityType nCapability, int2 nAreaNumber, int fIgnoreSecLvl, int *pnResult));
EXTERN_C int		hsc_does_station_have_capability_for_point _DECLARE((int2 nStation, enum ECapabilityType nCapability, PNTNUM nPoint, int fIgnoreSecLvl, int *pnResult));
EXTERN_C int		hsc_does_station_have_capability_for_alarm_priority _DECLARE((int2 nStation, enum ECapabilityType nCapability, int2 nPriority, BOOL bSystemAlarm, int *pnResult));
EXTERN_C int		hsc_get_station_alarm_priority_for_capability _DECLARE((int2 nStation, enum ECapabilityType nCapability, BOOL bSystemAlarm, int2 *pnPriority));
EXTERN_C int2		hsc_get_dfdperm_for_crt_area _DECLARE((int2 nStation, int2 nAreaNumber));
EXTERN_C int		hsc_UpdateCrttblOperAssetCaps _DECLARE((int nCrttblRecNo, BOOL fForce));
EXTERN_C int		hsc_does_operid_have_capability_for_area _DECLARE((int2 nOperid, enum ECapabilityType nCapability, int2 nAreaNumber, int fIgnoreSecLvl, int *pnResult));
EXTERN_C int		hsc_does_operid_list_have_capability_for_area _DECLARE((int nOperid, int *rgOperid, int cOperid, enum ECapabilityType nCapability, int nAreaNumber, int fIgnoreSecLvl));
EXTERN_C BOOL       hsc_get_console_asset_alarm_enable_status(int console, const char* szAsset);
EXTERN_C BOOL       hsc_get_console_area_alarm_enable_status(int console, int area);
EXTERN_C BOOL       hsc_get_station_area_alarm_enable_status(int station, int area);
EXTERN_C HRESULT    hsc_set_console_area_alarm_enable_status(int console, int area, BOOL isEnable, int2 securityLevel);
EXTERN_C int        hsc_GetStnType(int stationNumber);

// Advanced Parameter Security functions
//   from clib\cmis\src\apsRuntime_api.cpp
EXTERN_C int		hsc_aps_Initialize _DECLARE((int fAutoUpdate));
EXTERN_C int		hsc_aps_SimpleStart();
EXTERN_C int		hsc_aps_IsEnabled();
EXTERN_C void		hsc_aps_Load();
EXTERN_C int		hsc_aps_IsLoaded();
EXTERN_C int		hsc_aps_LoadFromFile _DECLARE((char *szFile));
EXTERN_C void		hsc_aps_UpdateSecLvlFile();
EXTERN_C int		hsc_aps_CheckParameterAccess4CRT _DECLARE((int nCRT, PNTNUM nPoint, PRMNUM nParam, int *pnResult));
EXTERN_C int		hsc_aps_CheckParameterAccess4GDASECURITY _DECLARE((GDASECURITY *pSecurity, PNTNUM nPoint, PRMNUM nParam));
EXTERN_C int		hsc_aps_CheckParameterAccess4PSLs _DECLARE((char *strPSLs, PNTNUM nPoint, PRMNUM nParam));
EXTERN_C int		hsc_aps_GetPSLs4CRT _DECLARE((int nCRT, char **pszPSLs, int *pnSize));
EXTERN_C int		hsc_aps_GetPSLsFromGDASECURITY _DECLARE((char **pszPSLs,  GDASECURITY *pSecurity));
EXTERN_C void		hsc_aps_FreeMemory _DECLARE((void * argptr));
EXTERN_C int		hsc_aps_WouldAPSBlockWrite _DECLARE((GDASECURITY *pSecurity, int cItems, PNTNUM* rgPoint, PRMNUM* rgParam, int *rgStatus));
EXTERN_C int		hsc_aps_DoesAPSHaveAnException _DECLARE((GDASECURITY *pSecurity, int cItems, PNTNUM* rgPoint, PRMNUM* rgParam, int *rgStatus, int fCheckRemote));
EXTERN_C int		hsc_aps_AdjustDfdLvl _DECLARE((PNTNUM nPoint, PRMNUM nParam, int2 crtlvl, int2 *pdfdlvl, int fCheckRemote));
//   from clib\cmis\src\grouphelper.c
EXTERN_C int		hsc_GetAPSSecLvl4Operator _DECLARE((int nOperidRec, int *pnApsSecLvl));
EXTERN_C int		hsc_GetAPSlevel4Groups _DECLARE((int cGroups, int *rgOperidRecNo, int2 *pnAPSseclvl, int fUpdateSecLvl));
EXTERN_C int		hsc_GetAPSlevel4Operator _DECLARE((int nOperidRec, int2 *pnAPSseclvl, int fUpdateSecLvl));
EXTERN_C int		hsc_CacheCrtProfileName(int, BOOL);
//   from clib\cmis\src\operlib.c
EXTERN_C int		hsc_getPSLs_from_formatted_operid _DECLARE((char** pszPSLs, int* pnPSLsLen, int* pfUseSecLvl, unsigned char* szFormattedOperId));
// End Advanced Parameter Security Functions

EXTERN_C void		hsc_event_fn(uint2, uint4);
EXTERN_C void		hsc_event_fn2(uint2, uint4, uint4, uint4, uint4, uint4, uint4, uint4);

EXTERN_C void		auditmsg _DECLARE((long, long, char*, char*, char*, ...));
EXTERN_C void		activitymsg _DECLARE((long, long, char*, char*, char*, ...));
EXTERN_C int		hsc_SetParanoid _DECLARE((int, int));
EXTERN_C int		hsc_auditout _DECLARE((char*, int));

EXTERN_C void CALLBACK  Lock_ApiAcs _DECLARE((void));
EXTERN_C void CALLBACK  Unlock_ApiAcs _DECLARE((void));

/************************************************************************/
/*****     COPYRIGHT 2008 - 2016    HONEYWELL INTERNATIONAL SARL     ****/
/************************************************************************/

#endif	/* end of conditional include PROTOTYPES_FLAG */
