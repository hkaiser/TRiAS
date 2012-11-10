/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat May 05 21:57:03 2001
 */
/* Compiler settings for IDisconnectableRowset.idl:
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

#ifndef __IDisconnectableRowset_h__
#define __IDisconnectableRowset_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDisconnectableRowset_FWD_DEFINED__
#define __IDisconnectableRowset_FWD_DEFINED__
typedef interface IDisconnectableRowset IDisconnectableRowset;
#endif 	/* __IDisconnectableRowset_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IDisconnectableRowset_INTERFACE_DEFINED__
#define __IDisconnectableRowset_INTERFACE_DEFINED__

/* interface IDisconnectableRowset */
/* [unique][helpstring][uuid][hidden][object] */ 


EXTERN_C const IID IID_IDisconnectableRowset;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2A29F476-1C19-11d4-801F-00508B6BAA48")
    IDisconnectableRowset : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE DisconnectRowset( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDisconnectableRowsetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDisconnectableRowset __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDisconnectableRowset __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDisconnectableRowset __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DisconnectRowset )( 
            IDisconnectableRowset __RPC_FAR * This);
        
        END_INTERFACE
    } IDisconnectableRowsetVtbl;

    interface IDisconnectableRowset
    {
        CONST_VTBL struct IDisconnectableRowsetVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDisconnectableRowset_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDisconnectableRowset_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDisconnectableRowset_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDisconnectableRowset_DisconnectRowset(This)	\
    (This)->lpVtbl -> DisconnectRowset(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDisconnectableRowset_DisconnectRowset_Proxy( 
    IDisconnectableRowset __RPC_FAR * This);


void __RPC_STUB IDisconnectableRowset_DisconnectRowset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDisconnectableRowset_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
