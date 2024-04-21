/************************************************************************/
/****     COPYRIGHT 2008 - 2017     HONEYWELL INTERNATIONAL SARL     ****/
/************************************************************************/

#ifndef points_flag
#define points_flag

#include "src/shheap.h"
#include "src/dictionary.h"
#include "src/dat000_def"
#include "src/ext000_def"
#include "src/cnt000_def"
#include "src/des000_def"
#include "src/points_def"
#include "hsctypes.h"
#include "parameters"
#include "src/hscesc.h"

/*
@(#)points.h  main.SVR_MASTERPROJ_Integration.R0930_Int.20
BEGIN_DOC
---------------------------------------------------------------------------
POINTS.H - point record database definitions
---------------------------------------------------------------------------
SUMMARY:
    This file contains a description of the shared memory heap
    used for holding the point database.

DESCRIPTION:
    The first malloc in the heap contains the point index array.
    Entry 0 holds the next point number to use above 65k.
    Entry 1 holds the next point number to use below 65k.
    Entry 2 holds the number of points.
    Entry 3 onwards are pointers to point instances, and if NULL,
    means that the point is not implemented.

        --------------
        | next above |
        | next       |
     -->| size = n   |       point             param list
        | point  1   |    ---------------    --------------------
        | point  2   |--->| parameters  |--->| offset to params |
        | point  3   |    | type        |    | num entires      |
        | .....  .   |    | ...         |    | offset of last   |
        | .....  .   |    | DAT         |    | numbers[n]       |
        | .....  .   |    | EXT         |    | hashes[n]        |
        | .....  .   |    | CNT         |    | numboffsets[n]   |
        | point  n   |    | DES         |    | hashoffsets[n]   |    ---------
        --------------    ---------------    | params...        |--->| value |
					     --------------------    ---------

    The point consists of a parameter block for additional
    parameters, a point type (STA,ANA,etc), some other fields,
    and then the old four part point record.

    The parameter block contans one or more variable length structures.
    Variable length, because it contains the parameter names which vary
    in length. The names will be null terminated and padded so that
    the next parameter starts on a 4 byte boundary. This is preceeded
    by number and name/hash lookup arrays, to make search times smaller.
    This is followed by offset arrays, offset of parameter in memory block,
    one for number and one for name, so we can jump to the parameter list entry.
    These arrays are compact and have 'num entries' plus 1 to hold a zero
    terminator, to make it easy to see a list seperator when looking at a dump.
    We also start with the size of the header, or offset to first parameter.
    We also have an offset to the last parameter, to save us walking the list.
    We can compare this size to the number of enties, to detect inconsistencies.
    We also compare the result of the offset, to ensure it is within bounds of the
    parameter list. The list of parameters follow these arrays.

    The PNTparam structure is optimised for GDA, containing the bare minimum
    to be able to describe a remote parameter. The value pointer
    points to a DICTvalue structure. For GDA, this is in the GDA heap
    and only exists while the parameter is being accessed. For other
    methods, the vaue structure is held in the point heap and is
    permanent. The min/max pointer points to an optional block of four
    DICTvalue structures, one each for the limit min, limit max,
    range min, and range max.

    The PNTSCNparam structure is for scanned parameters. This structure contains
    everythign required to scan an address, scale it, etc, as per an ANA PV.

    The PNTSCNALMparam structure is for alarming scanned parameters. This structure
    extends SCNparam to have alarm limits etc, as per an ANA PV.

    -----------------------------------------------------------------------
    NOTES -

    WARNING:
	Definitions in points_def are dependent on the following structure
 	definitions. ENSURE YOU MODIFY POINTS_DEF AS WELL.

    -----------------------------------------------------------------------

DEFINITIONS:
*/

// do not use _NEXT_POINT or _NUMBER_OF_POINTS unless inside points_lib
// in an intimate scenario. Never as a loop variable/condition.
#define _NEXT_POINT_ABOVE       ((PNTNUM *)points)[-2]
#define _NEXT_POINT             ((PNTNUM *)points)[-1]
#define _NUMBER_OF_POINTS       ((PNTNUM *)points)[ 0]
#define NUMPOINTS_OFFSET        2   /* offset in the raw array to the number of points entry */
#define POINTS_OFFSET           3   /* offset in the raw array to the first actual point entry */
#define FIRST_POINT_ABOVE       0x00010000
#define FIRST_POINT             0x00000001

#define PARAM_VAL     0		/* Items of a parameter */
#define PARAM_LMT_MIN 1
#define PARAM_LMT_MAX 2
#define PARAM_RNG_MIN 3
#define PARAM_RNG_MAX 4

#define PARAM_NUM_ACTALGO_OFFSET    50
#define PARAM_NUM_PVALGO_MIN        500
#define PARAM_NUM_PVALGO_MAX (PARAM_NUM_PVALGO_MIN+PARAM_NUM_ACTALGO_OFFSET-1)
#define PARAM_NUM_ACTALGO_MIN (PARAM_NUM_PVALGO_MIN+PARAM_NUM_ACTALGO_OFFSET)
#define PARAM_NUM_ACTALGO_MAX (PARAM_NUM_ACTALGO_MIN+PARAM_NUM_ACTALGO_OFFSET-1)
#define PPTNUM_POINT_DETAIL_DISPLAY 0    /* PointDetailDisplay */
#define PPTNUM_GROUP_DETAIL_DISPLAY 1    /* GroupDetailDisplay */
#define PPTNUM_ASSOCIATED_DISPLAY   2  /* AssociatedDisplay */
#define PPTNUM_INSTRUCTION_DISPLAY  3 /* InstructionDisplay */
#define PPTNUM_UNITS                4   /* Units */
#define PPTNUM_DESCRIPTION          5   /* Description */

#define POINT_LOCK_TIME 10000

#define PARAM_MAX_VARIANT_SIZE 10000000 // Arbitrary maximum size of variant data

#define ONE_SHOT        0   /* one shot acquire (subscribe period) */
#define HSC_READ_CACHE	0	/* read data from cache (subscribe period) */
#define HSC_READ_DEVICE	-1	/* read data from device (subscribe period) */

#define PARAM_TYPE_CONV 0	/* convert the parameter type to a standard HSC type*/
#define PARAM_TYPE_RAW  1	/* don't convert the parameter type*/

#define MAX_HIERARCHY_RECURSION 1000    /* maximum level of recursion before we bail out */
					/* (note: not meant to be a restriction but an unexpected error) */

#define MAX_LIC_COLLECTION_POINTS   5000    /* maximum number of collection points that can be built */
#define PNT_HIERARCHY_MAX_PARENTS   500	    /* maximum number of parents that can be added to a point */

typedef int2 PNTRELDIR;		/* point relationship direction (see points_def for available values) */

typedef int2 PNTRELTYP;		    /* point relationship type */
#define PNTRELTYP_INVALID       0
#define PNTRELTYP_CONTAINMENT   1
#define PNTRELTYP_REFERENCE     2

/* flags for modifying behavior of point relations' update functions like hsc_point_update_relatives() */
#define PNTREL_ALREADY_CHECKED       1
#define PNTREL_UPDATE_ALMCOUNTS      2
#define PNTREL_DONT_UPDATE_TIMESTAMP 4
#define PNTREL_POINT_IS_DELETED      8

/* flags for modifying behavior of point deletes */
#define PNTDEL_UNSUB        0x0001
#define PNTDEL_UPDCOUNT     0x0002
#define PNTDEL_DELALMMSG    0x0004
#define PNTDEL_DELACT       0x0008
#define PNTDEL_DELTAG       0x0010

#define PNTALM_AGGREGATE_OFFSET 0   /* offset of alarm count parameters that will return aggregate counts */
#define PNTALM_LEAF_OFFSET      2   /* offset of alarm count parameters that will return leaf counts */

#define PNTALM_STNIDX_FULLCOUNT	-1  /* station index for full alarm counts without regard to SOR */

#define BBDOCMASK 0xFFFF            /* Dependent object code in BBIndex */

// flags for hsc_security_set_priority
#define MAX_CMD_RSD_PRIORITY 63		/* Maximum command or residual control priority */

/*
STRUCTURE:
*/

// the following types are defined in hsctypes.idl
// PNTNUM     /*  0 for invalid point     */
// PNTNUM16   /*  0 for invalid point     */
// PNTTYP     /* -1 for invalid type	  */
// PRMNUM     /*  0 for invalid parameter */
// PRMTYP     /* -1 for invalid type	  */
// PPTNUM     /* property number          */

#define PNTNUM_INVALID  0
#define PNTTYP_INVALID -1
#define PNTTYP_NONE     0   /* used when we don't have a remote type*/
#define PRMNUM_INVALID  0
#define PRMTYP_INVALID -1
#define PNTSUBTYP_NONE  0

/************************************************************************************/
/* WARNING: Any modifications to the following structures may also require updates  */
/* to be made to the constants in points_def.                                       */
/************************************************************************************/

/*
  Layout of the point structures.
  The structure up to DAT, EXT, CNT, DES must be the same
*/

typedef struct
    {                                   // offset (words)
    GINDX   parameters;                 //   0  pointer to parameter list
    uint2   type;                       //   2  point type
    uint2   size;                       //   3  size of this point (bytes)
    GINDX   parents;                    //   4  pointer to parents list (POINTS heap)
    GINDX   children;                   //   6  pointer to child list (GDA heap)
    GINDX   almcounts;                  //   8  pointer to alarm counts by SOR (GDA heap)
    GINDX   BBArray;                    //  10  pointer to Basic Block array (HDA heap)
    PNTalmcount fullalmcount;           //  12  local alarm counts
    uint2   spare70[2];                 //  70  required for double alignment in ANA and others
    uint2   guid[PNT_GUID_SZ/2];        //  72  GUID
    uint2   subtype;                    //  80  point subtype
    uint2   itemnumber;                 //  81  item number
    uint2   flags;                      //  82  flags
    uint2   remotetype;                 //  83  remote point type
    PNTNUM  owner;                      //  84  point number of owner
    PRMNUM  lastParamNumber;            //  86  the number of the last parameter created
    uint2   assoccon;                   //  87  the associated connetion
    uint2   entityname[PNT_ENTITYNAME_SZ/2];    // 88 entity name
    uint2   connections[PNT_CONNECTION_COUNT];  // 108  connection array
    STA_DAT dat;                        // 112  old style point record
    STA_EXT ext;
    STA_CNT cnt;
    STA_DES des;
    } STApoint;

typedef struct
    {
    GINDX   parameters;
    uint2   type;
    uint2   size;
    GINDX   parents;
    GINDX   children;
    GINDX   almcounts;
    GINDX   BBArray;
    PNTalmcount fullalmcount;
    uint2   spare70[2];
    uint2   guid[PNT_GUID_SZ/2];
    uint2   subtype;
    uint2   itemnumber;
    uint2   flags;
    uint2   remotetype;
    PNTNUM  owner;
    PRMNUM  lastParamNumber;
    uint2   assoccon;
    uint2   entityname[PNT_ENTITYNAME_SZ/2];
    uint2   connections[PNT_CONNECTION_COUNT];
    ANA_DAT dat;
    ANA_EXT ext;
    ANA_CNT cnt;
    ANA_DES des;
    } ANApoint;

typedef struct
    {
    GINDX   parameters;
    uint2   type;
    uint2   size;
    GINDX   parents;
    GINDX   children;
    GINDX   almcounts;
    GINDX   BBArray;
    PNTalmcount fullalmcount;
    uint2   spare70[2];
    uint2   guid[PNT_GUID_SZ/2];
    uint2   subtype;
    uint2   itemnumber;
    uint2   flags;
    uint2   remotetype;
    PNTNUM  owner;
    PRMNUM  lastParamNumber;
    uint2   assoccon;
    uint2   entityname[PNT_ENTITYNAME_SZ/2];
    uint2   connections[PNT_CONNECTION_COUNT];
    ACC_DAT dat;
    ACC_EXT ext;
    ACC_CNT cnt;
    ACC_DES des;
    } ACCpoint;

typedef struct
    {
    GINDX   parameters;
    uint2   type;
    uint2   size;
    GINDX   parents;
    GINDX   children;
    GINDX   almcounts;
    GINDX   BBArray;
    PNTalmcount fullalmcount;
    uint2   spare70[2];
    uint2   guid[PNT_GUID_SZ/2];
    uint2   subtype;
    uint2   itemnumber;
    uint2   flags;
    uint2   remotetype;
    PNTNUM  owner;
    PRMNUM  lastParamNumber;
    uint2   assoccon;
    uint2   entityname[PNT_ENTITYNAME_SZ/2];
    uint2   connections[PNT_CONNECTION_COUNT];
    ACS_DAT dat;
    ACS_EXT ext;
    ACS_CNT cnt;
    ACS_DES des;
    } ACSpoint;

typedef struct
    {
    GINDX   parameters;
    uint2   type;
    uint2   size;
    GINDX   parents;
    GINDX   children;
    GINDX   almcounts;
    GINDX   BBArray;
    PNTalmcount fullalmcount;
    uint2   spare70[2];
    uint2   guid[PNT_GUID_SZ/2];
    uint2   subtype;
    uint2   itemnumber;
    uint2   flags;
    uint2   remotetype;
    PNTNUM  owner;
    PRMNUM  lastParamNumber;
    uint2   assoccon;
    uint2   entityname[PNT_ENTITYNAME_SZ/2];
    uint2   connections[PNT_CONNECTION_COUNT];
    CDA_DAT dat;
    CDA_EXT ext;
    CDA_CNT cnt;
    CDA_DES des;
    } CDApoint;

