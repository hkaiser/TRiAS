
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0280 */
/* at Tue Mar 21 20:08:13 2000
 */
/* Compiler settings for UndoRedo.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32 (32b run), ms_ext, c_ext
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

#ifndef __UndoRedo_h__
#define __UndoRedo_h__

/* Forward Declarations */ 

#ifndef __IUndoRedo_FWD_DEFINED__
#define __IUndoRedo_FWD_DEFINED__
typedef interface IUndoRedo IUndoRedo;
#endif 	/* __IUndoRedo_FWD_DEFINED__ */


#ifndef __IUndoRedoList_FWD_DEFINED__
#define __IUndoRedoList_FWD_DEFINED__
typedef interface IUndoRedoList IUndoRedoList;
#endif 	/* __IUndoRedoList_FWD_DEFINED__ */


#ifndef __IPropagateObjectNumber_FWD_DEFINED__
#define __IPropagateObjectNumber_FWD_DEFINED__
typedef interface IPropagateObjectNumber IPropagateObjectNumber;
#endif 	/* __IPropagateObjectNumber_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_UndoRedo_0000 */
/* [local] */ 




#ifndef _IUNDOREDO_DEFINED
#define _IUNDOREDO_DEFINED


extern RPC_IF_HANDLE __MIDL_itf_UndoRedo_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_UndoRedo_0000_v0_0_s_ifspec;

#ifndef __IUndoRedo_INTERFACE_DEFINED__
#define __IUndoRedo_INTERFACE_DEFINED__

/* interface IUndoRedo */
/* [unique][helpstring][uuid][object] */ 

#if !defined(_UNDOREDOCAPS_DEFINED)
#define _UNDOREDOCAPS_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum tagUNDOREDOCAPS
    {	UNDOREDOCAPS_NOFLAGS	= 0,
	UNDOREDOCAPS_ANDFLAGS	= 0x3,
	UNDOREDOCAPS_ORFLAGS	= 0x300,
	UNDOREDOCAPS_CANUNDO	= 0x1,
	UNDOREDOCAPS_CANREDO	= 0x2,
	UNDOREDOCAPS_REPAINT	= 0x100,
	UNDOREDOCAPS_MULTILEVEL	= 0x200
    }	UNDOREDOCAPS;

#endif // _UNDOREDOCAPS_DEFINED

