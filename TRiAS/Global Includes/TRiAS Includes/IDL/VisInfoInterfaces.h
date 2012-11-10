/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Mar 24 22:32:26 1999
 */
/* Compiler settings for VisInfoInterfaces.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
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

#ifndef __VisInfoInterfaces_h__
#define __VisInfoInterfaces_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __DVisInfo_FWD_DEFINED__
#define __DVisInfo_FWD_DEFINED__
typedef interface DVisInfo DVisInfo;
#endif 	/* __DVisInfo_FWD_DEFINED__ */


#ifndef __DPointVisInfo_FWD_DEFINED__
#define __DPointVisInfo_FWD_DEFINED__
typedef interface DPointVisInfo DPointVisInfo;
#endif 	/* __DPointVisInfo_FWD_DEFINED__ */


#ifndef __DLineVisInfo_FWD_DEFINED__
#define __DLineVisInfo_FWD_DEFINED__
typedef interface DLineVisInfo DLineVisInfo;
#endif 	/* __DLineVisInfo_FWD_DEFINED__ */


#ifndef __DAreaVisInfo_FWD_DEFINED__
#define __DAreaVisInfo_FWD_DEFINED__
typedef interface DAreaVisInfo DAreaVisInfo;
#endif 	/* __DAreaVisInfo_FWD_DEFINED__ */


#ifndef __DTextVisInfo_FWD_DEFINED__
#define __DTextVisInfo_FWD_DEFINED__
typedef interface DTextVisInfo DTextVisInfo;
#endif 	/* __DTextVisInfo_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "TRiASBaseInterfaces.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_VisInfoInterfaces_0000 */
/* [local] */ 






#if !defined(_VISINFOTYPE_DEFINED)
#define _VISINFOTYPE_DEFINED
typedef /* [public] */ 
enum _tagVISINFO_TYPE
    {	VISINFOTYPE_Point	= 0,
	VISINFOTYPE_Line	= 1,
	VISINFOTYPE_Area	= 2,
	VISINFOTYPE_Text	= 5,
	VISINFOTYPE_Unknown	= 6,
	VISINFOTYPE_Default	= 7
    }	VISINFOTYPE;

#endif // _VISINFOTYPE_DEFINED


extern RPC_IF_HANDLE __MIDL_itf_VisInfoInterfaces_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_VisInfoInterfaces_0000_v0_0_s_ifspec;

#ifndef __DVisInfo_INTERFACE_DEFINED__
#define __DVisInfo_INTERFACE_DEFINED__

/* interface DVisInfo */
/* [helpstring][uuid][dual][oleautomation][object] */ 

typedef /* [public] */ long TRIASCOLOR;


