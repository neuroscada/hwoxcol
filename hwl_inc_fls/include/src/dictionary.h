/************************************************************************/
/*****     COPYRIGHT 2009 - 2017    HONEYWELL INTERNATIONAL SARL     ****/
/************************************************************************/

#ifndef dictionary_flag
#define dictionary_flag

#include "src/shheap.h"

/*
@(#)dictionary.h	main.SVR_MASTERPROJ_Integration.R0930_Int.3
BEGIN_DOC
---------------------------------------------------------------------------
dictionary.h - dictionary database definitions
---------------------------------------------------------------------------
SUMMARY:
    This file contains a description of the shared memory heap
    used for holding the dictionary

DESCRIPTION:
    The first malloc in the heap is an array item structures, all of which
    will be classes, such as point. Each item contains a class or entity
    structure. A class would point to another array of item structures
    for the members of that class. Names are inline in the header.
    There is a count of how many null terminated names are contained in the
    block.

    +-------+        + ------+
    | array |------->| child |
    | of    |        | array |
    | items |        | of    |
    |       |        | items |     +-------+
    |       |        |       |---->| child |---> etc
    |       |        +-------+     | array |
    |       |                      | of    |
    +-------+                      | items |
                                   +-------+

    The array of items has a header that describes how many entries and contains
    index array pairs for fast lookup using a binary search.

    -----------------------------------------------------------------------
    NOTES -
    -----------------------------------------------------------------------

DEFINITIONS:
*/

//*************************************************************
// Locations of arrays and lists in item list memory block
typedef struct
    {
    int	First;		// offset of first item (size of header arrays)
    int	Last;		// offset of last item in list
    int	cNumb;		// count of the number entries in number array
    int	cHash;		// count of the number entries in hash array
    } DICTlistHeader;
// NumberArray[cNumb+1]        // array of point numbers
// HashesArray[cHash+1]        // array of point name hashes
// NumbOffsetArray[cNumb+1]    // array of offsets for item numbers
// HashOffsetArray[cHash+1]    // array of offsets for item name hashes
// int Base;                   // size of header and arrays, let's us locate beginning of block from 1st item in list
// ItemList...                 // size linked list of items

#define sizeof_DICTlistHdrSize         (sizeof(DICTlistHeader))
#define sizeof_DICTlistNumber          (sizeof(int))    // array of point numbers
#define sizeof_DICTlistHash            (sizeof(uint2))  // array of name hashes
#define sizeof_DICTlistOffset          (sizeof(int))	// array of offsets to items
#define DICTlistItemIncr               (sizeof_DICTlistNumber+sizeof_DICTlistHash+sizeof_DICTlistOffset*2)

#define DICTlistBaseOffset(pClass)     (*(int*)((char*)(pClass)-sizeof(int)))
#define DICTlistBase(pClass)           ((char*)(pClass) - DICTlistBaseOffset(pClass))
#define DICTlistFirstOffset(pBlock)    (((DICTlistHeader*)(pBlock))->First)
#define DICTlistLastOffset(pBlock)     (((DICTlistHeader*)(pBlock))->Last)
#define DICTlistNumbListCount(pBlock)  (((DICTlistHeader*)(pBlock))->cNumb)
#define DICTlistHashListCount(pBlock)  (((DICTlistHeader*)(pBlock))->cHash)
#define DICTlistNumbListSize(pBlock)   ((DICTlistNumbListCount(pBlock)+1)*sizeof_DICTlistNumber)
#define DICTlistHashListSize(pBlock)   ((DICTlistHashListCount(pBlock)+1)*sizeof_DICTlistHash)
#define DICTlistNumbOffsetListSize(pBlock) ((DICTlistNumbListCount(pBlock)+1)*sizeof_DICTlistOffset)
#define DICTlistHashOffsetListSize(pBlock) ((DICTlistHashListCount(pBlock)+1)*sizeof_DICTlistOffset)

