
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Tue May 21 09:52:15 2002
 */
/* Compiler settings for TDBGeo.idl:
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

#ifndef __TDBGeo_h__
#define __TDBGeo_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITRiASCSStorageService_FWD_DEFINED__
#define __ITRiASCSStorageService_FWD_DEFINED__
typedef interface ITRiASCSStorageService ITRiASCSStorageService;
#endif 	/* __ITRiASCSStorageService_FWD_DEFINED__ */


#ifndef __ITRiASCloneGeometry_FWD_DEFINED__
#define __ITRiASCloneGeometry_FWD_DEFINED__
typedef interface ITRiASCloneGeometry ITRiASCloneGeometry;
#endif 	/* __ITRiASCloneGeometry_FWD_DEFINED__ */


#ifndef __ITRiASSpatialRelationService_FWD_DEFINED__
#define __ITRiASSpatialRelationService_FWD_DEFINED__
typedef interface ITRiASSpatialRelationService ITRiASSpatialRelationService;
#endif 	/* __ITRiASSpatialRelationService_FWD_DEFINED__ */


#ifndef __IPersistMemoryGDO_FWD_DEFINED__
#define __IPersistMemoryGDO_FWD_DEFINED__
typedef interface IPersistMemoryGDO IPersistMemoryGDO;
#endif 	/* __IPersistMemoryGDO_FWD_DEFINED__ */


#ifndef __IPersistMemoryWks_FWD_DEFINED__
#define __IPersistMemoryWks_FWD_DEFINED__
typedef interface IPersistMemoryWks IPersistMemoryWks;
#endif 	/* __IPersistMemoryWks_FWD_DEFINED__ */


#ifndef __ITRiASCSStorageServiceGDO_FWD_DEFINED__
#define __ITRiASCSStorageServiceGDO_FWD_DEFINED__
typedef interface ITRiASCSStorageServiceGDO ITRiASCSStorageServiceGDO;
#endif 	/* __ITRiASCSStorageServiceGDO_FWD_DEFINED__ */


#ifndef __ITRiASCSStorageServiceWks_FWD_DEFINED__
#define __ITRiASCSStorageServiceWks_FWD_DEFINED__
typedef interface ITRiASCSStorageServiceWks ITRiASCSStorageServiceWks;
#endif 	/* __ITRiASCSStorageServiceWks_FWD_DEFINED__ */


#ifndef __ITRiASSimpleRectangle_FWD_DEFINED__
#define __ITRiASSimpleRectangle_FWD_DEFINED__
typedef interface ITRiASSimpleRectangle ITRiASSimpleRectangle;
#endif 	/* __ITRiASSimpleRectangle_FWD_DEFINED__ */


#ifndef __ITRiASCloneGeometry_FWD_DEFINED__
#define __ITRiASCloneGeometry_FWD_DEFINED__
typedef interface ITRiASCloneGeometry ITRiASCloneGeometry;
#endif 	/* __ITRiASCloneGeometry_FWD_DEFINED__ */


#ifndef __ITRiASCSGeometryProperties_FWD_DEFINED__
#define __ITRiASCSGeometryProperties_FWD_DEFINED__
typedef interface ITRiASCSGeometryProperties ITRiASCSGeometryProperties;
#endif 	/* __ITRiASCSGeometryProperties_FWD_DEFINED__ */


#ifndef __ITRiASSimplePoint_FWD_DEFINED__
#define __ITRiASSimplePoint_FWD_DEFINED__
typedef interface ITRiASSimplePoint ITRiASSimplePoint;
#endif 	/* __ITRiASSimplePoint_FWD_DEFINED__ */


#ifndef __ITRiASSimplePoints_FWD_DEFINED__
#define __ITRiASSimplePoints_FWD_DEFINED__
typedef interface ITRiASSimplePoints ITRiASSimplePoints;
#endif 	/* __ITRiASSimplePoints_FWD_DEFINED__ */


#ifndef __ITRiASCSMBRAccess_FWD_DEFINED__
#define __ITRiASCSMBRAccess_FWD_DEFINED__
typedef interface ITRiASCSMBRAccess ITRiASCSMBRAccess;
#endif 	/* __ITRiASCSMBRAccess_FWD_DEFINED__ */


#ifndef __TRiASCSPoint_FWD_DEFINED__
#define __TRiASCSPoint_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASCSPoint TRiASCSPoint;
#else
typedef struct TRiASCSPoint TRiASCSPoint;
#endif /* __cplusplus */

#endif 	/* __TRiASCSPoint_FWD_DEFINED__ */


#ifndef __TRiASCSPoints_FWD_DEFINED__
#define __TRiASCSPoints_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASCSPoints TRiASCSPoints;
#else
typedef struct TRiASCSPoints TRiASCSPoints;
#endif /* __cplusplus */

#endif 	/* __TRiASCSPoints_FWD_DEFINED__ */


#ifndef __TRiASCSVector_FWD_DEFINED__
#define __TRiASCSVector_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASCSVector TRiASCSVector;
#else
typedef struct TRiASCSVector TRiASCSVector;
#endif /* __cplusplus */

#endif 	/* __TRiASCSVector_FWD_DEFINED__ */


#ifndef __TRiASCSRectangleGeometry_FWD_DEFINED__
#define __TRiASCSRectangleGeometry_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASCSRectangleGeometry TRiASCSRectangleGeometry;
#else
typedef struct TRiASCSRectangleGeometry TRiASCSRectangleGeometry;
#endif /* __cplusplus */

#endif 	/* __TRiASCSRectangleGeometry_FWD_DEFINED__ */


#ifndef __TRiASCSLineGeometry_FWD_DEFINED__
#define __TRiASCSLineGeometry_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASCSLineGeometry TRiASCSLineGeometry;
#else
typedef struct TRiASCSLineGeometry TRiASCSLineGeometry;
#endif /* __cplusplus */

#endif 	/* __TRiASCSLineGeometry_FWD_DEFINED__ */


#ifndef __TRiASCSPointGeometry_FWD_DEFINED__
#define __TRiASCSPointGeometry_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASCSPointGeometry TRiASCSPointGeometry;
#else
typedef struct TRiASCSPointGeometry TRiASCSPointGeometry;
#endif /* __cplusplus */

#endif 	/* __TRiASCSPointGeometry_FWD_DEFINED__ */


#ifndef __TRiASCSOrientedPointGeometry_FWD_DEFINED__
#define __TRiASCSOrientedPointGeometry_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASCSOrientedPointGeometry TRiASCSOrientedPointGeometry;
#else
typedef struct TRiASCSOrientedPointGeometry TRiASCSOrientedPointGeometry;
#endif /* __cplusplus */

#endif 	/* __TRiASCSOrientedPointGeometry_FWD_DEFINED__ */


#ifndef __TRiASCSPolylineGeometry_FWD_DEFINED__
#define __TRiASCSPolylineGeometry_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASCSPolylineGeometry TRiASCSPolylineGeometry;
#else
typedef struct TRiASCSPolylineGeometry TRiASCSPolylineGeometry;
#endif /* __cplusplus */

#endif 	/* __TRiASCSPolylineGeometry_FWD_DEFINED__ */


#ifndef __TRiASCSPolygonGeometry_FWD_DEFINED__
#define __TRiASCSPolygonGeometry_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASCSPolygonGeometry TRiASCSPolygonGeometry;
#else
typedef struct TRiASCSPolygonGeometry TRiASCSPolygonGeometry;
#endif /* __cplusplus */

#endif 	/* __TRiASCSPolygonGeometry_FWD_DEFINED__ */


#ifndef __TRiASCSBoundaryGeometry_FWD_DEFINED__
#define __TRiASCSBoundaryGeometry_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASCSBoundaryGeometry TRiASCSBoundaryGeometry;
#else
typedef struct TRiASCSBoundaryGeometry TRiASCSBoundaryGeometry;
#endif /* __cplusplus */

#endif 	/* __TRiASCSBoundaryGeometry_FWD_DEFINED__ */


#ifndef __TRiASCSGeometryCollection_FWD_DEFINED__
#define __TRiASCSGeometryCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASCSGeometryCollection TRiASCSGeometryCollection;
#else
typedef struct TRiASCSGeometryCollection TRiASCSGeometryCollection;
#endif /* __cplusplus */

#endif 	/* __TRiASCSGeometryCollection_FWD_DEFINED__ */


#ifndef __TRiASCSTextPointGeometry_FWD_DEFINED__
#define __TRiASCSTextPointGeometry_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASCSTextPointGeometry TRiASCSTextPointGeometry;
#else
typedef struct TRiASCSTextPointGeometry TRiASCSTextPointGeometry;
#endif /* __cplusplus */

#endif 	/* __TRiASCSTextPointGeometry_FWD_DEFINED__ */


#ifndef __TRiASCSStorageService_FWD_DEFINED__
#define __TRiASCSStorageService_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASCSStorageService TRiASCSStorageService;
#else
typedef struct TRiASCSStorageService TRiASCSStorageService;
#endif /* __cplusplus */

#endif 	/* __TRiASCSStorageService_FWD_DEFINED__ */


#ifndef __TRiASCSPointEnum_FWD_DEFINED__
#define __TRiASCSPointEnum_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASCSPointEnum TRiASCSPointEnum;
#else
typedef struct TRiASCSPointEnum TRiASCSPointEnum;
#endif /* __cplusplus */

#endif 	/* __TRiASCSPointEnum_FWD_DEFINED__ */


#ifndef __GeometryMoniker_FWD_DEFINED__
#define __GeometryMoniker_FWD_DEFINED__

#ifdef __cplusplus
typedef class GeometryMoniker GeometryMoniker;
#else
typedef struct GeometryMoniker GeometryMoniker;
#endif /* __cplusplus */

#endif 	/* __GeometryMoniker_FWD_DEFINED__ */


#ifndef __TRiASSpatialRelationService_FWD_DEFINED__
#define __TRiASSpatialRelationService_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASSpatialRelationService TRiASSpatialRelationService;
#else
typedef struct TRiASSpatialRelationService TRiASSpatialRelationService;
#endif /* __cplusplus */

#endif 	/* __TRiASSpatialRelationService_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_TDBGeo_0000 */
/* [local] */ 

#define TYPELIB_TDBGeo_VERSION_MAJOR 1
#define TYPELIB_TDBGeo_VERSION_MINOR 0
#define TYPELIB_TDBGeo_VERSION "1.0"
#define TYPELIB_TDBGeo_LCID 0
#pragma once
#pragma once
#pragma once
#pragma once




