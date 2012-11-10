
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Tue Jan 04 13:18:30 2005
 */
/* Compiler settings for MMRefer.idl:
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

#ifndef __MMRefer_h__
#define __MMRefer_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMapReferenced_FWD_DEFINED__
#define __IMapReferenced_FWD_DEFINED__
typedef interface IMapReferenced IMapReferenced;
#endif 	/* __IMapReferenced_FWD_DEFINED__ */


#ifndef __MapReferenced_FWD_DEFINED__
#define __MapReferenced_FWD_DEFINED__

#ifdef __cplusplus
typedef class MapReferenced MapReferenced;
#else
typedef struct MapReferenced MapReferenced;
#endif /* __cplusplus */

#endif 	/* __MapReferenced_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IMapReferenced_INTERFACE_DEFINED__
#define __IMapReferenced_INTERFACE_DEFINED__

/* interface IMapReferenced */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMapReferenced;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B6AFCF05-1A64-11d2-8F7D-0060085FC1CE")
    IMapReferenced : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IMapReferencedVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMapReferenced * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMapReferenced * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMapReferenced * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMapReferenced * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMapReferenced * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMapReferenced * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMapReferenced * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IMapReferencedVtbl;

    interface IMapReferenced
    {
        CONST_VTBL struct IMapReferencedVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMapReferenced_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMapReferenced_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMapReferenced_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMapReferenced_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMapReferenced_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMapReferenced_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMapReferenced_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMapReferenced_INTERFACE_DEFINED__ */



#ifndef __MMREFERLib_LIBRARY_DEFINED__
#define __MMREFERLib_LIBRARY_DEFINED__

/* library MMREFERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_MMREFERLib;

EXTERN_C const CLSID CLSID_MapReferenced;

#ifdef __cplusplus

class DECLSPEC_UUID("B6AFCF06-1A64-11d2-8F7D-0060085FC1CE")
MapReferenced;
#endif
#endif /* __MMREFERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


