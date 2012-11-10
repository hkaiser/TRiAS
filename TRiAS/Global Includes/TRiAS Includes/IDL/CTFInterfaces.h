/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.76 */
/* at Tue May 05 20:39:08 1998
 */
/* Compiler settings for CTFInterfaces.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"
#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __CTFInterfaces_h__
#define __CTFInterfaces_h__

#ifdef __cplusplus
extern "C"{
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


/* header files for imported files */
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_CTFInterfaces_0000
 * at Tue May 05 20:39:08 1998
 * using MIDL 3.01.76
 ****************************************/
/* [local] */ 


#pragma once





extern RPC_IF_HANDLE __MIDL_itf_CTFInterfaces_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_CTFInterfaces_0000_v0_0_s_ifspec;

#ifndef ___DGMPoint_INTERFACE_DEFINED__
#define ___DGMPoint_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: _DGMPoint
 * at Tue May 05 20:39:08 1998
 * using MIDL 3.01.76
 ****************************************/
/* [object][local][oleautomation][nonextensible][dual][hidden][uuid] */ 



EXTERN_C const IID IID__DGMPoint;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("CE361C90-B00C-11CF-ABEF-08003601B769")
    _DGMPoint : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT __stdcall get_X( 
            /* [retval][out] */ double __RPC_FAR *returnValue) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT __stdcall put_X( 
            /* [in] */ double returnValue) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT __stdcall get_Y( 
            /* [retval][out] */ double __RPC_FAR *returnValue) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT __stdcall put_Y( 
            /* [in] */ double returnValue) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT __stdcall get_Z( 
            /* [retval][out] */ double __RPC_FAR *returnValue) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT __stdcall put_Z( 
            /* [in] */ double returnValue) = 0;
        
        virtual /* [hidden][restricted][id] */ HRESULT __stdcall GetPoint( 
            /* [out] */ double __RPC_FAR *Point) = 0;
        
        virtual /* [hidden][restricted][id] */ HRESULT __stdcall SetPoint( 
            /* [in] */ double __RPC_FAR *Point) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _DGMPointVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _DGMPoint __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _DGMPoint __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _DGMPoint __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _DGMPoint __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _DGMPoint __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _DGMPoint __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _DGMPoint __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( __stdcall __RPC_FAR *get_X )( 
            _DGMPoint __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *returnValue);
        
        /* [helpcontext][propput][id] */ HRESULT ( __stdcall __RPC_FAR *put_X )( 
            _DGMPoint __RPC_FAR * This,
            /* [in] */ double returnValue);
        
        /* [helpcontext][propget][id] */ HRESULT ( __stdcall __RPC_FAR *get_Y )( 
            _DGMPoint __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *returnValue);
        
        /* [helpcontext][propput][id] */ HRESULT ( __stdcall __RPC_FAR *put_Y )( 
            _DGMPoint __RPC_FAR * This,
            /* [in] */ double returnValue);
        
        /* [helpcontext][propget][id] */ HRESULT ( __stdcall __RPC_FAR *get_Z )( 
            _DGMPoint __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *returnValue);
        
        /* [helpcontext][propput][id] */ HRESULT ( __stdcall __RPC_FAR *put_Z )( 
            _DGMPoint __RPC_FAR * This,
            /* [in] */ double returnValue);
        
        /* [hidden][restricted][id] */ HRESULT ( __stdcall __RPC_FAR *GetPoint )( 
            _DGMPoint __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *Point);
        
        /* [hidden][restricted][id] */ HRESULT ( __stdcall __RPC_FAR *SetPoint )( 
            _DGMPoint __RPC_FAR * This,
            /* [in] */ double __RPC_FAR *Point);
        
        END_INTERFACE
    } _DGMPointVtbl;

    interface _DGMPoint
    {
        CONST_VTBL struct _DGMPointVtbl __RPC_FAR *lpVtbl;
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
    _DGMPoint __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *returnValue);


void __RPC_STUB _DGMPoint_get_X_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT __stdcall _DGMPoint_put_X_Proxy( 
    _DGMPoint __RPC_FAR * This,
    /* [in] */ double returnValue);


void __RPC_STUB _DGMPoint_put_X_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT __stdcall _DGMPoint_get_Y_Proxy( 
    _DGMPoint __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *returnValue);


