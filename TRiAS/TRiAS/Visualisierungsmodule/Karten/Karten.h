
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Sat Mar 09 19:53:36 2002
 */
/* Compiler settings for Karten.idl:
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

#ifndef __Karten_h__
#define __Karten_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DKarten_FWD_DEFINED__
#define ___DKarten_FWD_DEFINED__
typedef interface _DKarten _DKarten;
#endif 	/* ___DKarten_FWD_DEFINED__ */


#ifndef ___DKartenEvents_FWD_DEFINED__
#define ___DKartenEvents_FWD_DEFINED__
typedef interface _DKartenEvents _DKartenEvents;
#endif 	/* ___DKartenEvents_FWD_DEFINED__ */


#ifndef __Karten_FWD_DEFINED__
#define __Karten_FWD_DEFINED__

#ifdef __cplusplus
typedef class Karten Karten;
#else
typedef struct Karten Karten;
#endif /* __cplusplus */

#endif 	/* __Karten_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __KARTENLib_LIBRARY_DEFINED__
#define __KARTENLib_LIBRARY_DEFINED__

/* library KARTENLib */
/* [control][helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_KARTENLib;

#ifndef ___DKarten_DISPINTERFACE_DEFINED__
#define ___DKarten_DISPINTERFACE_DEFINED__

/* dispinterface _DKarten */
/* [hidden][helpstring][uuid] */ 


EXTERN_C const IID DIID__DKarten;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("0603C948-B16A-11CF-86AA-00A024145748")
    _DKarten : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DKartenVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DKarten * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DKarten * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DKarten * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DKarten * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DKarten * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DKarten * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DKarten * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DKartenVtbl;

    interface _DKarten
    {
        CONST_VTBL struct _DKartenVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DKarten_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DKarten_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DKarten_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DKarten_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DKarten_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DKarten_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DKarten_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DKarten_DISPINTERFACE_DEFINED__ */


#ifndef ___DKartenEvents_DISPINTERFACE_DEFINED__
#define ___DKartenEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DKartenEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DKartenEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("0603C949-B16A-11CF-86AA-00A024145748")
    _DKartenEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DKartenEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DKartenEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DKartenEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DKartenEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DKartenEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DKartenEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DKartenEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DKartenEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DKartenEventsVtbl;

    interface _DKartenEvents
    {
        CONST_VTBL struct _DKartenEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DKartenEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DKartenEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DKartenEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DKartenEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DKartenEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DKartenEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DKartenEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DKartenEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Karten;

#ifdef __cplusplus

class DECLSPEC_UUID("07963893-3123-101C-BB62-00AA0018497C")
Karten;
#endif
#endif /* __KARTENLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