#define DICTlistNumberList(pBlock)     (     (int*)((char*)(pBlock)+sizeof_DICTlistHdrSize))
#define DICTlistHashList(pBlock)       (   (uint2*)((char*)(DICTlistNumberList(pBlock))    +DICTlistNumbListSize(pBlock)))
#define DICTlistNumbOffsetList(pBlock) (     (int*)((char*)(DICTlistHashList(pBlock))      +DICTlistHashListSize(pBlock)))
#define DICTlistHashOffsetList(pBlock) (     (int*)((char*)(DICTlistNumbOffsetList(pBlock))+DICTlistNumbOffsetListSize(pBlock)))
#define DICTlistItemList(pBlock)       ((DICTitem*)((char*)(DICTlistHashOffsetList(pBlock))+DICTlistHashOffsetListSize(pBlock)+sizeof(int)))
#define DICTlistByNumbOffset(pBlock,i) ((DICTitem*)((char*)(pBlock)+DICTlistNumbOffsetList(pBlock)[i]))
#define DICTlistByHashOffset(pBlock,i) ((DICTitem*)((char*)(pBlock)+DICTlistHashOffsetList(pBlock)[i]))
#define DICTlistFirst(pBlock)          ((DICTitem*)((char*)(pBlock)+DICTlistFirstOffset(pBlock)))
#define DICTlistLast(pBlock)           ((DICTitem*)((char*)(pBlock)+DICTlistLastOffset(pBlock)))

/********************************** Attribute name and value association list */

typedef struct
    {
    int		value;
    char*	text;
    } enumlist;

/********************************** Dictionary structure types */

typedef enum
    {
    HSC_CLASS = 1,
    HSC_ENTITY
    } DICTtype;
#ifdef dict_parse_flag
enumlist DICTtypes[] =
    {
    HSC_CLASS	,"CLASS",
    HSC_ENTITY	,"ENTITY",
    0		,(char*)NULL
    };
#else
extern enumlist DICTtypes[];
#endif

/********************************** Name access methods */

typedef enum
    {
    NAM_STATIC = 1,
    NAM_LOOKUP
    } NAMEmethod;
#ifdef dict_parse_flag
enumlist NAMEmethods[] =
    {
    NAM_STATIC	,"STATIC_N",
    NAM_LOOKUP	,"LOOKUP_N",
    0		,(char*)NULL
    };
#else
EXTERN_C enumlist NAMEmethods[];
#endif

/********************************** Name method parameters */

typedef struct
    {
    int		file;
    int		record;
    int		word;
    short	width;
    } NAMElookup;

/********************************** Name structure */

#define MAX_NAME_LENGTH		256

typedef struct
    {
    uint2	crc;		// CRC16 of upper case name
    uint2	len;		// length of name
    char	string[2];	// null terminated name string
    } NAMEentry;
#define NAMEentrysize(pName) (sizeof(NAMEentry) - 2 + pName->len + 1)

typedef struct
    {
    NAMEmethod	    method;
    union
	{
	NAMElookup  lookup;
	} details;
    uint2	number;		        // number of names
    NAMEentry	name[1];		// at least 1 name
    } DICTname;

/********************************** Native data types */

typedef enum
    {
    DT_CHAR=1,	/* character string		*/
    DT_INT2,	/* 1 to 16 bit short integer	*/
    DT_INT4,	/* 32 bit integer		*/
    DT_REAL,	/* short float			*/
    DT_DBLE,	/* long float			*/
    DT_HIST,	/* history (-0 => large float)  */
    DT_VAR,	/* variant			*/
    DT_ENUM,	/* enumeration			*/
    DT_DATE_TIME,/* timestamp (int2 day,real sec)*/
    DT_STATUS,	/* status of a parameter value	*/
    DT_SRCADDR,	/* source address		*/
    DT_DSTADDR,	/* destination address		*/
    DT_SERVAR,	/* serialized variant		*/
    DT_POINTREF, /* used when creating remote container points	*/
    DT_INT8,	 /* 64 bit integer		*/
    DT_TIME,	 /* date and time (HSCTIME format)	*/
    DT_DELTATIME,/* delta time (HSCTIME format)		*/
    DT_TIMEOFDAY, /* time of day (HSCTIME format)	*/
    DT_ALARMHANDLE, /* handle for alarm grouping	*/
    DT_POINTREF2,/* used when creating remote container points	*/
    DT_LAST      /* marker for last data type, used for range checks. *** INSERT ABOVE THIS ***  */
    } DATAtype;
