
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Tue Nov 16 14:41:05 2004
 */
/* Compiler settings for D:\TRiASDEV.MVC\xtension\Statist\StatistApp.idl:
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

#ifndef __StatistApp_h__
#define __StatistApp_h__

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


#ifndef __IConfigObjectProperty_FWD_DEFINED__
#define __IConfigObjectProperty_FWD_DEFINED__
typedef interface IConfigObjectProperty IConfigObjectProperty;
#endif 	/* __IConfigObjectProperty_FWD_DEFINED__ */


#ifndef __IConfigSequenceForObjectProperty_FWD_DEFINED__
#define __IConfigSequenceForObjectProperty_FWD_DEFINED__
typedef interface IConfigSequenceForObjectProperty IConfigSequenceForObjectProperty;
#endif 	/* __IConfigSequenceForObjectProperty_FWD_DEFINED__ */


#ifndef __IValueProvider_FWD_DEFINED__
#define __IValueProvider_FWD_DEFINED__
typedef interface IValueProvider IValueProvider;
#endif 	/* __IValueProvider_FWD_DEFINED__ */


#ifndef __IValueProviderCallback_FWD_DEFINED__
#define __IValueProviderCallback_FWD_DEFINED__
typedef interface IValueProviderCallback IValueProviderCallback;
#endif 	/* __IValueProviderCallback_FWD_DEFINED__ */


#ifndef __IGenericStatistics_FWD_DEFINED__
#define __IGenericStatistics_FWD_DEFINED__
typedef interface IGenericStatistics IGenericStatistics;
#endif 	/* __IGenericStatistics_FWD_DEFINED__ */


#ifndef __ITRiASSimpleStatistics_FWD_DEFINED__
#define __ITRiASSimpleStatistics_FWD_DEFINED__
typedef interface ITRiASSimpleStatistics ITRiASSimpleStatistics;
#endif 	/* __ITRiASSimpleStatistics_FWD_DEFINED__ */


#ifndef __ITRiASUnitsOfMeasure_FWD_DEFINED__
#define __ITRiASUnitsOfMeasure_FWD_DEFINED__
typedef interface ITRiASUnitsOfMeasure ITRiASUnitsOfMeasure;
#endif 	/* __ITRiASUnitsOfMeasure_FWD_DEFINED__ */


#ifndef __ITRiASUnitIDs_FWD_DEFINED__
#define __ITRiASUnitIDs_FWD_DEFINED__
typedef interface ITRiASUnitIDs ITRiASUnitIDs;
#endif 	/* __ITRiASUnitIDs_FWD_DEFINED__ */


#ifndef __IPopupTree_FWD_DEFINED__
#define __IPopupTree_FWD_DEFINED__
typedef interface IPopupTree IPopupTree;
#endif 	/* __IPopupTree_FWD_DEFINED__ */


#ifndef __IProjectValuePageCtrl_FWD_DEFINED__
#define __IProjectValuePageCtrl_FWD_DEFINED__
typedef interface IProjectValuePageCtrl IProjectValuePageCtrl;
#endif 	/* __IProjectValuePageCtrl_FWD_DEFINED__ */


#ifndef __ITRiASUsedUnits_FWD_DEFINED__
#define __ITRiASUsedUnits_FWD_DEFINED__
typedef interface ITRiASUsedUnits ITRiASUsedUnits;
#endif 	/* __ITRiASUsedUnits_FWD_DEFINED__ */


#ifndef ___IPopupTreeEvents_FWD_DEFINED__
#define ___IPopupTreeEvents_FWD_DEFINED__
typedef interface _IPopupTreeEvents _IPopupTreeEvents;
#endif 	/* ___IPopupTreeEvents_FWD_DEFINED__ */


#ifndef ___IProjectValuePageCtrlEvents_FWD_DEFINED__
#define ___IProjectValuePageCtrlEvents_FWD_DEFINED__
typedef interface _IProjectValuePageCtrlEvents _IProjectValuePageCtrlEvents;
#endif 	/* ___IProjectValuePageCtrlEvents_FWD_DEFINED__ */


#ifndef __IValueProviderCallback_FWD_DEFINED__
#define __IValueProviderCallback_FWD_DEFINED__
typedef interface IValueProviderCallback IValueProviderCallback;
#endif 	/* __IValueProviderCallback_FWD_DEFINED__ */


#ifndef __TRiASSimpleStatistics_FWD_DEFINED__
#define __TRiASSimpleStatistics_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASSimpleStatistics TRiASSimpleStatistics;
#else
typedef struct TRiASSimpleStatistics TRiASSimpleStatistics;
#endif /* __cplusplus */

#endif 	/* __TRiASSimpleStatistics_FWD_DEFINED__ */


#ifndef __TRiASStatistCount_FWD_DEFINED__
#define __TRiASStatistCount_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASStatistCount TRiASStatistCount;
#else
typedef struct TRiASStatistCount TRiASStatistCount;
#endif /* __cplusplus */

#endif 	/* __TRiASStatistCount_FWD_DEFINED__ */


#ifndef __TRiASStatistCountNotNull_FWD_DEFINED__
#define __TRiASStatistCountNotNull_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASStatistCountNotNull TRiASStatistCountNotNull;
#else
typedef struct TRiASStatistCountNotNull TRiASStatistCountNotNull;
#endif /* __cplusplus */

#endif 	/* __TRiASStatistCountNotNull_FWD_DEFINED__ */


#ifndef __TRiASStatistSum_FWD_DEFINED__
#define __TRiASStatistSum_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASStatistSum TRiASStatistSum;
#else
typedef struct TRiASStatistSum TRiASStatistSum;
#endif /* __cplusplus */

#endif 	/* __TRiASStatistSum_FWD_DEFINED__ */


#ifndef __TRiASStatistArithmeticAverage_FWD_DEFINED__
#define __TRiASStatistArithmeticAverage_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASStatistArithmeticAverage TRiASStatistArithmeticAverage;
#else
typedef struct TRiASStatistArithmeticAverage TRiASStatistArithmeticAverage;
#endif /* __cplusplus */

#endif 	/* __TRiASStatistArithmeticAverage_FWD_DEFINED__ */


#ifndef __TRiASStatistGeometricAverage_FWD_DEFINED__
#define __TRiASStatistGeometricAverage_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASStatistGeometricAverage TRiASStatistGeometricAverage;
#else
typedef struct TRiASStatistGeometricAverage TRiASStatistGeometricAverage;
#endif /* __cplusplus */

#endif 	/* __TRiASStatistGeometricAverage_FWD_DEFINED__ */


#ifndef __TRiASStatistMedian_FWD_DEFINED__
#define __TRiASStatistMedian_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASStatistMedian TRiASStatistMedian;
#else
typedef struct TRiASStatistMedian TRiASStatistMedian;
#endif /* __cplusplus */

#endif 	/* __TRiASStatistMedian_FWD_DEFINED__ */


#ifndef __TRiASStatistMinValue_FWD_DEFINED__
#define __TRiASStatistMinValue_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASStatistMinValue TRiASStatistMinValue;
#else
typedef struct TRiASStatistMinValue TRiASStatistMinValue;
#endif /* __cplusplus */

#endif 	/* __TRiASStatistMinValue_FWD_DEFINED__ */


#ifndef __TRiASStatistMaxValue_FWD_DEFINED__
#define __TRiASStatistMaxValue_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASStatistMaxValue TRiASStatistMaxValue;
#else
typedef struct TRiASStatistMaxValue TRiASStatistMaxValue;
#endif /* __cplusplus */

#endif 	/* __TRiASStatistMaxValue_FWD_DEFINED__ */


#ifndef __TRiASStatistRange_FWD_DEFINED__
#define __TRiASStatistRange_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASStatistRange TRiASStatistRange;
#else
typedef struct TRiASStatistRange TRiASStatistRange;
#endif /* __cplusplus */

#endif 	/* __TRiASStatistRange_FWD_DEFINED__ */


#ifndef __TRiASStatistStandardDeviation_FWD_DEFINED__
#define __TRiASStatistStandardDeviation_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASStatistStandardDeviation TRiASStatistStandardDeviation;
#else
typedef struct TRiASStatistStandardDeviation TRiASStatistStandardDeviation;
#endif /* __cplusplus */

#endif 	/* __TRiASStatistStandardDeviation_FWD_DEFINED__ */


#ifndef __TRiASStatistVariance_FWD_DEFINED__
#define __TRiASStatistVariance_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASStatistVariance TRiASStatistVariance;
#else
typedef struct TRiASStatistVariance TRiASStatistVariance;
#endif /* __cplusplus */

#endif 	/* __TRiASStatistVariance_FWD_DEFINED__ */


#ifndef __TRiASUnitsOfMeasure_FWD_DEFINED__
#define __TRiASUnitsOfMeasure_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASUnitsOfMeasure TRiASUnitsOfMeasure;
#else
typedef struct TRiASUnitsOfMeasure TRiASUnitsOfMeasure;
#endif /* __cplusplus */

#endif 	/* __TRiASUnitsOfMeasure_FWD_DEFINED__ */


#ifndef __TRiASUnitIDs_FWD_DEFINED__
#define __TRiASUnitIDs_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASUnitIDs TRiASUnitIDs;
#else
typedef struct TRiASUnitIDs TRiASUnitIDs;
#endif /* __cplusplus */

#endif 	/* __TRiASUnitIDs_FWD_DEFINED__ */


#ifndef __CountLinePoints_FWD_DEFINED__
#define __CountLinePoints_FWD_DEFINED__

#ifdef __cplusplus
typedef class CountLinePoints CountLinePoints;
#else
typedef struct CountLinePoints CountLinePoints;
#endif /* __cplusplus */

#endif 	/* __CountLinePoints_FWD_DEFINED__ */


#ifndef __ObjContainerXMin_FWD_DEFINED__
#define __ObjContainerXMin_FWD_DEFINED__

#ifdef __cplusplus
typedef class ObjContainerXMin ObjContainerXMin;
#else
typedef struct ObjContainerXMin ObjContainerXMin;
#endif /* __cplusplus */

#endif 	/* __ObjContainerXMin_FWD_DEFINED__ */


#ifndef __ObjContainerXMax_FWD_DEFINED__
#define __ObjContainerXMax_FWD_DEFINED__

#ifdef __cplusplus
typedef class ObjContainerXMax ObjContainerXMax;
#else
typedef struct ObjContainerXMax ObjContainerXMax;
#endif /* __cplusplus */

#endif 	/* __ObjContainerXMax_FWD_DEFINED__ */


#ifndef __ObjContainerYMin_FWD_DEFINED__
#define __ObjContainerYMin_FWD_DEFINED__

#ifdef __cplusplus
typedef class ObjContainerYMin ObjContainerYMin;
#else
typedef struct ObjContainerYMin ObjContainerYMin;
#endif /* __cplusplus */

#endif 	/* __ObjContainerYMin_FWD_DEFINED__ */


#ifndef __ObjContainerYMax_FWD_DEFINED__
#define __ObjContainerYMax_FWD_DEFINED__

#ifdef __cplusplus
typedef class ObjContainerYMax ObjContainerYMax;
#else
typedef struct ObjContainerYMax ObjContainerYMax;
#endif /* __cplusplus */

#endif 	/* __ObjContainerYMax_FWD_DEFINED__ */


#ifndef __LengthOfLine_FWD_DEFINED__
#define __LengthOfLine_FWD_DEFINED__

#ifdef __cplusplus
typedef class LengthOfLine LengthOfLine;
#else
typedef struct LengthOfLine LengthOfLine;
#endif /* __cplusplus */

#endif 	/* __LengthOfLine_FWD_DEFINED__ */


#ifndef __CountAreaIsland_FWD_DEFINED__
#define __CountAreaIsland_FWD_DEFINED__

#ifdef __cplusplus
typedef class CountAreaIsland CountAreaIsland;
#else
typedef struct CountAreaIsland CountAreaIsland;
#endif /* __cplusplus */

#endif 	/* __CountAreaIsland_FWD_DEFINED__ */


#ifndef __SimpleAreaFrame_FWD_DEFINED__
#define __SimpleAreaFrame_FWD_DEFINED__

#ifdef __cplusplus
typedef class SimpleAreaFrame SimpleAreaFrame;
#else
typedef struct SimpleAreaFrame SimpleAreaFrame;
#endif /* __cplusplus */

#endif 	/* __SimpleAreaFrame_FWD_DEFINED__ */


#ifndef __FullAreaFrame_FWD_DEFINED__
#define __FullAreaFrame_FWD_DEFINED__

#ifdef __cplusplus
typedef class FullAreaFrame FullAreaFrame;
#else
typedef struct FullAreaFrame FullAreaFrame;
#endif /* __cplusplus */

#endif 	/* __FullAreaFrame_FWD_DEFINED__ */


#ifndef __SuperficialContents_FWD_DEFINED__
#define __SuperficialContents_FWD_DEFINED__

#ifdef __cplusplus
typedef class SuperficialContents SuperficialContents;
#else
typedef struct SuperficialContents SuperficialContents;
#endif /* __cplusplus */

#endif 	/* __SuperficialContents_FWD_DEFINED__ */


#ifndef __SimpleAreaRadius_FWD_DEFINED__
#define __SimpleAreaRadius_FWD_DEFINED__

#ifdef __cplusplus
typedef class SimpleAreaRadius SimpleAreaRadius;
#else
typedef struct SimpleAreaRadius SimpleAreaRadius;
#endif /* __cplusplus */

#endif 	/* __SimpleAreaRadius_FWD_DEFINED__ */


#ifndef __PointCoordX_FWD_DEFINED__
#define __PointCoordX_FWD_DEFINED__

#ifdef __cplusplus
typedef class PointCoordX PointCoordX;
#else
typedef struct PointCoordX PointCoordX;
#endif /* __cplusplus */

#endif 	/* __PointCoordX_FWD_DEFINED__ */


#ifndef __PointCoordY_FWD_DEFINED__
#define __PointCoordY_FWD_DEFINED__

#ifdef __cplusplus
typedef class PointCoordY PointCoordY;
#else
typedef struct PointCoordY PointCoordY;
#endif /* __cplusplus */

#endif 	/* __PointCoordY_FWD_DEFINED__ */


#ifndef __PointCentreCoordX_FWD_DEFINED__
#define __PointCentreCoordX_FWD_DEFINED__

#ifdef __cplusplus
typedef class PointCentreCoordX PointCentreCoordX;
#else
typedef struct PointCentreCoordX PointCentreCoordX;
#endif /* __cplusplus */

#endif 	/* __PointCentreCoordX_FWD_DEFINED__ */


#ifndef __PointCentreCoordY_FWD_DEFINED__
#define __PointCentreCoordY_FWD_DEFINED__

#ifdef __cplusplus
typedef class PointCentreCoordY PointCentreCoordY;
#else
typedef struct PointCentreCoordY PointCentreCoordY;
#endif /* __cplusplus */

#endif 	/* __PointCentreCoordY_FWD_DEFINED__ */


#ifndef __StatisticObjectProperty_FWD_DEFINED__
#define __StatisticObjectProperty_FWD_DEFINED__

