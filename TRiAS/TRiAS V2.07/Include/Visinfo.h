/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.00.44 */
/* at Wed Sep 02 11:36:23 1998
 */
/* Compiler settings for .\Visinfo.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"
#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __Visinfo_h__
#define __Visinfo_h__

#ifdef __cplusplus
extern "C"{
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


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "TRiASBaseInterfaces.h"
#include "VisInfoInterfaces.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL__intf_0000
 * at Wed Sep 02 11:36:23 1998
 * using MIDL 3.00.44
 ****************************************/
/* [local] */ 


#define VISINFO_TYPELIB_VERSION_MAJOR 1
#define VISINFO_TYPELIB_VERSION_MINOR 0
#define VISINFO_TYPELIB_VERSION "1.0"
#define VISINFO_TYPELIB_LCID 0


extern RPC_IF_HANDLE __MIDL__intf_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL__intf_0000_v0_0_s_ifspec;

#ifndef __IVisObjExt_INTERFACE_DEFINED__
#define __IVisObjExt_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IVisObjExt
 * at Wed Sep 02 11:36:23 1998
 * using MIDL 3.00.44
 ****************************************/
/* [object][unique][helpstring][uuid] */ 



EXTERN_C const IID IID_IVisObjExt;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IVisObjExt : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetVisInfoClass( 
            /* [in] */ long lIdent,
            /* [in] */ VISINFOTYPE rgType,
            /* [optional][in] */ VARIANT vViewName,
            /* [retval][out] */ DVisInfo __RPC_FAR *__RPC_FAR *ppIVisInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetVisInfoClass( 
            /* [in] */ long lIdent,
            /* [in] */ VISINFOTYPE rgType,
            /* [in] */ DVisInfo __RPC_FAR *pIVisInfo,
            /* [optional][in] */ VARIANT vViewName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ResetVisInfoClass( 
            /* [in] */ long lIdent,
            /* [in] */ VISINFOTYPE rgType,
            /* [optional][in] */ VARIANT vView) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetVisInfoObject( 
            /* [in] */ long lONr,
            /* [in] */ VISINFOTYPE rgType,
            /* [optional][in] */ VARIANT vViewName,
            /* [retval][out] */ DVisInfo __RPC_FAR *__RPC_FAR *ppIVisInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetVisInfoObject( 
            /* [in] */ long lONr,
            /* [in] */ VISINFOTYPE rgType,
            /* [in] */ DVisInfo __RPC_FAR *pIVisInfo,
            /* [in] */ VARIANT_BOOL fSameAsSource,
            /* [optional][in] */ VARIANT vViewName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ResetVisInfoObject( 
            /* [in] */ long lONr,
            /* [in] */ VISINFOTYPE rgType,
            /* [optional][in] */ VARIANT vViewName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetObjectHiddenStatus( 
            /* [in] */ long lONr,
            /* [optional][in] */ VARIANT vViewName,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfShow) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetObjectHiddenStatus( 
            /* [in] */ long lONr,
            /* [in] */ VARIANT_BOOL fShow,
            /* [optional][in] */ VARIANT vViewName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVisObjExtVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVisObjExt __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVisObjExt __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVisObjExt __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVisInfoClass )( 
            IVisObjExt __RPC_FAR * This,
            /* [in] */ long lIdent,
            /* [in] */ VISINFOTYPE rgType,
            /* [optional][in] */ VARIANT vViewName,
            /* [retval][out] */ DVisInfo __RPC_FAR *__RPC_FAR *ppIVisInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVisInfoClass )( 
            IVisObjExt __RPC_FAR * This,
            /* [in] */ long lIdent,
            /* [in] */ VISINFOTYPE rgType,
            /* [in] */ DVisInfo __RPC_FAR *pIVisInfo,
            /* [optional][in] */ VARIANT vViewName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetVisInfoClass )( 
            IVisObjExt __RPC_FAR * This,
            /* [in] */ long lIdent,
            /* [in] */ VISINFOTYPE rgType,
            /* [optional][in] */ VARIANT vView);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVisInfoObject )( 
            IVisObjExt __RPC_FAR * This,
            /* [in] */ long lONr,
            /* [in] */ VISINFOTYPE rgType,
            /* [optional][in] */ VARIANT vViewName,
            /* [retval][out] */ DVisInfo __RPC_FAR *__RPC_FAR *ppIVisInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVisInfoObject )( 
            IVisObjExt __RPC_FAR * This,
            /* [in] */ long lONr,
            /* [in] */ VISINFOTYPE rgType,
            /* [in] */ DVisInfo __RPC_FAR *pIVisInfo,
            /* [in] */ VARIANT_BOOL fSameAsSource,
            /* [optional][in] */ VARIANT vViewName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetVisInfoObject )( 
            IVisObjExt __RPC_FAR * This,
            /* [in] */ long lONr,
            /* [in] */ VISINFOTYPE rgType,
            /* [optional][in] */ VARIANT vViewName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetObjectHiddenStatus )( 
            IVisObjExt __RPC_FAR * This,
            /* [in] */ long lONr,
            /* [optional][in] */ VARIANT vViewName,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfShow);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetObjectHiddenStatus )( 
            IVisObjExt __RPC_FAR * This,
            /* [in] */ long lONr,
            /* [in] */ VARIANT_BOOL fShow,
            /* [optional][in] */ VARIANT vViewName);
        
        END_INTERFACE
    } IVisObjExtVtbl;

    interface IVisObjExt
    {
        CONST_VTBL struct IVisObjExtVtbl __RPC_FAR *lpVtbl;
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
    IVisObjExt __RPC_FAR * This,
    /* [in] */ long lIdent,
    /* [in] */ VISINFOTYPE rgType,
    /* [optional][in] */ VARIANT vViewName,
    /* [retval][out] */ DVisInfo __RPC_FAR *__RPC_FAR *ppIVisInfo);


void __RPC_STUB IVisObjExt_GetVisInfoClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisObjExt_SetVisInfoClass_Proxy( 
    IVisObjExt __RPC_FAR * This,
    /* [in] */ long lIdent,
    /* [in] */ VISINFOTYPE rgType,
    /* [in] */ DVisInfo __RPC_FAR *pIVisInfo,
    /* [optional][in] */ VARIANT vViewName);


void __RPC_STUB IVisObjExt_SetVisInfoClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisObjExt_ResetVisInfoClass_Proxy( 
    IVisObjExt __RPC_FAR * This,
    /* [in] */ long lIdent,
    /* [in] */ VISINFOTYPE rgType,
    /* [optional][in] */ VARIANT vView);


void __RPC_STUB IVisObjExt_ResetVisInfoClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisObjExt_GetVisInfoObject_Proxy( 
    IVisObjExt __RPC_FAR * This,
    /* [in] */ long lONr,
    /* [in] */ VISINFOTYPE rgType,
    /* [optional][in] */ VARIANT vViewName,
    /* [retval][out] */ DVisInfo __RPC_FAR *__RPC_FAR *ppIVisInfo);


void __RPC_STUB IVisObjExt_GetVisInfoObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisObjExt_SetVisInfoObject_Proxy( 
    IVisObjExt __RPC_FAR * This,
    /* [in] */ long lONr,
    /* [in] */ VISINFOTYPE rgType,
    /* [in] */ DVisInfo __RPC_FAR *pIVisInfo,
    /* [in] */ VARIANT_BOOL fSameAsSource,
    /* [optional][in] */ VARIANT vViewName);


void __RPC_STUB IVisObjExt_SetVisInfoObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisObjExt_ResetVisInfoObject_Proxy( 
    IVisObjExt __RPC_FAR * This,
    /* [in] */ long lONr,
    /* [in] */ VISINFOTYPE rgType,
    /* [optional][in] */ VARIANT vViewName);


void __RPC_STUB IVisObjExt_ResetVisInfoObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisObjExt_GetObjectHiddenStatus_Proxy( 
    IVisObjExt __RPC_FAR * This,
    /* [in] */ long lONr,
    /* [optional][in] */ VARIANT vViewName,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfShow);


void __RPC_STUB IVisObjExt_GetObjectHiddenStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisObjExt_SetObjectHiddenStatus_Proxy( 
    IVisObjExt __RPC_FAR * This,
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

/****************************************
 * Generated header for interface: IVisQuery
 * at Wed Sep 02 11:36:23 1998
 * using MIDL 3.00.44
 ****************************************/
/* [object][unique][helpstring][uuid] */ 


typedef /* [public] */ 
enum _tagIDENTVISMODE
    {	IDENTVISMODE_NoAction	= 0,
	IDENTVISMODE_HasNewVI	= 0x1,
	IDENTVISMODE_WillDrawComplete	= 0x2,
	IDENTVISMODE_HideObject	= 0x4,
	IDENTVISMODE_ModVisInfo	= 0x100,
	IDENTVISMODE_ModShowStatus	= 0x200
    }	IDENTVISMODE;


EXTERN_C const IID IID_IVisQuery;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IVisQuery : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetIdentMode( 
            /* [in] */ LONG Ident,
            BSTR View,
            /* [out][in] */ IDENTVISMODE __RPC_FAR *VisMode) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetObjectVis( 
            /* [in] */ LONG ObjNr,
            /* [out][in] */ DVisInfo __RPC_FAR *__RPC_FAR *Vis) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVisQueryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVisQuery __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVisQuery __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVisQuery __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIdentMode )( 
            IVisQuery __RPC_FAR * This,
            /* [in] */ LONG Ident,
            BSTR View,
            /* [out][in] */ IDENTVISMODE __RPC_FAR *VisMode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetObjectVis )( 
            IVisQuery __RPC_FAR * This,
            /* [in] */ LONG ObjNr,
            /* [out][in] */ DVisInfo __RPC_FAR *__RPC_FAR *Vis);
        
        END_INTERFACE
    } IVisQueryVtbl;

    interface IVisQuery
    {
        CONST_VTBL struct IVisQueryVtbl __RPC_FAR *lpVtbl;
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
    IVisQuery __RPC_FAR * This,
    /* [in] */ LONG Ident,
    BSTR View,
    /* [out][in] */ IDENTVISMODE __RPC_FAR *VisMode);


void __RPC_STUB IVisQuery_GetIdentMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisQuery_GetObjectVis_Proxy( 
    IVisQuery __RPC_FAR * This,
    /* [in] */ LONG ObjNr,
    /* [out][in] */ DVisInfo __RPC_FAR *__RPC_FAR *Vis);


void __RPC_STUB IVisQuery_GetObjectVis_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVisQuery_INTERFACE_DEFINED__ */


#ifndef __IMergeVisInfo_INTERFACE_DEFINED__
#define __IMergeVisInfo_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMergeVisInfo
 * at Wed Sep 02 11:36:23 1998
 * using MIDL 3.00.44
 ****************************************/
/* [object][unique][helpstring][uuid] */ 



EXTERN_C const IID IID_IMergeVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IMergeVisInfo : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE MergeVisInfo( 
            /* [in] */ VARIANT_BOOL OnlyChanged,
            /* [out][in] */ DVisInfo __RPC_FAR *__RPC_FAR *VisInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMergeVisInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMergeVisInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMergeVisInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMergeVisInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MergeVisInfo )( 
            IMergeVisInfo __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL OnlyChanged,
            /* [out][in] */ DVisInfo __RPC_FAR *__RPC_FAR *VisInfo);
        
        END_INTERFACE
    } IMergeVisInfoVtbl;

    interface IMergeVisInfo
    {
        CONST_VTBL struct IMergeVisInfoVtbl __RPC_FAR *lpVtbl;
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
    IMergeVisInfo __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL OnlyChanged,
    /* [out][in] */ DVisInfo __RPC_FAR *__RPC_FAR *VisInfo);


