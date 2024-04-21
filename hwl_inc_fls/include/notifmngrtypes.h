

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Mon Jun 05 17:32:29 2017
 */
/* Compiler settings for C:\Users\H109393\AppData\Local\Temp\2\notifmngrtypes.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __notifmngrtypes_h__
#define __notifmngrtypes_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

/* header files for imported files */
#include "hsctypes.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_notifmngrtypes_0000_0000 */
/* [local] */ 

typedef /* [v1_enum] */ 
enum NOTIFINDEXTYPE
    {
        NOTIFINDEXTYPE_INVALID	= -1,
        NOTIFINDEXTYPE_ALARMS	= 0,
        NOTIFINDEXTYPE_SYSTEMALARMS	= ( NOTIFINDEXTYPE_ALARMS + 1 ) ,
        NOTIFINDEXTYPE_ALERTS	= ( NOTIFINDEXTYPE_SYSTEMALARMS + 1 ) ,
        NOTIFINDEXTYPE_MESSAGES	= ( NOTIFINDEXTYPE_ALERTS + 1 ) ,
        NOTIFINDEXTYPE_ALLALARMS	= ( NOTIFINDEXTYPE_MESSAGES + 1 ) ,
        NOTIFINDEXTYPE_COUNT	= ( NOTIFINDEXTYPE_ALLALARMS + 1 ) 
    } 	NOTIFINDEXTYPE;

typedef /* [v1_enum] */ 
enum NOTIFTYPE
    {
        TYPE_INVALID	= 0,
        TYPE_ALARMS	= ( TYPE_INVALID + 1 ) ,
        TYPE_ALERTS	= ( TYPE_ALARMS + 1 ) ,
        TYPE_MESSAGES	= ( TYPE_ALERTS + 1 ) ,
        TYPE_EVENTS	= ( TYPE_MESSAGES + 1 ) ,
        TYPE_COUNT	= ( TYPE_EVENTS + 1 ) 
    } 	NOTIFTYPE;

typedef uint4 NOTIFINDEXID;

#define	NOTIFTYPE_MASK	( 0xc0000000 )

#define	NOTIFTYPE_OFFSET	( 30 )

#define	NOTIFMNGRID_MASK	( 0xff0000 )

#define	NOTIFMNGRID_OFFSET	( 16 )

#define	NOTIFID_MASK	( 0xffff )

#define	INVALID_INDEXID	( 0xffffffff )

typedef struct VIEWDATA
    {
    NOTIFTYPE nNotifType;
    BOOL bDeleted;
    BOOL bTimeModified;
    int2 nDirSize;
    int2 nFilSize;
    /* [string][unique] */ unsigned char *szSuppressionGroup;
    /* [size_is][unique] */ int2 *pDirBuffer;
    /* [size_is][unique] */ int2 *pFilBuffer;
    } 	VIEWDATA;

typedef /* [v1_enum] */ 
enum VIEWCOUNT
    {
        COUNT_UNACKED	= 0,
        COUNT_ACKED	= ( COUNT_UNACKED + 1 ) ,
        COUNT_SHELVED	= ( COUNT_ACKED + 1 ) ,
        COUNT_SUPPRESSED	= ( COUNT_SHELVED + 1 ) ,
        COUNT_MAX	= ( COUNT_SUPPRESSED + 1 ) 
    } 	VIEWCOUNT;

typedef struct VIEWCOUNTS
    {
    int2 nCounts;
    /* [size_is][unique] */ uint4 *pTotalCounts;
    /* [size_is][unique] */ uint4 *pFilteredCounts;
    } 	VIEWCOUNTS;

typedef /* [v1_enum] */ 
enum INDEXERROR
    {
        S_INVALIDINDEX	= 2,
        S_INVALIDINDEXTYPE	= ( S_INVALIDINDEX + 1 ) ,
        S_INVALIDFILTER	= ( S_INVALIDINDEXTYPE + 1 ) ,
        S_OUTOFMEMORY	= ( S_INVALIDFILTER + 1 ) ,
        S_POINTER	= ( S_OUTOFMEMORY + 1 ) ,
        S_INVALIDARG	= ( S_POINTER + 1 ) 
    } 	INDEXERROR;

#define	PubIsLocalOnly	( 0x1 )

#define	PubIsClusterOnly	( 0x2 )

#define	PubIsNonDirect	( 0x4 )

#define	PubIsPointNotif	( 0x8 )

#define	PubIsInRecovery	( 0x10 )

#define	PubIsActivityNotif	( 0x20 )

#define	PubActionMask	( 0xf000 )

#define	PubActionRecBegin	( 0x1000 )

#define	PubActionRecEnd	( 0x2000 )

#define	PubActionAdd	( 0x3000 )

#define	PubActionDel	( 0x4000 )

#define	PubActionChg	( 0x5000 )

#define	PubActionRec	( 0x6000 )

