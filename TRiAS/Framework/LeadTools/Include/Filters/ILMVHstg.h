/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Sep 02 15:29:13 2003
 */
/* Compiler settings for E:\mm\DShowFlt\HistoG\IHistoG.idl:
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

#ifndef __ILMVHstg_h__
#define __ILMVHstg_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ILMVHistoEq_FWD_DEFINED__
#define __ILMVHistoEq_FWD_DEFINED__
typedef interface ILMVHistoEq ILMVHistoEq;
#endif 	/* __ILMVHistoEq_FWD_DEFINED__ */


#ifndef __ILMVHistoView_FWD_DEFINED__
#define __ILMVHistoView_FWD_DEFINED__
typedef interface ILMVHistoView ILMVHistoView;
#endif 	/* __ILMVHistoView_FWD_DEFINED__ */


#ifndef __ILMVHistoEqDisp_FWD_DEFINED__
#define __ILMVHistoEqDisp_FWD_DEFINED__
typedef interface ILMVHistoEqDisp ILMVHistoEqDisp;
#endif 	/* __ILMVHistoEqDisp_FWD_DEFINED__ */


#ifndef __LMVHistoEq_FWD_DEFINED__
#define __LMVHistoEq_FWD_DEFINED__

#ifdef __cplusplus
typedef class LMVHistoEq LMVHistoEq;
#else
typedef struct LMVHistoEq LMVHistoEq;
#endif /* __cplusplus */

#endif 	/* __LMVHistoEq_FWD_DEFINED__ */


#ifndef __ILMVHistoViewDisp1_FWD_DEFINED__
#define __ILMVHistoViewDisp1_FWD_DEFINED__
typedef interface ILMVHistoViewDisp1 ILMVHistoViewDisp1;
#endif 	/* __ILMVHistoViewDisp1_FWD_DEFINED__ */


#ifndef __ILMVHistoViewDisp_FWD_DEFINED__
#define __ILMVHistoViewDisp_FWD_DEFINED__
typedef interface ILMVHistoViewDisp ILMVHistoViewDisp;
#endif 	/* __ILMVHistoViewDisp_FWD_DEFINED__ */


#ifndef __LMVHistoView_FWD_DEFINED__
#define __LMVHistoView_FWD_DEFINED__

#ifdef __cplusplus
typedef class LMVHistoView LMVHistoView;
#else
typedef struct LMVHistoView LMVHistoView;
#endif /* __cplusplus */

#endif 	/* __LMVHistoView_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __LMVHistogLib_LIBRARY_DEFINED__
#define __LMVHistogLib_LIBRARY_DEFINED__

/* library LMVHistogLib */
/* [helpstring][version][uuid] */ 

#ifndef __IHistoG_H__
#define __IHistoG_H__
static const GUID LIBID_LMVHistogLib             = {0xe2b7db81, 0x38c5, 0x11d5, {0x91, 0xf6, 0x00, 0x10, 0x4b, 0xdb, 0x8f, 0xf9}};
static const GUID CLSID_LMVHistoEq               = {0xe2b7db2e, 0x38c5, 0x11d5, {0x91, 0xf6, 0x00, 0x10, 0x4b, 0xdb, 0x8f, 0xf9}};
static const GUID CLSID_LMVHistoEqPropertyPage   = {0xe2b7db30, 0x38c5, 0x11d5, {0x91, 0xf6, 0x00, 0x10, 0x4b, 0xdb, 0x8f, 0xf9}};
static const GUID IID_ILMVHistoEq                = {0xe2b7db2f, 0x38c5, 0x11d5, {0x91, 0xf6, 0x00, 0x10, 0x4b, 0xdb, 0x8f, 0xf9}};
static const GUID CLSID_LMVAboutHistoEq          = {0xe2b7db4d, 0x38c5, 0x11d5, {0x91, 0xf6, 0x00, 0x10, 0x4b, 0xdb, 0x8f, 0xf9}};
static const GUID IID_ILMVHistoEqDisp            = {0xe2b7db82, 0x38c5, 0x11d5, {0x91, 0xf6, 0x00, 0x10, 0x4b, 0xdb, 0x8f, 0xf9}};
static const GUID CLSID_LMVHistoView             = {0xe2b7db2b, 0x38c5, 0x11d5, {0x91, 0xf6, 0x00, 0x10, 0x4b, 0xdb, 0x8f, 0xf9}};
static const GUID CLSID_LMVHistoViewPropertyPage = {0xe2b7db2d, 0x38c5, 0x11d5, {0x91, 0xf6, 0x00, 0x10, 0x4b, 0xdb, 0x8f, 0xf9}};
static const GUID IID_ILMVHistoView              = {0xe2b7db2c, 0x38c5, 0x11d5, {0x91, 0xf6, 0x00, 0x10, 0x4b, 0xdb, 0x8f, 0xf9}};
static const GUID CLSID_LMVAboutHistoView        = {0xe2b7db4e, 0x38c5, 0x11d5, {0x91, 0xf6, 0x00, 0x10, 0x4b, 0xdb, 0x8f, 0xf9}};
static const GUID IID_ILMVHistoViewDisp1         = {0xe2b7db83, 0x38c5, 0x11d5, {0x91, 0xf6, 0x00, 0x10, 0x4b, 0xdb, 0x8f, 0xf9}};
static const GUID IID_ILMVHistoViewDisp          = {0xe2b7dc52, 0x38c5, 0x11d5, {0x91, 0xf6, 0x00, 0x10, 0x4b, 0xdb, 0x8f, 0xf9}};
#endif 
enum{RGB8 = 1035,RGB24,REDCHANNEL,GREENCHANNEL,BLUECHANNEL,ALLCHANNELS};
enum{YUY2 = 1, YVYU, UYVY, IYU2};
typedef /* [public][public][public] */ struct  __MIDL___MIDL_itf_IHistoG_0000_0001
    {
    long lHistogramType;
    BOOL bEqualize;
    BOOL bRGBMode;
    BOOL bYUVHistogram;
    BOOL bYUVInput;
    long lDHistogramType;
    BOOL bDEqualize;
    BOOL bDRGBMode;
    }	HISTOEQ_ATTRIBUTES;

