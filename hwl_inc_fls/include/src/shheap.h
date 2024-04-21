/************************************************************************/
/*****     COPYRIGHT 2008-2016      HONEYWELL INTERNATIONAL SARL     ****/
/************************************************************************/

#ifndef heap_flag
#define heap_flag

#include "dual_defs.h"

/*
@(#)shheap.h	main.SVR_MASTERPROJ_Integration.R0930_Int.7
BEGIN_DOC
---------------------------------------------------------------------------
SHHEAP.H - definitions for shared heap
---------------------------------------------------------------------------
SUMMARY:
    This header file contains the definition and function prototypes for the
    use and implimentation of shared heaps

DESCRIPTION:

    -----------------------------------------------------------------------
    NOTES -
    -----------------------------------------------------------------------

DEFINITIONS:
*/

#define _KB_         1024
#define _MB_        (1024*1024)
#define NUMHEAPS     20

 	/* shared heap identifiers */

#define LOCKSID         0   /* record locks */
#define POINTSID        1   /* points */
#define DUALID          2   /* Dual queue */
#define DICTIONARYID	3	/* point parameter dictionary */
#define GDAID           4   /* GDA data */
#define PNTXMT_Q_ID     5   /* NIF point transmit queue */
/*                      6   */
#define BACNET_ID       7   /* BACnet Server */
#define TASKREQ_ID      8   /* task requests */
/*                      9   */

	/* shared heap segment/file names */

#define SHHEAP0_NAME	"locks"
#define SHHEAP1_NAME	"points"
#define SHHEAP2_NAME	"dual_q"
#define SHHEAP3_NAME	"dictionary"
#define SHHEAP4_NAME	"gda"
#define SHHEAP5_NAME	"pntxmt_q"
#define SHHEAP6_NAME	"shheap6"
#define SHHEAP7_NAME	"bacnetheap"
#define SHHEAP8_NAME	"taskrequest"
#define SHHEAP9_NAME    "shheap9"
#define SHHEAP10_NAME	"DbRepSrvUpdQ"
#define SHHEAP11_NAME	"shheap11"
#define SHHEAP12_NAME	"shheap12"
#define SHHEAP13_NAME	"shheap13"
#define SHHEAP14_NAME	"shheap14"
#define SHHEAP15_NAME	"shheap15"
#define SHHEAP16_NAME	"shheap16"
#define SHHEAP17_NAME	"shheap17"
#define SHHEAP18_NAME	"shheap18"
#define SHHEAP19_NAME	"shheap19"

	/* shared heap versions.
	   These must be changed if there is a change to the shared
	   heap contents. That is, if the point record is changed,
	   then the point heap version would be incremented. */

#define SHHEAP0_VER  1
#define SHHEAP1_VER  19
#define SHHEAP2_VER  1
#define SHHEAP3_VER  2
#define SHHEAP4_VER  1
#define SHHEAP5_VER  1
#define SHHEAP6_VER  1
#define SHHEAP7_VER  1
#define SHHEAP8_VER  1
#define SHHEAP9_VER  1
#define SHHEAP10_VER 1
#define SHHEAP11_VER 1
#define SHHEAP12_VER 1
#define SHHEAP13_VER 1
#define SHHEAP14_VER 1
#define SHHEAP15_VER 1
#define SHHEAP16_VER 1
#define SHHEAP17_VER 1
#define SHHEAP18_VER 1
#define SHHEAP19_VER 1

	/* shared heap default sizes. Must multiples of 4k.
	   Size can be specified at creation to shattach() */

#define SHHEAP0_SZ  (256*_KB_)
#define SHHEAP1_SZ  ( 32*_MB_)
#define SHHEAP2_SZ  (  5*_MB_)
#define SHHEAP3_SZ  (  2*_MB_)
#define SHHEAP4_SZ  ( 16*_MB_)
#define SHHEAP5_SZ  (256*_KB_)
#define SHHEAP6_SZ  (  1*_MB_)
#define SHHEAP7_SZ  (  1*_MB_)
#define SHHEAP8_SZ  (256*_KB_)
#define SHHEAP9_SZ  (  1*_MB_)
#define SHHEAP10_SZ (  1*_MB_)
#define SHHEAP11_SZ (  1*_MB_)
#define SHHEAP12_SZ (  1*_MB_)
#define SHHEAP13_SZ (  1*_MB_)
#define SHHEAP14_SZ (  1*_MB_)
#define SHHEAP15_SZ (  1*_MB_)
#define SHHEAP16_SZ (  1*_MB_)
#define SHHEAP17_SZ (  1*_MB_)
#define SHHEAP18_SZ (  1*_MB_)
#define SHHEAP19_SZ (  1*_MB_)

	/* shared heap flags
	 * NOFL - memory only
	 *    0 - memory + disk */

#define SHHEAP0_FLG     NOFL
#define SHHEAP1_FLG     0
#define SHHEAP2_FLG     NOFL
#define SHHEAP3_FLG     0
#define SHHEAP4_FLG     NOFL
#define SHHEAP5_FLG     NOFL
#define SHHEAP6_FLG     NOFL
#define SHHEAP7_FLG     0
#define SHHEAP8_FLG     NOFL
#define SHHEAP9_FLG     NOFL
#define SHHEAP10_FLG    NOFL
#define SHHEAP11_FLG    NOFL
#define SHHEAP12_FLG    NOFL
#define SHHEAP13_FLG    NOFL
#define SHHEAP14_FLG    NOFL
#define SHHEAP15_FLG    NOFL
#define SHHEAP16_FLG    NOFL
#define SHHEAP17_FLG    NOFL
#define SHHEAP18_FLG    NOFL    /* use for memory resident tests */
#define SHHEAP19_FLG    0       /* use for disc resident tests */

	/* shared heap CHECK levels */