#ifdef dict_parse_flag
enumlist DATAtypes[] =
    {
    DT_CHAR	,"CHAR",
    DT_INT2	,"INT2",
    DT_INT4	,"INT4",
    DT_REAL	,"REAL",
    DT_DBLE	,"DBLE",
    DT_HIST	,"HIST",
    DT_VAR	,"VAR",
    DT_ENUM	,"ENUM",
    DT_DATE_TIME,"DATE_TIME",
    DT_STATUS	,"STATUS",
    DT_SRCADDR	,"SRCADDR",
    DT_DSTADDR	,"DSTADDR",
    DT_SERVAR	,"SERVAR",
    DT_POINTREF	,"POINTREF",
    DT_INT8	,"INT8",
    DT_TIME	,"TIME",
    DT_DELTATIME,"DELTATIME",
    DT_TIMEOFDAY,"TIMEOFDAY",
    DT_ALARMHANDLE,"ALARMHANDLE",
    DT_POINTREF2,"POINTREF2",
    0		,(char*)NULL
    };
#else
EXTERN_C enumlist DATAtypes[];
#endif

/********************************** Data format methods */

typedef enum
    {
    DF_CHAR = 1,    /* character	    */
    DF_NUM,	    /* numeric		    */
    DF_POINT,	    /* point name	    */
    DF_PARAM,	    /* parameter name	    */
    DF_ENG,	    /* engineering units    */
    DF_PCT,	    /* percent		    */
    DF_ENUM,	    /* enumerated	    */
    DF_MODE,	    /* enumerated mode	    */
    DF_BIT,	    /* TRUE/FALSE	    */
    DF_STATE,	    /* state descriptor	    */
    DF_PNTTYPE,	    /* point type	    */
    DF_TIME,	    /* time		    */
    DF_DATE,	    /* date		    */
    DF_DATE_TIME,   /* time stamp	    */
    DF_GETVAL,	    /* format as pnt-param  */
    DF_DATE_TIME_UST, /* time stamp in UST   */
    DF_ENUM_SET	    /* enumerated set	    */
    } DATAformat;
#ifdef dict_parse_flag
enumlist DATAformats[] =
    {
    DF_CHAR		,"CHAR",
    DF_NUM		,"NUM",
    DF_POINT		,"POINT",
    DF_PARAM		,"PARAM",
    DF_ENG		,"ENG",
    DF_PCT		,"PCT",
    DF_ENUM		,"ENUM",
    DF_MODE		,"MODE",
    DF_BIT		,"BIT",
    DF_STATE		,"STATE",
    DF_PNTTYPE		,"PNTTYPE",
    DF_TIME		,"TIME",
    DF_DATE		,"DATE",
    DF_DATE_TIME	,"DATE_TIME",
    DF_GETVAL		,"GETVAL",
    DF_DATE_TIME_UST	,"DATE_TIME_UST",
    DF_ENUM_SET		,"ENUM_SET",
    0		,(char*)NULL
    };
#else
EXTERN_C enumlist DATAformats[];
#endif

/********************************** Point Build simplified parameter types */
/* these formats are passed by pnbld or embuilder when calling hsc_param_create_alt to create parameters */
typedef enum
    {
    PB_CHAR=1,	/* character string			*/ /* pntbld syntax ParameterName CHAR value */
    PB_INT2,	/* 1 to 16 bit short integer		*/ /* pntbld syntax ParameterName INT2 x */
    PB_INT4,	/* 32 bit integer			*/ /* pntbld syntax ParameterName INT4 x */
    PB_INT8,	/* 64 bit integer			*/ /* pntbld syntax ParameterName INT8 x */
    PB_REAL,	/* short float				*/ /* pntbld syntax ParameterName REAL x.xx */
    PB_DBLE,	/* long float				*/ /* pntbld syntax ParameterName DBLE x.xx */
    PB_BSTR,	/* variant BSTR (max 32k)		*/ /* pntbld syntax ParameterName BSTR value */
    PB_VCHAR,	/* variant VECTOR of character strings	*/ /* pntbld syntax ParameterName VCHAR value */
    PB_PNT,	/* point reference			*/ /* pntbld syntax ParameterName PNT pointnum */
    PB_PAR,	/* parameter reference			*/ /* pntbld syntax ParameterName PRM pointname paramname */
    PB_PSA,	/* point server point			*/ /* pntbld syntax ParameterName PSA pointnum*/
    PB_CDA,	/* DSA parameter 			*/ /* pntbld syntax ParameterName CDA  */
    PB_LAST     /* marker for last data type, used for range checks. *** INSERT ABOVE THIS ***  */
    } PNTBLDtype;
