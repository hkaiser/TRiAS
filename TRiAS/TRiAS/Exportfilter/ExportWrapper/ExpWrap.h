/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.76 */
/* at Tue Apr 07 20:23:40 1998
 */
/* Compiler settings for ExpWrap.idl:
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

#ifndef __ExpWrap_h__
#define __ExpWrap_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IAscExportWrapper_FWD_DEFINED__
#define __IAscExportWrapper_FWD_DEFINED__
typedef interface IAscExportWrapper IAscExportWrapper;
#endif 	/* __IAscExportWrapper_FWD_DEFINED__ */


#ifndef __AscExportWrapper_FWD_DEFINED__
#define __AscExportWrapper_FWD_DEFINED__

#ifdef __cplusplus
typedef class AscExportWrapper AscExportWrapper;
#else
typedef struct AscExportWrapper AscExportWrapper;
#endif /* __cplusplus */

#endif 	/* __AscExportWrapper_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_ExpWrap_0000
 * at Tue Apr 07 20:23:40 1998
 * using MIDL 3.01.76
 ****************************************/
/* [local] */ 


#if !defined(_DEFINED_HOBJECT)
#define _DEFINED_HOBJECT
typedef /* [hidden] */ long HOBJECT;

#endif // _DEFINED_HOBJECT
#if !defined(_DEFINED_HRELATION)
#define _DEFINED_HRELATION
typedef /* [hidden] */ long __RPC_FAR *HRELATION;

#endif // _DEFINED_HRELATION


extern RPC_IF_HANDLE __MIDL_itf_ExpWrap_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ExpWrap_0000_v0_0_s_ifspec;

#ifndef __IAscExportWrapper_INTERFACE_DEFINED__
#define __IAscExportWrapper_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAscExportWrapper
 * at Tue Apr 07 20:23:40 1998
 * using MIDL 3.01.76
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 


#if !defined(_OUTMODE_DEFINED)
#define _OUTMODE_DEFINED
typedef /* [helpstring][public] */ 
enum _tagOUTMODE
    {	OUTMODE_Overwrite	= 0,
	OUTMODE_Concatenate	= 1
    }	OUTMODE;

#endif // _OUTMODE_DEFINED
#if !defined(_DESCSTYLE_DEFINED)
#define _DESCSTYLE_DEFINED
typedef /* [helpstring][public] */ 
enum _tagDESCSTYLE
    {	DESCSTYLE_Normal	= 0,
	DESCSTYLE_System	= 1,
	DESCSTYLE_ReadOnly	= 2,
	DESCSTYLE_SystemRO	= 3,
	DESCSTYLE_Dynamic	= 4
    }	DESCSTYLE;

#endif // _DESCSTYLE_DEFINED
#if !defined(_RELTYPE_DEFINED)
#define _RELTYPE_DEFINED
typedef /* [helpstring][public] */ 
enum _tagRELTYPE
    {	RELTYPE_Text	= 0,
	RELTYPE_Equal	= 1,
	RELTYPE_Hierarchy	= 2
    }	RELTYPE;

#endif // _RELTYPE_DEFINED
#if !defined(_OBJECTTYPE_DEFINED)
#define _OBJECTTYPE_DEFINED
typedef /* [helpstring][public] */ 
enum _tagOBJECTTYPE
    {	OBJECTTYPE_Point	= 1,
	OBJECTTYPE_Line	= 2,
	OBJECTTYPE_Area	= 4,
	OBJECTTYPE_Circle	= 4,
	OBJECTTYPE_Text	= 8,
	OBJECTTYPE_Complex	= 16,
	OBJECTTYPE_Unknown	= 0,
	OBJECTTYPE_All	= 0x1f
    }	OBJECTTYPE;

#endif // _OBJECTTYPE_DEFINED

