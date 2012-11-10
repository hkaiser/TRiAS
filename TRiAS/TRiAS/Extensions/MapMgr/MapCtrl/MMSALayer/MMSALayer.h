
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Tue Jan 04 13:18:39 2005
 */
/* Compiler settings for MMSALayer.idl:
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

#ifndef __MMSALayer_h__
#define __MMSALayer_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMapSALayer_FWD_DEFINED__
#define __IMapSALayer_FWD_DEFINED__
typedef interface IMapSALayer IMapSALayer;
#endif 	/* __IMapSALayer_FWD_DEFINED__ */


#ifndef __MapSALayer_FWD_DEFINED__
#define __MapSALayer_FWD_DEFINED__

#ifdef __cplusplus
typedef class MapSALayer MapSALayer;
#else
typedef struct MapSALayer MapSALayer;
#endif /* __cplusplus */

#endif 	/* __MapSALayer_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __MMSALAYERLib_LIBRARY_DEFINED__
#define __MMSALAYERLib_LIBRARY_DEFINED__

/* library MMSALAYERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_MMSALAYERLib;

#ifndef __IMapSALayer_INTERFACE_DEFINED__
#define __IMapSALayer_INTERFACE_DEFINED__

/* interface IMapSALayer */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMapSALayer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5F311072-B950-11D4-A9C5-00104BAF20DA")
    IMapSALayer : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IMapSALayerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMapSALayer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMapSALayer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMapSALayer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMapSALayer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMapSALayer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMapSALayer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMapSALayer * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IMapSALayerVtbl;

    interface IMapSALayer
    {
        CONST_VTBL struct IMapSALayerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMapSALayer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMapSALayer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMapSALayer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMapSALayer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMapSALayer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMapSALayer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMapSALayer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMapSALayer_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MapSALayer;

#ifdef __cplusplus

class DECLSPEC_UUID("5F311073-B950-11D4-A9C5-00104BAF20DA")
MapSALayer;
#endif
#endif /* __MMSALAYERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