#ifdef dict_parse_flag
enumlist PNTBLDtypes[] =
    {
    PB_CHAR		,"CHAR",
    PB_INT2		,"INT2",
    PB_INT4		,"INT4",
    PB_INT8		,"INT8",
    PB_REAL		,"REAL",
    PB_DBLE		,"DBLE",
    PB_BSTR		,"BSTR",
    PB_VCHAR		,"VCHAR",
    PB_PNT		,"PNT",
    PB_PAR		,"PAR",
    PB_PSA		,"PSA",
    PB_CDA		,"CDA",
    0			,(char*)NULL
    };
#else
extern enumlist PNTBLDtypes[];
#endif

/********************************** Format method parameters */

typedef	struct
    {
    int		file;
    int		record;
    int		word;
    int		length;
    } DFenum;

typedef struct
    {
    uint2	len;		// length of enum entry
    uint2	ord;		// enum ordinal
    char	text[2];	// null terminated name string
    } DFenumentry;

typedef	struct
    {
    GINDX	genumlist;
    uint2	len;
    uint2	num;
    } DFenumset;

typedef	struct
    {
    GINDX	gtext;
    } DFunits;

typedef	struct
    {
    int		parameter;
    } DFstate;

typedef	struct
    {
    int		parameter;
    DATAtype	type;
    int		length;
    } DFgetval;
typedef	struct
    {
    int		word;	/* word offset of point number*/
    } DFparam;

/********************************** Format structure */

#define	DFF_LEFT	0x0001	/* left justified */
#define DFF_RIGHT	0x0002	/* right justified */
#define DFF_ACROSS	0x0010	/* acronyms across record */

#ifdef dict_parse_flag
enumlist FMTflags[] =
    {
    DFF_LEFT	,"LEFT",
    DFF_RIGHT	,"RIGHT",
    DFF_ACROSS	,"ACROSS",
    0		,(char*)NULL
    };
#else
EXTERN_C enumlist FMTflags[];
#endif

typedef struct
    {
    DATAformat	    method;
    union
	{
	DFenum	    fenum;
	DFenumset   fenumset;
	DFunits     funits;
	DFstate	    state;
	DFgetval    getval;
	DFparam	    param;
	} details;
    int		    flag;
    } DICTformat;

/********************************** Data conversion methods */

typedef enum
    {
    DC_PO2 = 1,	    /* (n+1)th power of 2 minus 1   */
    DC_SCALE	    /* type conversion		    */
    } DATAconversion;
#ifdef dict_parse_flag
enumlist DATAconversions[] =
    {
    DC_PO2	,"PO2",
    DC_SCALE	,"SCALE",
    0		,(char*)NULL
    };
#else
EXTERN_C enumlist DATAconversions[];
#endif

/********************************** Conversion method parameters */

typedef	struct
    {
    double	bias;
    double	scale;
    } DCscaled;

/********************************** Conversion structure */

typedef struct
    {
    DATAconversion  method;
    uint4           pad;
    union
	{
	DCscaled        scaled;
	} details;
    } DICTconversion;

/********************************** Data access methods	*/

typedef enum
    {
    DA_DATAIO = 1,
    DA_PRMDEF,
    DA_PARAM,
    DA_CDA,
    DA_EVENT,
    DA_QUE,
    DA_HISTORY,
    DA_CONSTANT,
    DA_HSTDTM,
    DA_VARIABLE,
    DA_POINT,
    DA_FIELDBUS_MODE,
    DA_ALMCOUNT,
    DA_MSGCOUNT,
    DA_PNTALM,
    DA_RELATIVES,
    DA_PNTBLK,
    DA_FUNCTION,
    DA_ALTCOUNT,
    DA_UNRESOLVED,
    DA_SCANNED,
    DA_ALARMED,
    DA_METHOD_MAX
    } DATAaccess;