typedef struct
    {
    GINDX   parameters;
    uint2   type;
    uint2   size;
    GINDX   parents;
    GINDX   children;
    GINDX   almcounts;
    GINDX   BBArray;
    PNTalmcount fullalmcount;
    uint2   spare70[2];
    uint2   guid[PNT_GUID_SZ/2];
    uint2   subtype;
    uint2   itemnumber;
    uint2   flags;
    uint2   remotetype;
    PNTNUM  owner;
    PRMNUM  lastParamNumber;
    uint2   assoccon;
    uint2   entityname[PNT_ENTITYNAME_SZ/2];
    uint2   connections[PNT_CONNECTION_COUNT];
    ASH_DAT dat;
    ASH_EXT ext;
    ASH_CNT cnt;
    ASH_DES des;
    } ASHpoint;

#pragma pack(push,2)		// so that we control the alignment

// C++ does not support anonymous structures
// So we have to specify the first 10 words in each of the structures to keep it compatible with existing code
// The new structures will consequently have to have a name

typedef struct
    {                                   // offsets are within PNTSCNparam structure
    addpkt  address;                    //  0 address to be scanned
    union
        {
    	struct
            {
            uint2   value;              //  6 value (0-3), field value (4-7)
            uint2   range;              //  7 value range  (bits 0-3)
                                        //  7 reverse mask (bits 4-7)
                                        //  7 alarm transitions (bit 15)
            uint2   targets[2];         //  8 target states (4 bits per out value)
            uint2   statedesc[8][4];    // 10 8 state descriptors (8 char)
            } dtenum;                   // 42
    	struct
            {
            uint2   value[32];          //  6 string value (usual spaced filled byte swapped)
            uint2   spare[4];           // 38 spare padding
            } dtchar;                   // 42
    	struct
            {
            DICTVALUE value;            //  6 value (same as field if not in manual)
            DICTVALUE field;            // 10 field value
            DICTVALUE eulo;             // 14 engineering units low (same type as value)
            DICTVALUE euhi;             // 18 engineering units high (same type as value)
            DICTVALUE bias;             // 22 optional bias (same type as value)
            double    scale;            // 26 optional scale
            uint2     eudesc[4];        // 30 engineering units descriptor
            uint2     deadbands;        // 34 drift (0:3) alarm (4:7) control (8:11)
            uint2     spare[7];         // 35 spare padding
            } dtnumb;                   // 42
	};
    HSCTIME lastscannedtime;            // 42 last time parameter was scanned
    HSCTIME lastprocessedtime;          // 46 last time parameter was processed
    uint4   pvalgoblk;                  // 50 PV algo block number
    uint4   actalgoblk;                 // 52 Action algo block number
    uint2   algos;                      // 54 PV algo (0:7) Action algo (8:15)
    uint2   assocparam;                 // 55 associated parameter
    uint2   controllevel;               // 56 control level (bits 0 to 7)
                                        // 56 authorized control in progress (bit 8)
                                        // 56 alarm external change (bit 9)
                                        // 56 manual value (bit 10)
                                        // 56 use bias and scale (bit 11) dtnumb only
                                        // 56 reverse value (bit 12) dtnumb and dtenum
                                        // 56 clamp value (bit 13) dtnumb
                                        // 56 initializing (bit 14)
                                        // 56 dynamic scanning disabled (bit 15)
    uint2   opcquality;                 // 57 OPC DA quality (0-7) field value quality (8-15)
    } _PNT_param_scan_;                 // 58

typedef struct
    {                                   // offsets are within PNTSCNALMparam structure
    DICTVALUE   almlimits[8];           //  0 alarm limits
    uint2       almondly[8];            // 32 alarm on delays
    uint2       almoffdly[8];           // 40 alarm off delay
    uint2       almpriorities[2];       // 48 alarm priorities (4 bits each)
    uint2       almsubpriorities[2];    // 50 alarm subpriorities (4 bits each)
    uint2       almenbledmap;           // 52 alarm enabled map (1 bit per alarm)
    uint2       almactivemap;           // 53 alarm active map (1 bit per alarm)
    uint2       almmsgindex;            // 54 alarm message number
    } _PNT_param_alarm_;                // 55

typedef struct
{
    uint2   nn;                 // xx number of names
    NAMEentry	name[1];		// xx parameter name (at least 1 name)
} _PNT_param_name_;

typedef struct
    {
    uint2   size;               //  0 size of structure (chars)
    uint2   number;             //  1 parameter number
    uint2   flags;              //  2 flags
#define     PARAM_FLAG_DELETE       0x0001  // parameter deleted
#define     PARAM_FLAG_BITSTRING    0x0002  // assumed type is bitstring
#define     PARAM_FLAG_VARIANT_MASK 0x0002  // mask for valid variant bits
#define     PARAM_FLAG_KOV          0x0004  // keep old value
#define     PARAM_FLAG_NREP         0x0008  // do not replicate to console stations
#define     PARAM_FLAG_FROM_CDA     0x0010  // parameter was discovered from CDA
#define     PARAM_FLAG_READONLY     0x0020  // parameter is read only
#define     PARAM_FLAG_GET_CON      0x0040  // Need to determine param connection for combo point param
//                                  0x0080  //
#define     PARAM_FLAG_OPER         0x0000  // Operator level required (see dictionary.h)
#define     PARAM_FLAG_SUPV         0x0100  // Supervisor level required (see dictionary.h)
#define     PARAM_FLAG_ENGR         0x0200  // Engineer level required (see dictionary.h)
#define     PARAM_FLAG_MNGR         0x0300  // Manager level required (see dictionary.h)
#define     PARAM_FLAG_NAPS         0x0400  // Does not support Advanced Parameter Security (APS)
#define     PARAM_FLAG_SEC_MASK     0x0300  // Bit mask for required security level
#define     PARAM_FLAG_SEC_OFST     8       // Bit offset for required security level
#define     PARAM_FLAG_LIMITS       0x1000  // param flag to indicate parameter is a LR parameter
#define     PARAM_FLAG_HART         0x2000  // param flag to indicate parameter is a HART parameter
#define     PARAM_FLAG_TECHADDR     0x4000  // param flag to indicate parameter uses the point's tech address
#define     PARAM_FLAG_INTDIAG      0x8000  // param flag to indicate parameter is an integrated diagnostic parameter for RTU
    uint2   method;             //  3 data access method
    uint2   type;               //  4 data type
    uint2   vt_type;            //  5 variant data type
    uint2   connection;         //  6 connection number for parameter
    uint2   flags2;             //  7 more flags
//                                       0x0001  //
#define     PARAM_FLAG2_KEEP_INV         0x0002  // persisting M4_KEEP_INV_PARAM
#define     PARAM_FLAG2_KEEP_INV_CHECKED 0x0004  // PARAM_FLAG2_KEEP_INV is initialised
    uint4   BBIndex;            //  8 BB index used by alarming
    GINDX   gValue;             // 10 handle to value structure
    GINDX   gLimits;            // 12 handle to value limits structures
    _PNT_param_name_ name;      // 14 parameter name (at least 1 name)
    } PNTparam;                 // 18

typedef struct
    {
    uint2   size;               //  0 size of structure (chars)
    uint2   number;             //  1 parameter number
    uint2   flags;              //  2 flags
    uint2   method;             //  3 data access method
    uint2   type;               //  4 data type
    uint2   vt_type;            //  5 variant data type
    uint2   connection;         //  6 connection number for parameter
    uint2   flags2;             //  7 more flags
    uint4   BBIndex;            //  8 BB index used by alarming
    _PNT_param_scan_ scan;      // 10 scanned parameter
    PRMNUM  subparams[50];      // 68 sub parameter numbers
    _PNT_param_name_ name;      //118 parameter name (at least 1 name)
    } PNTSCNparam;              //122

typedef struct
    {
    uint2   size;               //  0 size of structure (chars)
    uint2   number;             //  1 parameter number
    uint2   flags;              //  2 flags
    uint2   method;             //  3 data access method
    uint2   type;               //  4 data type
    uint2   vt_type;            //  5 variant data type
    uint2   connection;         //  6 connection number for parameter
    uint2   flags2;             //  7 more flags
    uint4   BBIndex;            //  8 BB index used by alarming
    _PNT_param_scan_ scan;      // 10 scanned parameter
    _PNT_param_alarm_ alarm;    // 68 alarm parameter
    PRMNUM  subparams[140];     //123 sub parameter numbers
    _PNT_param_name_ name;      //263 parameter name (at least 1 name)
    } PNTSCNALMparam;           //267

#pragma pack(pop)

// Locations of arrays and lists in parameter list memory block
typedef struct
    {
    int	First;		// offset of first parameter (size of header arrays)
    int	Last;		// offset of last parameter in list
    int	cNumb;		// count of the number entries in number array
    int	cHash;		// count of the number entries in hash array
    } PNTparamListHeader;
// NumberArray[cNumb+1]        // array of point numbers
// HashesArray[cHash+1]        // array of point name hashes
// NumbOffsetArray[cNumb+1]    // array of offsets for parameter numbers
// HashOffsetArray[cHash+1]    // array of offsets for parameter name hashes
// ParamList...                // size linked list of parameters

#define sizeof_PNTparamHdrSize         (sizeof(PNTparamListHeader))
#define sizeof_PNTparamNumber          (sizeof(PRMNUM)) // array of point numbers
#define sizeof_PNTparamHash            (sizeof(uint2))  // array of name hashes
#define sizeof_PNTparamOffset          (sizeof(int))	// array of offsets to parameters

#define PNTparamListFirst(pBlock)      (((PNTparamListHeader*)(pBlock))->First)
#define PNTparamListLast(pBlock)       (((PNTparamListHeader*)(pBlock))->Last)
#define PNTparamNumbListCount(pBlock)  (((PNTparamListHeader*)(pBlock))->cNumb)
#define PNTparamHashListCount(pBlock)  (((PNTparamListHeader*)(pBlock))->cHash)
#define PNTparamNumbListSize(pBlock)   ((PNTparamNumbListCount(pBlock)+1)*sizeof_PNTparamNumber)
#define PNTparamHashListSize(pBlock)   ((PNTparamHashListCount(pBlock)+1)*sizeof_PNTparamHash)
#define PNTparamNumbOffsetListSize(pBlock) ((PNTparamNumbListCount(pBlock)+1)*sizeof_PNTparamOffset)
#define PNTparamHashOffsetListSize(pBlock) ((PNTparamHashListCount(pBlock)+1)*sizeof_PNTparamOffset)
//					ParamList must be 8 byte aligned to kkep doubles alighned
#define PNTparamHeaderSize(pBlock)     ((sizeof_PNTparamHdrSize + PNTparamNumbListSize(pBlock) + PNTparamHashListSize(pBlock) \
					 + PNTparamNumbOffsetListSize(pBlock) + PNTparamHashOffsetListSize(pBlock) + 7) & ~7)
#define PNTparamNumberList(pBlock)     (  (PRMNUM*)((char*)(pBlock)+sizeof_PNTparamHdrSize))
#define PNTparamHashList(pBlock)       (   (uint2*)((char*)(PNTparamNumberList(pBlock))    +PNTparamNumbListSize(pBlock)))
#define PNTparamNumbOffsetList(pBlock) (     (int*)((char*)(PNTparamHashList(pBlock))      +PNTparamHashListSize(pBlock)))
#define PNTparamHashOffsetList(pBlock) (     (int*)((char*)(PNTparamNumbOffsetList(pBlock))+PNTparamNumbOffsetListSize(pBlock)))
#define PNTparamParamList(pBlock)      ((PNTparam*)((char*)(pBlock)+PNTparamHeaderSize(pBlock)))
#define PNTparamByNumbOffset(pBlock,i) ((PNTparam*)((char*)(pBlock)+PNTparamNumbOffsetList(pBlock)[i]))
#define PNTparamByHashOffset(pBlock,i) ((PNTparam*)((char*)(pBlock)+PNTparamHashOffsetList(pBlock)[i]))
#define PNTparamFirst(pBlock)          ((PNTparam*)((char*)(pBlock)+PNTparamListFirst(pBlock)))
#define PNTparamLast(pBlock)           ((PNTparam*)((char*)(pBlock)+PNTparamListLast(pBlock)))


typedef struct			/*BB alarm info */
    {
    uint4	BBIndex;	/* basic block index */
    uint2	EECode;		/* execution environment code */
    uint4	low;		/* Active U count for this BB,EE */
    uint4	high;		/* Active H count for this BB,EE */
    uint4	urgent;		/* Active L count for this BB,EE */
    uint4	unack;		/* unacked count for this BB,EE */
    uint2	BBpri;		/* alarm priority for this BB,EE */

/*              5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 */
/*             --------------------------------- */
/*             |         |I|A|U|  pri  | subpri| */
/*	       --------------------------------- */
/*              U - Unacked flag */
#define		BB_UNACK_FLAG	PNTALM_UNACKN_MASK	/* unacked alarms on this BB */
#define		BB_UNACK_BIT	PNTALM_UNACKN_BIT
/*              A - Acked flag - not used by server*/
/*              I - In alarm flag */
#define		BB_INALARM_FLAG	PNTALM_INALM_MASK	/* BB in alarm*/
#define		BB_INALARM_BIT	PNTALM_INALM_BIT
/*		Priority */
#define		BB_PRI_MASK	    PNTALM_ALMPRI_MASK
#define		BB_PRI_OFFSET	PNTALM_ALMPRI_BIT
#define		BB_PRI_WIDTH	PNTALM_ALMPRI_SZ
/*		Subpriority */
#define		BB_SUBPRI_MASK	    PNTALM_ALMSUBPRI_MASK
#define		BB_SUBPRI_OFFSET    PNTALM_ALMSUBPRI_BIT
#define		BB_SUBPRI_WIDTH	    PNTALM_ALMSUBPRI_SZ
    } BBalarminfo;

