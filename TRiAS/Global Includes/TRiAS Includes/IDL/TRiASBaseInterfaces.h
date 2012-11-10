/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.76 */
/* at Fri Feb 06 17:59:49 1998
 */
/* Compiler settings for TRiASBaseInterfaces.idl:
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

#ifndef __TRiASBaseInterfaces_h__
#define __TRiASBaseInterfaces_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

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


/* header files for imported files */
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_TRiASBaseInterfaces_0000
 * at Fri Feb 06 17:59:49 1998
 * using MIDL 3.01.76
 ****************************************/
/* [local] */ 






#if !defined(_RTTI_DEFINED)
#define _RTTI_DEFINED

enum _tagRTTI
    {	RTTI_Unknown	= 0,
	RTTI_Application	= 0x1,
	RTTI_Document	= 0x2,
	RTTI_Documents	= 0x3,
	RTTI_GeoView	= 0x4,
	RTTI_GeoViews	= 0x5,
	RTTI_GeoClass	= 0x6,
	RTTI_GeoClasses	= 0x7,
	RTTI_GeoObject	= 0x8,
	RTTI_GeoObjects	= 0x9,
	RTTI_GeoFeature	= 0xa,
	RTTI_GeoFeatures	= 0xb,
	RTTI_GeoObjectWin	= 0xc,
	RTTI_GeoObjectWins	= 0xd,
	RTTI_VisInfo	= 0xe,
	RTTI_PointVisInfo	= 0x1000e,
	RTTI_LineVisInfo	= 0x2000e,
	RTTI_AreaVisInfo	= 0x3000e,
	RTTI_TextVisInfo	= 0x4000e,
	RTTI_ToolBar	= 0xf,
	RTTI_ToolBars	= 0x10,
	RTTI_ToolBarButton	= 0x11,
	RTTI_ToolBarButtons	= 0x12,
	RTTI_Property	= 0x13,
	RTTI_Properties	= 0x14
    };
#endif // _RTTI_DEFINED


extern RPC_IF_HANDLE __MIDL_itf_TRiASBaseInterfaces_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_TRiASBaseInterfaces_0000_v0_0_s_ifspec;

#ifndef __DTRiASBaseClass_INTERFACE_DEFINED__
#define __DTRiASBaseClass_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: DTRiASBaseClass
 * at Fri Feb 06 17:59:49 1998
 * using MIDL 3.01.76
 ****************************************/
/* [helpstring][uuid][nonextensible][dual][oleautomation][object] */ 



EXTERN_C const IID IID_DTRiASBaseClass;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("8DE4E3E0-4D53-101B-AAE1-E7E7E7E7E7E7")
    DTRiASBaseClass : public IDispatch
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
 * at Fri Feb 06 17:59:49 1998
 * using MIDL 3.01.76
 ****************************************/
/* [helpstring][uuid][nonextensible][dual][oleautomation][object] */ 



EXTERN_C const IID IID_DTRiASCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("8DE4E3DF-4D53-101B-AAE1-E7E7E7E7E7E7")
    DTRiASCollection : public DTRiASBaseClass
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
 * at Fri Feb 06 17:59:49 1998
 * using MIDL 3.01.76
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
    
    interface DECLSPEC_UUID("079638C1-3123-101C-BB62-00AA0018497C")
    DTRiASProperty : public DTRiASBaseClass
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
 * at Fri Feb 06 17:59:49 1998
 * using MIDL 3.01.76
 ****************************************/
/* [oleautomation][helpstring][uuid][dual][object] */ 



EXTERN_C const IID IID_DTRiASProperties;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("079638C2-3123-101C-BB62-00AA0018497C")
    DTRiASProperties : public DTRiASCollection
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