EXTERN_C const IID IID_IAscExportWrapper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("DED33401-CDE6-11D1-85E2-00600875138A")
    IAscExportWrapper : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExportBegin( 
            /* [in] */ BSTR Name,
            /* [in] */ OUTMODE Mode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExportComment( 
            /* [in] */ BSTR Comment) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExportHeader( 
            /* [in] */ BSTR Header) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExportDescription( 
            /* [in] */ BSTR KeyInfo,
            /* [in] */ BSTR Description,
            /* [defaultvalue][optional][in] */ DESCSTYLE Style) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExportTrailer( 
            /* [in] */ BSTR TrailerInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BeginObject( 
            /* [in] */ HOBJECT ObjHandle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExportGeometry( 
            /* [in] */ OBJECTTYPE Type,
            /* [in] */ IUnknown __RPC_FAR *pIGeom) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExportFeature( 
            /* [in] */ VARIANT Feature) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExportRelation( 
            /* [in] */ HRELATION RelHandle,
            /* [in] */ RELTYPE Type,
            /* [in] */ HOBJECT ObjHandle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EndObject( 
            /* [in] */ HOBJECT ObjHandle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ BSTR RegKey) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAscExportWrapperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAscExportWrapper __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAscExportWrapper __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAscExportWrapper __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAscExportWrapper __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAscExportWrapper __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAscExportWrapper __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAscExportWrapper __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ExportBegin )( 
            IAscExportWrapper __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ OUTMODE Mode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ExportComment )( 
            IAscExportWrapper __RPC_FAR * This,
            /* [in] */ BSTR Comment);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ExportHeader )( 
            IAscExportWrapper __RPC_FAR * This,
            /* [in] */ BSTR Header);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ExportDescription )( 
            IAscExportWrapper __RPC_FAR * This,
            /* [in] */ BSTR KeyInfo,
            /* [in] */ BSTR Description,
            /* [defaultvalue][optional][in] */ DESCSTYLE Style);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ExportTrailer )( 
            IAscExportWrapper __RPC_FAR * This,
            /* [in] */ BSTR TrailerInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BeginObject )( 
            IAscExportWrapper __RPC_FAR * This,
            /* [in] */ HOBJECT ObjHandle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ExportGeometry )( 
            IAscExportWrapper __RPC_FAR * This,
            /* [in] */ OBJECTTYPE Type,
            /* [in] */ IUnknown __RPC_FAR *pIGeom);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ExportFeature )( 
            IAscExportWrapper __RPC_FAR * This,
            /* [in] */ VARIANT Feature);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ExportRelation )( 
            IAscExportWrapper __RPC_FAR * This,
            /* [in] */ HRELATION RelHandle,
            /* [in] */ RELTYPE Type,
            /* [in] */ HOBJECT ObjHandle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EndObject )( 
            IAscExportWrapper __RPC_FAR * This,
            /* [in] */ HOBJECT ObjHandle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IAscExportWrapper __RPC_FAR * This,
            /* [in] */ BSTR RegKey);
        
        END_INTERFACE
    } IAscExportWrapperVtbl;

    interface IAscExportWrapper
    {
        CONST_VTBL struct IAscExportWrapperVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAscExportWrapper_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAscExportWrapper_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAscExportWrapper_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAscExportWrapper_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAscExportWrapper_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAscExportWrapper_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAscExportWrapper_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAscExportWrapper_ExportBegin(This,Name,Mode)	\
    (This)->lpVtbl -> ExportBegin(This,Name,Mode)

#define IAscExportWrapper_ExportComment(This,Comment)	\
    (This)->lpVtbl -> ExportComment(This,Comment)

#define IAscExportWrapper_ExportHeader(This,Header)	\
    (This)->lpVtbl -> ExportHeader(This,Header)

#define IAscExportWrapper_ExportDescription(This,KeyInfo,Description,Style)	\
    (This)->lpVtbl -> ExportDescription(This,KeyInfo,Description,Style)

#define IAscExportWrapper_ExportTrailer(This,TrailerInfo)	\
    (This)->lpVtbl -> ExportTrailer(This,TrailerInfo)

#define IAscExportWrapper_BeginObject(This,ObjHandle)	\
    (This)->lpVtbl -> BeginObject(This,ObjHandle)

#define IAscExportWrapper_ExportGeometry(This,Type,pIGeom)	\
    (This)->lpVtbl -> ExportGeometry(This,Type,pIGeom)

#define IAscExportWrapper_ExportFeature(This,Feature)	\
    (This)->lpVtbl -> ExportFeature(This,Feature)

#define IAscExportWrapper_ExportRelation(This,RelHandle,Type,ObjHandle)	\
    (This)->lpVtbl -> ExportRelation(This,RelHandle,Type,ObjHandle)

#define IAscExportWrapper_EndObject(This,ObjHandle)	\
    (This)->lpVtbl -> EndObject(This,ObjHandle)

#define IAscExportWrapper_Initialize(This,RegKey)	\
    (This)->lpVtbl -> Initialize(This,RegKey)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAscExportWrapper_ExportBegin_Proxy( 
    IAscExportWrapper __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [in] */ OUTMODE Mode);


void __RPC_STUB IAscExportWrapper_ExportBegin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAscExportWrapper_ExportComment_Proxy( 
    IAscExportWrapper __RPC_FAR * This,
    /* [in] */ BSTR Comment);


void __RPC_STUB IAscExportWrapper_ExportComment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAscExportWrapper_ExportHeader_Proxy( 
    IAscExportWrapper __RPC_FAR * This,
    /* [in] */ BSTR Header);


void __RPC_STUB IAscExportWrapper_ExportHeader_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAscExportWrapper_ExportDescription_Proxy( 
    IAscExportWrapper __RPC_FAR * This,
    /* [in] */ BSTR KeyInfo,
    /* [in] */ BSTR Description,
    /* [defaultvalue][optional][in] */ DESCSTYLE Style);


void __RPC_STUB IAscExportWrapper_ExportDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAscExportWrapper_ExportTrailer_Proxy( 
    IAscExportWrapper __RPC_FAR * This,
    /* [in] */ BSTR TrailerInfo);


void __RPC_STUB IAscExportWrapper_ExportTrailer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAscExportWrapper_BeginObject_Proxy( 
    IAscExportWrapper __RPC_FAR * This,
    /* [in] */ HOBJECT ObjHandle);


void __RPC_STUB IAscExportWrapper_BeginObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAscExportWrapper_ExportGeometry_Proxy( 
    IAscExportWrapper __RPC_FAR * This,
    /* [in] */ OBJECTTYPE Type,
    /* [in] */ IUnknown __RPC_FAR *pIGeom);


void __RPC_STUB IAscExportWrapper_ExportGeometry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAscExportWrapper_ExportFeature_Proxy( 
    IAscExportWrapper __RPC_FAR * This,
    /* [in] */ VARIANT Feature);


void __RPC_STUB IAscExportWrapper_ExportFeature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAscExportWrapper_ExportRelation_Proxy( 
    IAscExportWrapper __RPC_FAR * This,
    /* [in] */ HRELATION RelHandle,
    /* [in] */ RELTYPE Type,
    /* [in] */ HOBJECT ObjHandle);


void __RPC_STUB IAscExportWrapper_ExportRelation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAscExportWrapper_EndObject_Proxy( 
    IAscExportWrapper __RPC_FAR * This,
    /* [in] */ HOBJECT ObjHandle);


void __RPC_STUB IAscExportWrapper_EndObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAscExportWrapper_Initialize_Proxy( 
    IAscExportWrapper __RPC_FAR * This,
    /* [in] */ BSTR RegKey);


void __RPC_STUB IAscExportWrapper_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAscExportWrapper_INTERFACE_DEFINED__ */



#ifndef __EXPWRAPLib_LIBRARY_DEFINED__
#define __EXPWRAPLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: EXPWRAPLib
 * at Tue Apr 07 20:23:40 1998
 * using MIDL 3.01.76
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_EXPWRAPLib;

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_AscExportWrapper;

class DECLSPEC_UUID("DED33402-CDE6-11D1-85E2-00600875138A")
AscExportWrapper;
#endif
#endif /* __EXPWRAPLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
