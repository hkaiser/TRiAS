
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Wed Oct 30 13:21:21 2002
 */
/* Compiler settings for TRiASCFG.idl:
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

#ifndef __TRiASCFG_h__
#define __TRiASCFG_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ILoadXmlService_FWD_DEFINED__
#define __ILoadXmlService_FWD_DEFINED__
typedef interface ILoadXmlService ILoadXmlService;
#endif 	/* __ILoadXmlService_FWD_DEFINED__ */


#ifndef __LoadXmlService_FWD_DEFINED__
#define __LoadXmlService_FWD_DEFINED__

#ifdef __cplusplus
typedef class LoadXmlService LoadXmlService;
#else
typedef struct LoadXmlService LoadXmlService;
#endif /* __cplusplus */

#endif 	/* __LoadXmlService_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __ILoadXmlService_INTERFACE_DEFINED__
#define __ILoadXmlService_INTERFACE_DEFINED__

/* interface ILoadXmlService */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ILoadXmlService;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7936AEC8-E1AD-408C-8240-89B62071CEC5")
    ILoadXmlService : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ResourceModule( 
            /* [retval][out] */ BSTR *Module) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ResourceModule( 
            /* [in] */ BSTR Module) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadXmlFromResource( 
            /* [in] */ BSTR Rsc,
            /* [retval][out] */ IDispatch **ppIXmlDoc) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadXmlFromFile( 
            /* [in] */ BSTR File,
            /* [retval][out] */ IDispatch **ppIXmlDoc) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILoadXmlServiceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILoadXmlService * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILoadXmlService * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILoadXmlService * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ILoadXmlService * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ILoadXmlService * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ILoadXmlService * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ILoadXmlService * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ResourceModule )( 
            ILoadXmlService * This,
            /* [retval][out] */ BSTR *Module);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ResourceModule )( 
            ILoadXmlService * This,
            /* [in] */ BSTR Module);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadXmlFromResource )( 
            ILoadXmlService * This,
            /* [in] */ BSTR Rsc,
            /* [retval][out] */ IDispatch **ppIXmlDoc);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadXmlFromFile )( 
            ILoadXmlService * This,
            /* [in] */ BSTR File,
            /* [retval][out] */ IDispatch **ppIXmlDoc);
        
        END_INTERFACE
    } ILoadXmlServiceVtbl;

    interface ILoadXmlService
    {
        CONST_VTBL struct ILoadXmlServiceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILoadXmlService_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILoadXmlService_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILoadXmlService_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILoadXmlService_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ILoadXmlService_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ILoadXmlService_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ILoadXmlService_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ILoadXmlService_get_ResourceModule(This,Module)	\
    (This)->lpVtbl -> get_ResourceModule(This,Module)

#define ILoadXmlService_put_ResourceModule(This,Module)	\
    (This)->lpVtbl -> put_ResourceModule(This,Module)

#define ILoadXmlService_LoadXmlFromResource(This,Rsc,ppIXmlDoc)	\
    (This)->lpVtbl -> LoadXmlFromResource(This,Rsc,ppIXmlDoc)

#define ILoadXmlService_LoadXmlFromFile(This,File,ppIXmlDoc)	\
    (This)->lpVtbl -> LoadXmlFromFile(This,File,ppIXmlDoc)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE ILoadXmlService_get_ResourceModule_Proxy( 
    ILoadXmlService * This,
    /* [retval][out] */ BSTR *Module);


void __RPC_STUB ILoadXmlService_get_ResourceModule_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE ILoadXmlService_put_ResourceModule_Proxy( 
    ILoadXmlService * This,
    /* [in] */ BSTR Module);


void __RPC_STUB ILoadXmlService_put_ResourceModule_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILoadXmlService_LoadXmlFromResource_Proxy( 
    ILoadXmlService * This,
    /* [in] */ BSTR Rsc,
    /* [retval][out] */ IDispatch **ppIXmlDoc);


void __RPC_STUB ILoadXmlService_LoadXmlFromResource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILoadXmlService_LoadXmlFromFile_Proxy( 
    ILoadXmlService * This,
    /* [in] */ BSTR File,
    /* [retval][out] */ IDispatch **ppIXmlDoc);


void __RPC_STUB ILoadXmlService_LoadXmlFromFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILoadXmlService_INTERFACE_DEFINED__ */



#ifndef __TRiASCFG_LIBRARY_DEFINED__
#define __TRiASCFG_LIBRARY_DEFINED__

/* library TRiASCFG */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_TRiASCFG;

EXTERN_C const CLSID CLSID_LoadXmlService;

#ifdef __cplusplus

class DECLSPEC_UUID("56CE2E72-6C9F-469D-93EA-C0D9FB51A019")
LoadXmlService;
#endif
#endif /* __TRiASCFG_LIBRARY_DEFINED__ */

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


