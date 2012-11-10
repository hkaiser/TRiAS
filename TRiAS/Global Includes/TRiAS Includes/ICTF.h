
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Fri Dec 03 14:21:54 2004
 */
/* Compiler settings for CTF.idl:
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

#ifndef __ICTF_h__
#define __ICTF_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DGMPoint_FWD_DEFINED__
#define ___DGMPoint_FWD_DEFINED__
typedef interface _DGMPoint _DGMPoint;
#endif 	/* ___DGMPoint_FWD_DEFINED__ */


#ifndef ___DGMPoints_FWD_DEFINED__
#define ___DGMPoints_FWD_DEFINED__
typedef interface _DGMPoints _DGMPoints;
#endif 	/* ___DGMPoints_FWD_DEFINED__ */


#ifndef __ICoordTransform_FWD_DEFINED__
#define __ICoordTransform_FWD_DEFINED__
typedef interface ICoordTransform ICoordTransform;
#endif 	/* __ICoordTransform_FWD_DEFINED__ */


#ifndef __ICoordTransformInit_FWD_DEFINED__
#define __ICoordTransformInit_FWD_DEFINED__
typedef interface ICoordTransformInit ICoordTransformInit;
#endif 	/* __ICoordTransformInit_FWD_DEFINED__ */


#ifndef __ICTFExContext_FWD_DEFINED__
#define __ICTFExContext_FWD_DEFINED__
typedef interface ICTFExContext ICTFExContext;
#endif 	/* __ICTFExContext_FWD_DEFINED__ */


#ifndef __ICoordTransformEvents_FWD_DEFINED__
#define __ICoordTransformEvents_FWD_DEFINED__
typedef interface ICoordTransformEvents ICoordTransformEvents;
#endif 	/* __ICoordTransformEvents_FWD_DEFINED__ */


#ifndef __DefaultCoordTrans_FWD_DEFINED__
#define __DefaultCoordTrans_FWD_DEFINED__

#ifdef __cplusplus
typedef class DefaultCoordTrans DefaultCoordTrans;
#else
typedef struct DefaultCoordTrans DefaultCoordTrans;
#endif /* __cplusplus */

#endif 	/* __DefaultCoordTrans_FWD_DEFINED__ */


#ifndef __ManageCoordParam_FWD_DEFINED__
#define __ManageCoordParam_FWD_DEFINED__

#ifdef __cplusplus
typedef class ManageCoordParam ManageCoordParam;
#else
typedef struct ManageCoordParam ManageCoordParam;
#endif /* __cplusplus */

#endif 	/* __ManageCoordParam_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_CTF_0000 */
/* [local] */ 

#pragma once





extern RPC_IF_HANDLE __MIDL_itf_CTF_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_CTF_0000_v0_0_s_ifspec;

#ifndef ___DGMPoint_INTERFACE_DEFINED__
#define ___DGMPoint_INTERFACE_DEFINED__

/* interface _DGMPoint */
/* [object][local][oleautomation][nonextensible][dual][hidden][uuid] */ 


