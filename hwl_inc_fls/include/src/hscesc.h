

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Mon Jun 05 17:34:46 2017
 */
/* Compiler settings for C:\Users\H109393\AppData\Local\Temp\2\hscesc.idl:
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

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __hscesc_h__
#define __hscesc_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IhscElectronicSignatureDialogs_FWD_DEFINED__
#define __IhscElectronicSignatureDialogs_FWD_DEFINED__
typedef interface IhscElectronicSignatureDialogs IhscElectronicSignatureDialogs;

#endif 	/* __IhscElectronicSignatureDialogs_FWD_DEFINED__ */


#ifndef __hscElectronicSignatureDialogs_FWD_DEFINED__
#define __hscElectronicSignatureDialogs_FWD_DEFINED__

#ifdef __cplusplus
typedef class hscElectronicSignatureDialogs hscElectronicSignatureDialogs;
#else
typedef struct hscElectronicSignatureDialogs hscElectronicSignatureDialogs;
#endif /* __cplusplus */

#endif 	/* __hscElectronicSignatureDialogs_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_hscesc_0000_0000 */
/* [local] */ 

typedef /* [public] */ 
enum __MIDL___MIDL_itf_hscesc_0000_0000_0001
    {
        SIGNSTATE_NONE	= 0,
        SIGNSTATE_SUCCESS	= 1,
        SIGNSTATE_FAILURE	= 2,
        SIGNSTATE_TIMEOUT	= 3,
        SIGNSTATE_TOOMANY	= 4
    } 	SIGNATURESTATE;

typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_hscesc_0000_0000_0002
    {
        EST_MESSAGE_CONFIRMATION	= 1,
        EST_POINT_CONTROL	= ( EST_MESSAGE_CONFIRMATION + 1 ) ,
        EST_GENERIC	= ( EST_POINT_CONTROL + 1 ) ,
        EST_ACTIVITY_CREATION	= ( EST_GENERIC + 1 ) ,
        EST_POINT_CONTROL_LIST	= ( EST_ACTIVITY_CREATION + 1 ) 
    } 	ESIG_TYPE;

typedef struct _hscSignature
    {
    long nVersion;
    long nSecurityLevel;
    long nControlLevel;
    /* [string] */ BSTR bstrArea;
    /* [string] */ BSTR bstrMeaning;
    /* [string] */ BSTR bstrUserID;
    /* [string] */ BSTR bstrComment;
    long fStatus;
    long nDate;
    float nTime;
    long nRetries;
    } 	hscSignature;

typedef struct _hscSignatureOperation
    {
    long nVersion;
    long nLrn;
    long nParam1;
    long nParam2;
    long nParam3;
    long nParam4;
    long nReasonSet;
    long cSignatures;
    /* [size_is] */ hscSignature *rgSignatures;
    ESIG_TYPE nSignatureType;
    /* [string] */ BSTR bstrMessageText;
    long nMSGIDX;
    long nMSG_COK;
    long nMSG_GEN_COK;
    /* [string] */ BSTR bstrPointName;
    /* [string] */ BSTR bstrPointDescription;
    /* [string] */ SAFEARRAY * psaParameterNames;
    SAFEARRAY * psaOldValues;
    SAFEARRAY * psaNewValues;
    /* [string] */ BSTR bstrActivityEntity;
    /* [string] */ BSTR bstrBatchId;
    /* [string] */ BSTR bstrPublicName;
    long fSuccess;
    /* [string] */ BSTR bstrReason;
    long nReasonNumber;
    } 	hscSignatureOperation;

#define	ESIG_MAXSIGNATURES	( 4 )



extern RPC_IF_HANDLE __MIDL_itf_hscesc_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_hscesc_0000_0000_v0_0_s_ifspec;

#ifndef __IhscElectronicSignatureDialogs_INTERFACE_DEFINED__
#define __IhscElectronicSignatureDialogs_INTERFACE_DEFINED__

