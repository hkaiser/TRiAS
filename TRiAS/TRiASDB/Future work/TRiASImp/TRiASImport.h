/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Tue Jan 27 14:13:26 1998
 */
/* Compiler settings for TRiASImport.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"
#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __TRiASImport_h__
#define __TRiASImport_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ITriasXtensionSite_FWD_DEFINED__
#define __ITriasXtensionSite_FWD_DEFINED__
typedef interface ITriasXtensionSite ITriasXtensionSite;
#endif 	/* __ITriasXtensionSite_FWD_DEFINED__ */


#ifndef __ImportDBEngine_FWD_DEFINED__
#define __ImportDBEngine_FWD_DEFINED__

#ifdef __cplusplus
typedef class ImportDBEngine ImportDBEngine;
#else
typedef struct ImportDBEngine ImportDBEngine;
#endif /* __cplusplus */

#endif 	/* __ImportDBEngine_FWD_DEFINED__ */


#ifndef __DatabaseBase_FWD_DEFINED__
#define __DatabaseBase_FWD_DEFINED__

#ifdef __cplusplus
typedef class DatabaseBase DatabaseBase;
#else
typedef struct DatabaseBase DatabaseBase;
#endif /* __cplusplus */

#endif 	/* __DatabaseBase_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "TriasDB.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ITriasXtensionSite_INTERFACE_DEFINED__
#define __ITriasXtensionSite_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITriasXtensionSite
 * at Tue Jan 27 14:13:26 1998
 * using MIDL 3.01.75
 ****************************************/
/* [object][unique][helpstring][uuid] */ 



EXTERN_C const IID IID_ITriasXtensionSite;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("07963815-3123-101C-BB62-00AA0018497C")
    ITriasXtensionSite : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetXtension( 
            /* [in] */ REFCLSID rClsID,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateInstance( 
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFCLSID rClsID,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITriasXtensionSiteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITriasXtensionSite __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITriasXtensionSite __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITriasXtensionSite __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetXtension )( 
            ITriasXtensionSite __RPC_FAR * This,
            /* [in] */ REFCLSID rClsID,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateInstance )( 
            ITriasXtensionSite __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFCLSID rClsID,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        END_INTERFACE
    } ITriasXtensionSiteVtbl;

    interface ITriasXtensionSite
    {
        CONST_VTBL struct ITriasXtensionSiteVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITriasXtensionSite_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITriasXtensionSite_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITriasXtensionSite_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITriasXtensionSite_GetXtension(This,rClsID,riid,ppvObject)	\
    (This)->lpVtbl -> GetXtension(This,rClsID,riid,ppvObject)

#define ITriasXtensionSite_CreateInstance(This,pUnkOuter,rClsID,riid,ppvObject)	\
    (This)->lpVtbl -> CreateInstance(This,pUnkOuter,rClsID,riid,ppvObject)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITriasXtensionSite_GetXtension_Proxy( 
    ITriasXtensionSite __RPC_FAR * This,
    /* [in] */ REFCLSID rClsID,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);


void __RPC_STUB ITriasXtensionSite_GetXtension_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITriasXtensionSite_CreateInstance_Proxy( 
    ITriasXtensionSite __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFCLSID rClsID,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);


void __RPC_STUB ITriasXtensionSite_CreateInstance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITriasXtensionSite_INTERFACE_DEFINED__ */



#ifndef __TRIASIMPORTLib_LIBRARY_DEFINED__
#define __TRIASIMPORTLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: TRIASIMPORTLib
 * at Tue Jan 27 14:13:26 1998
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_TRIASIMPORTLib;

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_ImportDBEngine;

class DECLSPEC_UUID("7BACA173-8C1B-11D1-A00E-0060975566B4")
ImportDBEngine;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_DatabaseBase;

class DECLSPEC_UUID("56FD6492-93D5-11D1-A024-0060975566B4")
DatabaseBase;
#endif
#endif /* __TRIASIMPORTLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
