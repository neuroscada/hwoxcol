/************************************************************************/
/*****     COPYRIGHT 2008 - 2016    HONEYWELL INTERNATIONAL SARL     ****/
/************************************************************************/

/* Conditionally print out a trace of header file activity */
#ifdef _HEADER_FILE_TRACE_FLAG
#pragma message("Entering Header file: netapi_user.h")
#endif

/* Check to see if we've finished processing this header file before */
#ifndef NETAPI_USER_ENDFLAG

/* Check to see if we've partially processed this header file already */
#ifdef NETAPI_USER_STARTFLAG
#pragma message("ERROR: Partially processed: netapi_user.h")
#else
#define NETAPI_USER_STARTFLAG

/*
@(#)netapi_user.h	main.SVR_MASTERPROJ_Integration.R0930_Int.1
BEGIN_DOC
---------------------------------------------------------------------------
NETAPI_USER.H - Contains all macros and function prototypes to be exposed
                to end users.
---------------------------------------------------------------------------
SUMMARY:

DESCRIPTION:

    -----------------------------------------------------------------------
    NOTES - 
    -----------------------------------------------------------------------

DEFINITIONS:

STRUCTURE:

END_DOC
*/

/***********************************************
** *** INCLUDE FILES                      *** **
***********************************************/
#include "src/netapi_types.h"
#include "src/deprecate.h"

/***********************************************
** *** Raw defines                        *** **
***********************************************/

#define __loadds
#define NAPICALL __loadds CALLBACK

/************************************
** *** Miscellaneous Functions *** **
************************************/
EXTERN_C int NAPICALL hsc_cnads_startup(void);
EXTERN_C int NAPICALL hsc_cnads_cleanup(void);
EXTERN_C int NAPICALL hsc_DATE_to_hsctime(DATE date, HSCTIME* pTime);
EXTERN_C int NAPICALL hsc_hsctime_to_DATE(HSCTIME time, DATE* pDate);
EXTERN_C void NAPICALL hsc_napierrstr(UINT err, char *texterr);
EXTERN_C int NAPICALL hsc_bad_value(float nValue);

/******************************
** *** History Functions *** **
******************************/
EXTERN_C int NAPICALL rgethst_date                           (char* szHostname, int num_gethsts, rgethst_date_data* gethst_date_data);
EXTERN_C int NAPICALL rgethst_ofst                           (char* szHostname, int num_gethsts, rgethst_ofst_data* gethst_ofst_data);
EXTERN_C int NAPICALL rhsc_param_hist_date_bynames           (char *szHostName, int chstbd, HIST_BYNAME_DATA* rghstbd);
EXTERN_C int NAPICALL rhsc_param_hist_offset_bynames         (char* szHostName, int chstbd, HIST_BYNAME_DATA* rghstbd);
EXTERN_C NAPI_DEPRECATED int NAPICALL rhsc_param_hist_dates  (char* szHostname, int num_gethsts, rgethstpar_date_data* gethstpar_date_data);
EXTERN_C NAPI_DEPRECATED int NAPICALL rhsc_param_hist_offsets(char* szHostname, int num_gethsts, rgethstpar_ofst_data* gethstpar_ofst_data);
EXTERN_C NAPI_DEPRECATED int NAPICALL rgethstpar_date        (char* szHostname, int num_gethsts, rgethstpar_date_data* gethstpar_date_data);
EXTERN_C NAPI_DEPRECATED int NAPICALL rgethstpar_ofst        (char* szHostname, int num_gethsts, rgethstpar_ofst_data* gethstpar_offset_data);
EXTERN_C int NAPICALL rhsc_param_hist_dates_vb_ansi          (char* szHostname, int cRequests, SAFEARRAY** ppsa);
EXTERN_C int NAPICALL rhsc_param_hist_offsets_vb_ansi        (char* szHostname, int cRequests, SAFEARRAY** ppsa);
EXTERN_C int NAPICALL rhsc_param_hist_date_bynames_vb_ansi   (char* szHostname, int cRequests, SAFEARRAY** ppsa);
EXTERN_C int NAPICALL rhsc_param_hist_offset_bynames_vb_ansi (char* szHostname, int cRequests, SAFEARRAY** ppsa);

