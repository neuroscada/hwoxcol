#ifndef dual_defs_flag
#define dual_defs_flag
/************************************************************************/
/*****     COPYRIGHT 2008 - 2016    HONEYWELL INTERNATIONAL SARL     ****/
/************************************************************************/

#include <winsock.h>

/*
@(#)dual_defs.h   main.SVR_MASTERPROJ_Integration.R0930_Int.14
BEGIN_DOC
---------------------------------------------------------------------------
DUAL_DEFS - defines Dual Redundant Data Manager common information
---------------------------------------------------------------------------
SUMMARY:

DESCRIPTION:

    -----------------------------------------------------------------------
    NOTES -
    -----------------------------------------------------------------------

DEFINITIONS:
*/

#define REDUNDANCY_VERSION 2

#define MAX_LINKS (8*4)         // 0 to 7 BCC by 2 servers by 2 links

#define MAXBHND 6000            // max msgno can be behind last_msgno
#define MAXTIMEBHND 120         // max time msgno can be behind last_msgno (Queue not being processed)
                                // must be greater than timeouts used on I/o calls while synching
#define SynchingTIMEOUT 60000   // RPC timeout when synching
#define SynchedTIMEOUT  30000   // RPC timeout when not synching

/*
END_DOC
*/

#define DUAL_MAX_HOSTNAME_LEN		(100)

/* define TCP/IP, UDP/IP service port numbers for Dual daemons */
#define DUAL_PSW_SERVICE_PORT		((unsigned short)(51000))
#define DUAL_LINK_SERVICE_PORT		((unsigned short)(51001))
#define DUAL_SYNC_SERVICE_PORT		((unsigned short)(51002))
#define DUAL_TIME_SERVICE_PORT		((unsigned short)(51003))
#define DUAL_FLMGR_SERVICE_PORT		((unsigned short)(51004))
#define DUAL_ONLINE_SERVICE_PORT	((unsigned short)(51010))
/* Use the 'get_redun_port() Macro in dual_macro.h to get these ports */
#define REDUN_ENDPOINT_LINK         ((unsigned short)(40218))
#define REDUN_ENDPOINT_PSW          ((unsigned short)(40219))
#define REDUN_ENDPOINT_SYNC         ((unsigned short)(40220))
#define REDUN_ENDPOINT_FILEREP      ((unsigned short)(40221))
#define REDUN_SERVICE_LINK          "hsc_redun_link"
#define REDUN_SERVICE_PSW           "hsc_redun_psw"
#define REDUN_SERVICE_SYNC          "hsc_redun_data"
#define REDUN_SERVICE_FILEREP       "hsc_redun_filerep"


#define DUAL_Q_WAIT_PERIOD		(10000)

#define DUAL_ONLINE_MAXIMUM_INACTIVITY_PERIOD	(30)

#define DUAL_ONLINE_SERVICE_BUFFER_SIZE		(1048576)		// (1024 * 1024) or 1mb
#define DUAL_ONLINE_MAX_MSGS_PER_PKT		(250)

#define DUAL_ONLINE_Q_RETRY_SEC			(0)
#define DUAL_ONLINE_Q_RETRY_USEC		(100000)
#define DUAL_ONLINE_LINK_RETRY_PERIOD		(7)
#define DUAL_ONLINE_SEC_PER_MB				(10)
#define DUAL_ONLINE_MAX_LINK_TIMEOUT		(300)
#define DUAL_ONLINE_MIN_LINK_TIMEOUT		(60)
#define DUAL_ONLINE_ABORT_TIMEOUT			(240)
#define DUAL_ONLINE_STARTUP_TIMEOUT			(180)
#define DUAL_ONLINE_MAX_NETWORK_DATA_SIZE	(4096)

#define DUAL_ONLINE_Q_NAME		("dual_data_q")

