
#pragma warning( disable: 4049 )  /* more than 64k source lines */
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */
#pragma warning( disable: 4211 )  /* redefine extent to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0359 */
/* at Thu Sep 05 15:06:08 2002
 */
/* Compiler settings for D:\TRiASDev\CvrtCoords\CvrtBna\CvrtBna.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


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

#ifndef __CvrtBna_h__
#define __CvrtBna_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITransformLineOfTextCallback_FWD_DEFINED__
#define __ITransformLineOfTextCallback_FWD_DEFINED__
typedef interface ITransformLineOfTextCallback ITransformLineOfTextCallback;
#endif 	/* __ITransformLineOfTextCallback_FWD_DEFINED__ */


#ifndef __ITransformLineOfText_FWD_DEFINED__
#define __ITransformLineOfText_FWD_DEFINED__
typedef interface ITransformLineOfText ITransformLineOfText;
#endif 	/* __ITransformLineOfText_FWD_DEFINED__ */


#ifndef __ConvertBnaCoords_FWD_DEFINED__
#define __ConvertBnaCoords_FWD_DEFINED__

#ifdef __cplusplus
typedef class ConvertBnaCoords ConvertBnaCoords;
#else
typedef struct ConvertBnaCoords ConvertBnaCoords;
#endif /* __cplusplus */

#endif 	/* __ConvertBnaCoords_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_CvrtBna_0000 */
/* [local] */ 

#pragma once


extern RPC_IF_HANDLE __MIDL_itf_CvrtBna_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_CvrtBna_0000_v0_0_s_ifspec;

#ifndef __ITransformLineOfTextCallback_INTERFACE_DEFINED__
#define __ITransformLineOfTextCallback_INTERFACE_DEFINED__

/* interface ITransformLineOfTextCallback */
/* [unique][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_ITransformLineOfTextCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4BB28F76-3DF5-4110-83C4-7A9F21E539D6")
    ITransformLineOfTextCallback : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TransformCoords( 
            /* [out][in] */ double *pdX,
            /* [out][in] */ double *pdY) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITransformLineOfTextCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITransformLineOfTextCallback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITransformLineOfTextCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITransformLineOfTextCallback * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITransformLineOfTextCallback * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITransformLineOfTextCallback * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITransformLineOfTextCallback * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITransformLineOfTextCallback * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *TransformCoords )( 
            ITransformLineOfTextCallback * This,
            /* [out][in] */ double *pdX,
            /* [out][in] */ double *pdY);
        
        END_INTERFACE
    } ITransformLineOfTextCallbackVtbl;

    interface ITransformLineOfTextCallback
    {
        CONST_VTBL struct ITransformLineOfTextCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITransformLineOfTextCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITransformLineOfTextCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITransformLineOfTextCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITransformLineOfTextCallback_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITransformLineOfTextCallback_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITransformLineOfTextCallback_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITransformLineOfTextCallback_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITransformLineOfTextCallback_TransformCoords(This,pdX,pdY)	\
    (This)->lpVtbl -> TransformCoords(This,pdX,pdY)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITransformLineOfTextCallback_TransformCoords_Proxy( 
    ITransformLineOfTextCallback * This,
    /* [out][in] */ double *pdX,
    /* [out][in] */ double *pdY);


void __RPC_STUB ITransformLineOfTextCallback_TransformCoords_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITransformLineOfTextCallback_INTERFACE_DEFINED__ */


#ifndef __ITransformLineOfText_INTERFACE_DEFINED__
#define __ITransformLineOfText_INTERFACE_DEFINED__

/* interface ITransformLineOfText */
/* [unique][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_ITransformLineOfText;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("073F080F-8D7F-42FF-B969-6147ED9D8776")
    ITransformLineOfText : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Callback( 
            /* [in] */ ITransformLineOfTextCallback *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TransformLineOfText( 
            /* [in] */ BSTR bstrIn,
            /* [retval][out] */ BSTR *bstrOut) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITransformLineOfTextVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITransformLineOfText * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITransformLineOfText * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITransformLineOfText * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITransformLineOfText * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITransformLineOfText * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITransformLineOfText * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITransformLineOfText * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Callback )( 
            ITransformLineOfText * This,
            /* [in] */ ITransformLineOfTextCallback *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            ITransformLineOfText * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *TransformLineOfText )( 
            ITransformLineOfText * This,
            /* [in] */ BSTR bstrIn,
            /* [retval][out] */ BSTR *bstrOut);
        
        END_INTERFACE
    } ITransformLineOfTextVtbl;

    interface ITransformLineOfText
    {
        CONST_VTBL struct ITransformLineOfTextVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITransformLineOfText_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITransformLineOfText_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITransformLineOfText_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITransformLineOfText_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITransformLineOfText_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITransformLineOfText_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITransformLineOfText_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITransformLineOfText_put_Callback(This,pVal)	\
    (This)->lpVtbl -> put_Callback(This,pVal)

#define ITransformLineOfText_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define ITransformLineOfText_TransformLineOfText(This,bstrIn,bstrOut)	\
    (This)->lpVtbl -> TransformLineOfText(This,bstrIn,bstrOut)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITransformLineOfText_put_Callback_Proxy( 
    ITransformLineOfText * This,
    /* [in] */ ITransformLineOfTextCallback *pVal);


void __RPC_STUB ITransformLineOfText_put_Callback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITransformLineOfText_get_Version_Proxy( 
    ITransformLineOfText * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITransformLineOfText_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITransformLineOfText_TransformLineOfText_Proxy( 
    ITransformLineOfText * This,
    /* [in] */ BSTR bstrIn,
    /* [retval][out] */ BSTR *bstrOut);


void __RPC_STUB ITransformLineOfText_TransformLineOfText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITransformLineOfText_INTERFACE_DEFINED__ */



#ifndef __CvrtBna_LIBRARY_DEFINED__
#define __CvrtBna_LIBRARY_DEFINED__

/* library CvrtBna */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_CvrtBna;

EXTERN_C const CLSID CLSID_ConvertBnaCoords;

#ifdef __cplusplus

class DECLSPEC_UUID("6CD362C8-AD9E-4A03-818C-830ED299F5BF")
ConvertBnaCoords;
#endif
#endif /* __CvrtBna_LIBRARY_DEFINED__ */

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


