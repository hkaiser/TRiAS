
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Thu Jan 17 12:57:25 2002
 */
/* Compiler settings for GeometryIdl.idl:
    Os, W1, Zp8, env=Win32 (32b run)
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

#ifndef __GeometryIdl_h__
#define __GeometryIdl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IGeometry_FWD_DEFINED__
#define __IGeometry_FWD_DEFINED__
typedef interface IGeometry IGeometry;
#endif 	/* __IGeometry_FWD_DEFINED__ */


#ifndef __IWks_FWD_DEFINED__
#define __IWks_FWD_DEFINED__
typedef interface IWks IWks;
#endif 	/* __IWks_FWD_DEFINED__ */


#ifndef __IGeometryFactory_FWD_DEFINED__
#define __IGeometryFactory_FWD_DEFINED__
typedef interface IGeometryFactory IGeometryFactory;
#endif 	/* __IGeometryFactory_FWD_DEFINED__ */


#ifndef __IPoint_FWD_DEFINED__
#define __IPoint_FWD_DEFINED__
typedef interface IPoint IPoint;
#endif 	/* __IPoint_FWD_DEFINED__ */


#ifndef __IPointZ_FWD_DEFINED__
#define __IPointZ_FWD_DEFINED__
typedef interface IPointZ IPointZ;
#endif 	/* __IPointZ_FWD_DEFINED__ */


#ifndef __ICurve_FWD_DEFINED__
#define __ICurve_FWD_DEFINED__
typedef interface ICurve ICurve;
#endif 	/* __ICurve_FWD_DEFINED__ */


#ifndef __ILineString_FWD_DEFINED__
#define __ILineString_FWD_DEFINED__
typedef interface ILineString ILineString;
#endif 	/* __ILineString_FWD_DEFINED__ */


#ifndef __ILinearRing_FWD_DEFINED__
#define __ILinearRing_FWD_DEFINED__
typedef interface ILinearRing ILinearRing;
#endif 	/* __ILinearRing_FWD_DEFINED__ */


#ifndef __ISurface_FWD_DEFINED__
#define __ISurface_FWD_DEFINED__
typedef interface ISurface ISurface;
#endif 	/* __ISurface_FWD_DEFINED__ */


#ifndef __IGeometryCollection_FWD_DEFINED__
#define __IGeometryCollection_FWD_DEFINED__
typedef interface IGeometryCollection IGeometryCollection;
#endif 	/* __IGeometryCollection_FWD_DEFINED__ */


#ifndef __IPolygon_FWD_DEFINED__
#define __IPolygon_FWD_DEFINED__
typedef interface IPolygon IPolygon;
#endif 	/* __IPolygon_FWD_DEFINED__ */


#ifndef __IMultiCurve_FWD_DEFINED__
#define __IMultiCurve_FWD_DEFINED__
typedef interface IMultiCurve IMultiCurve;
#endif 	/* __IMultiCurve_FWD_DEFINED__ */


#ifndef __IMultiSurface_FWD_DEFINED__
#define __IMultiSurface_FWD_DEFINED__
typedef interface IMultiSurface IMultiSurface;
#endif 	/* __IMultiSurface_FWD_DEFINED__ */


#ifndef __ISpatialRelation_FWD_DEFINED__
#define __ISpatialRelation_FWD_DEFINED__
typedef interface ISpatialRelation ISpatialRelation;
#endif 	/* __ISpatialRelation_FWD_DEFINED__ */


#ifndef __ISpatialRelation2_FWD_DEFINED__
#define __ISpatialRelation2_FWD_DEFINED__
typedef interface ISpatialRelation2 ISpatialRelation2;
#endif 	/* __ISpatialRelation2_FWD_DEFINED__ */


#ifndef __ISpatialOperator_FWD_DEFINED__
#define __ISpatialOperator_FWD_DEFINED__
typedef interface ISpatialOperator ISpatialOperator;
#endif 	/* __ISpatialOperator_FWD_DEFINED__ */


/* header files for imported files */
#include "ocidl.h"
#include "SpatialReferenceIdl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_GeometryIdl_0000 */
/* [local] */ 















extern RPC_IF_HANDLE __MIDL_itf_GeometryIdl_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_GeometryIdl_0000_v0_0_s_ifspec;

#ifndef __IGeometry_INTERFACE_DEFINED__
#define __IGeometry_INTERFACE_DEFINED__

/* interface IGeometry */
/* [uuid][object] */ 


EXTERN_C const IID IID_IGeometry;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6A124031-FE38-11d0-BECE-00805F7C4268")
    IGeometry : public IUnknown
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Dimension( 
            /* [retval][out] */ long *dimension) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_SpatialReference( 
            /* [retval][out] */ ISpatialReference **spatialRef) = 0;
        
        virtual /* [propputref] */ HRESULT STDMETHODCALLTYPE putref_SpatialReference( 
            /* [in] */ ISpatialReference *spatialRef) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_IsEmpty( 
            /* [retval][out] */ VARIANT_BOOL *isEmpty) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetEmpty( void) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_IsSimple( 
            /* [retval][out] */ VARIANT_BOOL *isSimple) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Envelope( 
            /* [retval][out] */ IGeometry **envelope) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IGeometry **newShape) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Project( 
            /* [in] */ ISpatialReference *newSystem,
            /* [retval][out] */ IGeometry **result) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Extent2D( 
            /* [out] */ double *minX,
            /* [out] */ double *minY,
            /* [out] */ double *maxX,
            /* [out] */ double *maxY) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGeometryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGeometry * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGeometry * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGeometry * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dimension )( 
            IGeometry * This,
            /* [retval][out] */ long *dimension);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_SpatialReference )( 
            IGeometry * This,
            /* [retval][out] */ ISpatialReference **spatialRef);
        
        /* [propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SpatialReference )( 
            IGeometry * This,
            /* [in] */ ISpatialReference *spatialRef);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsEmpty )( 
            IGeometry * This,
            /* [retval][out] */ VARIANT_BOOL *isEmpty);
        
        HRESULT ( STDMETHODCALLTYPE *SetEmpty )( 
            IGeometry * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsSimple )( 
            IGeometry * This,
            /* [retval][out] */ VARIANT_BOOL *isSimple);
        
        HRESULT ( STDMETHODCALLTYPE *Envelope )( 
            IGeometry * This,
            /* [retval][out] */ IGeometry **envelope);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IGeometry * This,
            /* [retval][out] */ IGeometry **newShape);
        
        HRESULT ( STDMETHODCALLTYPE *Project )( 
            IGeometry * This,
            /* [in] */ ISpatialReference *newSystem,
            /* [retval][out] */ IGeometry **result);
        
        HRESULT ( STDMETHODCALLTYPE *Extent2D )( 
            IGeometry * This,
            /* [out] */ double *minX,
            /* [out] */ double *minY,
            /* [out] */ double *maxX,
            /* [out] */ double *maxY);
        
        END_INTERFACE
    } IGeometryVtbl;

    interface IGeometry
    {
        CONST_VTBL struct IGeometryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGeometry_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGeometry_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGeometry_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGeometry_get_Dimension(This,dimension)	\
    (This)->lpVtbl -> get_Dimension(This,dimension)

#define IGeometry_get_SpatialReference(This,spatialRef)	\
    (This)->lpVtbl -> get_SpatialReference(This,spatialRef)

#define IGeometry_putref_SpatialReference(This,spatialRef)	\
    (This)->lpVtbl -> putref_SpatialReference(This,spatialRef)

#define IGeometry_get_IsEmpty(This,isEmpty)	\
    (This)->lpVtbl -> get_IsEmpty(This,isEmpty)

#define IGeometry_SetEmpty(This)	\
    (This)->lpVtbl -> SetEmpty(This)

#define IGeometry_get_IsSimple(This,isSimple)	\
    (This)->lpVtbl -> get_IsSimple(This,isSimple)

#define IGeometry_Envelope(This,envelope)	\
    (This)->lpVtbl -> Envelope(This,envelope)

#define IGeometry_Clone(This,newShape)	\
    (This)->lpVtbl -> Clone(This,newShape)

#define IGeometry_Project(This,newSystem,result)	\
    (This)->lpVtbl -> Project(This,newSystem,result)

#define IGeometry_Extent2D(This,minX,minY,maxX,maxY)	\
    (This)->lpVtbl -> Extent2D(This,minX,minY,maxX,maxY)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IGeometry_get_Dimension_Proxy( 
    IGeometry * This,
    /* [retval][out] */ long *dimension);


void __RPC_STUB IGeometry_get_Dimension_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IGeometry_get_SpatialReference_Proxy( 
    IGeometry * This,
    /* [retval][out] */ ISpatialReference **spatialRef);


void __RPC_STUB IGeometry_get_SpatialReference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propputref] */ HRESULT STDMETHODCALLTYPE IGeometry_putref_SpatialReference_Proxy( 
    IGeometry * This,
    /* [in] */ ISpatialReference *spatialRef);


void __RPC_STUB IGeometry_putref_SpatialReference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IGeometry_get_IsEmpty_Proxy( 
    IGeometry * This,
    /* [retval][out] */ VARIANT_BOOL *isEmpty);


void __RPC_STUB IGeometry_get_IsEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGeometry_SetEmpty_Proxy( 
    IGeometry * This);


void __RPC_STUB IGeometry_SetEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IGeometry_get_IsSimple_Proxy( 
    IGeometry * This,
    /* [retval][out] */ VARIANT_BOOL *isSimple);


void __RPC_STUB IGeometry_get_IsSimple_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGeometry_Envelope_Proxy( 
    IGeometry * This,
    /* [retval][out] */ IGeometry **envelope);


void __RPC_STUB IGeometry_Envelope_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGeometry_Clone_Proxy( 
    IGeometry * This,
    /* [retval][out] */ IGeometry **newShape);


void __RPC_STUB IGeometry_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGeometry_Project_Proxy( 
    IGeometry * This,
    /* [in] */ ISpatialReference *newSystem,
    /* [retval][out] */ IGeometry **result);