#ifdef dict_parse_flag
enumlist DATAaccesses[] =
    {
    DA_DATAIO		,"DATAIO",
    DA_PRMDEF		,"PRMDEF",
    DA_PARAM		,"PARAM",
    DA_CDA		,"CDA",
    DA_EVENT		,"EVENT",
    DA_QUE		,"QUE",
    DA_HISTORY		,"HISTORY",
    DA_CONSTANT 	,"CONSTANT",
    DA_HSTDTM		,"HIST_DTM",
    DA_VARIABLE		,"VARIABLE",
    DA_POINT		,"POINT",
    DA_FIELDBUS_MODE	,"FIELDBUS_MODE",
    DA_ALMCOUNT		,"ALMCOUNT",
    DA_MSGCOUNT		,"MSGCOUNT",
    DA_PNTALM		,"PNTALM",
    DA_RELATIVES	,"RELATIVES",
    DA_PNTBLK		,"PNTBLK",
    DA_FUNCTION		,"FUNCTION",
    DA_ALTCOUNT		,"ALTCOUNT",
    DA_UNRESOLVED	,"UNRESOLVED",
    DA_SCANNED  	,"SCANNED",
    DA_ALARMED  	,"ALARMED",
    0			,(char*)NULL
    };
#else
EXTERN_C enumlist DATAaccesses[];
#endif

/********************************** Access method parameters */

typedef	struct
    {
    int		file;
    int		record;
    int		word;
    short	bit;
    short	width;
    uint2	algonum;
    } DAdataio;

typedef	struct
    {
    int		point;
    int		definition;
    int		offset;
    } DAprmdef;

typedef	struct
    {
    int		point;
    int		param;
    int		offset;
    } DAparam;

typedef	struct
    {
    int		period;		// period of subscription
    uint4	lastupd;	// time of last update of value or quality
    uint4	lastacs;	// time of last access to value block
    uint4	lastrdacs;	// time of last auto read access (for average calculation)
    uint4	average;	// average access period (determines auto-subscribe)
    uint4	lastagacs;	// time of last access for all aging clients (those that do not unsubscribe)
    int		agperiod;	// fastest period requested for an aging client
    } DAcda;
// DICTaccess is padded to achieve double allignement of DICTconversion.
// DAcda is the largest member if DICTaccess.details.
// By padding DAcda rather than DICTaccess, we will have a spare int4 for use
// any time we want, without having to migrate the DICTvalue blocks.

typedef	struct
    {
    int		word;
    short	offset;
    short	width;
    } DAevent;

typedef	struct
    {
    int		file;
    int		header;
    } DAque;

typedef	struct
    {
    int		file;
    int		point;
    int		param;
    } DAhistory;

typedef	struct
    {
    GINDX	gPoint;	// point name
    int 	lPoint; // size of point block
    int 	nRoles;	// number of role names that follow point name
    int 	Flags;	// flags
#define	DApointFlag_AggAlarmsFromRelPoint	0x0001	// aggregate alarm counts from the related point to this point
#define	DApointFlag_AggAlarmsToRelPoint		0x0002	// aggregate alarm counts to the related point from this point
    } DApoint;

typedef	struct
    {				/* ONLY used during creation of entry, these end up in the variant */
    int		nElem;		/* number of elements in an array  */
    DATAtype  	type;		/* data type of elements (value type is VAR) */
    } DAvariable;

typedef	struct
    {
    int		actual;		/* actual mode parameter number */
    int		target;		/* target mode parameter number */
    } DAfieldbusmode;

typedef	struct
    {
    int		priority;
    int		active;
    int		acknowledged;
    } DAalmcount;

typedef struct
    {
    int		confirmable;
    int		acknowledged;
    int		confirmed;
    } DAmsgcount;

typedef	struct
    {
    int		active;
    int		acknowledged;
    } DAaltcount;

typedef struct
    {
    int		word;
    int		bit;
    int		width;
    } DApntalm;

typedef struct
    {
    int		type;
    } DArelatives;

typedef struct
    {
    int		word;
    int		bit;
    int		width;
    } DApntblk;

typedef struct
    {
    int		ordinal;	/* ordinal of function entry in jump table */
    int		param1;		/* parameter to pass the function */
    int		param2;		/* parameter to pass the function */
    int		param3;		/* parameter to pass the function */
    } DAfunction;

typedef struct
{
    DATAaccess  method;
    uint4       lastres;
    GINDX       gSourcePoint;
    GINDX       gSourceParam;
    PNTNUM      sourcePoint;
    uint2       paramFlags;
} DAunresolved;
/********************************** Access structure */

typedef struct
    {
    DATAaccess		method;
    union
	{
	DAdataio	dataio;
	DAprmdef	prmdef;
	DAparam		param;
	DAcda		cda;
	DAevent		event;
	DAque		queue;
	DAhistory	history;
	DApoint		point;
	DAvariable	variable;
	DAfieldbusmode	fieldbusmode;
	DAalmcount	almcount;
	DAmsgcount	msgcount;
	DApntalm	pntalm;
	DArelatives	relatives;
	DApntblk	pntblk;
	DAfunction	function;
	DAaltcount	altcount;
	DAunresolved 	unresolved;
	} details;
    short		repeat;
    short		pad;
    } DICTaccess;