/*
 * Constants for identifying the parameter associated with alarms through the BB index
 */
#define BB_PARAM_BITS 16
#define	BB_PARAM_MASK ((0x1<<BB_PARAM_BITS)-1)
#define BB_RACK_BITS  8
#define BB_RACK_MASK  ((0x1<<BB_RACK_BITS)-1)

typedef enum 
{
    BB_PARAM_MIN = 1,

    BB_PARAM_RTU_IOMODULE = BB_PARAM_MIN,
    BB_PARAM_RTU_IOCHANNEL,
    BB_PARAM_RTU_WIFICOMMS,
    BB_PARAM_RTU_WIFIBATTS,

    BB_PARAM_PLC_SYNC_STATE,
    BB_PARAM_PLC_CPU_FREE,
    BB_PARAM_PLC_TEMP,
    BB_PARAM_PLC_IP_CONFLICT_1,
    BB_PARAM_PLC_IP_CONFLICT_2,
    BB_PARAM_PLC_OPCUA_STATE,
    BB_PARAM_PLC_MSW_POSITION,
    BB_PARAM_PLC_EPM_STATUS,
    BB_PARAM_PLC_IOSLOT,
    BB_PARAM_PLC_IOCHANNEL,

    BB_PARAM_MAX = BB_PARAM_PLC_IOCHANNEL
} BB_PARAM;

typedef union       /* This structure is used to pass values into and */
    {           /* out of hsc_param_value() */
    GDAVARIANT  var;
    char    text[MAX_PARAM_VALUE_STRING_LEN+1];
    short   int2;
    long    int4;
    int8    int8;
    float   real;
    double  dble;
    struct {
       long ord;
       char text[MAX_PARAM_VALUE_STRING_LEN+1];
       } en;
    struct {
        ULONG   cSize;  /* size of serialized variant */
        BYTE    *pData; /* pointer to serialized variant */
        } servar;
    HSCTIME time;
    } PARvalue;

typedef struct          /* This structure is used internally by the */
    {                   /* parameter access routines */
    int         fParam;     /* flags for the parameter */
    int         hPoint;     /* which heap the point is in */
    int         hParam;     /* which heap the parameter is in */
    int         hValue;     /* which heap the value is in */
    int         hItem;      /* which heap the item is in */
    int         gParam;     /* heap index of parameter */
    int         gValue;     /* heap index of value */
    STApoint*   pPoint;     /* point record */
    PNTparam*   pParam;     /* parameter entry */
    DICTvalue*  pValue;     /* parameter value */
    DICTvalue*  pItem;      /* parameter item */
    PRMNUM  SubParam;       /* sub parameter number */
    } PARhandle;

typedef struct          /* This structure is used by  */
    {                   /* point_count routines */
    int     Type;           /* point type */
    int     Count;          /* point count for this type */
    } PNTcount;

/*
HELPER functions:
*/

static inline _PNT_param_name_ * _PNTParamNames (PNTparam* pParam)
{
    if (pParam == NULL)
        return (_PNT_param_name_ *)pParam;
    switch (pParam->method)
    {
    case DA_SCANNED : return &(((PNTSCNparam    *)pParam)->name);
    case DA_ALARMED : return &(((PNTSCNALMparam *)pParam)->name);
    default         : return &(((PNTparam       *)pParam)->name);
    }
}

static inline int _PNTParamSubParamClass (PNTparam* pParam)
{
    if (pParam == NULL)
        return SP_NUMB;
    switch (pParam->type)
    {
    case DT_ENUM : return SP_ENUM;
    case DT_CHAR : return SP_CHAR;
    default      : return SP_NUMB;
    }
}

static inline PRMNUM * _PNTParamSubParams (PNTparam* pParam)
{
    if (pParam == NULL)
        return NULL;
    switch (pParam->method)
    {
    case DA_SCANNED : return (((PNTSCNparam    *)pParam)->subparams);
    case DA_ALARMED : return (((PNTSCNALMparam *)pParam)->subparams);
    default         : return NULL;
    }
}

#pragma warning( push )
#pragma warning( disable : 4101 )
static inline int _numberofPNTParamSubParam (PNTparam* pParam)
{
    PNTSCNparam DummySCNparam;
    PNTSCNALMparam DummyALMparam;
    if (pParam == NULL)
        return 0;
    switch (pParam->method)
    {
    case DA_SCANNED : return sizeof(DummySCNparam.subparams)/sizeof(DummySCNparam.subparams[0]);
    case DA_ALARMED : return sizeof(DummyALMparam.subparams)/sizeof(DummyALMparam.subparams[0]);
    default         : return 0;
    }
}
#pragma warning( pop )

static inline PNTTYP hsc_point_get_remote_type(PNTTYP pointType, PNTTYP pointRemoteType)
{
    if (pointRemoteType == 0)
        return pointType;
    else
        return pointRemoteType;
}

/*
PROTOTYPES:
*/

EXTERN_C int2       hsc_ispointavailable_history    (PNTNUM*);
EXTERN_C int2       hsc_ispointavailable_netapi     (PNTNUM*);
EXTERN_C int2       hsc_ispointavailable_odbcdrv    (PNTNUM*);
EXTERN_C int2       hsc_ispointavailable_reports    (PNTNUM*);
EXTERN_C int2       hsc_ispointavailable_srvscripting(PNTNUM*);
EXTERN_C BOOL       hsc_ispoint_local       (PNTNUM);
EXTERN_C int CALLBACK   hsc_notification    (struct timeb,int,int,char*,char*,char*,char*,char*,char*,char*);
EXTERN_C GINDX*     hsc_points_get          (PNTNUM);
EXTERN_C void       hsc_points_flush        ();
EXTERN_C void       hsc_point_flush         (PNTNUM);
EXTERN_C STApoint*  hsc_point_access        (PNTNUM);
EXTERN_C int2       hsc_point_ack           (PNTNUM);
EXTERN_C int        hsc_point_count         (PNTTYP,int2,uint2);
EXTERN_C int        hsc_point_count_by_area (int);
EXTERN_C int        hsc_point_count_by_areaconn(int,int);
EXTERN_C int        hsc_point_count_by_conn (int iConnection);
EXTERN_C int        hsc_point_count_by_type (PNTcount**);
EXTERN_C int        hsc_point_count_by_type_ex (PNTcount**, BOOL);
EXTERN_C PNTNUM     hsc_number_of_points    ();
EXTERN_C PNTNUM     hsc_point_find_free     (PNTTYP type);
EXTERN_C PNTNUM     hsc_point_find_free_ex  (PNTTYP type, PNTTYP remotetype);
EXTERN_C PNTNUM     hsc_point_number        (const char*);
EXTERN_C PNTNUM     hsc_point_number_callback(const char*, on_gda_func_calling, on_gda_func_called);
EXTERN_C PNTNUM     hsc_point_number_callback_ex(const char*, int, on_gda_func_calling, on_gda_func_called);
EXTERN_C PNTNUM     hsc_point_number_ex     (const char*,int);
EXTERN_C int        hsc_point_number_ex2    (int,int, const char*const*,PNTNUM*,GDAERR*);
EXTERN_C int        hsc_point_number_ex3    (int,int, const char*const*,PNTNUM*,GDAERR*, on_gda_func_calling, on_gda_func_called);
EXTERN_C PNTNUM     hsc_point_number_search (const char*,PNTNUM);
EXTERN_C PNTNUM     hsc_point_number_search2 (const char*,PNTNUM,BOOL);
EXTERN_C PNTTYP     hsc_point_type          (PNTNUM);
EXTERN_C PNTTYP     hsc_point_type_ex       (STApoint *);
EXTERN_C uint2      hsc_point_type_to_acr   (PNTTYP pointtype);
EXTERN_C BOOL       hsc_point_is_tps        (PNTNUM);
EXTERN_C BOOL       hsc_point_is_tps_ex     (STApoint *pPoint);
EXTERN_C BOOL       hsc_point_is_containerequipment(PNTNUM);
EXTERN_C BOOL       hsc_point_is_containerequipment_ex(STApoint *);
EXTERN_C PNTTYP     hsc_point_remote_type   (PNTNUM);
EXTERN_C PNTTYP     hsc_point_remote_type_ex(STApoint *);
EXTERN_C int2       hsc_point_subtype       (PNTNUM);
EXTERN_C int2       hsc_point_subtype_ex    (STApoint *);
EXTERN_C uint2      hsc_point_itemnumber    (PNTNUM);
EXTERN_C uint2      hsc_point_itemnumber_ex (STApoint *);
EXTERN_C int        hsc_point_name          (PNTNUM,char*,int);
EXTERN_C int        hsc_point_name_change   (PNTNUM, char*);
EXTERN_C int        hsc_point_area          (PNTNUM);
EXTERN_C int        hsc_point_area_ex       (STApoint *);
EXTERN_C int        hsc_point_area_change   (PNTNUM, int2);
EXTERN_C int        hsc_point_subtype_change(PNTNUM, int2);
EXTERN_C int        hsc_point_area_change_ex(PNTNUM, STApoint *, int2);
EXTERN_C int        hsc_point_areachg_by_conn(int,int2);
EXTERN_C int        hsc_tpspoint_areachg_by_tpsunit(int,int,int2,int2);
EXTERN_C int        hsc_point_guid_change   (PNTNUM, GUID);
EXTERN_C int        hsc_point_desc_change   (PNTNUM, char *);
EXTERN_C int        hsc_point_connection    (PNTNUM);
EXTERN_C int        hsc_point_connection_ex (STApoint *);
EXTERN_C int2       hsc_point_pointservertype (PNTNUM);
EXTERN_C int2       hsc_point_pointservertype_ex (STApoint *);
EXTERN_C int        hsc_point_pointservertype_name(PNTNUM point, char* name, int namelen);
EXTERN_C int        hsc_point_size          (PNTNUM,uint2*,uint2*,uint2*,uint2*);
EXTERN_C int        hsc_point_read          (PNTNUM,uint2*,uint2*,uint2*,uint2*);
EXTERN_C int        hsc_point_read2         (PNTNUM,uint2*,uint2*,uint2*,uint2*,PNTTYP*);
EXTERN_C int        hsc_point_write         (PNTNUM,uint2*,uint2*,uint2*,uint2*);
EXTERN_C PNTNUM     hsc_point_create        (char*,PNTTYP,int2,char*,CREATETIME*,PNTNUM,int2,PNTNUM*,int2,char*,PNTTYP,PNTNUM,GUID*);
EXTERN_C PNTNUM     hsc_point_create_ex     (char*,PNTTYP,int2,char*,CREATETIME*,PNTNUM,int2,PNTNUM*,int2,char*,PNTTYP,PNTNUM,GUID*,BOOL,int);
EXTERN_C PNTNUM     hsc_point_create_system (char*,int2,char*,CREATETIME*,PNTNUM,int2,PNTNUM*,int2,char*,uint2,PNTNUM,GUID*);
EXTERN_C int        hsc_point_delete        (PNTNUM);
EXTERN_C int        hsc_point_delete_duplicate(PNTNUM);
EXTERN_C int        hsc_point_delete_ex     (PNTNUM,BOOL,BOOL,BOOL);
EXTERN_C int        hsc_point_delete_ex2    (PNTNUM,DWORD);
EXTERN_C int        hsc_point_delete_filedata (PNTNUM*,int);
EXTERN_C int        hsc_point_delete_by_areaconn(int,int);
EXTERN_C int        hsc_point_delete_by_conn(int iConneciton);
EXTERN_C int        hsc_tpspoint_delete_by_tpsunit(int,int,int2);
EXTERN_C int        hsc_point_delete_lock_query(PNTNUM point, PNTNUM **ppPointsToLock, int *piNumPointsToLock);
EXTERN_C void       hsc_point_clear_all     ();
EXTERN_C void       hsc_point_resubscribe   (PNTNUM*,uint4);
EXTERN_C void       hsc_point_resubscribe_all();
EXTERN_C void       hsc_point_unsubscribe   (PNTNUM*,uint4);
EXTERN_C void       hsc_point_unsubscribe_all();
EXTERN_C void       hsc_point_validate      (PNTNUM);
EXTERN_C int        hsc_combopoint_validate_param_connections(PNTNUM);
EXTERN_C void       hsc_point_validate_all  ();
EXTERN_C void       hsc_point_validate_all_ex (BOOL);
EXTERN_C void       hsc_point_validate_conn (char*);

EXTERN_C int        hsc_point_alarm_display (PNTNUM,char*,int);
EXTERN_C int        hsc_point_assoc_display (PNTNUM,char*,int);
EXTERN_C int        hsc_point_detail_display(PNTNUM,char*,int);
EXTERN_C int        hsc_point_group_display (PNTNUM,char*,int);
#ifdef sm1200
EXTERN_C int        hsc_point_sql_createarea(PNTNUM,int);
#endif

