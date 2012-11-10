/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon May 31 20:07:14 1999
 */
/* Compiler settings for TRiASARC.idl:
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

#ifndef __TRiASARC_h__
#define __TRiASARC_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ITRiASArcExport_FWD_DEFINED__
#define __ITRiASArcExport_FWD_DEFINED__
typedef interface ITRiASArcExport ITRiASArcExport;
#endif 	/* __ITRiASArcExport_FWD_DEFINED__ */


#ifndef __TRiASArcExport_FWD_DEFINED__
#define __TRiASArcExport_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASArcExport TRiASArcExport;
#else
typedef struct TRiASArcExport TRiASArcExport;
#endif /* __cplusplus */

#endif 	/* __TRiASArcExport_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_TRiASARC_0000 */
/* [local] */ 

#define TYPELIB_TRiASARC_VERSION_MAJOR 1
#define TYPELIB_TRiASARC_VERSION_MINOR 0
#define TYPELIB_TRiASARC_VERSION "1.0"
#define TYPELIB_TRiASARC_LCID 0


extern RPC_IF_HANDLE __MIDL_itf_TRiASARC_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_TRiASARC_0000_v0_0_s_ifspec;


#ifndef __TRiASArcExport_LIBRARY_DEFINED__
#define __TRiASArcExport_LIBRARY_DEFINED__

/* library TRiASArcExport */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_TRiASArcExport;

#ifndef __ITRiASArcExport_INTERFACE_DEFINED__
#define __ITRiASArcExport_INTERFACE_DEFINED__

/* interface ITRiASArcExport */
/* [helpstring][unique][dual][object][uuid] */ 


EXTERN_C const IID IID_ITRiASArcExport;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("286232A1-178B-11d3-9970-0060085FC1CE")
    ITRiASArcExport : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ITRiASArcExportVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITRiASArcExport __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITRiASArcExport __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITRiASArcExport __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITRiASArcExport __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITRiASArcExport __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITRiASArcExport __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITRiASArcExport __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ITRiASArcExportVtbl;

    interface ITRiASArcExport
    {
        CONST_VTBL struct ITRiASArcExportVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASArcExport_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASArcExport_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASArcExport_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASArcExport_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASArcExport_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASArcExport_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASArcExport_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITRiASArcExport_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_TRiASArcExport;

#ifdef __cplusplus

class DECLSPEC_UUID("286232A2-178B-11d3-9970-0060085FC1CE")
TRiASArcExport;
#endif
#endif /* __TRiASArcExport_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