/********************************** Value */

typedef union
    {
    short	int2;
    long	int4;
    int8	int8;
    float	real;
    double	dble;
    uint2	param;
    GINDX	gtext;	/* pointer to character array */
    struct
	{
	GINDX    gvar;	/* pointer to variant */
	DATAtype dt;	/* our data type, INT2 etc. */
	}       var;
    GINDX	genum;	/* pointer to 'enumlist' */
    struct
	{
	short   day;    /* note:			*/
	float   sec;    /* this is 32 bit aligned	*/
	}       datetime;
    HSCTIME     time;
    } DICTVALUE;

typedef struct
    {
    DATAtype  	    type;
    DICTformat	    format;
    DICTaccess 	    access;
    DICTconversion  conversion;
    GDAERR	    quality;
    DICTVALUE       value;
    uint4   BBIndex;	/* basic block index */
    uint2   EECode;	/* execution environment code */
    uint2   flags;	/* flags */
#define DICTvalue_NEW_SUB    0x0001	/* new subscription */
    } DICTvalue;

/********************************** ODBC structure */

#define	FL_PRM	0x0001		/* primary key */
#define FL_IDX	0x0002		/* non-unique index key */

#ifdef dict_parse_flag
enumlist ODBCflags[] =
    {
    FL_PRM	,"PRMKY",
    FL_IDX	,"INDEX",
    0		,(char*)NULL
    };
#else
EXTERN_C enumlist ODBCflags[];
#endif

typedef struct
    {
    int		    flag;
    int		    table;	/* column is key to this table */
    } DICTodbc;

/********************************** Class (table) definition structure */

typedef struct
    {
    GINDX	child;			/* childrenn */
    int		area;			/* position/parameter of area code 	*/
    short	enable_wrd;		/* word offset of record enable flag	*/
    short	enable_bit;		/* bit  offset of record enable flag	*/
    } DICTclass;

/********************************** Entity (column) definition structure */

typedef struct				/* as stored in the dictionary */
    {
    DICTodbc		odbc;
    DICTvalue		value;
    GINDX		limit_min;
    GINDX		limit_max;
    GINDX		range_min;
    GINDX		range_max;
    } DICTentity;

typedef struct				/* as used by fatDICTitem */
    {
    DICTodbc		odbc;
    DICTvalue		value;
    DICTvalue		limit_min;
    DICTvalue		limit_max;
    DICTvalue		range_min;
    DICTvalue		range_max;
    } fatDICTentity;

/********************************** Item header */

#define FL_RD	0x0001          /* read access */
#define FL_WRT	0x0002          /* write access */
#define FL_RW	(FL_RD|FL_WRT)	/* read & write access */
#define FL_OVR	0x0004          /* parameter overload allowed */
#define FL_CDA	0x0008          /* parameter must be overload by CDA method */
#define FL_NDS	0x0010          /* parameter is not valid on direct station */
#define FL_CWD	0x0020          /* clusterwide, this parameter should be replicated to console stations */
#define FL_LOC	0x0040          /* parameter must be overload by a LOCAL method */
#define FL_KOV	0x0080          /* keep old value when recreating parameter */
#define FL_OPER 0x0000          /* Operator level required to change parameter for APS, also requires FL_WRT but not FL_NAPS */
                                /* note this is not included in HDRflags below as it has a value of 0 */
#define FL_SUPV 0x0100          /* Supervisor level required to change parameter for APS, also requires FL_WRT but not FL_NAPS */
#define FL_ENGR 0x0200          /* Engineer level required to change parameter for APS, also requires FL_WRT but not FL_NAPS */
#define FL_MNGR 0x0300          /* Manager level required to change parameter for APS, also requires FL_WRT but not FL_NAPS */
#define FL_NAPS 0x0400          /* Does not support Advanced Parameter Security (APS) */
#define FL_NREP 0x0800          /* This parameter should not be replicated to console stations */
#define FL_UBT  0x1000          /* This sub parameter has same data type as base parameter */
#define FL_ALG  0x1000          /* This parameter is an Algo */
#define FL_HART 0x2000          /* This parameter is from a HART device and has specific alarm requirements */
#define FL_TECHADDR 0x04000     /* This parameter uses the point's tech address to address its source */
#define FL_INTDIAG  0x08000     /* This parameter is an integrated diagnostic parameter and has specific alarm requirements */