void __RPC_STUB IMergeVisInfo_MergeVisInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMergeVisInfo_INTERFACE_DEFINED__ */



#ifndef __VisInfoLib_LIBRARY_DEFINED__
#define __VisInfoLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: VisInfoLib
 * at Wed Sep 02 11:36:23 1998
 * using MIDL 3.00.44
 ****************************************/
/* [helpstring][lcid][version][uuid] */ 



EXTERN_C const IID LIBID_VisInfoLib;

#ifndef __IVisInfo_INTERFACE_DEFINED__
#define __IVisInfo_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IVisInfo
 * at Wed Sep 02 11:36:23 1998
 * using MIDL 3.00.44
 ****************************************/
/* [object][hidden][local][helpstring][oleautomation][uuid] */ 



EXTERN_C const IID IID_IVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IVisInfo : public IUnknown
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_isA( 
            /* [retval][out] */ LONG __RPC_FAR *plRTTI) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppIBase) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Parent( 
            /* [in] */ IDispatch __RPC_FAR *pIBase) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppIApp) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Application( 
            /* [in] */ IDispatch __RPC_FAR *pIApp) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Style( 
            /* [retval][out] */ int __RPC_FAR *piStyle) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Style( 
            /* [in] */ int iStyle) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Priority( 
            /* [retval][out] */ int __RPC_FAR *piPrio) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Priority( 
            /* [in] */ int iPrio) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDesc) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR bstrDesc) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_MainColor( 
            /* [retval][out] */ TRIASCOLOR __RPC_FAR *pocMain) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_MainColor( 
            /* [in] */ TRIASCOLOR ocMain) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVisInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVisInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVisInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVisInfo __RPC_FAR * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_isA )( 
            IVisInfo __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *plRTTI);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IVisInfo __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppIBase);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Parent )( 
            IVisInfo __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pIBase);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            IVisInfo __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppIApp);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Application )( 
            IVisInfo __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pIApp);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Style )( 
            IVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piStyle);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Style )( 
            IVisInfo __RPC_FAR * This,
            /* [in] */ int iStyle);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Priority )( 
            IVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piPrio);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Priority )( 
            IVisInfo __RPC_FAR * This,
            /* [in] */ int iPrio);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IVisInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDesc);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IVisInfo __RPC_FAR * This,
            /* [in] */ BSTR bstrDesc);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MainColor )( 
            IVisInfo __RPC_FAR * This,
            /* [retval][out] */ TRIASCOLOR __RPC_FAR *pocMain);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MainColor )( 
            IVisInfo __RPC_FAR * This,
            /* [in] */ TRIASCOLOR ocMain);
        
        END_INTERFACE
    } IVisInfoVtbl;

    interface IVisInfo
    {
        CONST_VTBL struct IVisInfoVtbl __RPC_FAR *lpVtbl;
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
    IVisInfo __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *plRTTI);