EXTERN_C const IID IID__DGMPoint;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CE361C90-B00C-11CF-ABEF-08003601B769")
    _DGMPoint : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT __stdcall get_X( 
            /* [retval][out] */ double *returnValue) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT __stdcall put_X( 
            /* [in] */ double returnValue) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT __stdcall get_Y( 
            /* [retval][out] */ double *returnValue) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT __stdcall put_Y( 
            /* [in] */ double returnValue) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT __stdcall get_Z( 
            /* [retval][out] */ double *returnValue) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT __stdcall put_Z( 
            /* [in] */ double returnValue) = 0;
        
        virtual /* [hidden][restricted][id] */ HRESULT __stdcall GetPoint( 
            /* [out] */ double *Point) = 0;
        
        virtual /* [hidden][restricted][id] */ HRESULT __stdcall SetPoint( 
            /* [in] */ double *Point) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _DGMPointVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DGMPoint * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DGMPoint * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DGMPoint * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DGMPoint * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DGMPoint * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DGMPoint * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DGMPoint * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( __stdcall *get_X )( 
            _DGMPoint * This,
            /* [retval][out] */ double *returnValue);
        
        /* [helpcontext][propput][id] */ HRESULT ( __stdcall *put_X )( 
            _DGMPoint * This,
            /* [in] */ double returnValue);
        
        /* [helpcontext][propget][id] */ HRESULT ( __stdcall *get_Y )( 
            _DGMPoint * This,
            /* [retval][out] */ double *returnValue);
        
        /* [helpcontext][propput][id] */ HRESULT ( __stdcall *put_Y )( 
            _DGMPoint * This,
            /* [in] */ double returnValue);
        
        /* [helpcontext][propget][id] */ HRESULT ( __stdcall *get_Z )( 
            _DGMPoint * This,
            /* [retval][out] */ double *returnValue);
        
        /* [helpcontext][propput][id] */ HRESULT ( __stdcall *put_Z )( 
            _DGMPoint * This,
            /* [in] */ double returnValue);
        
        /* [hidden][restricted][id] */ HRESULT ( __stdcall *GetPoint )( 
            _DGMPoint * This,
            /* [out] */ double *Point);
        
        /* [hidden][restricted][id] */ HRESULT ( __stdcall *SetPoint )( 
            _DGMPoint * This,
            /* [in] */ double *Point);
        
        END_INTERFACE
    } _DGMPointVtbl;

    interface _DGMPoint
    {
        CONST_VTBL struct _DGMPointVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DGMPoint_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DGMPoint_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DGMPoint_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DGMPoint_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DGMPoint_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DGMPoint_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DGMPoint_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define _DGMPoint_get_X(This,returnValue)	\
    (This)->lpVtbl -> get_X(This,returnValue)

#define _DGMPoint_put_X(This,returnValue)	\
    (This)->lpVtbl -> put_X(This,returnValue)

#define _DGMPoint_get_Y(This,returnValue)	\
    (This)->lpVtbl -> get_Y(This,returnValue)

#define _DGMPoint_put_Y(This,returnValue)	\
    (This)->lpVtbl -> put_Y(This,returnValue)

#define _DGMPoint_get_Z(This,returnValue)	\
    (This)->lpVtbl -> get_Z(This,returnValue)

#define _DGMPoint_put_Z(This,returnValue)	\
    (This)->lpVtbl -> put_Z(This,returnValue)

#define _DGMPoint_GetPoint(This,Point)	\
    (This)->lpVtbl -> GetPoint(This,Point)

#define _DGMPoint_SetPoint(This,Point)	\
    (This)->lpVtbl -> SetPoint(This,Point)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT __stdcall _DGMPoint_get_X_Proxy( 
    _DGMPoint * This,
    /* [retval][out] */ double *returnValue);


void __RPC_STUB _DGMPoint_get_X_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT __stdcall _DGMPoint_put_X_Proxy( 
    _DGMPoint * This,
    /* [in] */ double returnValue);


void __RPC_STUB _DGMPoint_put_X_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT __stdcall _DGMPoint_get_Y_Proxy( 
    _DGMPoint * This,
    /* [retval][out] */ double *returnValue);


void __RPC_STUB _DGMPoint_get_Y_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT __stdcall _DGMPoint_put_Y_Proxy( 
    _DGMPoint * This,
    /* [in] */ double returnValue);


void __RPC_STUB _DGMPoint_put_Y_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT __stdcall _DGMPoint_get_Z_Proxy( 
    _DGMPoint * This,
    /* [retval][out] */ double *returnValue);


void __RPC_STUB _DGMPoint_get_Z_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT __stdcall _DGMPoint_put_Z_Proxy( 
    _DGMPoint * This,
    /* [in] */ double returnValue);


void __RPC_STUB _DGMPoint_put_Z_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][restricted][id] */ HRESULT __stdcall _DGMPoint_GetPoint_Proxy( 
    _DGMPoint * This,
    /* [out] */ double *Point);


void __RPC_STUB _DGMPoint_GetPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][restricted][id] */ HRESULT __stdcall _DGMPoint_SetPoint_Proxy( 
    _DGMPoint * This,
    /* [in] */ double *Point);


void __RPC_STUB _DGMPoint_SetPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___DGMPoint_INTERFACE_DEFINED__ */


#ifndef ___DGMPoints_INTERFACE_DEFINED__
#define ___DGMPoints_INTERFACE_DEFINED__

/* interface _DGMPoints */
/* [object][local][oleautomation][nonextensible][dual][hidden][uuid] */ 


