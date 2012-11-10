/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Jun 08 19:03:02 1999
 */
/* Compiler settings for AcadDXF.idl:
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

#ifndef __AcadDXF_h__
#define __AcadDXF_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IAcadDXFExport_FWD_DEFINED__
#define __IAcadDXFExport_FWD_DEFINED__
typedef interface IAcadDXFExport IAcadDXFExport;
#endif 	/* __IAcadDXFExport_FWD_DEFINED__ */


#ifndef __AcadDXFExport_FWD_DEFINED__
#define __AcadDXFExport_FWD_DEFINED__

#ifdef __cplusplus
typedef class AcadDXFExport AcadDXFExport;
#else
typedef struct AcadDXFExport AcadDXFExport;
#endif /* __cplusplus */

#endif 	/* __AcadDXFExport_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_AcadDXF_0000 */
/* [local] */ 

#define TYPELIB_AcadDXF_VERSION_MAJOR 1
#define TYPELIB_AcadDXF_VERSION_MINOR 0
#define TYPELIB_AcadDXF_VERSION "1.0"
#define TYPELIB_AcadDXF_LCID 0


extern RPC_IF_HANDLE __MIDL_itf_AcadDXF_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AcadDXF_0000_v0_0_s_ifspec;


#ifndef __AcadDXFExport_LIBRARY_DEFINED__
#define __AcadDXFExport_LIBRARY_DEFINED__

/* library AcadDXFExport */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_AcadDXFExport;

#ifndef __IAcadDXFExport_INTERFACE_DEFINED__
#define __IAcadDXFExport_INTERFACE_DEFINED__

/* interface IAcadDXFExport */
/* [helpstring][unique][dual][object][uuid] */ 


EXTERN_C const IID IID_IAcadDXFExport;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("119B30E2-1DC0-11d3-9973-0060085FC1CE")
    IAcadDXFExport : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IAcadDXFExportVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAcadDXFExport __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAcadDXFExport __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAcadDXFExport __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAcadDXFExport __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAcadDXFExport __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAcadDXFExport __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAcadDXFExport __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IAcadDXFExportVtbl;

    interface IAcadDXFExport
    {
        CONST_VTBL struct IAcadDXFExportVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAcadDXFExport_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAcadDXFExport_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAcadDXFExport_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAcadDXFExport_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAcadDXFExport_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAcadDXFExport_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAcadDXFExport_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAcadDXFExport_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_AcadDXFExport;

#ifdef __cplusplus

class DECLSPEC_UUID("119B30E3-1DC0-11d3-9973-0060085FC1CE")
AcadDXFExport;
#endif
#endif /* __AcadDXFExport_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
