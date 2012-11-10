/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.00.44 */
/* at Mon Jun 16 11:03:28 1997
 */
/* Compiler settings for DynQuery.idl:
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

#ifndef __DynQuery_h__
#define __DynQuery_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEnumObjectsByNumber_FWD_DEFINED__
#define __IEnumObjectsByNumber_FWD_DEFINED__
typedef interface IEnumObjectsByNumber IEnumObjectsByNumber;
#endif 	/* __IEnumObjectsByNumber_FWD_DEFINED__ */


#ifndef __DTRiASBaseClass_FWD_DEFINED__
#define __DTRiASBaseClass_FWD_DEFINED__
typedef interface DTRiASBaseClass DTRiASBaseClass;
#endif 	/* __DTRiASBaseClass_FWD_DEFINED__ */


#ifndef __DTRiASCollection_FWD_DEFINED__
#define __DTRiASCollection_FWD_DEFINED__
typedef interface DTRiASCollection DTRiASCollection;
#endif 	/* __DTRiASCollection_FWD_DEFINED__ */


#ifndef __DTRiASProperty_FWD_DEFINED__
#define __DTRiASProperty_FWD_DEFINED__
typedef interface DTRiASProperty DTRiASProperty;
#endif 	/* __DTRiASProperty_FWD_DEFINED__ */


#ifndef __DTRiASProperties_FWD_DEFINED__
#define __DTRiASProperties_FWD_DEFINED__
typedef interface DTRiASProperties DTRiASProperties;
#endif 	/* __DTRiASProperties_FWD_DEFINED__ */


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


#ifndef __IDynQueryObjEnums_FWD_DEFINED__
#define __IDynQueryObjEnums_FWD_DEFINED__
typedef interface IDynQueryObjEnums IDynQueryObjEnums;
#endif 	/* __IDynQueryObjEnums_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL__intf_0000
 * at Mon Jun 16 11:03:28 1997
 * using MIDL 3.00.44
 ****************************************/
/* [local] */ 



#ifndef _ENUMOBJECTSBYNUMBER_DEFINED
#define _ENUMOBJECTSBYNUMBER_DEFINED


extern RPC_IF_HANDLE __MIDL__intf_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL__intf_0000_v0_0_s_ifspec;

#ifndef __IEnumObjectsByNumber_INTERFACE_DEFINED__
#define __IEnumObjectsByNumber_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IEnumObjectsByNumber
 * at Mon Jun 16 11:03:28 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][uuid][object] */ 



EXTERN_C const IID IID_IEnumObjectsByNumber;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IEnumObjectsByNumber : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ LONG __RPC_FAR *rgelt,
            /* [out] */ ULONG __RPC_FAR *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumObjectsByNumber __RPC_FAR *__RPC_FAR *ppenum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCount( 
            /* [out] */ ULONG __RPC_FAR *pclCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddItem( 
            /* [in] */ LONG item) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumObjectsByNumberVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEnumObjectsByNumber __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEnumObjectsByNumber __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEnumObjectsByNumber __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IEnumObjectsByNumber __RPC_FAR * This,
            /* [in] */ ULONG celt,
            /* [out] */ LONG __RPC_FAR *rgelt,
            /* [out] */ ULONG __RPC_FAR *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IEnumObjectsByNumber __RPC_FAR * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEnumObjectsByNumber __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IEnumObjectsByNumber __RPC_FAR * This,
            /* [out] */ IEnumObjectsByNumber __RPC_FAR *__RPC_FAR *ppenum);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCount )( 
            IEnumObjectsByNumber __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *pclCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddItem )( 
            IEnumObjectsByNumber __RPC_FAR * This,
            /* [in] */ LONG item);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            IEnumObjectsByNumber __RPC_FAR * This);
        
        END_INTERFACE
    } IEnumObjectsByNumberVtbl;

    interface IEnumObjectsByNumber
    {
        CONST_VTBL struct IEnumObjectsByNumberVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumObjectsByNumber_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumObjectsByNumber_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumObjectsByNumber_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumObjectsByNumber_Next(This,celt,rgelt,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched)

#define IEnumObjectsByNumber_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IEnumObjectsByNumber_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumObjectsByNumber_Clone(This,ppenum)	\
    (This)->lpVtbl -> Clone(This,ppenum)

#define IEnumObjectsByNumber_GetCount(This,pclCount)	\
    (This)->lpVtbl -> GetCount(This,pclCount)

#define IEnumObjectsByNumber_AddItem(This,item)	\
    (This)->lpVtbl -> AddItem(This,item)

#define IEnumObjectsByNumber_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumObjectsByNumber_Next_Proxy( 
    IEnumObjectsByNumber __RPC_FAR * This,
    /* [in] */ ULONG celt,
    /* [out] */ LONG __RPC_FAR *rgelt,
    /* [out] */ ULONG __RPC_FAR *pceltFetched);


