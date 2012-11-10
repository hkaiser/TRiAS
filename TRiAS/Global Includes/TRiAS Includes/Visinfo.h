
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Wed Mar 13 17:42:56 2002
 */
/* Compiler settings for .\Visinfo.idl:
    Os, W1, Zp8, env=Win32 (32b run)
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

#ifndef __Visinfo_h__
#define __Visinfo_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IVisObjExt_FWD_DEFINED__
#define __IVisObjExt_FWD_DEFINED__
typedef interface IVisObjExt IVisObjExt;
#endif 	/* __IVisObjExt_FWD_DEFINED__ */


#ifndef __IVisQuery_FWD_DEFINED__
#define __IVisQuery_FWD_DEFINED__
typedef interface IVisQuery IVisQuery;
#endif 	/* __IVisQuery_FWD_DEFINED__ */


#ifndef __IMergeVisInfo_FWD_DEFINED__
#define __IMergeVisInfo_FWD_DEFINED__
typedef interface IMergeVisInfo IMergeVisInfo;
#endif 	/* __IMergeVisInfo_FWD_DEFINED__ */


#ifndef __IRawVisInfo_FWD_DEFINED__
#define __IRawVisInfo_FWD_DEFINED__
typedef interface IRawVisInfo IRawVisInfo;
#endif 	/* __IRawVisInfo_FWD_DEFINED__ */


#ifndef __IExtendedObjectVisInfo_FWD_DEFINED__
#define __IExtendedObjectVisInfo_FWD_DEFINED__
typedef interface IExtendedObjectVisInfo IExtendedObjectVisInfo;
#endif 	/* __IExtendedObjectVisInfo_FWD_DEFINED__ */


#ifndef __IVisInfo_FWD_DEFINED__
#define __IVisInfo_FWD_DEFINED__
typedef interface IVisInfo IVisInfo;
#endif 	/* __IVisInfo_FWD_DEFINED__ */


#ifndef __IPointVisInfo_FWD_DEFINED__
#define __IPointVisInfo_FWD_DEFINED__
typedef interface IPointVisInfo IPointVisInfo;
#endif 	/* __IPointVisInfo_FWD_DEFINED__ */


#ifndef __ILineVisInfo_FWD_DEFINED__
#define __ILineVisInfo_FWD_DEFINED__
typedef interface ILineVisInfo ILineVisInfo;
#endif 	/* __ILineVisInfo_FWD_DEFINED__ */


#ifndef __IAreaVisInfo_FWD_DEFINED__
#define __IAreaVisInfo_FWD_DEFINED__
typedef interface IAreaVisInfo IAreaVisInfo;
#endif 	/* __IAreaVisInfo_FWD_DEFINED__ */


#ifndef __ITextVisInfo_FWD_DEFINED__
#define __ITextVisInfo_FWD_DEFINED__
typedef interface ITextVisInfo ITextVisInfo;
#endif 	/* __ITextVisInfo_FWD_DEFINED__ */


#ifndef __DefaultVisInfo_FWD_DEFINED__
#define __DefaultVisInfo_FWD_DEFINED__

#ifdef __cplusplus
typedef class DefaultVisInfo DefaultVisInfo;
#else
typedef struct DefaultVisInfo DefaultVisInfo;
#endif /* __cplusplus */

#endif 	/* __DefaultVisInfo_FWD_DEFINED__ */


#ifndef __PointVisInfo_FWD_DEFINED__
#define __PointVisInfo_FWD_DEFINED__

#ifdef __cplusplus
typedef class PointVisInfo PointVisInfo;
#else
typedef struct PointVisInfo PointVisInfo;
#endif /* __cplusplus */

#endif 	/* __PointVisInfo_FWD_DEFINED__ */


#ifndef __LineVisInfo_FWD_DEFINED__
#define __LineVisInfo_FWD_DEFINED__

#ifdef __cplusplus
typedef class LineVisInfo LineVisInfo;
#else
typedef struct LineVisInfo LineVisInfo;
#endif /* __cplusplus */

#endif 	/* __LineVisInfo_FWD_DEFINED__ */


#ifndef __AreaVisInfo_FWD_DEFINED__
#define __AreaVisInfo_FWD_DEFINED__

#ifdef __cplusplus
typedef class AreaVisInfo AreaVisInfo;
#else
typedef struct AreaVisInfo AreaVisInfo;
#endif /* __cplusplus */

#endif 	/* __AreaVisInfo_FWD_DEFINED__ */


#ifndef __TextVisInfo_FWD_DEFINED__
#define __TextVisInfo_FWD_DEFINED__

#ifdef __cplusplus
typedef class TextVisInfo TextVisInfo;
#else
typedef struct TextVisInfo TextVisInfo;
#endif /* __cplusplus */

#endif 	/* __TextVisInfo_FWD_DEFINED__ */


#ifndef __ObjVisInfoExtension_FWD_DEFINED__
#define __ObjVisInfoExtension_FWD_DEFINED__

#ifdef __cplusplus
typedef class ObjVisInfoExtension ObjVisInfoExtension;
#else
typedef struct ObjVisInfoExtension ObjVisInfoExtension;
#endif /* __cplusplus */

#endif 	/* __ObjVisInfoExtension_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "TRiASBaseInterfaces.h"
#include "VisInfoInterfaces.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_Visinfo_0000 */
/* [local] */ 

#define VISINFO_TYPELIB_VERSION_MAJOR 1
#define VISINFO_TYPELIB_VERSION_MINOR 0
#define VISINFO_TYPELIB_VERSION "1.0"
#define VISINFO_TYPELIB_LCID 0


extern RPC_IF_HANDLE __MIDL_itf_Visinfo_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_Visinfo_0000_v0_0_s_ifspec;

#ifndef __IVisObjExt_INTERFACE_DEFINED__
#define __IVisObjExt_INTERFACE_DEFINED__

