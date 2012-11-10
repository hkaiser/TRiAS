
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Tue Jan 04 13:17:47 2005
 */
/* Compiler settings for MapMgr.idl:
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

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __MapMgr_h__
#define __MapMgr_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMapImport_FWD_DEFINED__
#define __IMapImport_FWD_DEFINED__
typedef interface IMapImport IMapImport;
#endif 	/* __IMapImport_FWD_DEFINED__ */


#ifndef __IPictHolder_FWD_DEFINED__
#define __IPictHolder_FWD_DEFINED__
typedef interface IPictHolder IPictHolder;
#endif 	/* __IPictHolder_FWD_DEFINED__ */


#ifndef __MapImport_FWD_DEFINED__
#define __MapImport_FWD_DEFINED__

#ifdef __cplusplus
typedef class MapImport MapImport;
#else
typedef struct MapImport MapImport;
#endif /* __cplusplus */

#endif 	/* __MapImport_FWD_DEFINED__ */


#ifndef __PictHolder_FWD_DEFINED__
#define __PictHolder_FWD_DEFINED__

#ifdef __cplusplus
typedef class PictHolder PictHolder;
#else
typedef struct PictHolder PictHolder;
#endif /* __cplusplus */

#endif 	/* __PictHolder_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IMapImport_INTERFACE_DEFINED__
#define __IMapImport_INTERFACE_DEFINED__

/* interface IMapImport */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMapImport;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2CD725F2-0382-11D2-8F5A-0060085FC1CE")
    IMapImport : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IMapImportVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMapImport * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMapImport * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMapImport * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMapImport * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMapImport * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMapImport * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMapImport * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IMapImportVtbl;

    interface IMapImport
    {
        CONST_VTBL struct IMapImportVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMapImport_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMapImport_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMapImport_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMapImport_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMapImport_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMapImport_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMapImport_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMapImport_INTERFACE_DEFINED__ */



#ifndef __MAPMGRLib_LIBRARY_DEFINED__
#define __MAPMGRLib_LIBRARY_DEFINED__

/* library MAPMGRLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_MAPMGRLib;

#ifndef __IPictHolder_INTERFACE_DEFINED__
#define __IPictHolder_INTERFACE_DEFINED__

/* interface IPictHolder */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPictHolder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B6A2F4A8-1AF7-11D2-8F7D-0060085FC1CE")
    IPictHolder : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OpenPictureFile( 
            /* [in] */ BSTR strPicture) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPictHolderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPictHolder * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPictHolder * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPictHolder * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPictHolder * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPictHolder * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPictHolder * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPictHolder * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *OpenPictureFile )( 
            IPictHolder * This,
            /* [in] */ BSTR strPicture);
        
        HRESULT ( STDMETHODCALLTYPE *Close )( 
            IPictHolder * This);
        
        END_INTERFACE
    } IPictHolderVtbl;

    interface IPictHolder
    {
        CONST_VTBL struct IPictHolderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPictHolder_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPictHolder_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPictHolder_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPictHolder_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPictHolder_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPictHolder_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPictHolder_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPictHolder_OpenPictureFile(This,strPicture)	\
    (This)->lpVtbl -> OpenPictureFile(This,strPicture)

#define IPictHolder_Close(This)	\
    (This)->lpVtbl -> Close(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPictHolder_OpenPictureFile_Proxy( 
    IPictHolder * This,
    /* [in] */ BSTR strPicture);


void __RPC_STUB IPictHolder_OpenPictureFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPictHolder_Close_Proxy( 
    IPictHolder * This);


void __RPC_STUB IPictHolder_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPictHolder_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MapImport;

#ifdef __cplusplus

class DECLSPEC_UUID("2CD725F3-0382-11D2-8F5A-0060085FC1CE")
MapImport;
#endif

EXTERN_C const CLSID CLSID_PictHolder;

#ifdef __cplusplus

class DECLSPEC_UUID("B6A2F4A9-1AF7-11D2-8F7D-0060085FC1CE")
PictHolder;
#endif
#endif /* __MAPMGRLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