#define DUAL_ONLINE_KEEPALIVE_FUNC      (1)
#define DUAL_ONLINE_FILWRT_FUNC         (11)
#define DUAL_ONLINE_DATAIO_FUNC         (12)
#define DUAL_ONLINE_PUTTAG_FUNC         (13)
#define DUAL_ONLINE_DELTAG_FUNC         (14)
#define DUAL_ONLINE_CRGTSK_FUNC         (15)
#define DUAL_ONLINE_DLGTSK_FUNC         (16)
#define DUAL_ONLINE_HISTRY_FUNC         (17)
#define DUAL_ONLINE_EXECUT_FUNC         (18)
#define DUAL_ONLINE_EVARCH_FUNC         (19)
#define DUAL_ONLINE_RAWFIL_FUNC         (20)
#define DUAL_ONLINE_MKDIR_FUNC          (21)
#define DUAL_ONLINE_DMNCNT_FUNC         (22)
#define DUAL_ONLINE_SHHEAP_FUNC         (23)
#define DUAL_ONLINE_SCRIPTCMD_FUNC      (24)
#define DUAL_ONLINE_DBSEQ_FUNC          (25)
#define DUAL_ONLINE_EHMFIL_FUNC         (26)
#define DUAL_ONLINE_EHMRED_FUNC         (27)
#define DUAL_ONLINE_PRIVATEFILE_FUNC    (28)
#define DUAL_ONLINE_THIRDPARTYDB_FUNC   (29)

#define DUAL_EVARCH_WRITE_FUNC  (0)
#define DUAL_EVARCH_CLOSE_FUNC	(1)
#define DUAL_EVARCH_ARCHIV_FUNC	(2)
#define DUAL_EVARCH_EXPIRY_FUNC (3)

// some includes of this file do not include the following definitions
// so defining them if they don't exist
#ifndef EXTERN_C
#define EXTERN_C extern "C"
#endif
#ifndef DLLIMPORT
#define DLLIMPORT __declspec(dllimport)
#endif

EXTERN_C DLLIMPORT int dual_send_gate;	/* if =0 (default), send data to backup */
					/* else do not send data to backup */

struct error_buf_v0
{
    uint2	major_error;
    int2	minor_error;
};

struct error_buf
{
    uint2	major_error;
    int2	spare;
    int4	minor_error;
};

struct response_buf             // used for version 2 protocol
{
    int	             msgno;
    struct error_buf error;
};

struct response_buf_v1          // used for version 1 protocol
{
    int	                msgno;
    struct error_buf_v0 error;
};

struct response_buf_v0          // used for version 0 protocol
{
    struct error_buf_v0 error;
};

struct  redun_trans
    {
        int trans_flag;             // transaction flag
                                    //  0     - NOT a transaction
#define     D_SOT   (1)             //  1     - start of transaction
                                    //  2-n   - middle of transaction (sequential packet #)
#define     D_EOT   (-1)            // -1     - end of transaction
#define     D_APPLY (-2)            // -2     - apply stored transaction */
#define     D_CLEAR (-3)            // -3     - clear stored transaction */
        long transid;               // transaction ID
#define     D_COMPLETE 0x80000000   // marks as complete and prevents duplicate id matches
        int sz;                     // total size of transmitted block
    };

struct  redun_header
    {
        int fn;                 // redundancy function (DATAIO vs FILWRT, etc)
        int target;             // target machine (A to P), multiple bits set
        int msgno;              // client message number (see syssts_def)
    };
#define redun_set_index(nBCC,nBorA)  (nBCC*2+nBorA)
#define redun_set_target(nBCC,nBorA) ((nBCC<0) ? -1 : (1<<(nBCC*2+nBorA)))


struct online_dataio_hdr
    {
    int4	function;
    int4	file;
    int4	record;
    int4	num_rec;
    int4	buffer_len;
    int4	partl_sz;	// used for partial record writes (16bt words)
    };

struct online_filwrt_hdr
    {
    int4	file;
    int4	num_rec;		/* # records sent */
    int4	offst;			/* memory offset or 1st record # */
    int4	buffer_len;		/* compressed data size */
    };