#define TYPELIB_TDBGEO_VERSION_MAJOR 1
#define TYPELIB_TDBGEO_VERSION_MINOR 0
#define TYPELIB_TDBGEO_VERSION "1.0"
#define TYPELIB_TDBGEO_LCID 0
#if !defined(_GEOMETRYTYPE_DEFINED)
#define _GEOMETRYTYPE_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagGEOMETRYTYPE
    {	GEOMETRYTYPE_Point	= 1,
	GEOMETRYTYPE_Line	= 2,
	GEOMETRYTYPE_Area	= 4,
	GEOMETRYTYPE_Text	= 8,
	GEOMETRYTYPE_OrientedPoint	= 0x10001,
	GEOMETRYTYPE_Boundary	= 0x10004,
	GEOMETRYTYPE_Collection	= 0x20000,
	GEOMETRYTYPE_Unknown	= 0,
	GEOMETRYTYPE_SimpleMask	= 0xffff
    } 	GEOMETRYTYPE;

#endif // _GEOMETRYTYPE_DEFINED


extern RPC_IF_HANDLE __MIDL_itf_TDBGeo_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_TDBGeo_0000_v0_0_s_ifspec;

#ifndef __ITRiASCSStorageService_INTERFACE_DEFINED__
#define __ITRiASCSStorageService_INTERFACE_DEFINED__