/* do not use hsc_pnttyp_list, use hsc_pnttyp_list_create instead */
EXTERN_C int        hsc_pnttyp_list_create  (enumlist**);
EXTERN_C int        hsc_pnttyp_list     (enumlist*,int); /* obsolete */
EXTERN_C int        hsc_pnttyp_number   (char*);
EXTERN_C int        hsc_pnttyp_name     (int,char*,int);

EXTERN_C int        hsc_pntsubtyp_list_create (int,enumlist**);
EXTERN_C int        hsc_pntsubtyp_number    (int,char*);
EXTERN_C int        hsc_pntsubtyp_name  (int,int,char*,int);

EXTERN_C PNTparam*  hsc_param_access_lock   (STApoint*,PRMNUM,PRMNUM*,GINDX*);
EXTERN_C void       hsc_param_access_release(STApoint*,PNTparam*,GINDX);
EXTERN_C PNTparam*  hsc_param_block_check   (STApoint*,PNTparam*,PRMNUM);
EXTERN_C PNTparam*  hsc_param_find_first    (STApoint*,GINDX*);
EXTERN_C PNTparam*  hsc_param_find_next (STApoint*,GINDX*,PNTparam**,PNTparam*,PRMNUM);
EXTERN_C void       hsc_param_find_release  (GINDX*);
EXTERN_C PNTparam*  hsc_param_find_by_name  (PNTNUM,char*,PRMNUM*,GINDX*);
EXTERN_C PNTparam*  hsc_param_find_by_number(PNTNUM,PRMNUM,GINDX*);
EXTERN_C PNTparam*  hsc_param_add       (PNTNUM,PRMNUM,GINDX*,char*,fatDICTitem*,char*,PNTparam*);
EXTERN_C PNTparam*  hsc_param_upd_source(PNTNUM,PRMNUM,GINDX*,char*);
EXTERN_C DICTitem*  hsc_class_param_find_by_name  (STApoint*,char*);
EXTERN_C DICTitem*  hsc_class_param_find_by_number(STApoint*,PRMNUM);

EXTERN_C int        hsc_param_count     ();
EXTERN_C PARhandle  hsc_param_handle    (PNTNUM,PRMNUM,int);
EXTERN_C void       hsc_param_handle_release(PARhandle*);
EXTERN_C PRMNUM     hsc_param_create_alt    (PNTNUM,char*,int);
EXTERN_C PRMNUM     hsc_param_create_alt_ex (PNTNUM,char*,int,on_gda_func_calling,on_gda_func_called);
EXTERN_C PRMNUM     hsc_param_create    (PNTNUM,PRMNUM,char*,fatDICTitem*,char*);
typedef PRMNUM (*CreateParamFunction)(PNTNUM, const char *, const char *);
EXTERN_C PRMNUM     hsc_param_create_enum(PNTNUM,const char*,DATAaccess);
EXTERN_C PRMNUM     hsc_param_create_int2(PNTNUM,const char*,int2);
EXTERN_C PRMNUM     hsc_param_create_int4(PNTNUM,const char*,int4);
EXTERN_C PRMNUM     hsc_param_create_char(PNTNUM,const char*,const char*);
EXTERN_C PRMNUM     hsc_param_create_variant_bstr(PNTNUM,const char*,BSTR);
EXTERN_C PRMNUM     hsc_param_create_variant_bstr_by_szchar(PNTNUM,const char*,const char*);
EXTERN_C PRMNUM     hsc_param_create_variant_vector_char(PNTNUM,const char*,const char**,int);
EXTERN_C PRMNUM     hsc_param_create_param_ref(PNTNUM,const char*,const char*,const char*);
EXTERN_C PRMNUM     hsc_param_create_point_ref(PNTNUM,const char*,const char*);
EXTERN_C PRMNUM     hsc_param_create_derived (PNTNUM,PRMNUM,char*,DATAaccess,PARvalue*,uint2,uint2);

typedef PRMNUM (*CreateParamFunction)(PNTNUM, const char *, const char *);
EXTERN_C PRMNUM     hsc_param_create_int2(PNTNUM,const char*,int2);
EXTERN_C PRMNUM     hsc_param_create_char(PNTNUM,const char*,const char*);
EXTERN_C PRMNUM     hsc_param_create_variant_bstr(PNTNUM,const char*,BSTR);
EXTERN_C PRMNUM     hsc_param_create_variant_bstr_by_szchar(PNTNUM,const char*,const char*);
EXTERN_C PRMNUM     hsc_param_create_variant_vector_char(PNTNUM,const char*,const char**,int);
EXTERN_C PRMNUM     hsc_param_create_param_ref(PNTNUM,const char*,const char*,const char*);
EXTERN_C PRMNUM     hsc_param_create_point_ref(PNTNUM,const char*,const char*);

EXTERN_C int        hsc_param_delete    (PNTNUM,PRMNUM);
EXTERN_C int        hsc_param_delete_marked (PNTNUM);
EXTERN_C int        hsc_param_mark_delete   (PNTNUM,PRMNUM);
EXTERN_C int        hsc_param_unmark_delete (PNTNUM,PRMNUM);
/* do not use hsc_param_list or hsc_param_list_create, use hsc_param_list_create_limit instead */
EXTERN_C int        hsc_param_list_create_limit (PNTNUM,int,enumlist**);
EXTERN_C int        hsc_param_list_create   (PNTNUM,enumlist**);
EXTERN_C int        hsc_param_list_create_ana_aux_params    (PNTNUM,enumlist**);
EXTERN_C int        hsc_param_list_create_instance_params   (PNTNUM,enumlist**);
EXTERN_C int        hsc_param_list      (PNTNUM,enumlist*,int); /* obsolete */
EXTERN_C int        hsc_param_list_filter   (enumlist*,int,enumlist**);
EXTERN_C int        hsc_param_list_local    (PNTNUM,PNTTYP,int,enumlist **);
EXTERN_C int        hsc_param_list_merge    (int,int,enumlist *,int,enumlist *,int,enumlist **);
EXTERN_C int        hsc_param_method    (PNTNUM,PRMNUM);
EXTERN_C PRMNUM     hsc_param_number    (PNTNUM,char*);
EXTERN_C PRMNUM     hsc_param_number_callback(PNTNUM,char*,on_gda_func_calling,on_gda_func_called);
EXTERN_C PRMNUM     hsc_param_number_ex (PNTNUM*,char*);
EXTERN_C int        hsc_param_number_ex2    (int,char**,PNTNUM*,PRMNUM*,GDAERR*);
EXTERN_C int        hsc_param_number_ex3    (int,int,char**,PNTNUM*,PRMNUM*,GDAERR*);
EXTERN_C int        hsc_param_number_ex4    (int,int,char**,PNTNUM*,PRMNUM*,GDAERR*,on_gda_func_calling,on_gda_func_called);
EXTERN_C int        hsc_param_number_local_ex(int,char**,PNTNUM*,PRMNUM*,GDAERR*);
EXTERN_C PRMNUM     hsc_param_number_local  (PNTNUM*,char*);
EXTERN_C PRMNUM     hsc_param_number_local_bytype (PNTTYP,char*);
EXTERN_C int        hsc_param_name      (PNTNUM,PRMNUM,char*,int);
EXTERN_C int        hsc_param_name_next (PNTNUM,PRMNUM,char*,int);
EXTERN_C int        hsc_param_source    (PNTNUM,PRMNUM,char*,int);
EXTERN_C int        hsc_param_type      (PNTNUM,PRMNUM);
EXTERN_C int        hsc_param_type_ex   (PNTNUM,PRMNUM,int);
EXTERN_C int        hsc_param_SubParamClass(PNTNUM,PRMNUM);
EXTERN_C int        hsc_param_format    (PNTNUM,PRMNUM);
EXTERN_C int        hsc_param_id_item   (PNTNUM,PRMNUM,int,PNTNUM*,PRMNUM*);
EXTERN_C int        hsc_param_id_limits (PNTNUM,PRMNUM,PNTNUM*,PRMNUM*,PNTNUM*,PRMNUM*);
EXTERN_C int        hsc_param_id_range  (PNTNUM,PRMNUM,PNTNUM*,PRMNUM*,PNTNUM*,PRMNUM*);
EXTERN_C int        hsc_param_limits    (PNTNUM,PRMNUM,double*,double*);
EXTERN_C int        hsc_param_limits_local  (PNTNUM,PRMNUM,double*,double*);
EXTERN_C int        hsc_param_limits_ex (int4,int,PNTNUM*,PRMNUM*,double*,double*,GDAERR*);
EXTERN_C int        hsc_param_proc      (PNTNUM,PRMNUM,int2,int2,double,double,int2,int2*,double*);
EXTERN_C int        hsc_param_range     (PNTNUM,PRMNUM,double*,double*);
EXTERN_C int        hsc_param_units     (int, PNTNUM*, PRMNUM*, char ***,GDAERR**,int4);
EXTERN_C int        hsc_param_range_local   (PNTNUM,PRMNUM,double*,double*);
EXTERN_C int        hsc_param_range_ex  (int4,int,PNTNUM*,PRMNUM*,double*,double*,GDAERR*);
EXTERN_C int        hsc_param_raise     (PNTNUM,PRMNUM,int,double,PARvalue*,uint2*);
EXTERN_C int        hsc_param_value     (PNTNUM,PRMNUM,int,PARvalue*,uint2*);
EXTERN_C int        hsc_param_value_sec (PNTNUM,PRMNUM,int,PARvalue*,uint2*,GDASECURITY*);
EXTERN_C int        hsc_param_values    (int,int,PNTNUM*,PRMNUM*,int*,PARvalue*,uint2*,int*);
EXTERN_C int        hsc_param_values2   (int,int,PNTNUM*,PRMNUM*,int*,PARvalue*,uint2*,int*);
EXTERN_C int        hsc_param_values_get    (int,PNTNUM*,PRMNUM*,int*,PARvalue*,uint2*,GDAERR*);
EXTERN_C int        hsc_param_values_get2   (int,PNTNUM*,PRMNUM*,int*,PARvalue*,uint2*,GDAERR*);
EXTERN_C int        hsc_param_values_put    (int,PNTNUM*,PRMNUM*,int*,PARvalue*,uint2*,GDAERR*,GDASECURITY*);
EXTERN_C int        hsc_param_values_put_ex (int,int,PNTNUM*,PRMNUM*,int*,PARvalue*,uint2*,GDAERR*,GDASECURITY*);
EXTERN_C int        hsc_param_value_put (PNTNUM,PRMNUM,int,PARvalue*,uint2*);
EXTERN_C int        hsc_param_value_put_priority    (PNTNUM,PRMNUM,int,PARvalue*,uint2*,int,int);
EXTERN_C int        hsc_param_value_save    (PNTNUM,PRMNUM,int,PARvalue*,uint2*);
EXTERN_C int        hsc_param_values_save   (int,PNTNUM*,PRMNUM*,int*,PARvalue*,uint2*,GDAERR*,GDASECURITY*);
EXTERN_C int        hsc_param_value_put_sec (PNTNUM,PRMNUM,int,PARvalue*,uint2*,GDASECURITY*);
EXTERN_C int        hsc_param_value_of_type (PNTNUM,PRMNUM,int,PARvalue*,uint2*);
EXTERN_C int        hsc_param_value_of_type2(PNTNUM,PRMNUM,int,PARvalue*,uint2*,GDAERR*);
EXTERN_C int        hsc_param_values_get_of_type(int,uint2,PNTNUM*,PRMNUM*,int*,uint2*,GDAERR*);
EXTERN_C int        hsc_param_limit_min (PNTNUM,PRMNUM,int,PARvalue*,uint2*);
EXTERN_C int        hsc_param_limit_max (PNTNUM,PRMNUM,int,PARvalue*,uint2*);
EXTERN_C int        hsc_param_range_min (PNTNUM,PRMNUM,int,PARvalue*,uint2*);
EXTERN_C int        hsc_param_range_max (PNTNUM,PRMNUM,int,PARvalue*,uint2*);
EXTERN_C int        hsc_param_enum_list_create (PNTNUM,PRMNUM,int,enumlist**);
EXTERN_C char*      hsc_param_enum_string   (PNTNUM,PRMNUM,int4);
EXTERN_C int        hsc_param_enum_ordinal  (PNTNUM,PRMNUM,char*);
EXTERN_C int        hsc_param_acquire   (int,PNTNUM*,PRMNUM*,int);
EXTERN_C int        hsc_param_subscribe (int,PNTNUM*,PRMNUM*,int);
EXTERN_C int        hsc_param_subscribe_update(int,PNTNUM*,PRMNUM*,int*,uint8*);
EXTERN_C int        hsc_param_subscribe_update2(int,PNTNUM*,PRMNUM*,int*,uint8*, uint2*);
EXTERN_C int        hsc_param_subscribe_cancel(uint8*);
EXTERN_C int        hsc_param_resubscribe   (int,PNTNUM*,PRMNUM*,int);
EXTERN_C int        hsc_param_unsubscribe   (int,PNTNUM*,PRMNUM*,int);
EXTERN_C int        hsc_param_trigger   (int,PNTNUM*,PRMNUM*,int);
EXTERN_C int        hsc_param_trigger2  (int,PNTNUM*,PRMNUM*,int*);
EXTERN_C int        _hsc_param_find_free_   (STApoint*,PRMNUM,PRMNUM*,int);
EXTERN_C int        _hsc_param_delete_  (STApoint*,PNTparam*,PNTNUM,PRMNUM);
EXTERN_C char*      _hsc_param_create_index_array_ (PNTNUM,PNTparam*,int*);
EXTERN_C DICTvalue* _hsc_param_age_     (PNTNUM point, PNTparam* pParam, int Age);
EXTERN_C int        hsc_param_flush     (PNTNUM,PRMNUM);
EXTERN_C int        hsc_param_flags     (PNTNUM,PRMNUM);
EXTERN_C BOOL       hsc_param_GetDynScnStatus(STApoint *pPoint, PNTparam *pParam, PRMNUM Param, PRMNUM SubParam, int iCon);
EXTERN_C int        hsc_param_add_rangelimits   (PNTNUM, PRMNUM, DICTvalue, DICTvalue, DICTvalue, DICTvalue);
EXTERN_C BOOL       hsc_param_is_instance_param(PNTNUM, PRMNUM);
EXTERN_C BOOL       hsc_param_is_intdiag_alarm(PNTparam*,int4);
EXTERN_C uint2      hsc_param_get_flags (PNTNUM pointNum, PRMNUM paramNum);
EXTERN_C uint2      hsc_param_get_flags_ex (PNTparam*);

