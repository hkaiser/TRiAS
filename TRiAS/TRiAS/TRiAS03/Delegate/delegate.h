/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Thu Oct 29 22:13:10 1998
 */
/* Compiler settings for delegate.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __delegate_h__
#define __delegate_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDelegatorFactory_FWD_DEFINED__
#define __IDelegatorFactory_FWD_DEFINED__
typedef interface IDelegatorFactory IDelegatorFactory;
#endif 	/* __IDelegatorFactory_FWD_DEFINED__ */


#ifndef __CoDelegator_FWD_DEFINED__
#define __CoDelegator_FWD_DEFINED__

#ifdef __cplusplus
typedef class CoDelegator CoDelegator;
#else
typedef struct CoDelegator CoDelegator;
#endif /* __cplusplus */

#endif 	/* __CoDelegator_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __DelegatorLib_LIBRARY_DEFINED__
#define __DelegatorLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: DelegatorLib
 * at Thu Oct 29 22:13:10 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [lcid][version][uuid] */ 



EXTERN_C const IID LIBID_DelegatorLib;

#ifndef __IDelegatorFactory_INTERFACE_DEFINED__
#define __IDelegatorFactory_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDelegatorFactory
 * at Thu Oct 29 22:13:10 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][uuid] */ 



EXTERN_C const IID IID_IDelegatorFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("58DAD7D6-6F34-11D2-9EEC-006008447800")
    IDelegatorFactory : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateDelegator( 
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ IUnknown __RPC_FAR *pUnkInner,
            /* [in] */ REFIID iid,
            /* [out] */ void __RPC_FAR *__RPC_FAR *ppv) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDelegatorFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDelegatorFactory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDelegatorFactory __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDelegatorFactory __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateDelegator )( 
            IDelegatorFactory __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ IUnknown __RPC_FAR *pUnkInner,
            /* [in] */ REFIID iid,
            /* [out] */ void __RPC_FAR *__RPC_FAR *ppv);
        
        END_INTERFACE
    } IDelegatorFactoryVtbl;

    interface IDelegatorFactory
    {
        CONST_VTBL struct IDelegatorFactoryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDelegatorFactory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDelegatorFactory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDelegatorFactory_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDelegatorFactory_CreateDelegator(This,pUnkOuter,pUnkInner,iid,ppv)	\
    (This)->lpVtbl -> CreateDelegator(This,pUnkOuter,pUnkInner,iid,ppv)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDelegatorFactory_CreateDelegator_Proxy( 
    IDelegatorFactory __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ IUnknown __RPC_FAR *pUnkInner,
    /* [in] */ REFIID iid,
    /* [out] */ void __RPC_FAR *__RPC_FAR *ppv);


void __RPC_STUB IDelegatorFactory_CreateDelegator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDelegatorFactory_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CoDelegator;

#ifdef __cplusplus

class DECLSPEC_UUID("58DAD7D5-6F34-11D2-9EEC-006008447800")
CoDelegator;
#endif
#endif /* __DelegatorLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
