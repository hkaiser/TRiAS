/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Sep 10 16:43:09 2003
 */
/* Compiler settings for E:\mm\DShowFlt\Callback\ILMVCallback.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __ILMVCallback_h__
#define __ILMVCallback_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ILMVUserCallback1_FWD_DEFINED__
#define __ILMVUserCallback1_FWD_DEFINED__
typedef interface ILMVUserCallback1 ILMVUserCallback1;
#endif 	/* __ILMVUserCallback1_FWD_DEFINED__ */


#ifndef __ILMVUserCallback_FWD_DEFINED__
#define __ILMVUserCallback_FWD_DEFINED__
typedef interface ILMVUserCallback ILMVUserCallback;
#endif 	/* __ILMVUserCallback_FWD_DEFINED__ */


#ifndef __ILMVCallback1_FWD_DEFINED__
#define __ILMVCallback1_FWD_DEFINED__
typedef interface ILMVCallback1 ILMVCallback1;
#endif 	/* __ILMVCallback1_FWD_DEFINED__ */


#ifndef __ILMVCallback_FWD_DEFINED__
#define __ILMVCallback_FWD_DEFINED__
typedef interface ILMVCallback ILMVCallback;
#endif 	/* __ILMVCallback_FWD_DEFINED__ */


#ifndef __LMVCallback_FWD_DEFINED__
#define __LMVCallback_FWD_DEFINED__

#ifdef __cplusplus
typedef class LMVCallback LMVCallback;
#else
typedef struct LMVCallback LMVCallback;
#endif /* __cplusplus */

#endif 	/* __LMVCallback_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __LMVCallbackLib_LIBRARY_DEFINED__
#define __LMVCallbackLib_LIBRARY_DEFINED__

/* library LMVCallbackLib */
/* [helpstring][version][uuid] */ 

#ifndef __ILMVCALLBACK_H__
#define __ILMVCALLBACK_H__
static const GUID CLSID_CallbackFilter             = {0xe2b7dbca, 0x38c5, 0x11d5, {0x91, 0xf6, 0x00, 0x10, 0x4b, 0xdb, 0x8f, 0xf9}};
static const GUID CLSID_CallbackFilterPropertyPage = {0xe2b7dbcb, 0x38c5, 0x11d5, {0x91, 0xf6, 0x00, 0x10, 0x4b, 0xdb, 0x8f, 0xf9}};
static const GUID CLSID_LMVAboutCallback1          = {0xe2b7dbce, 0x38c5, 0x11d5, {0x91, 0xf6, 0x00, 0x10, 0x4b, 0xdb, 0x8f, 0xf9}};
static const GUID LIBID_LMVCallbackLib             = {0xe2b7dbcf, 0x38c5, 0x11d5, {0x91, 0xf6, 0x00, 0x10, 0x4b, 0xdb, 0x8f, 0xf9}};
static const GUID IID_ILMVCallback1                = {0xe2b7dbcc, 0x38c5, 0x11d5, {0x91, 0xf6, 0x00, 0x10, 0x4b, 0xdb, 0x8f, 0xf9}};
static const GUID IID_ILMVUserCallback1            = {0xe2b7dbcd, 0x38c5, 0x11d5, {0x91, 0xf6, 0x00, 0x10, 0x4b, 0xdb, 0x8f, 0xf9}};
static const GUID IID_ILMVCallback                 = {0xe2b7dc51, 0x38c5, 0x11d5, {0x91, 0xf6, 0x00, 0x10, 0x4b, 0xdb, 0x8f, 0xf9}};
static const GUID IID_ILMVUserCallback             = {0xe2b7dc50, 0x38c5, 0x11d5, {0x91, 0xf6, 0x00, 0x10, 0x4b, 0xdb, 0x8f, 0xf9}};
#endif 

EXTERN_C const IID LIBID_LMVCallbackLib;

#ifndef __ILMVUserCallback1_INTERFACE_DEFINED__
#define __ILMVUserCallback1_INTERFACE_DEFINED__

/* interface ILMVUserCallback1 */
/* [unique][helpstring][uuid][local][object] */ 


