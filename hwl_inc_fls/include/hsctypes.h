

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Mon Jun 05 17:41:49 2017
 */
/* Compiler settings for C:\Users\H109393\AppData\Local\Temp\2\hsctypes.idl:
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


#ifndef __hsctypes_h__
#define __hsctypes_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "propidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_hsctypes_0000_0000 */
/* [local] */ 

#ifndef hsctypes_flag
#define hsctypes_flag
typedef short int2;

typedef unsigned short uint2;

typedef long int4;

typedef unsigned long uint4;

typedef unsigned char uchar;

typedef __int64 int8;

typedef unsigned __int64 uint8;

#ifdef	NT
typedef unsigned short ushort;

typedef unsigned long ulong;

#endif
typedef FILETIME HSCTIME;

typedef int2 PNTRELTYP;

typedef int2 PNTRELDIR;

typedef uint2 PPTNUM;

typedef uint2 PRMNUM;

typedef int2 PRMTYP;

typedef uint4 PRMDEF;

typedef uint4 PNTNUM;

typedef uint2 PNTNUM16;

typedef int2 PNTTYP;

typedef uint4 IDXNUM;

typedef int GINDEX;

typedef long CREATETIME;

#define	NOCREATETIME	( -1 )

union minus_zero_tmp_var
    {
    float fval;
    long lval;
    } ;
typedef struct tagGDAERR
    {
    DWORD Code;
    DWORD Qualifier;
    } 	GDAERR;

typedef struct tagGDASERVAR
    {
    DWORD cSize;
    /* [size_is] */ unsigned char *pData;
    } 	GDASERVAR;

#define	GDASECURITY_CONTCNTRL	( 0x100 )

#define	GDASECURITY_PROGRAM	( 0x200 )

typedef struct tagGDASECURITY
    {
    int2 StationLevel;
    int2 ControlLevel;
    /* [string] */ unsigned char *pOperID;
    /* [string] */ unsigned char *pOperName;
    } 	GDASECURITY;

typedef struct tagENUMITEM
    {
    /* [string] */ unsigned char *pText;
    int Value;
    } 	ENUMITEM;

typedef struct tagITEMHANDLE
    {
    uint2 Point;
    uint2 Param;
    } 	ITEMHANDLE;

typedef struct tagPNTPRMPAIR
    {
    PNTNUM Point;
    PRMNUM Param;
    } 	PNTPRMPAIR;

typedef struct tagGDAALARMHANDLE
    {
    DWORD EECode;
    DWORD BBIndex;
    } 	GDAALARMHANDLE;

typedef struct tagPOINTREF
    {
    /* [string] */ unsigned char *pAlias;
    /* [string] */ unsigned char *pPointName;
    /* [string] */ unsigned char *pPointDescription;
    /* [string] */ unsigned char *pPointArea;
    CREATETIME PointCreateTime;
    } 	POINTREF;

typedef struct tagPOINTREFLIST
    {
    DWORD cPoints;
    /* [size_is] */ POINTREF *Point;
    } 	POINTREFLIST;

typedef struct tagPOINTREF2
    {
    POINTREF PointRef;
    /* [string] */ unsigned char *pPointLocation;
    /* [string] */ unsigned char *pPointItemName;
    /* [string] */ unsigned char *pPointOwner;
    /* [string] */ unsigned char *pPointGuid;
    short PointType;
    short PointSubtype;
    } 	POINTREF2;

typedef struct PerformanceStatsData
    {
    int InstanceID;
    int Value;
    /* [string] */ wchar_t *Timestamp;
    int Type;
    } 	PerformanceStatsData;

typedef struct PerformanceStringMap
    {
    int InstanceId;
    /* [string] */ wchar_t *Name;
    } 	PerformanceStringMap;

typedef struct tagPNTalmcount
    {
    uint4 CriticalRTNUnackAlms;
    uint4 CriticalActiveUnackAlms;
    uint4 CriticalActiveAckAlms;
    uint4 UrgentRTNUnackAlms;
    uint4 UrgentActiveUnackAlms;
    uint4 UrgentActiveAckAlms;
    uint4 HighRTNUnackAlms;
    uint4 HighActiveUnackAlms;
    uint4 HighActiveAckAlms;
    uint4 LowRTNUnackAlms;
    uint4 LowActiveUnackAlms;
    uint4 LowActiveAckAlms;
    uint4 TotalUnackInfoMsgs;
    uint4 TotalUnackUnconfConfMsgs;
    uint4 TotalAckUnconfConfMsgs;
    int2 Station;
    uint2 SpareWord;
    uint4 LastReadTime;
    uint4 DisabledAlms;
    uint4 TotalRTNUnackAlts;
    uint4 TotalActiveUnackAlts;
    uint4 TotalActiveAckAlts;
    uint4 DisabledAlts;
    uint4 ShelvedAlms;
    uint4 ShelvedAlts;
    uint4 TotalAckInfoMsgs;
    uint4 TotalAckConfConfMsgs;
    uint4 TotalUnackConfConfMsgs;
    uint4 SuppressedAlms;
    uint4 AlarmState;
    } 	PNTalmcount;