void __RPC_STUB IVisInfo_get_isA_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IVisInfo_get_Parent_Proxy( 
    IVisInfo __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppIBase);


void __RPC_STUB IVisInfo_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IVisInfo_put_Parent_Proxy( 
    IVisInfo __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *pIBase);


void __RPC_STUB IVisInfo_put_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IVisInfo_get_Application_Proxy( 
    IVisInfo __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppIApp);


void __RPC_STUB IVisInfo_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IVisInfo_put_Application_Proxy( 
    IVisInfo __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *pIApp);


void __RPC_STUB IVisInfo_put_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IVisInfo_get_Style_Proxy( 
    IVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *piStyle);


void __RPC_STUB IVisInfo_get_Style_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IVisInfo_put_Style_Proxy( 
    IVisInfo __RPC_FAR * This,
    /* [in] */ int iStyle);


void __RPC_STUB IVisInfo_put_Style_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IVisInfo_get_Priority_Proxy( 
    IVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *piPrio);


void __RPC_STUB IVisInfo_get_Priority_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IVisInfo_put_Priority_Proxy( 
    IVisInfo __RPC_FAR * This,
    /* [in] */ int iPrio);


void __RPC_STUB IVisInfo_put_Priority_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IVisInfo_get_Name_Proxy( 
    IVisInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrDesc);


