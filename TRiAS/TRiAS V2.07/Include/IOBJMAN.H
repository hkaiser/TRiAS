/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.00.44 */
/* at Tue May 26 23:27:22 1998
 */
/* Compiler settings for .\Objman.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"

#ifndef __iobjman_h__
#define __iobjman_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IObjectManagement_FWD_DEFINED__
#define __IObjectManagement_FWD_DEFINED__
typedef interface IObjectManagement IObjectManagement;
#endif 	/* __IObjectManagement_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __OBJMANLib_LIBRARY_DEFINED__
#define __OBJMANLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: OBJMANLib
 * at Tue May 26 23:27:22 1998
 * using MIDL 3.00.44
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_OBJMANLib;

#ifndef __IObjectManagement_INTERFACE_DEFINED__
#define __IObjectManagement_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IObjectManagement
 * at Tue May 26 23:27:22 1998
 * using MIDL 3.00.44
 ****************************************/
/* [object][helpstring][dual][uuid] */ 



EXTERN_C const IID IID_IObjectManagement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IObjectManagement : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetObject( 
            /* [in] */ BSTR bstrName,
            /* [out][in] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveObject( 
            /* [in] */ BSTR bstrName) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE DelObject( 
            /* [in] */ BSTR bstrName) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumObjects( 
            /* [in] */ DWORD __MIDL_0015,
            /* [out] */ IEnumUnknown __RPC_FAR *__RPC_FAR *ppenum) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumStrings( 
            /* [out][in] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateObject( 
            /* [in] */ REFGUID rClsID,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD dwMode,
            /* [out][in] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk,
            /* [in] */ VARIANT_BOOL fCreateTemp) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ReleaseObject( 
            /* [in] */ BSTR bstrName) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE RenameObject( 
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrNew) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetObject( 
            /* [in] */ IUnknown __RPC_FAR *pUnk,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD dwMode,
            /* [in] */ BOOL fCreateTemp) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Commit( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IObjectManagementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IObjectManagement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IObjectManagement __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IObjectManagement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IObjectManagement __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IObjectManagement __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IObjectManagement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IObjectManagement __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetObject )( 
            IObjectManagement __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [out][in] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveObject )( 
            IObjectManagement __RPC_FAR * This,
            /* [in] */ BSTR bstrName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DelObject )( 
            IObjectManagement __RPC_FAR * This,
            /* [in] */ BSTR bstrName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumObjects )( 
            IObjectManagement __RPC_FAR * This,
            /* [in] */ DWORD __MIDL_0015,
            /* [out] */ IEnumUnknown __RPC_FAR *__RPC_FAR *ppenum);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumStrings )( 
            IObjectManagement __RPC_FAR * This,
            /* [out][in] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateObject )( 
            IObjectManagement __RPC_FAR * This,
            /* [in] */ REFGUID rClsID,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD dwMode,
            /* [out][in] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk,
            /* [in] */ VARIANT_BOOL fCreateTemp);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseObject )( 
            IObjectManagement __RPC_FAR * This,
            /* [in] */ BSTR bstrName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RenameObject )( 
            IObjectManagement __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrNew);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetObject )( 
            IObjectManagement __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnk,
            /* [in] */ BSTR bstrName,
            /* [in] */ DWORD dwMode,
            /* [in] */ BOOL fCreateTemp);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Commit )( 
            IObjectManagement __RPC_FAR * This);
        
        END_INTERFACE
    } IObjectManagementVtbl;

    interface IObjectManagement
    {
        CONST_VTBL struct IObjectManagementVtbl __RPC_FAR *lpVtbl;
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

#define IObjectManagement_EnumObjects(This,__MIDL_0015,ppenum)	\
    (This)->lpVtbl -> EnumObjects(This,__MIDL_0015,ppenum)

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
    IObjectManagement __RPC_FAR * This,
    /* [in] */ BSTR bstrName,
    /* [out][in] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);


void __RPC_STUB IObjectManagement_GetObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IObjectManagement_SaveObject_Proxy( 
    IObjectManagement __RPC_FAR * This,
    /* [in] */ BSTR bstrName);


void __RPC_STUB IObjectManagement_SaveObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IObjectManagement_DelObject_Proxy( 
    IObjectManagement __RPC_FAR * This,
    /* [in] */ BSTR bstrName);


void __RPC_STUB IObjectManagement_DelObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IObjectManagement_EnumObjects_Proxy( 
    IObjectManagement __RPC_FAR * This,
    /* [in] */ DWORD __MIDL_0015,
    /* [out] */ IEnumUnknown __RPC_FAR *__RPC_FAR *ppenum);


void __RPC_STUB IObjectManagement_EnumObjects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IObjectManagement_EnumStrings_Proxy( 
    IObjectManagement __RPC_FAR * This,
    /* [out][in] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);


void __RPC_STUB IObjectManagement_EnumStrings_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IObjectManagement_CreateObject_Proxy( 
    IObjectManagement __RPC_FAR * This,
    /* [in] */ REFGUID rClsID,
    /* [in] */ BSTR bstrName,
    /* [in] */ DWORD dwMode,
    /* [out][in] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk,
    /* [in] */ VARIANT_BOOL fCreateTemp);


void __RPC_STUB IObjectManagement_CreateObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IObjectManagement_ReleaseObject_Proxy( 
    IObjectManagement __RPC_FAR * This,
    /* [in] */ BSTR bstrName);


void __RPC_STUB IObjectManagement_ReleaseObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IObjectManagement_RenameObject_Proxy( 
    IObjectManagement __RPC_FAR * This,
    /* [in] */ BSTR bstrName,
    /* [in] */ BSTR bstrNew);


void __RPC_STUB IObjectManagement_RenameObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IObjectManagement_SetObject_Proxy( 
    IObjectManagement __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnk,
    /* [in] */ BSTR bstrName,
    /* [in] */ DWORD dwMode,
    /* [in] */ BOOL fCreateTemp);


void __RPC_STUB IObjectManagement_SetObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IObjectManagement_Commit_Proxy( 
    IObjectManagement __RPC_FAR * This);


void __RPC_STUB IObjectManagement_Commit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IObjectManagement_INTERFACE_DEFINED__ */


#ifdef __cplusplus
EXTERN_C const CLSID CLSID_CObjectManagement;

class CObjectManagement;
#endif
#endif /* __OBJMANLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
