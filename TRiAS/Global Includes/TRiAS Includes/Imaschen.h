
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0280 */
/* at Tue May 23 14:03:02 2000
 */
/* Compiler settings for Imaschen.idl:
    Os (OptLev=s), W1, Zp8, env=Win32 (32b run), ms_ext, c_ext
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

#ifndef __Imaschen_h__
#define __Imaschen_h__

/* Forward Declarations */ 

#ifndef __IExtLinienVerfolgung_FWD_DEFINED__
#define __IExtLinienVerfolgung_FWD_DEFINED__
typedef interface IExtLinienVerfolgung IExtLinienVerfolgung;
#endif 	/* __IExtLinienVerfolgung_FWD_DEFINED__ */


#ifndef __IExtLinienVerfolgungEx_FWD_DEFINED__
#define __IExtLinienVerfolgungEx_FWD_DEFINED__
typedef interface IExtLinienVerfolgungEx IExtLinienVerfolgungEx;
#endif 	/* __IExtLinienVerfolgungEx_FWD_DEFINED__ */


#ifndef __ExtLinienVerfolgung_FWD_DEFINED__
#define __ExtLinienVerfolgung_FWD_DEFINED__

#ifdef __cplusplus
typedef class ExtLinienVerfolgung ExtLinienVerfolgung;
#else
typedef struct ExtLinienVerfolgung ExtLinienVerfolgung;
#endif /* __cplusplus */

#endif 	/* __ExtLinienVerfolgung_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __imaschen_LIBRARY_DEFINED__
#define __imaschen_LIBRARY_DEFINED__

/* library imaschen */
/* [helpstring][lcid][version][uuid] */ 


EXTERN_C const IID LIBID_imaschen;

#ifndef __IExtLinienVerfolgung_INTERFACE_DEFINED__
#define __IExtLinienVerfolgung_INTERFACE_DEFINED__