void __RPC_STUB IEnumObjectsByNumber_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumObjectsByNumber_Skip_Proxy( 
    IEnumObjectsByNumber __RPC_FAR * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumObjectsByNumber_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumObjectsByNumber_Reset_Proxy( 
    IEnumObjectsByNumber __RPC_FAR * This);


void __RPC_STUB IEnumObjectsByNumber_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumObjectsByNumber_Clone_Proxy( 
    IEnumObjectsByNumber __RPC_FAR * This,
    /* [out] */ IEnumObjectsByNumber __RPC_FAR *__RPC_FAR *ppenum);


void __RPC_STUB IEnumObjectsByNumber_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumObjectsByNumber_GetCount_Proxy( 
    IEnumObjectsByNumber __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *pclCount);


void __RPC_STUB IEnumObjectsByNumber_GetCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumObjectsByNumber_AddItem_Proxy( 
    IEnumObjectsByNumber __RPC_FAR * This,
    /* [in] */ LONG item);


void __RPC_STUB IEnumObjectsByNumber_AddItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumObjectsByNumber_Clear_Proxy( 
    IEnumObjectsByNumber __RPC_FAR * This);


void __RPC_STUB IEnumObjectsByNumber_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumObjectsByNumber_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL__intf_0137
 * at Mon Jun 16 11:03:28 1997
 * using MIDL 3.00.44
 ****************************************/
/* [local] */ 


#endif // _ENUMOBJECTSBYNUMBER_DEFINED






extern RPC_IF_HANDLE __MIDL__intf_0137_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL__intf_0137_v0_0_s_ifspec;

#ifndef __DTRiASBaseClass_INTERFACE_DEFINED__
#define __DTRiASBaseClass_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: DTRiASBaseClass
 * at Mon Jun 16 11:03:28 1997
 * using MIDL 3.00.44
 ****************************************/
/* [helpstring][uuid][nonextensible][dual][oleautomation][object] */ 



EXTERN_C const IID IID_DTRiASBaseClass;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DTRiASBaseClass : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_isA( 
            /* [retval][out] */ LONG __RPC_FAR *RTTI) = 0;
        
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Base) = 0;
        
        virtual /* [hidden][propput][id] */ HRESULT STDMETHODCALLTYPE put_Parent( 
            /* [in] */ IDispatch __RPC_FAR *Base) = 0;
        
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *App) = 0;
        
        virtual /* [hidden][propput][id] */ HRESULT STDMETHODCALLTYPE put_Application( 
            /* [in] */ IDispatch __RPC_FAR *App) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct DTRiASBaseClassVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            DTRiASBaseClass __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            DTRiASBaseClass __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            DTRiASBaseClass __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            DTRiASBaseClass __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            DTRiASBaseClass __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            DTRiASBaseClass __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            DTRiASBaseClass __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_isA )( 
            DTRiASBaseClass __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *RTTI);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            DTRiASBaseClass __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Base);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Parent )( 
            DTRiASBaseClass __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *Base);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            DTRiASBaseClass __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *App);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Application )( 
            DTRiASBaseClass __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *App);
        
        END_INTERFACE
    } DTRiASBaseClassVtbl;

    interface DTRiASBaseClass
    {
        CONST_VTBL struct DTRiASBaseClassVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define DTRiASBaseClass_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define DTRiASBaseClass_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define DTRiASBaseClass_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define DTRiASBaseClass_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define DTRiASBaseClass_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define DTRiASBaseClass_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define DTRiASBaseClass_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define DTRiASBaseClass_get_isA(This,RTTI)	\
    (This)->lpVtbl -> get_isA(This,RTTI)

#define DTRiASBaseClass_get_Parent(This,Base)	\
    (This)->lpVtbl -> get_Parent(This,Base)

#define DTRiASBaseClass_put_Parent(This,Base)	\
    (This)->lpVtbl -> put_Parent(This,Base)

#define DTRiASBaseClass_get_Application(This,App)	\
    (This)->lpVtbl -> get_Application(This,App)

#define DTRiASBaseClass_put_Application(This,App)	\
    (This)->lpVtbl -> put_Application(This,App)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE DTRiASBaseClass_get_isA_Proxy( 
    DTRiASBaseClass __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *RTTI);


void __RPC_STUB DTRiASBaseClass_get_isA_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE DTRiASBaseClass_get_Parent_Proxy( 
    DTRiASBaseClass __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Base);


void __RPC_STUB DTRiASBaseClass_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propput][id] */ HRESULT STDMETHODCALLTYPE DTRiASBaseClass_put_Parent_Proxy( 
    DTRiASBaseClass __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *Base);