struct online_filwrt_trans
    {
    struct redun_trans          trans;
    struct redun_header         header;
    struct online_filwrt_hdr    hdr;
    };

struct online_evarch_hdr
    {
    int4	evtxmt_func; /* 0 = write, 1 = close, 3 = archive */
    int4	evtrec_len;
    };

struct online_puttag_hdr
    {
    int4	tagnumber;
    int4	tagtype;
    int2	tagarea;
    int2	tagconnection;
    int4	tagname_len;
    };

struct online_deltag_hdr
    {
    int4	tagnumber;
    int4	tagtype;
    int4	tagname_len;
    };

struct online_crgtsk_hdr
    {
    int4	group_len;
    int4	lrn;
    int4	priority;
    int4	pathlen;
    };

struct online_dlgtsk_hdr
    {
    int4	group_len;
    int4	lrn;
    };

struct online_dmncnt_hdr
    {
    int4	name_len;
    int4	target;
    };

struct online_hist_hdr
    {
    int4	hsttyp;
    int4	buffer_len;
    };

struct online_execute_hdr
    {
    int4	cmnd_len;
    };

struct online_mkdir_hdr
    {
    int4        cmnd_len;
    int mode;
    };

struct online_shheap_hdr
    {
    int         function;	// page,close,expand
    int2 	hp_id;
    int2	num_pgs;	// # contiguous pages in a page update
    int		sz;		// data size for PAGEFN
    union
      {
        int	gaddr;		// page global addr (GADDR)
        int	blkno;		// new last block when expanding
      }		u;
    };
#define	SHHDRSZ	(sizeof(struct online_shheap_hdr))

struct online_shheap_trans
    {
    struct redun_trans          trans;
    struct redun_header         header;
    struct online_shheap_hdr    hdr;
    };

// thirdpartydb header
struct online_thirdpartydb_hdr_v1
{
	int4 db_id;
	int4 fn;
	int4 expanded_len;
	int4 compressed_len;
};
struct online_thirdpartydb_hdr
{
    int4 db_id;
    int4 fn;
    int4 expanded_len;
    int4 compressed_len;
    int4 flags;
};
// minimal online_thirdpartydb_hdr structure that includes transaction
struct online_thirdpartydb_trans
{
    struct redun_trans          trans;
    struct redun_header         header;
    struct online_thirdpartydb_hdr  thirdpartydb_hdr;
};

// thirdpartydbxmt Event Names

#define THIRDPARTYDB_SYNC_EVENT_NAME     "Global\\HW.HSC.THIRDPARTYDB.%s.SYNC.EVENT"
#define THIRDPARTYDB_SYNCED_EVENT_NAME   "Global\\HW.HSC.THIRDPARTYDB.%s.SYNCED.EVENT"
#define MAX_THIRDPARTYDB_NAME_SZ         (100)
#define MAX_THIRDPARTYDB_EVENT_NAME_SZ   (sizeof(THIRDPARTYDB_SYNCED_EVENT_NAME) + MAX_THIRDPARTYDB_NAME_SZ)
#define MAX_THIRDPARTYDB_SYNCED_WAIT     (30000)

// On-line Shared Heap and thirdpartydb Function Codes

#define	DATA_FN		(0)
#define	EXPAND_FN	(1)
#define STCOPY_FN	(2)
#define ENDCOPY_FN	(3)
#define ENDSYNC_FN  (4)
#define GETSTS_FN   (5)
#define FAILSYNC_FN (6)

struct script_hdr
{
	int ID;		/* Engine to control */
	int cmd;	/* control code. Codes defined in scriptingfunctions.h */
};



// Struct for EHM file transfer
struct dual_ehmfil_hdr
{
	int4 ehmxmt_func;	/* DUAL_EHM_SYNCH_REQ (0) = synch, DUAL_EHM_ARCHIVE_REQ (1) = archive */
	int4 flags;
};

