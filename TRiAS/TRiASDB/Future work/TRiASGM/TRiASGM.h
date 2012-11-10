/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.76 */
/* at Thu Jul 02 22:45:31 1998
 */
/* Compiler settings for TRiASGM.idl:
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

#ifndef __TRiASGM_h__
#define __TRiASGM_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ITRiASSourceInfo_FWD_DEFINED__
#define __ITRiASSourceInfo_FWD_DEFINED__
typedef interface ITRiASSourceInfo ITRiASSourceInfo;
#endif 	/* __ITRiASSourceInfo_FWD_DEFINED__ */


#ifndef __IRecordsetGenerator_FWD_DEFINED__
#define __IRecordsetGenerator_FWD_DEFINED__
typedef interface IRecordsetGenerator IRecordsetGenerator;
#endif 	/* __IRecordsetGenerator_FWD_DEFINED__ */


#ifndef __IGDOFramework_FWD_DEFINED__
#define __IGDOFramework_FWD_DEFINED__
typedef interface IGDOFramework IGDOFramework;
#endif 	/* __IGDOFramework_FWD_DEFINED__ */


#ifndef __IRecordsetSource_FWD_DEFINED__
#define __IRecordsetSource_FWD_DEFINED__
typedef interface IRecordsetSource IRecordsetSource;
#endif 	/* __IRecordsetSource_FWD_DEFINED__ */


#ifndef __OKSRecordsetGenerator_FWD_DEFINED__
#define __OKSRecordsetGenerator_FWD_DEFINED__

#ifdef __cplusplus
typedef class OKSRecordsetGenerator OKSRecordsetGenerator;
#else
typedef struct OKSRecordsetGenerator OKSRecordsetGenerator;
#endif /* __cplusplus */

#endif 	/* __OKSRecordsetGenerator_FWD_DEFINED__ */


#ifndef __ViewRecordsetGenerator_FWD_DEFINED__
#define __ViewRecordsetGenerator_FWD_DEFINED__

#ifdef __cplusplus
typedef class ViewRecordsetGenerator ViewRecordsetGenerator;
#else
typedef struct ViewRecordsetGenerator ViewRecordsetGenerator;
#endif /* __cplusplus */

#endif 	/* __ViewRecordsetGenerator_FWD_DEFINED__ */


#ifndef __RecordsetSource_FWD_DEFINED__
#define __RecordsetSource_FWD_DEFINED__

#ifdef __cplusplus
typedef class RecordsetSource RecordsetSource;
#else
typedef struct RecordsetSource RecordsetSource;
#endif /* __cplusplus */

#endif 	/* __RecordsetSource_FWD_DEFINED__ */


#ifndef __TRiASSourceInfo_FWD_DEFINED__
#define __TRiASSourceInfo_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASSourceInfo TRiASSourceInfo;
#else
typedef struct TRiASSourceInfo TRiASSourceInfo;
#endif /* __cplusplus */

#endif 	/* __TRiASSourceInfo_FWD_DEFINED__ */


#ifndef __TRiASDefaultVisInfo_FWD_DEFINED__
#define __TRiASDefaultVisInfo_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASDefaultVisInfo TRiASDefaultVisInfo;
#else
typedef struct TRiASDefaultVisInfo TRiASDefaultVisInfo;
#endif /* __cplusplus */

#endif 	/* __TRiASDefaultVisInfo_FWD_DEFINED__ */


#ifndef __TRiASPointVisInfo_FWD_DEFINED__
#define __TRiASPointVisInfo_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASPointVisInfo TRiASPointVisInfo;
#else
typedef struct TRiASPointVisInfo TRiASPointVisInfo;
#endif /* __cplusplus */

#endif 	/* __TRiASPointVisInfo_FWD_DEFINED__ */


#ifndef __TRiASLineVisInfo_FWD_DEFINED__
#define __TRiASLineVisInfo_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASLineVisInfo TRiASLineVisInfo;
#else
typedef struct TRiASLineVisInfo TRiASLineVisInfo;
#endif /* __cplusplus */

