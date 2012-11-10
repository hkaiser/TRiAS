
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Thu Jul 11 22:51:15 2002
 */
/* Compiler settings for D:\TRiASDev\CvrtGuid\CvrtGuid.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
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

#ifndef __CvrtGuid_h__
#define __CvrtGuid_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IConvertGuid_FWD_DEFINED__
#define __IConvertGuid_FWD_DEFINED__
typedef interface IConvertGuid IConvertGuid;
#endif 	/* __IConvertGuid_FWD_DEFINED__ */


#ifndef __ConvertGuid_FWD_DEFINED__
#define __ConvertGuid_FWD_DEFINED__

#ifdef __cplusplus
typedef class ConvertGuid ConvertGuid;
#else
typedef struct ConvertGuid ConvertGuid;
#endif /* __cplusplus */

#endif 	/* __ConvertGuid_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IConvertGuid_INTERFACE_DEFINED__
#define __IConvertGuid_INTERFACE_DEFINED__

/* interface IConvertGuid */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IConvertGuid;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9DA6B9BD-CF11-46BD-8C88-5460E1FE6A5E")
    IConvertGuid : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateGuid32String( 
            /* [retval][out] */ BSTR *GuidStr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GuidToGuid32String( 
            /* [in] */ BSTR Guid,
            /* [retval][out] */ BSTR *GuidStr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Guid32StringToGuid( 
            /* [in] */ BSTR GuidStr,
            /* [retval][out] */ BSTR *Guid) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IConvertGuidVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IConvertGuid * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IConvertGuid * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IConvertGuid * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IConvertGuid * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IConvertGuid * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IConvertGuid * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IConvertGuid * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateGuid32String )( 
            IConvertGuid * This,
            /* [retval][out] */ BSTR *GuidStr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GuidToGuid32String )( 
            IConvertGuid * This,
            /* [in] */ BSTR Guid,
            /* [retval][out] */ BSTR *GuidStr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Guid32StringToGuid )( 
            IConvertGuid * This,
            /* [in] */ BSTR GuidStr,
            /* [retval][out] */ BSTR *Guid);
        
        END_INTERFACE
    } IConvertGuidVtbl;

    interface IConvertGuid
    {
        CONST_VTBL struct IConvertGuidVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IConvertGuid_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IConvertGuid_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IConvertGuid_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IConvertGuid_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IConvertGuid_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IConvertGuid_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IConvertGuid_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IConvertGuid_CreateGuid32String(This,GuidStr)	\
    (This)->lpVtbl -> CreateGuid32String(This,GuidStr)

#define IConvertGuid_GuidToGuid32String(This,Guid,GuidStr)	\
    (This)->lpVtbl -> GuidToGuid32String(This,Guid,GuidStr)

#define IConvertGuid_Guid32StringToGuid(This,GuidStr,Guid)	\
    (This)->lpVtbl -> Guid32StringToGuid(This,GuidStr,Guid)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IConvertGuid_CreateGuid32String_Proxy( 
    IConvertGuid * This,
    /* [retval][out] */ BSTR *GuidStr);


void __RPC_STUB IConvertGuid_CreateGuid32String_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IConvertGuid_GuidToGuid32String_Proxy( 
    IConvertGuid * This,
    /* [in] */ BSTR Guid,
    /* [retval][out] */ BSTR *GuidStr);


void __RPC_STUB IConvertGuid_GuidToGuid32String_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IConvertGuid_Guid32StringToGuid_Proxy( 
    IConvertGuid * This,
    /* [in] */ BSTR GuidStr,
    /* [retval][out] */ BSTR *Guid);


void __RPC_STUB IConvertGuid_Guid32StringToGuid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IConvertGuid_INTERFACE_DEFINED__ */



#ifndef __ConvertGuid_LIBRARY_DEFINED__
#define __ConvertGuid_LIBRARY_DEFINED__

/* library ConvertGuid */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ConvertGuid;

EXTERN_C const CLSID CLSID_ConvertGuid;

#ifdef __cplusplus

class DECLSPEC_UUID("0237BF15-6F66-4C18-9D92-5C408C0492CE")
ConvertGuid;
#endif
#endif /* __ConvertGuid_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