EXTERN_C const IID IID_DVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0796386B-3123-101C-BB62-00AA0018497C")
    DVisInfo : public DTRiASBaseClass
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Style( 
            /* [retval][out] */ int __RPC_FAR *Style) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Style( 
            /* [in] */ int Style) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Priority( 
            /* [retval][out] */ int __RPC_FAR *Prio) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Priority( 
            /* [in] */ int Prio) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *Desc) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR Desc) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_MainColor( 
            /* [retval][out] */ TRIASCOLOR __RPC_FAR *Main) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_MainColor( 
            /* [in] */ TRIASCOLOR Main) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Changed( 
            /* [retval][out] */ int __RPC_FAR *Flags) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Changed( 
            /* [in] */ int Flags) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VisString( 
            /* [retval][out] */ BSTR __RPC_FAR *Desc) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Locatable( 
            /* [retval][out] */ int __RPC_FAR *Flags) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Locatable( 
            /* [in] */ int Flags) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Visible( 
            /* [retval][out] */ int __RPC_FAR *Flags) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Visible( 
            /* [in] */ int Flags) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_GeometryName( 
            /* [retval][out] */ BSTR __RPC_FAR *Desc) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_GeometryName( 
            /* [in] */ BSTR Desc) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct DVisInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            DVisInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            DVisInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            DVisInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            DVisInfo __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            DVisInfo __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            DVisInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            DVisInfo __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_isA )( 
            DVisInfo __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *RTTI);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            DVisInfo __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Base);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Parent )( 
            DVisInfo __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *Base);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            DVisInfo __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *App);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Application )( 
            DVisInfo __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *App);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Style )( 
            DVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Style);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Style )( 
            DVisInfo __RPC_FAR * This,
            /* [in] */ int Style);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Priority )( 
            DVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Prio);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Priority )( 
            DVisInfo __RPC_FAR * This,
            /* [in] */ int Prio);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            DVisInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Desc);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            DVisInfo __RPC_FAR * This,
            /* [in] */ BSTR Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MainColor )( 
            DVisInfo __RPC_FAR * This,
            /* [retval][out] */ TRIASCOLOR __RPC_FAR *Main);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MainColor )( 
            DVisInfo __RPC_FAR * This,
            /* [in] */ TRIASCOLOR Main);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Changed )( 
            DVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Changed )( 
            DVisInfo __RPC_FAR * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VisString )( 
            DVisInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Locatable )( 
            DVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Locatable )( 
            DVisInfo __RPC_FAR * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            DVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            DVisInfo __RPC_FAR * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GeometryName )( 
            DVisInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Desc);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GeometryName )( 
            DVisInfo __RPC_FAR * This,
            /* [in] */ BSTR Desc);
        
        END_INTERFACE
    } DVisInfoVtbl;

    interface DVisInfo
    {
        CONST_VTBL struct DVisInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define DVisInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define DVisInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define DVisInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define DVisInfo_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define DVisInfo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define DVisInfo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define DVisInfo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define DVisInfo_get_isA(This,RTTI)	\
    (This)->lpVtbl -> get_isA(This,RTTI)

#define DVisInfo_get_Parent(This,Base)	\
    (This)->lpVtbl -> get_Parent(This,Base)

#define DVisInfo_put_Parent(This,Base)	\
    (This)->lpVtbl -> put_Parent(This,Base)

#define DVisInfo_get_Application(This,App)	\
    (This)->lpVtbl -> get_Application(This,App)

#define DVisInfo_put_Application(This,App)	\
    (This)->lpVtbl -> put_Application(This,App)


#define DVisInfo_get_Style(This,Style)	\
    (This)->lpVtbl -> get_Style(This,Style)

#define DVisInfo_put_Style(This,Style)	\
    (This)->lpVtbl -> put_Style(This,Style)

#define DVisInfo_get_Priority(This,Prio)	\
    (This)->lpVtbl -> get_Priority(This,Prio)

#define DVisInfo_put_Priority(This,Prio)	\
    (This)->lpVtbl -> put_Priority(This,Prio)

#define DVisInfo_get_Name(This,Desc)	\
    (This)->lpVtbl -> get_Name(This,Desc)

#define DVisInfo_put_Name(This,Desc)	\
    (This)->lpVtbl -> put_Name(This,Desc)

#define DVisInfo_get_MainColor(This,Main)	\
    (This)->lpVtbl -> get_MainColor(This,Main)

#define DVisInfo_put_MainColor(This,Main)	\
    (This)->lpVtbl -> put_MainColor(This,Main)

#define DVisInfo_get_Changed(This,Flags)	\
    (This)->lpVtbl -> get_Changed(This,Flags)

#define DVisInfo_put_Changed(This,Flags)	\
    (This)->lpVtbl -> put_Changed(This,Flags)

#define DVisInfo_get_VisString(This,Desc)	\
    (This)->lpVtbl -> get_VisString(This,Desc)

#define DVisInfo_get_Locatable(This,Flags)	\
    (This)->lpVtbl -> get_Locatable(This,Flags)

#define DVisInfo_put_Locatable(This,Flags)	\
    (This)->lpVtbl -> put_Locatable(This,Flags)

#define DVisInfo_get_Visible(This,Flags)	\
    (This)->lpVtbl -> get_Visible(This,Flags)

#define DVisInfo_put_Visible(This,Flags)	\
    (This)->lpVtbl -> put_Visible(This,Flags)

#define DVisInfo_get_GeometryName(This,Desc)	\
    (This)->lpVtbl -> get_GeometryName(This,Desc)

#define DVisInfo_put_GeometryName(This,Desc)	\
    (This)->lpVtbl -> put_GeometryName(This,Desc)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_get_Style_Proxy( 
    DVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *Style);


void __RPC_STUB DVisInfo_get_Style_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_put_Style_Proxy( 
    DVisInfo __RPC_FAR * This,
    /* [in] */ int Style);


void __RPC_STUB DVisInfo_put_Style_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_get_Priority_Proxy( 
    DVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *Prio);


void __RPC_STUB DVisInfo_get_Priority_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_put_Priority_Proxy( 
    DVisInfo __RPC_FAR * This,
    /* [in] */ int Prio);


void __RPC_STUB DVisInfo_put_Priority_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_get_Name_Proxy( 
    DVisInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Desc);


void __RPC_STUB DVisInfo_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_put_Name_Proxy( 
    DVisInfo __RPC_FAR * This,
    /* [in] */ BSTR Desc);


void __RPC_STUB DVisInfo_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_get_MainColor_Proxy( 
    DVisInfo __RPC_FAR * This,
    /* [retval][out] */ TRIASCOLOR __RPC_FAR *Main);


void __RPC_STUB DVisInfo_get_MainColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_put_MainColor_Proxy( 
    DVisInfo __RPC_FAR * This,
    /* [in] */ TRIASCOLOR Main);


void __RPC_STUB DVisInfo_put_MainColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_get_Changed_Proxy( 
    DVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *Flags);


void __RPC_STUB DVisInfo_get_Changed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_put_Changed_Proxy( 
    DVisInfo __RPC_FAR * This,
    /* [in] */ int Flags);


void __RPC_STUB DVisInfo_put_Changed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_get_VisString_Proxy( 
    DVisInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Desc);


void __RPC_STUB DVisInfo_get_VisString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_get_Locatable_Proxy( 
    DVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *Flags);


void __RPC_STUB DVisInfo_get_Locatable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_put_Locatable_Proxy( 
    DVisInfo __RPC_FAR * This,
    /* [in] */ int Flags);


void __RPC_STUB DVisInfo_put_Locatable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_get_Visible_Proxy( 
    DVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *Flags);


void __RPC_STUB DVisInfo_get_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_put_Visible_Proxy( 
    DVisInfo __RPC_FAR * This,
    /* [in] */ int Flags);


void __RPC_STUB DVisInfo_put_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_get_GeometryName_Proxy( 
    DVisInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Desc);


void __RPC_STUB DVisInfo_get_GeometryName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_put_GeometryName_Proxy( 
    DVisInfo __RPC_FAR * This,
    /* [in] */ BSTR Desc);


void __RPC_STUB DVisInfo_put_GeometryName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __DVisInfo_INTERFACE_DEFINED__ */


#ifndef __DPointVisInfo_INTERFACE_DEFINED__
#define __DPointVisInfo_INTERFACE_DEFINED__

/* interface DPointVisInfo */
/* [helpstring][uuid][object][dual][oleautomation] */ 


EXTERN_C const IID IID_DPointVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("07963867-3123-101C-BB62-00AA0018497C")
    DPointVisInfo : public DVisInfo
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SizeX( 
            /* [retval][out] */ int __RPC_FAR *X) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_SizeX( 
            /* [in] */ int X) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SizeY( 
            /* [retval][out] */ int __RPC_FAR *Y) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_SizeY( 
            /* [in] */ int Y) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Rotate( 
            /* [retval][out] */ int __RPC_FAR *Rot) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Rotate( 
            /* [in] */ int Rot) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_BkColor( 
            /* [retval][out] */ TRIASCOLOR __RPC_FAR *Back) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_BkColor( 
            /* [in] */ TRIASCOLOR Back) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct DPointVisInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            DPointVisInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            DPointVisInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            DPointVisInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            DPointVisInfo __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            DPointVisInfo __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            DPointVisInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            DPointVisInfo __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_isA )( 
            DPointVisInfo __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *RTTI);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            DPointVisInfo __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Base);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Parent )( 
            DPointVisInfo __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *Base);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            DPointVisInfo __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *App);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Application )( 
            DPointVisInfo __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *App);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Style )( 
            DPointVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Style);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Style )( 
            DPointVisInfo __RPC_FAR * This,
            /* [in] */ int Style);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Priority )( 
            DPointVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Prio);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Priority )( 
            DPointVisInfo __RPC_FAR * This,
            /* [in] */ int Prio);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            DPointVisInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Desc);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            DPointVisInfo __RPC_FAR * This,
            /* [in] */ BSTR Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MainColor )( 
            DPointVisInfo __RPC_FAR * This,
            /* [retval][out] */ TRIASCOLOR __RPC_FAR *Main);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MainColor )( 
            DPointVisInfo __RPC_FAR * This,
            /* [in] */ TRIASCOLOR Main);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Changed )( 
            DPointVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Changed )( 
            DPointVisInfo __RPC_FAR * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VisString )( 
            DPointVisInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Locatable )( 
            DPointVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Locatable )( 
            DPointVisInfo __RPC_FAR * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            DPointVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            DPointVisInfo __RPC_FAR * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GeometryName )( 
            DPointVisInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Desc);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GeometryName )( 
            DPointVisInfo __RPC_FAR * This,
            /* [in] */ BSTR Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SizeX )( 
            DPointVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *X);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SizeX )( 
            DPointVisInfo __RPC_FAR * This,
            /* [in] */ int X);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SizeY )( 
            DPointVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Y);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SizeY )( 
            DPointVisInfo __RPC_FAR * This,
            /* [in] */ int Y);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Rotate )( 
            DPointVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Rot);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Rotate )( 
            DPointVisInfo __RPC_FAR * This,
            /* [in] */ int Rot);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BkColor )( 
            DPointVisInfo __RPC_FAR * This,
            /* [retval][out] */ TRIASCOLOR __RPC_FAR *Back);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BkColor )( 
            DPointVisInfo __RPC_FAR * This,
            /* [in] */ TRIASCOLOR Back);
        
        END_INTERFACE
    } DPointVisInfoVtbl;

    interface DPointVisInfo
    {
        CONST_VTBL struct DPointVisInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define DPointVisInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define DPointVisInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define DPointVisInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define DPointVisInfo_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define DPointVisInfo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define DPointVisInfo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define DPointVisInfo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define DPointVisInfo_get_isA(This,RTTI)	\
    (This)->lpVtbl -> get_isA(This,RTTI)

#define DPointVisInfo_get_Parent(This,Base)	\
    (This)->lpVtbl -> get_Parent(This,Base)

#define DPointVisInfo_put_Parent(This,Base)	\
    (This)->lpVtbl -> put_Parent(This,Base)

#define DPointVisInfo_get_Application(This,App)	\
    (This)->lpVtbl -> get_Application(This,App)

#define DPointVisInfo_put_Application(This,App)	\
    (This)->lpVtbl -> put_Application(This,App)


#define DPointVisInfo_get_Style(This,Style)	\
    (This)->lpVtbl -> get_Style(This,Style)

#define DPointVisInfo_put_Style(This,Style)	\
    (This)->lpVtbl -> put_Style(This,Style)

#define DPointVisInfo_get_Priority(This,Prio)	\
    (This)->lpVtbl -> get_Priority(This,Prio)

#define DPointVisInfo_put_Priority(This,Prio)	\
    (This)->lpVtbl -> put_Priority(This,Prio)

#define DPointVisInfo_get_Name(This,Desc)	\
    (This)->lpVtbl -> get_Name(This,Desc)

#define DPointVisInfo_put_Name(This,Desc)	\
    (This)->lpVtbl -> put_Name(This,Desc)

#define DPointVisInfo_get_MainColor(This,Main)	\
    (This)->lpVtbl -> get_MainColor(This,Main)

#define DPointVisInfo_put_MainColor(This,Main)	\
    (This)->lpVtbl -> put_MainColor(This,Main)

#define DPointVisInfo_get_Changed(This,Flags)	\
    (This)->lpVtbl -> get_Changed(This,Flags)

#define DPointVisInfo_put_Changed(This,Flags)	\
    (This)->lpVtbl -> put_Changed(This,Flags)

#define DPointVisInfo_get_VisString(This,Desc)	\
    (This)->lpVtbl -> get_VisString(This,Desc)

#define DPointVisInfo_get_Locatable(This,Flags)	\
    (This)->lpVtbl -> get_Locatable(This,Flags)

#define DPointVisInfo_put_Locatable(This,Flags)	\
    (This)->lpVtbl -> put_Locatable(This,Flags)

#define DPointVisInfo_get_Visible(This,Flags)	\
    (This)->lpVtbl -> get_Visible(This,Flags)

#define DPointVisInfo_put_Visible(This,Flags)	\
    (This)->lpVtbl -> put_Visible(This,Flags)

#define DPointVisInfo_get_GeometryName(This,Desc)	\
    (This)->lpVtbl -> get_GeometryName(This,Desc)

#define DPointVisInfo_put_GeometryName(This,Desc)	\
    (This)->lpVtbl -> put_GeometryName(This,Desc)


#define DPointVisInfo_get_SizeX(This,X)	\
    (This)->lpVtbl -> get_SizeX(This,X)

#define DPointVisInfo_put_SizeX(This,X)	\
    (This)->lpVtbl -> put_SizeX(This,X)

#define DPointVisInfo_get_SizeY(This,Y)	\
    (This)->lpVtbl -> get_SizeY(This,Y)

#define DPointVisInfo_put_SizeY(This,Y)	\
    (This)->lpVtbl -> put_SizeY(This,Y)

#define DPointVisInfo_get_Rotate(This,Rot)	\
    (This)->lpVtbl -> get_Rotate(This,Rot)

#define DPointVisInfo_put_Rotate(This,Rot)	\
    (This)->lpVtbl -> put_Rotate(This,Rot)

#define DPointVisInfo_get_BkColor(This,Back)	\
    (This)->lpVtbl -> get_BkColor(This,Back)

#define DPointVisInfo_put_BkColor(This,Back)	\
    (This)->lpVtbl -> put_BkColor(This,Back)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DPointVisInfo_get_SizeX_Proxy( 
    DPointVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *X);


void __RPC_STUB DPointVisInfo_get_SizeX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DPointVisInfo_put_SizeX_Proxy( 
    DPointVisInfo __RPC_FAR * This,
    /* [in] */ int X);


void __RPC_STUB DPointVisInfo_put_SizeX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DPointVisInfo_get_SizeY_Proxy( 
    DPointVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *Y);


void __RPC_STUB DPointVisInfo_get_SizeY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DPointVisInfo_put_SizeY_Proxy( 
    DPointVisInfo __RPC_FAR * This,
    /* [in] */ int Y);


void __RPC_STUB DPointVisInfo_put_SizeY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DPointVisInfo_get_Rotate_Proxy( 
    DPointVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *Rot);


void __RPC_STUB DPointVisInfo_get_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DPointVisInfo_put_Rotate_Proxy( 
    DPointVisInfo __RPC_FAR * This,
    /* [in] */ int Rot);


void __RPC_STUB DPointVisInfo_put_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DPointVisInfo_get_BkColor_Proxy( 
    DPointVisInfo __RPC_FAR * This,
    /* [retval][out] */ TRIASCOLOR __RPC_FAR *Back);


void __RPC_STUB DPointVisInfo_get_BkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DPointVisInfo_put_BkColor_Proxy( 
    DPointVisInfo __RPC_FAR * This,
    /* [in] */ TRIASCOLOR Back);


void __RPC_STUB DPointVisInfo_put_BkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __DPointVisInfo_INTERFACE_DEFINED__ */


#ifndef __DLineVisInfo_INTERFACE_DEFINED__
#define __DLineVisInfo_INTERFACE_DEFINED__

/* interface DLineVisInfo */
/* [helpstring][uuid][dual][oleautomation][object] */ 


EXTERN_C const IID IID_DLineVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("07963868-3123-101C-BB62-00AA0018497C")
    DLineVisInfo : public DVisInfo
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ int __RPC_FAR *Width) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ int Width) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct DLineVisInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            DLineVisInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            DLineVisInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            DLineVisInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            DLineVisInfo __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            DLineVisInfo __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            DLineVisInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            DLineVisInfo __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_isA )( 
            DLineVisInfo __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *RTTI);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            DLineVisInfo __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Base);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Parent )( 
            DLineVisInfo __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *Base);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            DLineVisInfo __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *App);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Application )( 
            DLineVisInfo __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *App);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Style )( 
            DLineVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Style);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Style )( 
            DLineVisInfo __RPC_FAR * This,
            /* [in] */ int Style);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Priority )( 
            DLineVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Prio);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Priority )( 
            DLineVisInfo __RPC_FAR * This,
            /* [in] */ int Prio);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            DLineVisInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Desc);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            DLineVisInfo __RPC_FAR * This,
            /* [in] */ BSTR Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MainColor )( 
            DLineVisInfo __RPC_FAR * This,
            /* [retval][out] */ TRIASCOLOR __RPC_FAR *Main);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MainColor )( 
            DLineVisInfo __RPC_FAR * This,
            /* [in] */ TRIASCOLOR Main);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Changed )( 
            DLineVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Changed )( 
            DLineVisInfo __RPC_FAR * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VisString )( 
            DLineVisInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Locatable )( 
            DLineVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Locatable )( 
            DLineVisInfo __RPC_FAR * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            DLineVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            DLineVisInfo __RPC_FAR * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GeometryName )( 
            DLineVisInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Desc);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GeometryName )( 
            DLineVisInfo __RPC_FAR * This,
            /* [in] */ BSTR Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Width )( 
            DLineVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Width);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Width )( 
            DLineVisInfo __RPC_FAR * This,
            /* [in] */ int Width);
        
        END_INTERFACE
    } DLineVisInfoVtbl;

    interface DLineVisInfo
    {
        CONST_VTBL struct DLineVisInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define DLineVisInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define DLineVisInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define DLineVisInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define DLineVisInfo_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define DLineVisInfo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define DLineVisInfo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define DLineVisInfo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define DLineVisInfo_get_isA(This,RTTI)	\
    (This)->lpVtbl -> get_isA(This,RTTI)

#define DLineVisInfo_get_Parent(This,Base)	\
    (This)->lpVtbl -> get_Parent(This,Base)

#define DLineVisInfo_put_Parent(This,Base)	\
    (This)->lpVtbl -> put_Parent(This,Base)

#define DLineVisInfo_get_Application(This,App)	\
    (This)->lpVtbl -> get_Application(This,App)

#define DLineVisInfo_put_Application(This,App)	\
    (This)->lpVtbl -> put_Application(This,App)


#define DLineVisInfo_get_Style(This,Style)	\
    (This)->lpVtbl -> get_Style(This,Style)

#define DLineVisInfo_put_Style(This,Style)	\
    (This)->lpVtbl -> put_Style(This,Style)

#define DLineVisInfo_get_Priority(This,Prio)	\
    (This)->lpVtbl -> get_Priority(This,Prio)

#define DLineVisInfo_put_Priority(This,Prio)	\
    (This)->lpVtbl -> put_Priority(This,Prio)

#define DLineVisInfo_get_Name(This,Desc)	\
    (This)->lpVtbl -> get_Name(This,Desc)

#define DLineVisInfo_put_Name(This,Desc)	\
    (This)->lpVtbl -> put_Name(This,Desc)

#define DLineVisInfo_get_MainColor(This,Main)	\
    (This)->lpVtbl -> get_MainColor(This,Main)

#define DLineVisInfo_put_MainColor(This,Main)	\
    (This)->lpVtbl -> put_MainColor(This,Main)

#define DLineVisInfo_get_Changed(This,Flags)	\
    (This)->lpVtbl -> get_Changed(This,Flags)

#define DLineVisInfo_put_Changed(This,Flags)	\
    (This)->lpVtbl -> put_Changed(This,Flags)

#define DLineVisInfo_get_VisString(This,Desc)	\
    (This)->lpVtbl -> get_VisString(This,Desc)

#define DLineVisInfo_get_Locatable(This,Flags)	\
    (This)->lpVtbl -> get_Locatable(This,Flags)

#define DLineVisInfo_put_Locatable(This,Flags)	\
    (This)->lpVtbl -> put_Locatable(This,Flags)

#define DLineVisInfo_get_Visible(This,Flags)	\
    (This)->lpVtbl -> get_Visible(This,Flags)

#define DLineVisInfo_put_Visible(This,Flags)	\
    (This)->lpVtbl -> put_Visible(This,Flags)

#define DLineVisInfo_get_GeometryName(This,Desc)	\
    (This)->lpVtbl -> get_GeometryName(This,Desc)

#define DLineVisInfo_put_GeometryName(This,Desc)	\
    (This)->lpVtbl -> put_GeometryName(This,Desc)


#define DLineVisInfo_get_Width(This,Width)	\
    (This)->lpVtbl -> get_Width(This,Width)

#define DLineVisInfo_put_Width(This,Width)	\
    (This)->lpVtbl -> put_Width(This,Width)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DLineVisInfo_get_Width_Proxy( 
    DLineVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *Width);


void __RPC_STUB DLineVisInfo_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DLineVisInfo_put_Width_Proxy( 
    DLineVisInfo __RPC_FAR * This,
    /* [in] */ int Width);


void __RPC_STUB DLineVisInfo_put_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __DLineVisInfo_INTERFACE_DEFINED__ */


#ifndef __DAreaVisInfo_INTERFACE_DEFINED__
#define __DAreaVisInfo_INTERFACE_DEFINED__

/* interface DAreaVisInfo */
/* [helpstring][uuid][object][dual][oleautomation] */ 


EXTERN_C const IID IID_DAreaVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("07963869-3123-101C-BB62-00AA0018497C")
    DAreaVisInfo : public DVisInfo
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ int __RPC_FAR *Width) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ int Width) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Opaque( 
            /* [retval][out] */ int __RPC_FAR *IsOpaque) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Opaque( 
            /* [in] */ int IsOpaque) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_BkContour( 
            /* [retval][out] */ int __RPC_FAR *BkContour) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_BkContour( 
            /* [in] */ int BkContour) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_BkColor( 
            /* [retval][out] */ TRIASCOLOR __RPC_FAR *Back) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_BkColor( 
            /* [in] */ TRIASCOLOR Back) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct DAreaVisInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            DAreaVisInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            DAreaVisInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_isA )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *RTTI);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Base);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Parent )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *Base);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *App);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Application )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *App);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Style )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Style);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Style )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [in] */ int Style);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Priority )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Prio);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Priority )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [in] */ int Prio);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Desc);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [in] */ BSTR Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MainColor )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [retval][out] */ TRIASCOLOR __RPC_FAR *Main);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MainColor )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [in] */ TRIASCOLOR Main);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Changed )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Changed )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VisString )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Locatable )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Locatable )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GeometryName )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Desc);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GeometryName )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [in] */ BSTR Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Width )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Width);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Width )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [in] */ int Width);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Opaque )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *IsOpaque);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Opaque )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [in] */ int IsOpaque);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BkContour )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *BkContour);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BkContour )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [in] */ int BkContour);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BkColor )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [retval][out] */ TRIASCOLOR __RPC_FAR *Back);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BkColor )( 
            DAreaVisInfo __RPC_FAR * This,
            /* [in] */ TRIASCOLOR Back);
        
        END_INTERFACE
    } DAreaVisInfoVtbl;

    interface DAreaVisInfo
    {
        CONST_VTBL struct DAreaVisInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define DAreaVisInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define DAreaVisInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define DAreaVisInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define DAreaVisInfo_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define DAreaVisInfo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define DAreaVisInfo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define DAreaVisInfo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define DAreaVisInfo_get_isA(This,RTTI)	\
    (This)->lpVtbl -> get_isA(This,RTTI)

#define DAreaVisInfo_get_Parent(This,Base)	\
    (This)->lpVtbl -> get_Parent(This,Base)

#define DAreaVisInfo_put_Parent(This,Base)	\
    (This)->lpVtbl -> put_Parent(This,Base)

#define DAreaVisInfo_get_Application(This,App)	\
    (This)->lpVtbl -> get_Application(This,App)

#define DAreaVisInfo_put_Application(This,App)	\
    (This)->lpVtbl -> put_Application(This,App)


#define DAreaVisInfo_get_Style(This,Style)	\
    (This)->lpVtbl -> get_Style(This,Style)

#define DAreaVisInfo_put_Style(This,Style)	\
    (This)->lpVtbl -> put_Style(This,Style)

#define DAreaVisInfo_get_Priority(This,Prio)	\
    (This)->lpVtbl -> get_Priority(This,Prio)

#define DAreaVisInfo_put_Priority(This,Prio)	\
    (This)->lpVtbl -> put_Priority(This,Prio)

#define DAreaVisInfo_get_Name(This,Desc)	\
    (This)->lpVtbl -> get_Name(This,Desc)

#define DAreaVisInfo_put_Name(This,Desc)	\
    (This)->lpVtbl -> put_Name(This,Desc)

#define DAreaVisInfo_get_MainColor(This,Main)	\
    (This)->lpVtbl -> get_MainColor(This,Main)

#define DAreaVisInfo_put_MainColor(This,Main)	\
    (This)->lpVtbl -> put_MainColor(This,Main)

#define DAreaVisInfo_get_Changed(This,Flags)	\
    (This)->lpVtbl -> get_Changed(This,Flags)

#define DAreaVisInfo_put_Changed(This,Flags)	\
    (This)->lpVtbl -> put_Changed(This,Flags)

#define DAreaVisInfo_get_VisString(This,Desc)	\
    (This)->lpVtbl -> get_VisString(This,Desc)

#define DAreaVisInfo_get_Locatable(This,Flags)	\
    (This)->lpVtbl -> get_Locatable(This,Flags)

#define DAreaVisInfo_put_Locatable(This,Flags)	\
    (This)->lpVtbl -> put_Locatable(This,Flags)

#define DAreaVisInfo_get_Visible(This,Flags)	\
    (This)->lpVtbl -> get_Visible(This,Flags)

#define DAreaVisInfo_put_Visible(This,Flags)	\
    (This)->lpVtbl -> put_Visible(This,Flags)

#define DAreaVisInfo_get_GeometryName(This,Desc)	\
    (This)->lpVtbl -> get_GeometryName(This,Desc)

#define DAreaVisInfo_put_GeometryName(This,Desc)	\
    (This)->lpVtbl -> put_GeometryName(This,Desc)


#define DAreaVisInfo_get_Width(This,Width)	\
    (This)->lpVtbl -> get_Width(This,Width)

#define DAreaVisInfo_put_Width(This,Width)	\
    (This)->lpVtbl -> put_Width(This,Width)

#define DAreaVisInfo_get_Opaque(This,IsOpaque)	\
    (This)->lpVtbl -> get_Opaque(This,IsOpaque)

#define DAreaVisInfo_put_Opaque(This,IsOpaque)	\
    (This)->lpVtbl -> put_Opaque(This,IsOpaque)

#define DAreaVisInfo_get_BkContour(This,BkContour)	\
    (This)->lpVtbl -> get_BkContour(This,BkContour)

#define DAreaVisInfo_put_BkContour(This,BkContour)	\
    (This)->lpVtbl -> put_BkContour(This,BkContour)

#define DAreaVisInfo_get_BkColor(This,Back)	\
    (This)->lpVtbl -> get_BkColor(This,Back)

#define DAreaVisInfo_put_BkColor(This,Back)	\
    (This)->lpVtbl -> put_BkColor(This,Back)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DAreaVisInfo_get_Width_Proxy( 
    DAreaVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *Width);


void __RPC_STUB DAreaVisInfo_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DAreaVisInfo_put_Width_Proxy( 
    DAreaVisInfo __RPC_FAR * This,
    /* [in] */ int Width);


void __RPC_STUB DAreaVisInfo_put_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DAreaVisInfo_get_Opaque_Proxy( 
    DAreaVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *IsOpaque);


void __RPC_STUB DAreaVisInfo_get_Opaque_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DAreaVisInfo_put_Opaque_Proxy( 
    DAreaVisInfo __RPC_FAR * This,
    /* [in] */ int IsOpaque);


void __RPC_STUB DAreaVisInfo_put_Opaque_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DAreaVisInfo_get_BkContour_Proxy( 
    DAreaVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *BkContour);


void __RPC_STUB DAreaVisInfo_get_BkContour_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DAreaVisInfo_put_BkContour_Proxy( 
    DAreaVisInfo __RPC_FAR * This,
    /* [in] */ int BkContour);


void __RPC_STUB DAreaVisInfo_put_BkContour_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DAreaVisInfo_get_BkColor_Proxy( 
    DAreaVisInfo __RPC_FAR * This,
    /* [retval][out] */ TRIASCOLOR __RPC_FAR *Back);


void __RPC_STUB DAreaVisInfo_get_BkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DAreaVisInfo_put_BkColor_Proxy( 
    DAreaVisInfo __RPC_FAR * This,
    /* [in] */ TRIASCOLOR Back);


void __RPC_STUB DAreaVisInfo_put_BkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __DAreaVisInfo_INTERFACE_DEFINED__ */


#ifndef __DTextVisInfo_INTERFACE_DEFINED__
#define __DTextVisInfo_INTERFACE_DEFINED__

/* interface DTextVisInfo */
/* [helpstring][uuid][object][dual][oleautomation] */ 

#if !defined(_TEXTVISINFO_DEFINED)
#define _TEXTVISINFO_DEFINED
typedef /* [public] */ 
enum _tagALIGNSTYLE
    {	ALIGNSTYLE_Left	= 0,
	ALIGNSTYLE_Centre	= 1,
	ALIGNSTYLE_Right	= 2,
	ALIGNSTYLE_Full	= 3
    }	ALIGNSTYLE;

typedef /* [public] */ 
enum _tagFRAMESTYLE
    {	FRAMESTYLE_NoFrame	= 0,
	FRAMESTYLE_SimpleFrame	= 0x1,
	FRAMESTYLE_Rounded	= 0x2,
	FRAMESTYLE_TargetColor	= 0x4
    }	FRAMESTYLE;

#endif // _TEXTVISINFO_DEFINED

EXTERN_C const IID IID_DTextVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0796386A-3123-101C-BB62-00AA0018497C")
    DTextVisInfo : public DVisInfo
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SizeX( 
            /* [retval][out] */ int __RPC_FAR *X) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_SizeX( 
            /* [in] */ int X) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SizeY( 
            /* [retval][out] */ int __RPC_FAR *Y) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_SizeY( 
            /* [in] */ int Y) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Bold( 
            /* [retval][out] */ int __RPC_FAR *IsBold) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Bold( 
            /* [in] */ int IsBold) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Italic( 
            /* [retval][out] */ int __RPC_FAR *IsItalic) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Italic( 
            /* [in] */ int IsItalic) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Underline( 
            /* [retval][out] */ int __RPC_FAR *IsUnderlined) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Underline( 
            /* [in] */ int IsUnderlined) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_StrikeThrough( 
            /* [retval][out] */ int __RPC_FAR *IsStrikedThrough) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_StrikeThrough( 
            /* [in] */ int IsStrikedThrough) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_FrameStyle( 
            /* [retval][out] */ FRAMESTYLE __RPC_FAR *FrameStyle) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_FrameStyle( 
            /* [in] */ FRAMESTYLE FrameStyle) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_AlignStyle( 
            /* [retval][out] */ ALIGNSTYLE __RPC_FAR *AlignStyle) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_AlignStyle( 
            /* [in] */ ALIGNSTYLE AlignStyle) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Rotate( 
            /* [retval][out] */ int __RPC_FAR *Rot) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Rotate( 
            /* [in] */ int Rot) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Slant( 
            /* [retval][out] */ int __RPC_FAR *Slant) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Slant( 
            /* [in] */ int Slant) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct DTextVisInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            DTextVisInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            DTextVisInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            DTextVisInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            DTextVisInfo __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            DTextVisInfo __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            DTextVisInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            DTextVisInfo __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_isA )( 
            DTextVisInfo __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *RTTI);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            DTextVisInfo __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Base);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Parent )( 
            DTextVisInfo __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *Base);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            DTextVisInfo __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *App);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Application )( 
            DTextVisInfo __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *App);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Style )( 
            DTextVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Style);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Style )( 
            DTextVisInfo __RPC_FAR * This,
            /* [in] */ int Style);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Priority )( 
            DTextVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Prio);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Priority )( 
            DTextVisInfo __RPC_FAR * This,
            /* [in] */ int Prio);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            DTextVisInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Desc);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            DTextVisInfo __RPC_FAR * This,
            /* [in] */ BSTR Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MainColor )( 
            DTextVisInfo __RPC_FAR * This,
            /* [retval][out] */ TRIASCOLOR __RPC_FAR *Main);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MainColor )( 
            DTextVisInfo __RPC_FAR * This,
            /* [in] */ TRIASCOLOR Main);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Changed )( 
            DTextVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Changed )( 
            DTextVisInfo __RPC_FAR * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VisString )( 
            DTextVisInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Locatable )( 
            DTextVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Locatable )( 
            DTextVisInfo __RPC_FAR * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            DTextVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            DTextVisInfo __RPC_FAR * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GeometryName )( 
            DTextVisInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Desc);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GeometryName )( 
            DTextVisInfo __RPC_FAR * This,
            /* [in] */ BSTR Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SizeX )( 
            DTextVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *X);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SizeX )( 
            DTextVisInfo __RPC_FAR * This,
            /* [in] */ int X);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SizeY )( 
            DTextVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Y);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SizeY )( 
            DTextVisInfo __RPC_FAR * This,
            /* [in] */ int Y);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Bold )( 
            DTextVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *IsBold);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Bold )( 
            DTextVisInfo __RPC_FAR * This,
            /* [in] */ int IsBold);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Italic )( 
            DTextVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *IsItalic);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Italic )( 
            DTextVisInfo __RPC_FAR * This,
            /* [in] */ int IsItalic);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Underline )( 
            DTextVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *IsUnderlined);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Underline )( 
            DTextVisInfo __RPC_FAR * This,
            /* [in] */ int IsUnderlined);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StrikeThrough )( 
            DTextVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *IsStrikedThrough);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StrikeThrough )( 
            DTextVisInfo __RPC_FAR * This,
            /* [in] */ int IsStrikedThrough);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FrameStyle )( 
            DTextVisInfo __RPC_FAR * This,
            /* [retval][out] */ FRAMESTYLE __RPC_FAR *FrameStyle);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FrameStyle )( 
            DTextVisInfo __RPC_FAR * This,
            /* [in] */ FRAMESTYLE FrameStyle);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AlignStyle )( 
            DTextVisInfo __RPC_FAR * This,
            /* [retval][out] */ ALIGNSTYLE __RPC_FAR *AlignStyle);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AlignStyle )( 
            DTextVisInfo __RPC_FAR * This,
            /* [in] */ ALIGNSTYLE AlignStyle);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Rotate )( 
            DTextVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Rot);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Rotate )( 
            DTextVisInfo __RPC_FAR * This,
            /* [in] */ int Rot);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Slant )( 
            DTextVisInfo __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Slant);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Slant )( 
            DTextVisInfo __RPC_FAR * This,
            /* [in] */ int Slant);
        
        END_INTERFACE
    } DTextVisInfoVtbl;

    interface DTextVisInfo
    {
        CONST_VTBL struct DTextVisInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define DTextVisInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define DTextVisInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define DTextVisInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define DTextVisInfo_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define DTextVisInfo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define DTextVisInfo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define DTextVisInfo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define DTextVisInfo_get_isA(This,RTTI)	\
    (This)->lpVtbl -> get_isA(This,RTTI)

#define DTextVisInfo_get_Parent(This,Base)	\
    (This)->lpVtbl -> get_Parent(This,Base)

#define DTextVisInfo_put_Parent(This,Base)	\
    (This)->lpVtbl -> put_Parent(This,Base)

#define DTextVisInfo_get_Application(This,App)	\
    (This)->lpVtbl -> get_Application(This,App)

#define DTextVisInfo_put_Application(This,App)	\
    (This)->lpVtbl -> put_Application(This,App)


#define DTextVisInfo_get_Style(This,Style)	\
    (This)->lpVtbl -> get_Style(This,Style)

#define DTextVisInfo_put_Style(This,Style)	\
    (This)->lpVtbl -> put_Style(This,Style)

#define DTextVisInfo_get_Priority(This,Prio)	\
    (This)->lpVtbl -> get_Priority(This,Prio)

#define DTextVisInfo_put_Priority(This,Prio)	\
    (This)->lpVtbl -> put_Priority(This,Prio)

#define DTextVisInfo_get_Name(This,Desc)	\
    (This)->lpVtbl -> get_Name(This,Desc)

#define DTextVisInfo_put_Name(This,Desc)	\
    (This)->lpVtbl -> put_Name(This,Desc)

#define DTextVisInfo_get_MainColor(This,Main)	\
    (This)->lpVtbl -> get_MainColor(This,Main)

#define DTextVisInfo_put_MainColor(This,Main)	\
    (This)->lpVtbl -> put_MainColor(This,Main)

#define DTextVisInfo_get_Changed(This,Flags)	\
    (This)->lpVtbl -> get_Changed(This,Flags)

#define DTextVisInfo_put_Changed(This,Flags)	\
    (This)->lpVtbl -> put_Changed(This,Flags)

#define DTextVisInfo_get_VisString(This,Desc)	\
    (This)->lpVtbl -> get_VisString(This,Desc)

#define DTextVisInfo_get_Locatable(This,Flags)	\
    (This)->lpVtbl -> get_Locatable(This,Flags)

#define DTextVisInfo_put_Locatable(This,Flags)	\
    (This)->lpVtbl -> put_Locatable(This,Flags)

#define DTextVisInfo_get_Visible(This,Flags)	\
    (This)->lpVtbl -> get_Visible(This,Flags)

#define DTextVisInfo_put_Visible(This,Flags)	\
    (This)->lpVtbl -> put_Visible(This,Flags)

#define DTextVisInfo_get_GeometryName(This,Desc)	\
    (This)->lpVtbl -> get_GeometryName(This,Desc)

#define DTextVisInfo_put_GeometryName(This,Desc)	\
    (This)->lpVtbl -> put_GeometryName(This,Desc)


#define DTextVisInfo_get_SizeX(This,X)	\
    (This)->lpVtbl -> get_SizeX(This,X)

#define DTextVisInfo_put_SizeX(This,X)	\
    (This)->lpVtbl -> put_SizeX(This,X)

#define DTextVisInfo_get_SizeY(This,Y)	\
    (This)->lpVtbl -> get_SizeY(This,Y)

#define DTextVisInfo_put_SizeY(This,Y)	\
    (This)->lpVtbl -> put_SizeY(This,Y)

#define DTextVisInfo_get_Bold(This,IsBold)	\
    (This)->lpVtbl -> get_Bold(This,IsBold)

#define DTextVisInfo_put_Bold(This,IsBold)	\
    (This)->lpVtbl -> put_Bold(This,IsBold)

#define DTextVisInfo_get_Italic(This,IsItalic)	\
    (This)->lpVtbl -> get_Italic(This,IsItalic)

#define DTextVisInfo_put_Italic(This,IsItalic)	\
    (This)->lpVtbl -> put_Italic(This,IsItalic)

#define DTextVisInfo_get_Underline(This,IsUnderlined)	\
    (This)->lpVtbl -> get_Underline(This,IsUnderlined)

#define DTextVisInfo_put_Underline(This,IsUnderlined)	\
    (This)->lpVtbl -> put_Underline(This,IsUnderlined)

#define DTextVisInfo_get_StrikeThrough(This,IsStrikedThrough)	\
    (This)->lpVtbl -> get_StrikeThrough(This,IsStrikedThrough)

#define DTextVisInfo_put_StrikeThrough(This,IsStrikedThrough)	\
    (This)->lpVtbl -> put_StrikeThrough(This,IsStrikedThrough)

#define DTextVisInfo_get_FrameStyle(This,FrameStyle)	\
    (This)->lpVtbl -> get_FrameStyle(This,FrameStyle)

#define DTextVisInfo_put_FrameStyle(This,FrameStyle)	\
    (This)->lpVtbl -> put_FrameStyle(This,FrameStyle)

#define DTextVisInfo_get_AlignStyle(This,AlignStyle)	\
    (This)->lpVtbl -> get_AlignStyle(This,AlignStyle)

#define DTextVisInfo_put_AlignStyle(This,AlignStyle)	\
    (This)->lpVtbl -> put_AlignStyle(This,AlignStyle)

#define DTextVisInfo_get_Rotate(This,Rot)	\
    (This)->lpVtbl -> get_Rotate(This,Rot)

#define DTextVisInfo_put_Rotate(This,Rot)	\
    (This)->lpVtbl -> put_Rotate(This,Rot)

#define DTextVisInfo_get_Slant(This,Slant)	\
    (This)->lpVtbl -> get_Slant(This,Slant)

#define DTextVisInfo_put_Slant(This,Slant)	\
    (This)->lpVtbl -> put_Slant(This,Slant)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_get_SizeX_Proxy( 
    DTextVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *X);


void __RPC_STUB DTextVisInfo_get_SizeX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_put_SizeX_Proxy( 
    DTextVisInfo __RPC_FAR * This,
    /* [in] */ int X);


void __RPC_STUB DTextVisInfo_put_SizeX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_get_SizeY_Proxy( 
    DTextVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *Y);


void __RPC_STUB DTextVisInfo_get_SizeY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_put_SizeY_Proxy( 
    DTextVisInfo __RPC_FAR * This,
    /* [in] */ int Y);


void __RPC_STUB DTextVisInfo_put_SizeY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_get_Bold_Proxy( 
    DTextVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *IsBold);


void __RPC_STUB DTextVisInfo_get_Bold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_put_Bold_Proxy( 
    DTextVisInfo __RPC_FAR * This,
    /* [in] */ int IsBold);


void __RPC_STUB DTextVisInfo_put_Bold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_get_Italic_Proxy( 
    DTextVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *IsItalic);


void __RPC_STUB DTextVisInfo_get_Italic_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_put_Italic_Proxy( 
    DTextVisInfo __RPC_FAR * This,
    /* [in] */ int IsItalic);


void __RPC_STUB DTextVisInfo_put_Italic_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_get_Underline_Proxy( 
    DTextVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *IsUnderlined);


void __RPC_STUB DTextVisInfo_get_Underline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_put_Underline_Proxy( 
    DTextVisInfo __RPC_FAR * This,
    /* [in] */ int IsUnderlined);


void __RPC_STUB DTextVisInfo_put_Underline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_get_StrikeThrough_Proxy( 
    DTextVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *IsStrikedThrough);


void __RPC_STUB DTextVisInfo_get_StrikeThrough_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_put_StrikeThrough_Proxy( 
    DTextVisInfo __RPC_FAR * This,
    /* [in] */ int IsStrikedThrough);


void __RPC_STUB DTextVisInfo_put_StrikeThrough_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_get_FrameStyle_Proxy( 
    DTextVisInfo __RPC_FAR * This,
    /* [retval][out] */ FRAMESTYLE __RPC_FAR *FrameStyle);


void __RPC_STUB DTextVisInfo_get_FrameStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_put_FrameStyle_Proxy( 
    DTextVisInfo __RPC_FAR * This,
    /* [in] */ FRAMESTYLE FrameStyle);


void __RPC_STUB DTextVisInfo_put_FrameStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_get_AlignStyle_Proxy( 
    DTextVisInfo __RPC_FAR * This,
    /* [retval][out] */ ALIGNSTYLE __RPC_FAR *AlignStyle);


void __RPC_STUB DTextVisInfo_get_AlignStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_put_AlignStyle_Proxy( 
    DTextVisInfo __RPC_FAR * This,
    /* [in] */ ALIGNSTYLE AlignStyle);


void __RPC_STUB DTextVisInfo_put_AlignStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_get_Rotate_Proxy( 
    DTextVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *Rot);


void __RPC_STUB DTextVisInfo_get_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_put_Rotate_Proxy( 
    DTextVisInfo __RPC_FAR * This,
    /* [in] */ int Rot);


void __RPC_STUB DTextVisInfo_put_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_get_Slant_Proxy( 
    DTextVisInfo __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *Slant);


void __RPC_STUB DTextVisInfo_get_Slant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_put_Slant_Proxy( 
    DTextVisInfo __RPC_FAR * This,
    /* [in] */ int Slant);


void __RPC_STUB DTextVisInfo_put_Slant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __DTextVisInfo_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