#ifdef __cplusplus
typedef class StatisticObjectProperty StatisticObjectProperty;
#else
typedef struct StatisticObjectProperty StatisticObjectProperty;
#endif /* __cplusplus */

#endif 	/* __StatisticObjectProperty_FWD_DEFINED__ */


#ifndef __MathOperationProperty_FWD_DEFINED__
#define __MathOperationProperty_FWD_DEFINED__

#ifdef __cplusplus
typedef class MathOperationProperty MathOperationProperty;
#else
typedef struct MathOperationProperty MathOperationProperty;
#endif /* __cplusplus */

#endif 	/* __MathOperationProperty_FWD_DEFINED__ */


#ifndef __SelectStatistValue_FWD_DEFINED__
#define __SelectStatistValue_FWD_DEFINED__

#ifdef __cplusplus
typedef class SelectStatistValue SelectStatistValue;
#else
typedef struct SelectStatistValue SelectStatistValue;
#endif /* __cplusplus */

#endif 	/* __SelectStatistValue_FWD_DEFINED__ */


#ifndef __MeshGeneration_FWD_DEFINED__
#define __MeshGeneration_FWD_DEFINED__

#ifdef __cplusplus
typedef class MeshGeneration MeshGeneration;
#else
typedef struct MeshGeneration MeshGeneration;
#endif /* __cplusplus */

#endif 	/* __MeshGeneration_FWD_DEFINED__ */


#ifndef __UnitsOfMeasurePP_FWD_DEFINED__
#define __UnitsOfMeasurePP_FWD_DEFINED__

#ifdef __cplusplus
typedef class UnitsOfMeasurePP UnitsOfMeasurePP;
#else
typedef struct UnitsOfMeasurePP UnitsOfMeasurePP;
#endif /* __cplusplus */

#endif 	/* __UnitsOfMeasurePP_FWD_DEFINED__ */


#ifndef __Statist_FWD_DEFINED__
#define __Statist_FWD_DEFINED__

#ifdef __cplusplus
typedef class Statist Statist;
#else
typedef struct Statist Statist;
#endif /* __cplusplus */

#endif 	/* __Statist_FWD_DEFINED__ */


#ifndef __PopupTree_FWD_DEFINED__
#define __PopupTree_FWD_DEFINED__

#ifdef __cplusplus
typedef class PopupTree PopupTree;
#else
typedef struct PopupTree PopupTree;
#endif /* __cplusplus */

#endif 	/* __PopupTree_FWD_DEFINED__ */


#ifndef __ProjectValuePageCtrl_FWD_DEFINED__
#define __ProjectValuePageCtrl_FWD_DEFINED__

#ifdef __cplusplus
typedef class ProjectValuePageCtrl ProjectValuePageCtrl;
#else
typedef struct ProjectValuePageCtrl ProjectValuePageCtrl;
#endif /* __cplusplus */

#endif 	/* __ProjectValuePageCtrl_FWD_DEFINED__ */


#ifndef __ORWndValuePageCtrl_FWD_DEFINED__
#define __ORWndValuePageCtrl_FWD_DEFINED__

#ifdef __cplusplus
typedef class ORWndValuePageCtrl ORWndValuePageCtrl;
#else
typedef struct ORWndValuePageCtrl ORWndValuePageCtrl;
#endif /* __cplusplus */

#endif 	/* __ORWndValuePageCtrl_FWD_DEFINED__ */


#ifndef __ProjectValuesCallback_FWD_DEFINED__
#define __ProjectValuesCallback_FWD_DEFINED__

#ifdef __cplusplus
typedef class ProjectValuesCallback ProjectValuesCallback;
#else
typedef struct ProjectValuesCallback ProjectValuesCallback;
#endif /* __cplusplus */

#endif 	/* __ProjectValuesCallback_FWD_DEFINED__ */


#ifndef __StatistUIOwner_FWD_DEFINED__
#define __StatistUIOwner_FWD_DEFINED__

#ifdef __cplusplus
typedef class StatistUIOwner StatistUIOwner;
#else
typedef struct StatistUIOwner StatistUIOwner;
#endif /* __cplusplus */

#endif 	/* __StatistUIOwner_FWD_DEFINED__ */


#ifndef __ObjectCountInClass_FWD_DEFINED__
#define __ObjectCountInClass_FWD_DEFINED__

#ifdef __cplusplus
typedef class ObjectCountInClass ObjectCountInClass;
#else
typedef struct ObjectCountInClass ObjectCountInClass;
#endif /* __cplusplus */

#endif 	/* __ObjectCountInClass_FWD_DEFINED__ */


#ifndef __ObjectCountInDatasource_FWD_DEFINED__
#define __ObjectCountInDatasource_FWD_DEFINED__

#ifdef __cplusplus
typedef class ObjectCountInDatasource ObjectCountInDatasource;
#else
typedef struct ObjectCountInDatasource ObjectCountInDatasource;
#endif /* __cplusplus */

#endif 	/* __ObjectCountInDatasource_FWD_DEFINED__ */


#ifndef __ObjectCountInORWndClass_FWD_DEFINED__
#define __ObjectCountInORWndClass_FWD_DEFINED__

#ifdef __cplusplus
typedef class ObjectCountInORWndClass ObjectCountInORWndClass;
#else
typedef struct ObjectCountInORWndClass ObjectCountInORWndClass;
#endif /* __cplusplus */

#endif 	/* __ObjectCountInORWndClass_FWD_DEFINED__ */


#ifndef __ObjectCountInORWnd_FWD_DEFINED__
#define __ObjectCountInORWnd_FWD_DEFINED__

#ifdef __cplusplus
typedef class ObjectCountInORWnd ObjectCountInORWnd;
#else
typedef struct ObjectCountInORWnd ObjectCountInORWnd;
#endif /* __cplusplus */

#endif 	/* __ObjectCountInORWnd_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "ProgInd2.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_StatistApp_0000 */
/* [local] */ 





extern RPC_IF_HANDLE __MIDL_itf_StatistApp_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_StatistApp_0000_v0_0_s_ifspec;

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


/* interface __MIDL_itf_StatistApp_0255 */
/* [local] */ 





extern RPC_IF_HANDLE __MIDL_itf_StatistApp_0255_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_StatistApp_0255_v0_0_s_ifspec;

#ifndef __IConfigObjectProperty_INTERFACE_DEFINED__
#define __IConfigObjectProperty_INTERFACE_DEFINED__