EXTERN_C int        hsc_enumlist_destroy(enumlist**);
EXTERN_C int        hsc_enumlist_copy   (enumlist*,enumlist*,int);

EXTERN_C int        hsc_stringlist_midl_destroy (int,char***);

EXTERN_C uint2*     hsc_decode_prmdef_ex    (STApoint* pPoint, PNTparam* pParam, PRMDEF prmdef);  // internal use only

EXTERN_C int        hsc_geti2       (PNTNUM     point, PRMDEF prmdef, uint2 *value);
EXTERN_C int        hsc_geti2_ex    (STApoint *pPoint, PRMDEF prmdef, uint2 *value);
EXTERN_C int        hsc_geti4       (PNTNUM     point, PRMDEF prmdef, int4  *value);
EXTERN_C int        hsc_geti4_ex    (STApoint *pPoint, PRMDEF prmdef, int4  *value);
EXTERN_C int        hsc_geti8       (PNTNUM     point, PRMDEF prmdef, int8  *value);
EXTERN_C int        hsc_geti8_ex    (STApoint *pPoint, PRMDEF prmdef, int8  *value);
EXTERN_C int        hsc_getrl       (PNTNUM     point, PRMDEF prmdef, float *value);
EXTERN_C int        hsc_getrl_ex    (STApoint *pPoint, PRMDEF prmdef, float *value);
EXTERN_C int        hsc_getr8       (PNTNUM     point, PRMDEF prmdef, double*value);
EXTERN_C int        hsc_getr8_ex    (STApoint *pPoint, PRMDEF prmdef, double*value);
EXTERN_C int        hsc_getch       (PNTNUM     point, PRMDEF prmdef, char  *value, int sizeofvalue);
EXTERN_C int        hsc_getch_ex    (STApoint *pPoint, PRMDEF prmdef, char  *value, int sizeofvalue);
EXTERN_C int        hsc_geti2s      (PNTNUM     point, PRMDEF prmdef, uint2 *value, int length);
EXTERN_C int        hsc_geti2s_ex   (STApoint *pPoint, PRMDEF prmdef, uint2 *value, int length);

EXTERN_C int        hsc_puti2       (PNTNUM     point, PRMDEF prmdef, uint2 value);
EXTERN_C int        hsc_puti2_ex    (STApoint *pPoint, PRMDEF prmdef, uint2 value);
EXTERN_C int        hsc_puti4       (PNTNUM     point, PRMDEF prmdef, int4  value);
EXTERN_C int        hsc_puti4_ex    (STApoint *pPoint, PRMDEF prmdef, int4  value);
EXTERN_C int        hsc_putrl       (PNTNUM     point, PRMDEF prmdef, float value);
EXTERN_C int        hsc_putrl_ex    (STApoint *pPoint, PRMDEF prmdef, float value);
EXTERN_C int        hsc_putr8       (PNTNUM     point, PRMDEF prmdef, double value);
EXTERN_C int        hsc_putr8_ex    (STApoint *pPoint, PRMDEF prmdef, double value);
EXTERN_C int        hsc_putch       (PNTNUM     point, PRMDEF prmdef, char*  value, int sizeofvalue);
EXTERN_C int        hsc_putch_ex    (STApoint *pPoint, PRMDEF prmdef, char*  value, int sizeofvalue);

EXTERN_C int        hsc_geti2_param     (PNTNUM point, PRMNUM param, PRMDEF prmdef, uint2 *value);
EXTERN_C int        hsc_geti2_param_ex  (PNTparam*           pparam, PRMDEF prmdef, uint2 *value);
EXTERN_C int        hsc_geti4_param     (PNTNUM point, PRMNUM param, PRMDEF prmdef, int4  *value);
EXTERN_C int        hsc_geti4_param_ex  (PNTparam*           pparam, PRMDEF prmdef, int4  *value);
EXTERN_C int        hsc_geti8_param     (PNTNUM point, PRMNUM param, PRMDEF prmdef, int8  *value);
EXTERN_C int        hsc_geti8_param_ex  (PNTparam*           pparam, PRMDEF prmdef, int8  *value);
EXTERN_C int        hsc_getrl_param     (PNTNUM point, PRMNUM param, PRMDEF prmdef, float *value);
EXTERN_C int        hsc_getr8_param     (PNTNUM point, PRMNUM param, PRMDEF prmdef, double *value);
EXTERN_C int        hsc_getr8_param_ex  (PNTparam*           pparam, PRMDEF prmdef, double *value);
EXTERN_C int        hsc_getch_param     (PNTNUM point, PRMNUM param, PRMDEF prmdef, char  *value, int length);
EXTERN_C int        hsc_geti2s_param    (PNTNUM point, PRMNUM param, PRMDEF prmdef, uint2 *value, int length);
EXTERN_C int        hsc_geti2s_param_ex (PNTparam*           pparam, PRMDEF prmdef, uint2 *value, int length);

EXTERN_C int        hsc_puti2_param     (PNTNUM point, PRMNUM param, PRMDEF prmdef, uint2  value);
EXTERN_C int        hsc_puti2_param_ex  (PNTparam*           pparam, PRMDEF prmdef, uint2  value);
EXTERN_C int        hsc_puti4_param     (PNTNUM point, PRMNUM param, PRMDEF prmdef, int4   value);
EXTERN_C int        hsc_puti8_param     (PNTNUM point, PRMNUM param, PRMDEF prmdef, int8   value);
EXTERN_C int        hsc_putrl_param     (PNTNUM point, PRMNUM param, PRMDEF prmdef, float  value);
EXTERN_C int        hsc_putr8_param     (PNTNUM point, PRMNUM param, PRMDEF prmdef, double value);
EXTERN_C int        hsc_putch_param     (PNTNUM point, PRMNUM param, PRMDEF prmdef, char  *value, int length);
EXTERN_C int        hsc_puti2s_param    (PNTNUM point, PRMNUM param, PRMDEF prmdef, uint2 *value, int length);
EXTERN_C int        hsc_puti2s_param_ex (PNTparam*           pparam, PRMDEF prmdef, uint2 *value, int length);
EXTERN_C int        hsc_putdt_param     (PNTNUM point, PRMNUM param, PRMDEF prmdef, uint2 *value, int type);

EXTERN_C int        hsc_geti2_struct    (PNTNUM     point, uint2 location, uint2 *value);
EXTERN_C int        hsc_geti2_struct_ex (STApoint *pPoint, uint2 location, uint2 *value);
EXTERN_C int        hsc_geti4_struct    (PNTNUM     point, uint2 location, uint4 *value);
EXTERN_C int        hsc_geti4_struct_ex (STApoint *pPoint, uint2 location, uint4 *value);
EXTERN_C int        hsc_getbits_struct  (PNTNUM     point, uint2 location, uint2 *value, uint2 bitmask);
EXTERN_C int        hsc_getbits_struct_ex   (STApoint *pPoint, uint2 location, uint2 *value, uint2 bitmask);
EXTERN_C int        hsc_getch_struct    (PNTNUM     point, uint2 location, uint2 length, char *value, int sizeofvalue);
EXTERN_C int        hsc_getch_struct_ex (STApoint *pPoint, uint2 location, uint2 length, char *value, int sizeofvalue);
EXTERN_C int        hsc_getbytes_struct (PNTNUM     point, uint2 location, uint2 length, BYTE *value);
EXTERN_C int        hsc_getbytes_struct_ex  (STApoint *pPoint, uint2 location, uint2 length, BYTE *value);

EXTERN_C int        hsc_puti2_struct    (PNTNUM     point, uint2 location, uint2 value);
EXTERN_C int        hsc_puti2_struct_ex (STApoint *pPoint, uint2 location, uint2 value);
EXTERN_C int        hsc_puti4_struct    (PNTNUM     point, uint2 location, uint4 value);
EXTERN_C int        hsc_puti4_struct_ex (STApoint *pPoint, uint2 location, uint4 value);
EXTERN_C int        hsc_putbits_struct  (PNTNUM     point, uint2 location, uint2 value, uint2 bitmask);
EXTERN_C int        hsc_putbits_struct_ex   (STApoint *pPoint, uint2 location, uint2 value, uint2 bitmask);
EXTERN_C int        hsc_putch_struct    (PNTNUM     point, uint2 location, uint2 length, char *value, int sizeofvalue);
EXTERN_C int        hsc_putch_struct_ex (STApoint *pPoint, uint2 location, uint2 length, char *value, int sizeofvalue);
EXTERN_C int        hsc_putbytes_struct (PNTNUM     point, uint2 location, uint2 length, BYTE *value);
EXTERN_C int        hsc_putbytes_struct_ex  (STApoint *pPoint, uint2 location, uint2 length, BYTE *value);

EXTERN_C int2       hsc_techaddr_deltag_by_pnt(PNTNUM);
EXTERN_C int4       hsc_techaddr_gettagtype(int2);
EXTERN_C int2       hsc_techaddr_gettag(PNTNUM,int4*,char*,int2);
EXTERN_C int2       hsc_techaddr_puttag(PNTNUM,int2,char*);

EXTERN_C int        getlst(int,float*,int2*);
EXTERN_C int        givlst(int,float*,int2*);

EXTERN_C int        hsc_tagtyp_find (int);
EXTERN_C int4 FORTCALL POINTTRA (int4*,int4*,int4*,PNTNUM*,PRMNUM*);
EXTERN_C int4 FORTCALL REATAGTYP(int4*,int4*,int2*,int2*,int4*);
EXTERN_C int        hsc_prmdef2param (int4,int4,PNTNUM,int2);
EXTERN_C int        hsc_param2name (int4,int4,PNTNUM,PRMNUM,char*,int);

EXTERN_C void       hsc_rtn_points(uint2,uint2,uint2,uint2);
EXTERN_C void       hsc_rtn_point(PNTNUM);

EXTERN_C int        PARvalueConvert(PARvalue*,DATAtype,PARvalue*,DATAtype);
EXTERN_C int        GDAITEMConvert(GDAITEM*,DATAtype,GDAITEM*);
EXTERN_C void       CtoFPARvalue(PARvalue*,DATAtype,int2*,PARvalue*);
EXTERN_C void       FtoCPARvalue(PARvalue*,DATAtype,int,PARvalue*);
EXTERN_C int        GDAtoPARvalue(GDAITEM*,PARvalue*,DATAtype*);
EXTERN_C GDAITEM*   PARtoGDAvalue(PARvalue*,DATAtype);
EXTERN_C PARvalue*  ClearPARvalue(PARvalue*,DATAtype);
EXTERN_C PARvalue*  InitializePARvalue(PARvalue*);

// Implementation for point server is not EXTERN_C
#ifdef _POINTSERVER
GDAITEM*        DestroyGDAvalue(GDAITEM*);
GDAITEM*        DestroyGDAvalues(GDAITEM*, int);
GDAITEM*        ClearGDAvalue(GDAITEM*);
GDAITEM*        InitializeGDAvalue(GDAITEM*);
GDAITEM*        CopyGDAvalue(GDAITEM*,GDAITEM*);
#else
EXTERN_C GDAITEM*   DestroyGDAvalue(GDAITEM*);
EXTERN_C GDAITEM*   DestroyGDAvalues(GDAITEM*, int);
EXTERN_C GDAITEM*   ClearGDAvalue(GDAITEM*);
EXTERN_C GDAITEM*   InitializeGDAvalue(GDAITEM*);
EXTERN_C GDAITEM*   CopyGDAvalue(GDAITEM*,GDAITEM*);
#endif
EXTERN_C int        PARvaluetoDble(PARvalue*,DATAtype,double*);
EXTERN_C int        PARvaluetoReal(PARvalue*,DATAtype,float*);
EXTERN_C int        PARvaluetoInt8(PARvalue*,DATAtype,int8*);
EXTERN_C int        PARvaluetoInt4(PARvalue*,DATAtype,int4*);
EXTERN_C int        PARvaluetoInt2(PARvalue*,DATAtype,int2*);
EXTERN_C HRESULT    SerializeVariantData(GDAVARIANT,char**,int*);
EXTERN_C HRESULT    SerializeVariantDataSize(GDAVARIANT,int*);
EXTERN_C HRESULT    UnSerializeVariantData(GDAVARIANT*,char*);
EXTERN_C int        hsc_variant_to_PARvalue(GDAVARIANT*,PARvalue*,uint2*,int);
EXTERN_C int        hsc_param_type_convert(GDAVARIANT*);
EXTERN_C int        hsc_param_type_convert_from_vt(VARTYPE);
EXTERN_C int        hsc_param_is_variant(PNTNUM point, PRMNUM param);
EXTERN_C int        hsc_param_is_variant_bitstring(GDAVARIANT *);
EXTERN_C int        hsc_param_is_variant_exposed(PNTNUM point, PRMNUM param, int offset);
EXTERN_C int        hsc_param_variant_type(PNTNUM, PRMNUM, VARTYPE*);
EXTERN_C int        hsc_param_variant_set_type(PNTNUM, PRMNUM, VARTYPE, uint2);
EXTERN_C int        hsc_param_is_array (PNTNUM,PRMNUM);

