
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Mon Feb 04 21:48:28 2002
 */
/* Compiler settings for SpatialReference.idl:
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

#ifndef __SpatialReference_h__
#define __SpatialReference_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISpatialReferenceInfo_FWD_DEFINED__
#define __ISpatialReferenceInfo_FWD_DEFINED__
typedef interface ISpatialReferenceInfo ISpatialReferenceInfo;
#endif 	/* __ISpatialReferenceInfo_FWD_DEFINED__ */


#ifndef __IUnit_FWD_DEFINED__
#define __IUnit_FWD_DEFINED__
typedef interface IUnit IUnit;
#endif 	/* __IUnit_FWD_DEFINED__ */


#ifndef __IAngularUnit_FWD_DEFINED__
#define __IAngularUnit_FWD_DEFINED__
typedef interface IAngularUnit IAngularUnit;
#endif 	/* __IAngularUnit_FWD_DEFINED__ */


#ifndef __ILinearUnit_FWD_DEFINED__
#define __ILinearUnit_FWD_DEFINED__
typedef interface ILinearUnit ILinearUnit;
#endif 	/* __ILinearUnit_FWD_DEFINED__ */


#ifndef __IEllipsoid_FWD_DEFINED__
#define __IEllipsoid_FWD_DEFINED__
typedef interface IEllipsoid IEllipsoid;
#endif 	/* __IEllipsoid_FWD_DEFINED__ */


#ifndef __IHorizontalDatum_FWD_DEFINED__
#define __IHorizontalDatum_FWD_DEFINED__
typedef interface IHorizontalDatum IHorizontalDatum;
#endif 	/* __IHorizontalDatum_FWD_DEFINED__ */


#ifndef __IPrimeMeridian_FWD_DEFINED__
#define __IPrimeMeridian_FWD_DEFINED__
typedef interface IPrimeMeridian IPrimeMeridian;
#endif 	/* __IPrimeMeridian_FWD_DEFINED__ */


#ifndef __ISpatialReference_FWD_DEFINED__
#define __ISpatialReference_FWD_DEFINED__
typedef interface ISpatialReference ISpatialReference;
#endif 	/* __ISpatialReference_FWD_DEFINED__ */


#ifndef __IGeodeticSpatialReference_FWD_DEFINED__
#define __IGeodeticSpatialReference_FWD_DEFINED__
typedef interface IGeodeticSpatialReference IGeodeticSpatialReference;
#endif 	/* __IGeodeticSpatialReference_FWD_DEFINED__ */


#ifndef __IGeographicCoordinateSystem_FWD_DEFINED__
#define __IGeographicCoordinateSystem_FWD_DEFINED__
typedef interface IGeographicCoordinateSystem IGeographicCoordinateSystem;
#endif 	/* __IGeographicCoordinateSystem_FWD_DEFINED__ */


#ifndef __IParameter_FWD_DEFINED__
#define __IParameter_FWD_DEFINED__
typedef interface IParameter IParameter;
#endif 	/* __IParameter_FWD_DEFINED__ */


#ifndef __IParameterInfo_FWD_DEFINED__
#define __IParameterInfo_FWD_DEFINED__
typedef interface IParameterInfo IParameterInfo;
#endif 	/* __IParameterInfo_FWD_DEFINED__ */


#ifndef __IGeographicTransform_FWD_DEFINED__
#define __IGeographicTransform_FWD_DEFINED__
typedef interface IGeographicTransform IGeographicTransform;
#endif 	/* __IGeographicTransform_FWD_DEFINED__ */


#ifndef __IProjection_FWD_DEFINED__
#define __IProjection_FWD_DEFINED__
typedef interface IProjection IProjection;
#endif 	/* __IProjection_FWD_DEFINED__ */


#ifndef __IProjectedCoordinateSystem_FWD_DEFINED__
#define __IProjectedCoordinateSystem_FWD_DEFINED__
typedef interface IProjectedCoordinateSystem IProjectedCoordinateSystem;
#endif 	/* __IProjectedCoordinateSystem_FWD_DEFINED__ */


#ifndef __ISpatialReferenceFactory_FWD_DEFINED__
#define __ISpatialReferenceFactory_FWD_DEFINED__
typedef interface ISpatialReferenceFactory ISpatialReferenceFactory;
#endif 	/* __ISpatialReferenceFactory_FWD_DEFINED__ */


#ifndef __ISpatialReferenceAuthorityFactory_FWD_DEFINED__
#define __ISpatialReferenceAuthorityFactory_FWD_DEFINED__
typedef interface ISpatialReferenceAuthorityFactory ISpatialReferenceAuthorityFactory;
#endif 	/* __ISpatialReferenceAuthorityFactory_FWD_DEFINED__ */


/* header files for imported files */
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_SpatialReference_0000 */
/* [local] */ 

#pragma once
typedef struct tagWKSPoint
    {
    double x;
    double y;
    } 	WKSPoint;




















extern RPC_IF_HANDLE __MIDL_itf_SpatialReference_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_SpatialReference_0000_v0_0_s_ifspec;

#ifndef __ISpatialReferenceInfo_INTERFACE_DEFINED__
#define __ISpatialReferenceInfo_INTERFACE_DEFINED__

/* interface ISpatialReferenceInfo */
/* [uuid][object] */ 