void __RPC_STUB DTRiASBaseClass_put_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE DTRiASBaseClass_get_Application_Proxy( 
    DTRiASBaseClass __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *App);


void __RPC_STUB DTRiASBaseClass_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propput][id] */ HRESULT STDMETHODCALLTYPE DTRiASBaseClass_put_Application_Proxy( 
    DTRiASBaseClass __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *App);


void __RPC_STUB DTRiASBaseClass_put_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __DTRiASBaseClass_INTERFACE_DEFINED__ */


#ifndef __DTRiASCollection_INTERFACE_DEFINED__
#define __DTRiASCollection_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: DTRiASCollection
 * at Mon Jun 16 11:03:28 1997
 * using MIDL 3.00.44
 ****************************************/
/* [helpstring][uuid][nonextensible][dual][oleautomation][object] */ 



EXTERN_C const IID IID_DTRiASCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DTRiASCollection : public DTRiASBaseClass
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *Count) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [optional][in] */ VARIANT Which,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item) = 0;
        
        virtual /* [restricted][id] */ HRESULT STDMETHODCALLTYPE _NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *NewEnum) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ VARIANT ToAdd,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *NewItem) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT ToRemove) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct DTRiASCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            DTRiASCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            DTRiASCollection __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            DTRiASCollection __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            DTRiASCollection __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            DTRiASCollection __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            DTRiASCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            DTRiASCollection __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_isA )( 
            DTRiASCollection __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *RTTI);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            DTRiASCollection __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Base);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Parent )( 
            DTRiASCollection __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *Base);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            DTRiASCollection __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *App);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Application )( 
            DTRiASCollection __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *App);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            DTRiASCollection __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Count);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            DTRiASCollection __RPC_FAR * This,
            /* [optional][in] */ VARIANT Which,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);
        
        /* [restricted][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_NewEnum )( 
            DTRiASCollection __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *NewEnum);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            DTRiASCollection __RPC_FAR * This,
            /* [in] */ VARIANT ToAdd,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *NewItem);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            DTRiASCollection __RPC_FAR * This,
            /* [in] */ VARIANT ToRemove);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            DTRiASCollection __RPC_FAR * This);
        
        END_INTERFACE
    } DTRiASCollectionVtbl;

    interface DTRiASCollection
    {
        CONST_VTBL struct DTRiASCollectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define DTRiASCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define DTRiASCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define DTRiASCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define DTRiASCollection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define DTRiASCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define DTRiASCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define DTRiASCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define DTRiASCollection_get_isA(This,RTTI)	\
    (This)->lpVtbl -> get_isA(This,RTTI)

#define DTRiASCollection_get_Parent(This,Base)	\
    (This)->lpVtbl -> get_Parent(This,Base)

#define DTRiASCollection_put_Parent(This,Base)	\
    (This)->lpVtbl -> put_Parent(This,Base)

#define DTRiASCollection_get_Application(This,App)	\
    (This)->lpVtbl -> get_Application(This,App)

#define DTRiASCollection_put_Application(This,App)	\
    (This)->lpVtbl -> put_Application(This,App)


#define DTRiASCollection_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define DTRiASCollection_Item(This,Which,Item)	\
    (This)->lpVtbl -> Item(This,Which,Item)

#define DTRiASCollection__NewEnum(This,NewEnum)	\
    (This)->lpVtbl -> _NewEnum(This,NewEnum)

#define DTRiASCollection_Add(This,ToAdd,NewItem)	\
    (This)->lpVtbl -> Add(This,ToAdd,NewItem)

#define DTRiASCollection_Remove(This,ToRemove)	\
    (This)->lpVtbl -> Remove(This,ToRemove)

#define DTRiASCollection_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE DTRiASCollection_get_Count_Proxy( 
    DTRiASCollection __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Count);