EXTERN_C const IID IID__DGMPoints;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4DBFC540-B33E-11CF-ABEF-08003601B769")
    _DGMPoints : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT __stdcall get_Count( 
            /* [retval][out] */ long *returnValue) = 0;
        
        virtual /* [hidden][restricted][propget][id] */ HRESULT __stdcall get_NewEnum( 
            /* [retval][out] */ IUnknown **returnValue) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT __stdcall Item( 
            /* [in] */ VARIANT index,
            /* [retval][out] */ _DGMPoint **returnValue) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT __stdcall Add( 
            /* [in] */ _DGMPoint *Point,
            /* [optional][in] */ VARIANT index) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT __stdcall Remove( 
            /* [in] */ VARIANT index) = 0;
        
        virtual /* [hidden][restricted][id] */ HRESULT __stdcall GetPoint( 
            /* [in] */ long index,
            /* [out] */ double *Point) = 0;
        
        virtual /* [hidden][restricted][id] */ HRESULT __stdcall SetPoint( 
            /* [in] */ long index,
            /* [in] */ double *Point) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _DGMPointsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DGMPoints * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DGMPoints * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DGMPoints * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DGMPoints * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DGMPoints * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DGMPoints * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DGMPoints * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( __stdcall *get_Count )( 
            _DGMPoints * This,
            /* [retval][out] */ long *returnValue);
        
        /* [hidden][restricted][propget][id] */ HRESULT ( __stdcall *get_NewEnum )( 
            _DGMPoints * This,
            /* [retval][out] */ IUnknown **returnValue);
        
        /* [helpcontext][id] */ HRESULT ( __stdcall *Item )( 
            _DGMPoints * This,
            /* [in] */ VARIANT index,
            /* [retval][out] */ _DGMPoint **returnValue);
        
        /* [helpcontext][id] */ HRESULT ( __stdcall *Add )( 
            _DGMPoints * This,
            /* [in] */ _DGMPoint *Point,
            /* [optional][in] */ VARIANT index);
        
        /* [helpcontext][id] */ HRESULT ( __stdcall *Remove )( 
            _DGMPoints * This,
            /* [in] */ VARIANT index);
        
        /* [hidden][restricted][id] */ HRESULT ( __stdcall *GetPoint )( 
            _DGMPoints * This,
            /* [in] */ long index,
            /* [out] */ double *Point);
        
        /* [hidden][restricted][id] */ HRESULT ( __stdcall *SetPoint )( 
            _DGMPoints * This,
            /* [in] */ long index,
            /* [in] */ double *Point);
        
        END_INTERFACE
    } _DGMPointsVtbl;

    interface _DGMPoints
    {
        CONST_VTBL struct _DGMPointsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DGMPoints_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DGMPoints_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DGMPoints_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DGMPoints_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DGMPoints_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DGMPoints_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DGMPoints_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define _DGMPoints_get_Count(This,returnValue)	\
    (This)->lpVtbl -> get_Count(This,returnValue)

#define _DGMPoints_get_NewEnum(This,returnValue)	\
    (This)->lpVtbl -> get_NewEnum(This,returnValue)

#define _DGMPoints_Item(This,index,returnValue)	\
    (This)->lpVtbl -> Item(This,index,returnValue)

#define _DGMPoints_Add(This,Point,index)	\
    (This)->lpVtbl -> Add(This,Point,index)

#define _DGMPoints_Remove(This,index)	\
    (This)->lpVtbl -> Remove(This,index)

#define _DGMPoints_GetPoint(This,index,Point)	\
    (This)->lpVtbl -> GetPoint(This,index,Point)

#define _DGMPoints_SetPoint(This,index,Point)	\
    (This)->lpVtbl -> SetPoint(This,index,Point)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT __stdcall _DGMPoints_get_Count_Proxy( 
    _DGMPoints * This,
    /* [retval][out] */ long *returnValue);


void __RPC_STUB _DGMPoints_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][restricted][propget][id] */ HRESULT __stdcall _DGMPoints_get_NewEnum_Proxy( 
    _DGMPoints * This,
    /* [retval][out] */ IUnknown **returnValue);


void __RPC_STUB _DGMPoints_get_NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT __stdcall _DGMPoints_Item_Proxy( 
    _DGMPoints * This,
    /* [in] */ VARIANT index,
    /* [retval][out] */ _DGMPoint **returnValue);


void __RPC_STUB _DGMPoints_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT __stdcall _DGMPoints_Add_Proxy( 
    _DGMPoints * This,
    /* [in] */ _DGMPoint *Point,
    /* [optional][in] */ VARIANT index);


void __RPC_STUB _DGMPoints_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT __stdcall _DGMPoints_Remove_Proxy( 
    _DGMPoints * This,
    /* [in] */ VARIANT index);


void __RPC_STUB _DGMPoints_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][restricted][id] */ HRESULT __stdcall _DGMPoints_GetPoint_Proxy( 
    _DGMPoints * This,
    /* [in] */ long index,
    /* [out] */ double *Point);


void __RPC_STUB _DGMPoints_GetPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][restricted][id] */ HRESULT __stdcall _DGMPoints_SetPoint_Proxy( 
    _DGMPoints * This,
    /* [in] */ long index,
    /* [in] */ double *Point);


void __RPC_STUB _DGMPoints_SetPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___DGMPoints_INTERFACE_DEFINED__ */


#ifndef __ICoordTransform_INTERFACE_DEFINED__
#define __ICoordTransform_INTERFACE_DEFINED__

/* interface ICoordTransform */
/* [unique][helpstring][dual][uuid][object] */ 

typedef /* [public] */ 
enum _tagTRANSDIRECTION
    {	TRANSDIRECTION_FORWARD	= 0,
	TRANSDIRECTION_INVERSE	= 1,
	TRANSDIRECTION_IGNORED	= 2
    } 	TRANSDIRECTION;