EXTERN_C int NAPICALL rhsc_param_hist_dates_2                (char* szHostname, int num_gethsts, rgethstpar_date_data_2* gethstpar_date_data2);
EXTERN_C int NAPICALL rhsc_param_hist_offsets_2              (char* szHostname, int num_gethsts, rgethstpar_ofst_data_2* gethstpar_ofst_data2);

/************************************************************
** *** Point, Parameter Functions                      *** **
************************************************************/
EXTERN_C NAPI_DEPRECATED int NAPICALL rgetpnt           (char* szHostname, int num_points, struct rgetpnt_data_str* getpnt_data);
EXTERN_C NAPI_DEPRECATED int NAPICALL rhsc_point_numbers(char* szHostname, int cpntnd, POINT_NUMBER_DATA* rgpntnd);
EXTERN_C NAPI_DEPRECATED int NAPICALL rhsc_param_numbers(char* szHostname, int cprmnd, PARAM_NUMBER_DATA* rgprmnd);
EXTERN_C short NAPICALL rgetpnt_vb_ansi         (char* szHostname, short cRequests, SAFEARRAY** ppsa);
EXTERN_C int NAPICALL rhsc_point_numbers_vb_ansi(char* szHostname, int cRequests, SAFEARRAY** ppsa);
EXTERN_C int NAPICALL rhsc_param_numbers_vb_ansi(char* szHostname, int cRequests, SAFEARRAY** ppsa);

EXTERN_C int NAPICALL rhsc_point_numbers_2  (char* szHostname, int cpntnd, POINT_NUMBER_DATA_2* rgpntnd);
EXTERN_C int NAPICALL rhsc_param_numbers_2  (char* szHostname, int cprmnd, PARAM_NUMBER_DATA_2* rgprmnd2);



/**************************************************
** *** Get and Put Parameter Value Functions *** **
**************************************************/
EXTERN_C int NAPICALL rhsc_param_value_puts_sec        (char* szHostname, int cprmvd, PARAM_VALUE_DATA* rgprmvd, unsigned short nStn);
EXTERN_C int NAPICALL rhsc_param_value_bynames         (char* szHostname, int nPeriod, int cprmbd, PARAM_BYNAME_DATA* rgprmbd);
EXTERN_C int NAPICALL rhsc_param_value_put_bynames     (char* szHostname, int cprmbd, PARAM_BYNAME_DATA* rgprmbd);
EXTERN_C int NAPICALL rhsc_param_value_put_sec_bynames (char* szHostname, int cprmbd, PARAM_BYNAME_DATA* rgprmbd, unsigned short nStn);
EXTERN_C NAPI_DEPRECATED int NAPICALL rgetval_ascii    (char* szHostname, int num_points, struct rgetval_ascii_data_str* getval_ascii_data);
EXTERN_C NAPI_DEPRECATED int NAPICALL rgetval_hist     (char* szHostname, int num_points, struct rgetval_hist_data_str* getval_hist_data);
EXTERN_C NAPI_DEPRECATED int NAPICALL rgetval_numb     (char* szHostname, int num_points, struct rgetval_numb_data_str* getval_numb_data);
EXTERN_C NAPI_DEPRECATED int NAPICALL rputval_numb     (char* szHostname, int num_points, rputval_numb_data* putval_numb_data);
EXTERN_C NAPI_DEPRECATED int NAPICALL rputval_ascii    (char* szHostname, int num_points, rputval_ascii_data* putval_ascii_data);
EXTERN_C NAPI_DEPRECATED int NAPICALL rputval_hist     (char* szHostname, int num_points, rputval_hist_data* putval_hist_data);
EXTERN_C NAPI_DEPRECATED int NAPICALL rhsc_param_values(char *szHostname, int nPeriod, int cprmvd, PARAM_VALUE_DATA* rgprmvd);
EXTERN_C NAPI_DEPRECATED int NAPICALL rhsc_param_value_puts(char* szHostname, int cprmvd, PARAM_VALUE_DATA* rgprmvd);
EXTERN_C short NAPICALL rgetval_ascii_vb_ansi             (char* szHostname, short cRequests, SAFEARRAY** ppsa);
EXTERN_C short NAPICALL rputval_ascii_vb_ansi             (char* szHostname, short cRequests, SAFEARRAY** ppsa);
EXTERN_C int NAPICALL rhsc_param_value_bynames_vb_ansi    (char* szHostname, int nPeriod, int cRequests, SAFEARRAY** ppsa);
EXTERN_C int NAPICALL rhsc_param_values_vb_ansi           (char* szHostname, int nPeriod, int cRequests, SAFEARRAY** ppsa);
EXTERN_C int NAPICALL rhsc_param_value_puts_vb_ansi       (char* szHostname, int cRequests, SAFEARRAY** ppsa);
EXTERN_C int NAPICALL rhsc_param_value_puts_sec_vb_ansi   (char *szHostname, int cRequests, SAFEARRAY** ppsa, unsigned short nStn);
EXTERN_C int NAPICALL rhsc_param_value_put_bynames_vb_ansi(char* szHostname, int cRequests, SAFEARRAY** ppsa);
EXTERN_C int NAPICALL rhsc_param_value_put_sec_bynames_vb_ansi(char *szHostname, int cRequests, SAFEARRAY** ppsa, unsigned short nStn);

