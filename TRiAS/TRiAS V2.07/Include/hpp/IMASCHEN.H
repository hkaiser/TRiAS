/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.00.44 */
/* at Wed Dec 17 19:37:16 1997
 */
/* Compiler settings for Imaschen.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"

#ifndef __Imaschen_h__
#define __Imaschen_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IExtLinienVerfolgung_FWD_DEFINED__
#define __IExtLinienVerfolgung_FWD_DEFINED__
typedef interface IExtLinienVerfolgung IExtLinienVerfolgung;
#endif 	/* __IExtLinienVerfolgung_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __imaschen_LIBRARY_DEFINED__
#define __imaschen_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: imaschen
 * at Wed Dec 17 19:37:16 1997
 * using MIDL 3.00.44
 ****************************************/
/* [helpstring][lcid][version][uuid] */ 



DEFINE_GUID(LIBID_imaschen,0x079638D9,0x3123,0x101C,0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C);

#ifndef __IExtLinienVerfolgung_INTERFACE_DEFINED__
#define __IExtLinienVerfolgung_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IExtLinienVerfolgung
 * at Wed Dec 17 19:37:16 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



DEFINE_GUID(IID_IExtLinienVerfolgung,0x079638D5,0x3123,0x101C,0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IExtLinienVerfolgung : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE LinesUnion( 
            /* [in] */ IEnumObjectsByNumber __RPC_FAR *pInput,
            /* [in] */ double dTolerance,
            /* [in] */ VARIANT_BOOL bOutputUnIdents,
            /* [in] */ VARIANT_BOOL bCreateAreas,
            /* [optional][in] */ VARIANT vPI,
            /* [optional][out] */ VARIANT __RPC_FAR *pvUsed,
            /* [retval][out] */ IEnumObjectsByNumber __RPC_FAR *__RPC_FAR *ppUnion) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IExtLinienVerfolgungVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IExtLinienVerfolgung __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IExtLinienVerfolgung __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IExtLinienVerfolgung __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IExtLinienVerfolgung __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IExtLinienVerfolgung __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IExtLinienVerfolgung __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IExtLinienVerfolgung __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LinesUnion )( 
            IExtLinienVerfolgung __RPC_FAR * This,
            /* [in] */ IEnumObjectsByNumber __RPC_FAR *pInput,
            /* [in] */ double dTolerance,
            /* [in] */ VARIANT_BOOL bOutputUnIdents,
            /* [in] */ VARIANT_BOOL bCreateAreas,
            /* [optional][in] */ VARIANT vPI,
            /* [optional][out] */ VARIANT __RPC_FAR *pvUsed,
            /* [retval][out] */ IEnumObjectsByNumber __RPC_FAR *__RPC_FAR *ppUnion);
        
        END_INTERFACE
    } IExtLinienVerfolgungVtbl;

    interface IExtLinienVerfolgung
    {
        CONST_VTBL struct IExtLinienVerfolgungVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IExtLinienVerfolgung_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IExtLinienVerfolgung_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IExtLinienVerfolgung_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IExtLinienVerfolgung_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IExtLinienVerfolgung_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IExtLinienVerfolgung_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IExtLinienVerfolgung_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IExtLinienVerfolgung_LinesUnion(This,pInput,dTolerance,bOutputUnIdents,bCreateAreas,vPI,pvUsed,ppUnion)	\
    (This)->lpVtbl -> LinesUnion(This,pInput,dTolerance,bOutputUnIdents,bCreateAreas,vPI,pvUsed,ppUnion)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IExtLinienVerfolgung_LinesUnion_Proxy( 
    IExtLinienVerfolgung __RPC_FAR * This,
    /* [in] */ IEnumObjectsByNumber __RPC_FAR *pInput,
    /* [in] */ double dTolerance,
    /* [in] */ VARIANT_BOOL bOutputUnIdents,
    /* [in] */ VARIANT_BOOL bCreateAreas,
    /* [optional][in] */ VARIANT vPI,
    /* [optional][out] */ VARIANT __RPC_FAR *pvUsed,
    /* [retval][out] */ IEnumObjectsByNumber __RPC_FAR *__RPC_FAR *ppUnion);


void __RPC_STUB IExtLinienVerfolgung_LinesUnion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IExtLinienVerfolgung_INTERFACE_DEFINED__ */


#ifdef __cplusplus
DEFINE_GUID(CLSID_ExtLinienVerfolgung,0x079638DA,0x3123,0x101C,0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C);

class ExtLinienVerfolgung;
#endif
#endif /* __imaschen_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
