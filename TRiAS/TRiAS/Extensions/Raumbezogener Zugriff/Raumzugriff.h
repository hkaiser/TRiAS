/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.00.15 */
/* at Wed Jul 23 09:15:05 1997
 */
/* Compiler settings for Raumzugriff.idl:
    Os, W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"
#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __Raumzugriff_h__
#define __Raumzugriff_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISpatialTreeQuery_FWD_DEFINED__
#define __ISpatialTreeQuery_FWD_DEFINED__
typedef interface ISpatialTreeQuery ISpatialTreeQuery;
#endif 	/* __ISpatialTreeQuery_FWD_DEFINED__ */


#ifndef __ISpatialTreeCallback_FWD_DEFINED__
#define __ISpatialTreeCallback_FWD_DEFINED__
typedef interface ISpatialTreeCallback ISpatialTreeCallback;
#endif 	/* __ISpatialTreeCallback_FWD_DEFINED__ */


#ifndef __ISpatialTreeInit_FWD_DEFINED__
#define __ISpatialTreeInit_FWD_DEFINED__
typedef interface ISpatialTreeInit ISpatialTreeInit;
#endif 	/* __ISpatialTreeInit_FWD_DEFINED__ */


#ifndef __ITestObjekt_FWD_DEFINED__
#define __ITestObjekt_FWD_DEFINED__
typedef interface ITestObjekt ITestObjekt;
#endif 	/* __ITestObjekt_FWD_DEFINED__ */


#ifndef __ISpatialTree_FWD_DEFINED__
#define __ISpatialTree_FWD_DEFINED__
typedef interface ISpatialTree ISpatialTree;
#endif 	/* __ISpatialTree_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL__intf_0000
 * at Wed Jul 23 09:15:05 1997
 * using MIDL 3.00.15
 ****************************************/
/* [local] */ 


//+-------------------------------------------------------------------------
//
//  TRiAS Extension
//  Schneller raumbezogener Zugriff
//
//  Interfacebeschreibung
//
//--------------------------------------------------------------------------




//+-------------------------------------------------------------------------
//
//  ISpatialTreeQuery
//
//  Interface zur Parametrisierung des raumbezogenen Zugriffes
//
//--------------------------------------------------------------------------




extern RPC_IF_HANDLE __MIDL__intf_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL__intf_0000_v0_0_s_ifspec;