#endif 	/* __TRiASLineVisInfo_FWD_DEFINED__ */


#ifndef __TRiASAreaVisInfo_FWD_DEFINED__
#define __TRiASAreaVisInfo_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASAreaVisInfo TRiASAreaVisInfo;
#else
typedef struct TRiASAreaVisInfo TRiASAreaVisInfo;
#endif /* __cplusplus */

#endif 	/* __TRiASAreaVisInfo_FWD_DEFINED__ */


#ifndef __TRiASTextVisInfo_FWD_DEFINED__
#define __TRiASTextVisInfo_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASTextVisInfo TRiASTextVisInfo;
#else
typedef struct TRiASTextVisInfo TRiASTextVisInfo;
#endif /* __cplusplus */

#endif 	/* __TRiASTextVisInfo_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_TRiASGM_0000
 * at Thu Jul 02 22:45:31 1998
 * using MIDL 3.01.76
 ****************************************/
/* [local] */ 


#if !defined(_DEFINED_HPROJECT)
#define _DEFINED_HPROJECT
typedef /* [hidden] */ struct  HPROJECT__
    {
    int unused;
    }	__RPC_FAR *HPROJECT;

#endif // _DEFINED_HPROJECT






extern RPC_IF_HANDLE __MIDL_itf_TRiASGM_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_TRiASGM_0000_v0_0_s_ifspec;

#ifndef __ITRiASSourceInfo_INTERFACE_DEFINED__
#define __ITRiASSourceInfo_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITRiASSourceInfo
 * at Thu Jul 02 22:45:31 1998
 * using MIDL 3.01.76
 ****************************************/
/* [unique][helpstring][uuid][object] */ 