typedef struct tagPOINTREF2LIST
    {
    DWORD cPoints;
    /* [size_is] */ POINTREF2 *Point;
    } 	POINTREF2LIST;

typedef PROPVARIANT GDAVARIANT;

typedef struct tagAREAPTLIST
    {
    /* [string] */ unsigned char *szareaname;
    int numpts;
    /* [string][size_is][size_is] */ unsigned char **pszptnames;
    } 	AREAPTLIST;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_hsctypes_0000_0000_0001
    {
        AREA_CHANGE	= 1,
        CON_DEL	= 2,
        CON_MAN_REFRESH	= 3
    } 	TCEVENTCODE;

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_hsctypes_0000_0000_0002
    {
        LINEAR_INTERPOLATION	= 1,
        STEP_INTERPOLATION	= 2
    } 	INTERPOLATION_TYPE;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_hsctypes_0000_0000_0003
    {
        PARAM_ATTRIB_INVALID	= 0,
        PARAM_ATTRIB_PVFORMAT	= ( PARAM_ATTRIB_INVALID + 1 ) ,
        PARAM_ATTRIB_CTRLCONFIRM	= ( PARAM_ATTRIB_PVFORMAT + 1 ) ,
        PARAM_ATTRIB_CANVALIDATE	= ( PARAM_ATTRIB_CTRLCONFIRM + 1 ) ,
        PARAM_ATTRIB_LIMIT_TARGET	= ( PARAM_ATTRIB_CANVALIDATE + 1 ) ,
        PARAM_ATTRIB_PVFORMAT_RAW	= ( PARAM_ATTRIB_LIMIT_TARGET + 1 ) ,
        PARAM_ATTRIB_LIMIT_ALL	= ( PARAM_ATTRIB_PVFORMAT_RAW + 1 ) ,
        PARAM_ATTRIB_LIMIT_NAMES	= ( PARAM_ATTRIB_LIMIT_ALL + 1 ) ,
        PARAM_ATTRIB_LIMIT_HELP	= ( PARAM_ATTRIB_LIMIT_NAMES + 1 ) ,
        PARAM_ATTRIB_TOTAL	= ( PARAM_ATTRIB_LIMIT_HELP + 1 ) 
    } 	PARAM_ATTRIBUTE_TYPE;

typedef /* [switch_type] */ union tag_GDAVALUEUNION
    {
    /* [case()][string] */ unsigned char *pText;
    /* [case()] */ short int2;
    /* [case()] */ int int4;
    /* [case()] */ int8 int8;
    /* [case()] */ float real;
    /* [case()] */ double dble;
    /* [case()] */ ENUMITEM en;
    /* [case()] */ GDAERR Status;
    /* [case()] */ GDASERVAR servar;
    /* [case()] */ POINTREFLIST PointList;
    /* [case()] */ POINTREF2LIST PointList2;
    /* [case()] */ GDAVARIANT *pVar;
    /* [case()] */ HSCTIME time;
    /* [case()] */ GDAALARMHANDLE AlarmHandle;
    /* [default] */  /* Empty union arm */ 
    } 	GDAVALUEUNION;

typedef struct tag_GDAITEM
    {
    /* [switch_is] */ GDAVALUEUNION Value;
    short sValueType;
    uchar ucQuality;
    } 	GDAITEM;

typedef /* [public] */ struct __MIDL___MIDL_itf_hsctypes_0000_0000_0004
    {
    unsigned char cEvent[ 4 ];
    } 	GDAHANDLE;

typedef /* [public][public][public] */ struct __MIDL___MIDL_itf_hsctypes_0000_0000_0005
    {
    uint4 dwLrn;
    uint4 dwProcessId;
    uint4 dwThreadId;
    uint4 dwTraceId;
    /* [string] */ unsigned char *szName;
    /* [string] */ wchar_t *pszExtraClientInfo;
    } 	GDACLIENT;

typedef /* [public][public] */ struct __MIDL___MIDL_itf_hsctypes_0000_0000_0006
    {
    uint8 ListId;
    GDACLIENT Client;
    int Period;
    int LastAccessed;
    } 	SUBCLIENT;

