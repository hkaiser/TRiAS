
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Tue Jan 04 13:18:48 2005
 */
/* Compiler settings for MMLaBra.idl:
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

#ifndef __MMLaBra_h__
#define __MMLaBra_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMapLaBra_FWD_DEFINED__
#define __IMapLaBra_FWD_DEFINED__
typedef interface IMapLaBra IMapLaBra;
#endif 	/* __IMapLaBra_FWD_DEFINED__ */


#ifndef __MapLaBra_FWD_DEFINED__
#define __MapLaBra_FWD_DEFINED__

#ifdef __cplusplus
typedef class MapLaBra MapLaBra;
#else
typedef struct MapLaBra MapLaBra;
#endif /* __cplusplus */

#endif 	/* __MapLaBra_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __MMLABRALib_LIBRARY_DEFINED__
#define __MMLABRALib_LIBRARY_DEFINED__

/* library MMLABRALib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_MMLABRALib;

#ifndef __IMapLaBra_INTERFACE_DEFINED__
#define __IMapLaBra_INTERFACE_DEFINED__

/* interface IMapLaBra */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMapLaBra;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("21655001-EC75-11d4-A9F9-00104BAF20DA")
    IMapLaBra : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IMapLaBraVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMapLaBra * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMapLaBra * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMapLaBra * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMapLaBra * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMapLaBra * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMapLaBra * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMapLaBra * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IMapLaBraVtbl;

    interface IMapLaBra
    {
        CONST_VTBL struct IMapLaBraVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMapLaBra_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMapLaBra_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMapLaBra_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMapLaBra_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMapLaBra_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMapLaBra_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMapLaBra_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMapLaBra_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MapLaBra;

#ifdef __cplusplus

class DECLSPEC_UUID("21655002-EC75-11d4-A9F9-00104BAF20DA")
MapLaBra;
#endif
#endif /* __MMLABRALib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