void __RPC_STUB IVisInfo_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IVisInfo_put_Name_Proxy( 
    IVisInfo __RPC_FAR * This,
    /* [in] */ BSTR bstrDesc);


void __RPC_STUB IVisInfo_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IVisInfo_get_MainColor_Proxy( 
    IVisInfo __RPC_FAR * This,
    /* [retval][out] */ TRIASCOLOR __RPC_FAR *pocMain);


void __RPC_STUB IVisInfo_get_MainColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IVisInfo_put_MainColor_Proxy( 
    IVisInfo __RPC_FAR * This,
    /* [in] */ TRIASCOLOR ocMain);


void __RPC_STUB IVisInfo_put_MainColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVisInfo_INTERFACE_DEFINED__ */


#ifndef __IPointVisInfo_INTERFACE_DEFINED__
#define __IPointVisInfo_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IPointVisInfo
 * at Wed Sep 02 11:36:23 1998
 * using MIDL 3.00.44
 ****************************************/
/* [object][hidden][local][helpstring][oleautomation][uuid] */ 



EXTERN_C const IID IID_IPointVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IPointVisInfo : public IVisInfo
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_SizeX( 
            /* [retval][out] */ int __RPC_FAR *piX) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_SizeX( 
            /* [in] */ int iX) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_SizeY( 
            /* [retval][out] */ int __RPC_FAR *piY) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_SizeY( 
            /* [in] */ int iY) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Rotate( 
            /* [retval][out] */ int __RPC_FAR *piRot) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Rotate( 
            /* [in] */ int iRot) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_BkColor( 
            /* [retval][out] */ TRIASCOLOR __RPC_FAR *pocBack) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_BkColor( 
            /* [in] */ TRIASCOLOR ocBack) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPointVisInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPointVisInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPointVisInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPointVisInfo __RPC_FAR * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_isA )( 
            IPointVisInfo __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *plRTTI);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IPointVisInfo __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppIBase);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Parent )( 
            IPointVisInfo __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pIBase);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            IPointVisInfo __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppIApp);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Application )( 
            IPointVisInfo __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pIApp);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Style )( 
            IPointVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piStyle);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Style )( 
            IPointVisInfo __RPC_FAR * This,
            /* [in] */ int iStyle);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Priority )( 
            IPointVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piPrio);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Priority )( 
            IPointVisInfo __RPC_FAR * This,
            /* [in] */ int iPrio);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IPointVisInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDesc);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IPointVisInfo __RPC_FAR * This,
            /* [in] */ BSTR bstrDesc);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MainColor )( 
            IPointVisInfo __RPC_FAR * This,
            /* [retval][out] */ TRIASCOLOR __RPC_FAR *pocMain);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MainColor )( 
            IPointVisInfo __RPC_FAR * This,
            /* [in] */ TRIASCOLOR ocMain);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SizeX )( 
            IPointVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piX);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SizeX )( 
            IPointVisInfo __RPC_FAR * This,
            /* [in] */ int iX);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SizeY )( 
            IPointVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piY);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SizeY )( 
            IPointVisInfo __RPC_FAR * This,
            /* [in] */ int iY);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Rotate )( 
            IPointVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piRot);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Rotate )( 
            IPointVisInfo __RPC_FAR * This,
            /* [in] */ int iRot);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BkColor )( 
            IPointVisInfo __RPC_FAR * This,
            /* [retval][out] */ TRIASCOLOR __RPC_FAR *pocBack);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BkColor )( 
            IPointVisInfo __RPC_FAR * This,
            /* [in] */ TRIASCOLOR ocBack);
        
        END_INTERFACE
    } IPointVisInfoVtbl;

    interface IPointVisInfo
    {
        CONST_VTBL struct IPointVisInfoVtbl __RPC_FAR *lpVtbl;
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
    IPointVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *piX);


