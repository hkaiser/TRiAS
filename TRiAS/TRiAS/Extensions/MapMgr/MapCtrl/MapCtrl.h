
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Tue Jan 04 13:17:17 2005
 */
/* Compiler settings for MapCtrl.idl:
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

#ifndef __MapCtrl_h__
#define __MapCtrl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITopoPict_FWD_DEFINED__
#define __ITopoPict_FWD_DEFINED__
typedef interface ITopoPict ITopoPict;
#endif 	/* __ITopoPict_FWD_DEFINED__ */


#ifndef __ITopoMap_FWD_DEFINED__
#define __ITopoMap_FWD_DEFINED__
typedef interface ITopoMap ITopoMap;
#endif 	/* __ITopoMap_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __MAPCTRLLib_LIBRARY_DEFINED__
#define __MAPCTRLLib_LIBRARY_DEFINED__

/* library MAPCTRLLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_MAPCTRLLib;

#ifndef __ITopoPict_INTERFACE_DEFINED__
#define __ITopoPict_INTERFACE_DEFINED__

/* interface ITopoPict */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITopoPict;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D24C1821-1B49-11d2-8F7D-0060085FC1CE")
    ITopoPict : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTagValue( 
            /* [in] */ long tag,
            /* [out] */ VARIANT *value) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetGeoCodedPoints( 
            /* [out] */ SAFEARRAY * *pCoordinates,
            /* [out] */ IUnknown **ppICS) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITopoPictVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITopoPict * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITopoPict * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITopoPict * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetTagValue )( 
            ITopoPict * This,
            /* [in] */ long tag,
            /* [out] */ VARIANT *value);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetGeoCodedPoints )( 
            ITopoPict * This,
            /* [out] */ SAFEARRAY * *pCoordinates,
            /* [out] */ IUnknown **ppICS);
        
        END_INTERFACE
    } ITopoPictVtbl;

    interface ITopoPict
    {
        CONST_VTBL struct ITopoPictVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITopoPict_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITopoPict_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITopoPict_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITopoPict_GetTagValue(This,tag,value)	\
    (This)->lpVtbl -> GetTagValue(This,tag,value)

#define ITopoPict_GetGeoCodedPoints(This,pCoordinates,ppICS)	\
    (This)->lpVtbl -> GetGeoCodedPoints(This,pCoordinates,ppICS)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITopoPict_GetTagValue_Proxy( 
    ITopoPict * This,
    /* [in] */ long tag,
    /* [out] */ VARIANT *value);


void __RPC_STUB ITopoPict_GetTagValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITopoPict_GetGeoCodedPoints_Proxy( 
    ITopoPict * This,
    /* [out] */ SAFEARRAY * *pCoordinates,
    /* [out] */ IUnknown **ppICS);


void __RPC_STUB ITopoPict_GetGeoCodedPoints_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITopoPict_INTERFACE_DEFINED__ */


#ifndef __ITopoMap_INTERFACE_DEFINED__
#define __ITopoMap_INTERFACE_DEFINED__

/* interface ITopoMap */
/* [unique][helpstring][dual][uuid][object] */ 

typedef /* [v1_enum][public] */ 
enum _tagCOPYFLAG
    {	COPYFLAG_Default	= 0x6,
	COPYFLAG_SourceAreFiles	= 0,
	COPYFLAG_SourceIsDirectory	= 0x1,
	COPYFLAG_MayCopyFiles	= 0,
	COPYFLAG_ShouldCopyFiles	= 0x2,
	COPYFLAG_MustReduceFiles	= 0x4
    } 	COPYFLAG;


EXTERN_C const IID IID_ITopoMap;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B6AFCF00-1A64-11d2-8F7D-0060085FC1CE")
    ITopoMap : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCoordSystem( 
            /* [out][in] */ IUnknown **ppCoordSystem) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetImageFileFilter( 
            /* [out][in] */ BSTR *pStrFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAltFileFilter( 
            /* [out][in] */ BSTR *pStrFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDisplayName( 
            /* [out][in] */ BSTR *pStrDisplay) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CheckPictureFile( 
            /* [in] */ ITopoPict *__MIDL_0011,
            /* [out][in] */ long *bFileIsvalidForMe) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CheckAltFile( 
            /* [in] */ BSTR strFileName,
            /* [out][in] */ long *bFileIsvalidForMe) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PrepareFinalData( 
            /* [out][in] */ long *bHavePrepared) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCoordinates( 
            /* [out] */ SAFEARRAY * *pCoordinates) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRefPoints( 
            /* [out] */ SAFEARRAY * *pCoordinates) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HaveNomenclatur( 
            /* [out][in] */ long *pYesNo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NeedFixPoints( 
            /* [out][in] */ long *pNeedPoints) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PutFixPoints( 
            /* [in] */ SAFEARRAY * pCoordinates) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNameAndIdent( 
            /* [in] */ BSTR strPathName,
            /* [out] */ BSTR *strName,
            /* [out] */ BSTR *strIdent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDifferenz( 
            /* [out] */ SAFEARRAY * *pCoordinates) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAltFileTyp( 
            /* [out][in] */ BSTR *pStrTyp) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HaveMultiMap( 
            /* [out][in] */ long *pYesNo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BitmapIndex( 
            /* [retval][out] */ long *plIndex) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CorrectName( 
            /* [in] */ BSTR bstrDestDir,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ BSTR *pbstrToWrite) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CorrectDirectory( 
            /* [in] */ BSTR bstrDestDir,
            /* [retval][out] */ BSTR *pbstrToWrite) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CopyFlags( 
            /* [retval][out] */ COPYFLAG *prgFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDescription( 
            /* [retval][out] */ BSTR *pbstrDesc) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDefaultFileTyp( 
            /* [out][in] */ BSTR *pStrTyp) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MakeFullName( 
            /* [in] */ BSTR bstrBaseDir,
            /* [retval][out] */ BSTR *pbstrFullFileName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NeedsCoordSystem( 
            /* [retval][out] */ VARIANT_BOOL *pfNeedsCoordSys) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PutCoordSystem( 
            /* [in] */ IUnknown *pICS) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITopoMapVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITopoMap * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITopoMap * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITopoMap * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetCoordSystem )( 
            ITopoMap * This,
            /* [out][in] */ IUnknown **ppCoordSystem);
        
        HRESULT ( STDMETHODCALLTYPE *GetImageFileFilter )( 
            ITopoMap * This,
            /* [out][in] */ BSTR *pStrFilter);
        
        HRESULT ( STDMETHODCALLTYPE *GetAltFileFilter )( 
            ITopoMap * This,
            /* [out][in] */ BSTR *pStrFilter);
        
        HRESULT ( STDMETHODCALLTYPE *GetDisplayName )( 
            ITopoMap * This,
            /* [out][in] */ BSTR *pStrDisplay);
        
        HRESULT ( STDMETHODCALLTYPE *CheckPictureFile )( 
            ITopoMap * This,
            /* [in] */ ITopoPict *__MIDL_0011,
            /* [out][in] */ long *bFileIsvalidForMe);
        
        HRESULT ( STDMETHODCALLTYPE *CheckAltFile )( 
            ITopoMap * This,
            /* [in] */ BSTR strFileName,
            /* [out][in] */ long *bFileIsvalidForMe);
        
        HRESULT ( STDMETHODCALLTYPE *PrepareFinalData )( 
            ITopoMap * This,
            /* [out][in] */ long *bHavePrepared);
        
        HRESULT ( STDMETHODCALLTYPE *GetCoordinates )( 
            ITopoMap * This,
            /* [out] */ SAFEARRAY * *pCoordinates);
        
        HRESULT ( STDMETHODCALLTYPE *GetRefPoints )( 
            ITopoMap * This,
            /* [out] */ SAFEARRAY * *pCoordinates);
        
        HRESULT ( STDMETHODCALLTYPE *HaveNomenclatur )( 
            ITopoMap * This,
            /* [out][in] */ long *pYesNo);
        
        HRESULT ( STDMETHODCALLTYPE *NeedFixPoints )( 
            ITopoMap * This,
            /* [out][in] */ long *pNeedPoints);
        
        HRESULT ( STDMETHODCALLTYPE *PutFixPoints )( 
            ITopoMap * This,
            /* [in] */ SAFEARRAY * pCoordinates);
        
        HRESULT ( STDMETHODCALLTYPE *GetNameAndIdent )( 
            ITopoMap * This,
            /* [in] */ BSTR strPathName,
            /* [out] */ BSTR *strName,
            /* [out] */ BSTR *strIdent);
        
        HRESULT ( STDMETHODCALLTYPE *GetDifferenz )( 
            ITopoMap * This,
            /* [out] */ SAFEARRAY * *pCoordinates);
        
        HRESULT ( STDMETHODCALLTYPE *GetAltFileTyp )( 
            ITopoMap * This,
            /* [out][in] */ BSTR *pStrTyp);
        
        HRESULT ( STDMETHODCALLTYPE *HaveMultiMap )( 
            ITopoMap * This,
            /* [out][in] */ long *pYesNo);
        
        HRESULT ( STDMETHODCALLTYPE *BitmapIndex )( 
            ITopoMap * This,
            /* [retval][out] */ long *plIndex);
        
        HRESULT ( STDMETHODCALLTYPE *CorrectName )( 
            ITopoMap * This,
            /* [in] */ BSTR bstrDestDir,
            /* [in] */ BSTR bstrName,
            /* [retval][out] */ BSTR *pbstrToWrite);
        
        HRESULT ( STDMETHODCALLTYPE *CorrectDirectory )( 
            ITopoMap * This,
            /* [in] */ BSTR bstrDestDir,
            /* [retval][out] */ BSTR *pbstrToWrite);
        
        HRESULT ( STDMETHODCALLTYPE *CopyFlags )( 
            ITopoMap * This,
            /* [retval][out] */ COPYFLAG *prgFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetDescription )( 
            ITopoMap * This,
            /* [retval][out] */ BSTR *pbstrDesc);
        
        HRESULT ( STDMETHODCALLTYPE *GetDefaultFileTyp )( 
            ITopoMap * This,
            /* [out][in] */ BSTR *pStrTyp);
        
        HRESULT ( STDMETHODCALLTYPE *MakeFullName )( 
            ITopoMap * This,
            /* [in] */ BSTR bstrBaseDir,
            /* [retval][out] */ BSTR *pbstrFullFileName);
        
        HRESULT ( STDMETHODCALLTYPE *NeedsCoordSystem )( 
            ITopoMap * This,
            /* [retval][out] */ VARIANT_BOOL *pfNeedsCoordSys);
        
        HRESULT ( STDMETHODCALLTYPE *PutCoordSystem )( 
            ITopoMap * This,
            /* [in] */ IUnknown *pICS);
        
        END_INTERFACE
    } ITopoMapVtbl;

    interface ITopoMap
    {
        CONST_VTBL struct ITopoMapVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITopoMap_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITopoMap_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITopoMap_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITopoMap_GetCoordSystem(This,ppCoordSystem)	\
    (This)->lpVtbl -> GetCoordSystem(This,ppCoordSystem)

#define ITopoMap_GetImageFileFilter(This,pStrFilter)	\
    (This)->lpVtbl -> GetImageFileFilter(This,pStrFilter)

#define ITopoMap_GetAltFileFilter(This,pStrFilter)	\
    (This)->lpVtbl -> GetAltFileFilter(This,pStrFilter)

#define ITopoMap_GetDisplayName(This,pStrDisplay)	\
    (This)->lpVtbl -> GetDisplayName(This,pStrDisplay)

#define ITopoMap_CheckPictureFile(This,__MIDL_0011,bFileIsvalidForMe)	\
    (This)->lpVtbl -> CheckPictureFile(This,__MIDL_0011,bFileIsvalidForMe)

#define ITopoMap_CheckAltFile(This,strFileName,bFileIsvalidForMe)	\
    (This)->lpVtbl -> CheckAltFile(This,strFileName,bFileIsvalidForMe)

#define ITopoMap_PrepareFinalData(This,bHavePrepared)	\
    (This)->lpVtbl -> PrepareFinalData(This,bHavePrepared)

#define ITopoMap_GetCoordinates(This,pCoordinates)	\
    (This)->lpVtbl -> GetCoordinates(This,pCoordinates)

#define ITopoMap_GetRefPoints(This,pCoordinates)	\
    (This)->lpVtbl -> GetRefPoints(This,pCoordinates)

#define ITopoMap_HaveNomenclatur(This,pYesNo)	\
    (This)->lpVtbl -> HaveNomenclatur(This,pYesNo)

#define ITopoMap_NeedFixPoints(This,pNeedPoints)	\
    (This)->lpVtbl -> NeedFixPoints(This,pNeedPoints)

#define ITopoMap_PutFixPoints(This,pCoordinates)	\
    (This)->lpVtbl -> PutFixPoints(This,pCoordinates)

#define ITopoMap_GetNameAndIdent(This,strPathName,strName,strIdent)	\
    (This)->lpVtbl -> GetNameAndIdent(This,strPathName,strName,strIdent)

#define ITopoMap_GetDifferenz(This,pCoordinates)	\
    (This)->lpVtbl -> GetDifferenz(This,pCoordinates)

#define ITopoMap_GetAltFileTyp(This,pStrTyp)	\
    (This)->lpVtbl -> GetAltFileTyp(This,pStrTyp)

#define ITopoMap_HaveMultiMap(This,pYesNo)	\
    (This)->lpVtbl -> HaveMultiMap(This,pYesNo)

#define ITopoMap_BitmapIndex(This,plIndex)	\
    (This)->lpVtbl -> BitmapIndex(This,plIndex)

#define ITopoMap_CorrectName(This,bstrDestDir,bstrName,pbstrToWrite)	\
    (This)->lpVtbl -> CorrectName(This,bstrDestDir,bstrName,pbstrToWrite)

#define ITopoMap_CorrectDirectory(This,bstrDestDir,pbstrToWrite)	\
    (This)->lpVtbl -> CorrectDirectory(This,bstrDestDir,pbstrToWrite)

#define ITopoMap_CopyFlags(This,prgFlags)	\
    (This)->lpVtbl -> CopyFlags(This,prgFlags)

#define ITopoMap_GetDescription(This,pbstrDesc)	\
    (This)->lpVtbl -> GetDescription(This,pbstrDesc)

#define ITopoMap_GetDefaultFileTyp(This,pStrTyp)	\
    (This)->lpVtbl -> GetDefaultFileTyp(This,pStrTyp)

#define ITopoMap_MakeFullName(This,bstrBaseDir,pbstrFullFileName)	\
    (This)->lpVtbl -> MakeFullName(This,bstrBaseDir,pbstrFullFileName)

#define ITopoMap_NeedsCoordSystem(This,pfNeedsCoordSys)	\
    (This)->lpVtbl -> NeedsCoordSystem(This,pfNeedsCoordSys)

#define ITopoMap_PutCoordSystem(This,pICS)	\
    (This)->lpVtbl -> PutCoordSystem(This,pICS)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ITopoMap_GetCoordSystem_Proxy( 
    ITopoMap * This,
    /* [out][in] */ IUnknown **ppCoordSystem);


void __RPC_STUB ITopoMap_GetCoordSystem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITopoMap_GetImageFileFilter_Proxy( 
    ITopoMap * This,
    /* [out][in] */ BSTR *pStrFilter);


void __RPC_STUB ITopoMap_GetImageFileFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITopoMap_GetAltFileFilter_Proxy( 
    ITopoMap * This,
    /* [out][in] */ BSTR *pStrFilter);


void __RPC_STUB ITopoMap_GetAltFileFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITopoMap_GetDisplayName_Proxy( 
    ITopoMap * This,
    /* [out][in] */ BSTR *pStrDisplay);


void __RPC_STUB ITopoMap_GetDisplayName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITopoMap_CheckPictureFile_Proxy( 
    ITopoMap * This,
    /* [in] */ ITopoPict *__MIDL_0011,
    /* [out][in] */ long *bFileIsvalidForMe);


void __RPC_STUB ITopoMap_CheckPictureFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITopoMap_CheckAltFile_Proxy( 
    ITopoMap * This,
    /* [in] */ BSTR strFileName,
    /* [out][in] */ long *bFileIsvalidForMe);


void __RPC_STUB ITopoMap_CheckAltFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITopoMap_PrepareFinalData_Proxy( 
    ITopoMap * This,
    /* [out][in] */ long *bHavePrepared);


void __RPC_STUB ITopoMap_PrepareFinalData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITopoMap_GetCoordinates_Proxy( 
    ITopoMap * This,
    /* [out] */ SAFEARRAY * *pCoordinates);


void __RPC_STUB ITopoMap_GetCoordinates_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITopoMap_GetRefPoints_Proxy( 
    ITopoMap * This,
    /* [out] */ SAFEARRAY * *pCoordinates);


void __RPC_STUB ITopoMap_GetRefPoints_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITopoMap_HaveNomenclatur_Proxy( 
    ITopoMap * This,
    /* [out][in] */ long *pYesNo);


void __RPC_STUB ITopoMap_HaveNomenclatur_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITopoMap_NeedFixPoints_Proxy( 
    ITopoMap * This,
    /* [out][in] */ long *pNeedPoints);


void __RPC_STUB ITopoMap_NeedFixPoints_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITopoMap_PutFixPoints_Proxy( 
    ITopoMap * This,
    /* [in] */ SAFEARRAY * pCoordinates);


void __RPC_STUB ITopoMap_PutFixPoints_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITopoMap_GetNameAndIdent_Proxy( 
    ITopoMap * This,
    /* [in] */ BSTR strPathName,
    /* [out] */ BSTR *strName,
    /* [out] */ BSTR *strIdent);


void __RPC_STUB ITopoMap_GetNameAndIdent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITopoMap_GetDifferenz_Proxy( 
    ITopoMap * This,
    /* [out] */ SAFEARRAY * *pCoordinates);


void __RPC_STUB ITopoMap_GetDifferenz_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITopoMap_GetAltFileTyp_Proxy( 
    ITopoMap * This,
    /* [out][in] */ BSTR *pStrTyp);


void __RPC_STUB ITopoMap_GetAltFileTyp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITopoMap_HaveMultiMap_Proxy( 
    ITopoMap * This,
    /* [out][in] */ long *pYesNo);


void __RPC_STUB ITopoMap_HaveMultiMap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITopoMap_BitmapIndex_Proxy( 
    ITopoMap * This,
    /* [retval][out] */ long *plIndex);


void __RPC_STUB ITopoMap_BitmapIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITopoMap_CorrectName_Proxy( 
    ITopoMap * This,
    /* [in] */ BSTR bstrDestDir,
    /* [in] */ BSTR bstrName,
    /* [retval][out] */ BSTR *pbstrToWrite);


void __RPC_STUB ITopoMap_CorrectName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITopoMap_CorrectDirectory_Proxy( 
    ITopoMap * This,
    /* [in] */ BSTR bstrDestDir,
    /* [retval][out] */ BSTR *pbstrToWrite);


void __RPC_STUB ITopoMap_CorrectDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITopoMap_CopyFlags_Proxy( 
    ITopoMap * This,
    /* [retval][out] */ COPYFLAG *prgFlags);


void __RPC_STUB ITopoMap_CopyFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITopoMap_GetDescription_Proxy( 
    ITopoMap * This,
    /* [retval][out] */ BSTR *pbstrDesc);


void __RPC_STUB ITopoMap_GetDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITopoMap_GetDefaultFileTyp_Proxy( 
    ITopoMap * This,
    /* [out][in] */ BSTR *pStrTyp);


void __RPC_STUB ITopoMap_GetDefaultFileTyp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITopoMap_MakeFullName_Proxy( 
    ITopoMap * This,
    /* [in] */ BSTR bstrBaseDir,
    /* [retval][out] */ BSTR *pbstrFullFileName);


void __RPC_STUB ITopoMap_MakeFullName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITopoMap_NeedsCoordSystem_Proxy( 
    ITopoMap * This,
    /* [retval][out] */ VARIANT_BOOL *pfNeedsCoordSys);


void __RPC_STUB ITopoMap_NeedsCoordSystem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITopoMap_PutCoordSystem_Proxy( 
    ITopoMap * This,
    /* [in] */ IUnknown *pICS);


void __RPC_STUB ITopoMap_PutCoordSystem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITopoMap_INTERFACE_DEFINED__ */

#endif /* __MAPCTRLLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