// Struct for EHM redundant write transfer
struct dual_ehmredwrt_hdr
{
	int4 compress_length;
	int4 decompress_length;
	int4 flags;			/* DUAL_EHM_COMPRESSED_BUFFER */
};

// EHM Dual Synch/Archive Macros
#define DUAL_EHM_SYNCH_REQ			(0)			// Online sync. request (ehmxmt_func)
#define DUAL_EHM_ARCHIVE_REQ		(1)			// Archive request (ehmxmt_func)
#define DUAL_EHM_RECENT_FILE		(0x0001)	// Flag for transfer of EHM recent history file
#define	EHMHDRSZ		(sizeof(struct dual_ehmfil_hdr))

// EHM Dual Redundant History Values
#define DUAL_EHM_COMPRESSED_BUFFER	(0x0001)	// Flag indicating compressed buffer
#define EHMHSTHDRSZ		(sizeof(struct dual_ehmredwrt_hdr))

//////////////////////////////////////////////////////////////////////////
// private file update header definition
typedef struct
{
    uint4 hdrsize;  // header size:     this is the number of bytes in this header structure
    uint4 recoff;   // record offset:   this is the byte offset into a record buffer where the record number is stored
    uint4 recsiz;   // record size:     this is the byte size of a single record
    uint4 reccnt;   // record count:    this is the number of records in the buffer
    uint4 maprec;   // mapped records:  this is the number of records mapped into memory in the file
    uint4 maxrec;   // maximum records: this is the total maximum number of records in the file
} PRIVATEFILE_UPDATE_HEADER;

#define PRIVATEFILE_UPDATE_HEADER_SIZE (sizeof(PRIVATEFILE_UPDATE_HEADER))

#define PRIVATEFILE_SYNC_NAME           "privatefile_%hu_sync.pvf"


//////////////////////////////////////////////////////////////////////////
// direct station definitions

// direct station directory file sequence numbers
struct	online_dbseq_hdr
    {
    int4    systm_seq;  // system sequence #
    int4    num_files;  // number of file sequence #s
    int4    sz;         // compressed sequence buffer sz (bytes)
    };


struct dual_file_hdr
    {
    int4	modfd_tm;
    uint2	mode;
    uint2	owner;
    uint2	group;
    int4	fl_size;
    int4	nm_size;
    int2	open_mode;
    int2	flags;
#if defined NT
    FILETIME ftc;
    FILETIME fta;
    FILETIME ftm;
#endif
    };
#define	FLMNGR_BLDLSTI	(0)	/* build list starting from path */
#define	FLMNGR_BLDLSTX	(1)	/* exclude these files */
#define	FLMNGR_FLDATA	(2)

/* flags (flag) for the file transfer */
#define SNDUFL_CLOSE_CONNECTION	(0x0001) /* ignored if using RPC */

/* flags (flag2) for the file transfer */
#define FILE_OVERWRITE	(0x0001)	/* ignore timestamp of file on the backup  */
#define FILE_DELETE		(0x0002)	/* delete the specified file on the backup */
#define DIR_DELETE		(0x0003)	/* delete the specified directory tree on the backup */
#define DUAL_FLMASK		(0x000f)	/* allow 4 bits for file/directory flags */
#define DUAL_RPT_ERR	(0x0010)	/* report peer file system errors to caller */
#define DUAL_ISDATADIR  (0x0020)	/* sending from the data directory */


/* response codes */
#define	S_U_NOTOK	(-1)
#define	S_U_OK		(0)
#define	S_U_PATH	(1)	/* path not found */
#define	S_U_OPN		(2)	/* cant open file */
#define	S_U_WRT		(3)	/* cant write file */
#define	S_U_TIME	(4)	/* primary file not later */
#define	S_U_TO	    (5)	/* data timeout */

/* snd_u_fl error codes */
#define SNDUFL_OK             0
#define SNDUFL_ERROR_NETWORK -1
#define SNDUFL_ERROR_FILE    -2
#define SNDUFL_ERROR_ARGS    -3