void __RPC_STUB IPointVisInfo_get_SizeX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPointVisInfo_put_SizeX_Proxy( 
    IPointVisInfo __RPC_FAR * This,
    /* [in] */ int iX);


void __RPC_STUB IPointVisInfo_put_SizeX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPointVisInfo_get_SizeY_Proxy( 
    IPointVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *piY);


void __RPC_STUB IPointVisInfo_get_SizeY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPointVisInfo_put_SizeY_Proxy( 
    IPointVisInfo __RPC_FAR * This,
    /* [in] */ int iY);


void __RPC_STUB IPointVisInfo_put_SizeY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPointVisInfo_get_Rotate_Proxy( 
    IPointVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *piRot);


void __RPC_STUB IPointVisInfo_get_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPointVisInfo_put_Rotate_Proxy( 
    IPointVisInfo __RPC_FAR * This,
    /* [in] */ int iRot);


void __RPC_STUB IPointVisInfo_put_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPointVisInfo_get_BkColor_Proxy( 
    IPointVisInfo __RPC_FAR * This,
    /* [retval][out] */ TRIASCOLOR __RPC_FAR *pocBack);


void __RPC_STUB IPointVisInfo_get_BkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPointVisInfo_put_BkColor_Proxy( 
    IPointVisInfo __RPC_FAR * This,
    /* [in] */ TRIASCOLOR ocBack);


void __RPC_STUB IPointVisInfo_put_BkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPointVisInfo_INTERFACE_DEFINED__ */


#ifndef __ILineVisInfo_INTERFACE_DEFINED__
#define __ILineVisInfo_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ILineVisInfo
 * at Wed Sep 02 11:36:23 1998
 * using MIDL 3.00.44
 ****************************************/
/* [object][hidden][local][helpstring][oleautomation][uuid] */ 



EXTERN_C const IID IID_ILineVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ILineVisInfo : public IVisInfo
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ int __RPC_FAR *piWidth) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ int iWidth) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILineVisInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILineVisInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILineVisInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILineVisInfo __RPC_FAR * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_isA )( 
            ILineVisInfo __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *plRTTI);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            ILineVisInfo __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppIBase);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Parent )( 
            ILineVisInfo __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pIBase);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            ILineVisInfo __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppIApp);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Application )( 
            ILineVisInfo __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pIApp);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Style )( 
            ILineVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piStyle);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Style )( 
            ILineVisInfo __RPC_FAR * This,
            /* [in] */ int iStyle);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Priority )( 
            ILineVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piPrio);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Priority )( 
            ILineVisInfo __RPC_FAR * This,
            /* [in] */ int iPrio);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ILineVisInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDesc);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            ILineVisInfo __RPC_FAR * This,
            /* [in] */ BSTR bstrDesc);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MainColor )( 
            ILineVisInfo __RPC_FAR * This,
            /* [retval][out] */ TRIASCOLOR __RPC_FAR *pocMain);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MainColor )( 
            ILineVisInfo __RPC_FAR * This,
            /* [in] */ TRIASCOLOR ocMain);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Width )( 
            ILineVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piWidth);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Width )( 
            ILineVisInfo __RPC_FAR * This,
            /* [in] */ int iWidth);
        
        END_INTERFACE
    } ILineVisInfoVtbl;

    interface ILineVisInfo
    {
        CONST_VTBL struct ILineVisInfoVtbl __RPC_FAR *lpVtbl;
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
    ILineVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *piWidth);


void __RPC_STUB ILineVisInfo_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ILineVisInfo_put_Width_Proxy( 
    ILineVisInfo __RPC_FAR * This,
    /* [in] */ int iWidth);