/* interface IhscElectronicSignatureDialogs */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IhscElectronicSignatureDialogs;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("927BE7FC-79C6-4CEE-AAAF-462FF2843676")
    IhscElectronicSignatureDialogs : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SignatureDialog( 
            /* [in] */ LONG hWnd,
            /* [string][in] */ BSTR szServer,
            /* [string][in] */ BSTR szLegalText,
            /* [in] */ VARIANT vtReasonSet,
            /* [in] */ BOOL fRaiseEvents,
            /* [in] */ BOOL fHideUsername,
            /* [in] */ LONG nTimeoutSeconds,
            /* [in] */ IUnknown *pUnknown,
            /* [in] */ LONG cSignatures,
            /* [in] */ SAFEARRAY * saszMeaning,
            /* [in] */ SAFEARRAY * sanControlLevel,
            /* [in] */ SAFEARRAY * sanSecurityLevel,
            /* [in] */ SAFEARRAY * saszArea,
            /* [in] */ SAFEARRAY * sanRetries,
            /* [in] */ ESIG_TYPE estType,
            /* [string][in] */ BSTR szMessage,
            /* [string][in] */ BSTR szPoint,
            /* [string][in] */ BSTR szPointDescription,
            /* [string][in] */ BSTR szParameter,
            /* [string][in] */ BSTR szCurValue,
            /* [string][in] */ BSTR szNewValue,
            /* [string][out] */ BSTR *szReason,
            /* [out] */ long *nReason,
            /* [out] */ SAFEARRAY * *psaszUserIDs,
            /* [out] */ SAFEARRAY * *psaszComments,
            /* [out] */ SAFEARRAY * *psafStatus,
            /* [out] */ SAFEARRAY * *psanDate,
            /* [out] */ SAFEARRAY * *psanTime,
            /* [retval][out] */ long *fSuccess) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SignatureDialog_Buffer( 
            /* [in] */ DWORD hWnd,
            /* [in] */ BSTR bstrServer,
            /* [in] */ BSTR chInBuf,
            /* [out] */ BSTR *pchOutBuf) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SignatureDialog_Buffer_Byte( 
            /* [in] */ DWORD hWnd,
            /* [in] */ BSTR bstrServer,
            /* [in] */ SAFEARRAY * saBuffer,
            /* [out] */ SAFEARRAY * *psaOutBuffer) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IhscElectronicSignatureDialogsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IhscElectronicSignatureDialogs * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IhscElectronicSignatureDialogs * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IhscElectronicSignatureDialogs * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IhscElectronicSignatureDialogs * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IhscElectronicSignatureDialogs * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IhscElectronicSignatureDialogs * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IhscElectronicSignatureDialogs * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SignatureDialog )( 
            IhscElectronicSignatureDialogs * This,
            /* [in] */ LONG hWnd,
            /* [string][in] */ BSTR szServer,
            /* [string][in] */ BSTR szLegalText,
            /* [in] */ VARIANT vtReasonSet,
            /* [in] */ BOOL fRaiseEvents,
            /* [in] */ BOOL fHideUsername,
            /* [in] */ LONG nTimeoutSeconds,
            /* [in] */ IUnknown *pUnknown,
            /* [in] */ LONG cSignatures,
            /* [in] */ SAFEARRAY * saszMeaning,
            /* [in] */ SAFEARRAY * sanControlLevel,
            /* [in] */ SAFEARRAY * sanSecurityLevel,
            /* [in] */ SAFEARRAY * saszArea,
            /* [in] */ SAFEARRAY * sanRetries,
            /* [in] */ ESIG_TYPE estType,
            /* [string][in] */ BSTR szMessage,
            /* [string][in] */ BSTR szPoint,
            /* [string][in] */ BSTR szPointDescription,
            /* [string][in] */ BSTR szParameter,
            /* [string][in] */ BSTR szCurValue,
            /* [string][in] */ BSTR szNewValue,
            /* [string][out] */ BSTR *szReason,
            /* [out] */ long *nReason,
            /* [out] */ SAFEARRAY * *psaszUserIDs,
            /* [out] */ SAFEARRAY * *psaszComments,
            /* [out] */ SAFEARRAY * *psafStatus,
            /* [out] */ SAFEARRAY * *psanDate,
            /* [out] */ SAFEARRAY * *psanTime,
            /* [retval][out] */ long *fSuccess);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SignatureDialog_Buffer )( 
            IhscElectronicSignatureDialogs * This,
            /* [in] */ DWORD hWnd,
            /* [in] */ BSTR bstrServer,
            /* [in] */ BSTR chInBuf,
            /* [out] */ BSTR *pchOutBuf);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SignatureDialog_Buffer_Byte )( 
            IhscElectronicSignatureDialogs * This,
            /* [in] */ DWORD hWnd,
            /* [in] */ BSTR bstrServer,
            /* [in] */ SAFEARRAY * saBuffer,
            /* [out] */ SAFEARRAY * *psaOutBuffer);
        
        END_INTERFACE
    } IhscElectronicSignatureDialogsVtbl;

    interface IhscElectronicSignatureDialogs
    {
        CONST_VTBL struct IhscElectronicSignatureDialogsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IhscElectronicSignatureDialogs_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IhscElectronicSignatureDialogs_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IhscElectronicSignatureDialogs_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IhscElectronicSignatureDialogs_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IhscElectronicSignatureDialogs_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IhscElectronicSignatureDialogs_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IhscElectronicSignatureDialogs_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IhscElectronicSignatureDialogs_SignatureDialog(This,hWnd,szServer,szLegalText,vtReasonSet,fRaiseEvents,fHideUsername,nTimeoutSeconds,pUnknown,cSignatures,saszMeaning,sanControlLevel,sanSecurityLevel,saszArea,sanRetries,estType,szMessage,szPoint,szPointDescription,szParameter,szCurValue,szNewValue,szReason,nReason,psaszUserIDs,psaszComments,psafStatus,psanDate,psanTime,fSuccess)	\
    ( (This)->lpVtbl -> SignatureDialog(This,hWnd,szServer,szLegalText,vtReasonSet,fRaiseEvents,fHideUsername,nTimeoutSeconds,pUnknown,cSignatures,saszMeaning,sanControlLevel,sanSecurityLevel,saszArea,sanRetries,estType,szMessage,szPoint,szPointDescription,szParameter,szCurValue,szNewValue,szReason,nReason,psaszUserIDs,psaszComments,psafStatus,psanDate,psanTime,fSuccess) ) 

#define IhscElectronicSignatureDialogs_SignatureDialog_Buffer(This,hWnd,bstrServer,chInBuf,pchOutBuf)	\
    ( (This)->lpVtbl -> SignatureDialog_Buffer(This,hWnd,bstrServer,chInBuf,pchOutBuf) ) 

#define IhscElectronicSignatureDialogs_SignatureDialog_Buffer_Byte(This,hWnd,bstrServer,saBuffer,psaOutBuffer)	\
    ( (This)->lpVtbl -> SignatureDialog_Buffer_Byte(This,hWnd,bstrServer,saBuffer,psaOutBuffer) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IhscElectronicSignatureDialogs_INTERFACE_DEFINED__ */



#ifndef __HSCESCLib_LIBRARY_DEFINED__
#define __HSCESCLib_LIBRARY_DEFINED__

/* library HSCESCLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_HSCESCLib;

EXTERN_C const CLSID CLSID_hscElectronicSignatureDialogs;

#ifdef __cplusplus

class DECLSPEC_UUID("36B7808F-830B-4837-9325-52F77B943A49")
hscElectronicSignatureDialogs;
#endif
#endif /* __HSCESCLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


