/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Jun 07 22:53:29 2001
 */
/* Compiler settings for TRiASExpression.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
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

#ifndef __TRiASExpression_h__
#define __TRiASExpression_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ITRiASExpression_FWD_DEFINED__
#define __ITRiASExpression_FWD_DEFINED__
typedef interface ITRiASExpression ITRiASExpression;
#endif 	/* __ITRiASExpression_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_TRiASExpression_0000 */
/* [local] */ 

#pragma once



extern RPC_IF_HANDLE __MIDL_itf_TRiASExpression_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_TRiASExpression_0000_v0_0_s_ifspec;

#ifndef __ITRiASExpression_INTERFACE_DEFINED__
#define __ITRiASExpression_INTERFACE_DEFINED__

/* interface ITRiASExpression */
/* [object][helpstring][unique][local][uuid] */ 


EXTERN_C const IID IID_ITRiASExpression;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1BDC7DDB-DE4B-4BC6-8FAE-A3EE2640C812")
    ITRiASExpression : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Calculate( 
            /* [in] */ INT_PTR PrjHandle,
            /* [in] */ INT_PTR Object,
            /* [retval][out] */ VARIANT __RPC_FAR *Value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASExpressionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITRiASExpression __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITRiASExpression __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITRiASExpression __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Calculate )( 
            ITRiASExpression __RPC_FAR * This,
            /* [in] */ INT_PTR PrjHandle,
            /* [in] */ INT_PTR Object,
            /* [retval][out] */ VARIANT __RPC_FAR *Value);
        
        END_INTERFACE
    } ITRiASExpressionVtbl;

    interface ITRiASExpression
    {
        CONST_VTBL struct ITRiASExpressionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASExpression_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASExpression_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASExpression_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASExpression_Calculate(This,PrjHandle,Object,Value)	\
    (This)->lpVtbl -> Calculate(This,PrjHandle,Object,Value)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ITRiASExpression_Calculate_Proxy( 
    ITRiASExpression __RPC_FAR * This,
    /* [in] */ INT_PTR PrjHandle,
    /* [in] */ INT_PTR Object,
    /* [retval][out] */ VARIANT __RPC_FAR *Value);


void __RPC_STUB ITRiASExpression_Calculate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASExpression_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