void __RPC_STUB ILineVisInfo_put_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILineVisInfo_INTERFACE_DEFINED__ */


#ifndef __IAreaVisInfo_INTERFACE_DEFINED__
#define __IAreaVisInfo_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAreaVisInfo
 * at Wed Sep 02 11:36:23 1998
 * using MIDL 3.00.44
 ****************************************/
/* [object][hidden][local][helpstring][oleautomation][uuid] */ 



EXTERN_C const IID IID_IAreaVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IAreaVisInfo : public IVisInfo
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ int __RPC_FAR *piWidth) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ int iWidth) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Opaque( 
            /* [retval][out] */ int __RPC_FAR *pfOpaque) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Opaque( 
            /* [in] */ int fOpaque) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_BkContour( 
            /* [retval][out] */ int __RPC_FAR *pfBkContour) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_BkContour( 
            /* [in] */ int fBkContour) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_BkColor( 
            /* [retval][out] */ TRIASCOLOR __RPC_FAR *pocBack) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_BkColor( 
            /* [in] */ TRIASCOLOR ocBack) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAreaVisInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAreaVisInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAreaVisInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAreaVisInfo __RPC_FAR * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_isA )( 
            IAreaVisInfo __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *plRTTI);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IAreaVisInfo __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppIBase);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Parent )( 
            IAreaVisInfo __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pIBase);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            IAreaVisInfo __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppIApp);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Application )( 
            IAreaVisInfo __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pIApp);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Style )( 
            IAreaVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piStyle);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Style )( 
            IAreaVisInfo __RPC_FAR * This,
            /* [in] */ int iStyle);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Priority )( 
            IAreaVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piPrio);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Priority )( 
            IAreaVisInfo __RPC_FAR * This,
            /* [in] */ int iPrio);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IAreaVisInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDesc);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IAreaVisInfo __RPC_FAR * This,
            /* [in] */ BSTR bstrDesc);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MainColor )( 
            IAreaVisInfo __RPC_FAR * This,
            /* [retval][out] */ TRIASCOLOR __RPC_FAR *pocMain);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MainColor )( 
            IAreaVisInfo __RPC_FAR * This,
            /* [in] */ TRIASCOLOR ocMain);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Width )( 
            IAreaVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piWidth);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Width )( 
            IAreaVisInfo __RPC_FAR * This,
            /* [in] */ int iWidth);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Opaque )( 
            IAreaVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pfOpaque);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Opaque )( 
            IAreaVisInfo __RPC_FAR * This,
            /* [in] */ int fOpaque);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BkContour )( 
            IAreaVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pfBkContour);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BkContour )( 
            IAreaVisInfo __RPC_FAR * This,
            /* [in] */ int fBkContour);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BkColor )( 
            IAreaVisInfo __RPC_FAR * This,
            /* [retval][out] */ TRIASCOLOR __RPC_FAR *pocBack);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BkColor )( 
            IAreaVisInfo __RPC_FAR * This,
            /* [in] */ TRIASCOLOR ocBack);
        
        END_INTERFACE
    } IAreaVisInfoVtbl;

    interface IAreaVisInfo
    {
        CONST_VTBL struct IAreaVisInfoVtbl __RPC_FAR *lpVtbl;
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
    IAreaVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *piWidth);


void __RPC_STUB IAreaVisInfo_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IAreaVisInfo_put_Width_Proxy( 
    IAreaVisInfo __RPC_FAR * This,
    /* [in] */ int iWidth);


void __RPC_STUB IAreaVisInfo_put_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IAreaVisInfo_get_Opaque_Proxy( 
    IAreaVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pfOpaque);


void __RPC_STUB IAreaVisInfo_get_Opaque_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IAreaVisInfo_put_Opaque_Proxy( 
    IAreaVisInfo __RPC_FAR * This,
    /* [in] */ int fOpaque);


void __RPC_STUB IAreaVisInfo_put_Opaque_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IAreaVisInfo_get_BkContour_Proxy( 
    IAreaVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pfBkContour);


void __RPC_STUB IAreaVisInfo_get_BkContour_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IAreaVisInfo_put_BkContour_Proxy( 
    IAreaVisInfo __RPC_FAR * This,
    /* [in] */ int fBkContour);


void __RPC_STUB IAreaVisInfo_put_BkContour_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IAreaVisInfo_get_BkColor_Proxy( 
    IAreaVisInfo __RPC_FAR * This,
    /* [retval][out] */ TRIASCOLOR __RPC_FAR *pocBack);


void __RPC_STUB IAreaVisInfo_get_BkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IAreaVisInfo_put_BkColor_Proxy( 
    IAreaVisInfo __RPC_FAR * This,
    /* [in] */ TRIASCOLOR ocBack);