/* defaults for SQLRep and Event DB synchs in minutes */
#define	SQL_SYNCH_TIMEOUT_DEFAULT	(30)
#define	EMS_SYNCH_TIMEOUT_DEFAULT	(30)

// Flags for filwrt() and filxmt()
#define FILWRT_SEND_TO_BACKUP		(0)
#define FILWRT_NO_SEND_TO_BACKUP	(1)

//////////////////////////////////////////////////////////////////////////
// DUAL queue routines

EXTERN_C struct unix_queue *q_open(char *queue);
EXTERN_C int                q_seg_rd(struct unix_queue *qp, char** buffer, unsigned* buf_size);
EXTERN_C int                q_seg_rd_reset();
EXTERN_C void               q_remove();

//////////////////////////////////////////////////////////////////////////
// svc_trans transaction statuses

#ifdef __cplusplus

enum struct TRANSACTION_SYNC_STATUS
{
    UNSYNCHED = 0,
    INPROGRESS,
    TOBEAPPLIED,
    SYNCHED
};

struct TRANSACTION_SYNC_INFO
{
    TRANSACTION_SYNC_STATUS status;
    // The following are currently used for thirdpartydbs only.  If additional fields need
    // adding for heaps, these can be moved into a union.
    bool bSynch;
    int4 flags;
};

static const int4 GETSTS_COMPLETE_FLAG = 0x1;

#define TRANSSYNCH_ERROR_FLAG_FIRST 1
#define TRANSSYNCH_ERROR_FLAG_LAST 16

inline int hsc_get_transsynch_error_flag(int nId)
{
    return (1 << nId);
}

inline int hsc_transsynch_id_to_error_id(int nFunction, int nId)
{
    return nFunction == DUAL_ONLINE_SHHEAP_FUNC ? nId + 1 : nId;
}

inline int hsc_error_id_to_transsynch_id(int nFunction, int nId)
{
    return nFunction == DUAL_ONLINE_SHHEAP_FUNC ? nId - 1 : nId;
}

#endif

//////////////////////////////////////////////////////////////////////////
// servicing routines

struct trans_threads {
    HANDLE hThread;     // thread handle (needs to be visible to main)
    DWORD  nThread;     // thread id
    int	   nFunction;	// function this thread is servicing
    int	   nId;	        // id of the database this thread is servicing
    };

typedef struct {
    char*        rcv_buf;       // network receive buffer
    char*        exp_buf;       // decompression buffer
    char*        hst_buf;       // history buffer
    char*        cnt_buf;       // history counts buffer
    unsigned int rcv_buf_sz;    // network receive buffer size
    unsigned int exp_buf_sz;    // decompression buffer size
    unsigned int hst_buf_sz;    // history buffer size
    unsigned int cnt_buf_sz;    // history counts buffer size
    } DUAL_SVC_BUFFERS;

typedef struct {
    int                 network;        // network socket
    int                 nBCC;           // clients BCC number
    int                 nBorA;          // clients BorA
    int                 nVersion;       // protocol version to use
    struct sockaddr_in  address;        // clients address
    struct error_buf    error;          // set non 0 if error found
    int                 function_code;  // last function we read
    int                 dup_flg;        // set to 1 if duplicate message found (0 good, -1 error)
    uint2               msgno;          // last message number
    } DUAL_SVC_HANDLE;

#ifndef _DECLARE
#ifdef NT
#define _DECLARE(formal_parameters) formal_parameters
#else
#define _DECLARE(formal_parameters) ()
#endif
#endif /* _DECLARE */