typedef /* [public] */ struct __MIDL___MIDL_itf_hsctypes_0000_0000_0007
    {
    int2 Items;
    /* [size_is] */ SUBCLIENT *pClients;
    } 	SUBCLIENTS;

typedef /* [public] */ struct __MIDL___MIDL_itf_hsctypes_0000_0000_0008
    {
    uint8 key;
    PNTNUM PointNum;
    PRMNUM ParamNum;
    /* [string] */ unsigned char *szClientName;
    unsigned long Period;
    int iDynScnPeriod;
    } 	GDASUBSCRIPTION;

typedef /* [public] */ struct __MIDL___MIDL_itf_hsctypes_0000_0000_0009
    {
    /* [string] */ unsigned char *szSubscriberAddress;
    BOOL bIsDSAAdvSec;
    /* [string] */ unsigned char *szDSAImplicitAcct;
    /* [string] */ unsigned char *szDSAExplicitAcct;
    } 	GDAADVDSA;

typedef /* [switch_type] */ union tag_HSTUNION
    {
    /* [case()][string] */ unsigned char *pStr;
    /* [case()] */ short i2;
    /* [case()] */ int i4;
    /* [case()] */ int8 i8;
    /* [case()] */ float flt;
    /* [case()] */ double dbl;
    /* [case()] */ ENUMITEM en;
    /* [case()] */ GDAVARIANT *pVar;
    /* [case()] */ HSCTIME time;
    /* [default] */  /* Empty union arm */ 
    } 	HSTUNION;

typedef struct tag_HSTVALUE
    {
    short sValueType;
    /* [switch_is] */ HSTUNION Value;
    } 	HSTVALUE;

typedef struct tag_HSTARRAY
    {
    long lMaxValues;
    long lNumValues;
    INTERPOLATION_TYPE eInterpolationType;
    /* [size_is] */ HSCTIME *pTimestamp;
    /* [size_is] */ short *pBias;
    /* [size_is] */ long *pQuality;
    /* [size_is] */ HSTVALUE *pValue;
    } 	HSTARRAY;

typedef struct tag_EVENTVIEWDATA
    {
    VARIANT vCellData;
    LONG lViewSize;
    LONG lNumFields;
    LONG pkSelectedRow;
    VARIANT vSelectedRowData;
    LONG lTableSize;
    LONG lViewPosn;
    DATE dtServerTime;
    LONG lUpdateFlags;
    LONG lUpdateFlags2;
    BOOL bCellDataChanged;
    int2 nSelectedEventBufSize;
    /* [size_is][unique] */ int2 *pSelectedEventBuffer;
    VARIANT vTrendCellData;
    LONG lTrendViewSize;
    LONG lTrendNumFields;
    } 	EVENTVIEWDATA;

typedef 
enum HSCMODEATTRTYPE
    {
        HSCMODEATTR_NONE	= 0,
        HSCMODEATTR_OPER	= 1,
        HSCMODEATTR_PROG	= 2,
        HSCMODEATTR_NORMAL	= 3,
        HSCMODEATTR_COUNT	= 4
    } 	HSCMODEATTRTYPE;

typedef struct tag_PHDCollectRptRecord
    {
    PNTNUM nPointNumber;
    PRMNUM nParamNumber;
    int2 nFstHistSetting;
    int2 nSlwHistSetting;
    int2 nExtHistSetting;
    int2 nExcHistSetting;
    } 	PHDCollectRptRecord;

typedef /* [public] */ struct __MIDL___MIDL_itf_hsctypes_0000_0000_0010
    {
    /* [string] */ unsigned char *tagname;
    /* [string] */ unsigned char *desc;
    uint2 actType;
    /* [string] */ unsigned char *assetTagname;
    } 	ActivityEntitySummary;

typedef int4 SRVCAVALPRM;

#define	CONTROLLER_MASK	( 0x1 )

#define	BACNET_MASK	( 0x2 )

#define	ALLPOINTS_MASK	( 0x4 )

#define	FIREPOINT_MASK	( 0x8 )

#define	CONTROLLER_CHANNEL_MASK	( 0x10 )

#define	CONTROLLER_NETWORK_MASK	( 0x20 )

#define	ACCESSPOINT_MASK	( 0x40 )

#define	DOORPOINT_MASK	( 0x80 )

#define	CAMERAPOINT_MASK	( 0x100 )

#define	ENROLLMENTREADER_MASK	( 0x200 )

#define	ELOCKPOINT_MASK	( 0x400 )

#define	PSDEFAULT	( "$$PSDEFAULT$$" )

#define	PSDEFAULT_SZ	( 14 )