typedef struct NOTIFPUB
    {
    NOTIFTYPE nNotifType;
    NOTIFCOOKIE nCookie;
    HSCTIME HostTime;
    int8 nEventId;
    int2 nConnection;
    int2 nArea;
    PNTNUM nParent;
    PNTNUM nAssocAsset;
    uint4 nPubReason;
    uint2 nPubFlags;
    uint2 nPointNameLen;
    uint2 nDirSize;
    uint2 nFilSize;
    uint2 nBufSize;
    /* [size_is][unique] */ BYTE *pBuffer;
    } 	NOTIFPUB;

typedef NOTIFPUB *LPNOTIFPUB;

typedef 
enum CHANGER
    {
        CHANGER_DONTCARE	= 0,
        CHANGER_NOTIFSYNC	= ( CHANGER_DONTCARE + 1 ) ,
        CHANGER_GDACLIENT_DSA	= ( CHANGER_NOTIFSYNC + 1 ) ,
        CHANGER_GDACLIENT_CSTN	= ( CHANGER_GDACLIENT_DSA + 1 ) ,
        CHANGER_OPCCLIENT	= ( CHANGER_GDACLIENT_CSTN + 1 ) 
    } 	CHANGER;

typedef /* [v1_enum] */ 
enum NOTIFACTION
    {
        NOTIFACTION_ZERO	= 0,
        NOTIFACTION_SILENCE	= 1,
        NOTIFACTION_ACK	= 2,
        NOTIFACTION_RESPOND	= 3,
        NOTIFACTION_RESET	= 4,
        NOTIFACTION_SHELVE	= 5,
        NOTIFACTION_UNSHELVE	= 6,
        NOTIFACTION_CONFIRM	= 7,
        NOTIFACTION_CLEAR	= 8,
        NOTIFACTION_ACKPNT	= 9,
        NOTIFACTION_ADDCOMMENT	= 10,
        NOTIFACTION_DEL	= 11,
        NOTIFACTION_COUNT	= 12
    } 	NOTIFACTION;

typedef struct ACTIONDATA_SILENCE
    {
    HSCTIME SilenceTime;
    } 	ACTIONDATA_SILENCE;

typedef struct ACTIONDATA_ACK
    {
    uint2 nAlmMgmtMethod;
    } 	ACTIONDATA_ACK;

typedef struct ACTIONDATA_RESPOND
    {
    uint2 nAlmMgmtMethod;
    /* [string] */ unsigned char *szResponse;
    } 	ACTIONDATA_RESPOND;

typedef struct ACTIONDATA_RESET
    {
    uint2 nAlmMgmtMethod;
    } 	ACTIONDATA_RESET;

typedef struct ACTIONDATA_SHELVE
    {
    /* [string] */ unsigned char *szReason;
    /* [string] */ unsigned char *szComments;
    HSCTIME ShelveTime;
    HSCTIME ExpireTime;
    int2 nReasonIdx;
    int2 nPeriodIdx;
    uint2 nUnshelvedDelay;
    } 	ACTIONDATA_SHELVE;

typedef struct ACTIONDATA_UNSHELVE
    {
    HSCTIME ShelveTime;
    } 	ACTIONDATA_UNSHELVE;

typedef struct ACTIONDATA_CONFIRM
    {
    long placeholder_del_me;
    } 	ACTIONDATA_CONFIRM;

typedef struct ACTIONDATA_CLEAR
    {
    long placeholder_del_me;
    } 	ACTIONDATA_CLEAR;

typedef struct ACTIONDATA_ACKPNT
    {
    PNTNUM nPoint;
    uint2 nEE;
    uint4 nBB;
    HSCTIME AckUpToTime;
    BOOL bSuppressEvent;
    } 	ACTIONDATA_ACKPNT;

typedef struct ACTIONDATA_ADDCOMMENT
    {
    BOOL bSuppressEvent;
    /* [string] */ unsigned char *szCommentText;
    } 	ACTIONDATA_ADDCOMMENT;

typedef struct ACTIONDATA_DEL
    {
    uint2 nConnection;
    uint2 nPointCount;
    /* [size_is][unique] */ PNTNUM *pPoints;
    } 	ACTIONDATA_DEL;

typedef /* [switch_type] */ union ACTIONUNION
    {
    /* [case()] */ ACTIONDATA_SILENCE silence;
    /* [case()] */ ACTIONDATA_ACK ack;
    /* [case()] */ ACTIONDATA_RESPOND respond;
    /* [case()] */ ACTIONDATA_RESET reset;
    /* [case()] */ ACTIONDATA_SHELVE shelve;
    /* [case()] */ ACTIONDATA_UNSHELVE unshelve;
    /* [case()] */ ACTIONDATA_CONFIRM confirm;
    /* [case()] */ ACTIONDATA_CLEAR clear;
    /* [case()] */ ACTIONDATA_ACKPNT ackpnt;
    /* [case()] */ ACTIONDATA_ADDCOMMENT addcomment;
    /* [case()] */ ACTIONDATA_DEL del;
    /* [default] */  /* Empty union arm */ 
    } 	ACTIONUNION;

typedef struct ACTIONDATA
    {
    NOTIFACTION action;
    NOTIFCOOKIE cookie;
    CHANGER changer;
    /* [switch_is] */ ACTIONUNION data;
    } 	ACTIONDATA;