void __RPC_STUB DTRiASCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE DTRiASCollection_Item_Proxy( 
    DTRiASCollection __RPC_FAR * This,
    /* [optional][in] */ VARIANT Which,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB DTRiASCollection_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id] */ HRESULT STDMETHODCALLTYPE DTRiASCollection__NewEnum_Proxy( 
    DTRiASCollection __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *NewEnum);


void __RPC_STUB DTRiASCollection__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE DTRiASCollection_Add_Proxy( 
    DTRiASCollection __RPC_FAR * This,
    /* [in] */ VARIANT ToAdd,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *NewItem);


void __RPC_STUB DTRiASCollection_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE DTRiASCollection_Remove_Proxy( 
    DTRiASCollection __RPC_FAR * This,
    /* [in] */ VARIANT ToRemove);


void __RPC_STUB DTRiASCollection_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE DTRiASCollection_Refresh_Proxy( 
    DTRiASCollection __RPC_FAR * This);


void __RPC_STUB DTRiASCollection_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __DTRiASCollection_INTERFACE_DEFINED__ */


#ifndef __DTRiASProperty_INTERFACE_DEFINED__
#define __DTRiASProperty_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: DTRiASProperty
 * at Mon Jun 16 11:03:28 1997
 * using MIDL 3.00.44
 ****************************************/
/* [oleautomation][helpstring][uuid][dual][object] */ 


typedef /* [helpstring][public] */ 
enum _tagPROPERTYTYPE
    {	PROPERTYTYPE_INTEGER	= VT_I4,
	PROPERTYTYPE_DOUBLE	= VT_R8,
	PROPERTYTYPE_BSTR	= VT_BSTR,
	PROPERTYTYPE_DISPATCH	= VT_DISPATCH,
	PROPERTYTYPE_VARIANT	= VT_VARIANT,
	PROPERTYTYPE_UNKNOWN	= VT_UNKNOWN
    }	PROPERTYTYPE;