/* interface ITRiASCSStorageService */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASCSStorageService;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("80B9A2F5-02B0-11D2-8650-00600875138A")
    ITRiASCSStorageService : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StorageToGeometry( 
            /* [in] */ VARIANT Blob,
            /* [out][in] */ GEOMETRYTYPE *prgType,
            /* [retval][out] */ IDispatch **Geometry) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GeometryToStorage( 
            /* [in] */ GEOMETRYTYPE rgType,
            /* [in] */ IDispatch *Geometry,
            /* [retval][out] */ VARIANT *Blob) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RetrieveType( 
            /* [in] */ IDispatch *Geometry,
            /* [retval][out] */ GEOMETRYTYPE *prgType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StorageToObject( 
            /* [in] */ VARIANT Blob,
            /* [retval][out] */ IDispatch **Obj) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ObjectToStorage( 
            /* [in] */ IDispatch *Obj,
            /* [retval][out] */ VARIANT *Blob) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASCSStorageServiceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASCSStorageService * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASCSStorageService * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASCSStorageService * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASCSStorageService * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASCSStorageService * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASCSStorageService * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASCSStorageService * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StorageToGeometry )( 
            ITRiASCSStorageService * This,
            /* [in] */ VARIANT Blob,
            /* [out][in] */ GEOMETRYTYPE *prgType,
            /* [retval][out] */ IDispatch **Geometry);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GeometryToStorage )( 
            ITRiASCSStorageService * This,
            /* [in] */ GEOMETRYTYPE rgType,
            /* [in] */ IDispatch *Geometry,
            /* [retval][out] */ VARIANT *Blob);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RetrieveType )( 
            ITRiASCSStorageService * This,
            /* [in] */ IDispatch *Geometry,
            /* [retval][out] */ GEOMETRYTYPE *prgType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StorageToObject )( 
            ITRiASCSStorageService * This,
            /* [in] */ VARIANT Blob,
            /* [retval][out] */ IDispatch **Obj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ObjectToStorage )( 
            ITRiASCSStorageService * This,
            /* [in] */ IDispatch *Obj,
            /* [retval][out] */ VARIANT *Blob);
        
        END_INTERFACE
    } ITRiASCSStorageServiceVtbl;

    interface ITRiASCSStorageService
    {
        CONST_VTBL struct ITRiASCSStorageServiceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASCSStorageService_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASCSStorageService_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASCSStorageService_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASCSStorageService_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASCSStorageService_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASCSStorageService_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASCSStorageService_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASCSStorageService_StorageToGeometry(This,Blob,prgType,Geometry)	\
    (This)->lpVtbl -> StorageToGeometry(This,Blob,prgType,Geometry)

#define ITRiASCSStorageService_GeometryToStorage(This,rgType,Geometry,Blob)	\
    (This)->lpVtbl -> GeometryToStorage(This,rgType,Geometry,Blob)

#define ITRiASCSStorageService_RetrieveType(This,Geometry,prgType)	\
    (This)->lpVtbl -> RetrieveType(This,Geometry,prgType)

#define ITRiASCSStorageService_StorageToObject(This,Blob,Obj)	\
    (This)->lpVtbl -> StorageToObject(This,Blob,Obj)

#define ITRiASCSStorageService_ObjectToStorage(This,Obj,Blob)	\
    (This)->lpVtbl -> ObjectToStorage(This,Obj,Blob)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASCSStorageService_StorageToGeometry_Proxy( 
    ITRiASCSStorageService * This,
    /* [in] */ VARIANT Blob,
    /* [out][in] */ GEOMETRYTYPE *prgType,
    /* [retval][out] */ IDispatch **Geometry);


void __RPC_STUB ITRiASCSStorageService_StorageToGeometry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASCSStorageService_GeometryToStorage_Proxy( 
    ITRiASCSStorageService * This,
    /* [in] */ GEOMETRYTYPE rgType,
    /* [in] */ IDispatch *Geometry,
    /* [retval][out] */ VARIANT *Blob);


void __RPC_STUB ITRiASCSStorageService_GeometryToStorage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASCSStorageService_RetrieveType_Proxy( 
    ITRiASCSStorageService * This,
    /* [in] */ IDispatch *Geometry,
    /* [retval][out] */ GEOMETRYTYPE *prgType);


void __RPC_STUB ITRiASCSStorageService_RetrieveType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASCSStorageService_StorageToObject_Proxy( 
    ITRiASCSStorageService * This,
    /* [in] */ VARIANT Blob,
    /* [retval][out] */ IDispatch **Obj);


void __RPC_STUB ITRiASCSStorageService_StorageToObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASCSStorageService_ObjectToStorage_Proxy( 
    ITRiASCSStorageService * This,
    /* [in] */ IDispatch *Obj,
    /* [retval][out] */ VARIANT *Blob);


void __RPC_STUB ITRiASCSStorageService_ObjectToStorage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASCSStorageService_INTERFACE_DEFINED__ */


#ifndef __ITRiASCloneGeometry_INTERFACE_DEFINED__
#define __ITRiASCloneGeometry_INTERFACE_DEFINED__

/* interface ITRiASCloneGeometry */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASCloneGeometry;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BF10A784-5907-11D2-9ED2-006008447800")
    ITRiASCloneGeometry : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IDispatch **ClGeomOnedObj) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASCloneGeometryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASCloneGeometry * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASCloneGeometry * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASCloneGeometry * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASCloneGeometry * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASCloneGeometry * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASCloneGeometry * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASCloneGeometry * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ITRiASCloneGeometry * This,
            /* [retval][out] */ IDispatch **ClGeomOnedObj);
        
        END_INTERFACE
    } ITRiASCloneGeometryVtbl;

    interface ITRiASCloneGeometry
    {
        CONST_VTBL struct ITRiASCloneGeometryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASCloneGeometry_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASCloneGeometry_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASCloneGeometry_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASCloneGeometry_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASCloneGeometry_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASCloneGeometry_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASCloneGeometry_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASCloneGeometry_Clone(This,ClGeomOnedObj)	\
    (This)->lpVtbl -> Clone(This,ClGeomOnedObj)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASCloneGeometry_Clone_Proxy( 
    ITRiASCloneGeometry * This,
    /* [retval][out] */ IDispatch **ClGeomOnedObj);


void __RPC_STUB ITRiASCloneGeometry_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASCloneGeometry_INTERFACE_DEFINED__ */



#ifndef __TDBGEO_LIBRARY_DEFINED__
#define __TDBGEO_LIBRARY_DEFINED__

/* library TDBGEO */
/* [helpstring][version][lcid][uuid] */ 



EXTERN_C const IID LIBID_TDBGEO;

#ifndef __ITRiASSpatialRelationService_INTERFACE_DEFINED__
#define __ITRiASSpatialRelationService_INTERFACE_DEFINED__

/* interface ITRiASSpatialRelationService */
/* [unique][helpstring][dual][uuid][object] */ 

typedef /* [helpcontext][helpstring][v1_enum][public] */ 
enum _tagSPATIALRELATION
    {	SPATIALRELATION_Unknown	= 0,
	SPATIALRELATION_Equals	= 0x1,
	SPATIALRELATION_Touches	= 0x2,
	SPATIALRELATION_Contains	= 0x4,
	SPATIALRELATION_Within	= 0x8,
	SPATIALRELATION_Disjoint	= 0x10,
	SPATIALRELATION_Crosses	= 0x20,
	SPATIALRELATION_Overlaps	= 0x40,
	SPATIALRELATION_Intersects	= 0x80
    } 	SPATIALRELATION;


EXTERN_C const IID IID_ITRiASSpatialRelationService;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C80B64C7-B0D8-4D93-A124-DD8A864BA25B")
    ITRiASSpatialRelationService : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Equals( 
            /* [in] */ VARIANT CsOne,
            /* [in] */ IDispatch *GeomOne,
            /* [in] */ VARIANT CsTwo,
            /* [in] */ IDispatch *GeomTwo,
            /* [retval][out] */ VARIANT_BOOL *equals) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Touches( 
            /* [in] */ VARIANT CsOne,
            /* [in] */ IDispatch *GeomOne,
            /* [in] */ VARIANT CsTwo,
            /* [in] */ IDispatch *GeomTwo,
            /* [retval][out] */ VARIANT_BOOL *touches) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Contains( 
            /* [in] */ VARIANT CsOne,
            /* [in] */ IDispatch *GeomOne,
            /* [in] */ VARIANT CsTwo,
            /* [in] */ IDispatch *GeomTwo,
            /* [retval][out] */ VARIANT_BOOL *contains) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Within( 
            /* [in] */ VARIANT CsOne,
            /* [in] */ IDispatch *GeomOne,
            /* [in] */ VARIANT CsTwo,
            /* [in] */ IDispatch *GeomTwo,
            /* [retval][out] */ VARIANT_BOOL *within) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Disjoint( 
            /* [in] */ VARIANT CsOne,
            /* [in] */ IDispatch *GeomOne,
            /* [in] */ VARIANT CsTwo,
            /* [in] */ IDispatch *GeomTwo,
            /* [retval][out] */ VARIANT_BOOL *disjoint) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Crosses( 
            /* [in] */ VARIANT CsOne,
            /* [in] */ IDispatch *GeomOne,
            /* [in] */ VARIANT CsTwo,
            /* [in] */ IDispatch *GeomTwo,
            /* [retval][out] */ VARIANT_BOOL *crosses) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Overlaps( 
            /* [in] */ VARIANT CsOne,
            /* [in] */ IDispatch *GeomOne,
            /* [in] */ VARIANT CsTwo,
            /* [in] */ IDispatch *GeomTwo,
            /* [retval][out] */ VARIANT_BOOL *overlaps) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Intersects( 
            /* [in] */ VARIANT CsOne,
            /* [in] */ IDispatch *GeomOne,
            /* [in] */ VARIANT CsTwo,
            /* [in] */ IDispatch *GeomTwo,
            /* [retval][out] */ VARIANT_BOOL *intersects) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Relate( 
            /* [in] */ VARIANT CsOne,
            /* [in] */ IDispatch *GeomOne,
            /* [in] */ VARIANT CsTwo,
            /* [in] */ IDispatch *GeomTwo,
            /* [in] */ SPATIALRELATION Pattern,
            /* [retval][out] */ VARIANT_BOOL *isrelated) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSpatialRelation( 
            /* [in] */ VARIANT CsOne,
            /* [in] */ IDispatch *GeomOne,
            /* [in] */ VARIANT CsTwo,
            /* [in] */ IDispatch *GeomTwo,
            /* [retval][out] */ SPATIALRELATION *Pattern) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_TransformPipe( 
            /* [in] */ /* external definition not present */ ITRiASCSTransform *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TransformPipe( 
            /* [retval][out] */ /* external definition not present */ ITRiASCSTransform **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASSpatialRelationServiceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASSpatialRelationService * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASSpatialRelationService * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASSpatialRelationService * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASSpatialRelationService * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASSpatialRelationService * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASSpatialRelationService * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASSpatialRelationService * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Equals )( 
            ITRiASSpatialRelationService * This,
            /* [in] */ VARIANT CsOne,
            /* [in] */ IDispatch *GeomOne,
            /* [in] */ VARIANT CsTwo,
            /* [in] */ IDispatch *GeomTwo,
            /* [retval][out] */ VARIANT_BOOL *equals);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Touches )( 
            ITRiASSpatialRelationService * This,
            /* [in] */ VARIANT CsOne,
            /* [in] */ IDispatch *GeomOne,
            /* [in] */ VARIANT CsTwo,
            /* [in] */ IDispatch *GeomTwo,
            /* [retval][out] */ VARIANT_BOOL *touches);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Contains )( 
            ITRiASSpatialRelationService * This,
            /* [in] */ VARIANT CsOne,
            /* [in] */ IDispatch *GeomOne,
            /* [in] */ VARIANT CsTwo,
            /* [in] */ IDispatch *GeomTwo,
            /* [retval][out] */ VARIANT_BOOL *contains);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Within )( 
            ITRiASSpatialRelationService * This,
            /* [in] */ VARIANT CsOne,
            /* [in] */ IDispatch *GeomOne,
            /* [in] */ VARIANT CsTwo,
            /* [in] */ IDispatch *GeomTwo,
            /* [retval][out] */ VARIANT_BOOL *within);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Disjoint )( 
            ITRiASSpatialRelationService * This,
            /* [in] */ VARIANT CsOne,
            /* [in] */ IDispatch *GeomOne,
            /* [in] */ VARIANT CsTwo,
            /* [in] */ IDispatch *GeomTwo,
            /* [retval][out] */ VARIANT_BOOL *disjoint);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Crosses )( 
            ITRiASSpatialRelationService * This,
            /* [in] */ VARIANT CsOne,
            /* [in] */ IDispatch *GeomOne,
            /* [in] */ VARIANT CsTwo,
            /* [in] */ IDispatch *GeomTwo,
            /* [retval][out] */ VARIANT_BOOL *crosses);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Overlaps )( 
            ITRiASSpatialRelationService * This,
            /* [in] */ VARIANT CsOne,
            /* [in] */ IDispatch *GeomOne,
            /* [in] */ VARIANT CsTwo,
            /* [in] */ IDispatch *GeomTwo,
            /* [retval][out] */ VARIANT_BOOL *overlaps);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Intersects )( 
            ITRiASSpatialRelationService * This,
            /* [in] */ VARIANT CsOne,
            /* [in] */ IDispatch *GeomOne,
            /* [in] */ VARIANT CsTwo,
            /* [in] */ IDispatch *GeomTwo,
            /* [retval][out] */ VARIANT_BOOL *intersects);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Relate )( 
            ITRiASSpatialRelationService * This,
            /* [in] */ VARIANT CsOne,
            /* [in] */ IDispatch *GeomOne,
            /* [in] */ VARIANT CsTwo,
            /* [in] */ IDispatch *GeomTwo,
            /* [in] */ SPATIALRELATION Pattern,
            /* [retval][out] */ VARIANT_BOOL *isrelated);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSpatialRelation )( 
            ITRiASSpatialRelationService * This,
            /* [in] */ VARIANT CsOne,
            /* [in] */ IDispatch *GeomOne,
            /* [in] */ VARIANT CsTwo,
            /* [in] */ IDispatch *GeomTwo,
            /* [retval][out] */ SPATIALRELATION *Pattern);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_TransformPipe )( 
            ITRiASSpatialRelationService * This,
            /* [in] */ /* external definition not present */ ITRiASCSTransform *newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TransformPipe )( 
            ITRiASSpatialRelationService * This,
            /* [retval][out] */ /* external definition not present */ ITRiASCSTransform **pVal);
        
        END_INTERFACE
    } ITRiASSpatialRelationServiceVtbl;

    interface ITRiASSpatialRelationService
    {
        CONST_VTBL struct ITRiASSpatialRelationServiceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASSpatialRelationService_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASSpatialRelationService_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASSpatialRelationService_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASSpatialRelationService_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASSpatialRelationService_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASSpatialRelationService_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASSpatialRelationService_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASSpatialRelationService_Equals(This,CsOne,GeomOne,CsTwo,GeomTwo,equals)	\
    (This)->lpVtbl -> Equals(This,CsOne,GeomOne,CsTwo,GeomTwo,equals)

#define ITRiASSpatialRelationService_Touches(This,CsOne,GeomOne,CsTwo,GeomTwo,touches)	\
    (This)->lpVtbl -> Touches(This,CsOne,GeomOne,CsTwo,GeomTwo,touches)

#define ITRiASSpatialRelationService_Contains(This,CsOne,GeomOne,CsTwo,GeomTwo,contains)	\
    (This)->lpVtbl -> Contains(This,CsOne,GeomOne,CsTwo,GeomTwo,contains)

#define ITRiASSpatialRelationService_Within(This,CsOne,GeomOne,CsTwo,GeomTwo,within)	\
    (This)->lpVtbl -> Within(This,CsOne,GeomOne,CsTwo,GeomTwo,within)

#define ITRiASSpatialRelationService_Disjoint(This,CsOne,GeomOne,CsTwo,GeomTwo,disjoint)	\
    (This)->lpVtbl -> Disjoint(This,CsOne,GeomOne,CsTwo,GeomTwo,disjoint)

#define ITRiASSpatialRelationService_Crosses(This,CsOne,GeomOne,CsTwo,GeomTwo,crosses)	\
    (This)->lpVtbl -> Crosses(This,CsOne,GeomOne,CsTwo,GeomTwo,crosses)

#define ITRiASSpatialRelationService_Overlaps(This,CsOne,GeomOne,CsTwo,GeomTwo,overlaps)	\
    (This)->lpVtbl -> Overlaps(This,CsOne,GeomOne,CsTwo,GeomTwo,overlaps)

#define ITRiASSpatialRelationService_Intersects(This,CsOne,GeomOne,CsTwo,GeomTwo,intersects)	\
    (This)->lpVtbl -> Intersects(This,CsOne,GeomOne,CsTwo,GeomTwo,intersects)

#define ITRiASSpatialRelationService_Relate(This,CsOne,GeomOne,CsTwo,GeomTwo,Pattern,isrelated)	\
    (This)->lpVtbl -> Relate(This,CsOne,GeomOne,CsTwo,GeomTwo,Pattern,isrelated)

#define ITRiASSpatialRelationService_GetSpatialRelation(This,CsOne,GeomOne,CsTwo,GeomTwo,Pattern)	\
    (This)->lpVtbl -> GetSpatialRelation(This,CsOne,GeomOne,CsTwo,GeomTwo,Pattern)

#define ITRiASSpatialRelationService_putref_TransformPipe(This,newVal)	\
    (This)->lpVtbl -> putref_TransformPipe(This,newVal)

#define ITRiASSpatialRelationService_get_TransformPipe(This,pVal)	\
    (This)->lpVtbl -> get_TransformPipe(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASSpatialRelationService_Equals_Proxy( 
    ITRiASSpatialRelationService * This,
    /* [in] */ VARIANT CsOne,
    /* [in] */ IDispatch *GeomOne,
    /* [in] */ VARIANT CsTwo,
    /* [in] */ IDispatch *GeomTwo,
    /* [retval][out] */ VARIANT_BOOL *equals);


void __RPC_STUB ITRiASSpatialRelationService_Equals_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASSpatialRelationService_Touches_Proxy( 
    ITRiASSpatialRelationService * This,
    /* [in] */ VARIANT CsOne,
    /* [in] */ IDispatch *GeomOne,
    /* [in] */ VARIANT CsTwo,
    /* [in] */ IDispatch *GeomTwo,
    /* [retval][out] */ VARIANT_BOOL *touches);


void __RPC_STUB ITRiASSpatialRelationService_Touches_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASSpatialRelationService_Contains_Proxy( 
    ITRiASSpatialRelationService * This,
    /* [in] */ VARIANT CsOne,
    /* [in] */ IDispatch *GeomOne,
    /* [in] */ VARIANT CsTwo,
    /* [in] */ IDispatch *GeomTwo,
    /* [retval][out] */ VARIANT_BOOL *contains);


void __RPC_STUB ITRiASSpatialRelationService_Contains_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASSpatialRelationService_Within_Proxy( 
    ITRiASSpatialRelationService * This,
    /* [in] */ VARIANT CsOne,
    /* [in] */ IDispatch *GeomOne,
    /* [in] */ VARIANT CsTwo,
    /* [in] */ IDispatch *GeomTwo,
    /* [retval][out] */ VARIANT_BOOL *within);


void __RPC_STUB ITRiASSpatialRelationService_Within_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASSpatialRelationService_Disjoint_Proxy( 
    ITRiASSpatialRelationService * This,
    /* [in] */ VARIANT CsOne,
    /* [in] */ IDispatch *GeomOne,
    /* [in] */ VARIANT CsTwo,
    /* [in] */ IDispatch *GeomTwo,
    /* [retval][out] */ VARIANT_BOOL *disjoint);


void __RPC_STUB ITRiASSpatialRelationService_Disjoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASSpatialRelationService_Crosses_Proxy( 
    ITRiASSpatialRelationService * This,
    /* [in] */ VARIANT CsOne,
    /* [in] */ IDispatch *GeomOne,
    /* [in] */ VARIANT CsTwo,
    /* [in] */ IDispatch *GeomTwo,
    /* [retval][out] */ VARIANT_BOOL *crosses);


void __RPC_STUB ITRiASSpatialRelationService_Crosses_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASSpatialRelationService_Overlaps_Proxy( 
    ITRiASSpatialRelationService * This,
    /* [in] */ VARIANT CsOne,
    /* [in] */ IDispatch *GeomOne,
    /* [in] */ VARIANT CsTwo,
    /* [in] */ IDispatch *GeomTwo,
    /* [retval][out] */ VARIANT_BOOL *overlaps);


void __RPC_STUB ITRiASSpatialRelationService_Overlaps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASSpatialRelationService_Intersects_Proxy( 
    ITRiASSpatialRelationService * This,
    /* [in] */ VARIANT CsOne,
    /* [in] */ IDispatch *GeomOne,
    /* [in] */ VARIANT CsTwo,
    /* [in] */ IDispatch *GeomTwo,
    /* [retval][out] */ VARIANT_BOOL *intersects);


void __RPC_STUB ITRiASSpatialRelationService_Intersects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASSpatialRelationService_Relate_Proxy( 
    ITRiASSpatialRelationService * This,
    /* [in] */ VARIANT CsOne,
    /* [in] */ IDispatch *GeomOne,
    /* [in] */ VARIANT CsTwo,
    /* [in] */ IDispatch *GeomTwo,
    /* [in] */ SPATIALRELATION Pattern,
    /* [retval][out] */ VARIANT_BOOL *isrelated);


void __RPC_STUB ITRiASSpatialRelationService_Relate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASSpatialRelationService_GetSpatialRelation_Proxy( 
    ITRiASSpatialRelationService * This,
    /* [in] */ VARIANT CsOne,
    /* [in] */ IDispatch *GeomOne,
    /* [in] */ VARIANT CsTwo,
    /* [in] */ IDispatch *GeomTwo,
    /* [retval][out] */ SPATIALRELATION *Pattern);


void __RPC_STUB ITRiASSpatialRelationService_GetSpatialRelation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE ITRiASSpatialRelationService_putref_TransformPipe_Proxy( 
    ITRiASSpatialRelationService * This,
    /* [in] */ /* external definition not present */ ITRiASCSTransform *newVal);


void __RPC_STUB ITRiASSpatialRelationService_putref_TransformPipe_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSpatialRelationService_get_TransformPipe_Proxy( 
    ITRiASSpatialRelationService * This,
    /* [retval][out] */ /* external definition not present */ ITRiASCSTransform **pVal);


void __RPC_STUB ITRiASSpatialRelationService_get_TransformPipe_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASSpatialRelationService_INTERFACE_DEFINED__ */


#ifndef __IPersistMemoryGDO_INTERFACE_DEFINED__
#define __IPersistMemoryGDO_INTERFACE_DEFINED__

/* interface IPersistMemoryGDO */
/* [oleautomation][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPersistMemoryGDO;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("66BC9091-B4A0-11d2-98E0-0060085FC1CE")
    IPersistMemoryGDO : public IPersistMemory
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE LoadGDO( 
            /* [size_is][in] */ LPVOID pMem,
            /* [in] */ ULONG cbSize) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE SaveGDO( 
            /* [size_is][out] */ LPVOID pMem,
            /* [in] */ BOOL fClearDirty,
            /* [in] */ ULONG cbSize) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPersistMemoryGDOVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPersistMemoryGDO * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPersistMemoryGDO * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPersistMemoryGDO * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassID )( 
            IPersistMemoryGDO * This,
            /* [out] */ CLSID *pClassID);
        
        HRESULT ( STDMETHODCALLTYPE *IsDirty )( 
            IPersistMemoryGDO * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            IPersistMemoryGDO * This,
            /* [size_is][in] */ LPVOID pMem,
            /* [in] */ ULONG cbSize);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Save )( 
            IPersistMemoryGDO * This,
            /* [size_is][out] */ LPVOID pMem,
            /* [in] */ BOOL fClearDirty,
            /* [in] */ ULONG cbSize);
        
        HRESULT ( STDMETHODCALLTYPE *GetSizeMax )( 
            IPersistMemoryGDO * This,
            /* [out] */ ULONG *pCbSize);
        
        HRESULT ( STDMETHODCALLTYPE *InitNew )( 
            IPersistMemoryGDO * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *LoadGDO )( 
            IPersistMemoryGDO * This,
            /* [size_is][in] */ LPVOID pMem,
            /* [in] */ ULONG cbSize);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *SaveGDO )( 
            IPersistMemoryGDO * This,
            /* [size_is][out] */ LPVOID pMem,
            /* [in] */ BOOL fClearDirty,
            /* [in] */ ULONG cbSize);
        
        END_INTERFACE
    } IPersistMemoryGDOVtbl;

    interface IPersistMemoryGDO
    {
        CONST_VTBL struct IPersistMemoryGDOVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPersistMemoryGDO_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPersistMemoryGDO_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPersistMemoryGDO_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPersistMemoryGDO_GetClassID(This,pClassID)	\
    (This)->lpVtbl -> GetClassID(This,pClassID)


#define IPersistMemoryGDO_IsDirty(This)	\
    (This)->lpVtbl -> IsDirty(This)

#define IPersistMemoryGDO_Load(This,pMem,cbSize)	\
    (This)->lpVtbl -> Load(This,pMem,cbSize)

#define IPersistMemoryGDO_Save(This,pMem,fClearDirty,cbSize)	\
    (This)->lpVtbl -> Save(This,pMem,fClearDirty,cbSize)

#define IPersistMemoryGDO_GetSizeMax(This,pCbSize)	\
    (This)->lpVtbl -> GetSizeMax(This,pCbSize)

#define IPersistMemoryGDO_InitNew(This)	\
    (This)->lpVtbl -> InitNew(This)


#define IPersistMemoryGDO_LoadGDO(This,pMem,cbSize)	\
    (This)->lpVtbl -> LoadGDO(This,pMem,cbSize)

#define IPersistMemoryGDO_SaveGDO(This,pMem,fClearDirty,cbSize)	\
    (This)->lpVtbl -> SaveGDO(This,pMem,fClearDirty,cbSize)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [local] */ HRESULT STDMETHODCALLTYPE IPersistMemoryGDO_LoadGDO_Proxy( 
    IPersistMemoryGDO * This,
    /* [size_is][in] */ LPVOID pMem,
    /* [in] */ ULONG cbSize);


void __RPC_STUB IPersistMemoryGDO_LoadGDO_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [local] */ HRESULT STDMETHODCALLTYPE IPersistMemoryGDO_SaveGDO_Proxy( 
    IPersistMemoryGDO * This,
    /* [size_is][out] */ LPVOID pMem,
    /* [in] */ BOOL fClearDirty,
    /* [in] */ ULONG cbSize);


void __RPC_STUB IPersistMemoryGDO_SaveGDO_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPersistMemoryGDO_INTERFACE_DEFINED__ */


#ifndef __IPersistMemoryWks_INTERFACE_DEFINED__
#define __IPersistMemoryWks_INTERFACE_DEFINED__

/* interface IPersistMemoryWks */
/* [oleautomation][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPersistMemoryWks;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("97F2B75E-BDA5-4A5D-B14E-70824A7A94C8")
    IPersistMemoryWks : public IPersistMemoryGDO
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetSizeMaxWkb( 
            /* [out] */ ULONG *pulSize) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE LoadWkb( 
            /* [size_is][in] */ LPVOID pMem,
            /* [in] */ ULONG cbSize) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE SaveWkb( 
            /* [size_is][out] */ LPVOID pMem,
            /* [in] */ BOOL fClearDirty,
            /* [in] */ ULONG cbSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LoadWkt( 
            /* [in] */ BSTR WKT) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SaveWkt( 
            /* [out] */ BSTR *WKT,
            /* [in] */ BOOL fClearDirty) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPersistMemoryWksVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPersistMemoryWks * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPersistMemoryWks * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPersistMemoryWks * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassID )( 
            IPersistMemoryWks * This,
            /* [out] */ CLSID *pClassID);
        
        HRESULT ( STDMETHODCALLTYPE *IsDirty )( 
            IPersistMemoryWks * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            IPersistMemoryWks * This,
            /* [size_is][in] */ LPVOID pMem,
            /* [in] */ ULONG cbSize);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Save )( 
            IPersistMemoryWks * This,
            /* [size_is][out] */ LPVOID pMem,
            /* [in] */ BOOL fClearDirty,
            /* [in] */ ULONG cbSize);
        
        HRESULT ( STDMETHODCALLTYPE *GetSizeMax )( 
            IPersistMemoryWks * This,
            /* [out] */ ULONG *pCbSize);
        
        HRESULT ( STDMETHODCALLTYPE *InitNew )( 
            IPersistMemoryWks * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *LoadGDO )( 
            IPersistMemoryWks * This,
            /* [size_is][in] */ LPVOID pMem,
            /* [in] */ ULONG cbSize);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *SaveGDO )( 
            IPersistMemoryWks * This,
            /* [size_is][out] */ LPVOID pMem,
            /* [in] */ BOOL fClearDirty,
            /* [in] */ ULONG cbSize);
        
        HRESULT ( STDMETHODCALLTYPE *GetSizeMaxWkb )( 
            IPersistMemoryWks * This,
            /* [out] */ ULONG *pulSize);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *LoadWkb )( 
            IPersistMemoryWks * This,
            /* [size_is][in] */ LPVOID pMem,
            /* [in] */ ULONG cbSize);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *SaveWkb )( 
            IPersistMemoryWks * This,
            /* [size_is][out] */ LPVOID pMem,
            /* [in] */ BOOL fClearDirty,
            /* [in] */ ULONG cbSize);
        
        HRESULT ( STDMETHODCALLTYPE *LoadWkt )( 
            IPersistMemoryWks * This,
            /* [in] */ BSTR WKT);
        
        HRESULT ( STDMETHODCALLTYPE *SaveWkt )( 
            IPersistMemoryWks * This,
            /* [out] */ BSTR *WKT,
            /* [in] */ BOOL fClearDirty);
        
        END_INTERFACE
    } IPersistMemoryWksVtbl;

    interface IPersistMemoryWks
    {
        CONST_VTBL struct IPersistMemoryWksVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPersistMemoryWks_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPersistMemoryWks_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPersistMemoryWks_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPersistMemoryWks_GetClassID(This,pClassID)	\
    (This)->lpVtbl -> GetClassID(This,pClassID)


#define IPersistMemoryWks_IsDirty(This)	\
    (This)->lpVtbl -> IsDirty(This)

#define IPersistMemoryWks_Load(This,pMem,cbSize)	\
    (This)->lpVtbl -> Load(This,pMem,cbSize)

#define IPersistMemoryWks_Save(This,pMem,fClearDirty,cbSize)	\
    (This)->lpVtbl -> Save(This,pMem,fClearDirty,cbSize)

#define IPersistMemoryWks_GetSizeMax(This,pCbSize)	\
    (This)->lpVtbl -> GetSizeMax(This,pCbSize)

#define IPersistMemoryWks_InitNew(This)	\
    (This)->lpVtbl -> InitNew(This)


#define IPersistMemoryWks_LoadGDO(This,pMem,cbSize)	\
    (This)->lpVtbl -> LoadGDO(This,pMem,cbSize)

#define IPersistMemoryWks_SaveGDO(This,pMem,fClearDirty,cbSize)	\
    (This)->lpVtbl -> SaveGDO(This,pMem,fClearDirty,cbSize)


#define IPersistMemoryWks_GetSizeMaxWkb(This,pulSize)	\
    (This)->lpVtbl -> GetSizeMaxWkb(This,pulSize)

#define IPersistMemoryWks_LoadWkb(This,pMem,cbSize)	\
    (This)->lpVtbl -> LoadWkb(This,pMem,cbSize)

#define IPersistMemoryWks_SaveWkb(This,pMem,fClearDirty,cbSize)	\
    (This)->lpVtbl -> SaveWkb(This,pMem,fClearDirty,cbSize)

#define IPersistMemoryWks_LoadWkt(This,WKT)	\
    (This)->lpVtbl -> LoadWkt(This,WKT)

#define IPersistMemoryWks_SaveWkt(This,WKT,fClearDirty)	\
    (This)->lpVtbl -> SaveWkt(This,WKT,fClearDirty)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPersistMemoryWks_GetSizeMaxWkb_Proxy( 
    IPersistMemoryWks * This,
    /* [out] */ ULONG *pulSize);


void __RPC_STUB IPersistMemoryWks_GetSizeMaxWkb_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [local] */ HRESULT STDMETHODCALLTYPE IPersistMemoryWks_LoadWkb_Proxy( 
    IPersistMemoryWks * This,
    /* [size_is][in] */ LPVOID pMem,
    /* [in] */ ULONG cbSize);


void __RPC_STUB IPersistMemoryWks_LoadWkb_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [local] */ HRESULT STDMETHODCALLTYPE IPersistMemoryWks_SaveWkb_Proxy( 
    IPersistMemoryWks * This,
    /* [size_is][out] */ LPVOID pMem,
    /* [in] */ BOOL fClearDirty,
    /* [in] */ ULONG cbSize);


void __RPC_STUB IPersistMemoryWks_SaveWkb_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPersistMemoryWks_LoadWkt_Proxy( 
    IPersistMemoryWks * This,
    /* [in] */ BSTR WKT);


void __RPC_STUB IPersistMemoryWks_LoadWkt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPersistMemoryWks_SaveWkt_Proxy( 
    IPersistMemoryWks * This,
    /* [out] */ BSTR *WKT,
    /* [in] */ BOOL fClearDirty);


void __RPC_STUB IPersistMemoryWks_SaveWkt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPersistMemoryWks_INTERFACE_DEFINED__ */


#ifndef __ITRiASCSStorageServiceGDO_INTERFACE_DEFINED__
#define __ITRiASCSStorageServiceGDO_INTERFACE_DEFINED__

/* interface ITRiASCSStorageServiceGDO */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASCSStorageServiceGDO;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("66BC9090-B4A0-11d2-98E0-0060085FC1CE")
    ITRiASCSStorageServiceGDO : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StorageToGeometryGDO( 
            /* [in] */ VARIANT Blob,
            /* [out][in] */ GEOMETRYTYPE *prgType,
            /* [retval][out] */ IDispatch **Geometry) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GeometryToStorageGDO( 
            /* [in] */ GEOMETRYTYPE rgType,
            /* [in] */ IDispatch *Geometry,
            /* [retval][out] */ VARIANT *Blob) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RetrieveType( 
            /* [in] */ IDispatch *Geometry,
            /* [retval][out] */ GEOMETRYTYPE *prgType) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASCSStorageServiceGDOVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASCSStorageServiceGDO * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASCSStorageServiceGDO * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASCSStorageServiceGDO * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASCSStorageServiceGDO * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASCSStorageServiceGDO * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASCSStorageServiceGDO * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASCSStorageServiceGDO * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StorageToGeometryGDO )( 
            ITRiASCSStorageServiceGDO * This,
            /* [in] */ VARIANT Blob,
            /* [out][in] */ GEOMETRYTYPE *prgType,
            /* [retval][out] */ IDispatch **Geometry);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GeometryToStorageGDO )( 
            ITRiASCSStorageServiceGDO * This,
            /* [in] */ GEOMETRYTYPE rgType,
            /* [in] */ IDispatch *Geometry,
            /* [retval][out] */ VARIANT *Blob);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RetrieveType )( 
            ITRiASCSStorageServiceGDO * This,
            /* [in] */ IDispatch *Geometry,
            /* [retval][out] */ GEOMETRYTYPE *prgType);
        
        END_INTERFACE
    } ITRiASCSStorageServiceGDOVtbl;

    interface ITRiASCSStorageServiceGDO
    {
        CONST_VTBL struct ITRiASCSStorageServiceGDOVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASCSStorageServiceGDO_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASCSStorageServiceGDO_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASCSStorageServiceGDO_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASCSStorageServiceGDO_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASCSStorageServiceGDO_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASCSStorageServiceGDO_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASCSStorageServiceGDO_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASCSStorageServiceGDO_StorageToGeometryGDO(This,Blob,prgType,Geometry)	\
    (This)->lpVtbl -> StorageToGeometryGDO(This,Blob,prgType,Geometry)

#define ITRiASCSStorageServiceGDO_GeometryToStorageGDO(This,rgType,Geometry,Blob)	\
    (This)->lpVtbl -> GeometryToStorageGDO(This,rgType,Geometry,Blob)

#define ITRiASCSStorageServiceGDO_RetrieveType(This,Geometry,prgType)	\
    (This)->lpVtbl -> RetrieveType(This,Geometry,prgType)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASCSStorageServiceGDO_StorageToGeometryGDO_Proxy( 
    ITRiASCSStorageServiceGDO * This,
    /* [in] */ VARIANT Blob,
    /* [out][in] */ GEOMETRYTYPE *prgType,
    /* [retval][out] */ IDispatch **Geometry);


void __RPC_STUB ITRiASCSStorageServiceGDO_StorageToGeometryGDO_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASCSStorageServiceGDO_GeometryToStorageGDO_Proxy( 
    ITRiASCSStorageServiceGDO * This,
    /* [in] */ GEOMETRYTYPE rgType,
    /* [in] */ IDispatch *Geometry,
    /* [retval][out] */ VARIANT *Blob);


void __RPC_STUB ITRiASCSStorageServiceGDO_GeometryToStorageGDO_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASCSStorageServiceGDO_RetrieveType_Proxy( 
    ITRiASCSStorageServiceGDO * This,
    /* [in] */ IDispatch *Geometry,
    /* [retval][out] */ GEOMETRYTYPE *prgType);


void __RPC_STUB ITRiASCSStorageServiceGDO_RetrieveType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASCSStorageServiceGDO_INTERFACE_DEFINED__ */


#ifndef __ITRiASCSStorageServiceWks_INTERFACE_DEFINED__
#define __ITRiASCSStorageServiceWks_INTERFACE_DEFINED__

/* interface ITRiASCSStorageServiceWks */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASCSStorageServiceWks;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A8C0586B-70AE-4E2F-822F-2C74C2069A26")
    ITRiASCSStorageServiceWks : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StorageToGeometryWkb( 
            /* [in] */ VARIANT Blob,
            /* [out][in] */ GEOMETRYTYPE *prgType,
            /* [retval][out] */ IDispatch **Geometry) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GeometryToStorageWkb( 
            /* [in] */ GEOMETRYTYPE rgType,
            /* [in] */ IDispatch *Geometry,
            /* [retval][out] */ VARIANT *Blob) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StorageToGeometryWkt( 
            /* [in] */ BSTR Wkt,
            /* [out][in] */ GEOMETRYTYPE *prgType,
            /* [retval][out] */ IDispatch **Geometry) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GeometryToStorageWkt( 
            /* [in] */ GEOMETRYTYPE rgType,
            /* [in] */ IDispatch *Geometry,
            /* [retval][out] */ BSTR *Wkt) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RetrieveType( 
            /* [in] */ IDispatch *Geometry,
            /* [retval][out] */ GEOMETRYTYPE *prgType) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASCSStorageServiceWksVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASCSStorageServiceWks * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASCSStorageServiceWks * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASCSStorageServiceWks * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASCSStorageServiceWks * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASCSStorageServiceWks * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASCSStorageServiceWks * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASCSStorageServiceWks * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StorageToGeometryWkb )( 
            ITRiASCSStorageServiceWks * This,
            /* [in] */ VARIANT Blob,
            /* [out][in] */ GEOMETRYTYPE *prgType,
            /* [retval][out] */ IDispatch **Geometry);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GeometryToStorageWkb )( 
            ITRiASCSStorageServiceWks * This,
            /* [in] */ GEOMETRYTYPE rgType,
            /* [in] */ IDispatch *Geometry,
            /* [retval][out] */ VARIANT *Blob);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StorageToGeometryWkt )( 
            ITRiASCSStorageServiceWks * This,
            /* [in] */ BSTR Wkt,
            /* [out][in] */ GEOMETRYTYPE *prgType,
            /* [retval][out] */ IDispatch **Geometry);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GeometryToStorageWkt )( 
            ITRiASCSStorageServiceWks * This,
            /* [in] */ GEOMETRYTYPE rgType,
            /* [in] */ IDispatch *Geometry,
            /* [retval][out] */ BSTR *Wkt);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RetrieveType )( 
            ITRiASCSStorageServiceWks * This,
            /* [in] */ IDispatch *Geometry,
            /* [retval][out] */ GEOMETRYTYPE *prgType);
        
        END_INTERFACE
    } ITRiASCSStorageServiceWksVtbl;

    interface ITRiASCSStorageServiceWks
    {
        CONST_VTBL struct ITRiASCSStorageServiceWksVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASCSStorageServiceWks_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASCSStorageServiceWks_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASCSStorageServiceWks_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASCSStorageServiceWks_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASCSStorageServiceWks_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASCSStorageServiceWks_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASCSStorageServiceWks_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASCSStorageServiceWks_StorageToGeometryWkb(This,Blob,prgType,Geometry)	\
    (This)->lpVtbl -> StorageToGeometryWkb(This,Blob,prgType,Geometry)

#define ITRiASCSStorageServiceWks_GeometryToStorageWkb(This,rgType,Geometry,Blob)	\
    (This)->lpVtbl -> GeometryToStorageWkb(This,rgType,Geometry,Blob)

#define ITRiASCSStorageServiceWks_StorageToGeometryWkt(This,Wkt,prgType,Geometry)	\
    (This)->lpVtbl -> StorageToGeometryWkt(This,Wkt,prgType,Geometry)

#define ITRiASCSStorageServiceWks_GeometryToStorageWkt(This,rgType,Geometry,Wkt)	\
    (This)->lpVtbl -> GeometryToStorageWkt(This,rgType,Geometry,Wkt)

#define ITRiASCSStorageServiceWks_RetrieveType(This,Geometry,prgType)	\
    (This)->lpVtbl -> RetrieveType(This,Geometry,prgType)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASCSStorageServiceWks_StorageToGeometryWkb_Proxy( 
    ITRiASCSStorageServiceWks * This,
    /* [in] */ VARIANT Blob,
    /* [out][in] */ GEOMETRYTYPE *prgType,
    /* [retval][out] */ IDispatch **Geometry);


void __RPC_STUB ITRiASCSStorageServiceWks_StorageToGeometryWkb_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASCSStorageServiceWks_GeometryToStorageWkb_Proxy( 
    ITRiASCSStorageServiceWks * This,
    /* [in] */ GEOMETRYTYPE rgType,
    /* [in] */ IDispatch *Geometry,
    /* [retval][out] */ VARIANT *Blob);


void __RPC_STUB ITRiASCSStorageServiceWks_GeometryToStorageWkb_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASCSStorageServiceWks_StorageToGeometryWkt_Proxy( 
    ITRiASCSStorageServiceWks * This,
    /* [in] */ BSTR Wkt,
    /* [out][in] */ GEOMETRYTYPE *prgType,
    /* [retval][out] */ IDispatch **Geometry);


void __RPC_STUB ITRiASCSStorageServiceWks_StorageToGeometryWkt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASCSStorageServiceWks_GeometryToStorageWkt_Proxy( 
    ITRiASCSStorageServiceWks * This,
    /* [in] */ GEOMETRYTYPE rgType,
    /* [in] */ IDispatch *Geometry,
    /* [retval][out] */ BSTR *Wkt);


void __RPC_STUB ITRiASCSStorageServiceWks_GeometryToStorageWkt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASCSStorageServiceWks_RetrieveType_Proxy( 
    ITRiASCSStorageServiceWks * This,
    /* [in] */ IDispatch *Geometry,
    /* [retval][out] */ GEOMETRYTYPE *prgType);


void __RPC_STUB ITRiASCSStorageServiceWks_RetrieveType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASCSStorageServiceWks_INTERFACE_DEFINED__ */


#ifndef __ITRiASSimpleRectangle_INTERFACE_DEFINED__
#define __ITRiASSimpleRectangle_INTERFACE_DEFINED__

/* interface ITRiASSimpleRectangle */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_ITRiASSimpleRectangle;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3EFE0E50-8003-11d2-9870-0060085FC1CE")
    ITRiASSimpleRectangle : public _DGMRectangleGeometry
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XMin( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_XMin( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_YMin( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_YMin( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ZMin( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ZMin( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XMax( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_XMax( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_YMax( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_YMax( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ZMax( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ZMax( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRect( 
            /* [out] */ double *pValXMin,
            /* [out] */ double *pValYMin,
            /* [out] */ double *pValXMax,
            /* [out] */ double *pValYMax) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetRect( 
            /* [in] */ double newValXMin,
            /* [in] */ double newValYMin,
            /* [in] */ double newValXMax,
            /* [in] */ double newValYMax) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASSimpleRectangleVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASSimpleRectangle * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [out][idldescattr] */ void **ppvObj,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASSimpleRectangle * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Release )( 
            ITRiASSimpleRectangle * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASSimpleRectangle * This,
            /* [out][idldescattr] */ unsigned UINT *pctinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASSimpleRectangle * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void **pptinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASSimpleRectangle * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ signed char **rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long *rgdispid,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASSimpleRectangle * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ struct DISPPARAMS *pdispparams,
            /* [out][idldescattr] */ VARIANT *pvarResult,
            /* [out][idldescattr] */ struct EXCEPINFO *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT *puArgErr,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            ITRiASSimpleRectangle * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            ITRiASSimpleRectangle * This,
            /* [retval][out] */ double *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Width )( 
            ITRiASSimpleRectangle * This,
            /* [in][idldescattr] */ double noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Height )( 
            ITRiASSimpleRectangle * This,
            /* [retval][out] */ double *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Height )( 
            ITRiASSimpleRectangle * This,
            /* [in][idldescattr] */ double noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Rotation )( 
            ITRiASSimpleRectangle * This,
            /* [retval][out] */ double *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Rotation )( 
            ITRiASSimpleRectangle * This,
            /* [in][idldescattr] */ double noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Origin )( 
            ITRiASSimpleRectangle * This,
            /* [retval][out] */ **retval);
        
        /* [id][propputref][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *putref_Origin )( 
            ITRiASSimpleRectangle * This,
            /* [in][idldescattr] */ point	*noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Normal )( 
            ITRiASSimpleRectangle * This,
            /* [retval][out] */ **retval);
        
        /* [id][propputref][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *putref_Normal )( 
            ITRiASSimpleRectangle * This,
            /* [in][idldescattr] */ Vector	*noname,
            /* [retval][out] */ void *retval);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XMin )( 
            ITRiASSimpleRectangle * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_XMin )( 
            ITRiASSimpleRectangle * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_YMin )( 
            ITRiASSimpleRectangle * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_YMin )( 
            ITRiASSimpleRectangle * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ZMin )( 
            ITRiASSimpleRectangle * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ZMin )( 
            ITRiASSimpleRectangle * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XMax )( 
            ITRiASSimpleRectangle * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_XMax )( 
            ITRiASSimpleRectangle * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_YMax )( 
            ITRiASSimpleRectangle * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_YMax )( 
            ITRiASSimpleRectangle * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ZMax )( 
            ITRiASSimpleRectangle * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ZMax )( 
            ITRiASSimpleRectangle * This,
            /* [in] */ double newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetRect )( 
            ITRiASSimpleRectangle * This,
            /* [out] */ double *pValXMin,
            /* [out] */ double *pValYMin,
            /* [out] */ double *pValXMax,
            /* [out] */ double *pValYMax);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetRect )( 
            ITRiASSimpleRectangle * This,
            /* [in] */ double newValXMin,
            /* [in] */ double newValYMin,
            /* [in] */ double newValXMax,
            /* [in] */ double newValYMax);
        
        END_INTERFACE
    } ITRiASSimpleRectangleVtbl;

    interface ITRiASSimpleRectangle
    {
        CONST_VTBL struct ITRiASSimpleRectangleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASSimpleRectangle_QueryInterface(This,riid,ppvObj,retval)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval)

#define ITRiASSimpleRectangle_AddRef(This,retval)	\
    (This)->lpVtbl -> AddRef(This,retval)

#define ITRiASSimpleRectangle_Release(This,retval)	\
    (This)->lpVtbl -> Release(This,retval)

#define ITRiASSimpleRectangle_GetTypeInfoCount(This,pctinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval)

#define ITRiASSimpleRectangle_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval)

#define ITRiASSimpleRectangle_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)

#define ITRiASSimpleRectangle_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)

#define ITRiASSimpleRectangle_get_Type(This,retval)	\
    (This)->lpVtbl -> get_Type(This,retval)

#define ITRiASSimpleRectangle_get_Width(This,retval)	\
    (This)->lpVtbl -> get_Width(This,retval)

#define ITRiASSimpleRectangle_put_Width(This,noname,retval)	\
    (This)->lpVtbl -> put_Width(This,noname,retval)

#define ITRiASSimpleRectangle_get_Height(This,retval)	\
    (This)->lpVtbl -> get_Height(This,retval)

#define ITRiASSimpleRectangle_put_Height(This,noname,retval)	\
    (This)->lpVtbl -> put_Height(This,noname,retval)

#define ITRiASSimpleRectangle_get_Rotation(This,retval)	\
    (This)->lpVtbl -> get_Rotation(This,retval)

#define ITRiASSimpleRectangle_put_Rotation(This,noname,retval)	\
    (This)->lpVtbl -> put_Rotation(This,noname,retval)

#define ITRiASSimpleRectangle_get_Origin(This,retval)	\
    (This)->lpVtbl -> get_Origin(This,retval)

#define ITRiASSimpleRectangle_putref_Origin(This,noname,retval)	\
    (This)->lpVtbl -> putref_Origin(This,noname,retval)

#define ITRiASSimpleRectangle_get_Normal(This,retval)	\
    (This)->lpVtbl -> get_Normal(This,retval)

#define ITRiASSimpleRectangle_putref_Normal(This,noname,retval)	\
    (This)->lpVtbl -> putref_Normal(This,noname,retval)


#define ITRiASSimpleRectangle_get_XMin(This,pVal)	\
    (This)->lpVtbl -> get_XMin(This,pVal)

#define ITRiASSimpleRectangle_put_XMin(This,newVal)	\
    (This)->lpVtbl -> put_XMin(This,newVal)

#define ITRiASSimpleRectangle_get_YMin(This,pVal)	\
    (This)->lpVtbl -> get_YMin(This,pVal)

#define ITRiASSimpleRectangle_put_YMin(This,newVal)	\
    (This)->lpVtbl -> put_YMin(This,newVal)

#define ITRiASSimpleRectangle_get_ZMin(This,pVal)	\
    (This)->lpVtbl -> get_ZMin(This,pVal)

#define ITRiASSimpleRectangle_put_ZMin(This,newVal)	\
    (This)->lpVtbl -> put_ZMin(This,newVal)

#define ITRiASSimpleRectangle_get_XMax(This,pVal)	\
    (This)->lpVtbl -> get_XMax(This,pVal)

#define ITRiASSimpleRectangle_put_XMax(This,newVal)	\
    (This)->lpVtbl -> put_XMax(This,newVal)

#define ITRiASSimpleRectangle_get_YMax(This,pVal)	\
    (This)->lpVtbl -> get_YMax(This,pVal)

#define ITRiASSimpleRectangle_put_YMax(This,newVal)	\
    (This)->lpVtbl -> put_YMax(This,newVal)

#define ITRiASSimpleRectangle_get_ZMax(This,pVal)	\
    (This)->lpVtbl -> get_ZMax(This,pVal)

#define ITRiASSimpleRectangle_put_ZMax(This,newVal)	\
    (This)->lpVtbl -> put_ZMax(This,newVal)

#define ITRiASSimpleRectangle_GetRect(This,pValXMin,pValYMin,pValXMax,pValYMax)	\
    (This)->lpVtbl -> GetRect(This,pValXMin,pValYMin,pValXMax,pValYMax)

#define ITRiASSimpleRectangle_SetRect(This,newValXMin,newValYMin,newValXMax,newValYMax)	\
    (This)->lpVtbl -> SetRect(This,newValXMin,newValYMin,newValXMax,newValYMax)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleRectangle_get_XMin_Proxy( 
    ITRiASSimpleRectangle * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB ITRiASSimpleRectangle_get_XMin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleRectangle_put_XMin_Proxy( 
    ITRiASSimpleRectangle * This,
    /* [in] */ double newVal);


void __RPC_STUB ITRiASSimpleRectangle_put_XMin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleRectangle_get_YMin_Proxy( 
    ITRiASSimpleRectangle * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB ITRiASSimpleRectangle_get_YMin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleRectangle_put_YMin_Proxy( 
    ITRiASSimpleRectangle * This,
    /* [in] */ double newVal);


void __RPC_STUB ITRiASSimpleRectangle_put_YMin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleRectangle_get_ZMin_Proxy( 
    ITRiASSimpleRectangle * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB ITRiASSimpleRectangle_get_ZMin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleRectangle_put_ZMin_Proxy( 
    ITRiASSimpleRectangle * This,
    /* [in] */ double newVal);


void __RPC_STUB ITRiASSimpleRectangle_put_ZMin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleRectangle_get_XMax_Proxy( 
    ITRiASSimpleRectangle * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB ITRiASSimpleRectangle_get_XMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleRectangle_put_XMax_Proxy( 
    ITRiASSimpleRectangle * This,
    /* [in] */ double newVal);


void __RPC_STUB ITRiASSimpleRectangle_put_XMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleRectangle_get_YMax_Proxy( 
    ITRiASSimpleRectangle * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB ITRiASSimpleRectangle_get_YMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleRectangle_put_YMax_Proxy( 
    ITRiASSimpleRectangle * This,
    /* [in] */ double newVal);


void __RPC_STUB ITRiASSimpleRectangle_put_YMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleRectangle_get_ZMax_Proxy( 
    ITRiASSimpleRectangle * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB ITRiASSimpleRectangle_get_ZMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleRectangle_put_ZMax_Proxy( 
    ITRiASSimpleRectangle * This,
    /* [in] */ double newVal);


void __RPC_STUB ITRiASSimpleRectangle_put_ZMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleRectangle_GetRect_Proxy( 
    ITRiASSimpleRectangle * This,
    /* [out] */ double *pValXMin,
    /* [out] */ double *pValYMin,
    /* [out] */ double *pValXMax,
    /* [out] */ double *pValYMax);


void __RPC_STUB ITRiASSimpleRectangle_GetRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleRectangle_SetRect_Proxy( 
    ITRiASSimpleRectangle * This,
    /* [in] */ double newValXMin,
    /* [in] */ double newValYMin,
    /* [in] */ double newValXMax,
    /* [in] */ double newValYMax);


void __RPC_STUB ITRiASSimpleRectangle_SetRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASSimpleRectangle_INTERFACE_DEFINED__ */


#ifndef __ITRiASCSGeometryProperties_INTERFACE_DEFINED__
#define __ITRiASCSGeometryProperties_INTERFACE_DEFINED__

/* interface ITRiASCSGeometryProperties */
/* [unique][helpstring][uuid][dual][object] */ 


EXTERN_C const IID IID_ITRiASCSGeometryProperties;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CBC5D024-03AF-11D2-8651-00600875138A")
    ITRiASCSGeometryProperties : public ITRiASCloneGeometry
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ GEOMETRYTYPE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Envelope( 
            /* [retval][out] */ ITRiASSimpleRectangle **Rect) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InitString( 
            /* [retval][out] */ BSTR *pbstrMkName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_InitString( 
            /* [in] */ BSTR bstrMkName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASCSGeometryPropertiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASCSGeometryProperties * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASCSGeometryProperties * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASCSGeometryProperties * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASCSGeometryProperties * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASCSGeometryProperties * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASCSGeometryProperties * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASCSGeometryProperties * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ITRiASCSGeometryProperties * This,
            /* [retval][out] */ IDispatch **ClGeomOnedObj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            ITRiASCSGeometryProperties * This,
            /* [retval][out] */ GEOMETRYTYPE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Envelope )( 
            ITRiASCSGeometryProperties * This,
            /* [retval][out] */ ITRiASSimpleRectangle **Rect);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InitString )( 
            ITRiASCSGeometryProperties * This,
            /* [retval][out] */ BSTR *pbstrMkName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InitString )( 
            ITRiASCSGeometryProperties * This,
            /* [in] */ BSTR bstrMkName);
        
        END_INTERFACE
    } ITRiASCSGeometryPropertiesVtbl;

    interface ITRiASCSGeometryProperties
    {
        CONST_VTBL struct ITRiASCSGeometryPropertiesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASCSGeometryProperties_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASCSGeometryProperties_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASCSGeometryProperties_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASCSGeometryProperties_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASCSGeometryProperties_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASCSGeometryProperties_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASCSGeometryProperties_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASCSGeometryProperties_Clone(This,ClGeomOnedObj)	\
    (This)->lpVtbl -> Clone(This,ClGeomOnedObj)


#define ITRiASCSGeometryProperties_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define ITRiASCSGeometryProperties_get_Envelope(This,Rect)	\
    (This)->lpVtbl -> get_Envelope(This,Rect)

#define ITRiASCSGeometryProperties_get_InitString(This,pbstrMkName)	\
    (This)->lpVtbl -> get_InitString(This,pbstrMkName)

#define ITRiASCSGeometryProperties_put_InitString(This,bstrMkName)	\
    (This)->lpVtbl -> put_InitString(This,bstrMkName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASCSGeometryProperties_get_Type_Proxy( 
    ITRiASCSGeometryProperties * This,
    /* [retval][out] */ GEOMETRYTYPE *pVal);


void __RPC_STUB ITRiASCSGeometryProperties_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASCSGeometryProperties_get_Envelope_Proxy( 
    ITRiASCSGeometryProperties * This,
    /* [retval][out] */ ITRiASSimpleRectangle **Rect);


void __RPC_STUB ITRiASCSGeometryProperties_get_Envelope_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASCSGeometryProperties_get_InitString_Proxy( 
    ITRiASCSGeometryProperties * This,
    /* [retval][out] */ BSTR *pbstrMkName);


void __RPC_STUB ITRiASCSGeometryProperties_get_InitString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASCSGeometryProperties_put_InitString_Proxy( 
    ITRiASCSGeometryProperties * This,
    /* [in] */ BSTR bstrMkName);


void __RPC_STUB ITRiASCSGeometryProperties_put_InitString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASCSGeometryProperties_INTERFACE_DEFINED__ */


#ifndef __ITRiASSimplePoint_INTERFACE_DEFINED__
#define __ITRiASSimplePoint_INTERFACE_DEFINED__

/* interface ITRiASSimplePoint */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_ITRiASSimplePoint;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("809D42DF-ECB5-47E4-8DBE-2F59EE0546B5")
    ITRiASSimplePoint : public _DGMPointGeometry
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPoint( 
            /* [out] */ double *pVals) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetPoint( 
            /* [in] */ double *pVals) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_X( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_X( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Y( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Y( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Z( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Z( 
            /* [in] */ double newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASSimplePointVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASSimplePoint * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [out][idldescattr] */ void **ppvObj,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASSimplePoint * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Release )( 
            ITRiASSimplePoint * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASSimplePoint * This,
            /* [out][idldescattr] */ unsigned UINT *pctinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASSimplePoint * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void **pptinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASSimplePoint * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ signed char **rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long *rgdispid,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASSimplePoint * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ struct DISPPARAMS *pdispparams,
            /* [out][idldescattr] */ VARIANT *pvarResult,
            /* [out][idldescattr] */ struct EXCEPINFO *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT *puArgErr,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            ITRiASSimplePoint * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Origin )( 
            ITRiASSimplePoint * This,
            /* [retval][out] */ **retval);
        
        /* [id][propputref][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *putref_Origin )( 
            ITRiASSimplePoint * This,
            /* [in][idldescattr] */ point	*noname,
            /* [retval][out] */ void *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPoint )( 
            ITRiASSimplePoint * This,
            /* [out] */ double *pVals);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetPoint )( 
            ITRiASSimplePoint * This,
            /* [in] */ double *pVals);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_X )( 
            ITRiASSimplePoint * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_X )( 
            ITRiASSimplePoint * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Y )( 
            ITRiASSimplePoint * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Y )( 
            ITRiASSimplePoint * This,
            /* [in] */ double newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Z )( 
            ITRiASSimplePoint * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Z )( 
            ITRiASSimplePoint * This,
            /* [in] */ double newVal);
        
        END_INTERFACE
    } ITRiASSimplePointVtbl;

    interface ITRiASSimplePoint
    {
        CONST_VTBL struct ITRiASSimplePointVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASSimplePoint_QueryInterface(This,riid,ppvObj,retval)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval)

#define ITRiASSimplePoint_AddRef(This,retval)	\
    (This)->lpVtbl -> AddRef(This,retval)

#define ITRiASSimplePoint_Release(This,retval)	\
    (This)->lpVtbl -> Release(This,retval)

#define ITRiASSimplePoint_GetTypeInfoCount(This,pctinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval)

#define ITRiASSimplePoint_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval)

#define ITRiASSimplePoint_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)

#define ITRiASSimplePoint_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)

#define ITRiASSimplePoint_get_Type(This,retval)	\
    (This)->lpVtbl -> get_Type(This,retval)

#define ITRiASSimplePoint_get_Origin(This,retval)	\
    (This)->lpVtbl -> get_Origin(This,retval)

#define ITRiASSimplePoint_putref_Origin(This,noname,retval)	\
    (This)->lpVtbl -> putref_Origin(This,noname,retval)


#define ITRiASSimplePoint_GetPoint(This,pVals)	\
    (This)->lpVtbl -> GetPoint(This,pVals)

#define ITRiASSimplePoint_SetPoint(This,pVals)	\
    (This)->lpVtbl -> SetPoint(This,pVals)

#define ITRiASSimplePoint_get_X(This,pVal)	\
    (This)->lpVtbl -> get_X(This,pVal)

#define ITRiASSimplePoint_put_X(This,newVal)	\
    (This)->lpVtbl -> put_X(This,newVal)

#define ITRiASSimplePoint_get_Y(This,pVal)	\
    (This)->lpVtbl -> get_Y(This,pVal)

#define ITRiASSimplePoint_put_Y(This,newVal)	\
    (This)->lpVtbl -> put_Y(This,newVal)

#define ITRiASSimplePoint_get_Z(This,pVal)	\
    (This)->lpVtbl -> get_Z(This,pVal)

#define ITRiASSimplePoint_put_Z(This,newVal)	\
    (This)->lpVtbl -> put_Z(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASSimplePoint_GetPoint_Proxy( 
    ITRiASSimplePoint * This,
    /* [out] */ double *pVals);


void __RPC_STUB ITRiASSimplePoint_GetPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASSimplePoint_SetPoint_Proxy( 
    ITRiASSimplePoint * This,
    /* [in] */ double *pVals);


void __RPC_STUB ITRiASSimplePoint_SetPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSimplePoint_get_X_Proxy( 
    ITRiASSimplePoint * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB ITRiASSimplePoint_get_X_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ITRiASSimplePoint_put_X_Proxy( 
    ITRiASSimplePoint * This,
    /* [in] */ double newVal);


void __RPC_STUB ITRiASSimplePoint_put_X_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSimplePoint_get_Y_Proxy( 
    ITRiASSimplePoint * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB ITRiASSimplePoint_get_Y_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ITRiASSimplePoint_put_Y_Proxy( 
    ITRiASSimplePoint * This,
    /* [in] */ double newVal);


void __RPC_STUB ITRiASSimplePoint_put_Y_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSimplePoint_get_Z_Proxy( 
    ITRiASSimplePoint * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB ITRiASSimplePoint_get_Z_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ITRiASSimplePoint_put_Z_Proxy( 
    ITRiASSimplePoint * This,
    /* [in] */ double newVal);


void __RPC_STUB ITRiASSimplePoint_put_Z_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASSimplePoint_INTERFACE_DEFINED__ */


#ifndef __ITRiASSimplePoints_INTERFACE_DEFINED__
#define __ITRiASSimplePoints_INTERFACE_DEFINED__

/* interface ITRiASSimplePoints */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_ITRiASSimplePoints;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("09E3D3D3-E334-43A0-803D-9B086F730EE5")
    ITRiASSimplePoints : public _DGMPoints
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPoints( 
            /* [in] */ ULONG lFirst,
            /* [in] */ ULONG nCoords,
            /* [size_is][out][in] */ double *Coords) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASSimplePointsVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASSimplePoints * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [out][idldescattr] */ void **ppvObj,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASSimplePoints * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Release )( 
            ITRiASSimplePoints * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASSimplePoints * This,
            /* [out][idldescattr] */ unsigned UINT *pctinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASSimplePoints * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void **pptinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASSimplePoints * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ signed char **rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long *rgdispid,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASSimplePoints * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ struct DISPPARAMS *pdispparams,
            /* [out][idldescattr] */ VARIANT *pvarResult,
            /* [out][idldescattr] */ struct EXCEPINFO *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT *puArgErr,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITRiASSimplePoints * This,
            /* [retval][out] */ signed long *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_NewEnum )( 
            ITRiASSimplePoints * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            ITRiASSimplePoints * This,
            /* [in][idldescattr] */ VARIANT index,
            /* [retval][out] */ **retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ITRiASSimplePoints * This,
            /* [in][idldescattr] */ point	*point,
            /* [optional][in][idldescattr] */ VARIANT index,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ITRiASSimplePoints * This,
            /* [in][idldescattr] */ VARIANT index,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetPoint )( 
            ITRiASSimplePoints * This,
            /* [in][idldescattr] */ signed long index,
            /* [out][idldescattr] */ double *point,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *SetPoint )( 
            ITRiASSimplePoints * This,
            /* [in][idldescattr] */ signed long index,
            /* [in][idldescattr] */ double *point,
            /* [retval][out] */ void *retval);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPoints )( 
            ITRiASSimplePoints * This,
            /* [in] */ ULONG lFirst,
            /* [in] */ ULONG nCoords,
            /* [size_is][out][in] */ double *Coords);
        
        END_INTERFACE
    } ITRiASSimplePointsVtbl;

    interface ITRiASSimplePoints
    {
        CONST_VTBL struct ITRiASSimplePointsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASSimplePoints_QueryInterface(This,riid,ppvObj,retval)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval)

#define ITRiASSimplePoints_AddRef(This,retval)	\
    (This)->lpVtbl -> AddRef(This,retval)

#define ITRiASSimplePoints_Release(This,retval)	\
    (This)->lpVtbl -> Release(This,retval)

#define ITRiASSimplePoints_GetTypeInfoCount(This,pctinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval)

#define ITRiASSimplePoints_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval)

#define ITRiASSimplePoints_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)

#define ITRiASSimplePoints_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)

#define ITRiASSimplePoints_get_Count(This,retval)	\
    (This)->lpVtbl -> get_Count(This,retval)

#define ITRiASSimplePoints_get_NewEnum(This,retval)	\
    (This)->lpVtbl -> get_NewEnum(This,retval)

#define ITRiASSimplePoints_Item(This,index,retval)	\
    (This)->lpVtbl -> Item(This,index,retval)

#define ITRiASSimplePoints_Add(This,point,index,retval)	\
    (This)->lpVtbl -> Add(This,point,index,retval)

#define ITRiASSimplePoints_Remove(This,index,retval)	\
    (This)->lpVtbl -> Remove(This,index,retval)

#define ITRiASSimplePoints_GetPoint(This,index,point,retval)	\
    (This)->lpVtbl -> GetPoint(This,index,point,retval)

#define ITRiASSimplePoints_SetPoint(This,index,point,retval)	\
    (This)->lpVtbl -> SetPoint(This,index,point,retval)


#define ITRiASSimplePoints_GetPoints(This,lFirst,nCoords,Coords)	\
    (This)->lpVtbl -> GetPoints(This,lFirst,nCoords,Coords)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASSimplePoints_GetPoints_Proxy( 
    ITRiASSimplePoints * This,
    /* [in] */ ULONG lFirst,
    /* [in] */ ULONG nCoords,
    /* [size_is][out][in] */ double *Coords);


void __RPC_STUB ITRiASSimplePoints_GetPoints_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASSimplePoints_INTERFACE_DEFINED__ */


#ifndef __ITRiASCSMBRAccess_INTERFACE_DEFINED__
#define __ITRiASCSMBRAccess_INTERFACE_DEFINED__

/* interface ITRiASCSMBRAccess */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITRiASCSMBRAccess;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("59FEEBE3-3B7D-11d2-8C6B-080036D63803")
    ITRiASCSMBRAccess : public IUnknown
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Envelope( 
            /* [retval][out] */ ITRiASSimpleRectangle **Rect) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASCSMBRAccessVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASCSMBRAccess * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASCSMBRAccess * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASCSMBRAccess * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Envelope )( 
            ITRiASCSMBRAccess * This,
            /* [retval][out] */ ITRiASSimpleRectangle **Rect);
        
        END_INTERFACE
    } ITRiASCSMBRAccessVtbl;

    interface ITRiASCSMBRAccess
    {
        CONST_VTBL struct ITRiASCSMBRAccessVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASCSMBRAccess_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASCSMBRAccess_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASCSMBRAccess_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASCSMBRAccess_get_Envelope(This,Rect)	\
    (This)->lpVtbl -> get_Envelope(This,Rect)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASCSMBRAccess_get_Envelope_Proxy( 
    ITRiASCSMBRAccess * This,
    /* [retval][out] */ ITRiASSimpleRectangle **Rect);


void __RPC_STUB ITRiASCSMBRAccess_get_Envelope_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASCSMBRAccess_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_TRiASCSPoint;

#ifdef __cplusplus

class DECLSPEC_UUID("0BDC3C1E-503F-11D1-96F0-00A024D6F582")
TRiASCSPoint;
#endif

EXTERN_C const CLSID CLSID_TRiASCSPoints;

#ifdef __cplusplus

class DECLSPEC_UUID("0BDC3C21-503F-11D1-96F0-00A024D6F582")
TRiASCSPoints;
#endif

EXTERN_C const CLSID CLSID_TRiASCSVector;

#ifdef __cplusplus

class DECLSPEC_UUID("BC145188-013F-11D2-864C-00600875138A")
TRiASCSVector;
#endif

EXTERN_C const CLSID CLSID_TRiASCSRectangleGeometry;

#ifdef __cplusplus

class DECLSPEC_UUID("CF648167-9E24-11D1-BA1C-080036D63803")
TRiASCSRectangleGeometry;
#endif

EXTERN_C const CLSID CLSID_TRiASCSLineGeometry;

#ifdef __cplusplus

class DECLSPEC_UUID("96D754A4-A21F-11D1-A050-0060975566B4")
TRiASCSLineGeometry;
#endif

EXTERN_C const CLSID CLSID_TRiASCSPointGeometry;

#ifdef __cplusplus

class DECLSPEC_UUID("3327AD94-A2B1-11D1-A051-0060975566B4")
TRiASCSPointGeometry;
#endif

EXTERN_C const CLSID CLSID_TRiASCSOrientedPointGeometry;

#ifdef __cplusplus

class DECLSPEC_UUID("1369BDE5-2567-11D2-9EA2-006008447800")
TRiASCSOrientedPointGeometry;
#endif

EXTERN_C const CLSID CLSID_TRiASCSPolylineGeometry;

#ifdef __cplusplus

class DECLSPEC_UUID("3327AD96-A2B1-11D1-A051-0060975566B4")
TRiASCSPolylineGeometry;
#endif

EXTERN_C const CLSID CLSID_TRiASCSPolygonGeometry;

#ifdef __cplusplus

class DECLSPEC_UUID("3327AD98-A2B1-11D1-A051-0060975566B4")
TRiASCSPolygonGeometry;
#endif

EXTERN_C const CLSID CLSID_TRiASCSBoundaryGeometry;

#ifdef __cplusplus

class DECLSPEC_UUID("3327AD9A-A2B1-11D1-A051-0060975566B4")
TRiASCSBoundaryGeometry;
#endif

EXTERN_C const CLSID CLSID_TRiASCSGeometryCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("3327AD9C-A2B1-11D1-A051-0060975566B4")
TRiASCSGeometryCollection;
#endif

EXTERN_C const CLSID CLSID_TRiASCSTextPointGeometry;

#ifdef __cplusplus

class DECLSPEC_UUID("ABEE61B0-B1B8-11D1-A074-0060975566B4")
TRiASCSTextPointGeometry;
#endif

EXTERN_C const CLSID CLSID_TRiASCSStorageService;

#ifdef __cplusplus

class DECLSPEC_UUID("80B9A2F6-02B0-11D2-8650-00600875138A")
TRiASCSStorageService;
#endif

EXTERN_C const CLSID CLSID_TRiASCSPointEnum;

#ifdef __cplusplus

class DECLSPEC_UUID("67B5B598-3BFB-11D2-8C6C-080036D63803")
TRiASCSPointEnum;
#endif

EXTERN_C const CLSID CLSID_GeometryMoniker;

#ifdef __cplusplus

class DECLSPEC_UUID("AB41EB68-6218-43FD-B29F-DDF8A96AEEA1")
GeometryMoniker;
#endif

EXTERN_C const CLSID CLSID_TRiASSpatialRelationService;

#ifdef __cplusplus

class DECLSPEC_UUID("49EA68E0-C4F9-4392-A083-B1A0D5E6AFF6")
TRiASSpatialRelationService;
#endif
#endif /* __TDBGEO_LIBRARY_DEFINED__ */

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