void __RPC_STUB _DGMPoint_get_Y_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT __stdcall _DGMPoint_put_Y_Proxy( 
    _DGMPoint __RPC_FAR * This,
    /* [in] */ double returnValue);


void __RPC_STUB _DGMPoint_put_Y_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT __stdcall _DGMPoint_get_Z_Proxy( 
    _DGMPoint __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *returnValue);


void __RPC_STUB _DGMPoint_get_Z_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT __stdcall _DGMPoint_put_Z_Proxy( 
    _DGMPoint __RPC_FAR * This,
    /* [in] */ double returnValue);


void __RPC_STUB _DGMPoint_put_Z_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][restricted][id] */ HRESULT __stdcall _DGMPoint_GetPoint_Proxy( 
    _DGMPoint __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *Point);


void __RPC_STUB _DGMPoint_GetPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][restricted][id] */ HRESULT __stdcall _DGMPoint_SetPoint_Proxy( 
    _DGMPoint __RPC_FAR * This,
    /* [in] */ double __RPC_FAR *Point);


void __RPC_STUB _DGMPoint_SetPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___DGMPoint_INTERFACE_DEFINED__ */


#ifndef ___DGMPoints_INTERFACE_DEFINED__
#define ___DGMPoints_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: _DGMPoints
 * at Tue May 05 20:39:08 1998
 * using MIDL 3.01.76
 ****************************************/
/* [object][local][oleautomation][nonextensible][dual][hidden][uuid] */ 



EXTERN_C const IID IID__DGMPoints;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("4DBFC540-B33E-11CF-ABEF-08003601B769")
    _DGMPoints : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT __stdcall get_Count( 
            /* [retval][out] */ long __RPC_FAR *returnValue) = 0;
        
        virtual /* [hidden][restricted][propget][id] */ HRESULT __stdcall get_NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *returnValue) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT __stdcall Item( 
            /* [in] */ VARIANT index,
            /* [retval][out] */ _DGMPoint __RPC_FAR *__RPC_FAR *returnValue) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT __stdcall Add( 
            /* [in] */ _DGMPoint __RPC_FAR *Point,
            /* [optional][in] */ VARIANT index) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT __stdcall Remove( 
            /* [in] */ VARIANT index) = 0;
        
        virtual /* [hidden][restricted][id] */ HRESULT __stdcall GetPoint( 
            /* [in] */ long index,
            /* [out] */ double __RPC_FAR *Point) = 0;
        
        virtual /* [hidden][restricted][id] */ HRESULT __stdcall SetPoint( 
            /* [in] */ long index,
            /* [in] */ double __RPC_FAR *Point) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _DGMPointsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _DGMPoints __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _DGMPoints __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _DGMPoints __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _DGMPoints __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _DGMPoints __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _DGMPoints __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _DGMPoints __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( __stdcall __RPC_FAR *get_Count )( 
            _DGMPoints __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *returnValue);
        
        /* [hidden][restricted][propget][id] */ HRESULT ( __stdcall __RPC_FAR *get_NewEnum )( 
            _DGMPoints __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *returnValue);
        
        /* [helpcontext][id] */ HRESULT ( __stdcall __RPC_FAR *Item )( 
            _DGMPoints __RPC_FAR * This,
            /* [in] */ VARIANT index,
            /* [retval][out] */ _DGMPoint __RPC_FAR *__RPC_FAR *returnValue);
        
        /* [helpcontext][id] */ HRESULT ( __stdcall __RPC_FAR *Add )( 
            _DGMPoints __RPC_FAR * This,
            /* [in] */ _DGMPoint __RPC_FAR *Point,
            /* [optional][in] */ VARIANT index);
        
        /* [helpcontext][id] */ HRESULT ( __stdcall __RPC_FAR *Remove )( 
            _DGMPoints __RPC_FAR * This,
            /* [in] */ VARIANT index);
        
        /* [hidden][restricted][id] */ HRESULT ( __stdcall __RPC_FAR *GetPoint )( 
            _DGMPoints __RPC_FAR * This,
            /* [in] */ long index,
            /* [out] */ double __RPC_FAR *Point);
        
        /* [hidden][restricted][id] */ HRESULT ( __stdcall __RPC_FAR *SetPoint )( 
            _DGMPoints __RPC_FAR * This,
            /* [in] */ long index,
            /* [in] */ double __RPC_FAR *Point);
        
        END_INTERFACE
    } _DGMPointsVtbl;

    interface _DGMPoints
    {
        CONST_VTBL struct _DGMPointsVtbl __RPC_FAR *lpVtbl;
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
    _DGMPoints __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *returnValue);