void __RPC_STUB IAreaVisInfo_put_BkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAreaVisInfo_INTERFACE_DEFINED__ */


#ifndef __ITextVisInfo_INTERFACE_DEFINED__
#define __ITextVisInfo_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITextVisInfo
 * at Wed Sep 02 11:36:23 1998
 * using MIDL 3.00.44
 ****************************************/
/* [object][hidden][local][helpstring][oleautomation][uuid] */ 



EXTERN_C const IID IID_ITextVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ITextVisInfo : public IVisInfo
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_SizeX( 
            /* [retval][out] */ int __RPC_FAR *piX) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_SizeX( 
            /* [in] */ int iX) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_SizeY( 
            /* [retval][out] */ int __RPC_FAR *piY) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_SizeY( 
            /* [in] */ int iY) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Bold( 
            /* [retval][out] */ int __RPC_FAR *pfBold) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Bold( 
            /* [in] */ int fBold) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Italic( 
            /* [retval][out] */ int __RPC_FAR *pfItalic) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Italic( 
            /* [in] */ int fItalic) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Underline( 
            /* [retval][out] */ int __RPC_FAR *pfUnderline) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Underline( 
            /* [in] */ int fUnderline) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_StrikeThrough( 
            /* [retval][out] */ int __RPC_FAR *pfStrikeThrough) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_StrikeThrough( 
            /* [in] */ int fStrikeThrough) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_FrameStyle( 
            /* [retval][out] */ FRAMESTYLE __RPC_FAR *prgFrameStyle) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_FrameStyle( 
            /* [in] */ FRAMESTYLE rgFrameStyle) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_AlignStyle( 
            /* [retval][out] */ ALIGNSTYLE __RPC_FAR *prgAlign) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_AlignStyle( 
            /* [in] */ ALIGNSTYLE rgAlign) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Rotate( 
            /* [retval][out] */ int __RPC_FAR *piRot) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Rotate( 
            /* [in] */ int iRot) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Slant( 
            /* [retval][out] */ int __RPC_FAR *piSlant) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Slant( 
            /* [in] */ int iSlant) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITextVisInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITextVisInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITextVisInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITextVisInfo __RPC_FAR * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_isA )( 
            ITextVisInfo __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *plRTTI);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            ITextVisInfo __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppIBase);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Parent )( 
            ITextVisInfo __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pIBase);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            ITextVisInfo __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppIApp);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Application )( 
            ITextVisInfo __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pIApp);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Style )( 
            ITextVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piStyle);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Style )( 
            ITextVisInfo __RPC_FAR * This,
            /* [in] */ int iStyle);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Priority )( 
            ITextVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piPrio);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Priority )( 
            ITextVisInfo __RPC_FAR * This,
            /* [in] */ int iPrio);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ITextVisInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrDesc);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            ITextVisInfo __RPC_FAR * This,
            /* [in] */ BSTR bstrDesc);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MainColor )( 
            ITextVisInfo __RPC_FAR * This,
            /* [retval][out] */ TRIASCOLOR __RPC_FAR *pocMain);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MainColor )( 
            ITextVisInfo __RPC_FAR * This,
            /* [in] */ TRIASCOLOR ocMain);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SizeX )( 
            ITextVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piX);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SizeX )( 
            ITextVisInfo __RPC_FAR * This,
            /* [in] */ int iX);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SizeY )( 
            ITextVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piY);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SizeY )( 
            ITextVisInfo __RPC_FAR * This,
            /* [in] */ int iY);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Bold )( 
            ITextVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pfBold);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Bold )( 
            ITextVisInfo __RPC_FAR * This,
            /* [in] */ int fBold);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Italic )( 
            ITextVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pfItalic);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Italic )( 
            ITextVisInfo __RPC_FAR * This,
            /* [in] */ int fItalic);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Underline )( 
            ITextVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pfUnderline);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Underline )( 
            ITextVisInfo __RPC_FAR * This,
            /* [in] */ int fUnderline);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StrikeThrough )( 
            ITextVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pfStrikeThrough);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StrikeThrough )( 
            ITextVisInfo __RPC_FAR * This,
            /* [in] */ int fStrikeThrough);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FrameStyle )( 
            ITextVisInfo __RPC_FAR * This,
            /* [retval][out] */ FRAMESTYLE __RPC_FAR *prgFrameStyle);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FrameStyle )( 
            ITextVisInfo __RPC_FAR * This,
            /* [in] */ FRAMESTYLE rgFrameStyle);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AlignStyle )( 
            ITextVisInfo __RPC_FAR * This,
            /* [retval][out] */ ALIGNSTYLE __RPC_FAR *prgAlign);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AlignStyle )( 
            ITextVisInfo __RPC_FAR * This,
            /* [in] */ ALIGNSTYLE rgAlign);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Rotate )( 
            ITextVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piRot);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Rotate )( 
            ITextVisInfo __RPC_FAR * This,
            /* [in] */ int iRot);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Slant )( 
            ITextVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piSlant);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Slant )( 
            ITextVisInfo __RPC_FAR * This,
            /* [in] */ int iSlant);
        
        END_INTERFACE
    } ITextVisInfoVtbl;

    interface ITextVisInfo
    {
        CONST_VTBL struct ITextVisInfoVtbl __RPC_FAR *lpVtbl;
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
    ITextVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *piX);