/* interface IConfigObjectProperty */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IConfigObjectProperty;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("101228D6-D0B0-41D3-8F95-370E888F0446")
    IConfigObjectProperty : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConfigObjectProperty( 
            HWND hWnd) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsConfigured( 
            /* [retval][out] */ VARIANT_BOOL *ConfigState) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IConfigObjectPropertyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IConfigObjectProperty * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IConfigObjectProperty * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IConfigObjectProperty * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigObjectProperty )( 
            IConfigObjectProperty * This,
            HWND hWnd);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsConfigured )( 
            IConfigObjectProperty * This,
            /* [retval][out] */ VARIANT_BOOL *ConfigState);
        
        END_INTERFACE
    } IConfigObjectPropertyVtbl;

    interface IConfigObjectProperty
    {
        CONST_VTBL struct IConfigObjectPropertyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IConfigObjectProperty_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IConfigObjectProperty_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IConfigObjectProperty_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IConfigObjectProperty_ConfigObjectProperty(This,hWnd)	\
    (This)->lpVtbl -> ConfigObjectProperty(This,hWnd)

#define IConfigObjectProperty_get_IsConfigured(This,ConfigState)	\
    (This)->lpVtbl -> get_IsConfigured(This,ConfigState)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IConfigObjectProperty_ConfigObjectProperty_Proxy( 
    IConfigObjectProperty * This,
    HWND hWnd);


void __RPC_STUB IConfigObjectProperty_ConfigObjectProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IConfigObjectProperty_get_IsConfigured_Proxy( 
    IConfigObjectProperty * This,
    /* [retval][out] */ VARIANT_BOOL *ConfigState);


void __RPC_STUB IConfigObjectProperty_get_IsConfigured_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IConfigObjectProperty_INTERFACE_DEFINED__ */


#ifndef __IConfigSequenceForObjectProperty_INTERFACE_DEFINED__
#define __IConfigSequenceForObjectProperty_INTERFACE_DEFINED__

/* interface IConfigSequenceForObjectProperty */
/* [unique][helpstring][uuid][object] */ 

#if !defined(_CALCLSID_DATA)
#define _CALCLSID_DATA
typedef /* [restricted][hidden] */ struct tagCALPCLSID
    {
    ULONG cElems;
    const CLSID **ppElems;
    const IUnknown **ppActions;
    const VARIANT **ppvData;
    const BSTR *ppMkData;
    const BSTR *ppHeaderTitle;
    const BSTR *ppHeaderSubTitle;
    } 	CALPCLSID;

#endif // !defined(_CALCLSID_DATA)

EXTERN_C const IID IID_IConfigSequenceForObjectProperty;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F7D428CF-8D5A-4B93-A129-F1D7C1EDE597")
    IConfigSequenceForObjectProperty : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddAction( 
            IUnknown *pIAct) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddActionsByCLSID( 
            CALPCLSID *pcsClsId) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PrepareActions( 
            HWND hParent,
            IDataObject *pIData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IConfigSequenceForObjectPropertyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IConfigSequenceForObjectProperty * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IConfigSequenceForObjectProperty * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IConfigSequenceForObjectProperty * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddAction )( 
            IConfigSequenceForObjectProperty * This,
            IUnknown *pIAct);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddActionsByCLSID )( 
            IConfigSequenceForObjectProperty * This,
            CALPCLSID *pcsClsId);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PrepareActions )( 
            IConfigSequenceForObjectProperty * This,
            HWND hParent,
            IDataObject *pIData);
        
        END_INTERFACE
    } IConfigSequenceForObjectPropertyVtbl;

    interface IConfigSequenceForObjectProperty
    {
        CONST_VTBL struct IConfigSequenceForObjectPropertyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IConfigSequenceForObjectProperty_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IConfigSequenceForObjectProperty_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IConfigSequenceForObjectProperty_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IConfigSequenceForObjectProperty_AddAction(This,pIAct)	\
    (This)->lpVtbl -> AddAction(This,pIAct)

#define IConfigSequenceForObjectProperty_AddActionsByCLSID(This,pcsClsId)	\
    (This)->lpVtbl -> AddActionsByCLSID(This,pcsClsId)

#define IConfigSequenceForObjectProperty_PrepareActions(This,hParent,pIData)	\
    (This)->lpVtbl -> PrepareActions(This,hParent,pIData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IConfigSequenceForObjectProperty_AddAction_Proxy( 
    IConfigSequenceForObjectProperty * This,
    IUnknown *pIAct);


void __RPC_STUB IConfigSequenceForObjectProperty_AddAction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IConfigSequenceForObjectProperty_AddActionsByCLSID_Proxy( 
    IConfigSequenceForObjectProperty * This,
    CALPCLSID *pcsClsId);


void __RPC_STUB IConfigSequenceForObjectProperty_AddActionsByCLSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IConfigSequenceForObjectProperty_PrepareActions_Proxy( 
    IConfigSequenceForObjectProperty * This,
    HWND hParent,
    IDataObject *pIData);


void __RPC_STUB IConfigSequenceForObjectProperty_PrepareActions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IConfigSequenceForObjectProperty_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_StatistApp_0261 */
/* [local] */ 





extern RPC_IF_HANDLE __MIDL_itf_StatistApp_0261_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_StatistApp_0261_v0_0_s_ifspec;

#ifndef __IValueProvider_INTERFACE_DEFINED__
#define __IValueProvider_INTERFACE_DEFINED__

/* interface IValueProvider */
/* [unique][helpstring][uuid][oleautomation][object] */ 

#if !defined(_VALUEPROVIDERPROP_DEFINED)
#define _VALUEPROVIDERPROP_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagVALUEPROVIDERPROP
    {	VALUEPROVIDERPROP_Unknown	= 0,
	VALUEPROVIDERPROP_String	= 0,
	VALUEPROVIDERPROP_Integer	= 0x10000,
	VALUEPROVIDERPROP_Double	= 0x20000,
	VALUEPROVIDERPROP_Bool	= 0x40000,
	VALUEPROVIDERPROP_Date	= 0x80000
    } 	VALUEPROVIDERPROP;

#endif // !defined(_VALUEPROVIDERPROP_DEFINED)

EXTERN_C const IID IID_IValueProvider;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("30E4A6F6-4712-4487-AA53-92BE3062C452")
    IValueProvider : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *Name) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *Name) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Flags( 
            /* [retval][out] */ VALUEPROVIDERPROP *Flags) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ VARIANT *Value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IValueProviderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IValueProvider * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IValueProvider * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IValueProvider * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IValueProvider * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IValueProvider * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IValueProvider * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IValueProvider * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IValueProvider * This,
            /* [retval][out] */ BSTR *Name);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            IValueProvider * This,
            /* [retval][out] */ BSTR *Name);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Flags )( 
            IValueProvider * This,
            /* [retval][out] */ VALUEPROVIDERPROP *Flags);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IValueProvider * This,
            /* [retval][out] */ VARIANT *Value);
        
        END_INTERFACE
    } IValueProviderVtbl;

    interface IValueProvider
    {
        CONST_VTBL struct IValueProviderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IValueProvider_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IValueProvider_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IValueProvider_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IValueProvider_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IValueProvider_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IValueProvider_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IValueProvider_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IValueProvider_get_Name(This,Name)	\
    (This)->lpVtbl -> get_Name(This,Name)

#define IValueProvider_get_Description(This,Name)	\
    (This)->lpVtbl -> get_Description(This,Name)

#define IValueProvider_get_Flags(This,Flags)	\
    (This)->lpVtbl -> get_Flags(This,Flags)

#define IValueProvider_get_Value(This,Value)	\
    (This)->lpVtbl -> get_Value(This,Value)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IValueProvider_get_Name_Proxy( 
    IValueProvider * This,
    /* [retval][out] */ BSTR *Name);


void __RPC_STUB IValueProvider_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IValueProvider_get_Description_Proxy( 
    IValueProvider * This,
    /* [retval][out] */ BSTR *Name);


void __RPC_STUB IValueProvider_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IValueProvider_get_Flags_Proxy( 
    IValueProvider * This,
    /* [retval][out] */ VALUEPROVIDERPROP *Flags);


void __RPC_STUB IValueProvider_get_Flags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IValueProvider_get_Value_Proxy( 
    IValueProvider * This,
    /* [retval][out] */ VARIANT *Value);


void __RPC_STUB IValueProvider_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IValueProvider_INTERFACE_DEFINED__ */


#ifndef __IValueProviderCallback_INTERFACE_DEFINED__
#define __IValueProviderCallback_INTERFACE_DEFINED__

/* interface IValueProviderCallback */
/* [uuid][object] */ 


EXTERN_C const IID IID_IValueProviderCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("648DD314-74D9-4A73-B64F-455017A29D77")
    IValueProviderCallback : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NeedsRefresh( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IValueProviderCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IValueProviderCallback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IValueProviderCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IValueProviderCallback * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NeedsRefresh )( 
            IValueProviderCallback * This);
        
        END_INTERFACE
    } IValueProviderCallbackVtbl;

    interface IValueProviderCallback
    {
        CONST_VTBL struct IValueProviderCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IValueProviderCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IValueProviderCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IValueProviderCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IValueProviderCallback_NeedsRefresh(This)	\
    (This)->lpVtbl -> NeedsRefresh(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IValueProviderCallback_NeedsRefresh_Proxy( 
    IValueProviderCallback * This);


void __RPC_STUB IValueProviderCallback_NeedsRefresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IValueProviderCallback_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_StatistApp_0265 */
/* [local] */ 

#define TYPELIB_STATIST_VERSION_MAJOR 1
#define TYPELIB_STATIST_VERSION_MINOR 0
#define TYPELIB_STATIST_VERSION "1.0"
#define TYPELIB_STATIST_LCID 0







extern RPC_IF_HANDLE __MIDL_itf_StatistApp_0265_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_StatistApp_0265_v0_0_s_ifspec;

#ifndef __IGenericStatistics_INTERFACE_DEFINED__
#define __IGenericStatistics_INTERFACE_DEFINED__

/* interface IGenericStatistics */
/* [unique][helpstring][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IGenericStatistics;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("85D47179-0B52-40D0-A30D-DB9BCBA26ED3")
    IGenericStatistics : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddValue( 
            /* [in] */ double Value,
            /* [optional][in] */ VARIANT Data) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveValue( 
            /* [in] */ double Value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Calculate( 
            /* [retval][out] */ VARIANT *Value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGenericStatisticsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGenericStatistics * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGenericStatistics * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGenericStatistics * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IGenericStatistics * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IGenericStatistics * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IGenericStatistics * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IGenericStatistics * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IGenericStatistics * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            IGenericStatistics * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddValue )( 
            IGenericStatistics * This,
            /* [in] */ double Value,
            /* [optional][in] */ VARIANT Data);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveValue )( 
            IGenericStatistics * This,
            /* [in] */ double Value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IGenericStatistics * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Calculate )( 
            IGenericStatistics * This,
            /* [retval][out] */ VARIANT *Value);
        
        END_INTERFACE
    } IGenericStatisticsVtbl;

    interface IGenericStatistics
    {
        CONST_VTBL struct IGenericStatisticsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGenericStatistics_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGenericStatistics_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGenericStatistics_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGenericStatistics_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IGenericStatistics_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IGenericStatistics_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IGenericStatistics_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IGenericStatistics_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IGenericStatistics_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#define IGenericStatistics_AddValue(This,Value,Data)	\
    (This)->lpVtbl -> AddValue(This,Value,Data)

#define IGenericStatistics_RemoveValue(This,Value)	\
    (This)->lpVtbl -> RemoveValue(This,Value)

#define IGenericStatistics_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IGenericStatistics_Calculate(This,Value)	\
    (This)->lpVtbl -> Calculate(This,Value)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGenericStatistics_get_Name_Proxy( 
    IGenericStatistics * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IGenericStatistics_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGenericStatistics_get_Description_Proxy( 
    IGenericStatistics * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IGenericStatistics_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGenericStatistics_AddValue_Proxy( 
    IGenericStatistics * This,
    /* [in] */ double Value,
    /* [optional][in] */ VARIANT Data);


void __RPC_STUB IGenericStatistics_AddValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGenericStatistics_RemoveValue_Proxy( 
    IGenericStatistics * This,
    /* [in] */ double Value);


void __RPC_STUB IGenericStatistics_RemoveValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGenericStatistics_Reset_Proxy( 
    IGenericStatistics * This);


void __RPC_STUB IGenericStatistics_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGenericStatistics_Calculate_Proxy( 
    IGenericStatistics * This,
    /* [retval][out] */ VARIANT *Value);


void __RPC_STUB IGenericStatistics_Calculate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGenericStatistics_INTERFACE_DEFINED__ */


#ifndef __ITRiASSimpleStatistics_INTERFACE_DEFINED__
#define __ITRiASSimpleStatistics_INTERFACE_DEFINED__

/* interface ITRiASSimpleStatistics */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASSimpleStatistics;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0CB3A698-E5CE-11D2-9BD9-586A20524153")
    ITRiASSimpleStatistics : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ ULONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Sum( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CountNotNull( 
            /* [retval][out] */ ULONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ArithmeticAverage( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GeometricAverage( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Median( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MinValue( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MaxValue( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Range( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StandardDeviation( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Variance( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddValue( 
            /* [in] */ double Value,
            /* [optional][in] */ VARIANT Data) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveValue( 
            /* [in] */ double Value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RangesByEqualCount( 
            /* [in] */ ULONG NumOfRanges,
            /* [out][in] */ SAFEARRAY * *MinBounds,
            /* [out][in] */ SAFEARRAY * *MaxBounds,
            /* [out][in] */ SAFEARRAY * *Counts,
            /* [out][in] */ SAFEARRAY * *Data) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RangesByEqualRange( 
            /* [in] */ ULONG NumberOfRanges,
            /* [in] */ double StartValue,
            /* [in] */ double EndValue,
            /* [out][in] */ SAFEARRAY * *MinBounds,
            /* [out][in] */ SAFEARRAY * *MaxBounds,
            /* [out][in] */ SAFEARRAY * *Counts,
            /* [out][in] */ SAFEARRAY * *Data) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RangesByStandardDeviation( 
            /* [in] */ ULONG NumberOfRanges,
            /* [out][in] */ SAFEARRAY * *MinBounds,
            /* [out][in] */ SAFEARRAY * *MaxBounds,
            /* [out][in] */ SAFEARRAY * *Counts,
            /* [out][in] */ SAFEARRAY * *Data) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASSimpleStatisticsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASSimpleStatistics * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASSimpleStatistics * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASSimpleStatistics * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASSimpleStatistics * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASSimpleStatistics * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASSimpleStatistics * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASSimpleStatistics * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITRiASSimpleStatistics * This,
            /* [retval][out] */ ULONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Sum )( 
            ITRiASSimpleStatistics * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CountNotNull )( 
            ITRiASSimpleStatistics * This,
            /* [retval][out] */ ULONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ArithmeticAverage )( 
            ITRiASSimpleStatistics * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GeometricAverage )( 
            ITRiASSimpleStatistics * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Median )( 
            ITRiASSimpleStatistics * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinValue )( 
            ITRiASSimpleStatistics * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxValue )( 
            ITRiASSimpleStatistics * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Range )( 
            ITRiASSimpleStatistics * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StandardDeviation )( 
            ITRiASSimpleStatistics * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Variance )( 
            ITRiASSimpleStatistics * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddValue )( 
            ITRiASSimpleStatistics * This,
            /* [in] */ double Value,
            /* [optional][in] */ VARIANT Data);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveValue )( 
            ITRiASSimpleStatistics * This,
            /* [in] */ double Value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            ITRiASSimpleStatistics * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RangesByEqualCount )( 
            ITRiASSimpleStatistics * This,
            /* [in] */ ULONG NumOfRanges,
            /* [out][in] */ SAFEARRAY * *MinBounds,
            /* [out][in] */ SAFEARRAY * *MaxBounds,
            /* [out][in] */ SAFEARRAY * *Counts,
            /* [out][in] */ SAFEARRAY * *Data);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RangesByEqualRange )( 
            ITRiASSimpleStatistics * This,
            /* [in] */ ULONG NumberOfRanges,
            /* [in] */ double StartValue,
            /* [in] */ double EndValue,
            /* [out][in] */ SAFEARRAY * *MinBounds,
            /* [out][in] */ SAFEARRAY * *MaxBounds,
            /* [out][in] */ SAFEARRAY * *Counts,
            /* [out][in] */ SAFEARRAY * *Data);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RangesByStandardDeviation )( 
            ITRiASSimpleStatistics * This,
            /* [in] */ ULONG NumberOfRanges,
            /* [out][in] */ SAFEARRAY * *MinBounds,
            /* [out][in] */ SAFEARRAY * *MaxBounds,
            /* [out][in] */ SAFEARRAY * *Counts,
            /* [out][in] */ SAFEARRAY * *Data);
        
        END_INTERFACE
    } ITRiASSimpleStatisticsVtbl;

    interface ITRiASSimpleStatistics
    {
        CONST_VTBL struct ITRiASSimpleStatisticsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASSimpleStatistics_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASSimpleStatistics_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASSimpleStatistics_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASSimpleStatistics_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASSimpleStatistics_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASSimpleStatistics_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASSimpleStatistics_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASSimpleStatistics_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define ITRiASSimpleStatistics_get_Sum(This,pVal)	\
    (This)->lpVtbl -> get_Sum(This,pVal)

#define ITRiASSimpleStatistics_get_CountNotNull(This,pVal)	\
    (This)->lpVtbl -> get_CountNotNull(This,pVal)

#define ITRiASSimpleStatistics_get_ArithmeticAverage(This,pVal)	\
    (This)->lpVtbl -> get_ArithmeticAverage(This,pVal)

#define ITRiASSimpleStatistics_get_GeometricAverage(This,pVal)	\
    (This)->lpVtbl -> get_GeometricAverage(This,pVal)

#define ITRiASSimpleStatistics_get_Median(This,pVal)	\
    (This)->lpVtbl -> get_Median(This,pVal)

#define ITRiASSimpleStatistics_get_MinValue(This,pVal)	\
    (This)->lpVtbl -> get_MinValue(This,pVal)

#define ITRiASSimpleStatistics_get_MaxValue(This,pVal)	\
    (This)->lpVtbl -> get_MaxValue(This,pVal)

#define ITRiASSimpleStatistics_get_Range(This,pVal)	\
    (This)->lpVtbl -> get_Range(This,pVal)

#define ITRiASSimpleStatistics_get_StandardDeviation(This,pVal)	\
    (This)->lpVtbl -> get_StandardDeviation(This,pVal)

#define ITRiASSimpleStatistics_get_Variance(This,pVal)	\
    (This)->lpVtbl -> get_Variance(This,pVal)

#define ITRiASSimpleStatistics_AddValue(This,Value,Data)	\
    (This)->lpVtbl -> AddValue(This,Value,Data)

#define ITRiASSimpleStatistics_RemoveValue(This,Value)	\
    (This)->lpVtbl -> RemoveValue(This,Value)

#define ITRiASSimpleStatistics_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define ITRiASSimpleStatistics_RangesByEqualCount(This,NumOfRanges,MinBounds,MaxBounds,Counts,Data)	\
    (This)->lpVtbl -> RangesByEqualCount(This,NumOfRanges,MinBounds,MaxBounds,Counts,Data)

#define ITRiASSimpleStatistics_RangesByEqualRange(This,NumberOfRanges,StartValue,EndValue,MinBounds,MaxBounds,Counts,Data)	\
    (This)->lpVtbl -> RangesByEqualRange(This,NumberOfRanges,StartValue,EndValue,MinBounds,MaxBounds,Counts,Data)

#define ITRiASSimpleStatistics_RangesByStandardDeviation(This,NumberOfRanges,MinBounds,MaxBounds,Counts,Data)	\
    (This)->lpVtbl -> RangesByStandardDeviation(This,NumberOfRanges,MinBounds,MaxBounds,Counts,Data)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleStatistics_get_Count_Proxy( 
    ITRiASSimpleStatistics * This,
    /* [retval][out] */ ULONG *pVal);


void __RPC_STUB ITRiASSimpleStatistics_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleStatistics_get_Sum_Proxy( 
    ITRiASSimpleStatistics * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB ITRiASSimpleStatistics_get_Sum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleStatistics_get_CountNotNull_Proxy( 
    ITRiASSimpleStatistics * This,
    /* [retval][out] */ ULONG *pVal);


void __RPC_STUB ITRiASSimpleStatistics_get_CountNotNull_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleStatistics_get_ArithmeticAverage_Proxy( 
    ITRiASSimpleStatistics * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB ITRiASSimpleStatistics_get_ArithmeticAverage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleStatistics_get_GeometricAverage_Proxy( 
    ITRiASSimpleStatistics * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB ITRiASSimpleStatistics_get_GeometricAverage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleStatistics_get_Median_Proxy( 
    ITRiASSimpleStatistics * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB ITRiASSimpleStatistics_get_Median_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleStatistics_get_MinValue_Proxy( 
    ITRiASSimpleStatistics * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB ITRiASSimpleStatistics_get_MinValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleStatistics_get_MaxValue_Proxy( 
    ITRiASSimpleStatistics * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB ITRiASSimpleStatistics_get_MaxValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleStatistics_get_Range_Proxy( 
    ITRiASSimpleStatistics * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB ITRiASSimpleStatistics_get_Range_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleStatistics_get_StandardDeviation_Proxy( 
    ITRiASSimpleStatistics * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB ITRiASSimpleStatistics_get_StandardDeviation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleStatistics_get_Variance_Proxy( 
    ITRiASSimpleStatistics * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB ITRiASSimpleStatistics_get_Variance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleStatistics_AddValue_Proxy( 
    ITRiASSimpleStatistics * This,
    /* [in] */ double Value,
    /* [optional][in] */ VARIANT Data);


void __RPC_STUB ITRiASSimpleStatistics_AddValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleStatistics_RemoveValue_Proxy( 
    ITRiASSimpleStatistics * This,
    /* [in] */ double Value);


void __RPC_STUB ITRiASSimpleStatistics_RemoveValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleStatistics_Reset_Proxy( 
    ITRiASSimpleStatistics * This);


void __RPC_STUB ITRiASSimpleStatistics_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleStatistics_RangesByEqualCount_Proxy( 
    ITRiASSimpleStatistics * This,
    /* [in] */ ULONG NumOfRanges,
    /* [out][in] */ SAFEARRAY * *MinBounds,
    /* [out][in] */ SAFEARRAY * *MaxBounds,
    /* [out][in] */ SAFEARRAY * *Counts,
    /* [out][in] */ SAFEARRAY * *Data);


void __RPC_STUB ITRiASSimpleStatistics_RangesByEqualCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleStatistics_RangesByEqualRange_Proxy( 
    ITRiASSimpleStatistics * This,
    /* [in] */ ULONG NumberOfRanges,
    /* [in] */ double StartValue,
    /* [in] */ double EndValue,
    /* [out][in] */ SAFEARRAY * *MinBounds,
    /* [out][in] */ SAFEARRAY * *MaxBounds,
    /* [out][in] */ SAFEARRAY * *Counts,
    /* [out][in] */ SAFEARRAY * *Data);


void __RPC_STUB ITRiASSimpleStatistics_RangesByEqualRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleStatistics_RangesByStandardDeviation_Proxy( 
    ITRiASSimpleStatistics * This,
    /* [in] */ ULONG NumberOfRanges,
    /* [out][in] */ SAFEARRAY * *MinBounds,
    /* [out][in] */ SAFEARRAY * *MaxBounds,
    /* [out][in] */ SAFEARRAY * *Counts,
    /* [out][in] */ SAFEARRAY * *Data);


void __RPC_STUB ITRiASSimpleStatistics_RangesByStandardDeviation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASSimpleStatistics_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_StatistApp_0271 */
/* [local] */ 

#if !defined(_UNITTYPECONSTANTS_DEFINED)
#define _UNITTYPECONSTANTS_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagUNITTYPECONSTANTS
    {	UNITTYPECONSTANTS_Distance	= 1,
	UNITTYPECONSTANTS_Angle	= 2,
	UNITTYPECONSTANTS_Mass	= 3,
	UNITTYPECONSTANTS_Time	= 4,
	UNITTYPECONSTANTS_Temperature	= 5,
	UNITTYPECONSTANTS_ElectricCharge	= 6,
	UNITTYPECONSTANTS_LuminousIntensity	= 7,
	UNITTYPECONSTANTS_AmountOfSubstance	= 8,
	UNITTYPECONSTANTS_SolidAngle	= 9,
	UNITTYPECONSTANTS_AngularAcceleration	= 10,
	UNITTYPECONSTANTS_AngularMomentum	= 11,
	UNITTYPECONSTANTS_AngularVelocity	= 12,
	UNITTYPECONSTANTS_Area	= 13,
	UNITTYPECONSTANTS_BodyForce	= 14,
	UNITTYPECONSTANTS_CoefficientOfThermalExpansion	= 15,
	UNITTYPECONSTANTS_Density	= 16,
	UNITTYPECONSTANTS_ElectricalCapacitance	= 17,
	UNITTYPECONSTANTS_ElectricalConductance	= 18,
	UNITTYPECONSTANTS_ElectricalFieldStrength	= 19,
	UNITTYPECONSTANTS_ElectricalInductance	= 20,
	UNITTYPECONSTANTS_ElectricalPotential	= 21,
	UNITTYPECONSTANTS_ElectricalResistance	= 22,
	UNITTYPECONSTANTS_Energy	= 23,
	UNITTYPECONSTANTS_Entropy	= 24,
	UNITTYPECONSTANTS_FilmCoefficient	= 25,
	UNITTYPECONSTANTS_Force	= 26,
	UNITTYPECONSTANTS_ForcePerArea	= 27,
	UNITTYPECONSTANTS_ForcePerDistance	= 28,
	UNITTYPECONSTANTS_Frequency	= 29,
	UNITTYPECONSTANTS_HeatCapacity	= 30,
	UNITTYPECONSTANTS_HeatFluxPerArea	= 31,
	UNITTYPECONSTANTS_HeatFluxPerDistance	= 32,
	UNITTYPECONSTANTS_HeatSource	= 33,
	UNITTYPECONSTANTS_Illuminance	= 34,
	UNITTYPECONSTANTS_LinearAcceleration	= 35,
	UNITTYPECONSTANTS_LinearPerAngular	= 36,
	UNITTYPECONSTANTS_LinearVelocity	= 37,
	UNITTYPECONSTANTS_LuminousFlux	= 38,
	UNITTYPECONSTANTS_MagneticFieldStrength	= 39,
	UNITTYPECONSTANTS_MagneticFlux	= 40,
	UNITTYPECONSTANTS_MagneticFluxDensity	= 41,
	UNITTYPECONSTANTS_MassFlowRate	= 42,
	UNITTYPECONSTANTS_MassMomentOfInertia	= 43,
	UNITTYPECONSTANTS_MassPerArea	= 44,
	UNITTYPECONSTANTS_MassPerLength	= 45,
	UNITTYPECONSTANTS_Momentum	= 46,
	UNITTYPECONSTANTS_PerDistance	= 47,
	UNITTYPECONSTANTS_Power	= 48,
	UNITTYPECONSTANTS_QuantityOfElectricity	= 49,
	UNITTYPECONSTANTS_RadiantIntensity	= 50,
	UNITTYPECONSTANTS_RotationalStiffness	= 51,
	UNITTYPECONSTANTS_SecondMomentOfArea	= 52,
	UNITTYPECONSTANTS_ThermalConductivity	= 53,
	UNITTYPECONSTANTS_DynamicViscosity	= 54,
	UNITTYPECONSTANTS_KinematicViscosity	= 55,
	UNITTYPECONSTANTS_Volume	= 56,
	UNITTYPECONSTANTS_VolumeFlowRate	= 57,
	UNITTYPECONSTANTS_Scalar	= 58
    } 	UNITTYPECONSTANTS;

#endif // _UNITTYPECONSTANTS_DEFINED
#if !defined(_UNITCONSTANTS_DEFINED)
#define _UNITCONSTANTS_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagUNITCONSTANTS
    {	UNITCONSTANTS_Unknown	= -1,
	UNITCONSTANTS_BestFitSI	= 0,
	UNITCONSTANTS_DistanceMeter	= 59,
	UNITCONSTANTS_DistanceNanometer	= 60,
	UNITCONSTANTS_DistanceMillimeter	= 61,
	UNITCONSTANTS_DistanceCentimeter	= 62,
	UNITCONSTANTS_DistanceKilometer	= 63,
	UNITCONSTANTS_DistanceInch	= 64,
	UNITCONSTANTS_DistanceFoot	= 65,
	UNITCONSTANTS_DistanceYard	= 66,
	UNITCONSTANTS_DistanceMile	= 67,
	UNITCONSTANTS_DistanceTenth	= 68,
	UNITCONSTANTS_DistanceHundredth	= 69,
	UNITCONSTANTS_DistanceThousandth	= 70,
	UNITCONSTANTS_DistanceRod	= 71,
	UNITCONSTANTS_DistancePole	= 72,
	UNITCONSTANTS_DistanceLink	= 73,
	UNITCONSTANTS_DistanceChain	= 74,
	UNITCONSTANTS_DistancePoint	= 75,
	UNITCONSTANTS_DistanceFurlong	= 76,
	UNITCONSTANTS_AngleRadian	= 77,
	UNITCONSTANTS_AngleDegree	= 78,
	UNITCONSTANTS_AngleMinute	= 79,
	UNITCONSTANTS_AngleSecond	= 80,
	UNITCONSTANTS_AngleGradian	= 81,
	UNITCONSTANTS_AngleRevolution	= 82,
	UNITCONSTANTS_MassKilogram	= 83,
	UNITCONSTANTS_MassGram	= 84,
	UNITCONSTANTS_MassMilligram	= 85,
	UNITCONSTANTS_MassMegagram	= 86,
	UNITCONSTANTS_MassGrain	= 87,
	UNITCONSTANTS_MassSlug	= 88,
	UNITCONSTANTS_MassPoundMass	= 89,
	UNITCONSTANTS_MassSlinch	= 90,
	UNITCONSTANTS_MassOunce	= 91,
	UNITCONSTANTS_MassMetricTon	= 92,
	UNITCONSTANTS_MassLongTon	= 93,
	UNITCONSTANTS_MassShortTon	= 94,
	UNITCONSTANTS_TimeSecond	= 95,
	UNITCONSTANTS_TimeMinute	= 96,
	UNITCONSTANTS_TimeHour	= 97,
	UNITCONSTANTS_TimeDay	= 98,
	UNITCONSTANTS_TimeWeek	= 99,
	UNITCONSTANTS_TimeYear	= 100,
	UNITCONSTANTS_TimeMillisecond	= 101,
	UNITCONSTANTS_TimeNanosecond	= 102,
	UNITCONSTANTS_TemperatureKelvin	= 103,
	UNITCONSTANTS_TemperatureFahrenheit	= 104,
	UNITCONSTANTS_TemperatureCelcius	= 105,
	UNITCONSTANTS_TemperatureRankine	= 106,
	UNITCONSTANTS_ElectricChargeAmpere	= 107,
	UNITCONSTANTS_LuminousIntensityCandela	= 108,
	UNITCONSTANTS_AmountOfSubstanceMole	= 109,
	UNITCONSTANTS_SolidAngleSteradian	= 110,
	UNITCONSTANTS_AngularAccelerationRadianPerSqrSecond	= 111,
	UNITCONSTANTS_AngularAccelerationDegreePerSqrSecond	= 112,
	UNITCONSTANTS_AngularAccelerationCyclePerSqrSecond	= 113,
	UNITCONSTANTS_AngularMomentumKilogramSqrMeterPerSecond	= 114,
	UNITCONSTANTS_AngularVelocityRadianPerSecond	= 115,
	UNITCONSTANTS_AngularVelocityRadianPerMinute	= 116,
	UNITCONSTANTS_AngularVelocityRadianPerHour	= 117,
	UNITCONSTANTS_AngularVelocityCyclePerSecond	= 118,
	UNITCONSTANTS_AngularVelocityCyclePerMinute	= 119,
	UNITCONSTANTS_AngularVelocityCyclePerHour	= 120,
	UNITCONSTANTS_AngularVelocityDegreePerSecond	= 121,
	UNITCONSTANTS_AngularVelocityDegreePerMinute	= 122,
	UNITCONSTANTS_AngularVelocityDegreePerHour	= 123,
	UNITCONSTANTS_AreaSquareMeter	= 124,
	UNITCONSTANTS_AreaSquareMillimeter	= 125,
	UNITCONSTANTS_AreaSquareCentimeter	= 126,
	UNITCONSTANTS_AreaSquareKilometer	= 127,
	UNITCONSTANTS_AreaSquareInch	= 128,
	UNITCONSTANTS_AreaSquareFoot	= 129,
	UNITCONSTANTS_AreaSquareYard	= 130,
	UNITCONSTANTS_AreaSquareMile	= 131,
	UNITCONSTANTS_AreaAcre	= 132,
	UNITCONSTANTS_BodyForceNewtonPerCubicMeter	= 133,
	UNITCONSTANTS_BodyForceNewtonPerCubicCentimeter	= 134,
	UNITCONSTANTS_BodyForceNewtonPerCubicMillimeter	= 135,
	UNITCONSTANTS_BodyForceKilonewtonPerCubicMeter	= 136,
	UNITCONSTANTS_BodyForcePoundForcePerCubicInch	= 137,
	UNITCONSTANTS_BodyForcePoundForcePerCubicFoot	= 138,
	UNITCONSTANTS_CoefficientOfThermalExpansionPerKelvin	= 139,
	UNITCONSTANTS_CoefficientOfThermalExpansionPerCelcius	= 140,
	UNITCONSTANTS_CoefficientOfThermalExpansionPerFahrenheit	= 141,
	UNITCONSTANTS_CoefficientOfThermalExpansionPerRankine	= 142,
	UNITCONSTANTS_DensityKilogramPerCubicMeter	= 143,
	UNITCONSTANTS_DensityKilogramPerCubicMillimeter	= 144,
	UNITCONSTANTS_DensityKilogramPerCubicCentimeter	= 145,
	UNITCONSTANTS_DensityPoundMassPerCubicFoot	= 146,
	UNITCONSTANTS_DensityPoundMassPerCubicInch	= 147,
	UNITCONSTANTS_DensitySlugPerCubicFoot	= 148,
	UNITCONSTANTS_DensitySlinchPerCubicInch	= 149,
	UNITCONSTANTS_ElectricalCapacitanceFarad	= 150,
	UNITCONSTANTS_ElectricalConductanceSiemens	= 151,
	UNITCONSTANTS_ElectricalFieldStrengthVoltPerMeter	= 152,
	UNITCONSTANTS_ElectricalPotentialVolt	= 153,
	UNITCONSTANTS_ElectricalResistanceOhm	= 154,
	UNITCONSTANTS_EnergyJoule	= 155,
	UNITCONSTANTS_EnergyMicrojoule	= 156,
	UNITCONSTANTS_EnergyKilojoule	= 157,
	UNITCONSTANTS_EnergyWattSecond	= 158,
	UNITCONSTANTS_EnergyWattHour	= 159,
	UNITCONSTANTS_EnergyKilowattHour	= 160,
	UNITCONSTANTS_EnergyInchPoundForce	= 161,
	UNITCONSTANTS_EnergyFootPoundForce	= 162,
	UNITCONSTANTS_EnergyBtu	= 163,
	UNITCONSTANTS_EnergyErg	= 164,
	UNITCONSTANTS_EnergyElectronVolt	= 165,
	UNITCONSTANTS_EntropyJoulePerKelvin	= 166,
	UNITCONSTANTS_FilmCoefficientWattPerSqrMeterKelvin	= 167,
	UNITCONSTANTS_FilmCoefficientBtuPerHourSqrFootFahrenheit	= 168,
	UNITCONSTANTS_FilmCoefficientFootPoundPerSqrFootFahrenheit	= 169,
	UNITCONSTANTS_FilmCoefficientInchPoundPerSqrInchFahrenheit	= 170,
	UNITCONSTANTS_ForceNewton	= 171,
	UNITCONSTANTS_ForceNanonewton	= 172,
	UNITCONSTANTS_ForceMillinewton	= 173,
	UNITCONSTANTS_ForceKilonewton	= 174,
	UNITCONSTANTS_ForcePoundForce	= 175,
	UNITCONSTANTS_ForceDyne	= 176,
	UNITCONSTANTS_ForceKip	= 177,
	UNITCONSTANTS_ForcePerAreaPascal	= 178,
	UNITCONSTANTS_ForcePerAreaMillipascal	= 179,
	UNITCONSTANTS_ForcePerAreaKilopascal	= 180,
	UNITCONSTANTS_ForcePerAreaMegapascal	= 181,
	UNITCONSTANTS_ForcePerAreaPoundForcePerSqrInch	= 182,
	UNITCONSTANTS_ForcePerAreaKipPerSqrInch	= 183,
	UNITCONSTANTS_ForcePerAreaPoundForcePerSqrFoot	= 184,
	UNITCONSTANTS_ForcePerAreaKipPerSqrFoot	= 185,
	UNITCONSTANTS_ForcePerAreaBar	= 186,
	UNITCONSTANTS_ForcePerAreaMillibar	= 187,
	UNITCONSTANTS_ForcePerAreaAtmosphere	= 188,
	UNITCONSTANTS_ForcePerDistanceNewtonPerMeter	= 189,
	UNITCONSTANTS_ForcePerDistanceNewtonPerMillimeter	= 190,
	UNITCONSTANTS_ForcePerDistanceNewtonPerCentimeter	= 191,
	UNITCONSTANTS_ForcePerDistanceKilonewtonPerMeter	= 192,
	UNITCONSTANTS_ForcePerDistancePoundForcePerInch	= 193,
	UNITCONSTANTS_ForcePerDistancePoundForcePerFoot	= 194,
	UNITCONSTANTS_ForcePerDistanceKipPerInch	= 195,
	UNITCONSTANTS_ForcePerDistanceKipPerFoot	= 196,
	UNITCONSTANTS_ForcePerDistanceDynePerMeter	= 197,
	UNITCONSTANTS_ForcePerDistanceDynePerMillimeter	= 198,
	UNITCONSTANTS_FrequencyPerSecond	= 199,
	UNITCONSTANTS_FrequencyPerMinute	= 200,
	UNITCONSTANTS_FrequencyPerHour	= 201,
	UNITCONSTANTS_HeatCapacityJoulePerKilogramKelvin	= 202,
	UNITCONSTANTS_HeatCapacityBtuPerPoundMassFahrenheit	= 203,
	UNITCONSTANTS_HeatFluxPerAreaWattPerSqrMeter	= 204,
	UNITCONSTANTS_HeatFluxPerAreaKilowattPerSqrMeter	= 205,
	UNITCONSTANTS_HeatFluxPerAreaInchPoundForcePerSecondSqrInch	= 206,
	UNITCONSTANTS_HeatFluxPerAreaFootPoundForcePerSecondSqrFoot	= 207,
	UNITCONSTANTS_HeatFluxPerAreaBtuPerHourSqrFoot	= 208,
	UNITCONSTANTS_HeatFluxPerAreaHorsepowerPerSqrFoot	= 209,
	UNITCONSTANTS_HeatFluxPerDistanceWattPerMeter	= 210,
	UNITCONSTANTS_HeatFluxPerDistanceKilowattPerMeter	= 211,
	UNITCONSTANTS_HeatFluxPerDistanceMicrowattPerMeter	= 212,
	UNITCONSTANTS_HeatFluxPerDistanceMicrowattPerMillimeter	= 213,
	UNITCONSTANTS_HeatFluxPerDistanceInchPoundForcePerSecondInch	= 214,
	UNITCONSTANTS_HeatFluxPerDistanceBtuPerHourFoot	= 215,
	UNITCONSTANTS_HeatFluxPerDistanceHorsepowerPerFoot	= 216,
	UNITCONSTANTS_HeatSourceWattPerCubicMeter	= 217,
	UNITCONSTANTS_HeatSourceKilowattPerCubicMeter	= 218,
	UNITCONSTANTS_HeatSourceInchPoundForcePerSecondCubicInch	= 219,
	UNITCONSTANTS_HeatSourceFootPoundForcePerSecondCubicFoot	= 220,
	UNITCONSTANTS_HeatSourceBtuPerHourCubicFoot	= 221,
	UNITCONSTANTS_HeatSourceHorsepowerPerCubicFoot	= 222,
	UNITCONSTANTS_IlluminanceLux	= 223,
	UNITCONSTANTS_LinearAccelerationMeterPerSqrSecond	= 224,
	UNITCONSTANTS_LinearAccelerationKilometerPerSqrSecond	= 225,
	UNITCONSTANTS_LinearAccelerationMillimeterPerSqrSecond	= 226,
	UNITCONSTANTS_LinearAccelerationCentimeterPerSqrSecond	= 227,
	UNITCONSTANTS_LinearAccelerationInchPerSqrSecond	= 228,
	UNITCONSTANTS_LinearAccelerationFootPerSqrSecond	= 229,
	UNITCONSTANTS_LinearAccelerationMilePerSqrSecond	= 230,
	UNITCONSTANTS_LinearAccelerationMilePerSqrHour	= 231,
	UNITCONSTANTS_LinearAccelerationKilometerPerSqrHour	= 232,
	UNITCONSTANTS_LinearPerAngularMeterPerRadian	= 233,
	UNITCONSTANTS_LinearPerAngularMeterPerRevolution	= 234,
	UNITCONSTANTS_LinearPerAngularMillimeterPerRevolution	= 235,
	UNITCONSTANTS_LinearPerAngularInchPerRevolution	= 236,
	UNITCONSTANTS_LinearPerAngularFootPerRevolution	= 237,
	UNITCONSTANTS_LinearVelocityMeterPerSecond	= 238,
	UNITCONSTANTS_LinearVelocityMillimeterPerSecond	= 239,
	UNITCONSTANTS_LinearVelocityCentimeterPerSecond	= 240,
	UNITCONSTANTS_LinearVelocityKilometerPerSecond	= 241,
	UNITCONSTANTS_LinearVelocityKilometerPerHour	= 242,
	UNITCONSTANTS_LinearVelocityInchPerSecond	= 243,
	UNITCONSTANTS_LinearVelocityFootPerSecond	= 244,
	UNITCONSTANTS_LinearVelocityMilePerSecond	= 245,
	UNITCONSTANTS_LinearVelocityMilePerHour	= 246,
	UNITCONSTANTS_LuminousFluxLumen	= 247,
	UNITCONSTANTS_MagneticFieldStrengthAmperePerMeter	= 248,
	UNITCONSTANTS_MagneticFluxWeber	= 249,
	UNITCONSTANTS_MagneticFluxDensityTesla	= 250,
	UNITCONSTANTS_MassFlowRateKilogramPerSecond	= 251,
	UNITCONSTANTS_MassFlowRateGramPerSecond	= 252,
	UNITCONSTANTS_MassFlowRateMegagramPerSecond	= 253,
	UNITCONSTANTS_MassFlowRatePoundMassPerSecond	= 254,
	UNITCONSTANTS_MassFlowRateSlugPerSecond	= 255,
	UNITCONSTANTS_MassFlowRateSlinchPerSecond	= 256,
	UNITCONSTANTS_MassMomentOfInertiaKilogramSqrMeter	= 257,
	UNITCONSTANTS_MassMomentOfInertiaKilogramSqrMillimeter	= 258,
	UNITCONSTANTS_MassMomentOfInertiaGramSqrMillimeter	= 259,
	UNITCONSTANTS_MassMomentOfInertiaGramSqrCentimeter	= 260,
	UNITCONSTANTS_MassMomentOfInertiaSlugSqrFoot	= 261,
	UNITCONSTANTS_MassMomentOfInertiaSlugSqrInch	= 262,
	UNITCONSTANTS_MassMomentOfInertiaSlinchSqrInch	= 263,
	UNITCONSTANTS_MassMomentOfInertiaPoundMassSqrInch	= 264,
	UNITCONSTANTS_MassMomentOfInertiaPoundMassSqrFoot	= 265,
	UNITCONSTANTS_MassPerAreaKilogramPerSqrMeter	= 266,
	UNITCONSTANTS_MassPerAreaKilogramPerSqrMillimeter	= 267,
	UNITCONSTANTS_MassPerAreaGramPerSqrMillimeter	= 268,
	UNITCONSTANTS_MassPerAreaGramPerSqrCentimeter	= 269,
	UNITCONSTANTS_MassPerAreaSlugPerSqrInch	= 270,
	UNITCONSTANTS_MassPerAreaSlugPerSqrFoot	= 271,
	UNITCONSTANTS_MassPerAreaSlinchPerSqrInch	= 272,
	UNITCONSTANTS_MassPerAreaPoundMassPerSqrInch	= 273,
	UNITCONSTANTS_MassPerAreaPoundMassPerSqrFoot	= 274,
	UNITCONSTANTS_MassPerLengthKilogramPerMeter	= 275,
	UNITCONSTANTS_MassPerLengthKilogramPerMillimeter	= 276,
	UNITCONSTANTS_MassPerLengthGramPerMillimeter	= 277,
	UNITCONSTANTS_MassPerLengthGramPerCentimeter	= 278,
	UNITCONSTANTS_MassPerLengthSlugPerInch	= 279,
	UNITCONSTANTS_MassPerLengthSlugPerFoot	= 280,
	UNITCONSTANTS_MassPerLengthSlinchPerInch	= 281,
	UNITCONSTANTS_MassPerLengthPoundMassPerInch	= 282,
	UNITCONSTANTS_MassPerLengthPoundMassPerFoot	= 283,
	UNITCONSTANTS_MomentumKilogramMeterPerSecond	= 284,
	UNITCONSTANTS_PerDistancePerMeter	= 285,
	UNITCONSTANTS_PerDistancePerNanometer	= 286,
	UNITCONSTANTS_PerDistancePerMillimeter	= 287,
	UNITCONSTANTS_PerDistancePerCentimeter	= 288,
	UNITCONSTANTS_PerDistancePerKilometer	= 289,
	UNITCONSTANTS_PerDistancePerInch	= 290,
	UNITCONSTANTS_PerDistancePerFoot	= 291,
	UNITCONSTANTS_PerDistancePerYard	= 292,
	UNITCONSTANTS_PerDistancePerMile	= 293,
	UNITCONSTANTS_PerDistancePerTenth	= 294,
	UNITCONSTANTS_PerDistancePerHundredth	= 295,
	UNITCONSTANTS_PerDistancePerMil	= 296,
	UNITCONSTANTS_PowerWatt	= 297,
	UNITCONSTANTS_PowerKilowatt	= 298,
	UNITCONSTANTS_PowerMicrowatt	= 299,
	UNITCONSTANTS_PowerInchPoundForcePerSecond	= 300,
	UNITCONSTANTS_PowerFootPoundForcePerSecond	= 301,
	UNITCONSTANTS_PowerBtuPerHour	= 302,
	UNITCONSTANTS_PowerHorsepower	= 303,
	UNITCONSTANTS_QuantityOfElectricityCoulomb	= 304,
	UNITCONSTANTS_RadiantIntensityWattPerSteradian	= 305,
	UNITCONSTANTS_RotationalStiffnessNewtonMeterPerRadian	= 306,
	UNITCONSTANTS_RotationalStiffnessNewtonMeterPerDegree	= 307,
	UNITCONSTANTS_RotationalStiffnessNewtonMillimeterPerRadian	= 308,
	UNITCONSTANTS_RotationalStiffnessNewtonMillimeterPerDegree	= 309,
	UNITCONSTANTS_RotationalStiffnessKilonewtonMeterPerRadian	= 310,
	UNITCONSTANTS_RotationalStiffnessKilonewtonMeterPerDegree	= 311,
	UNITCONSTANTS_RotationalStiffnessPoundForceInchPerRadian	= 312,
	UNITCONSTANTS_RotationalStiffnessPoundForceInchPerDegree	= 313,
	UNITCONSTANTS_RotationalStiffnessPoundForceFootPerRadian	= 314,
	UNITCONSTANTS_RotationalStiffnessPoundForceFootPerDegree	= 315,
	UNITCONSTANTS_SecondMomentOfAreaMeterToFourth	= 316,
	UNITCONSTANTS_SecondMomentOfAreaMillimeterToFourth	= 317,
	UNITCONSTANTS_SecondMomentOfAreaCentimeterToFourth	= 318,
	UNITCONSTANTS_SecondMomentOfAreaInchToFourth	= 319,
	UNITCONSTANTS_SecondMomentOfAreaFootToFourth	= 320,
	UNITCONSTANTS_ThermalConductivityWattPerMeterCelcius	= 321,
	UNITCONSTANTS_ThermalConductivityKilowattPerMeterCelcius	= 322,
	UNITCONSTANTS_ThermalConductivityBtuPerHourFahrenheit	= 323,
	UNITCONSTANTS_ThermalConductivityInchPoundForcePerSecondInchFahrenheit	= 324,
	UNITCONSTANTS_DynamicViscosityPascalSecond	= 325,
	UNITCONSTANTS_DynamicViscosityKilopascalSecond	= 326,
	UNITCONSTANTS_DynamicViscosityMegapascalSecond	= 327,
	UNITCONSTANTS_DynamicViscosityPoundForceSecondPerSqrInch	= 328,
	UNITCONSTANTS_KinematicViscositySqrMeterPerSecond	= 329,
	UNITCONSTANTS_KinematicViscositySqrMillimeterPerSecond	= 330,
	UNITCONSTANTS_KinematicViscositySqrCentimeterPerSecond	= 331,
	UNITCONSTANTS_KinematicViscositySqrInchPerSecond	= 332,
	UNITCONSTANTS_KinematicViscositySqrFootPerSecond	= 333,
	UNITCONSTANTS_VolumeCubicMeter	= 334,
	UNITCONSTANTS_VolumeCubicMillimeter	= 335,
	UNITCONSTANTS_VolumeLiter	= 336,
	UNITCONSTANTS_VolumeMilliliter	= 337,
	UNITCONSTANTS_VolumeCubicInch	= 338,
	UNITCONSTANTS_VolumeCubicFoot	= 339,
	UNITCONSTANTS_VolumeCubicYard	= 340,
	UNITCONSTANTS_VolumeGallon	= 341,
	UNITCONSTANTS_VolumeQuart	= 342,
	UNITCONSTANTS_VolumePint	= 343,
	UNITCONSTANTS_VolumeFluidOunce	= 344,
	UNITCONSTANTS_ScalarNull	= 346,
	UNITCONSTANTS_VolumeFlowRateCubicMeterPerSecond	= 347,
	UNITCONSTANTS_VolumeFlowRateCubicMillimeterPerSecond	= 348,
	UNITCONSTANTS_VolumeFlowRateLiterPerSecond	= 349,
	UNITCONSTANTS_VolumeFlowRateMilliliterPerSecond	= 350,
	UNITCONSTANTS_VolumeFlowRateCubicInchPerSecond	= 351,
	UNITCONSTANTS_VolumeFlowRateCubicFootPerSecond	= 352,
	UNITCONSTANTS_VolumeFlowRateCubicYardPerSecond	= 353,
	UNITCONSTANTS_VolumeFlowRateGallonPerSecond	= 354,
	UNITCONSTANTS_VolumeFlowRateGallonPerMinute	= 355,
	UNITCONSTANTS_ElectricalInductanceHenry	= 356,
	UNITCONSTANTS_AngleDegreeSymbol	= 357,
	UNITCONSTANTS_AngleMinuteSymbol	= 358,
	UNITCONSTANTS_AngleSecondSymbol	= 359,
	UNITCONSTANTS_DistanceFootSymbol	= 360,
	UNITCONSTANTS_DistanceInchSymbol	= 361,
	UNITCONSTANTS_AreaHectare	= 362,
	UNITCONSTANTS_ForcePerAreaNewtonPerSqrMillimeter	= 363,
	UNITCONSTANTS_DynamicViscosityPoise	= 364,
	UNITCONSTANTS_DynamicViscosityCentipoise	= 365,
	UNITCONSTANTS_VolumeCubicCentimeter	= 366,
	UNITCONSTANTS_AngleDegreesMinutesSeconds	= 65536,
	UNITCONSTANTS_AngleHPFormat	= 65537,
	UNITCONSTANTS_DistanceSurveyInchTwoCharacters	= 65538,
	UNITCONSTANTS_DistanceSurveyKilofootTwoCharacters	= 65539,
	UNITCONSTANTS_DistanceSurveyFootTwoCharacters	= 65540,
	UNITCONSTANTS_DistanceNauticalMile	= 65541,
	UNITCONSTANTS_DistanceKilofoot	= 65542,
	UNITCONSTANTS_DistanceSurveyInch	= 65543,
	UNITCONSTANTS_DistanceSurveyFoot	= 65544,
	UNITCONSTANTS_DistanceSurveyKilofoot	= 65545,
	UNITCONSTANTS_AreaDeciare	= 65546,
	UNITCONSTANTS_AreaAres	= 65547,
	UNITCONSTANTS_AreaCentare	= 65548,
	UNITCONSTANTS_AreaSquareRod	= 65549,
	UNITCONSTANTS_AreaPerch	= 65550,
	UNITCONSTANTS_AreaSquareChain	= 65551,
	UNITCONSTANTS_AreaSquareLink	= 65552,
	UNITCONSTANTS_DistanceDecimeter	= 65553,
	UNITCONSTANTS_AreaHektar	= 65554,
	UNITCONSTANTS_AreaSquareDecimeter	= 65555
    } 	UNITCONSTANTS;

#endif // _UNITCONSTANTS_DEFINED


extern RPC_IF_HANDLE __MIDL_itf_StatistApp_0271_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_StatistApp_0271_v0_0_s_ifspec;

#ifndef __ITRiASUnitsOfMeasure_INTERFACE_DEFINED__
#define __ITRiASUnitsOfMeasure_INTERFACE_DEFINED__

/* interface ITRiASUnitsOfMeasure */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASUnitsOfMeasure;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A2497E88-EF70-11D2-9BE5-5AB320524153")
    ITRiASUnitsOfMeasure : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetUnitIDs( 
            /* [in] */ UNITTYPECONSTANTS UnitType,
            /* [retval][out] */ ITRiASUnitIDs **UnitIDs) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetUnitID( 
            /* [in] */ UNITTYPECONSTANTS UnitType,
            /* [in] */ BSTR UnitName,
            /* [in] */ VARIANT_BOOL CaseFlag,
            /* [retval][out] */ LONG *pUnit) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetUnitName( 
            /* [in] */ LONG UnitId,
            /* [retval][out] */ BSTR *UnitName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCompBaseUnit( 
            /* [in] */ UNITTYPECONSTANTS UnitType,
            /* [retval][out] */ LONG *Unit) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConvertUnitToUnit( 
            /* [in] */ UNITTYPECONSTANTS UnitType,
            /* [in] */ double ValueIn,
            /* [in] */ LONG UnitIDFrom,
            /* [in] */ LONG UnitIDTo,
            /* [retval][out] */ double *ValueOut) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddUserDefinedUnit( 
            /* [in] */ UNITTYPECONSTANTS UnitType,
            /* [in] */ BSTR UnitName,
            /* [in] */ double NumCompBaseUnits,
            /* [in] */ double UnitOffset,
            /* [in] */ BSTR AppName,
            /* [in] */ BSTR AppVersion,
            /* [retval][out] */ LONG *pUnit) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteUserDefinedUnit( 
            /* [in] */ UNITTYPECONSTANTS UnitType,
            /* [in] */ LONG UnitID,
            /* [in] */ BSTR AppName,
            /* [in] */ BSTR AppVersionStr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadUserDefinedUnits( 
            /* [in] */ BSTR AppName,
            /* [in] */ BSTR AppVersionStr) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASUnitsOfMeasureVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASUnitsOfMeasure * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASUnitsOfMeasure * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASUnitsOfMeasure * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASUnitsOfMeasure * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASUnitsOfMeasure * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASUnitsOfMeasure * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASUnitsOfMeasure * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetUnitIDs )( 
            ITRiASUnitsOfMeasure * This,
            /* [in] */ UNITTYPECONSTANTS UnitType,
            /* [retval][out] */ ITRiASUnitIDs **UnitIDs);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetUnitID )( 
            ITRiASUnitsOfMeasure * This,
            /* [in] */ UNITTYPECONSTANTS UnitType,
            /* [in] */ BSTR UnitName,
            /* [in] */ VARIANT_BOOL CaseFlag,
            /* [retval][out] */ LONG *pUnit);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetUnitName )( 
            ITRiASUnitsOfMeasure * This,
            /* [in] */ LONG UnitId,
            /* [retval][out] */ BSTR *UnitName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCompBaseUnit )( 
            ITRiASUnitsOfMeasure * This,
            /* [in] */ UNITTYPECONSTANTS UnitType,
            /* [retval][out] */ LONG *Unit);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ConvertUnitToUnit )( 
            ITRiASUnitsOfMeasure * This,
            /* [in] */ UNITTYPECONSTANTS UnitType,
            /* [in] */ double ValueIn,
            /* [in] */ LONG UnitIDFrom,
            /* [in] */ LONG UnitIDTo,
            /* [retval][out] */ double *ValueOut);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddUserDefinedUnit )( 
            ITRiASUnitsOfMeasure * This,
            /* [in] */ UNITTYPECONSTANTS UnitType,
            /* [in] */ BSTR UnitName,
            /* [in] */ double NumCompBaseUnits,
            /* [in] */ double UnitOffset,
            /* [in] */ BSTR AppName,
            /* [in] */ BSTR AppVersion,
            /* [retval][out] */ LONG *pUnit);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteUserDefinedUnit )( 
            ITRiASUnitsOfMeasure * This,
            /* [in] */ UNITTYPECONSTANTS UnitType,
            /* [in] */ LONG UnitID,
            /* [in] */ BSTR AppName,
            /* [in] */ BSTR AppVersionStr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadUserDefinedUnits )( 
            ITRiASUnitsOfMeasure * This,
            /* [in] */ BSTR AppName,
            /* [in] */ BSTR AppVersionStr);
        
        END_INTERFACE
    } ITRiASUnitsOfMeasureVtbl;

    interface ITRiASUnitsOfMeasure
    {
        CONST_VTBL struct ITRiASUnitsOfMeasureVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASUnitsOfMeasure_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASUnitsOfMeasure_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASUnitsOfMeasure_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASUnitsOfMeasure_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASUnitsOfMeasure_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASUnitsOfMeasure_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASUnitsOfMeasure_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASUnitsOfMeasure_GetUnitIDs(This,UnitType,UnitIDs)	\
    (This)->lpVtbl -> GetUnitIDs(This,UnitType,UnitIDs)

#define ITRiASUnitsOfMeasure_GetUnitID(This,UnitType,UnitName,CaseFlag,pUnit)	\
    (This)->lpVtbl -> GetUnitID(This,UnitType,UnitName,CaseFlag,pUnit)

#define ITRiASUnitsOfMeasure_GetUnitName(This,UnitId,UnitName)	\
    (This)->lpVtbl -> GetUnitName(This,UnitId,UnitName)

#define ITRiASUnitsOfMeasure_GetCompBaseUnit(This,UnitType,Unit)	\
    (This)->lpVtbl -> GetCompBaseUnit(This,UnitType,Unit)

#define ITRiASUnitsOfMeasure_ConvertUnitToUnit(This,UnitType,ValueIn,UnitIDFrom,UnitIDTo,ValueOut)	\
    (This)->lpVtbl -> ConvertUnitToUnit(This,UnitType,ValueIn,UnitIDFrom,UnitIDTo,ValueOut)

#define ITRiASUnitsOfMeasure_AddUserDefinedUnit(This,UnitType,UnitName,NumCompBaseUnits,UnitOffset,AppName,AppVersion,pUnit)	\
    (This)->lpVtbl -> AddUserDefinedUnit(This,UnitType,UnitName,NumCompBaseUnits,UnitOffset,AppName,AppVersion,pUnit)

#define ITRiASUnitsOfMeasure_DeleteUserDefinedUnit(This,UnitType,UnitID,AppName,AppVersionStr)	\
    (This)->lpVtbl -> DeleteUserDefinedUnit(This,UnitType,UnitID,AppName,AppVersionStr)

#define ITRiASUnitsOfMeasure_LoadUserDefinedUnits(This,AppName,AppVersionStr)	\
    (This)->lpVtbl -> LoadUserDefinedUnits(This,AppName,AppVersionStr)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASUnitsOfMeasure_GetUnitIDs_Proxy( 
    ITRiASUnitsOfMeasure * This,
    /* [in] */ UNITTYPECONSTANTS UnitType,
    /* [retval][out] */ ITRiASUnitIDs **UnitIDs);


void __RPC_STUB ITRiASUnitsOfMeasure_GetUnitIDs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASUnitsOfMeasure_GetUnitID_Proxy( 
    ITRiASUnitsOfMeasure * This,
    /* [in] */ UNITTYPECONSTANTS UnitType,
    /* [in] */ BSTR UnitName,
    /* [in] */ VARIANT_BOOL CaseFlag,
    /* [retval][out] */ LONG *pUnit);


void __RPC_STUB ITRiASUnitsOfMeasure_GetUnitID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASUnitsOfMeasure_GetUnitName_Proxy( 
    ITRiASUnitsOfMeasure * This,
    /* [in] */ LONG UnitId,
    /* [retval][out] */ BSTR *UnitName);


void __RPC_STUB ITRiASUnitsOfMeasure_GetUnitName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASUnitsOfMeasure_GetCompBaseUnit_Proxy( 
    ITRiASUnitsOfMeasure * This,
    /* [in] */ UNITTYPECONSTANTS UnitType,
    /* [retval][out] */ LONG *Unit);


void __RPC_STUB ITRiASUnitsOfMeasure_GetCompBaseUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASUnitsOfMeasure_ConvertUnitToUnit_Proxy( 
    ITRiASUnitsOfMeasure * This,
    /* [in] */ UNITTYPECONSTANTS UnitType,
    /* [in] */ double ValueIn,
    /* [in] */ LONG UnitIDFrom,
    /* [in] */ LONG UnitIDTo,
    /* [retval][out] */ double *ValueOut);


void __RPC_STUB ITRiASUnitsOfMeasure_ConvertUnitToUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASUnitsOfMeasure_AddUserDefinedUnit_Proxy( 
    ITRiASUnitsOfMeasure * This,
    /* [in] */ UNITTYPECONSTANTS UnitType,
    /* [in] */ BSTR UnitName,
    /* [in] */ double NumCompBaseUnits,
    /* [in] */ double UnitOffset,
    /* [in] */ BSTR AppName,
    /* [in] */ BSTR AppVersion,
    /* [retval][out] */ LONG *pUnit);


void __RPC_STUB ITRiASUnitsOfMeasure_AddUserDefinedUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASUnitsOfMeasure_DeleteUserDefinedUnit_Proxy( 
    ITRiASUnitsOfMeasure * This,
    /* [in] */ UNITTYPECONSTANTS UnitType,
    /* [in] */ LONG UnitID,
    /* [in] */ BSTR AppName,
    /* [in] */ BSTR AppVersionStr);


void __RPC_STUB ITRiASUnitsOfMeasure_DeleteUserDefinedUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASUnitsOfMeasure_LoadUserDefinedUnits_Proxy( 
    ITRiASUnitsOfMeasure * This,
    /* [in] */ BSTR AppName,
    /* [in] */ BSTR AppVersionStr);


void __RPC_STUB ITRiASUnitsOfMeasure_LoadUserDefinedUnits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASUnitsOfMeasure_INTERFACE_DEFINED__ */


#ifndef __ITRiASUnitIDs_INTERFACE_DEFINED__
#define __ITRiASUnitIDs_INTERFACE_DEFINED__

/* interface ITRiASUnitIDs */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASUnitIDs;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A2497E98-EF70-11D2-9BE5-5AB320524153")
    ITRiASUnitIDs : public IStaticCollection
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ITRiASUnitIDsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASUnitIDs * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASUnitIDs * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASUnitIDs * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASUnitIDs * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASUnitIDs * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASUnitIDs * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASUnitIDs * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITRiASUnitIDs * This,
            /* [retval][out] */ ULONG *c);
        
        /* [restricted][id] */ HRESULT ( __stdcall *_NewEnum )( 
            ITRiASUnitIDs * This,
            /* [retval][out] */ IUnknown **ppunk);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            ITRiASUnitIDs * This);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ITRiASUnitIDs * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ VARIANT *retval);
        
        END_INTERFACE
    } ITRiASUnitIDsVtbl;

    interface ITRiASUnitIDs
    {
        CONST_VTBL struct ITRiASUnitIDsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASUnitIDs_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASUnitIDs_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASUnitIDs_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASUnitIDs_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASUnitIDs_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASUnitIDs_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASUnitIDs_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASUnitIDs_get_Count(This,c)	\
    (This)->lpVtbl -> get_Count(This,c)

#define ITRiASUnitIDs__NewEnum(This,ppunk)	\
    (This)->lpVtbl -> _NewEnum(This,ppunk)

#define ITRiASUnitIDs_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define ITRiASUnitIDs_get_Item(This,Index,retval)	\
    (This)->lpVtbl -> get_Item(This,Index,retval)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITRiASUnitIDs_INTERFACE_DEFINED__ */


#ifndef __IPopupTree_INTERFACE_DEFINED__
#define __IPopupTree_INTERFACE_DEFINED__

/* interface IPopupTree */
/* [unique][helpstring][dual][uuid][object] */ 

typedef /* [v1_enum][public] */ 
enum _tagPOPUPTREEMODE
    {	POPUPTREEMODE_UNKNOWN	= 0,
	POPUPTREEMODE_SHOWOBJPROPS	= 1,
	POPUPTREEMODE_SHOWSTATFUNCS	= 2
    } 	POPUPTREEMODE;


EXTERN_C const IID IID_IPopupTree;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("328F04FD-C376-47C8-BAB2-3427AC1D4331")
    IPopupTree : public IDispatch
    {
    public:
        virtual /* [id][requestedit][bindable][propputref] */ HRESULT STDMETHODCALLTYPE putref_Font( 
            /* [in] */ IFontDisp *pFont) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_Font( 
            /* [in] */ IFontDisp *pFont) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_Font( 
            /* [retval][out] */ IFontDisp **ppFont) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_TabStop( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_TabStop( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_Caption( 
            /* [in] */ BSTR strCaption) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_Caption( 
            /* [retval][out] */ BSTR *pstrCaption) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_Valid( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_Valid( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_ButtonTooltipText( 
            /* [in] */ BSTR ToolTipText) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_ButtonTooltipText( 
            /* [retval][out] */ BSTR *ToolTipText) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_PopupTreeMode( 
            /* [in] */ POPUPTREEMODE Mode) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_PopupTreeMode( 
            /* [retval][out] */ POPUPTREEMODE *Mode) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_HasSelection( 
            /* [retval][out] */ VARIANT_BOOL *HasSel) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Selection( 
            /* [in] */ REFIID riid,
            /* [retval][out][iid_is] */ IUnknown **Selection) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetSelection( 
            /* [in] */ BSTR Selection) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPopupTreeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPopupTree * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPopupTree * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPopupTree * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPopupTree * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPopupTree * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPopupTree * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPopupTree * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][requestedit][bindable][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Font )( 
            IPopupTree * This,
            /* [in] */ IFontDisp *pFont);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Font )( 
            IPopupTree * This,
            /* [in] */ IFontDisp *pFont);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Font )( 
            IPopupTree * This,
            /* [retval][out] */ IFontDisp **ppFont);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Enabled )( 
            IPopupTree * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Enabled )( 
            IPopupTree * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TabStop )( 
            IPopupTree * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TabStop )( 
            IPopupTree * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Caption )( 
            IPopupTree * This,
            /* [in] */ BSTR strCaption);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Caption )( 
            IPopupTree * This,
            /* [retval][out] */ BSTR *pstrCaption);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Valid )( 
            IPopupTree * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Valid )( 
            IPopupTree * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ButtonTooltipText )( 
            IPopupTree * This,
            /* [in] */ BSTR ToolTipText);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ButtonTooltipText )( 
            IPopupTree * This,
            /* [retval][out] */ BSTR *ToolTipText);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PopupTreeMode )( 
            IPopupTree * This,
            /* [in] */ POPUPTREEMODE Mode);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PopupTreeMode )( 
            IPopupTree * This,
            /* [retval][out] */ POPUPTREEMODE *Mode);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasSelection )( 
            IPopupTree * This,
            /* [retval][out] */ VARIANT_BOOL *HasSel);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Selection )( 
            IPopupTree * This,
            /* [in] */ REFIID riid,
            /* [retval][out][iid_is] */ IUnknown **Selection);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetSelection )( 
            IPopupTree * This,
            /* [in] */ BSTR Selection);
        
        END_INTERFACE
    } IPopupTreeVtbl;

    interface IPopupTree
    {
        CONST_VTBL struct IPopupTreeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPopupTree_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPopupTree_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPopupTree_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPopupTree_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPopupTree_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPopupTree_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPopupTree_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPopupTree_putref_Font(This,pFont)	\
    (This)->lpVtbl -> putref_Font(This,pFont)

#define IPopupTree_put_Font(This,pFont)	\
    (This)->lpVtbl -> put_Font(This,pFont)

#define IPopupTree_get_Font(This,ppFont)	\
    (This)->lpVtbl -> get_Font(This,ppFont)

#define IPopupTree_put_Enabled(This,vbool)	\
    (This)->lpVtbl -> put_Enabled(This,vbool)

#define IPopupTree_get_Enabled(This,pbool)	\
    (This)->lpVtbl -> get_Enabled(This,pbool)

#define IPopupTree_put_TabStop(This,vbool)	\
    (This)->lpVtbl -> put_TabStop(This,vbool)

#define IPopupTree_get_TabStop(This,pbool)	\
    (This)->lpVtbl -> get_TabStop(This,pbool)

#define IPopupTree_put_Caption(This,strCaption)	\
    (This)->lpVtbl -> put_Caption(This,strCaption)

#define IPopupTree_get_Caption(This,pstrCaption)	\
    (This)->lpVtbl -> get_Caption(This,pstrCaption)

#define IPopupTree_put_Valid(This,vbool)	\
    (This)->lpVtbl -> put_Valid(This,vbool)

#define IPopupTree_get_Valid(This,pbool)	\
    (This)->lpVtbl -> get_Valid(This,pbool)

#define IPopupTree_put_ButtonTooltipText(This,ToolTipText)	\
    (This)->lpVtbl -> put_ButtonTooltipText(This,ToolTipText)

#define IPopupTree_get_ButtonTooltipText(This,ToolTipText)	\
    (This)->lpVtbl -> get_ButtonTooltipText(This,ToolTipText)

#define IPopupTree_put_PopupTreeMode(This,Mode)	\
    (This)->lpVtbl -> put_PopupTreeMode(This,Mode)

#define IPopupTree_get_PopupTreeMode(This,Mode)	\
    (This)->lpVtbl -> get_PopupTreeMode(This,Mode)

#define IPopupTree_get_HasSelection(This,HasSel)	\
    (This)->lpVtbl -> get_HasSelection(This,HasSel)

#define IPopupTree_get_Selection(This,riid,Selection)	\
    (This)->lpVtbl -> get_Selection(This,riid,Selection)

#define IPopupTree_SetSelection(This,Selection)	\
    (This)->lpVtbl -> SetSelection(This,Selection)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][requestedit][bindable][propputref] */ HRESULT STDMETHODCALLTYPE IPopupTree_putref_Font_Proxy( 
    IPopupTree * This,
    /* [in] */ IFontDisp *pFont);


void __RPC_STUB IPopupTree_putref_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IPopupTree_put_Font_Proxy( 
    IPopupTree * This,
    /* [in] */ IFontDisp *pFont);


void __RPC_STUB IPopupTree_put_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IPopupTree_get_Font_Proxy( 
    IPopupTree * This,
    /* [retval][out] */ IFontDisp **ppFont);


void __RPC_STUB IPopupTree_get_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IPopupTree_put_Enabled_Proxy( 
    IPopupTree * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB IPopupTree_put_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IPopupTree_get_Enabled_Proxy( 
    IPopupTree * This,
    /* [retval][out] */ VARIANT_BOOL *pbool);


void __RPC_STUB IPopupTree_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IPopupTree_put_TabStop_Proxy( 
    IPopupTree * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB IPopupTree_put_TabStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IPopupTree_get_TabStop_Proxy( 
    IPopupTree * This,
    /* [retval][out] */ VARIANT_BOOL *pbool);


void __RPC_STUB IPopupTree_get_TabStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IPopupTree_put_Caption_Proxy( 
    IPopupTree * This,
    /* [in] */ BSTR strCaption);


void __RPC_STUB IPopupTree_put_Caption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IPopupTree_get_Caption_Proxy( 
    IPopupTree * This,
    /* [retval][out] */ BSTR *pstrCaption);


void __RPC_STUB IPopupTree_get_Caption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IPopupTree_put_Valid_Proxy( 
    IPopupTree * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB IPopupTree_put_Valid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IPopupTree_get_Valid_Proxy( 
    IPopupTree * This,
    /* [retval][out] */ VARIANT_BOOL *pbool);


void __RPC_STUB IPopupTree_get_Valid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IPopupTree_put_ButtonTooltipText_Proxy( 
    IPopupTree * This,
    /* [in] */ BSTR ToolTipText);


void __RPC_STUB IPopupTree_put_ButtonTooltipText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IPopupTree_get_ButtonTooltipText_Proxy( 
    IPopupTree * This,
    /* [retval][out] */ BSTR *ToolTipText);


void __RPC_STUB IPopupTree_get_ButtonTooltipText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IPopupTree_put_PopupTreeMode_Proxy( 
    IPopupTree * This,
    /* [in] */ POPUPTREEMODE Mode);


void __RPC_STUB IPopupTree_put_PopupTreeMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IPopupTree_get_PopupTreeMode_Proxy( 
    IPopupTree * This,
    /* [retval][out] */ POPUPTREEMODE *Mode);


void __RPC_STUB IPopupTree_get_PopupTreeMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPopupTree_get_HasSelection_Proxy( 
    IPopupTree * This,
    /* [retval][out] */ VARIANT_BOOL *HasSel);


void __RPC_STUB IPopupTree_get_HasSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IPopupTree_get_Selection_Proxy( 
    IPopupTree * This,
    /* [in] */ REFIID riid,
    /* [retval][out][iid_is] */ IUnknown **Selection);


void __RPC_STUB IPopupTree_get_Selection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPopupTree_SetSelection_Proxy( 
    IPopupTree * This,
    /* [in] */ BSTR Selection);


void __RPC_STUB IPopupTree_SetSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPopupTree_INTERFACE_DEFINED__ */


#ifndef __IProjectValuePageCtrl_INTERFACE_DEFINED__
#define __IProjectValuePageCtrl_INTERFACE_DEFINED__

/* interface IProjectValuePageCtrl */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IProjectValuePageCtrl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B3D935F5-3F95-4E5E-9BAF-3C13FE1CC010")
    IProjectValuePageCtrl : public IDispatch
    {
    public:
        virtual /* [id][propputref] */ HRESULT STDMETHODCALLTYPE putref_Font( 
            /* [in] */ IFontDisp *pFont) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Font( 
            /* [in] */ IFontDisp *pFont) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Font( 
            /* [retval][out] */ IFontDisp **ppFont) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_TabStop( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_TabStop( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_Valid( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_Valid( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IProjectValuePageCtrlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProjectValuePageCtrl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProjectValuePageCtrl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProjectValuePageCtrl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IProjectValuePageCtrl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IProjectValuePageCtrl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IProjectValuePageCtrl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IProjectValuePageCtrl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Font )( 
            IProjectValuePageCtrl * This,
            /* [in] */ IFontDisp *pFont);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Font )( 
            IProjectValuePageCtrl * This,
            /* [in] */ IFontDisp *pFont);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Font )( 
            IProjectValuePageCtrl * This,
            /* [retval][out] */ IFontDisp **ppFont);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Enabled )( 
            IProjectValuePageCtrl * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Enabled )( 
            IProjectValuePageCtrl * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TabStop )( 
            IProjectValuePageCtrl * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TabStop )( 
            IProjectValuePageCtrl * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Valid )( 
            IProjectValuePageCtrl * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Valid )( 
            IProjectValuePageCtrl * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        END_INTERFACE
    } IProjectValuePageCtrlVtbl;

    interface IProjectValuePageCtrl
    {
        CONST_VTBL struct IProjectValuePageCtrlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProjectValuePageCtrl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IProjectValuePageCtrl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IProjectValuePageCtrl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IProjectValuePageCtrl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IProjectValuePageCtrl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IProjectValuePageCtrl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IProjectValuePageCtrl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IProjectValuePageCtrl_putref_Font(This,pFont)	\
    (This)->lpVtbl -> putref_Font(This,pFont)

#define IProjectValuePageCtrl_put_Font(This,pFont)	\
    (This)->lpVtbl -> put_Font(This,pFont)

#define IProjectValuePageCtrl_get_Font(This,ppFont)	\
    (This)->lpVtbl -> get_Font(This,ppFont)

#define IProjectValuePageCtrl_put_Enabled(This,vbool)	\
    (This)->lpVtbl -> put_Enabled(This,vbool)

#define IProjectValuePageCtrl_get_Enabled(This,pbool)	\
    (This)->lpVtbl -> get_Enabled(This,pbool)

#define IProjectValuePageCtrl_put_TabStop(This,vbool)	\
    (This)->lpVtbl -> put_TabStop(This,vbool)

#define IProjectValuePageCtrl_get_TabStop(This,pbool)	\
    (This)->lpVtbl -> get_TabStop(This,pbool)

#define IProjectValuePageCtrl_put_Valid(This,vbool)	\
    (This)->lpVtbl -> put_Valid(This,vbool)

#define IProjectValuePageCtrl_get_Valid(This,pbool)	\
    (This)->lpVtbl -> get_Valid(This,pbool)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propputref] */ HRESULT STDMETHODCALLTYPE IProjectValuePageCtrl_putref_Font_Proxy( 
    IProjectValuePageCtrl * This,
    /* [in] */ IFontDisp *pFont);


void __RPC_STUB IProjectValuePageCtrl_putref_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IProjectValuePageCtrl_put_Font_Proxy( 
    IProjectValuePageCtrl * This,
    /* [in] */ IFontDisp *pFont);


void __RPC_STUB IProjectValuePageCtrl_put_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IProjectValuePageCtrl_get_Font_Proxy( 
    IProjectValuePageCtrl * This,
    /* [retval][out] */ IFontDisp **ppFont);


void __RPC_STUB IProjectValuePageCtrl_get_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IProjectValuePageCtrl_put_Enabled_Proxy( 
    IProjectValuePageCtrl * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB IProjectValuePageCtrl_put_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IProjectValuePageCtrl_get_Enabled_Proxy( 
    IProjectValuePageCtrl * This,
    /* [retval][out] */ VARIANT_BOOL *pbool);


void __RPC_STUB IProjectValuePageCtrl_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IProjectValuePageCtrl_put_TabStop_Proxy( 
    IProjectValuePageCtrl * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB IProjectValuePageCtrl_put_TabStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IProjectValuePageCtrl_get_TabStop_Proxy( 
    IProjectValuePageCtrl * This,
    /* [retval][out] */ VARIANT_BOOL *pbool);


void __RPC_STUB IProjectValuePageCtrl_get_TabStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IProjectValuePageCtrl_put_Valid_Proxy( 
    IProjectValuePageCtrl * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB IProjectValuePageCtrl_put_Valid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IProjectValuePageCtrl_get_Valid_Proxy( 
    IProjectValuePageCtrl * This,
    /* [retval][out] */ VARIANT_BOOL *pbool);


void __RPC_STUB IProjectValuePageCtrl_get_Valid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IProjectValuePageCtrl_INTERFACE_DEFINED__ */


#ifndef __ITRiASUsedUnits_INTERFACE_DEFINED__
#define __ITRiASUsedUnits_INTERFACE_DEFINED__

/* interface ITRiASUsedUnits */
/* [unique][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASUsedUnits;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("249B5720-57BE-45EB-B7E2-E78B24C819E8")
    ITRiASUsedUnits : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UnitOfLength( 
            /* [retval][out] */ UNITCONSTANTS *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UnitOfLength( 
            /* [in] */ UNITCONSTANTS newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UnitOfArea( 
            /* [retval][out] */ UNITCONSTANTS *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UnitOfArea( 
            /* [in] */ UNITCONSTANTS newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AppendUnits( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AppendUnits( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveUsedUnits( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RestoreUsedUnits( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASUsedUnitsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASUsedUnits * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASUsedUnits * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASUsedUnits * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASUsedUnits * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASUsedUnits * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASUsedUnits * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASUsedUnits * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UnitOfLength )( 
            ITRiASUsedUnits * This,
            /* [retval][out] */ UNITCONSTANTS *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UnitOfLength )( 
            ITRiASUsedUnits * This,
            /* [in] */ UNITCONSTANTS newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UnitOfArea )( 
            ITRiASUsedUnits * This,
            /* [retval][out] */ UNITCONSTANTS *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UnitOfArea )( 
            ITRiASUsedUnits * This,
            /* [in] */ UNITCONSTANTS newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AppendUnits )( 
            ITRiASUsedUnits * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AppendUnits )( 
            ITRiASUsedUnits * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveUsedUnits )( 
            ITRiASUsedUnits * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RestoreUsedUnits )( 
            ITRiASUsedUnits * This);
        
        END_INTERFACE
    } ITRiASUsedUnitsVtbl;

    interface ITRiASUsedUnits
    {
        CONST_VTBL struct ITRiASUsedUnitsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASUsedUnits_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASUsedUnits_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASUsedUnits_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASUsedUnits_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASUsedUnits_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASUsedUnits_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASUsedUnits_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASUsedUnits_get_UnitOfLength(This,pVal)	\
    (This)->lpVtbl -> get_UnitOfLength(This,pVal)

#define ITRiASUsedUnits_put_UnitOfLength(This,newVal)	\
    (This)->lpVtbl -> put_UnitOfLength(This,newVal)

#define ITRiASUsedUnits_get_UnitOfArea(This,pVal)	\
    (This)->lpVtbl -> get_UnitOfArea(This,pVal)

#define ITRiASUsedUnits_put_UnitOfArea(This,newVal)	\
    (This)->lpVtbl -> put_UnitOfArea(This,newVal)

#define ITRiASUsedUnits_get_AppendUnits(This,pVal)	\
    (This)->lpVtbl -> get_AppendUnits(This,pVal)

#define ITRiASUsedUnits_put_AppendUnits(This,newVal)	\
    (This)->lpVtbl -> put_AppendUnits(This,newVal)

#define ITRiASUsedUnits_SaveUsedUnits(This)	\
    (This)->lpVtbl -> SaveUsedUnits(This)

#define ITRiASUsedUnits_RestoreUsedUnits(This)	\
    (This)->lpVtbl -> RestoreUsedUnits(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASUsedUnits_get_UnitOfLength_Proxy( 
    ITRiASUsedUnits * This,
    /* [retval][out] */ UNITCONSTANTS *pVal);


void __RPC_STUB ITRiASUsedUnits_get_UnitOfLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASUsedUnits_put_UnitOfLength_Proxy( 
    ITRiASUsedUnits * This,
    /* [in] */ UNITCONSTANTS newVal);


void __RPC_STUB ITRiASUsedUnits_put_UnitOfLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASUsedUnits_get_UnitOfArea_Proxy( 
    ITRiASUsedUnits * This,
    /* [retval][out] */ UNITCONSTANTS *pVal);


void __RPC_STUB ITRiASUsedUnits_get_UnitOfArea_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASUsedUnits_put_UnitOfArea_Proxy( 
    ITRiASUsedUnits * This,
    /* [in] */ UNITCONSTANTS newVal);


void __RPC_STUB ITRiASUsedUnits_put_UnitOfArea_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASUsedUnits_get_AppendUnits_Proxy( 
    ITRiASUsedUnits * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASUsedUnits_get_AppendUnits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASUsedUnits_put_AppendUnits_Proxy( 
    ITRiASUsedUnits * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ITRiASUsedUnits_put_AppendUnits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASUsedUnits_SaveUsedUnits_Proxy( 
    ITRiASUsedUnits * This);


void __RPC_STUB ITRiASUsedUnits_SaveUsedUnits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASUsedUnits_RestoreUsedUnits_Proxy( 
    ITRiASUsedUnits * This);


void __RPC_STUB ITRiASUsedUnits_RestoreUsedUnits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASUsedUnits_INTERFACE_DEFINED__ */



#ifndef __TRiASStatistics_LIBRARY_DEFINED__
#define __TRiASStatistics_LIBRARY_DEFINED__

/* library TRiASStatistics */
/* [helpstring][lcid][version][uuid] */ 


enum STATIST_VERSIONS
    {	TYPELIB_STATIST_MAJOR_VERSION	= 1,
	TYPELIB_STATIST_MINOR_VERSION	= 0
    } ;


EXTERN_C const IID LIBID_TRiASStatistics;

#ifndef ___IPopupTreeEvents_DISPINTERFACE_DEFINED__
#define ___IPopupTreeEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IPopupTreeEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IPopupTreeEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("987F28F0-4C14-4F53-82E2-AB190D3FF3E9")
    _IPopupTreeEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IPopupTreeEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IPopupTreeEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IPopupTreeEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IPopupTreeEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IPopupTreeEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IPopupTreeEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IPopupTreeEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IPopupTreeEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IPopupTreeEventsVtbl;

    interface _IPopupTreeEvents
    {
        CONST_VTBL struct _IPopupTreeEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IPopupTreeEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IPopupTreeEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IPopupTreeEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IPopupTreeEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IPopupTreeEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IPopupTreeEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IPopupTreeEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IPopupTreeEvents_DISPINTERFACE_DEFINED__ */


#ifndef ___IProjectValuePageCtrlEvents_DISPINTERFACE_DEFINED__
#define ___IProjectValuePageCtrlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IProjectValuePageCtrlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IProjectValuePageCtrlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("F5157D32-88E7-4DC4-9466-D80B3B2318BC")
    _IProjectValuePageCtrlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IProjectValuePageCtrlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IProjectValuePageCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IProjectValuePageCtrlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IProjectValuePageCtrlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IProjectValuePageCtrlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IProjectValuePageCtrlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IProjectValuePageCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IProjectValuePageCtrlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IProjectValuePageCtrlEventsVtbl;

    interface _IProjectValuePageCtrlEvents
    {
        CONST_VTBL struct _IProjectValuePageCtrlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IProjectValuePageCtrlEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IProjectValuePageCtrlEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IProjectValuePageCtrlEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IProjectValuePageCtrlEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IProjectValuePageCtrlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IProjectValuePageCtrlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IProjectValuePageCtrlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IProjectValuePageCtrlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_TRiASSimpleStatistics;

#ifdef __cplusplus

class DECLSPEC_UUID("0CB3A699-E5CE-11D2-9BD9-586A20524153")
TRiASSimpleStatistics;
#endif

EXTERN_C const CLSID CLSID_TRiASStatistCount;

#ifdef __cplusplus

class DECLSPEC_UUID("84B653D0-006E-430F-A998-132EFBA3E780")
TRiASStatistCount;
#endif

EXTERN_C const CLSID CLSID_TRiASStatistCountNotNull;

#ifdef __cplusplus

class DECLSPEC_UUID("84B653DB-006E-430F-A998-132EFBA3E780")
TRiASStatistCountNotNull;
#endif

EXTERN_C const CLSID CLSID_TRiASStatistSum;

#ifdef __cplusplus

class DECLSPEC_UUID("84B653D1-006E-430F-A998-132EFBA3E780")
TRiASStatistSum;
#endif

EXTERN_C const CLSID CLSID_TRiASStatistArithmeticAverage;

#ifdef __cplusplus

class DECLSPEC_UUID("84B653D3-006E-430F-A998-132EFBA3E780")
TRiASStatistArithmeticAverage;
#endif

EXTERN_C const CLSID CLSID_TRiASStatistGeometricAverage;

#ifdef __cplusplus

class DECLSPEC_UUID("84B653D4-006E-430F-A998-132EFBA3E780")
TRiASStatistGeometricAverage;
#endif

EXTERN_C const CLSID CLSID_TRiASStatistMedian;

#ifdef __cplusplus

class DECLSPEC_UUID("84B653D5-006E-430F-A998-132EFBA3E780")
TRiASStatistMedian;
#endif

EXTERN_C const CLSID CLSID_TRiASStatistMinValue;

#ifdef __cplusplus

class DECLSPEC_UUID("84B653D6-006E-430F-A998-132EFBA3E780")
TRiASStatistMinValue;
#endif

EXTERN_C const CLSID CLSID_TRiASStatistMaxValue;

#ifdef __cplusplus

class DECLSPEC_UUID("84B653D7-006E-430F-A998-132EFBA3E780")
TRiASStatistMaxValue;
#endif

EXTERN_C const CLSID CLSID_TRiASStatistRange;

#ifdef __cplusplus

class DECLSPEC_UUID("84B653D8-006E-430F-A998-132EFBA3E780")
TRiASStatistRange;
#endif

EXTERN_C const CLSID CLSID_TRiASStatistStandardDeviation;

#ifdef __cplusplus

class DECLSPEC_UUID("84B653D9-006E-430F-A998-132EFBA3E780")
TRiASStatistStandardDeviation;
#endif

EXTERN_C const CLSID CLSID_TRiASStatistVariance;

#ifdef __cplusplus

class DECLSPEC_UUID("84B653DA-006E-430F-A998-132EFBA3E780")
TRiASStatistVariance;
#endif

EXTERN_C const CLSID CLSID_TRiASUnitsOfMeasure;

#ifdef __cplusplus

class DECLSPEC_UUID("A2497E89-EF70-11D2-9BE5-5AB320524153")
TRiASUnitsOfMeasure;
#endif

EXTERN_C const CLSID CLSID_TRiASUnitIDs;

#ifdef __cplusplus

class DECLSPEC_UUID("A2497E99-EF70-11D2-9BE5-5AB320524153")
TRiASUnitIDs;
#endif

EXTERN_C const CLSID CLSID_CountLinePoints;

#ifdef __cplusplus

class DECLSPEC_UUID("A19D28F7-F022-11D2-9BE5-5AB320524153")
CountLinePoints;
#endif

EXTERN_C const CLSID CLSID_ObjContainerXMin;

#ifdef __cplusplus

class DECLSPEC_UUID("3C1EC684-70AA-11D3-A897-00104BAF20DA")
ObjContainerXMin;
#endif

EXTERN_C const CLSID CLSID_ObjContainerXMax;

#ifdef __cplusplus

class DECLSPEC_UUID("3C1EC686-70AA-11D3-A897-00104BAF20DA")
ObjContainerXMax;
#endif

EXTERN_C const CLSID CLSID_ObjContainerYMin;

#ifdef __cplusplus

class DECLSPEC_UUID("3C1EC688-70AA-11D3-A897-00104BAF20DA")
ObjContainerYMin;
#endif

EXTERN_C const CLSID CLSID_ObjContainerYMax;

#ifdef __cplusplus

class DECLSPEC_UUID("3C1EC68A-70AA-11D3-A897-00104BAF20DA")
ObjContainerYMax;
#endif

EXTERN_C const CLSID CLSID_LengthOfLine;

#ifdef __cplusplus

class DECLSPEC_UUID("5F9A0AB4-64E2-11D3-A88C-00104BAF20DA")
LengthOfLine;
#endif

EXTERN_C const CLSID CLSID_CountAreaIsland;

#ifdef __cplusplus

class DECLSPEC_UUID("6C6BB024-65CA-11D3-A88D-00104BAF20DA")
CountAreaIsland;
#endif

EXTERN_C const CLSID CLSID_SimpleAreaFrame;

#ifdef __cplusplus

class DECLSPEC_UUID("6C6BB026-65CA-11D3-A88D-00104BAF20DA")
SimpleAreaFrame;
#endif

EXTERN_C const CLSID CLSID_FullAreaFrame;

#ifdef __cplusplus

class DECLSPEC_UUID("6C6BB028-65CA-11D3-A88D-00104BAF20DA")
FullAreaFrame;
#endif

EXTERN_C const CLSID CLSID_SuperficialContents;

#ifdef __cplusplus

class DECLSPEC_UUID("B2735E54-668B-11D3-A88E-00104BAF20DA")
SuperficialContents;
#endif

EXTERN_C const CLSID CLSID_SimpleAreaRadius;

#ifdef __cplusplus

class DECLSPEC_UUID("3C1EC68C-70AA-11D3-A897-00104BAF20DA")
SimpleAreaRadius;
#endif

EXTERN_C const CLSID CLSID_PointCoordX;

#ifdef __cplusplus

class DECLSPEC_UUID("1E5FBF6A-F236-11D2-9BEB-0ECD20524153")
PointCoordX;
#endif

EXTERN_C const CLSID CLSID_PointCoordY;

#ifdef __cplusplus

class DECLSPEC_UUID("1E5FBF6B-F236-11D2-9BEB-0ECD20524153")
PointCoordY;
#endif

EXTERN_C const CLSID CLSID_PointCentreCoordX;

#ifdef __cplusplus

class DECLSPEC_UUID("D49CF54A-6417-11D3-A88B-00104BAF20DA")
PointCentreCoordX;
#endif

EXTERN_C const CLSID CLSID_PointCentreCoordY;

#ifdef __cplusplus

class DECLSPEC_UUID("D49CF547-6417-11D3-A88B-00104BAF20DA")
PointCentreCoordY;
#endif

EXTERN_C const CLSID CLSID_StatisticObjectProperty;

#ifdef __cplusplus

class DECLSPEC_UUID("3357E0C8-3FBF-487A-80D6-7BDF7A7DAC57")
StatisticObjectProperty;
#endif

EXTERN_C const CLSID CLSID_MathOperationProperty;

#ifdef __cplusplus

class DECLSPEC_UUID("AE9FD8D1-4BC1-4236-AD70-EA35610617DA")
MathOperationProperty;
#endif

EXTERN_C const CLSID CLSID_SelectStatistValue;

#ifdef __cplusplus

class DECLSPEC_UUID("6C743068-F9FA-42FA-9C6F-DD72B5315BE4")
SelectStatistValue;
#endif

EXTERN_C const CLSID CLSID_MeshGeneration;

#ifdef __cplusplus

class DECLSPEC_UUID("BACFCBFF-5544-40BE-B43A-4A9C3C43DDE8")
MeshGeneration;
#endif

EXTERN_C const CLSID CLSID_UnitsOfMeasurePP;

#ifdef __cplusplus

class DECLSPEC_UUID("5A0BCA2C-13A9-4EF1-95D6-5753B29AE151")
UnitsOfMeasurePP;
#endif

EXTERN_C const CLSID CLSID_Statist;

#ifdef __cplusplus

class DECLSPEC_UUID("CF461D82-EE47-11D2-9BE4-BAF620524153")
Statist;
#endif

EXTERN_C const CLSID CLSID_PopupTree;

#ifdef __cplusplus

class DECLSPEC_UUID("09C04255-07E6-4EFD-8DED-F362DAE31E2B")
PopupTree;
#endif

EXTERN_C const CLSID CLSID_ProjectValuePageCtrl;

#ifdef __cplusplus

class DECLSPEC_UUID("F2B6B295-E366-4C3F-AA82-5C5668A2C057")
ProjectValuePageCtrl;
#endif

EXTERN_C const CLSID CLSID_ORWndValuePageCtrl;

#ifdef __cplusplus

class DECLSPEC_UUID("E92ECACF-E793-4736-9CAD-EBCC975326AC")
ORWndValuePageCtrl;
#endif

EXTERN_C const CLSID CLSID_ProjectValuesCallback;

#ifdef __cplusplus

class DECLSPEC_UUID("41F6DE64-8D87-43F2-B774-8EC07B66BF5E")
ProjectValuesCallback;
#endif

EXTERN_C const CLSID CLSID_StatistUIOwner;

#ifdef __cplusplus

class DECLSPEC_UUID("3FF6E1AD-62E0-4E48-820B-7C98B9DA0D20")
StatistUIOwner;
#endif

EXTERN_C const CLSID CLSID_ObjectCountInClass;

#ifdef __cplusplus

class DECLSPEC_UUID("BFDC4B6B-EB57-4C70-ADAF-4AB92F89DBB8")
ObjectCountInClass;
#endif

EXTERN_C const CLSID CLSID_ObjectCountInDatasource;

#ifdef __cplusplus

class DECLSPEC_UUID("DB218675-9E7F-403B-BE83-AD4C16E8FED0")
ObjectCountInDatasource;
#endif

EXTERN_C const CLSID CLSID_ObjectCountInORWndClass;

#ifdef __cplusplus

class DECLSPEC_UUID("76B7B7C1-696E-4FFA-997A-6D3BA8D9B373")
ObjectCountInORWndClass;
#endif

EXTERN_C const CLSID CLSID_ObjectCountInORWnd;

#ifdef __cplusplus

class DECLSPEC_UUID("B86C2D2C-308E-49DB-8447-23E38988CC98")
ObjectCountInORWnd;
#endif
#endif /* __TRiASStatistics_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  HWND_UserSize(     unsigned long *, unsigned long            , HWND * ); 
unsigned char * __RPC_USER  HWND_UserMarshal(  unsigned long *, unsigned char *, HWND * ); 
unsigned char * __RPC_USER  HWND_UserUnmarshal(unsigned long *, unsigned char *, HWND * ); 
void                      __RPC_USER  HWND_UserFree(     unsigned long *, HWND * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