EXTERN_C int        hsc_security_set(GDASECURITY*);
EXTERN_C int            hsc_security_set_ex(int,GDASECURITY*);
EXTERN_C int        hsc_security_set_priority(GDASECURITY* pSecurity, int command, int residual);
EXTERN_C int        hsc_security_set_priority_stn(GDASECURITY* pSecurity, int command, int residual, int2 stationLevel);
EXTERN_C int        hsc_security_set_stn(GDASECURITY* pSecurity, int2 stationLevel);
EXTERN_C void       hsc_security_destroy(GDASECURITY*);
EXTERN_C int        hsc_variant_to_gdaitem(VARIANT *pVar, GDAITEM *pItem);

EXTERN_C BOOL       hsc_ispoint_replicable(PNTNUM);
EXTERN_C BOOL       hsc_ispoint_replicable_ex(STApoint *);
EXTERN_C BOOL       hsc_istype_replicable(PNTTYP);
EXTERN_C BOOL       hsc_isparam_replicable(PNTNUM, PRMNUM, PNTTYP, uint2);

/*BB alarming functions*/
EXTERN_C int2       hsc_BBAlarmUpdate(struct almdir*,BOOL,BOOL,BOOL);
EXTERN_C int2       hsc_getAlarmState(PNTNUM,PRMNUM,uint4*,uint4*,uint2*,uint2,uint4,int);
EXTERN_C int2       hsc_setAlarmState(PNTNUM,uint2,uint2,uint2,uint4,BOOL,BOOL);
EXTERN_C int2       hsc_get_EE_and_BB(PNTNUM,PRMNUM,uint2*,uint4*);

/* aggregate alarming functions and struct */
typedef enum {
    AC_INVALIDATE = 0,
    AC_ADDITION,
    AC_CHANGE,
    AC_SUBTRACTION
} AC_UPDATES;

EXTERN_C int        hsc_almcount_setpointalmcounts(PNTNUM point, PNTalmcount almcounts);
EXTERN_C int        hsc_almcount_clear(PNTNUM point);
EXTERN_C int        hsc_almcount_clear_container_equipment();
EXTERN_C int        hsc_almcount_refresh(PNTNUM point);
EXTERN_C int        hsc_almcount_refresh_ex(PNTNUM point, PNTNUM countpoint);
EXTERN_C int        hsc_almcount_clean_point(PNTNUM point, int station);
EXTERN_C int        hsc_almcount_update(PNTNUM point, AC_UPDATES update, PNTalmcount almcounts1, PNTalmcount almcounts2);
EXTERN_C int        hsc_almcount_updatepointparents(PNTNUM point, BOOL bParentsAdded, PNTNUM *pParentList, int count);
#ifdef __cplusplus
int                 hsc_almcount_updatepointparents_list(PNTNUM point, BOOL bParentsAdded, PNTNUM *pParentList, int count, STApoint* pPoint = NULL);
#endif
EXTERN_C int        hsc_almcount_updatepointswithcounts(PNTNUM point, int pointArea, BOOL bAddCounts, PNTNUM *pPoints, int count, PNTalmcount fullCounts);

EXTERN_C BOOL       hsc_almcount_apply_change(AC_UPDATES update, PNTalmcount *pTargetCounts, PNTalmcount almcounts1, PNTalmcount almcounts2, int2 nMinPriority);

EXTERN_C int        hsc_almcount_find(PNTNUM point, int offset, int station, PNTalmcount *pRetCount);
EXTERN_C int        hsc_almcount_clean_station(int station);
EXTERN_C int        hsc_almcount_validate_settings();
EXTERN_C int        hsc_almcount_recalculate();
EXTERN_C void       hsc_almcount_recalculate_on_startup();
EXTERN_C int        hsc_almcount_recalculate_point(PNTNUM point);

/* Enterprise Model functions */
EXTERN_C void       hsc_em_FreePointList(PNTNUM *pPointList);
EXTERN_C void       hsc_em_FreeNameList(char **ppNameList, int iNumNames);
EXTERN_C int        hsc_em_GetRootAssets(int *pCount, PNTNUM **ppPointList);
EXTERN_C int        hsc_em_GetRootAlarmGroups(int *pCount, PNTNUM **ppPointList);
EXTERN_C int        hsc_em_GetModelPoints(int *pCount, PNTNUM **ppPointList);
EXTERN_C int        hsc_em_GetServerPoints(int *pCount, PNTNUM **ppPointList);
EXTERN_C PNTNUM     hsc_em_GetSysPoint(uint2 pointSubType, uint2 iItemNumber);
EXTERN_C PNTNUM     hsc_em_GetSysPointByName(uint2 pointSubType, uint2 iItemNumber, const char* szTagName);
EXTERN_C int        hsc_em_GetServerTagName(char *szAlias, char *szTagName, int TagNameLen);
EXTERN_C int        hsc_em_GetSysPntTagName(uint2 pointSubType, uint2 iItemNumber, char* szTagName, int TagNameLen);
EXTERN_C int        hsc_em_GetSysPntSubTypeAndItemNumber(char *szTagName, int2 *pointSubType, int2 *itemNumber);
EXTERN_C int        hsc_em_GetSysPntDescription(uint2, uint2, char*, int);
EXTERN_C int        hsc_em_GetSysPntEntityName(uint2 pointSubType, uint2 iItemNumber, char* szEntityName, int EntityNameLen);
EXTERN_C int        hsc_em_GetRootEntities(int *pCount, PNTNUM **ppPointList);
EXTERN_C int        hsc_em_GetDSASystemName(char *name, int namelen);
EXTERN_C int        hsc_em_SetDSASystemName(char *name);
EXTERN_C void       hsc_em_GetLastPointChangeTime(HSCTIME *pTime);
EXTERN_C void       hsc_em_GetLastAssetLoadTime(HSCTIME *pTime);
EXTERN_C void       hsc_em_GetLastAlarmGroupLoadTime(HSCTIME *pTime);
EXTERN_C void       hsc_em_GetLastSystemAlarmGroupLoadTime(HSCTIME *pTime);
EXTERN_C void       hsc_em_GetLastSystemConfigLoadTime(HSCTIME *pTime);
EXTERN_C int        hsc_em_GetModelName(uint2 model, char *name, int namelen);
EXTERN_C int        hsc_em_SetModelName(uint2 model, char *name);
EXTERN_C PNTNUM     hsc_em_ResolveGUIDtoPoint(GUID *pGUID);
EXTERN_C int        hsc_em_ResolveGUIDtoTag(GUID *pGUID,struct tagfl *pTagRec);
EXTERN_C int2       hsc_em_ResolveGUIDToCrt(GUID *pGUID);
EXTERN_C int2       hsc_em_ResolveGUIDtoArea(GUID *pGUID);
EXTERN_C int        hsc_em_ResolveName(char*,int,struct tagfl*);
EXTERN_C int        hsc_em_ResolveFullName(char*,struct tagfl*);
EXTERN_C int        hsc_em_ResolveTagName(char*,int,struct tagfl*);
EXTERN_C int        hsc_em_ResolveTagNameEx(char*,int,PNTNUM,struct tagfl*);
EXTERN_C int        hsc_em_FindTagNameMatch(char *szName, struct tagfl *pRecord);
EXTERN_C int        hsc_em_FindNameMatch(char *szName, struct tagfl *pRecord);
EXTERN_C int        hsc_em_GetSimpleName(char *szName, char *szSimpleName, int iSimpleNameLen);
EXTERN_C int        hsc_em_TagNameSplit(char *szTagName, char *szOwner, int iOwnerLen, char *szBaseName, int iBaseNameLen);
EXTERN_C PNTNUM     hsc_em_GetDefaultOwnerEx(PNTTYP type, int2 subtype, int2 gdacon);
EXTERN_C PNTNUM     hsc_em_GetDefaultOwner(int gdacon);
EXTERN_C PNTNUM     hsc_em_GetOwnerPoint(char *szOwner);
EXTERN_C int        hsc_em_GetOwnerString(PNTNUM owner, char *szOwner, int iStrLen);
EXTERN_C BOOL       hsc_em_CheckTagNameClash(char *szTagName, PNTNUM owner, int iTagType, int iTagNum, int *piClashingTagNum);
EXTERN_C BOOL       hsc_em_CheckGUIDClash(GUID *pGUID, int iTagType, int iTagNum, int *piClashingTagType, int *piClashingTagNum);
EXTERN_C BOOL       hsc_em_CheckEntityNameClash(char *szName, PNTNUM parent, int iTagType, int iTagNum, int *piClashingTagType, int *piClashingTagNum, BOOL *pTagFound, struct tagfl *pTagRecord);
EXTERN_C int        hsc_GUIDFromString(char *szGUID, GUID *pGUID);
EXTERN_C int        hsc_StringFromGUID(GUID *pGUID, char *pszGUID);
EXTERN_C int        hsc_em_SetAlarmDisabled(PNTNUM, int2, BOOL);
EXTERN_C BOOL       hsc_em_GetAlarmDisabledMatch(PNTNUM);
EXTERN_C int        hsc_em_GetTotalAlarmDisabledAreas(int station);
EXTERN_C BOOL       hsc_em_HasAssignedConsoleAlarmDisabledDescendants(int console, int station, PNTNUM point);
EXTERN_C BOOL       hsc_em_GetConsoleAlarmDisabledMatch(int console, int station, PNTNUM point);
EXTERN_C HRESULT    hsc_em_SetConsoleAlarmDisabled(int console, int station, PNTNUM point, BOOL isEnable, BOOL isPropagate, int2 securityLevel);
EXTERN_C int        hsc_em_GetTotalConsoleAlarmDisabledAreas(int console, int station);
EXTERN_C int        hsc_em_SetSignatureDisabled(PNTNUM, int2, BOOL);
EXTERN_C BOOL       hsc_em_GetSignatureDisabledMatch(PNTNUM);
EXTERN_C int        hsc_em_GetGlobalEventServerName(char *name, int namelen);
EXTERN_C int        hsc_em_SetGlobalEventServerName(const char *name);
EXTERN_C int        hsc_em_FlattenUnassignedItems();
EXTERN_C int        hsc_em_GetControllerIORackTagName(uint2 iItemNumber, uint2 iRackNumber, char* szTagName, unsigned int TagNameLen);
EXTERN_C int        hsc_em_GetControllerIORackEntityName(uint2 iItemNumber, uint2 iRackNumber, char* szEntityName, unsigned int EntityNameLen);
EXTERN_C BOOL       hsc_point_is_company_enabled(PNTNUM point);

EXTERN_C int        hsc_point_name_ex(PNTNUM point, char *name, int namelen, int flags);
EXTERN_C int        hsc_point_entityname(PNTNUM point, char *name, int namelen);
EXTERN_C int        hsc_point_fullname(PNTNUM point, char *name, int namelen);
EXTERN_C int        hsc_point_location_tagname(PNTNUM point, char *name, int namelen);
EXTERN_C int        hsc_point_location_tagname_ex(PNTNUM point, char *name, int namelen, int flags);
EXTERN_C int        hsc_point_location_fullname(PNTNUM point, char *name, int namelen);
EXTERN_C int        hsc_point_entityname_change(PNTNUM point, char *name);
EXTERN_C int        hsc_point_owner_change(PNTNUM point, PNTNUM owner);
EXTERN_C int        hsc_point_rename(PNTNUM point);
EXTERN_C int        hsc_point_guid(PNTNUM point, GUID *pGUID);

EXTERN_C void       hsc_point_freeRelTypList(PNTRELTYP *pRelTypList);
EXTERN_C void       hsc_point_freeRelDirList(PNTRELDIR *pRelDirList);