#define	INIT_NOTIFLIST	( 0x1 )

#define	INIT_NOTIFSYNC	( 0x2 )

typedef struct CONTEXTFILTER
    {
    NOTIFTYPE nType;
    uint4 nFlags;
    int2 nOrderByIdx;
    int2 nFilterByIdx;
    /* [string] */ unsigned char *szFilter;
    uint2 nPointCount;
    /* [size_is][unique] */ PNTNUM *pFilterByPoints;
    uint2 nAreaCount;
    /* [size_is][unique] */ int2 *pFilterByAreas;
    uint4 nLowerBound;
    uint4 nUpperBound;
    } 	CONTEXTFILTER;

#define	CONTEXTFILTER_FLAG_POINT_NOTIFICATIONS_ONLY	( 0x1 )

#define	CONTEXTFILTER_FLAG_SYSTEM_NOTIFICATIONS_ONLY	( 0x2 )

#define	CONTEXTFILTER_FLAG_NON_SYSTEM_NOTIFICATIONS_ONLY	( 0x4 )

typedef uint8 NSTIME;

typedef struct NSKEY
    {
    uint2 nClass;
    uint2 nArea;
    uint2 nConnection;
    uint2 nOrgConnection;
    uint4 nPoint;
    uint2 nParam;
    uint2 nType;
    uint2 nSubtype;
    uint2 nEE;
    uint4 nBB;
    NSTIME InstanceTime;
    } 	NSKEY;

typedef NSKEY *PNSKEY;

#define	TIME_COUNT	( 5 )

#define	ACTIVE	( 0 )

#define	ACTIVE_ACKED	( 1 )

#define	ACTIVE_CONFIRMED	( 2 )

#define	ACTIVE_CLEARED	( 3 )

#define	ACTIVE_SHELVED	( 2 )

#define	REAL_SHELVED	( 3 )

#define	REAL_EXPIRE	( 4 )

typedef struct NSDATA
    {
    NSTIME Times[ 5 ];
    NSTIME LastUsedTime;
    int8 nTransId;
    uint2 nFlags;
    int2 nExpireBias;
    uint2 nUnshelvedDelay;
    unsigned char szShelvedReason[ 31 ];
    } 	NSDATA;

typedef NSDATA *PNSDATA;

#define	NSDATA_FLAG_SHELVED	( 0x1 )

#define	NSDATA_FLAG_SHELVEDUNTILRTN	( 0x2 )

#define	ACTION_SYNCREQ	( 0x1 )

#define	ACTION_UPDATE	( 0x2 )

#define	ACTION_NEW	( 0x3 )

#define	ACTION_RECOVERY	( 0x4 )

#define	ACTION_GETNOTIF	( 0x5 )

#define	CLASS_ALARM	( 0x1 )

#define	CLASS_MESSAGE	( 0x2 )

#define	CLASS_RECOVERY_ALL	( 0x8 )

#define	CLASS_RECOVERY_AREA	( 0x9 )

#define	CLASS_RECOVERY_EE	( 0xa )

#define	CLASS_RECOVERY_PNT	( 0xb )

#define	CLASS_RECOVERY_EEPNT	( 0xc )

#define	CLASS_RECOVERY_BBEEPNT	( 0xd )

#define	CLASS_RECOVERY_CON	( 0xe )

#define	STATE_ACKED	( 0x1 )

#define	STATE_CONFIRMED	( 0x2 )

#define	STATE_SHELVED	( 0x4 )

#define	STATE_CLEARED	( 0x8 )

#define	STATE_GETCANDIDATE	( 0x10 )

#define	STATE_TRANSID	( 0x20 )

#define	STATE_UNSHELVED	( 0x40 )

#define	STATE_SHELVEDUNTILRTN	( 0x80 )

#define	STATE_AUTOUNSHELVED	( 0x100 )

typedef struct NSACTION
    {
    uint2 nAction;
    uint2 nState;
    uint2 nConsole;
    uint2 nNodeId;
    NOTIFCOOKIE nCookie;
    NSKEY key;
    NSDATA data;
    } 	NSACTION;

#define	CONSOLE_MASK	( 0xfff )

#define	CONSOLE_FILTER_MASK	( 0xf000 )

#define	CONSOLE_FILTER_PASSED	( 0x1000 )

#define	CONSOLE_FILTER_NOTINSOR	( 0x2000 )

#define	CONSOLE_FILTER_REJECTED	( 0x3000 )

typedef NSACTION *PNSACTION;

typedef struct NSNOTIF
    {
    uint4 nNotifParent;
    uint4 nNotifPoint;
    uint2 nNotifParam;
    uint2 nNotifTargetParam;
    uint2 nNotifDataSize;
    uint2 nStringRefSize;
    uint2 nStringBlockSize;
    uint2 nExtStringBlockSize;
    uint2 nStringBlockCount;
    uint2 nSize;
    /* [size_is][unique] */ BYTE *pCompressedNotif;
    } 	NSNOTIF;

typedef NSNOTIF *PNSNOTIF;



extern RPC_IF_HANDLE __MIDL_itf_notifmngrtypes_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_notifmngrtypes_0000_0000_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


