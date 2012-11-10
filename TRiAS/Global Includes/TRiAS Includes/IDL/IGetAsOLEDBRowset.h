/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat May 05 21:35:49 2001
 */
/* Compiler settings for IGetAsOLEDBRowset.idl:
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

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __IGetAsOLEDBRowset_h__
#define __IGetAsOLEDBRowset_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef ___IGetAsOLEDBRowset_FWD_DEFINED__
#define ___IGetAsOLEDBRowset_FWD_DEFINED__
typedef interface _IGetAsOLEDBRowset _IGetAsOLEDBRowset;
#endif 	/* ___IGetAsOLEDBRowset_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef ___IGetAsOLEDBRowset_INTERFACE_DEFINED__
#define ___IGetAsOLEDBRowset_INTERFACE_DEFINED__

/* interface _IGetAsOLEDBRowset */
/* [unique][helpstring][uuid][hidden][object] */ 


EXTERN_C const IID IID__IGetAsOLEDBRowset;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0C60F1D3-0C52-11d3-8022-00805F9B645A")
    _IGetAsOLEDBRowset : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAsRowset( 
            /* [in] */ IUnknown __RPC_FAR *pUnkCreator,
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFIID riid,
            /* [out] */ LONG __RPC_FAR *pcRowsAffected,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _IGetAsOLEDBRowsetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IGetAsOLEDBRowset __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IGetAsOLEDBRowset __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IGetAsOLEDBRowset __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAsRowset )( 
            _IGetAsOLEDBRowset __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnkCreator,
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFIID riid,
            /* [out] */ LONG __RPC_FAR *pcRowsAffected,
            /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset);
        
        END_INTERFACE
    } _IGetAsOLEDBRowsetVtbl;

    interface _IGetAsOLEDBRowset
    {
        CONST_VTBL struct _IGetAsOLEDBRowsetVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IGetAsOLEDBRowset_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IGetAsOLEDBRowset_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IGetAsOLEDBRowset_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IGetAsOLEDBRowset_GetAsRowset(This,pUnkCreator,pUnkOuter,riid,pcRowsAffected,ppRowset)	\
    (This)->lpVtbl -> GetAsRowset(This,pUnkCreator,pUnkOuter,riid,pcRowsAffected,ppRowset)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE _IGetAsOLEDBRowset_GetAsRowset_Proxy( 
    _IGetAsOLEDBRowset __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkCreator,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFIID riid,
    /* [out] */ LONG __RPC_FAR *pcRowsAffected,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset);


void __RPC_STUB _IGetAsOLEDBRowset_GetAsRowset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___IGetAsOLEDBRowset_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
