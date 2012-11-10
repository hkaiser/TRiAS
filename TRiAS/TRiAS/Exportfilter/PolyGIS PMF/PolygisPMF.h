
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Thu Apr 11 15:34:16 2002
 */
/* Compiler settings for PolygisPMF.idl:
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

#ifndef __PolygisPMF_h__
#define __PolygisPMF_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IPolygisPMFExport_FWD_DEFINED__
#define __IPolygisPMFExport_FWD_DEFINED__
typedef interface IPolygisPMFExport IPolygisPMFExport;
#endif 	/* __IPolygisPMFExport_FWD_DEFINED__ */


#ifndef __PolygisPMFExport_FWD_DEFINED__
#define __PolygisPMFExport_FWD_DEFINED__

#ifdef __cplusplus
typedef class PolygisPMFExport PolygisPMFExport;
#else
typedef struct PolygisPMFExport PolygisPMFExport;
#endif /* __cplusplus */

#endif 	/* __PolygisPMFExport_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_PolygisPMF_0000 */
/* [local] */ 

#define TYPELIB_PolygisPMF_VERSION_MAJOR 1
#define TYPELIB_PolygisPMF_VERSION_MINOR 0
#define TYPELIB_PolygisPMF_VERSION "1.0"
#define TYPELIB_PolygisPMF_LCID 0


extern RPC_IF_HANDLE __MIDL_itf_PolygisPMF_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_PolygisPMF_0000_v0_0_s_ifspec;


#ifndef __PolygisPMFExport_LIBRARY_DEFINED__
#define __PolygisPMFExport_LIBRARY_DEFINED__

/* library PolygisPMFExport */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_PolygisPMFExport;

#ifndef __IPolygisPMFExport_INTERFACE_DEFINED__
#define __IPolygisPMFExport_INTERFACE_DEFINED__

/* interface IPolygisPMFExport */
/* [helpstring][unique][dual][object][uuid] */ 


EXTERN_C const IID IID_IPolygisPMFExport;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("599F5AFC-6931-46a8-8D57-5C02DC5E1353")
    IPolygisPMFExport : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IPolygisPMFExportVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPolygisPMFExport * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPolygisPMFExport * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPolygisPMFExport * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPolygisPMFExport * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPolygisPMFExport * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPolygisPMFExport * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPolygisPMFExport * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IPolygisPMFExportVtbl;

    interface IPolygisPMFExport
    {
        CONST_VTBL struct IPolygisPMFExportVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPolygisPMFExport_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPolygisPMFExport_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPolygisPMFExport_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPolygisPMFExport_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPolygisPMFExport_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPolygisPMFExport_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPolygisPMFExport_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPolygisPMFExport_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PolygisPMFExport;

#ifdef __cplusplus

class DECLSPEC_UUID("D92F5E3D-7B28-4d3d-ADB7-9907860A6D91")
PolygisPMFExport;
#endif
#endif /* __PolygisPMFExport_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