EXTERN_C const IID IID_ICoordTransform;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0BDC3C18-503F-11D1-96F0-00A024D6F582")
    ICoordTransform : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AspectRatio( 
            /* [in] */ _DGMPoint *Point1,
            /* [in] */ _DGMPoint *Point2,
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsMetric( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CanConfig( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Transform( 
            /* [in] */ _DGMPoint *Point,
            TRANSDIRECTION Dir) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TransformColl( 
            /* [in] */ _DGMPoints *Points,
            TRANSDIRECTION Dir) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TransformEx( 
            /* [in] */ _DGMPoint *Point,
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IDispatch *Param) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TransformCollEx( 
            /* [in] */ _DGMPoints *Points,
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IDispatch *Param) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Native( 
            /* [in] */ _DGMPoint *Point,
            TRANSDIRECTION Dir) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NativeColl( 
            /* [in] */ _DGMPoints *Points,
            TRANSDIRECTION Dir) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NativeEx( 
            /* [in] */ _DGMPoint *Point,
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IDispatch *Param) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NativeCollEx( 
            /* [in] */ _DGMPoints *Points,
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IDispatch *Param) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TransformParameter( 
            /* [in] */ _DGMPoint *Point,
            /* [in] */ TRANSDIRECTION Dir,
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FreeTransformParameter( 
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IDispatch *pDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NativeParameter( 
            /* [in] */ _DGMPoint *Point,
            /* [in] */ TRANSDIRECTION Dir,
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FreeNativeParameter( 
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IDispatch *pIDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Distance( 
            /* [in] */ _DGMPoint *Point1,
            /* [in] */ _DGMPoint *Point2,
            /* [retval][out] */ _DGMPoint **pDist) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DistancePoint( 
            /* [in] */ _DGMPoint *Point,
            /* [in] */ _DGMPoint *Delta,
            /* [retval][out] */ _DGMPoint **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ToStrings( 
            /* [in] */ _DGMPoint *Point,
            /* [out] */ BSTR *XStr,
            /* [out] */ BSTR *YStr,
            /* [out] */ BSTR *ZStr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ToPoint( 
            /* [in] */ BSTR XStr,
            /* [in] */ BSTR YStr,
            /* [in] */ BSTR ZStr,
            /* [retval][out] */ _DGMPoint **Point) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Envelope( 
            /* [retval][out] */ IDispatch **Rect) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DistanceEx( 
            /* [in] */ _DGMPoint *Point1,
            /* [in] */ _DGMPoint *Point2,
            /* [out] */ _DGMPoint **pDist,
            /* [retval][out] */ double *Dist) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TransformEx2( 
            /* [in] */ _DGMPoint *Point,
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IUnknown *pICS) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TransformCollEx2( 
            /* [in] */ _DGMPoints *Points,
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IUnknown *pICS) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CoordTransformPipe( 
            /* [retval][out] */ IDispatch **CoordTransPipe) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICoordTransformVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICoordTransform * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICoordTransform * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICoordTransform * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICoordTransform * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICoordTransform * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICoordTransform * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICoordTransform * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            ICoordTransform * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AspectRatio )( 
            ICoordTransform * This,
            /* [in] */ _DGMPoint *Point1,
            /* [in] */ _DGMPoint *Point2,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsMetric )( 
            ICoordTransform * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CanConfig )( 
            ICoordTransform * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Transform )( 
            ICoordTransform * This,
            /* [in] */ _DGMPoint *Point,
            TRANSDIRECTION Dir);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *TransformColl )( 
            ICoordTransform * This,
            /* [in] */ _DGMPoints *Points,
            TRANSDIRECTION Dir);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *TransformEx )( 
            ICoordTransform * This,
            /* [in] */ _DGMPoint *Point,
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IDispatch *Param);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *TransformCollEx )( 
            ICoordTransform * This,
            /* [in] */ _DGMPoints *Points,
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IDispatch *Param);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Native )( 
            ICoordTransform * This,
            /* [in] */ _DGMPoint *Point,
            TRANSDIRECTION Dir);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NativeColl )( 
            ICoordTransform * This,
            /* [in] */ _DGMPoints *Points,
            TRANSDIRECTION Dir);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NativeEx )( 
            ICoordTransform * This,
            /* [in] */ _DGMPoint *Point,
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IDispatch *Param);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NativeCollEx )( 
            ICoordTransform * This,
            /* [in] */ _DGMPoints *Points,
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IDispatch *Param);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *TransformParameter )( 
            ICoordTransform * This,
            /* [in] */ _DGMPoint *Point,
            /* [in] */ TRANSDIRECTION Dir,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FreeTransformParameter )( 
            ICoordTransform * This,
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IDispatch *pDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NativeParameter )( 
            ICoordTransform * This,
            /* [in] */ _DGMPoint *Point,
            /* [in] */ TRANSDIRECTION Dir,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FreeNativeParameter )( 
            ICoordTransform * This,
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IDispatch *pIDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Distance )( 
            ICoordTransform * This,
            /* [in] */ _DGMPoint *Point1,
            /* [in] */ _DGMPoint *Point2,
            /* [retval][out] */ _DGMPoint **pDist);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DistancePoint )( 
            ICoordTransform * This,
            /* [in] */ _DGMPoint *Point,
            /* [in] */ _DGMPoint *Delta,
            /* [retval][out] */ _DGMPoint **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ToStrings )( 
            ICoordTransform * This,
            /* [in] */ _DGMPoint *Point,
            /* [out] */ BSTR *XStr,
            /* [out] */ BSTR *YStr,
            /* [out] */ BSTR *ZStr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ToPoint )( 
            ICoordTransform * This,
            /* [in] */ BSTR XStr,
            /* [in] */ BSTR YStr,
            /* [in] */ BSTR ZStr,
            /* [retval][out] */ _DGMPoint **Point);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Envelope )( 
            ICoordTransform * This,
            /* [retval][out] */ IDispatch **Rect);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DistanceEx )( 
            ICoordTransform * This,
            /* [in] */ _DGMPoint *Point1,
            /* [in] */ _DGMPoint *Point2,
            /* [out] */ _DGMPoint **pDist,
            /* [retval][out] */ double *Dist);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *TransformEx2 )( 
            ICoordTransform * This,
            /* [in] */ _DGMPoint *Point,
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IUnknown *pICS);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *TransformCollEx2 )( 
            ICoordTransform * This,
            /* [in] */ _DGMPoints *Points,
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IUnknown *pICS);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CoordTransformPipe )( 
            ICoordTransform * This,
            /* [retval][out] */ IDispatch **CoordTransPipe);
        
        END_INTERFACE
    } ICoordTransformVtbl;

    interface ICoordTransform
    {
        CONST_VTBL struct ICoordTransformVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICoordTransform_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICoordTransform_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICoordTransform_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICoordTransform_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICoordTransform_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICoordTransform_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICoordTransform_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICoordTransform_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#define ICoordTransform_get_AspectRatio(This,Point1,Point2,pVal)	\
    (This)->lpVtbl -> get_AspectRatio(This,Point1,Point2,pVal)

#define ICoordTransform_get_IsMetric(This,pVal)	\
    (This)->lpVtbl -> get_IsMetric(This,pVal)

#define ICoordTransform_get_CanConfig(This,pVal)	\
    (This)->lpVtbl -> get_CanConfig(This,pVal)

#define ICoordTransform_Transform(This,Point,Dir)	\
    (This)->lpVtbl -> Transform(This,Point,Dir)

#define ICoordTransform_TransformColl(This,Points,Dir)	\
    (This)->lpVtbl -> TransformColl(This,Points,Dir)

#define ICoordTransform_TransformEx(This,Point,Dir,Param)	\
    (This)->lpVtbl -> TransformEx(This,Point,Dir,Param)

#define ICoordTransform_TransformCollEx(This,Points,Dir,Param)	\
    (This)->lpVtbl -> TransformCollEx(This,Points,Dir,Param)

#define ICoordTransform_Native(This,Point,Dir)	\
    (This)->lpVtbl -> Native(This,Point,Dir)

#define ICoordTransform_NativeColl(This,Points,Dir)	\
    (This)->lpVtbl -> NativeColl(This,Points,Dir)

#define ICoordTransform_NativeEx(This,Point,Dir,Param)	\
    (This)->lpVtbl -> NativeEx(This,Point,Dir,Param)

#define ICoordTransform_NativeCollEx(This,Points,Dir,Param)	\
    (This)->lpVtbl -> NativeCollEx(This,Points,Dir,Param)

#define ICoordTransform_TransformParameter(This,Point,Dir,pVal)	\
    (This)->lpVtbl -> TransformParameter(This,Point,Dir,pVal)

#define ICoordTransform_FreeTransformParameter(This,Dir,pDisp)	\
    (This)->lpVtbl -> FreeTransformParameter(This,Dir,pDisp)

#define ICoordTransform_NativeParameter(This,Point,Dir,pVal)	\
    (This)->lpVtbl -> NativeParameter(This,Point,Dir,pVal)

#define ICoordTransform_FreeNativeParameter(This,Dir,pIDisp)	\
    (This)->lpVtbl -> FreeNativeParameter(This,Dir,pIDisp)

#define ICoordTransform_Distance(This,Point1,Point2,pDist)	\
    (This)->lpVtbl -> Distance(This,Point1,Point2,pDist)

#define ICoordTransform_DistancePoint(This,Point,Delta,pVal)	\
    (This)->lpVtbl -> DistancePoint(This,Point,Delta,pVal)

#define ICoordTransform_ToStrings(This,Point,XStr,YStr,ZStr)	\
    (This)->lpVtbl -> ToStrings(This,Point,XStr,YStr,ZStr)

#define ICoordTransform_ToPoint(This,XStr,YStr,ZStr,Point)	\
    (This)->lpVtbl -> ToPoint(This,XStr,YStr,ZStr,Point)

#define ICoordTransform_get_Envelope(This,Rect)	\
    (This)->lpVtbl -> get_Envelope(This,Rect)

#define ICoordTransform_DistanceEx(This,Point1,Point2,pDist,Dist)	\
    (This)->lpVtbl -> DistanceEx(This,Point1,Point2,pDist,Dist)

#define ICoordTransform_TransformEx2(This,Point,Dir,pICS)	\
    (This)->lpVtbl -> TransformEx2(This,Point,Dir,pICS)

#define ICoordTransform_TransformCollEx2(This,Points,Dir,pICS)	\
    (This)->lpVtbl -> TransformCollEx2(This,Points,Dir,pICS)

#define ICoordTransform_get_CoordTransformPipe(This,CoordTransPipe)	\
    (This)->lpVtbl -> get_CoordTransformPipe(This,CoordTransPipe)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICoordTransform_get_Description_Proxy( 
    ICoordTransform * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ICoordTransform_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICoordTransform_get_AspectRatio_Proxy( 
    ICoordTransform * This,
    /* [in] */ _DGMPoint *Point1,
    /* [in] */ _DGMPoint *Point2,
    /* [retval][out] */ double *pVal);


void __RPC_STUB ICoordTransform_get_AspectRatio_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICoordTransform_get_IsMetric_Proxy( 
    ICoordTransform * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ICoordTransform_get_IsMetric_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICoordTransform_get_CanConfig_Proxy( 
    ICoordTransform * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ICoordTransform_get_CanConfig_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_Transform_Proxy( 
    ICoordTransform * This,
    /* [in] */ _DGMPoint *Point,
    TRANSDIRECTION Dir);


void __RPC_STUB ICoordTransform_Transform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_TransformColl_Proxy( 
    ICoordTransform * This,
    /* [in] */ _DGMPoints *Points,
    TRANSDIRECTION Dir);


void __RPC_STUB ICoordTransform_TransformColl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_TransformEx_Proxy( 
    ICoordTransform * This,
    /* [in] */ _DGMPoint *Point,
    /* [in] */ TRANSDIRECTION Dir,
    /* [in] */ IDispatch *Param);


void __RPC_STUB ICoordTransform_TransformEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_TransformCollEx_Proxy( 
    ICoordTransform * This,
    /* [in] */ _DGMPoints *Points,
    /* [in] */ TRANSDIRECTION Dir,
    /* [in] */ IDispatch *Param);


void __RPC_STUB ICoordTransform_TransformCollEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_Native_Proxy( 
    ICoordTransform * This,
    /* [in] */ _DGMPoint *Point,
    TRANSDIRECTION Dir);


void __RPC_STUB ICoordTransform_Native_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_NativeColl_Proxy( 
    ICoordTransform * This,
    /* [in] */ _DGMPoints *Points,
    TRANSDIRECTION Dir);


void __RPC_STUB ICoordTransform_NativeColl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_NativeEx_Proxy( 
    ICoordTransform * This,
    /* [in] */ _DGMPoint *Point,
    /* [in] */ TRANSDIRECTION Dir,
    /* [in] */ IDispatch *Param);


void __RPC_STUB ICoordTransform_NativeEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_NativeCollEx_Proxy( 
    ICoordTransform * This,
    /* [in] */ _DGMPoints *Points,
    /* [in] */ TRANSDIRECTION Dir,
    /* [in] */ IDispatch *Param);


void __RPC_STUB ICoordTransform_NativeCollEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_TransformParameter_Proxy( 
    ICoordTransform * This,
    /* [in] */ _DGMPoint *Point,
    /* [in] */ TRANSDIRECTION Dir,
    /* [retval][out] */ IDispatch **pVal);


void __RPC_STUB ICoordTransform_TransformParameter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_FreeTransformParameter_Proxy( 
    ICoordTransform * This,
    /* [in] */ TRANSDIRECTION Dir,
    /* [in] */ IDispatch *pDisp);


void __RPC_STUB ICoordTransform_FreeTransformParameter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_NativeParameter_Proxy( 
    ICoordTransform * This,
    /* [in] */ _DGMPoint *Point,
    /* [in] */ TRANSDIRECTION Dir,
    /* [retval][out] */ IDispatch **pVal);


void __RPC_STUB ICoordTransform_NativeParameter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_FreeNativeParameter_Proxy( 
    ICoordTransform * This,
    /* [in] */ TRANSDIRECTION Dir,
    /* [in] */ IDispatch *pIDisp);


void __RPC_STUB ICoordTransform_FreeNativeParameter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_Distance_Proxy( 
    ICoordTransform * This,
    /* [in] */ _DGMPoint *Point1,
    /* [in] */ _DGMPoint *Point2,
    /* [retval][out] */ _DGMPoint **pDist);


void __RPC_STUB ICoordTransform_Distance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_DistancePoint_Proxy( 
    ICoordTransform * This,
    /* [in] */ _DGMPoint *Point,
    /* [in] */ _DGMPoint *Delta,
    /* [retval][out] */ _DGMPoint **pVal);


void __RPC_STUB ICoordTransform_DistancePoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_ToStrings_Proxy( 
    ICoordTransform * This,
    /* [in] */ _DGMPoint *Point,
    /* [out] */ BSTR *XStr,
    /* [out] */ BSTR *YStr,
    /* [out] */ BSTR *ZStr);


void __RPC_STUB ICoordTransform_ToStrings_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_ToPoint_Proxy( 
    ICoordTransform * This,
    /* [in] */ BSTR XStr,
    /* [in] */ BSTR YStr,
    /* [in] */ BSTR ZStr,
    /* [retval][out] */ _DGMPoint **Point);


void __RPC_STUB ICoordTransform_ToPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICoordTransform_get_Envelope_Proxy( 
    ICoordTransform * This,
    /* [retval][out] */ IDispatch **Rect);


void __RPC_STUB ICoordTransform_get_Envelope_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_DistanceEx_Proxy( 
    ICoordTransform * This,
    /* [in] */ _DGMPoint *Point1,
    /* [in] */ _DGMPoint *Point2,
    /* [out] */ _DGMPoint **pDist,
    /* [retval][out] */ double *Dist);


void __RPC_STUB ICoordTransform_DistanceEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_TransformEx2_Proxy( 
    ICoordTransform * This,
    /* [in] */ _DGMPoint *Point,
    /* [in] */ TRANSDIRECTION Dir,
    /* [in] */ IUnknown *pICS);


void __RPC_STUB ICoordTransform_TransformEx2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_TransformCollEx2_Proxy( 
    ICoordTransform * This,
    /* [in] */ _DGMPoints *Points,
    /* [in] */ TRANSDIRECTION Dir,
    /* [in] */ IUnknown *pICS);


void __RPC_STUB ICoordTransform_TransformCollEx2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICoordTransform_get_CoordTransformPipe_Proxy( 
    ICoordTransform * This,
    /* [retval][out] */ IDispatch **CoordTransPipe);


void __RPC_STUB ICoordTransform_get_CoordTransformPipe_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICoordTransform_INTERFACE_DEFINED__ */


#ifndef __ICoordTransformInit_INTERFACE_DEFINED__
#define __ICoordTransformInit_INTERFACE_DEFINED__

/* interface ICoordTransformInit */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ICoordTransformInit;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0BDC3C1B-503F-11d1-96F0-00A024D6F582")
    ICoordTransformInit : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InitCoordTransform( 
            IUnknown *Props) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReInitCoordTransform( 
            IUnknown *Props) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TermCoordTransform( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICoordTransformInitVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICoordTransformInit * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICoordTransformInit * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICoordTransformInit * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *InitCoordTransform )( 
            ICoordTransformInit * This,
            IUnknown *Props);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ReInitCoordTransform )( 
            ICoordTransformInit * This,
            IUnknown *Props);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TermCoordTransform )( 
            ICoordTransformInit * This);
        
        END_INTERFACE
    } ICoordTransformInitVtbl;

    interface ICoordTransformInit
    {
        CONST_VTBL struct ICoordTransformInitVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICoordTransformInit_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICoordTransformInit_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICoordTransformInit_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICoordTransformInit_InitCoordTransform(This,Props)	\
    (This)->lpVtbl -> InitCoordTransform(This,Props)

#define ICoordTransformInit_ReInitCoordTransform(This,Props)	\
    (This)->lpVtbl -> ReInitCoordTransform(This,Props)

#define ICoordTransformInit_TermCoordTransform(This)	\
    (This)->lpVtbl -> TermCoordTransform(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICoordTransformInit_InitCoordTransform_Proxy( 
    ICoordTransformInit * This,
    IUnknown *Props);


void __RPC_STUB ICoordTransformInit_InitCoordTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICoordTransformInit_ReInitCoordTransform_Proxy( 
    ICoordTransformInit * This,
    IUnknown *Props);


void __RPC_STUB ICoordTransformInit_ReInitCoordTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICoordTransformInit_TermCoordTransform_Proxy( 
    ICoordTransformInit * This);


void __RPC_STUB ICoordTransformInit_TermCoordTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICoordTransformInit_INTERFACE_DEFINED__ */


#ifndef __ICTFExContext_INTERFACE_DEFINED__
#define __ICTFExContext_INTERFACE_DEFINED__

/* interface ICTFExContext */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICTFExContext;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5FA91F05-A839-11D1-A060-0060975566B4")
    ICTFExContext : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Meridian( 
            /* [retval][out] */ int *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Meridian( 
            /* [in] */ int newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICTFExContextVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICTFExContext * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICTFExContext * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICTFExContext * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICTFExContext * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICTFExContext * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICTFExContext * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICTFExContext * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            ICTFExContext * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Meridian )( 
            ICTFExContext * This,
            /* [retval][out] */ int *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Meridian )( 
            ICTFExContext * This,
            /* [in] */ int newVal);
        
        END_INTERFACE
    } ICTFExContextVtbl;

    interface ICTFExContext
    {
        CONST_VTBL struct ICTFExContextVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICTFExContext_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICTFExContext_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICTFExContext_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICTFExContext_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICTFExContext_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICTFExContext_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICTFExContext_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICTFExContext_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#define ICTFExContext_get_Meridian(This,pVal)	\
    (This)->lpVtbl -> get_Meridian(This,pVal)

#define ICTFExContext_put_Meridian(This,newVal)	\
    (This)->lpVtbl -> put_Meridian(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICTFExContext_get_Description_Proxy( 
    ICTFExContext * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ICTFExContext_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICTFExContext_get_Meridian_Proxy( 
    ICTFExContext * This,
    /* [retval][out] */ int *pVal);


void __RPC_STUB ICTFExContext_get_Meridian_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICTFExContext_put_Meridian_Proxy( 
    ICTFExContext * This,
    /* [in] */ int newVal);


void __RPC_STUB ICTFExContext_put_Meridian_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICTFExContext_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_CTF_0257 */
/* [local] */ 

#pragma once



extern RPC_IF_HANDLE __MIDL_itf_CTF_0257_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_CTF_0257_v0_0_s_ifspec;

#ifndef __ICoordTransformEvents_INTERFACE_DEFINED__
#define __ICoordTransformEvents_INTERFACE_DEFINED__

/* interface ICoordTransformEvents */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ICoordTransformEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("764CA444-DFF6-11D1-8608-00600875138A")
    ICoordTransformEvents : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CoordParamsToChange( 
            /* [in] */ IDispatch *pICoordSys,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ChangingCoordParams( 
            /* [in] */ IDispatch *pICoordSys) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ChangedCoordParams( 
            /* [in] */ IDispatch *pICoordSys) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICoordTransformEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICoordTransformEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICoordTransformEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICoordTransformEvents * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CoordParamsToChange )( 
            ICoordTransformEvents * This,
            /* [in] */ IDispatch *pICoordSys,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ChangingCoordParams )( 
            ICoordTransformEvents * This,
            /* [in] */ IDispatch *pICoordSys);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ChangedCoordParams )( 
            ICoordTransformEvents * This,
            /* [in] */ IDispatch *pICoordSys);
        
        END_INTERFACE
    } ICoordTransformEventsVtbl;

    interface ICoordTransformEvents
    {
        CONST_VTBL struct ICoordTransformEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICoordTransformEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICoordTransformEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICoordTransformEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICoordTransformEvents_CoordParamsToChange(This,pICoordSys,pVal)	\
    (This)->lpVtbl -> CoordParamsToChange(This,pICoordSys,pVal)

#define ICoordTransformEvents_ChangingCoordParams(This,pICoordSys)	\
    (This)->lpVtbl -> ChangingCoordParams(This,pICoordSys)

#define ICoordTransformEvents_ChangedCoordParams(This,pICoordSys)	\
    (This)->lpVtbl -> ChangedCoordParams(This,pICoordSys)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransformEvents_CoordParamsToChange_Proxy( 
    ICoordTransformEvents * This,
    /* [in] */ IDispatch *pICoordSys,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ICoordTransformEvents_CoordParamsToChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransformEvents_ChangingCoordParams_Proxy( 
    ICoordTransformEvents * This,
    /* [in] */ IDispatch *pICoordSys);


void __RPC_STUB ICoordTransformEvents_ChangingCoordParams_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransformEvents_ChangedCoordParams_Proxy( 
    ICoordTransformEvents * This,
    /* [in] */ IDispatch *pICoordSys);


void __RPC_STUB ICoordTransformEvents_ChangedCoordParams_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICoordTransformEvents_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_CTF_0258 */
/* [local] */ 

#define TYPELIB_CTF_VERSION_MAJOR 1
#define TYPELIB_CTF_VERSION_MINOR 0
#define TYPELIB_CTF_VERSION "1.0"
#define TYPELIB_CTF_LCID 0


extern RPC_IF_HANDLE __MIDL_itf_CTF_0258_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_CTF_0258_v0_0_s_ifspec;


#ifndef __CoordTransLib_LIBRARY_DEFINED__
#define __CoordTransLib_LIBRARY_DEFINED__

/* library CoordTransLib */
/* [helpstring][lcid][version][uuid] */ 


EXTERN_C const IID LIBID_CoordTransLib;

EXTERN_C const CLSID CLSID_DefaultCoordTrans;

#ifdef __cplusplus

class DECLSPEC_UUID("0BDC3C19-503F-11D1-96F0-00A024D6F582")
DefaultCoordTrans;
#endif

EXTERN_C const CLSID CLSID_ManageCoordParam;

#ifdef __cplusplus

class DECLSPEC_UUID("95F58F37-DF2C-11D1-8606-00600875138A")
ManageCoordParam;
#endif
#endif /* __CoordTransLib_LIBRARY_DEFINED__ */

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