void __RPC_STUB ITextVisInfo_get_SizeX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_put_SizeX_Proxy( 
    ITextVisInfo __RPC_FAR * This,
    /* [in] */ int iX);


void __RPC_STUB ITextVisInfo_put_SizeX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_get_SizeY_Proxy( 
    ITextVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *piY);


void __RPC_STUB ITextVisInfo_get_SizeY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_put_SizeY_Proxy( 
    ITextVisInfo __RPC_FAR * This,
    /* [in] */ int iY);


void __RPC_STUB ITextVisInfo_put_SizeY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_get_Bold_Proxy( 
    ITextVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pfBold);


void __RPC_STUB ITextVisInfo_get_Bold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_put_Bold_Proxy( 
    ITextVisInfo __RPC_FAR * This,
    /* [in] */ int fBold);


void __RPC_STUB ITextVisInfo_put_Bold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_get_Italic_Proxy( 
    ITextVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pfItalic);


void __RPC_STUB ITextVisInfo_get_Italic_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_put_Italic_Proxy( 
    ITextVisInfo __RPC_FAR * This,
    /* [in] */ int fItalic);


void __RPC_STUB ITextVisInfo_put_Italic_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_get_Underline_Proxy( 
    ITextVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pfUnderline);


void __RPC_STUB ITextVisInfo_get_Underline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_put_Underline_Proxy( 
    ITextVisInfo __RPC_FAR * This,
    /* [in] */ int fUnderline);


void __RPC_STUB ITextVisInfo_put_Underline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_get_StrikeThrough_Proxy( 
    ITextVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pfStrikeThrough);


void __RPC_STUB ITextVisInfo_get_StrikeThrough_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_put_StrikeThrough_Proxy( 
    ITextVisInfo __RPC_FAR * This,
    /* [in] */ int fStrikeThrough);


void __RPC_STUB ITextVisInfo_put_StrikeThrough_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_get_FrameStyle_Proxy( 
    ITextVisInfo __RPC_FAR * This,
    /* [retval][out] */ FRAMESTYLE __RPC_FAR *prgFrameStyle);


void __RPC_STUB ITextVisInfo_get_FrameStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_put_FrameStyle_Proxy( 
    ITextVisInfo __RPC_FAR * This,
    /* [in] */ FRAMESTYLE rgFrameStyle);


void __RPC_STUB ITextVisInfo_put_FrameStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_get_AlignStyle_Proxy( 
    ITextVisInfo __RPC_FAR * This,
    /* [retval][out] */ ALIGNSTYLE __RPC_FAR *prgAlign);


void __RPC_STUB ITextVisInfo_get_AlignStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_put_AlignStyle_Proxy( 
    ITextVisInfo __RPC_FAR * This,
    /* [in] */ ALIGNSTYLE rgAlign);


void __RPC_STUB ITextVisInfo_put_AlignStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_get_Rotate_Proxy( 
    ITextVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *piRot);


void __RPC_STUB ITextVisInfo_get_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_put_Rotate_Proxy( 
    ITextVisInfo __RPC_FAR * This,
    /* [in] */ int iRot);


void __RPC_STUB ITextVisInfo_put_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_get_Slant_Proxy( 
    ITextVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *piSlant);


void __RPC_STUB ITextVisInfo_get_Slant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ITextVisInfo_put_Slant_Proxy( 
    ITextVisInfo __RPC_FAR * This,
    /* [in] */ int iSlant);


void __RPC_STUB ITextVisInfo_put_Slant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITextVisInfo_INTERFACE_DEFINED__ */


#ifdef __cplusplus
EXTERN_C const CLSID CLSID_DefaultVisInfo;

class DefaultVisInfo;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_PointVisInfo;

class PointVisInfo;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_LineVisInfo;

class LineVisInfo;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_AreaVisInfo;

class AreaVisInfo;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_TextVisInfo;

class TextVisInfo;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_ObjVisInfoExtension;

class ObjVisInfoExtension;
#endif
#endif /* __VisInfoLib_LIBRARY_DEFINED__ */

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
