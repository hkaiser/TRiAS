/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Apr 19 12:19:12 1999
 */
/* Compiler settings for ProgInd2.idl:
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

#ifndef __ProgInd2_h__
#define __ProgInd2_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IProgressIndicator2_FWD_DEFINED__
#define __IProgressIndicator2_FWD_DEFINED__
typedef interface IProgressIndicator2 IProgressIndicator2;
#endif 	/* __IProgressIndicator2_FWD_DEFINED__ */


#ifndef __IMultiProgressIndicator_FWD_DEFINED__
#define __IMultiProgressIndicator_FWD_DEFINED__
typedef interface IMultiProgressIndicator IMultiProgressIndicator;
#endif 	/* __IMultiProgressIndicator_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_ProgInd2_0000 */
/* [local] */ 



#ifndef _LPPROGRESSINDICATOR_DEFINED
#define _LPPROGRESSINDICATOR_DEFINED


extern RPC_IF_HANDLE __MIDL_itf_ProgInd2_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ProgInd2_0000_v0_0_s_ifspec;

#ifndef __IProgressIndicator2_INTERFACE_DEFINED__
#define __IProgressIndicator2_INTERFACE_DEFINED__

/* interface IProgressIndicator2 */
/* [object][unique][helpstring][oleautomation][dual][uuid] */ 

typedef 
enum tagPIFLAGS
    {	PIFLAGS_CAPTION	= 0x1,
	PIFLAGS_FILE	= 0x2,
	PIFLAGS_FILENAME	= 0x4,
	PIFLAGS_STATUS	= 0x8,
	PIFLAGS_RESULT	= 0x10,
	PIFLAGS_TIME	= 0x20,
	PIFLAGS_ADJUSTPERCENT	= 0x40,
	PIFLAGS_INIT_SHOWWINDOW	= 0x100,
	PIFLAGS_AVI_COPY	= 0x1000,
	PIFLAGS_AVI_MOVE	= 0x2000,
	PIFLAGS_AVI_DELETE	= 0x3000,
	PIFLAGS_AVI_MASK	= 0x7000,
	PIFLAGS_ALL	= 0x7f,
	PIFLAGS_RESETCANCEL	= 0x8000
    }	PIFLAGS;