EXTERN_C int NAPICALL rhsc_param_values_2              (char* szHostname, int nPeriod, int cprmvd, PARAM_VALUE_DATA_2* rgprmvd2);
EXTERN_C int NAPICALL rhsc_param_value_puts_2          (char* szHostname, int cprmvd, PARAM_VALUE_DATA_2* rgprmvd2);
EXTERN_C int NAPICALL rhsc_param_value_puts_sec_2      (char* szHostname, int cprmvd, PARAM_VALUE_DATA_2* rgprmvd, unsigned short nStn);


/*************************************************
** *** Get and Put User File Data Functions *** **
*************************************************/
EXTERN_C int NAPICALL rgetdat              (char* szHostname, int num_fields, rgetdat_data* getdat_data);
EXTERN_C int NAPICALL rputdat              (char* szHostname, int num_fields, rgetdat_data* putdat_data);
EXTERN_C short NAPICALL rgetdat_str_vb_ansi(char* szHostname, short cRequests, SAFEARRAY** ppsa);
EXTERN_C short NAPICALL rputdat_str_vb_ansi(char* szHostname, short cRequests, SAFEARRAY** ppsa);

/****************************************************************
** *** Notification, Alarm, Event Functions                *** **
****************************************************************/
EXTERN_C int NAPICALL rhsc_notifications        (char* szHostname, int cnotd, NOTIFICATION_DATA* rgnotd);
EXTERN_C int NAPICALL rhsc_notifications_vb_ansi(char* szHostname, int cRequests, SAFEARRAY** ppsa);

/****************************************************************
** *** Task Functions                                      *** **
****************************************************************/
EXTERN_C int NAPICALL rrqstsk(char* szHostname, int num_lrns, rrqstsk_data* rqstsk_data);
EXTERN_C int NAPICALL rrqtskb(char* szHostname, int num_lrns, rrqtskb_data* rqstsk_data);

/****************************************************************
** *** Authentication/Authorisation Functions              *** **
****************************************************************/
EXTERN_C int NAPICALL rlogin(char* szHostname, wchar_t *wszUsername, wchar_t *wszDomain, wchar_t *wszPassword);
EXTERN_C int NAPICALL rlogoff(char* szHostname);

#define NETAPI_USER_ENDFLAG
#endif               /* end of if not *_startflag */
#endif               /* end of if not *_endflag */

/* Conditionally print out a trace of header file activity */
#ifdef _HEADER_FILE_TRACE_FLAG
#pragma message("Leaving Header file: netapi_user.h")
#endif

/************************************************************************/
/*****     COPYRIGHT 2008 - 2016    HONEYWELL INTERNATIONAL SARL     ****/
/************************************************************************/