/* interface IVisObjExt */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IVisObjExt;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("079638E0-3123-101C-BB62-00AA0018497C")
    IVisObjExt : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetVisInfoClass( 
            /* [in] */ long lIdent,
            /* [in] */ VISINFOTYPE rgType,
            /* [optional][in] */ VARIANT vViewName,
            /* [retval][out] */ DVisInfo **ppIVisInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetVisInfoClass( 
            /* [in] */ long lIdent,
            /* [in] */ VISINFOTYPE rgType,
            /* [in] */ DVisInfo *pIVisInfo,
            /* [optional][in] */ VARIANT vViewName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ResetVisInfoClass( 
            /* [in] */ long lIdent,
            /* [in] */ VISINFOTYPE rgType,
            /* [optional][in] */ VARIANT vView) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetVisInfoObject( 
            /* [in] */ long lONr,
            /* [in] */ VISINFOTYPE rgType,
            /* [optional][in] */ VARIANT vViewName,
            /* [retval][out] */ DVisInfo **ppIVisInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetVisInfoObject( 
            /* [in] */ long lONr,
            /* [in] */ VISINFOTYPE rgType,
            /* [in] */ DVisInfo *pIVisInfo,
            /* [in] */ VARIANT_BOOL fSameAsSource,
            /* [optional][in] */ VARIANT vViewName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ResetVisInfoObject( 
            /* [in] */ long lONr,
            /* [in] */ VISINFOTYPE rgType,
            /* [optional][in] */ VARIANT vViewName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetObjectHiddenStatus( 
            /* [in] */ long lONr,
            /* [optional][in] */ VARIANT vViewName,
            /* [retval][out] */ VARIANT_BOOL *pfShow) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetObjectHiddenStatus( 
            /* [in] */ long lONr,
            /* [in] */ VARIANT_BOOL fShow,
            /* [optional][in] */ VARIANT vViewName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVisObjExtVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVisObjExt * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVisObjExt * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVisObjExt * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetVisInfoClass )( 
            IVisObjExt * This,
            /* [in] */ long lIdent,
            /* [in] */ VISINFOTYPE rgType,
            /* [optional][in] */ VARIANT vViewName,
            /* [retval][out] */ DVisInfo **ppIVisInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetVisInfoClass )( 
            IVisObjExt * This,
            /* [in] */ long lIdent,
            /* [in] */ VISINFOTYPE rgType,
            /* [in] */ DVisInfo *pIVisInfo,
            /* [optional][in] */ VARIANT vViewName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ResetVisInfoClass )( 
            IVisObjExt * This,
            /* [in] */ long lIdent,
            /* [in] */ VISINFOTYPE rgType,
            /* [optional][in] */ VARIANT vView);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetVisInfoObject )( 
            IVisObjExt * This,
            /* [in] */ long lONr,
            /* [in] */ VISINFOTYPE rgType,
            /* [optional][in] */ VARIANT vViewName,
            /* [retval][out] */ DVisInfo **ppIVisInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetVisInfoObject )( 
            IVisObjExt * This,
            /* [in] */ long lONr,
            /* [in] */ VISINFOTYPE rgType,
            /* [in] */ DVisInfo *pIVisInfo,
            /* [in] */ VARIANT_BOOL fSameAsSource,
            /* [optional][in] */ VARIANT vViewName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ResetVisInfoObject )( 
            IVisObjExt * This,
            /* [in] */ long lONr,
            /* [in] */ VISINFOTYPE rgType,
            /* [optional][in] */ VARIANT vViewName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetObjectHiddenStatus )( 
            IVisObjExt * This,
            /* [in] */ long lONr,
            /* [optional][in] */ VARIANT vViewName,
            /* [retval][out] */ VARIANT_BOOL *pfShow);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetObjectHiddenStatus )( 
            IVisObjExt * This,
            /* [in] */ long lONr,
            /* [in] */ VARIANT_BOOL fShow,
            /* [optional][in] */ VARIANT vViewName);
        
        END_INTERFACE
    } IVisObjExtVtbl;

    interface IVisObjExt
    {
        CONST_VTBL struct IVisObjExtVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVisObjExt_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVisObjExt_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVisObjExt_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVisObjExt_GetVisInfoClass(This,lIdent,rgType,vViewName,ppIVisInfo)	\
    (This)->lpVtbl -> GetVisInfoClass(This,lIdent,rgType,vViewName,ppIVisInfo)

#define IVisObjExt_SetVisInfoClass(This,lIdent,rgType,pIVisInfo,vViewName)	\
    (This)->lpVtbl -> SetVisInfoClass(This,lIdent,rgType,pIVisInfo,vViewName)

#define IVisObjExt_ResetVisInfoClass(This,lIdent,rgType,vView)	\
    (This)->lpVtbl -> ResetVisInfoClass(This,lIdent,rgType,vView)

#define IVisObjExt_GetVisInfoObject(This,lONr,rgType,vViewName,ppIVisInfo)	\
    (This)->lpVtbl -> GetVisInfoObject(This,lONr,rgType,vViewName,ppIVisInfo)

#define IVisObjExt_SetVisInfoObject(This,lONr,rgType,pIVisInfo,fSameAsSource,vViewName)	\
    (This)->lpVtbl -> SetVisInfoObject(This,lONr,rgType,pIVisInfo,fSameAsSource,vViewName)

#define IVisObjExt_ResetVisInfoObject(This,lONr,rgType,vViewName)	\
    (This)->lpVtbl -> ResetVisInfoObject(This,lONr,rgType,vViewName)

#define IVisObjExt_GetObjectHiddenStatus(This,lONr,vViewName,pfShow)	\
    (This)->lpVtbl -> GetObjectHiddenStatus(This,lONr,vViewName,pfShow)

#define IVisObjExt_SetObjectHiddenStatus(This,lONr,fShow,vViewName)	\
    (This)->lpVtbl -> SetObjectHiddenStatus(This,lONr,fShow,vViewName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisObjExt_GetVisInfoClass_Proxy( 
    IVisObjExt * This,
    /* [in] */ long lIdent,
    /* [in] */ VISINFOTYPE rgType,
    /* [optional][in] */ VARIANT vViewName,
    /* [retval][out] */ DVisInfo **ppIVisInfo);


void __RPC_STUB IVisObjExt_GetVisInfoClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisObjExt_SetVisInfoClass_Proxy( 
    IVisObjExt * This,
    /* [in] */ long lIdent,
    /* [in] */ VISINFOTYPE rgType,
    /* [in] */ DVisInfo *pIVisInfo,
    /* [optional][in] */ VARIANT vViewName);


void __RPC_STUB IVisObjExt_SetVisInfoClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisObjExt_ResetVisInfoClass_Proxy( 
    IVisObjExt * This,
    /* [in] */ long lIdent,
    /* [in] */ VISINFOTYPE rgType,
    /* [optional][in] */ VARIANT vView);


void __RPC_STUB IVisObjExt_ResetVisInfoClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisObjExt_GetVisInfoObject_Proxy( 
    IVisObjExt * This,
    /* [in] */ long lONr,
    /* [in] */ VISINFOTYPE rgType,
    /* [optional][in] */ VARIANT vViewName,
    /* [retval][out] */ DVisInfo **ppIVisInfo);


void __RPC_STUB IVisObjExt_GetVisInfoObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisObjExt_SetVisInfoObject_Proxy( 
    IVisObjExt * This,
    /* [in] */ long lONr,
    /* [in] */ VISINFOTYPE rgType,
    /* [in] */ DVisInfo *pIVisInfo,
    /* [in] */ VARIANT_BOOL fSameAsSource,
    /* [optional][in] */ VARIANT vViewName);


void __RPC_STUB IVisObjExt_SetVisInfoObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisObjExt_ResetVisInfoObject_Proxy( 
    IVisObjExt * This,
    /* [in] */ long lONr,
    /* [in] */ VISINFOTYPE rgType,
    /* [optional][in] */ VARIANT vViewName);


void __RPC_STUB IVisObjExt_ResetVisInfoObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisObjExt_GetObjectHiddenStatus_Proxy( 
    IVisObjExt * This,
    /* [in] */ long lONr,
    /* [optional][in] */ VARIANT vViewName,
    /* [retval][out] */ VARIANT_BOOL *pfShow);


void __RPC_STUB IVisObjExt_GetObjectHiddenStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisObjExt_SetObjectHiddenStatus_Proxy( 
    IVisObjExt * This,
    /* [in] */ long lONr,
    /* [in] */ VARIANT_BOOL fShow,
    /* [optional][in] */ VARIANT vViewName);


void __RPC_STUB IVisObjExt_SetObjectHiddenStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVisObjExt_INTERFACE_DEFINED__ */


#ifndef __IVisQuery_INTERFACE_DEFINED__
#define __IVisQuery_INTERFACE_DEFINED__

/* interface IVisQuery */
/* [object][unique][helpstring][uuid] */ 

typedef /* [public] */ 
enum _tagIDENTVISMODE
    {	IDENTVISMODE_NoAction	= 0,
	IDENTVISMODE_HasNewVI	= 0x1,
	IDENTVISMODE_WillDrawComplete	= 0x2,
	IDENTVISMODE_HideObject	= 0x4,
	IDENTVISMODE_ModVisInfo	= 0x100,
	IDENTVISMODE_ModShowStatus	= 0x200
    } 	IDENTVISMODE;


EXTERN_C const IID IID_IVisQuery;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("079638E3-3123-101C-BB62-00AA0018497C")
    IVisQuery : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetIdentMode( 
            /* [in] */ LONG Ident,
            BSTR View,
            /* [out][in] */ IDENTVISMODE *VisMode) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetObjectVis( 
            /* [in] */ LONG ObjNr,
            /* [out][in] */ DVisInfo **Vis) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVisQueryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVisQuery * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVisQuery * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVisQuery * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetIdentMode )( 
            IVisQuery * This,
            /* [in] */ LONG Ident,
            BSTR View,
            /* [out][in] */ IDENTVISMODE *VisMode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetObjectVis )( 
            IVisQuery * This,
            /* [in] */ LONG ObjNr,
            /* [out][in] */ DVisInfo **Vis);
        
        END_INTERFACE
    } IVisQueryVtbl;

    interface IVisQuery
    {
        CONST_VTBL struct IVisQueryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVisQuery_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVisQuery_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVisQuery_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVisQuery_GetIdentMode(This,Ident,View,VisMode)	\
    (This)->lpVtbl -> GetIdentMode(This,Ident,View,VisMode)

#define IVisQuery_GetObjectVis(This,ObjNr,Vis)	\
    (This)->lpVtbl -> GetObjectVis(This,ObjNr,Vis)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisQuery_GetIdentMode_Proxy( 
    IVisQuery * This,
    /* [in] */ LONG Ident,
    BSTR View,
    /* [out][in] */ IDENTVISMODE *VisMode);


void __RPC_STUB IVisQuery_GetIdentMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisQuery_GetObjectVis_Proxy( 
    IVisQuery * This,
    /* [in] */ LONG ObjNr,
    /* [out][in] */ DVisInfo **Vis);


void __RPC_STUB IVisQuery_GetObjectVis_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVisQuery_INTERFACE_DEFINED__ */


#ifndef __IMergeVisInfo_INTERFACE_DEFINED__
#define __IMergeVisInfo_INTERFACE_DEFINED__

/* interface IMergeVisInfo */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IMergeVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("079638E4-3123-101C-BB62-00AA0018497C")
    IMergeVisInfo : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE MergeVisInfo( 
            /* [in] */ VARIANT_BOOL OnlyChanged,
            /* [out][in] */ DVisInfo **VisInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMergeVisInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMergeVisInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMergeVisInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMergeVisInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *MergeVisInfo )( 
            IMergeVisInfo * This,
            /* [in] */ VARIANT_BOOL OnlyChanged,
            /* [out][in] */ DVisInfo **VisInfo);
        
        END_INTERFACE
    } IMergeVisInfoVtbl;

    interface IMergeVisInfo
    {
        CONST_VTBL struct IMergeVisInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMergeVisInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMergeVisInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMergeVisInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMergeVisInfo_MergeVisInfo(This,OnlyChanged,VisInfo)	\
    (This)->lpVtbl -> MergeVisInfo(This,OnlyChanged,VisInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMergeVisInfo_MergeVisInfo_Proxy( 
    IMergeVisInfo * This,
    /* [in] */ VARIANT_BOOL OnlyChanged,
    /* [out][in] */ DVisInfo **VisInfo);


void __RPC_STUB IMergeVisInfo_MergeVisInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMergeVisInfo_INTERFACE_DEFINED__ */


#ifndef __IRawVisInfo_INTERFACE_DEFINED__
#define __IRawVisInfo_INTERFACE_DEFINED__

/* interface IRawVisInfo */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRawVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4BAB20A3-A922-11D1-8588-00600875138A")
    IRawVisInfo : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetRawData( 
            /* [in] */ VISINFOTYPE rgType,
            /* [in] */ BSTR Data) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RetrieveRawData( 
            /* [in] */ VISINFOTYPE rgType,
            /* [retval][out] */ BSTR *Data) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRawVisInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRawVisInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRawVisInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRawVisInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetRawData )( 
            IRawVisInfo * This,
            /* [in] */ VISINFOTYPE rgType,
            /* [in] */ BSTR Data);
        
        HRESULT ( STDMETHODCALLTYPE *RetrieveRawData )( 
            IRawVisInfo * This,
            /* [in] */ VISINFOTYPE rgType,
            /* [retval][out] */ BSTR *Data);
        
        END_INTERFACE
    } IRawVisInfoVtbl;

    interface IRawVisInfo
    {
        CONST_VTBL struct IRawVisInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRawVisInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRawVisInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRawVisInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRawVisInfo_SetRawData(This,rgType,Data)	\
    (This)->lpVtbl -> SetRawData(This,rgType,Data)

#define IRawVisInfo_RetrieveRawData(This,rgType,Data)	\
    (This)->lpVtbl -> RetrieveRawData(This,rgType,Data)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRawVisInfo_SetRawData_Proxy( 
    IRawVisInfo * This,
    /* [in] */ VISINFOTYPE rgType,
    /* [in] */ BSTR Data);


void __RPC_STUB IRawVisInfo_SetRawData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRawVisInfo_RetrieveRawData_Proxy( 
    IRawVisInfo * This,
    /* [in] */ VISINFOTYPE rgType,
    /* [retval][out] */ BSTR *Data);


void __RPC_STUB IRawVisInfo_RetrieveRawData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRawVisInfo_INTERFACE_DEFINED__ */


#ifndef __IExtendedObjectVisInfo_INTERFACE_DEFINED__
#define __IExtendedObjectVisInfo_INTERFACE_DEFINED__

/* interface IExtendedObjectVisInfo */
/* [helpstring][uuid][object][oleautomation] */ 


EXTERN_C const IID IID_IExtendedObjectVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8B4834A5-EB76-4567-A97A-D38ACEE077A6")
    IExtendedObjectVisInfo : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HasInfos( 
            /* [retval][out] */ VARIANT_BOOL *HasInfos) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ModuleInfo( 
            /* [retval][out] */ BSTR *ModuleName) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ModuleInfo( 
            /* [in] */ BSTR ModuleName) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ExtendedInfo( 
            /* [retval][out] */ BSTR *VisString) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ExtendedInfo( 
            /* [in] */ BSTR VisString) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IExtendedObjectVisInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IExtendedObjectVisInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IExtendedObjectVisInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IExtendedObjectVisInfo * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasInfos )( 
            IExtendedObjectVisInfo * This,
            /* [retval][out] */ VARIANT_BOOL *HasInfos);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ModuleInfo )( 
            IExtendedObjectVisInfo * This,
            /* [retval][out] */ BSTR *ModuleName);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ModuleInfo )( 
            IExtendedObjectVisInfo * This,
            /* [in] */ BSTR ModuleName);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExtendedInfo )( 
            IExtendedObjectVisInfo * This,
            /* [retval][out] */ BSTR *VisString);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ExtendedInfo )( 
            IExtendedObjectVisInfo * This,
            /* [in] */ BSTR VisString);
        
        END_INTERFACE
    } IExtendedObjectVisInfoVtbl;

    interface IExtendedObjectVisInfo
    {
        CONST_VTBL struct IExtendedObjectVisInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IExtendedObjectVisInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IExtendedObjectVisInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IExtendedObjectVisInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IExtendedObjectVisInfo_get_HasInfos(This,HasInfos)	\
    (This)->lpVtbl -> get_HasInfos(This,HasInfos)

#define IExtendedObjectVisInfo_get_ModuleInfo(This,ModuleName)	\
    (This)->lpVtbl -> get_ModuleInfo(This,ModuleName)

#define IExtendedObjectVisInfo_put_ModuleInfo(This,ModuleName)	\
    (This)->lpVtbl -> put_ModuleInfo(This,ModuleName)

#define IExtendedObjectVisInfo_get_ExtendedInfo(This,VisString)	\
    (This)->lpVtbl -> get_ExtendedInfo(This,VisString)

#define IExtendedObjectVisInfo_put_ExtendedInfo(This,VisString)	\
    (This)->lpVtbl -> put_ExtendedInfo(This,VisString)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IExtendedObjectVisInfo_get_HasInfos_Proxy( 
    IExtendedObjectVisInfo * This,
    /* [retval][out] */ VARIANT_BOOL *HasInfos);


void __RPC_STUB IExtendedObjectVisInfo_get_HasInfos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IExtendedObjectVisInfo_get_ModuleInfo_Proxy( 
    IExtendedObjectVisInfo * This,
    /* [retval][out] */ BSTR *ModuleName);


void __RPC_STUB IExtendedObjectVisInfo_get_ModuleInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IExtendedObjectVisInfo_put_ModuleInfo_Proxy( 
    IExtendedObjectVisInfo * This,
    /* [in] */ BSTR ModuleName);


void __RPC_STUB IExtendedObjectVisInfo_put_ModuleInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IExtendedObjectVisInfo_get_ExtendedInfo_Proxy( 
    IExtendedObjectVisInfo * This,
    /* [retval][out] */ BSTR *VisString);


void __RPC_STUB IExtendedObjectVisInfo_get_ExtendedInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IExtendedObjectVisInfo_put_ExtendedInfo_Proxy( 
    IExtendedObjectVisInfo * This,
    /* [in] */ BSTR VisString);


void __RPC_STUB IExtendedObjectVisInfo_put_ExtendedInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IExtendedObjectVisInfo_INTERFACE_DEFINED__ */



#ifndef __VisInfoLib_LIBRARY_DEFINED__
#define __VisInfoLib_LIBRARY_DEFINED__

/* library VisInfoLib */
/* [helpstring][lcid][version][uuid] */ 


EXTERN_C const IID LIBID_VisInfoLib;

#ifndef __IVisInfo_INTERFACE_DEFINED__
#define __IVisInfo_INTERFACE_DEFINED__

/* interface IVisInfo */
/* [object][hidden][local][helpstring][oleautomation][uuid] */ 


EXTERN_C const IID IID_IVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("07963865-3123-101C-BB62-00AA0018497C")
    IVisInfo : public IUnknown
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_isA( 
            /* [retval][out] */ LONG *plRTTI) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch **ppIBase) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Parent( 
            /* [in] */ IDispatch *pIBase) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ IDispatch **ppIApp) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Application( 
            /* [in] */ IDispatch *pIApp) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Style( 
            /* [retval][out] */ int *piStyle) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Style( 
            /* [in] */ int iStyle) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Priority( 
            /* [retval][out] */ int *piPrio) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Priority( 
            /* [in] */ int iPrio) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pbstrDesc) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR bstrDesc) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_MainColor( 
            /* [retval][out] */ TRIASCOLOR *pocMain) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_MainColor( 
            /* [in] */ TRIASCOLOR ocMain) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVisInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVisInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVisInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVisInfo * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_isA )( 
            IVisInfo * This,
            /* [retval][out] */ LONG *plRTTI);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            IVisInfo * This,
            /* [retval][out] */ IDispatch **ppIBase);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Parent )( 
            IVisInfo * This,
            /* [in] */ IDispatch *pIBase);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            IVisInfo * This,
            /* [retval][out] */ IDispatch **ppIApp);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Application )( 
            IVisInfo * This,
            /* [in] */ IDispatch *pIApp);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Style )( 
            IVisInfo * This,
            /* [retval][out] */ int *piStyle);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Style )( 
            IVisInfo * This,
            /* [in] */ int iStyle);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Priority )( 
            IVisInfo * This,
            /* [retval][out] */ int *piPrio);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Priority )( 
            IVisInfo * This,
            /* [in] */ int iPrio);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IVisInfo * This,
            /* [retval][out] */ BSTR *pbstrDesc);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IVisInfo * This,
            /* [in] */ BSTR bstrDesc);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_MainColor )( 
            IVisInfo * This,
            /* [retval][out] */ TRIASCOLOR *pocMain);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_MainColor )( 
            IVisInfo * This,
            /* [in] */ TRIASCOLOR ocMain);
        
        END_INTERFACE
    } IVisInfoVtbl;

    interface IVisInfo
    {
        CONST_VTBL struct IVisInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVisInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVisInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVisInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVisInfo_get_isA(This,plRTTI)	\
    (This)->lpVtbl -> get_isA(This,plRTTI)

#define IVisInfo_get_Parent(This,ppIBase)	\
    (This)->lpVtbl -> get_Parent(This,ppIBase)

#define IVisInfo_put_Parent(This,pIBase)	\
    (This)->lpVtbl -> put_Parent(This,pIBase)

#define IVisInfo_get_Application(This,ppIApp)	\
    (This)->lpVtbl -> get_Application(This,ppIApp)

#define IVisInfo_put_Application(This,pIApp)	\
    (This)->lpVtbl -> put_Application(This,pIApp)

#define IVisInfo_get_Style(This,piStyle)	\
    (This)->lpVtbl -> get_Style(This,piStyle)

#define IVisInfo_put_Style(This,iStyle)	\
    (This)->lpVtbl -> put_Style(This,iStyle)

#define IVisInfo_get_Priority(This,piPrio)	\
    (This)->lpVtbl -> get_Priority(This,piPrio)

#define IVisInfo_put_Priority(This,iPrio)	\
    (This)->lpVtbl -> put_Priority(This,iPrio)

#define IVisInfo_get_Name(This,pbstrDesc)	\
    (This)->lpVtbl -> get_Name(This,pbstrDesc)

#define IVisInfo_put_Name(This,bstrDesc)	\
    (This)->lpVtbl -> put_Name(This,bstrDesc)

#define IVisInfo_get_MainColor(This,pocMain)	\
    (This)->lpVtbl -> get_MainColor(This,pocMain)

#define IVisInfo_put_MainColor(This,ocMain)	\
    (This)->lpVtbl -> put_MainColor(This,ocMain)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IVisInfo_get_isA_Proxy( 
    IVisInfo * This,
    /* [retval][out] */ LONG *plRTTI);


void __RPC_STUB IVisInfo_get_isA_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IVisInfo_get_Parent_Proxy( 
    IVisInfo * This,
    /* [retval][out] */ IDispatch **ppIBase);


void __RPC_STUB IVisInfo_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IVisInfo_put_Parent_Proxy( 
    IVisInfo * This,
    /* [in] */ IDispatch *pIBase);


void __RPC_STUB IVisInfo_put_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IVisInfo_get_Application_Proxy( 
    IVisInfo * This,
    /* [retval][out] */ IDispatch **ppIApp);


void __RPC_STUB IVisInfo_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IVisInfo_put_Application_Proxy( 
    IVisInfo * This,
    /* [in] */ IDispatch *pIApp);


void __RPC_STUB IVisInfo_put_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IVisInfo_get_Style_Proxy( 
    IVisInfo * This,
    /* [retval][out] */ int *piStyle);


void __RPC_STUB IVisInfo_get_Style_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IVisInfo_put_Style_Proxy( 
    IVisInfo * This,
    /* [in] */ int iStyle);


void __RPC_STUB IVisInfo_put_Style_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IVisInfo_get_Priority_Proxy( 
    IVisInfo * This,
    /* [retval][out] */ int *piPrio);


void __RPC_STUB IVisInfo_get_Priority_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IVisInfo_put_Priority_Proxy( 
    IVisInfo * This,
    /* [in] */ int iPrio);


void __RPC_STUB IVisInfo_put_Priority_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IVisInfo_get_Name_Proxy( 
    IVisInfo * This,
    /* [retval][out] */ BSTR *pbstrDesc);


void __RPC_STUB IVisInfo_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IVisInfo_put_Name_Proxy( 
    IVisInfo * This,
    /* [in] */ BSTR bstrDesc);


void __RPC_STUB IVisInfo_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IVisInfo_get_MainColor_Proxy( 
    IVisInfo * This,
    /* [retval][out] */ TRIASCOLOR *pocMain);


void __RPC_STUB IVisInfo_get_MainColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IVisInfo_put_MainColor_Proxy( 
    IVisInfo * This,
    /* [in] */ TRIASCOLOR ocMain);


void __RPC_STUB IVisInfo_put_MainColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVisInfo_INTERFACE_DEFINED__ */


#ifndef __IPointVisInfo_INTERFACE_DEFINED__
#define __IPointVisInfo_INTERFACE_DEFINED__

/* interface IPointVisInfo */
/* [object][hidden][local][helpstring][oleautomation][uuid] */ 


EXTERN_C const IID IID_IPointVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0796385E-3123-101C-BB62-00AA0018497C")
    IPointVisInfo : public IVisInfo
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_SizeX( 
            /* [retval][out] */ int *piX) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_SizeX( 
            /* [in] */ int iX) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_SizeY( 
            /* [retval][out] */ int *piY) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_SizeY( 
            /* [in] */ int iY) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Rotate( 
            /* [retval][out] */ int *piRot) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Rotate( 
            /* [in] */ int iRot) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_BkColor( 
            /* [retval][out] */ TRIASCOLOR *pocBack) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_BkColor( 
            /* [in] */ TRIASCOLOR ocBack) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPointVisInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPointVisInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPointVisInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPointVisInfo * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_isA )( 
            IPointVisInfo * This,
            /* [retval][out] */ LONG *plRTTI);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            IPointVisInfo * This,
            /* [retval][out] */ IDispatch **ppIBase);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Parent )( 
            IPointVisInfo * This,
            /* [in] */ IDispatch *pIBase);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            IPointVisInfo * This,
            /* [retval][out] */ IDispatch **ppIApp);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Application )( 
            IPointVisInfo * This,
            /* [in] */ IDispatch *pIApp);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Style )( 
            IPointVisInfo * This,
            /* [retval][out] */ int *piStyle);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Style )( 
            IPointVisInfo * This,
            /* [in] */ int iStyle);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Priority )( 
            IPointVisInfo * This,
            /* [retval][out] */ int *piPrio);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Priority )( 
            IPointVisInfo * This,
            /* [in] */ int iPrio);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IPointVisInfo * This,
            /* [retval][out] */ BSTR *pbstrDesc);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IPointVisInfo * This,
            /* [in] */ BSTR bstrDesc);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_MainColor )( 
            IPointVisInfo * This,
            /* [retval][out] */ TRIASCOLOR *pocMain);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_MainColor )( 
            IPointVisInfo * This,
            /* [in] */ TRIASCOLOR ocMain);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_SizeX )( 
            IPointVisInfo * This,
            /* [retval][out] */ int *piX);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_SizeX )( 
            IPointVisInfo * This,
            /* [in] */ int iX);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_SizeY )( 
            IPointVisInfo * This,
            /* [retval][out] */ int *piY);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_SizeY )( 
            IPointVisInfo * This,
            /* [in] */ int iY);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Rotate )( 
            IPointVisInfo * This,
            /* [retval][out] */ int *piRot);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Rotate )( 
            IPointVisInfo * This,
            /* [in] */ int iRot);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_BkColor )( 
            IPointVisInfo * This,
            /* [retval][out] */ TRIASCOLOR *pocBack);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_BkColor )( 
            IPointVisInfo * This,
            /* [in] */ TRIASCOLOR ocBack);
        
        END_INTERFACE
    } IPointVisInfoVtbl;

    interface IPointVisInfo
    {
        CONST_VTBL struct IPointVisInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPointVisInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPointVisInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPointVisInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPointVisInfo_get_isA(This,plRTTI)	\
    (This)->lpVtbl -> get_isA(This,plRTTI)

#define IPointVisInfo_get_Parent(This,ppIBase)	\
    (This)->lpVtbl -> get_Parent(This,ppIBase)

#define IPointVisInfo_put_Parent(This,pIBase)	\
    (This)->lpVtbl -> put_Parent(This,pIBase)

#define IPointVisInfo_get_Application(This,ppIApp)	\
    (This)->lpVtbl -> get_Application(This,ppIApp)

#define IPointVisInfo_put_Application(This,pIApp)	\
    (This)->lpVtbl -> put_Application(This,pIApp)

#define IPointVisInfo_get_Style(This,piStyle)	\
    (This)->lpVtbl -> get_Style(This,piStyle)

#define IPointVisInfo_put_Style(This,iStyle)	\
    (This)->lpVtbl -> put_Style(This,iStyle)

#define IPointVisInfo_get_Priority(This,piPrio)	\
    (This)->lpVtbl -> get_Priority(This,piPrio)

#define IPointVisInfo_put_Priority(This,iPrio)	\
    (This)->lpVtbl -> put_Priority(This,iPrio)

#define IPointVisInfo_get_Name(This,pbstrDesc)	\
    (This)->lpVtbl -> get_Name(This,pbstrDesc)

#define IPointVisInfo_put_Name(This,bstrDesc)	\
    (This)->lpVtbl -> put_Name(This,bstrDesc)

#define IPointVisInfo_get_MainColor(This,pocMain)	\
    (This)->lpVtbl -> get_MainColor(This,pocMain)

#define IPointVisInfo_put_MainColor(This,ocMain)	\
    (This)->lpVtbl -> put_MainColor(This,ocMain)


#define IPointVisInfo_get_SizeX(This,piX)	\
    (This)->lpVtbl -> get_SizeX(This,piX)

#define IPointVisInfo_put_SizeX(This,iX)	\
    (This)->lpVtbl -> put_SizeX(This,iX)

#define IPointVisInfo_get_SizeY(This,piY)	\
    (This)->lpVtbl -> get_SizeY(This,piY)

#define IPointVisInfo_put_SizeY(This,iY)	\
    (This)->lpVtbl -> put_SizeY(This,iY)

#define IPointVisInfo_get_Rotate(This,piRot)	\
    (This)->lpVtbl -> get_Rotate(This,piRot)

#define IPointVisInfo_put_Rotate(This,iRot)	\
    (This)->lpVtbl -> put_Rotate(This,iRot)

#define IPointVisInfo_get_BkColor(This,pocBack)	\
    (This)->lpVtbl -> get_BkColor(This,pocBack)

#define IPointVisInfo_put_BkColor(This,ocBack)	\
    (This)->lpVtbl -> put_BkColor(This,ocBack)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IPointVisInfo_get_SizeX_Proxy( 
    IPointVisInfo * This,
    /* [retval][out] */ int *piX);


void __RPC_STUB IPointVisInfo_get_SizeX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPointVisInfo_put_SizeX_Proxy( 
    IPointVisInfo * This,
    /* [in] */ int iX);


void __RPC_STUB IPointVisInfo_put_SizeX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPointVisInfo_get_SizeY_Proxy( 
    IPointVisInfo * This,
    /* [retval][out] */ int *piY);


void __RPC_STUB IPointVisInfo_get_SizeY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPointVisInfo_put_SizeY_Proxy( 
    IPointVisInfo * This,
    /* [in] */ int iY);


void __RPC_STUB IPointVisInfo_put_SizeY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPointVisInfo_get_Rotate_Proxy( 
    IPointVisInfo * This,
    /* [retval][out] */ int *piRot);


void __RPC_STUB IPointVisInfo_get_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPointVisInfo_put_Rotate_Proxy( 
    IPointVisInfo * This,
    /* [in] */ int iRot);


void __RPC_STUB IPointVisInfo_put_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPointVisInfo_get_BkColor_Proxy( 
    IPointVisInfo * This,
    /* [retval][out] */ TRIASCOLOR *pocBack);


void __RPC_STUB IPointVisInfo_get_BkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPointVisInfo_put_BkColor_Proxy( 
    IPointVisInfo * This,
    /* [in] */ TRIASCOLOR ocBack);


void __RPC_STUB IPointVisInfo_put_BkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPointVisInfo_INTERFACE_DEFINED__ */


#ifndef __ILineVisInfo_INTERFACE_DEFINED__
#define __ILineVisInfo_INTERFACE_DEFINED__

/* interface ILineVisInfo */
/* [object][hidden][local][helpstring][oleautomation][uuid] */ 


EXTERN_C const IID IID_ILineVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("07963860-3123-101C-BB62-00AA0018497C")
    ILineVisInfo : public IVisInfo
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ int *piWidth) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ int iWidth) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILineVisInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILineVisInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILineVisInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILineVisInfo * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_isA )( 
            ILineVisInfo * This,
            /* [retval][out] */ LONG *plRTTI);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            ILineVisInfo * This,
            /* [retval][out] */ IDispatch **ppIBase);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Parent )( 
            ILineVisInfo * This,
            /* [in] */ IDispatch *pIBase);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            ILineVisInfo * This,
            /* [retval][out] */ IDispatch **ppIApp);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Application )( 
            ILineVisInfo * This,
            /* [in] */ IDispatch *pIApp);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Style )( 
            ILineVisInfo * This,
            /* [retval][out] */ int *piStyle);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Style )( 
            ILineVisInfo * This,
            /* [in] */ int iStyle);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Priority )( 
            ILineVisInfo * This,
            /* [retval][out] */ int *piPrio);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Priority )( 
            ILineVisInfo * This,
            /* [in] */ int iPrio);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ILineVisInfo * This,
            /* [retval][out] */ BSTR *pbstrDesc);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            ILineVisInfo * This,
            /* [in] */ BSTR bstrDesc);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_MainColor )( 
            ILineVisInfo * This,
            /* [retval][out] */ TRIASCOLOR *pocMain);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_MainColor )( 
            ILineVisInfo * This,
            /* [in] */ TRIASCOLOR ocMain);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            ILineVisInfo * This,
            /* [retval][out] */ int *piWidth);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Width )( 
            ILineVisInfo * This,
            /* [in] */ int iWidth);
        
        END_INTERFACE
    } ILineVisInfoVtbl;

    interface ILineVisInfo
    {
        CONST_VTBL struct ILineVisInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILineVisInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILineVisInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILineVisInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILineVisInfo_get_isA(This,plRTTI)	\
    (This)->lpVtbl -> get_isA(This,plRTTI)

#define ILineVisInfo_get_Parent(This,ppIBase)	\
    (This)->lpVtbl -> get_Parent(This,ppIBase)

#define ILineVisInfo_put_Parent(This,pIBase)	\
    (This)->lpVtbl -> put_Parent(This,pIBase)

#define ILineVisInfo_get_Application(This,ppIApp)	\
    (This)->lpVtbl -> get_Application(This,ppIApp)

#define ILineVisInfo_put_Application(This,pIApp)	\
    (This)->lpVtbl -> put_Application(This,pIApp)

#define ILineVisInfo_get_Style(This,piStyle)	\
    (This)->lpVtbl -> get_Style(This,piStyle)

#define ILineVisInfo_put_Style(This,iStyle)	\
    (This)->lpVtbl -> put_Style(This,iStyle)

#define ILineVisInfo_get_Priority(This,piPrio)	\
    (This)->lpVtbl -> get_Priority(This,piPrio)

#define ILineVisInfo_put_Priority(This,iPrio)	\
    (This)->lpVtbl -> put_Priority(This,iPrio)

#define ILineVisInfo_get_Name(This,pbstrDesc)	\
    (This)->lpVtbl -> get_Name(This,pbstrDesc)

#define ILineVisInfo_put_Name(This,bstrDesc)	\
    (This)->lpVtbl -> put_Name(This,bstrDesc)

#define ILineVisInfo_get_MainColor(This,pocMain)	\
    (This)->lpVtbl -> get_MainColor(This,pocMain)

#define ILineVisInfo_put_MainColor(This,ocMain)	\
    (This)->lpVtbl -> put_MainColor(This,ocMain)


#define ILineVisInfo_get_Width(This,piWidth)	\
    (This)->lpVtbl -> get_Width(This,piWidth)

#define ILineVisInfo_put_Width(This,iWidth)	\
    (This)->lpVtbl -> put_Width(This,iWidth)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE ILineVisInfo_get_Width_Proxy( 
    ILineVisInfo * This,
    /* [retval][out] */ int *piWidth);


void __RPC_STUB ILineVisInfo_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ILineVisInfo_put_Width_Proxy( 
    ILineVisInfo * This,
    /* [in] */ int iWidth);


void __RPC_STUB ILineVisInfo_put_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILineVisInfo_INTERFACE_DEFINED__ */


#ifndef __IAreaVisInfo_INTERFACE_DEFINED__
#define __IAreaVisInfo_INTERFACE_DEFINED__

/* interface IAreaVisInfo */
/* [object][hidden][local][helpstring][oleautomation][uuid] */ 


EXTERN_C const IID IID_IAreaVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("07963862-3123-101C-BB62-00AA0018497C")
    IAreaVisInfo : public IVisInfo
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ int *piWidth) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ int iWidth) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Opaque( 
            /* [retval][out] */ int *pfOpaque) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Opaque( 
            /* [in] */ int fOpaque) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_BkContour( 
            /* [retval][out] */ int *pfBkContour) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_BkContour( 
            /* [in] */ int fBkContour) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_BkColor( 
            /* [retval][out] */ TRIASCOLOR *pocBack) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_BkColor( 
            /* [in] */ TRIASCOLOR ocBack) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAreaVisInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAreaVisInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAreaVisInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAreaVisInfo * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_isA )( 
            IAreaVisInfo * This,
            /* [retval][out] */ LONG *plRTTI);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            IAreaVisInfo * This,
            /* [retval][out] */ IDispatch **ppIBase);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Parent )( 
            IAreaVisInfo * This,
            /* [in] */ IDispatch *pIBase);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            IAreaVisInfo * This,
            /* [retval][out] */ IDispatch **ppIApp);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Application )( 
            IAreaVisInfo * This,
            /* [in] */ IDispatch *pIApp);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Style )( 
            IAreaVisInfo * This,
            /* [retval][out] */ int *piStyle);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Style )( 
            IAreaVisInfo * This,
            /* [in] */ int iStyle);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Priority )( 
            IAreaVisInfo * This,
            /* [retval][out] */ int *piPrio);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Priority )( 
            IAreaVisInfo * This,
            /* [in] */ int iPrio);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IAreaVisInfo * This,
            /* [retval][out] */ BSTR *pbstrDesc);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IAreaVisInfo * This,
            /* [in] */ BSTR bstrDesc);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_MainColor )( 
            IAreaVisInfo * This,
            /* [retval][out] */ TRIASCOLOR *pocMain);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_MainColor )( 
            IAreaVisInfo * This,
            /* [in] */ TRIASCOLOR ocMain);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            IAreaVisInfo * This,
            /* [retval][out] */ int *piWidth);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Width )( 
            IAreaVisInfo * This,
            /* [in] */ int iWidth);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Opaque )( 
            IAreaVisInfo * This,
            /* [retval][out] */ int *pfOpaque);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Opaque )( 
            IAreaVisInfo * This,
            /* [in] */ int fOpaque);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_BkContour )( 
            IAreaVisInfo * This,
            /* [retval][out] */ int *pfBkContour);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_BkContour )( 
            IAreaVisInfo * This,
            /* [in] */ int fBkContour);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_BkColor )( 
            IAreaVisInfo * This,
            /* [retval][out] */ TRIASCOLOR *pocBack);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_BkColor )( 
            IAreaVisInfo * This,
            /* [in] */ TRIASCOLOR ocBack);
        
        END_INTERFACE
    } IAreaVisInfoVtbl;

    interface IAreaVisInfo
    {
        CONST_VTBL struct IAreaVisInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAreaVisInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAreaVisInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAreaVisInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAreaVisInfo_get_isA(This,plRTTI)	\
    (This)->lpVtbl -> get_isA(This,plRTTI)

#define IAreaVisInfo_get_Parent(This,ppIBase)	\
    (This)->lpVtbl -> get_Parent(This,ppIBase)

#define IAreaVisInfo_put_Parent(This,pIBase)	\
    (This)->lpVtbl -> put_Parent(This,pIBase)

#define IAreaVisInfo_get_Application(This,ppIApp)	\
    (This)->lpVtbl -> get_Application(This,ppIApp)

#define IAreaVisInfo_put_Application(This,pIApp)	\
    (This)->lpVtbl -> put_Application(This,pIApp)

#define IAreaVisInfo_get_Style(This,piStyle)	\
    (This)->lpVtbl -> get_Style(This,piStyle)

#define IAreaVisInfo_put_Style(This,iStyle)	\
    (This)->lpVtbl -> put_Style(This,iStyle)

#define IAreaVisInfo_get_Priority(This,piPrio)	\
    (This)->lpVtbl -> get_Priority(This,piPrio)

#define IAreaVisInfo_put_Priority(This,iPrio)	\
    (This)->lpVtbl -> put_Priority(This,iPrio)

#define IAreaVisInfo_get_Name(This,pbstrDesc)	\
    (This)->lpVtbl -> get_Name(This,pbstrDesc)

#define IAreaVisInfo_put_Name(This,bstrDesc)	\
    (This)->lpVtbl -> put_Name(This,bstrDesc)

#define IAreaVisInfo_get_MainColor(This,pocMain)	\
    (This)->lpVtbl -> get_MainColor(This,pocMain)

#define IAreaVisInfo_put_MainColor(This,ocMain)	\
    (This)->lpVtbl -> put_MainColor(This,ocMain)


#define IAreaVisInfo_get_Width(This,piWidth)	\
    (This)->lpVtbl -> get_Width(This,piWidth)

#define IAreaVisInfo_put_Width(This,iWidth)	\
    (This)->lpVtbl -> put_Width(This,iWidth)

#define IAreaVisInfo_get_Opaque(This,pfOpaque)	\
    (This)->lpVtbl -> get_Opaque(This,pfOpaque)

#define IAreaVisInfo_put_Opaque(This,fOpaque)	\
    (This)->lpVtbl -> put_Opaque(This,fOpaque)

#define IAreaVisInfo_get_BkContour(This,pfBkContour)	\
    (This)->lpVtbl -> get_BkContour(This,pfBkContour)

#define IAreaVisInfo_put_BkContour(This,fBkContour)	\
    (This)->lpVtbl -> put_BkContour(This,fBkContour)

#define IAreaVisInfo_get_BkColor(This,pocBack)	\
    (This)->lpVtbl -> get_BkColor(This,pocBack)

#define IAreaVisInfo_put_BkColor(This,ocBack)	\
    (This)->lpVtbl -> put_BkColor(This,ocBack)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IAreaVisInfo_get_Width_Proxy( 
    IAreaVisInfo * This,
    /* [retval][out] */ int *piWidth);


void __RPC_STUB IAreaVisInfo_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IAreaVisInfo_put_Width_Proxy( 
    IAreaVisInfo * This,
    /* [in] */ int iWidth);


void __RPC_STUB IAreaVisInfo_put_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IAreaVisInfo_get_Opaque_Proxy( 
    IAreaVisInfo * This,
    /* [retval][out] */ int *pfOpaque);


void __RPC_STUB IAreaVisInfo_get_Opaque_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IAreaVisInfo_put_Opaque_Proxy( 
    IAreaVisInfo * This,
    /* [in] */ int fOpaque);


void __RPC_STUB IAreaVisInfo_put_Opaque_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IAreaVisInfo_get_BkContour_Proxy( 
    IAreaVisInfo * This,
    /* [retval][out] */ int *pfBkContour);


void __RPC_STUB IAreaVisInfo_get_BkContour_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IAreaVisInfo_put_BkContour_Proxy( 
    IAreaVisInfo * This,
    /* [in] */ int fBkContour);


void __RPC_STUB IAreaVisInfo_put_BkContour_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IAreaVisInfo_get_BkColor_Proxy( 
    IAreaVisInfo * This,
    /* [retval][out] */ TRIASCOLOR *pocBack);


void __RPC_STUB IAreaVisInfo_get_BkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IAreaVisInfo_put_BkColor_Proxy( 
    IAreaVisInfo * This,
    /* [in] */ TRIASCOLOR ocBack);


void __RPC_STUB IAreaVisInfo_put_BkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAreaVisInfo_INTERFACE_DEFINED__ */


#ifndef __ITextVisInfo_INTERFACE_DEFINED__
#define __ITextVisInfo_INTERFACE_DEFINED__

/* interface ITextVisInfo */
/* [object][hidden][local][helpstring][oleautomation][uuid] */ 


EXTERN_C const IID IID_ITextVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("07963864-3123-101C-BB62-00AA0018497C")
    ITextVisInfo : public IVisInfo
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_SizeX( 
            /* [retval][out] */ int *piX) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_SizeX( 
            /* [in] */ int iX) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_SizeY( 
            /* [retval][out] */ int *piY) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_SizeY( 
            /* [in] */ int iY) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Bold( 
            /* [retval][out] */ int *pfBold) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Bold( 
            /* [in] */ int fBold) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Italic( 
            /* [retval][out] */ int *pfItalic) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Italic( 
            /* [in] */ int fItalic) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Underline( 
            /* [retval][out] */ int *pfUnderline) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Underline( 
            /* [in] */ int fUnderline) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_StrikeThrough( 
            /* [retval][out] */ int *pfStrikeThrough) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_StrikeThrough( 
            /* [in] */ int fStrikeThrough) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_FrameStyle( 
            /* [retval][out] */ FRAMESTYLE *prgFrameStyle) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_FrameStyle( 
            /* [in] */ FRAMESTYLE rgFrameStyle) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_AlignStyle( 
            /* [retval][out] */ ALIGNSTYLE *prgAlign) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_AlignStyle( 
            /* [in] */ ALIGNSTYLE rgAlign) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Rotate( 
            /* [retval][out] */ int *piRot) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Rotate( 
            /* [in] */ int iRot) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Slant( 
            /* [retval][out] */ int *piSlant) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Slant( 
            /* [in] */ int iSlant) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITextVisInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITextVisInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITextVisInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITextVisInfo * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_isA )( 
            ITextVisInfo * This,
            /* [retval][out] */ LONG *plRTTI);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            ITextVisInfo * This,
            /* [retval][out] */ IDispatch **ppIBase);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Parent )( 
            ITextVisInfo * This,
            /* [in] */ IDispatch *pIBase);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            ITextVisInfo * This,
            /* [retval][out] */ IDispatch **ppIApp);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Application )( 
            ITextVisInfo * This,
            /* [in] */ IDispatch *pIApp);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Style )( 
            ITextVisInfo * This,
            /* [retval][out] */ int *piStyle);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Style )( 
            ITextVisInfo * This,
            /* [in] */ int iStyle);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Priority )( 
            ITextVisInfo * This,
            /* [retval][out] */ int *piPrio);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Priority )( 
            ITextVisInfo * This,
            /* [in] */ int iPrio);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ITextVisInfo * This,
            /* [retval][out] */ BSTR *pbstrDesc);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            ITextVisInfo * This,
            /* [in] */ BSTR bstrDesc);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_MainColor )( 
            ITextVisInfo * This,
            /* [retval][out] */ TRIASCOLOR *pocMain);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_MainColor )( 
            ITextVisInfo * This,
            /* [in] */ TRIASCOLOR ocMain);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_SizeX )( 
            ITextVisInfo * This,
            /* [retval][out] */ int *piX);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_SizeX )( 
            ITextVisInfo * This,
            /* [in] */ int iX);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_SizeY )( 
            ITextVisInfo * This,
            /* [retval][out] */ int *piY);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_SizeY )( 
            ITextVisInfo * This,
            /* [in] */ int iY);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Bold )( 
            ITextVisInfo * This,
            /* [retval][out] */ int *pfBold);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Bold )( 
            ITextVisInfo * This,
            /* [in] */ int fBold);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Italic )( 
            ITextVisInfo * This,
            /* [retval][out] */ int *pfItalic);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Italic )( 
            ITextVisInfo * This,
            /* [in] */ int fItalic);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Underline )( 
            ITextVisInfo * This,
            /* [retval][out] */ int *pfUnderline);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Underline )( 
            ITextVisInfo * This,
            /* [in] */ int fUnderline);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_StrikeThrough )( 
            ITextVisInfo * This,
            /* [retval][out] */ int *pfStrikeThrough);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_StrikeThrough )( 
            ITextVisInfo * This,
            /* [in] */ int fStrikeThrough);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_FrameStyle )( 
            ITextVisInfo * This,
            /* [retval][out] */ FRAMESTYLE *prgFrameStyle);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_FrameStyle )( 
            ITextVisInfo * This,
            /* [in] */ FRAMESTYLE rgFrameStyle);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_AlignStyle )( 
            ITextVisInfo * This,
            /* [retval][out] */ ALIGNSTYLE *prgAlign);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_AlignStyle )( 
            ITextVisInfo * This,
            /* [in] */ ALIGNSTYLE rgAlign);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Rotate )( 
            ITextVisInfo * This,
            /* [retval][out] */ int *piRot);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Rotate )( 
            ITextVisInfo * This,
            /* [in] */ int iRot);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Slant )( 
            ITextVisInfo * This,
            /* [retval][out] */ int *piSlant);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Slant )( 
            ITextVisInfo * This,
            /* [in] */ int iSlant);
        
        END_INTERFACE
    } ITextVisInfoVtbl;

    interface ITextVisInfo
    {
        CONST_VTBL struct ITextVisInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITextVisInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITextVisInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITextVisInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITextVisInfo_get_isA(This,plRTTI)	\
    (This)->lpVtbl -> get_isA(This,plRTTI)

#define ITextVisInfo_get_Parent(This,ppIBase)	\
    (This)->lpVtbl -> get_Parent(This,ppIBase)

#define ITextVisInfo_put_Parent(This,pIBase)	\
    (This)->lpVtbl -> put_Parent(This,pIBase)

#define ITextVisInfo_get_Application(This,ppIApp)	\
    (This)->lpVtbl -> get_Application(This,ppIApp)

#define ITextVisInfo_put_Application(This,pIApp)	\
    (This)->lpVtbl -> put_Application(This,pIApp)

#define ITextVisInfo_get_Style(This,piStyle)	\
    (This)->lpVtbl -> get_Style(This,piStyle)

#define ITextVisInfo_put_Style(This,iStyle)	\
    (This)->lpVtbl -> put_Style(This,iStyle)

#define ITextVisInfo_get_Priority(This,piPrio)	\
    (This)->lpVtbl -> get_Priority(This,piPrio)

#define ITextVisInfo_put_Priority(This,iPrio)	\
    (This)->lpVtbl -> put_Priority(This,iPrio)

#define ITextVisInfo_get_Name(This,pbstrDesc)	\
    (This)->lpVtbl -> get_Name(This,pbstrDesc)

#define ITextVisInfo_put_Name(This,bstrDesc)	\
    (This)->lpVtbl -> put_Name(This,bstrDesc)

#define ITextVisInfo_get_MainColor(This,pocMain)	\
    (This)->lpVtbl -> get_MainColor(This,pocMain)

#define ITextVisInfo_put_MainColor(This,ocMain)	\
    (This)->lpVtbl -> put_MainColor(This,ocMain)


#define ITextVisInfo_get_SizeX(This,piX)	\
    (This)->lpVtbl -> get_SizeX(This,piX)

#define ITextVisInfo_put_SizeX(This,iX)	\
    (This)->lpVtbl -> put_SizeX(This,iX)

#define ITextVisInfo_get_SizeY(This,piY)	\
    (This)->lpVtbl -> get_SizeY(This,piY)

#define ITextVisInfo_put_SizeY(This,iY)	\
    (This)->lpVtbl -> put_SizeY(This,iY)

#define ITextVisInfo_get_Bold(This,pfBold)	\
    (This)->lpVtbl -> get_Bold(This,pfBold)

#define ITextVisInfo_put_Bold(This,fBold)	\
    (This)->lpVtbl -> put_Bold(This,fBold)

#define ITextVisInfo_get_Italic(This,pfItalic)	\
    (This)->lpVtbl -> get_Italic(This,pfItalic)

#define ITextVisInfo_put_Italic(This,fItalic)	\
    (This)->lpVtbl -> put_Italic(This,fItalic)

#define ITextVisInfo_get_Underline(This,pfUnderline)	\
    (This)->lpVtbl -> get_Underline(This,pfUnderline)

#define ITextVisInfo_put_Underline(This,fUnderline)	\
    (This)->lpVtbl -> put_Underline(This,fUnderline)

#define ITextVisInfo_get_StrikeThrough(This,pfStrikeThrough)	\
    (This)->lpVtbl -> get_StrikeThrough(This,pfStrikeThrough)

#define ITextVisInfo_put_StrikeThrough(This,fStrikeThrough)	\
    (This)->lpVtbl -> put_StrikeThrough(This,fStrikeThrough)

#define ITextVisInfo_get_FrameStyle(This,prgFrameStyle)	\
    (This)->lpVtbl -> get_FrameStyle(This,prgFrameStyle)

#define ITextVisInfo_put_FrameStyle(This,rgFrameStyle)	\
    (This)->lpVtbl -> put_FrameStyle(This,rgFrameStyle)

#define ITextVisInfo_get_AlignStyle(This,prgAlign)	\
    (This)->lpVtbl -> get_AlignStyle(This,prgAlign)

#define ITextVisInfo_put_AlignStyle(This,rgAlign)	\
    (This)->lpVtbl -> put_AlignStyle(This,rgAlign)

#define ITextVisInfo_get_Rotate(This,piRot)	\
    (This)->lpVtbl -> get_Rotate(This,piRot)

#define ITextVisInfo_put_Rotate(This,iRot)	\
    (This)->lpVtbl -> put_Rotate(This,iRot)

#define ITextVisInfo_get_Slant(This,piSlant)	\
    (This)->lpVtbl -> get_Slant(This,piSlant)

#define ITextVisInfo_put_Slant(This,iSlant)	\
    (This)->lpVtbl -> put_Slant(This,iSlant)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_get_SizeX_Proxy( 
    ITextVisInfo * This,
    /* [retval][out] */ int *piX);


void __RPC_STUB ITextVisInfo_get_SizeX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_put_SizeX_Proxy( 
    ITextVisInfo * This,
    /* [in] */ int iX);


void __RPC_STUB ITextVisInfo_put_SizeX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_get_SizeY_Proxy( 
    ITextVisInfo * This,
    /* [retval][out] */ int *piY);


void __RPC_STUB ITextVisInfo_get_SizeY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_put_SizeY_Proxy( 
    ITextVisInfo * This,
    /* [in] */ int iY);


void __RPC_STUB ITextVisInfo_put_SizeY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_get_Bold_Proxy( 
    ITextVisInfo * This,
    /* [retval][out] */ int *pfBold);


void __RPC_STUB ITextVisInfo_get_Bold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_put_Bold_Proxy( 
    ITextVisInfo * This,
    /* [in] */ int fBold);


void __RPC_STUB ITextVisInfo_put_Bold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_get_Italic_Proxy( 
    ITextVisInfo * This,
    /* [retval][out] */ int *pfItalic);


void __RPC_STUB ITextVisInfo_get_Italic_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_put_Italic_Proxy( 
    ITextVisInfo * This,
    /* [in] */ int fItalic);


void __RPC_STUB ITextVisInfo_put_Italic_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_get_Underline_Proxy( 
    ITextVisInfo * This,
    /* [retval][out] */ int *pfUnderline);


void __RPC_STUB ITextVisInfo_get_Underline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_put_Underline_Proxy( 
    ITextVisInfo * This,
    /* [in] */ int fUnderline);


void __RPC_STUB ITextVisInfo_put_Underline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_get_StrikeThrough_Proxy( 
    ITextVisInfo * This,
    /* [retval][out] */ int *pfStrikeThrough);


void __RPC_STUB ITextVisInfo_get_StrikeThrough_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_put_StrikeThrough_Proxy( 
    ITextVisInfo * This,
    /* [in] */ int fStrikeThrough);


void __RPC_STUB ITextVisInfo_put_StrikeThrough_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_get_FrameStyle_Proxy( 
    ITextVisInfo * This,
    /* [retval][out] */ FRAMESTYLE *prgFrameStyle);


void __RPC_STUB ITextVisInfo_get_FrameStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_put_FrameStyle_Proxy( 
    ITextVisInfo * This,
    /* [in] */ FRAMESTYLE rgFrameStyle);


void __RPC_STUB ITextVisInfo_put_FrameStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_get_AlignStyle_Proxy( 
    ITextVisInfo * This,
    /* [retval][out] */ ALIGNSTYLE *prgAlign);


void __RPC_STUB ITextVisInfo_get_AlignStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_put_AlignStyle_Proxy( 
    ITextVisInfo * This,
    /* [in] */ ALIGNSTYLE rgAlign);


void __RPC_STUB ITextVisInfo_put_AlignStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_get_Rotate_Proxy( 
    ITextVisInfo * This,
    /* [retval][out] */ int *piRot);


void __RPC_STUB ITextVisInfo_get_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_put_Rotate_Proxy( 
    ITextVisInfo * This,
    /* [in] */ int iRot);


void __RPC_STUB ITextVisInfo_put_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_get_Slant_Proxy( 
    ITextVisInfo * This,
    /* [retval][out] */ int *piSlant);


void __RPC_STUB ITextVisInfo_get_Slant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_put_Slant_Proxy( 
    ITextVisInfo * This,
    /* [in] */ int iSlant);


void __RPC_STUB ITextVisInfo_put_Slant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITextVisInfo_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_DefaultVisInfo;

#ifdef __cplusplus

class DECLSPEC_UUID("289BE0C4-92F6-11D1-BA03-080036D63803")
DefaultVisInfo;
#endif

EXTERN_C const CLSID CLSID_PointVisInfo;

#ifdef __cplusplus

class DECLSPEC_UUID("0796385D-3123-101C-BB62-00AA0018497C")
PointVisInfo;
#endif

EXTERN_C const CLSID CLSID_LineVisInfo;

#ifdef __cplusplus

class DECLSPEC_UUID("0796385F-3123-101C-BB62-00AA0018497C")
LineVisInfo;
#endif

EXTERN_C const CLSID CLSID_AreaVisInfo;

#ifdef __cplusplus

class DECLSPEC_UUID("07963861-3123-101C-BB62-00AA0018497C")
AreaVisInfo;
#endif

EXTERN_C const CLSID CLSID_TextVisInfo;

#ifdef __cplusplus

class DECLSPEC_UUID("07963863-3123-101C-BB62-00AA0018497C")
TextVisInfo;
#endif

EXTERN_C const CLSID CLSID_ObjVisInfoExtension;

#ifdef __cplusplus

class DECLSPEC_UUID("ED9655C5-3122-101C-BB62-00AA0018497C")
ObjVisInfoExtension;
#endif
#endif /* __VisInfoLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