#define	SH_C_DEFRAG	-2	/* check, repair, and defragment the heap */
#define	SH_C_REPAIR	-1	/* check and repair the heap */
#define	SH_C_CHECK	0	/* check and report stats only */
#define	SH_C_FREE	1	/* check and report free blocks */
#define	SH_C_MALLOC	2	/* check and report malloc blocks */
#define	SH_C_DUMP	3	/* check and dump contents of malloc blocks */
#define SH_C_LOCK       0x0100  /* mask with 0 to 3 to keep heap locked */

	/* shared heap VERBOSE levels */

#define	SH_V_ALL	0	/* report everything */
#define	SH_V_SOME	1	/* report major steps */
#define	SH_V_ERRORS	2	/* report if errors exist */
#define	SH_V_SILENT	3	/* don't report anything */

/*
STRUCTURES:
*/

typedef	unsigned int GADDR;	// internal abstracted heap address
typedef int	GINDX;		// application independant malloc handle

/* shattach() heap creation structure */

struct shcreate
  {
    int		cr_sz;			/* segment size (-1 use default) */
    int		max_sz;			/* max # segments to limit growth */
    int		flags;			/* transfered to gcntrl (see shheapish.h) */
#define	NOFL		  0x00008000	/* no backup file */
#define	shLockIntoMemory  0x00010000	/* lock heap into memory */
  };


/*
PROTOTYPES:
	where:
		char* laddr	- malloc block addr local to process
        	int   id	- heap id (lock, etc)
		int   sz	- malloc block size
		GINDX indx	- global malloc handle
*/

EXTERN_C char*  CALLBACK shmalloc (int id,int sz);              /* malloc */
EXTERN_C char*  CALLBACK shrealloc(int id,char* laddr,int sz);  /* realloc */
EXTERN_C void   CALLBACK shfree   (int id,char* laddr);         /* free */
EXTERN_C int    CALLBACK shfreeall(int id);                     /* free all mallocs */
EXTERN_C int    CALLBACK shcheck  (int id,int clvl,int vlvl);   /* check/dump heap */
EXTERN_C int	CALLBACK shlock_test (int pid, int tid, int heapid); /* test if a heap is locked */
EXTERN_C int    CALLBACK shlock   (int id,int wait);            /* lock heap, wait in ms */
EXTERN_C void   CALLBACK shunlock (int id);                     /* unlock heap */
EXTERN_C int    CALLBACK shInitialise(void*,void*);             /* initialise heap dll */
EXTERN_C int    CALLBACK shUnInitialise(void);                  /* uninitialise heap dll */

EXTERN_C int    CALLBACK shTransmitCopy(int id, int target);    // copy heap to to heap.cpy for transmit
EXTERN_C int    CALLBACK shTransmitSend(int id, int target, int* pStatuses, int statusCount);    // send heap.cpy to target server
EXTERN_C int    CALLBACK shReceive     (int id);                // receive heap file

EXTERN_C int    CALLBACK shTransBegin(int id, char* progname, char* lineno); /* begin a transaction */
EXTERN_C int    CALLBACK shTransEnd  (int id, char* progname, char* lineno); /* end a transaction (flush) */
EXTERN_C int    CALLBACK shTransAbort(int id, char* progname, char* lineno); /* abort a transaction */
EXTERN_C int    CALLBACK shTransSaveOld(int id,void* laddr,int sz); /* save transaction data */
EXTERN_C int    CALLBACK shTransSaveNew(int id,void* laddr,int sz); /* save transaction data */

EXTERN_C void   CALLBACK shsetflush(int id,void* laddr,int sz); /* mark as needing flush */
EXTERN_C void   CALLBACK shflush   (int id);                    /* flush heap to disk */

EXTERN_C int	CALLBACK shBackup   (int id);
EXTERN_C int	CALLBACK shRestore  (int id,char* name);

EXTERN_C struct lcntrl* CALLBACK shattach (int id,struct shcreate* shcr); /* attach heap */
EXTERN_C int    CALLBACK shdetach (int id);             /* detach heap */
EXTERN_C GINDX	CALLBACK shltoi   (int id,char* laddr);	/* convert local addr to index */
EXTERN_C char*	CALLBACK shitol   (int id,GINDX indx);	/* convert index to local address */
EXTERN_C char*	CALLBACK shitoll  (int id,GINDX indx,int* size); /* convert index to local address, size, and lock index */
EXTERN_C void	CALLBACK shitolu  (int id,GINDX indx);	/* unlock index  */
EXTERN_C int	CALLBACK SHMSZ	  (int id,void* laddr);	/* get size of malloc block */
EXTERN_C char*  CALLBACK shgetfst (int id); /* return local addr of 1st malloc, used as start of malloc chains */
EXTERN_C int    CALLBACK svc_shheap (DUAL_SVC_HANDLE*,char*,struct error_buf*); /* dual service heap */

// The following functions are in the cdual library

EXTERN_C int    shpgxmt(int sendto,int id,GADDR pgaddr,char* page,int sz,int flag); /* transmit data */
EXTERN_C int    shhpxmt(int sendto,int id,int fn,int blkno);             /* transmit function */


/*
END_DOC
*/

#endif  /* end of conditional include _flag */

/************************************************************************/
/*****     COPYRIGHT 2008-2016      HONEYWELL INTERNATIONAL SARL     ****/
/************************************************************************/