EXTERN_C const IID IID_ILMVUserCallback1;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E2B7DBCD-38C5-11D5-91F6-00104BDB8FF9")
    ILMVUserCallback1 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ReceiveProc( 
            BYTE __RPC_FAR *pData,
            LONG lWidth,
            LONG lHeight,
            LONG lBitCount,
            LONG lSize,
            BOOL bTopDown) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILMVUserCallback1Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILMVUserCallback1 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILMVUserCallback1 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILMVUserCallback1 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReceiveProc )( 
            ILMVUserCallback1 __RPC_FAR * This,
            BYTE __RPC_FAR *pData,
            LONG lWidth,
            LONG lHeight,
            LONG lBitCount,
            LONG lSize,
            BOOL bTopDown);
        
        END_INTERFACE
    } ILMVUserCallback1Vtbl;

    interface ILMVUserCallback1
    {
        CONST_VTBL struct ILMVUserCallback1Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILMVUserCallback1_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILMVUserCallback1_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILMVUserCallback1_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILMVUserCallback1_ReceiveProc(This,pData,lWidth,lHeight,lBitCount,lSize,bTopDown)	\
    (This)->lpVtbl -> ReceiveProc(This,pData,lWidth,lHeight,lBitCount,lSize,bTopDown)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ILMVUserCallback1_ReceiveProc_Proxy( 
    ILMVUserCallback1 __RPC_FAR * This,
    BYTE __RPC_FAR *pData,
    LONG lWidth,
    LONG lHeight,
    LONG lBitCount,
    LONG lSize,
    BOOL bTopDown);


void __RPC_STUB ILMVUserCallback1_ReceiveProc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILMVUserCallback1_INTERFACE_DEFINED__ */


#ifndef __ILMVUserCallback_INTERFACE_DEFINED__
#define __ILMVUserCallback_INTERFACE_DEFINED__

/* interface ILMVUserCallback */
/* [unique][helpstring][uuid][local][object] */ 


EXTERN_C const IID IID_ILMVUserCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E2B7DC50-38C5-11D5-91F6-00104BDB8FF9")
    ILMVUserCallback : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ReceiveProc( 
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *pData,
            /* [in] */ long lWidth,
            /* [in] */ long lHeight,
            /* [in] */ long lBitCount,
            /* [in] */ long lSize,
            /* [in] */ long bTopDown) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILMVUserCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILMVUserCallback __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILMVUserCallback __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILMVUserCallback __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReceiveProc )( 
            ILMVUserCallback __RPC_FAR * This,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *pData,
            /* [in] */ long lWidth,
            /* [in] */ long lHeight,
            /* [in] */ long lBitCount,
            /* [in] */ long lSize,
            /* [in] */ long bTopDown);
        
        END_INTERFACE
    } ILMVUserCallbackVtbl;

    interface ILMVUserCallback
    {
        CONST_VTBL struct ILMVUserCallbackVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILMVUserCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILMVUserCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILMVUserCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILMVUserCallback_ReceiveProc(This,pData,lWidth,lHeight,lBitCount,lSize,bTopDown)	\
    (This)->lpVtbl -> ReceiveProc(This,pData,lWidth,lHeight,lBitCount,lSize,bTopDown)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ILMVUserCallback_ReceiveProc_Proxy( 
    ILMVUserCallback __RPC_FAR * This,
    /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *pData,
    /* [in] */ long lWidth,
    /* [in] */ long lHeight,
    /* [in] */ long lBitCount,
    /* [in] */ long lSize,
    /* [in] */ long bTopDown);


void __RPC_STUB ILMVUserCallback_ReceiveProc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILMVUserCallback_INTERFACE_DEFINED__ */


#ifndef __ILMVCallback1_INTERFACE_DEFINED__
#define __ILMVCallback1_INTERFACE_DEFINED__

/* interface ILMVCallback1 */
/* [unique][helpstring][uuid][dual][local][object] */ 


EXTERN_C const IID IID_ILMVCallback1;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E2B7DBCC-38C5-11D5-91F6-00104BDB8FF9")
    ILMVCallback1 : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReceiveProcObj( 
            /* [in] */ ILMVUserCallback1 __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InputPalette( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OutputPalette( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutputPalette( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILMVCallback1Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILMVCallback1 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILMVCallback1 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILMVCallback1 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ILMVCallback1 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ILMVCallback1 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ILMVCallback1 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ILMVCallback1 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ReceiveProcObj )( 
            ILMVCallback1 __RPC_FAR * This,
            /* [in] */ ILMVUserCallback1 __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InputPalette )( 
            ILMVCallback1 __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OutputPalette )( 
            ILMVCallback1 __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OutputPalette )( 
            ILMVCallback1 __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        END_INTERFACE
    } ILMVCallback1Vtbl;

    interface ILMVCallback1
    {
        CONST_VTBL struct ILMVCallback1Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILMVCallback1_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILMVCallback1_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILMVCallback1_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILMVCallback1_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ILMVCallback1_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ILMVCallback1_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ILMVCallback1_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ILMVCallback1_put_ReceiveProcObj(This,pVal)	\
    (This)->lpVtbl -> put_ReceiveProcObj(This,pVal)

#define ILMVCallback1_get_InputPalette(This,pVal)	\
    (This)->lpVtbl -> get_InputPalette(This,pVal)

#define ILMVCallback1_put_OutputPalette(This,newVal)	\
    (This)->lpVtbl -> put_OutputPalette(This,newVal)

#define ILMVCallback1_get_OutputPalette(This,pVal)	\
    (This)->lpVtbl -> get_OutputPalette(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ILMVCallback1_put_ReceiveProcObj_Proxy( 
    ILMVCallback1 __RPC_FAR * This,
    /* [in] */ ILMVUserCallback1 __RPC_FAR *pVal);


void __RPC_STUB ILMVCallback1_put_ReceiveProcObj_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVCallback1_get_InputPalette_Proxy( 
    ILMVCallback1 __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB ILMVCallback1_get_InputPalette_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ILMVCallback1_put_OutputPalette_Proxy( 
    ILMVCallback1 __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB ILMVCallback1_put_OutputPalette_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVCallback1_get_OutputPalette_Proxy( 
    ILMVCallback1 __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB ILMVCallback1_get_OutputPalette_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILMVCallback1_INTERFACE_DEFINED__ */


#ifndef __ILMVCallback_INTERFACE_DEFINED__
#define __ILMVCallback_INTERFACE_DEFINED__

/* interface ILMVCallback */
/* [unique][helpstring][uuid][dual][local][object] */ 


EXTERN_C const IID IID_ILMVCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E2B7DC51-38C5-11D5-91F6-00104BDB8FF9")
    ILMVCallback : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReceiveProcObj( 
            /* [in] */ IUnknown __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InputPalette( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OutputPalette( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutputPalette( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILMVCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILMVCallback __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILMVCallback __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILMVCallback __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ILMVCallback __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ILMVCallback __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ILMVCallback __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ILMVCallback __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ReceiveProcObj )( 
            ILMVCallback __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InputPalette )( 
            ILMVCallback __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OutputPalette )( 
            ILMVCallback __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OutputPalette )( 
            ILMVCallback __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        END_INTERFACE
    } ILMVCallbackVtbl;

    interface ILMVCallback
    {
        CONST_VTBL struct ILMVCallbackVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILMVCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILMVCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILMVCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILMVCallback_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ILMVCallback_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ILMVCallback_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ILMVCallback_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ILMVCallback_put_ReceiveProcObj(This,pVal)	\
    (This)->lpVtbl -> put_ReceiveProcObj(This,pVal)

#define ILMVCallback_get_InputPalette(This,pVal)	\
    (This)->lpVtbl -> get_InputPalette(This,pVal)

#define ILMVCallback_put_OutputPalette(This,newVal)	\
    (This)->lpVtbl -> put_OutputPalette(This,newVal)

#define ILMVCallback_get_OutputPalette(This,pVal)	\
    (This)->lpVtbl -> get_OutputPalette(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ILMVCallback_put_ReceiveProcObj_Proxy( 
    ILMVCallback __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pVal);


void __RPC_STUB ILMVCallback_put_ReceiveProcObj_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVCallback_get_InputPalette_Proxy( 
    ILMVCallback __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB ILMVCallback_get_InputPalette_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ILMVCallback_put_OutputPalette_Proxy( 
    ILMVCallback __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB ILMVCallback_put_OutputPalette_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVCallback_get_OutputPalette_Proxy( 
    ILMVCallback __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB ILMVCallback_get_OutputPalette_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILMVCallback_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_LMVCallback;

#ifdef __cplusplus

class DECLSPEC_UUID("E2B7DBCA-38C5-11D5-91F6-00104BDB8FF9")
LMVCallback;
#endif
#endif /* __LMVCallbackLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