#define	PSROOT	( "$$PSROOT$$" )

#define	PSROOT_SZ	( 11 )

#define	PSSYSINT	( "$$PSSYSINT$$" )

#define	PSSYSINT_SZ	( 13 )

typedef 
enum DAS_ITEM_STATUS
    {
        OK	= 0,
        ERR_INV_POINT	= ( OK + 1 ) ,
        ERR_INV_BLOCK	= ( ERR_INV_POINT + 1 ) ,
        ERR_INV_CONDITION	= ( ERR_INV_BLOCK + 1 ) ,
        WARN_COULD_NOT_VALIDATE	= ( ERR_INV_CONDITION + 1 ) ,
        WARN_VALIDATE_NOT_SUPPORTED	= ( WARN_COULD_NOT_VALIDATE + 1 ) ,
        ERR_PNT_TYPE_NOT_SUPPORTED	= ( WARN_VALIDATE_NOT_SUPPORTED + 1 ) 
    } 	DAS_ITEM_STATUS;

typedef struct DAS_BLOCK
    {
    /* [string] */ unsigned char *szBlock;
    unsigned int nConditions;
    /* [string][size_is] */ unsigned char **pszConditions;
    DAS_ITEM_STATUS Status;
    } 	DAS_BLOCK;

typedef struct DAS_POINT
    {
    unsigned int nBlocks;
    /* [size_is] */ DAS_BLOCK *pBlocks;
    unsigned int flags;
    int nCon;
    DAS_ITEM_STATUS Status;
    } 	DAS_POINT;

typedef struct DAS_ITEM
    {
    /* [string] */ unsigned char *szPoint;
    /* [string] */ unsigned char *szBlock;
    /* [string] */ unsigned char *szCondition;
    int nCon;
    } 	DAS_ITEM;

typedef __int64 ITEMHANDLE2;

typedef uint4 GDATABLEID;

typedef uint8 GDAROWID;

typedef uint8 GDAVALUEID;

typedef uint2 GDACELLID;

typedef uint2 GDAUPDATEID;

#define	CLIENTCONNECTION_MASK	( 0xfff )

#define	GDARESERVEDCELL_MASK	( 0x8000 )

typedef uint2 GDATABLELOCKOPTION;

#define	GDATABLELOCK_MASK	( 0xf )

#define	GDATABLELOCK_LOCKROWS	( 0x1 )

#define	GDATABLELOCK_UNLOCKROWS	( 0x2 )

#define	GDATABLEMATCH_MASK	( 0xf0 )

#define	GDATABLEMATCH_UPDATEIDONLY	( 0x10 )

#define	GDATABLEMATCH_UPDATEIDOROLDEST	( 0x20 )

#define	GDATABLEMATCH_UPDATEIDORLATEST	( 0x30 )

typedef uint2 GDACELLOPTIONS;

#define	GDACELLKIND_MASK	( 0xf )

#define	GDACELLKIND_PARAM	( 0 )

#define	GDACELLKIND_MODEL	( 0x1 )

#define	GDACELLINCS_MASK	( 0xf0 )

#define	GDACELLINCS_RANGE	( 0x10 )

#define	GDACELLINCS_ALARMHANDLE	( 0x20 )

#define	GDACELLINCS_UNITS	( 0x40 )

#define	GDACELLATTR_MASK	( 0xf000 )

#define	GDACELLATTR_VALUE	( 0 )

#define	GDACELLATTR_RANGELO	( 0x1000 )

#define	GDACELLATTR_RANGEHI	( 0x2000 )

#define	GDACELLATTR_UNITS	( 0x3000 )

#define	GDACELLATTR_PRETAGNAME	( 0x4000 )

typedef struct GDACELLITEM
    {
    /* [string] */ unsigned char *szName;
    GDACELLOPTIONS Options;
    GDACELLID CellId;
    } 	GDACELLITEM;

typedef 
enum GDAFROMFIELD
    {
        GDAFROMFIELD_MODEL	= 0,
        GDAFROMFIELD_MODELTYPE	= ( GDAFROMFIELD_MODEL + 1 ) ,
        GDAFROMFIELD_NAMEMASK	= ( GDAFROMFIELD_MODELTYPE + 1 ) ,
        GDAFROMFIELD_ROLE	= ( GDAFROMFIELD_NAMEMASK + 1 ) ,
        GDAFROMFIELD_ORIGIN	= ( GDAFROMFIELD_ROLE + 1 ) ,
        GDAFROMFIELD_ANCESTOR	= ( GDAFROMFIELD_ORIGIN + 1 ) 
    } 	GDAFROMFIELD;