/* interface IExtLinienVerfolgung */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IExtLinienVerfolgung;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("079638D5-3123-101C-BB62-00AA0018497C")
    IExtLinienVerfolgung : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE LinesUnion( 
            /* [in] */ IEnumObjectsByNumber __RPC_FAR *pInput,
            /* [in] */ double dTolerance,
            /* [in] */ VARIANT_BOOL bOutputUnIdents,
            /* [in] */ VARIANT_BOOL bCreateAreas,
            /* [optional][in] */ VARIANT vPI,
            /* [optional][out] */ VARIANT __RPC_FAR *pvUsed,
            /* [retval][out] */ IEnumObjectsByNumber __RPC_FAR *__RPC_FAR *ppUnion) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IExtLinienVerfolgungVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IExtLinienVerfolgung __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IExtLinienVerfolgung __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IExtLinienVerfolgung __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IExtLinienVerfolgung __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IExtLinienVerfolgung __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IExtLinienVerfolgung __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IExtLinienVerfolgung __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LinesUnion )( 
            IExtLinienVerfolgung __RPC_FAR * This,
            /* [in] */ IEnumObjectsByNumber __RPC_FAR *pInput,
            /* [in] */ double dTolerance,
            /* [in] */ VARIANT_BOOL bOutputUnIdents,
            /* [in] */ VARIANT_BOOL bCreateAreas,
            /* [optional][in] */ VARIANT vPI,
            /* [optional][out] */ VARIANT __RPC_FAR *pvUsed,
            /* [retval][out] */ IEnumObjectsByNumber __RPC_FAR *__RPC_FAR *ppUnion);
        
        END_INTERFACE
    } IExtLinienVerfolgungVtbl;

    interface IExtLinienVerfolgung
    {
        CONST_VTBL struct IExtLinienVerfolgungVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IExtLinienVerfolgung_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IExtLinienVerfolgung_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IExtLinienVerfolgung_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IExtLinienVerfolgung_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IExtLinienVerfolgung_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IExtLinienVerfolgung_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IExtLinienVerfolgung_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IExtLinienVerfolgung_LinesUnion(This,pInput,dTolerance,bOutputUnIdents,bCreateAreas,vPI,pvUsed,ppUnion)	\
    (This)->lpVtbl -> LinesUnion(This,pInput,dTolerance,bOutputUnIdents,bCreateAreas,vPI,pvUsed,ppUnion)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IExtLinienVerfolgung_LinesUnion_Proxy( 
    IExtLinienVerfolgung __RPC_FAR * This,
    /* [in] */ IEnumObjectsByNumber __RPC_FAR *pInput,
    /* [in] */ double dTolerance,
    /* [in] */ VARIANT_BOOL bOutputUnIdents,
    /* [in] */ VARIANT_BOOL bCreateAreas,
    /* [optional][in] */ VARIANT vPI,
    /* [optional][out] */ VARIANT __RPC_FAR *pvUsed,
    /* [retval][out] */ IEnumObjectsByNumber __RPC_FAR *__RPC_FAR *ppUnion);


void __RPC_STUB IExtLinienVerfolgung_LinesUnion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IExtLinienVerfolgung_INTERFACE_DEFINED__ */


#ifndef __IExtLinienVerfolgungEx_INTERFACE_DEFINED__
#define __IExtLinienVerfolgungEx_INTERFACE_DEFINED__

/* interface IExtLinienVerfolgungEx */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IExtLinienVerfolgungEx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D41E2047-E037-11D2-9BCF-3E6920524153")
    IExtLinienVerfolgungEx : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE LinesUnion( 
            /* [in] */ INT_PTR hPr,
            /* [in] */ IEnumObjectsByNumber __RPC_FAR *pInput,
            /* [in] */ double dTolerance,
            /* [in] */ VARIANT_BOOL bOutputUnIdents,
            /* [in] */ VARIANT_BOOL bCreateAreas,
            /* [optional][in] */ VARIANT vPI,
            /* [optional][out] */ VARIANT __RPC_FAR *pvUsed,
            /* [retval][out] */ IEnumObjectsByNumber __RPC_FAR *__RPC_FAR *ppUnion) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IExtLinienVerfolgungExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IExtLinienVerfolgungEx __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IExtLinienVerfolgungEx __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IExtLinienVerfolgungEx __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IExtLinienVerfolgungEx __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IExtLinienVerfolgungEx __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IExtLinienVerfolgungEx __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IExtLinienVerfolgungEx __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LinesUnion )( 
            IExtLinienVerfolgungEx __RPC_FAR * This,
            /* [in] */ INT_PTR hPr,
            /* [in] */ IEnumObjectsByNumber __RPC_FAR *pInput,
            /* [in] */ double dTolerance,
            /* [in] */ VARIANT_BOOL bOutputUnIdents,
            /* [in] */ VARIANT_BOOL bCreateAreas,
            /* [optional][in] */ VARIANT vPI,
            /* [optional][out] */ VARIANT __RPC_FAR *pvUsed,
            /* [retval][out] */ IEnumObjectsByNumber __RPC_FAR *__RPC_FAR *ppUnion);
        
        END_INTERFACE
    } IExtLinienVerfolgungExVtbl;

    interface IExtLinienVerfolgungEx
    {
        CONST_VTBL struct IExtLinienVerfolgungExVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IExtLinienVerfolgungEx_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IExtLinienVerfolgungEx_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IExtLinienVerfolgungEx_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IExtLinienVerfolgungEx_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IExtLinienVerfolgungEx_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IExtLinienVerfolgungEx_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IExtLinienVerfolgungEx_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IExtLinienVerfolgungEx_LinesUnion(This,hPr,pInput,dTolerance,bOutputUnIdents,bCreateAreas,vPI,pvUsed,ppUnion)	\
    (This)->lpVtbl -> LinesUnion(This,hPr,pInput,dTolerance,bOutputUnIdents,bCreateAreas,vPI,pvUsed,ppUnion)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IExtLinienVerfolgungEx_LinesUnion_Proxy( 
    IExtLinienVerfolgungEx __RPC_FAR * This,
    /* [in] */ INT_PTR hPr,
    /* [in] */ IEnumObjectsByNumber __RPC_FAR *pInput,
    /* [in] */ double dTolerance,
    /* [in] */ VARIANT_BOOL bOutputUnIdents,
    /* [in] */ VARIANT_BOOL bCreateAreas,
    /* [optional][in] */ VARIANT vPI,
    /* [optional][out] */ VARIANT __RPC_FAR *pvUsed,
    /* [retval][out] */ IEnumObjectsByNumber __RPC_FAR *__RPC_FAR *ppUnion);


void __RPC_STUB IExtLinienVerfolgungEx_LinesUnion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IExtLinienVerfolgungEx_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ExtLinienVerfolgung;

#ifdef __cplusplus

class DECLSPEC_UUID("079638DA-3123-101C-BB62-00AA0018497C")
ExtLinienVerfolgung;
#endif
#endif /* __imaschen_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