EXTERN_C int        hsc_point_update_relatives_ex(PNTNUM point, PNTRELTYP reltyp, PNTRELDIR reldir, PNTNUM *pRelatives, int iNumRelatives, DWORD dwFlags, PNTNUM **ppPointsToLock, int *piNumPointsToLock);
EXTERN_C int        hsc_point_update_relatives(PNTNUM point, PNTRELTYP reltyp, PNTRELDIR reldir, PNTNUM *pRelatives, int iNumRelatives, BOOL checked, BOOL updatecounts, PNTNUM **ppPointsToLock, int *piNumPointsToLock);
EXTERN_C int        hsc_point_update_repl_relatives(PNTNUM point, PNTNUM *pRelatives, PNTRELTYP *pRelTypes, PNTRELDIR *pRelDirs, int iNumRelatives, PNTNUM **ppPointsToLock, int *piNumPointsToLock);
EXTERN_C int        hsc_point_add_containment_relation(PNTNUM child, PNTNUM parent);
EXTERN_C int        hsc_point_add_reference_relation(PNTNUM refitem, PNTNUM referer);
EXTERN_C int        hsc_point_add_relation(PNTNUM, PNTNUM, BOOL, BOOL);
EXTERN_C int        hsc_point_add_relations(PNTNUM, PNTRELDIR, int, PNTNUM*, BOOL, BOOL);
EXTERN_C int        hsc_point_add_relations_ex(PNTNUM, PNTRELDIR, int, PNTNUM*, DWORD);
EXTERN_C int        hsc_point_mod_parent(PNTNUM child, PNTNUM oldparent, PNTNUM newparent);

EXTERN_C int        hsc_point_check_proposed_relation(PNTNUM, PNTNUM, PNTNUM);
EXTERN_C int        hsc_point_check_proposed_relations(PNTNUM, PNTRELDIR, int, PNTNUM*);
EXTERN_C int        hsc_point_check_num_proposed_relations(PNTRELDIR reldir, int count);
EXTERN_C int        hsc_point_check_num_proposed_relations_ex(PNTNUM point, PNTRELDIR reldir, int iNumPropsedRelatives, PNTNUM *pProposedRelatives);
EXTERN_C int        hsc_point_check_existing_relations(PNTNUM point);
EXTERN_C int        hsc_point_check_num_existing_relations(PNTNUM point);
EXTERN_C int        hsc_check_cyclic_relations();
EXTERN_C int        hsc_point_check_cyclic_relations(PNTNUM point);
EXTERN_C int        hsc_point_check_links();
EXTERN_C int        hsc_point_check_parentlinks(PNTNUM point);
EXTERN_C int        hsc_point_check_childlinks(PNTNUM point);
EXTERN_C int        hsc_point_check_entityname(PNTNUM point);
EXTERN_C int        hsc_point_check_parameters(PNTNUM point);

EXTERN_C int        hsc_point_del_invalid_parents(PNTNUM point);
EXTERN_C int        hsc_point_del_invalid_children(PNTNUM point);
EXTERN_C int        hsc_point_del_containment_relation(PNTNUM child, PNTNUM parent, BOOL);
EXTERN_C int        hsc_point_del_reference_relation(PNTNUM refitem, PNTNUM referer, BOOL);
EXTERN_C int        hsc_point_del_relation(PNTNUM, PNTNUM, BOOL, BOOL);
EXTERN_C int        hsc_point_del_relations_ex(PNTNUM, PNTRELDIR, int, PNTNUM*, DWORD);
EXTERN_C int        hsc_point_del_relations(PNTNUM, PNTRELDIR, int, PNTNUM*, BOOL, BOOL);
EXTERN_C int        hsc_point_del_all_relations(PNTNUM, BOOL, BOOL);

EXTERN_C STApoint*  hsc_point_find_next(GINDX**,  PNTNUM*);

EXTERN_C int        hsc_point_get_parents(PNTNUM, int*, PNTNUM**);
EXTERN_C int        hsc_point_get_parent(PNTNUM, int, PNTNUM*);
EXTERN_C int        hsc_point_get_num_parents(PNTNUM, int*);
EXTERN_C int        hsc_point_get_ancestors(PNTNUM point, int *piNumAncestors, PNTNUM **ppAncestors);
EXTERN_C int        hsc_point_get_children(PNTNUM, int*, PNTNUM**);
EXTERN_C int        hsc_point_get_children_names_of_type(char* szPointName, PNTTYP childType, int iSortOrder, int *piNumChildren, char ***prgszChildren);
EXTERN_C int        hsc_point_get_child(PNTNUM, int, PNTNUM*);
EXTERN_C int        hsc_point_get_num_children(PNTNUM, int*);

EXTERN_C int        hsc_point_get_containment_parents(PNTNUM child, int *piNumParents, PNTNUM **ppParents);
EXTERN_C int        hsc_point_get_containment_parent(PNTNUM child, int offset, PNTNUM *pParent);
EXTERN_C int        hsc_point_get_num_containment_parents(PNTNUM child, int *piNumParents);
EXTERN_C int        hsc_point_get_containment_children(PNTNUM parent, int *piNumChildren, PNTNUM **ppChildren);
EXTERN_C int        hsc_point_get_containment_child(PNTNUM parent, int offset, PNTNUM *pChild);
EXTERN_C int        hsc_point_get_containment_child_byname(PNTNUM point, char *szChildName, PNTNUM *pChild);
EXTERN_C int        hsc_point_get_num_containment_children(PNTNUM parent, int *piNumChildren);
EXTERN_C int        hsc_point_get_containment_ancestors(PNTNUM point, int *piNumAncestors, PNTNUM **ppAncestors);
EXTERN_C int        hsc_point_get_containment_ancestor(PNTNUM point, int offset, PNTNUM *pAncestor);
EXTERN_C int        hsc_point_get_num_containment_ancestors(PNTNUM point, int *piNumAncestors);
EXTERN_C int        hsc_point_get_containment_descendents(PNTNUM point, int *piNumDescendents, PNTNUM **ppDescendents);
EXTERN_C int        hsc_point_get_containment_descendent(PNTNUM point, int offset, PNTNUM *pDescendent);
EXTERN_C int        hsc_point_get_num_containment_descendents(PNTNUM point, int *piNumDescendents);

EXTERN_C int        hsc_point_get_references(PNTNUM point, int *piNumRefItems, PNTNUM **ppRefItems);
EXTERN_C int        hsc_point_get_reference(PNTNUM point, int offset, PNTNUM *pRefItem);
EXTERN_C int        hsc_point_get_num_references(PNTNUM point, int *piNumRefItems);
EXTERN_C int        hsc_point_get_referers(PNTNUM point, int *piNumRefItems, PNTNUM **ppRefItems);
EXTERN_C int        hsc_point_get_referer(PNTNUM point, int offset, PNTNUM *pRefItem);
EXTERN_C int        hsc_point_get_num_referers(PNTNUM point, int *piNumRefItems);

EXTERN_C int        hsc_asset_get_parents(PNTNUM point, int *piNumParents, PNTNUM **ppParents);
EXTERN_C int        hsc_asset_get_parent(PNTNUM point, int offset, PNTNUM *pParent);
EXTERN_C int        hsc_asset_get_num_parents(PNTNUM point, int *piNumParents);
EXTERN_C int        hsc_asset_get_children(PNTNUM point, int *piNumChildren, PNTNUM **ppChildren);
EXTERN_C int        hsc_asset_get_child(PNTNUM point, int offset, PNTNUM *pChild);
EXTERN_C int        hsc_asset_get_num_children(PNTNUM point, int *piNumChildren);
EXTERN_C int        hsc_asset_get_ancestors(PNTNUM point, int *piNumAncestors, PNTNUM **ppAncestors);
EXTERN_C int        hsc_asset_get_ancestor(PNTNUM point, int offset, PNTNUM *pAncestor);
EXTERN_C int        hsc_asset_get_num_ancestors(PNTNUM point, int *piNumAncestors);
EXTERN_C int        hsc_asset_get_descendents(PNTNUM point, int *piNumDescendents, PNTNUM **ppDescendents);
EXTERN_C int        hsc_asset_get_descendent(PNTNUM point, int offset, PNTNUM *pDescendent);
EXTERN_C int        hsc_asset_get_num_descendents(PNTNUM point, int *piNumDescendents);

EXTERN_C int        hsc_point_get_relatives(PNTNUM point, PNTRELTYP reltyp, PNTRELDIR reldir, PNTNUM **ppRelatives, int *piNumRelatives);
EXTERN_C int        hsc_point_get_repl_relatives(PNTNUM point, PNTNUM **ppRelatives, PNTRELTYP **ppRelTypes, PNTRELDIR **ppRelDirs, int *piNumRelatives);
EXTERN_C int2       hsc_point_get_relation_type(PNTNUM child, PNTNUM parent);
EXTERN_C int2       hsc_point_get_relation_type_ex(STApoint *pChild, STApoint *pParent);
EXTERN_C int        hsc_point_get_primary_parent(PNTNUM child, PNTNUM *pParent);
EXTERN_C int        hsc_point_get_remote_descendents(PNTNUM point, int iConnection, int *piNumRemoteDescendents, PNTNUM **ppRemoteDescendents);
EXTERN_C int        hsc_point_get_descendents(PNTNUM point, int *piNumDescendents, PNTNUM **ppDescendents);
EXTERN_C int        hsc_point_get_areaenabled_descendents(PNTNUM point, int *piNumDescendents, PNTNUM **ppDescendents);
EXTERN_C int        hsc_point_get_areascoped_descendents(PNTNUM point, int *piNumDescendents, PNTNUM **ppDescendents);
EXTERN_C BOOL       hsc_point_relation_is_replicable(PNTNUM child, PNTNUM parent);
EXTERN_C BOOL       hsc_point_relation_is_replicable_ex(STApoint *pChild, STApoint *pParent);
EXTERN_C int        hsc_point_is_descendent(PNTNUM point1, PNTNUM point2, int depth, BOOL* pVal);
EXTERN_C int        hsc_point_is_ancestor(PNTNUM point1, PNTNUM point2, int depth, BOOL* pVal);
EXTERN_C BOOL       hsc_point_is_child(PNTNUM parent, PNTNUM child);
EXTERN_C BOOL       hsc_point_is_parent(PNTNUM child, PNTNUM parent);
EXTERN_C int        hsc_point_sort_relations(PNTNUM point);
EXTERN_C int        hsc_point_rebuild_children();
EXTERN_C PNTNUM     hsc_point_owner(PNTNUM point);
EXTERN_C PNTNUM     hsc_point_owner_ex(STApoint* pPoint);
EXTERN_C int        hsc_point_get_owned_points(PNTNUM owner, PNTNUM **ppOwnedPoints, int *piNumOwnedPoints);

EXTERN_C int        hsc_point_get_assoc_asset(PNTNUM point, PNTNUM *asset);
EXTERN_C int        hsc_point_get_assoc_asset_fullitemname(PNTNUM point, char *fullitemname, int namelen);
EXTERN_C int        hsc_point_get_assoc_asset_tagname(PNTNUM point, char *tagname, int namelen);
EXTERN_C int        hsc_point_set_assoc_asset(PNTNUM point, PNTNUM asset);
EXTERN_C int        hsc_point_set_assoc_asset_ex(PNTNUM point, STApoint *pPoint, PNTNUM asset, STApoint *pAsset);
EXTERN_C int        hsc_point_get_parent_asset(PNTNUM point, PNTNUM *parent);
EXTERN_C int        hsc_point_set_parent_asset(PNTNUM point, PNTNUM parent);
EXTERN_C int        hsc_point_set_area_enabled(PNTNUM point, BOOL areaenabled);
EXTERN_C int        hsc_point_set_area_enabled_ex(PNTNUM point, BOOL areaenabled, int area);
EXTERN_C int        hsc_point_create_area(PNTNUM point, int area);
EXTERN_C BOOL       hsc_point_is_area_enabled(PNTNUM point);
EXTERN_C BOOL       hsc_point_is_area_enabled_ex(STApoint *pPoint);
EXTERN_C int        hsc_clear_area(int iAreaNum);
EXTERN_C int        hsc_clear_areas(int2* areaNums, int aCount);
EXTERN_C int        hsc_clear_areas_link_parents(int2* areaNums, int aCount, PNTNUM* parentNums);
EXTERN_C BOOL       hsc_point_has_duplicates(PNTNUM point);
EXTERN_C BOOL       hsc_point_has_assigned_descendents(PNTNUM point, int2 crtnum);
EXTERN_C BOOL       hsc_point_is_unassigned_item(PNTNUM point);
EXTERN_C int        hsc_point_gettaginfo(PNTNUM point, struct tagfl *pTagRec);
EXTERN_C int        hsc_point_updatetag(PNTNUM point);
EXTERN_C int        hsc_tag_validatepoint(PNTNUM point);
EXTERN_C int        hsc_update_childpoint_areas(PNTNUM point, int2 area);
EXTERN_C BOOL       hsc_has_assoc_asset(PNTNUM point);
EXTERN_C BOOL       hsc_descendants_has_assoc_asset(PNTNUM point);

EXTERN_C int        hsc_create_model_point(uint2 model, int area);
EXTERN_C int        hsc_create_unassigned_items_point(int area);
EXTERN_C int        hsc_create_orphan_activities_point();
EXTERN_C int        hsc_create_collection_point(uint2 collection);
EXTERN_C int        hsc_update_rawitem_point(int gdarec, char *szNewAlias, char *szNewSrvAlias, BOOL bRenameClashes);
EXTERN_C int        hsc_update_cstn_localsrv_point(char *szName);
EXTERN_C int        hsc_update_server_point(int, char*,BOOL);
EXTERN_C int        hsc_update_sysinterface_point(int, char*);
EXTERN_C int        hsc_update_gda_point(int, char*,BOOL);
EXTERN_C PNTNUM     hsc_get_gda_point(int);
EXTERN_C int        hsc_check_clusterserver_pntnum();
EXTERN_C int        hsc_update_channel_point(int, char*);
EXTERN_C int        hsc_check_channel_point(int, char*);
EXTERN_C int        hsc_update_controller_point(int rtu, char* szRtuName);
EXTERN_C int        hsc_check_controller_point(int, char*, int);
EXTERN_C int        hsc_update_controllerwireless_point(int rtu, BOOL bDelete);
EXTERN_C int        hsc_update_controlleriorack_point(int rtu, int rackNumber, BOOL bDelete);
EXTERN_C int        hsc_update_meter_point(int conrec, char *szItemName, char *szTagName, BOOL bDelete);
EXTERN_C int        hsc_update_flexstation_point(int, char*);
EXTERN_C int        hsc_update_consolestation_point(int, char*);
EXTERN_C int        hsc_update_printer_point(int, char*);
EXTERN_C int        hsc_update_console_point(int, char*);
EXTERN_C int        hsc_update_cstn_client_point(int, int);
EXTERN_C int        hsc_update_cdaconstatus_point();
EXTERN_C int        hsc_update_nbcc_point(int, char*);
EXTERN_C int        hsc_rename_sysinterface_point(PNTNUM point);

