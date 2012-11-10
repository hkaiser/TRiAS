

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Thu Jan 16 12:35:34 2003
 */
/* Compiler settings for ConfigObjectProperty.Idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

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

#ifndef __ConfigObjectProperty_h__
#define __ConfigObjectProperty_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IConfigObjectProperty_FWD_DEFINED__
#define __IConfigObjectProperty_FWD_DEFINED__
typedef interface IConfigObjectProperty IConfigObjectProperty;
#endif 	/* __IConfigObjectProperty_FWD_DEFINED__ */


#ifndef __IConfigSequenceForObjectProperty_FWD_DEFINED__
#define __IConfigSequenceForObjectProperty_FWD_DEFINED__
typedef interface IConfigSequenceForObjectProperty IConfigSequenceForObjectProperty;
#endif 	/* __IConfigSequenceForObjectProperty_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_ConfigObjectProperty_0000 */
/* [local] */ 





extern RPC_IF_HANDLE __MIDL_itf_ConfigObjectProperty_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ConfigObjectProperty_0000_v0_0_s_ifspec;

#ifndef __IConfigObjectProperty_INTERFACE_DEFINED__
#define __IConfigObjectProperty_INTERFACE_DEFINED__

/* interface IConfigObjectProperty */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IConfigObjectProperty;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("101228D6-D0B0-41D3-8F95-370E888F0446")
    IConfigObjectProperty : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConfigObjectProperty( 
            HWND hWnd) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsConfigured( 
            /* [retval][out] */ VARIANT_BOOL *ConfigState) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IConfigObjectPropertyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IConfigObjectProperty * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IConfigObjectProperty * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IConfigObjectProperty * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigObjectProperty )( 
            IConfigObjectProperty * This,
            HWND hWnd);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsConfigured )( 
            IConfigObjectProperty * This,
            /* [retval][out] */ VARIANT_BOOL *ConfigState);
        
        END_INTERFACE
    } IConfigObjectPropertyVtbl;

    interface IConfigObjectProperty
    {
        CONST_VTBL struct IConfigObjectPropertyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IConfigObjectProperty_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IConfigObjectProperty_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IConfigObjectProperty_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IConfigObjectProperty_ConfigObjectProperty(This,hWnd)	\
    (This)->lpVtbl -> ConfigObjectProperty(This,hWnd)

#define IConfigObjectProperty_get_IsConfigured(This,ConfigState)	\
    (This)->lpVtbl -> get_IsConfigured(This,ConfigState)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IConfigObjectProperty_ConfigObjectProperty_Proxy( 
    IConfigObjectProperty * This,
    HWND hWnd);


void __RPC_STUB IConfigObjectProperty_ConfigObjectProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IConfigObjectProperty_get_IsConfigured_Proxy( 
    IConfigObjectProperty * This,
    /* [retval][out] */ VARIANT_BOOL *ConfigState);


void __RPC_STUB IConfigObjectProperty_get_IsConfigured_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IConfigObjectProperty_INTERFACE_DEFINED__ */


#ifndef __IConfigSequenceForObjectProperty_INTERFACE_DEFINED__
#define __IConfigSequenceForObjectProperty_INTERFACE_DEFINED__

/* interface IConfigSequenceForObjectProperty */
/* [unique][helpstring][uuid][object] */ 

#if !defined(_CALCLSID_DATA)
#define _CALCLSID_DATA
typedef /* [restricted][hidden] */ struct tagCALPCLSID
    {
    ULONG cElems;
    const CLSID **ppElems;
    const IUnknown **ppActions;
    const VARIANT **ppvData;
    const BSTR *ppMkData;
    const BSTR *ppHeaderTitle;
    const BSTR *ppHeaderSubTitle;
    } 	CALPCLSID;

#endif // !defined(_CALCLSID_DATA)

EXTERN_C const IID IID_IConfigSequenceForObjectProperty;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F7D428CF-8D5A-4B93-A129-F1D7C1EDE597")
    IConfigSequenceForObjectProperty : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddAction( 
            IUnknown *pIAct) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddActionsByCLSID( 
            CALPCLSID *pcsClsId) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PrepareActions( 
            HWND hParent,
            IDataObject *pIData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IConfigSequenceForObjectPropertyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IConfigSequenceForObjectProperty * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IConfigSequenceForObjectProperty * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IConfigSequenceForObjectProperty * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddAction )( 
            IConfigSequenceForObjectProperty * This,
            IUnknown *pIAct);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddActionsByCLSID )( 
            IConfigSequenceForObjectProperty * This,
            CALPCLSID *pcsClsId);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PrepareActions )( 
            IConfigSequenceForObjectProperty * This,
            HWND hParent,
            IDataObject *pIData);
        
        END_INTERFACE
    } IConfigSequenceForObjectPropertyVtbl;

    interface IConfigSequenceForObjectProperty
    {
        CONST_VTBL struct IConfigSequenceForObjectPropertyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IConfigSequenceForObjectProperty_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IConfigSequenceForObjectProperty_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IConfigSequenceForObjectProperty_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IConfigSequenceForObjectProperty_AddAction(This,pIAct)	\
    (This)->lpVtbl -> AddAction(This,pIAct)

#define IConfigSequenceForObjectProperty_AddActionsByCLSID(This,pcsClsId)	\
    (This)->lpVtbl -> AddActionsByCLSID(This,pcsClsId)

#define IConfigSequenceForObjectProperty_PrepareActions(This,hParent,pIData)	\
    (This)->lpVtbl -> PrepareActions(This,hParent,pIData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IConfigSequenceForObjectProperty_AddAction_Proxy( 
    IConfigSequenceForObjectProperty * This,
    IUnknown *pIAct);


void __RPC_STUB IConfigSequenceForObjectProperty_AddAction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IConfigSequenceForObjectProperty_AddActionsByCLSID_Proxy( 
    IConfigSequenceForObjectProperty * This,
    CALPCLSID *pcsClsId);


void __RPC_STUB IConfigSequenceForObjectProperty_AddActionsByCLSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IConfigSequenceForObjectProperty_PrepareActions_Proxy( 
    IConfigSequenceForObjectProperty * This,
    HWND hParent,
    IDataObject *pIData);


void __RPC_STUB IConfigSequenceForObjectProperty_PrepareActions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IConfigSequenceForObjectProperty_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  HWND_UserSize(     unsigned long *, unsigned long            , HWND * ); 
unsigned char * __RPC_USER  HWND_UserMarshal(  unsigned long *, unsigned char *, HWND * ); 
unsigned char * __RPC_USER  HWND_UserUnmarshal(unsigned long *, unsigned char *, HWND * ); 
void                      __RPC_USER  HWND_UserFree(     unsigned long *, HWND * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