EXTERN_C const IID IID_DTRiASProperty;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DTRiASProperty : public DTRiASBaseClass
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ VARIANT __RPC_FAR *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ VARIANT Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *Name) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Inherited( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *IsInherited) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ PROPERTYTYPE __RPC_FAR *PropType) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ PROPERTYTYPE PropType) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct DTRiASPropertyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            DTRiASProperty __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            DTRiASProperty __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            DTRiASProperty __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            DTRiASProperty __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            DTRiASProperty __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            DTRiASProperty __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            DTRiASProperty __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_isA )( 
            DTRiASProperty __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *RTTI);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            DTRiASProperty __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Base);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Parent )( 
            DTRiASProperty __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *Base);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            DTRiASProperty __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *App);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Application )( 
            DTRiASProperty __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *App);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Value )( 
            DTRiASProperty __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Value )( 
            DTRiASProperty __RPC_FAR * This,
            /* [in] */ VARIANT Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            DTRiASProperty __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Name);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            DTRiASProperty __RPC_FAR * This,
            /* [in] */ BSTR Name);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Inherited )( 
            DTRiASProperty __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *IsInherited);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            DTRiASProperty __RPC_FAR * This,
            /* [retval][out] */ PROPERTYTYPE __RPC_FAR *PropType);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Type )( 
            DTRiASProperty __RPC_FAR * This,
            /* [in] */ PROPERTYTYPE PropType);
        
        END_INTERFACE
    } DTRiASPropertyVtbl;

    interface DTRiASProperty
    {
        CONST_VTBL struct DTRiASPropertyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define DTRiASProperty_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define DTRiASProperty_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define DTRiASProperty_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define DTRiASProperty_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define DTRiASProperty_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define DTRiASProperty_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define DTRiASProperty_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define DTRiASProperty_get_isA(This,RTTI)	\
    (This)->lpVtbl -> get_isA(This,RTTI)

#define DTRiASProperty_get_Parent(This,Base)	\
    (This)->lpVtbl -> get_Parent(This,Base)

#define DTRiASProperty_put_Parent(This,Base)	\
    (This)->lpVtbl -> put_Parent(This,Base)

#define DTRiASProperty_get_Application(This,App)	\
    (This)->lpVtbl -> get_Application(This,App)

#define DTRiASProperty_put_Application(This,App)	\
    (This)->lpVtbl -> put_Application(This,App)


#define DTRiASProperty_get_Value(This,Value)	\
    (This)->lpVtbl -> get_Value(This,Value)

#define DTRiASProperty_put_Value(This,Value)	\
    (This)->lpVtbl -> put_Value(This,Value)

#define DTRiASProperty_get_Name(This,Name)	\
    (This)->lpVtbl -> get_Name(This,Name)

#define DTRiASProperty_put_Name(This,Name)	\
    (This)->lpVtbl -> put_Name(This,Name)

#define DTRiASProperty_get_Inherited(This,IsInherited)	\
    (This)->lpVtbl -> get_Inherited(This,IsInherited)

#define DTRiASProperty_get_Type(This,PropType)	\
    (This)->lpVtbl -> get_Type(This,PropType)

#define DTRiASProperty_put_Type(This,PropType)	\
    (This)->lpVtbl -> put_Type(This,PropType)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE DTRiASProperty_get_Value_Proxy( 
    DTRiASProperty __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *Value);


void __RPC_STUB DTRiASProperty_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE DTRiASProperty_put_Value_Proxy( 
    DTRiASProperty __RPC_FAR * This,
    /* [in] */ VARIANT Value);


void __RPC_STUB DTRiASProperty_put_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE DTRiASProperty_get_Name_Proxy( 
    DTRiASProperty __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Name);


void __RPC_STUB DTRiASProperty_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE DTRiASProperty_put_Name_Proxy( 
    DTRiASProperty __RPC_FAR * This,
    /* [in] */ BSTR Name);


void __RPC_STUB DTRiASProperty_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE DTRiASProperty_get_Inherited_Proxy( 
    DTRiASProperty __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *IsInherited);


void __RPC_STUB DTRiASProperty_get_Inherited_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE DTRiASProperty_get_Type_Proxy( 
    DTRiASProperty __RPC_FAR * This,
    /* [retval][out] */ PROPERTYTYPE __RPC_FAR *PropType);


void __RPC_STUB DTRiASProperty_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE DTRiASProperty_put_Type_Proxy( 
    DTRiASProperty __RPC_FAR * This,
    /* [in] */ PROPERTYTYPE PropType);


void __RPC_STUB DTRiASProperty_put_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __DTRiASProperty_INTERFACE_DEFINED__ */


#ifndef __DTRiASProperties_INTERFACE_DEFINED__
#define __DTRiASProperties_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: DTRiASProperties
 * at Mon Jun 16 11:03:28 1997
 * using MIDL 3.00.44
 ****************************************/
/* [oleautomation][helpstring][uuid][dual][object] */ 



EXTERN_C const IID IID_DTRiASProperties;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DTRiASProperties : public DTRiASCollection
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct DTRiASPropertiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            DTRiASProperties __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            DTRiASProperties __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            DTRiASProperties __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            DTRiASProperties __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            DTRiASProperties __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            DTRiASProperties __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            DTRiASProperties __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_isA )( 
            DTRiASProperties __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *RTTI);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            DTRiASProperties __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Base);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Parent )( 
            DTRiASProperties __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *Base);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            DTRiASProperties __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *App);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Application )( 
            DTRiASProperties __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *App);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            DTRiASProperties __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Count);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            DTRiASProperties __RPC_FAR * This,
            /* [optional][in] */ VARIANT Which,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);
        
        /* [restricted][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_NewEnum )( 
            DTRiASProperties __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *NewEnum);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            DTRiASProperties __RPC_FAR * This,
            /* [in] */ VARIANT ToAdd,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *NewItem);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            DTRiASProperties __RPC_FAR * This,
            /* [in] */ VARIANT ToRemove);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            DTRiASProperties __RPC_FAR * This);
        
        END_INTERFACE
    } DTRiASPropertiesVtbl;

    interface DTRiASProperties
    {
        CONST_VTBL struct DTRiASPropertiesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define DTRiASProperties_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define DTRiASProperties_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define DTRiASProperties_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define DTRiASProperties_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define DTRiASProperties_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define DTRiASProperties_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define DTRiASProperties_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define DTRiASProperties_get_isA(This,RTTI)	\
    (This)->lpVtbl -> get_isA(This,RTTI)

#define DTRiASProperties_get_Parent(This,Base)	\
    (This)->lpVtbl -> get_Parent(This,Base)

#define DTRiASProperties_put_Parent(This,Base)	\
    (This)->lpVtbl -> put_Parent(This,Base)

#define DTRiASProperties_get_Application(This,App)	\
    (This)->lpVtbl -> get_Application(This,App)

#define DTRiASProperties_put_Application(This,App)	\
    (This)->lpVtbl -> put_Application(This,App)


#define DTRiASProperties_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define DTRiASProperties_Item(This,Which,Item)	\
    (This)->lpVtbl -> Item(This,Which,Item)

#define DTRiASProperties__NewEnum(This,NewEnum)	\
    (This)->lpVtbl -> _NewEnum(This,NewEnum)

#define DTRiASProperties_Add(This,ToAdd,NewItem)	\
    (This)->lpVtbl -> Add(This,ToAdd,NewItem)

#define DTRiASProperties_Remove(This,ToRemove)	\
    (This)->lpVtbl -> Remove(This,ToRemove)

#define DTRiASProperties_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __DTRiASProperties_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL__intf_0141
 * at Mon Jun 16 11:03:28 1997
 * using MIDL 3.00.44
 ****************************************/
/* [local] */ 









extern RPC_IF_HANDLE __MIDL__intf_0141_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL__intf_0141_v0_0_s_ifspec;

#ifndef __DVisInfo_INTERFACE_DEFINED__
#define __DVisInfo_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: DVisInfo
 * at Mon Jun 16 11:03:28 1997
 * using MIDL 3.00.44
 ****************************************/
/* [helpstring][uuid][dual][oleautomation][object] */ 


typedef /* [public] */ long TRIASCOLOR;


EXTERN_C const IID IID_DVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DVisInfo : public DTRiASBaseClass
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



#endif 	/* __DVisInfo_INTERFACE_DEFINED__ */


#ifndef __DPointVisInfo_INTERFACE_DEFINED__
#define __DPointVisInfo_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: DPointVisInfo
 * at Mon Jun 16 11:03:28 1997
 * using MIDL 3.00.44
 ****************************************/
/* [helpstring][uuid][object][dual][oleautomation] */ 



EXTERN_C const IID IID_DPointVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DPointVisInfo : public DVisInfo
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

/****************************************
 * Generated header for interface: DLineVisInfo
 * at Mon Jun 16 11:03:28 1997
 * using MIDL 3.00.44
 ****************************************/
/* [helpstring][uuid][dual][oleautomation][object] */ 



EXTERN_C const IID IID_DLineVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DLineVisInfo : public DVisInfo
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

/****************************************
 * Generated header for interface: DAreaVisInfo
 * at Mon Jun 16 11:03:28 1997
 * using MIDL 3.00.44
 ****************************************/
/* [helpstring][uuid][object][dual][oleautomation] */ 



EXTERN_C const IID IID_DAreaVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DAreaVisInfo : public DVisInfo
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

/****************************************
 * Generated header for interface: DTextVisInfo
 * at Mon Jun 16 11:03:28 1997
 * using MIDL 3.00.44
 ****************************************/
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
    
    interface DTextVisInfo : public DVisInfo
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


#ifndef __IDynQueryObjEnums_INTERFACE_DEFINED__
#define __IDynQueryObjEnums_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDynQueryObjEnums
 * at Mon Jun 16 11:03:28 1997
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][uuid][object] */ 