EXTERN_C const IID IID_ITRiASSourceInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("2C9394B2-B038-11D1-859D-00600875138A")
    ITRiASSourceInfo : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Handle( 
            /* [retval][out] */ HPROJECT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Handle( 
            /* [in] */ HPROJECT newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TableName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TableName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CoordSystemType( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_CoordSystemType( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Ident( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Ident( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Types( 
            /* [retval][out] */ DWORD __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Types( 
            /* [in] */ DWORD newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASSourceInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITRiASSourceInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITRiASSourceInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITRiASSourceInfo __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Handle )( 
            ITRiASSourceInfo __RPC_FAR * This,
            /* [retval][out] */ HPROJECT __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Handle )( 
            ITRiASSourceInfo __RPC_FAR * This,
            /* [in] */ HPROJECT newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TableName )( 
            ITRiASSourceInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TableName )( 
            ITRiASSourceInfo __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CoordSystemType )( 
            ITRiASSourceInfo __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CoordSystemType )( 
            ITRiASSourceInfo __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Ident )( 
            ITRiASSourceInfo __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Ident )( 
            ITRiASSourceInfo __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Types )( 
            ITRiASSourceInfo __RPC_FAR * This,
            /* [retval][out] */ DWORD __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Types )( 
            ITRiASSourceInfo __RPC_FAR * This,
            /* [in] */ DWORD newVal);
        
        END_INTERFACE
    } ITRiASSourceInfoVtbl;

    interface ITRiASSourceInfo
    {
        CONST_VTBL struct ITRiASSourceInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASSourceInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASSourceInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASSourceInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASSourceInfo_get_Handle(This,pVal)	\
    (This)->lpVtbl -> get_Handle(This,pVal)

#define ITRiASSourceInfo_put_Handle(This,newVal)	\
    (This)->lpVtbl -> put_Handle(This,newVal)

#define ITRiASSourceInfo_get_TableName(This,pVal)	\
    (This)->lpVtbl -> get_TableName(This,pVal)

#define ITRiASSourceInfo_put_TableName(This,newVal)	\
    (This)->lpVtbl -> put_TableName(This,newVal)

#define ITRiASSourceInfo_get_CoordSystemType(This,pVal)	\
    (This)->lpVtbl -> get_CoordSystemType(This,pVal)

#define ITRiASSourceInfo_put_CoordSystemType(This,newVal)	\
    (This)->lpVtbl -> put_CoordSystemType(This,newVal)

#define ITRiASSourceInfo_get_Ident(This,pVal)	\
    (This)->lpVtbl -> get_Ident(This,pVal)

#define ITRiASSourceInfo_put_Ident(This,newVal)	\
    (This)->lpVtbl -> put_Ident(This,newVal)

#define ITRiASSourceInfo_get_Types(This,pVal)	\
    (This)->lpVtbl -> get_Types(This,pVal)

#define ITRiASSourceInfo_put_Types(This,newVal)	\
    (This)->lpVtbl -> put_Types(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSourceInfo_get_Handle_Proxy( 
    ITRiASSourceInfo __RPC_FAR * This,
    /* [retval][out] */ HPROJECT __RPC_FAR *pVal);


void __RPC_STUB ITRiASSourceInfo_get_Handle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ITRiASSourceInfo_put_Handle_Proxy( 
    ITRiASSourceInfo __RPC_FAR * This,
    /* [in] */ HPROJECT newVal);


void __RPC_STUB ITRiASSourceInfo_put_Handle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSourceInfo_get_TableName_Proxy( 
    ITRiASSourceInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITRiASSourceInfo_get_TableName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ITRiASSourceInfo_put_TableName_Proxy( 
    ITRiASSourceInfo __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITRiASSourceInfo_put_TableName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSourceInfo_get_CoordSystemType_Proxy( 
    ITRiASSourceInfo __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB ITRiASSourceInfo_get_CoordSystemType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ITRiASSourceInfo_put_CoordSystemType_Proxy( 
    ITRiASSourceInfo __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB ITRiASSourceInfo_put_CoordSystemType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSourceInfo_get_Ident_Proxy( 
    ITRiASSourceInfo __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB ITRiASSourceInfo_get_Ident_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ITRiASSourceInfo_put_Ident_Proxy( 
    ITRiASSourceInfo __RPC_FAR * This,
    /* [in] */ LONG newVal);


void __RPC_STUB ITRiASSourceInfo_put_Ident_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSourceInfo_get_Types_Proxy( 
    ITRiASSourceInfo __RPC_FAR * This,
    /* [retval][out] */ DWORD __RPC_FAR *pVal);


void __RPC_STUB ITRiASSourceInfo_get_Types_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ITRiASSourceInfo_put_Types_Proxy( 
    ITRiASSourceInfo __RPC_FAR * This,
    /* [in] */ DWORD newVal);


void __RPC_STUB ITRiASSourceInfo_put_Types_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASSourceInfo_INTERFACE_DEFINED__ */



#ifndef __TRIASGMLib_LIBRARY_DEFINED__
#define __TRIASGMLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: TRIASGMLib
 * at Thu Jul 02 22:45:31 1998
 * using MIDL 3.01.76
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_TRIASGMLib;

#ifndef __IRecordsetGenerator_INTERFACE_DEFINED__
#define __IRecordsetGenerator_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRecordsetGenerator
 * at Thu Jul 02 22:45:31 1998
 * using MIDL 3.01.76
 ****************************************/
/* [unique][helpstring][uuid][object] */ 



EXTERN_C const IID IID_IRecordsetGenerator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("724C7533-2A1B-11D1-920D-006097383187")
    IRecordsetGenerator : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetOutputRecordset( 
            /* [retval][out] */ /* external definition not present */ GRecordset __RPC_FAR *__RPC_FAR *ppOutputRecordset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFeatureName( 
            /* [in] */ BSTR bsFeatureName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSourceInfo( 
            /* [in] */ VARIANT vSourceInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRecordsetGeneratorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRecordsetGenerator __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRecordsetGenerator __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRecordsetGenerator __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOutputRecordset )( 
            IRecordsetGenerator __RPC_FAR * This,
            /* [retval][out] */ /* external definition not present */ GRecordset __RPC_FAR *__RPC_FAR *ppOutputRecordset);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFeatureName )( 
            IRecordsetGenerator __RPC_FAR * This,
            /* [in] */ BSTR bsFeatureName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSourceInfo )( 
            IRecordsetGenerator __RPC_FAR * This,
            /* [in] */ VARIANT vSourceInfo);
        
        END_INTERFACE
    } IRecordsetGeneratorVtbl;

    interface IRecordsetGenerator
    {
        CONST_VTBL struct IRecordsetGeneratorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRecordsetGenerator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRecordsetGenerator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRecordsetGenerator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRecordsetGenerator_GetOutputRecordset(This,ppOutputRecordset)	\
    (This)->lpVtbl -> GetOutputRecordset(This,ppOutputRecordset)

#define IRecordsetGenerator_SetFeatureName(This,bsFeatureName)	\
    (This)->lpVtbl -> SetFeatureName(This,bsFeatureName)

#define IRecordsetGenerator_SetSourceInfo(This,vSourceInfo)	\
    (This)->lpVtbl -> SetSourceInfo(This,vSourceInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRecordsetGenerator_GetOutputRecordset_Proxy( 
    IRecordsetGenerator __RPC_FAR * This,
    /* [retval][out] */ /* external definition not present */ GRecordset __RPC_FAR *__RPC_FAR *ppOutputRecordset);


void __RPC_STUB IRecordsetGenerator_GetOutputRecordset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRecordsetGenerator_SetFeatureName_Proxy( 
    IRecordsetGenerator __RPC_FAR * This,
    /* [in] */ BSTR bsFeatureName);


void __RPC_STUB IRecordsetGenerator_SetFeatureName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRecordsetGenerator_SetSourceInfo_Proxy( 
    IRecordsetGenerator __RPC_FAR * This,
    /* [in] */ VARIANT vSourceInfo);


void __RPC_STUB IRecordsetGenerator_SetSourceInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRecordsetGenerator_INTERFACE_DEFINED__ */


#ifndef __IGDOFramework_INTERFACE_DEFINED__
#define __IGDOFramework_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IGDOFramework
 * at Thu Jul 02 22:45:31 1998
 * using MIDL 3.01.76
 ****************************************/
/* [unique][helpstring][uuid][object] */ 



EXTERN_C const IID IID_IGDOFramework;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("700DC600-0E7D-11d1-9207-006097383187")
    IGDOFramework : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateGDatabase( 
            /* [in] */ IRecordsetSource __RPC_FAR *pRecordsetSource,
            /* [retval][out] */ /* external definition not present */ GDatabase __RPC_FAR *__RPC_FAR *ppIGDatabase) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGDOFrameworkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IGDOFramework __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IGDOFramework __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IGDOFramework __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateGDatabase )( 
            IGDOFramework __RPC_FAR * This,
            /* [in] */ IRecordsetSource __RPC_FAR *pRecordsetSource,
            /* [retval][out] */ /* external definition not present */ GDatabase __RPC_FAR *__RPC_FAR *ppIGDatabase);
        
        END_INTERFACE
    } IGDOFrameworkVtbl;

    interface IGDOFramework
    {
        CONST_VTBL struct IGDOFrameworkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGDOFramework_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGDOFramework_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGDOFramework_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGDOFramework_CreateGDatabase(This,pRecordsetSource,ppIGDatabase)	\
    (This)->lpVtbl -> CreateGDatabase(This,pRecordsetSource,ppIGDatabase)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IGDOFramework_CreateGDatabase_Proxy( 
    IGDOFramework __RPC_FAR * This,
    /* [in] */ IRecordsetSource __RPC_FAR *pRecordsetSource,
    /* [retval][out] */ /* external definition not present */ GDatabase __RPC_FAR *__RPC_FAR *ppIGDatabase);


void __RPC_STUB IGDOFramework_CreateGDatabase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGDOFramework_INTERFACE_DEFINED__ */


#ifndef __IRecordsetSource_INTERFACE_DEFINED__
#define __IRecordsetSource_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRecordsetSource
 * at Thu Jul 02 22:45:31 1998
 * using MIDL 3.01.76
 ****************************************/
/* [unique][helpstring][uuid][object] */ 



EXTERN_C const IID IID_IRecordsetSource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("9C3B10B0-0E7D-11d1-9207-006097383187")
    IRecordsetSource : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OpenSource( 
            /* [in] */ BSTR Name,
            /* [optional][in] */ VARIANT Exclusive,
            /* [optional][in] */ VARIANT Readonly,
            /* [optional][in] */ VARIANT ModTrack,
            /* [optional][in] */ VARIANT Source) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTableNames( 
            /* [retval][out] */ SAFEARRAY __RPC_FAR *__RPC_FAR *TableNames) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGRecordset( 
            /* [in] */ BSTR TableName,
            /* [retval][out] */ /* external definition not present */ GRecordset __RPC_FAR *__RPC_FAR *pSourceGRecordset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetProperty( 
            /* [in] */ BSTR PropName,
            /* [retval][out] */ VARIANT __RPC_FAR *PropValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OpenRecordset( 
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Type,
            /* [optional][in] */ VARIANT Options,
            /* [in] */ VARIANT SpatialOp,
            /* [in] */ VARIANT SpatialGeometryFilter,
            /* [in] */ VARIANT GeometryFieldName,
            /* [retval][out] */ /* external definition not present */ GRecordset __RPC_FAR *__RPC_FAR *ppGRecordset) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRecordsetSourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRecordsetSource __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRecordsetSource __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRecordsetSource __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenSource )( 
            IRecordsetSource __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [optional][in] */ VARIANT Exclusive,
            /* [optional][in] */ VARIANT Readonly,
            /* [optional][in] */ VARIANT ModTrack,
            /* [optional][in] */ VARIANT Source);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTableNames )( 
            IRecordsetSource __RPC_FAR * This,
            /* [retval][out] */ SAFEARRAY __RPC_FAR *__RPC_FAR *TableNames);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGRecordset )( 
            IRecordsetSource __RPC_FAR * This,
            /* [in] */ BSTR TableName,
            /* [retval][out] */ /* external definition not present */ GRecordset __RPC_FAR *__RPC_FAR *pSourceGRecordset);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProperty )( 
            IRecordsetSource __RPC_FAR * This,
            /* [in] */ BSTR PropName,
            /* [retval][out] */ VARIANT __RPC_FAR *PropValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenRecordset )( 
            IRecordsetSource __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Type,
            /* [optional][in] */ VARIANT Options,
            /* [in] */ VARIANT SpatialOp,
            /* [in] */ VARIANT SpatialGeometryFilter,
            /* [in] */ VARIANT GeometryFieldName,
            /* [retval][out] */ /* external definition not present */ GRecordset __RPC_FAR *__RPC_FAR *ppGRecordset);
        
        END_INTERFACE
    } IRecordsetSourceVtbl;

    interface IRecordsetSource
    {
        CONST_VTBL struct IRecordsetSourceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRecordsetSource_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRecordsetSource_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRecordsetSource_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRecordsetSource_OpenSource(This,Name,Exclusive,Readonly,ModTrack,Source)	\
    (This)->lpVtbl -> OpenSource(This,Name,Exclusive,Readonly,ModTrack,Source)

#define IRecordsetSource_GetTableNames(This,TableNames)	\
    (This)->lpVtbl -> GetTableNames(This,TableNames)

#define IRecordsetSource_GetGRecordset(This,TableName,pSourceGRecordset)	\
    (This)->lpVtbl -> GetGRecordset(This,TableName,pSourceGRecordset)

#define IRecordsetSource_GetProperty(This,PropName,PropValue)	\
    (This)->lpVtbl -> GetProperty(This,PropName,PropValue)

#define IRecordsetSource_OpenRecordset(This,Name,Type,Options,SpatialOp,SpatialGeometryFilter,GeometryFieldName,ppGRecordset)	\
    (This)->lpVtbl -> OpenRecordset(This,Name,Type,Options,SpatialOp,SpatialGeometryFilter,GeometryFieldName,ppGRecordset)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRecordsetSource_OpenSource_Proxy( 
    IRecordsetSource __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [optional][in] */ VARIANT Exclusive,
    /* [optional][in] */ VARIANT Readonly,
    /* [optional][in] */ VARIANT ModTrack,
    /* [optional][in] */ VARIANT Source);


void __RPC_STUB IRecordsetSource_OpenSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRecordsetSource_GetTableNames_Proxy( 
    IRecordsetSource __RPC_FAR * This,
    /* [retval][out] */ SAFEARRAY __RPC_FAR *__RPC_FAR *TableNames);


void __RPC_STUB IRecordsetSource_GetTableNames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRecordsetSource_GetGRecordset_Proxy( 
    IRecordsetSource __RPC_FAR * This,
    /* [in] */ BSTR TableName,
    /* [retval][out] */ /* external definition not present */ GRecordset __RPC_FAR *__RPC_FAR *pSourceGRecordset);


void __RPC_STUB IRecordsetSource_GetGRecordset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRecordsetSource_GetProperty_Proxy( 
    IRecordsetSource __RPC_FAR * This,
    /* [in] */ BSTR PropName,
    /* [retval][out] */ VARIANT __RPC_FAR *PropValue);


void __RPC_STUB IRecordsetSource_GetProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRecordsetSource_OpenRecordset_Proxy( 
    IRecordsetSource __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [in] */ VARIANT Type,
    /* [optional][in] */ VARIANT Options,
    /* [in] */ VARIANT SpatialOp,
    /* [in] */ VARIANT SpatialGeometryFilter,
    /* [in] */ VARIANT GeometryFieldName,
    /* [retval][out] */ /* external definition not present */ GRecordset __RPC_FAR *__RPC_FAR *ppGRecordset);


void __RPC_STUB IRecordsetSource_OpenRecordset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRecordsetSource_INTERFACE_DEFINED__ */


#ifdef __cplusplus
EXTERN_C const CLSID CLSID_OKSRecordsetGenerator;

class DECLSPEC_UUID("7417A5E4-AED0-11D1-859A-00600875138A")
OKSRecordsetGenerator;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_ViewRecordsetGenerator;

class DECLSPEC_UUID("7417A5E5-AED0-11D1-859A-00600875138A")
ViewRecordsetGenerator;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_RecordsetSource;

class DECLSPEC_UUID("7417A5E7-AED0-11D1-859A-00600875138A")
RecordsetSource;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_TRiASSourceInfo;

class DECLSPEC_UUID("2C9394B4-B038-11D1-859D-00600875138A")
TRiASSourceInfo;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_TRiASDefaultVisInfo;

class DECLSPEC_UUID("429906A0-B83F-11D1-85B5-00600875138A")
TRiASDefaultVisInfo;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_TRiASPointVisInfo;

class DECLSPEC_UUID("429906A1-B83F-11D1-85B5-00600875138A")
TRiASPointVisInfo;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_TRiASLineVisInfo;

class DECLSPEC_UUID("429906A2-B83F-11D1-85B5-00600875138A")
TRiASLineVisInfo;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_TRiASAreaVisInfo;

class DECLSPEC_UUID("429906A3-B83F-11D1-85B5-00600875138A")
TRiASAreaVisInfo;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_TRiASTextVisInfo;

class DECLSPEC_UUID("429906A4-B83F-11D1-85B5-00600875138A")
TRiASTextVisInfo;
#endif
#endif /* __TRIASGMLib_LIBRARY_DEFINED__ */

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