#define	MODEL_PARAMETER	( "PARAMETER" )

#define	MODEL_EQUIPMENT	( "EQUIPMENT" )

typedef struct GDAFROMITEM
    {
    /* [string] */ unsigned char *szValue;
    GDAFROMFIELD Field;
    } 	GDAFROMITEM;

typedef 
enum GDASORTDIRECTION
    {
        GDASORT_ASC	= 0,
        GDASORT_DSC	= ( GDASORT_ASC + 1 ) 
    } 	GDASORTDIRECTION;

typedef struct GDASORTITEM
    {
    GDACELLID CellId;
    GDASORTDIRECTION Direction;
    } 	GDASORTITEM;

typedef uint2 GDAMODELFLAGS;

typedef uint2 GDAQUERYFLAGS;

#define	GDAQUERYFLAG_DYNAMICSCAN	( 0x1 )

#define	GDAQUERYFLAG_ROWALARMSTATE	( 0x2 )

#define	GDAQUERYFLAG_ROWALARMSTATEBYCELL	( 0x4 )

#define	GDAQUERYFLAG_HEADERONLY	( 0x10 )

#define	GDAQUERYFLAG_HEADERALARMCOUNTS	( 0x20 )

#define	GDAQUERYFLAG_DISABLESORFILTERING	( 0x40 )

#define	GDAQUERYFLAG_DISABLEROWDELETION	( 0x80 )

typedef struct GDAQUERY
    {
    GDAQUERYFLAGS nQueryFlags;
    GDAMODELFLAGS nModelFlags;
    uint4 nPeriod;
    uint2 nCellCount;
    /* [size_is] */ GDACELLITEM *pCells;
    uint2 nFromCount;
    /* [size_is] */ GDAFROMITEM *pFromFields;
    /* [string] */ unsigned char *szWhereClause;
    uint2 nSortCount;
    /* [size_is] */ GDASORTITEM *pSortFields;
    } 	GDAQUERY;

typedef struct GDATABLEVIEWCELL
    {
    GDACELLID CellId;
    uint2 Area;
    GDAITEM Value;
    GDAERR Status;
    double RangeLo;
    double RangeHi;
    /* [string] */ unsigned char *szUnits;
    uint4 AlarmState;
    } 	GDATABLEVIEWCELL;

typedef uint2 GDATABLEVIEWROWFLAGS;

#define	GDATABLEVIEWROWFLAGS_ROWLOCALPOINTRESOLVED	( 0x1 )

#define	GDATABLEVIEWROWFLAGS_ROWDELETED	( 0x2 )

#define	GDATABLEVIEWROWFLAGS_ROWOUTSIDESOR	( 0x4 )

#define	GDATABLEVIEWROWFLAGS_ROWHIDDEN	( 0x8 )

typedef struct GDATABLEVIEWROW
    {
    GDAROWID RowId;
    uint4 AlarmState;
    PNTNUM nLocalPoint;
    GDATABLEVIEWROWFLAGS nRowFlags;
    uint2 nCellCount;
    /* [size_is] */ GDATABLEVIEWCELL *pCells;
    } 	GDATABLEVIEWROW;

typedef struct GDATABLEVIEW
    {
    GDAUPDATEID UpdateId;
    uint4 nRowPosition;
    uint4 nRowCount;
    /* [size_is] */ GDATABLEVIEWROW *pRows;
    uint4 nTableRowCountUnfiltered;
    uint4 nTableRowCountSorFiltered;
    uint4 nTableRowCount;
    PNTalmcount TableAlarmCounts;
    BOOL bTableLocked;
    BOOL bTableSorted;
    uint4 nTableRowCountNotShown;
    uint4 nTableRowCountNotHidden;
    } 	GDATABLEVIEW;

typedef struct GDATABLESOURCECELL
    {
    GDACELLID CellId;
    GDACELLOPTIONS CellOptions;
    PNTNUM nPoint;
    PRMNUM nParam;
    uint2 nStatus;
    } 	GDATABLESOURCECELL;

typedef struct GDATABLESOURCEROW
    {
    PNTNUM nRowPoint;
    uint2 nCellCount;
    /* [size_is] */ GDATABLESOURCECELL *pCells;
    } 	GDATABLESOURCEROW;

typedef struct GDATABLESOURCE
    {
    uint4 nRowCount;
    /* [size_is] */ GDATABLESOURCEROW *pRows;
    } 	GDATABLESOURCE;

typedef uint4 NOTIFCOOKIE;

#define	NULL_COOKIE	( 0 )

#endif


extern RPC_IF_HANDLE __MIDL_itf_hsctypes_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_hsctypes_0000_0000_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