EXTERN_C const IID IID_IDynQueryObjEnums;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IDynQueryObjEnums : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ BSTR pcName,
            /* [in] */ IEnumObjectsByNumber __RPC_FAR *pIObjs,
            /* [in] */ DVisInfo __RPC_FAR *pIVis) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Erase( 
            /* [in] */ BSTR bstrName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ long lONr,
            /* [out][in] */ BSTR __RPC_FAR *pbstrName,
            /* [out][in] */ DVisInfo __RPC_FAR *__RPC_FAR *ppIVis) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ClassFromIdent( 
            /* [in] */ long lIdent,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrOKS) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IdentFromClass( 
            /* [in] */ BSTR bstrOKS,
            /* [retval][out] */ long __RPC_FAR *plIdent) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnumIdents( 
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppIIdents) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ViewName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ViewName( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDynQueryObjEnumsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDynQueryObjEnums __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDynQueryObjEnums __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDynQueryObjEnums __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Insert )( 
            IDynQueryObjEnums __RPC_FAR * This,
            /* [in] */ BSTR pcName,
            /* [in] */ IEnumObjectsByNumber __RPC_FAR *pIObjs,
            /* [in] */ DVisInfo __RPC_FAR *pIVis);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Erase )( 
            IDynQueryObjEnums __RPC_FAR * This,
            /* [in] */ BSTR bstrName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Find )( 
            IDynQueryObjEnums __RPC_FAR * This,
            /* [in] */ long lONr,
            /* [out][in] */ BSTR __RPC_FAR *pbstrName,
            /* [out][in] */ DVisInfo __RPC_FAR *__RPC_FAR *ppIVis);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClassFromIdent )( 
            IDynQueryObjEnums __RPC_FAR * This,
            /* [in] */ long lIdent,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrOKS);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IdentFromClass )( 
            IDynQueryObjEnums __RPC_FAR * This,
            /* [in] */ BSTR bstrOKS,
            /* [retval][out] */ long __RPC_FAR *plIdent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumIdents )( 
            IDynQueryObjEnums __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppIIdents);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ViewName )( 
            IDynQueryObjEnums __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ViewName )( 
            IDynQueryObjEnums __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IDynQueryObjEnumsVtbl;

    interface IDynQueryObjEnums
    {
        CONST_VTBL struct IDynQueryObjEnumsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDynQueryObjEnums_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDynQueryObjEnums_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDynQueryObjEnums_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDynQueryObjEnums_Insert(This,pcName,pIObjs,pIVis)	\
    (This)->lpVtbl -> Insert(This,pcName,pIObjs,pIVis)

#define IDynQueryObjEnums_Erase(This,bstrName)	\
    (This)->lpVtbl -> Erase(This,bstrName)

#define IDynQueryObjEnums_Find(This,lONr,pbstrName,ppIVis)	\
    (This)->lpVtbl -> Find(This,lONr,pbstrName,ppIVis)

#define IDynQueryObjEnums_ClassFromIdent(This,lIdent,pbstrOKS)	\
    (This)->lpVtbl -> ClassFromIdent(This,lIdent,pbstrOKS)

#define IDynQueryObjEnums_IdentFromClass(This,bstrOKS,plIdent)	\
    (This)->lpVtbl -> IdentFromClass(This,bstrOKS,plIdent)

#define IDynQueryObjEnums_EnumIdents(This,ppIIdents)	\
    (This)->lpVtbl -> EnumIdents(This,ppIIdents)

#define IDynQueryObjEnums_get_ViewName(This,pVal)	\
    (This)->lpVtbl -> get_ViewName(This,pVal)

#define IDynQueryObjEnums_put_ViewName(This,newVal)	\
    (This)->lpVtbl -> put_ViewName(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDynQueryObjEnums_Insert_Proxy( 
    IDynQueryObjEnums __RPC_FAR * This,
    /* [in] */ BSTR pcName,
    /* [in] */ IEnumObjectsByNumber __RPC_FAR *pIObjs,
    /* [in] */ DVisInfo __RPC_FAR *pIVis);


void __RPC_STUB IDynQueryObjEnums_Insert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDynQueryObjEnums_Erase_Proxy( 
    IDynQueryObjEnums __RPC_FAR * This,
    /* [in] */ BSTR bstrName);


void __RPC_STUB IDynQueryObjEnums_Erase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDynQueryObjEnums_Find_Proxy( 
    IDynQueryObjEnums __RPC_FAR * This,
    /* [in] */ long lONr,
    /* [out][in] */ BSTR __RPC_FAR *pbstrName,
    /* [out][in] */ DVisInfo __RPC_FAR *__RPC_FAR *ppIVis);


void __RPC_STUB IDynQueryObjEnums_Find_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDynQueryObjEnums_ClassFromIdent_Proxy( 
    IDynQueryObjEnums __RPC_FAR * This,
    /* [in] */ long lIdent,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrOKS);


void __RPC_STUB IDynQueryObjEnums_ClassFromIdent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDynQueryObjEnums_IdentFromClass_Proxy( 
    IDynQueryObjEnums __RPC_FAR * This,
    /* [in] */ BSTR bstrOKS,
    /* [retval][out] */ long __RPC_FAR *plIdent);


void __RPC_STUB IDynQueryObjEnums_IdentFromClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDynQueryObjEnums_EnumIdents_Proxy( 
    IDynQueryObjEnums __RPC_FAR * This,
    /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppIIdents);


void __RPC_STUB IDynQueryObjEnums_EnumIdents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IDynQueryObjEnums_get_ViewName_Proxy( 
    IDynQueryObjEnums __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IDynQueryObjEnums_get_ViewName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IDynQueryObjEnums_put_ViewName_Proxy( 
    IDynQueryObjEnums __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IDynQueryObjEnums_put_ViewName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDynQueryObjEnums_INTERFACE_DEFINED__ */



#ifndef __DynQueryLib_LIBRARY_DEFINED__
#define __DynQueryLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: DynQueryLib
 * at Mon Jun 16 11:03:28 1997
 * using MIDL 3.00.44
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_DynQueryLib;

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_DynQueryObjEnums;

class DynQueryObjEnums;
#endif
#endif /* __DynQueryLib_LIBRARY_DEFINED__ */

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