void __RPC_STUB _DGMPoints_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][restricted][propget][id] */ HRESULT __stdcall _DGMPoints_get_NewEnum_Proxy( 
    _DGMPoints __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *returnValue);


void __RPC_STUB _DGMPoints_get_NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT __stdcall _DGMPoints_Item_Proxy( 
    _DGMPoints __RPC_FAR * This,
    /* [in] */ VARIANT index,
    /* [retval][out] */ _DGMPoint __RPC_FAR *__RPC_FAR *returnValue);


void __RPC_STUB _DGMPoints_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT __stdcall _DGMPoints_Add_Proxy( 
    _DGMPoints __RPC_FAR * This,
    /* [in] */ _DGMPoint __RPC_FAR *Point,
    /* [optional][in] */ VARIANT index);


void __RPC_STUB _DGMPoints_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT __stdcall _DGMPoints_Remove_Proxy( 
    _DGMPoints __RPC_FAR * This,
    /* [in] */ VARIANT index);


void __RPC_STUB _DGMPoints_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][restricted][id] */ HRESULT __stdcall _DGMPoints_GetPoint_Proxy( 
    _DGMPoints __RPC_FAR * This,
    /* [in] */ long index,
    /* [out] */ double __RPC_FAR *Point);


void __RPC_STUB _DGMPoints_GetPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][restricted][id] */ HRESULT __stdcall _DGMPoints_SetPoint_Proxy( 
    _DGMPoints __RPC_FAR * This,
    /* [in] */ long index,
    /* [in] */ double __RPC_FAR *Point);


void __RPC_STUB _DGMPoints_SetPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___DGMPoints_INTERFACE_DEFINED__ */


#ifndef __ICoordTransform_INTERFACE_DEFINED__
#define __ICoordTransform_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICoordTransform
 * at Tue May 05 20:39:08 1998
 * using MIDL 3.01.76
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 


typedef /* [public] */ 
enum _tagTRANSDIRECTION
    {	TRANSDIRECTION_FORWARD	= 0,
	TRANSDIRECTION_INVERSE	= 1,
	TRANSDIRECTION_IGNORED	= 2
    }	TRANSDIRECTION;