EXTERN_C const IID IID_IUndoRedo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("07963808-3123-101C-BB62-00AA0018497C")
    IUndoRedo : public IUnknown
    {
    public:
        virtual /* [local][helpstring] */ DWORD STDMETHODCALLTYPE Capabilities( 
            /* [out] */ signed char __RPC_FAR *__RPC_FAR *pDesc) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Undo( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Redo( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUndoRedoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IUndoRedo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IUndoRedo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IUndoRedo __RPC_FAR * This);
        
        /* [local][helpstring] */ DWORD ( STDMETHODCALLTYPE __RPC_FAR *Capabilities )( 
            IUndoRedo __RPC_FAR * This,
            /* [out] */ signed char __RPC_FAR *__RPC_FAR *pDesc);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Undo )( 
            IUndoRedo __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Redo )( 
            IUndoRedo __RPC_FAR * This);
        
        END_INTERFACE
    } IUndoRedoVtbl;

    interface IUndoRedo
    {
        CONST_VTBL struct IUndoRedoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUndoRedo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUndoRedo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUndoRedo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUndoRedo_Capabilities(This,pDesc)	\
    (This)->lpVtbl -> Capabilities(This,pDesc)

#define IUndoRedo_Undo(This)	\
    (This)->lpVtbl -> Undo(This)

#define IUndoRedo_Redo(This)	\
    (This)->lpVtbl -> Redo(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IUndoRedo_remoteCapabilities_Proxy( 
    IUndoRedo __RPC_FAR * This,
    /* [out] */ signed char __RPC_FAR *__RPC_FAR *pDesc,
    /* [retval][out] */ DWORD __RPC_FAR *pdwCaps);


void __RPC_STUB IUndoRedo_remoteCapabilities_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IUndoRedo_Undo_Proxy( 
    IUndoRedo __RPC_FAR * This);


void __RPC_STUB IUndoRedo_Undo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IUndoRedo_Redo_Proxy( 
    IUndoRedo __RPC_FAR * This);


void __RPC_STUB IUndoRedo_Redo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUndoRedo_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_UndoRedo_0105 */
/* [local] */ 

typedef IUndoRedo * LPUNDOREDO;
#endif // _IUNDOREDO_DEFINED
#ifndef _IUNDOREDOLIST_DEFINED
#define _IUNDOREDOLIST_DEFINED


extern RPC_IF_HANDLE __MIDL_itf_UndoRedo_0105_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_UndoRedo_0105_v0_0_s_ifspec;

#ifndef __IUndoRedoList_INTERFACE_DEFINED__
#define __IUndoRedoList_INTERFACE_DEFINED__

/* interface IUndoRedoList */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IUndoRedoList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("07963809-3123-101C-BB62-00AA0018497C")
    IUndoRedoList : public IUndoRedo
    {
    public:
        virtual /* [local][helpstring] */ ULONG STDMETHODCALLTYPE Count( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddUndoRedo( 
            /* [in] */ IUndoRedo __RPC_FAR *pIUndoRedo) = 0;
        
        virtual /* [local][helpstring] */ DWORD STDMETHODCALLTYPE Undo( 
            /* [in] */ long lCnt,
            /* [in] */ IUndoRedoList __RPC_FAR *pIRedoList) = 0;
        
        virtual /* [local][helpstring] */ DWORD STDMETHODCALLTYPE Redo( 
            /* [in] */ long lCnt,
            /* [in] */ IUndoRedoList __RPC_FAR *pIUndoList) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUndoRedoListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IUndoRedoList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IUndoRedoList __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IUndoRedoList __RPC_FAR * This);
        
        /* [local][helpstring] */ DWORD ( STDMETHODCALLTYPE __RPC_FAR *Capabilities )( 
            IUndoRedoList __RPC_FAR * This,
            /* [out] */ signed char __RPC_FAR *__RPC_FAR *pDesc);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Undo )( 
            IUndoRedoList __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Redo )( 
            IUndoRedoList __RPC_FAR * This);
        
        /* [local][helpstring] */ ULONG ( STDMETHODCALLTYPE __RPC_FAR *Count )( 
            IUndoRedoList __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddUndoRedo )( 
            IUndoRedoList __RPC_FAR * This,
            /* [in] */ IUndoRedo __RPC_FAR *pIUndoRedo);
        
        /* [local][helpstring] */ DWORD ( STDMETHODCALLTYPE __RPC_FAR *Undo )( 
            IUndoRedoList __RPC_FAR * This,
            /* [in] */ long lCnt,
            /* [in] */ IUndoRedoList __RPC_FAR *pIRedoList);
        
        /* [local][helpstring] */ DWORD ( STDMETHODCALLTYPE __RPC_FAR *Redo )( 
            IUndoRedoList __RPC_FAR * This,
            /* [in] */ long lCnt,
            /* [in] */ IUndoRedoList __RPC_FAR *pIUndoList);
        
        END_INTERFACE
    } IUndoRedoListVtbl;

    interface IUndoRedoList
    {
        CONST_VTBL struct IUndoRedoListVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUndoRedoList_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUndoRedoList_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUndoRedoList_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUndoRedoList_Capabilities(This,pDesc)	\
    (This)->lpVtbl -> Capabilities(This,pDesc)

#define IUndoRedoList_Undo(This)	\
    (This)->lpVtbl -> Undo(This)

#define IUndoRedoList_Redo(This)	\
    (This)->lpVtbl -> Redo(This)


#define IUndoRedoList_Count(This)	\
    (This)->lpVtbl -> Count(This)

#define IUndoRedoList_AddUndoRedo(This,pIUndoRedo)	\
    (This)->lpVtbl -> AddUndoRedo(This,pIUndoRedo)

#define IUndoRedoList_Undo(This,lCnt,pIRedoList)	\
    (This)->lpVtbl -> Undo(This,lCnt,pIRedoList)

#define IUndoRedoList_Redo(This,lCnt,pIUndoList)	\
    (This)->lpVtbl -> Redo(This,lCnt,pIUndoList)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IUndoRedoList_remoteCount_Proxy( 
    IUndoRedoList __RPC_FAR * This,
    /* [retval][out] */ ULONG __RPC_FAR *pulCnt);


void __RPC_STUB IUndoRedoList_remoteCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IUndoRedoList_AddUndoRedo_Proxy( 
    IUndoRedoList __RPC_FAR * This,
    /* [in] */ IUndoRedo __RPC_FAR *pIUndoRedo);


void __RPC_STUB IUndoRedoList_AddUndoRedo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IUndoRedoList_remoteUndo_Proxy( 
    IUndoRedoList __RPC_FAR * This,
    /* [in] */ long lCnt,
    /* [in] */ IUndoRedoList __RPC_FAR *pIRedoList,
    /* [retval][out] */ DWORD __RPC_FAR *pdwCaps);


void __RPC_STUB IUndoRedoList_remoteUndo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IUndoRedoList_remoteRedo_Proxy( 
    IUndoRedoList __RPC_FAR * This,
    /* [in] */ long lCnt,
    /* [in] */ IUndoRedoList __RPC_FAR *pIUndoList,
    /* [retval][out] */ DWORD __RPC_FAR *pdwCaps);


void __RPC_STUB IUndoRedoList_remoteRedo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUndoRedoList_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_UndoRedo_0106 */
/* [local] */ 

typedef IUndoRedoList * LPUNDOREDOLIST;
#endif // _IUNDOREDOLIST_DEFINED
#ifndef _IPROPAGATEOBJECTNUMBER_DEFINED
#define _IPROPAGATEOBJECTNUMBER_DEFINED


extern RPC_IF_HANDLE __MIDL_itf_UndoRedo_0106_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_UndoRedo_0106_v0_0_s_ifspec;

#ifndef __IPropagateObjectNumber_INTERFACE_DEFINED__
#define __IPropagateObjectNumber_INTERFACE_DEFINED__

/* interface IPropagateObjectNumber */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPropagateObjectNumber;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9A55E460-24EB-11D3-94F1-0080C786297B")
    IPropagateObjectNumber : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetUndoObjectNumber( 
            /* [retval][out] */ INT_PTR __RPC_FAR *plONr) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetUndoObjectNumber( 
            /* [in] */ INT_PTR lONr) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRedoObjectNumber( 
            /* [retval][out] */ INT_PTR __RPC_FAR *plONr) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetRedoObjectNumber( 
            /* [in] */ INT_PTR lONr) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPropagateObjectNumberVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPropagateObjectNumber __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPropagateObjectNumber __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPropagateObjectNumber __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetUndoObjectNumber )( 
            IPropagateObjectNumber __RPC_FAR * This,
            /* [retval][out] */ INT_PTR __RPC_FAR *plONr);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetUndoObjectNumber )( 
            IPropagateObjectNumber __RPC_FAR * This,
            /* [in] */ INT_PTR lONr);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRedoObjectNumber )( 
            IPropagateObjectNumber __RPC_FAR * This,
            /* [retval][out] */ INT_PTR __RPC_FAR *plONr);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetRedoObjectNumber )( 
            IPropagateObjectNumber __RPC_FAR * This,
            /* [in] */ INT_PTR lONr);
        
        END_INTERFACE
    } IPropagateObjectNumberVtbl;

    interface IPropagateObjectNumber
    {
        CONST_VTBL struct IPropagateObjectNumberVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPropagateObjectNumber_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPropagateObjectNumber_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPropagateObjectNumber_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPropagateObjectNumber_GetUndoObjectNumber(This,plONr)	\
    (This)->lpVtbl -> GetUndoObjectNumber(This,plONr)

#define IPropagateObjectNumber_SetUndoObjectNumber(This,lONr)	\
    (This)->lpVtbl -> SetUndoObjectNumber(This,lONr)

#define IPropagateObjectNumber_GetRedoObjectNumber(This,plONr)	\
    (This)->lpVtbl -> GetRedoObjectNumber(This,plONr)

#define IPropagateObjectNumber_SetRedoObjectNumber(This,lONr)	\
    (This)->lpVtbl -> SetRedoObjectNumber(This,lONr)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPropagateObjectNumber_GetUndoObjectNumber_Proxy( 
    IPropagateObjectNumber __RPC_FAR * This,
    /* [retval][out] */ INT_PTR __RPC_FAR *plONr);


void __RPC_STUB IPropagateObjectNumber_GetUndoObjectNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPropagateObjectNumber_SetUndoObjectNumber_Proxy( 
    IPropagateObjectNumber __RPC_FAR * This,
    /* [in] */ INT_PTR lONr);


void __RPC_STUB IPropagateObjectNumber_SetUndoObjectNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPropagateObjectNumber_GetRedoObjectNumber_Proxy( 
    IPropagateObjectNumber __RPC_FAR * This,
    /* [retval][out] */ INT_PTR __RPC_FAR *plONr);


void __RPC_STUB IPropagateObjectNumber_GetRedoObjectNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPropagateObjectNumber_SetRedoObjectNumber_Proxy( 
    IPropagateObjectNumber __RPC_FAR * This,
    /* [in] */ INT_PTR lONr);


void __RPC_STUB IPropagateObjectNumber_SetRedoObjectNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPropagateObjectNumber_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_UndoRedo_0107 */
/* [local] */ 

#endif // _IPROPAGATEOBJECTNUMBER_DEFINED


extern RPC_IF_HANDLE __MIDL_itf_UndoRedo_0107_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_UndoRedo_0107_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* [local][helpstring] */ DWORD STDMETHODCALLTYPE IUndoRedo_Capabilities_Proxy( 
    IUndoRedo __RPC_FAR * This,
    /* [out] */ signed char __RPC_FAR *__RPC_FAR *pDesc);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IUndoRedo_Capabilities_Stub( 
    IUndoRedo __RPC_FAR * This,
    /* [out] */ signed char __RPC_FAR *__RPC_FAR *pDesc,
    /* [retval][out] */ DWORD __RPC_FAR *pdwCaps);

/* [local][helpstring] */ ULONG STDMETHODCALLTYPE IUndoRedoList_Count_Proxy( 
    IUndoRedoList __RPC_FAR * This);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IUndoRedoList_Count_Stub( 
    IUndoRedoList __RPC_FAR * This,
    /* [retval][out] */ ULONG __RPC_FAR *pulCnt);

/* [local][helpstring] */ DWORD STDMETHODCALLTYPE IUndoRedoList_Undo_Proxy( 
    IUndoRedoList __RPC_FAR * This,
    /* [in] */ long lCnt,
    /* [in] */ IUndoRedoList __RPC_FAR *pIRedoList);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IUndoRedoList_Undo_Stub( 
    IUndoRedoList __RPC_FAR * This,
    /* [in] */ long lCnt,
    /* [in] */ IUndoRedoList __RPC_FAR *pIRedoList,
    /* [retval][out] */ DWORD __RPC_FAR *pdwCaps);

/* [local][helpstring] */ DWORD STDMETHODCALLTYPE IUndoRedoList_Redo_Proxy( 
    IUndoRedoList __RPC_FAR * This,
    /* [in] */ long lCnt,
    /* [in] */ IUndoRedoList __RPC_FAR *pIUndoList);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IUndoRedoList_Redo_Stub( 
    IUndoRedoList __RPC_FAR * This,
    /* [in] */ long lCnt,
    /* [in] */ IUndoRedoList __RPC_FAR *pIUndoList,
    /* [retval][out] */ DWORD __RPC_FAR *pdwCaps);



/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