EXTERN_C const IID IID_ISpatialReferenceInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("bcca38a0-fe1c-11d0-ad87-080009b6f22b")
    ISpatialReferenceInfo : public IUnknown
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *name) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR name) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Authority( 
            /* [retval][out] */ BSTR *name) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Authority( 
            /* [in] */ BSTR name) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Code( 
            /* [retval][out] */ long *code) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Code( 
            /* [in] */ long code) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Alias( 
            /* [retval][out] */ BSTR *alias) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Alias( 
            /* [in] */ BSTR alias) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Abbreviation( 
            /* [retval][out] */ BSTR *abbrev) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Abbreviation( 
            /* [in] */ BSTR abbrev) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Remarks( 
            /* [retval][out] */ BSTR *remarks) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Remarks( 
            /* [in] */ BSTR remarks) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_WellKnownText( 
            /* [retval][out] */ BSTR *wkt) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISpatialReferenceInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISpatialReferenceInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISpatialReferenceInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISpatialReferenceInfo * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ISpatialReferenceInfo * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            ISpatialReferenceInfo * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Authority )( 
            ISpatialReferenceInfo * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Authority )( 
            ISpatialReferenceInfo * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Code )( 
            ISpatialReferenceInfo * This,
            /* [retval][out] */ long *code);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Code )( 
            ISpatialReferenceInfo * This,
            /* [in] */ long code);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Alias )( 
            ISpatialReferenceInfo * This,
            /* [retval][out] */ BSTR *alias);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Alias )( 
            ISpatialReferenceInfo * This,
            /* [in] */ BSTR alias);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Abbreviation )( 
            ISpatialReferenceInfo * This,
            /* [retval][out] */ BSTR *abbrev);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Abbreviation )( 
            ISpatialReferenceInfo * This,
            /* [in] */ BSTR abbrev);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Remarks )( 
            ISpatialReferenceInfo * This,
            /* [retval][out] */ BSTR *remarks);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Remarks )( 
            ISpatialReferenceInfo * This,
            /* [in] */ BSTR remarks);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_WellKnownText )( 
            ISpatialReferenceInfo * This,
            /* [retval][out] */ BSTR *wkt);
        
        END_INTERFACE
    } ISpatialReferenceInfoVtbl;

    interface ISpatialReferenceInfo
    {
        CONST_VTBL struct ISpatialReferenceInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISpatialReferenceInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISpatialReferenceInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISpatialReferenceInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISpatialReferenceInfo_get_Name(This,name)	\
    (This)->lpVtbl -> get_Name(This,name)

#define ISpatialReferenceInfo_put_Name(This,name)	\
    (This)->lpVtbl -> put_Name(This,name)

#define ISpatialReferenceInfo_get_Authority(This,name)	\
    (This)->lpVtbl -> get_Authority(This,name)

#define ISpatialReferenceInfo_put_Authority(This,name)	\
    (This)->lpVtbl -> put_Authority(This,name)

#define ISpatialReferenceInfo_get_Code(This,code)	\
    (This)->lpVtbl -> get_Code(This,code)

#define ISpatialReferenceInfo_put_Code(This,code)	\
    (This)->lpVtbl -> put_Code(This,code)

#define ISpatialReferenceInfo_get_Alias(This,alias)	\
    (This)->lpVtbl -> get_Alias(This,alias)

#define ISpatialReferenceInfo_put_Alias(This,alias)	\
    (This)->lpVtbl -> put_Alias(This,alias)

#define ISpatialReferenceInfo_get_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> get_Abbreviation(This,abbrev)

#define ISpatialReferenceInfo_put_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> put_Abbreviation(This,abbrev)

#define ISpatialReferenceInfo_get_Remarks(This,remarks)	\
    (This)->lpVtbl -> get_Remarks(This,remarks)

#define ISpatialReferenceInfo_put_Remarks(This,remarks)	\
    (This)->lpVtbl -> put_Remarks(This,remarks)

#define ISpatialReferenceInfo_get_WellKnownText(This,wkt)	\
    (This)->lpVtbl -> get_WellKnownText(This,wkt)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_get_Name_Proxy( 
    ISpatialReferenceInfo * This,
    /* [retval][out] */ BSTR *name);


void __RPC_STUB ISpatialReferenceInfo_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_put_Name_Proxy( 
    ISpatialReferenceInfo * This,
    /* [in] */ BSTR name);


void __RPC_STUB ISpatialReferenceInfo_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_get_Authority_Proxy( 
    ISpatialReferenceInfo * This,
    /* [retval][out] */ BSTR *name);


void __RPC_STUB ISpatialReferenceInfo_get_Authority_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_put_Authority_Proxy( 
    ISpatialReferenceInfo * This,
    /* [in] */ BSTR name);


void __RPC_STUB ISpatialReferenceInfo_put_Authority_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_get_Code_Proxy( 
    ISpatialReferenceInfo * This,
    /* [retval][out] */ long *code);


void __RPC_STUB ISpatialReferenceInfo_get_Code_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_put_Code_Proxy( 
    ISpatialReferenceInfo * This,
    /* [in] */ long code);


void __RPC_STUB ISpatialReferenceInfo_put_Code_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_get_Alias_Proxy( 
    ISpatialReferenceInfo * This,
    /* [retval][out] */ BSTR *alias);


void __RPC_STUB ISpatialReferenceInfo_get_Alias_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_put_Alias_Proxy( 
    ISpatialReferenceInfo * This,
    /* [in] */ BSTR alias);


void __RPC_STUB ISpatialReferenceInfo_put_Alias_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_get_Abbreviation_Proxy( 
    ISpatialReferenceInfo * This,
    /* [retval][out] */ BSTR *abbrev);


void __RPC_STUB ISpatialReferenceInfo_get_Abbreviation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_put_Abbreviation_Proxy( 
    ISpatialReferenceInfo * This,
    /* [in] */ BSTR abbrev);


void __RPC_STUB ISpatialReferenceInfo_put_Abbreviation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_get_Remarks_Proxy( 
    ISpatialReferenceInfo * This,
    /* [retval][out] */ BSTR *remarks);


void __RPC_STUB ISpatialReferenceInfo_get_Remarks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_put_Remarks_Proxy( 
    ISpatialReferenceInfo * This,
    /* [in] */ BSTR remarks);


void __RPC_STUB ISpatialReferenceInfo_put_Remarks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_get_WellKnownText_Proxy( 
    ISpatialReferenceInfo * This,
    /* [retval][out] */ BSTR *wkt);


void __RPC_STUB ISpatialReferenceInfo_get_WellKnownText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISpatialReferenceInfo_INTERFACE_DEFINED__ */


#ifndef __IUnit_INTERFACE_DEFINED__
#define __IUnit_INTERFACE_DEFINED__

/* interface IUnit */
/* [uuid][object] */ 


EXTERN_C const IID IID_IUnit;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("221733b0-fe1d-11d0-ad87-080009b6f22b")
    IUnit : public ISpatialReferenceInfo
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IUnitVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUnit * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUnit * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUnit * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IUnit * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IUnit * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Authority )( 
            IUnit * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Authority )( 
            IUnit * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Code )( 
            IUnit * This,
            /* [retval][out] */ long *code);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Code )( 
            IUnit * This,
            /* [in] */ long code);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Alias )( 
            IUnit * This,
            /* [retval][out] */ BSTR *alias);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Alias )( 
            IUnit * This,
            /* [in] */ BSTR alias);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Abbreviation )( 
            IUnit * This,
            /* [retval][out] */ BSTR *abbrev);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Abbreviation )( 
            IUnit * This,
            /* [in] */ BSTR abbrev);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Remarks )( 
            IUnit * This,
            /* [retval][out] */ BSTR *remarks);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Remarks )( 
            IUnit * This,
            /* [in] */ BSTR remarks);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_WellKnownText )( 
            IUnit * This,
            /* [retval][out] */ BSTR *wkt);
        
        END_INTERFACE
    } IUnitVtbl;

    interface IUnit
    {
        CONST_VTBL struct IUnitVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUnit_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUnit_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUnit_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUnit_get_Name(This,name)	\
    (This)->lpVtbl -> get_Name(This,name)

#define IUnit_put_Name(This,name)	\
    (This)->lpVtbl -> put_Name(This,name)

#define IUnit_get_Authority(This,name)	\
    (This)->lpVtbl -> get_Authority(This,name)

#define IUnit_put_Authority(This,name)	\
    (This)->lpVtbl -> put_Authority(This,name)

#define IUnit_get_Code(This,code)	\
    (This)->lpVtbl -> get_Code(This,code)

#define IUnit_put_Code(This,code)	\
    (This)->lpVtbl -> put_Code(This,code)

#define IUnit_get_Alias(This,alias)	\
    (This)->lpVtbl -> get_Alias(This,alias)

#define IUnit_put_Alias(This,alias)	\
    (This)->lpVtbl -> put_Alias(This,alias)

#define IUnit_get_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> get_Abbreviation(This,abbrev)

#define IUnit_put_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> put_Abbreviation(This,abbrev)

#define IUnit_get_Remarks(This,remarks)	\
    (This)->lpVtbl -> get_Remarks(This,remarks)

#define IUnit_put_Remarks(This,remarks)	\
    (This)->lpVtbl -> put_Remarks(This,remarks)

#define IUnit_get_WellKnownText(This,wkt)	\
    (This)->lpVtbl -> get_WellKnownText(This,wkt)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUnit_INTERFACE_DEFINED__ */


#ifndef __IAngularUnit_INTERFACE_DEFINED__
#define __IAngularUnit_INTERFACE_DEFINED__

/* interface IAngularUnit */
/* [uuid][object] */ 


EXTERN_C const IID IID_IAngularUnit;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4febc550-fe1d-11d0-ad87-080009b6f22b")
    IAngularUnit : public IUnit
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_RadiansPerUnit( 
            /* [retval][out] */ double *factor) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_RadiansPerUnit( 
            /* [in] */ double factor) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAngularUnitVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAngularUnit * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAngularUnit * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAngularUnit * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IAngularUnit * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IAngularUnit * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Authority )( 
            IAngularUnit * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Authority )( 
            IAngularUnit * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Code )( 
            IAngularUnit * This,
            /* [retval][out] */ long *code);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Code )( 
            IAngularUnit * This,
            /* [in] */ long code);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Alias )( 
            IAngularUnit * This,
            /* [retval][out] */ BSTR *alias);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Alias )( 
            IAngularUnit * This,
            /* [in] */ BSTR alias);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Abbreviation )( 
            IAngularUnit * This,
            /* [retval][out] */ BSTR *abbrev);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Abbreviation )( 
            IAngularUnit * This,
            /* [in] */ BSTR abbrev);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Remarks )( 
            IAngularUnit * This,
            /* [retval][out] */ BSTR *remarks);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Remarks )( 
            IAngularUnit * This,
            /* [in] */ BSTR remarks);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_WellKnownText )( 
            IAngularUnit * This,
            /* [retval][out] */ BSTR *wkt);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RadiansPerUnit )( 
            IAngularUnit * This,
            /* [retval][out] */ double *factor);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RadiansPerUnit )( 
            IAngularUnit * This,
            /* [in] */ double factor);
        
        END_INTERFACE
    } IAngularUnitVtbl;

    interface IAngularUnit
    {
        CONST_VTBL struct IAngularUnitVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAngularUnit_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAngularUnit_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAngularUnit_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAngularUnit_get_Name(This,name)	\
    (This)->lpVtbl -> get_Name(This,name)

#define IAngularUnit_put_Name(This,name)	\
    (This)->lpVtbl -> put_Name(This,name)

#define IAngularUnit_get_Authority(This,name)	\
    (This)->lpVtbl -> get_Authority(This,name)

#define IAngularUnit_put_Authority(This,name)	\
    (This)->lpVtbl -> put_Authority(This,name)

#define IAngularUnit_get_Code(This,code)	\
    (This)->lpVtbl -> get_Code(This,code)

#define IAngularUnit_put_Code(This,code)	\
    (This)->lpVtbl -> put_Code(This,code)

#define IAngularUnit_get_Alias(This,alias)	\
    (This)->lpVtbl -> get_Alias(This,alias)

#define IAngularUnit_put_Alias(This,alias)	\
    (This)->lpVtbl -> put_Alias(This,alias)

#define IAngularUnit_get_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> get_Abbreviation(This,abbrev)

#define IAngularUnit_put_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> put_Abbreviation(This,abbrev)

#define IAngularUnit_get_Remarks(This,remarks)	\
    (This)->lpVtbl -> get_Remarks(This,remarks)

#define IAngularUnit_put_Remarks(This,remarks)	\
    (This)->lpVtbl -> put_Remarks(This,remarks)

#define IAngularUnit_get_WellKnownText(This,wkt)	\
    (This)->lpVtbl -> get_WellKnownText(This,wkt)



#define IAngularUnit_get_RadiansPerUnit(This,factor)	\
    (This)->lpVtbl -> get_RadiansPerUnit(This,factor)

#define IAngularUnit_put_RadiansPerUnit(This,factor)	\
    (This)->lpVtbl -> put_RadiansPerUnit(This,factor)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IAngularUnit_get_RadiansPerUnit_Proxy( 
    IAngularUnit * This,
    /* [retval][out] */ double *factor);


void __RPC_STUB IAngularUnit_get_RadiansPerUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IAngularUnit_put_RadiansPerUnit_Proxy( 
    IAngularUnit * This,
    /* [in] */ double factor);


void __RPC_STUB IAngularUnit_put_RadiansPerUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAngularUnit_INTERFACE_DEFINED__ */


#ifndef __ILinearUnit_INTERFACE_DEFINED__
#define __ILinearUnit_INTERFACE_DEFINED__

/* interface ILinearUnit */
/* [uuid][object] */ 


EXTERN_C const IID IID_ILinearUnit;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("80855df0-fe1d-11d0-ad87-080009b6f22b")
    ILinearUnit : public IUnit
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_MetersPerUnit( 
            /* [retval][out] */ double *factor) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_MetersPerUnit( 
            /* [in] */ double factor) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILinearUnitVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILinearUnit * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILinearUnit * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILinearUnit * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ILinearUnit * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            ILinearUnit * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Authority )( 
            ILinearUnit * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Authority )( 
            ILinearUnit * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Code )( 
            ILinearUnit * This,
            /* [retval][out] */ long *code);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Code )( 
            ILinearUnit * This,
            /* [in] */ long code);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Alias )( 
            ILinearUnit * This,
            /* [retval][out] */ BSTR *alias);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Alias )( 
            ILinearUnit * This,
            /* [in] */ BSTR alias);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Abbreviation )( 
            ILinearUnit * This,
            /* [retval][out] */ BSTR *abbrev);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Abbreviation )( 
            ILinearUnit * This,
            /* [in] */ BSTR abbrev);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Remarks )( 
            ILinearUnit * This,
            /* [retval][out] */ BSTR *remarks);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Remarks )( 
            ILinearUnit * This,
            /* [in] */ BSTR remarks);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_WellKnownText )( 
            ILinearUnit * This,
            /* [retval][out] */ BSTR *wkt);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_MetersPerUnit )( 
            ILinearUnit * This,
            /* [retval][out] */ double *factor);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_MetersPerUnit )( 
            ILinearUnit * This,
            /* [in] */ double factor);
        
        END_INTERFACE
    } ILinearUnitVtbl;

    interface ILinearUnit
    {
        CONST_VTBL struct ILinearUnitVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILinearUnit_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILinearUnit_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILinearUnit_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILinearUnit_get_Name(This,name)	\
    (This)->lpVtbl -> get_Name(This,name)

#define ILinearUnit_put_Name(This,name)	\
    (This)->lpVtbl -> put_Name(This,name)

#define ILinearUnit_get_Authority(This,name)	\
    (This)->lpVtbl -> get_Authority(This,name)

#define ILinearUnit_put_Authority(This,name)	\
    (This)->lpVtbl -> put_Authority(This,name)

#define ILinearUnit_get_Code(This,code)	\
    (This)->lpVtbl -> get_Code(This,code)

#define ILinearUnit_put_Code(This,code)	\
    (This)->lpVtbl -> put_Code(This,code)

#define ILinearUnit_get_Alias(This,alias)	\
    (This)->lpVtbl -> get_Alias(This,alias)

#define ILinearUnit_put_Alias(This,alias)	\
    (This)->lpVtbl -> put_Alias(This,alias)

#define ILinearUnit_get_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> get_Abbreviation(This,abbrev)

#define ILinearUnit_put_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> put_Abbreviation(This,abbrev)

#define ILinearUnit_get_Remarks(This,remarks)	\
    (This)->lpVtbl -> get_Remarks(This,remarks)

#define ILinearUnit_put_Remarks(This,remarks)	\
    (This)->lpVtbl -> put_Remarks(This,remarks)

#define ILinearUnit_get_WellKnownText(This,wkt)	\
    (This)->lpVtbl -> get_WellKnownText(This,wkt)



#define ILinearUnit_get_MetersPerUnit(This,factor)	\
    (This)->lpVtbl -> get_MetersPerUnit(This,factor)

#define ILinearUnit_put_MetersPerUnit(This,factor)	\
    (This)->lpVtbl -> put_MetersPerUnit(This,factor)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE ILinearUnit_get_MetersPerUnit_Proxy( 
    ILinearUnit * This,
    /* [retval][out] */ double *factor);


void __RPC_STUB ILinearUnit_get_MetersPerUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ILinearUnit_put_MetersPerUnit_Proxy( 
    ILinearUnit * This,
    /* [in] */ double factor);


void __RPC_STUB ILinearUnit_put_MetersPerUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILinearUnit_INTERFACE_DEFINED__ */


#ifndef __IEllipsoid_INTERFACE_DEFINED__
#define __IEllipsoid_INTERFACE_DEFINED__

/* interface IEllipsoid */
/* [uuid][object] */ 


EXTERN_C const IID IID_IEllipsoid;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ce7266c0-fe1d-11d0-ad87-080009b6f22b")
    IEllipsoid : public ISpatialReferenceInfo
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_SemiMajorAxis( 
            /* [retval][out] */ double *axis) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_SemiMajorAxis( 
            /* [in] */ double axis) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_SemiMinorAxis( 
            /* [retval][out] */ double *axis) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_SemiMinorAxis( 
            /* [in] */ double axis) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_InverseFlattening( 
            /* [retval][out] */ double *invFlat) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_InverseFlattening( 
            /* [in] */ double invFlat) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_AxisUnit( 
            /* [retval][out] */ ILinearUnit **unit) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_AxisUnit( 
            /* [in] */ ILinearUnit *unit) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEllipsoidVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEllipsoid * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEllipsoid * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEllipsoid * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IEllipsoid * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IEllipsoid * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Authority )( 
            IEllipsoid * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Authority )( 
            IEllipsoid * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Code )( 
            IEllipsoid * This,
            /* [retval][out] */ long *code);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Code )( 
            IEllipsoid * This,
            /* [in] */ long code);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Alias )( 
            IEllipsoid * This,
            /* [retval][out] */ BSTR *alias);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Alias )( 
            IEllipsoid * This,
            /* [in] */ BSTR alias);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Abbreviation )( 
            IEllipsoid * This,
            /* [retval][out] */ BSTR *abbrev);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Abbreviation )( 
            IEllipsoid * This,
            /* [in] */ BSTR abbrev);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Remarks )( 
            IEllipsoid * This,
            /* [retval][out] */ BSTR *remarks);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Remarks )( 
            IEllipsoid * This,
            /* [in] */ BSTR remarks);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_WellKnownText )( 
            IEllipsoid * This,
            /* [retval][out] */ BSTR *wkt);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_SemiMajorAxis )( 
            IEllipsoid * This,
            /* [retval][out] */ double *axis);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_SemiMajorAxis )( 
            IEllipsoid * This,
            /* [in] */ double axis);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_SemiMinorAxis )( 
            IEllipsoid * This,
            /* [retval][out] */ double *axis);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_SemiMinorAxis )( 
            IEllipsoid * This,
            /* [in] */ double axis);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_InverseFlattening )( 
            IEllipsoid * This,
            /* [retval][out] */ double *invFlat);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_InverseFlattening )( 
            IEllipsoid * This,
            /* [in] */ double invFlat);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_AxisUnit )( 
            IEllipsoid * This,
            /* [retval][out] */ ILinearUnit **unit);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_AxisUnit )( 
            IEllipsoid * This,
            /* [in] */ ILinearUnit *unit);
        
        END_INTERFACE
    } IEllipsoidVtbl;

    interface IEllipsoid
    {
        CONST_VTBL struct IEllipsoidVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEllipsoid_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEllipsoid_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEllipsoid_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEllipsoid_get_Name(This,name)	\
    (This)->lpVtbl -> get_Name(This,name)

#define IEllipsoid_put_Name(This,name)	\
    (This)->lpVtbl -> put_Name(This,name)

#define IEllipsoid_get_Authority(This,name)	\
    (This)->lpVtbl -> get_Authority(This,name)

#define IEllipsoid_put_Authority(This,name)	\
    (This)->lpVtbl -> put_Authority(This,name)

#define IEllipsoid_get_Code(This,code)	\
    (This)->lpVtbl -> get_Code(This,code)

#define IEllipsoid_put_Code(This,code)	\
    (This)->lpVtbl -> put_Code(This,code)

#define IEllipsoid_get_Alias(This,alias)	\
    (This)->lpVtbl -> get_Alias(This,alias)

#define IEllipsoid_put_Alias(This,alias)	\
    (This)->lpVtbl -> put_Alias(This,alias)

#define IEllipsoid_get_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> get_Abbreviation(This,abbrev)

#define IEllipsoid_put_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> put_Abbreviation(This,abbrev)

#define IEllipsoid_get_Remarks(This,remarks)	\
    (This)->lpVtbl -> get_Remarks(This,remarks)

#define IEllipsoid_put_Remarks(This,remarks)	\
    (This)->lpVtbl -> put_Remarks(This,remarks)

#define IEllipsoid_get_WellKnownText(This,wkt)	\
    (This)->lpVtbl -> get_WellKnownText(This,wkt)


#define IEllipsoid_get_SemiMajorAxis(This,axis)	\
    (This)->lpVtbl -> get_SemiMajorAxis(This,axis)

#define IEllipsoid_put_SemiMajorAxis(This,axis)	\
    (This)->lpVtbl -> put_SemiMajorAxis(This,axis)

#define IEllipsoid_get_SemiMinorAxis(This,axis)	\
    (This)->lpVtbl -> get_SemiMinorAxis(This,axis)

#define IEllipsoid_put_SemiMinorAxis(This,axis)	\
    (This)->lpVtbl -> put_SemiMinorAxis(This,axis)

#define IEllipsoid_get_InverseFlattening(This,invFlat)	\
    (This)->lpVtbl -> get_InverseFlattening(This,invFlat)

#define IEllipsoid_put_InverseFlattening(This,invFlat)	\
    (This)->lpVtbl -> put_InverseFlattening(This,invFlat)

#define IEllipsoid_get_AxisUnit(This,unit)	\
    (This)->lpVtbl -> get_AxisUnit(This,unit)

#define IEllipsoid_put_AxisUnit(This,unit)	\
    (This)->lpVtbl -> put_AxisUnit(This,unit)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IEllipsoid_get_SemiMajorAxis_Proxy( 
    IEllipsoid * This,
    /* [retval][out] */ double *axis);


void __RPC_STUB IEllipsoid_get_SemiMajorAxis_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IEllipsoid_put_SemiMajorAxis_Proxy( 
    IEllipsoid * This,
    /* [in] */ double axis);


void __RPC_STUB IEllipsoid_put_SemiMajorAxis_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IEllipsoid_get_SemiMinorAxis_Proxy( 
    IEllipsoid * This,
    /* [retval][out] */ double *axis);


void __RPC_STUB IEllipsoid_get_SemiMinorAxis_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IEllipsoid_put_SemiMinorAxis_Proxy( 
    IEllipsoid * This,
    /* [in] */ double axis);


void __RPC_STUB IEllipsoid_put_SemiMinorAxis_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IEllipsoid_get_InverseFlattening_Proxy( 
    IEllipsoid * This,
    /* [retval][out] */ double *invFlat);


void __RPC_STUB IEllipsoid_get_InverseFlattening_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IEllipsoid_put_InverseFlattening_Proxy( 
    IEllipsoid * This,
    /* [in] */ double invFlat);


void __RPC_STUB IEllipsoid_put_InverseFlattening_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IEllipsoid_get_AxisUnit_Proxy( 
    IEllipsoid * This,
    /* [retval][out] */ ILinearUnit **unit);


void __RPC_STUB IEllipsoid_get_AxisUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IEllipsoid_put_AxisUnit_Proxy( 
    IEllipsoid * This,
    /* [in] */ ILinearUnit *unit);


void __RPC_STUB IEllipsoid_put_AxisUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEllipsoid_INTERFACE_DEFINED__ */


#ifndef __IHorizontalDatum_INTERFACE_DEFINED__
#define __IHorizontalDatum_INTERFACE_DEFINED__

/* interface IHorizontalDatum */
/* [uuid][object] */ 


EXTERN_C const IID IID_IHorizontalDatum;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("f699c510-fe1d-11d0-ad87-080009b6f22b")
    IHorizontalDatum : public ISpatialReferenceInfo
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Ellipsoid( 
            /* [retval][out] */ IEllipsoid **ellipsoid) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Ellipsoid( 
            /* [in] */ IEllipsoid *ellipsoid) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHorizontalDatumVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IHorizontalDatum * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IHorizontalDatum * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IHorizontalDatum * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IHorizontalDatum * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IHorizontalDatum * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Authority )( 
            IHorizontalDatum * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Authority )( 
            IHorizontalDatum * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Code )( 
            IHorizontalDatum * This,
            /* [retval][out] */ long *code);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Code )( 
            IHorizontalDatum * This,
            /* [in] */ long code);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Alias )( 
            IHorizontalDatum * This,
            /* [retval][out] */ BSTR *alias);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Alias )( 
            IHorizontalDatum * This,
            /* [in] */ BSTR alias);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Abbreviation )( 
            IHorizontalDatum * This,
            /* [retval][out] */ BSTR *abbrev);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Abbreviation )( 
            IHorizontalDatum * This,
            /* [in] */ BSTR abbrev);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Remarks )( 
            IHorizontalDatum * This,
            /* [retval][out] */ BSTR *remarks);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Remarks )( 
            IHorizontalDatum * This,
            /* [in] */ BSTR remarks);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_WellKnownText )( 
            IHorizontalDatum * This,
            /* [retval][out] */ BSTR *wkt);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Ellipsoid )( 
            IHorizontalDatum * This,
            /* [retval][out] */ IEllipsoid **ellipsoid);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Ellipsoid )( 
            IHorizontalDatum * This,
            /* [in] */ IEllipsoid *ellipsoid);
        
        END_INTERFACE
    } IHorizontalDatumVtbl;

    interface IHorizontalDatum
    {
        CONST_VTBL struct IHorizontalDatumVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHorizontalDatum_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHorizontalDatum_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHorizontalDatum_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHorizontalDatum_get_Name(This,name)	\
    (This)->lpVtbl -> get_Name(This,name)

#define IHorizontalDatum_put_Name(This,name)	\
    (This)->lpVtbl -> put_Name(This,name)

#define IHorizontalDatum_get_Authority(This,name)	\
    (This)->lpVtbl -> get_Authority(This,name)

#define IHorizontalDatum_put_Authority(This,name)	\
    (This)->lpVtbl -> put_Authority(This,name)

#define IHorizontalDatum_get_Code(This,code)	\
    (This)->lpVtbl -> get_Code(This,code)

#define IHorizontalDatum_put_Code(This,code)	\
    (This)->lpVtbl -> put_Code(This,code)

#define IHorizontalDatum_get_Alias(This,alias)	\
    (This)->lpVtbl -> get_Alias(This,alias)

#define IHorizontalDatum_put_Alias(This,alias)	\
    (This)->lpVtbl -> put_Alias(This,alias)

#define IHorizontalDatum_get_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> get_Abbreviation(This,abbrev)

#define IHorizontalDatum_put_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> put_Abbreviation(This,abbrev)

#define IHorizontalDatum_get_Remarks(This,remarks)	\
    (This)->lpVtbl -> get_Remarks(This,remarks)

#define IHorizontalDatum_put_Remarks(This,remarks)	\
    (This)->lpVtbl -> put_Remarks(This,remarks)

#define IHorizontalDatum_get_WellKnownText(This,wkt)	\
    (This)->lpVtbl -> get_WellKnownText(This,wkt)


#define IHorizontalDatum_get_Ellipsoid(This,ellipsoid)	\
    (This)->lpVtbl -> get_Ellipsoid(This,ellipsoid)

#define IHorizontalDatum_put_Ellipsoid(This,ellipsoid)	\
    (This)->lpVtbl -> put_Ellipsoid(This,ellipsoid)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IHorizontalDatum_get_Ellipsoid_Proxy( 
    IHorizontalDatum * This,
    /* [retval][out] */ IEllipsoid **ellipsoid);


void __RPC_STUB IHorizontalDatum_get_Ellipsoid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IHorizontalDatum_put_Ellipsoid_Proxy( 
    IHorizontalDatum * This,
    /* [in] */ IEllipsoid *ellipsoid);


void __RPC_STUB IHorizontalDatum_put_Ellipsoid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHorizontalDatum_INTERFACE_DEFINED__ */


#ifndef __IPrimeMeridian_INTERFACE_DEFINED__
#define __IPrimeMeridian_INTERFACE_DEFINED__

/* interface IPrimeMeridian */
/* [uuid][object] */ 


EXTERN_C const IID IID_IPrimeMeridian;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("15129940-fe1e-11d0-ad87-080009b6f22b")
    IPrimeMeridian : public ISpatialReferenceInfo
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Longitude( 
            /* [retval][out] */ double *longitude) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Longitude( 
            /* [in] */ double longitude) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_AngularUnit( 
            /* [retval][out] */ IAngularUnit **unit) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_AngularUnit( 
            /* [in] */ IAngularUnit *unit) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPrimeMeridianVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPrimeMeridian * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPrimeMeridian * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPrimeMeridian * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IPrimeMeridian * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IPrimeMeridian * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Authority )( 
            IPrimeMeridian * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Authority )( 
            IPrimeMeridian * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Code )( 
            IPrimeMeridian * This,
            /* [retval][out] */ long *code);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Code )( 
            IPrimeMeridian * This,
            /* [in] */ long code);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Alias )( 
            IPrimeMeridian * This,
            /* [retval][out] */ BSTR *alias);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Alias )( 
            IPrimeMeridian * This,
            /* [in] */ BSTR alias);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Abbreviation )( 
            IPrimeMeridian * This,
            /* [retval][out] */ BSTR *abbrev);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Abbreviation )( 
            IPrimeMeridian * This,
            /* [in] */ BSTR abbrev);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Remarks )( 
            IPrimeMeridian * This,
            /* [retval][out] */ BSTR *remarks);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Remarks )( 
            IPrimeMeridian * This,
            /* [in] */ BSTR remarks);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_WellKnownText )( 
            IPrimeMeridian * This,
            /* [retval][out] */ BSTR *wkt);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Longitude )( 
            IPrimeMeridian * This,
            /* [retval][out] */ double *longitude);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Longitude )( 
            IPrimeMeridian * This,
            /* [in] */ double longitude);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_AngularUnit )( 
            IPrimeMeridian * This,
            /* [retval][out] */ IAngularUnit **unit);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_AngularUnit )( 
            IPrimeMeridian * This,
            /* [in] */ IAngularUnit *unit);
        
        END_INTERFACE
    } IPrimeMeridianVtbl;

    interface IPrimeMeridian
    {
        CONST_VTBL struct IPrimeMeridianVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPrimeMeridian_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPrimeMeridian_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPrimeMeridian_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPrimeMeridian_get_Name(This,name)	\
    (This)->lpVtbl -> get_Name(This,name)

#define IPrimeMeridian_put_Name(This,name)	\
    (This)->lpVtbl -> put_Name(This,name)

#define IPrimeMeridian_get_Authority(This,name)	\
    (This)->lpVtbl -> get_Authority(This,name)

#define IPrimeMeridian_put_Authority(This,name)	\
    (This)->lpVtbl -> put_Authority(This,name)

#define IPrimeMeridian_get_Code(This,code)	\
    (This)->lpVtbl -> get_Code(This,code)

#define IPrimeMeridian_put_Code(This,code)	\
    (This)->lpVtbl -> put_Code(This,code)

#define IPrimeMeridian_get_Alias(This,alias)	\
    (This)->lpVtbl -> get_Alias(This,alias)

#define IPrimeMeridian_put_Alias(This,alias)	\
    (This)->lpVtbl -> put_Alias(This,alias)

#define IPrimeMeridian_get_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> get_Abbreviation(This,abbrev)

#define IPrimeMeridian_put_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> put_Abbreviation(This,abbrev)

#define IPrimeMeridian_get_Remarks(This,remarks)	\
    (This)->lpVtbl -> get_Remarks(This,remarks)

#define IPrimeMeridian_put_Remarks(This,remarks)	\
    (This)->lpVtbl -> put_Remarks(This,remarks)

#define IPrimeMeridian_get_WellKnownText(This,wkt)	\
    (This)->lpVtbl -> get_WellKnownText(This,wkt)


#define IPrimeMeridian_get_Longitude(This,longitude)	\
    (This)->lpVtbl -> get_Longitude(This,longitude)

#define IPrimeMeridian_put_Longitude(This,longitude)	\
    (This)->lpVtbl -> put_Longitude(This,longitude)

#define IPrimeMeridian_get_AngularUnit(This,unit)	\
    (This)->lpVtbl -> get_AngularUnit(This,unit)

#define IPrimeMeridian_put_AngularUnit(This,unit)	\
    (This)->lpVtbl -> put_AngularUnit(This,unit)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IPrimeMeridian_get_Longitude_Proxy( 
    IPrimeMeridian * This,
    /* [retval][out] */ double *longitude);


void __RPC_STUB IPrimeMeridian_get_Longitude_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPrimeMeridian_put_Longitude_Proxy( 
    IPrimeMeridian * This,
    /* [in] */ double longitude);


void __RPC_STUB IPrimeMeridian_put_Longitude_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IPrimeMeridian_get_AngularUnit_Proxy( 
    IPrimeMeridian * This,
    /* [retval][out] */ IAngularUnit **unit);


void __RPC_STUB IPrimeMeridian_get_AngularUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IPrimeMeridian_put_AngularUnit_Proxy( 
    IPrimeMeridian * This,
    /* [in] */ IAngularUnit *unit);


void __RPC_STUB IPrimeMeridian_put_AngularUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPrimeMeridian_INTERFACE_DEFINED__ */


#ifndef __ISpatialReference_INTERFACE_DEFINED__
#define __ISpatialReference_INTERFACE_DEFINED__

/* interface ISpatialReference */
/* [uuid][object] */ 


EXTERN_C const IID IID_ISpatialReference;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4c4c5c00-fe1e-11d0-ad87-080009b6f22b")
    ISpatialReference : public ISpatialReferenceInfo
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ISpatialReferenceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISpatialReference * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISpatialReference * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISpatialReference * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ISpatialReference * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            ISpatialReference * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Authority )( 
            ISpatialReference * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Authority )( 
            ISpatialReference * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Code )( 
            ISpatialReference * This,
            /* [retval][out] */ long *code);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Code )( 
            ISpatialReference * This,
            /* [in] */ long code);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Alias )( 
            ISpatialReference * This,
            /* [retval][out] */ BSTR *alias);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Alias )( 
            ISpatialReference * This,
            /* [in] */ BSTR alias);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Abbreviation )( 
            ISpatialReference * This,
            /* [retval][out] */ BSTR *abbrev);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Abbreviation )( 
            ISpatialReference * This,
            /* [in] */ BSTR abbrev);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Remarks )( 
            ISpatialReference * This,
            /* [retval][out] */ BSTR *remarks);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Remarks )( 
            ISpatialReference * This,
            /* [in] */ BSTR remarks);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_WellKnownText )( 
            ISpatialReference * This,
            /* [retval][out] */ BSTR *wkt);
        
        END_INTERFACE
    } ISpatialReferenceVtbl;

    interface ISpatialReference
    {
        CONST_VTBL struct ISpatialReferenceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISpatialReference_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISpatialReference_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISpatialReference_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISpatialReference_get_Name(This,name)	\
    (This)->lpVtbl -> get_Name(This,name)

#define ISpatialReference_put_Name(This,name)	\
    (This)->lpVtbl -> put_Name(This,name)

#define ISpatialReference_get_Authority(This,name)	\
    (This)->lpVtbl -> get_Authority(This,name)

#define ISpatialReference_put_Authority(This,name)	\
    (This)->lpVtbl -> put_Authority(This,name)

#define ISpatialReference_get_Code(This,code)	\
    (This)->lpVtbl -> get_Code(This,code)

#define ISpatialReference_put_Code(This,code)	\
    (This)->lpVtbl -> put_Code(This,code)

#define ISpatialReference_get_Alias(This,alias)	\
    (This)->lpVtbl -> get_Alias(This,alias)

#define ISpatialReference_put_Alias(This,alias)	\
    (This)->lpVtbl -> put_Alias(This,alias)

#define ISpatialReference_get_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> get_Abbreviation(This,abbrev)

#define ISpatialReference_put_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> put_Abbreviation(This,abbrev)

#define ISpatialReference_get_Remarks(This,remarks)	\
    (This)->lpVtbl -> get_Remarks(This,remarks)

#define ISpatialReference_put_Remarks(This,remarks)	\
    (This)->lpVtbl -> put_Remarks(This,remarks)

#define ISpatialReference_get_WellKnownText(This,wkt)	\
    (This)->lpVtbl -> get_WellKnownText(This,wkt)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISpatialReference_INTERFACE_DEFINED__ */


#ifndef __IGeodeticSpatialReference_INTERFACE_DEFINED__
#define __IGeodeticSpatialReference_INTERFACE_DEFINED__

/* interface IGeodeticSpatialReference */
/* [uuid][object] */ 


EXTERN_C const IID IID_IGeodeticSpatialReference;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7c3c56d0-fe1e-11d0-ad87-080009b6f22b")
    IGeodeticSpatialReference : public ISpatialReference
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IGeodeticSpatialReferenceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGeodeticSpatialReference * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGeodeticSpatialReference * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGeodeticSpatialReference * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IGeodeticSpatialReference * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IGeodeticSpatialReference * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Authority )( 
            IGeodeticSpatialReference * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Authority )( 
            IGeodeticSpatialReference * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Code )( 
            IGeodeticSpatialReference * This,
            /* [retval][out] */ long *code);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Code )( 
            IGeodeticSpatialReference * This,
            /* [in] */ long code);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Alias )( 
            IGeodeticSpatialReference * This,
            /* [retval][out] */ BSTR *alias);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Alias )( 
            IGeodeticSpatialReference * This,
            /* [in] */ BSTR alias);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Abbreviation )( 
            IGeodeticSpatialReference * This,
            /* [retval][out] */ BSTR *abbrev);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Abbreviation )( 
            IGeodeticSpatialReference * This,
            /* [in] */ BSTR abbrev);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Remarks )( 
            IGeodeticSpatialReference * This,
            /* [retval][out] */ BSTR *remarks);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Remarks )( 
            IGeodeticSpatialReference * This,
            /* [in] */ BSTR remarks);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_WellKnownText )( 
            IGeodeticSpatialReference * This,
            /* [retval][out] */ BSTR *wkt);
        
        END_INTERFACE
    } IGeodeticSpatialReferenceVtbl;

    interface IGeodeticSpatialReference
    {
        CONST_VTBL struct IGeodeticSpatialReferenceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGeodeticSpatialReference_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGeodeticSpatialReference_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGeodeticSpatialReference_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGeodeticSpatialReference_get_Name(This,name)	\
    (This)->lpVtbl -> get_Name(This,name)

#define IGeodeticSpatialReference_put_Name(This,name)	\
    (This)->lpVtbl -> put_Name(This,name)

#define IGeodeticSpatialReference_get_Authority(This,name)	\
    (This)->lpVtbl -> get_Authority(This,name)

#define IGeodeticSpatialReference_put_Authority(This,name)	\
    (This)->lpVtbl -> put_Authority(This,name)

#define IGeodeticSpatialReference_get_Code(This,code)	\
    (This)->lpVtbl -> get_Code(This,code)

#define IGeodeticSpatialReference_put_Code(This,code)	\
    (This)->lpVtbl -> put_Code(This,code)

#define IGeodeticSpatialReference_get_Alias(This,alias)	\
    (This)->lpVtbl -> get_Alias(This,alias)

#define IGeodeticSpatialReference_put_Alias(This,alias)	\
    (This)->lpVtbl -> put_Alias(This,alias)

#define IGeodeticSpatialReference_get_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> get_Abbreviation(This,abbrev)

#define IGeodeticSpatialReference_put_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> put_Abbreviation(This,abbrev)

#define IGeodeticSpatialReference_get_Remarks(This,remarks)	\
    (This)->lpVtbl -> get_Remarks(This,remarks)

#define IGeodeticSpatialReference_put_Remarks(This,remarks)	\
    (This)->lpVtbl -> put_Remarks(This,remarks)

#define IGeodeticSpatialReference_get_WellKnownText(This,wkt)	\
    (This)->lpVtbl -> get_WellKnownText(This,wkt)



#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGeodeticSpatialReference_INTERFACE_DEFINED__ */


#ifndef __IGeographicCoordinateSystem_INTERFACE_DEFINED__
#define __IGeographicCoordinateSystem_INTERFACE_DEFINED__

/* interface IGeographicCoordinateSystem */
/* [uuid][object] */ 


EXTERN_C const IID IID_IGeographicCoordinateSystem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a3fd5390-fe1e-11d0-ad87-080009b6f22b")
    IGeographicCoordinateSystem : public IGeodeticSpatialReference
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Usage( 
            /* [retval][out] */ BSTR *usage) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Usage( 
            /* [in] */ BSTR usage) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_HorizontalDatum( 
            /* [retval][out] */ IHorizontalDatum **datum) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_HorizontalDatum( 
            /* [in] */ IHorizontalDatum *datum) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_AngularUnit( 
            /* [retval][out] */ IAngularUnit **unit) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_AngularUnit( 
            /* [in] */ IAngularUnit *unit) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_PrimeMeridian( 
            /* [retval][out] */ IPrimeMeridian **prmMerid) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_PrimeMeridian( 
            /* [in] */ IPrimeMeridian *prmMerid) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGeographicCoordinateSystemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGeographicCoordinateSystem * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGeographicCoordinateSystem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGeographicCoordinateSystem * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IGeographicCoordinateSystem * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IGeographicCoordinateSystem * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Authority )( 
            IGeographicCoordinateSystem * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Authority )( 
            IGeographicCoordinateSystem * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Code )( 
            IGeographicCoordinateSystem * This,
            /* [retval][out] */ long *code);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Code )( 
            IGeographicCoordinateSystem * This,
            /* [in] */ long code);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Alias )( 
            IGeographicCoordinateSystem * This,
            /* [retval][out] */ BSTR *alias);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Alias )( 
            IGeographicCoordinateSystem * This,
            /* [in] */ BSTR alias);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Abbreviation )( 
            IGeographicCoordinateSystem * This,
            /* [retval][out] */ BSTR *abbrev);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Abbreviation )( 
            IGeographicCoordinateSystem * This,
            /* [in] */ BSTR abbrev);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Remarks )( 
            IGeographicCoordinateSystem * This,
            /* [retval][out] */ BSTR *remarks);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Remarks )( 
            IGeographicCoordinateSystem * This,
            /* [in] */ BSTR remarks);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_WellKnownText )( 
            IGeographicCoordinateSystem * This,
            /* [retval][out] */ BSTR *wkt);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Usage )( 
            IGeographicCoordinateSystem * This,
            /* [retval][out] */ BSTR *usage);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Usage )( 
            IGeographicCoordinateSystem * This,
            /* [in] */ BSTR usage);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_HorizontalDatum )( 
            IGeographicCoordinateSystem * This,
            /* [retval][out] */ IHorizontalDatum **datum);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_HorizontalDatum )( 
            IGeographicCoordinateSystem * This,
            /* [in] */ IHorizontalDatum *datum);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_AngularUnit )( 
            IGeographicCoordinateSystem * This,
            /* [retval][out] */ IAngularUnit **unit);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_AngularUnit )( 
            IGeographicCoordinateSystem * This,
            /* [in] */ IAngularUnit *unit);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrimeMeridian )( 
            IGeographicCoordinateSystem * This,
            /* [retval][out] */ IPrimeMeridian **prmMerid);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_PrimeMeridian )( 
            IGeographicCoordinateSystem * This,
            /* [in] */ IPrimeMeridian *prmMerid);
        
        END_INTERFACE
    } IGeographicCoordinateSystemVtbl;

    interface IGeographicCoordinateSystem
    {
        CONST_VTBL struct IGeographicCoordinateSystemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGeographicCoordinateSystem_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGeographicCoordinateSystem_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGeographicCoordinateSystem_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGeographicCoordinateSystem_get_Name(This,name)	\
    (This)->lpVtbl -> get_Name(This,name)

#define IGeographicCoordinateSystem_put_Name(This,name)	\
    (This)->lpVtbl -> put_Name(This,name)

#define IGeographicCoordinateSystem_get_Authority(This,name)	\
    (This)->lpVtbl -> get_Authority(This,name)

#define IGeographicCoordinateSystem_put_Authority(This,name)	\
    (This)->lpVtbl -> put_Authority(This,name)

#define IGeographicCoordinateSystem_get_Code(This,code)	\
    (This)->lpVtbl -> get_Code(This,code)

#define IGeographicCoordinateSystem_put_Code(This,code)	\
    (This)->lpVtbl -> put_Code(This,code)

#define IGeographicCoordinateSystem_get_Alias(This,alias)	\
    (This)->lpVtbl -> get_Alias(This,alias)

#define IGeographicCoordinateSystem_put_Alias(This,alias)	\
    (This)->lpVtbl -> put_Alias(This,alias)

#define IGeographicCoordinateSystem_get_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> get_Abbreviation(This,abbrev)

#define IGeographicCoordinateSystem_put_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> put_Abbreviation(This,abbrev)

#define IGeographicCoordinateSystem_get_Remarks(This,remarks)	\
    (This)->lpVtbl -> get_Remarks(This,remarks)

#define IGeographicCoordinateSystem_put_Remarks(This,remarks)	\
    (This)->lpVtbl -> put_Remarks(This,remarks)

#define IGeographicCoordinateSystem_get_WellKnownText(This,wkt)	\
    (This)->lpVtbl -> get_WellKnownText(This,wkt)




#define IGeographicCoordinateSystem_get_Usage(This,usage)	\
    (This)->lpVtbl -> get_Usage(This,usage)

#define IGeographicCoordinateSystem_put_Usage(This,usage)	\
    (This)->lpVtbl -> put_Usage(This,usage)

#define IGeographicCoordinateSystem_get_HorizontalDatum(This,datum)	\
    (This)->lpVtbl -> get_HorizontalDatum(This,datum)

#define IGeographicCoordinateSystem_put_HorizontalDatum(This,datum)	\
    (This)->lpVtbl -> put_HorizontalDatum(This,datum)

#define IGeographicCoordinateSystem_get_AngularUnit(This,unit)	\
    (This)->lpVtbl -> get_AngularUnit(This,unit)

#define IGeographicCoordinateSystem_put_AngularUnit(This,unit)	\
    (This)->lpVtbl -> put_AngularUnit(This,unit)

#define IGeographicCoordinateSystem_get_PrimeMeridian(This,prmMerid)	\
    (This)->lpVtbl -> get_PrimeMeridian(This,prmMerid)

#define IGeographicCoordinateSystem_put_PrimeMeridian(This,prmMerid)	\
    (This)->lpVtbl -> put_PrimeMeridian(This,prmMerid)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IGeographicCoordinateSystem_get_Usage_Proxy( 
    IGeographicCoordinateSystem * This,
    /* [retval][out] */ BSTR *usage);


void __RPC_STUB IGeographicCoordinateSystem_get_Usage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IGeographicCoordinateSystem_put_Usage_Proxy( 
    IGeographicCoordinateSystem * This,
    /* [in] */ BSTR usage);


void __RPC_STUB IGeographicCoordinateSystem_put_Usage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IGeographicCoordinateSystem_get_HorizontalDatum_Proxy( 
    IGeographicCoordinateSystem * This,
    /* [retval][out] */ IHorizontalDatum **datum);


void __RPC_STUB IGeographicCoordinateSystem_get_HorizontalDatum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IGeographicCoordinateSystem_put_HorizontalDatum_Proxy( 
    IGeographicCoordinateSystem * This,
    /* [in] */ IHorizontalDatum *datum);


void __RPC_STUB IGeographicCoordinateSystem_put_HorizontalDatum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IGeographicCoordinateSystem_get_AngularUnit_Proxy( 
    IGeographicCoordinateSystem * This,
    /* [retval][out] */ IAngularUnit **unit);


void __RPC_STUB IGeographicCoordinateSystem_get_AngularUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IGeographicCoordinateSystem_put_AngularUnit_Proxy( 
    IGeographicCoordinateSystem * This,
    /* [in] */ IAngularUnit *unit);


void __RPC_STUB IGeographicCoordinateSystem_put_AngularUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IGeographicCoordinateSystem_get_PrimeMeridian_Proxy( 
    IGeographicCoordinateSystem * This,
    /* [retval][out] */ IPrimeMeridian **prmMerid);


void __RPC_STUB IGeographicCoordinateSystem_get_PrimeMeridian_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IGeographicCoordinateSystem_put_PrimeMeridian_Proxy( 
    IGeographicCoordinateSystem * This,
    /* [in] */ IPrimeMeridian *prmMerid);


void __RPC_STUB IGeographicCoordinateSystem_put_PrimeMeridian_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGeographicCoordinateSystem_INTERFACE_DEFINED__ */


#ifndef __IParameter_INTERFACE_DEFINED__
#define __IParameter_INTERFACE_DEFINED__

/* interface IParameter */
/* [uuid][object] */ 


EXTERN_C const IID IID_IParameter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9a5e32d0-fe1f-11d0-ad87-080009b6f22b")
    IParameter : public ISpatialReferenceInfo
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ValueUnit( 
            /* [in] */ IUnit *unit) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ValueUnit( 
            /* [retval][out] */ IUnit **unit) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ double value) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ double *value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IParameterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IParameter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IParameter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IParameter * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IParameter * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IParameter * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Authority )( 
            IParameter * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Authority )( 
            IParameter * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Code )( 
            IParameter * This,
            /* [retval][out] */ long *code);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Code )( 
            IParameter * This,
            /* [in] */ long code);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Alias )( 
            IParameter * This,
            /* [retval][out] */ BSTR *alias);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Alias )( 
            IParameter * This,
            /* [in] */ BSTR alias);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Abbreviation )( 
            IParameter * This,
            /* [retval][out] */ BSTR *abbrev);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Abbreviation )( 
            IParameter * This,
            /* [in] */ BSTR abbrev);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Remarks )( 
            IParameter * This,
            /* [retval][out] */ BSTR *remarks);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Remarks )( 
            IParameter * This,
            /* [in] */ BSTR remarks);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_WellKnownText )( 
            IParameter * This,
            /* [retval][out] */ BSTR *wkt);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ValueUnit )( 
            IParameter * This,
            /* [in] */ IUnit *unit);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ValueUnit )( 
            IParameter * This,
            /* [retval][out] */ IUnit **unit);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            IParameter * This,
            /* [in] */ double value);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IParameter * This,
            /* [retval][out] */ double *value);
        
        END_INTERFACE
    } IParameterVtbl;

    interface IParameter
    {
        CONST_VTBL struct IParameterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IParameter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IParameter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IParameter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IParameter_get_Name(This,name)	\
    (This)->lpVtbl -> get_Name(This,name)

#define IParameter_put_Name(This,name)	\
    (This)->lpVtbl -> put_Name(This,name)

#define IParameter_get_Authority(This,name)	\
    (This)->lpVtbl -> get_Authority(This,name)

#define IParameter_put_Authority(This,name)	\
    (This)->lpVtbl -> put_Authority(This,name)

#define IParameter_get_Code(This,code)	\
    (This)->lpVtbl -> get_Code(This,code)

#define IParameter_put_Code(This,code)	\
    (This)->lpVtbl -> put_Code(This,code)

#define IParameter_get_Alias(This,alias)	\
    (This)->lpVtbl -> get_Alias(This,alias)

#define IParameter_put_Alias(This,alias)	\
    (This)->lpVtbl -> put_Alias(This,alias)

#define IParameter_get_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> get_Abbreviation(This,abbrev)

#define IParameter_put_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> put_Abbreviation(This,abbrev)

#define IParameter_get_Remarks(This,remarks)	\
    (This)->lpVtbl -> get_Remarks(This,remarks)

#define IParameter_put_Remarks(This,remarks)	\
    (This)->lpVtbl -> put_Remarks(This,remarks)

#define IParameter_get_WellKnownText(This,wkt)	\
    (This)->lpVtbl -> get_WellKnownText(This,wkt)


#define IParameter_put_ValueUnit(This,unit)	\
    (This)->lpVtbl -> put_ValueUnit(This,unit)

#define IParameter_get_ValueUnit(This,unit)	\
    (This)->lpVtbl -> get_ValueUnit(This,unit)

#define IParameter_put_Value(This,value)	\
    (This)->lpVtbl -> put_Value(This,value)

#define IParameter_get_Value(This,value)	\
    (This)->lpVtbl -> get_Value(This,value)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IParameter_put_ValueUnit_Proxy( 
    IParameter * This,
    /* [in] */ IUnit *unit);


void __RPC_STUB IParameter_put_ValueUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IParameter_get_ValueUnit_Proxy( 
    IParameter * This,
    /* [retval][out] */ IUnit **unit);


void __RPC_STUB IParameter_get_ValueUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IParameter_put_Value_Proxy( 
    IParameter * This,
    /* [in] */ double value);


void __RPC_STUB IParameter_put_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IParameter_get_Value_Proxy( 
    IParameter * This,
    /* [retval][out] */ double *value);


void __RPC_STUB IParameter_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IParameter_INTERFACE_DEFINED__ */


#ifndef __IParameterInfo_INTERFACE_DEFINED__
#define __IParameterInfo_INTERFACE_DEFINED__

/* interface IParameterInfo */
/* [uuid][object] */ 


EXTERN_C const IID IID_IParameterInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7309b460-fe1f-11d0-ad87-080009b6f22b")
    IParameterInfo : public IUnknown
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_NumParameters( 
            /* [retval][out] */ long *numParameters) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DefaultParameters( 
            /* [in] */ long size,
            /* [size_is][out] */ IParameter *parameters[  ]) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Parameters( 
            /* [in] */ long size,
            /* [size_is][out] */ IParameter *parameters[  ]) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Parameters( 
            /* [in] */ long size,
            /* [size_is][in] */ IParameter *parameters[  ]) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IParameterInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IParameterInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IParameterInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IParameterInfo * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_NumParameters )( 
            IParameterInfo * This,
            /* [retval][out] */ long *numParameters);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultParameters )( 
            IParameterInfo * This,
            /* [in] */ long size,
            /* [size_is][out] */ IParameter *parameters[  ]);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parameters )( 
            IParameterInfo * This,
            /* [in] */ long size,
            /* [size_is][out] */ IParameter *parameters[  ]);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Parameters )( 
            IParameterInfo * This,
            /* [in] */ long size,
            /* [size_is][in] */ IParameter *parameters[  ]);
        
        END_INTERFACE
    } IParameterInfoVtbl;

    interface IParameterInfo
    {
        CONST_VTBL struct IParameterInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IParameterInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IParameterInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IParameterInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IParameterInfo_get_NumParameters(This,numParameters)	\
    (This)->lpVtbl -> get_NumParameters(This,numParameters)

#define IParameterInfo_get_DefaultParameters(This,size,parameters)	\
    (This)->lpVtbl -> get_DefaultParameters(This,size,parameters)

#define IParameterInfo_get_Parameters(This,size,parameters)	\
    (This)->lpVtbl -> get_Parameters(This,size,parameters)

#define IParameterInfo_put_Parameters(This,size,parameters)	\
    (This)->lpVtbl -> put_Parameters(This,size,parameters)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IParameterInfo_get_NumParameters_Proxy( 
    IParameterInfo * This,
    /* [retval][out] */ long *numParameters);


void __RPC_STUB IParameterInfo_get_NumParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IParameterInfo_get_DefaultParameters_Proxy( 
    IParameterInfo * This,
    /* [in] */ long size,
    /* [size_is][out] */ IParameter *parameters[  ]);


void __RPC_STUB IParameterInfo_get_DefaultParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IParameterInfo_get_Parameters_Proxy( 
    IParameterInfo * This,
    /* [in] */ long size,
    /* [size_is][out] */ IParameter *parameters[  ]);


void __RPC_STUB IParameterInfo_get_Parameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IParameterInfo_put_Parameters_Proxy( 
    IParameterInfo * This,
    /* [in] */ long size,
    /* [size_is][in] */ IParameter *parameters[  ]);


void __RPC_STUB IParameterInfo_put_Parameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IParameterInfo_INTERFACE_DEFINED__ */


#ifndef __IGeographicTransform_INTERFACE_DEFINED__
#define __IGeographicTransform_INTERFACE_DEFINED__

/* interface IGeographicTransform */
/* [uuid][object] */ 


EXTERN_C const IID IID_IGeographicTransform;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5eb513c0-fe1f-11d0-ad87-080009b6f22b")
    IGeographicTransform : public ISpatialReferenceInfo
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_SourceGCS( 
            /* [out] */ IGeographicCoordinateSystem **gcs) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_SourceGCS( 
            /* [in] */ IGeographicCoordinateSystem *gcs) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_TargetGCS( 
            /* [out] */ IGeographicCoordinateSystem **gcs) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_TargetGCS( 
            /* [in] */ IGeographicCoordinateSystem *gcs) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ParameterInfo( 
            /* [out] */ IParameterInfo **paramInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Forward( 
            /* [in] */ long count,
            /* [size_is][out][in] */ WKSPoint points[  ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Inverse( 
            /* [in] */ long count,
            /* [size_is][out][in] */ WKSPoint points[  ]) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGeographicTransformVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGeographicTransform * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGeographicTransform * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGeographicTransform * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IGeographicTransform * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IGeographicTransform * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Authority )( 
            IGeographicTransform * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Authority )( 
            IGeographicTransform * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Code )( 
            IGeographicTransform * This,
            /* [retval][out] */ long *code);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Code )( 
            IGeographicTransform * This,
            /* [in] */ long code);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Alias )( 
            IGeographicTransform * This,
            /* [retval][out] */ BSTR *alias);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Alias )( 
            IGeographicTransform * This,
            /* [in] */ BSTR alias);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Abbreviation )( 
            IGeographicTransform * This,
            /* [retval][out] */ BSTR *abbrev);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Abbreviation )( 
            IGeographicTransform * This,
            /* [in] */ BSTR abbrev);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Remarks )( 
            IGeographicTransform * This,
            /* [retval][out] */ BSTR *remarks);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Remarks )( 
            IGeographicTransform * This,
            /* [in] */ BSTR remarks);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_WellKnownText )( 
            IGeographicTransform * This,
            /* [retval][out] */ BSTR *wkt);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_SourceGCS )( 
            IGeographicTransform * This,
            /* [out] */ IGeographicCoordinateSystem **gcs);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_SourceGCS )( 
            IGeographicTransform * This,
            /* [in] */ IGeographicCoordinateSystem *gcs);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_TargetGCS )( 
            IGeographicTransform * This,
            /* [out] */ IGeographicCoordinateSystem **gcs);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_TargetGCS )( 
            IGeographicTransform * This,
            /* [in] */ IGeographicCoordinateSystem *gcs);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ParameterInfo )( 
            IGeographicTransform * This,
            /* [out] */ IParameterInfo **paramInfo);
        
        HRESULT ( STDMETHODCALLTYPE *Forward )( 
            IGeographicTransform * This,
            /* [in] */ long count,
            /* [size_is][out][in] */ WKSPoint points[  ]);
        
        HRESULT ( STDMETHODCALLTYPE *Inverse )( 
            IGeographicTransform * This,
            /* [in] */ long count,
            /* [size_is][out][in] */ WKSPoint points[  ]);
        
        END_INTERFACE
    } IGeographicTransformVtbl;

    interface IGeographicTransform
    {
        CONST_VTBL struct IGeographicTransformVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGeographicTransform_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGeographicTransform_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGeographicTransform_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGeographicTransform_get_Name(This,name)	\
    (This)->lpVtbl -> get_Name(This,name)

#define IGeographicTransform_put_Name(This,name)	\
    (This)->lpVtbl -> put_Name(This,name)

#define IGeographicTransform_get_Authority(This,name)	\
    (This)->lpVtbl -> get_Authority(This,name)

#define IGeographicTransform_put_Authority(This,name)	\
    (This)->lpVtbl -> put_Authority(This,name)

#define IGeographicTransform_get_Code(This,code)	\
    (This)->lpVtbl -> get_Code(This,code)

#define IGeographicTransform_put_Code(This,code)	\
    (This)->lpVtbl -> put_Code(This,code)

#define IGeographicTransform_get_Alias(This,alias)	\
    (This)->lpVtbl -> get_Alias(This,alias)

#define IGeographicTransform_put_Alias(This,alias)	\
    (This)->lpVtbl -> put_Alias(This,alias)

#define IGeographicTransform_get_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> get_Abbreviation(This,abbrev)

#define IGeographicTransform_put_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> put_Abbreviation(This,abbrev)

#define IGeographicTransform_get_Remarks(This,remarks)	\
    (This)->lpVtbl -> get_Remarks(This,remarks)

#define IGeographicTransform_put_Remarks(This,remarks)	\
    (This)->lpVtbl -> put_Remarks(This,remarks)

#define IGeographicTransform_get_WellKnownText(This,wkt)	\
    (This)->lpVtbl -> get_WellKnownText(This,wkt)


#define IGeographicTransform_get_SourceGCS(This,gcs)	\
    (This)->lpVtbl -> get_SourceGCS(This,gcs)

#define IGeographicTransform_put_SourceGCS(This,gcs)	\
    (This)->lpVtbl -> put_SourceGCS(This,gcs)

#define IGeographicTransform_get_TargetGCS(This,gcs)	\
    (This)->lpVtbl -> get_TargetGCS(This,gcs)

#define IGeographicTransform_put_TargetGCS(This,gcs)	\
    (This)->lpVtbl -> put_TargetGCS(This,gcs)

#define IGeographicTransform_get_ParameterInfo(This,paramInfo)	\
    (This)->lpVtbl -> get_ParameterInfo(This,paramInfo)

#define IGeographicTransform_Forward(This,count,points)	\
    (This)->lpVtbl -> Forward(This,count,points)

#define IGeographicTransform_Inverse(This,count,points)	\
    (This)->lpVtbl -> Inverse(This,count,points)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IGeographicTransform_get_SourceGCS_Proxy( 
    IGeographicTransform * This,
    /* [out] */ IGeographicCoordinateSystem **gcs);


void __RPC_STUB IGeographicTransform_get_SourceGCS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IGeographicTransform_put_SourceGCS_Proxy( 
    IGeographicTransform * This,
    /* [in] */ IGeographicCoordinateSystem *gcs);


void __RPC_STUB IGeographicTransform_put_SourceGCS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IGeographicTransform_get_TargetGCS_Proxy( 
    IGeographicTransform * This,
    /* [out] */ IGeographicCoordinateSystem **gcs);


void __RPC_STUB IGeographicTransform_get_TargetGCS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IGeographicTransform_put_TargetGCS_Proxy( 
    IGeographicTransform * This,
    /* [in] */ IGeographicCoordinateSystem *gcs);


void __RPC_STUB IGeographicTransform_put_TargetGCS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IGeographicTransform_get_ParameterInfo_Proxy( 
    IGeographicTransform * This,
    /* [out] */ IParameterInfo **paramInfo);


void __RPC_STUB IGeographicTransform_get_ParameterInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGeographicTransform_Forward_Proxy( 
    IGeographicTransform * This,
    /* [in] */ long count,
    /* [size_is][out][in] */ WKSPoint points[  ]);


void __RPC_STUB IGeographicTransform_Forward_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGeographicTransform_Inverse_Proxy( 
    IGeographicTransform * This,
    /* [in] */ long count,
    /* [size_is][out][in] */ WKSPoint points[  ]);


void __RPC_STUB IGeographicTransform_Inverse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGeographicTransform_INTERFACE_DEFINED__ */


#ifndef __IProjection_INTERFACE_DEFINED__
#define __IProjection_INTERFACE_DEFINED__

/* interface IProjection */
/* [uuid][object] */ 


EXTERN_C const IID IID_IProjection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5002f420-fe1f-11d0-ad87-080009b6f22b")
    IProjection : public ISpatialReferenceInfo
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Usage( 
            /* [retval][out] */ BSTR *usage) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Classification( 
            /* [retval][out] */ BSTR *classification) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Forward( 
            /* [in] */ long count,
            /* [size_is][out][in] */ WKSPoint points[  ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Inverse( 
            /* [in] */ long count,
            /* [size_is][out][in] */ WKSPoint points[  ]) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ParameterInfo( 
            /* [retval][out] */ IParameterInfo **paramInfo) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_AngularUnit( 
            /* [retval][out] */ IAngularUnit **unit) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_AngularUnit( 
            /* [in] */ IAngularUnit *unit) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_LinearUnit( 
            /* [retval][out] */ ILinearUnit **unit) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_LinearUnit( 
            /* [in] */ ILinearUnit *unit) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Ellipsoid( 
            /* [retval][out] */ IEllipsoid **ellipsoid) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Ellipsoid( 
            /* [in] */ IEllipsoid *ellipsoid) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IProjectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProjection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProjection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProjection * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IProjection * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IProjection * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Authority )( 
            IProjection * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Authority )( 
            IProjection * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Code )( 
            IProjection * This,
            /* [retval][out] */ long *code);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Code )( 
            IProjection * This,
            /* [in] */ long code);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Alias )( 
            IProjection * This,
            /* [retval][out] */ BSTR *alias);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Alias )( 
            IProjection * This,
            /* [in] */ BSTR alias);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Abbreviation )( 
            IProjection * This,
            /* [retval][out] */ BSTR *abbrev);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Abbreviation )( 
            IProjection * This,
            /* [in] */ BSTR abbrev);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Remarks )( 
            IProjection * This,
            /* [retval][out] */ BSTR *remarks);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Remarks )( 
            IProjection * This,
            /* [in] */ BSTR remarks);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_WellKnownText )( 
            IProjection * This,
            /* [retval][out] */ BSTR *wkt);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Usage )( 
            IProjection * This,
            /* [retval][out] */ BSTR *usage);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Classification )( 
            IProjection * This,
            /* [retval][out] */ BSTR *classification);
        
        HRESULT ( STDMETHODCALLTYPE *Forward )( 
            IProjection * This,
            /* [in] */ long count,
            /* [size_is][out][in] */ WKSPoint points[  ]);
        
        HRESULT ( STDMETHODCALLTYPE *Inverse )( 
            IProjection * This,
            /* [in] */ long count,
            /* [size_is][out][in] */ WKSPoint points[  ]);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ParameterInfo )( 
            IProjection * This,
            /* [retval][out] */ IParameterInfo **paramInfo);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_AngularUnit )( 
            IProjection * This,
            /* [retval][out] */ IAngularUnit **unit);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_AngularUnit )( 
            IProjection * This,
            /* [in] */ IAngularUnit *unit);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_LinearUnit )( 
            IProjection * This,
            /* [retval][out] */ ILinearUnit **unit);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_LinearUnit )( 
            IProjection * This,
            /* [in] */ ILinearUnit *unit);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Ellipsoid )( 
            IProjection * This,
            /* [retval][out] */ IEllipsoid **ellipsoid);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Ellipsoid )( 
            IProjection * This,
            /* [in] */ IEllipsoid *ellipsoid);
        
        END_INTERFACE
    } IProjectionVtbl;

    interface IProjection
    {
        CONST_VTBL struct IProjectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProjection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IProjection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IProjection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IProjection_get_Name(This,name)	\
    (This)->lpVtbl -> get_Name(This,name)

#define IProjection_put_Name(This,name)	\
    (This)->lpVtbl -> put_Name(This,name)

#define IProjection_get_Authority(This,name)	\
    (This)->lpVtbl -> get_Authority(This,name)

#define IProjection_put_Authority(This,name)	\
    (This)->lpVtbl -> put_Authority(This,name)

#define IProjection_get_Code(This,code)	\
    (This)->lpVtbl -> get_Code(This,code)

#define IProjection_put_Code(This,code)	\
    (This)->lpVtbl -> put_Code(This,code)

#define IProjection_get_Alias(This,alias)	\
    (This)->lpVtbl -> get_Alias(This,alias)

#define IProjection_put_Alias(This,alias)	\
    (This)->lpVtbl -> put_Alias(This,alias)

#define IProjection_get_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> get_Abbreviation(This,abbrev)

#define IProjection_put_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> put_Abbreviation(This,abbrev)

#define IProjection_get_Remarks(This,remarks)	\
    (This)->lpVtbl -> get_Remarks(This,remarks)

#define IProjection_put_Remarks(This,remarks)	\
    (This)->lpVtbl -> put_Remarks(This,remarks)

#define IProjection_get_WellKnownText(This,wkt)	\
    (This)->lpVtbl -> get_WellKnownText(This,wkt)


#define IProjection_get_Usage(This,usage)	\
    (This)->lpVtbl -> get_Usage(This,usage)

#define IProjection_get_Classification(This,classification)	\
    (This)->lpVtbl -> get_Classification(This,classification)

#define IProjection_Forward(This,count,points)	\
    (This)->lpVtbl -> Forward(This,count,points)

#define IProjection_Inverse(This,count,points)	\
    (This)->lpVtbl -> Inverse(This,count,points)

#define IProjection_get_ParameterInfo(This,paramInfo)	\
    (This)->lpVtbl -> get_ParameterInfo(This,paramInfo)

#define IProjection_get_AngularUnit(This,unit)	\
    (This)->lpVtbl -> get_AngularUnit(This,unit)

#define IProjection_put_AngularUnit(This,unit)	\
    (This)->lpVtbl -> put_AngularUnit(This,unit)

#define IProjection_get_LinearUnit(This,unit)	\
    (This)->lpVtbl -> get_LinearUnit(This,unit)

#define IProjection_put_LinearUnit(This,unit)	\
    (This)->lpVtbl -> put_LinearUnit(This,unit)

#define IProjection_get_Ellipsoid(This,ellipsoid)	\
    (This)->lpVtbl -> get_Ellipsoid(This,ellipsoid)

#define IProjection_put_Ellipsoid(This,ellipsoid)	\
    (This)->lpVtbl -> put_Ellipsoid(This,ellipsoid)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IProjection_get_Usage_Proxy( 
    IProjection * This,
    /* [retval][out] */ BSTR *usage);


void __RPC_STUB IProjection_get_Usage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjection_get_Classification_Proxy( 
    IProjection * This,
    /* [retval][out] */ BSTR *classification);


void __RPC_STUB IProjection_get_Classification_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IProjection_Forward_Proxy( 
    IProjection * This,
    /* [in] */ long count,
    /* [size_is][out][in] */ WKSPoint points[  ]);


void __RPC_STUB IProjection_Forward_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IProjection_Inverse_Proxy( 
    IProjection * This,
    /* [in] */ long count,
    /* [size_is][out][in] */ WKSPoint points[  ]);


void __RPC_STUB IProjection_Inverse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjection_get_ParameterInfo_Proxy( 
    IProjection * This,
    /* [retval][out] */ IParameterInfo **paramInfo);


void __RPC_STUB IProjection_get_ParameterInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjection_get_AngularUnit_Proxy( 
    IProjection * This,
    /* [retval][out] */ IAngularUnit **unit);


void __RPC_STUB IProjection_get_AngularUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IProjection_put_AngularUnit_Proxy( 
    IProjection * This,
    /* [in] */ IAngularUnit *unit);


void __RPC_STUB IProjection_put_AngularUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjection_get_LinearUnit_Proxy( 
    IProjection * This,
    /* [retval][out] */ ILinearUnit **unit);


void __RPC_STUB IProjection_get_LinearUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IProjection_put_LinearUnit_Proxy( 
    IProjection * This,
    /* [in] */ ILinearUnit *unit);


void __RPC_STUB IProjection_put_LinearUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjection_get_Ellipsoid_Proxy( 
    IProjection * This,
    /* [retval][out] */ IEllipsoid **ellipsoid);


void __RPC_STUB IProjection_get_Ellipsoid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IProjection_put_Ellipsoid_Proxy( 
    IProjection * This,
    /* [in] */ IEllipsoid *ellipsoid);


void __RPC_STUB IProjection_put_Ellipsoid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IProjection_INTERFACE_DEFINED__ */


#ifndef __IProjectedCoordinateSystem_INTERFACE_DEFINED__
#define __IProjectedCoordinateSystem_INTERFACE_DEFINED__

/* interface IProjectedCoordinateSystem */
/* [uuid][object] */ 


EXTERN_C const IID IID_IProjectedCoordinateSystem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3dc39ff0-fe1f-11d0-ad87-080009b6f22b")
    IProjectedCoordinateSystem : public IGeodeticSpatialReference
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Usage( 
            /* [retval][out] */ BSTR *usage) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Usage( 
            /* [in] */ BSTR usage) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_GeographicCoordinateSystem( 
            /* [retval][out] */ IGeographicCoordinateSystem **gcs) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_GeographicCoordinateSystem( 
            /* [in] */ IGeographicCoordinateSystem *gcs) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_LinearUnit( 
            /* [retval][out] */ ILinearUnit **unit) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_LinearUnit( 
            /* [in] */ ILinearUnit *unit) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Projection( 
            /* [retval][out] */ IProjection **projection) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Projection( 
            /* [in] */ IProjection *projection) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ParameterInfo( 
            /* [retval][out] */ IParameterInfo **paramInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Forward( 
            /* [in] */ long count,
            /* [size_is][out][in] */ WKSPoint points[  ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Inverse( 
            /* [in] */ long count,
            /* [size_is][out][in] */ WKSPoint points[  ]) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IProjectedCoordinateSystemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProjectedCoordinateSystem * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProjectedCoordinateSystem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProjectedCoordinateSystem * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IProjectedCoordinateSystem * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IProjectedCoordinateSystem * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Authority )( 
            IProjectedCoordinateSystem * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Authority )( 
            IProjectedCoordinateSystem * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Code )( 
            IProjectedCoordinateSystem * This,
            /* [retval][out] */ long *code);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Code )( 
            IProjectedCoordinateSystem * This,
            /* [in] */ long code);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Alias )( 
            IProjectedCoordinateSystem * This,
            /* [retval][out] */ BSTR *alias);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Alias )( 
            IProjectedCoordinateSystem * This,
            /* [in] */ BSTR alias);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Abbreviation )( 
            IProjectedCoordinateSystem * This,
            /* [retval][out] */ BSTR *abbrev);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Abbreviation )( 
            IProjectedCoordinateSystem * This,
            /* [in] */ BSTR abbrev);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Remarks )( 
            IProjectedCoordinateSystem * This,
            /* [retval][out] */ BSTR *remarks);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Remarks )( 
            IProjectedCoordinateSystem * This,
            /* [in] */ BSTR remarks);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_WellKnownText )( 
            IProjectedCoordinateSystem * This,
            /* [retval][out] */ BSTR *wkt);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Usage )( 
            IProjectedCoordinateSystem * This,
            /* [retval][out] */ BSTR *usage);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Usage )( 
            IProjectedCoordinateSystem * This,
            /* [in] */ BSTR usage);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_GeographicCoordinateSystem )( 
            IProjectedCoordinateSystem * This,
            /* [retval][out] */ IGeographicCoordinateSystem **gcs);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_GeographicCoordinateSystem )( 
            IProjectedCoordinateSystem * This,
            /* [in] */ IGeographicCoordinateSystem *gcs);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_LinearUnit )( 
            IProjectedCoordinateSystem * This,
            /* [retval][out] */ ILinearUnit **unit);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_LinearUnit )( 
            IProjectedCoordinateSystem * This,
            /* [in] */ ILinearUnit *unit);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Projection )( 
            IProjectedCoordinateSystem * This,
            /* [retval][out] */ IProjection **projection);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Projection )( 
            IProjectedCoordinateSystem * This,
            /* [in] */ IProjection *projection);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ParameterInfo )( 
            IProjectedCoordinateSystem * This,
            /* [retval][out] */ IParameterInfo **paramInfo);
        
        HRESULT ( STDMETHODCALLTYPE *Forward )( 
            IProjectedCoordinateSystem * This,
            /* [in] */ long count,
            /* [size_is][out][in] */ WKSPoint points[  ]);
        
        HRESULT ( STDMETHODCALLTYPE *Inverse )( 
            IProjectedCoordinateSystem * This,
            /* [in] */ long count,
            /* [size_is][out][in] */ WKSPoint points[  ]);
        
        END_INTERFACE
    } IProjectedCoordinateSystemVtbl;

    interface IProjectedCoordinateSystem
    {
        CONST_VTBL struct IProjectedCoordinateSystemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProjectedCoordinateSystem_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IProjectedCoordinateSystem_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IProjectedCoordinateSystem_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IProjectedCoordinateSystem_get_Name(This,name)	\
    (This)->lpVtbl -> get_Name(This,name)

#define IProjectedCoordinateSystem_put_Name(This,name)	\
    (This)->lpVtbl -> put_Name(This,name)

#define IProjectedCoordinateSystem_get_Authority(This,name)	\
    (This)->lpVtbl -> get_Authority(This,name)

#define IProjectedCoordinateSystem_put_Authority(This,name)	\
    (This)->lpVtbl -> put_Authority(This,name)

#define IProjectedCoordinateSystem_get_Code(This,code)	\
    (This)->lpVtbl -> get_Code(This,code)

#define IProjectedCoordinateSystem_put_Code(This,code)	\
    (This)->lpVtbl -> put_Code(This,code)

#define IProjectedCoordinateSystem_get_Alias(This,alias)	\
    (This)->lpVtbl -> get_Alias(This,alias)

#define IProjectedCoordinateSystem_put_Alias(This,alias)	\
    (This)->lpVtbl -> put_Alias(This,alias)

#define IProjectedCoordinateSystem_get_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> get_Abbreviation(This,abbrev)

#define IProjectedCoordinateSystem_put_Abbreviation(This,abbrev)	\
    (This)->lpVtbl -> put_Abbreviation(This,abbrev)

#define IProjectedCoordinateSystem_get_Remarks(This,remarks)	\
    (This)->lpVtbl -> get_Remarks(This,remarks)

#define IProjectedCoordinateSystem_put_Remarks(This,remarks)	\
    (This)->lpVtbl -> put_Remarks(This,remarks)

#define IProjectedCoordinateSystem_get_WellKnownText(This,wkt)	\
    (This)->lpVtbl -> get_WellKnownText(This,wkt)




#define IProjectedCoordinateSystem_get_Usage(This,usage)	\
    (This)->lpVtbl -> get_Usage(This,usage)

#define IProjectedCoordinateSystem_put_Usage(This,usage)	\
    (This)->lpVtbl -> put_Usage(This,usage)

#define IProjectedCoordinateSystem_get_GeographicCoordinateSystem(This,gcs)	\
    (This)->lpVtbl -> get_GeographicCoordinateSystem(This,gcs)

#define IProjectedCoordinateSystem_put_GeographicCoordinateSystem(This,gcs)	\
    (This)->lpVtbl -> put_GeographicCoordinateSystem(This,gcs)

#define IProjectedCoordinateSystem_get_LinearUnit(This,unit)	\
    (This)->lpVtbl -> get_LinearUnit(This,unit)

#define IProjectedCoordinateSystem_put_LinearUnit(This,unit)	\
    (This)->lpVtbl -> put_LinearUnit(This,unit)

#define IProjectedCoordinateSystem_get_Projection(This,projection)	\
    (This)->lpVtbl -> get_Projection(This,projection)

#define IProjectedCoordinateSystem_put_Projection(This,projection)	\
    (This)->lpVtbl -> put_Projection(This,projection)

#define IProjectedCoordinateSystem_get_ParameterInfo(This,paramInfo)	\
    (This)->lpVtbl -> get_ParameterInfo(This,paramInfo)

#define IProjectedCoordinateSystem_Forward(This,count,points)	\
    (This)->lpVtbl -> Forward(This,count,points)

#define IProjectedCoordinateSystem_Inverse(This,count,points)	\
    (This)->lpVtbl -> Inverse(This,count,points)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_get_Usage_Proxy( 
    IProjectedCoordinateSystem * This,
    /* [retval][out] */ BSTR *usage);


void __RPC_STUB IProjectedCoordinateSystem_get_Usage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_put_Usage_Proxy( 
    IProjectedCoordinateSystem * This,
    /* [in] */ BSTR usage);


void __RPC_STUB IProjectedCoordinateSystem_put_Usage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_get_GeographicCoordinateSystem_Proxy( 
    IProjectedCoordinateSystem * This,
    /* [retval][out] */ IGeographicCoordinateSystem **gcs);


void __RPC_STUB IProjectedCoordinateSystem_get_GeographicCoordinateSystem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_put_GeographicCoordinateSystem_Proxy( 
    IProjectedCoordinateSystem * This,
    /* [in] */ IGeographicCoordinateSystem *gcs);


void __RPC_STUB IProjectedCoordinateSystem_put_GeographicCoordinateSystem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_get_LinearUnit_Proxy( 
    IProjectedCoordinateSystem * This,
    /* [retval][out] */ ILinearUnit **unit);


void __RPC_STUB IProjectedCoordinateSystem_get_LinearUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_put_LinearUnit_Proxy( 
    IProjectedCoordinateSystem * This,
    /* [in] */ ILinearUnit *unit);


void __RPC_STUB IProjectedCoordinateSystem_put_LinearUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_get_Projection_Proxy( 
    IProjectedCoordinateSystem * This,
    /* [retval][out] */ IProjection **projection);


void __RPC_STUB IProjectedCoordinateSystem_get_Projection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_put_Projection_Proxy( 
    IProjectedCoordinateSystem * This,
    /* [in] */ IProjection *projection);


void __RPC_STUB IProjectedCoordinateSystem_put_Projection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_get_ParameterInfo_Proxy( 
    IProjectedCoordinateSystem * This,
    /* [retval][out] */ IParameterInfo **paramInfo);


void __RPC_STUB IProjectedCoordinateSystem_get_ParameterInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_Forward_Proxy( 
    IProjectedCoordinateSystem * This,
    /* [in] */ long count,
    /* [size_is][out][in] */ WKSPoint points[  ]);


void __RPC_STUB IProjectedCoordinateSystem_Forward_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_Inverse_Proxy( 
    IProjectedCoordinateSystem * This,
    /* [in] */ long count,
    /* [size_is][out][in] */ WKSPoint points[  ]);


void __RPC_STUB IProjectedCoordinateSystem_Inverse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IProjectedCoordinateSystem_INTERFACE_DEFINED__ */


#ifndef __ISpatialReferenceFactory_INTERFACE_DEFINED__
#define __ISpatialReferenceFactory_INTERFACE_DEFINED__

/* interface ISpatialReferenceFactory */
/* [uuid][object] */ 


EXTERN_C const IID IID_ISpatialReferenceFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("620600B1-FEA1-11d0-B04B-0080C7F79481")
    ISpatialReferenceFactory : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateFromWKT( 
            /* [in] */ BSTR wktSpatialReference,
            /* [out] */ ISpatialReference **sref) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISpatialReferenceFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISpatialReferenceFactory * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISpatialReferenceFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISpatialReferenceFactory * This);
        
        HRESULT ( STDMETHODCALLTYPE *CreateFromWKT )( 
            ISpatialReferenceFactory * This,
            /* [in] */ BSTR wktSpatialReference,
            /* [out] */ ISpatialReference **sref);
        
        END_INTERFACE
    } ISpatialReferenceFactoryVtbl;

    interface ISpatialReferenceFactory
    {
        CONST_VTBL struct ISpatialReferenceFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISpatialReferenceFactory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISpatialReferenceFactory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISpatialReferenceFactory_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISpatialReferenceFactory_CreateFromWKT(This,wktSpatialReference,sref)	\
    (This)->lpVtbl -> CreateFromWKT(This,wktSpatialReference,sref)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISpatialReferenceFactory_CreateFromWKT_Proxy( 
    ISpatialReferenceFactory * This,
    /* [in] */ BSTR wktSpatialReference,
    /* [out] */ ISpatialReference **sref);


void __RPC_STUB ISpatialReferenceFactory_CreateFromWKT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISpatialReferenceFactory_INTERFACE_DEFINED__ */


#ifndef __ISpatialReferenceAuthorityFactory_INTERFACE_DEFINED__
#define __ISpatialReferenceAuthorityFactory_INTERFACE_DEFINED__

/* interface ISpatialReferenceAuthorityFactory */
/* [uuid][object] */ 


EXTERN_C const IID IID_ISpatialReferenceAuthorityFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("30ae14f0-fe1f-11d0-ad87-080009b6f22b")
    ISpatialReferenceAuthorityFactory : public IUnknown
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Authority( 
            /* [out] */ BSTR *authority) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateProjectedCoordinateSystem( 
            /* [in] */ long code,
            /* [out] */ IProjectedCoordinateSystem **pcs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateGeographicCoordinateSystem( 
            /* [in] */ long code,
            /* [out] */ IGeographicCoordinateSystem **gcs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateProjection( 
            /* [in] */ long code,
            /* [out] */ IProjection **projection) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateGeographicTransform( 
            /* [in] */ long code,
            /* [out] */ IGeographicTransform **gt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateHorizontalDatum( 
            /* [in] */ long code,
            /* [out] */ IHorizontalDatum **datum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateEllipsoid( 
            /* [in] */ long code,
            /* [out] */ IEllipsoid **ellipsoid) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreatePrimeMeridian( 
            /* [in] */ long code,
            /* [out] */ IPrimeMeridian **prmMerid) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateLinearUnit( 
            /* [in] */ long code,
            /* [out] */ ILinearUnit **unit) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateAngularUnit( 
            /* [in] */ long code,
            /* [out] */ IAngularUnit **unit) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISpatialReferenceAuthorityFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISpatialReferenceAuthorityFactory * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISpatialReferenceAuthorityFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISpatialReferenceAuthorityFactory * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Authority )( 
            ISpatialReferenceAuthorityFactory * This,
            /* [out] */ BSTR *authority);
        
        HRESULT ( STDMETHODCALLTYPE *CreateProjectedCoordinateSystem )( 
            ISpatialReferenceAuthorityFactory * This,
            /* [in] */ long code,
            /* [out] */ IProjectedCoordinateSystem **pcs);
        
        HRESULT ( STDMETHODCALLTYPE *CreateGeographicCoordinateSystem )( 
            ISpatialReferenceAuthorityFactory * This,
            /* [in] */ long code,
            /* [out] */ IGeographicCoordinateSystem **gcs);
        
        HRESULT ( STDMETHODCALLTYPE *CreateProjection )( 
            ISpatialReferenceAuthorityFactory * This,
            /* [in] */ long code,
            /* [out] */ IProjection **projection);
        
        HRESULT ( STDMETHODCALLTYPE *CreateGeographicTransform )( 
            ISpatialReferenceAuthorityFactory * This,
            /* [in] */ long code,
            /* [out] */ IGeographicTransform **gt);
        
        HRESULT ( STDMETHODCALLTYPE *CreateHorizontalDatum )( 
            ISpatialReferenceAuthorityFactory * This,
            /* [in] */ long code,
            /* [out] */ IHorizontalDatum **datum);
        
        HRESULT ( STDMETHODCALLTYPE *CreateEllipsoid )( 
            ISpatialReferenceAuthorityFactory * This,
            /* [in] */ long code,
            /* [out] */ IEllipsoid **ellipsoid);
        
        HRESULT ( STDMETHODCALLTYPE *CreatePrimeMeridian )( 
            ISpatialReferenceAuthorityFactory * This,
            /* [in] */ long code,
            /* [out] */ IPrimeMeridian **prmMerid);
        
        HRESULT ( STDMETHODCALLTYPE *CreateLinearUnit )( 
            ISpatialReferenceAuthorityFactory * This,
            /* [in] */ long code,
            /* [out] */ ILinearUnit **unit);
        
        HRESULT ( STDMETHODCALLTYPE *CreateAngularUnit )( 
            ISpatialReferenceAuthorityFactory * This,
            /* [in] */ long code,
            /* [out] */ IAngularUnit **unit);
        
        END_INTERFACE
    } ISpatialReferenceAuthorityFactoryVtbl;

    interface ISpatialReferenceAuthorityFactory
    {
        CONST_VTBL struct ISpatialReferenceAuthorityFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISpatialReferenceAuthorityFactory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISpatialReferenceAuthorityFactory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISpatialReferenceAuthorityFactory_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISpatialReferenceAuthorityFactory_get_Authority(This,authority)	\
    (This)->lpVtbl -> get_Authority(This,authority)

#define ISpatialReferenceAuthorityFactory_CreateProjectedCoordinateSystem(This,code,pcs)	\
    (This)->lpVtbl -> CreateProjectedCoordinateSystem(This,code,pcs)

#define ISpatialReferenceAuthorityFactory_CreateGeographicCoordinateSystem(This,code,gcs)	\
    (This)->lpVtbl -> CreateGeographicCoordinateSystem(This,code,gcs)

#define ISpatialReferenceAuthorityFactory_CreateProjection(This,code,projection)	\
    (This)->lpVtbl -> CreateProjection(This,code,projection)

#define ISpatialReferenceAuthorityFactory_CreateGeographicTransform(This,code,gt)	\
    (This)->lpVtbl -> CreateGeographicTransform(This,code,gt)

#define ISpatialReferenceAuthorityFactory_CreateHorizontalDatum(This,code,datum)	\
    (This)->lpVtbl -> CreateHorizontalDatum(This,code,datum)

#define ISpatialReferenceAuthorityFactory_CreateEllipsoid(This,code,ellipsoid)	\
    (This)->lpVtbl -> CreateEllipsoid(This,code,ellipsoid)

#define ISpatialReferenceAuthorityFactory_CreatePrimeMeridian(This,code,prmMerid)	\
    (This)->lpVtbl -> CreatePrimeMeridian(This,code,prmMerid)

#define ISpatialReferenceAuthorityFactory_CreateLinearUnit(This,code,unit)	\
    (This)->lpVtbl -> CreateLinearUnit(This,code,unit)

#define ISpatialReferenceAuthorityFactory_CreateAngularUnit(This,code,unit)	\
    (This)->lpVtbl -> CreateAngularUnit(This,code,unit)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_get_Authority_Proxy( 
    ISpatialReferenceAuthorityFactory * This,
    /* [out] */ BSTR *authority);


void __RPC_STUB ISpatialReferenceAuthorityFactory_get_Authority_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_CreateProjectedCoordinateSystem_Proxy( 
    ISpatialReferenceAuthorityFactory * This,
    /* [in] */ long code,
    /* [out] */ IProjectedCoordinateSystem **pcs);


void __RPC_STUB ISpatialReferenceAuthorityFactory_CreateProjectedCoordinateSystem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_CreateGeographicCoordinateSystem_Proxy( 
    ISpatialReferenceAuthorityFactory * This,
    /* [in] */ long code,
    /* [out] */ IGeographicCoordinateSystem **gcs);


void __RPC_STUB ISpatialReferenceAuthorityFactory_CreateGeographicCoordinateSystem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_CreateProjection_Proxy( 
    ISpatialReferenceAuthorityFactory * This,
    /* [in] */ long code,
    /* [out] */ IProjection **projection);


void __RPC_STUB ISpatialReferenceAuthorityFactory_CreateProjection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_CreateGeographicTransform_Proxy( 
    ISpatialReferenceAuthorityFactory * This,
    /* [in] */ long code,
    /* [out] */ IGeographicTransform **gt);


void __RPC_STUB ISpatialReferenceAuthorityFactory_CreateGeographicTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_CreateHorizontalDatum_Proxy( 
    ISpatialReferenceAuthorityFactory * This,
    /* [in] */ long code,
    /* [out] */ IHorizontalDatum **datum);


void __RPC_STUB ISpatialReferenceAuthorityFactory_CreateHorizontalDatum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_CreateEllipsoid_Proxy( 
    ISpatialReferenceAuthorityFactory * This,
    /* [in] */ long code,
    /* [out] */ IEllipsoid **ellipsoid);


void __RPC_STUB ISpatialReferenceAuthorityFactory_CreateEllipsoid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_CreatePrimeMeridian_Proxy( 
    ISpatialReferenceAuthorityFactory * This,
    /* [in] */ long code,
    /* [out] */ IPrimeMeridian **prmMerid);


void __RPC_STUB ISpatialReferenceAuthorityFactory_CreatePrimeMeridian_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_CreateLinearUnit_Proxy( 
    ISpatialReferenceAuthorityFactory * This,
    /* [in] */ long code,
    /* [out] */ ILinearUnit **unit);


void __RPC_STUB ISpatialReferenceAuthorityFactory_CreateLinearUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_CreateAngularUnit_Proxy( 
    ISpatialReferenceAuthorityFactory * This,
    /* [in] */ long code,
    /* [out] */ IAngularUnit **unit);


void __RPC_STUB ISpatialReferenceAuthorityFactory_CreateAngularUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISpatialReferenceAuthorityFactory_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


