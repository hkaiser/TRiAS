
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Mon Nov 24 14:09:46 2003
 */
/* Compiler settings for D:\TRiASDEV.MVC\EXPORT\PolyGISDAT\PolygisDAT.idl:
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

#ifndef __PolygisDAT_h__
#define __PolygisDAT_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IPolygisDatExport_FWD_DEFINED__
#define __IPolygisDatExport_FWD_DEFINED__
typedef interface IPolygisDatExport IPolygisDatExport;
#endif 	/* __IPolygisDatExport_FWD_DEFINED__ */


#ifndef __PolygisDAT_FWD_DEFINED__
#define __PolygisDAT_FWD_DEFINED__

#ifdef __cplusplus
typedef class PolygisDAT PolygisDAT;
#else
typedef struct PolygisDAT PolygisDAT;
#endif /* __cplusplus */

#endif 	/* __PolygisDAT_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_PolygisDAT_0000 */
/* [local] */ 

#define TYPELIB_PolygisDAT_VERSION_MAJOR 1
#define TYPELIB_PolygisDAT_VERSION_MINOR 0
#define TYPELIB_PolygisDAT_VERSION "1.0"
#define TYPELIB_PolygisDAT_LCID 0


extern RPC_IF_HANDLE __MIDL_itf_PolygisDAT_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_PolygisDAT_0000_v0_0_s_ifspec;


#ifndef __PolygisDAT_LIBRARY_DEFINED__
#define __PolygisDAT_LIBRARY_DEFINED__

/* library PolygisDAT */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_PolygisDAT;

#ifndef __IPolygisDatExport_INTERFACE_DEFINED__
#define __IPolygisDatExport_INTERFACE_DEFINED__

/* interface IPolygisDatExport */
/* [helpstring][unique][dual][object][uuid] */ 


EXTERN_C const IID IID_IPolygisDatExport;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A9C738B5-172E-42d2-8FF4-2B70F8A672AD")
    IPolygisDatExport : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IPolygisDatExportVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPolygisDatExport * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPolygisDatExport * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPolygisDatExport * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPolygisDatExport * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPolygisDatExport * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPolygisDatExport * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPolygisDatExport * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IPolygisDatExportVtbl;

    interface IPolygisDatExport
    {
        CONST_VTBL struct IPolygisDatExportVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPolygisDatExport_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPolygisDatExport_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPolygisDatExport_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPolygisDatExport_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPolygisDatExport_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPolygisDatExport_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPolygisDatExport_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPolygisDatExport_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PolygisDAT;

#ifdef __cplusplus

class DECLSPEC_UUID("152651A7-2994-4752-A2CA-38EAB8C9EA54")
PolygisDAT;
#endif
#endif /* __PolygisDAT_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