EXTERN_C const IID IID_ICoordTransform;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0BDC3C18-503F-11D1-96F0-00A024D6F582")
    ICoordTransform : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AspectRatio( 
            /* [in] */ _DGMPoint __RPC_FAR *Point1,
            /* [in] */ _DGMPoint __RPC_FAR *Point2,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsMetric( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CanConfig( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Transform( 
            /* [in] */ _DGMPoint __RPC_FAR *Point,
            TRANSDIRECTION Dir) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TransformColl( 
            /* [in] */ _DGMPoints __RPC_FAR *Points,
            TRANSDIRECTION Dir) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TransformEx( 
            /* [in] */ _DGMPoint __RPC_FAR *Point,
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IDispatch __RPC_FAR *Param) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TransformCollEx( 
            /* [in] */ _DGMPoints __RPC_FAR *Points,
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IDispatch __RPC_FAR *Param) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Native( 
            /* [in] */ _DGMPoint __RPC_FAR *Point,
            TRANSDIRECTION Dir) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NativeColl( 
            /* [in] */ _DGMPoints __RPC_FAR *Points,
            TRANSDIRECTION Dir) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NativeEx( 
            /* [in] */ _DGMPoint __RPC_FAR *Point,
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IDispatch __RPC_FAR *Param) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NativeCollEx( 
            /* [in] */ _DGMPoints __RPC_FAR *Points,
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IDispatch __RPC_FAR *Param) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TransformParameter( 
            /* [in] */ _DGMPoint __RPC_FAR *Point,
            /* [in] */ TRANSDIRECTION Dir,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FreeTransformParameter( 
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IDispatch __RPC_FAR *pDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NativeParameter( 
            /* [in] */ _DGMPoint __RPC_FAR *Point,
            /* [in] */ TRANSDIRECTION Dir,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FreeNativeParameter( 
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IDispatch __RPC_FAR *pIDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Distance( 
            /* [in] */ _DGMPoint __RPC_FAR *Point1,
            /* [in] */ _DGMPoint __RPC_FAR *Point2,
            /* [retval][out] */ _DGMPoint __RPC_FAR *__RPC_FAR *pDist) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DistancePoint( 
            /* [in] */ _DGMPoint __RPC_FAR *Point,
            /* [in] */ _DGMPoint __RPC_FAR *Delta,
            /* [retval][out] */ _DGMPoint __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ToStrings( 
            /* [in] */ _DGMPoint __RPC_FAR *Point,
            /* [out] */ BSTR __RPC_FAR *XStr,
            /* [out] */ BSTR __RPC_FAR *YStr,
            /* [out] */ BSTR __RPC_FAR *ZStr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ToPoint( 
            /* [in] */ BSTR XStr,
            /* [in] */ BSTR YStr,
            /* [in] */ BSTR ZStr,
            /* [retval][out] */ _DGMPoint __RPC_FAR *__RPC_FAR *Point) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Container( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Rect) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICoordTransformVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICoordTransform __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICoordTransform __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICoordTransform __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICoordTransform __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICoordTransform __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICoordTransform __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICoordTransform __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Description )( 
            ICoordTransform __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AspectRatio )( 
            ICoordTransform __RPC_FAR * This,
            /* [in] */ _DGMPoint __RPC_FAR *Point1,
            /* [in] */ _DGMPoint __RPC_FAR *Point2,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsMetric )( 
            ICoordTransform __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CanConfig )( 
            ICoordTransform __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Transform )( 
            ICoordTransform __RPC_FAR * This,
            /* [in] */ _DGMPoint __RPC_FAR *Point,
            TRANSDIRECTION Dir);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TransformColl )( 
            ICoordTransform __RPC_FAR * This,
            /* [in] */ _DGMPoints __RPC_FAR *Points,
            TRANSDIRECTION Dir);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TransformEx )( 
            ICoordTransform __RPC_FAR * This,
            /* [in] */ _DGMPoint __RPC_FAR *Point,
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IDispatch __RPC_FAR *Param);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TransformCollEx )( 
            ICoordTransform __RPC_FAR * This,
            /* [in] */ _DGMPoints __RPC_FAR *Points,
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IDispatch __RPC_FAR *Param);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Native )( 
            ICoordTransform __RPC_FAR * This,
            /* [in] */ _DGMPoint __RPC_FAR *Point,
            TRANSDIRECTION Dir);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NativeColl )( 
            ICoordTransform __RPC_FAR * This,
            /* [in] */ _DGMPoints __RPC_FAR *Points,
            TRANSDIRECTION Dir);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NativeEx )( 
            ICoordTransform __RPC_FAR * This,
            /* [in] */ _DGMPoint __RPC_FAR *Point,
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IDispatch __RPC_FAR *Param);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NativeCollEx )( 
            ICoordTransform __RPC_FAR * This,
            /* [in] */ _DGMPoints __RPC_FAR *Points,
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IDispatch __RPC_FAR *Param);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TransformParameter )( 
            ICoordTransform __RPC_FAR * This,
            /* [in] */ _DGMPoint __RPC_FAR *Point,
            /* [in] */ TRANSDIRECTION Dir,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FreeTransformParameter )( 
            ICoordTransform __RPC_FAR * This,
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IDispatch __RPC_FAR *pDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NativeParameter )( 
            ICoordTransform __RPC_FAR * This,
            /* [in] */ _DGMPoint __RPC_FAR *Point,
            /* [in] */ TRANSDIRECTION Dir,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FreeNativeParameter )( 
            ICoordTransform __RPC_FAR * This,
            /* [in] */ TRANSDIRECTION Dir,
            /* [in] */ IDispatch __RPC_FAR *pIDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Distance )( 
            ICoordTransform __RPC_FAR * This,
            /* [in] */ _DGMPoint __RPC_FAR *Point1,
            /* [in] */ _DGMPoint __RPC_FAR *Point2,
            /* [retval][out] */ _DGMPoint __RPC_FAR *__RPC_FAR *pDist);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DistancePoint )( 
            ICoordTransform __RPC_FAR * This,
            /* [in] */ _DGMPoint __RPC_FAR *Point,
            /* [in] */ _DGMPoint __RPC_FAR *Delta,
            /* [retval][out] */ _DGMPoint __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ToStrings )( 
            ICoordTransform __RPC_FAR * This,
            /* [in] */ _DGMPoint __RPC_FAR *Point,
            /* [out] */ BSTR __RPC_FAR *XStr,
            /* [out] */ BSTR __RPC_FAR *YStr,
            /* [out] */ BSTR __RPC_FAR *ZStr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ToPoint )( 
            ICoordTransform __RPC_FAR * This,
            /* [in] */ BSTR XStr,
            /* [in] */ BSTR YStr,
            /* [in] */ BSTR ZStr,
            /* [retval][out] */ _DGMPoint __RPC_FAR *__RPC_FAR *Point);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Container )( 
            ICoordTransform __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Rect);
        
        END_INTERFACE
    } ICoordTransformVtbl;

    interface ICoordTransform
    {
        CONST_VTBL struct ICoordTransformVtbl __RPC_FAR *lpVtbl;
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

#define ICoordTransform_get_Container(This,Rect)	\
    (This)->lpVtbl -> get_Container(This,Rect)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICoordTransform_get_Description_Proxy( 
    ICoordTransform __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ICoordTransform_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICoordTransform_get_AspectRatio_Proxy( 
    ICoordTransform __RPC_FAR * This,
    /* [in] */ _DGMPoint __RPC_FAR *Point1,
    /* [in] */ _DGMPoint __RPC_FAR *Point2,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB ICoordTransform_get_AspectRatio_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICoordTransform_get_IsMetric_Proxy( 
    ICoordTransform __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB ICoordTransform_get_IsMetric_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICoordTransform_get_CanConfig_Proxy( 
    ICoordTransform __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB ICoordTransform_get_CanConfig_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_Transform_Proxy( 
    ICoordTransform __RPC_FAR * This,
    /* [in] */ _DGMPoint __RPC_FAR *Point,
    TRANSDIRECTION Dir);


void __RPC_STUB ICoordTransform_Transform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_TransformColl_Proxy( 
    ICoordTransform __RPC_FAR * This,
    /* [in] */ _DGMPoints __RPC_FAR *Points,
    TRANSDIRECTION Dir);


void __RPC_STUB ICoordTransform_TransformColl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_TransformEx_Proxy( 
    ICoordTransform __RPC_FAR * This,
    /* [in] */ _DGMPoint __RPC_FAR *Point,
    /* [in] */ TRANSDIRECTION Dir,
    /* [in] */ IDispatch __RPC_FAR *Param);


void __RPC_STUB ICoordTransform_TransformEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_TransformCollEx_Proxy( 
    ICoordTransform __RPC_FAR * This,
    /* [in] */ _DGMPoints __RPC_FAR *Points,
    /* [in] */ TRANSDIRECTION Dir,
    /* [in] */ IDispatch __RPC_FAR *Param);


void __RPC_STUB ICoordTransform_TransformCollEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_Native_Proxy( 
    ICoordTransform __RPC_FAR * This,
    /* [in] */ _DGMPoint __RPC_FAR *Point,
    TRANSDIRECTION Dir);


void __RPC_STUB ICoordTransform_Native_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_NativeColl_Proxy( 
    ICoordTransform __RPC_FAR * This,
    /* [in] */ _DGMPoints __RPC_FAR *Points,
    TRANSDIRECTION Dir);


void __RPC_STUB ICoordTransform_NativeColl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_NativeEx_Proxy( 
    ICoordTransform __RPC_FAR * This,
    /* [in] */ _DGMPoint __RPC_FAR *Point,
    /* [in] */ TRANSDIRECTION Dir,
    /* [in] */ IDispatch __RPC_FAR *Param);


void __RPC_STUB ICoordTransform_NativeEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_NativeCollEx_Proxy( 
    ICoordTransform __RPC_FAR * This,
    /* [in] */ _DGMPoints __RPC_FAR *Points,
    /* [in] */ TRANSDIRECTION Dir,
    /* [in] */ IDispatch __RPC_FAR *Param);


void __RPC_STUB ICoordTransform_NativeCollEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_TransformParameter_Proxy( 
    ICoordTransform __RPC_FAR * This,
    /* [in] */ _DGMPoint __RPC_FAR *Point,
    /* [in] */ TRANSDIRECTION Dir,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB ICoordTransform_TransformParameter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_FreeTransformParameter_Proxy( 
    ICoordTransform __RPC_FAR * This,
    /* [in] */ TRANSDIRECTION Dir,
    /* [in] */ IDispatch __RPC_FAR *pDisp);


void __RPC_STUB ICoordTransform_FreeTransformParameter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_NativeParameter_Proxy( 
    ICoordTransform __RPC_FAR * This,
    /* [in] */ _DGMPoint __RPC_FAR *Point,
    /* [in] */ TRANSDIRECTION Dir,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB ICoordTransform_NativeParameter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_FreeNativeParameter_Proxy( 
    ICoordTransform __RPC_FAR * This,
    /* [in] */ TRANSDIRECTION Dir,
    /* [in] */ IDispatch __RPC_FAR *pIDisp);


void __RPC_STUB ICoordTransform_FreeNativeParameter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_Distance_Proxy( 
    ICoordTransform __RPC_FAR * This,
    /* [in] */ _DGMPoint __RPC_FAR *Point1,
    /* [in] */ _DGMPoint __RPC_FAR *Point2,
    /* [retval][out] */ _DGMPoint __RPC_FAR *__RPC_FAR *pDist);


void __RPC_STUB ICoordTransform_Distance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_DistancePoint_Proxy( 
    ICoordTransform __RPC_FAR * This,
    /* [in] */ _DGMPoint __RPC_FAR *Point,
    /* [in] */ _DGMPoint __RPC_FAR *Delta,
    /* [retval][out] */ _DGMPoint __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB ICoordTransform_DistancePoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_ToStrings_Proxy( 
    ICoordTransform __RPC_FAR * This,
    /* [in] */ _DGMPoint __RPC_FAR *Point,
    /* [out] */ BSTR __RPC_FAR *XStr,
    /* [out] */ BSTR __RPC_FAR *YStr,
    /* [out] */ BSTR __RPC_FAR *ZStr);


void __RPC_STUB ICoordTransform_ToStrings_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICoordTransform_ToPoint_Proxy( 
    ICoordTransform __RPC_FAR * This,
    /* [in] */ BSTR XStr,
    /* [in] */ BSTR YStr,
    /* [in] */ BSTR ZStr,
    /* [retval][out] */ _DGMPoint __RPC_FAR *__RPC_FAR *Point);


void __RPC_STUB ICoordTransform_ToPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICoordTransform_get_Container_Proxy( 
    ICoordTransform __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Rect);


void __RPC_STUB ICoordTransform_get_Container_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICoordTransform_INTERFACE_DEFINED__ */


#ifndef __ICoordTransformInit_INTERFACE_DEFINED__
#define __ICoordTransformInit_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICoordTransformInit
 * at Tue May 05 20:39:08 1998
 * using MIDL 3.01.76
 ****************************************/
/* [unique][helpstring][uuid][object] */ 



EXTERN_C const IID IID_ICoordTransformInit;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0BDC3C1B-503F-11d1-96F0-00A024D6F582")
    ICoordTransformInit : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InitCoordTransform( 
            IUnknown __RPC_FAR *Props) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReInitCoordTransform( 
            IUnknown __RPC_FAR *Props) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TermCoordTransform( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICoordTransformInitVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICoordTransformInit __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICoordTransformInit __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICoordTransformInit __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InitCoordTransform )( 
            ICoordTransformInit __RPC_FAR * This,
            IUnknown __RPC_FAR *Props);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReInitCoordTransform )( 
            ICoordTransformInit __RPC_FAR * This,
            IUnknown __RPC_FAR *Props);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TermCoordTransform )( 
            ICoordTransformInit __RPC_FAR * This);
        
        END_INTERFACE
    } ICoordTransformInitVtbl;

    interface ICoordTransformInit
    {
        CONST_VTBL struct ICoordTransformInitVtbl __RPC_FAR *lpVtbl;
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
    ICoordTransformInit __RPC_FAR * This,
    IUnknown __RPC_FAR *Props);


void __RPC_STUB ICoordTransformInit_InitCoordTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICoordTransformInit_ReInitCoordTransform_Proxy( 
    ICoordTransformInit __RPC_FAR * This,
    IUnknown __RPC_FAR *Props);


void __RPC_STUB ICoordTransformInit_ReInitCoordTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICoordTransformInit_TermCoordTransform_Proxy( 
    ICoordTransformInit __RPC_FAR * This);


void __RPC_STUB ICoordTransformInit_TermCoordTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICoordTransformInit_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
