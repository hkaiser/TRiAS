
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Mon Nov 08 09:12:51 2004
 */
/* Compiler settings for ObjMan.idl:
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

#ifndef __iobjman_h__
#define __iobjman_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IObjectManagement_FWD_DEFINED__
#define __IObjectManagement_FWD_DEFINED__
typedef interface IObjectManagement IObjectManagement;
#endif 	/* __IObjectManagement_FWD_DEFINED__ */


#ifndef __CObjectManagement_FWD_DEFINED__
#define __CObjectManagement_FWD_DEFINED__

#ifdef __cplusplus
typedef class CObjectManagement CObjectManagement;
#else
typedef struct CObjectManagement CObjectManagement;
#endif /* __cplusplus */

#endif 	/* __CObjectManagement_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __OBJMANLib_LIBRARY_DEFINED__
#define __OBJMANLib_LIBRARY_DEFINED__

/* library OBJMANLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_OBJMANLib;

#ifndef __IObjectManagement_INTERFACE_DEFINED__
#define __IObjectManagement_INTERFACE_DEFINED__

/* interface IObjectManagement */
/* [object][helpstring][dual][uuid] */ 


EXTERN_C const IID IID_IObjectManagement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0796384D-3123-101C-BB62-00AA0018497C")
    IObjectManagement : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetObject( 
            /* [in] */ BSTR bstrName,
            /* [out][in] */ IUnknown **ppUnk) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveObject( 
            /* [in] */ BSTR bstrName) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE DelObject( 
            /* [in] */ BSTR bstrName) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumObjects( 
            /* [in] */ DWORD __MIDL_0010,
            /* [out] */ IEnumUnknown **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumStrings( 
            /* [out][in] */ IUnknown **ppUnk) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateObject( 
            /* [in] */ REFGUID rClsID,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD dwMode,
            /* [out][in] */ IUnknown **ppUnk,
            /* [in] */ VARIANT_BOOL fCreateTemp) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ReleaseObject( 
            /* [in] */ BSTR bstrName) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE RenameObject( 
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrNew) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetObject( 
            /* [in] */ IUnknown *pUnk,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD dwMode,
            /* [in] */ BOOL fCreateTemp) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Commit( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IObjectManagementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IObjectManagement * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IObjectManagement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IObjectManagement * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IObjectManagement * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IObjectManagement * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IObjectManagement * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IObjectManagement * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetObject )( 
            IObjectManagement * This,
            /* [in] */ BSTR bstrName,
            /* [out][in] */ IUnknown **ppUnk);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveObject )( 
            IObjectManagement * This,
            /* [in] */ BSTR bstrName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DelObject )( 
            IObjectManagement * This,
            /* [in] */ BSTR bstrName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnumObjects )( 
            IObjectManagement * This,
            /* [in] */ DWORD __MIDL_0010,
            /* [out] */ IEnumUnknown **ppenum);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnumStrings )( 
            IObjectManagement * This,
            /* [out][in] */ IUnknown **ppUnk);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateObject )( 
            IObjectManagement * This,
            /* [in] */ REFGUID rClsID,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD dwMode,
            /* [out][in] */ IUnknown **ppUnk,
            /* [in] */ VARIANT_BOOL fCreateTemp);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReleaseObject )( 
            IObjectManagement * This,
            /* [in] */ BSTR bstrName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RenameObject )( 
            IObjectManagement * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrNew);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetObject )( 
            IObjectManagement * This,
            /* [in] */ IUnknown *pUnk,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD dwMode,
            /* [in] */ BOOL fCreateTemp);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Commit )( 
            IObjectManagement * This);
        
        END_INTERFACE
    } IObjectManagementVtbl;

    interface IObjectManagement
    {
        CONST_VTBL struct IObjectManagementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IObjectManagement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IObjectManagement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IObjectManagement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IObjectManagement_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IObjectManagement_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IObjectManagement_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IObjectManagement_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IObjectManagement_GetObject(This,bstrName,ppUnk)	\
    (This)->lpVtbl -> GetObject(This,bstrName,ppUnk)

#define IObjectManagement_SaveObject(This,bstrName)	\
    (This)->lpVtbl -> SaveObject(This,bstrName)

#define IObjectManagement_DelObject(This,bstrName)	\
    (This)->lpVtbl -> DelObject(This,bstrName)

#define IObjectManagement_EnumObjects(This,__MIDL_0010,ppenum)	\
    (This)->lpVtbl -> EnumObjects(This,__MIDL_0010,ppenum)

#define IObjectManagement_EnumStrings(This,ppUnk)	\
    (This)->lpVtbl -> EnumStrings(This,ppUnk)

#define IObjectManagement_CreateObject(This,rClsID,bstrName,dwMode,ppUnk,fCreateTemp)	\
    (This)->lpVtbl -> CreateObject(This,rClsID,bstrName,dwMode,ppUnk,fCreateTemp)

#define IObjectManagement_ReleaseObject(This,bstrName)	\
    (This)->lpVtbl -> ReleaseObject(This,bstrName)

#define IObjectManagement_RenameObject(This,bstrName,bstrNew)	\
    (This)->lpVtbl -> RenameObject(This,bstrName,bstrNew)

#define IObjectManagement_SetObject(This,pUnk,bstrName,dwMode,fCreateTemp)	\
    (This)->lpVtbl -> SetObject(This,pUnk,bstrName,dwMode,fCreateTemp)

#define IObjectManagement_Commit(This)	\
    (This)->lpVtbl -> Commit(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IObjectManagement_GetObject_Proxy( 
    IObjectManagement * This,
    /* [in] */ BSTR bstrName,
    /* [out][in] */ IUnknown **ppUnk);


void __RPC_STUB IObjectManagement_GetObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IObjectManagement_SaveObject_Proxy( 
    IObjectManagement * This,
    /* [in] */ BSTR bstrName);


void __RPC_STUB IObjectManagement_SaveObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IObjectManagement_DelObject_Proxy( 
    IObjectManagement * This,
    /* [in] */ BSTR bstrName);


void __RPC_STUB IObjectManagement_DelObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IObjectManagement_EnumObjects_Proxy( 
    IObjectManagement * This,
    /* [in] */ DWORD __MIDL_0010,
    /* [out] */ IEnumUnknown **ppenum);


void __RPC_STUB IObjectManagement_EnumObjects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IObjectManagement_EnumStrings_Proxy( 
    IObjectManagement * This,
    /* [out][in] */ IUnknown **ppUnk);


void __RPC_STUB IObjectManagement_EnumStrings_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IObjectManagement_CreateObject_Proxy( 
    IObjectManagement * This,
    /* [in] */ REFGUID rClsID,
    /* [in] */ BSTR bstrName,
    /* [in] */ DWORD dwMode,
    /* [out][in] */ IUnknown **ppUnk,
    /* [in] */ VARIANT_BOOL fCreateTemp);


void __RPC_STUB IObjectManagement_CreateObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IObjectManagement_ReleaseObject_Proxy( 
    IObjectManagement * This,
    /* [in] */ BSTR bstrName);


void __RPC_STUB IObjectManagement_ReleaseObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IObjectManagement_RenameObject_Proxy( 
    IObjectManagement * This,
    /* [in] */ BSTR bstrName,
    /* [in] */ BSTR bstrNew);


void __RPC_STUB IObjectManagement_RenameObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IObjectManagement_SetObject_Proxy( 
    IObjectManagement * This,
    /* [in] */ IUnknown *pUnk,
    /* [in] */ BSTR bstrName,
    /* [in] */ DWORD dwMode,
    /* [in] */ BOOL fCreateTemp);


void __RPC_STUB IObjectManagement_SetObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IObjectManagement_Commit_Proxy( 
    IObjectManagement * This);


void __RPC_STUB IObjectManagement_Commit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IObjectManagement_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CObjectManagement;

#ifdef __cplusplus

class DECLSPEC_UUID("0796384E-3123-101C-BB62-00AA0018497C")
CObjectManagement;
#endif
#endif /* __OBJMANLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