typedef /* [public][public][public] */ struct  __MIDL___MIDL_itf_IHistoG_0000_0002
    {
    long lHistogramType;
    BOOL bRGBMode;
    long lDHistogramType;
    BOOL bDRGBMode;
    }	HISTVIEW_ATTRIBUTES;


EXTERN_C const IID LIBID_LMVHistogLib;

#ifndef __ILMVHistoEq_INTERFACE_DEFINED__
#define __ILMVHistoEq_INTERFACE_DEFINED__

/* interface ILMVHistoEq */
/* [unique][helpstring][uuid][local][object] */ 


EXTERN_C const IID IID_ILMVHistoEq;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E2B7DB2F-38C5-11D5-91F6-00104BDB8FF9")
    ILMVHistoEq : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IsLEADInputPinConnected( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsLEADOutputPinConnected( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetHistoEq_Attributes( 
            HISTOEQ_ATTRIBUTES __RPC_FAR *__MIDL_0015) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetHistoEq_Attributes( 
            HISTOEQ_ATTRIBUTES __MIDL_0016) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIODimensions( 
            /* [out] */ long __RPC_FAR *plInWidth,
            /* [out] */ long __RPC_FAR *plInHeight,
            /* [out] */ long __RPC_FAR *plOutWidth,
            /* [out] */ long __RPC_FAR *plOutHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIOBitCount( 
            /* [out] */ int __RPC_FAR *plInBits,
            /* [out] */ int __RPC_FAR *plOutBits) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILMVHistoEqVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILMVHistoEq __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILMVHistoEq __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILMVHistoEq __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsLEADInputPinConnected )( 
            ILMVHistoEq __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsLEADOutputPinConnected )( 
            ILMVHistoEq __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHistoEq_Attributes )( 
            ILMVHistoEq __RPC_FAR * This,
            HISTOEQ_ATTRIBUTES __RPC_FAR *__MIDL_0015);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetHistoEq_Attributes )( 
            ILMVHistoEq __RPC_FAR * This,
            HISTOEQ_ATTRIBUTES __MIDL_0016);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIODimensions )( 
            ILMVHistoEq __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *plInWidth,
            /* [out] */ long __RPC_FAR *plInHeight,
            /* [out] */ long __RPC_FAR *plOutWidth,
            /* [out] */ long __RPC_FAR *plOutHeight);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIOBitCount )( 
            ILMVHistoEq __RPC_FAR * This,
            /* [out] */ int __RPC_FAR *plInBits,
            /* [out] */ int __RPC_FAR *plOutBits);
        
        END_INTERFACE
    } ILMVHistoEqVtbl;

    interface ILMVHistoEq
    {
        CONST_VTBL struct ILMVHistoEqVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILMVHistoEq_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILMVHistoEq_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILMVHistoEq_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILMVHistoEq_IsLEADInputPinConnected(This)	\
    (This)->lpVtbl -> IsLEADInputPinConnected(This)

#define ILMVHistoEq_IsLEADOutputPinConnected(This)	\
    (This)->lpVtbl -> IsLEADOutputPinConnected(This)

#define ILMVHistoEq_GetHistoEq_Attributes(This,__MIDL_0015)	\
    (This)->lpVtbl -> GetHistoEq_Attributes(This,__MIDL_0015)

#define ILMVHistoEq_SetHistoEq_Attributes(This,__MIDL_0016)	\
    (This)->lpVtbl -> SetHistoEq_Attributes(This,__MIDL_0016)

#define ILMVHistoEq_GetIODimensions(This,plInWidth,plInHeight,plOutWidth,plOutHeight)	\
    (This)->lpVtbl -> GetIODimensions(This,plInWidth,plInHeight,plOutWidth,plOutHeight)

#define ILMVHistoEq_GetIOBitCount(This,plInBits,plOutBits)	\
    (This)->lpVtbl -> GetIOBitCount(This,plInBits,plOutBits)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ILMVHistoEq_IsLEADInputPinConnected_Proxy( 
    ILMVHistoEq __RPC_FAR * This);


void __RPC_STUB ILMVHistoEq_IsLEADInputPinConnected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ILMVHistoEq_IsLEADOutputPinConnected_Proxy( 
    ILMVHistoEq __RPC_FAR * This);


void __RPC_STUB ILMVHistoEq_IsLEADOutputPinConnected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ILMVHistoEq_GetHistoEq_Attributes_Proxy( 
    ILMVHistoEq __RPC_FAR * This,
    HISTOEQ_ATTRIBUTES __RPC_FAR *__MIDL_0015);


void __RPC_STUB ILMVHistoEq_GetHistoEq_Attributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ILMVHistoEq_SetHistoEq_Attributes_Proxy( 
    ILMVHistoEq __RPC_FAR * This,
    HISTOEQ_ATTRIBUTES __MIDL_0016);


void __RPC_STUB ILMVHistoEq_SetHistoEq_Attributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ILMVHistoEq_GetIODimensions_Proxy( 
    ILMVHistoEq __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *plInWidth,
    /* [out] */ long __RPC_FAR *plInHeight,
    /* [out] */ long __RPC_FAR *plOutWidth,
    /* [out] */ long __RPC_FAR *plOutHeight);


void __RPC_STUB ILMVHistoEq_GetIODimensions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ILMVHistoEq_GetIOBitCount_Proxy( 
    ILMVHistoEq __RPC_FAR * This,
    /* [out] */ int __RPC_FAR *plInBits,
    /* [out] */ int __RPC_FAR *plOutBits);


void __RPC_STUB ILMVHistoEq_GetIOBitCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILMVHistoEq_INTERFACE_DEFINED__ */


#ifndef __ILMVHistoView_INTERFACE_DEFINED__
#define __ILMVHistoView_INTERFACE_DEFINED__

/* interface ILMVHistoView */
/* [unique][helpstring][uuid][local][object] */ 


EXTERN_C const IID IID_ILMVHistoView;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E2B7DB2C-38C5-11D5-91F6-00104BDB8FF9")
    ILMVHistoView : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IsLEADInputPinConnected( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsLEADOutputPinConnected( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetHistogramArray( 
            long __RPC_FAR *HistogramArray,
            __int64 __RPC_FAR *llFrameCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetHistView_Attributes( 
            HISTVIEW_ATTRIBUTES __RPC_FAR *__MIDL_0017) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetHistView_Attributes( 
            HISTVIEW_ATTRIBUTES __MIDL_0018) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIODimensions( 
            /* [out] */ long __RPC_FAR *plInWidth,
            /* [out] */ long __RPC_FAR *plInHeight,
            /* [out] */ long __RPC_FAR *plOutWidth,
            /* [out] */ long __RPC_FAR *plOutHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIOBitCount( 
            /* [out] */ int __RPC_FAR *plInBits,
            /* [out] */ int __RPC_FAR *plOutBits) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILMVHistoViewVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILMVHistoView __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILMVHistoView __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILMVHistoView __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsLEADInputPinConnected )( 
            ILMVHistoView __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsLEADOutputPinConnected )( 
            ILMVHistoView __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHistogramArray )( 
            ILMVHistoView __RPC_FAR * This,
            long __RPC_FAR *HistogramArray,
            __int64 __RPC_FAR *llFrameCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHistView_Attributes )( 
            ILMVHistoView __RPC_FAR * This,
            HISTVIEW_ATTRIBUTES __RPC_FAR *__MIDL_0017);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetHistView_Attributes )( 
            ILMVHistoView __RPC_FAR * This,
            HISTVIEW_ATTRIBUTES __MIDL_0018);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIODimensions )( 
            ILMVHistoView __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *plInWidth,
            /* [out] */ long __RPC_FAR *plInHeight,
            /* [out] */ long __RPC_FAR *plOutWidth,
            /* [out] */ long __RPC_FAR *plOutHeight);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIOBitCount )( 
            ILMVHistoView __RPC_FAR * This,
            /* [out] */ int __RPC_FAR *plInBits,
            /* [out] */ int __RPC_FAR *plOutBits);
        
        END_INTERFACE
    } ILMVHistoViewVtbl;

    interface ILMVHistoView
    {
        CONST_VTBL struct ILMVHistoViewVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILMVHistoView_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILMVHistoView_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILMVHistoView_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILMVHistoView_IsLEADInputPinConnected(This)	\
    (This)->lpVtbl -> IsLEADInputPinConnected(This)

#define ILMVHistoView_IsLEADOutputPinConnected(This)	\
    (This)->lpVtbl -> IsLEADOutputPinConnected(This)

#define ILMVHistoView_GetHistogramArray(This,HistogramArray,llFrameCount)	\
    (This)->lpVtbl -> GetHistogramArray(This,HistogramArray,llFrameCount)

#define ILMVHistoView_GetHistView_Attributes(This,__MIDL_0017)	\
    (This)->lpVtbl -> GetHistView_Attributes(This,__MIDL_0017)

#define ILMVHistoView_SetHistView_Attributes(This,__MIDL_0018)	\
    (This)->lpVtbl -> SetHistView_Attributes(This,__MIDL_0018)

#define ILMVHistoView_GetIODimensions(This,plInWidth,plInHeight,plOutWidth,plOutHeight)	\
    (This)->lpVtbl -> GetIODimensions(This,plInWidth,plInHeight,plOutWidth,plOutHeight)

#define ILMVHistoView_GetIOBitCount(This,plInBits,plOutBits)	\
    (This)->lpVtbl -> GetIOBitCount(This,plInBits,plOutBits)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ILMVHistoView_IsLEADInputPinConnected_Proxy( 
    ILMVHistoView __RPC_FAR * This);


void __RPC_STUB ILMVHistoView_IsLEADInputPinConnected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ILMVHistoView_IsLEADOutputPinConnected_Proxy( 
    ILMVHistoView __RPC_FAR * This);


void __RPC_STUB ILMVHistoView_IsLEADOutputPinConnected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ILMVHistoView_GetHistogramArray_Proxy( 
    ILMVHistoView __RPC_FAR * This,
    long __RPC_FAR *HistogramArray,
    __int64 __RPC_FAR *llFrameCount);


void __RPC_STUB ILMVHistoView_GetHistogramArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ILMVHistoView_GetHistView_Attributes_Proxy( 
    ILMVHistoView __RPC_FAR * This,
    HISTVIEW_ATTRIBUTES __RPC_FAR *__MIDL_0017);


void __RPC_STUB ILMVHistoView_GetHistView_Attributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ILMVHistoView_SetHistView_Attributes_Proxy( 
    ILMVHistoView __RPC_FAR * This,
    HISTVIEW_ATTRIBUTES __MIDL_0018);


void __RPC_STUB ILMVHistoView_SetHistView_Attributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ILMVHistoView_GetIODimensions_Proxy( 
    ILMVHistoView __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *plInWidth,
    /* [out] */ long __RPC_FAR *plInHeight,
    /* [out] */ long __RPC_FAR *plOutWidth,
    /* [out] */ long __RPC_FAR *plOutHeight);


void __RPC_STUB ILMVHistoView_GetIODimensions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ILMVHistoView_GetIOBitCount_Proxy( 
    ILMVHistoView __RPC_FAR * This,
    /* [out] */ int __RPC_FAR *plInBits,
    /* [out] */ int __RPC_FAR *plOutBits);


void __RPC_STUB ILMVHistoView_GetIOBitCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILMVHistoView_INTERFACE_DEFINED__ */


#ifndef __ILMVHistoEqDisp_INTERFACE_DEFINED__
#define __ILMVHistoEqDisp_INTERFACE_DEFINED__

/* interface ILMVHistoEqDisp */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ILMVHistoEqDisp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E2B7DB82-38C5-11D5-91F6-00104BDB8FF9")
    ILMVHistoEqDisp : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EnableEqualize( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EnableEqualize( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RGBMode( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RGBMode( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HistogramType( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HistogramType( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultEnableEqualize( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DefaultEnableEqualize( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultRGBMode( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DefaultRGBMode( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultHistogramType( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DefaultHistogramType( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsLEADInputPinConnected( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsLEADOutputPinConnected( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InWidth( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InHeight( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutWidth( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutHeight( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InBits( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutBits( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_YUVHistogram( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_YUVHistogram( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_YUVInput( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILMVHistoEqDispVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILMVHistoEqDisp __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILMVHistoEqDisp __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EnableEqualize )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EnableEqualize )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RGBMode )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RGBMode )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HistogramType )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HistogramType )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DefaultEnableEqualize )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DefaultEnableEqualize )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DefaultRGBMode )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DefaultRGBMode )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DefaultHistogramType )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DefaultHistogramType )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsLEADInputPinConnected )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsLEADOutputPinConnected )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InWidth )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InHeight )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OutWidth )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OutHeight )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InBits )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OutBits )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_YUVHistogram )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_YUVHistogram )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_YUVInput )( 
            ILMVHistoEqDisp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        END_INTERFACE
    } ILMVHistoEqDispVtbl;

    interface ILMVHistoEqDisp
    {
        CONST_VTBL struct ILMVHistoEqDispVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILMVHistoEqDisp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILMVHistoEqDisp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILMVHistoEqDisp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILMVHistoEqDisp_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ILMVHistoEqDisp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ILMVHistoEqDisp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ILMVHistoEqDisp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ILMVHistoEqDisp_get_EnableEqualize(This,pVal)	\
    (This)->lpVtbl -> get_EnableEqualize(This,pVal)

#define ILMVHistoEqDisp_put_EnableEqualize(This,newVal)	\
    (This)->lpVtbl -> put_EnableEqualize(This,newVal)

#define ILMVHistoEqDisp_get_RGBMode(This,pVal)	\
    (This)->lpVtbl -> get_RGBMode(This,pVal)

#define ILMVHistoEqDisp_put_RGBMode(This,newVal)	\
    (This)->lpVtbl -> put_RGBMode(This,newVal)

#define ILMVHistoEqDisp_get_HistogramType(This,pVal)	\
    (This)->lpVtbl -> get_HistogramType(This,pVal)

#define ILMVHistoEqDisp_put_HistogramType(This,newVal)	\
    (This)->lpVtbl -> put_HistogramType(This,newVal)

#define ILMVHistoEqDisp_get_DefaultEnableEqualize(This,pVal)	\
    (This)->lpVtbl -> get_DefaultEnableEqualize(This,pVal)

#define ILMVHistoEqDisp_put_DefaultEnableEqualize(This,newVal)	\
    (This)->lpVtbl -> put_DefaultEnableEqualize(This,newVal)

#define ILMVHistoEqDisp_get_DefaultRGBMode(This,pVal)	\
    (This)->lpVtbl -> get_DefaultRGBMode(This,pVal)

#define ILMVHistoEqDisp_put_DefaultRGBMode(This,newVal)	\
    (This)->lpVtbl -> put_DefaultRGBMode(This,newVal)

#define ILMVHistoEqDisp_get_DefaultHistogramType(This,pVal)	\
    (This)->lpVtbl -> get_DefaultHistogramType(This,pVal)

#define ILMVHistoEqDisp_put_DefaultHistogramType(This,newVal)	\
    (This)->lpVtbl -> put_DefaultHistogramType(This,newVal)

#define ILMVHistoEqDisp_get_IsLEADInputPinConnected(This,pVal)	\
    (This)->lpVtbl -> get_IsLEADInputPinConnected(This,pVal)

#define ILMVHistoEqDisp_get_IsLEADOutputPinConnected(This,pVal)	\
    (This)->lpVtbl -> get_IsLEADOutputPinConnected(This,pVal)

#define ILMVHistoEqDisp_get_InWidth(This,pVal)	\
    (This)->lpVtbl -> get_InWidth(This,pVal)

#define ILMVHistoEqDisp_get_InHeight(This,pVal)	\
    (This)->lpVtbl -> get_InHeight(This,pVal)

#define ILMVHistoEqDisp_get_OutWidth(This,pVal)	\
    (This)->lpVtbl -> get_OutWidth(This,pVal)

#define ILMVHistoEqDisp_get_OutHeight(This,pVal)	\
    (This)->lpVtbl -> get_OutHeight(This,pVal)

#define ILMVHistoEqDisp_get_InBits(This,pVal)	\
    (This)->lpVtbl -> get_InBits(This,pVal)

#define ILMVHistoEqDisp_get_OutBits(This,pVal)	\
    (This)->lpVtbl -> get_OutBits(This,pVal)

#define ILMVHistoEqDisp_get_YUVHistogram(This,pVal)	\
    (This)->lpVtbl -> get_YUVHistogram(This,pVal)

#define ILMVHistoEqDisp_put_YUVHistogram(This,newVal)	\
    (This)->lpVtbl -> put_YUVHistogram(This,newVal)

#define ILMVHistoEqDisp_get_YUVInput(This,pVal)	\
    (This)->lpVtbl -> get_YUVInput(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoEqDisp_get_EnableEqualize_Proxy( 
    ILMVHistoEqDisp __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoEqDisp_get_EnableEqualize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ILMVHistoEqDisp_put_EnableEqualize_Proxy( 
    ILMVHistoEqDisp __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ILMVHistoEqDisp_put_EnableEqualize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoEqDisp_get_RGBMode_Proxy( 
    ILMVHistoEqDisp __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoEqDisp_get_RGBMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ILMVHistoEqDisp_put_RGBMode_Proxy( 
    ILMVHistoEqDisp __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ILMVHistoEqDisp_put_RGBMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoEqDisp_get_HistogramType_Proxy( 
    ILMVHistoEqDisp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoEqDisp_get_HistogramType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ILMVHistoEqDisp_put_HistogramType_Proxy( 
    ILMVHistoEqDisp __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ILMVHistoEqDisp_put_HistogramType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoEqDisp_get_DefaultEnableEqualize_Proxy( 
    ILMVHistoEqDisp __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoEqDisp_get_DefaultEnableEqualize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ILMVHistoEqDisp_put_DefaultEnableEqualize_Proxy( 
    ILMVHistoEqDisp __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ILMVHistoEqDisp_put_DefaultEnableEqualize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoEqDisp_get_DefaultRGBMode_Proxy( 
    ILMVHistoEqDisp __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoEqDisp_get_DefaultRGBMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ILMVHistoEqDisp_put_DefaultRGBMode_Proxy( 
    ILMVHistoEqDisp __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ILMVHistoEqDisp_put_DefaultRGBMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoEqDisp_get_DefaultHistogramType_Proxy( 
    ILMVHistoEqDisp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoEqDisp_get_DefaultHistogramType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ILMVHistoEqDisp_put_DefaultHistogramType_Proxy( 
    ILMVHistoEqDisp __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ILMVHistoEqDisp_put_DefaultHistogramType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoEqDisp_get_IsLEADInputPinConnected_Proxy( 
    ILMVHistoEqDisp __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoEqDisp_get_IsLEADInputPinConnected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoEqDisp_get_IsLEADOutputPinConnected_Proxy( 
    ILMVHistoEqDisp __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoEqDisp_get_IsLEADOutputPinConnected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoEqDisp_get_InWidth_Proxy( 
    ILMVHistoEqDisp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoEqDisp_get_InWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoEqDisp_get_InHeight_Proxy( 
    ILMVHistoEqDisp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoEqDisp_get_InHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoEqDisp_get_OutWidth_Proxy( 
    ILMVHistoEqDisp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoEqDisp_get_OutWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoEqDisp_get_OutHeight_Proxy( 
    ILMVHistoEqDisp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoEqDisp_get_OutHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoEqDisp_get_InBits_Proxy( 
    ILMVHistoEqDisp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoEqDisp_get_InBits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoEqDisp_get_OutBits_Proxy( 
    ILMVHistoEqDisp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoEqDisp_get_OutBits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoEqDisp_get_YUVHistogram_Proxy( 
    ILMVHistoEqDisp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoEqDisp_get_YUVHistogram_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ILMVHistoEqDisp_put_YUVHistogram_Proxy( 
    ILMVHistoEqDisp __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ILMVHistoEqDisp_put_YUVHistogram_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoEqDisp_get_YUVInput_Proxy( 
    ILMVHistoEqDisp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoEqDisp_get_YUVInput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILMVHistoEqDisp_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_LMVHistoEq;

#ifdef __cplusplus

class DECLSPEC_UUID("E2B7DB2E-38C5-11D5-91F6-00104BDB8FF9")
LMVHistoEq;
#endif

#ifndef __ILMVHistoViewDisp1_INTERFACE_DEFINED__
#define __ILMVHistoViewDisp1_INTERFACE_DEFINED__

/* interface ILMVHistoViewDisp1 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ILMVHistoViewDisp1;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E2B7DB83-38C5-11D5-91F6-00104BDB8FF9")
    ILMVHistoViewDisp1 : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RGBMode( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RGBMode( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HistogramType( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HistogramType( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultRGBMode( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DefaultRGBMode( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultHistogramType( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DefaultHistogramType( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsLEADInputPinConnected( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsLEADOutputPinConnected( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InWidth( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InHeight( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutWidth( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutHeight( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InBits( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutBits( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILMVHistoViewDisp1Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILMVHistoViewDisp1 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILMVHistoViewDisp1 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILMVHistoViewDisp1 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ILMVHistoViewDisp1 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ILMVHistoViewDisp1 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ILMVHistoViewDisp1 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ILMVHistoViewDisp1 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RGBMode )( 
            ILMVHistoViewDisp1 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RGBMode )( 
            ILMVHistoViewDisp1 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HistogramType )( 
            ILMVHistoViewDisp1 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HistogramType )( 
            ILMVHistoViewDisp1 __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DefaultRGBMode )( 
            ILMVHistoViewDisp1 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DefaultRGBMode )( 
            ILMVHistoViewDisp1 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DefaultHistogramType )( 
            ILMVHistoViewDisp1 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DefaultHistogramType )( 
            ILMVHistoViewDisp1 __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsLEADInputPinConnected )( 
            ILMVHistoViewDisp1 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsLEADOutputPinConnected )( 
            ILMVHistoViewDisp1 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InWidth )( 
            ILMVHistoViewDisp1 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InHeight )( 
            ILMVHistoViewDisp1 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OutWidth )( 
            ILMVHistoViewDisp1 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OutHeight )( 
            ILMVHistoViewDisp1 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InBits )( 
            ILMVHistoViewDisp1 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OutBits )( 
            ILMVHistoViewDisp1 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        END_INTERFACE
    } ILMVHistoViewDisp1Vtbl;

    interface ILMVHistoViewDisp1
    {
        CONST_VTBL struct ILMVHistoViewDisp1Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILMVHistoViewDisp1_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILMVHistoViewDisp1_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILMVHistoViewDisp1_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILMVHistoViewDisp1_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ILMVHistoViewDisp1_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ILMVHistoViewDisp1_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ILMVHistoViewDisp1_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ILMVHistoViewDisp1_get_RGBMode(This,pVal)	\
    (This)->lpVtbl -> get_RGBMode(This,pVal)

#define ILMVHistoViewDisp1_put_RGBMode(This,newVal)	\
    (This)->lpVtbl -> put_RGBMode(This,newVal)

#define ILMVHistoViewDisp1_get_HistogramType(This,pVal)	\
    (This)->lpVtbl -> get_HistogramType(This,pVal)

#define ILMVHistoViewDisp1_put_HistogramType(This,newVal)	\
    (This)->lpVtbl -> put_HistogramType(This,newVal)

#define ILMVHistoViewDisp1_get_DefaultRGBMode(This,pVal)	\
    (This)->lpVtbl -> get_DefaultRGBMode(This,pVal)

#define ILMVHistoViewDisp1_put_DefaultRGBMode(This,newVal)	\
    (This)->lpVtbl -> put_DefaultRGBMode(This,newVal)

#define ILMVHistoViewDisp1_get_DefaultHistogramType(This,pVal)	\
    (This)->lpVtbl -> get_DefaultHistogramType(This,pVal)

#define ILMVHistoViewDisp1_put_DefaultHistogramType(This,newVal)	\
    (This)->lpVtbl -> put_DefaultHistogramType(This,newVal)

#define ILMVHistoViewDisp1_get_IsLEADInputPinConnected(This,pVal)	\
    (This)->lpVtbl -> get_IsLEADInputPinConnected(This,pVal)

#define ILMVHistoViewDisp1_get_IsLEADOutputPinConnected(This,pVal)	\
    (This)->lpVtbl -> get_IsLEADOutputPinConnected(This,pVal)

#define ILMVHistoViewDisp1_get_InWidth(This,pVal)	\
    (This)->lpVtbl -> get_InWidth(This,pVal)

#define ILMVHistoViewDisp1_get_InHeight(This,pVal)	\
    (This)->lpVtbl -> get_InHeight(This,pVal)

#define ILMVHistoViewDisp1_get_OutWidth(This,pVal)	\
    (This)->lpVtbl -> get_OutWidth(This,pVal)

#define ILMVHistoViewDisp1_get_OutHeight(This,pVal)	\
    (This)->lpVtbl -> get_OutHeight(This,pVal)

#define ILMVHistoViewDisp1_get_InBits(This,pVal)	\
    (This)->lpVtbl -> get_InBits(This,pVal)

#define ILMVHistoViewDisp1_get_OutBits(This,pVal)	\
    (This)->lpVtbl -> get_OutBits(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoViewDisp1_get_RGBMode_Proxy( 
    ILMVHistoViewDisp1 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoViewDisp1_get_RGBMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ILMVHistoViewDisp1_put_RGBMode_Proxy( 
    ILMVHistoViewDisp1 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ILMVHistoViewDisp1_put_RGBMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoViewDisp1_get_HistogramType_Proxy( 
    ILMVHistoViewDisp1 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoViewDisp1_get_HistogramType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ILMVHistoViewDisp1_put_HistogramType_Proxy( 
    ILMVHistoViewDisp1 __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ILMVHistoViewDisp1_put_HistogramType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoViewDisp1_get_DefaultRGBMode_Proxy( 
    ILMVHistoViewDisp1 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoViewDisp1_get_DefaultRGBMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ILMVHistoViewDisp1_put_DefaultRGBMode_Proxy( 
    ILMVHistoViewDisp1 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ILMVHistoViewDisp1_put_DefaultRGBMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoViewDisp1_get_DefaultHistogramType_Proxy( 
    ILMVHistoViewDisp1 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoViewDisp1_get_DefaultHistogramType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ILMVHistoViewDisp1_put_DefaultHistogramType_Proxy( 
    ILMVHistoViewDisp1 __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ILMVHistoViewDisp1_put_DefaultHistogramType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoViewDisp1_get_IsLEADInputPinConnected_Proxy( 
    ILMVHistoViewDisp1 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoViewDisp1_get_IsLEADInputPinConnected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoViewDisp1_get_IsLEADOutputPinConnected_Proxy( 
    ILMVHistoViewDisp1 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoViewDisp1_get_IsLEADOutputPinConnected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoViewDisp1_get_InWidth_Proxy( 
    ILMVHistoViewDisp1 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoViewDisp1_get_InWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoViewDisp1_get_InHeight_Proxy( 
    ILMVHistoViewDisp1 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoViewDisp1_get_InHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoViewDisp1_get_OutWidth_Proxy( 
    ILMVHistoViewDisp1 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoViewDisp1_get_OutWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoViewDisp1_get_OutHeight_Proxy( 
    ILMVHistoViewDisp1 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoViewDisp1_get_OutHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoViewDisp1_get_InBits_Proxy( 
    ILMVHistoViewDisp1 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoViewDisp1_get_InBits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILMVHistoViewDisp1_get_OutBits_Proxy( 
    ILMVHistoViewDisp1 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ILMVHistoViewDisp1_get_OutBits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILMVHistoViewDisp1_INTERFACE_DEFINED__ */


#ifndef __ILMVHistoViewDisp_INTERFACE_DEFINED__
#define __ILMVHistoViewDisp_INTERFACE_DEFINED__

/* interface ILMVHistoViewDisp */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ILMVHistoViewDisp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E2B7DC52-38C5-11D5-91F6-00104BDB8FF9")
    ILMVHistoViewDisp : public ILMVHistoViewDisp1
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetHistogramArray( 
            /* [out][in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *HistogramArray,
            long __RPC_FAR *llFrameCount) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILMVHistoViewDispVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILMVHistoViewDisp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILMVHistoViewDisp __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILMVHistoViewDisp __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ILMVHistoViewDisp __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ILMVHistoViewDisp __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ILMVHistoViewDisp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ILMVHistoViewDisp __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RGBMode )( 
            ILMVHistoViewDisp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RGBMode )( 
            ILMVHistoViewDisp __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HistogramType )( 
            ILMVHistoViewDisp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HistogramType )( 
            ILMVHistoViewDisp __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DefaultRGBMode )( 
            ILMVHistoViewDisp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DefaultRGBMode )( 
            ILMVHistoViewDisp __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DefaultHistogramType )( 
            ILMVHistoViewDisp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DefaultHistogramType )( 
            ILMVHistoViewDisp __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsLEADInputPinConnected )( 
            ILMVHistoViewDisp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsLEADOutputPinConnected )( 
            ILMVHistoViewDisp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InWidth )( 
            ILMVHistoViewDisp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InHeight )( 
            ILMVHistoViewDisp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OutWidth )( 
            ILMVHistoViewDisp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OutHeight )( 
            ILMVHistoViewDisp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InBits )( 
            ILMVHistoViewDisp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OutBits )( 
            ILMVHistoViewDisp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHistogramArray )( 
            ILMVHistoViewDisp __RPC_FAR * This,
            /* [out][in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *HistogramArray,
            long __RPC_FAR *llFrameCount);
        
        END_INTERFACE
    } ILMVHistoViewDispVtbl;

    interface ILMVHistoViewDisp
    {
        CONST_VTBL struct ILMVHistoViewDispVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILMVHistoViewDisp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILMVHistoViewDisp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILMVHistoViewDisp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILMVHistoViewDisp_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ILMVHistoViewDisp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ILMVHistoViewDisp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ILMVHistoViewDisp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ILMVHistoViewDisp_get_RGBMode(This,pVal)	\
    (This)->lpVtbl -> get_RGBMode(This,pVal)

#define ILMVHistoViewDisp_put_RGBMode(This,newVal)	\
    (This)->lpVtbl -> put_RGBMode(This,newVal)

#define ILMVHistoViewDisp_get_HistogramType(This,pVal)	\
    (This)->lpVtbl -> get_HistogramType(This,pVal)

#define ILMVHistoViewDisp_put_HistogramType(This,newVal)	\
    (This)->lpVtbl -> put_HistogramType(This,newVal)

#define ILMVHistoViewDisp_get_DefaultRGBMode(This,pVal)	\
    (This)->lpVtbl -> get_DefaultRGBMode(This,pVal)

#define ILMVHistoViewDisp_put_DefaultRGBMode(This,newVal)	\
    (This)->lpVtbl -> put_DefaultRGBMode(This,newVal)

#define ILMVHistoViewDisp_get_DefaultHistogramType(This,pVal)	\
    (This)->lpVtbl -> get_DefaultHistogramType(This,pVal)

#define ILMVHistoViewDisp_put_DefaultHistogramType(This,newVal)	\
    (This)->lpVtbl -> put_DefaultHistogramType(This,newVal)

#define ILMVHistoViewDisp_get_IsLEADInputPinConnected(This,pVal)	\
    (This)->lpVtbl -> get_IsLEADInputPinConnected(This,pVal)

#define ILMVHistoViewDisp_get_IsLEADOutputPinConnected(This,pVal)	\
    (This)->lpVtbl -> get_IsLEADOutputPinConnected(This,pVal)

#define ILMVHistoViewDisp_get_InWidth(This,pVal)	\
    (This)->lpVtbl -> get_InWidth(This,pVal)

#define ILMVHistoViewDisp_get_InHeight(This,pVal)	\
    (This)->lpVtbl -> get_InHeight(This,pVal)

#define ILMVHistoViewDisp_get_OutWidth(This,pVal)	\
    (This)->lpVtbl -> get_OutWidth(This,pVal)

#define ILMVHistoViewDisp_get_OutHeight(This,pVal)	\
    (This)->lpVtbl -> get_OutHeight(This,pVal)

#define ILMVHistoViewDisp_get_InBits(This,pVal)	\
    (This)->lpVtbl -> get_InBits(This,pVal)

#define ILMVHistoViewDisp_get_OutBits(This,pVal)	\
    (This)->lpVtbl -> get_OutBits(This,pVal)


#define ILMVHistoViewDisp_GetHistogramArray(This,HistogramArray,llFrameCount)	\
    (This)->lpVtbl -> GetHistogramArray(This,HistogramArray,llFrameCount)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ILMVHistoViewDisp_GetHistogramArray_Proxy( 
    ILMVHistoViewDisp __RPC_FAR * This,
    /* [out][in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *HistogramArray,
    long __RPC_FAR *llFrameCount);


void __RPC_STUB ILMVHistoViewDisp_GetHistogramArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILMVHistoViewDisp_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_LMVHistoView;

#ifdef __cplusplus

class DECLSPEC_UUID("E2B7DB2B-38C5-11D5-91F6-00104BDB8FF9")
LMVHistoView;
#endif
#endif /* __LMVHistogLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