#ifndef __ISpatialTreeQuery_INTERFACE_DEFINED__
#define __ISpatialTreeQuery_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ISpatialTreeQuery
 * at Wed Jul 23 09:15:05 1997
 * using MIDL 3.00.15
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ISpatialTreeQuery;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ISpatialTreeQuery : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetBorder( 
            /* [in] */ ULONG dim,
            /* [in] */ VARIANT amin,
            /* [in] */ VARIANT amax) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBorder( 
            /* [in] */ ULONG dim,
            /* [out] */ VARIANT __RPC_FAR *pmin,
            /* [out] */ VARIANT __RPC_FAR *pmax) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddDim( 
            /* [in] */ VARIANT amin,
            /* [in] */ VARIANT amax,
            /* [in] */ VARTYPE vt) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISpatialTreeQueryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISpatialTreeQuery __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISpatialTreeQuery __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISpatialTreeQuery __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISpatialTreeQuery __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISpatialTreeQuery __RPC_FAR * This,
            /* [in] */ UINT itinfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *pptinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISpatialTreeQuery __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out][in] */ DISPID __RPC_FAR *rgdispid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISpatialTreeQuery __RPC_FAR * This,
            /* [in] */ DISPID dispidMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [unique][in] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [unique][out][in] */ VARIANT __RPC_FAR *pvarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pexcepinfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetBorder )( 
            ISpatialTreeQuery __RPC_FAR * This,
            /* [in] */ ULONG dim,
            /* [in] */ VARIANT amin,
            /* [in] */ VARIANT amax);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBorder )( 
            ISpatialTreeQuery __RPC_FAR * This,
            /* [in] */ ULONG dim,
            /* [out] */ VARIANT __RPC_FAR *pmin,
            /* [out] */ VARIANT __RPC_FAR *pmax);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddDim )( 
            ISpatialTreeQuery __RPC_FAR * This,
            /* [in] */ VARIANT amin,
            /* [in] */ VARIANT amax,
            /* [in] */ VARTYPE vt);
        
        END_INTERFACE
    } ISpatialTreeQueryVtbl;

    interface ISpatialTreeQuery
    {
        CONST_VTBL struct ISpatialTreeQueryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISpatialTreeQuery_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISpatialTreeQuery_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISpatialTreeQuery_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISpatialTreeQuery_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISpatialTreeQuery_GetTypeInfo(This,itinfo,lcid,pptinfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo)

#define ISpatialTreeQuery_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid)

#define ISpatialTreeQuery_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr)


#define ISpatialTreeQuery_SetBorder(This,dim,amin,amax)	\
    (This)->lpVtbl -> SetBorder(This,dim,amin,amax)

#define ISpatialTreeQuery_GetBorder(This,dim,pmin,pmax)	\
    (This)->lpVtbl -> GetBorder(This,dim,pmin,pmax)

#define ISpatialTreeQuery_AddDim(This,amin,amax,vt)	\
    (This)->lpVtbl -> AddDim(This,amin,amax,vt)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISpatialTreeQuery_SetBorder_Proxy( 
    ISpatialTreeQuery __RPC_FAR * This,
    /* [in] */ ULONG dim,
    /* [in] */ VARIANT amin,
    /* [in] */ VARIANT amax);


void __RPC_STUB ISpatialTreeQuery_SetBorder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISpatialTreeQuery_GetBorder_Proxy( 
    ISpatialTreeQuery __RPC_FAR * This,
    /* [in] */ ULONG dim,
    /* [out] */ VARIANT __RPC_FAR *pmin,
    /* [out] */ VARIANT __RPC_FAR *pmax);


void __RPC_STUB ISpatialTreeQuery_GetBorder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISpatialTreeQuery_AddDim_Proxy( 
    ISpatialTreeQuery __RPC_FAR * This,
    /* [in] */ VARIANT amin,
    /* [in] */ VARIANT amax,
    /* [in] */ VARTYPE vt);


void __RPC_STUB ISpatialTreeQuery_AddDim_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISpatialTreeQuery_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL__intf_0069
 * at Wed Jul 23 09:15:05 1997
 * using MIDL 3.00.15
 ****************************************/
/* [local] */ 




//+-------------------------------------------------------------------------
//
//  ISpatialTreeCallback
//
//  Interface zur Feinselektion bei der Durchführung des raumbezogenen Zugriffes
//
//--------------------------------------------------------------------------




extern RPC_IF_HANDLE __MIDL__intf_0069_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL__intf_0069_v0_0_s_ifspec;

#ifndef __ISpatialTreeCallback_INTERFACE_DEFINED__
#define __ISpatialTreeCallback_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ISpatialTreeCallback
 * at Wed Jul 23 09:15:05 1997
 * using MIDL 3.00.15
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ISpatialTreeCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ISpatialTreeCallback : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Accept( 
            /* [in] */ IDispatch __RPC_FAR *pICallback) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISpatialTreeCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISpatialTreeCallback __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISpatialTreeCallback __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISpatialTreeCallback __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISpatialTreeCallback __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISpatialTreeCallback __RPC_FAR * This,
            /* [in] */ UINT itinfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *pptinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISpatialTreeCallback __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out][in] */ DISPID __RPC_FAR *rgdispid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISpatialTreeCallback __RPC_FAR * This,
            /* [in] */ DISPID dispidMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [unique][in] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [unique][out][in] */ VARIANT __RPC_FAR *pvarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pexcepinfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Accept )( 
            ISpatialTreeCallback __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pICallback);
        
        END_INTERFACE
    } ISpatialTreeCallbackVtbl;

    interface ISpatialTreeCallback
    {
        CONST_VTBL struct ISpatialTreeCallbackVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISpatialTreeCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISpatialTreeCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISpatialTreeCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISpatialTreeCallback_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISpatialTreeCallback_GetTypeInfo(This,itinfo,lcid,pptinfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo)

#define ISpatialTreeCallback_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid)

#define ISpatialTreeCallback_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr)


#define ISpatialTreeCallback_Accept(This,pICallback)	\
    (This)->lpVtbl -> Accept(This,pICallback)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISpatialTreeCallback_Accept_Proxy( 
    ISpatialTreeCallback __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *pICallback);


void __RPC_STUB ISpatialTreeCallback_Accept_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISpatialTreeCallback_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL__intf_0070
 * at Wed Jul 23 09:15:05 1997
 * using MIDL 3.00.15
 ****************************************/
/* [local] */ 




//+-------------------------------------------------------------------------
//
//  ISpatialTreeInit
//
//  Interface zur Initialisierung des raumbezogenen Zugriffes
//
//--------------------------------------------------------------------------




extern RPC_IF_HANDLE __MIDL__intf_0070_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL__intf_0070_v0_0_s_ifspec;

#ifndef __ISpatialTreeInit_INTERFACE_DEFINED__
#define __ISpatialTreeInit_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ISpatialTreeInit
 * at Wed Jul 23 09:15:05 1997
 * using MIDL 3.00.15
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ISpatialTreeInit;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ISpatialTreeInit : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AddDimension( 
            /* [in] */ DISPID amin,
            /* [in] */ DISPID amax,
            /* [in] */ VARTYPE comptype,
            /* [out] */ int __RPC_FAR *pIndex) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SiteInterface( 
            /* [in] */ IUnknown __RPC_FAR *pSiteInterface) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISpatialTreeInitVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISpatialTreeInit __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISpatialTreeInit __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISpatialTreeInit __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISpatialTreeInit __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISpatialTreeInit __RPC_FAR * This,
            /* [in] */ UINT itinfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *pptinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISpatialTreeInit __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out][in] */ DISPID __RPC_FAR *rgdispid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISpatialTreeInit __RPC_FAR * This,
            /* [in] */ DISPID dispidMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [unique][in] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [unique][out][in] */ VARIANT __RPC_FAR *pvarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pexcepinfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AddDimension )( 
            ISpatialTreeInit __RPC_FAR * This,
            /* [in] */ DISPID amin,
            /* [in] */ DISPID amax,
            /* [in] */ VARTYPE comptype,
            /* [out] */ int __RPC_FAR *pIndex);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SiteInterface )( 
            ISpatialTreeInit __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pSiteInterface);
        
        END_INTERFACE
    } ISpatialTreeInitVtbl;

    interface ISpatialTreeInit
    {
        CONST_VTBL struct ISpatialTreeInitVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISpatialTreeInit_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISpatialTreeInit_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISpatialTreeInit_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISpatialTreeInit_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISpatialTreeInit_GetTypeInfo(This,itinfo,lcid,pptinfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo)

#define ISpatialTreeInit_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid)

#define ISpatialTreeInit_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr)


#define ISpatialTreeInit_put_AddDimension(This,amin,amax,comptype,pIndex)	\
    (This)->lpVtbl -> put_AddDimension(This,amin,amax,comptype,pIndex)

#define ISpatialTreeInit_put_SiteInterface(This,pSiteInterface)	\
    (This)->lpVtbl -> put_SiteInterface(This,pSiteInterface)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISpatialTreeInit_put_AddDimension_Proxy( 
    ISpatialTreeInit __RPC_FAR * This,
    /* [in] */ DISPID amin,
    /* [in] */ DISPID amax,
    /* [in] */ VARTYPE comptype,
    /* [out] */ int __RPC_FAR *pIndex);


void __RPC_STUB ISpatialTreeInit_put_AddDimension_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISpatialTreeInit_put_SiteInterface_Proxy( 
    ISpatialTreeInit __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pSiteInterface);


void __RPC_STUB ISpatialTreeInit_put_SiteInterface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISpatialTreeInit_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL__intf_0071
 * at Wed Jul 23 09:15:05 1997
 * using MIDL 3.00.15
 ****************************************/
/* [local] */ 




//+-------------------------------------------------------------------------
//
//  ITestObjekt
//
//  Interface für TestObjekte
//
//--------------------------------------------------------------------------




extern RPC_IF_HANDLE __MIDL__intf_0071_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL__intf_0071_v0_0_s_ifspec;

#ifndef __ITestObjekt_INTERFACE_DEFINED__
#define __ITestObjekt_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITestObjekt
 * at Wed Jul 23 09:15:05 1997
 * using MIDL 3.00.15
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ITestObjekt;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ITestObjekt : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE put_xmin( 
            /* [in] */ VARIANT amin) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE put_xmax( 
            /* [in] */ VARIANT amax) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE get_xmin( 
            /* [out] */ VARIANT __RPC_FAR *pmin) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE get_xmax( 
            /* [out] */ VARIANT __RPC_FAR *pmax) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITestObjektVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITestObjekt __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITestObjekt __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITestObjekt __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITestObjekt __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITestObjekt __RPC_FAR * This,
            /* [in] */ UINT itinfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *pptinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITestObjekt __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out][in] */ DISPID __RPC_FAR *rgdispid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITestObjekt __RPC_FAR * This,
            /* [in] */ DISPID dispidMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [unique][in] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [unique][out][in] */ VARIANT __RPC_FAR *pvarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pexcepinfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_xmin )( 
            ITestObjekt __RPC_FAR * This,
            /* [in] */ VARIANT amin);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_xmax )( 
            ITestObjekt __RPC_FAR * This,
            /* [in] */ VARIANT amax);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_xmin )( 
            ITestObjekt __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pmin);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_xmax )( 
            ITestObjekt __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pmax);
        
        END_INTERFACE
    } ITestObjektVtbl;

    interface ITestObjekt
    {
        CONST_VTBL struct ITestObjektVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITestObjekt_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITestObjekt_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITestObjekt_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITestObjekt_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITestObjekt_GetTypeInfo(This,itinfo,lcid,pptinfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo)

#define ITestObjekt_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid)

#define ITestObjekt_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr)


#define ITestObjekt_put_xmin(This,amin)	\
    (This)->lpVtbl -> put_xmin(This,amin)

#define ITestObjekt_put_xmax(This,amax)	\
    (This)->lpVtbl -> put_xmax(This,amax)

#define ITestObjekt_get_xmin(This,pmin)	\
    (This)->lpVtbl -> get_xmin(This,pmin)

#define ITestObjekt_get_xmax(This,pmax)	\
    (This)->lpVtbl -> get_xmax(This,pmax)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITestObjekt_put_xmin_Proxy( 
    ITestObjekt __RPC_FAR * This,
    /* [in] */ VARIANT amin);


void __RPC_STUB ITestObjekt_put_xmin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITestObjekt_put_xmax_Proxy( 
    ITestObjekt __RPC_FAR * This,
    /* [in] */ VARIANT amax);


void __RPC_STUB ITestObjekt_put_xmax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITestObjekt_get_xmin_Proxy( 
    ITestObjekt __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pmin);


void __RPC_STUB ITestObjekt_get_xmin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITestObjekt_get_xmax_Proxy( 
    ITestObjekt __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pmax);


void __RPC_STUB ITestObjekt_get_xmax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITestObjekt_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL__intf_0072
 * at Wed Jul 23 09:15:05 1997
 * using MIDL 3.00.15
 ****************************************/
/* [local] */ 




//+-------------------------------------------------------------------------
//
//  ISpatialTree
//
//  Interface zur Durchführung des raumbezogenen Zugriffes
//
//--------------------------------------------------------------------------




extern RPC_IF_HANDLE __MIDL__intf_0072_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL__intf_0072_v0_0_s_ifspec;

#ifndef __ISpatialTree_INTERFACE_DEFINED__
#define __ISpatialTree_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ISpatialTree
 * at Wed Jul 23 09:15:05 1997
 * using MIDL 3.00.15
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ISpatialTree;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ISpatialTree : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ IDispatch __RPC_FAR *pnewObj,
            /* [in] */ ULONG ObjNr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeletebyNr( 
            /* [in] */ ULONG ObjNr) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ ULONG __RPC_FAR *pCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Container( 
            /* [retval][out] */ ISpatialTreeQuery __RPC_FAR *__RPC_FAR *ppIQuestion) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Dimension( 
            /* [retval][out] */ ULONG __RPC_FAR *pDim) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DimensionIDs( 
            /* [in] */ ULONG Dim,
            /* [out] */ DISPID __RPC_FAR *pmin,
            /* [out] */ DISPID __RPC_FAR *pmax,
            /* [out] */ VARTYPE __RPC_FAR *comptype) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Optimize( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Intersection( 
            /* [in] */ ISpatialTreeQuery __RPC_FAR *pIQuestion,
            /* [in] */ ISpatialTreeCallback __RPC_FAR *pICallback,
            /* [out] */ IEnumUnknown __RPC_FAR *__RPC_FAR *ppReturn) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Containment( 
            /* [in] */ ISpatialTreeQuery __RPC_FAR *pIQuestion,
            /* [in] */ ISpatialTreeCallback __RPC_FAR *pICallback,
            /* [out] */ IEnumUnknown __RPC_FAR *__RPC_FAR *ppReturn) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISpatialTreeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISpatialTree __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISpatialTree __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISpatialTree __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISpatialTree __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISpatialTree __RPC_FAR * This,
            /* [in] */ UINT itinfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *pptinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISpatialTree __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out][in] */ DISPID __RPC_FAR *rgdispid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISpatialTree __RPC_FAR * This,
            /* [in] */ DISPID dispidMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [unique][in] */ DISPPARAMS __RPC_FAR *pdispparams,
            /* [unique][out][in] */ VARIANT __RPC_FAR *pvarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pexcepinfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Insert )( 
            ISpatialTree __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pnewObj,
            /* [in] */ ULONG ObjNr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeletebyNr )( 
            ISpatialTree __RPC_FAR * This,
            /* [in] */ ULONG ObjNr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ISpatialTree __RPC_FAR * This,
            /* [retval][out] */ ULONG __RPC_FAR *pCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Container )( 
            ISpatialTree __RPC_FAR * This,
            /* [retval][out] */ ISpatialTreeQuery __RPC_FAR *__RPC_FAR *ppIQuestion);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Dimension )( 
            ISpatialTree __RPC_FAR * This,
            /* [retval][out] */ ULONG __RPC_FAR *pDim);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DimensionIDs )( 
            ISpatialTree __RPC_FAR * This,
            /* [in] */ ULONG Dim,
            /* [out] */ DISPID __RPC_FAR *pmin,
            /* [out] */ DISPID __RPC_FAR *pmax,
            /* [out] */ VARTYPE __RPC_FAR *comptype);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Optimize )( 
            ISpatialTree __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Intersection )( 
            ISpatialTree __RPC_FAR * This,
            /* [in] */ ISpatialTreeQuery __RPC_FAR *pIQuestion,
            /* [in] */ ISpatialTreeCallback __RPC_FAR *pICallback,
            /* [out] */ IEnumUnknown __RPC_FAR *__RPC_FAR *ppReturn);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Containment )( 
            ISpatialTree __RPC_FAR * This,
            /* [in] */ ISpatialTreeQuery __RPC_FAR *pIQuestion,
            /* [in] */ ISpatialTreeCallback __RPC_FAR *pICallback,
            /* [out] */ IEnumUnknown __RPC_FAR *__RPC_FAR *ppReturn);
        
        END_INTERFACE
    } ISpatialTreeVtbl;

    interface ISpatialTree
    {
        CONST_VTBL struct ISpatialTreeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISpatialTree_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISpatialTree_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISpatialTree_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISpatialTree_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISpatialTree_GetTypeInfo(This,itinfo,lcid,pptinfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo)

#define ISpatialTree_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid)

#define ISpatialTree_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr)


#define ISpatialTree_Insert(This,pnewObj,ObjNr)	\
    (This)->lpVtbl -> Insert(This,pnewObj,ObjNr)

#define ISpatialTree_DeletebyNr(This,ObjNr)	\
    (This)->lpVtbl -> DeletebyNr(This,ObjNr)

#define ISpatialTree_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define ISpatialTree_get_Container(This,ppIQuestion)	\
    (This)->lpVtbl -> get_Container(This,ppIQuestion)

#define ISpatialTree_get_Dimension(This,pDim)	\
    (This)->lpVtbl -> get_Dimension(This,pDim)

#define ISpatialTree_get_DimensionIDs(This,Dim,pmin,pmax,comptype)	\
    (This)->lpVtbl -> get_DimensionIDs(This,Dim,pmin,pmax,comptype)

#define ISpatialTree_Optimize(This)	\
    (This)->lpVtbl -> Optimize(This)

#define ISpatialTree_Intersection(This,pIQuestion,pICallback,ppReturn)	\
    (This)->lpVtbl -> Intersection(This,pIQuestion,pICallback,ppReturn)

#define ISpatialTree_Containment(This,pIQuestion,pICallback,ppReturn)	\
    (This)->lpVtbl -> Containment(This,pIQuestion,pICallback,ppReturn)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISpatialTree_Insert_Proxy( 
    ISpatialTree __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *pnewObj,
    /* [in] */ ULONG ObjNr);


void __RPC_STUB ISpatialTree_Insert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISpatialTree_DeletebyNr_Proxy( 
    ISpatialTree __RPC_FAR * This,
    /* [in] */ ULONG ObjNr);


void __RPC_STUB ISpatialTree_DeletebyNr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISpatialTree_get_Count_Proxy( 
    ISpatialTree __RPC_FAR * This,
    /* [retval][out] */ ULONG __RPC_FAR *pCount);


void __RPC_STUB ISpatialTree_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISpatialTree_get_Container_Proxy( 
    ISpatialTree __RPC_FAR * This,
    /* [retval][out] */ ISpatialTreeQuery __RPC_FAR *__RPC_FAR *ppIQuestion);


void __RPC_STUB ISpatialTree_get_Container_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISpatialTree_get_Dimension_Proxy( 
    ISpatialTree __RPC_FAR * This,
    /* [retval][out] */ ULONG __RPC_FAR *pDim);


void __RPC_STUB ISpatialTree_get_Dimension_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISpatialTree_get_DimensionIDs_Proxy( 
    ISpatialTree __RPC_FAR * This,
    /* [in] */ ULONG Dim,
    /* [out] */ DISPID __RPC_FAR *pmin,
    /* [out] */ DISPID __RPC_FAR *pmax,
    /* [out] */ VARTYPE __RPC_FAR *comptype);


void __RPC_STUB ISpatialTree_get_DimensionIDs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISpatialTree_Optimize_Proxy( 
    ISpatialTree __RPC_FAR * This);


void __RPC_STUB ISpatialTree_Optimize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISpatialTree_Intersection_Proxy( 
    ISpatialTree __RPC_FAR * This,
    /* [in] */ ISpatialTreeQuery __RPC_FAR *pIQuestion,
    /* [in] */ ISpatialTreeCallback __RPC_FAR *pICallback,
    /* [out] */ IEnumUnknown __RPC_FAR *__RPC_FAR *ppReturn);


void __RPC_STUB ISpatialTree_Intersection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISpatialTree_Containment_Proxy( 
    ISpatialTree __RPC_FAR * This,
    /* [in] */ ISpatialTreeQuery __RPC_FAR *pIQuestion,
    /* [in] */ ISpatialTreeCallback __RPC_FAR *pICallback,
    /* [out] */ IEnumUnknown __RPC_FAR *__RPC_FAR *ppReturn);


void __RPC_STUB ISpatialTree_Containment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISpatialTree_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL__intf_0073
 * at Wed Jul 23 09:15:05 1997
 * using MIDL 3.00.15
 ****************************************/
/* [local] */ 




//+-------------------------------------------------------------------------
//
//  Raumzugriff
//
//  Definition der Bibliothek
//
//--------------------------------------------------------------------------




extern RPC_IF_HANDLE __MIDL__intf_0073_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL__intf_0073_v0_0_s_ifspec;


#ifndef __RAUMZUGRIFFLib_LIBRARY_DEFINED__
#define __RAUMZUGRIFFLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: RAUMZUGRIFFLib
 * at Wed Jul 23 09:15:05 1997
 * using MIDL 3.00.15
 ****************************************/
/* [helpstring][version][uuid] */ 




//+-------------------------------------------------------------------------
//
//  CSpatialTreeQuery
//
//  Abfrageobjekt für den raumbezogenen Zugriff
//
//--------------------------------------------------------------------------




//+-------------------------------------------------------------------------
//
//  CSpatialTree
//
//  Objekt für den raumbezogenen Zugriff
//
//--------------------------------------------------------------------------




//+-------------------------------------------------------------------------
//
//  CTestObjekt
//
//  Objekt für den raumbezogenen Zugriff
//
//--------------------------------------------------------------------------



EXTERN_C const IID LIBID_RAUMZUGRIFFLib;

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_CSpatialTreeQuery;

class CSpatialTreeQuery;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_CSpatialTree;

class CSpatialTree;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_CTestObjekt;

class CTestObjekt;
#endif
#endif /* __RAUMZUGRIFFLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