EXTERN_C int svc_req            _DECLARE((DUAL_SVC_HANDLE*, DUAL_SVC_BUFFERS*));
EXTERN_C int service_request    _DECLARE((DUAL_SVC_HANDLE*, DUAL_SVC_BUFFERS*, struct error_buf*));
EXTERN_C int svc_keepalive      _DECLARE((DUAL_SVC_HANDLE*, DUAL_SVC_BUFFERS*, struct error_buf*));
EXTERN_C int svc_crgtsk         _DECLARE((DUAL_SVC_HANDLE*, DUAL_SVC_BUFFERS*, struct error_buf*));
EXTERN_C int svc_dataio         _DECLARE((DUAL_SVC_HANDLE*, DUAL_SVC_BUFFERS*, struct error_buf*));
EXTERN_C int svc_dbseq          _DECLARE((DUAL_SVC_HANDLE*, DUAL_SVC_BUFFERS*, struct error_buf*));
EXTERN_C int svc_deltag         _DECLARE((DUAL_SVC_HANDLE*, DUAL_SVC_BUFFERS*, struct error_buf*));
EXTERN_C int svc_dlgtsk         _DECLARE((DUAL_SVC_HANDLE*, DUAL_SVC_BUFFERS*, struct error_buf*));
EXTERN_C int svc_dmncnt         _DECLARE((DUAL_SVC_HANDLE*, DUAL_SVC_BUFFERS*, struct error_buf*));
EXTERN_C int svc_execute        _DECLARE((DUAL_SVC_HANDLE*, DUAL_SVC_BUFFERS*, struct error_buf*));
EXTERN_C int svc_filwrt         _DECLARE((DUAL_SVC_HANDLE*, DUAL_SVC_BUFFERS*, struct error_buf*));
EXTERN_C int svc_heap           _DECLARE((DUAL_SVC_HANDLE*, DUAL_SVC_BUFFERS*, struct error_buf*));
EXTERN_C int svc_history        _DECLARE((DUAL_SVC_HANDLE*, DUAL_SVC_BUFFERS*, struct error_buf*));
EXTERN_C int svc_mkdir          _DECLARE((DUAL_SVC_HANDLE*, DUAL_SVC_BUFFERS*, struct error_buf*));
EXTERN_C int svc_puttag         _DECLARE((DUAL_SVC_HANDLE*, DUAL_SVC_BUFFERS*, struct error_buf*));
EXTERN_C int svc_scriptcmd      _DECLARE((DUAL_SVC_HANDLE*, DUAL_SVC_BUFFERS*, struct error_buf*));
EXTERN_C int svc_trans          _DECLARE((DUAL_SVC_HANDLE*, struct redun_trans*, struct error_buf*));
EXTERN_C int steward_trans      _DECLARE((DUAL_SVC_HANDLE*, const char*, const struct redun_trans*, struct error_buf*));
EXTERN_C int svc_ehmfil         _DECLARE((DUAL_SVC_HANDLE*, DUAL_SVC_BUFFERS*, struct error_buf*));
EXTERN_C int svc_ehmhstxmt      _DECLARE((DUAL_SVC_HANDLE*, DUAL_SVC_BUFFERS*, struct error_buf*));
EXTERN_C int svc_privatefilexmt _DECLARE((DUAL_SVC_HANDLE*, DUAL_SVC_BUFFERS*, struct error_buf*));
EXTERN_C int svc_thirdpartydb   _DECLARE((DUAL_SVC_HANDLE*, DUAL_SVC_BUFFERS*, struct error_buf*));

//////////////////////////////////////////////////////////////////////////
// data access  routines
EXTERN_C int hsc_redun_close    _DECLARE((DUAL_SVC_HANDLE*));
EXTERN_C int hsc_redun_read     _DECLARE((DUAL_SVC_HANDLE*, char*, int));
EXTERN_C int hsc_redun_write    _DECLARE((DUAL_SVC_HANDLE*, char*, int));
EXTERN_C int hsc_redun_flush    _DECLARE((DUAL_SVC_HANDLE*));


/************************************************************************/
/*****     COPYRIGHT 2008 - 2016    HONEYWELL INTERNATIONAL SARL     ****/
/************************************************************************/

#endif	/* end of conditional include _flag */
