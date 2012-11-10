

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Tue Dec 17 20:14:55 2002
 */
/* Compiler settings for Collection.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
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

#ifndef __Collection_h__
#define __Collection_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IStaticCollection_FWD_DEFINED__
#define __IStaticCollection_FWD_DEFINED__
typedef interface IStaticCollection IStaticCollection;
#endif 	/* __IStaticCollection_FWD_DEFINED__ */


#ifndef __IDynamicCollection_FWD_DEFINED__
#define __IDynamicCollection_FWD_DEFINED__
typedef interface IDynamicCollection IDynamicCollection;
#endif 	/* __IDynamicCollection_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_Collection_0000 */
/* [local] */ 





extern RPC_IF_HANDLE __MIDL_itf_Collection_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_Collection_0000_v0_0_s_ifspec;

#ifndef __IStaticCollection_INTERFACE_DEFINED__
#define __IStaticCollection_INTERFACE_DEFINED__

/* interface IStaticCollection */
/* [object][oleautomation][nonextensible][dual][uuid] */ 


EXTERN_C const IID IID_IStaticCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AE5F4110-9CBF-11d2-9F09-006008447800")
    IStaticCollection : public IDispatch
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ ULONG *c) = 0;
        
        virtual /* [restricted][id] */ HRESULT __stdcall _NewEnum( 
            /* [retval][out] */ IUnknown **ppunk) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ VARIANT *retval) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IStaticCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStaticCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStaticCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStaticCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IStaticCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IStaticCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IStaticCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IStaticCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IStaticCollection * This,
            /* [retval][out] */ ULONG *c);
        
        /* [restricted][id] */ HRESULT ( __stdcall *_NewEnum )( 
            IStaticCollection * This,
            /* [retval][out] */ IUnknown **ppunk);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IStaticCollection * This);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IStaticCollection * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ VARIANT *retval);
        
        END_INTERFACE
    } IStaticCollectionVtbl;

    interface IStaticCollection
    {
        CONST_VTBL struct IStaticCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStaticCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStaticCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IStaticCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IStaticCollection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IStaticCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IStaticCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IStaticCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IStaticCollection_get_Count(This,c)	\
    (This)->lpVtbl -> get_Count(This,c)

#define IStaticCollection__NewEnum(This,ppunk)	\
    (This)->lpVtbl -> _NewEnum(This,ppunk)

#define IStaticCollection_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IStaticCollection_get_Item(This,Index,retval)	\
    (This)->lpVtbl -> get_Item(This,Index,retval)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IStaticCollection_get_Count_Proxy( 
    IStaticCollection * This,
    /* [retval][out] */ ULONG *c);


void __RPC_STUB IStaticCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id] */ HRESULT __stdcall IStaticCollection__NewEnum_Proxy( 
    IStaticCollection * This,
    /* [retval][out] */ IUnknown **ppunk);


void __RPC_STUB IStaticCollection__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IStaticCollection_Refresh_Proxy( 
    IStaticCollection * This);


void __RPC_STUB IStaticCollection_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IStaticCollection_get_Item_Proxy( 
    IStaticCollection * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ VARIANT *retval);


void __RPC_STUB IStaticCollection_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IStaticCollection_INTERFACE_DEFINED__ */


#ifndef __IDynamicCollection_INTERFACE_DEFINED__
#define __IDynamicCollection_INTERFACE_DEFINED__

/* interface IDynamicCollection */
/* [object][oleautomation][nonextensible][dual][uuid] */ 


EXTERN_C const IID IID_IDynamicCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AE5F4111-9CBF-11d2-9F09-006008447800")
    IDynamicCollection : public IStaticCollection
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Append( 
            /* [in] */ IDispatch *Object) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteByIndex( 
            /* [in] */ VARIANT Index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteByObject( 
            /* [in] */ IDispatch *Object) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDynamicCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDynamicCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDynamicCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDynamicCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDynamicCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDynamicCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDynamicCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDynamicCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IDynamicCollection * This,
            /* [retval][out] */ ULONG *c);
        
        /* [restricted][id] */ HRESULT ( __stdcall *_NewEnum )( 
            IDynamicCollection * This,
            /* [retval][out] */ IUnknown **ppunk);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IDynamicCollection * This);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IDynamicCollection * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ VARIANT *retval);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Append )( 
            IDynamicCollection * This,
            /* [in] */ IDispatch *Object);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteByIndex )( 
            IDynamicCollection * This,
            /* [in] */ VARIANT Index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteByObject )( 
            IDynamicCollection * This,
            /* [in] */ IDispatch *Object);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IDynamicCollection * This);
        
        END_INTERFACE
    } IDynamicCollectionVtbl;

    interface IDynamicCollection
    {
        CONST_VTBL struct IDynamicCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDynamicCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDynamicCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDynamicCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDynamicCollection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDynamicCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDynamicCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDynamicCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDynamicCollection_get_Count(This,c)	\
    (This)->lpVtbl -> get_Count(This,c)

#define IDynamicCollection__NewEnum(This,ppunk)	\
    (This)->lpVtbl -> _NewEnum(This,ppunk)

#define IDynamicCollection_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IDynamicCollection_get_Item(This,Index,retval)	\
    (This)->lpVtbl -> get_Item(This,Index,retval)


#define IDynamicCollection_Append(This,Object)	\
    (This)->lpVtbl -> Append(This,Object)

#define IDynamicCollection_DeleteByIndex(This,Index)	\
    (This)->lpVtbl -> DeleteByIndex(This,Index)

#define IDynamicCollection_DeleteByObject(This,Object)	\
    (This)->lpVtbl -> DeleteByObject(This,Object)

#define IDynamicCollection_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDynamicCollection_Append_Proxy( 
    IDynamicCollection * This,
    /* [in] */ IDispatch *Object);


void __RPC_STUB IDynamicCollection_Append_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDynamicCollection_DeleteByIndex_Proxy( 
    IDynamicCollection * This,
    /* [in] */ VARIANT Index);


void __RPC_STUB IDynamicCollection_DeleteByIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDynamicCollection_DeleteByObject_Proxy( 
    IDynamicCollection * This,
    /* [in] */ IDispatch *Object);


void __RPC_STUB IDynamicCollection_DeleteByObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDynamicCollection_Clear_Proxy( 
    IDynamicCollection * This);


void __RPC_STUB IDynamicCollection_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDynamicCollection_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