EXTERN_C PNTNUM     hsc_get_areaenabled_point(int2);
EXTERN_C int        hsc_get_point_areaenabled_point_name_ex(PNTNUM point, char* name, int namelen, int flags);
EXTERN_C PNTNUM     hsc_get_channel_point(char *szName);
EXTERN_C PNTNUM     hsc_get_controller_point(char *szName);
EXTERN_C PNTNUM     hsc_get_localsrv_point();
EXTERN_C PNTNUM     hsc_get_localsys_point();
EXTERN_C PNTNUM     hsc_get_unassigned_items_point();
EXTERN_C PNTNUM     hsc_get_orphan_activities_point();
EXTERN_C PNTNUM     hsc_get_root_asset_point();
EXTERN_C int        hsc_point_move_to_unassigned_items(PNTNUM point);
EXTERN_C int        hsc_point_move_to_unassigned_items_ex(PNTNUM point, PNTNUM **ppPointsToLock, int *piNumPointsToLock);
EXTERN_C int        hsc_point_move_to_orphan_activities(PNTNUM point, PNTNUM **ppPointsToLock, int *piNumPointsToLock);
EXTERN_C PNTNUM     hsc_getpointnumber(int2, int2);
EXTERN_C int        hsc_getcorrespondingrecord(PNTNUM nPoint, int2* pFileNum, int4* pRecNum);
EXTERN_C int        hsc_getSYSPointRecord(STApoint* pPoint);
EXTERN_C BOOL       hsc_point_is_system_entity(PNTNUM point);
EXTERN_C BOOL       hsc_point_is_system_entity_ex(STApoint* pPoint);
EXTERN_C BOOL       hsc_point_is_network_entity(PNTNUM point);
EXTERN_C BOOL       hsc_point_is_network_entity_ex(STApoint* pPoint);
EXTERN_C BOOL       hsc_point_is_network_entity_by_types(PNTTYP pointtype, int2 subtype);
EXTERN_C int        hsc_ispoint_real(PNTNUM PointNumber);
EXTERN_C BOOL       hsc_ispoint_root(PNTNUM point);
EXTERN_C BOOL       hsc_ispoint_owner(PNTNUM point);
EXTERN_C BOOL       hsc_ispoint_localsrv(PNTNUM point);
EXTERN_C BOOL       hsc_ispoint_localsys(PNTNUM point);
EXTERN_C BOOL       hsc_ispoint_rawitem(PNTNUM point);
EXTERN_C BOOL       hsc_is_container (STApoint *pPoint);
EXTERN_C int        hsc_valid_algo_details(STApoint* pPoint,PRMNUM Param, uint2 algonum, int* precord);

EXTERN_C int        hsc_build_system_points(void);
EXTERN_C int        hsc_build_model_points(void);
EXTERN_C int        hsc_build_model_points_ex(int nAssetModelAreaNum, int nAlarmGroupModelAreaNum, int nSystemAlarmGroupModelAreaNum, int nSystemModelAreaNum, int nUnassignedItemsAreaNum);
EXTERN_C int        hsc_build_syscollection_points(void);
EXTERN_C int        hsc_build_server_points(void);

EXTERN_C int        hsc_check_point_parent(PNTNUM point);
EXTERN_C int        hsc_check_points_parent(void);
EXTERN_C int        hsc_check_area_table(void);
EXTERN_C int        hsc_check_emh(void);
EXTERN_C int        hsc_check_owners(void);
EXTERN_C int        hsc_check_and_correct_owner(PNTNUM point);
EXTERN_C BOOL       hsc_update_createtime_by_area(int AreaNum);
EXTERN_C int        hsc_entmodel_CheckInstall(void);

EXTERN_C int        hsc_migrate_system_area(void);
EXTERN_C int        hsc_migrate_createlocalgdaentry_skeleton(void);
EXTERN_C int        hsc_migrate_pre810_points(void);
EXTERN_C int        hsc_migrate_areas_to_assets(BOOL);
EXTERN_C int        hsc_migrate_area_to_asset(char*, int2);
#ifdef sm1200
EXTERN_C int        hsc_migrate_orgpoint_access();
EXTERN_C void       hsc_update_syspoints_i18n();
#endif
EXTERN_C int        hsc_update_syspoints_guid();

EXTERN_C int        hsc_security_set_permissions(int2 filenum, int2 recnum, int2 areanum, int2 permissions);
EXTERN_C int        hsc_security_set_permissions_ex(int2 area, int2 permission);
EXTERN_C int        hsc_security_set_permissions_byarray(int2* areas, int aCount, int2 permission);
EXTERN_C int        hsc_security_get_permissions(int2 filenum, int2 recnum, int2 areanum, int2 *permissions);
EXTERN_C int        hsc_security_copy_permissions(int2 srcarea, int2 destarea);
EXTERN_C int        hsc_security_copy_permissions_ex(int2 filenum, int2 recnum, int2 srcarea, int2 destarea);
EXTERN_C int        hsc_security_copy_subordinates(int2 filenum, int2 recnum, int2 areanum);
EXTERN_C int        hsc_security_assign_all(int2 filenum, int2 recnum, int2 permission);
EXTERN_C BOOL       hsc_security_permissions_match(int2 filenum, int2 recnum, int2 areanum1, int2 areanum2, BOOL bOnlyCheckAssignment);
EXTERN_C BOOL       hsc_security_descendent_permissions_match(int2 filenum, int2 recnum, PNTNUM point, BOOL bOnlyCheckAssignment);
EXTERN_C int        hsc_security_handle_change(int2 filenum, int2 recnum);
EXTERN_C BOOL       hsc_security_allow_change(GDASECURITY *pSecurity, int2 filenum, int2 recnum, int2 areanum, BOOL bPropagated);

EXTERN_C int2       hsc_DidSignatureSucceed(struct bigprm *bigprmblk);
EXTERN_C int        hsc_opersign_message(int2 nCrt, int4 nCookie, int4 nPublisherCookie, int2 nNumSigs, int2 nSig2Level, PNTNUM nPoint, char* szArea, char* szMessage, char* szMeaning1, char* szMeaning2);
EXTERN_C int        hsc_opersign_pointcontrol(int2 nCrt, PNTNUM nPoint,PRMNUM nParam,PARvalue pvNewValue,uint2 pvType);
EXTERN_C int        hsc_opersign_generic2(int2 nCrt, int2 nLRN,int4 nParam1,int4 nParam2,int4 nParam3,int4 nParam4,int2 nReasonSet,int2 cSignatures,int2 nPriCtrlLvl,int2 nSecSecLvl,int2 nArea,char* szSource,char* szDescription,char* szCondition,PARvalue pvNewValue,PARvalue pvOldValue,uint2 pvType,char* szPriMeaning,char* szSecMeaning);
EXTERN_C int        hsc_opersign_AssetEsigDisable(int2 nCrt, PNTNUM nPoint, int2 newVal, int2 fDescendants);
EXTERN_C int        hsc_OperSign_Send_Message(int2 nCrt, PNTNUM nPoint, int4 nMSG_COK,int4 nMSG_GEN_COK,int2 nReasonSet,char* szMessage,int2 cSignatures,int2* rgSecurityLevel,int2* rgControlLevel,char** rgszArea,char** rgszMeaning);
EXTERN_C int        hsc_OperSign_Send_PointControl(int2 nCrt, int2 nReasonSet, PNTNUM nPoint, PRMNUM nParam, PARvalue pvOldValue, PARvalue pvNewValue, uint2 pvType, int2 cSignatures, int2* rgSecurityLevel, int2* rgControlLevel, char** rgszArea, char** rgszMeaning);
EXTERN_C int        hsc_OperSign_Send_Generic(int2 nCrt,int2 lrn,int4 param1,int4 param2,int4 param3,int4 param4,char *szPoint, char *szParam, char *szDescription,PARvalue pvOldValue,PARvalue pvNewValue,uint2 pvType,int2 nReasonSet,int2 cSignatures,int2 * rgSecurityLevel,int2 * rgControlLevel,char ** rgszArea,char ** rgszMeaning);
EXTERN_C int        hsc_OperSign_Send(int2 nCrt, hscSignatureOperation hso);

EXTERN_C int        hsc_move_area_references(int2 iSrcArea, int2 iDstArea);
EXTERN_C int2       hsc_isparam_historisable(PNTNUM *pPoint, PRMNUM *pParam, int2 *piFile);

/* Activity Point Functions */
EXTERN_C BOOL       hsc_point_is_actmodel_item(PNTNUM point);
EXTERN_C BOOL       hsc_point_is_actmodel_item_ex(STApoint *pPoint);
EXTERN_C BOOL       hsc_point_is_activity_entity(PNTNUM point);
EXTERN_C BOOL       hsc_point_is_activity_entity_ex(STApoint* pPoint);
EXTERN_C int        hsc_point_activity_display_format(PNTNUM point, PRMNUM param, char* szBuffer, uint4 nBufSize);

/* EFM Meter Point Functions */
EXTERN_C BOOL       hsc_point_is_efm_meter(PNTNUM point);
EXTERN_C BOOL       hsc_point_is_efm_meter_ex(STApoint *pPoint);

/* Combo point functions */
EXTERN_C BOOL       hsc_point_is_combopoint(PNTNUM);
EXTERN_C BOOL       hsc_point_is_combopoint_ehb(PNTNUM point);
EXTERN_C BOOL       hsc_point_is_combopoint_ex(STApoint* pPoint);
EXTERN_C BOOL       hsc_point_is_combopoint_ehb_ex(STApoint* pPoint);
EXTERN_C BOOL       hsc_pointflags_combopoint_flags_equal(uint2 flags1, uint2 flags2);
EXTERN_C void       hsc_pointflags_copy_combopoint_flags(uint2 sourceFlags, uint2* pDestFlags);
EXTERN_C BOOL       hsc_pointflags_is_combopoint(uint2 pointFlags);
EXTERN_C BOOL       hsc_pointflags_is_combopoint_ehb(uint2 pointFlags);
EXTERN_C BOOL       hsc_pointflags_is_combopoint_ehpm(uint2 pointFlags);
EXTERN_C BOOL       hsc_pointflags_is_combopoint_cda_first(uint2 pointFlags);
EXTERN_C BOOL       hsc_pointflags_is_combopoint_methodscoped(uint2 pointFlags);

EXTERN_C void       hsc_param_clear_combopoint_flags(STApoint* pPoint);
EXTERN_C void       hsc_combopoint_param_copy_from_cda(PNTNUM point, PRMNUM param, uint2 paramFlags);
EXTERN_C void       hsc_combopoint_param_set_from_cda(PNTparam* pParam);
EXTERN_C void       hsc_combopoint_param_set_not_from_cda(PNTparam* pParam);
EXTERN_C BOOL       hsc_combopoint_param_is_from_cda(PNTparam* pParam);
EXTERN_C void       hsc_combopoint_param_set_getcon(PNTparam* pParam);
EXTERN_C void       hsc_combopoint_paramflags_set_getcon(uint2* pParamFlags);
EXTERN_C void       hsc_combopoint_param_clear_getcon(PNTparam* pParam);
EXTERN_C BOOL       hsc_combopoint_param_is_getcon(PNTparam* pParam);

/* --------------------------------------------------
 * Prototypes only accessible by C++ Code
 * --------------------------------------------------*/
#ifdef __cplusplus
#ifdef __include_cpp_points_h__
#include <map>
#include <list>

int hsc_find_tpspoint_by_unit_ex(std::map<int, int2> mapTPSUnitIndices, int iConnection, std::list<PNTNUM>& lstTPSPointNumbers);

#endif
#endif


/*
MACROS:
*/

#define IS_SYSTEM_ENTITY(remtype, subtype)          ((remtype == SYS) || (((remtype == CDA) || (remtype == PSA)) && (subtype != 0)))
#define IS_ROOT_ENTITY(remtype, subtype)            ((remtype == SYS) && (subtype == SYS_MODEL))
#define IS_OWNER_POINT(type, subtype)               ((type == SYS) && (subtype == SYS_SERVER))
#define IS_CONTAINER_EQUIPMENT(remtype, pntflags)   ((remtype == CON) && ((pntflags & PNTFLG_EQUIPMENT_MASK) != 0))

/*
END_DOC
*/

#endif	/* end of conditional include points_flag */

/************************************************************************/
/****     COPYRIGHT 2008 - 2017     HONEYWELL INTERNATIONAL SARL     ****/
/************************************************************************/