#define FL_SEC_MASK 0x0300      /* Bit mask for required security level */
#define FL_SEC_OFST 8           /* Bit offset for required security level */

#ifdef dict_parse_flag
enumlist HDRflags[] =
    {
     FL_RD          ,"FL_RD",
     FL_WRT         ,"FL_WRT",
     FL_RW          ,"FL_RW",
     FL_OVR         ,"FL_OVR",
    (FL_CDA|FL_OVR) ,"FL_CDA",
    (FL_NDS|FL_OVR) ,"FL_NDS",
    (FL_CWD|FL_RW)  ,"FL_CWD",
    (FL_LOC|FL_OVR) ,"FL_LOC",
     FL_KOV         ,"FL_KOV",
     FL_SUPV        ,"FL_SUPV",
     FL_ENGR        ,"FL_ENGR",
     FL_MNGR        ,"FL_MNGR",
     FL_NAPS        ,"FL_NAPS",
     FL_NREP        ,"FL_NREP",
     FL_UBT         ,"FL_UBT",
     FL_ALG         ,"FL_ALG",
     FL_HART        ,"FL_HART",
     FL_TECHADDR    ,"FL_TECHADDR",
     FL_INTDIAG     ,"FL_INTDIAG",
    0	            ,(char*)NULL
    };
#else
EXTERN_C enumlist HDRflags[];
#endif

typedef struct
    {
    int			size;	// size of header structure (bytes)
    DICTtype		type;
    int			number;
    int			flag;
    union {
	DICTclass	classy;
	DICTentity	entity;
	} ce;
    DICTname		name;	// variable length
    } DICTitem;

typedef struct			// as used by the parser and create
    {
    int			size;	// size of header structure (bytes)
    DICTtype		type;
    int			number;
    int			flag;
    union {
	DICTclass	classy;
	fatDICTentity	entity;
	} ce;
    DICTname		name;	// variable length
    } fatDICTitem;

/**********************************/

/*
PROTOTYPES:
*/

EXTERN_C DICTitem*	hsc_dict_get		();
EXTERN_C DICTitem*	hsc_dict_add_by_name	(DICTitem*,char**,fatDICTitem*,char*);
EXTERN_C DICTitem*	hsc_dict_find_by_name	(DICTitem*,char**);
EXTERN_C DICTitem*	hsc_dict_find_by_number	(DICTitem*,int*);
EXTERN_C int		hsc_dict_list		(DICTitem*,DICTtype,enumlist**);
EXTERN_C void		hsc_dict_list_unique	(char*,DICTitem*,enumlist*,int*,int*);
EXTERN_C void		hsc_dict_list_unique_last(char*,DICTitem*,enumlist*,int*,int*);
EXTERN_C void		hsc_dict_list_unique_position(char*,DICTitem*,enumlist*,int*,int*,int);
EXTERN_C void		hsc_dict_walk		(DICTitem*,char*,void(*routine)(char*,...),void*,void*,void*);
EXTERN_C void		hsc_dict_dump		(DICTitem*,char*);
EXTERN_C int		hsc_dict_parse		(char*,PNTNUM,fatDICTitem*,char*,char**,char*,int*,GDAITEM**);
typedef BOOL            (*on_gda_func_calling)  (int* context);
typedef void            (*on_gda_func_called)   (int context);
EXTERN_C int		hsc_dict_parse_ex	(char*,PNTNUM,fatDICTitem*,char*,char**,char*,int*,GDAITEM**,on_gda_func_calling,on_gda_func_called);
EXTERN_C char*		hsc_dict_nextToken	(char*);
EXTERN_C void		hsc_dict_FatDICTitemInit (fatDICTitem*);
EXTERN_C void		hsc_dict_FatDICTitemSetType (fatDICTitem*, DATAtype, DATAformat, DATAaccess);
/*
END_DOC
*/

#endif	/* end of conditional include dictionary_flag */

/************************************************************************/
/*****     COPYRIGHT 2009 - 2017    HONEYWELL INTERNATIONAL SARL     ****/
/************************************************************************/