EXTERN_C const IID IID_IProgressIndicator2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("079638D1-3123-101C-BB62-00AA0018497C")
    IProgressIndicator2 : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE InitNew( 
            /* [in] */ LONG hWndParent,
            /* [in] */ DWORD dwReserved,
            /* [retval][out] */ LONG __RPC_FAR *phWnd) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Restart( 
            /* [in] */ ULONG ulMinPos,
            /* [in] */ ULONG ulMaxPos,
            /* [in] */ PIFLAGS rgFlags) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ChangeText( 
            /* [in] */ PIFLAGS rgWhichText,
            /* [in] */ BSTR bstrNewText) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RetrieveText( 
            /* [in] */ PIFLAGS rgWhichText,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrOutText) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetPosition( 
            /* [in] */ ULONG ulNewPos,
            /* [retval][out] */ INT __RPC_FAR *piPercent) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE IncrementPosition( 
            /* [retval][out] */ INT __RPC_FAR *piPercent) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE IsCanceled( void) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Flags( 
            /* [retval][out] */ PIFLAGS __RPC_FAR *prgFlags) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Flags( 
            /* [in] */ PIFLAGS rgFlags) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RetrieveRange( 
            /* [out][in] */ ULONG __RPC_FAR *pulMinPos,
            /* [out][in] */ ULONG __RPC_FAR *pulMaxPos) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IProgressIndicator2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IProgressIndicator2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IProgressIndicator2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IProgressIndicator2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IProgressIndicator2 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IProgressIndicator2 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IProgressIndicator2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IProgressIndicator2 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InitNew )( 
            IProgressIndicator2 __RPC_FAR * This,
            /* [in] */ LONG hWndParent,
            /* [in] */ DWORD dwReserved,
            /* [retval][out] */ LONG __RPC_FAR *phWnd);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Restart )( 
            IProgressIndicator2 __RPC_FAR * This,
            /* [in] */ ULONG ulMinPos,
            /* [in] */ ULONG ulMaxPos,
            /* [in] */ PIFLAGS rgFlags);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ChangeText )( 
            IProgressIndicator2 __RPC_FAR * This,
            /* [in] */ PIFLAGS rgWhichText,
            /* [in] */ BSTR bstrNewText);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RetrieveText )( 
            IProgressIndicator2 __RPC_FAR * This,
            /* [in] */ PIFLAGS rgWhichText,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrOutText);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPosition )( 
            IProgressIndicator2 __RPC_FAR * This,
            /* [in] */ ULONG ulNewPos,
            /* [retval][out] */ INT __RPC_FAR *piPercent);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IncrementPosition )( 
            IProgressIndicator2 __RPC_FAR * This,
            /* [retval][out] */ INT __RPC_FAR *piPercent);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsCanceled )( 
            IProgressIndicator2 __RPC_FAR * This);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Flags )( 
            IProgressIndicator2 __RPC_FAR * This,
            /* [retval][out] */ PIFLAGS __RPC_FAR *prgFlags);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Flags )( 
            IProgressIndicator2 __RPC_FAR * This,
            /* [in] */ PIFLAGS rgFlags);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RetrieveRange )( 
            IProgressIndicator2 __RPC_FAR * This,
            /* [out][in] */ ULONG __RPC_FAR *pulMinPos,
            /* [out][in] */ ULONG __RPC_FAR *pulMaxPos);
        
        END_INTERFACE
    } IProgressIndicator2Vtbl;

    interface IProgressIndicator2
    {
        CONST_VTBL struct IProgressIndicator2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProgressIndicator2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IProgressIndicator2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IProgressIndicator2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IProgressIndicator2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IProgressIndicator2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IProgressIndicator2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IProgressIndicator2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IProgressIndicator2_InitNew(This,hWndParent,dwReserved,phWnd)	\
    (This)->lpVtbl -> InitNew(This,hWndParent,dwReserved,phWnd)

#define IProgressIndicator2_Restart(This,ulMinPos,ulMaxPos,rgFlags)	\
    (This)->lpVtbl -> Restart(This,ulMinPos,ulMaxPos,rgFlags)

#define IProgressIndicator2_ChangeText(This,rgWhichText,bstrNewText)	\
    (This)->lpVtbl -> ChangeText(This,rgWhichText,bstrNewText)

#define IProgressIndicator2_RetrieveText(This,rgWhichText,pbstrOutText)	\
    (This)->lpVtbl -> RetrieveText(This,rgWhichText,pbstrOutText)

#define IProgressIndicator2_SetPosition(This,ulNewPos,piPercent)	\
    (This)->lpVtbl -> SetPosition(This,ulNewPos,piPercent)

#define IProgressIndicator2_IncrementPosition(This,piPercent)	\
    (This)->lpVtbl -> IncrementPosition(This,piPercent)

#define IProgressIndicator2_IsCanceled(This)	\
    (This)->lpVtbl -> IsCanceled(This)

#define IProgressIndicator2_get_Flags(This,prgFlags)	\
    (This)->lpVtbl -> get_Flags(This,prgFlags)

#define IProgressIndicator2_put_Flags(This,rgFlags)	\
    (This)->lpVtbl -> put_Flags(This,rgFlags)

#define IProgressIndicator2_RetrieveRange(This,pulMinPos,pulMaxPos)	\
    (This)->lpVtbl -> RetrieveRange(This,pulMinPos,pulMaxPos)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE IProgressIndicator2_InitNew_Proxy( 
    IProgressIndicator2 __RPC_FAR * This,
    /* [in] */ LONG hWndParent,
    /* [in] */ DWORD dwReserved,
    /* [retval][out] */ LONG __RPC_FAR *phWnd);


void __RPC_STUB IProgressIndicator2_InitNew_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IProgressIndicator2_Restart_Proxy( 
    IProgressIndicator2 __RPC_FAR * This,
    /* [in] */ ULONG ulMinPos,
    /* [in] */ ULONG ulMaxPos,
    /* [in] */ PIFLAGS rgFlags);


void __RPC_STUB IProgressIndicator2_Restart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IProgressIndicator2_ChangeText_Proxy( 
    IProgressIndicator2 __RPC_FAR * This,
    /* [in] */ PIFLAGS rgWhichText,
    /* [in] */ BSTR bstrNewText);


void __RPC_STUB IProgressIndicator2_ChangeText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IProgressIndicator2_RetrieveText_Proxy( 
    IProgressIndicator2 __RPC_FAR * This,
    /* [in] */ PIFLAGS rgWhichText,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrOutText);


void __RPC_STUB IProgressIndicator2_RetrieveText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IProgressIndicator2_SetPosition_Proxy( 
    IProgressIndicator2 __RPC_FAR * This,
    /* [in] */ ULONG ulNewPos,
    /* [retval][out] */ INT __RPC_FAR *piPercent);


void __RPC_STUB IProgressIndicator2_SetPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IProgressIndicator2_IncrementPosition_Proxy( 
    IProgressIndicator2 __RPC_FAR * This,
    /* [retval][out] */ INT __RPC_FAR *piPercent);


void __RPC_STUB IProgressIndicator2_IncrementPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IProgressIndicator2_IsCanceled_Proxy( 
    IProgressIndicator2 __RPC_FAR * This);


void __RPC_STUB IProgressIndicator2_IsCanceled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IProgressIndicator2_get_Flags_Proxy( 
    IProgressIndicator2 __RPC_FAR * This,
    /* [retval][out] */ PIFLAGS __RPC_FAR *prgFlags);


void __RPC_STUB IProgressIndicator2_get_Flags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IProgressIndicator2_put_Flags_Proxy( 
    IProgressIndicator2 __RPC_FAR * This,
    /* [in] */ PIFLAGS rgFlags);


void __RPC_STUB IProgressIndicator2_put_Flags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IProgressIndicator2_RetrieveRange_Proxy( 
    IProgressIndicator2 __RPC_FAR * This,
    /* [out][in] */ ULONG __RPC_FAR *pulMinPos,
    /* [out][in] */ ULONG __RPC_FAR *pulMaxPos);


void __RPC_STUB IProgressIndicator2_RetrieveRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IProgressIndicator2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_ProgInd2_0094 */
/* [local] */ 

#endif
#ifndef _MULTIPROGRESSINDICATOR_DEFINED
#define _MULTIPROGRESSINDICATOR_DEFINED


extern RPC_IF_HANDLE __MIDL_itf_ProgInd2_0094_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ProgInd2_0094_v0_0_s_ifspec;

#ifndef __IMultiProgressIndicator_INTERFACE_DEFINED__
#define __IMultiProgressIndicator_INTERFACE_DEFINED__

/* interface IMultiProgressIndicator */
/* [object][helpstring][oleautomation][dual][uuid] */ 


EXTERN_C const IID IID_IMultiProgressIndicator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("079638D4-3123-101C-BB62-00AA0018497C")
    IMultiProgressIndicator : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ int iRangeCnt,
            /* [in] */ IProgressIndicator2 __RPC_FAR *pPI) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRange( 
            /* [in] */ int iRange,
            /* [retval][out] */ IProgressIndicator2 __RPC_FAR *__RPC_FAR *ppPI) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_RangeCnt( 
            /* [retval][out] */ int __RPC_FAR *piRangeCnt) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMultiProgressIndicatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMultiProgressIndicator __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMultiProgressIndicator __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMultiProgressIndicator __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMultiProgressIndicator __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMultiProgressIndicator __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMultiProgressIndicator __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMultiProgressIndicator __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init )( 
            IMultiProgressIndicator __RPC_FAR * This,
            /* [in] */ int iRangeCnt,
            /* [in] */ IProgressIndicator2 __RPC_FAR *pPI);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRange )( 
            IMultiProgressIndicator __RPC_FAR * This,
            /* [in] */ int iRange,
            /* [retval][out] */ IProgressIndicator2 __RPC_FAR *__RPC_FAR *ppPI);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RangeCnt )( 
            IMultiProgressIndicator __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piRangeCnt);
        
        END_INTERFACE
    } IMultiProgressIndicatorVtbl;

    interface IMultiProgressIndicator
    {
        CONST_VTBL struct IMultiProgressIndicatorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMultiProgressIndicator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMultiProgressIndicator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMultiProgressIndicator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMultiProgressIndicator_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMultiProgressIndicator_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMultiProgressIndicator_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMultiProgressIndicator_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMultiProgressIndicator_Init(This,iRangeCnt,pPI)	\
    (This)->lpVtbl -> Init(This,iRangeCnt,pPI)

#define IMultiProgressIndicator_GetRange(This,iRange,ppPI)	\
    (This)->lpVtbl -> GetRange(This,iRange,ppPI)

#define IMultiProgressIndicator_get_RangeCnt(This,piRangeCnt)	\
    (This)->lpVtbl -> get_RangeCnt(This,piRangeCnt)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMultiProgressIndicator_Init_Proxy( 
    IMultiProgressIndicator __RPC_FAR * This,
    /* [in] */ int iRangeCnt,
    /* [in] */ IProgressIndicator2 __RPC_FAR *pPI);


void __RPC_STUB IMultiProgressIndicator_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMultiProgressIndicator_GetRange_Proxy( 
    IMultiProgressIndicator __RPC_FAR * This,
    /* [in] */ int iRange,
    /* [retval][out] */ IProgressIndicator2 __RPC_FAR *__RPC_FAR *ppPI);


void __RPC_STUB IMultiProgressIndicator_GetRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IMultiProgressIndicator_get_RangeCnt_Proxy( 
    IMultiProgressIndicator __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *piRangeCnt);


void __RPC_STUB IMultiProgressIndicator_get_RangeCnt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMultiProgressIndicator_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_ProgInd2_0095 */
/* [local] */ 

#endif // _MULTIPROGRESSINDICATOR_DEFINED


extern RPC_IF_HANDLE __MIDL_itf_ProgInd2_0095_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ProgInd2_0095_v0_0_s_ifspec;

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