void __RPC_STUB IGeometry_Project_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGeometry_Extent2D_Proxy( 
    IGeometry * This,
    /* [out] */ double *minX,
    /* [out] */ double *minY,
    /* [out] */ double *maxX,
    /* [out] */ double *maxY);


void __RPC_STUB IGeometry_Extent2D_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGeometry_INTERFACE_DEFINED__ */


#ifndef __IWks_INTERFACE_DEFINED__
#define __IWks_INTERFACE_DEFINED__

/* interface IWks */
/* [uuid][object] */ 


EXTERN_C const IID IID_IWks;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6A124032-FE38-11d0-BECE-00805F7C4268")
    IWks : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ExportToWKB( 
            /* [retval][out] */ VARIANT *wkb) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ExportToWKT( 
            /* [retval][out] */ BSTR *wkt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ImportFromWKB( 
            /* [in] */ VARIANT wkb,
            /* [in] */ ISpatialReference *spatialRef) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ImportFromWKT( 
            /* [in] */ BSTR wkt,
            /* [in] */ ISpatialReference *spatialRef) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWksVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWks * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWks * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWks * This);
        
        HRESULT ( STDMETHODCALLTYPE *ExportToWKB )( 
            IWks * This,
            /* [retval][out] */ VARIANT *wkb);
        
        HRESULT ( STDMETHODCALLTYPE *ExportToWKT )( 
            IWks * This,
            /* [retval][out] */ BSTR *wkt);
        
        HRESULT ( STDMETHODCALLTYPE *ImportFromWKB )( 
            IWks * This,
            /* [in] */ VARIANT wkb,
            /* [in] */ ISpatialReference *spatialRef);
        
        HRESULT ( STDMETHODCALLTYPE *ImportFromWKT )( 
            IWks * This,
            /* [in] */ BSTR wkt,
            /* [in] */ ISpatialReference *spatialRef);
        
        END_INTERFACE
    } IWksVtbl;

    interface IWks
    {
        CONST_VTBL struct IWksVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWks_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWks_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWks_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWks_ExportToWKB(This,wkb)	\
    (This)->lpVtbl -> ExportToWKB(This,wkb)

#define IWks_ExportToWKT(This,wkt)	\
    (This)->lpVtbl -> ExportToWKT(This,wkt)

#define IWks_ImportFromWKB(This,wkb,spatialRef)	\
    (This)->lpVtbl -> ImportFromWKB(This,wkb,spatialRef)

#define IWks_ImportFromWKT(This,wkt,spatialRef)	\
    (This)->lpVtbl -> ImportFromWKT(This,wkt,spatialRef)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWks_ExportToWKB_Proxy( 
    IWks * This,
    /* [retval][out] */ VARIANT *wkb);


void __RPC_STUB IWks_ExportToWKB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWks_ExportToWKT_Proxy( 
    IWks * This,
    /* [retval][out] */ BSTR *wkt);


void __RPC_STUB IWks_ExportToWKT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWks_ImportFromWKB_Proxy( 
    IWks * This,
    /* [in] */ VARIANT wkb,
    /* [in] */ ISpatialReference *spatialRef);


void __RPC_STUB IWks_ImportFromWKB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWks_ImportFromWKT_Proxy( 
    IWks * This,
    /* [in] */ BSTR wkt,
    /* [in] */ ISpatialReference *spatialRef);


void __RPC_STUB IWks_ImportFromWKT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWks_INTERFACE_DEFINED__ */


#ifndef __IGeometryFactory_INTERFACE_DEFINED__
#define __IGeometryFactory_INTERFACE_DEFINED__

/* interface IGeometryFactory */
/* [uuid][object] */ 


EXTERN_C const IID IID_IGeometryFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6A124033-FE38-11d0-BECE-00805F7C4268")
    IGeometryFactory : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateFromWKB( 
            /* [in] */ VARIANT wkb,
            /* [in] */ ISpatialReference *spatialRef,
            /* [retval][out] */ IGeometry **geometry) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateFromWKT( 
            /* [in] */ BSTR wkt,
            /* [in] */ ISpatialReference *spatialRef,
            /* [retval][out] */ IGeometry **geometry) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGeometryFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGeometryFactory * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGeometryFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGeometryFactory * This);
        
        HRESULT ( STDMETHODCALLTYPE *CreateFromWKB )( 
            IGeometryFactory * This,
            /* [in] */ VARIANT wkb,
            /* [in] */ ISpatialReference *spatialRef,
            /* [retval][out] */ IGeometry **geometry);
        
        HRESULT ( STDMETHODCALLTYPE *CreateFromWKT )( 
            IGeometryFactory * This,
            /* [in] */ BSTR wkt,
            /* [in] */ ISpatialReference *spatialRef,
            /* [retval][out] */ IGeometry **geometry);
        
        END_INTERFACE
    } IGeometryFactoryVtbl;

    interface IGeometryFactory
    {
        CONST_VTBL struct IGeometryFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGeometryFactory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGeometryFactory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGeometryFactory_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGeometryFactory_CreateFromWKB(This,wkb,spatialRef,geometry)	\
    (This)->lpVtbl -> CreateFromWKB(This,wkb,spatialRef,geometry)

#define IGeometryFactory_CreateFromWKT(This,wkt,spatialRef,geometry)	\
    (This)->lpVtbl -> CreateFromWKT(This,wkt,spatialRef,geometry)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IGeometryFactory_CreateFromWKB_Proxy( 
    IGeometryFactory * This,
    /* [in] */ VARIANT wkb,
    /* [in] */ ISpatialReference *spatialRef,
    /* [retval][out] */ IGeometry **geometry);


void __RPC_STUB IGeometryFactory_CreateFromWKB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGeometryFactory_CreateFromWKT_Proxy( 
    IGeometryFactory * This,
    /* [in] */ BSTR wkt,
    /* [in] */ ISpatialReference *spatialRef,
    /* [retval][out] */ IGeometry **geometry);


void __RPC_STUB IGeometryFactory_CreateFromWKT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGeometryFactory_INTERFACE_DEFINED__ */


#ifndef __IPoint_INTERFACE_DEFINED__
#define __IPoint_INTERFACE_DEFINED__

/* interface IPoint */
/* [uuid][object] */ 


EXTERN_C const IID IID_IPoint;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6A124035-FE38-11d0-BECE-00805F7C4268")
    IPoint : public IGeometry
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Coords( 
            /* [out] */ double *x,
            /* [out] */ double *y) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_X( 
            /* [retval][out] */ double *x) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Y( 
            /* [retval][out] */ double *y) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPointVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPoint * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPoint * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPoint * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dimension )( 
            IPoint * This,
            /* [retval][out] */ long *dimension);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_SpatialReference )( 
            IPoint * This,
            /* [retval][out] */ ISpatialReference **spatialRef);
        
        /* [propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SpatialReference )( 
            IPoint * This,
            /* [in] */ ISpatialReference *spatialRef);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsEmpty )( 
            IPoint * This,
            /* [retval][out] */ VARIANT_BOOL *isEmpty);
        
        HRESULT ( STDMETHODCALLTYPE *SetEmpty )( 
            IPoint * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsSimple )( 
            IPoint * This,
            /* [retval][out] */ VARIANT_BOOL *isSimple);
        
        HRESULT ( STDMETHODCALLTYPE *Envelope )( 
            IPoint * This,
            /* [retval][out] */ IGeometry **envelope);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IPoint * This,
            /* [retval][out] */ IGeometry **newShape);
        
        HRESULT ( STDMETHODCALLTYPE *Project )( 
            IPoint * This,
            /* [in] */ ISpatialReference *newSystem,
            /* [retval][out] */ IGeometry **result);
        
        HRESULT ( STDMETHODCALLTYPE *Extent2D )( 
            IPoint * This,
            /* [out] */ double *minX,
            /* [out] */ double *minY,
            /* [out] */ double *maxX,
            /* [out] */ double *maxY);
        
        HRESULT ( STDMETHODCALLTYPE *Coords )( 
            IPoint * This,
            /* [out] */ double *x,
            /* [out] */ double *y);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_X )( 
            IPoint * This,
            /* [retval][out] */ double *x);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Y )( 
            IPoint * This,
            /* [retval][out] */ double *y);
        
        END_INTERFACE
    } IPointVtbl;

    interface IPoint
    {
        CONST_VTBL struct IPointVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPoint_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPoint_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPoint_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPoint_get_Dimension(This,dimension)	\
    (This)->lpVtbl -> get_Dimension(This,dimension)

#define IPoint_get_SpatialReference(This,spatialRef)	\
    (This)->lpVtbl -> get_SpatialReference(This,spatialRef)

#define IPoint_putref_SpatialReference(This,spatialRef)	\
    (This)->lpVtbl -> putref_SpatialReference(This,spatialRef)

#define IPoint_get_IsEmpty(This,isEmpty)	\
    (This)->lpVtbl -> get_IsEmpty(This,isEmpty)

#define IPoint_SetEmpty(This)	\
    (This)->lpVtbl -> SetEmpty(This)

#define IPoint_get_IsSimple(This,isSimple)	\
    (This)->lpVtbl -> get_IsSimple(This,isSimple)

#define IPoint_Envelope(This,envelope)	\
    (This)->lpVtbl -> Envelope(This,envelope)

#define IPoint_Clone(This,newShape)	\
    (This)->lpVtbl -> Clone(This,newShape)

#define IPoint_Project(This,newSystem,result)	\
    (This)->lpVtbl -> Project(This,newSystem,result)

#define IPoint_Extent2D(This,minX,minY,maxX,maxY)	\
    (This)->lpVtbl -> Extent2D(This,minX,minY,maxX,maxY)


#define IPoint_Coords(This,x,y)	\
    (This)->lpVtbl -> Coords(This,x,y)

#define IPoint_get_X(This,x)	\
    (This)->lpVtbl -> get_X(This,x)

#define IPoint_get_Y(This,y)	\
    (This)->lpVtbl -> get_Y(This,y)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPoint_Coords_Proxy( 
    IPoint * This,
    /* [out] */ double *x,
    /* [out] */ double *y);


void __RPC_STUB IPoint_Coords_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPoint_get_X_Proxy( 
    IPoint * This,
    /* [retval][out] */ double *x);


void __RPC_STUB IPoint_get_X_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPoint_get_Y_Proxy( 
    IPoint * This,
    /* [retval][out] */ double *y);


void __RPC_STUB IPoint_get_Y_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPoint_INTERFACE_DEFINED__ */


#ifndef __IPointZ_INTERFACE_DEFINED__
#define __IPointZ_INTERFACE_DEFINED__

/* interface IPointZ */
/* [uuid][object] */ 


EXTERN_C const IID IID_IPointZ;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D4579E2D-1D2B-11d3-80BE-00C04F680FFF")
    IPointZ : public IPoint
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Z( 
            /* [retval][out] */ double *z) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPointZVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPointZ * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPointZ * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPointZ * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dimension )( 
            IPointZ * This,
            /* [retval][out] */ long *dimension);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_SpatialReference )( 
            IPointZ * This,
            /* [retval][out] */ ISpatialReference **spatialRef);
        
        /* [propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SpatialReference )( 
            IPointZ * This,
            /* [in] */ ISpatialReference *spatialRef);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsEmpty )( 
            IPointZ * This,
            /* [retval][out] */ VARIANT_BOOL *isEmpty);
        
        HRESULT ( STDMETHODCALLTYPE *SetEmpty )( 
            IPointZ * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsSimple )( 
            IPointZ * This,
            /* [retval][out] */ VARIANT_BOOL *isSimple);
        
        HRESULT ( STDMETHODCALLTYPE *Envelope )( 
            IPointZ * This,
            /* [retval][out] */ IGeometry **envelope);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IPointZ * This,
            /* [retval][out] */ IGeometry **newShape);
        
        HRESULT ( STDMETHODCALLTYPE *Project )( 
            IPointZ * This,
            /* [in] */ ISpatialReference *newSystem,
            /* [retval][out] */ IGeometry **result);
        
        HRESULT ( STDMETHODCALLTYPE *Extent2D )( 
            IPointZ * This,
            /* [out] */ double *minX,
            /* [out] */ double *minY,
            /* [out] */ double *maxX,
            /* [out] */ double *maxY);
        
        HRESULT ( STDMETHODCALLTYPE *Coords )( 
            IPointZ * This,
            /* [out] */ double *x,
            /* [out] */ double *y);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_X )( 
            IPointZ * This,
            /* [retval][out] */ double *x);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Y )( 
            IPointZ * This,
            /* [retval][out] */ double *y);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Z )( 
            IPointZ * This,
            /* [retval][out] */ double *z);
        
        END_INTERFACE
    } IPointZVtbl;

    interface IPointZ
    {
        CONST_VTBL struct IPointZVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPointZ_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPointZ_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPointZ_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPointZ_get_Dimension(This,dimension)	\
    (This)->lpVtbl -> get_Dimension(This,dimension)

#define IPointZ_get_SpatialReference(This,spatialRef)	\
    (This)->lpVtbl -> get_SpatialReference(This,spatialRef)

#define IPointZ_putref_SpatialReference(This,spatialRef)	\
    (This)->lpVtbl -> putref_SpatialReference(This,spatialRef)

#define IPointZ_get_IsEmpty(This,isEmpty)	\
    (This)->lpVtbl -> get_IsEmpty(This,isEmpty)

#define IPointZ_SetEmpty(This)	\
    (This)->lpVtbl -> SetEmpty(This)

#define IPointZ_get_IsSimple(This,isSimple)	\
    (This)->lpVtbl -> get_IsSimple(This,isSimple)

#define IPointZ_Envelope(This,envelope)	\
    (This)->lpVtbl -> Envelope(This,envelope)

#define IPointZ_Clone(This,newShape)	\
    (This)->lpVtbl -> Clone(This,newShape)

#define IPointZ_Project(This,newSystem,result)	\
    (This)->lpVtbl -> Project(This,newSystem,result)

#define IPointZ_Extent2D(This,minX,minY,maxX,maxY)	\
    (This)->lpVtbl -> Extent2D(This,minX,minY,maxX,maxY)


#define IPointZ_Coords(This,x,y)	\
    (This)->lpVtbl -> Coords(This,x,y)

#define IPointZ_get_X(This,x)	\
    (This)->lpVtbl -> get_X(This,x)

#define IPointZ_get_Y(This,y)	\
    (This)->lpVtbl -> get_Y(This,y)


#define IPointZ_get_Z(This,z)	\
    (This)->lpVtbl -> get_Z(This,z)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IPointZ_get_Z_Proxy( 
    IPointZ * This,
    /* [retval][out] */ double *z);


void __RPC_STUB IPointZ_get_Z_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPointZ_INTERFACE_DEFINED__ */


#ifndef __ICurve_INTERFACE_DEFINED__
#define __ICurve_INTERFACE_DEFINED__

/* interface ICurve */
/* [uuid][object] */ 


EXTERN_C const IID IID_ICurve;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6A124036-FE38-11d0-BECE-00805F7C4268")
    ICurve : public IGeometry
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ double *value) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StartPoint( 
            /* [retval][out] */ IPoint **sp) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EndPoint( 
            /* [retval][out] */ IPoint **ep) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_IsClosed( 
            /* [retval][out] */ VARIANT_BOOL *isClosed) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Value( 
            /* [in] */ double t,
            /* [retval][out] */ IPoint **p) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICurveVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICurve * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICurve * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICurve * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dimension )( 
            ICurve * This,
            /* [retval][out] */ long *dimension);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_SpatialReference )( 
            ICurve * This,
            /* [retval][out] */ ISpatialReference **spatialRef);
        
        /* [propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SpatialReference )( 
            ICurve * This,
            /* [in] */ ISpatialReference *spatialRef);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsEmpty )( 
            ICurve * This,
            /* [retval][out] */ VARIANT_BOOL *isEmpty);
        
        HRESULT ( STDMETHODCALLTYPE *SetEmpty )( 
            ICurve * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsSimple )( 
            ICurve * This,
            /* [retval][out] */ VARIANT_BOOL *isSimple);
        
        HRESULT ( STDMETHODCALLTYPE *Envelope )( 
            ICurve * This,
            /* [retval][out] */ IGeometry **envelope);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ICurve * This,
            /* [retval][out] */ IGeometry **newShape);
        
        HRESULT ( STDMETHODCALLTYPE *Project )( 
            ICurve * This,
            /* [in] */ ISpatialReference *newSystem,
            /* [retval][out] */ IGeometry **result);
        
        HRESULT ( STDMETHODCALLTYPE *Extent2D )( 
            ICurve * This,
            /* [out] */ double *minX,
            /* [out] */ double *minY,
            /* [out] */ double *maxX,
            /* [out] */ double *maxY);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            ICurve * This,
            /* [retval][out] */ double *value);
        
        HRESULT ( STDMETHODCALLTYPE *StartPoint )( 
            ICurve * This,
            /* [retval][out] */ IPoint **sp);
        
        HRESULT ( STDMETHODCALLTYPE *EndPoint )( 
            ICurve * This,
            /* [retval][out] */ IPoint **ep);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsClosed )( 
            ICurve * This,
            /* [retval][out] */ VARIANT_BOOL *isClosed);
        
        HRESULT ( STDMETHODCALLTYPE *Value )( 
            ICurve * This,
            /* [in] */ double t,
            /* [retval][out] */ IPoint **p);
        
        END_INTERFACE
    } ICurveVtbl;

    interface ICurve
    {
        CONST_VTBL struct ICurveVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICurve_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICurve_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICurve_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICurve_get_Dimension(This,dimension)	\
    (This)->lpVtbl -> get_Dimension(This,dimension)

#define ICurve_get_SpatialReference(This,spatialRef)	\
    (This)->lpVtbl -> get_SpatialReference(This,spatialRef)

#define ICurve_putref_SpatialReference(This,spatialRef)	\
    (This)->lpVtbl -> putref_SpatialReference(This,spatialRef)

#define ICurve_get_IsEmpty(This,isEmpty)	\
    (This)->lpVtbl -> get_IsEmpty(This,isEmpty)

#define ICurve_SetEmpty(This)	\
    (This)->lpVtbl -> SetEmpty(This)

#define ICurve_get_IsSimple(This,isSimple)	\
    (This)->lpVtbl -> get_IsSimple(This,isSimple)

#define ICurve_Envelope(This,envelope)	\
    (This)->lpVtbl -> Envelope(This,envelope)

#define ICurve_Clone(This,newShape)	\
    (This)->lpVtbl -> Clone(This,newShape)

#define ICurve_Project(This,newSystem,result)	\
    (This)->lpVtbl -> Project(This,newSystem,result)

#define ICurve_Extent2D(This,minX,minY,maxX,maxY)	\
    (This)->lpVtbl -> Extent2D(This,minX,minY,maxX,maxY)


#define ICurve_get_Length(This,value)	\
    (This)->lpVtbl -> get_Length(This,value)

#define ICurve_StartPoint(This,sp)	\
    (This)->lpVtbl -> StartPoint(This,sp)

#define ICurve_EndPoint(This,ep)	\
    (This)->lpVtbl -> EndPoint(This,ep)

#define ICurve_get_IsClosed(This,isClosed)	\
    (This)->lpVtbl -> get_IsClosed(This,isClosed)

#define ICurve_Value(This,t,p)	\
    (This)->lpVtbl -> Value(This,t,p)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE ICurve_get_Length_Proxy( 
    ICurve * This,
    /* [retval][out] */ double *value);


void __RPC_STUB ICurve_get_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICurve_StartPoint_Proxy( 
    ICurve * This,
    /* [retval][out] */ IPoint **sp);


void __RPC_STUB ICurve_StartPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICurve_EndPoint_Proxy( 
    ICurve * This,
    /* [retval][out] */ IPoint **ep);


void __RPC_STUB ICurve_EndPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ICurve_get_IsClosed_Proxy( 
    ICurve * This,
    /* [retval][out] */ VARIANT_BOOL *isClosed);


void __RPC_STUB ICurve_get_IsClosed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICurve_Value_Proxy( 
    ICurve * This,
    /* [in] */ double t,
    /* [retval][out] */ IPoint **p);


void __RPC_STUB ICurve_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICurve_INTERFACE_DEFINED__ */


#ifndef __ILineString_INTERFACE_DEFINED__
#define __ILineString_INTERFACE_DEFINED__

/* interface ILineString */
/* [uuid][object] */ 


EXTERN_C const IID IID_ILineString;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6A124037-FE38-11d0-BECE-00805F7C4268")
    ILineString : public ICurve
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_NumPoints( 
            /* [retval][out] */ long *numPoints) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Point( 
            /* [in] */ long index,
            /* [retval][out] */ IPoint **point) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILineStringVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILineString * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILineString * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILineString * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dimension )( 
            ILineString * This,
            /* [retval][out] */ long *dimension);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_SpatialReference )( 
            ILineString * This,
            /* [retval][out] */ ISpatialReference **spatialRef);
        
        /* [propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SpatialReference )( 
            ILineString * This,
            /* [in] */ ISpatialReference *spatialRef);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsEmpty )( 
            ILineString * This,
            /* [retval][out] */ VARIANT_BOOL *isEmpty);
        
        HRESULT ( STDMETHODCALLTYPE *SetEmpty )( 
            ILineString * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsSimple )( 
            ILineString * This,
            /* [retval][out] */ VARIANT_BOOL *isSimple);
        
        HRESULT ( STDMETHODCALLTYPE *Envelope )( 
            ILineString * This,
            /* [retval][out] */ IGeometry **envelope);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ILineString * This,
            /* [retval][out] */ IGeometry **newShape);
        
        HRESULT ( STDMETHODCALLTYPE *Project )( 
            ILineString * This,
            /* [in] */ ISpatialReference *newSystem,
            /* [retval][out] */ IGeometry **result);
        
        HRESULT ( STDMETHODCALLTYPE *Extent2D )( 
            ILineString * This,
            /* [out] */ double *minX,
            /* [out] */ double *minY,
            /* [out] */ double *maxX,
            /* [out] */ double *maxY);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            ILineString * This,
            /* [retval][out] */ double *value);
        
        HRESULT ( STDMETHODCALLTYPE *StartPoint )( 
            ILineString * This,
            /* [retval][out] */ IPoint **sp);
        
        HRESULT ( STDMETHODCALLTYPE *EndPoint )( 
            ILineString * This,
            /* [retval][out] */ IPoint **ep);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsClosed )( 
            ILineString * This,
            /* [retval][out] */ VARIANT_BOOL *isClosed);
        
        HRESULT ( STDMETHODCALLTYPE *Value )( 
            ILineString * This,
            /* [in] */ double t,
            /* [retval][out] */ IPoint **p);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_NumPoints )( 
            ILineString * This,
            /* [retval][out] */ long *numPoints);
        
        HRESULT ( STDMETHODCALLTYPE *Point )( 
            ILineString * This,
            /* [in] */ long index,
            /* [retval][out] */ IPoint **point);
        
        END_INTERFACE
    } ILineStringVtbl;

    interface ILineString
    {
        CONST_VTBL struct ILineStringVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILineString_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILineString_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILineString_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILineString_get_Dimension(This,dimension)	\
    (This)->lpVtbl -> get_Dimension(This,dimension)

#define ILineString_get_SpatialReference(This,spatialRef)	\
    (This)->lpVtbl -> get_SpatialReference(This,spatialRef)

#define ILineString_putref_SpatialReference(This,spatialRef)	\
    (This)->lpVtbl -> putref_SpatialReference(This,spatialRef)

#define ILineString_get_IsEmpty(This,isEmpty)	\
    (This)->lpVtbl -> get_IsEmpty(This,isEmpty)

#define ILineString_SetEmpty(This)	\
    (This)->lpVtbl -> SetEmpty(This)

#define ILineString_get_IsSimple(This,isSimple)	\
    (This)->lpVtbl -> get_IsSimple(This,isSimple)

#define ILineString_Envelope(This,envelope)	\
    (This)->lpVtbl -> Envelope(This,envelope)

#define ILineString_Clone(This,newShape)	\
    (This)->lpVtbl -> Clone(This,newShape)

#define ILineString_Project(This,newSystem,result)	\
    (This)->lpVtbl -> Project(This,newSystem,result)

#define ILineString_Extent2D(This,minX,minY,maxX,maxY)	\
    (This)->lpVtbl -> Extent2D(This,minX,minY,maxX,maxY)


#define ILineString_get_Length(This,value)	\
    (This)->lpVtbl -> get_Length(This,value)

#define ILineString_StartPoint(This,sp)	\
    (This)->lpVtbl -> StartPoint(This,sp)

#define ILineString_EndPoint(This,ep)	\
    (This)->lpVtbl -> EndPoint(This,ep)

#define ILineString_get_IsClosed(This,isClosed)	\
    (This)->lpVtbl -> get_IsClosed(This,isClosed)

#define ILineString_Value(This,t,p)	\
    (This)->lpVtbl -> Value(This,t,p)


#define ILineString_get_NumPoints(This,numPoints)	\
    (This)->lpVtbl -> get_NumPoints(This,numPoints)

#define ILineString_Point(This,index,point)	\
    (This)->lpVtbl -> Point(This,index,point)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE ILineString_get_NumPoints_Proxy( 
    ILineString * This,
    /* [retval][out] */ long *numPoints);


void __RPC_STUB ILineString_get_NumPoints_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ILineString_Point_Proxy( 
    ILineString * This,
    /* [in] */ long index,
    /* [retval][out] */ IPoint **point);


void __RPC_STUB ILineString_Point_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILineString_INTERFACE_DEFINED__ */


#ifndef __ILinearRing_INTERFACE_DEFINED__
#define __ILinearRing_INTERFACE_DEFINED__

/* interface ILinearRing */
/* [uuid][object] */ 


EXTERN_C const IID IID_ILinearRing;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6A124038-FE38-11d0-BECE-00805F7C4268")
    ILinearRing : public ILineString
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ILinearRingVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILinearRing * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILinearRing * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILinearRing * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dimension )( 
            ILinearRing * This,
            /* [retval][out] */ long *dimension);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_SpatialReference )( 
            ILinearRing * This,
            /* [retval][out] */ ISpatialReference **spatialRef);
        
        /* [propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SpatialReference )( 
            ILinearRing * This,
            /* [in] */ ISpatialReference *spatialRef);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsEmpty )( 
            ILinearRing * This,
            /* [retval][out] */ VARIANT_BOOL *isEmpty);
        
        HRESULT ( STDMETHODCALLTYPE *SetEmpty )( 
            ILinearRing * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsSimple )( 
            ILinearRing * This,
            /* [retval][out] */ VARIANT_BOOL *isSimple);
        
        HRESULT ( STDMETHODCALLTYPE *Envelope )( 
            ILinearRing * This,
            /* [retval][out] */ IGeometry **envelope);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ILinearRing * This,
            /* [retval][out] */ IGeometry **newShape);
        
        HRESULT ( STDMETHODCALLTYPE *Project )( 
            ILinearRing * This,
            /* [in] */ ISpatialReference *newSystem,
            /* [retval][out] */ IGeometry **result);
        
        HRESULT ( STDMETHODCALLTYPE *Extent2D )( 
            ILinearRing * This,
            /* [out] */ double *minX,
            /* [out] */ double *minY,
            /* [out] */ double *maxX,
            /* [out] */ double *maxY);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            ILinearRing * This,
            /* [retval][out] */ double *value);
        
        HRESULT ( STDMETHODCALLTYPE *StartPoint )( 
            ILinearRing * This,
            /* [retval][out] */ IPoint **sp);
        
        HRESULT ( STDMETHODCALLTYPE *EndPoint )( 
            ILinearRing * This,
            /* [retval][out] */ IPoint **ep);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsClosed )( 
            ILinearRing * This,
            /* [retval][out] */ VARIANT_BOOL *isClosed);
        
        HRESULT ( STDMETHODCALLTYPE *Value )( 
            ILinearRing * This,
            /* [in] */ double t,
            /* [retval][out] */ IPoint **p);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_NumPoints )( 
            ILinearRing * This,
            /* [retval][out] */ long *numPoints);
        
        HRESULT ( STDMETHODCALLTYPE *Point )( 
            ILinearRing * This,
            /* [in] */ long index,
            /* [retval][out] */ IPoint **point);
        
        END_INTERFACE
    } ILinearRingVtbl;

    interface ILinearRing
    {
        CONST_VTBL struct ILinearRingVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILinearRing_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILinearRing_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILinearRing_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILinearRing_get_Dimension(This,dimension)	\
    (This)->lpVtbl -> get_Dimension(This,dimension)

#define ILinearRing_get_SpatialReference(This,spatialRef)	\
    (This)->lpVtbl -> get_SpatialReference(This,spatialRef)

#define ILinearRing_putref_SpatialReference(This,spatialRef)	\
    (This)->lpVtbl -> putref_SpatialReference(This,spatialRef)

#define ILinearRing_get_IsEmpty(This,isEmpty)	\
    (This)->lpVtbl -> get_IsEmpty(This,isEmpty)

#define ILinearRing_SetEmpty(This)	\
    (This)->lpVtbl -> SetEmpty(This)

#define ILinearRing_get_IsSimple(This,isSimple)	\
    (This)->lpVtbl -> get_IsSimple(This,isSimple)

#define ILinearRing_Envelope(This,envelope)	\
    (This)->lpVtbl -> Envelope(This,envelope)

#define ILinearRing_Clone(This,newShape)	\
    (This)->lpVtbl -> Clone(This,newShape)

#define ILinearRing_Project(This,newSystem,result)	\
    (This)->lpVtbl -> Project(This,newSystem,result)

#define ILinearRing_Extent2D(This,minX,minY,maxX,maxY)	\
    (This)->lpVtbl -> Extent2D(This,minX,minY,maxX,maxY)


#define ILinearRing_get_Length(This,value)	\
    (This)->lpVtbl -> get_Length(This,value)

#define ILinearRing_StartPoint(This,sp)	\
    (This)->lpVtbl -> StartPoint(This,sp)

#define ILinearRing_EndPoint(This,ep)	\
    (This)->lpVtbl -> EndPoint(This,ep)

#define ILinearRing_get_IsClosed(This,isClosed)	\
    (This)->lpVtbl -> get_IsClosed(This,isClosed)

#define ILinearRing_Value(This,t,p)	\
    (This)->lpVtbl -> Value(This,t,p)


#define ILinearRing_get_NumPoints(This,numPoints)	\
    (This)->lpVtbl -> get_NumPoints(This,numPoints)

#define ILinearRing_Point(This,index,point)	\
    (This)->lpVtbl -> Point(This,index,point)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILinearRing_INTERFACE_DEFINED__ */


#ifndef __ISurface_INTERFACE_DEFINED__
#define __ISurface_INTERFACE_DEFINED__

/* interface ISurface */
/* [uuid][object] */ 


EXTERN_C const IID IID_ISurface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6A124039-FE38-11d0-BECE-00805F7C4268")
    ISurface : public IGeometry
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Area( 
            /* [retval][out] */ double *area) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Centroid( 
            /* [retval][out] */ IPoint **result) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PointOnSurface( 
            /* [retval][out] */ IPoint **result) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISurfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISurface * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISurface * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISurface * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dimension )( 
            ISurface * This,
            /* [retval][out] */ long *dimension);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_SpatialReference )( 
            ISurface * This,
            /* [retval][out] */ ISpatialReference **spatialRef);
        
        /* [propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SpatialReference )( 
            ISurface * This,
            /* [in] */ ISpatialReference *spatialRef);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsEmpty )( 
            ISurface * This,
            /* [retval][out] */ VARIANT_BOOL *isEmpty);
        
        HRESULT ( STDMETHODCALLTYPE *SetEmpty )( 
            ISurface * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsSimple )( 
            ISurface * This,
            /* [retval][out] */ VARIANT_BOOL *isSimple);
        
        HRESULT ( STDMETHODCALLTYPE *Envelope )( 
            ISurface * This,
            /* [retval][out] */ IGeometry **envelope);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISurface * This,
            /* [retval][out] */ IGeometry **newShape);
        
        HRESULT ( STDMETHODCALLTYPE *Project )( 
            ISurface * This,
            /* [in] */ ISpatialReference *newSystem,
            /* [retval][out] */ IGeometry **result);
        
        HRESULT ( STDMETHODCALLTYPE *Extent2D )( 
            ISurface * This,
            /* [out] */ double *minX,
            /* [out] */ double *minY,
            /* [out] */ double *maxX,
            /* [out] */ double *maxY);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Area )( 
            ISurface * This,
            /* [retval][out] */ double *area);
        
        HRESULT ( STDMETHODCALLTYPE *Centroid )( 
            ISurface * This,
            /* [retval][out] */ IPoint **result);
        
        HRESULT ( STDMETHODCALLTYPE *PointOnSurface )( 
            ISurface * This,
            /* [retval][out] */ IPoint **result);
        
        END_INTERFACE
    } ISurfaceVtbl;

    interface ISurface
    {
        CONST_VTBL struct ISurfaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISurface_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISurface_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISurface_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISurface_get_Dimension(This,dimension)	\
    (This)->lpVtbl -> get_Dimension(This,dimension)

#define ISurface_get_SpatialReference(This,spatialRef)	\
    (This)->lpVtbl -> get_SpatialReference(This,spatialRef)

#define ISurface_putref_SpatialReference(This,spatialRef)	\
    (This)->lpVtbl -> putref_SpatialReference(This,spatialRef)

#define ISurface_get_IsEmpty(This,isEmpty)	\
    (This)->lpVtbl -> get_IsEmpty(This,isEmpty)

#define ISurface_SetEmpty(This)	\
    (This)->lpVtbl -> SetEmpty(This)

#define ISurface_get_IsSimple(This,isSimple)	\
    (This)->lpVtbl -> get_IsSimple(This,isSimple)

#define ISurface_Envelope(This,envelope)	\
    (This)->lpVtbl -> Envelope(This,envelope)

#define ISurface_Clone(This,newShape)	\
    (This)->lpVtbl -> Clone(This,newShape)

#define ISurface_Project(This,newSystem,result)	\
    (This)->lpVtbl -> Project(This,newSystem,result)

#define ISurface_Extent2D(This,minX,minY,maxX,maxY)	\
    (This)->lpVtbl -> Extent2D(This,minX,minY,maxX,maxY)


#define ISurface_get_Area(This,area)	\
    (This)->lpVtbl -> get_Area(This,area)

#define ISurface_Centroid(This,result)	\
    (This)->lpVtbl -> Centroid(This,result)

#define ISurface_PointOnSurface(This,result)	\
    (This)->lpVtbl -> PointOnSurface(This,result)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE ISurface_get_Area_Proxy( 
    ISurface * This,
    /* [retval][out] */ double *area);


void __RPC_STUB ISurface_get_Area_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISurface_Centroid_Proxy( 
    ISurface * This,
    /* [retval][out] */ IPoint **result);


void __RPC_STUB ISurface_Centroid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISurface_PointOnSurface_Proxy( 
    ISurface * This,
    /* [retval][out] */ IPoint **result);


void __RPC_STUB ISurface_PointOnSurface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISurface_INTERFACE_DEFINED__ */


#ifndef __IGeometryCollection_INTERFACE_DEFINED__
#define __IGeometryCollection_INTERFACE_DEFINED__

/* interface IGeometryCollection */
/* [uuid][object] */ 


EXTERN_C const IID IID_IGeometryCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6A12403A-FE38-11d0-BECE-00805F7C4268")
    IGeometryCollection : public IGeometry
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_NumGeometries( 
            /* [retval][out] */ long *numberOf) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Geometry( 
            /* [in] */ long index,
            /* [retval][out] */ IGeometry **geometry) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGeometryCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGeometryCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGeometryCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGeometryCollection * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dimension )( 
            IGeometryCollection * This,
            /* [retval][out] */ long *dimension);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_SpatialReference )( 
            IGeometryCollection * This,
            /* [retval][out] */ ISpatialReference **spatialRef);
        
        /* [propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SpatialReference )( 
            IGeometryCollection * This,
            /* [in] */ ISpatialReference *spatialRef);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsEmpty )( 
            IGeometryCollection * This,
            /* [retval][out] */ VARIANT_BOOL *isEmpty);
        
        HRESULT ( STDMETHODCALLTYPE *SetEmpty )( 
            IGeometryCollection * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsSimple )( 
            IGeometryCollection * This,
            /* [retval][out] */ VARIANT_BOOL *isSimple);
        
        HRESULT ( STDMETHODCALLTYPE *Envelope )( 
            IGeometryCollection * This,
            /* [retval][out] */ IGeometry **envelope);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IGeometryCollection * This,
            /* [retval][out] */ IGeometry **newShape);
        
        HRESULT ( STDMETHODCALLTYPE *Project )( 
            IGeometryCollection * This,
            /* [in] */ ISpatialReference *newSystem,
            /* [retval][out] */ IGeometry **result);
        
        HRESULT ( STDMETHODCALLTYPE *Extent2D )( 
            IGeometryCollection * This,
            /* [out] */ double *minX,
            /* [out] */ double *minY,
            /* [out] */ double *maxX,
            /* [out] */ double *maxY);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_NumGeometries )( 
            IGeometryCollection * This,
            /* [retval][out] */ long *numberOf);
        
        HRESULT ( STDMETHODCALLTYPE *Geometry )( 
            IGeometryCollection * This,
            /* [in] */ long index,
            /* [retval][out] */ IGeometry **geometry);
        
        END_INTERFACE
    } IGeometryCollectionVtbl;

    interface IGeometryCollection
    {
        CONST_VTBL struct IGeometryCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGeometryCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGeometryCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGeometryCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGeometryCollection_get_Dimension(This,dimension)	\
    (This)->lpVtbl -> get_Dimension(This,dimension)

#define IGeometryCollection_get_SpatialReference(This,spatialRef)	\
    (This)->lpVtbl -> get_SpatialReference(This,spatialRef)

#define IGeometryCollection_putref_SpatialReference(This,spatialRef)	\
    (This)->lpVtbl -> putref_SpatialReference(This,spatialRef)

#define IGeometryCollection_get_IsEmpty(This,isEmpty)	\
    (This)->lpVtbl -> get_IsEmpty(This,isEmpty)

#define IGeometryCollection_SetEmpty(This)	\
    (This)->lpVtbl -> SetEmpty(This)

#define IGeometryCollection_get_IsSimple(This,isSimple)	\
    (This)->lpVtbl -> get_IsSimple(This,isSimple)

#define IGeometryCollection_Envelope(This,envelope)	\
    (This)->lpVtbl -> Envelope(This,envelope)

#define IGeometryCollection_Clone(This,newShape)	\
    (This)->lpVtbl -> Clone(This,newShape)

#define IGeometryCollection_Project(This,newSystem,result)	\
    (This)->lpVtbl -> Project(This,newSystem,result)

#define IGeometryCollection_Extent2D(This,minX,minY,maxX,maxY)	\
    (This)->lpVtbl -> Extent2D(This,minX,minY,maxX,maxY)


#define IGeometryCollection_get_NumGeometries(This,numberOf)	\
    (This)->lpVtbl -> get_NumGeometries(This,numberOf)

#define IGeometryCollection_Geometry(This,index,geometry)	\
    (This)->lpVtbl -> Geometry(This,index,geometry)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IGeometryCollection_get_NumGeometries_Proxy( 
    IGeometryCollection * This,
    /* [retval][out] */ long *numberOf);


void __RPC_STUB IGeometryCollection_get_NumGeometries_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGeometryCollection_Geometry_Proxy( 
    IGeometryCollection * This,
    /* [in] */ long index,
    /* [retval][out] */ IGeometry **geometry);


void __RPC_STUB IGeometryCollection_Geometry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGeometryCollection_INTERFACE_DEFINED__ */


#ifndef __IPolygon_INTERFACE_DEFINED__
#define __IPolygon_INTERFACE_DEFINED__

/* interface IPolygon */
/* [uuid][object] */ 


EXTERN_C const IID IID_IPolygon;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6A12403C-FE38-11d0-BECE-00805F7C4268")
    IPolygon : public ISurface
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ExteriorRing( 
            /* [retval][out] */ ILinearRing **exteriorRing) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_NumInteriorRings( 
            /* [retval][out] */ long *count) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InteriorRing( 
            /* [in] */ long index,
            /* [retval][out] */ ILinearRing **interiorRing) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPolygonVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPolygon * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPolygon * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPolygon * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dimension )( 
            IPolygon * This,
            /* [retval][out] */ long *dimension);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_SpatialReference )( 
            IPolygon * This,
            /* [retval][out] */ ISpatialReference **spatialRef);
        
        /* [propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SpatialReference )( 
            IPolygon * This,
            /* [in] */ ISpatialReference *spatialRef);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsEmpty )( 
            IPolygon * This,
            /* [retval][out] */ VARIANT_BOOL *isEmpty);
        
        HRESULT ( STDMETHODCALLTYPE *SetEmpty )( 
            IPolygon * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsSimple )( 
            IPolygon * This,
            /* [retval][out] */ VARIANT_BOOL *isSimple);
        
        HRESULT ( STDMETHODCALLTYPE *Envelope )( 
            IPolygon * This,
            /* [retval][out] */ IGeometry **envelope);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IPolygon * This,
            /* [retval][out] */ IGeometry **newShape);
        
        HRESULT ( STDMETHODCALLTYPE *Project )( 
            IPolygon * This,
            /* [in] */ ISpatialReference *newSystem,
            /* [retval][out] */ IGeometry **result);
        
        HRESULT ( STDMETHODCALLTYPE *Extent2D )( 
            IPolygon * This,
            /* [out] */ double *minX,
            /* [out] */ double *minY,
            /* [out] */ double *maxX,
            /* [out] */ double *maxY);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Area )( 
            IPolygon * This,
            /* [retval][out] */ double *area);
        
        HRESULT ( STDMETHODCALLTYPE *Centroid )( 
            IPolygon * This,
            /* [retval][out] */ IPoint **result);
        
        HRESULT ( STDMETHODCALLTYPE *PointOnSurface )( 
            IPolygon * This,
            /* [retval][out] */ IPoint **result);
        
        HRESULT ( STDMETHODCALLTYPE *ExteriorRing )( 
            IPolygon * This,
            /* [retval][out] */ ILinearRing **exteriorRing);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_NumInteriorRings )( 
            IPolygon * This,
            /* [retval][out] */ long *count);
        
        HRESULT ( STDMETHODCALLTYPE *InteriorRing )( 
            IPolygon * This,
            /* [in] */ long index,
            /* [retval][out] */ ILinearRing **interiorRing);
        
        END_INTERFACE
    } IPolygonVtbl;

    interface IPolygon
    {
        CONST_VTBL struct IPolygonVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPolygon_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPolygon_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPolygon_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPolygon_get_Dimension(This,dimension)	\
    (This)->lpVtbl -> get_Dimension(This,dimension)

#define IPolygon_get_SpatialReference(This,spatialRef)	\
    (This)->lpVtbl -> get_SpatialReference(This,spatialRef)

#define IPolygon_putref_SpatialReference(This,spatialRef)	\
    (This)->lpVtbl -> putref_SpatialReference(This,spatialRef)

#define IPolygon_get_IsEmpty(This,isEmpty)	\
    (This)->lpVtbl -> get_IsEmpty(This,isEmpty)

#define IPolygon_SetEmpty(This)	\
    (This)->lpVtbl -> SetEmpty(This)

#define IPolygon_get_IsSimple(This,isSimple)	\
    (This)->lpVtbl -> get_IsSimple(This,isSimple)

#define IPolygon_Envelope(This,envelope)	\
    (This)->lpVtbl -> Envelope(This,envelope)

#define IPolygon_Clone(This,newShape)	\
    (This)->lpVtbl -> Clone(This,newShape)

#define IPolygon_Project(This,newSystem,result)	\
    (This)->lpVtbl -> Project(This,newSystem,result)

#define IPolygon_Extent2D(This,minX,minY,maxX,maxY)	\
    (This)->lpVtbl -> Extent2D(This,minX,minY,maxX,maxY)


#define IPolygon_get_Area(This,area)	\
    (This)->lpVtbl -> get_Area(This,area)

#define IPolygon_Centroid(This,result)	\
    (This)->lpVtbl -> Centroid(This,result)

#define IPolygon_PointOnSurface(This,result)	\
    (This)->lpVtbl -> PointOnSurface(This,result)


#define IPolygon_ExteriorRing(This,exteriorRing)	\
    (This)->lpVtbl -> ExteriorRing(This,exteriorRing)

#define IPolygon_get_NumInteriorRings(This,count)	\
    (This)->lpVtbl -> get_NumInteriorRings(This,count)

#define IPolygon_InteriorRing(This,index,interiorRing)	\
    (This)->lpVtbl -> InteriorRing(This,index,interiorRing)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPolygon_ExteriorRing_Proxy( 
    IPolygon * This,
    /* [retval][out] */ ILinearRing **exteriorRing);


void __RPC_STUB IPolygon_ExteriorRing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPolygon_get_NumInteriorRings_Proxy( 
    IPolygon * This,
    /* [retval][out] */ long *count);


void __RPC_STUB IPolygon_get_NumInteriorRings_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPolygon_InteriorRing_Proxy( 
    IPolygon * This,
    /* [in] */ long index,
    /* [retval][out] */ ILinearRing **interiorRing);


void __RPC_STUB IPolygon_InteriorRing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPolygon_INTERFACE_DEFINED__ */


#ifndef __IMultiCurve_INTERFACE_DEFINED__
#define __IMultiCurve_INTERFACE_DEFINED__

/* interface IMultiCurve */
/* [uuid][object] */ 


EXTERN_C const IID IID_IMultiCurve;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6A12403D-FE38-11d0-BECE-00805F7C4268")
    IMultiCurve : public IGeometryCollection
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ double *length) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_IsClosed( 
            /* [retval][out] */ VARIANT_BOOL *isClosed) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMultiCurveVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMultiCurve * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMultiCurve * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMultiCurve * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dimension )( 
            IMultiCurve * This,
            /* [retval][out] */ long *dimension);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_SpatialReference )( 
            IMultiCurve * This,
            /* [retval][out] */ ISpatialReference **spatialRef);
        
        /* [propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SpatialReference )( 
            IMultiCurve * This,
            /* [in] */ ISpatialReference *spatialRef);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsEmpty )( 
            IMultiCurve * This,
            /* [retval][out] */ VARIANT_BOOL *isEmpty);
        
        HRESULT ( STDMETHODCALLTYPE *SetEmpty )( 
            IMultiCurve * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsSimple )( 
            IMultiCurve * This,
            /* [retval][out] */ VARIANT_BOOL *isSimple);
        
        HRESULT ( STDMETHODCALLTYPE *Envelope )( 
            IMultiCurve * This,
            /* [retval][out] */ IGeometry **envelope);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IMultiCurve * This,
            /* [retval][out] */ IGeometry **newShape);
        
        HRESULT ( STDMETHODCALLTYPE *Project )( 
            IMultiCurve * This,
            /* [in] */ ISpatialReference *newSystem,
            /* [retval][out] */ IGeometry **result);
        
        HRESULT ( STDMETHODCALLTYPE *Extent2D )( 
            IMultiCurve * This,
            /* [out] */ double *minX,
            /* [out] */ double *minY,
            /* [out] */ double *maxX,
            /* [out] */ double *maxY);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_NumGeometries )( 
            IMultiCurve * This,
            /* [retval][out] */ long *numberOf);
        
        HRESULT ( STDMETHODCALLTYPE *Geometry )( 
            IMultiCurve * This,
            /* [in] */ long index,
            /* [retval][out] */ IGeometry **geometry);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IMultiCurve * This,
            /* [retval][out] */ double *length);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsClosed )( 
            IMultiCurve * This,
            /* [retval][out] */ VARIANT_BOOL *isClosed);
        
        END_INTERFACE
    } IMultiCurveVtbl;

    interface IMultiCurve
    {
        CONST_VTBL struct IMultiCurveVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMultiCurve_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMultiCurve_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMultiCurve_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMultiCurve_get_Dimension(This,dimension)	\
    (This)->lpVtbl -> get_Dimension(This,dimension)

#define IMultiCurve_get_SpatialReference(This,spatialRef)	\
    (This)->lpVtbl -> get_SpatialReference(This,spatialRef)

#define IMultiCurve_putref_SpatialReference(This,spatialRef)	\
    (This)->lpVtbl -> putref_SpatialReference(This,spatialRef)

#define IMultiCurve_get_IsEmpty(This,isEmpty)	\
    (This)->lpVtbl -> get_IsEmpty(This,isEmpty)

#define IMultiCurve_SetEmpty(This)	\
    (This)->lpVtbl -> SetEmpty(This)

#define IMultiCurve_get_IsSimple(This,isSimple)	\
    (This)->lpVtbl -> get_IsSimple(This,isSimple)

#define IMultiCurve_Envelope(This,envelope)	\
    (This)->lpVtbl -> Envelope(This,envelope)

#define IMultiCurve_Clone(This,newShape)	\
    (This)->lpVtbl -> Clone(This,newShape)

#define IMultiCurve_Project(This,newSystem,result)	\
    (This)->lpVtbl -> Project(This,newSystem,result)

#define IMultiCurve_Extent2D(This,minX,minY,maxX,maxY)	\
    (This)->lpVtbl -> Extent2D(This,minX,minY,maxX,maxY)


#define IMultiCurve_get_NumGeometries(This,numberOf)	\
    (This)->lpVtbl -> get_NumGeometries(This,numberOf)

#define IMultiCurve_Geometry(This,index,geometry)	\
    (This)->lpVtbl -> Geometry(This,index,geometry)


#define IMultiCurve_get_Length(This,length)	\
    (This)->lpVtbl -> get_Length(This,length)

#define IMultiCurve_get_IsClosed(This,isClosed)	\
    (This)->lpVtbl -> get_IsClosed(This,isClosed)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IMultiCurve_get_Length_Proxy( 
    IMultiCurve * This,
    /* [retval][out] */ double *length);


void __RPC_STUB IMultiCurve_get_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IMultiCurve_get_IsClosed_Proxy( 
    IMultiCurve * This,
    /* [retval][out] */ VARIANT_BOOL *isClosed);


void __RPC_STUB IMultiCurve_get_IsClosed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMultiCurve_INTERFACE_DEFINED__ */


#ifndef __IMultiSurface_INTERFACE_DEFINED__
#define __IMultiSurface_INTERFACE_DEFINED__

/* interface IMultiSurface */
/* [uuid][object] */ 


EXTERN_C const IID IID_IMultiSurface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6A12403F-FE38-11d0-BECE-00805F7C4268")
    IMultiSurface : public IGeometryCollection
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Area( 
            /* [retval][out] */ double *area) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Centroid( 
            /* [retval][out] */ IPoint **result) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PointOnSurface( 
            /* [retval][out] */ IPoint **result) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMultiSurfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMultiSurface * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMultiSurface * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMultiSurface * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dimension )( 
            IMultiSurface * This,
            /* [retval][out] */ long *dimension);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_SpatialReference )( 
            IMultiSurface * This,
            /* [retval][out] */ ISpatialReference **spatialRef);
        
        /* [propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_SpatialReference )( 
            IMultiSurface * This,
            /* [in] */ ISpatialReference *spatialRef);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsEmpty )( 
            IMultiSurface * This,
            /* [retval][out] */ VARIANT_BOOL *isEmpty);
        
        HRESULT ( STDMETHODCALLTYPE *SetEmpty )( 
            IMultiSurface * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsSimple )( 
            IMultiSurface * This,
            /* [retval][out] */ VARIANT_BOOL *isSimple);
        
        HRESULT ( STDMETHODCALLTYPE *Envelope )( 
            IMultiSurface * This,
            /* [retval][out] */ IGeometry **envelope);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IMultiSurface * This,
            /* [retval][out] */ IGeometry **newShape);
        
        HRESULT ( STDMETHODCALLTYPE *Project )( 
            IMultiSurface * This,
            /* [in] */ ISpatialReference *newSystem,
            /* [retval][out] */ IGeometry **result);
        
        HRESULT ( STDMETHODCALLTYPE *Extent2D )( 
            IMultiSurface * This,
            /* [out] */ double *minX,
            /* [out] */ double *minY,
            /* [out] */ double *maxX,
            /* [out] */ double *maxY);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_NumGeometries )( 
            IMultiSurface * This,
            /* [retval][out] */ long *numberOf);
        
        HRESULT ( STDMETHODCALLTYPE *Geometry )( 
            IMultiSurface * This,
            /* [in] */ long index,
            /* [retval][out] */ IGeometry **geometry);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Area )( 
            IMultiSurface * This,
            /* [retval][out] */ double *area);
        
        HRESULT ( STDMETHODCALLTYPE *Centroid )( 
            IMultiSurface * This,
            /* [retval][out] */ IPoint **result);
        
        HRESULT ( STDMETHODCALLTYPE *PointOnSurface )( 
            IMultiSurface * This,
            /* [retval][out] */ IPoint **result);
        
        END_INTERFACE
    } IMultiSurfaceVtbl;

    interface IMultiSurface
    {
        CONST_VTBL struct IMultiSurfaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMultiSurface_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMultiSurface_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMultiSurface_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMultiSurface_get_Dimension(This,dimension)	\
    (This)->lpVtbl -> get_Dimension(This,dimension)

#define IMultiSurface_get_SpatialReference(This,spatialRef)	\
    (This)->lpVtbl -> get_SpatialReference(This,spatialRef)

#define IMultiSurface_putref_SpatialReference(This,spatialRef)	\
    (This)->lpVtbl -> putref_SpatialReference(This,spatialRef)

#define IMultiSurface_get_IsEmpty(This,isEmpty)	\
    (This)->lpVtbl -> get_IsEmpty(This,isEmpty)

#define IMultiSurface_SetEmpty(This)	\
    (This)->lpVtbl -> SetEmpty(This)

#define IMultiSurface_get_IsSimple(This,isSimple)	\
    (This)->lpVtbl -> get_IsSimple(This,isSimple)

#define IMultiSurface_Envelope(This,envelope)	\
    (This)->lpVtbl -> Envelope(This,envelope)

#define IMultiSurface_Clone(This,newShape)	\
    (This)->lpVtbl -> Clone(This,newShape)

#define IMultiSurface_Project(This,newSystem,result)	\
    (This)->lpVtbl -> Project(This,newSystem,result)

#define IMultiSurface_Extent2D(This,minX,minY,maxX,maxY)	\
    (This)->lpVtbl -> Extent2D(This,minX,minY,maxX,maxY)


#define IMultiSurface_get_NumGeometries(This,numberOf)	\
    (This)->lpVtbl -> get_NumGeometries(This,numberOf)

#define IMultiSurface_Geometry(This,index,geometry)	\
    (This)->lpVtbl -> Geometry(This,index,geometry)


#define IMultiSurface_get_Area(This,area)	\
    (This)->lpVtbl -> get_Area(This,area)

#define IMultiSurface_Centroid(This,result)	\
    (This)->lpVtbl -> Centroid(This,result)

#define IMultiSurface_PointOnSurface(This,result)	\
    (This)->lpVtbl -> PointOnSurface(This,result)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IMultiSurface_get_Area_Proxy( 
    IMultiSurface * This,
    /* [retval][out] */ double *area);


void __RPC_STUB IMultiSurface_get_Area_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMultiSurface_Centroid_Proxy( 
    IMultiSurface * This,
    /* [retval][out] */ IPoint **result);


void __RPC_STUB IMultiSurface_Centroid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMultiSurface_PointOnSurface_Proxy( 
    IMultiSurface * This,
    /* [retval][out] */ IPoint **result);


void __RPC_STUB IMultiSurface_PointOnSurface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMultiSurface_INTERFACE_DEFINED__ */


#ifndef __ISpatialRelation_INTERFACE_DEFINED__
#define __ISpatialRelation_INTERFACE_DEFINED__

/* interface ISpatialRelation */
/* [uuid][object] */ 


EXTERN_C const IID IID_ISpatialRelation;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6A124040-FE38-11d0-BECE-00805F7C4268")
    ISpatialRelation : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Equals( 
            /* [in] */ IGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *equals) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Touches( 
            /* [in] */ IGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *touches) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Contains( 
            /* [in] */ IGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *contains) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Within( 
            /* [in] */ IGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *within) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Disjoint( 
            /* [in] */ IGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *disjoint) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Crosses( 
            /* [in] */ IGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *crosses) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Overlaps( 
            /* [in] */ IGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *overlaps) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Intersects( 
            /* [in] */ IGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *overlaps) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISpatialRelationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISpatialRelation * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISpatialRelation * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISpatialRelation * This);
        
        HRESULT ( STDMETHODCALLTYPE *Equals )( 
            ISpatialRelation * This,
            /* [in] */ IGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *equals);
        
        HRESULT ( STDMETHODCALLTYPE *Touches )( 
            ISpatialRelation * This,
            /* [in] */ IGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *touches);
        
        HRESULT ( STDMETHODCALLTYPE *Contains )( 
            ISpatialRelation * This,
            /* [in] */ IGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *contains);
        
        HRESULT ( STDMETHODCALLTYPE *Within )( 
            ISpatialRelation * This,
            /* [in] */ IGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *within);
        
        HRESULT ( STDMETHODCALLTYPE *Disjoint )( 
            ISpatialRelation * This,
            /* [in] */ IGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *disjoint);
        
        HRESULT ( STDMETHODCALLTYPE *Crosses )( 
            ISpatialRelation * This,
            /* [in] */ IGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *crosses);
        
        HRESULT ( STDMETHODCALLTYPE *Overlaps )( 
            ISpatialRelation * This,
            /* [in] */ IGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *overlaps);
        
        HRESULT ( STDMETHODCALLTYPE *Intersects )( 
            ISpatialRelation * This,
            /* [in] */ IGeometry *other,
            /* [retval][out] */ VARIANT_BOOL *overlaps);
        
        END_INTERFACE
    } ISpatialRelationVtbl;

    interface ISpatialRelation
    {
        CONST_VTBL struct ISpatialRelationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISpatialRelation_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISpatialRelation_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISpatialRelation_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISpatialRelation_Equals(This,other,equals)	\
    (This)->lpVtbl -> Equals(This,other,equals)

#define ISpatialRelation_Touches(This,other,touches)	\
    (This)->lpVtbl -> Touches(This,other,touches)

#define ISpatialRelation_Contains(This,other,contains)	\
    (This)->lpVtbl -> Contains(This,other,contains)

#define ISpatialRelation_Within(This,other,within)	\
    (This)->lpVtbl -> Within(This,other,within)

#define ISpatialRelation_Disjoint(This,other,disjoint)	\
    (This)->lpVtbl -> Disjoint(This,other,disjoint)

#define ISpatialRelation_Crosses(This,other,crosses)	\
    (This)->lpVtbl -> Crosses(This,other,crosses)

#define ISpatialRelation_Overlaps(This,other,overlaps)	\
    (This)->lpVtbl -> Overlaps(This,other,overlaps)

#define ISpatialRelation_Intersects(This,other,overlaps)	\
    (This)->lpVtbl -> Intersects(This,other,overlaps)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISpatialRelation_Equals_Proxy( 
    ISpatialRelation * This,
    /* [in] */ IGeometry *other,
    /* [retval][out] */ VARIANT_BOOL *equals);


void __RPC_STUB ISpatialRelation_Equals_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISpatialRelation_Touches_Proxy( 
    ISpatialRelation * This,
    /* [in] */ IGeometry *other,
    /* [retval][out] */ VARIANT_BOOL *touches);


void __RPC_STUB ISpatialRelation_Touches_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISpatialRelation_Contains_Proxy( 
    ISpatialRelation * This,
    /* [in] */ IGeometry *other,
    /* [retval][out] */ VARIANT_BOOL *contains);


void __RPC_STUB ISpatialRelation_Contains_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISpatialRelation_Within_Proxy( 
    ISpatialRelation * This,
    /* [in] */ IGeometry *other,
    /* [retval][out] */ VARIANT_BOOL *within);


void __RPC_STUB ISpatialRelation_Within_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISpatialRelation_Disjoint_Proxy( 
    ISpatialRelation * This,
    /* [in] */ IGeometry *other,
    /* [retval][out] */ VARIANT_BOOL *disjoint);


void __RPC_STUB ISpatialRelation_Disjoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISpatialRelation_Crosses_Proxy( 
    ISpatialRelation * This,
    /* [in] */ IGeometry *other,
    /* [retval][out] */ VARIANT_BOOL *crosses);


void __RPC_STUB ISpatialRelation_Crosses_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISpatialRelation_Overlaps_Proxy( 
    ISpatialRelation * This,
    /* [in] */ IGeometry *other,
    /* [retval][out] */ VARIANT_BOOL *overlaps);


void __RPC_STUB ISpatialRelation_Overlaps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISpatialRelation_Intersects_Proxy( 
    ISpatialRelation * This,
    /* [in] */ IGeometry *other,
    /* [retval][out] */ VARIANT_BOOL *overlaps);


void __RPC_STUB ISpatialRelation_Intersects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISpatialRelation_INTERFACE_DEFINED__ */


#ifndef __ISpatialRelation2_INTERFACE_DEFINED__
#define __ISpatialRelation2_INTERFACE_DEFINED__

/* interface ISpatialRelation2 */
/* [uuid][object] */ 


EXTERN_C const IID IID_ISpatialRelation2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6A124041-FE38-11d0-BECE-00805F7C4268")
    ISpatialRelation2 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Relate( 
            /* [in] */ IGeometry *other,
            /* [in] */ BSTR patternMatrix,
            /* [retval][out] */ VARIANT_BOOL *isRelated) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISpatialRelation2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISpatialRelation2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISpatialRelation2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISpatialRelation2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *Relate )( 
            ISpatialRelation2 * This,
            /* [in] */ IGeometry *other,
            /* [in] */ BSTR patternMatrix,
            /* [retval][out] */ VARIANT_BOOL *isRelated);
        
        END_INTERFACE
    } ISpatialRelation2Vtbl;

    interface ISpatialRelation2
    {
        CONST_VTBL struct ISpatialRelation2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISpatialRelation2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISpatialRelation2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISpatialRelation2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISpatialRelation2_Relate(This,other,patternMatrix,isRelated)	\
    (This)->lpVtbl -> Relate(This,other,patternMatrix,isRelated)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISpatialRelation2_Relate_Proxy( 
    ISpatialRelation2 * This,
    /* [in] */ IGeometry *other,
    /* [in] */ BSTR patternMatrix,
    /* [retval][out] */ VARIANT_BOOL *isRelated);


void __RPC_STUB ISpatialRelation2_Relate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISpatialRelation2_INTERFACE_DEFINED__ */


#ifndef __ISpatialOperator_INTERFACE_DEFINED__
#define __ISpatialOperator_INTERFACE_DEFINED__

/* interface ISpatialOperator */
/* [uuid][object] */ 


EXTERN_C const IID IID_ISpatialOperator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6A124042-FE38-11d0-BECE-00805F7C4268")
    ISpatialOperator : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Distance( 
            /* [in] */ IGeometry *other,
            /* [retval][out] */ double *distance) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Boundary( 
            /* [retval][out] */ IGeometry **boundary) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Buffer( 
            /* [in] */ double distance,
            /* [retval][out] */ IGeometry **result) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConvexHull( 
            /* [retval][out] */ IGeometry **result) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Intersection( 
            /* [in] */ IGeometry *other,
            /* [retval][out] */ IGeometry **result) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Union( 
            /* [in] */ IGeometry *other,
            /* [retval][out] */ IGeometry **result) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Difference( 
            /* [in] */ IGeometry *other,
            /* [retval][out] */ IGeometry **result) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SymmetricDifference( 
            /* [in] */ IGeometry *other,
            /* [retval][out] */ IGeometry **result) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISpatialOperatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISpatialOperator * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISpatialOperator * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISpatialOperator * This);
        
        HRESULT ( STDMETHODCALLTYPE *Distance )( 
            ISpatialOperator * This,
            /* [in] */ IGeometry *other,
            /* [retval][out] */ double *distance);
        
        HRESULT ( STDMETHODCALLTYPE *Boundary )( 
            ISpatialOperator * This,
            /* [retval][out] */ IGeometry **boundary);
        
        HRESULT ( STDMETHODCALLTYPE *Buffer )( 
            ISpatialOperator * This,
            /* [in] */ double distance,
            /* [retval][out] */ IGeometry **result);
        
        HRESULT ( STDMETHODCALLTYPE *ConvexHull )( 
            ISpatialOperator * This,
            /* [retval][out] */ IGeometry **result);
        
        HRESULT ( STDMETHODCALLTYPE *Intersection )( 
            ISpatialOperator * This,
            /* [in] */ IGeometry *other,
            /* [retval][out] */ IGeometry **result);
        
        HRESULT ( STDMETHODCALLTYPE *Union )( 
            ISpatialOperator * This,
            /* [in] */ IGeometry *other,
            /* [retval][out] */ IGeometry **result);
        
        HRESULT ( STDMETHODCALLTYPE *Difference )( 
            ISpatialOperator * This,
            /* [in] */ IGeometry *other,
            /* [retval][out] */ IGeometry **result);
        
        HRESULT ( STDMETHODCALLTYPE *SymmetricDifference )( 
            ISpatialOperator * This,
            /* [in] */ IGeometry *other,
            /* [retval][out] */ IGeometry **result);
        
        END_INTERFACE
    } ISpatialOperatorVtbl;

    interface ISpatialOperator
    {
        CONST_VTBL struct ISpatialOperatorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISpatialOperator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISpatialOperator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISpatialOperator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISpatialOperator_Distance(This,other,distance)	\
    (This)->lpVtbl -> Distance(This,other,distance)

#define ISpatialOperator_Boundary(This,boundary)	\
    (This)->lpVtbl -> Boundary(This,boundary)

#define ISpatialOperator_Buffer(This,distance,result)	\
    (This)->lpVtbl -> Buffer(This,distance,result)

#define ISpatialOperator_ConvexHull(This,result)	\
    (This)->lpVtbl -> ConvexHull(This,result)

#define ISpatialOperator_Intersection(This,other,result)	\
    (This)->lpVtbl -> Intersection(This,other,result)

#define ISpatialOperator_Union(This,other,result)	\
    (This)->lpVtbl -> Union(This,other,result)

#define ISpatialOperator_Difference(This,other,result)	\
    (This)->lpVtbl -> Difference(This,other,result)

#define ISpatialOperator_SymmetricDifference(This,other,result)	\
    (This)->lpVtbl -> SymmetricDifference(This,other,result)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISpatialOperator_Distance_Proxy( 
    ISpatialOperator * This,
    /* [in] */ IGeometry *other,
    /* [retval][out] */ double *distance);


void __RPC_STUB ISpatialOperator_Distance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISpatialOperator_Boundary_Proxy( 
    ISpatialOperator * This,
    /* [retval][out] */ IGeometry **boundary);


void __RPC_STUB ISpatialOperator_Boundary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISpatialOperator_Buffer_Proxy( 
    ISpatialOperator * This,
    /* [in] */ double distance,
    /* [retval][out] */ IGeometry **result);


void __RPC_STUB ISpatialOperator_Buffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISpatialOperator_ConvexHull_Proxy( 
    ISpatialOperator * This,
    /* [retval][out] */ IGeometry **result);


void __RPC_STUB ISpatialOperator_ConvexHull_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISpatialOperator_Intersection_Proxy( 
    ISpatialOperator * This,
    /* [in] */ IGeometry *other,
    /* [retval][out] */ IGeometry **result);


void __RPC_STUB ISpatialOperator_Intersection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISpatialOperator_Union_Proxy( 
    ISpatialOperator * This,
    /* [in] */ IGeometry *other,
    /* [retval][out] */ IGeometry **result);


void __RPC_STUB ISpatialOperator_Union_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISpatialOperator_Difference_Proxy( 
    ISpatialOperator * This,
    /* [in] */ IGeometry *other,
    /* [retval][out] */ IGeometry **result);


void __RPC_STUB ISpatialOperator_Difference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISpatialOperator_SymmetricDifference_Proxy( 
    ISpatialOperator * This,
    /* [in] */ IGeometry *other,
    /* [retval][out] */ IGeometry **result);


void __RPC_STUB ISpatialOperator_SymmetricDifference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISpatialOperator_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


