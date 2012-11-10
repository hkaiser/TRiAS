
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Fri Dec 03 14:25:58 2004
 */
/* Compiler settings for TRiASDB.idl:
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

#ifndef __TRiASDB_h__
#define __TRiASDB_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITRiASDBEngineEvents_FWD_DEFINED__
#define __ITRiASDBEngineEvents_FWD_DEFINED__
typedef interface ITRiASDBEngineEvents ITRiASDBEngineEvents;
#endif 	/* __ITRiASDBEngineEvents_FWD_DEFINED__ */


#ifndef __ITRiASProjectEvents_FWD_DEFINED__
#define __ITRiASProjectEvents_FWD_DEFINED__
typedef interface ITRiASProjectEvents ITRiASProjectEvents;
#endif 	/* __ITRiASProjectEvents_FWD_DEFINED__ */


#ifndef __ITRiASConnectionEvents_FWD_DEFINED__
#define __ITRiASConnectionEvents_FWD_DEFINED__
typedef interface ITRiASConnectionEvents ITRiASConnectionEvents;
#endif 	/* __ITRiASConnectionEvents_FWD_DEFINED__ */


#ifndef __ITRiASViewEvents_FWD_DEFINED__
#define __ITRiASViewEvents_FWD_DEFINED__
typedef interface ITRiASViewEvents ITRiASViewEvents;
#endif 	/* __ITRiASViewEvents_FWD_DEFINED__ */


#ifndef __ITRiASPropertyEvents_FWD_DEFINED__
#define __ITRiASPropertyEvents_FWD_DEFINED__
typedef interface ITRiASPropertyEvents ITRiASPropertyEvents;
#endif 	/* __ITRiASPropertyEvents_FWD_DEFINED__ */


#ifndef __ITRiASViewItemEvents_FWD_DEFINED__
#define __ITRiASViewItemEvents_FWD_DEFINED__
typedef interface ITRiASViewItemEvents ITRiASViewItemEvents;
#endif 	/* __ITRiASViewItemEvents_FWD_DEFINED__ */


#ifndef __ITRiASObjectsEvents_FWD_DEFINED__
#define __ITRiASObjectsEvents_FWD_DEFINED__
typedef interface ITRiASObjectsEvents ITRiASObjectsEvents;
#endif 	/* __ITRiASObjectsEvents_FWD_DEFINED__ */


#ifndef __ITRiASObjectEvents_FWD_DEFINED__
#define __ITRiASObjectEvents_FWD_DEFINED__
typedef interface ITRiASObjectEvents ITRiASObjectEvents;
#endif 	/* __ITRiASObjectEvents_FWD_DEFINED__ */


#ifndef __ITRiASFeatureEvents_FWD_DEFINED__
#define __ITRiASFeatureEvents_FWD_DEFINED__
typedef interface ITRiASFeatureEvents ITRiASFeatureEvents;
#endif 	/* __ITRiASFeatureEvents_FWD_DEFINED__ */


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


#ifndef __IParseRegularExpression_FWD_DEFINED__
#define __IParseRegularExpression_FWD_DEFINED__
typedef interface IParseRegularExpression IParseRegularExpression;
#endif 	/* __IParseRegularExpression_FWD_DEFINED__ */


#ifndef __IParseStringPairs_FWD_DEFINED__
#define __IParseStringPairs_FWD_DEFINED__
typedef interface IParseStringPairs IParseStringPairs;
#endif 	/* __IParseStringPairs_FWD_DEFINED__ */


#ifndef __IParseStringPairs2_FWD_DEFINED__
#define __IParseStringPairs2_FWD_DEFINED__
typedef interface IParseStringPairs2 IParseStringPairs2;
#endif 	/* __IParseStringPairs2_FWD_DEFINED__ */


#ifndef __IComposeStringPairs_FWD_DEFINED__
#define __IComposeStringPairs_FWD_DEFINED__
typedef interface IComposeStringPairs IComposeStringPairs;
#endif 	/* __IComposeStringPairs_FWD_DEFINED__ */


#ifndef __ITRiASDBEngine_FWD_DEFINED__
#define __ITRiASDBEngine_FWD_DEFINED__
typedef interface ITRiASDBEngine ITRiASDBEngine;
#endif 	/* __ITRiASDBEngine_FWD_DEFINED__ */


#ifndef __ITRiASBase_FWD_DEFINED__
#define __ITRiASBase_FWD_DEFINED__
typedef interface ITRiASBase ITRiASBase;
#endif 	/* __ITRiASBase_FWD_DEFINED__ */


#ifndef __ITRiASPropertyBase_FWD_DEFINED__
#define __ITRiASPropertyBase_FWD_DEFINED__
typedef interface ITRiASPropertyBase ITRiASPropertyBase;
#endif 	/* __ITRiASPropertyBase_FWD_DEFINED__ */


#ifndef __ITRiASProject_FWD_DEFINED__
#define __ITRiASProject_FWD_DEFINED__
typedef interface ITRiASProject ITRiASProject;
#endif 	/* __ITRiASProject_FWD_DEFINED__ */


#ifndef __ITRiASProjects_FWD_DEFINED__
#define __ITRiASProjects_FWD_DEFINED__
typedef interface ITRiASProjects ITRiASProjects;
#endif 	/* __ITRiASProjects_FWD_DEFINED__ */


#ifndef __ITRiASConnections_FWD_DEFINED__
#define __ITRiASConnections_FWD_DEFINED__
typedef interface ITRiASConnections ITRiASConnections;
#endif 	/* __ITRiASConnections_FWD_DEFINED__ */


#ifndef __ITRiASConnection_FWD_DEFINED__
#define __ITRiASConnection_FWD_DEFINED__
typedef interface ITRiASConnection ITRiASConnection;
#endif 	/* __ITRiASConnection_FWD_DEFINED__ */


#ifndef __ITRiASRefreshChangesCallback_FWD_DEFINED__
#define __ITRiASRefreshChangesCallback_FWD_DEFINED__
typedef interface ITRiASRefreshChangesCallback ITRiASRefreshChangesCallback;
#endif 	/* __ITRiASRefreshChangesCallback_FWD_DEFINED__ */


#ifndef __ITRiASDatabase_FWD_DEFINED__
#define __ITRiASDatabase_FWD_DEFINED__
typedef interface ITRiASDatabase ITRiASDatabase;
#endif 	/* __ITRiASDatabase_FWD_DEFINED__ */


#ifndef __ITRiASAccessDatabase_FWD_DEFINED__
#define __ITRiASAccessDatabase_FWD_DEFINED__
typedef interface ITRiASAccessDatabase ITRiASAccessDatabase;
#endif 	/* __ITRiASAccessDatabase_FWD_DEFINED__ */


#ifndef __ITRiASViews_FWD_DEFINED__
#define __ITRiASViews_FWD_DEFINED__
typedef interface ITRiASViews ITRiASViews;
#endif 	/* __ITRiASViews_FWD_DEFINED__ */


#ifndef __ITRiASView_FWD_DEFINED__
#define __ITRiASView_FWD_DEFINED__
typedef interface ITRiASView ITRiASView;
#endif 	/* __ITRiASView_FWD_DEFINED__ */


#ifndef __ITRiASViewItems_FWD_DEFINED__
#define __ITRiASViewItems_FWD_DEFINED__
typedef interface ITRiASViewItems ITRiASViewItems;
#endif 	/* __ITRiASViewItems_FWD_DEFINED__ */


#ifndef __ITRiASViewItem_FWD_DEFINED__
#define __ITRiASViewItem_FWD_DEFINED__
typedef interface ITRiASViewItem ITRiASViewItem;
#endif 	/* __ITRiASViewItem_FWD_DEFINED__ */


#ifndef __ITRiASObject_FWD_DEFINED__
#define __ITRiASObject_FWD_DEFINED__
typedef interface ITRiASObject ITRiASObject;
#endif 	/* __ITRiASObject_FWD_DEFINED__ */


#ifndef __ITRiASObjectCallback_FWD_DEFINED__
#define __ITRiASObjectCallback_FWD_DEFINED__
typedef interface ITRiASObjectCallback ITRiASObjectCallback;
#endif 	/* __ITRiASObjectCallback_FWD_DEFINED__ */


#ifndef __ITRiASObjects_FWD_DEFINED__
#define __ITRiASObjects_FWD_DEFINED__
typedef interface ITRiASObjects ITRiASObjects;
#endif 	/* __ITRiASObjects_FWD_DEFINED__ */


#ifndef __ITRiASObjectsEx_FWD_DEFINED__
#define __ITRiASObjectsEx_FWD_DEFINED__
typedef interface ITRiASObjectsEx ITRiASObjectsEx;
#endif 	/* __ITRiASObjectsEx_FWD_DEFINED__ */


#ifndef __ITRiASObjectsCallback_FWD_DEFINED__
#define __ITRiASObjectsCallback_FWD_DEFINED__
typedef interface ITRiASObjectsCallback ITRiASObjectsCallback;
#endif 	/* __ITRiASObjectsCallback_FWD_DEFINED__ */


#ifndef __ITRiASObjectsCollection_FWD_DEFINED__
#define __ITRiASObjectsCollection_FWD_DEFINED__
typedef interface ITRiASObjectsCollection ITRiASObjectsCollection;
#endif 	/* __ITRiASObjectsCollection_FWD_DEFINED__ */


#ifndef __ITRiASObjectsCollectionCallback_FWD_DEFINED__
#define __ITRiASObjectsCollectionCallback_FWD_DEFINED__
typedef interface ITRiASObjectsCollectionCallback ITRiASObjectsCollectionCallback;
#endif 	/* __ITRiASObjectsCollectionCallback_FWD_DEFINED__ */


#ifndef __ITRiASFeatures_FWD_DEFINED__
#define __ITRiASFeatures_FWD_DEFINED__
typedef interface ITRiASFeatures ITRiASFeatures;
#endif 	/* __ITRiASFeatures_FWD_DEFINED__ */


#ifndef __ITRiASFeaturesCallback_FWD_DEFINED__
#define __ITRiASFeaturesCallback_FWD_DEFINED__
typedef interface ITRiASFeaturesCallback ITRiASFeaturesCallback;
#endif 	/* __ITRiASFeaturesCallback_FWD_DEFINED__ */


#ifndef __ITRiASFeature_FWD_DEFINED__
#define __ITRiASFeature_FWD_DEFINED__
typedef interface ITRiASFeature ITRiASFeature;
#endif 	/* __ITRiASFeature_FWD_DEFINED__ */


#ifndef __ITRiASFeatureCallback_FWD_DEFINED__
#define __ITRiASFeatureCallback_FWD_DEFINED__
typedef interface ITRiASFeatureCallback ITRiASFeatureCallback;
#endif 	/* __ITRiASFeatureCallback_FWD_DEFINED__ */


#ifndef __ITRiASSearchObjects_FWD_DEFINED__
#define __ITRiASSearchObjects_FWD_DEFINED__
typedef interface ITRiASSearchObjects ITRiASSearchObjects;
#endif 	/* __ITRiASSearchObjects_FWD_DEFINED__ */


#ifndef __ITRiASRelations_FWD_DEFINED__
#define __ITRiASRelations_FWD_DEFINED__
typedef interface ITRiASRelations ITRiASRelations;
#endif 	/* __ITRiASRelations_FWD_DEFINED__ */


#ifndef __ITRiASRelation_FWD_DEFINED__
#define __ITRiASRelation_FWD_DEFINED__
typedef interface ITRiASRelation ITRiASRelation;
#endif 	/* __ITRiASRelation_FWD_DEFINED__ */


#ifndef __ITRiASProperties_FWD_DEFINED__
#define __ITRiASProperties_FWD_DEFINED__
typedef interface ITRiASProperties ITRiASProperties;
#endif 	/* __ITRiASProperties_FWD_DEFINED__ */


#ifndef __ITRiASProperty_FWD_DEFINED__
#define __ITRiASProperty_FWD_DEFINED__
typedef interface ITRiASProperty ITRiASProperty;
#endif 	/* __ITRiASProperty_FWD_DEFINED__ */


#ifndef __ITRiASPropertySupport_FWD_DEFINED__
#define __ITRiASPropertySupport_FWD_DEFINED__
typedef interface ITRiASPropertySupport ITRiASPropertySupport;
#endif 	/* __ITRiASPropertySupport_FWD_DEFINED__ */


#ifndef __ITRiASPropertyMapHandler_FWD_DEFINED__
#define __ITRiASPropertyMapHandler_FWD_DEFINED__
typedef interface ITRiASPropertyMapHandler ITRiASPropertyMapHandler;
#endif 	/* __ITRiASPropertyMapHandler_FWD_DEFINED__ */


#ifndef __ITRiASPropertyCallback_FWD_DEFINED__
#define __ITRiASPropertyCallback_FWD_DEFINED__
typedef interface ITRiASPropertyCallback ITRiASPropertyCallback;
#endif 	/* __ITRiASPropertyCallback_FWD_DEFINED__ */


#ifndef __ITRiASDataServerRegEntries_FWD_DEFINED__
#define __ITRiASDataServerRegEntries_FWD_DEFINED__
typedef interface ITRiASDataServerRegEntries ITRiASDataServerRegEntries;
#endif 	/* __ITRiASDataServerRegEntries_FWD_DEFINED__ */


#ifndef __ITRiASDataServerRegEntry_FWD_DEFINED__
#define __ITRiASDataServerRegEntry_FWD_DEFINED__
typedef interface ITRiASDataServerRegEntry ITRiASDataServerRegEntry;
#endif 	/* __ITRiASDataServerRegEntry_FWD_DEFINED__ */


#ifndef __ITRiASOpenWizardPropExt_FWD_DEFINED__
#define __ITRiASOpenWizardPropExt_FWD_DEFINED__
typedef interface ITRiASOpenWizardPropExt ITRiASOpenWizardPropExt;
#endif 	/* __ITRiASOpenWizardPropExt_FWD_DEFINED__ */


#ifndef __ITRiASObjectHandleMap_FWD_DEFINED__
#define __ITRiASObjectHandleMap_FWD_DEFINED__
typedef interface ITRiASObjectHandleMap ITRiASObjectHandleMap;
#endif 	/* __ITRiASObjectHandleMap_FWD_DEFINED__ */


#ifndef __IObjectWithName_FWD_DEFINED__
#define __IObjectWithName_FWD_DEFINED__
typedef interface IObjectWithName IObjectWithName;
#endif 	/* __IObjectWithName_FWD_DEFINED__ */


#ifndef __ITRiASObjectsOperations_FWD_DEFINED__
#define __ITRiASObjectsOperations_FWD_DEFINED__
typedef interface ITRiASObjectsOperations ITRiASObjectsOperations;
#endif 	/* __ITRiASObjectsOperations_FWD_DEFINED__ */


#ifndef __ITRiASHandle_FWD_DEFINED__
#define __ITRiASHandle_FWD_DEFINED__
typedef interface ITRiASHandle ITRiASHandle;
#endif 	/* __ITRiASHandle_FWD_DEFINED__ */


#ifndef __ITRiASQueryVisInfo_FWD_DEFINED__
#define __ITRiASQueryVisInfo_FWD_DEFINED__
typedef interface ITRiASQueryVisInfo ITRiASQueryVisInfo;
#endif 	/* __ITRiASQueryVisInfo_FWD_DEFINED__ */


#ifndef __IReconnectDialog_FWD_DEFINED__
#define __IReconnectDialog_FWD_DEFINED__
typedef interface IReconnectDialog IReconnectDialog;
#endif 	/* __IReconnectDialog_FWD_DEFINED__ */


#ifndef __ICreateDatabase_FWD_DEFINED__
#define __ICreateDatabase_FWD_DEFINED__
typedef interface ICreateDatabase ICreateDatabase;
#endif 	/* __ICreateDatabase_FWD_DEFINED__ */


#ifndef __ITRiASConnectionFilter_FWD_DEFINED__
#define __ITRiASConnectionFilter_FWD_DEFINED__
typedef interface ITRiASConnectionFilter ITRiASConnectionFilter;
#endif 	/* __ITRiASConnectionFilter_FWD_DEFINED__ */


#ifndef __ITRiASConnectionFilters_FWD_DEFINED__
#define __ITRiASConnectionFilters_FWD_DEFINED__
typedef interface ITRiASConnectionFilters ITRiASConnectionFilters;
#endif 	/* __ITRiASConnectionFilters_FWD_DEFINED__ */


#ifndef __ITRiASMainDBEngine_FWD_DEFINED__
#define __ITRiASMainDBEngine_FWD_DEFINED__
typedef interface ITRiASMainDBEngine ITRiASMainDBEngine;
#endif 	/* __ITRiASMainDBEngine_FWD_DEFINED__ */


#ifndef __ITRiASSimpleDBEngine_FWD_DEFINED__
#define __ITRiASSimpleDBEngine_FWD_DEFINED__
typedef interface ITRiASSimpleDBEngine ITRiASSimpleDBEngine;
#endif 	/* __ITRiASSimpleDBEngine_FWD_DEFINED__ */


#ifndef __ITRiASSimpleObject_FWD_DEFINED__
#define __ITRiASSimpleObject_FWD_DEFINED__
typedef interface ITRiASSimpleObject ITRiASSimpleObject;
#endif 	/* __ITRiASSimpleObject_FWD_DEFINED__ */


#ifndef __ITRiASSimpleObjects_FWD_DEFINED__
#define __ITRiASSimpleObjects_FWD_DEFINED__
typedef interface ITRiASSimpleObjects ITRiASSimpleObjects;
#endif 	/* __ITRiASSimpleObjects_FWD_DEFINED__ */


#ifndef __ITRiASSimpleObjectsCollection_FWD_DEFINED__
#define __ITRiASSimpleObjectsCollection_FWD_DEFINED__
typedef interface ITRiASSimpleObjectsCollection ITRiASSimpleObjectsCollection;
#endif 	/* __ITRiASSimpleObjectsCollection_FWD_DEFINED__ */


#ifndef __ITRiASSimpleFeatures_FWD_DEFINED__
#define __ITRiASSimpleFeatures_FWD_DEFINED__
typedef interface ITRiASSimpleFeatures ITRiASSimpleFeatures;
#endif 	/* __ITRiASSimpleFeatures_FWD_DEFINED__ */


#ifndef __ITRiASSimpleGeoFeatures_FWD_DEFINED__
#define __ITRiASSimpleGeoFeatures_FWD_DEFINED__
typedef interface ITRiASSimpleGeoFeatures ITRiASSimpleGeoFeatures;
#endif 	/* __ITRiASSimpleGeoFeatures_FWD_DEFINED__ */


#ifndef __ITRiASSimpleFeature_FWD_DEFINED__
#define __ITRiASSimpleFeature_FWD_DEFINED__
typedef interface ITRiASSimpleFeature ITRiASSimpleFeature;
#endif 	/* __ITRiASSimpleFeature_FWD_DEFINED__ */


#ifndef __IReconnectDialog_FWD_DEFINED__
#define __IReconnectDialog_FWD_DEFINED__
typedef interface IReconnectDialog IReconnectDialog;
#endif 	/* __IReconnectDialog_FWD_DEFINED__ */


#ifndef __ICreateDatabase_FWD_DEFINED__
#define __ICreateDatabase_FWD_DEFINED__
typedef interface ICreateDatabase ICreateDatabase;
#endif 	/* __ICreateDatabase_FWD_DEFINED__ */


#ifndef __TRiASProjects_FWD_DEFINED__
#define __TRiASProjects_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASProjects TRiASProjects;
#else
typedef struct TRiASProjects TRiASProjects;
#endif /* __cplusplus */

#endif 	/* __TRiASProjects_FWD_DEFINED__ */


#ifndef __TRiASProject_FWD_DEFINED__
#define __TRiASProject_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASProject TRiASProject;
#else
typedef struct TRiASProject TRiASProject;
#endif /* __cplusplus */

#endif 	/* __TRiASProject_FWD_DEFINED__ */


#ifndef __OleDocumentWrapper_FWD_DEFINED__
#define __OleDocumentWrapper_FWD_DEFINED__

#ifdef __cplusplus
typedef class OleDocumentWrapper OleDocumentWrapper;
#else
typedef struct OleDocumentWrapper OleDocumentWrapper;
#endif /* __cplusplus */

#endif 	/* __OleDocumentWrapper_FWD_DEFINED__ */


#ifndef __TRiASConnections_FWD_DEFINED__
#define __TRiASConnections_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASConnections TRiASConnections;
#else
typedef struct TRiASConnections TRiASConnections;
#endif /* __cplusplus */

#endif 	/* __TRiASConnections_FWD_DEFINED__ */


#ifndef __TRiASConnection_FWD_DEFINED__
#define __TRiASConnection_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASConnection TRiASConnection;
#else
typedef struct TRiASConnection TRiASConnection;
#endif /* __cplusplus */

#endif 	/* __TRiASConnection_FWD_DEFINED__ */


#ifndef __TRiASDatabaseOnFile_FWD_DEFINED__
#define __TRiASDatabaseOnFile_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASDatabaseOnFile TRiASDatabaseOnFile;
#else
typedef struct TRiASDatabaseOnFile TRiASDatabaseOnFile;
#endif /* __cplusplus */

#endif 	/* __TRiASDatabaseOnFile_FWD_DEFINED__ */


#ifndef __TRiASDatabaseOnStg_FWD_DEFINED__
#define __TRiASDatabaseOnStg_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASDatabaseOnStg TRiASDatabaseOnStg;
#else
typedef struct TRiASDatabaseOnStg TRiASDatabaseOnStg;
#endif /* __cplusplus */

#endif 	/* __TRiASDatabaseOnStg_FWD_DEFINED__ */


#ifndef __TRiASCompatibleDatabase_FWD_DEFINED__
#define __TRiASCompatibleDatabase_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASCompatibleDatabase TRiASCompatibleDatabase;
#else
typedef struct TRiASCompatibleDatabase TRiASCompatibleDatabase;
#endif /* __cplusplus */

#endif 	/* __TRiASCompatibleDatabase_FWD_DEFINED__ */


#ifndef __TRiASViews_FWD_DEFINED__
#define __TRiASViews_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASViews TRiASViews;
#else
typedef struct TRiASViews TRiASViews;
#endif /* __cplusplus */

#endif 	/* __TRiASViews_FWD_DEFINED__ */


#ifndef __TRiASView_FWD_DEFINED__
#define __TRiASView_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASView TRiASView;
#else
typedef struct TRiASView TRiASView;
#endif /* __cplusplus */

#endif 	/* __TRiASView_FWD_DEFINED__ */


#ifndef __TRiASViewItems_FWD_DEFINED__
#define __TRiASViewItems_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASViewItems TRiASViewItems;
#else
typedef struct TRiASViewItems TRiASViewItems;
#endif /* __cplusplus */

#endif 	/* __TRiASViewItems_FWD_DEFINED__ */


#ifndef __TRiASViewItem_FWD_DEFINED__
#define __TRiASViewItem_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASViewItem TRiASViewItem;
#else
typedef struct TRiASViewItem TRiASViewItem;
#endif /* __cplusplus */

#endif 	/* __TRiASViewItem_FWD_DEFINED__ */


#ifndef __TRiASObjects_FWD_DEFINED__
#define __TRiASObjects_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASObjects TRiASObjects;
#else
typedef struct TRiASObjects TRiASObjects;
#endif /* __cplusplus */

#endif 	/* __TRiASObjects_FWD_DEFINED__ */


#ifndef __TRiASSimpleObjects_FWD_DEFINED__
#define __TRiASSimpleObjects_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASSimpleObjects TRiASSimpleObjects;
#else
typedef struct TRiASSimpleObjects TRiASSimpleObjects;
#endif /* __cplusplus */

#endif 	/* __TRiASSimpleObjects_FWD_DEFINED__ */


#ifndef __TRiASObjectsCollection_FWD_DEFINED__
#define __TRiASObjectsCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASObjectsCollection TRiASObjectsCollection;
#else
typedef struct TRiASObjectsCollection TRiASObjectsCollection;
#endif /* __cplusplus */

#endif 	/* __TRiASObjectsCollection_FWD_DEFINED__ */


#ifndef __TRiASSimpleObjectsCollection_FWD_DEFINED__
#define __TRiASSimpleObjectsCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASSimpleObjectsCollection TRiASSimpleObjectsCollection;
#else
typedef struct TRiASSimpleObjectsCollection TRiASSimpleObjectsCollection;
#endif /* __cplusplus */

#endif 	/* __TRiASSimpleObjectsCollection_FWD_DEFINED__ */


#ifndef __TRiASObject_FWD_DEFINED__
#define __TRiASObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASObject TRiASObject;
#else
typedef struct TRiASObject TRiASObject;
#endif /* __cplusplus */

#endif 	/* __TRiASObject_FWD_DEFINED__ */


#ifndef __TRiASSimpleObject_FWD_DEFINED__
#define __TRiASSimpleObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASSimpleObject TRiASSimpleObject;
#else
typedef struct TRiASSimpleObject TRiASSimpleObject;
#endif /* __cplusplus */

#endif 	/* __TRiASSimpleObject_FWD_DEFINED__ */


#ifndef __TRiASFeatures_FWD_DEFINED__
#define __TRiASFeatures_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASFeatures TRiASFeatures;
#else
typedef struct TRiASFeatures TRiASFeatures;
#endif /* __cplusplus */

#endif 	/* __TRiASFeatures_FWD_DEFINED__ */


#ifndef __TRiASSimpleFeatures_FWD_DEFINED__
#define __TRiASSimpleFeatures_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASSimpleFeatures TRiASSimpleFeatures;
#else
typedef struct TRiASSimpleFeatures TRiASSimpleFeatures;
#endif /* __cplusplus */

#endif 	/* __TRiASSimpleFeatures_FWD_DEFINED__ */


#ifndef __TRiASSimpleGeoFeatures_FWD_DEFINED__
#define __TRiASSimpleGeoFeatures_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASSimpleGeoFeatures TRiASSimpleGeoFeatures;
#else
typedef struct TRiASSimpleGeoFeatures TRiASSimpleGeoFeatures;
#endif /* __cplusplus */

#endif 	/* __TRiASSimpleGeoFeatures_FWD_DEFINED__ */


#ifndef __TRiASFeature_FWD_DEFINED__
#define __TRiASFeature_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASFeature TRiASFeature;
#else
typedef struct TRiASFeature TRiASFeature;
#endif /* __cplusplus */

#endif 	/* __TRiASFeature_FWD_DEFINED__ */


#ifndef __TRiASSimpleFeature_FWD_DEFINED__
#define __TRiASSimpleFeature_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASSimpleFeature TRiASSimpleFeature;
#else
typedef struct TRiASSimpleFeature TRiASSimpleFeature;
#endif /* __cplusplus */

#endif 	/* __TRiASSimpleFeature_FWD_DEFINED__ */


#ifndef __TRiASGuidFeature_FWD_DEFINED__
#define __TRiASGuidFeature_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASGuidFeature TRiASGuidFeature;
#else
typedef struct TRiASGuidFeature TRiASGuidFeature;
#endif /* __cplusplus */

#endif 	/* __TRiASGuidFeature_FWD_DEFINED__ */


#ifndef __TRiASSimpleGeoFeature_FWD_DEFINED__
#define __TRiASSimpleGeoFeature_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASSimpleGeoFeature TRiASSimpleGeoFeature;
#else
typedef struct TRiASSimpleGeoFeature TRiASSimpleGeoFeature;
#endif /* __cplusplus */

#endif 	/* __TRiASSimpleGeoFeature_FWD_DEFINED__ */


#ifndef __TRiASRelations_FWD_DEFINED__
#define __TRiASRelations_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASRelations TRiASRelations;
#else
typedef struct TRiASRelations TRiASRelations;
#endif /* __cplusplus */

#endif 	/* __TRiASRelations_FWD_DEFINED__ */


#ifndef __TRiASRelation_FWD_DEFINED__
#define __TRiASRelation_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASRelation TRiASRelation;
#else
typedef struct TRiASRelation TRiASRelation;
#endif /* __cplusplus */

#endif 	/* __TRiASRelation_FWD_DEFINED__ */


#ifndef __TRiASDBEngine_FWD_DEFINED__
#define __TRiASDBEngine_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASDBEngine TRiASDBEngine;
#else
typedef struct TRiASDBEngine TRiASDBEngine;
#endif /* __cplusplus */

#endif 	/* __TRiASDBEngine_FWD_DEFINED__ */


#ifndef __TRiASProperty_FWD_DEFINED__
#define __TRiASProperty_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASProperty TRiASProperty;
#else
typedef struct TRiASProperty TRiASProperty;
#endif /* __cplusplus */

#endif 	/* __TRiASProperty_FWD_DEFINED__ */


#ifndef __TRiASProperties_FWD_DEFINED__
#define __TRiASProperties_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASProperties TRiASProperties;
#else
typedef struct TRiASProperties TRiASProperties;
#endif /* __cplusplus */

#endif 	/* __TRiASProperties_FWD_DEFINED__ */


#ifndef __TRiASDataServerRegEntries_FWD_DEFINED__
#define __TRiASDataServerRegEntries_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASDataServerRegEntries TRiASDataServerRegEntries;
#else
typedef struct TRiASDataServerRegEntries TRiASDataServerRegEntries;
#endif /* __cplusplus */

#endif 	/* __TRiASDataServerRegEntries_FWD_DEFINED__ */


#ifndef __TRiASDataServerRegEntry_FWD_DEFINED__
#define __TRiASDataServerRegEntry_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASDataServerRegEntry TRiASDataServerRegEntry;
#else
typedef struct TRiASDataServerRegEntry TRiASDataServerRegEntry;
#endif /* __cplusplus */

#endif 	/* __TRiASDataServerRegEntry_FWD_DEFINED__ */


#ifndef __TRiASVariantProperty_FWD_DEFINED__
#define __TRiASVariantProperty_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASVariantProperty TRiASVariantProperty;
#else
typedef struct TRiASVariantProperty TRiASVariantProperty;
#endif /* __cplusplus */

#endif 	/* __TRiASVariantProperty_FWD_DEFINED__ */


#ifndef __TRiASAutoSaveProperty_FWD_DEFINED__
#define __TRiASAutoSaveProperty_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASAutoSaveProperty TRiASAutoSaveProperty;
#else
typedef struct TRiASAutoSaveProperty TRiASAutoSaveProperty;
#endif /* __cplusplus */

#endif 	/* __TRiASAutoSaveProperty_FWD_DEFINED__ */


#ifndef __OpenWizPropExt_FWD_DEFINED__
#define __OpenWizPropExt_FWD_DEFINED__

#ifdef __cplusplus
typedef class OpenWizPropExt OpenWizPropExt;
#else
typedef struct OpenWizPropExt OpenWizPropExt;
#endif /* __cplusplus */

#endif 	/* __OpenWizPropExt_FWD_DEFINED__ */


#ifndef __TRiASObjectHandleMap_FWD_DEFINED__
#define __TRiASObjectHandleMap_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASObjectHandleMap TRiASObjectHandleMap;
#else
typedef struct TRiASObjectHandleMap TRiASObjectHandleMap;
#endif /* __cplusplus */

#endif 	/* __TRiASObjectHandleMap_FWD_DEFINED__ */


#ifndef __TRiASObjectsHandleMap_FWD_DEFINED__
#define __TRiASObjectsHandleMap_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASObjectsHandleMap TRiASObjectsHandleMap;
#else
typedef struct TRiASObjectsHandleMap TRiASObjectsHandleMap;
#endif /* __cplusplus */

#endif 	/* __TRiASObjectsHandleMap_FWD_DEFINED__ */


#ifndef __TRiASFeatureHandleMap_FWD_DEFINED__
#define __TRiASFeatureHandleMap_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASFeatureHandleMap TRiASFeatureHandleMap;
#else
typedef struct TRiASFeatureHandleMap TRiASFeatureHandleMap;
#endif /* __cplusplus */

#endif 	/* __TRiASFeatureHandleMap_FWD_DEFINED__ */


#ifndef __TRiASGenericHandleMap_FWD_DEFINED__
#define __TRiASGenericHandleMap_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASGenericHandleMap TRiASGenericHandleMap;
#else
typedef struct TRiASGenericHandleMap TRiASGenericHandleMap;
#endif /* __cplusplus */

#endif 	/* __TRiASGenericHandleMap_FWD_DEFINED__ */


#ifndef __TRiASMetaDataMap_FWD_DEFINED__
#define __TRiASMetaDataMap_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASMetaDataMap TRiASMetaDataMap;
#else
typedef struct TRiASMetaDataMap TRiASMetaDataMap;
#endif /* __cplusplus */

#endif 	/* __TRiASMetaDataMap_FWD_DEFINED__ */


#ifndef __TRiASObjectsOperations_FWD_DEFINED__
#define __TRiASObjectsOperations_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASObjectsOperations TRiASObjectsOperations;
#else
typedef struct TRiASObjectsOperations TRiASObjectsOperations;
#endif /* __cplusplus */

#endif 	/* __TRiASObjectsOperations_FWD_DEFINED__ */


#ifndef __TRiASConnectionFilters_FWD_DEFINED__
#define __TRiASConnectionFilters_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASConnectionFilters TRiASConnectionFilters;
#else
typedef struct TRiASConnectionFilters TRiASConnectionFilters;
#endif /* __cplusplus */

#endif 	/* __TRiASConnectionFilters_FWD_DEFINED__ */


#ifndef __TRiASConnectionFilter_FWD_DEFINED__
#define __TRiASConnectionFilter_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASConnectionFilter TRiASConnectionFilter;
#else
typedef struct TRiASConnectionFilter TRiASConnectionFilter;
#endif /* __cplusplus */

#endif 	/* __TRiASConnectionFilter_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "TRiASBaseInterfaces.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_TRiASDB_0000 */
/* [local] */ 

#define TYPELIB_TRIASDB_VERSION_MAJOR 1
#define TYPELIB_TRIASDB_VERSION_MINOR 0
#define TYPELIB_TRIASDB_VERSION "1.0"
#define TYPELIB_TRIASDB_LCID 0
#include <TRiASDBModuleStrings.h>











extern RPC_IF_HANDLE __MIDL_itf_TRiASDB_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_TRiASDB_0000_v0_0_s_ifspec;

#ifndef __ITRiASDBEngineEvents_INTERFACE_DEFINED__
#define __ITRiASDBEngineEvents_INTERFACE_DEFINED__

/* interface ITRiASDBEngineEvents */
/* [unique][helpstring][uuid][object] */ 

typedef /* [helpstring][v1_enum][public] */ 
enum _tagCONTINUEMODE
    {	CONTINUEMODE_Continue	= 0,
	CONTINUEMODE_ShouldBreak	= 1,
	CONTINUEMODE_MustBreak	= 2
    } 	CONTINUEMODE;


EXTERN_C const IID IID_ITRiASDBEngineEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("27B09D60-15CE-4988-80D6-BEBFE391B9AC")
    ITRiASDBEngineEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AskToContinue( 
            /* [retval][out] */ CONTINUEMODE *Mode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASDBEngineEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASDBEngineEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASDBEngineEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASDBEngineEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AskToContinue )( 
            ITRiASDBEngineEvents * This,
            /* [retval][out] */ CONTINUEMODE *Mode);
        
        END_INTERFACE
    } ITRiASDBEngineEventsVtbl;

    interface ITRiASDBEngineEvents
    {
        CONST_VTBL struct ITRiASDBEngineEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASDBEngineEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASDBEngineEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASDBEngineEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASDBEngineEvents_AskToContinue(This,Mode)	\
    (This)->lpVtbl -> AskToContinue(This,Mode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASDBEngineEvents_AskToContinue_Proxy( 
    ITRiASDBEngineEvents * This,
    /* [retval][out] */ CONTINUEMODE *Mode);


void __RPC_STUB ITRiASDBEngineEvents_AskToContinue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASDBEngineEvents_INTERFACE_DEFINED__ */


#ifndef __ITRiASProjectEvents_INTERFACE_DEFINED__
#define __ITRiASProjectEvents_INTERFACE_DEFINED__

/* interface ITRiASProjectEvents */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITRiASProjectEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9A9E8F28-3D7F-11d1-96C0-00A024D6F582")
    ITRiASProjectEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ProjectToCreate( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ProjectCreated( 
            /* [in] */ IDispatch *pIPrj) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OpeningProject( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ProjectToOpen( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ProjectIsOpening( 
            /* [in] */ IDispatch *pIPrj) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ProjectOpened( 
            /* [in] */ IDispatch *pIPrj) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ClosingProject( 
            /* [in] */ IDispatch *pIPrj,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ProjectToClose( 
            /* [in] */ IDispatch *pIPrj) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ProjectClosed( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [in] */ IDispatch *pIPrj,
            /* [in] */ IUnknown *Stg,
            /* [in] */ VARIANT_BOOL fSameAsLoad) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SaveCompleted( 
            /* [in] */ IDispatch *pIPrj,
            /* [in] */ VARIANT Stg) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE HandsOffStorage( 
            /* [in] */ IDispatch *pIPrj) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ErrorOpeningProject( 
            /* [in] */ IDispatch *pIPrj) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASProjectEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASProjectEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASProjectEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASProjectEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ProjectToCreate )( 
            ITRiASProjectEvents * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ProjectCreated )( 
            ITRiASProjectEvents * This,
            /* [in] */ IDispatch *pIPrj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OpeningProject )( 
            ITRiASProjectEvents * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ProjectToOpen )( 
            ITRiASProjectEvents * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ProjectIsOpening )( 
            ITRiASProjectEvents * This,
            /* [in] */ IDispatch *pIPrj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ProjectOpened )( 
            ITRiASProjectEvents * This,
            /* [in] */ IDispatch *pIPrj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ClosingProject )( 
            ITRiASProjectEvents * This,
            /* [in] */ IDispatch *pIPrj,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ProjectToClose )( 
            ITRiASProjectEvents * This,
            /* [in] */ IDispatch *pIPrj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ProjectClosed )( 
            ITRiASProjectEvents * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Save )( 
            ITRiASProjectEvents * This,
            /* [in] */ IDispatch *pIPrj,
            /* [in] */ IUnknown *Stg,
            /* [in] */ VARIANT_BOOL fSameAsLoad);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SaveCompleted )( 
            ITRiASProjectEvents * This,
            /* [in] */ IDispatch *pIPrj,
            /* [in] */ VARIANT Stg);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *HandsOffStorage )( 
            ITRiASProjectEvents * This,
            /* [in] */ IDispatch *pIPrj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ErrorOpeningProject )( 
            ITRiASProjectEvents * This,
            /* [in] */ IDispatch *pIPrj);
        
        END_INTERFACE
    } ITRiASProjectEventsVtbl;

    interface ITRiASProjectEvents
    {
        CONST_VTBL struct ITRiASProjectEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASProjectEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASProjectEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASProjectEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASProjectEvents_ProjectToCreate(This,Name)	\
    (This)->lpVtbl -> ProjectToCreate(This,Name)

#define ITRiASProjectEvents_ProjectCreated(This,pIPrj)	\
    (This)->lpVtbl -> ProjectCreated(This,pIPrj)

#define ITRiASProjectEvents_OpeningProject(This,Name,pVal)	\
    (This)->lpVtbl -> OpeningProject(This,Name,pVal)

#define ITRiASProjectEvents_ProjectToOpen(This,Name)	\
    (This)->lpVtbl -> ProjectToOpen(This,Name)

#define ITRiASProjectEvents_ProjectIsOpening(This,pIPrj)	\
    (This)->lpVtbl -> ProjectIsOpening(This,pIPrj)

#define ITRiASProjectEvents_ProjectOpened(This,pIPrj)	\
    (This)->lpVtbl -> ProjectOpened(This,pIPrj)

#define ITRiASProjectEvents_ClosingProject(This,pIPrj,pVal)	\
    (This)->lpVtbl -> ClosingProject(This,pIPrj,pVal)

#define ITRiASProjectEvents_ProjectToClose(This,pIPrj)	\
    (This)->lpVtbl -> ProjectToClose(This,pIPrj)

#define ITRiASProjectEvents_ProjectClosed(This,Name)	\
    (This)->lpVtbl -> ProjectClosed(This,Name)

#define ITRiASProjectEvents_Save(This,pIPrj,Stg,fSameAsLoad)	\
    (This)->lpVtbl -> Save(This,pIPrj,Stg,fSameAsLoad)

#define ITRiASProjectEvents_SaveCompleted(This,pIPrj,Stg)	\
    (This)->lpVtbl -> SaveCompleted(This,pIPrj,Stg)

#define ITRiASProjectEvents_HandsOffStorage(This,pIPrj)	\
    (This)->lpVtbl -> HandsOffStorage(This,pIPrj)

#define ITRiASProjectEvents_ErrorOpeningProject(This,pIPrj)	\
    (This)->lpVtbl -> ErrorOpeningProject(This,pIPrj)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASProjectEvents_ProjectToCreate_Proxy( 
    ITRiASProjectEvents * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASProjectEvents_ProjectToCreate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASProjectEvents_ProjectCreated_Proxy( 
    ITRiASProjectEvents * This,
    /* [in] */ IDispatch *pIPrj);


void __RPC_STUB ITRiASProjectEvents_ProjectCreated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASProjectEvents_OpeningProject_Proxy( 
    ITRiASProjectEvents * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASProjectEvents_OpeningProject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASProjectEvents_ProjectToOpen_Proxy( 
    ITRiASProjectEvents * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASProjectEvents_ProjectToOpen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASProjectEvents_ProjectIsOpening_Proxy( 
    ITRiASProjectEvents * This,
    /* [in] */ IDispatch *pIPrj);


void __RPC_STUB ITRiASProjectEvents_ProjectIsOpening_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASProjectEvents_ProjectOpened_Proxy( 
    ITRiASProjectEvents * This,
    /* [in] */ IDispatch *pIPrj);


void __RPC_STUB ITRiASProjectEvents_ProjectOpened_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASProjectEvents_ClosingProject_Proxy( 
    ITRiASProjectEvents * This,
    /* [in] */ IDispatch *pIPrj,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASProjectEvents_ClosingProject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASProjectEvents_ProjectToClose_Proxy( 
    ITRiASProjectEvents * This,
    /* [in] */ IDispatch *pIPrj);


void __RPC_STUB ITRiASProjectEvents_ProjectToClose_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASProjectEvents_ProjectClosed_Proxy( 
    ITRiASProjectEvents * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASProjectEvents_ProjectClosed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASProjectEvents_Save_Proxy( 
    ITRiASProjectEvents * This,
    /* [in] */ IDispatch *pIPrj,
    /* [in] */ IUnknown *Stg,
    /* [in] */ VARIANT_BOOL fSameAsLoad);


void __RPC_STUB ITRiASProjectEvents_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASProjectEvents_SaveCompleted_Proxy( 
    ITRiASProjectEvents * This,
    /* [in] */ IDispatch *pIPrj,
    /* [in] */ VARIANT Stg);


void __RPC_STUB ITRiASProjectEvents_SaveCompleted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASProjectEvents_HandsOffStorage_Proxy( 
    ITRiASProjectEvents * This,
    /* [in] */ IDispatch *pIPrj);


void __RPC_STUB ITRiASProjectEvents_HandsOffStorage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASProjectEvents_ErrorOpeningProject_Proxy( 
    ITRiASProjectEvents * This,
    /* [in] */ IDispatch *pIPrj);


void __RPC_STUB ITRiASProjectEvents_ErrorOpeningProject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASProjectEvents_INTERFACE_DEFINED__ */


#ifndef __ITRiASConnectionEvents_INTERFACE_DEFINED__
#define __ITRiASConnectionEvents_INTERFACE_DEFINED__

/* interface ITRiASConnectionEvents */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITRiASConnectionEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9A9E8F29-3D7F-11d1-96C0-00A024D6F582")
    ITRiASConnectionEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreatingConnection( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConnectionToCreate( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConnectionCreated( 
            /* [in] */ IDispatch *pIConn) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OpeningConnection( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConnectionToOpen( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConnectionOpened( 
            /* [in] */ IDispatch *pIConn) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ClosingConnection( 
            /* [in] */ IDispatch *pIConn,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConnectionToClose( 
            /* [in] */ IDispatch *pIConn) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConnectionClosed( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeletingConnection( 
            /* [in] */ IDispatch *pIConn,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConnectionToDelete( 
            /* [in] */ IDispatch *pIConn) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConnectionDeleted( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RenamingConnection( 
            /* [in] */ BSTR OldName,
            /* [in] */ BSTR NewName,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConnectionToRename( 
            /* [in] */ BSTR OldName,
            /* [in] */ BSTR NewName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConnectionRenamed( 
            /* [in] */ IDispatch *pIConn) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ChangingConnectedDatasource( 
            /* [in] */ IDispatch *pIConn,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConnectedDatasourceToChange( 
            /* [in] */ IDispatch *pIConn) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConnectedDatasourceChanged( 
            /* [in] */ IDispatch *pIConn) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASConnectionEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASConnectionEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASConnectionEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASConnectionEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreatingConnection )( 
            ITRiASConnectionEvents * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConnectionToCreate )( 
            ITRiASConnectionEvents * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConnectionCreated )( 
            ITRiASConnectionEvents * This,
            /* [in] */ IDispatch *pIConn);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OpeningConnection )( 
            ITRiASConnectionEvents * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConnectionToOpen )( 
            ITRiASConnectionEvents * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConnectionOpened )( 
            ITRiASConnectionEvents * This,
            /* [in] */ IDispatch *pIConn);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ClosingConnection )( 
            ITRiASConnectionEvents * This,
            /* [in] */ IDispatch *pIConn,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConnectionToClose )( 
            ITRiASConnectionEvents * This,
            /* [in] */ IDispatch *pIConn);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConnectionClosed )( 
            ITRiASConnectionEvents * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeletingConnection )( 
            ITRiASConnectionEvents * This,
            /* [in] */ IDispatch *pIConn,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConnectionToDelete )( 
            ITRiASConnectionEvents * This,
            /* [in] */ IDispatch *pIConn);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConnectionDeleted )( 
            ITRiASConnectionEvents * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RenamingConnection )( 
            ITRiASConnectionEvents * This,
            /* [in] */ BSTR OldName,
            /* [in] */ BSTR NewName,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConnectionToRename )( 
            ITRiASConnectionEvents * This,
            /* [in] */ BSTR OldName,
            /* [in] */ BSTR NewName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConnectionRenamed )( 
            ITRiASConnectionEvents * This,
            /* [in] */ IDispatch *pIConn);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ChangingConnectedDatasource )( 
            ITRiASConnectionEvents * This,
            /* [in] */ IDispatch *pIConn,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConnectedDatasourceToChange )( 
            ITRiASConnectionEvents * This,
            /* [in] */ IDispatch *pIConn);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConnectedDatasourceChanged )( 
            ITRiASConnectionEvents * This,
            /* [in] */ IDispatch *pIConn);
        
        END_INTERFACE
    } ITRiASConnectionEventsVtbl;

    interface ITRiASConnectionEvents
    {
        CONST_VTBL struct ITRiASConnectionEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASConnectionEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASConnectionEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASConnectionEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASConnectionEvents_CreatingConnection(This,Name,pVal)	\
    (This)->lpVtbl -> CreatingConnection(This,Name,pVal)

#define ITRiASConnectionEvents_ConnectionToCreate(This,Name)	\
    (This)->lpVtbl -> ConnectionToCreate(This,Name)

#define ITRiASConnectionEvents_ConnectionCreated(This,pIConn)	\
    (This)->lpVtbl -> ConnectionCreated(This,pIConn)

#define ITRiASConnectionEvents_OpeningConnection(This,Name,pVal)	\
    (This)->lpVtbl -> OpeningConnection(This,Name,pVal)

#define ITRiASConnectionEvents_ConnectionToOpen(This,Name)	\
    (This)->lpVtbl -> ConnectionToOpen(This,Name)

#define ITRiASConnectionEvents_ConnectionOpened(This,pIConn)	\
    (This)->lpVtbl -> ConnectionOpened(This,pIConn)

#define ITRiASConnectionEvents_ClosingConnection(This,pIConn,pVal)	\
    (This)->lpVtbl -> ClosingConnection(This,pIConn,pVal)

#define ITRiASConnectionEvents_ConnectionToClose(This,pIConn)	\
    (This)->lpVtbl -> ConnectionToClose(This,pIConn)

#define ITRiASConnectionEvents_ConnectionClosed(This,Name)	\
    (This)->lpVtbl -> ConnectionClosed(This,Name)

#define ITRiASConnectionEvents_DeletingConnection(This,pIConn,pVal)	\
    (This)->lpVtbl -> DeletingConnection(This,pIConn,pVal)

#define ITRiASConnectionEvents_ConnectionToDelete(This,pIConn)	\
    (This)->lpVtbl -> ConnectionToDelete(This,pIConn)

#define ITRiASConnectionEvents_ConnectionDeleted(This,Name)	\
    (This)->lpVtbl -> ConnectionDeleted(This,Name)

#define ITRiASConnectionEvents_RenamingConnection(This,OldName,NewName,pVal)	\
    (This)->lpVtbl -> RenamingConnection(This,OldName,NewName,pVal)

#define ITRiASConnectionEvents_ConnectionToRename(This,OldName,NewName)	\
    (This)->lpVtbl -> ConnectionToRename(This,OldName,NewName)

#define ITRiASConnectionEvents_ConnectionRenamed(This,pIConn)	\
    (This)->lpVtbl -> ConnectionRenamed(This,pIConn)

#define ITRiASConnectionEvents_ChangingConnectedDatasource(This,pIConn,pVal)	\
    (This)->lpVtbl -> ChangingConnectedDatasource(This,pIConn,pVal)

#define ITRiASConnectionEvents_ConnectedDatasourceToChange(This,pIConn)	\
    (This)->lpVtbl -> ConnectedDatasourceToChange(This,pIConn)

#define ITRiASConnectionEvents_ConnectedDatasourceChanged(This,pIConn)	\
    (This)->lpVtbl -> ConnectedDatasourceChanged(This,pIConn)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASConnectionEvents_CreatingConnection_Proxy( 
    ITRiASConnectionEvents * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASConnectionEvents_CreatingConnection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASConnectionEvents_ConnectionToCreate_Proxy( 
    ITRiASConnectionEvents * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASConnectionEvents_ConnectionToCreate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASConnectionEvents_ConnectionCreated_Proxy( 
    ITRiASConnectionEvents * This,
    /* [in] */ IDispatch *pIConn);


void __RPC_STUB ITRiASConnectionEvents_ConnectionCreated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASConnectionEvents_OpeningConnection_Proxy( 
    ITRiASConnectionEvents * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASConnectionEvents_OpeningConnection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASConnectionEvents_ConnectionToOpen_Proxy( 
    ITRiASConnectionEvents * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASConnectionEvents_ConnectionToOpen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASConnectionEvents_ConnectionOpened_Proxy( 
    ITRiASConnectionEvents * This,
    /* [in] */ IDispatch *pIConn);


void __RPC_STUB ITRiASConnectionEvents_ConnectionOpened_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASConnectionEvents_ClosingConnection_Proxy( 
    ITRiASConnectionEvents * This,
    /* [in] */ IDispatch *pIConn,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASConnectionEvents_ClosingConnection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASConnectionEvents_ConnectionToClose_Proxy( 
    ITRiASConnectionEvents * This,
    /* [in] */ IDispatch *pIConn);


void __RPC_STUB ITRiASConnectionEvents_ConnectionToClose_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASConnectionEvents_ConnectionClosed_Proxy( 
    ITRiASConnectionEvents * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASConnectionEvents_ConnectionClosed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASConnectionEvents_DeletingConnection_Proxy( 
    ITRiASConnectionEvents * This,
    /* [in] */ IDispatch *pIConn,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASConnectionEvents_DeletingConnection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASConnectionEvents_ConnectionToDelete_Proxy( 
    ITRiASConnectionEvents * This,
    /* [in] */ IDispatch *pIConn);


void __RPC_STUB ITRiASConnectionEvents_ConnectionToDelete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASConnectionEvents_ConnectionDeleted_Proxy( 
    ITRiASConnectionEvents * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASConnectionEvents_ConnectionDeleted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASConnectionEvents_RenamingConnection_Proxy( 
    ITRiASConnectionEvents * This,
    /* [in] */ BSTR OldName,
    /* [in] */ BSTR NewName,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASConnectionEvents_RenamingConnection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASConnectionEvents_ConnectionToRename_Proxy( 
    ITRiASConnectionEvents * This,
    /* [in] */ BSTR OldName,
    /* [in] */ BSTR NewName);


void __RPC_STUB ITRiASConnectionEvents_ConnectionToRename_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASConnectionEvents_ConnectionRenamed_Proxy( 
    ITRiASConnectionEvents * This,
    /* [in] */ IDispatch *pIConn);


void __RPC_STUB ITRiASConnectionEvents_ConnectionRenamed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASConnectionEvents_ChangingConnectedDatasource_Proxy( 
    ITRiASConnectionEvents * This,
    /* [in] */ IDispatch *pIConn,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASConnectionEvents_ChangingConnectedDatasource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASConnectionEvents_ConnectedDatasourceToChange_Proxy( 
    ITRiASConnectionEvents * This,
    /* [in] */ IDispatch *pIConn);


void __RPC_STUB ITRiASConnectionEvents_ConnectedDatasourceToChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASConnectionEvents_ConnectedDatasourceChanged_Proxy( 
    ITRiASConnectionEvents * This,
    /* [in] */ IDispatch *pIConn);


void __RPC_STUB ITRiASConnectionEvents_ConnectedDatasourceChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASConnectionEvents_INTERFACE_DEFINED__ */


#ifndef __ITRiASViewEvents_INTERFACE_DEFINED__
#define __ITRiASViewEvents_INTERFACE_DEFINED__

/* interface ITRiASViewEvents */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITRiASViewEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3E4A3F24-878C-11D1-9784-00A024D6F582")
    ITRiASViewEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreatingView( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ViewToCreate( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ViewCreated( 
            /* [in] */ IDispatch *pIView) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ChangingView( 
            /* [in] */ BSTR OldName,
            /* [in] */ BSTR NewName,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ViewToChange( 
            /* [in] */ BSTR OldName,
            /* [in] */ BSTR NewName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ViewChanged( 
            /* [in] */ IDispatch *pIView) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeletingView( 
            /* [in] */ IDispatch *pIConn,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ViewToDelete( 
            /* [in] */ IDispatch *pIView) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ViewDeleted( 
            /* [in] */ BSTR Name) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASViewEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASViewEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASViewEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASViewEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreatingView )( 
            ITRiASViewEvents * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ViewToCreate )( 
            ITRiASViewEvents * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ViewCreated )( 
            ITRiASViewEvents * This,
            /* [in] */ IDispatch *pIView);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ChangingView )( 
            ITRiASViewEvents * This,
            /* [in] */ BSTR OldName,
            /* [in] */ BSTR NewName,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ViewToChange )( 
            ITRiASViewEvents * This,
            /* [in] */ BSTR OldName,
            /* [in] */ BSTR NewName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ViewChanged )( 
            ITRiASViewEvents * This,
            /* [in] */ IDispatch *pIView);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeletingView )( 
            ITRiASViewEvents * This,
            /* [in] */ IDispatch *pIConn,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ViewToDelete )( 
            ITRiASViewEvents * This,
            /* [in] */ IDispatch *pIView);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ViewDeleted )( 
            ITRiASViewEvents * This,
            /* [in] */ BSTR Name);
        
        END_INTERFACE
    } ITRiASViewEventsVtbl;

    interface ITRiASViewEvents
    {
        CONST_VTBL struct ITRiASViewEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASViewEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASViewEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASViewEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASViewEvents_CreatingView(This,Name,pVal)	\
    (This)->lpVtbl -> CreatingView(This,Name,pVal)

#define ITRiASViewEvents_ViewToCreate(This,Name)	\
    (This)->lpVtbl -> ViewToCreate(This,Name)

#define ITRiASViewEvents_ViewCreated(This,pIView)	\
    (This)->lpVtbl -> ViewCreated(This,pIView)

#define ITRiASViewEvents_ChangingView(This,OldName,NewName,pVal)	\
    (This)->lpVtbl -> ChangingView(This,OldName,NewName,pVal)

#define ITRiASViewEvents_ViewToChange(This,OldName,NewName)	\
    (This)->lpVtbl -> ViewToChange(This,OldName,NewName)

#define ITRiASViewEvents_ViewChanged(This,pIView)	\
    (This)->lpVtbl -> ViewChanged(This,pIView)

#define ITRiASViewEvents_DeletingView(This,pIConn,pVal)	\
    (This)->lpVtbl -> DeletingView(This,pIConn,pVal)

#define ITRiASViewEvents_ViewToDelete(This,pIView)	\
    (This)->lpVtbl -> ViewToDelete(This,pIView)

#define ITRiASViewEvents_ViewDeleted(This,Name)	\
    (This)->lpVtbl -> ViewDeleted(This,Name)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASViewEvents_CreatingView_Proxy( 
    ITRiASViewEvents * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASViewEvents_CreatingView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASViewEvents_ViewToCreate_Proxy( 
    ITRiASViewEvents * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASViewEvents_ViewToCreate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASViewEvents_ViewCreated_Proxy( 
    ITRiASViewEvents * This,
    /* [in] */ IDispatch *pIView);


void __RPC_STUB ITRiASViewEvents_ViewCreated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASViewEvents_ChangingView_Proxy( 
    ITRiASViewEvents * This,
    /* [in] */ BSTR OldName,
    /* [in] */ BSTR NewName,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASViewEvents_ChangingView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASViewEvents_ViewToChange_Proxy( 
    ITRiASViewEvents * This,
    /* [in] */ BSTR OldName,
    /* [in] */ BSTR NewName);


void __RPC_STUB ITRiASViewEvents_ViewToChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASViewEvents_ViewChanged_Proxy( 
    ITRiASViewEvents * This,
    /* [in] */ IDispatch *pIView);


void __RPC_STUB ITRiASViewEvents_ViewChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASViewEvents_DeletingView_Proxy( 
    ITRiASViewEvents * This,
    /* [in] */ IDispatch *pIConn,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASViewEvents_DeletingView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASViewEvents_ViewToDelete_Proxy( 
    ITRiASViewEvents * This,
    /* [in] */ IDispatch *pIView);


void __RPC_STUB ITRiASViewEvents_ViewToDelete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASViewEvents_ViewDeleted_Proxy( 
    ITRiASViewEvents * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASViewEvents_ViewDeleted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASViewEvents_INTERFACE_DEFINED__ */


#ifndef __ITRiASPropertyEvents_INTERFACE_DEFINED__
#define __ITRiASPropertyEvents_INTERFACE_DEFINED__

/* interface ITRiASPropertyEvents */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITRiASPropertyEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9A9E8F2A-3D7F-11d1-96C0-00A024D6F582")
    ITRiASPropertyEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreatingProperty( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PropertyToCreate( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PropertyCreated( 
            /* [in] */ IDispatch *pIProp) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ModifyingProperty( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PropertyToModify( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PropertyModified( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeletingProperty( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PropertyToDelete( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PropertyDeleted( 
            /* [in] */ BSTR Name) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASPropertyEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASPropertyEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASPropertyEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASPropertyEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreatingProperty )( 
            ITRiASPropertyEvents * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PropertyToCreate )( 
            ITRiASPropertyEvents * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PropertyCreated )( 
            ITRiASPropertyEvents * This,
            /* [in] */ IDispatch *pIProp);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ModifyingProperty )( 
            ITRiASPropertyEvents * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PropertyToModify )( 
            ITRiASPropertyEvents * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PropertyModified )( 
            ITRiASPropertyEvents * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeletingProperty )( 
            ITRiASPropertyEvents * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PropertyToDelete )( 
            ITRiASPropertyEvents * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PropertyDeleted )( 
            ITRiASPropertyEvents * This,
            /* [in] */ BSTR Name);
        
        END_INTERFACE
    } ITRiASPropertyEventsVtbl;

    interface ITRiASPropertyEvents
    {
        CONST_VTBL struct ITRiASPropertyEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASPropertyEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASPropertyEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASPropertyEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASPropertyEvents_CreatingProperty(This,Name,pVal)	\
    (This)->lpVtbl -> CreatingProperty(This,Name,pVal)

#define ITRiASPropertyEvents_PropertyToCreate(This,Name)	\
    (This)->lpVtbl -> PropertyToCreate(This,Name)

#define ITRiASPropertyEvents_PropertyCreated(This,pIProp)	\
    (This)->lpVtbl -> PropertyCreated(This,pIProp)

#define ITRiASPropertyEvents_ModifyingProperty(This,Name,pVal)	\
    (This)->lpVtbl -> ModifyingProperty(This,Name,pVal)

#define ITRiASPropertyEvents_PropertyToModify(This,Name)	\
    (This)->lpVtbl -> PropertyToModify(This,Name)

#define ITRiASPropertyEvents_PropertyModified(This,Name)	\
    (This)->lpVtbl -> PropertyModified(This,Name)

#define ITRiASPropertyEvents_DeletingProperty(This,Name,pVal)	\
    (This)->lpVtbl -> DeletingProperty(This,Name,pVal)

#define ITRiASPropertyEvents_PropertyToDelete(This,Name)	\
    (This)->lpVtbl -> PropertyToDelete(This,Name)

#define ITRiASPropertyEvents_PropertyDeleted(This,Name)	\
    (This)->lpVtbl -> PropertyDeleted(This,Name)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASPropertyEvents_CreatingProperty_Proxy( 
    ITRiASPropertyEvents * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASPropertyEvents_CreatingProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASPropertyEvents_PropertyToCreate_Proxy( 
    ITRiASPropertyEvents * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASPropertyEvents_PropertyToCreate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASPropertyEvents_PropertyCreated_Proxy( 
    ITRiASPropertyEvents * This,
    /* [in] */ IDispatch *pIProp);


void __RPC_STUB ITRiASPropertyEvents_PropertyCreated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASPropertyEvents_ModifyingProperty_Proxy( 
    ITRiASPropertyEvents * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASPropertyEvents_ModifyingProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASPropertyEvents_PropertyToModify_Proxy( 
    ITRiASPropertyEvents * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASPropertyEvents_PropertyToModify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASPropertyEvents_PropertyModified_Proxy( 
    ITRiASPropertyEvents * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASPropertyEvents_PropertyModified_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASPropertyEvents_DeletingProperty_Proxy( 
    ITRiASPropertyEvents * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASPropertyEvents_DeletingProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASPropertyEvents_PropertyToDelete_Proxy( 
    ITRiASPropertyEvents * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASPropertyEvents_PropertyToDelete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASPropertyEvents_PropertyDeleted_Proxy( 
    ITRiASPropertyEvents * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASPropertyEvents_PropertyDeleted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASPropertyEvents_INTERFACE_DEFINED__ */


#ifndef __ITRiASViewItemEvents_INTERFACE_DEFINED__
#define __ITRiASViewItemEvents_INTERFACE_DEFINED__

/* interface ITRiASViewItemEvents */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITRiASViewItemEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B7AEB934-922C-11D1-BA01-080036D63803")
    ITRiASViewItemEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreatingViewItem( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ViewItemToCreate( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ViewItemCreated( 
            /* [in] */ IDispatch *Item) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ModifyingViewItem( 
            /* [in] */ IDispatch *Item,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ViewItemToModify( 
            /* [in] */ IDispatch *Item) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ViewItemModified( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeletingViewItem( 
            /* [in] */ IDispatch *Item,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ViewItemToDelete( 
            /* [in] */ IDispatch *Item) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ViewItemDeleted( 
            /* [in] */ BSTR Name) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASViewItemEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASViewItemEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASViewItemEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASViewItemEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreatingViewItem )( 
            ITRiASViewItemEvents * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ViewItemToCreate )( 
            ITRiASViewItemEvents * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ViewItemCreated )( 
            ITRiASViewItemEvents * This,
            /* [in] */ IDispatch *Item);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ModifyingViewItem )( 
            ITRiASViewItemEvents * This,
            /* [in] */ IDispatch *Item,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ViewItemToModify )( 
            ITRiASViewItemEvents * This,
            /* [in] */ IDispatch *Item);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ViewItemModified )( 
            ITRiASViewItemEvents * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeletingViewItem )( 
            ITRiASViewItemEvents * This,
            /* [in] */ IDispatch *Item,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ViewItemToDelete )( 
            ITRiASViewItemEvents * This,
            /* [in] */ IDispatch *Item);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ViewItemDeleted )( 
            ITRiASViewItemEvents * This,
            /* [in] */ BSTR Name);
        
        END_INTERFACE
    } ITRiASViewItemEventsVtbl;

    interface ITRiASViewItemEvents
    {
        CONST_VTBL struct ITRiASViewItemEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASViewItemEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASViewItemEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASViewItemEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASViewItemEvents_CreatingViewItem(This,Name,pVal)	\
    (This)->lpVtbl -> CreatingViewItem(This,Name,pVal)

#define ITRiASViewItemEvents_ViewItemToCreate(This,Name)	\
    (This)->lpVtbl -> ViewItemToCreate(This,Name)

#define ITRiASViewItemEvents_ViewItemCreated(This,Item)	\
    (This)->lpVtbl -> ViewItemCreated(This,Item)

#define ITRiASViewItemEvents_ModifyingViewItem(This,Item,pVal)	\
    (This)->lpVtbl -> ModifyingViewItem(This,Item,pVal)

#define ITRiASViewItemEvents_ViewItemToModify(This,Item)	\
    (This)->lpVtbl -> ViewItemToModify(This,Item)

#define ITRiASViewItemEvents_ViewItemModified(This,Name)	\
    (This)->lpVtbl -> ViewItemModified(This,Name)

#define ITRiASViewItemEvents_DeletingViewItem(This,Item,pVal)	\
    (This)->lpVtbl -> DeletingViewItem(This,Item,pVal)

#define ITRiASViewItemEvents_ViewItemToDelete(This,Item)	\
    (This)->lpVtbl -> ViewItemToDelete(This,Item)

#define ITRiASViewItemEvents_ViewItemDeleted(This,Name)	\
    (This)->lpVtbl -> ViewItemDeleted(This,Name)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASViewItemEvents_CreatingViewItem_Proxy( 
    ITRiASViewItemEvents * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASViewItemEvents_CreatingViewItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASViewItemEvents_ViewItemToCreate_Proxy( 
    ITRiASViewItemEvents * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASViewItemEvents_ViewItemToCreate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASViewItemEvents_ViewItemCreated_Proxy( 
    ITRiASViewItemEvents * This,
    /* [in] */ IDispatch *Item);


void __RPC_STUB ITRiASViewItemEvents_ViewItemCreated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASViewItemEvents_ModifyingViewItem_Proxy( 
    ITRiASViewItemEvents * This,
    /* [in] */ IDispatch *Item,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASViewItemEvents_ModifyingViewItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASViewItemEvents_ViewItemToModify_Proxy( 
    ITRiASViewItemEvents * This,
    /* [in] */ IDispatch *Item);


void __RPC_STUB ITRiASViewItemEvents_ViewItemToModify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASViewItemEvents_ViewItemModified_Proxy( 
    ITRiASViewItemEvents * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASViewItemEvents_ViewItemModified_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASViewItemEvents_DeletingViewItem_Proxy( 
    ITRiASViewItemEvents * This,
    /* [in] */ IDispatch *Item,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASViewItemEvents_DeletingViewItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASViewItemEvents_ViewItemToDelete_Proxy( 
    ITRiASViewItemEvents * This,
    /* [in] */ IDispatch *Item);


void __RPC_STUB ITRiASViewItemEvents_ViewItemToDelete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASViewItemEvents_ViewItemDeleted_Proxy( 
    ITRiASViewItemEvents * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASViewItemEvents_ViewItemDeleted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASViewItemEvents_INTERFACE_DEFINED__ */


#ifndef __ITRiASObjectsEvents_INTERFACE_DEFINED__
#define __ITRiASObjectsEvents_INTERFACE_DEFINED__

/* interface ITRiASObjectsEvents */
/* [unique][helpstring][uuid][object] */ 

#if !defined(_CHANGEDOBJECTS_DEFINED)
#define _CHANGEDOBJECTS_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagCHANGEDOBJECTS
    {	CHANGEDOBJECTS_Name	= 0x1,
	CHANGEDOBJECTS_Description	= 0x2,
	CHANGEDOBJECTS_OKS	= 0x4,
	CHANGEDOBJECTS_Handle	= 0x8,
	CHANGEDOBJECTS_Types	= 0x10,
	CHANGEDOBJECTS_ROMode	= 0x20
    } 	CHANGEDOBJECTS;

#endif // _CHANGEDOBJECTS_DEFINED

EXTERN_C const IID IID_ITRiASObjectsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D0248D00-3AEA-11D3-94FB-0080C786297B")
    ITRiASObjectsEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreatingObjects( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ObjectsToCreate( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ObjectsCreated( 
            /* [in] */ IDispatch *Item) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ModifyingObjects( 
            /* [in] */ CHANGEDOBJECTS Mode,
            /* [in] */ IDispatch *Item,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ObjectsToModify( 
            /* [in] */ CHANGEDOBJECTS Mode,
            /* [in] */ IDispatch *Item) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ObjectsModified( 
            /* [in] */ CHANGEDOBJECTS Mode,
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeletingObjects( 
            /* [in] */ IDispatch *Object,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ObjectsToDelete( 
            /* [in] */ IDispatch *Object) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ObjectsDeleted( 
            /* [in] */ BSTR Name) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASObjectsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASObjectsEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASObjectsEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASObjectsEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreatingObjects )( 
            ITRiASObjectsEvents * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ObjectsToCreate )( 
            ITRiASObjectsEvents * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ObjectsCreated )( 
            ITRiASObjectsEvents * This,
            /* [in] */ IDispatch *Item);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ModifyingObjects )( 
            ITRiASObjectsEvents * This,
            /* [in] */ CHANGEDOBJECTS Mode,
            /* [in] */ IDispatch *Item,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ObjectsToModify )( 
            ITRiASObjectsEvents * This,
            /* [in] */ CHANGEDOBJECTS Mode,
            /* [in] */ IDispatch *Item);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ObjectsModified )( 
            ITRiASObjectsEvents * This,
            /* [in] */ CHANGEDOBJECTS Mode,
            /* [in] */ BSTR Name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeletingObjects )( 
            ITRiASObjectsEvents * This,
            /* [in] */ IDispatch *Object,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ObjectsToDelete )( 
            ITRiASObjectsEvents * This,
            /* [in] */ IDispatch *Object);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ObjectsDeleted )( 
            ITRiASObjectsEvents * This,
            /* [in] */ BSTR Name);
        
        END_INTERFACE
    } ITRiASObjectsEventsVtbl;

    interface ITRiASObjectsEvents
    {
        CONST_VTBL struct ITRiASObjectsEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASObjectsEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASObjectsEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASObjectsEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASObjectsEvents_CreatingObjects(This,Name,pVal)	\
    (This)->lpVtbl -> CreatingObjects(This,Name,pVal)

#define ITRiASObjectsEvents_ObjectsToCreate(This,Name)	\
    (This)->lpVtbl -> ObjectsToCreate(This,Name)

#define ITRiASObjectsEvents_ObjectsCreated(This,Item)	\
    (This)->lpVtbl -> ObjectsCreated(This,Item)

#define ITRiASObjectsEvents_ModifyingObjects(This,Mode,Item,pVal)	\
    (This)->lpVtbl -> ModifyingObjects(This,Mode,Item,pVal)

#define ITRiASObjectsEvents_ObjectsToModify(This,Mode,Item)	\
    (This)->lpVtbl -> ObjectsToModify(This,Mode,Item)

#define ITRiASObjectsEvents_ObjectsModified(This,Mode,Name)	\
    (This)->lpVtbl -> ObjectsModified(This,Mode,Name)

#define ITRiASObjectsEvents_DeletingObjects(This,Object,pVal)	\
    (This)->lpVtbl -> DeletingObjects(This,Object,pVal)

#define ITRiASObjectsEvents_ObjectsToDelete(This,Object)	\
    (This)->lpVtbl -> ObjectsToDelete(This,Object)

#define ITRiASObjectsEvents_ObjectsDeleted(This,Name)	\
    (This)->lpVtbl -> ObjectsDeleted(This,Name)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsEvents_CreatingObjects_Proxy( 
    ITRiASObjectsEvents * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASObjectsEvents_CreatingObjects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsEvents_ObjectsToCreate_Proxy( 
    ITRiASObjectsEvents * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASObjectsEvents_ObjectsToCreate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsEvents_ObjectsCreated_Proxy( 
    ITRiASObjectsEvents * This,
    /* [in] */ IDispatch *Item);


void __RPC_STUB ITRiASObjectsEvents_ObjectsCreated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsEvents_ModifyingObjects_Proxy( 
    ITRiASObjectsEvents * This,
    /* [in] */ CHANGEDOBJECTS Mode,
    /* [in] */ IDispatch *Item,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASObjectsEvents_ModifyingObjects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsEvents_ObjectsToModify_Proxy( 
    ITRiASObjectsEvents * This,
    /* [in] */ CHANGEDOBJECTS Mode,
    /* [in] */ IDispatch *Item);


void __RPC_STUB ITRiASObjectsEvents_ObjectsToModify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsEvents_ObjectsModified_Proxy( 
    ITRiASObjectsEvents * This,
    /* [in] */ CHANGEDOBJECTS Mode,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASObjectsEvents_ObjectsModified_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsEvents_DeletingObjects_Proxy( 
    ITRiASObjectsEvents * This,
    /* [in] */ IDispatch *Object,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASObjectsEvents_DeletingObjects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsEvents_ObjectsToDelete_Proxy( 
    ITRiASObjectsEvents * This,
    /* [in] */ IDispatch *Object);


void __RPC_STUB ITRiASObjectsEvents_ObjectsToDelete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsEvents_ObjectsDeleted_Proxy( 
    ITRiASObjectsEvents * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASObjectsEvents_ObjectsDeleted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASObjectsEvents_INTERFACE_DEFINED__ */


#ifndef __ITRiASObjectEvents_INTERFACE_DEFINED__
#define __ITRiASObjectEvents_INTERFACE_DEFINED__

/* interface ITRiASObjectEvents */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITRiASObjectEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("25FE9634-F798-11D1-8637-00600875138A")
    ITRiASObjectEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreatingObject( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ObjectToCreate( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ObjectCreated( 
            /* [in] */ IDispatch *Item) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ModifyingObject( 
            /* [in] */ IDispatch *Item,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ObjectToModify( 
            /* [in] */ IDispatch *Item) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ObjectModified( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeletingObject( 
            /* [in] */ IDispatch *Object,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ObjectToDelete( 
            /* [in] */ IDispatch *Object) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ObjectDeleted( 
            /* [in] */ BSTR Name) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASObjectEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASObjectEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASObjectEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASObjectEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreatingObject )( 
            ITRiASObjectEvents * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ObjectToCreate )( 
            ITRiASObjectEvents * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ObjectCreated )( 
            ITRiASObjectEvents * This,
            /* [in] */ IDispatch *Item);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ModifyingObject )( 
            ITRiASObjectEvents * This,
            /* [in] */ IDispatch *Item,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ObjectToModify )( 
            ITRiASObjectEvents * This,
            /* [in] */ IDispatch *Item);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ObjectModified )( 
            ITRiASObjectEvents * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeletingObject )( 
            ITRiASObjectEvents * This,
            /* [in] */ IDispatch *Object,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ObjectToDelete )( 
            ITRiASObjectEvents * This,
            /* [in] */ IDispatch *Object);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ObjectDeleted )( 
            ITRiASObjectEvents * This,
            /* [in] */ BSTR Name);
        
        END_INTERFACE
    } ITRiASObjectEventsVtbl;

    interface ITRiASObjectEvents
    {
        CONST_VTBL struct ITRiASObjectEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASObjectEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASObjectEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASObjectEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASObjectEvents_CreatingObject(This,Name,pVal)	\
    (This)->lpVtbl -> CreatingObject(This,Name,pVal)

#define ITRiASObjectEvents_ObjectToCreate(This,Name)	\
    (This)->lpVtbl -> ObjectToCreate(This,Name)

#define ITRiASObjectEvents_ObjectCreated(This,Item)	\
    (This)->lpVtbl -> ObjectCreated(This,Item)

#define ITRiASObjectEvents_ModifyingObject(This,Item,pVal)	\
    (This)->lpVtbl -> ModifyingObject(This,Item,pVal)

#define ITRiASObjectEvents_ObjectToModify(This,Item)	\
    (This)->lpVtbl -> ObjectToModify(This,Item)

#define ITRiASObjectEvents_ObjectModified(This,Name)	\
    (This)->lpVtbl -> ObjectModified(This,Name)

#define ITRiASObjectEvents_DeletingObject(This,Object,pVal)	\
    (This)->lpVtbl -> DeletingObject(This,Object,pVal)

#define ITRiASObjectEvents_ObjectToDelete(This,Object)	\
    (This)->lpVtbl -> ObjectToDelete(This,Object)

#define ITRiASObjectEvents_ObjectDeleted(This,Name)	\
    (This)->lpVtbl -> ObjectDeleted(This,Name)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectEvents_CreatingObject_Proxy( 
    ITRiASObjectEvents * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASObjectEvents_CreatingObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectEvents_ObjectToCreate_Proxy( 
    ITRiASObjectEvents * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASObjectEvents_ObjectToCreate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectEvents_ObjectCreated_Proxy( 
    ITRiASObjectEvents * This,
    /* [in] */ IDispatch *Item);


void __RPC_STUB ITRiASObjectEvents_ObjectCreated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectEvents_ModifyingObject_Proxy( 
    ITRiASObjectEvents * This,
    /* [in] */ IDispatch *Item,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASObjectEvents_ModifyingObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectEvents_ObjectToModify_Proxy( 
    ITRiASObjectEvents * This,
    /* [in] */ IDispatch *Item);


void __RPC_STUB ITRiASObjectEvents_ObjectToModify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectEvents_ObjectModified_Proxy( 
    ITRiASObjectEvents * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASObjectEvents_ObjectModified_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectEvents_DeletingObject_Proxy( 
    ITRiASObjectEvents * This,
    /* [in] */ IDispatch *Object,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASObjectEvents_DeletingObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectEvents_ObjectToDelete_Proxy( 
    ITRiASObjectEvents * This,
    /* [in] */ IDispatch *Object);


void __RPC_STUB ITRiASObjectEvents_ObjectToDelete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectEvents_ObjectDeleted_Proxy( 
    ITRiASObjectEvents * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASObjectEvents_ObjectDeleted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASObjectEvents_INTERFACE_DEFINED__ */


#ifndef __ITRiASFeatureEvents_INTERFACE_DEFINED__
#define __ITRiASFeatureEvents_INTERFACE_DEFINED__

/* interface ITRiASFeatureEvents */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITRiASFeatureEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3C078223-DE71-11D1-8603-00600875138A")
    ITRiASFeatureEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreatingFeature( 
            /* [in] */ VARIANT NameOrHandle,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FeatureToCreate( 
            /* [in] */ VARIANT NameOrHandle) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FeatureCreated( 
            /* [in] */ IDispatch *Item) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ModifyingFeature( 
            /* [in] */ IDispatch *Item,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FeatureToModify( 
            /* [in] */ IDispatch *Item) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FeatureModified( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeletingFeature( 
            /* [in] */ IDispatch *Item,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FeatureToDelete( 
            /* [in] */ IDispatch *Item) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FeatureDeleted( 
            /* [in] */ BSTR Name) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASFeatureEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASFeatureEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASFeatureEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASFeatureEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreatingFeature )( 
            ITRiASFeatureEvents * This,
            /* [in] */ VARIANT NameOrHandle,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FeatureToCreate )( 
            ITRiASFeatureEvents * This,
            /* [in] */ VARIANT NameOrHandle);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FeatureCreated )( 
            ITRiASFeatureEvents * This,
            /* [in] */ IDispatch *Item);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ModifyingFeature )( 
            ITRiASFeatureEvents * This,
            /* [in] */ IDispatch *Item,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FeatureToModify )( 
            ITRiASFeatureEvents * This,
            /* [in] */ IDispatch *Item);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FeatureModified )( 
            ITRiASFeatureEvents * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeletingFeature )( 
            ITRiASFeatureEvents * This,
            /* [in] */ IDispatch *Item,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FeatureToDelete )( 
            ITRiASFeatureEvents * This,
            /* [in] */ IDispatch *Item);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FeatureDeleted )( 
            ITRiASFeatureEvents * This,
            /* [in] */ BSTR Name);
        
        END_INTERFACE
    } ITRiASFeatureEventsVtbl;

    interface ITRiASFeatureEvents
    {
        CONST_VTBL struct ITRiASFeatureEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASFeatureEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASFeatureEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASFeatureEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASFeatureEvents_CreatingFeature(This,NameOrHandle,pVal)	\
    (This)->lpVtbl -> CreatingFeature(This,NameOrHandle,pVal)

#define ITRiASFeatureEvents_FeatureToCreate(This,NameOrHandle)	\
    (This)->lpVtbl -> FeatureToCreate(This,NameOrHandle)

#define ITRiASFeatureEvents_FeatureCreated(This,Item)	\
    (This)->lpVtbl -> FeatureCreated(This,Item)

#define ITRiASFeatureEvents_ModifyingFeature(This,Item,pVal)	\
    (This)->lpVtbl -> ModifyingFeature(This,Item,pVal)

#define ITRiASFeatureEvents_FeatureToModify(This,Item)	\
    (This)->lpVtbl -> FeatureToModify(This,Item)

#define ITRiASFeatureEvents_FeatureModified(This,Name)	\
    (This)->lpVtbl -> FeatureModified(This,Name)

#define ITRiASFeatureEvents_DeletingFeature(This,Item,pVal)	\
    (This)->lpVtbl -> DeletingFeature(This,Item,pVal)

#define ITRiASFeatureEvents_FeatureToDelete(This,Item)	\
    (This)->lpVtbl -> FeatureToDelete(This,Item)

#define ITRiASFeatureEvents_FeatureDeleted(This,Name)	\
    (This)->lpVtbl -> FeatureDeleted(This,Name)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASFeatureEvents_CreatingFeature_Proxy( 
    ITRiASFeatureEvents * This,
    /* [in] */ VARIANT NameOrHandle,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASFeatureEvents_CreatingFeature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASFeatureEvents_FeatureToCreate_Proxy( 
    ITRiASFeatureEvents * This,
    /* [in] */ VARIANT NameOrHandle);


void __RPC_STUB ITRiASFeatureEvents_FeatureToCreate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASFeatureEvents_FeatureCreated_Proxy( 
    ITRiASFeatureEvents * This,
    /* [in] */ IDispatch *Item);


void __RPC_STUB ITRiASFeatureEvents_FeatureCreated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASFeatureEvents_ModifyingFeature_Proxy( 
    ITRiASFeatureEvents * This,
    /* [in] */ IDispatch *Item,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASFeatureEvents_ModifyingFeature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASFeatureEvents_FeatureToModify_Proxy( 
    ITRiASFeatureEvents * This,
    /* [in] */ IDispatch *Item);


void __RPC_STUB ITRiASFeatureEvents_FeatureToModify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASFeatureEvents_FeatureModified_Proxy( 
    ITRiASFeatureEvents * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASFeatureEvents_FeatureModified_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASFeatureEvents_DeletingFeature_Proxy( 
    ITRiASFeatureEvents * This,
    /* [in] */ IDispatch *Item,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASFeatureEvents_DeletingFeature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASFeatureEvents_FeatureToDelete_Proxy( 
    ITRiASFeatureEvents * This,
    /* [in] */ IDispatch *Item);


void __RPC_STUB ITRiASFeatureEvents_FeatureToDelete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASFeatureEvents_FeatureDeleted_Proxy( 
    ITRiASFeatureEvents * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASFeatureEvents_FeatureDeleted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASFeatureEvents_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_TRiASDB_0260 */
/* [local] */ 

#pragma once





#if !defined(_VISINFOTYPE_DEFINED)
#define _VISINFOTYPE_DEFINED
typedef /* [public] */ 
enum _tagVISINFO_TYPE
    {	VISINFOTYPE_Point	= 0,
	VISINFOTYPE_Line	= 1,
	VISINFOTYPE_Area	= 2,
	VISINFOTYPE_Text	= 5,
	VISINFOTYPE_Unknown	= 6,
	VISINFOTYPE_Default	= 7
    } 	VISINFOTYPE;

#endif // _VISINFOTYPE_DEFINED


extern RPC_IF_HANDLE __MIDL_itf_TRiASDB_0260_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_TRiASDB_0260_v0_0_s_ifspec;

#ifndef __DVisInfo_INTERFACE_DEFINED__
#define __DVisInfo_INTERFACE_DEFINED__

/* interface DVisInfo */
/* [helpstring][uuid][dual][oleautomation][object] */ 

typedef /* [public] */ long TRIASCOLOR;


EXTERN_C const IID IID_DVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0796386B-3123-101C-BB62-00AA0018497C")
    DVisInfo : public DTRiASBaseClass
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Style( 
            /* [retval][out] */ int *Style) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Style( 
            /* [in] */ int Style) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Priority( 
            /* [retval][out] */ int *Prio) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Priority( 
            /* [in] */ int Prio) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *Desc) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR Desc) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_MainColor( 
            /* [retval][out] */ TRIASCOLOR *Main) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_MainColor( 
            /* [in] */ TRIASCOLOR Main) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Changed( 
            /* [retval][out] */ int *Flags) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Changed( 
            /* [in] */ int Flags) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VisString( 
            /* [retval][out] */ BSTR *Desc) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Locatable( 
            /* [retval][out] */ int *Flags) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Locatable( 
            /* [in] */ int Flags) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Visible( 
            /* [retval][out] */ int *Flags) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Visible( 
            /* [in] */ int Flags) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_GeometryName( 
            /* [retval][out] */ BSTR *Desc) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_GeometryName( 
            /* [in] */ BSTR Desc) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct DVisInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            DVisInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            DVisInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            DVisInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            DVisInfo * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            DVisInfo * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            DVisInfo * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            DVisInfo * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_isA )( 
            DVisInfo * This,
            /* [retval][out] */ LONG *RTTI);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            DVisInfo * This,
            /* [retval][out] */ IDispatch **Base);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Parent )( 
            DVisInfo * This,
            /* [in] */ IDispatch *Base);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            DVisInfo * This,
            /* [retval][out] */ IDispatch **App);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Application )( 
            DVisInfo * This,
            /* [in] */ IDispatch *App);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Style )( 
            DVisInfo * This,
            /* [retval][out] */ int *Style);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Style )( 
            DVisInfo * This,
            /* [in] */ int Style);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Priority )( 
            DVisInfo * This,
            /* [retval][out] */ int *Prio);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Priority )( 
            DVisInfo * This,
            /* [in] */ int Prio);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            DVisInfo * This,
            /* [retval][out] */ BSTR *Desc);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            DVisInfo * This,
            /* [in] */ BSTR Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_MainColor )( 
            DVisInfo * This,
            /* [retval][out] */ TRIASCOLOR *Main);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_MainColor )( 
            DVisInfo * This,
            /* [in] */ TRIASCOLOR Main);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Changed )( 
            DVisInfo * This,
            /* [retval][out] */ int *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Changed )( 
            DVisInfo * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_VisString )( 
            DVisInfo * This,
            /* [retval][out] */ BSTR *Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Locatable )( 
            DVisInfo * This,
            /* [retval][out] */ int *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Locatable )( 
            DVisInfo * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Visible )( 
            DVisInfo * This,
            /* [retval][out] */ int *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Visible )( 
            DVisInfo * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_GeometryName )( 
            DVisInfo * This,
            /* [retval][out] */ BSTR *Desc);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_GeometryName )( 
            DVisInfo * This,
            /* [in] */ BSTR Desc);
        
        END_INTERFACE
    } DVisInfoVtbl;

    interface DVisInfo
    {
        CONST_VTBL struct DVisInfoVtbl *lpVtbl;
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

#define DVisInfo_get_Locatable(This,Flags)	\
    (This)->lpVtbl -> get_Locatable(This,Flags)

#define DVisInfo_put_Locatable(This,Flags)	\
    (This)->lpVtbl -> put_Locatable(This,Flags)

#define DVisInfo_get_Visible(This,Flags)	\
    (This)->lpVtbl -> get_Visible(This,Flags)

#define DVisInfo_put_Visible(This,Flags)	\
    (This)->lpVtbl -> put_Visible(This,Flags)

#define DVisInfo_get_GeometryName(This,Desc)	\
    (This)->lpVtbl -> get_GeometryName(This,Desc)

#define DVisInfo_put_GeometryName(This,Desc)	\
    (This)->lpVtbl -> put_GeometryName(This,Desc)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_get_Style_Proxy( 
    DVisInfo * This,
    /* [retval][out] */ int *Style);


void __RPC_STUB DVisInfo_get_Style_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_put_Style_Proxy( 
    DVisInfo * This,
    /* [in] */ int Style);


void __RPC_STUB DVisInfo_put_Style_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_get_Priority_Proxy( 
    DVisInfo * This,
    /* [retval][out] */ int *Prio);


void __RPC_STUB DVisInfo_get_Priority_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_put_Priority_Proxy( 
    DVisInfo * This,
    /* [in] */ int Prio);


void __RPC_STUB DVisInfo_put_Priority_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_get_Name_Proxy( 
    DVisInfo * This,
    /* [retval][out] */ BSTR *Desc);


void __RPC_STUB DVisInfo_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_put_Name_Proxy( 
    DVisInfo * This,
    /* [in] */ BSTR Desc);


void __RPC_STUB DVisInfo_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_get_MainColor_Proxy( 
    DVisInfo * This,
    /* [retval][out] */ TRIASCOLOR *Main);


void __RPC_STUB DVisInfo_get_MainColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_put_MainColor_Proxy( 
    DVisInfo * This,
    /* [in] */ TRIASCOLOR Main);


void __RPC_STUB DVisInfo_put_MainColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_get_Changed_Proxy( 
    DVisInfo * This,
    /* [retval][out] */ int *Flags);


void __RPC_STUB DVisInfo_get_Changed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_put_Changed_Proxy( 
    DVisInfo * This,
    /* [in] */ int Flags);


void __RPC_STUB DVisInfo_put_Changed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_get_VisString_Proxy( 
    DVisInfo * This,
    /* [retval][out] */ BSTR *Desc);


void __RPC_STUB DVisInfo_get_VisString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_get_Locatable_Proxy( 
    DVisInfo * This,
    /* [retval][out] */ int *Flags);


void __RPC_STUB DVisInfo_get_Locatable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_put_Locatable_Proxy( 
    DVisInfo * This,
    /* [in] */ int Flags);


void __RPC_STUB DVisInfo_put_Locatable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_get_Visible_Proxy( 
    DVisInfo * This,
    /* [retval][out] */ int *Flags);


void __RPC_STUB DVisInfo_get_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_put_Visible_Proxy( 
    DVisInfo * This,
    /* [in] */ int Flags);


void __RPC_STUB DVisInfo_put_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_get_GeometryName_Proxy( 
    DVisInfo * This,
    /* [retval][out] */ BSTR *Desc);


void __RPC_STUB DVisInfo_get_GeometryName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DVisInfo_put_GeometryName_Proxy( 
    DVisInfo * This,
    /* [in] */ BSTR Desc);


void __RPC_STUB DVisInfo_put_GeometryName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __DVisInfo_INTERFACE_DEFINED__ */


#ifndef __DPointVisInfo_INTERFACE_DEFINED__
#define __DPointVisInfo_INTERFACE_DEFINED__

/* interface DPointVisInfo */
/* [helpstring][uuid][object][dual][oleautomation] */ 


EXTERN_C const IID IID_DPointVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("07963867-3123-101C-BB62-00AA0018497C")
    DPointVisInfo : public DVisInfo
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SizeX( 
            /* [retval][out] */ int *X) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_SizeX( 
            /* [in] */ int X) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SizeY( 
            /* [retval][out] */ int *Y) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_SizeY( 
            /* [in] */ int Y) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Rotate( 
            /* [retval][out] */ int *Rot) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Rotate( 
            /* [in] */ int Rot) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_BkColor( 
            /* [retval][out] */ TRIASCOLOR *Back) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_BkColor( 
            /* [in] */ TRIASCOLOR Back) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct DPointVisInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            DPointVisInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            DPointVisInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            DPointVisInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            DPointVisInfo * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            DPointVisInfo * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            DPointVisInfo * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            DPointVisInfo * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_isA )( 
            DPointVisInfo * This,
            /* [retval][out] */ LONG *RTTI);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            DPointVisInfo * This,
            /* [retval][out] */ IDispatch **Base);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Parent )( 
            DPointVisInfo * This,
            /* [in] */ IDispatch *Base);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            DPointVisInfo * This,
            /* [retval][out] */ IDispatch **App);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Application )( 
            DPointVisInfo * This,
            /* [in] */ IDispatch *App);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Style )( 
            DPointVisInfo * This,
            /* [retval][out] */ int *Style);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Style )( 
            DPointVisInfo * This,
            /* [in] */ int Style);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Priority )( 
            DPointVisInfo * This,
            /* [retval][out] */ int *Prio);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Priority )( 
            DPointVisInfo * This,
            /* [in] */ int Prio);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            DPointVisInfo * This,
            /* [retval][out] */ BSTR *Desc);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            DPointVisInfo * This,
            /* [in] */ BSTR Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_MainColor )( 
            DPointVisInfo * This,
            /* [retval][out] */ TRIASCOLOR *Main);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_MainColor )( 
            DPointVisInfo * This,
            /* [in] */ TRIASCOLOR Main);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Changed )( 
            DPointVisInfo * This,
            /* [retval][out] */ int *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Changed )( 
            DPointVisInfo * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_VisString )( 
            DPointVisInfo * This,
            /* [retval][out] */ BSTR *Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Locatable )( 
            DPointVisInfo * This,
            /* [retval][out] */ int *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Locatable )( 
            DPointVisInfo * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Visible )( 
            DPointVisInfo * This,
            /* [retval][out] */ int *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Visible )( 
            DPointVisInfo * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_GeometryName )( 
            DPointVisInfo * This,
            /* [retval][out] */ BSTR *Desc);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_GeometryName )( 
            DPointVisInfo * This,
            /* [in] */ BSTR Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SizeX )( 
            DPointVisInfo * This,
            /* [retval][out] */ int *X);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SizeX )( 
            DPointVisInfo * This,
            /* [in] */ int X);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SizeY )( 
            DPointVisInfo * This,
            /* [retval][out] */ int *Y);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SizeY )( 
            DPointVisInfo * This,
            /* [in] */ int Y);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Rotate )( 
            DPointVisInfo * This,
            /* [retval][out] */ int *Rot);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Rotate )( 
            DPointVisInfo * This,
            /* [in] */ int Rot);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_BkColor )( 
            DPointVisInfo * This,
            /* [retval][out] */ TRIASCOLOR *Back);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_BkColor )( 
            DPointVisInfo * This,
            /* [in] */ TRIASCOLOR Back);
        
        END_INTERFACE
    } DPointVisInfoVtbl;

    interface DPointVisInfo
    {
        CONST_VTBL struct DPointVisInfoVtbl *lpVtbl;
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

#define DPointVisInfo_get_Locatable(This,Flags)	\
    (This)->lpVtbl -> get_Locatable(This,Flags)

#define DPointVisInfo_put_Locatable(This,Flags)	\
    (This)->lpVtbl -> put_Locatable(This,Flags)

#define DPointVisInfo_get_Visible(This,Flags)	\
    (This)->lpVtbl -> get_Visible(This,Flags)

#define DPointVisInfo_put_Visible(This,Flags)	\
    (This)->lpVtbl -> put_Visible(This,Flags)

#define DPointVisInfo_get_GeometryName(This,Desc)	\
    (This)->lpVtbl -> get_GeometryName(This,Desc)

#define DPointVisInfo_put_GeometryName(This,Desc)	\
    (This)->lpVtbl -> put_GeometryName(This,Desc)


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
    DPointVisInfo * This,
    /* [retval][out] */ int *X);


void __RPC_STUB DPointVisInfo_get_SizeX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DPointVisInfo_put_SizeX_Proxy( 
    DPointVisInfo * This,
    /* [in] */ int X);


void __RPC_STUB DPointVisInfo_put_SizeX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DPointVisInfo_get_SizeY_Proxy( 
    DPointVisInfo * This,
    /* [retval][out] */ int *Y);


void __RPC_STUB DPointVisInfo_get_SizeY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DPointVisInfo_put_SizeY_Proxy( 
    DPointVisInfo * This,
    /* [in] */ int Y);


void __RPC_STUB DPointVisInfo_put_SizeY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DPointVisInfo_get_Rotate_Proxy( 
    DPointVisInfo * This,
    /* [retval][out] */ int *Rot);


void __RPC_STUB DPointVisInfo_get_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DPointVisInfo_put_Rotate_Proxy( 
    DPointVisInfo * This,
    /* [in] */ int Rot);


void __RPC_STUB DPointVisInfo_put_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DPointVisInfo_get_BkColor_Proxy( 
    DPointVisInfo * This,
    /* [retval][out] */ TRIASCOLOR *Back);


void __RPC_STUB DPointVisInfo_get_BkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DPointVisInfo_put_BkColor_Proxy( 
    DPointVisInfo * This,
    /* [in] */ TRIASCOLOR Back);


void __RPC_STUB DPointVisInfo_put_BkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __DPointVisInfo_INTERFACE_DEFINED__ */


#ifndef __DLineVisInfo_INTERFACE_DEFINED__
#define __DLineVisInfo_INTERFACE_DEFINED__

/* interface DLineVisInfo */
/* [helpstring][uuid][dual][oleautomation][object] */ 


EXTERN_C const IID IID_DLineVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("07963868-3123-101C-BB62-00AA0018497C")
    DLineVisInfo : public DVisInfo
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ int *Width) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ int Width) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct DLineVisInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            DLineVisInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            DLineVisInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            DLineVisInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            DLineVisInfo * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            DLineVisInfo * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            DLineVisInfo * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            DLineVisInfo * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_isA )( 
            DLineVisInfo * This,
            /* [retval][out] */ LONG *RTTI);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            DLineVisInfo * This,
            /* [retval][out] */ IDispatch **Base);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Parent )( 
            DLineVisInfo * This,
            /* [in] */ IDispatch *Base);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            DLineVisInfo * This,
            /* [retval][out] */ IDispatch **App);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Application )( 
            DLineVisInfo * This,
            /* [in] */ IDispatch *App);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Style )( 
            DLineVisInfo * This,
            /* [retval][out] */ int *Style);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Style )( 
            DLineVisInfo * This,
            /* [in] */ int Style);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Priority )( 
            DLineVisInfo * This,
            /* [retval][out] */ int *Prio);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Priority )( 
            DLineVisInfo * This,
            /* [in] */ int Prio);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            DLineVisInfo * This,
            /* [retval][out] */ BSTR *Desc);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            DLineVisInfo * This,
            /* [in] */ BSTR Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_MainColor )( 
            DLineVisInfo * This,
            /* [retval][out] */ TRIASCOLOR *Main);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_MainColor )( 
            DLineVisInfo * This,
            /* [in] */ TRIASCOLOR Main);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Changed )( 
            DLineVisInfo * This,
            /* [retval][out] */ int *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Changed )( 
            DLineVisInfo * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_VisString )( 
            DLineVisInfo * This,
            /* [retval][out] */ BSTR *Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Locatable )( 
            DLineVisInfo * This,
            /* [retval][out] */ int *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Locatable )( 
            DLineVisInfo * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Visible )( 
            DLineVisInfo * This,
            /* [retval][out] */ int *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Visible )( 
            DLineVisInfo * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_GeometryName )( 
            DLineVisInfo * This,
            /* [retval][out] */ BSTR *Desc);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_GeometryName )( 
            DLineVisInfo * This,
            /* [in] */ BSTR Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            DLineVisInfo * This,
            /* [retval][out] */ int *Width);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Width )( 
            DLineVisInfo * This,
            /* [in] */ int Width);
        
        END_INTERFACE
    } DLineVisInfoVtbl;

    interface DLineVisInfo
    {
        CONST_VTBL struct DLineVisInfoVtbl *lpVtbl;
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

#define DLineVisInfo_get_Locatable(This,Flags)	\
    (This)->lpVtbl -> get_Locatable(This,Flags)

#define DLineVisInfo_put_Locatable(This,Flags)	\
    (This)->lpVtbl -> put_Locatable(This,Flags)

#define DLineVisInfo_get_Visible(This,Flags)	\
    (This)->lpVtbl -> get_Visible(This,Flags)

#define DLineVisInfo_put_Visible(This,Flags)	\
    (This)->lpVtbl -> put_Visible(This,Flags)

#define DLineVisInfo_get_GeometryName(This,Desc)	\
    (This)->lpVtbl -> get_GeometryName(This,Desc)

#define DLineVisInfo_put_GeometryName(This,Desc)	\
    (This)->lpVtbl -> put_GeometryName(This,Desc)


#define DLineVisInfo_get_Width(This,Width)	\
    (This)->lpVtbl -> get_Width(This,Width)

#define DLineVisInfo_put_Width(This,Width)	\
    (This)->lpVtbl -> put_Width(This,Width)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DLineVisInfo_get_Width_Proxy( 
    DLineVisInfo * This,
    /* [retval][out] */ int *Width);


void __RPC_STUB DLineVisInfo_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DLineVisInfo_put_Width_Proxy( 
    DLineVisInfo * This,
    /* [in] */ int Width);


void __RPC_STUB DLineVisInfo_put_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __DLineVisInfo_INTERFACE_DEFINED__ */


#ifndef __DAreaVisInfo_INTERFACE_DEFINED__
#define __DAreaVisInfo_INTERFACE_DEFINED__

/* interface DAreaVisInfo */
/* [helpstring][uuid][object][dual][oleautomation] */ 


EXTERN_C const IID IID_DAreaVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("07963869-3123-101C-BB62-00AA0018497C")
    DAreaVisInfo : public DVisInfo
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ int *Width) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ int Width) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Opaque( 
            /* [retval][out] */ int *IsOpaque) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Opaque( 
            /* [in] */ int IsOpaque) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_BkContour( 
            /* [retval][out] */ int *BkContour) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_BkContour( 
            /* [in] */ int BkContour) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_BkColor( 
            /* [retval][out] */ TRIASCOLOR *Back) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_BkColor( 
            /* [in] */ TRIASCOLOR Back) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct DAreaVisInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            DAreaVisInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            DAreaVisInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            DAreaVisInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            DAreaVisInfo * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            DAreaVisInfo * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            DAreaVisInfo * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            DAreaVisInfo * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_isA )( 
            DAreaVisInfo * This,
            /* [retval][out] */ LONG *RTTI);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            DAreaVisInfo * This,
            /* [retval][out] */ IDispatch **Base);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Parent )( 
            DAreaVisInfo * This,
            /* [in] */ IDispatch *Base);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            DAreaVisInfo * This,
            /* [retval][out] */ IDispatch **App);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Application )( 
            DAreaVisInfo * This,
            /* [in] */ IDispatch *App);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Style )( 
            DAreaVisInfo * This,
            /* [retval][out] */ int *Style);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Style )( 
            DAreaVisInfo * This,
            /* [in] */ int Style);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Priority )( 
            DAreaVisInfo * This,
            /* [retval][out] */ int *Prio);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Priority )( 
            DAreaVisInfo * This,
            /* [in] */ int Prio);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            DAreaVisInfo * This,
            /* [retval][out] */ BSTR *Desc);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            DAreaVisInfo * This,
            /* [in] */ BSTR Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_MainColor )( 
            DAreaVisInfo * This,
            /* [retval][out] */ TRIASCOLOR *Main);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_MainColor )( 
            DAreaVisInfo * This,
            /* [in] */ TRIASCOLOR Main);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Changed )( 
            DAreaVisInfo * This,
            /* [retval][out] */ int *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Changed )( 
            DAreaVisInfo * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_VisString )( 
            DAreaVisInfo * This,
            /* [retval][out] */ BSTR *Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Locatable )( 
            DAreaVisInfo * This,
            /* [retval][out] */ int *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Locatable )( 
            DAreaVisInfo * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Visible )( 
            DAreaVisInfo * This,
            /* [retval][out] */ int *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Visible )( 
            DAreaVisInfo * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_GeometryName )( 
            DAreaVisInfo * This,
            /* [retval][out] */ BSTR *Desc);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_GeometryName )( 
            DAreaVisInfo * This,
            /* [in] */ BSTR Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            DAreaVisInfo * This,
            /* [retval][out] */ int *Width);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Width )( 
            DAreaVisInfo * This,
            /* [in] */ int Width);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Opaque )( 
            DAreaVisInfo * This,
            /* [retval][out] */ int *IsOpaque);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Opaque )( 
            DAreaVisInfo * This,
            /* [in] */ int IsOpaque);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_BkContour )( 
            DAreaVisInfo * This,
            /* [retval][out] */ int *BkContour);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_BkContour )( 
            DAreaVisInfo * This,
            /* [in] */ int BkContour);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_BkColor )( 
            DAreaVisInfo * This,
            /* [retval][out] */ TRIASCOLOR *Back);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_BkColor )( 
            DAreaVisInfo * This,
            /* [in] */ TRIASCOLOR Back);
        
        END_INTERFACE
    } DAreaVisInfoVtbl;

    interface DAreaVisInfo
    {
        CONST_VTBL struct DAreaVisInfoVtbl *lpVtbl;
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

#define DAreaVisInfo_get_Locatable(This,Flags)	\
    (This)->lpVtbl -> get_Locatable(This,Flags)

#define DAreaVisInfo_put_Locatable(This,Flags)	\
    (This)->lpVtbl -> put_Locatable(This,Flags)

#define DAreaVisInfo_get_Visible(This,Flags)	\
    (This)->lpVtbl -> get_Visible(This,Flags)

#define DAreaVisInfo_put_Visible(This,Flags)	\
    (This)->lpVtbl -> put_Visible(This,Flags)

#define DAreaVisInfo_get_GeometryName(This,Desc)	\
    (This)->lpVtbl -> get_GeometryName(This,Desc)

#define DAreaVisInfo_put_GeometryName(This,Desc)	\
    (This)->lpVtbl -> put_GeometryName(This,Desc)


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
    DAreaVisInfo * This,
    /* [retval][out] */ int *Width);


void __RPC_STUB DAreaVisInfo_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DAreaVisInfo_put_Width_Proxy( 
    DAreaVisInfo * This,
    /* [in] */ int Width);


void __RPC_STUB DAreaVisInfo_put_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DAreaVisInfo_get_Opaque_Proxy( 
    DAreaVisInfo * This,
    /* [retval][out] */ int *IsOpaque);


void __RPC_STUB DAreaVisInfo_get_Opaque_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DAreaVisInfo_put_Opaque_Proxy( 
    DAreaVisInfo * This,
    /* [in] */ int IsOpaque);


void __RPC_STUB DAreaVisInfo_put_Opaque_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DAreaVisInfo_get_BkContour_Proxy( 
    DAreaVisInfo * This,
    /* [retval][out] */ int *BkContour);


void __RPC_STUB DAreaVisInfo_get_BkContour_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DAreaVisInfo_put_BkContour_Proxy( 
    DAreaVisInfo * This,
    /* [in] */ int BkContour);


void __RPC_STUB DAreaVisInfo_put_BkContour_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DAreaVisInfo_get_BkColor_Proxy( 
    DAreaVisInfo * This,
    /* [retval][out] */ TRIASCOLOR *Back);


void __RPC_STUB DAreaVisInfo_get_BkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DAreaVisInfo_put_BkColor_Proxy( 
    DAreaVisInfo * This,
    /* [in] */ TRIASCOLOR Back);


void __RPC_STUB DAreaVisInfo_put_BkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __DAreaVisInfo_INTERFACE_DEFINED__ */


#ifndef __DTextVisInfo_INTERFACE_DEFINED__
#define __DTextVisInfo_INTERFACE_DEFINED__

/* interface DTextVisInfo */
/* [helpstring][uuid][object][dual][oleautomation] */ 

#if !defined(_TEXTVISINFO_DEFINED)
#define _TEXTVISINFO_DEFINED
typedef /* [public] */ 
enum _tagALIGNSTYLE
    {	ALIGNSTYLE_Left	= 0,
	ALIGNSTYLE_Centre	= 1,
	ALIGNSTYLE_Right	= 2,
	ALIGNSTYLE_Full	= 3
    } 	ALIGNSTYLE;

typedef /* [public] */ 
enum _tagFRAMESTYLE
    {	FRAMESTYLE_NoFrame	= 0,
	FRAMESTYLE_SimpleFrame	= 0x1,
	FRAMESTYLE_Rounded	= 0x2,
	FRAMESTYLE_TargetColor	= 0x4
    } 	FRAMESTYLE;

#endif // _TEXTVISINFO_DEFINED

EXTERN_C const IID IID_DTextVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0796386A-3123-101C-BB62-00AA0018497C")
    DTextVisInfo : public DVisInfo
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SizeX( 
            /* [retval][out] */ int *X) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_SizeX( 
            /* [in] */ int X) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SizeY( 
            /* [retval][out] */ int *Y) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_SizeY( 
            /* [in] */ int Y) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Bold( 
            /* [retval][out] */ int *IsBold) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Bold( 
            /* [in] */ int IsBold) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Italic( 
            /* [retval][out] */ int *IsItalic) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Italic( 
            /* [in] */ int IsItalic) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Underline( 
            /* [retval][out] */ int *IsUnderlined) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Underline( 
            /* [in] */ int IsUnderlined) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_StrikeThrough( 
            /* [retval][out] */ int *IsStrikedThrough) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_StrikeThrough( 
            /* [in] */ int IsStrikedThrough) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_FrameStyle( 
            /* [retval][out] */ FRAMESTYLE *FrameStyle) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_FrameStyle( 
            /* [in] */ FRAMESTYLE FrameStyle) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_AlignStyle( 
            /* [retval][out] */ ALIGNSTYLE *AlignStyle) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_AlignStyle( 
            /* [in] */ ALIGNSTYLE AlignStyle) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Rotate( 
            /* [retval][out] */ int *Rot) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Rotate( 
            /* [in] */ int Rot) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Slant( 
            /* [retval][out] */ int *Slant) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Slant( 
            /* [in] */ int Slant) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct DTextVisInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            DTextVisInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            DTextVisInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            DTextVisInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            DTextVisInfo * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            DTextVisInfo * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            DTextVisInfo * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            DTextVisInfo * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_isA )( 
            DTextVisInfo * This,
            /* [retval][out] */ LONG *RTTI);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            DTextVisInfo * This,
            /* [retval][out] */ IDispatch **Base);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Parent )( 
            DTextVisInfo * This,
            /* [in] */ IDispatch *Base);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            DTextVisInfo * This,
            /* [retval][out] */ IDispatch **App);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Application )( 
            DTextVisInfo * This,
            /* [in] */ IDispatch *App);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Style )( 
            DTextVisInfo * This,
            /* [retval][out] */ int *Style);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Style )( 
            DTextVisInfo * This,
            /* [in] */ int Style);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Priority )( 
            DTextVisInfo * This,
            /* [retval][out] */ int *Prio);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Priority )( 
            DTextVisInfo * This,
            /* [in] */ int Prio);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            DTextVisInfo * This,
            /* [retval][out] */ BSTR *Desc);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            DTextVisInfo * This,
            /* [in] */ BSTR Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_MainColor )( 
            DTextVisInfo * This,
            /* [retval][out] */ TRIASCOLOR *Main);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_MainColor )( 
            DTextVisInfo * This,
            /* [in] */ TRIASCOLOR Main);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Changed )( 
            DTextVisInfo * This,
            /* [retval][out] */ int *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Changed )( 
            DTextVisInfo * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_VisString )( 
            DTextVisInfo * This,
            /* [retval][out] */ BSTR *Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Locatable )( 
            DTextVisInfo * This,
            /* [retval][out] */ int *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Locatable )( 
            DTextVisInfo * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Visible )( 
            DTextVisInfo * This,
            /* [retval][out] */ int *Flags);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Visible )( 
            DTextVisInfo * This,
            /* [in] */ int Flags);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_GeometryName )( 
            DTextVisInfo * This,
            /* [retval][out] */ BSTR *Desc);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_GeometryName )( 
            DTextVisInfo * This,
            /* [in] */ BSTR Desc);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SizeX )( 
            DTextVisInfo * This,
            /* [retval][out] */ int *X);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SizeX )( 
            DTextVisInfo * This,
            /* [in] */ int X);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SizeY )( 
            DTextVisInfo * This,
            /* [retval][out] */ int *Y);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SizeY )( 
            DTextVisInfo * This,
            /* [in] */ int Y);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Bold )( 
            DTextVisInfo * This,
            /* [retval][out] */ int *IsBold);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Bold )( 
            DTextVisInfo * This,
            /* [in] */ int IsBold);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Italic )( 
            DTextVisInfo * This,
            /* [retval][out] */ int *IsItalic);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Italic )( 
            DTextVisInfo * This,
            /* [in] */ int IsItalic);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Underline )( 
            DTextVisInfo * This,
            /* [retval][out] */ int *IsUnderlined);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Underline )( 
            DTextVisInfo * This,
            /* [in] */ int IsUnderlined);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_StrikeThrough )( 
            DTextVisInfo * This,
            /* [retval][out] */ int *IsStrikedThrough);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_StrikeThrough )( 
            DTextVisInfo * This,
            /* [in] */ int IsStrikedThrough);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_FrameStyle )( 
            DTextVisInfo * This,
            /* [retval][out] */ FRAMESTYLE *FrameStyle);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_FrameStyle )( 
            DTextVisInfo * This,
            /* [in] */ FRAMESTYLE FrameStyle);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_AlignStyle )( 
            DTextVisInfo * This,
            /* [retval][out] */ ALIGNSTYLE *AlignStyle);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_AlignStyle )( 
            DTextVisInfo * This,
            /* [in] */ ALIGNSTYLE AlignStyle);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Rotate )( 
            DTextVisInfo * This,
            /* [retval][out] */ int *Rot);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Rotate )( 
            DTextVisInfo * This,
            /* [in] */ int Rot);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Slant )( 
            DTextVisInfo * This,
            /* [retval][out] */ int *Slant);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Slant )( 
            DTextVisInfo * This,
            /* [in] */ int Slant);
        
        END_INTERFACE
    } DTextVisInfoVtbl;

    interface DTextVisInfo
    {
        CONST_VTBL struct DTextVisInfoVtbl *lpVtbl;
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

#define DTextVisInfo_get_Locatable(This,Flags)	\
    (This)->lpVtbl -> get_Locatable(This,Flags)

#define DTextVisInfo_put_Locatable(This,Flags)	\
    (This)->lpVtbl -> put_Locatable(This,Flags)

#define DTextVisInfo_get_Visible(This,Flags)	\
    (This)->lpVtbl -> get_Visible(This,Flags)

#define DTextVisInfo_put_Visible(This,Flags)	\
    (This)->lpVtbl -> put_Visible(This,Flags)

#define DTextVisInfo_get_GeometryName(This,Desc)	\
    (This)->lpVtbl -> get_GeometryName(This,Desc)

#define DTextVisInfo_put_GeometryName(This,Desc)	\
    (This)->lpVtbl -> put_GeometryName(This,Desc)


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
    DTextVisInfo * This,
    /* [retval][out] */ int *X);


void __RPC_STUB DTextVisInfo_get_SizeX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_put_SizeX_Proxy( 
    DTextVisInfo * This,
    /* [in] */ int X);


void __RPC_STUB DTextVisInfo_put_SizeX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_get_SizeY_Proxy( 
    DTextVisInfo * This,
    /* [retval][out] */ int *Y);


void __RPC_STUB DTextVisInfo_get_SizeY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_put_SizeY_Proxy( 
    DTextVisInfo * This,
    /* [in] */ int Y);


void __RPC_STUB DTextVisInfo_put_SizeY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_get_Bold_Proxy( 
    DTextVisInfo * This,
    /* [retval][out] */ int *IsBold);


void __RPC_STUB DTextVisInfo_get_Bold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_put_Bold_Proxy( 
    DTextVisInfo * This,
    /* [in] */ int IsBold);


void __RPC_STUB DTextVisInfo_put_Bold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_get_Italic_Proxy( 
    DTextVisInfo * This,
    /* [retval][out] */ int *IsItalic);


void __RPC_STUB DTextVisInfo_get_Italic_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_put_Italic_Proxy( 
    DTextVisInfo * This,
    /* [in] */ int IsItalic);


void __RPC_STUB DTextVisInfo_put_Italic_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_get_Underline_Proxy( 
    DTextVisInfo * This,
    /* [retval][out] */ int *IsUnderlined);


void __RPC_STUB DTextVisInfo_get_Underline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_put_Underline_Proxy( 
    DTextVisInfo * This,
    /* [in] */ int IsUnderlined);


void __RPC_STUB DTextVisInfo_put_Underline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_get_StrikeThrough_Proxy( 
    DTextVisInfo * This,
    /* [retval][out] */ int *IsStrikedThrough);


void __RPC_STUB DTextVisInfo_get_StrikeThrough_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_put_StrikeThrough_Proxy( 
    DTextVisInfo * This,
    /* [in] */ int IsStrikedThrough);


void __RPC_STUB DTextVisInfo_put_StrikeThrough_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_get_FrameStyle_Proxy( 
    DTextVisInfo * This,
    /* [retval][out] */ FRAMESTYLE *FrameStyle);


void __RPC_STUB DTextVisInfo_get_FrameStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_put_FrameStyle_Proxy( 
    DTextVisInfo * This,
    /* [in] */ FRAMESTYLE FrameStyle);


void __RPC_STUB DTextVisInfo_put_FrameStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_get_AlignStyle_Proxy( 
    DTextVisInfo * This,
    /* [retval][out] */ ALIGNSTYLE *AlignStyle);


void __RPC_STUB DTextVisInfo_get_AlignStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_put_AlignStyle_Proxy( 
    DTextVisInfo * This,
    /* [in] */ ALIGNSTYLE AlignStyle);


void __RPC_STUB DTextVisInfo_put_AlignStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_get_Rotate_Proxy( 
    DTextVisInfo * This,
    /* [retval][out] */ int *Rot);


void __RPC_STUB DTextVisInfo_get_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_put_Rotate_Proxy( 
    DTextVisInfo * This,
    /* [in] */ int Rot);


void __RPC_STUB DTextVisInfo_put_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_get_Slant_Proxy( 
    DTextVisInfo * This,
    /* [retval][out] */ int *Slant);


void __RPC_STUB DTextVisInfo_get_Slant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE DTextVisInfo_put_Slant_Proxy( 
    DTextVisInfo * This,
    /* [in] */ int Slant);


void __RPC_STUB DTextVisInfo_put_Slant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __DTextVisInfo_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_TRiASDB_0281 */
/* [local] */ 







extern RPC_IF_HANDLE __MIDL_itf_TRiASDB_0281_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_TRiASDB_0281_v0_0_s_ifspec;

#ifndef __IParseRegularExpression_INTERFACE_DEFINED__
#define __IParseRegularExpression_INTERFACE_DEFINED__

/* interface IParseRegularExpression */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IParseRegularExpression;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C21AAF92-2DE5-11D1-969A-00A024D6F582")
    IParseRegularExpression : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Pattern( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Pattern( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Groups( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Group( 
            /* [in] */ long Index,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Match( 
            /* [in] */ BSTR ToMatch,
            /* [optional][in] */ VARIANT StartAt,
            /* [optional][in] */ VARIANT MatchLen,
            /* [retval][out] */ long *Matched) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Search( 
            /* [in] */ BSTR ToSearch,
            /* [optional][out][in] */ VARIANT *StartAt,
            /* [optional][out][in] */ VARIANT *SearchLen,
            /* [retval][out] */ BSTR *Found) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Replace( 
            /* [in] */ BSTR ToReplace,
            /* [in] */ BSTR NewString,
            /* [optional][in] */ VARIANT ToStart,
            /* [optional][in] */ VARIANT ReplaceLen,
            /* [optional][in] */ VARIANT Global,
            /* [retval][out] */ BSTR *Result) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IParseRegularExpressionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IParseRegularExpression * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IParseRegularExpression * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IParseRegularExpression * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IParseRegularExpression * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IParseRegularExpression * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IParseRegularExpression * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IParseRegularExpression * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Pattern )( 
            IParseRegularExpression * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Pattern )( 
            IParseRegularExpression * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Groups )( 
            IParseRegularExpression * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Group )( 
            IParseRegularExpression * This,
            /* [in] */ long Index,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Match )( 
            IParseRegularExpression * This,
            /* [in] */ BSTR ToMatch,
            /* [optional][in] */ VARIANT StartAt,
            /* [optional][in] */ VARIANT MatchLen,
            /* [retval][out] */ long *Matched);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Search )( 
            IParseRegularExpression * This,
            /* [in] */ BSTR ToSearch,
            /* [optional][out][in] */ VARIANT *StartAt,
            /* [optional][out][in] */ VARIANT *SearchLen,
            /* [retval][out] */ BSTR *Found);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Replace )( 
            IParseRegularExpression * This,
            /* [in] */ BSTR ToReplace,
            /* [in] */ BSTR NewString,
            /* [optional][in] */ VARIANT ToStart,
            /* [optional][in] */ VARIANT ReplaceLen,
            /* [optional][in] */ VARIANT Global,
            /* [retval][out] */ BSTR *Result);
        
        END_INTERFACE
    } IParseRegularExpressionVtbl;

    interface IParseRegularExpression
    {
        CONST_VTBL struct IParseRegularExpressionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IParseRegularExpression_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IParseRegularExpression_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IParseRegularExpression_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IParseRegularExpression_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IParseRegularExpression_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IParseRegularExpression_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IParseRegularExpression_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IParseRegularExpression_get_Pattern(This,pVal)	\
    (This)->lpVtbl -> get_Pattern(This,pVal)

#define IParseRegularExpression_put_Pattern(This,newVal)	\
    (This)->lpVtbl -> put_Pattern(This,newVal)

#define IParseRegularExpression_get_Groups(This,pVal)	\
    (This)->lpVtbl -> get_Groups(This,pVal)

#define IParseRegularExpression_get_Group(This,Index,pVal)	\
    (This)->lpVtbl -> get_Group(This,Index,pVal)

#define IParseRegularExpression_Match(This,ToMatch,StartAt,MatchLen,Matched)	\
    (This)->lpVtbl -> Match(This,ToMatch,StartAt,MatchLen,Matched)

#define IParseRegularExpression_Search(This,ToSearch,StartAt,SearchLen,Found)	\
    (This)->lpVtbl -> Search(This,ToSearch,StartAt,SearchLen,Found)

#define IParseRegularExpression_Replace(This,ToReplace,NewString,ToStart,ReplaceLen,Global,Result)	\
    (This)->lpVtbl -> Replace(This,ToReplace,NewString,ToStart,ReplaceLen,Global,Result)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IParseRegularExpression_get_Pattern_Proxy( 
    IParseRegularExpression * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IParseRegularExpression_get_Pattern_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IParseRegularExpression_put_Pattern_Proxy( 
    IParseRegularExpression * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IParseRegularExpression_put_Pattern_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IParseRegularExpression_get_Groups_Proxy( 
    IParseRegularExpression * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IParseRegularExpression_get_Groups_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IParseRegularExpression_get_Group_Proxy( 
    IParseRegularExpression * This,
    /* [in] */ long Index,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IParseRegularExpression_get_Group_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IParseRegularExpression_Match_Proxy( 
    IParseRegularExpression * This,
    /* [in] */ BSTR ToMatch,
    /* [optional][in] */ VARIANT StartAt,
    /* [optional][in] */ VARIANT MatchLen,
    /* [retval][out] */ long *Matched);


void __RPC_STUB IParseRegularExpression_Match_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IParseRegularExpression_Search_Proxy( 
    IParseRegularExpression * This,
    /* [in] */ BSTR ToSearch,
    /* [optional][out][in] */ VARIANT *StartAt,
    /* [optional][out][in] */ VARIANT *SearchLen,
    /* [retval][out] */ BSTR *Found);


void __RPC_STUB IParseRegularExpression_Search_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IParseRegularExpression_Replace_Proxy( 
    IParseRegularExpression * This,
    /* [in] */ BSTR ToReplace,
    /* [in] */ BSTR NewString,
    /* [optional][in] */ VARIANT ToStart,
    /* [optional][in] */ VARIANT ReplaceLen,
    /* [optional][in] */ VARIANT Global,
    /* [retval][out] */ BSTR *Result);


void __RPC_STUB IParseRegularExpression_Replace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IParseRegularExpression_INTERFACE_DEFINED__ */


#ifndef __IParseStringPairs_INTERFACE_DEFINED__
#define __IParseStringPairs_INTERFACE_DEFINED__

/* interface IParseStringPairs */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IParseStringPairs;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C21AAF95-2DE5-11D1-969A-00A024D6F582")
    IParseStringPairs : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Pattern( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Pattern( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [in] */ BSTR Key,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Parse( 
            /* [in] */ BSTR ToParse,
            /* [retval][out] */ long *Pairs) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetKeyStrings( 
            /* [retval][out] */ IUnknown **Keys) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitObject( 
            /* [in] */ IUnknown *pIUnk,
            /* [optional][in] */ VARIANT ErrorLog) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IParseStringPairsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IParseStringPairs * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IParseStringPairs * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IParseStringPairs * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IParseStringPairs * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IParseStringPairs * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IParseStringPairs * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IParseStringPairs * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Pattern )( 
            IParseStringPairs * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Pattern )( 
            IParseStringPairs * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IParseStringPairs * This,
            /* [in] */ BSTR Key,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Parse )( 
            IParseStringPairs * This,
            /* [in] */ BSTR ToParse,
            /* [retval][out] */ long *Pairs);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetKeyStrings )( 
            IParseStringPairs * This,
            /* [retval][out] */ IUnknown **Keys);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InitObject )( 
            IParseStringPairs * This,
            /* [in] */ IUnknown *pIUnk,
            /* [optional][in] */ VARIANT ErrorLog);
        
        END_INTERFACE
    } IParseStringPairsVtbl;

    interface IParseStringPairs
    {
        CONST_VTBL struct IParseStringPairsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IParseStringPairs_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IParseStringPairs_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IParseStringPairs_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IParseStringPairs_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IParseStringPairs_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IParseStringPairs_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IParseStringPairs_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IParseStringPairs_get_Pattern(This,pVal)	\
    (This)->lpVtbl -> get_Pattern(This,pVal)

#define IParseStringPairs_put_Pattern(This,newVal)	\
    (This)->lpVtbl -> put_Pattern(This,newVal)

#define IParseStringPairs_get_Value(This,Key,pVal)	\
    (This)->lpVtbl -> get_Value(This,Key,pVal)

#define IParseStringPairs_Parse(This,ToParse,Pairs)	\
    (This)->lpVtbl -> Parse(This,ToParse,Pairs)

#define IParseStringPairs_GetKeyStrings(This,Keys)	\
    (This)->lpVtbl -> GetKeyStrings(This,Keys)

#define IParseStringPairs_InitObject(This,pIUnk,ErrorLog)	\
    (This)->lpVtbl -> InitObject(This,pIUnk,ErrorLog)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IParseStringPairs_get_Pattern_Proxy( 
    IParseStringPairs * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IParseStringPairs_get_Pattern_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IParseStringPairs_put_Pattern_Proxy( 
    IParseStringPairs * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IParseStringPairs_put_Pattern_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IParseStringPairs_get_Value_Proxy( 
    IParseStringPairs * This,
    /* [in] */ BSTR Key,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IParseStringPairs_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IParseStringPairs_Parse_Proxy( 
    IParseStringPairs * This,
    /* [in] */ BSTR ToParse,
    /* [retval][out] */ long *Pairs);


void __RPC_STUB IParseStringPairs_Parse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IParseStringPairs_GetKeyStrings_Proxy( 
    IParseStringPairs * This,
    /* [retval][out] */ IUnknown **Keys);


void __RPC_STUB IParseStringPairs_GetKeyStrings_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IParseStringPairs_InitObject_Proxy( 
    IParseStringPairs * This,
    /* [in] */ IUnknown *pIUnk,
    /* [optional][in] */ VARIANT ErrorLog);


void __RPC_STUB IParseStringPairs_InitObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IParseStringPairs_INTERFACE_DEFINED__ */


#ifndef __IParseStringPairs2_INTERFACE_DEFINED__
#define __IParseStringPairs2_INTERFACE_DEFINED__

/* interface IParseStringPairs2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IParseStringPairs2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1A61EAD7-9298-4EEA-B626-47B043CF75E2")
    IParseStringPairs2 : public IParseStringPairs
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeletePair( 
            /* [in] */ BSTR Key) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IParseStringPairs2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IParseStringPairs2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IParseStringPairs2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IParseStringPairs2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IParseStringPairs2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IParseStringPairs2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IParseStringPairs2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IParseStringPairs2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Pattern )( 
            IParseStringPairs2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Pattern )( 
            IParseStringPairs2 * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IParseStringPairs2 * This,
            /* [in] */ BSTR Key,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Parse )( 
            IParseStringPairs2 * This,
            /* [in] */ BSTR ToParse,
            /* [retval][out] */ long *Pairs);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetKeyStrings )( 
            IParseStringPairs2 * This,
            /* [retval][out] */ IUnknown **Keys);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InitObject )( 
            IParseStringPairs2 * This,
            /* [in] */ IUnknown *pIUnk,
            /* [optional][in] */ VARIANT ErrorLog);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeletePair )( 
            IParseStringPairs2 * This,
            /* [in] */ BSTR Key);
        
        END_INTERFACE
    } IParseStringPairs2Vtbl;

    interface IParseStringPairs2
    {
        CONST_VTBL struct IParseStringPairs2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IParseStringPairs2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IParseStringPairs2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IParseStringPairs2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IParseStringPairs2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IParseStringPairs2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IParseStringPairs2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IParseStringPairs2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IParseStringPairs2_get_Pattern(This,pVal)	\
    (This)->lpVtbl -> get_Pattern(This,pVal)

#define IParseStringPairs2_put_Pattern(This,newVal)	\
    (This)->lpVtbl -> put_Pattern(This,newVal)

#define IParseStringPairs2_get_Value(This,Key,pVal)	\
    (This)->lpVtbl -> get_Value(This,Key,pVal)

#define IParseStringPairs2_Parse(This,ToParse,Pairs)	\
    (This)->lpVtbl -> Parse(This,ToParse,Pairs)

#define IParseStringPairs2_GetKeyStrings(This,Keys)	\
    (This)->lpVtbl -> GetKeyStrings(This,Keys)

#define IParseStringPairs2_InitObject(This,pIUnk,ErrorLog)	\
    (This)->lpVtbl -> InitObject(This,pIUnk,ErrorLog)


#define IParseStringPairs2_DeletePair(This,Key)	\
    (This)->lpVtbl -> DeletePair(This,Key)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IParseStringPairs2_DeletePair_Proxy( 
    IParseStringPairs2 * This,
    /* [in] */ BSTR Key);


void __RPC_STUB IParseStringPairs2_DeletePair_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IParseStringPairs2_INTERFACE_DEFINED__ */


#ifndef __IComposeStringPairs_INTERFACE_DEFINED__
#define __IComposeStringPairs_INTERFACE_DEFINED__

/* interface IComposeStringPairs */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IComposeStringPairs;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6B77F344-A121-11D1-BA21-080036D63803")
    IComposeStringPairs : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ComposedData( 
            /* [in] */ BSTR Pattern,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetValue( 
            /* [in] */ BSTR Key,
            /* [in] */ BSTR Val,
            /* [defaultvalue][in] */ VARIANT_BOOL fCreate = ( VARIANT_BOOL  )0) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IComposeStringPairsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IComposeStringPairs * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IComposeStringPairs * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IComposeStringPairs * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IComposeStringPairs * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IComposeStringPairs * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IComposeStringPairs * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IComposeStringPairs * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ComposedData )( 
            IComposeStringPairs * This,
            /* [in] */ BSTR Pattern,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetValue )( 
            IComposeStringPairs * This,
            /* [in] */ BSTR Key,
            /* [in] */ BSTR Val,
            /* [defaultvalue][in] */ VARIANT_BOOL fCreate);
        
        END_INTERFACE
    } IComposeStringPairsVtbl;

    interface IComposeStringPairs
    {
        CONST_VTBL struct IComposeStringPairsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IComposeStringPairs_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IComposeStringPairs_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IComposeStringPairs_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IComposeStringPairs_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IComposeStringPairs_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IComposeStringPairs_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IComposeStringPairs_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IComposeStringPairs_get_ComposedData(This,Pattern,pVal)	\
    (This)->lpVtbl -> get_ComposedData(This,Pattern,pVal)

#define IComposeStringPairs_SetValue(This,Key,Val,fCreate)	\
    (This)->lpVtbl -> SetValue(This,Key,Val,fCreate)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IComposeStringPairs_get_ComposedData_Proxy( 
    IComposeStringPairs * This,
    /* [in] */ BSTR Pattern,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IComposeStringPairs_get_ComposedData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IComposeStringPairs_SetValue_Proxy( 
    IComposeStringPairs * This,
    /* [in] */ BSTR Key,
    /* [in] */ BSTR Val,
    /* [defaultvalue][in] */ VARIANT_BOOL fCreate);


void __RPC_STUB IComposeStringPairs_SetValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IComposeStringPairs_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_TRiASDB_0285 */
/* [local] */ 

#pragma once
#if !defined(_DEFINED_HPROJECT)
#define _DEFINED_HPROJECT
#define HACTPROJECT		((HPROJECT)(-1))		// aktuelles Projekt
#define HACTCONNECTION	((HPROJECT)(NULL))		// aktuelle Datenquelle
typedef /* [hidden] */ struct HPROJECT__
    {
    int unused;
    } 	*HPROJECT;

#endif // _DEFINED_HPROJECT
#if !defined(_DEFINED_HOBJECTS)
#define _DEFINED_HOBJECTS
#define INVALID_HOBJECTS		((HOBJECTS)(NULL))		// ungültiges Handle
typedef /* [hidden] */ INT_PTR HOBJECTS;

#endif // _DEFINED_HOBJECTS
#if !defined(_DEFINED_HOBJECT)
#define _DEFINED_HOBJECT
#define INVALID_HOBJECT		((HOBJECT)(NULL))		// ungültiges Handle
typedef /* [hidden] */ INT_PTR HOBJECT;

#endif // _DEFINED_HOBJECT
#if !defined(_DEFINED_HFEATURE)
#define _DEFINED_HFEATURE
#define INVALID_HFEATURE		((HFEATURE)(NULL))		// ungültiges Handle
typedef /* [hidden] */ INT_PTR HFEATURE;

#endif // _DEFINED_HFEATURE








































extern RPC_IF_HANDLE __MIDL_itf_TRiASDB_0285_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_TRiASDB_0285_v0_0_s_ifspec;

#ifndef __ITRiASDBEngine_INTERFACE_DEFINED__
#define __ITRiASDBEngine_INTERFACE_DEFINED__

/* interface ITRiASDBEngine */
/* [unique][helpstring][dual][uuid][object] */ 

#if !defined(_STARTMODE_DEFINED)
#define _STARTMODE_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagSTARTMODE
    {	STARTMODE_Normal	= 0,
	STARTMODE_SysAdmin	= 1,
	STARTMODE_BackupDatafile	= 2,
	STARTMODE_CompatibleWithStb	= 0x80
    } 	STARTMODE;

#endif // _STARTMODE_DEFINED

EXTERN_C const IID IID_ITRiASDBEngine;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1CB3AB7B-2E87-11D1-969D-00A024D6F582")
    ITRiASDBEngine : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Password( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UserName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Start( 
            /* [in] */ STARTMODE Mode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumDataBaseTypes( 
            /* [retval][out] */ IUnknown **ppIEnum) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASDBEngineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASDBEngine * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASDBEngine * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASDBEngine * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASDBEngine * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASDBEngine * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASDBEngine * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASDBEngine * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            ITRiASDBEngine * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Password )( 
            ITRiASDBEngine * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UserName )( 
            ITRiASDBEngine * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            ITRiASDBEngine * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Start )( 
            ITRiASDBEngine * This,
            /* [in] */ STARTMODE Mode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnumDataBaseTypes )( 
            ITRiASDBEngine * This,
            /* [retval][out] */ IUnknown **ppIEnum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Stop )( 
            ITRiASDBEngine * This);
        
        END_INTERFACE
    } ITRiASDBEngineVtbl;

    interface ITRiASDBEngine
    {
        CONST_VTBL struct ITRiASDBEngineVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASDBEngine_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASDBEngine_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASDBEngine_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASDBEngine_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASDBEngine_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASDBEngine_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASDBEngine_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASDBEngine_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define ITRiASDBEngine_put_Password(This,newVal)	\
    (This)->lpVtbl -> put_Password(This,newVal)

#define ITRiASDBEngine_put_UserName(This,newVal)	\
    (This)->lpVtbl -> put_UserName(This,newVal)

#define ITRiASDBEngine_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#define ITRiASDBEngine_Start(This,Mode)	\
    (This)->lpVtbl -> Start(This,Mode)

#define ITRiASDBEngine_EnumDataBaseTypes(This,ppIEnum)	\
    (This)->lpVtbl -> EnumDataBaseTypes(This,ppIEnum)

#define ITRiASDBEngine_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDBEngine_get_Version_Proxy( 
    ITRiASDBEngine * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASDBEngine_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASDBEngine_put_Password_Proxy( 
    ITRiASDBEngine * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITRiASDBEngine_put_Password_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASDBEngine_put_UserName_Proxy( 
    ITRiASDBEngine * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITRiASDBEngine_put_UserName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDBEngine_get_Description_Proxy( 
    ITRiASDBEngine * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASDBEngine_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASDBEngine_Start_Proxy( 
    ITRiASDBEngine * This,
    /* [in] */ STARTMODE Mode);


void __RPC_STUB ITRiASDBEngine_Start_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASDBEngine_EnumDataBaseTypes_Proxy( 
    ITRiASDBEngine * This,
    /* [retval][out] */ IUnknown **ppIEnum);


void __RPC_STUB ITRiASDBEngine_EnumDataBaseTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASDBEngine_Stop_Proxy( 
    ITRiASDBEngine * This);


void __RPC_STUB ITRiASDBEngine_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASDBEngine_INTERFACE_DEFINED__ */


#ifndef __ITRiASBase_INTERFACE_DEFINED__
#define __ITRiASBase_INTERFACE_DEFINED__

/* interface ITRiASBase */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASBase;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("710B2C36-890F-11D2-9EFB-006008447800")
    ITRiASBase : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][restricted][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE put_Application( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][restricted][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE put_Parent( 
            /* [in] */ IDispatch *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASBaseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASBase * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASBase * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASBase * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASBase * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASBase * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASBase * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASBase * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            ITRiASBase * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Application )( 
            ITRiASBase * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            ITRiASBase * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Parent )( 
            ITRiASBase * This,
            /* [in] */ IDispatch *newVal);
        
        END_INTERFACE
    } ITRiASBaseVtbl;

    interface ITRiASBase
    {
        CONST_VTBL struct ITRiASBaseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASBase_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASBase_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASBase_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASBase_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASBase_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASBase_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASBase_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASBase_get_Application(This,pVal)	\
    (This)->lpVtbl -> get_Application(This,pVal)

#define ITRiASBase_put_Application(This,newVal)	\
    (This)->lpVtbl -> put_Application(This,newVal)

#define ITRiASBase_get_Parent(This,pVal)	\
    (This)->lpVtbl -> get_Parent(This,pVal)

#define ITRiASBase_put_Parent(This,newVal)	\
    (This)->lpVtbl -> put_Parent(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASBase_get_Application_Proxy( 
    ITRiASBase * This,
    /* [retval][out] */ IDispatch **pVal);


void __RPC_STUB ITRiASBase_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][restricted][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASBase_put_Application_Proxy( 
    ITRiASBase * This,
    /* [in] */ IDispatch *newVal);


void __RPC_STUB ITRiASBase_put_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASBase_get_Parent_Proxy( 
    ITRiASBase * This,
    /* [retval][out] */ IDispatch **pVal);


void __RPC_STUB ITRiASBase_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][restricted][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASBase_put_Parent_Proxy( 
    ITRiASBase * This,
    /* [in] */ IDispatch *newVal);


void __RPC_STUB ITRiASBase_put_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASBase_INTERFACE_DEFINED__ */


#ifndef __ITRiASPropertyBase_INTERFACE_DEFINED__
#define __ITRiASPropertyBase_INTERFACE_DEFINED__

/* interface ITRiASPropertyBase */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASPropertyBase;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("97993C78-5FE6-11D1-B9E6-080036D63803")
    ITRiASPropertyBase : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Properties( 
            /* [retval][out] */ ITRiASProperties **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Properties( 
            /* [in] */ ITRiASProperties *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Property( 
            /* [in] */ BSTR Which,
            /* [retval][out] */ ITRiASProperty **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateProperty( 
            /* [in] */ BSTR Which,
            /* [retval][out] */ ITRiASProperty **Prop) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveProperty( 
            /* [in] */ BSTR Name) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASPropertyBaseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASPropertyBase * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASPropertyBase * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASPropertyBase * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASPropertyBase * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASPropertyBase * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASPropertyBase * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASPropertyBase * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Properties )( 
            ITRiASPropertyBase * This,
            /* [retval][out] */ ITRiASProperties **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Properties )( 
            ITRiASPropertyBase * This,
            /* [in] */ ITRiASProperties *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Property )( 
            ITRiASPropertyBase * This,
            /* [in] */ BSTR Which,
            /* [retval][out] */ ITRiASProperty **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateProperty )( 
            ITRiASPropertyBase * This,
            /* [in] */ BSTR Which,
            /* [retval][out] */ ITRiASProperty **Prop);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveProperty )( 
            ITRiASPropertyBase * This,
            /* [in] */ BSTR Name);
        
        END_INTERFACE
    } ITRiASPropertyBaseVtbl;

    interface ITRiASPropertyBase
    {
        CONST_VTBL struct ITRiASPropertyBaseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASPropertyBase_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASPropertyBase_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASPropertyBase_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASPropertyBase_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASPropertyBase_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASPropertyBase_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASPropertyBase_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASPropertyBase_get_Properties(This,pVal)	\
    (This)->lpVtbl -> get_Properties(This,pVal)

#define ITRiASPropertyBase_put_Properties(This,pVal)	\
    (This)->lpVtbl -> put_Properties(This,pVal)

#define ITRiASPropertyBase_get_Property(This,Which,pVal)	\
    (This)->lpVtbl -> get_Property(This,Which,pVal)

#define ITRiASPropertyBase_CreateProperty(This,Which,Prop)	\
    (This)->lpVtbl -> CreateProperty(This,Which,Prop)

#define ITRiASPropertyBase_RemoveProperty(This,Name)	\
    (This)->lpVtbl -> RemoveProperty(This,Name)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASPropertyBase_get_Properties_Proxy( 
    ITRiASPropertyBase * This,
    /* [retval][out] */ ITRiASProperties **pVal);


void __RPC_STUB ITRiASPropertyBase_get_Properties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASPropertyBase_put_Properties_Proxy( 
    ITRiASPropertyBase * This,
    /* [in] */ ITRiASProperties *pVal);


void __RPC_STUB ITRiASPropertyBase_put_Properties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASPropertyBase_get_Property_Proxy( 
    ITRiASPropertyBase * This,
    /* [in] */ BSTR Which,
    /* [retval][out] */ ITRiASProperty **pVal);


void __RPC_STUB ITRiASPropertyBase_get_Property_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASPropertyBase_CreateProperty_Proxy( 
    ITRiASPropertyBase * This,
    /* [in] */ BSTR Which,
    /* [retval][out] */ ITRiASProperty **Prop);


void __RPC_STUB ITRiASPropertyBase_CreateProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASPropertyBase_RemoveProperty_Proxy( 
    ITRiASPropertyBase * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASPropertyBase_RemoveProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASPropertyBase_INTERFACE_DEFINED__ */


#ifndef __ITRiASProject_INTERFACE_DEFINED__
#define __ITRiASProject_INTERFACE_DEFINED__

/* interface ITRiASProject */
/* [unique][helpstring][dual][uuid][object] */ 

#if !defined(_OPENMODE_DEFINED)
#define _OPENMODE_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagOPENMODE
    {	OPENMODE_Unknown	= 0xffff,
	OPENMODE_Normal	= 0,
	OPENMODE_ReadOnly	= 1,
	OPENMODE_NoDefaultView	= 2,
	OPENMODE_HideDocument	= 4,
	OPENMODE_Activate	= 8,
	OPENMODE_DoNotAddToMRU	= 0x10,
	OPENMODE_CreateInternalDatasource	= 0x100,
	OPENMODE_16BitCompatible	= 0x2040
    } 	OPENMODE;

#endif // _OPENMODE_DEFINED

EXTERN_C const IID IID_ITRiASProject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1CB3AB62-2E87-11D1-969D-00A024D6F582")
    ITRiASProject : public ITRiASBase
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Updatable( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Updatable( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OpenedAsCopy( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OpenedAsCopy( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CouldOpenTarget( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Mode( 
            /* [retval][out] */ OPENMODE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Mode( 
            /* [in] */ OPENMODE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Connections( 
            /* [retval][out] */ ITRiASConnections **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Connection( 
            /* [in] */ VARIANT vItem,
            /* [retval][out] */ ITRiASConnection **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Views( 
            /* [retval][out] */ ITRiASViews **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_View( 
            /* [in] */ BSTR Name,
            /* [defaultvalue][in] */ VARIANT_BOOL fCreate,
            /* [retval][out] */ ITRiASView **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Temporary( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Temporary( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [restricted][hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Handle( 
            /* [retval][out] */ INT_PTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Dirty( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Dirty( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Activated( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Activated( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ObjectsDefs( 
            /* [retval][out] */ ITRiASObjectsCollection **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ObjectsDef( 
            /* [in] */ VARIANT vItem,
            /* [defaultvalue][in] */ VARIANT_BOOL fCreate,
            /* [defaultvalue][in] */ BSTR Type,
            /* [retval][out] */ ITRiASObjects **pIObjsDef) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( 
            /* [defaultvalue][in] */ VARIANT_BOOL Commit = ( VARIANT_BOOL  )0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NewPassword( 
            /* [in] */ BSTR OldPassword,
            /* [in] */ BSTR NewPassword) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveAs( 
            BSTR NewName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExportCopyAs( 
            BSTR NewName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConnectionFilters( 
            /* [retval][out] */ ITRiASConnectionFilters **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConnectionFilter( 
            /* [in] */ VARIANT vItem,
            /* [defaultvalue][in] */ VARIANT_BOOL fCreate,
            /* [retval][out] */ ITRiASConnectionFilter **ppVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASProjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASProject * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASProject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASProject * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASProject * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASProject * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASProject * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASProject * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            ITRiASProject * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Application )( 
            ITRiASProject * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            ITRiASProject * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Parent )( 
            ITRiASProject * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            ITRiASProject * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ITRiASProject * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            ITRiASProject * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Updatable )( 
            ITRiASProject * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Updatable )( 
            ITRiASProject * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OpenedAsCopy )( 
            ITRiASProject * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OpenedAsCopy )( 
            ITRiASProject * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CouldOpenTarget )( 
            ITRiASProject * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Mode )( 
            ITRiASProject * This,
            /* [retval][out] */ OPENMODE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Mode )( 
            ITRiASProject * This,
            /* [in] */ OPENMODE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Connections )( 
            ITRiASProject * This,
            /* [retval][out] */ ITRiASConnections **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Connection )( 
            ITRiASProject * This,
            /* [in] */ VARIANT vItem,
            /* [retval][out] */ ITRiASConnection **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Views )( 
            ITRiASProject * This,
            /* [retval][out] */ ITRiASViews **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_View )( 
            ITRiASProject * This,
            /* [in] */ BSTR Name,
            /* [defaultvalue][in] */ VARIANT_BOOL fCreate,
            /* [retval][out] */ ITRiASView **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Temporary )( 
            ITRiASProject * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Temporary )( 
            ITRiASProject * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [restricted][hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Handle )( 
            ITRiASProject * This,
            /* [retval][out] */ INT_PTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dirty )( 
            ITRiASProject * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Dirty )( 
            ITRiASProject * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Activated )( 
            ITRiASProject * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Activated )( 
            ITRiASProject * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ObjectsDefs )( 
            ITRiASProject * This,
            /* [retval][out] */ ITRiASObjectsCollection **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ObjectsDef )( 
            ITRiASProject * This,
            /* [in] */ VARIANT vItem,
            /* [defaultvalue][in] */ VARIANT_BOOL fCreate,
            /* [defaultvalue][in] */ BSTR Type,
            /* [retval][out] */ ITRiASObjects **pIObjsDef);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Close )( 
            ITRiASProject * This,
            /* [defaultvalue][in] */ VARIANT_BOOL Commit);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NewPassword )( 
            ITRiASProject * This,
            /* [in] */ BSTR OldPassword,
            /* [in] */ BSTR NewPassword);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Save )( 
            ITRiASProject * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveAs )( 
            ITRiASProject * This,
            BSTR NewName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ExportCopyAs )( 
            ITRiASProject * This,
            BSTR NewName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConnectionFilters )( 
            ITRiASProject * This,
            /* [retval][out] */ ITRiASConnectionFilters **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConnectionFilter )( 
            ITRiASProject * This,
            /* [in] */ VARIANT vItem,
            /* [defaultvalue][in] */ VARIANT_BOOL fCreate,
            /* [retval][out] */ ITRiASConnectionFilter **ppVal);
        
        END_INTERFACE
    } ITRiASProjectVtbl;

    interface ITRiASProject
    {
        CONST_VTBL struct ITRiASProjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASProject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASProject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASProject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASProject_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASProject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASProject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASProject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASProject_get_Application(This,pVal)	\
    (This)->lpVtbl -> get_Application(This,pVal)

#define ITRiASProject_put_Application(This,newVal)	\
    (This)->lpVtbl -> put_Application(This,newVal)

#define ITRiASProject_get_Parent(This,pVal)	\
    (This)->lpVtbl -> get_Parent(This,pVal)

#define ITRiASProject_put_Parent(This,newVal)	\
    (This)->lpVtbl -> put_Parent(This,newVal)


#define ITRiASProject_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define ITRiASProject_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define ITRiASProject_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define ITRiASProject_get_Updatable(This,pVal)	\
    (This)->lpVtbl -> get_Updatable(This,pVal)

#define ITRiASProject_put_Updatable(This,newVal)	\
    (This)->lpVtbl -> put_Updatable(This,newVal)

#define ITRiASProject_get_OpenedAsCopy(This,pVal)	\
    (This)->lpVtbl -> get_OpenedAsCopy(This,pVal)

#define ITRiASProject_put_OpenedAsCopy(This,newVal)	\
    (This)->lpVtbl -> put_OpenedAsCopy(This,newVal)

#define ITRiASProject_get_CouldOpenTarget(This,pVal)	\
    (This)->lpVtbl -> get_CouldOpenTarget(This,pVal)

#define ITRiASProject_get_Mode(This,pVal)	\
    (This)->lpVtbl -> get_Mode(This,pVal)

#define ITRiASProject_put_Mode(This,newVal)	\
    (This)->lpVtbl -> put_Mode(This,newVal)

#define ITRiASProject_get_Connections(This,pVal)	\
    (This)->lpVtbl -> get_Connections(This,pVal)

#define ITRiASProject_get_Connection(This,vItem,pVal)	\
    (This)->lpVtbl -> get_Connection(This,vItem,pVal)

#define ITRiASProject_get_Views(This,pVal)	\
    (This)->lpVtbl -> get_Views(This,pVal)

#define ITRiASProject_get_View(This,Name,fCreate,pVal)	\
    (This)->lpVtbl -> get_View(This,Name,fCreate,pVal)

#define ITRiASProject_get_Temporary(This,pVal)	\
    (This)->lpVtbl -> get_Temporary(This,pVal)

#define ITRiASProject_put_Temporary(This,newVal)	\
    (This)->lpVtbl -> put_Temporary(This,newVal)

#define ITRiASProject_get_Handle(This,pVal)	\
    (This)->lpVtbl -> get_Handle(This,pVal)

#define ITRiASProject_get_Dirty(This,pVal)	\
    (This)->lpVtbl -> get_Dirty(This,pVal)

#define ITRiASProject_put_Dirty(This,newVal)	\
    (This)->lpVtbl -> put_Dirty(This,newVal)

#define ITRiASProject_get_Activated(This,pVal)	\
    (This)->lpVtbl -> get_Activated(This,pVal)

#define ITRiASProject_put_Activated(This,newVal)	\
    (This)->lpVtbl -> put_Activated(This,newVal)

#define ITRiASProject_get_ObjectsDefs(This,pVal)	\
    (This)->lpVtbl -> get_ObjectsDefs(This,pVal)

#define ITRiASProject_get_ObjectsDef(This,vItem,fCreate,Type,pIObjsDef)	\
    (This)->lpVtbl -> get_ObjectsDef(This,vItem,fCreate,Type,pIObjsDef)

#define ITRiASProject_Close(This,Commit)	\
    (This)->lpVtbl -> Close(This,Commit)

#define ITRiASProject_NewPassword(This,OldPassword,NewPassword)	\
    (This)->lpVtbl -> NewPassword(This,OldPassword,NewPassword)

#define ITRiASProject_Save(This)	\
    (This)->lpVtbl -> Save(This)

#define ITRiASProject_SaveAs(This,NewName)	\
    (This)->lpVtbl -> SaveAs(This,NewName)

#define ITRiASProject_ExportCopyAs(This,NewName)	\
    (This)->lpVtbl -> ExportCopyAs(This,NewName)

#define ITRiASProject_get_ConnectionFilters(This,pVal)	\
    (This)->lpVtbl -> get_ConnectionFilters(This,pVal)

#define ITRiASProject_get_ConnectionFilter(This,vItem,fCreate,ppVal)	\
    (This)->lpVtbl -> get_ConnectionFilter(This,vItem,fCreate,ppVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASProject_get_Version_Proxy( 
    ITRiASProject * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITRiASProject_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASProject_get_Name_Proxy( 
    ITRiASProject * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASProject_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASProject_put_Name_Proxy( 
    ITRiASProject * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITRiASProject_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASProject_get_Updatable_Proxy( 
    ITRiASProject * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASProject_get_Updatable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASProject_put_Updatable_Proxy( 
    ITRiASProject * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ITRiASProject_put_Updatable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASProject_get_OpenedAsCopy_Proxy( 
    ITRiASProject * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASProject_get_OpenedAsCopy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASProject_put_OpenedAsCopy_Proxy( 
    ITRiASProject * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ITRiASProject_put_OpenedAsCopy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASProject_get_CouldOpenTarget_Proxy( 
    ITRiASProject * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASProject_get_CouldOpenTarget_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASProject_get_Mode_Proxy( 
    ITRiASProject * This,
    /* [retval][out] */ OPENMODE *pVal);


void __RPC_STUB ITRiASProject_get_Mode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASProject_put_Mode_Proxy( 
    ITRiASProject * This,
    /* [in] */ OPENMODE newVal);


void __RPC_STUB ITRiASProject_put_Mode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASProject_get_Connections_Proxy( 
    ITRiASProject * This,
    /* [retval][out] */ ITRiASConnections **pVal);


void __RPC_STUB ITRiASProject_get_Connections_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASProject_get_Connection_Proxy( 
    ITRiASProject * This,
    /* [in] */ VARIANT vItem,
    /* [retval][out] */ ITRiASConnection **pVal);


void __RPC_STUB ITRiASProject_get_Connection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASProject_get_Views_Proxy( 
    ITRiASProject * This,
    /* [retval][out] */ ITRiASViews **pVal);


void __RPC_STUB ITRiASProject_get_Views_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASProject_get_View_Proxy( 
    ITRiASProject * This,
    /* [in] */ BSTR Name,
    /* [defaultvalue][in] */ VARIANT_BOOL fCreate,
    /* [retval][out] */ ITRiASView **pVal);


void __RPC_STUB ITRiASProject_get_View_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASProject_get_Temporary_Proxy( 
    ITRiASProject * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASProject_get_Temporary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASProject_put_Temporary_Proxy( 
    ITRiASProject * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ITRiASProject_put_Temporary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASProject_get_Handle_Proxy( 
    ITRiASProject * This,
    /* [retval][out] */ INT_PTR *pVal);


void __RPC_STUB ITRiASProject_get_Handle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASProject_get_Dirty_Proxy( 
    ITRiASProject * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASProject_get_Dirty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASProject_put_Dirty_Proxy( 
    ITRiASProject * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ITRiASProject_put_Dirty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASProject_get_Activated_Proxy( 
    ITRiASProject * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASProject_get_Activated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASProject_put_Activated_Proxy( 
    ITRiASProject * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ITRiASProject_put_Activated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASProject_get_ObjectsDefs_Proxy( 
    ITRiASProject * This,
    /* [retval][out] */ ITRiASObjectsCollection **pVal);


void __RPC_STUB ITRiASProject_get_ObjectsDefs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASProject_get_ObjectsDef_Proxy( 
    ITRiASProject * This,
    /* [in] */ VARIANT vItem,
    /* [defaultvalue][in] */ VARIANT_BOOL fCreate,
    /* [defaultvalue][in] */ BSTR Type,
    /* [retval][out] */ ITRiASObjects **pIObjsDef);


void __RPC_STUB ITRiASProject_get_ObjectsDef_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASProject_Close_Proxy( 
    ITRiASProject * This,
    /* [defaultvalue][in] */ VARIANT_BOOL Commit);


void __RPC_STUB ITRiASProject_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASProject_NewPassword_Proxy( 
    ITRiASProject * This,
    /* [in] */ BSTR OldPassword,
    /* [in] */ BSTR NewPassword);


void __RPC_STUB ITRiASProject_NewPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASProject_Save_Proxy( 
    ITRiASProject * This);


void __RPC_STUB ITRiASProject_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASProject_SaveAs_Proxy( 
    ITRiASProject * This,
    BSTR NewName);


void __RPC_STUB ITRiASProject_SaveAs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASProject_ExportCopyAs_Proxy( 
    ITRiASProject * This,
    BSTR NewName);


void __RPC_STUB ITRiASProject_ExportCopyAs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASProject_get_ConnectionFilters_Proxy( 
    ITRiASProject * This,
    /* [retval][out] */ ITRiASConnectionFilters **pVal);


void __RPC_STUB ITRiASProject_get_ConnectionFilters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASProject_get_ConnectionFilter_Proxy( 
    ITRiASProject * This,
    /* [in] */ VARIANT vItem,
    /* [defaultvalue][in] */ VARIANT_BOOL fCreate,
    /* [retval][out] */ ITRiASConnectionFilter **ppVal);


void __RPC_STUB ITRiASProject_get_ConnectionFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASProject_INTERFACE_DEFINED__ */


#ifndef __ITRiASProjects_INTERFACE_DEFINED__
#define __ITRiASProjects_INTERFACE_DEFINED__

/* interface ITRiASProjects */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASProjects;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1CB3AB79-2E87-11D1-969D-00A024D6F582")
    ITRiASProjects : public ITRiASBase
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ITRiASProject **Project) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE _NewEnum( 
            /* [retval][out] */ IUnknown **ppIEnum) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ ITRiASProject **Connection) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT Index) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE _Add( 
            /* [in] */ ITRiASProject *Project,
            /* [defaultvalue][in] */ VARIANT_BOOL FullAdd = ( VARIANT_BOOL  )0xffff) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE _Clone( 
            /* [retval][out] */ ITRiASProjects **Prjs) = 0;
        
        virtual /* [restricted][hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEventSink( 
            /* [in] */ IUnknown *pIUnk,
            /* [in] */ VARIANT_BOOL fAdvise) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveProject( 
            /* [in] */ ITRiASProject *Project) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ActiveProject( 
            /* [retval][out] */ ITRiASProject **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASProjectsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASProjects * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASProjects * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASProjects * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASProjects * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASProjects * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASProjects * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASProjects * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            ITRiASProjects * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Application )( 
            ITRiASProjects * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            ITRiASProjects * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Parent )( 
            ITRiASProjects * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITRiASProjects * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            ITRiASProjects * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ITRiASProject **Project);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *_NewEnum )( 
            ITRiASProjects * This,
            /* [retval][out] */ IUnknown **ppIEnum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ITRiASProjects * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ ITRiASProject **Connection);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ITRiASProjects * This,
            /* [in] */ VARIANT Index);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *_Add )( 
            ITRiASProjects * This,
            /* [in] */ ITRiASProject *Project,
            /* [defaultvalue][in] */ VARIANT_BOOL FullAdd);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *_Clone )( 
            ITRiASProjects * This,
            /* [retval][out] */ ITRiASProjects **Prjs);
        
        /* [restricted][hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEventSink )( 
            ITRiASProjects * This,
            /* [in] */ IUnknown *pIUnk,
            /* [in] */ VARIANT_BOOL fAdvise);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveProject )( 
            ITRiASProjects * This,
            /* [in] */ ITRiASProject *Project);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ActiveProject )( 
            ITRiASProjects * This,
            /* [retval][out] */ ITRiASProject **pVal);
        
        END_INTERFACE
    } ITRiASProjectsVtbl;

    interface ITRiASProjects
    {
        CONST_VTBL struct ITRiASProjectsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASProjects_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASProjects_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASProjects_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASProjects_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASProjects_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASProjects_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASProjects_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASProjects_get_Application(This,pVal)	\
    (This)->lpVtbl -> get_Application(This,pVal)

#define ITRiASProjects_put_Application(This,newVal)	\
    (This)->lpVtbl -> put_Application(This,newVal)

#define ITRiASProjects_get_Parent(This,pVal)	\
    (This)->lpVtbl -> get_Parent(This,pVal)

#define ITRiASProjects_put_Parent(This,newVal)	\
    (This)->lpVtbl -> put_Parent(This,newVal)


#define ITRiASProjects_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define ITRiASProjects_Item(This,Index,Project)	\
    (This)->lpVtbl -> Item(This,Index,Project)

#define ITRiASProjects__NewEnum(This,ppIEnum)	\
    (This)->lpVtbl -> _NewEnum(This,ppIEnum)

#define ITRiASProjects_Add(This,Name,Connection)	\
    (This)->lpVtbl -> Add(This,Name,Connection)

#define ITRiASProjects_Remove(This,Index)	\
    (This)->lpVtbl -> Remove(This,Index)

#define ITRiASProjects__Add(This,Project,FullAdd)	\
    (This)->lpVtbl -> _Add(This,Project,FullAdd)

#define ITRiASProjects__Clone(This,Prjs)	\
    (This)->lpVtbl -> _Clone(This,Prjs)

#define ITRiASProjects_SetEventSink(This,pIUnk,fAdvise)	\
    (This)->lpVtbl -> SetEventSink(This,pIUnk,fAdvise)

#define ITRiASProjects_RemoveProject(This,Project)	\
    (This)->lpVtbl -> RemoveProject(This,Project)

#define ITRiASProjects_get_ActiveProject(This,pVal)	\
    (This)->lpVtbl -> get_ActiveProject(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASProjects_get_Count_Proxy( 
    ITRiASProjects * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITRiASProjects_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASProjects_Item_Proxy( 
    ITRiASProjects * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ ITRiASProject **Project);


void __RPC_STUB ITRiASProjects_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE ITRiASProjects__NewEnum_Proxy( 
    ITRiASProjects * This,
    /* [retval][out] */ IUnknown **ppIEnum);


void __RPC_STUB ITRiASProjects__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASProjects_Add_Proxy( 
    ITRiASProjects * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ ITRiASProject **Connection);


void __RPC_STUB ITRiASProjects_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASProjects_Remove_Proxy( 
    ITRiASProjects * This,
    /* [in] */ VARIANT Index);


void __RPC_STUB ITRiASProjects_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASProjects__Add_Proxy( 
    ITRiASProjects * This,
    /* [in] */ ITRiASProject *Project,
    /* [defaultvalue][in] */ VARIANT_BOOL FullAdd);


void __RPC_STUB ITRiASProjects__Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASProjects__Clone_Proxy( 
    ITRiASProjects * This,
    /* [retval][out] */ ITRiASProjects **Prjs);


void __RPC_STUB ITRiASProjects__Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASProjects_SetEventSink_Proxy( 
    ITRiASProjects * This,
    /* [in] */ IUnknown *pIUnk,
    /* [in] */ VARIANT_BOOL fAdvise);


void __RPC_STUB ITRiASProjects_SetEventSink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASProjects_RemoveProject_Proxy( 
    ITRiASProjects * This,
    /* [in] */ ITRiASProject *Project);


void __RPC_STUB ITRiASProjects_RemoveProject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASProjects_get_ActiveProject_Proxy( 
    ITRiASProjects * This,
    /* [retval][out] */ ITRiASProject **pVal);


void __RPC_STUB ITRiASProjects_get_ActiveProject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASProjects_INTERFACE_DEFINED__ */


#ifndef __ITRiASConnections_INTERFACE_DEFINED__
#define __ITRiASConnections_INTERFACE_DEFINED__

/* interface ITRiASConnections */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASConnections;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("191A9AF7-37FE-11D1-96B6-00A024D6F582")
    ITRiASConnections : public ITRiASBase
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ITRiASConnection **Connection) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE _NewEnum( 
            /* [retval][out] */ IUnknown **ppIEnum) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ ITRiASConnection **Connection) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT Index) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE _Add( 
            /* [in] */ ITRiASConnection *Connection,
            /* [defaultvalue][in] */ VARIANT_BOOL FullAdd = ( VARIANT_BOOL  )0xffff) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE _Clone( 
            /* [retval][out] */ ITRiASConnections **Conns) = 0;
        
        virtual /* [restricted][hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEventSink( 
            /* [in] */ IUnknown *Unk,
            /* [in] */ VARIANT_BOOL fAdvise) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveConnection( 
            /* [in] */ ITRiASConnection *Connection) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASConnectionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASConnections * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASConnections * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASConnections * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASConnections * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASConnections * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASConnections * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASConnections * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            ITRiASConnections * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Application )( 
            ITRiASConnections * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            ITRiASConnections * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Parent )( 
            ITRiASConnections * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITRiASConnections * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            ITRiASConnections * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ITRiASConnection **Connection);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *_NewEnum )( 
            ITRiASConnections * This,
            /* [retval][out] */ IUnknown **ppIEnum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ITRiASConnections * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ ITRiASConnection **Connection);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ITRiASConnections * This,
            /* [in] */ VARIANT Index);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *_Add )( 
            ITRiASConnections * This,
            /* [in] */ ITRiASConnection *Connection,
            /* [defaultvalue][in] */ VARIANT_BOOL FullAdd);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *_Clone )( 
            ITRiASConnections * This,
            /* [retval][out] */ ITRiASConnections **Conns);
        
        /* [restricted][hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEventSink )( 
            ITRiASConnections * This,
            /* [in] */ IUnknown *Unk,
            /* [in] */ VARIANT_BOOL fAdvise);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveConnection )( 
            ITRiASConnections * This,
            /* [in] */ ITRiASConnection *Connection);
        
        END_INTERFACE
    } ITRiASConnectionsVtbl;

    interface ITRiASConnections
    {
        CONST_VTBL struct ITRiASConnectionsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASConnections_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASConnections_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASConnections_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASConnections_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASConnections_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASConnections_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASConnections_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASConnections_get_Application(This,pVal)	\
    (This)->lpVtbl -> get_Application(This,pVal)

#define ITRiASConnections_put_Application(This,newVal)	\
    (This)->lpVtbl -> put_Application(This,newVal)

#define ITRiASConnections_get_Parent(This,pVal)	\
    (This)->lpVtbl -> get_Parent(This,pVal)

#define ITRiASConnections_put_Parent(This,newVal)	\
    (This)->lpVtbl -> put_Parent(This,newVal)


#define ITRiASConnections_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define ITRiASConnections_Item(This,Index,Connection)	\
    (This)->lpVtbl -> Item(This,Index,Connection)

#define ITRiASConnections__NewEnum(This,ppIEnum)	\
    (This)->lpVtbl -> _NewEnum(This,ppIEnum)

#define ITRiASConnections_Add(This,Name,Connection)	\
    (This)->lpVtbl -> Add(This,Name,Connection)

#define ITRiASConnections_Remove(This,Index)	\
    (This)->lpVtbl -> Remove(This,Index)

#define ITRiASConnections__Add(This,Connection,FullAdd)	\
    (This)->lpVtbl -> _Add(This,Connection,FullAdd)

#define ITRiASConnections__Clone(This,Conns)	\
    (This)->lpVtbl -> _Clone(This,Conns)

#define ITRiASConnections_SetEventSink(This,Unk,fAdvise)	\
    (This)->lpVtbl -> SetEventSink(This,Unk,fAdvise)

#define ITRiASConnections_RemoveConnection(This,Connection)	\
    (This)->lpVtbl -> RemoveConnection(This,Connection)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASConnections_get_Count_Proxy( 
    ITRiASConnections * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITRiASConnections_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASConnections_Item_Proxy( 
    ITRiASConnections * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ ITRiASConnection **Connection);


void __RPC_STUB ITRiASConnections_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE ITRiASConnections__NewEnum_Proxy( 
    ITRiASConnections * This,
    /* [retval][out] */ IUnknown **ppIEnum);


void __RPC_STUB ITRiASConnections__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASConnections_Add_Proxy( 
    ITRiASConnections * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ ITRiASConnection **Connection);


void __RPC_STUB ITRiASConnections_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASConnections_Remove_Proxy( 
    ITRiASConnections * This,
    /* [in] */ VARIANT Index);


void __RPC_STUB ITRiASConnections_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASConnections__Add_Proxy( 
    ITRiASConnections * This,
    /* [in] */ ITRiASConnection *Connection,
    /* [defaultvalue][in] */ VARIANT_BOOL FullAdd);


void __RPC_STUB ITRiASConnections__Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASConnections__Clone_Proxy( 
    ITRiASConnections * This,
    /* [retval][out] */ ITRiASConnections **Conns);


void __RPC_STUB ITRiASConnections__Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASConnections_SetEventSink_Proxy( 
    ITRiASConnections * This,
    /* [in] */ IUnknown *Unk,
    /* [in] */ VARIANT_BOOL fAdvise);


void __RPC_STUB ITRiASConnections_SetEventSink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASConnections_RemoveConnection_Proxy( 
    ITRiASConnections * This,
    /* [in] */ ITRiASConnection *Connection);


void __RPC_STUB ITRiASConnections_RemoveConnection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASConnections_INTERFACE_DEFINED__ */


#ifndef __ITRiASConnection_INTERFACE_DEFINED__
#define __ITRiASConnection_INTERFACE_DEFINED__

/* interface ITRiASConnection */
/* [unique][helpstring][dual][uuid][object] */ 

#if !defined(_CONNECTSTATUS_DEFINED)
#define _CONNECTSTATUS_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagCONNECTSTATUS
    {	CONNECTSTATUS_Closed	= 0,
	CONNECTSTATUS_Opened	= 1
    } 	CONNECTSTATUS;

#endif // _CONNECTSTATUS_DEFINED
#if !defined(_CONNECTPARAM_DEFINED)
#define _CONNECTPARAM_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagCONNECTPARAM
    {	CONNECTPARAM_Unknown	= 0,
	CONNECTPARAM_FileOrDir	= 1,
	CONNECTPARAM_MultiFile	= 2,
	CONNECTPARAM_Storage	= 3,
	CONNECTPARAM_ConnectString	= 4
    } 	CONNECTPARAM;

#endif // _CONNECTPARAM_DEFINED
#if !defined(_CONNECTMODE_DEFINED)
#define _CONNECTMODE_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagCONNECTMODE
    {	CONNECTMODE_UseDefaultMode	= ~0,
	CONNECTMODE_ConnectAfterLoadIfApplicable	= 0x8000,
	CONNECTMODE_OpenReadOnly	= 0,
	CONNECTMODE_OpenReadWrite	= 1,
	CONNECTMODE_IsReadOnly	= 2,
	CONNECTMODE_OpenNoResolution	= 0,
	CONNECTMODE_OpenUserResolves	= 0x100,
	CONNECTMODE_OpenAutoResolution	= 0x200,
	CONNECTMODE_OpenFlags	= 0x1,
	CONNECTMODE_OpenResolutionFlags	= 0x300,
	CONNECTMODE_CloseNoResolution	= 0,
	CONNECTMODE_CloseUserResolves	= 0x1000,
	CONNECTMODE_CloseAutoResolution	= 0x2000,
	CONNECTMODE_CloseResolutionFlags	= 0x3000,
	CONNECTMODE_ResolutionFlags	= CONNECTMODE_OpenResolutionFlags | CONNECTMODE_CloseResolutionFlags,
	CONNECTMODE_ResetConnectAskMode	= 0x400,
	CONNECTMODE_ResetDisconnectAskMode	= 0x4000,
	CONNECTMODE_ResetAskMode	= CONNECTMODE_ResetConnectAskMode | CONNECTMODE_ResetDisconnectAskMode
    } 	CONNECTMODE;

#endif // _CONNECTMODE_DEFINED

EXTERN_C const IID IID_ITRiASConnection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("191A9AF4-37FE-11D1-96B6-00A024D6F582")
    ITRiASConnection : public ITRiASBase
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConnectInfo( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConnectInfo( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Status( 
            /* [retval][out] */ CONNECTSTATUS *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Param( 
            /* [retval][out] */ CONNECTPARAM *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Mode( 
            /* [retval][out] */ CONNECTMODE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Mode( 
            /* [in] */ CONNECTMODE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Location( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Location( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Locations( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Locations( 
            /* [in] */ IUnknown *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Database( 
            /* [retval][out] */ ITRiASDatabase **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Updatable( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SchemaUpdatable( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Transactions( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][hidden][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get_VersionLong( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GuidPath( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Connect( 
            /* [defaultvalue][in] */ CONNECTMODE rgMode = CONNECTMODE_UseDefaultMode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Disconnect( 
            /* [defaultvalue][in] */ CONNECTMODE rgMode = CONNECTMODE_UseDefaultMode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveConnectedDatabase( 
            /* [in] */ CONNECTMODE Mode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveAsConnectedDatabase( 
            /* [in] */ CONNECTMODE Mode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASConnectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASConnection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASConnection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASConnection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASConnection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASConnection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASConnection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASConnection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            ITRiASConnection * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Application )( 
            ITRiASConnection * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            ITRiASConnection * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Parent )( 
            ITRiASConnection * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ITRiASConnection * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            ITRiASConnection * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            ITRiASConnection * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            ITRiASConnection * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConnectInfo )( 
            ITRiASConnection * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ConnectInfo )( 
            ITRiASConnection * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Status )( 
            ITRiASConnection * This,
            /* [retval][out] */ CONNECTSTATUS *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Param )( 
            ITRiASConnection * This,
            /* [retval][out] */ CONNECTPARAM *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Mode )( 
            ITRiASConnection * This,
            /* [retval][out] */ CONNECTMODE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Mode )( 
            ITRiASConnection * This,
            /* [in] */ CONNECTMODE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            ITRiASConnection * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Type )( 
            ITRiASConnection * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Location )( 
            ITRiASConnection * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Location )( 
            ITRiASConnection * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Locations )( 
            ITRiASConnection * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Locations )( 
            ITRiASConnection * This,
            /* [in] */ IUnknown *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Database )( 
            ITRiASConnection * This,
            /* [retval][out] */ ITRiASDatabase **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Updatable )( 
            ITRiASConnection * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SchemaUpdatable )( 
            ITRiASConnection * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Transactions )( 
            ITRiASConnection * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            ITRiASConnection * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][hidden][restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VersionLong )( 
            ITRiASConnection * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GuidPath )( 
            ITRiASConnection * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Connect )( 
            ITRiASConnection * This,
            /* [defaultvalue][in] */ CONNECTMODE rgMode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Disconnect )( 
            ITRiASConnection * This,
            /* [defaultvalue][in] */ CONNECTMODE rgMode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ITRiASConnection * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveConnectedDatabase )( 
            ITRiASConnection * This,
            /* [in] */ CONNECTMODE Mode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveAsConnectedDatabase )( 
            ITRiASConnection * This,
            /* [in] */ CONNECTMODE Mode);
        
        END_INTERFACE
    } ITRiASConnectionVtbl;

    interface ITRiASConnection
    {
        CONST_VTBL struct ITRiASConnectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASConnection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASConnection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASConnection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASConnection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASConnection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASConnection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASConnection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASConnection_get_Application(This,pVal)	\
    (This)->lpVtbl -> get_Application(This,pVal)

#define ITRiASConnection_put_Application(This,newVal)	\
    (This)->lpVtbl -> put_Application(This,newVal)

#define ITRiASConnection_get_Parent(This,pVal)	\
    (This)->lpVtbl -> get_Parent(This,pVal)

#define ITRiASConnection_put_Parent(This,newVal)	\
    (This)->lpVtbl -> put_Parent(This,newVal)


#define ITRiASConnection_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define ITRiASConnection_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define ITRiASConnection_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#define ITRiASConnection_put_Description(This,newVal)	\
    (This)->lpVtbl -> put_Description(This,newVal)

#define ITRiASConnection_get_ConnectInfo(This,pVal)	\
    (This)->lpVtbl -> get_ConnectInfo(This,pVal)

#define ITRiASConnection_put_ConnectInfo(This,newVal)	\
    (This)->lpVtbl -> put_ConnectInfo(This,newVal)

#define ITRiASConnection_get_Status(This,pVal)	\
    (This)->lpVtbl -> get_Status(This,pVal)

#define ITRiASConnection_get_Param(This,pVal)	\
    (This)->lpVtbl -> get_Param(This,pVal)

#define ITRiASConnection_get_Mode(This,pVal)	\
    (This)->lpVtbl -> get_Mode(This,pVal)

#define ITRiASConnection_put_Mode(This,newVal)	\
    (This)->lpVtbl -> put_Mode(This,newVal)

#define ITRiASConnection_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define ITRiASConnection_put_Type(This,newVal)	\
    (This)->lpVtbl -> put_Type(This,newVal)

#define ITRiASConnection_get_Location(This,pVal)	\
    (This)->lpVtbl -> get_Location(This,pVal)

#define ITRiASConnection_put_Location(This,newVal)	\
    (This)->lpVtbl -> put_Location(This,newVal)

#define ITRiASConnection_get_Locations(This,pVal)	\
    (This)->lpVtbl -> get_Locations(This,pVal)

#define ITRiASConnection_put_Locations(This,newVal)	\
    (This)->lpVtbl -> put_Locations(This,newVal)

#define ITRiASConnection_get_Database(This,pVal)	\
    (This)->lpVtbl -> get_Database(This,pVal)

#define ITRiASConnection_get_Updatable(This,pVal)	\
    (This)->lpVtbl -> get_Updatable(This,pVal)

#define ITRiASConnection_get_SchemaUpdatable(This,pVal)	\
    (This)->lpVtbl -> get_SchemaUpdatable(This,pVal)

#define ITRiASConnection_get_Transactions(This,pVal)	\
    (This)->lpVtbl -> get_Transactions(This,pVal)

#define ITRiASConnection_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define ITRiASConnection_get_VersionLong(This,pVal)	\
    (This)->lpVtbl -> get_VersionLong(This,pVal)

#define ITRiASConnection_get_GuidPath(This,pVal)	\
    (This)->lpVtbl -> get_GuidPath(This,pVal)

#define ITRiASConnection_Connect(This,rgMode)	\
    (This)->lpVtbl -> Connect(This,rgMode)

#define ITRiASConnection_Disconnect(This,rgMode)	\
    (This)->lpVtbl -> Disconnect(This,rgMode)

#define ITRiASConnection_Remove(This)	\
    (This)->lpVtbl -> Remove(This)

#define ITRiASConnection_SaveConnectedDatabase(This,Mode)	\
    (This)->lpVtbl -> SaveConnectedDatabase(This,Mode)

#define ITRiASConnection_SaveAsConnectedDatabase(This,Mode)	\
    (This)->lpVtbl -> SaveAsConnectedDatabase(This,Mode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_get_Name_Proxy( 
    ITRiASConnection * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASConnection_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_put_Name_Proxy( 
    ITRiASConnection * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITRiASConnection_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_get_Description_Proxy( 
    ITRiASConnection * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASConnection_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_put_Description_Proxy( 
    ITRiASConnection * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITRiASConnection_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_get_ConnectInfo_Proxy( 
    ITRiASConnection * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASConnection_get_ConnectInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_put_ConnectInfo_Proxy( 
    ITRiASConnection * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITRiASConnection_put_ConnectInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_get_Status_Proxy( 
    ITRiASConnection * This,
    /* [retval][out] */ CONNECTSTATUS *pVal);


void __RPC_STUB ITRiASConnection_get_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_get_Param_Proxy( 
    ITRiASConnection * This,
    /* [retval][out] */ CONNECTPARAM *pVal);


void __RPC_STUB ITRiASConnection_get_Param_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_get_Mode_Proxy( 
    ITRiASConnection * This,
    /* [retval][out] */ CONNECTMODE *pVal);


void __RPC_STUB ITRiASConnection_get_Mode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_put_Mode_Proxy( 
    ITRiASConnection * This,
    /* [in] */ CONNECTMODE newVal);


void __RPC_STUB ITRiASConnection_put_Mode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_get_Type_Proxy( 
    ITRiASConnection * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASConnection_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_put_Type_Proxy( 
    ITRiASConnection * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITRiASConnection_put_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_get_Location_Proxy( 
    ITRiASConnection * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASConnection_get_Location_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_put_Location_Proxy( 
    ITRiASConnection * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITRiASConnection_put_Location_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_get_Locations_Proxy( 
    ITRiASConnection * This,
    /* [retval][out] */ IUnknown **pVal);


void __RPC_STUB ITRiASConnection_get_Locations_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_put_Locations_Proxy( 
    ITRiASConnection * This,
    /* [in] */ IUnknown *newVal);


void __RPC_STUB ITRiASConnection_put_Locations_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_get_Database_Proxy( 
    ITRiASConnection * This,
    /* [retval][out] */ ITRiASDatabase **pVal);


void __RPC_STUB ITRiASConnection_get_Database_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_get_Updatable_Proxy( 
    ITRiASConnection * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASConnection_get_Updatable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_get_SchemaUpdatable_Proxy( 
    ITRiASConnection * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASConnection_get_SchemaUpdatable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_get_Transactions_Proxy( 
    ITRiASConnection * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASConnection_get_Transactions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_get_Version_Proxy( 
    ITRiASConnection * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASConnection_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][hidden][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_get_VersionLong_Proxy( 
    ITRiASConnection * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB ITRiASConnection_get_VersionLong_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_get_GuidPath_Proxy( 
    ITRiASConnection * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASConnection_get_GuidPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_Connect_Proxy( 
    ITRiASConnection * This,
    /* [defaultvalue][in] */ CONNECTMODE rgMode);


void __RPC_STUB ITRiASConnection_Connect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_Disconnect_Proxy( 
    ITRiASConnection * This,
    /* [defaultvalue][in] */ CONNECTMODE rgMode);


void __RPC_STUB ITRiASConnection_Disconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_Remove_Proxy( 
    ITRiASConnection * This);


void __RPC_STUB ITRiASConnection_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_SaveConnectedDatabase_Proxy( 
    ITRiASConnection * This,
    /* [in] */ CONNECTMODE Mode);


void __RPC_STUB ITRiASConnection_SaveConnectedDatabase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASConnection_SaveAsConnectedDatabase_Proxy( 
    ITRiASConnection * This,
    /* [in] */ CONNECTMODE Mode);


void __RPC_STUB ITRiASConnection_SaveAsConnectedDatabase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASConnection_INTERFACE_DEFINED__ */


#ifndef __ITRiASRefreshChangesCallback_INTERFACE_DEFINED__
#define __ITRiASRefreshChangesCallback_INTERFACE_DEFINED__

/* interface ITRiASRefreshChangesCallback */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASRefreshChangesCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4A4E2AB2-9212-443E-A3A8-4251E6D70D58")
    ITRiASRefreshChangesCallback : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ITRiASRefreshChangesCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASRefreshChangesCallback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASRefreshChangesCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASRefreshChangesCallback * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASRefreshChangesCallback * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASRefreshChangesCallback * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASRefreshChangesCallback * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASRefreshChangesCallback * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } ITRiASRefreshChangesCallbackVtbl;

    interface ITRiASRefreshChangesCallback
    {
        CONST_VTBL struct ITRiASRefreshChangesCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASRefreshChangesCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASRefreshChangesCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASRefreshChangesCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASRefreshChangesCallback_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASRefreshChangesCallback_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASRefreshChangesCallback_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASRefreshChangesCallback_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITRiASRefreshChangesCallback_INTERFACE_DEFINED__ */


#ifndef __ITRiASDatabase_INTERFACE_DEFINED__
#define __ITRiASDatabase_INTERFACE_DEFINED__

/* interface ITRiASDatabase */
/* [unique][helpstring][dual][uuid][object] */ 

#if !defined(_RELOADDATABASE_DEFINED)
#define _RELOADDATABASE_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagRELOADDATABASE
    {	RELOADDATABASE_Envelope	= 1,
	RELOADDATABASE_Objects	= 2,
	RELOADDATABASE_ResetLookupWindow	= 4,
	RELOADDATABASE_Features	= 8,
	RELOADDATABASE_EnsureFeatures	= 0x100,
	RELOADDATABASE_All	= 0xf,
	RELOADDATABASE_ConnectionInitialized	= 0x10
    } 	RELOADDATABASE;

#endif // _RELOADDATABASE_DEFINED
#if !defined(_DATABASESTORAGEMODE_DEFINED)
#define _DATABASESTORAGEMODE_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagDATABASESTORAGEMODE
    {	DATABASESTORAGEMODE_Unknown	= 0,
	DATABASESTORAGEMODE_FileBased	= 1,
	DATABASESTORAGEMODE_MultiFileBased	= 2,
	DATABASESTORAGEMODE_DirectoryBased	= 3,
	DATABASESTORAGEMODE_StorageBased	= 4,
	DATABASESTORAGEMODE_MemoryBased	= 5,
	DATABASESTORAGEMODE_ConnectStringBased	= 6
    } 	DATABASESTORAGEMODE;

#endif // _DATABASESTORAGEMODE_DEFINED
#if !defined(_lint)
/* [helpstring] */ #define	COLLATEORDER_Neutral	( 1024 )

/* [helpstring] */ #define	COLLATEORDER_Arabic	( 1025 )

/* [helpstring] */ #define	COLLATEORDER_Cyrillic	( 1049 )

/* [helpstring] */ #define	COLLATEORDER_Czech	( 1029 )

/* [helpstring] */ #define	COLLATEORDER_Dutch	( 1043 )

/* [helpstring] */ #define	COLLATEORDER_General	( 1033 )

/* [helpstring] */ #define	COLLATEORDER_Greek	( 1032 )

/* [helpstring] */ #define	COLLATEORDER_Hebrew	( 1037 )

/* [helpstring] */ #define	COLLATEORDER_Hungarian	( 1038 )

/* [helpstring] */ #define	COLLATEORDER_Icelandic	( 1039 )

/* [helpstring] */ #define	COLLATEORDER_Norwdan	( 1030 )

/* [helpstring] */ #define	COLLATEORDER_PDXIntl	( 1033 )

/* [helpstring] */ #define	COLLATEORDER_PDXNor	( 1030 )

/* [helpstring] */ #define	COLLATEORDER_PDXSwe	( 1053 )

/* [helpstring] */ #define	COLLATEORDER_Polish	( 1045 )

/* [helpstring] */ #define	COLLATEORDER_Spanish	( 1034 )

/* [helpstring] */ #define	COLLATEORDER_SwedFin	( 1053 )

/* [helpstring] */ #define	COLLATEORDER_Turkish	( 1055 )

/* [helpstring] */ #define	COLLATEORDER_Japanese	( 1041 )

/* [helpstring] */ #define	COLLATEORDER_ChineseSimplified	( 2052 )

/* [helpstring] */ #define	COLLATEORDER_ChineseTraditional	( 1028 )

/* [helpstring] */ #define	COLLATEORDER_Korean	( 1036 )

/* [helpstring] */ #define	COLLATEORDER_Thai	( 4126 )

/* [helpstring] */ #define	COLLATEORDER_Undefined	( -1 )

#endif // !defined(_lint)
#if !defined(_lint)
/* [helpstring] */ #define	LOCALE_Arabic	( ";LANGID=0x0401;CP=1256;COUNTRY=0" )

/* [helpstring] */ #define	LOCALE_Czech	( ";LANGID=0x0405;CP=1250;COUNTRY=0" )

/* [helpstring] */ #define	LOCALE_Dutch	( ";LANGID=0x0413;CP=1252;COUNTRY=0" )

/* [helpstring] */ #define	LOCALE_General	( ";LANGID=0x0409;CP=1252;COUNTRY=0" )

/* [helpstring] */ #define	LOCALE_Greek	( ";LANGID=0x0408;CP=1253;COUNTRY=0" )

/* [helpstring] */ #define	LOCALE_Hebrew	( ";LANGID=0x040D;CP=1255;COUNTRY=0" )

/* [helpstring] */ #define	LOCALE_Hungarian	( ";LANGID=0x040E;CP=1250;COUNTRY=0" )

/* [helpstring] */ #define	LOCALE_Icelandic	( ";LANGID=0x040F;CP=1252;COUNTRY=0" )

/* [helpstring] */ #define	LOCALE_Nordic	( ";LANGID=0x041D;CP=1252;COUNTRY=0" )

/* [helpstring] */ #define	LOCALE_NorwDan	( ";LANGID=0x0414;CP=1252;COUNTRY=0" )

/* [helpstring] */ #define	LOCALE_Polish	( ";LANGID=0x0415;CP=1250;COUNTRY=0" )

/* [helpstring] */ #define	LOCALE_Cyrillic	( ";LANGID=0x0419;CP=1251;COUNTRY=0" )

/* [helpstring] */ #define	LOCALE_Spanish	( ";LANGID=0x040A;CP=1252;COUNTRY=0" )

/* [helpstring] */ #define	LOCALE_SwedFin	( ";LANGID=0x040B;CP=1252;COUNTRY=0" )

/* [helpstring] */ #define	LOCALE_Turkish	( ";LANGID=0x041F;CP=1254;COUNTRY=0" )

/* [helpstring] */ #define	LOCALE_Japanese	( ";LANGID=0x0411;CP=932;COUNTRY=0" )

/* [helpstring] */ #define	LOCALE_ChineseSimplified	( ";LANGID=0x0804;CP=936;COUNTRY=0" )

/* [helpstring] */ #define	LOCALE_ChineseTraditional	( ";LANGID=0x0404;CP=950;COUNTRY=0" )

/* [helpstring] */ #define	LOCALE_Korean	( ";LANGID=0x040C;CP=494;COUNTRY=0" )

/* [helpstring] */ #define	LOCALE_Thai	( ";LANGID=0x101E;CP=874;COUNTRY=0" )

#endif // !defined(_lint)

EXTERN_C const IID IID_ITRiASDatabase;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6ACC24A3-3969-11D1-96B8-00A024D6F582")
    ITRiASDatabase : public ITRiASBase
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VersionLong( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [restricted][hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Handle( 
            /* [retval][out] */ INT_PTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsDirty( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IsDirty( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OpenedAsCopy( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CouldOpenTarget( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SchemaUpdatable( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CollatingOrder( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Connect( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Transactions( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Updatable( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Temporary( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Temporary( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TemporaryName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StorageMode( 
            /* [retval][out] */ DATABASESTORAGEMODE *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateDatabase( 
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Locale,
            /* [in] */ BSTR Source) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateDatabaseFromFiles( 
            /* [in] */ IUnknown *FileNames,
            /* [in] */ BSTR Locale,
            /* [in] */ BSTR Source) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenDatabase( 
            /* [in] */ BSTR Name,
            /* [defaultvalue][in] */ VARIANT_BOOL Exclusive = ( VARIANT_BOOL  )0xffff,
            /* [defaultvalue][in] */ VARIANT_BOOL ReadOnly = ( VARIANT_BOOL  )0,
            /* [defaultvalue][in] */ VARIANT_BOOL ModTrack = ( VARIANT_BOOL  )0,
            /* [defaultvalue][in] */ BSTR Source = L"") = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenFilesAsDatabase( 
            /* [in] */ IUnknown *FileNames,
            /* [defaultvalue][in] */ VARIANT_BOOL Exclusive = ( VARIANT_BOOL  )0xffff,
            /* [defaultvalue][in] */ VARIANT_BOOL ReadOnly = ( VARIANT_BOOL  )0,
            /* [defaultvalue][in] */ VARIANT_BOOL ModTrack = ( VARIANT_BOOL  )0,
            /* [defaultvalue][in] */ BSTR Source = L"") = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveAs( 
            /* [in] */ BSTR NewName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BeginTrans( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearModificationLog( 
            /* [defaultvalue][in] */ LONG Entry = -1L) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CommitTrans( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Rollback( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReLoad( 
            /* [in] */ RELOADDATABASE ToReLoad) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateDatabaseOnStg( 
            /* [in] */ IUnknown *Storage,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Locale,
            /* [in] */ BSTR Source) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenStorageAsDatabase( 
            /* [in] */ IUnknown *Storage,
            /* [defaultvalue][in] */ VARIANT_BOOL Exclusive = ( VARIANT_BOOL  )0xffff,
            /* [defaultvalue][in] */ VARIANT_BOOL ReadOnly = ( VARIANT_BOOL  )0,
            /* [defaultvalue][in] */ VARIANT_BOOL ModTrack = ( VARIANT_BOOL  )0,
            /* [defaultvalue][in] */ BSTR Source = L"") = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RefreshChangesFromModificationLog( 
            /* [in] */ ITRiASRefreshChangesCallback *Callback) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASDatabaseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASDatabase * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASDatabase * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASDatabase * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASDatabase * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASDatabase * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASDatabase * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASDatabase * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            ITRiASDatabase * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Application )( 
            ITRiASDatabase * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            ITRiASDatabase * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Parent )( 
            ITRiASDatabase * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VersionLong )( 
            ITRiASDatabase * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [restricted][hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Handle )( 
            ITRiASDatabase * This,
            /* [retval][out] */ INT_PTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsDirty )( 
            ITRiASDatabase * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsDirty )( 
            ITRiASDatabase * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OpenedAsCopy )( 
            ITRiASDatabase * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CouldOpenTarget )( 
            ITRiASDatabase * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SchemaUpdatable )( 
            ITRiASDatabase * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ITRiASDatabase * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            ITRiASDatabase * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CollatingOrder )( 
            ITRiASDatabase * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Connect )( 
            ITRiASDatabase * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Transactions )( 
            ITRiASDatabase * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Updatable )( 
            ITRiASDatabase * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Temporary )( 
            ITRiASDatabase * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Temporary )( 
            ITRiASDatabase * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TemporaryName )( 
            ITRiASDatabase * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            ITRiASDatabase * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StorageMode )( 
            ITRiASDatabase * This,
            /* [retval][out] */ DATABASESTORAGEMODE *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateDatabase )( 
            ITRiASDatabase * This,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Locale,
            /* [in] */ BSTR Source);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateDatabaseFromFiles )( 
            ITRiASDatabase * This,
            /* [in] */ IUnknown *FileNames,
            /* [in] */ BSTR Locale,
            /* [in] */ BSTR Source);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OpenDatabase )( 
            ITRiASDatabase * This,
            /* [in] */ BSTR Name,
            /* [defaultvalue][in] */ VARIANT_BOOL Exclusive,
            /* [defaultvalue][in] */ VARIANT_BOOL ReadOnly,
            /* [defaultvalue][in] */ VARIANT_BOOL ModTrack,
            /* [defaultvalue][in] */ BSTR Source);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OpenFilesAsDatabase )( 
            ITRiASDatabase * This,
            /* [in] */ IUnknown *FileNames,
            /* [defaultvalue][in] */ VARIANT_BOOL Exclusive,
            /* [defaultvalue][in] */ VARIANT_BOOL ReadOnly,
            /* [defaultvalue][in] */ VARIANT_BOOL ModTrack,
            /* [defaultvalue][in] */ BSTR Source);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Save )( 
            ITRiASDatabase * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveAs )( 
            ITRiASDatabase * This,
            /* [in] */ BSTR NewName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Close )( 
            ITRiASDatabase * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *BeginTrans )( 
            ITRiASDatabase * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ClearModificationLog )( 
            ITRiASDatabase * This,
            /* [defaultvalue][in] */ LONG Entry);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CommitTrans )( 
            ITRiASDatabase * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Rollback )( 
            ITRiASDatabase * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReLoad )( 
            ITRiASDatabase * This,
            /* [in] */ RELOADDATABASE ToReLoad);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateDatabaseOnStg )( 
            ITRiASDatabase * This,
            /* [in] */ IUnknown *Storage,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Locale,
            /* [in] */ BSTR Source);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OpenStorageAsDatabase )( 
            ITRiASDatabase * This,
            /* [in] */ IUnknown *Storage,
            /* [defaultvalue][in] */ VARIANT_BOOL Exclusive,
            /* [defaultvalue][in] */ VARIANT_BOOL ReadOnly,
            /* [defaultvalue][in] */ VARIANT_BOOL ModTrack,
            /* [defaultvalue][in] */ BSTR Source);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RefreshChangesFromModificationLog )( 
            ITRiASDatabase * This,
            /* [in] */ ITRiASRefreshChangesCallback *Callback);
        
        END_INTERFACE
    } ITRiASDatabaseVtbl;

    interface ITRiASDatabase
    {
        CONST_VTBL struct ITRiASDatabaseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASDatabase_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASDatabase_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASDatabase_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASDatabase_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASDatabase_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASDatabase_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASDatabase_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASDatabase_get_Application(This,pVal)	\
    (This)->lpVtbl -> get_Application(This,pVal)

#define ITRiASDatabase_put_Application(This,newVal)	\
    (This)->lpVtbl -> put_Application(This,newVal)

#define ITRiASDatabase_get_Parent(This,pVal)	\
    (This)->lpVtbl -> get_Parent(This,pVal)

#define ITRiASDatabase_put_Parent(This,newVal)	\
    (This)->lpVtbl -> put_Parent(This,newVal)


#define ITRiASDatabase_get_VersionLong(This,pVal)	\
    (This)->lpVtbl -> get_VersionLong(This,pVal)

#define ITRiASDatabase_get_Handle(This,pVal)	\
    (This)->lpVtbl -> get_Handle(This,pVal)

#define ITRiASDatabase_get_IsDirty(This,pVal)	\
    (This)->lpVtbl -> get_IsDirty(This,pVal)

#define ITRiASDatabase_put_IsDirty(This,newVal)	\
    (This)->lpVtbl -> put_IsDirty(This,newVal)

#define ITRiASDatabase_get_OpenedAsCopy(This,pVal)	\
    (This)->lpVtbl -> get_OpenedAsCopy(This,pVal)

#define ITRiASDatabase_get_CouldOpenTarget(This,pVal)	\
    (This)->lpVtbl -> get_CouldOpenTarget(This,pVal)

#define ITRiASDatabase_get_SchemaUpdatable(This,pVal)	\
    (This)->lpVtbl -> get_SchemaUpdatable(This,pVal)

#define ITRiASDatabase_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define ITRiASDatabase_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define ITRiASDatabase_get_CollatingOrder(This,pVal)	\
    (This)->lpVtbl -> get_CollatingOrder(This,pVal)

#define ITRiASDatabase_get_Connect(This,pVal)	\
    (This)->lpVtbl -> get_Connect(This,pVal)

#define ITRiASDatabase_get_Transactions(This,pVal)	\
    (This)->lpVtbl -> get_Transactions(This,pVal)

#define ITRiASDatabase_get_Updatable(This,pVal)	\
    (This)->lpVtbl -> get_Updatable(This,pVal)

#define ITRiASDatabase_get_Temporary(This,pVal)	\
    (This)->lpVtbl -> get_Temporary(This,pVal)

#define ITRiASDatabase_put_Temporary(This,newVal)	\
    (This)->lpVtbl -> put_Temporary(This,newVal)

#define ITRiASDatabase_get_TemporaryName(This,pVal)	\
    (This)->lpVtbl -> get_TemporaryName(This,pVal)

#define ITRiASDatabase_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define ITRiASDatabase_get_StorageMode(This,pVal)	\
    (This)->lpVtbl -> get_StorageMode(This,pVal)

#define ITRiASDatabase_CreateDatabase(This,Name,Locale,Source)	\
    (This)->lpVtbl -> CreateDatabase(This,Name,Locale,Source)

#define ITRiASDatabase_CreateDatabaseFromFiles(This,FileNames,Locale,Source)	\
    (This)->lpVtbl -> CreateDatabaseFromFiles(This,FileNames,Locale,Source)

#define ITRiASDatabase_OpenDatabase(This,Name,Exclusive,ReadOnly,ModTrack,Source)	\
    (This)->lpVtbl -> OpenDatabase(This,Name,Exclusive,ReadOnly,ModTrack,Source)

#define ITRiASDatabase_OpenFilesAsDatabase(This,FileNames,Exclusive,ReadOnly,ModTrack,Source)	\
    (This)->lpVtbl -> OpenFilesAsDatabase(This,FileNames,Exclusive,ReadOnly,ModTrack,Source)

#define ITRiASDatabase_Save(This)	\
    (This)->lpVtbl -> Save(This)

#define ITRiASDatabase_SaveAs(This,NewName)	\
    (This)->lpVtbl -> SaveAs(This,NewName)

#define ITRiASDatabase_Close(This)	\
    (This)->lpVtbl -> Close(This)

#define ITRiASDatabase_BeginTrans(This)	\
    (This)->lpVtbl -> BeginTrans(This)

#define ITRiASDatabase_ClearModificationLog(This,Entry)	\
    (This)->lpVtbl -> ClearModificationLog(This,Entry)

#define ITRiASDatabase_CommitTrans(This)	\
    (This)->lpVtbl -> CommitTrans(This)

#define ITRiASDatabase_Rollback(This)	\
    (This)->lpVtbl -> Rollback(This)

#define ITRiASDatabase_ReLoad(This,ToReLoad)	\
    (This)->lpVtbl -> ReLoad(This,ToReLoad)

#define ITRiASDatabase_CreateDatabaseOnStg(This,Storage,Name,Locale,Source)	\
    (This)->lpVtbl -> CreateDatabaseOnStg(This,Storage,Name,Locale,Source)

#define ITRiASDatabase_OpenStorageAsDatabase(This,Storage,Exclusive,ReadOnly,ModTrack,Source)	\
    (This)->lpVtbl -> OpenStorageAsDatabase(This,Storage,Exclusive,ReadOnly,ModTrack,Source)

#define ITRiASDatabase_RefreshChangesFromModificationLog(This,Callback)	\
    (This)->lpVtbl -> RefreshChangesFromModificationLog(This,Callback)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_get_VersionLong_Proxy( 
    ITRiASDatabase * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB ITRiASDatabase_get_VersionLong_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_get_Handle_Proxy( 
    ITRiASDatabase * This,
    /* [retval][out] */ INT_PTR *pVal);


void __RPC_STUB ITRiASDatabase_get_Handle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_get_IsDirty_Proxy( 
    ITRiASDatabase * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASDatabase_get_IsDirty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_put_IsDirty_Proxy( 
    ITRiASDatabase * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ITRiASDatabase_put_IsDirty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_get_OpenedAsCopy_Proxy( 
    ITRiASDatabase * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASDatabase_get_OpenedAsCopy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_get_CouldOpenTarget_Proxy( 
    ITRiASDatabase * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASDatabase_get_CouldOpenTarget_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_get_SchemaUpdatable_Proxy( 
    ITRiASDatabase * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASDatabase_get_SchemaUpdatable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_get_Name_Proxy( 
    ITRiASDatabase * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASDatabase_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_get_Version_Proxy( 
    ITRiASDatabase * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASDatabase_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_get_CollatingOrder_Proxy( 
    ITRiASDatabase * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITRiASDatabase_get_CollatingOrder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_get_Connect_Proxy( 
    ITRiASDatabase * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASDatabase_get_Connect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_get_Transactions_Proxy( 
    ITRiASDatabase * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASDatabase_get_Transactions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_get_Updatable_Proxy( 
    ITRiASDatabase * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASDatabase_get_Updatable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_get_Temporary_Proxy( 
    ITRiASDatabase * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASDatabase_get_Temporary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_put_Temporary_Proxy( 
    ITRiASDatabase * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ITRiASDatabase_put_Temporary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_get_TemporaryName_Proxy( 
    ITRiASDatabase * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASDatabase_get_TemporaryName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_get_Type_Proxy( 
    ITRiASDatabase * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASDatabase_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_get_StorageMode_Proxy( 
    ITRiASDatabase * This,
    /* [retval][out] */ DATABASESTORAGEMODE *pVal);


void __RPC_STUB ITRiASDatabase_get_StorageMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_CreateDatabase_Proxy( 
    ITRiASDatabase * This,
    /* [in] */ BSTR Name,
    /* [in] */ BSTR Locale,
    /* [in] */ BSTR Source);


void __RPC_STUB ITRiASDatabase_CreateDatabase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_CreateDatabaseFromFiles_Proxy( 
    ITRiASDatabase * This,
    /* [in] */ IUnknown *FileNames,
    /* [in] */ BSTR Locale,
    /* [in] */ BSTR Source);


void __RPC_STUB ITRiASDatabase_CreateDatabaseFromFiles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_OpenDatabase_Proxy( 
    ITRiASDatabase * This,
    /* [in] */ BSTR Name,
    /* [defaultvalue][in] */ VARIANT_BOOL Exclusive,
    /* [defaultvalue][in] */ VARIANT_BOOL ReadOnly,
    /* [defaultvalue][in] */ VARIANT_BOOL ModTrack,
    /* [defaultvalue][in] */ BSTR Source);


void __RPC_STUB ITRiASDatabase_OpenDatabase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_OpenFilesAsDatabase_Proxy( 
    ITRiASDatabase * This,
    /* [in] */ IUnknown *FileNames,
    /* [defaultvalue][in] */ VARIANT_BOOL Exclusive,
    /* [defaultvalue][in] */ VARIANT_BOOL ReadOnly,
    /* [defaultvalue][in] */ VARIANT_BOOL ModTrack,
    /* [defaultvalue][in] */ BSTR Source);


void __RPC_STUB ITRiASDatabase_OpenFilesAsDatabase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_Save_Proxy( 
    ITRiASDatabase * This);


void __RPC_STUB ITRiASDatabase_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_SaveAs_Proxy( 
    ITRiASDatabase * This,
    /* [in] */ BSTR NewName);


void __RPC_STUB ITRiASDatabase_SaveAs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_Close_Proxy( 
    ITRiASDatabase * This);


void __RPC_STUB ITRiASDatabase_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_BeginTrans_Proxy( 
    ITRiASDatabase * This);


void __RPC_STUB ITRiASDatabase_BeginTrans_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_ClearModificationLog_Proxy( 
    ITRiASDatabase * This,
    /* [defaultvalue][in] */ LONG Entry);


void __RPC_STUB ITRiASDatabase_ClearModificationLog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_CommitTrans_Proxy( 
    ITRiASDatabase * This);


void __RPC_STUB ITRiASDatabase_CommitTrans_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_Rollback_Proxy( 
    ITRiASDatabase * This);


void __RPC_STUB ITRiASDatabase_Rollback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_ReLoad_Proxy( 
    ITRiASDatabase * This,
    /* [in] */ RELOADDATABASE ToReLoad);


void __RPC_STUB ITRiASDatabase_ReLoad_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_CreateDatabaseOnStg_Proxy( 
    ITRiASDatabase * This,
    /* [in] */ IUnknown *Storage,
    /* [in] */ BSTR Name,
    /* [in] */ BSTR Locale,
    /* [in] */ BSTR Source);


void __RPC_STUB ITRiASDatabase_CreateDatabaseOnStg_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_OpenStorageAsDatabase_Proxy( 
    ITRiASDatabase * This,
    /* [in] */ IUnknown *Storage,
    /* [defaultvalue][in] */ VARIANT_BOOL Exclusive,
    /* [defaultvalue][in] */ VARIANT_BOOL ReadOnly,
    /* [defaultvalue][in] */ VARIANT_BOOL ModTrack,
    /* [defaultvalue][in] */ BSTR Source);


void __RPC_STUB ITRiASDatabase_OpenStorageAsDatabase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASDatabase_RefreshChangesFromModificationLog_Proxy( 
    ITRiASDatabase * This,
    /* [in] */ ITRiASRefreshChangesCallback *Callback);


void __RPC_STUB ITRiASDatabase_RefreshChangesFromModificationLog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASDatabase_INTERFACE_DEFINED__ */


#ifndef __ITRiASAccessDatabase_INTERFACE_DEFINED__
#define __ITRiASAccessDatabase_INTERFACE_DEFINED__

/* interface ITRiASAccessDatabase */
/* [unique][helpstring][dual][uuid][object] */ 

#if !defined(_ENVELOPETYPE_DEFINED)
#define _ENVELOPETYPE_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagENVELOPETYPE
    {	ENVELOPETYPE_AllGeometries	= 0,
	ENVELOPETYPE_MaxPossible	= 1
    } 	ENVELOPETYPE;

#endif // _ENVELOPETYPE_DEFINED

EXTERN_C const IID IID_ITRiASAccessDatabase;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B7AEB938-922C-11D1-BA01-080036D63803")
    ITRiASAccessDatabase : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Views( 
            /* [retval][out] */ ITRiASViews **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StartViewName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ObjectsDefs( 
            /* [retval][out] */ ITRiASObjectsCollection **pIObjsDefs) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ObjectsDef( 
            /* [in] */ VARIANT vItem,
            /* [defaultvalue][in] */ VARIANT_BOOL fCreate,
            /* [defaultvalue][in] */ BSTR Type,
            /* [retval][out] */ ITRiASObjects **pIObjsDef) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Envelope( 
            /* [in] */ ENVELOPETYPE Type,
            /* [retval][out] */ IDispatch **Rect) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ObjectCount( 
            /* [retval][out] */ long *ObjCnt) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AttachedCS( 
            /* [in] */ BSTR DbName,
            /* [retval][out] */ BSTR *AssocCS) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConnectionFilter( 
            /* [retval][out] */ ITRiASConnectionFilter **Filter) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConnectionFilter( 
            /* [in] */ ITRiASConnectionFilter *Filter) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASAccessDatabaseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASAccessDatabase * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASAccessDatabase * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASAccessDatabase * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASAccessDatabase * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASAccessDatabase * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASAccessDatabase * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASAccessDatabase * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Views )( 
            ITRiASAccessDatabase * This,
            /* [retval][out] */ ITRiASViews **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartViewName )( 
            ITRiASAccessDatabase * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ObjectsDefs )( 
            ITRiASAccessDatabase * This,
            /* [retval][out] */ ITRiASObjectsCollection **pIObjsDefs);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ObjectsDef )( 
            ITRiASAccessDatabase * This,
            /* [in] */ VARIANT vItem,
            /* [defaultvalue][in] */ VARIANT_BOOL fCreate,
            /* [defaultvalue][in] */ BSTR Type,
            /* [retval][out] */ ITRiASObjects **pIObjsDef);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Envelope )( 
            ITRiASAccessDatabase * This,
            /* [in] */ ENVELOPETYPE Type,
            /* [retval][out] */ IDispatch **Rect);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ObjectCount )( 
            ITRiASAccessDatabase * This,
            /* [retval][out] */ long *ObjCnt);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AttachedCS )( 
            ITRiASAccessDatabase * This,
            /* [in] */ BSTR DbName,
            /* [retval][out] */ BSTR *AssocCS);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConnectionFilter )( 
            ITRiASAccessDatabase * This,
            /* [retval][out] */ ITRiASConnectionFilter **Filter);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ConnectionFilter )( 
            ITRiASAccessDatabase * This,
            /* [in] */ ITRiASConnectionFilter *Filter);
        
        END_INTERFACE
    } ITRiASAccessDatabaseVtbl;

    interface ITRiASAccessDatabase
    {
        CONST_VTBL struct ITRiASAccessDatabaseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASAccessDatabase_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASAccessDatabase_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASAccessDatabase_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASAccessDatabase_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASAccessDatabase_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASAccessDatabase_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASAccessDatabase_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASAccessDatabase_get_Views(This,pVal)	\
    (This)->lpVtbl -> get_Views(This,pVal)

#define ITRiASAccessDatabase_get_StartViewName(This,pVal)	\
    (This)->lpVtbl -> get_StartViewName(This,pVal)

#define ITRiASAccessDatabase_get_ObjectsDefs(This,pIObjsDefs)	\
    (This)->lpVtbl -> get_ObjectsDefs(This,pIObjsDefs)

#define ITRiASAccessDatabase_get_ObjectsDef(This,vItem,fCreate,Type,pIObjsDef)	\
    (This)->lpVtbl -> get_ObjectsDef(This,vItem,fCreate,Type,pIObjsDef)

#define ITRiASAccessDatabase_get_Envelope(This,Type,Rect)	\
    (This)->lpVtbl -> get_Envelope(This,Type,Rect)

#define ITRiASAccessDatabase_get_ObjectCount(This,ObjCnt)	\
    (This)->lpVtbl -> get_ObjectCount(This,ObjCnt)

#define ITRiASAccessDatabase_get_AttachedCS(This,DbName,AssocCS)	\
    (This)->lpVtbl -> get_AttachedCS(This,DbName,AssocCS)

#define ITRiASAccessDatabase_get_ConnectionFilter(This,Filter)	\
    (This)->lpVtbl -> get_ConnectionFilter(This,Filter)

#define ITRiASAccessDatabase_put_ConnectionFilter(This,Filter)	\
    (This)->lpVtbl -> put_ConnectionFilter(This,Filter)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASAccessDatabase_get_Views_Proxy( 
    ITRiASAccessDatabase * This,
    /* [retval][out] */ ITRiASViews **pVal);


void __RPC_STUB ITRiASAccessDatabase_get_Views_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASAccessDatabase_get_StartViewName_Proxy( 
    ITRiASAccessDatabase * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASAccessDatabase_get_StartViewName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASAccessDatabase_get_ObjectsDefs_Proxy( 
    ITRiASAccessDatabase * This,
    /* [retval][out] */ ITRiASObjectsCollection **pIObjsDefs);


void __RPC_STUB ITRiASAccessDatabase_get_ObjectsDefs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASAccessDatabase_get_ObjectsDef_Proxy( 
    ITRiASAccessDatabase * This,
    /* [in] */ VARIANT vItem,
    /* [defaultvalue][in] */ VARIANT_BOOL fCreate,
    /* [defaultvalue][in] */ BSTR Type,
    /* [retval][out] */ ITRiASObjects **pIObjsDef);


void __RPC_STUB ITRiASAccessDatabase_get_ObjectsDef_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASAccessDatabase_get_Envelope_Proxy( 
    ITRiASAccessDatabase * This,
    /* [in] */ ENVELOPETYPE Type,
    /* [retval][out] */ IDispatch **Rect);


void __RPC_STUB ITRiASAccessDatabase_get_Envelope_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASAccessDatabase_get_ObjectCount_Proxy( 
    ITRiASAccessDatabase * This,
    /* [retval][out] */ long *ObjCnt);


void __RPC_STUB ITRiASAccessDatabase_get_ObjectCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASAccessDatabase_get_AttachedCS_Proxy( 
    ITRiASAccessDatabase * This,
    /* [in] */ BSTR DbName,
    /* [retval][out] */ BSTR *AssocCS);


void __RPC_STUB ITRiASAccessDatabase_get_AttachedCS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASAccessDatabase_get_ConnectionFilter_Proxy( 
    ITRiASAccessDatabase * This,
    /* [retval][out] */ ITRiASConnectionFilter **Filter);


void __RPC_STUB ITRiASAccessDatabase_get_ConnectionFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASAccessDatabase_put_ConnectionFilter_Proxy( 
    ITRiASAccessDatabase * This,
    /* [in] */ ITRiASConnectionFilter *Filter);


void __RPC_STUB ITRiASAccessDatabase_put_ConnectionFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASAccessDatabase_INTERFACE_DEFINED__ */


#ifndef __ITRiASViews_INTERFACE_DEFINED__
#define __ITRiASViews_INTERFACE_DEFINED__

/* interface ITRiASViews */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASViews;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1CB3AB67-2E87-11D1-969D-00A024D6F582")
    ITRiASViews : public ITRiASBase
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ITRiASView **View) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE _NewEnum( 
            /* [retval][out] */ IUnknown **ppIEnum) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ ITRiASView **View) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT Index) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE _Add( 
            /* [in] */ ITRiASView *View,
            /* [defaultvalue][in] */ VARIANT_BOOL FullAdd = ( VARIANT_BOOL  )0xffff) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE _Clone( 
            /* [retval][out] */ ITRiASViews **Views) = 0;
        
        virtual /* [restricted][hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEventSink( 
            /* [in] */ IUnknown *pIUnk,
            /* [in] */ VARIANT_BOOL fAdvise) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveView( 
            /* [in] */ ITRiASView *View) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StartViewName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StartViewName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnFinalRelease( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASViewsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASViews * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASViews * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASViews * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASViews * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASViews * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASViews * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASViews * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            ITRiASViews * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Application )( 
            ITRiASViews * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            ITRiASViews * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Parent )( 
            ITRiASViews * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITRiASViews * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            ITRiASViews * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ITRiASView **View);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *_NewEnum )( 
            ITRiASViews * This,
            /* [retval][out] */ IUnknown **ppIEnum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ITRiASViews * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ ITRiASView **View);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ITRiASViews * This,
            /* [in] */ VARIANT Index);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *_Add )( 
            ITRiASViews * This,
            /* [in] */ ITRiASView *View,
            /* [defaultvalue][in] */ VARIANT_BOOL FullAdd);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *_Clone )( 
            ITRiASViews * This,
            /* [retval][out] */ ITRiASViews **Views);
        
        /* [restricted][hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEventSink )( 
            ITRiASViews * This,
            /* [in] */ IUnknown *pIUnk,
            /* [in] */ VARIANT_BOOL fAdvise);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveView )( 
            ITRiASViews * This,
            /* [in] */ ITRiASView *View);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartViewName )( 
            ITRiASViews * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartViewName )( 
            ITRiASViews * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnFinalRelease )( 
            ITRiASViews * This);
        
        END_INTERFACE
    } ITRiASViewsVtbl;

    interface ITRiASViews
    {
        CONST_VTBL struct ITRiASViewsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASViews_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASViews_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASViews_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASViews_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASViews_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASViews_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASViews_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASViews_get_Application(This,pVal)	\
    (This)->lpVtbl -> get_Application(This,pVal)

#define ITRiASViews_put_Application(This,newVal)	\
    (This)->lpVtbl -> put_Application(This,newVal)

#define ITRiASViews_get_Parent(This,pVal)	\
    (This)->lpVtbl -> get_Parent(This,pVal)

#define ITRiASViews_put_Parent(This,newVal)	\
    (This)->lpVtbl -> put_Parent(This,newVal)


#define ITRiASViews_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define ITRiASViews_Item(This,Index,View)	\
    (This)->lpVtbl -> Item(This,Index,View)

#define ITRiASViews__NewEnum(This,ppIEnum)	\
    (This)->lpVtbl -> _NewEnum(This,ppIEnum)

#define ITRiASViews_Add(This,Name,View)	\
    (This)->lpVtbl -> Add(This,Name,View)

#define ITRiASViews_Remove(This,Index)	\
    (This)->lpVtbl -> Remove(This,Index)

#define ITRiASViews__Add(This,View,FullAdd)	\
    (This)->lpVtbl -> _Add(This,View,FullAdd)

#define ITRiASViews__Clone(This,Views)	\
    (This)->lpVtbl -> _Clone(This,Views)

#define ITRiASViews_SetEventSink(This,pIUnk,fAdvise)	\
    (This)->lpVtbl -> SetEventSink(This,pIUnk,fAdvise)

#define ITRiASViews_RemoveView(This,View)	\
    (This)->lpVtbl -> RemoveView(This,View)

#define ITRiASViews_get_StartViewName(This,pVal)	\
    (This)->lpVtbl -> get_StartViewName(This,pVal)

#define ITRiASViews_put_StartViewName(This,newVal)	\
    (This)->lpVtbl -> put_StartViewName(This,newVal)

#define ITRiASViews_OnFinalRelease(This)	\
    (This)->lpVtbl -> OnFinalRelease(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASViews_get_Count_Proxy( 
    ITRiASViews * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITRiASViews_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASViews_Item_Proxy( 
    ITRiASViews * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ ITRiASView **View);


void __RPC_STUB ITRiASViews_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE ITRiASViews__NewEnum_Proxy( 
    ITRiASViews * This,
    /* [retval][out] */ IUnknown **ppIEnum);


void __RPC_STUB ITRiASViews__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASViews_Add_Proxy( 
    ITRiASViews * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ ITRiASView **View);


void __RPC_STUB ITRiASViews_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASViews_Remove_Proxy( 
    ITRiASViews * This,
    /* [in] */ VARIANT Index);


void __RPC_STUB ITRiASViews_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASViews__Add_Proxy( 
    ITRiASViews * This,
    /* [in] */ ITRiASView *View,
    /* [defaultvalue][in] */ VARIANT_BOOL FullAdd);


void __RPC_STUB ITRiASViews__Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASViews__Clone_Proxy( 
    ITRiASViews * This,
    /* [retval][out] */ ITRiASViews **Views);


void __RPC_STUB ITRiASViews__Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASViews_SetEventSink_Proxy( 
    ITRiASViews * This,
    /* [in] */ IUnknown *pIUnk,
    /* [in] */ VARIANT_BOOL fAdvise);


void __RPC_STUB ITRiASViews_SetEventSink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASViews_RemoveView_Proxy( 
    ITRiASViews * This,
    /* [in] */ ITRiASView *View);


void __RPC_STUB ITRiASViews_RemoveView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASViews_get_StartViewName_Proxy( 
    ITRiASViews * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASViews_get_StartViewName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASViews_put_StartViewName_Proxy( 
    ITRiASViews * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITRiASViews_put_StartViewName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASViews_OnFinalRelease_Proxy( 
    ITRiASViews * This);


void __RPC_STUB ITRiASViews_OnFinalRelease_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASViews_INTERFACE_DEFINED__ */


#ifndef __ITRiASView_INTERFACE_DEFINED__
#define __ITRiASView_INTERFACE_DEFINED__

/* interface ITRiASView */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASView;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1CB3AB65-2E87-11D1-969D-00A024D6F582")
    ITRiASView : public ITRiASBase
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ViewItems( 
            /* [retval][out] */ ITRiASViewItems **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ViewItem( 
            /* [in] */ VARIANT vItem,
            /* [defaultvalue][in] */ VARIANT_BOOL fCreate,
            /* [defaultvalue][in] */ BSTR Type,
            /* [retval][out] */ ITRiASViewItem **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsStartView( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IsStartView( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Relations( 
            /* [retval][out] */ ITRiASRelations **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Relations( 
            /* [in] */ ITRiASRelations *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddViewItem( 
            /* [in] */ ITRiASViewItem *Item) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ObjectsDefs( 
            /* [retval][out] */ ITRiASObjectsCollection **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnFinalRelease( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RelatedDataSourceName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RelatedDataSourceName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConnectionFilter( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConnectionFilter( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASViewVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASView * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASView * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASView * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASView * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASView * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASView * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASView * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            ITRiASView * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Application )( 
            ITRiASView * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            ITRiASView * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Parent )( 
            ITRiASView * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ITRiASView * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            ITRiASView * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ViewItems )( 
            ITRiASView * This,
            /* [retval][out] */ ITRiASViewItems **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ViewItem )( 
            ITRiASView * This,
            /* [in] */ VARIANT vItem,
            /* [defaultvalue][in] */ VARIANT_BOOL fCreate,
            /* [defaultvalue][in] */ BSTR Type,
            /* [retval][out] */ ITRiASViewItem **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsStartView )( 
            ITRiASView * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsStartView )( 
            ITRiASView * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Relations )( 
            ITRiASView * This,
            /* [retval][out] */ ITRiASRelations **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Relations )( 
            ITRiASView * This,
            /* [in] */ ITRiASRelations *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddViewItem )( 
            ITRiASView * This,
            /* [in] */ ITRiASViewItem *Item);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ObjectsDefs )( 
            ITRiASView * This,
            /* [retval][out] */ ITRiASObjectsCollection **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnFinalRelease )( 
            ITRiASView * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RelatedDataSourceName )( 
            ITRiASView * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RelatedDataSourceName )( 
            ITRiASView * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConnectionFilter )( 
            ITRiASView * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ConnectionFilter )( 
            ITRiASView * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } ITRiASViewVtbl;

    interface ITRiASView
    {
        CONST_VTBL struct ITRiASViewVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASView_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASView_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASView_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASView_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASView_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASView_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASView_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASView_get_Application(This,pVal)	\
    (This)->lpVtbl -> get_Application(This,pVal)

#define ITRiASView_put_Application(This,newVal)	\
    (This)->lpVtbl -> put_Application(This,newVal)

#define ITRiASView_get_Parent(This,pVal)	\
    (This)->lpVtbl -> get_Parent(This,pVal)

#define ITRiASView_put_Parent(This,newVal)	\
    (This)->lpVtbl -> put_Parent(This,newVal)


#define ITRiASView_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define ITRiASView_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define ITRiASView_get_ViewItems(This,pVal)	\
    (This)->lpVtbl -> get_ViewItems(This,pVal)

#define ITRiASView_get_ViewItem(This,vItem,fCreate,Type,pVal)	\
    (This)->lpVtbl -> get_ViewItem(This,vItem,fCreate,Type,pVal)

#define ITRiASView_get_IsStartView(This,pVal)	\
    (This)->lpVtbl -> get_IsStartView(This,pVal)

#define ITRiASView_put_IsStartView(This,newVal)	\
    (This)->lpVtbl -> put_IsStartView(This,newVal)

#define ITRiASView_get_Relations(This,pVal)	\
    (This)->lpVtbl -> get_Relations(This,pVal)

#define ITRiASView_put_Relations(This,pVal)	\
    (This)->lpVtbl -> put_Relations(This,pVal)

#define ITRiASView_AddViewItem(This,Item)	\
    (This)->lpVtbl -> AddViewItem(This,Item)

#define ITRiASView_get_ObjectsDefs(This,pVal)	\
    (This)->lpVtbl -> get_ObjectsDefs(This,pVal)

#define ITRiASView_OnFinalRelease(This)	\
    (This)->lpVtbl -> OnFinalRelease(This)

#define ITRiASView_get_RelatedDataSourceName(This,pVal)	\
    (This)->lpVtbl -> get_RelatedDataSourceName(This,pVal)

#define ITRiASView_put_RelatedDataSourceName(This,newVal)	\
    (This)->lpVtbl -> put_RelatedDataSourceName(This,newVal)

#define ITRiASView_get_ConnectionFilter(This,pVal)	\
    (This)->lpVtbl -> get_ConnectionFilter(This,pVal)

#define ITRiASView_put_ConnectionFilter(This,newVal)	\
    (This)->lpVtbl -> put_ConnectionFilter(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASView_get_Name_Proxy( 
    ITRiASView * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASView_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASView_put_Name_Proxy( 
    ITRiASView * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITRiASView_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASView_get_ViewItems_Proxy( 
    ITRiASView * This,
    /* [retval][out] */ ITRiASViewItems **pVal);


void __RPC_STUB ITRiASView_get_ViewItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASView_get_ViewItem_Proxy( 
    ITRiASView * This,
    /* [in] */ VARIANT vItem,
    /* [defaultvalue][in] */ VARIANT_BOOL fCreate,
    /* [defaultvalue][in] */ BSTR Type,
    /* [retval][out] */ ITRiASViewItem **pVal);


void __RPC_STUB ITRiASView_get_ViewItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASView_get_IsStartView_Proxy( 
    ITRiASView * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASView_get_IsStartView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASView_put_IsStartView_Proxy( 
    ITRiASView * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ITRiASView_put_IsStartView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASView_get_Relations_Proxy( 
    ITRiASView * This,
    /* [retval][out] */ ITRiASRelations **pVal);


void __RPC_STUB ITRiASView_get_Relations_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASView_put_Relations_Proxy( 
    ITRiASView * This,
    /* [in] */ ITRiASRelations *pVal);


void __RPC_STUB ITRiASView_put_Relations_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASView_AddViewItem_Proxy( 
    ITRiASView * This,
    /* [in] */ ITRiASViewItem *Item);


void __RPC_STUB ITRiASView_AddViewItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASView_get_ObjectsDefs_Proxy( 
    ITRiASView * This,
    /* [retval][out] */ ITRiASObjectsCollection **pVal);


void __RPC_STUB ITRiASView_get_ObjectsDefs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASView_OnFinalRelease_Proxy( 
    ITRiASView * This);


void __RPC_STUB ITRiASView_OnFinalRelease_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASView_get_RelatedDataSourceName_Proxy( 
    ITRiASView * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASView_get_RelatedDataSourceName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASView_put_RelatedDataSourceName_Proxy( 
    ITRiASView * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITRiASView_put_RelatedDataSourceName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASView_get_ConnectionFilter_Proxy( 
    ITRiASView * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASView_get_ConnectionFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASView_put_ConnectionFilter_Proxy( 
    ITRiASView * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITRiASView_put_ConnectionFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASView_INTERFACE_DEFINED__ */


#ifndef __ITRiASViewItems_INTERFACE_DEFINED__
#define __ITRiASViewItems_INTERFACE_DEFINED__

/* interface ITRiASViewItems */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASViewItems;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1CB3AB69-2E87-11D1-969D-00A024D6F582")
    ITRiASViewItems : public ITRiASBase
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ITRiASViewItem **ViewItem) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE _NewEnum( 
            /* [retval][out] */ IUnknown **ppIEnum) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ItemCount( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Desc,
            /* [defaultvalue][in] */ BSTR Type,
            /* [retval][out] */ ITRiASViewItem **ViewItem) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT Index) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE _Add( 
            /* [in] */ ITRiASViewItem *ViewItem,
            /* [defaultvalue][in] */ VARIANT_BOOL FullAdd = ( VARIANT_BOOL  )0xffff) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE _Clone( 
            /* [retval][out] */ ITRiASViewItems **ViewItems) = 0;
        
        virtual /* [restricted][hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEventSink( 
            /* [in] */ IUnknown *Unk,
            /* [in] */ VARIANT_BOOL fAdvise) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASViewItemsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASViewItems * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASViewItems * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASViewItems * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASViewItems * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASViewItems * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASViewItems * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASViewItems * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            ITRiASViewItems * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Application )( 
            ITRiASViewItems * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            ITRiASViewItems * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Parent )( 
            ITRiASViewItems * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITRiASViewItems * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            ITRiASViewItems * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ITRiASViewItem **ViewItem);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *_NewEnum )( 
            ITRiASViewItems * This,
            /* [retval][out] */ IUnknown **ppIEnum);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ItemCount )( 
            ITRiASViewItems * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ITRiASViewItems * This,
            /* [in] */ BSTR Desc,
            /* [defaultvalue][in] */ BSTR Type,
            /* [retval][out] */ ITRiASViewItem **ViewItem);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ITRiASViewItems * This,
            /* [in] */ VARIANT Index);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *_Add )( 
            ITRiASViewItems * This,
            /* [in] */ ITRiASViewItem *ViewItem,
            /* [defaultvalue][in] */ VARIANT_BOOL FullAdd);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *_Clone )( 
            ITRiASViewItems * This,
            /* [retval][out] */ ITRiASViewItems **ViewItems);
        
        /* [restricted][hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEventSink )( 
            ITRiASViewItems * This,
            /* [in] */ IUnknown *Unk,
            /* [in] */ VARIANT_BOOL fAdvise);
        
        END_INTERFACE
    } ITRiASViewItemsVtbl;

    interface ITRiASViewItems
    {
        CONST_VTBL struct ITRiASViewItemsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASViewItems_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASViewItems_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASViewItems_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASViewItems_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASViewItems_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASViewItems_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASViewItems_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASViewItems_get_Application(This,pVal)	\
    (This)->lpVtbl -> get_Application(This,pVal)

#define ITRiASViewItems_put_Application(This,newVal)	\
    (This)->lpVtbl -> put_Application(This,newVal)

#define ITRiASViewItems_get_Parent(This,pVal)	\
    (This)->lpVtbl -> get_Parent(This,pVal)

#define ITRiASViewItems_put_Parent(This,newVal)	\
    (This)->lpVtbl -> put_Parent(This,newVal)


#define ITRiASViewItems_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define ITRiASViewItems_Item(This,Index,ViewItem)	\
    (This)->lpVtbl -> Item(This,Index,ViewItem)

#define ITRiASViewItems__NewEnum(This,ppIEnum)	\
    (This)->lpVtbl -> _NewEnum(This,ppIEnum)

#define ITRiASViewItems_get_ItemCount(This,pVal)	\
    (This)->lpVtbl -> get_ItemCount(This,pVal)

#define ITRiASViewItems_Add(This,Desc,Type,ViewItem)	\
    (This)->lpVtbl -> Add(This,Desc,Type,ViewItem)

#define ITRiASViewItems_Remove(This,Index)	\
    (This)->lpVtbl -> Remove(This,Index)

#define ITRiASViewItems__Add(This,ViewItem,FullAdd)	\
    (This)->lpVtbl -> _Add(This,ViewItem,FullAdd)

#define ITRiASViewItems__Clone(This,ViewItems)	\
    (This)->lpVtbl -> _Clone(This,ViewItems)

#define ITRiASViewItems_SetEventSink(This,Unk,fAdvise)	\
    (This)->lpVtbl -> SetEventSink(This,Unk,fAdvise)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASViewItems_get_Count_Proxy( 
    ITRiASViewItems * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITRiASViewItems_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASViewItems_Item_Proxy( 
    ITRiASViewItems * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ ITRiASViewItem **ViewItem);


void __RPC_STUB ITRiASViewItems_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE ITRiASViewItems__NewEnum_Proxy( 
    ITRiASViewItems * This,
    /* [retval][out] */ IUnknown **ppIEnum);


void __RPC_STUB ITRiASViewItems__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASViewItems_get_ItemCount_Proxy( 
    ITRiASViewItems * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITRiASViewItems_get_ItemCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASViewItems_Add_Proxy( 
    ITRiASViewItems * This,
    /* [in] */ BSTR Desc,
    /* [defaultvalue][in] */ BSTR Type,
    /* [retval][out] */ ITRiASViewItem **ViewItem);


void __RPC_STUB ITRiASViewItems_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASViewItems_Remove_Proxy( 
    ITRiASViewItems * This,
    /* [in] */ VARIANT Index);


void __RPC_STUB ITRiASViewItems_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASViewItems__Add_Proxy( 
    ITRiASViewItems * This,
    /* [in] */ ITRiASViewItem *ViewItem,
    /* [defaultvalue][in] */ VARIANT_BOOL FullAdd);


void __RPC_STUB ITRiASViewItems__Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASViewItems__Clone_Proxy( 
    ITRiASViewItems * This,
    /* [retval][out] */ ITRiASViewItems **ViewItems);


void __RPC_STUB ITRiASViewItems__Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASViewItems_SetEventSink_Proxy( 
    ITRiASViewItems * This,
    /* [in] */ IUnknown *Unk,
    /* [in] */ VARIANT_BOOL fAdvise);


void __RPC_STUB ITRiASViewItems_SetEventSink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASViewItems_INTERFACE_DEFINED__ */


#ifndef __ITRiASViewItem_INTERFACE_DEFINED__
#define __ITRiASViewItem_INTERFACE_DEFINED__

/* interface ITRiASViewItem */
/* [unique][helpstring][dual][uuid][object] */ 

#if !defined(_OBJECTTYPE_DEFINED)
#define _OBJECTTYPE_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagOBJECTTYPE
    {	OBJECTTYPE_Point	= 1,
	OBJECTTYPE_Line	= 2,
	OBJECTTYPE_Area	= 4,
	OBJECTTYPE_Circle	= 4,
	OBJECTTYPE_Text	= 8,
	OBJECTTYPE_Complex	= 16,
	OBJECTTYPE_Unknown	= 0,
	OBJECTTYPE_AllSimple	= 0xf,
	OBJECTTYPE_All	= 0x1f
    } 	OBJECTTYPE;

#endif // _OBJECTTYPE_DEFINED

EXTERN_C const IID IID_ITRiASViewItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1CB3AB6B-2E87-11D1-969D-00A024D6F582")
    ITRiASViewItem : public ITRiASBase
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VisInfo( 
            /* [defaultvalue][in] */ OBJECTTYPE Type,
            /* [retval][out] */ DVisInfo **pVal) = 0;
        
        virtual /* [restricted][hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VisInfo( 
            /* [defaultvalue][in] */ OBJECTTYPE Type,
            /* [in] */ DVisInfo *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Objects( 
            /* [in] */ OBJECTTYPE Type,
            /* [retval][out] */ ITRiASObjects **pVal) = 0;
        
        virtual /* [restricted][hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Objects( 
            /* [in] */ OBJECTTYPE Type,
            /* [in] */ ITRiASObjects *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ObjectTypes( 
            /* [retval][out] */ OBJECTTYPE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ObjectTypes( 
            /* [in] */ OBJECTTYPE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Types( 
            /* [retval][out] */ OBJECTTYPE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Types( 
            /* [in] */ OBJECTTYPE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultTypes( 
            /* [retval][out] */ OBJECTTYPE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DefaultTypes( 
            /* [in] */ OBJECTTYPE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ItemCount( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ObjectsMoniker( 
            /* [in] */ OBJECTTYPE rgType,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ObjectsMoniker( 
            /* [in] */ OBJECTTYPE rgType,
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASViewItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASViewItem * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASViewItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASViewItem * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASViewItem * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASViewItem * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASViewItem * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASViewItem * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            ITRiASViewItem * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Application )( 
            ITRiASViewItem * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            ITRiASViewItem * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Parent )( 
            ITRiASViewItem * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            ITRiASViewItem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            ITRiASViewItem * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VisInfo )( 
            ITRiASViewItem * This,
            /* [defaultvalue][in] */ OBJECTTYPE Type,
            /* [retval][out] */ DVisInfo **pVal);
        
        /* [restricted][hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VisInfo )( 
            ITRiASViewItem * This,
            /* [defaultvalue][in] */ OBJECTTYPE Type,
            /* [in] */ DVisInfo *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Objects )( 
            ITRiASViewItem * This,
            /* [in] */ OBJECTTYPE Type,
            /* [retval][out] */ ITRiASObjects **pVal);
        
        /* [restricted][hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Objects )( 
            ITRiASViewItem * This,
            /* [in] */ OBJECTTYPE Type,
            /* [in] */ ITRiASObjects *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ITRiASViewItem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ObjectTypes )( 
            ITRiASViewItem * This,
            /* [retval][out] */ OBJECTTYPE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ObjectTypes )( 
            ITRiASViewItem * This,
            /* [in] */ OBJECTTYPE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Types )( 
            ITRiASViewItem * This,
            /* [retval][out] */ OBJECTTYPE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Types )( 
            ITRiASViewItem * This,
            /* [in] */ OBJECTTYPE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultTypes )( 
            ITRiASViewItem * This,
            /* [retval][out] */ OBJECTTYPE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DefaultTypes )( 
            ITRiASViewItem * This,
            /* [in] */ OBJECTTYPE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ItemCount )( 
            ITRiASViewItem * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ObjectsMoniker )( 
            ITRiASViewItem * This,
            /* [in] */ OBJECTTYPE rgType,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ObjectsMoniker )( 
            ITRiASViewItem * This,
            /* [in] */ OBJECTTYPE rgType,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } ITRiASViewItemVtbl;

    interface ITRiASViewItem
    {
        CONST_VTBL struct ITRiASViewItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASViewItem_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASViewItem_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASViewItem_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASViewItem_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASViewItem_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASViewItem_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASViewItem_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASViewItem_get_Application(This,pVal)	\
    (This)->lpVtbl -> get_Application(This,pVal)

#define ITRiASViewItem_put_Application(This,newVal)	\
    (This)->lpVtbl -> put_Application(This,newVal)

#define ITRiASViewItem_get_Parent(This,pVal)	\
    (This)->lpVtbl -> get_Parent(This,pVal)

#define ITRiASViewItem_put_Parent(This,newVal)	\
    (This)->lpVtbl -> put_Parent(This,newVal)


#define ITRiASViewItem_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#define ITRiASViewItem_put_Description(This,newVal)	\
    (This)->lpVtbl -> put_Description(This,newVal)

#define ITRiASViewItem_get_VisInfo(This,Type,pVal)	\
    (This)->lpVtbl -> get_VisInfo(This,Type,pVal)

#define ITRiASViewItem_put_VisInfo(This,Type,newVal)	\
    (This)->lpVtbl -> put_VisInfo(This,Type,newVal)

#define ITRiASViewItem_get_Objects(This,Type,pVal)	\
    (This)->lpVtbl -> get_Objects(This,Type,pVal)

#define ITRiASViewItem_put_Objects(This,Type,newVal)	\
    (This)->lpVtbl -> put_Objects(This,Type,newVal)

#define ITRiASViewItem_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define ITRiASViewItem_get_ObjectTypes(This,pVal)	\
    (This)->lpVtbl -> get_ObjectTypes(This,pVal)

#define ITRiASViewItem_put_ObjectTypes(This,newVal)	\
    (This)->lpVtbl -> put_ObjectTypes(This,newVal)

#define ITRiASViewItem_get_Types(This,pVal)	\
    (This)->lpVtbl -> get_Types(This,pVal)

#define ITRiASViewItem_put_Types(This,newVal)	\
    (This)->lpVtbl -> put_Types(This,newVal)

#define ITRiASViewItem_get_DefaultTypes(This,pVal)	\
    (This)->lpVtbl -> get_DefaultTypes(This,pVal)

#define ITRiASViewItem_put_DefaultTypes(This,newVal)	\
    (This)->lpVtbl -> put_DefaultTypes(This,newVal)

#define ITRiASViewItem_get_ItemCount(This,pVal)	\
    (This)->lpVtbl -> get_ItemCount(This,pVal)

#define ITRiASViewItem_get_ObjectsMoniker(This,rgType,pVal)	\
    (This)->lpVtbl -> get_ObjectsMoniker(This,rgType,pVal)

#define ITRiASViewItem_put_ObjectsMoniker(This,rgType,newVal)	\
    (This)->lpVtbl -> put_ObjectsMoniker(This,rgType,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASViewItem_get_Description_Proxy( 
    ITRiASViewItem * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASViewItem_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASViewItem_put_Description_Proxy( 
    ITRiASViewItem * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITRiASViewItem_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASViewItem_get_VisInfo_Proxy( 
    ITRiASViewItem * This,
    /* [defaultvalue][in] */ OBJECTTYPE Type,
    /* [retval][out] */ DVisInfo **pVal);


void __RPC_STUB ITRiASViewItem_get_VisInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASViewItem_put_VisInfo_Proxy( 
    ITRiASViewItem * This,
    /* [defaultvalue][in] */ OBJECTTYPE Type,
    /* [in] */ DVisInfo *newVal);


void __RPC_STUB ITRiASViewItem_put_VisInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASViewItem_get_Objects_Proxy( 
    ITRiASViewItem * This,
    /* [in] */ OBJECTTYPE Type,
    /* [retval][out] */ ITRiASObjects **pVal);


void __RPC_STUB ITRiASViewItem_get_Objects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASViewItem_put_Objects_Proxy( 
    ITRiASViewItem * This,
    /* [in] */ OBJECTTYPE Type,
    /* [in] */ ITRiASObjects *newVal);


void __RPC_STUB ITRiASViewItem_put_Objects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASViewItem_get_Name_Proxy( 
    ITRiASViewItem * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASViewItem_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASViewItem_get_ObjectTypes_Proxy( 
    ITRiASViewItem * This,
    /* [retval][out] */ OBJECTTYPE *pVal);


void __RPC_STUB ITRiASViewItem_get_ObjectTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASViewItem_put_ObjectTypes_Proxy( 
    ITRiASViewItem * This,
    /* [in] */ OBJECTTYPE newVal);


void __RPC_STUB ITRiASViewItem_put_ObjectTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASViewItem_get_Types_Proxy( 
    ITRiASViewItem * This,
    /* [retval][out] */ OBJECTTYPE *pVal);


void __RPC_STUB ITRiASViewItem_get_Types_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASViewItem_put_Types_Proxy( 
    ITRiASViewItem * This,
    /* [in] */ OBJECTTYPE newVal);


void __RPC_STUB ITRiASViewItem_put_Types_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASViewItem_get_DefaultTypes_Proxy( 
    ITRiASViewItem * This,
    /* [retval][out] */ OBJECTTYPE *pVal);


void __RPC_STUB ITRiASViewItem_get_DefaultTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASViewItem_put_DefaultTypes_Proxy( 
    ITRiASViewItem * This,
    /* [in] */ OBJECTTYPE newVal);


void __RPC_STUB ITRiASViewItem_put_DefaultTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASViewItem_get_ItemCount_Proxy( 
    ITRiASViewItem * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITRiASViewItem_get_ItemCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASViewItem_get_ObjectsMoniker_Proxy( 
    ITRiASViewItem * This,
    /* [in] */ OBJECTTYPE rgType,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASViewItem_get_ObjectsMoniker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASViewItem_put_ObjectsMoniker_Proxy( 
    ITRiASViewItem * This,
    /* [in] */ OBJECTTYPE rgType,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITRiASViewItem_put_ObjectsMoniker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASViewItem_INTERFACE_DEFINED__ */


#ifndef __ITRiASObject_INTERFACE_DEFINED__
#define __ITRiASObject_INTERFACE_DEFINED__

/* interface ITRiASObject */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1CB3AB6F-2E87-11D1-969D-00A024D6F582")
    ITRiASObject : public ITRiASBase
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ OBJECTTYPE *pVal) = 0;
        
        virtual /* [hidden][restricted][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ OBJECTTYPE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [restricted][hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Handle( 
            /* [retval][out] */ INT_PTR *pVal) = 0;
        
        virtual /* [restricted][hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Handle( 
            /* [in] */ INT_PTR newVal) = 0;
        
        virtual /* [restricted][hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ObjectsHandle( 
            /* [retval][out] */ INT_PTR *pVal) = 0;
        
        virtual /* [restricted][hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ObjectsHandle( 
            /* [in] */ INT_PTR newVal) = 0;
        
        virtual /* [helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_ObjectCallback( 
            ITRiASObjectCallback *pICB) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DatabaseHandle( 
            /* [retval][out] */ INT_PTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Features( 
            /* [retval][out] */ ITRiASFeatures **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Features( 
            /* [in] */ ITRiASFeatures *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GeometryFeatures( 
            /* [retval][out] */ ITRiASFeatures **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_GeometryFeatures( 
            /* [in] */ ITRiASFeatures *newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASObject * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASObject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASObject * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASObject * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASObject * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASObject * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASObject * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            ITRiASObject * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Application )( 
            ITRiASObject * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            ITRiASObject * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Parent )( 
            ITRiASObject * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            ITRiASObject * This,
            /* [retval][out] */ OBJECTTYPE *pVal);
        
        /* [hidden][restricted][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Type )( 
            ITRiASObject * This,
            /* [in] */ OBJECTTYPE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ITRiASObject * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            ITRiASObject * This,
            /* [in] */ BSTR newVal);
        
        /* [restricted][hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Handle )( 
            ITRiASObject * This,
            /* [retval][out] */ INT_PTR *pVal);
        
        /* [restricted][hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Handle )( 
            ITRiASObject * This,
            /* [in] */ INT_PTR newVal);
        
        /* [restricted][hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ObjectsHandle )( 
            ITRiASObject * This,
            /* [retval][out] */ INT_PTR *pVal);
        
        /* [restricted][hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ObjectsHandle )( 
            ITRiASObject * This,
            /* [in] */ INT_PTR newVal);
        
        /* [helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_ObjectCallback )( 
            ITRiASObject * This,
            ITRiASObjectCallback *pICB);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DatabaseHandle )( 
            ITRiASObject * This,
            /* [retval][out] */ INT_PTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Features )( 
            ITRiASObject * This,
            /* [retval][out] */ ITRiASFeatures **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Features )( 
            ITRiASObject * This,
            /* [in] */ ITRiASFeatures *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GeometryFeatures )( 
            ITRiASObject * This,
            /* [retval][out] */ ITRiASFeatures **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_GeometryFeatures )( 
            ITRiASObject * This,
            /* [in] */ ITRiASFeatures *newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Delete )( 
            ITRiASObject * This);
        
        END_INTERFACE
    } ITRiASObjectVtbl;

    interface ITRiASObject
    {
        CONST_VTBL struct ITRiASObjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASObject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASObject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASObject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASObject_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASObject_get_Application(This,pVal)	\
    (This)->lpVtbl -> get_Application(This,pVal)

#define ITRiASObject_put_Application(This,newVal)	\
    (This)->lpVtbl -> put_Application(This,newVal)

#define ITRiASObject_get_Parent(This,pVal)	\
    (This)->lpVtbl -> get_Parent(This,pVal)

#define ITRiASObject_put_Parent(This,newVal)	\
    (This)->lpVtbl -> put_Parent(This,newVal)


#define ITRiASObject_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define ITRiASObject_put_Type(This,newVal)	\
    (This)->lpVtbl -> put_Type(This,newVal)

#define ITRiASObject_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define ITRiASObject_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define ITRiASObject_get_Handle(This,pVal)	\
    (This)->lpVtbl -> get_Handle(This,pVal)

#define ITRiASObject_put_Handle(This,newVal)	\
    (This)->lpVtbl -> put_Handle(This,newVal)

#define ITRiASObject_get_ObjectsHandle(This,pVal)	\
    (This)->lpVtbl -> get_ObjectsHandle(This,pVal)

#define ITRiASObject_put_ObjectsHandle(This,newVal)	\
    (This)->lpVtbl -> put_ObjectsHandle(This,newVal)

#define ITRiASObject_putref_ObjectCallback(This,pICB)	\
    (This)->lpVtbl -> putref_ObjectCallback(This,pICB)

#define ITRiASObject_get_DatabaseHandle(This,pVal)	\
    (This)->lpVtbl -> get_DatabaseHandle(This,pVal)

#define ITRiASObject_get_Features(This,pVal)	\
    (This)->lpVtbl -> get_Features(This,pVal)

#define ITRiASObject_put_Features(This,newVal)	\
    (This)->lpVtbl -> put_Features(This,newVal)

#define ITRiASObject_get_GeometryFeatures(This,pVal)	\
    (This)->lpVtbl -> get_GeometryFeatures(This,pVal)

#define ITRiASObject_put_GeometryFeatures(This,newVal)	\
    (This)->lpVtbl -> put_GeometryFeatures(This,newVal)

#define ITRiASObject_Delete(This)	\
    (This)->lpVtbl -> Delete(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObject_get_Type_Proxy( 
    ITRiASObject * This,
    /* [retval][out] */ OBJECTTYPE *pVal);


void __RPC_STUB ITRiASObject_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][restricted][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASObject_put_Type_Proxy( 
    ITRiASObject * This,
    /* [in] */ OBJECTTYPE newVal);


void __RPC_STUB ITRiASObject_put_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObject_get_Name_Proxy( 
    ITRiASObject * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASObject_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASObject_put_Name_Proxy( 
    ITRiASObject * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITRiASObject_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObject_get_Handle_Proxy( 
    ITRiASObject * This,
    /* [retval][out] */ INT_PTR *pVal);


void __RPC_STUB ITRiASObject_get_Handle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASObject_put_Handle_Proxy( 
    ITRiASObject * This,
    /* [in] */ INT_PTR newVal);


void __RPC_STUB ITRiASObject_put_Handle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObject_get_ObjectsHandle_Proxy( 
    ITRiASObject * This,
    /* [retval][out] */ INT_PTR *pVal);


void __RPC_STUB ITRiASObject_get_ObjectsHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASObject_put_ObjectsHandle_Proxy( 
    ITRiASObject * This,
    /* [in] */ INT_PTR newVal);


void __RPC_STUB ITRiASObject_put_ObjectsHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE ITRiASObject_putref_ObjectCallback_Proxy( 
    ITRiASObject * This,
    ITRiASObjectCallback *pICB);


void __RPC_STUB ITRiASObject_putref_ObjectCallback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObject_get_DatabaseHandle_Proxy( 
    ITRiASObject * This,
    /* [retval][out] */ INT_PTR *pVal);


void __RPC_STUB ITRiASObject_get_DatabaseHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObject_get_Features_Proxy( 
    ITRiASObject * This,
    /* [retval][out] */ ITRiASFeatures **pVal);


void __RPC_STUB ITRiASObject_get_Features_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASObject_put_Features_Proxy( 
    ITRiASObject * This,
    /* [in] */ ITRiASFeatures *newVal);


void __RPC_STUB ITRiASObject_put_Features_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObject_get_GeometryFeatures_Proxy( 
    ITRiASObject * This,
    /* [retval][out] */ ITRiASFeatures **pVal);


void __RPC_STUB ITRiASObject_get_GeometryFeatures_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASObject_put_GeometryFeatures_Proxy( 
    ITRiASObject * This,
    /* [in] */ ITRiASFeatures *newVal);


void __RPC_STUB ITRiASObject_put_GeometryFeatures_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObject_Delete_Proxy( 
    ITRiASObject * This);


void __RPC_STUB ITRiASObject_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASObject_INTERFACE_DEFINED__ */


#ifndef __ITRiASObjectCallback_INTERFACE_DEFINED__
#define __ITRiASObjectCallback_INTERFACE_DEFINED__

/* interface ITRiASObjectCallback */
/* [unique][helpstring][oleautomation][uuid][object] */ 

#if !defined(_CHANGEDOBJECT_DEFINED)
#define _CHANGEDOBJECT_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagCHANGEDOBJECT
    {	CHANGEDOBJECT_Name	= 0x1,
	CHANGEDOBJECT_Handle	= 0x2,
	CHANGEDOBJECT_Type	= 0x4
    } 	CHANGEDOBJECT;

#endif // _CHANGEDOBJECT_DEFINED
#if !defined(_SETUPOBJECTMODE_DEFINED)
#define _SETUPOBJECTMODE_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagSETUPOBJECTMODE
    {	SETUPOBJECTMODE_InitOrLoad	= 0,
	SETUPOBJECTMODE_Normal	= 1,
	SETUPOBJECTMODE_Force	= 0x8000
    } 	SETUPOBJECTMODE;

#endif // _SETUPOBJECTMODE_DEFINED
#if !defined(_SETUPFEATURESMODE_DEFINED)
#define _SETUPFEATURESMODE_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagSETUPFEATURESMODE
    {	SETUPFEATURESMODE_InitOrLoad	= 0,
	SETUPFEATURESMODE_Normal	= 1,
	SETUPFEATURESMODE_Reset	= 2,
	SETUPFEATURESMODE_Force	= 0x8000
    } 	SETUPFEATURESMODE;

#endif // _SETUPFEATURESMODE_DEFINED

EXTERN_C const IID IID_ITRiASObjectCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3F9633F4-C718-11D1-85D6-00600875138A")
    ITRiASObjectCallback : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultType( 
            /* [retval][out] */ BSTR *Type) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetupObject( 
            /* [defaultvalue][in] */ SETUPOBJECTMODE SetupMode = SETUPOBJECTMODE_Normal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetupFeatures( 
            /* [defaultvalue][in] */ SETUPFEATURESMODE SetupMode = SETUPFEATURESMODE_Normal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnChanging( 
            /* [in] */ CHANGEDOBJECT rgWhat,
            /* [in] */ VARIANT NewValue,
            /* [retval][out] */ VARIANT_BOOL *DisAllow) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnChanged( 
            /* [in] */ CHANGEDOBJECT rgWhat,
            /* [in] */ VARIANT OldValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnDelete( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnFinalRelease( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASObjectCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASObjectCallback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASObjectCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASObjectCallback * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultType )( 
            ITRiASObjectCallback * This,
            /* [retval][out] */ BSTR *Type);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetupObject )( 
            ITRiASObjectCallback * This,
            /* [defaultvalue][in] */ SETUPOBJECTMODE SetupMode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetupFeatures )( 
            ITRiASObjectCallback * This,
            /* [defaultvalue][in] */ SETUPFEATURESMODE SetupMode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnChanging )( 
            ITRiASObjectCallback * This,
            /* [in] */ CHANGEDOBJECT rgWhat,
            /* [in] */ VARIANT NewValue,
            /* [retval][out] */ VARIANT_BOOL *DisAllow);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnChanged )( 
            ITRiASObjectCallback * This,
            /* [in] */ CHANGEDOBJECT rgWhat,
            /* [in] */ VARIANT OldValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnDelete )( 
            ITRiASObjectCallback * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnFinalRelease )( 
            ITRiASObjectCallback * This);
        
        END_INTERFACE
    } ITRiASObjectCallbackVtbl;

    interface ITRiASObjectCallback
    {
        CONST_VTBL struct ITRiASObjectCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASObjectCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASObjectCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASObjectCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASObjectCallback_get_DefaultType(This,Type)	\
    (This)->lpVtbl -> get_DefaultType(This,Type)

#define ITRiASObjectCallback_SetupObject(This,SetupMode)	\
    (This)->lpVtbl -> SetupObject(This,SetupMode)

#define ITRiASObjectCallback_SetupFeatures(This,SetupMode)	\
    (This)->lpVtbl -> SetupFeatures(This,SetupMode)

#define ITRiASObjectCallback_OnChanging(This,rgWhat,NewValue,DisAllow)	\
    (This)->lpVtbl -> OnChanging(This,rgWhat,NewValue,DisAllow)

#define ITRiASObjectCallback_OnChanged(This,rgWhat,OldValue)	\
    (This)->lpVtbl -> OnChanged(This,rgWhat,OldValue)

#define ITRiASObjectCallback_OnDelete(This)	\
    (This)->lpVtbl -> OnDelete(This)

#define ITRiASObjectCallback_OnFinalRelease(This)	\
    (This)->lpVtbl -> OnFinalRelease(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObjectCallback_get_DefaultType_Proxy( 
    ITRiASObjectCallback * This,
    /* [retval][out] */ BSTR *Type);


void __RPC_STUB ITRiASObjectCallback_get_DefaultType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectCallback_SetupObject_Proxy( 
    ITRiASObjectCallback * This,
    /* [defaultvalue][in] */ SETUPOBJECTMODE SetupMode);


void __RPC_STUB ITRiASObjectCallback_SetupObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectCallback_SetupFeatures_Proxy( 
    ITRiASObjectCallback * This,
    /* [defaultvalue][in] */ SETUPFEATURESMODE SetupMode);


void __RPC_STUB ITRiASObjectCallback_SetupFeatures_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectCallback_OnChanging_Proxy( 
    ITRiASObjectCallback * This,
    /* [in] */ CHANGEDOBJECT rgWhat,
    /* [in] */ VARIANT NewValue,
    /* [retval][out] */ VARIANT_BOOL *DisAllow);


void __RPC_STUB ITRiASObjectCallback_OnChanging_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectCallback_OnChanged_Proxy( 
    ITRiASObjectCallback * This,
    /* [in] */ CHANGEDOBJECT rgWhat,
    /* [in] */ VARIANT OldValue);


void __RPC_STUB ITRiASObjectCallback_OnChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectCallback_OnDelete_Proxy( 
    ITRiASObjectCallback * This);


void __RPC_STUB ITRiASObjectCallback_OnDelete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectCallback_OnFinalRelease_Proxy( 
    ITRiASObjectCallback * This);


void __RPC_STUB ITRiASObjectCallback_OnFinalRelease_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASObjectCallback_INTERFACE_DEFINED__ */


#ifndef __ITRiASObjects_INTERFACE_DEFINED__
#define __ITRiASObjects_INTERFACE_DEFINED__

/* interface ITRiASObjects */
/* [unique][helpstring][dual][uuid][object] */ 

#if !defined(_OBJECTSCOLLECTIONTYPE_DEFINED)
#define _OBJECTSCOLLECTIONTYPE_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagOBJECTSCOLLECTIONTYPE
    {	OBJECTSCOLLECTIONTYPE_Unknown	= 0,
	OBJECTSCOLLECTIONTYPE_Class	= 1,
	OBJECTSCOLLECTIONTYPE_Query	= 2,
	OBJECTSCOLLECTIONTYPE_Temporary	= 4
    } 	OBJECTSCOLLECTIONTYPE;

#endif // _OBJECTSCOLLECTIONTYPE_DEFINED
#if !defined(_CLASSIFYMODE_DEFINED)
#define _CLASSIFYMODE_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagCLASSIFYMODE
    {	CLASSIFYMODE_DoNotClassify	= 0,
	CLASSIFYMODE_DatasourceOnly	= 0x1,
	CLASSIFYMODE_IgnoreNewProperties	= 0x2,
	CLASSIFYMODE_InitObjectType	= 0x4
    } 	CLASSIFYMODE;

#endif // _CLASSIFYMODE_DEFINED

EXTERN_C const IID IID_ITRiASObjects;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1CB3AB6D-2E87-11D1-969D-00A024D6F582")
    ITRiASObjects : public ITRiASBase
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][restricted][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE put_Count( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TableName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Types( 
            /* [retval][out] */ OBJECTTYPE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Types( 
            /* [in] */ OBJECTTYPE newVal) = 0;
        
        virtual /* [restricted][hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Handle( 
            /* [retval][out] */ INT_PTR *pVal) = 0;
        
        virtual /* [restricted][hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Handle( 
            /* [in] */ INT_PTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OKS( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OKS( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_ObjectsCallback( 
            ITRiASObjectsCallback *pICB) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Features( 
            /* [retval][out] */ ITRiASFeatures **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Features( 
            /* [in] */ ITRiASFeatures *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Feature( 
            /* [in] */ VARIANT Item,
            /* [defaultvalue][in] */ VARIANT_BOOL Create,
            /* [defaultvalue][in] */ BSTR Type,
            /* [retval][out] */ ITRiASFeature **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GeometryFeatures( 
            /* [retval][out] */ ITRiASFeatures **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_GeometryFeatures( 
            /* [in] */ ITRiASFeatures *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GeometryFeature( 
            /* [in] */ VARIANT Item,
            /* [defaultvalue][in] */ VARIANT_BOOL Create,
            /* [defaultvalue][in] */ BSTR Type,
            /* [retval][out] */ ITRiASFeature **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultGeometry( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DefaultGeometry( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PrimaryKey( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PrimaryKey( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CollectionType( 
            /* [retval][out] */ OBJECTSCOLLECTIONTYPE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CollectionType( 
            /* [in] */ OBJECTSCOLLECTIONTYPE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Updatable( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Updatable( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ITRiASObject **Obj) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE _NewEnum( 
            /* [retval][out] */ IUnknown **ppIEnum) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Name,
            /* [defaultvalue][in] */ BSTR Type,
            /* [defaultvalue][in] */ OBJECTTYPE rgType,
            /* [retval][out] */ ITRiASObject **Object) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE _Remove( 
            /* [in] */ VARIANT Index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Classify( 
            /* [in] */ ITRiASObject *Obj,
            /* [in] */ CLASSIFYMODE Mode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Delete( 
            /* [in] */ VARIANT Index) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE _Add( 
            /* [in] */ ITRiASObject *Obj,
            /* [defaultvalue][in] */ VARIANT_BOOL FullAdd = ( VARIANT_BOOL  )0) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE _Reset( void) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE _Clone( 
            /* [retval][out] */ ITRiASObjects **Objs) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [restricted][hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEventSink( 
            /* [in] */ IUnknown *Unk,
            /* [in] */ VARIANT_BOOL fAdvise) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASObjectsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASObjects * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASObjects * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASObjects * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASObjects * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASObjects * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASObjects * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASObjects * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            ITRiASObjects * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Application )( 
            ITRiASObjects * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            ITRiASObjects * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Parent )( 
            ITRiASObjects * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITRiASObjects * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Count )( 
            ITRiASObjects * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ITRiASObjects * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            ITRiASObjects * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            ITRiASObjects * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            ITRiASObjects * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TableName )( 
            ITRiASObjects * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Types )( 
            ITRiASObjects * This,
            /* [retval][out] */ OBJECTTYPE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Types )( 
            ITRiASObjects * This,
            /* [in] */ OBJECTTYPE newVal);
        
        /* [restricted][hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Handle )( 
            ITRiASObjects * This,
            /* [retval][out] */ INT_PTR *pVal);
        
        /* [restricted][hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Handle )( 
            ITRiASObjects * This,
            /* [in] */ INT_PTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OKS )( 
            ITRiASObjects * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OKS )( 
            ITRiASObjects * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_ObjectsCallback )( 
            ITRiASObjects * This,
            ITRiASObjectsCallback *pICB);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Features )( 
            ITRiASObjects * This,
            /* [retval][out] */ ITRiASFeatures **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Features )( 
            ITRiASObjects * This,
            /* [in] */ ITRiASFeatures *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Feature )( 
            ITRiASObjects * This,
            /* [in] */ VARIANT Item,
            /* [defaultvalue][in] */ VARIANT_BOOL Create,
            /* [defaultvalue][in] */ BSTR Type,
            /* [retval][out] */ ITRiASFeature **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GeometryFeatures )( 
            ITRiASObjects * This,
            /* [retval][out] */ ITRiASFeatures **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_GeometryFeatures )( 
            ITRiASObjects * This,
            /* [in] */ ITRiASFeatures *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GeometryFeature )( 
            ITRiASObjects * This,
            /* [in] */ VARIANT Item,
            /* [defaultvalue][in] */ VARIANT_BOOL Create,
            /* [defaultvalue][in] */ BSTR Type,
            /* [retval][out] */ ITRiASFeature **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultGeometry )( 
            ITRiASObjects * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DefaultGeometry )( 
            ITRiASObjects * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrimaryKey )( 
            ITRiASObjects * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PrimaryKey )( 
            ITRiASObjects * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CollectionType )( 
            ITRiASObjects * This,
            /* [retval][out] */ OBJECTSCOLLECTIONTYPE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CollectionType )( 
            ITRiASObjects * This,
            /* [in] */ OBJECTSCOLLECTIONTYPE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Updatable )( 
            ITRiASObjects * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Updatable )( 
            ITRiASObjects * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            ITRiASObjects * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ITRiASObject **Obj);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *_NewEnum )( 
            ITRiASObjects * This,
            /* [retval][out] */ IUnknown **ppIEnum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ITRiASObjects * This,
            /* [in] */ BSTR Name,
            /* [defaultvalue][in] */ BSTR Type,
            /* [defaultvalue][in] */ OBJECTTYPE rgType,
            /* [retval][out] */ ITRiASObject **Object);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *_Remove )( 
            ITRiASObjects * This,
            /* [in] */ VARIANT Index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Classify )( 
            ITRiASObjects * This,
            /* [in] */ ITRiASObject *Obj,
            /* [in] */ CLASSIFYMODE Mode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Delete )( 
            ITRiASObjects * This,
            /* [in] */ VARIANT Index);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *_Add )( 
            ITRiASObjects * This,
            /* [in] */ ITRiASObject *Obj,
            /* [defaultvalue][in] */ VARIANT_BOOL FullAdd);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *_Reset )( 
            ITRiASObjects * This);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *_Clone )( 
            ITRiASObjects * This,
            /* [retval][out] */ ITRiASObjects **Objs);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            ITRiASObjects * This);
        
        /* [restricted][hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEventSink )( 
            ITRiASObjects * This,
            /* [in] */ IUnknown *Unk,
            /* [in] */ VARIANT_BOOL fAdvise);
        
        END_INTERFACE
    } ITRiASObjectsVtbl;

    interface ITRiASObjects
    {
        CONST_VTBL struct ITRiASObjectsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASObjects_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASObjects_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASObjects_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASObjects_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASObjects_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASObjects_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASObjects_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASObjects_get_Application(This,pVal)	\
    (This)->lpVtbl -> get_Application(This,pVal)

#define ITRiASObjects_put_Application(This,newVal)	\
    (This)->lpVtbl -> put_Application(This,newVal)

#define ITRiASObjects_get_Parent(This,pVal)	\
    (This)->lpVtbl -> get_Parent(This,pVal)

#define ITRiASObjects_put_Parent(This,newVal)	\
    (This)->lpVtbl -> put_Parent(This,newVal)


#define ITRiASObjects_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define ITRiASObjects_put_Count(This,newVal)	\
    (This)->lpVtbl -> put_Count(This,newVal)

#define ITRiASObjects_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define ITRiASObjects_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define ITRiASObjects_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#define ITRiASObjects_put_Description(This,newVal)	\
    (This)->lpVtbl -> put_Description(This,newVal)

#define ITRiASObjects_get_TableName(This,pVal)	\
    (This)->lpVtbl -> get_TableName(This,pVal)

#define ITRiASObjects_get_Types(This,pVal)	\
    (This)->lpVtbl -> get_Types(This,pVal)

#define ITRiASObjects_put_Types(This,newVal)	\
    (This)->lpVtbl -> put_Types(This,newVal)

#define ITRiASObjects_get_Handle(This,pVal)	\
    (This)->lpVtbl -> get_Handle(This,pVal)

#define ITRiASObjects_put_Handle(This,newVal)	\
    (This)->lpVtbl -> put_Handle(This,newVal)

#define ITRiASObjects_get_OKS(This,pVal)	\
    (This)->lpVtbl -> get_OKS(This,pVal)

#define ITRiASObjects_put_OKS(This,newVal)	\
    (This)->lpVtbl -> put_OKS(This,newVal)

#define ITRiASObjects_putref_ObjectsCallback(This,pICB)	\
    (This)->lpVtbl -> putref_ObjectsCallback(This,pICB)

#define ITRiASObjects_get_Features(This,pVal)	\
    (This)->lpVtbl -> get_Features(This,pVal)

#define ITRiASObjects_put_Features(This,newVal)	\
    (This)->lpVtbl -> put_Features(This,newVal)

#define ITRiASObjects_get_Feature(This,Item,Create,Type,pVal)	\
    (This)->lpVtbl -> get_Feature(This,Item,Create,Type,pVal)

#define ITRiASObjects_get_GeometryFeatures(This,pVal)	\
    (This)->lpVtbl -> get_GeometryFeatures(This,pVal)

#define ITRiASObjects_put_GeometryFeatures(This,newVal)	\
    (This)->lpVtbl -> put_GeometryFeatures(This,newVal)

#define ITRiASObjects_get_GeometryFeature(This,Item,Create,Type,pVal)	\
    (This)->lpVtbl -> get_GeometryFeature(This,Item,Create,Type,pVal)

#define ITRiASObjects_get_DefaultGeometry(This,pVal)	\
    (This)->lpVtbl -> get_DefaultGeometry(This,pVal)

#define ITRiASObjects_put_DefaultGeometry(This,newVal)	\
    (This)->lpVtbl -> put_DefaultGeometry(This,newVal)

#define ITRiASObjects_get_PrimaryKey(This,pVal)	\
    (This)->lpVtbl -> get_PrimaryKey(This,pVal)

#define ITRiASObjects_put_PrimaryKey(This,newVal)	\
    (This)->lpVtbl -> put_PrimaryKey(This,newVal)

#define ITRiASObjects_get_CollectionType(This,pVal)	\
    (This)->lpVtbl -> get_CollectionType(This,pVal)

#define ITRiASObjects_put_CollectionType(This,newVal)	\
    (This)->lpVtbl -> put_CollectionType(This,newVal)

#define ITRiASObjects_get_Updatable(This,pVal)	\
    (This)->lpVtbl -> get_Updatable(This,pVal)

#define ITRiASObjects_put_Updatable(This,newVal)	\
    (This)->lpVtbl -> put_Updatable(This,newVal)

#define ITRiASObjects_Item(This,Index,Obj)	\
    (This)->lpVtbl -> Item(This,Index,Obj)

#define ITRiASObjects__NewEnum(This,ppIEnum)	\
    (This)->lpVtbl -> _NewEnum(This,ppIEnum)

#define ITRiASObjects_Add(This,Name,Type,rgType,Object)	\
    (This)->lpVtbl -> Add(This,Name,Type,rgType,Object)

#define ITRiASObjects__Remove(This,Index)	\
    (This)->lpVtbl -> _Remove(This,Index)

#define ITRiASObjects_Classify(This,Obj,Mode)	\
    (This)->lpVtbl -> Classify(This,Obj,Mode)

#define ITRiASObjects_Delete(This,Index)	\
    (This)->lpVtbl -> Delete(This,Index)

#define ITRiASObjects__Add(This,Obj,FullAdd)	\
    (This)->lpVtbl -> _Add(This,Obj,FullAdd)

#define ITRiASObjects__Reset(This)	\
    (This)->lpVtbl -> _Reset(This)

#define ITRiASObjects__Clone(This,Objs)	\
    (This)->lpVtbl -> _Clone(This,Objs)

#define ITRiASObjects_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define ITRiASObjects_SetEventSink(This,Unk,fAdvise)	\
    (This)->lpVtbl -> SetEventSink(This,Unk,fAdvise)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_get_Count_Proxy( 
    ITRiASObjects * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITRiASObjects_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][restricted][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_put_Count_Proxy( 
    ITRiASObjects * This,
    /* [in] */ long newVal);


void __RPC_STUB ITRiASObjects_put_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_get_Name_Proxy( 
    ITRiASObjects * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASObjects_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_put_Name_Proxy( 
    ITRiASObjects * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITRiASObjects_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_get_Description_Proxy( 
    ITRiASObjects * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASObjects_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_put_Description_Proxy( 
    ITRiASObjects * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITRiASObjects_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_get_TableName_Proxy( 
    ITRiASObjects * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASObjects_get_TableName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_get_Types_Proxy( 
    ITRiASObjects * This,
    /* [retval][out] */ OBJECTTYPE *pVal);


void __RPC_STUB ITRiASObjects_get_Types_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_put_Types_Proxy( 
    ITRiASObjects * This,
    /* [in] */ OBJECTTYPE newVal);


void __RPC_STUB ITRiASObjects_put_Types_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_get_Handle_Proxy( 
    ITRiASObjects * This,
    /* [retval][out] */ INT_PTR *pVal);


void __RPC_STUB ITRiASObjects_get_Handle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_put_Handle_Proxy( 
    ITRiASObjects * This,
    /* [in] */ INT_PTR newVal);


void __RPC_STUB ITRiASObjects_put_Handle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_get_OKS_Proxy( 
    ITRiASObjects * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASObjects_get_OKS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_put_OKS_Proxy( 
    ITRiASObjects * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITRiASObjects_put_OKS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_putref_ObjectsCallback_Proxy( 
    ITRiASObjects * This,
    ITRiASObjectsCallback *pICB);


void __RPC_STUB ITRiASObjects_putref_ObjectsCallback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_get_Features_Proxy( 
    ITRiASObjects * This,
    /* [retval][out] */ ITRiASFeatures **pVal);


void __RPC_STUB ITRiASObjects_get_Features_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_put_Features_Proxy( 
    ITRiASObjects * This,
    /* [in] */ ITRiASFeatures *newVal);


void __RPC_STUB ITRiASObjects_put_Features_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_get_Feature_Proxy( 
    ITRiASObjects * This,
    /* [in] */ VARIANT Item,
    /* [defaultvalue][in] */ VARIANT_BOOL Create,
    /* [defaultvalue][in] */ BSTR Type,
    /* [retval][out] */ ITRiASFeature **pVal);


void __RPC_STUB ITRiASObjects_get_Feature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_get_GeometryFeatures_Proxy( 
    ITRiASObjects * This,
    /* [retval][out] */ ITRiASFeatures **pVal);


void __RPC_STUB ITRiASObjects_get_GeometryFeatures_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_put_GeometryFeatures_Proxy( 
    ITRiASObjects * This,
    /* [in] */ ITRiASFeatures *newVal);


void __RPC_STUB ITRiASObjects_put_GeometryFeatures_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_get_GeometryFeature_Proxy( 
    ITRiASObjects * This,
    /* [in] */ VARIANT Item,
    /* [defaultvalue][in] */ VARIANT_BOOL Create,
    /* [defaultvalue][in] */ BSTR Type,
    /* [retval][out] */ ITRiASFeature **pVal);


void __RPC_STUB ITRiASObjects_get_GeometryFeature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_get_DefaultGeometry_Proxy( 
    ITRiASObjects * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASObjects_get_DefaultGeometry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_put_DefaultGeometry_Proxy( 
    ITRiASObjects * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITRiASObjects_put_DefaultGeometry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_get_PrimaryKey_Proxy( 
    ITRiASObjects * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASObjects_get_PrimaryKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_put_PrimaryKey_Proxy( 
    ITRiASObjects * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITRiASObjects_put_PrimaryKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_get_CollectionType_Proxy( 
    ITRiASObjects * This,
    /* [retval][out] */ OBJECTSCOLLECTIONTYPE *pVal);


void __RPC_STUB ITRiASObjects_get_CollectionType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_put_CollectionType_Proxy( 
    ITRiASObjects * This,
    /* [in] */ OBJECTSCOLLECTIONTYPE newVal);


void __RPC_STUB ITRiASObjects_put_CollectionType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_get_Updatable_Proxy( 
    ITRiASObjects * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASObjects_get_Updatable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_put_Updatable_Proxy( 
    ITRiASObjects * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ITRiASObjects_put_Updatable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_Item_Proxy( 
    ITRiASObjects * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ ITRiASObject **Obj);


void __RPC_STUB ITRiASObjects_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjects__NewEnum_Proxy( 
    ITRiASObjects * This,
    /* [retval][out] */ IUnknown **ppIEnum);


void __RPC_STUB ITRiASObjects__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_Add_Proxy( 
    ITRiASObjects * This,
    /* [in] */ BSTR Name,
    /* [defaultvalue][in] */ BSTR Type,
    /* [defaultvalue][in] */ OBJECTTYPE rgType,
    /* [retval][out] */ ITRiASObject **Object);


void __RPC_STUB ITRiASObjects_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjects__Remove_Proxy( 
    ITRiASObjects * This,
    /* [in] */ VARIANT Index);


void __RPC_STUB ITRiASObjects__Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_Classify_Proxy( 
    ITRiASObjects * This,
    /* [in] */ ITRiASObject *Obj,
    /* [in] */ CLASSIFYMODE Mode);


void __RPC_STUB ITRiASObjects_Classify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_Delete_Proxy( 
    ITRiASObjects * This,
    /* [in] */ VARIANT Index);


void __RPC_STUB ITRiASObjects_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjects__Add_Proxy( 
    ITRiASObjects * This,
    /* [in] */ ITRiASObject *Obj,
    /* [defaultvalue][in] */ VARIANT_BOOL FullAdd);


void __RPC_STUB ITRiASObjects__Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjects__Reset_Proxy( 
    ITRiASObjects * This);


void __RPC_STUB ITRiASObjects__Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjects__Clone_Proxy( 
    ITRiASObjects * This,
    /* [retval][out] */ ITRiASObjects **Objs);


void __RPC_STUB ITRiASObjects__Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_Refresh_Proxy( 
    ITRiASObjects * This);


void __RPC_STUB ITRiASObjects_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjects_SetEventSink_Proxy( 
    ITRiASObjects * This,
    /* [in] */ IUnknown *Unk,
    /* [in] */ VARIANT_BOOL fAdvise);


void __RPC_STUB ITRiASObjects_SetEventSink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASObjects_INTERFACE_DEFINED__ */


#ifndef __ITRiASObjectsEx_INTERFACE_DEFINED__
#define __ITRiASObjectsEx_INTERFACE_DEFINED__

/* interface ITRiASObjectsEx */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ITRiASObjectsEx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("22CE36EB-2399-41D1-848E-20592F3A5A74")
    ITRiASObjectsEx : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LocalHandle( 
            /* [retval][out] */ INT_PTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [defaultvalue][in] */ OBJECTTYPE rgType,
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Handles( 
            /* [in] */ long Count,
            /* [size_is][out][in] */ INT_PTR *pHandles) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASObjectsExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASObjectsEx * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASObjectsEx * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASObjectsEx * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASObjectsEx * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASObjectsEx * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASObjectsEx * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASObjectsEx * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LocalHandle )( 
            ITRiASObjectsEx * This,
            /* [retval][out] */ INT_PTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITRiASObjectsEx * This,
            /* [defaultvalue][in] */ OBJECTTYPE rgType,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Handles )( 
            ITRiASObjectsEx * This,
            /* [in] */ long Count,
            /* [size_is][out][in] */ INT_PTR *pHandles);
        
        END_INTERFACE
    } ITRiASObjectsExVtbl;

    interface ITRiASObjectsEx
    {
        CONST_VTBL struct ITRiASObjectsExVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASObjectsEx_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASObjectsEx_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASObjectsEx_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASObjectsEx_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASObjectsEx_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASObjectsEx_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASObjectsEx_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASObjectsEx_get_LocalHandle(This,pVal)	\
    (This)->lpVtbl -> get_LocalHandle(This,pVal)

#define ITRiASObjectsEx_get_Count(This,rgType,pVal)	\
    (This)->lpVtbl -> get_Count(This,rgType,pVal)

#define ITRiASObjectsEx_get_Handles(This,Count,pHandles)	\
    (This)->lpVtbl -> get_Handles(This,Count,pHandles)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsEx_get_LocalHandle_Proxy( 
    ITRiASObjectsEx * This,
    /* [retval][out] */ INT_PTR *pVal);


void __RPC_STUB ITRiASObjectsEx_get_LocalHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsEx_get_Count_Proxy( 
    ITRiASObjectsEx * This,
    /* [defaultvalue][in] */ OBJECTTYPE rgType,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITRiASObjectsEx_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsEx_get_Handles_Proxy( 
    ITRiASObjectsEx * This,
    /* [in] */ long Count,
    /* [size_is][out][in] */ INT_PTR *pHandles);


void __RPC_STUB ITRiASObjectsEx_get_Handles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASObjectsEx_INTERFACE_DEFINED__ */


#ifndef __ITRiASObjectsCallback_INTERFACE_DEFINED__
#define __ITRiASObjectsCallback_INTERFACE_DEFINED__

/* interface ITRiASObjectsCallback */
/* [unique][helpstring][oleautomation][uuid][object] */ 

#if !defined(_SETUPOBJECTSMODE_DEFINED)
#define _SETUPOBJECTSMODE_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagSETUPOBJECTSMODE
    {	SETUPOBJECTSMODE_InitOrLoad	= 0,
	SETUPOBJECTSMODE_Count	= 1,
	SETUPOBJECTSMODE_Load	= 2,
	SETUPOBJECTSMODE_ResetObjectInfo	= 4,
	SETUPOBJECTSMODE_Force	= 0x8000
    } 	SETUPOBJECTSMODE;

#endif // _SETUPOBJECTSMODE_DEFINED

EXTERN_C const IID IID_ITRiASObjectsCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3F9633F3-C718-11D1-85D6-00600875138A")
    ITRiASObjectsCallback : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultType( 
            /* [retval][out] */ BSTR *Type) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetupObjects( 
            /* [in] */ SETUPOBJECTSMODE Mode) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetupFeatures( 
            /* [defaultvalue][in] */ SETUPFEATURESMODE SetupMode = SETUPFEATURESMODE_Normal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnCreate( 
            /* [in] */ BSTR Name,
            /* [defaultvalue][in] */ BSTR Type,
            /* [defaultvalue][in] */ OBJECTTYPE rgType,
            /* [retval][out] */ ITRiASObject **Obj) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnChanging( 
            /* [in] */ CHANGEDOBJECTS rgWhat,
            /* [in] */ VARIANT NewValue,
            /* [retval][out] */ VARIANT_BOOL *DisAllow) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnChanged( 
            /* [in] */ CHANGEDOBJECTS rgWhat,
            /* [in] */ VARIANT OldValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnDelete( 
            /* [in] */ INT_PTR hObj) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnAdd( 
            /* [in] */ ITRiASObject *Obj,
            /* [in] */ CLASSIFYMODE Mode) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnRemove( 
            /* [in] */ ITRiASObject *Obj) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MapFeatureHandle( 
            /* [in] */ VARIANT NameOrHandle,
            /* [retval][out] */ VARIANT *NewNameOrHandle) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnFinalRelease( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASObjectsCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASObjectsCallback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASObjectsCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASObjectsCallback * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultType )( 
            ITRiASObjectsCallback * This,
            /* [retval][out] */ BSTR *Type);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetupObjects )( 
            ITRiASObjectsCallback * This,
            /* [in] */ SETUPOBJECTSMODE Mode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetupFeatures )( 
            ITRiASObjectsCallback * This,
            /* [defaultvalue][in] */ SETUPFEATURESMODE SetupMode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnCreate )( 
            ITRiASObjectsCallback * This,
            /* [in] */ BSTR Name,
            /* [defaultvalue][in] */ BSTR Type,
            /* [defaultvalue][in] */ OBJECTTYPE rgType,
            /* [retval][out] */ ITRiASObject **Obj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnChanging )( 
            ITRiASObjectsCallback * This,
            /* [in] */ CHANGEDOBJECTS rgWhat,
            /* [in] */ VARIANT NewValue,
            /* [retval][out] */ VARIANT_BOOL *DisAllow);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnChanged )( 
            ITRiASObjectsCallback * This,
            /* [in] */ CHANGEDOBJECTS rgWhat,
            /* [in] */ VARIANT OldValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnDelete )( 
            ITRiASObjectsCallback * This,
            /* [in] */ INT_PTR hObj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnAdd )( 
            ITRiASObjectsCallback * This,
            /* [in] */ ITRiASObject *Obj,
            /* [in] */ CLASSIFYMODE Mode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnRemove )( 
            ITRiASObjectsCallback * This,
            /* [in] */ ITRiASObject *Obj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *MapFeatureHandle )( 
            ITRiASObjectsCallback * This,
            /* [in] */ VARIANT NameOrHandle,
            /* [retval][out] */ VARIANT *NewNameOrHandle);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnFinalRelease )( 
            ITRiASObjectsCallback * This);
        
        END_INTERFACE
    } ITRiASObjectsCallbackVtbl;

    interface ITRiASObjectsCallback
    {
        CONST_VTBL struct ITRiASObjectsCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASObjectsCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASObjectsCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASObjectsCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASObjectsCallback_get_DefaultType(This,Type)	\
    (This)->lpVtbl -> get_DefaultType(This,Type)

#define ITRiASObjectsCallback_SetupObjects(This,Mode)	\
    (This)->lpVtbl -> SetupObjects(This,Mode)

#define ITRiASObjectsCallback_SetupFeatures(This,SetupMode)	\
    (This)->lpVtbl -> SetupFeatures(This,SetupMode)

#define ITRiASObjectsCallback_OnCreate(This,Name,Type,rgType,Obj)	\
    (This)->lpVtbl -> OnCreate(This,Name,Type,rgType,Obj)

#define ITRiASObjectsCallback_OnChanging(This,rgWhat,NewValue,DisAllow)	\
    (This)->lpVtbl -> OnChanging(This,rgWhat,NewValue,DisAllow)

#define ITRiASObjectsCallback_OnChanged(This,rgWhat,OldValue)	\
    (This)->lpVtbl -> OnChanged(This,rgWhat,OldValue)

#define ITRiASObjectsCallback_OnDelete(This,hObj)	\
    (This)->lpVtbl -> OnDelete(This,hObj)

#define ITRiASObjectsCallback_OnAdd(This,Obj,Mode)	\
    (This)->lpVtbl -> OnAdd(This,Obj,Mode)

#define ITRiASObjectsCallback_OnRemove(This,Obj)	\
    (This)->lpVtbl -> OnRemove(This,Obj)

#define ITRiASObjectsCallback_MapFeatureHandle(This,NameOrHandle,NewNameOrHandle)	\
    (This)->lpVtbl -> MapFeatureHandle(This,NameOrHandle,NewNameOrHandle)

#define ITRiASObjectsCallback_OnFinalRelease(This)	\
    (This)->lpVtbl -> OnFinalRelease(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsCallback_get_DefaultType_Proxy( 
    ITRiASObjectsCallback * This,
    /* [retval][out] */ BSTR *Type);


void __RPC_STUB ITRiASObjectsCallback_get_DefaultType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsCallback_SetupObjects_Proxy( 
    ITRiASObjectsCallback * This,
    /* [in] */ SETUPOBJECTSMODE Mode);


void __RPC_STUB ITRiASObjectsCallback_SetupObjects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsCallback_SetupFeatures_Proxy( 
    ITRiASObjectsCallback * This,
    /* [defaultvalue][in] */ SETUPFEATURESMODE SetupMode);


void __RPC_STUB ITRiASObjectsCallback_SetupFeatures_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsCallback_OnCreate_Proxy( 
    ITRiASObjectsCallback * This,
    /* [in] */ BSTR Name,
    /* [defaultvalue][in] */ BSTR Type,
    /* [defaultvalue][in] */ OBJECTTYPE rgType,
    /* [retval][out] */ ITRiASObject **Obj);


void __RPC_STUB ITRiASObjectsCallback_OnCreate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsCallback_OnChanging_Proxy( 
    ITRiASObjectsCallback * This,
    /* [in] */ CHANGEDOBJECTS rgWhat,
    /* [in] */ VARIANT NewValue,
    /* [retval][out] */ VARIANT_BOOL *DisAllow);


void __RPC_STUB ITRiASObjectsCallback_OnChanging_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsCallback_OnChanged_Proxy( 
    ITRiASObjectsCallback * This,
    /* [in] */ CHANGEDOBJECTS rgWhat,
    /* [in] */ VARIANT OldValue);


void __RPC_STUB ITRiASObjectsCallback_OnChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsCallback_OnDelete_Proxy( 
    ITRiASObjectsCallback * This,
    /* [in] */ INT_PTR hObj);


void __RPC_STUB ITRiASObjectsCallback_OnDelete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsCallback_OnAdd_Proxy( 
    ITRiASObjectsCallback * This,
    /* [in] */ ITRiASObject *Obj,
    /* [in] */ CLASSIFYMODE Mode);


void __RPC_STUB ITRiASObjectsCallback_OnAdd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsCallback_OnRemove_Proxy( 
    ITRiASObjectsCallback * This,
    /* [in] */ ITRiASObject *Obj);


void __RPC_STUB ITRiASObjectsCallback_OnRemove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsCallback_MapFeatureHandle_Proxy( 
    ITRiASObjectsCallback * This,
    /* [in] */ VARIANT NameOrHandle,
    /* [retval][out] */ VARIANT *NewNameOrHandle);


void __RPC_STUB ITRiASObjectsCallback_MapFeatureHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsCallback_OnFinalRelease_Proxy( 
    ITRiASObjectsCallback * This);


void __RPC_STUB ITRiASObjectsCallback_OnFinalRelease_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASObjectsCallback_INTERFACE_DEFINED__ */


#ifndef __ITRiASObjectsCollection_INTERFACE_DEFINED__
#define __ITRiASObjectsCollection_INTERFACE_DEFINED__

/* interface ITRiASObjectsCollection */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASObjectsCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("48172D64-AB72-11D1-858D-00600875138A")
    ITRiASObjectsCollection : public ITRiASBase
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_ObjectsCollectionCallback( 
            /* [in] */ ITRiASObjectsCollectionCallback *pICB) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ITRiASObjects **Obj) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE _NewEnum( 
            /* [retval][out] */ IUnknown **ppIEnum) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Name,
            /* [defaultvalue][in] */ BSTR Type,
            /* [retval][out] */ ITRiASObjects **Object) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT Index) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE _Add( 
            /* [in] */ ITRiASObjects *Obj,
            /* [defaultvalue][in] */ VARIANT_BOOL FullAdd = ( VARIANT_BOOL  )0xffff) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE _Clone( 
            /* [retval][out] */ ITRiASObjectsCollection **ObjsColl) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASObjectsCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASObjectsCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASObjectsCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASObjectsCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASObjectsCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASObjectsCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASObjectsCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASObjectsCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            ITRiASObjectsCollection * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Application )( 
            ITRiASObjectsCollection * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            ITRiASObjectsCollection * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Parent )( 
            ITRiASObjectsCollection * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITRiASObjectsCollection * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_ObjectsCollectionCallback )( 
            ITRiASObjectsCollection * This,
            /* [in] */ ITRiASObjectsCollectionCallback *pICB);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            ITRiASObjectsCollection * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ITRiASObjects **Obj);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *_NewEnum )( 
            ITRiASObjectsCollection * This,
            /* [retval][out] */ IUnknown **ppIEnum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ITRiASObjectsCollection * This,
            /* [in] */ BSTR Name,
            /* [defaultvalue][in] */ BSTR Type,
            /* [retval][out] */ ITRiASObjects **Object);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ITRiASObjectsCollection * This,
            /* [in] */ VARIANT Index);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *_Add )( 
            ITRiASObjectsCollection * This,
            /* [in] */ ITRiASObjects *Obj,
            /* [defaultvalue][in] */ VARIANT_BOOL FullAdd);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *_Clone )( 
            ITRiASObjectsCollection * This,
            /* [retval][out] */ ITRiASObjectsCollection **ObjsColl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            ITRiASObjectsCollection * This);
        
        END_INTERFACE
    } ITRiASObjectsCollectionVtbl;

    interface ITRiASObjectsCollection
    {
        CONST_VTBL struct ITRiASObjectsCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASObjectsCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASObjectsCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASObjectsCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASObjectsCollection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASObjectsCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASObjectsCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASObjectsCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASObjectsCollection_get_Application(This,pVal)	\
    (This)->lpVtbl -> get_Application(This,pVal)

#define ITRiASObjectsCollection_put_Application(This,newVal)	\
    (This)->lpVtbl -> put_Application(This,newVal)

#define ITRiASObjectsCollection_get_Parent(This,pVal)	\
    (This)->lpVtbl -> get_Parent(This,pVal)

#define ITRiASObjectsCollection_put_Parent(This,newVal)	\
    (This)->lpVtbl -> put_Parent(This,newVal)


#define ITRiASObjectsCollection_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define ITRiASObjectsCollection_putref_ObjectsCollectionCallback(This,pICB)	\
    (This)->lpVtbl -> putref_ObjectsCollectionCallback(This,pICB)

#define ITRiASObjectsCollection_Item(This,Index,Obj)	\
    (This)->lpVtbl -> Item(This,Index,Obj)

#define ITRiASObjectsCollection__NewEnum(This,ppIEnum)	\
    (This)->lpVtbl -> _NewEnum(This,ppIEnum)

#define ITRiASObjectsCollection_Add(This,Name,Type,Object)	\
    (This)->lpVtbl -> Add(This,Name,Type,Object)

#define ITRiASObjectsCollection_Remove(This,Index)	\
    (This)->lpVtbl -> Remove(This,Index)

#define ITRiASObjectsCollection__Add(This,Obj,FullAdd)	\
    (This)->lpVtbl -> _Add(This,Obj,FullAdd)

#define ITRiASObjectsCollection__Clone(This,ObjsColl)	\
    (This)->lpVtbl -> _Clone(This,ObjsColl)

#define ITRiASObjectsCollection_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsCollection_get_Count_Proxy( 
    ITRiASObjectsCollection * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITRiASObjectsCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsCollection_putref_ObjectsCollectionCallback_Proxy( 
    ITRiASObjectsCollection * This,
    /* [in] */ ITRiASObjectsCollectionCallback *pICB);


void __RPC_STUB ITRiASObjectsCollection_putref_ObjectsCollectionCallback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsCollection_Item_Proxy( 
    ITRiASObjectsCollection * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ ITRiASObjects **Obj);


void __RPC_STUB ITRiASObjectsCollection_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsCollection__NewEnum_Proxy( 
    ITRiASObjectsCollection * This,
    /* [retval][out] */ IUnknown **ppIEnum);


void __RPC_STUB ITRiASObjectsCollection__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsCollection_Add_Proxy( 
    ITRiASObjectsCollection * This,
    /* [in] */ BSTR Name,
    /* [defaultvalue][in] */ BSTR Type,
    /* [retval][out] */ ITRiASObjects **Object);


void __RPC_STUB ITRiASObjectsCollection_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsCollection_Remove_Proxy( 
    ITRiASObjectsCollection * This,
    /* [in] */ VARIANT Index);


void __RPC_STUB ITRiASObjectsCollection_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsCollection__Add_Proxy( 
    ITRiASObjectsCollection * This,
    /* [in] */ ITRiASObjects *Obj,
    /* [defaultvalue][in] */ VARIANT_BOOL FullAdd);


void __RPC_STUB ITRiASObjectsCollection__Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsCollection__Clone_Proxy( 
    ITRiASObjectsCollection * This,
    /* [retval][out] */ ITRiASObjectsCollection **ObjsColl);


void __RPC_STUB ITRiASObjectsCollection__Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsCollection_Refresh_Proxy( 
    ITRiASObjectsCollection * This);


void __RPC_STUB ITRiASObjectsCollection_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASObjectsCollection_INTERFACE_DEFINED__ */


#ifndef __ITRiASObjectsCollectionCallback_INTERFACE_DEFINED__
#define __ITRiASObjectsCollectionCallback_INTERFACE_DEFINED__

/* interface ITRiASObjectsCollectionCallback */
/* [unique][helpstring][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ITRiASObjectsCollectionCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5F20C608-B87C-11D2-95A8-006008447800")
    ITRiASObjectsCollectionCallback : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultType( 
            /* [retval][out] */ BSTR *Type) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnCreate( 
            /* [in] */ VARIANT NameOrHandle,
            /* [in] */ BSTR Type,
            /* [in] */ OBJECTSCOLLECTIONTYPE rgType,
            /* [retval][out] */ ITRiASObjects **Objs) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnDelete( 
            /* [in] */ VARIANT vWhich) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnFinalRelease( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASObjectsCollectionCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASObjectsCollectionCallback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASObjectsCollectionCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASObjectsCollectionCallback * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultType )( 
            ITRiASObjectsCollectionCallback * This,
            /* [retval][out] */ BSTR *Type);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnCreate )( 
            ITRiASObjectsCollectionCallback * This,
            /* [in] */ VARIANT NameOrHandle,
            /* [in] */ BSTR Type,
            /* [in] */ OBJECTSCOLLECTIONTYPE rgType,
            /* [retval][out] */ ITRiASObjects **Objs);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnDelete )( 
            ITRiASObjectsCollectionCallback * This,
            /* [in] */ VARIANT vWhich);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnFinalRelease )( 
            ITRiASObjectsCollectionCallback * This);
        
        END_INTERFACE
    } ITRiASObjectsCollectionCallbackVtbl;

    interface ITRiASObjectsCollectionCallback
    {
        CONST_VTBL struct ITRiASObjectsCollectionCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASObjectsCollectionCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASObjectsCollectionCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASObjectsCollectionCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASObjectsCollectionCallback_get_DefaultType(This,Type)	\
    (This)->lpVtbl -> get_DefaultType(This,Type)

#define ITRiASObjectsCollectionCallback_OnCreate(This,NameOrHandle,Type,rgType,Objs)	\
    (This)->lpVtbl -> OnCreate(This,NameOrHandle,Type,rgType,Objs)

#define ITRiASObjectsCollectionCallback_OnDelete(This,vWhich)	\
    (This)->lpVtbl -> OnDelete(This,vWhich)

#define ITRiASObjectsCollectionCallback_OnFinalRelease(This)	\
    (This)->lpVtbl -> OnFinalRelease(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsCollectionCallback_get_DefaultType_Proxy( 
    ITRiASObjectsCollectionCallback * This,
    /* [retval][out] */ BSTR *Type);


void __RPC_STUB ITRiASObjectsCollectionCallback_get_DefaultType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsCollectionCallback_OnCreate_Proxy( 
    ITRiASObjectsCollectionCallback * This,
    /* [in] */ VARIANT NameOrHandle,
    /* [in] */ BSTR Type,
    /* [in] */ OBJECTSCOLLECTIONTYPE rgType,
    /* [retval][out] */ ITRiASObjects **Objs);


void __RPC_STUB ITRiASObjectsCollectionCallback_OnCreate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsCollectionCallback_OnDelete_Proxy( 
    ITRiASObjectsCollectionCallback * This,
    /* [in] */ VARIANT vWhich);


void __RPC_STUB ITRiASObjectsCollectionCallback_OnDelete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsCollectionCallback_OnFinalRelease_Proxy( 
    ITRiASObjectsCollectionCallback * This);


void __RPC_STUB ITRiASObjectsCollectionCallback_OnFinalRelease_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASObjectsCollectionCallback_INTERFACE_DEFINED__ */


#ifndef __ITRiASFeatures_INTERFACE_DEFINED__
#define __ITRiASFeatures_INTERFACE_DEFINED__

/* interface ITRiASFeatures */
/* [unique][helpstring][dual][uuid][object] */ 

#if !defined(_FEATURETYPE_DEFINED)
#define _FEATURETYPE_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagFEATURETYPE
    {	FEATURETYPE_Object	= 0x61,
	FEATURETYPE_View	= 0x62,
	FEATURETYPE_Ident	= 0x63,
	FEATURETYPE_Unknown	= 0x75,
	FEATURETYPE_TypeMask	= 0xff,
	FEATURETYPE_System	= 0x100,
	FEATURETYPE_AllFeatures	= 0x200,
	FEATURETYPE_ReadOnly	= 0x400,
	FEATURETYPE_Geometry	= 0x800,
	FEATURETYPE_DefinitionOnly	= 0x1000,
	FEATURETYPE_IsGlobal	= 0x4000,
	FEATURETYPE_IsPrimaryFeature	= 0x8000,
	FEATURETYPE_DataTypeMask	= ~0xffff
    } 	FEATURETYPE;

#define DATATYPE_FROM_VT(x)	MAKELONG(0,(x))
#define VT_FROM_DATATYPE(x)	HIWORD(x)
#endif // _FEATURETYPE_DEFINED
#if !defined(_FEATURESTYPE_DEFINED)
#define _FEATURESTYPE_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagFEATURESTYPE
    {	FEATURESTYPE_Unknown	= 0,
	FEATURESTYPE_Attributes	= 1,
	FEATURESTYPE_Geometries	= 2
    } 	FEATURESTYPE;

#endif // _FEATURESTYPE_DEFINED

EXTERN_C const IID IID_ITRiASFeatures;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1CB3AB71-2E87-11D1-969D-00A024D6F582")
    ITRiASFeatures : public ITRiASBase
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_FeaturesCallback( 
            ITRiASFeaturesCallback *pICB) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RelatedObject( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_RelatedObject( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FeaturesType( 
            /* [retval][out] */ FEATURESTYPE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FeaturesType( 
            /* [in] */ FEATURESTYPE newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ITRiASFeature **Feature) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE _NewEnum( 
            /* [retval][out] */ IUnknown **ppIEnum) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ VARIANT NameOrHandle,
            /* [defaultvalue][in] */ BSTR Type,
            /* [defaultvalue][in] */ FEATURETYPE rgType,
            /* [retval][out] */ ITRiASFeature **Feature) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT Index) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE _Add( 
            /* [in] */ ITRiASFeature *Feature,
            /* [defaultvalue][in] */ VARIANT_BOOL FullAdd = ( VARIANT_BOOL  )0xffff) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE _Clone( 
            /* [retval][out] */ ITRiASFeatures **Features) = 0;
        
        virtual /* [restricted][hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEventSink( 
            /* [in] */ IUnknown *Unk,
            /* [out][in] */ DWORD *Cookie,
            /* [in] */ VARIANT_BOOL fAdvise) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RefreshEx( 
            /* [in] */ SETUPFEATURESMODE Mode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASFeaturesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASFeatures * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASFeatures * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASFeatures * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASFeatures * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASFeatures * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASFeatures * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASFeatures * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            ITRiASFeatures * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Application )( 
            ITRiASFeatures * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            ITRiASFeatures * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Parent )( 
            ITRiASFeatures * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITRiASFeatures * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_FeaturesCallback )( 
            ITRiASFeatures * This,
            ITRiASFeaturesCallback *pICB);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RelatedObject )( 
            ITRiASFeatures * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_RelatedObject )( 
            ITRiASFeatures * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FeaturesType )( 
            ITRiASFeatures * This,
            /* [retval][out] */ FEATURESTYPE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FeaturesType )( 
            ITRiASFeatures * This,
            /* [in] */ FEATURESTYPE newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            ITRiASFeatures * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ITRiASFeature **Feature);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *_NewEnum )( 
            ITRiASFeatures * This,
            /* [retval][out] */ IUnknown **ppIEnum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ITRiASFeatures * This,
            /* [in] */ VARIANT NameOrHandle,
            /* [defaultvalue][in] */ BSTR Type,
            /* [defaultvalue][in] */ FEATURETYPE rgType,
            /* [retval][out] */ ITRiASFeature **Feature);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ITRiASFeatures * This,
            /* [in] */ VARIANT Index);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *_Add )( 
            ITRiASFeatures * This,
            /* [in] */ ITRiASFeature *Feature,
            /* [defaultvalue][in] */ VARIANT_BOOL FullAdd);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *_Clone )( 
            ITRiASFeatures * This,
            /* [retval][out] */ ITRiASFeatures **Features);
        
        /* [restricted][hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEventSink )( 
            ITRiASFeatures * This,
            /* [in] */ IUnknown *Unk,
            /* [out][in] */ DWORD *Cookie,
            /* [in] */ VARIANT_BOOL fAdvise);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            ITRiASFeatures * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RefreshEx )( 
            ITRiASFeatures * This,
            /* [in] */ SETUPFEATURESMODE Mode);
        
        END_INTERFACE
    } ITRiASFeaturesVtbl;

    interface ITRiASFeatures
    {
        CONST_VTBL struct ITRiASFeaturesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASFeatures_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASFeatures_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASFeatures_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASFeatures_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASFeatures_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASFeatures_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASFeatures_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASFeatures_get_Application(This,pVal)	\
    (This)->lpVtbl -> get_Application(This,pVal)

#define ITRiASFeatures_put_Application(This,newVal)	\
    (This)->lpVtbl -> put_Application(This,newVal)

#define ITRiASFeatures_get_Parent(This,pVal)	\
    (This)->lpVtbl -> get_Parent(This,pVal)

#define ITRiASFeatures_put_Parent(This,newVal)	\
    (This)->lpVtbl -> put_Parent(This,newVal)


#define ITRiASFeatures_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define ITRiASFeatures_putref_FeaturesCallback(This,pICB)	\
    (This)->lpVtbl -> putref_FeaturesCallback(This,pICB)

#define ITRiASFeatures_get_RelatedObject(This,pVal)	\
    (This)->lpVtbl -> get_RelatedObject(This,pVal)

#define ITRiASFeatures_putref_RelatedObject(This,newVal)	\
    (This)->lpVtbl -> putref_RelatedObject(This,newVal)

#define ITRiASFeatures_get_FeaturesType(This,pVal)	\
    (This)->lpVtbl -> get_FeaturesType(This,pVal)

#define ITRiASFeatures_put_FeaturesType(This,newVal)	\
    (This)->lpVtbl -> put_FeaturesType(This,newVal)

#define ITRiASFeatures_Item(This,Index,Feature)	\
    (This)->lpVtbl -> Item(This,Index,Feature)

#define ITRiASFeatures__NewEnum(This,ppIEnum)	\
    (This)->lpVtbl -> _NewEnum(This,ppIEnum)

#define ITRiASFeatures_Add(This,NameOrHandle,Type,rgType,Feature)	\
    (This)->lpVtbl -> Add(This,NameOrHandle,Type,rgType,Feature)

#define ITRiASFeatures_Remove(This,Index)	\
    (This)->lpVtbl -> Remove(This,Index)

#define ITRiASFeatures__Add(This,Feature,FullAdd)	\
    (This)->lpVtbl -> _Add(This,Feature,FullAdd)

#define ITRiASFeatures__Clone(This,Features)	\
    (This)->lpVtbl -> _Clone(This,Features)

#define ITRiASFeatures_SetEventSink(This,Unk,Cookie,fAdvise)	\
    (This)->lpVtbl -> SetEventSink(This,Unk,Cookie,fAdvise)

#define ITRiASFeatures_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define ITRiASFeatures_RefreshEx(This,Mode)	\
    (This)->lpVtbl -> RefreshEx(This,Mode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASFeatures_get_Count_Proxy( 
    ITRiASFeatures * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITRiASFeatures_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE ITRiASFeatures_putref_FeaturesCallback_Proxy( 
    ITRiASFeatures * This,
    ITRiASFeaturesCallback *pICB);


void __RPC_STUB ITRiASFeatures_putref_FeaturesCallback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASFeatures_get_RelatedObject_Proxy( 
    ITRiASFeatures * This,
    /* [retval][out] */ IDispatch **pVal);


void __RPC_STUB ITRiASFeatures_get_RelatedObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE ITRiASFeatures_putref_RelatedObject_Proxy( 
    ITRiASFeatures * This,
    /* [in] */ IDispatch *newVal);


void __RPC_STUB ITRiASFeatures_putref_RelatedObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASFeatures_get_FeaturesType_Proxy( 
    ITRiASFeatures * This,
    /* [retval][out] */ FEATURESTYPE *pVal);


void __RPC_STUB ITRiASFeatures_get_FeaturesType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASFeatures_put_FeaturesType_Proxy( 
    ITRiASFeatures * This,
    /* [in] */ FEATURESTYPE newVal);


void __RPC_STUB ITRiASFeatures_put_FeaturesType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASFeatures_Item_Proxy( 
    ITRiASFeatures * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ ITRiASFeature **Feature);


void __RPC_STUB ITRiASFeatures_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE ITRiASFeatures__NewEnum_Proxy( 
    ITRiASFeatures * This,
    /* [retval][out] */ IUnknown **ppIEnum);


void __RPC_STUB ITRiASFeatures__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASFeatures_Add_Proxy( 
    ITRiASFeatures * This,
    /* [in] */ VARIANT NameOrHandle,
    /* [defaultvalue][in] */ BSTR Type,
    /* [defaultvalue][in] */ FEATURETYPE rgType,
    /* [retval][out] */ ITRiASFeature **Feature);


void __RPC_STUB ITRiASFeatures_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASFeatures_Remove_Proxy( 
    ITRiASFeatures * This,
    /* [in] */ VARIANT Index);


void __RPC_STUB ITRiASFeatures_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASFeatures__Add_Proxy( 
    ITRiASFeatures * This,
    /* [in] */ ITRiASFeature *Feature,
    /* [defaultvalue][in] */ VARIANT_BOOL FullAdd);


void __RPC_STUB ITRiASFeatures__Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASFeatures__Clone_Proxy( 
    ITRiASFeatures * This,
    /* [retval][out] */ ITRiASFeatures **Features);


void __RPC_STUB ITRiASFeatures__Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASFeatures_SetEventSink_Proxy( 
    ITRiASFeatures * This,
    /* [in] */ IUnknown *Unk,
    /* [out][in] */ DWORD *Cookie,
    /* [in] */ VARIANT_BOOL fAdvise);


void __RPC_STUB ITRiASFeatures_SetEventSink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASFeatures_Refresh_Proxy( 
    ITRiASFeatures * This);


void __RPC_STUB ITRiASFeatures_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASFeatures_RefreshEx_Proxy( 
    ITRiASFeatures * This,
    /* [in] */ SETUPFEATURESMODE Mode);


void __RPC_STUB ITRiASFeatures_RefreshEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASFeatures_INTERFACE_DEFINED__ */


#ifndef __ITRiASFeaturesCallback_INTERFACE_DEFINED__
#define __ITRiASFeaturesCallback_INTERFACE_DEFINED__

/* interface ITRiASFeaturesCallback */
/* [unique][helpstring][oleautomation][uuid][object] */ 

#if !defined(_CHANGEDFEATURES_DEFINED)
#define _CHANGEDFEATURES_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagCHANGEDFEATURES
    {	CHANGEDFEATURES_Name	= 0x1,
	CHANGEDFEATURES_Description	= 0x2,
	CHANGEDFEATURES_Handle	= 0x4
    } 	CHANGEDFEATURES;

#endif // _CHANGEDFEATURES_DEFINED

EXTERN_C const IID IID_ITRiASFeaturesCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EBC2D694-DEC1-11D1-8605-00600875138A")
    ITRiASFeaturesCallback : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultType( 
            /* [retval][out] */ BSTR *Type) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetupFeatures( 
            /* [in] */ IDispatch *Parent,
            /* [defaultvalue][in] */ SETUPFEATURESMODE SetupMode = SETUPFEATURESMODE_Normal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnCreate( 
            /* [in] */ VARIANT NameOrHandle,
            /* [in] */ BSTR Type,
            /* [in] */ FEATURETYPE rgType,
            /* [retval][out] */ ITRiASFeature **Feat) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnChanging( 
            /* [in] */ CHANGEDFEATURES rgWhat,
            /* [in] */ VARIANT NewValue,
            /* [retval][out] */ VARIANT_BOOL *DisAllow) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnChanged( 
            /* [in] */ CHANGEDFEATURES rgWhat,
            /* [in] */ VARIANT OldValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnDelete( 
            /* [in] */ VARIANT vWhich) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnFinalRelease( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASFeaturesCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASFeaturesCallback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASFeaturesCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASFeaturesCallback * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultType )( 
            ITRiASFeaturesCallback * This,
            /* [retval][out] */ BSTR *Type);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetupFeatures )( 
            ITRiASFeaturesCallback * This,
            /* [in] */ IDispatch *Parent,
            /* [defaultvalue][in] */ SETUPFEATURESMODE SetupMode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnCreate )( 
            ITRiASFeaturesCallback * This,
            /* [in] */ VARIANT NameOrHandle,
            /* [in] */ BSTR Type,
            /* [in] */ FEATURETYPE rgType,
            /* [retval][out] */ ITRiASFeature **Feat);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnChanging )( 
            ITRiASFeaturesCallback * This,
            /* [in] */ CHANGEDFEATURES rgWhat,
            /* [in] */ VARIANT NewValue,
            /* [retval][out] */ VARIANT_BOOL *DisAllow);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnChanged )( 
            ITRiASFeaturesCallback * This,
            /* [in] */ CHANGEDFEATURES rgWhat,
            /* [in] */ VARIANT OldValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnDelete )( 
            ITRiASFeaturesCallback * This,
            /* [in] */ VARIANT vWhich);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnFinalRelease )( 
            ITRiASFeaturesCallback * This);
        
        END_INTERFACE
    } ITRiASFeaturesCallbackVtbl;

    interface ITRiASFeaturesCallback
    {
        CONST_VTBL struct ITRiASFeaturesCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASFeaturesCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASFeaturesCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASFeaturesCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASFeaturesCallback_get_DefaultType(This,Type)	\
    (This)->lpVtbl -> get_DefaultType(This,Type)

#define ITRiASFeaturesCallback_SetupFeatures(This,Parent,SetupMode)	\
    (This)->lpVtbl -> SetupFeatures(This,Parent,SetupMode)

#define ITRiASFeaturesCallback_OnCreate(This,NameOrHandle,Type,rgType,Feat)	\
    (This)->lpVtbl -> OnCreate(This,NameOrHandle,Type,rgType,Feat)

#define ITRiASFeaturesCallback_OnChanging(This,rgWhat,NewValue,DisAllow)	\
    (This)->lpVtbl -> OnChanging(This,rgWhat,NewValue,DisAllow)

#define ITRiASFeaturesCallback_OnChanged(This,rgWhat,OldValue)	\
    (This)->lpVtbl -> OnChanged(This,rgWhat,OldValue)

#define ITRiASFeaturesCallback_OnDelete(This,vWhich)	\
    (This)->lpVtbl -> OnDelete(This,vWhich)

#define ITRiASFeaturesCallback_OnFinalRelease(This)	\
    (This)->lpVtbl -> OnFinalRelease(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITRiASFeaturesCallback_get_DefaultType_Proxy( 
    ITRiASFeaturesCallback * This,
    /* [retval][out] */ BSTR *Type);


void __RPC_STUB ITRiASFeaturesCallback_get_DefaultType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASFeaturesCallback_SetupFeatures_Proxy( 
    ITRiASFeaturesCallback * This,
    /* [in] */ IDispatch *Parent,
    /* [defaultvalue][in] */ SETUPFEATURESMODE SetupMode);


void __RPC_STUB ITRiASFeaturesCallback_SetupFeatures_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASFeaturesCallback_OnCreate_Proxy( 
    ITRiASFeaturesCallback * This,
    /* [in] */ VARIANT NameOrHandle,
    /* [in] */ BSTR Type,
    /* [in] */ FEATURETYPE rgType,
    /* [retval][out] */ ITRiASFeature **Feat);


void __RPC_STUB ITRiASFeaturesCallback_OnCreate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASFeaturesCallback_OnChanging_Proxy( 
    ITRiASFeaturesCallback * This,
    /* [in] */ CHANGEDFEATURES rgWhat,
    /* [in] */ VARIANT NewValue,
    /* [retval][out] */ VARIANT_BOOL *DisAllow);


void __RPC_STUB ITRiASFeaturesCallback_OnChanging_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASFeaturesCallback_OnChanged_Proxy( 
    ITRiASFeaturesCallback * This,
    /* [in] */ CHANGEDFEATURES rgWhat,
    /* [in] */ VARIANT OldValue);


void __RPC_STUB ITRiASFeaturesCallback_OnChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASFeaturesCallback_OnDelete_Proxy( 
    ITRiASFeaturesCallback * This,
    /* [in] */ VARIANT vWhich);


void __RPC_STUB ITRiASFeaturesCallback_OnDelete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASFeaturesCallback_OnFinalRelease_Proxy( 
    ITRiASFeaturesCallback * This);


void __RPC_STUB ITRiASFeaturesCallback_OnFinalRelease_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASFeaturesCallback_INTERFACE_DEFINED__ */


#ifndef __ITRiASFeature_INTERFACE_DEFINED__
#define __ITRiASFeature_INTERFACE_DEFINED__

/* interface ITRiASFeature */
/* [unique][helpstring][dual][uuid][object] */ 

#if !defined(_EVALEXPARAM_DEFINED)
#define _EVALEXPARAM_DEFINED

enum _tagEVALEXPARAM
    {	EVALEXPARAM_CoordSysGuid	= 0,
	EVALEXPARAM_Window	= 1,
	EVALEXPARAM_Envelope	= 2
    } ;
#endif // _EVALEXPARAM_DEFINED

EXTERN_C const IID IID_ITRiASFeature;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1CB3AB73-2E87-11D1-969D-00A024D6F582")
    ITRiASFeature : public ITRiASBase
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [restricted][hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Handle( 
            /* [retval][out] */ INT_PTR *pVal) = 0;
        
        virtual /* [restricted][hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Handle( 
            /* [in] */ INT_PTR newVal) = 0;
        
        virtual /* [helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_FeatureCallback( 
            ITRiASFeatureCallback *pICB) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ FEATURETYPE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ FEATURETYPE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Updatable( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Updatable( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Eval( 
            /* [in] */ ITRiASObject *Obj,
            /* [retval][out] */ VARIANT *Val) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EvalEx( 
            /* [in] */ ITRiASObject *Obj,
            /* [out][in] */ SAFEARRAY * *Constraints,
            /* [retval][out] */ VARIANT *Val) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Update( 
            /* [in] */ ITRiASObject *Obj,
            /* [in] */ VARIANT Val) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ITRiASFeature **NewFeat) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Length( 
            /* [in] */ long newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASFeatureVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASFeature * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASFeature * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASFeature * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASFeature * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASFeature * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASFeature * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASFeature * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            ITRiASFeature * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Application )( 
            ITRiASFeature * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            ITRiASFeature * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Parent )( 
            ITRiASFeature * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ITRiASFeature * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            ITRiASFeature * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            ITRiASFeature * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            ITRiASFeature * This,
            /* [in] */ BSTR newVal);
        
        /* [restricted][hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Handle )( 
            ITRiASFeature * This,
            /* [retval][out] */ INT_PTR *pVal);
        
        /* [restricted][hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Handle )( 
            ITRiASFeature * This,
            /* [in] */ INT_PTR newVal);
        
        /* [helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_FeatureCallback )( 
            ITRiASFeature * This,
            ITRiASFeatureCallback *pICB);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            ITRiASFeature * This,
            /* [retval][out] */ FEATURETYPE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Type )( 
            ITRiASFeature * This,
            /* [in] */ FEATURETYPE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Updatable )( 
            ITRiASFeature * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Updatable )( 
            ITRiASFeature * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Eval )( 
            ITRiASFeature * This,
            /* [in] */ ITRiASObject *Obj,
            /* [retval][out] */ VARIANT *Val);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EvalEx )( 
            ITRiASFeature * This,
            /* [in] */ ITRiASObject *Obj,
            /* [out][in] */ SAFEARRAY * *Constraints,
            /* [retval][out] */ VARIANT *Val);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Update )( 
            ITRiASFeature * This,
            /* [in] */ ITRiASObject *Obj,
            /* [in] */ VARIANT Val);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ITRiASFeature * This,
            /* [retval][out] */ ITRiASFeature **NewFeat);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            ITRiASFeature * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Length )( 
            ITRiASFeature * This,
            /* [in] */ long newVal);
        
        END_INTERFACE
    } ITRiASFeatureVtbl;

    interface ITRiASFeature
    {
        CONST_VTBL struct ITRiASFeatureVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASFeature_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASFeature_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASFeature_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASFeature_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASFeature_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASFeature_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASFeature_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASFeature_get_Application(This,pVal)	\
    (This)->lpVtbl -> get_Application(This,pVal)

#define ITRiASFeature_put_Application(This,newVal)	\
    (This)->lpVtbl -> put_Application(This,newVal)

#define ITRiASFeature_get_Parent(This,pVal)	\
    (This)->lpVtbl -> get_Parent(This,pVal)

#define ITRiASFeature_put_Parent(This,newVal)	\
    (This)->lpVtbl -> put_Parent(This,newVal)


#define ITRiASFeature_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define ITRiASFeature_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define ITRiASFeature_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#define ITRiASFeature_put_Description(This,newVal)	\
    (This)->lpVtbl -> put_Description(This,newVal)

#define ITRiASFeature_get_Handle(This,pVal)	\
    (This)->lpVtbl -> get_Handle(This,pVal)

#define ITRiASFeature_put_Handle(This,newVal)	\
    (This)->lpVtbl -> put_Handle(This,newVal)

#define ITRiASFeature_putref_FeatureCallback(This,pICB)	\
    (This)->lpVtbl -> putref_FeatureCallback(This,pICB)

#define ITRiASFeature_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define ITRiASFeature_put_Type(This,newVal)	\
    (This)->lpVtbl -> put_Type(This,newVal)

#define ITRiASFeature_get_Updatable(This,pVal)	\
    (This)->lpVtbl -> get_Updatable(This,pVal)

#define ITRiASFeature_put_Updatable(This,newVal)	\
    (This)->lpVtbl -> put_Updatable(This,newVal)

#define ITRiASFeature_Eval(This,Obj,Val)	\
    (This)->lpVtbl -> Eval(This,Obj,Val)

#define ITRiASFeature_EvalEx(This,Obj,Constraints,Val)	\
    (This)->lpVtbl -> EvalEx(This,Obj,Constraints,Val)

#define ITRiASFeature_Update(This,Obj,Val)	\
    (This)->lpVtbl -> Update(This,Obj,Val)

#define ITRiASFeature_Clone(This,NewFeat)	\
    (This)->lpVtbl -> Clone(This,NewFeat)

#define ITRiASFeature_get_Length(This,pVal)	\
    (This)->lpVtbl -> get_Length(This,pVal)

#define ITRiASFeature_put_Length(This,newVal)	\
    (This)->lpVtbl -> put_Length(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASFeature_get_Name_Proxy( 
    ITRiASFeature * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASFeature_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASFeature_put_Name_Proxy( 
    ITRiASFeature * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITRiASFeature_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASFeature_get_Description_Proxy( 
    ITRiASFeature * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASFeature_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASFeature_put_Description_Proxy( 
    ITRiASFeature * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITRiASFeature_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASFeature_get_Handle_Proxy( 
    ITRiASFeature * This,
    /* [retval][out] */ INT_PTR *pVal);


void __RPC_STUB ITRiASFeature_get_Handle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASFeature_put_Handle_Proxy( 
    ITRiASFeature * This,
    /* [in] */ INT_PTR newVal);


void __RPC_STUB ITRiASFeature_put_Handle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE ITRiASFeature_putref_FeatureCallback_Proxy( 
    ITRiASFeature * This,
    ITRiASFeatureCallback *pICB);


void __RPC_STUB ITRiASFeature_putref_FeatureCallback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASFeature_get_Type_Proxy( 
    ITRiASFeature * This,
    /* [retval][out] */ FEATURETYPE *pVal);


void __RPC_STUB ITRiASFeature_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASFeature_put_Type_Proxy( 
    ITRiASFeature * This,
    /* [in] */ FEATURETYPE newVal);


void __RPC_STUB ITRiASFeature_put_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASFeature_get_Updatable_Proxy( 
    ITRiASFeature * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASFeature_get_Updatable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASFeature_put_Updatable_Proxy( 
    ITRiASFeature * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ITRiASFeature_put_Updatable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASFeature_Eval_Proxy( 
    ITRiASFeature * This,
    /* [in] */ ITRiASObject *Obj,
    /* [retval][out] */ VARIANT *Val);


void __RPC_STUB ITRiASFeature_Eval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASFeature_EvalEx_Proxy( 
    ITRiASFeature * This,
    /* [in] */ ITRiASObject *Obj,
    /* [out][in] */ SAFEARRAY * *Constraints,
    /* [retval][out] */ VARIANT *Val);


void __RPC_STUB ITRiASFeature_EvalEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASFeature_Update_Proxy( 
    ITRiASFeature * This,
    /* [in] */ ITRiASObject *Obj,
    /* [in] */ VARIANT Val);


void __RPC_STUB ITRiASFeature_Update_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASFeature_Clone_Proxy( 
    ITRiASFeature * This,
    /* [retval][out] */ ITRiASFeature **NewFeat);


void __RPC_STUB ITRiASFeature_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASFeature_get_Length_Proxy( 
    ITRiASFeature * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITRiASFeature_get_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASFeature_put_Length_Proxy( 
    ITRiASFeature * This,
    /* [in] */ long newVal);


void __RPC_STUB ITRiASFeature_put_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASFeature_INTERFACE_DEFINED__ */


#ifndef __ITRiASFeatureCallback_INTERFACE_DEFINED__
#define __ITRiASFeatureCallback_INTERFACE_DEFINED__

/* interface ITRiASFeatureCallback */
/* [unique][helpstring][oleautomation][uuid][object] */ 

#if !defined(_SETUPFEATUREMODE_DEFINED)
#define _SETUPFEATUREMODE_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagSETUPFEATUREMODE
    {	SETUPFEATUREMODE_InitOrLoad	= 0,
	SETUPFEATUREMODE_Normal	= 1,
	SETUPFEATUREMODE_Force	= 0x8000
    } 	SETUPFEATUREMODE;

#endif // _SETUPFEATUREMODE_DEFINED
#if !defined(_CHANGEDFEATURE_DEFINED)
#define _CHANGEDFEATURE_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagCHANGEDFEATURE
    {	CHANGEDFEATURE_Name	= 0x1,
	CHANGEDFEATURE_Description	= 0x2,
	CHANGEDFEATURE_Handle	= 0x4,
	CHANGEDFEATURE_Value	= 0x8,
	CHANGEDFEATURE_ROMode	= 0x10,
	CHANGEDFEATURE_Type	= 0x20,
	CHANGEDFEATURE_Length	= 0x40
    } 	CHANGEDFEATURE;

#endif // _CHANGEDFEATURE_DEFINED

EXTERN_C const IID IID_ITRiASFeatureCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EBC2D693-DEC1-11D1-8605-00600875138A")
    ITRiASFeatureCallback : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultType( 
            /* [retval][out] */ BSTR *Type) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetupFeature( 
            /* [defaultvalue][in] */ SETUPFEATUREMODE SetupMode = SETUPFEATUREMODE_Normal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnChanging( 
            /* [in] */ CHANGEDFEATURE rgWhat,
            /* [in] */ VARIANT NewValue,
            /* [retval][out] */ VARIANT_BOOL *DisAllow) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnChanged( 
            /* [in] */ CHANGEDFEATURE rgWhat,
            /* [in] */ VARIANT OldValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Eval( 
            /* [in] */ ITRiASObject *Obj,
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EvalEx( 
            /* [in] */ ITRiASObject *Obj,
            /* [out][in] */ SAFEARRAY * *Constraints,
            /* [retval][out] */ VARIANT *Val) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Update( 
            /* [in] */ ITRiASObject *Obj,
            /* [in] */ VARIANT Val) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ITRiASFeature **NewFeat) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnFinalRelease( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASFeatureCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASFeatureCallback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASFeatureCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASFeatureCallback * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultType )( 
            ITRiASFeatureCallback * This,
            /* [retval][out] */ BSTR *Type);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetupFeature )( 
            ITRiASFeatureCallback * This,
            /* [defaultvalue][in] */ SETUPFEATUREMODE SetupMode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnChanging )( 
            ITRiASFeatureCallback * This,
            /* [in] */ CHANGEDFEATURE rgWhat,
            /* [in] */ VARIANT NewValue,
            /* [retval][out] */ VARIANT_BOOL *DisAllow);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnChanged )( 
            ITRiASFeatureCallback * This,
            /* [in] */ CHANGEDFEATURE rgWhat,
            /* [in] */ VARIANT OldValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Eval )( 
            ITRiASFeatureCallback * This,
            /* [in] */ ITRiASObject *Obj,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EvalEx )( 
            ITRiASFeatureCallback * This,
            /* [in] */ ITRiASObject *Obj,
            /* [out][in] */ SAFEARRAY * *Constraints,
            /* [retval][out] */ VARIANT *Val);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Update )( 
            ITRiASFeatureCallback * This,
            /* [in] */ ITRiASObject *Obj,
            /* [in] */ VARIANT Val);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ITRiASFeatureCallback * This,
            /* [retval][out] */ ITRiASFeature **NewFeat);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnFinalRelease )( 
            ITRiASFeatureCallback * This);
        
        END_INTERFACE
    } ITRiASFeatureCallbackVtbl;

    interface ITRiASFeatureCallback
    {
        CONST_VTBL struct ITRiASFeatureCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASFeatureCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASFeatureCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASFeatureCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASFeatureCallback_get_DefaultType(This,Type)	\
    (This)->lpVtbl -> get_DefaultType(This,Type)

#define ITRiASFeatureCallback_SetupFeature(This,SetupMode)	\
    (This)->lpVtbl -> SetupFeature(This,SetupMode)

#define ITRiASFeatureCallback_OnChanging(This,rgWhat,NewValue,DisAllow)	\
    (This)->lpVtbl -> OnChanging(This,rgWhat,NewValue,DisAllow)

#define ITRiASFeatureCallback_OnChanged(This,rgWhat,OldValue)	\
    (This)->lpVtbl -> OnChanged(This,rgWhat,OldValue)

#define ITRiASFeatureCallback_Eval(This,Obj,pVal)	\
    (This)->lpVtbl -> Eval(This,Obj,pVal)

#define ITRiASFeatureCallback_EvalEx(This,Obj,Constraints,Val)	\
    (This)->lpVtbl -> EvalEx(This,Obj,Constraints,Val)

#define ITRiASFeatureCallback_Update(This,Obj,Val)	\
    (This)->lpVtbl -> Update(This,Obj,Val)

#define ITRiASFeatureCallback_Clone(This,NewFeat)	\
    (This)->lpVtbl -> Clone(This,NewFeat)

#define ITRiASFeatureCallback_OnFinalRelease(This)	\
    (This)->lpVtbl -> OnFinalRelease(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITRiASFeatureCallback_get_DefaultType_Proxy( 
    ITRiASFeatureCallback * This,
    /* [retval][out] */ BSTR *Type);


void __RPC_STUB ITRiASFeatureCallback_get_DefaultType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASFeatureCallback_SetupFeature_Proxy( 
    ITRiASFeatureCallback * This,
    /* [defaultvalue][in] */ SETUPFEATUREMODE SetupMode);


void __RPC_STUB ITRiASFeatureCallback_SetupFeature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASFeatureCallback_OnChanging_Proxy( 
    ITRiASFeatureCallback * This,
    /* [in] */ CHANGEDFEATURE rgWhat,
    /* [in] */ VARIANT NewValue,
    /* [retval][out] */ VARIANT_BOOL *DisAllow);


void __RPC_STUB ITRiASFeatureCallback_OnChanging_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASFeatureCallback_OnChanged_Proxy( 
    ITRiASFeatureCallback * This,
    /* [in] */ CHANGEDFEATURE rgWhat,
    /* [in] */ VARIANT OldValue);


void __RPC_STUB ITRiASFeatureCallback_OnChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASFeatureCallback_Eval_Proxy( 
    ITRiASFeatureCallback * This,
    /* [in] */ ITRiASObject *Obj,
    /* [retval][out] */ VARIANT *pVal);


void __RPC_STUB ITRiASFeatureCallback_Eval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASFeatureCallback_EvalEx_Proxy( 
    ITRiASFeatureCallback * This,
    /* [in] */ ITRiASObject *Obj,
    /* [out][in] */ SAFEARRAY * *Constraints,
    /* [retval][out] */ VARIANT *Val);


void __RPC_STUB ITRiASFeatureCallback_EvalEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASFeatureCallback_Update_Proxy( 
    ITRiASFeatureCallback * This,
    /* [in] */ ITRiASObject *Obj,
    /* [in] */ VARIANT Val);


void __RPC_STUB ITRiASFeatureCallback_Update_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASFeatureCallback_Clone_Proxy( 
    ITRiASFeatureCallback * This,
    /* [retval][out] */ ITRiASFeature **NewFeat);


void __RPC_STUB ITRiASFeatureCallback_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASFeatureCallback_OnFinalRelease_Proxy( 
    ITRiASFeatureCallback * This);


void __RPC_STUB ITRiASFeatureCallback_OnFinalRelease_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASFeatureCallback_INTERFACE_DEFINED__ */


#ifndef __ITRiASSearchObjects_INTERFACE_DEFINED__
#define __ITRiASSearchObjects_INTERFACE_DEFINED__

/* interface ITRiASSearchObjects */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASSearchObjects;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C92461C5-2139-11D2-9E9C-006008447800")
    ITRiASSearchObjects : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConsiderSearch( 
            /* [in] */ BSTR Command,
            /* [in] */ SAFEARRAY * Params) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SearchObjects( 
            /* [in] */ BSTR Command,
            /* [in] */ ITRiASObjects *Objs,
            /* [in] */ SAFEARRAY * Params) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConstraintObjects( 
            /* [in] */ ITRiASObjects *Obj) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASSearchObjectsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASSearchObjects * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASSearchObjects * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASSearchObjects * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASSearchObjects * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASSearchObjects * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASSearchObjects * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASSearchObjects * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ConsiderSearch )( 
            ITRiASSearchObjects * This,
            /* [in] */ BSTR Command,
            /* [in] */ SAFEARRAY * Params);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SearchObjects )( 
            ITRiASSearchObjects * This,
            /* [in] */ BSTR Command,
            /* [in] */ ITRiASObjects *Objs,
            /* [in] */ SAFEARRAY * Params);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ConstraintObjects )( 
            ITRiASSearchObjects * This,
            /* [in] */ ITRiASObjects *Obj);
        
        END_INTERFACE
    } ITRiASSearchObjectsVtbl;

    interface ITRiASSearchObjects
    {
        CONST_VTBL struct ITRiASSearchObjectsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASSearchObjects_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASSearchObjects_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASSearchObjects_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASSearchObjects_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASSearchObjects_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASSearchObjects_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASSearchObjects_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASSearchObjects_ConsiderSearch(This,Command,Params)	\
    (This)->lpVtbl -> ConsiderSearch(This,Command,Params)

#define ITRiASSearchObjects_SearchObjects(This,Command,Objs,Params)	\
    (This)->lpVtbl -> SearchObjects(This,Command,Objs,Params)

#define ITRiASSearchObjects_ConstraintObjects(This,Obj)	\
    (This)->lpVtbl -> ConstraintObjects(This,Obj)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASSearchObjects_ConsiderSearch_Proxy( 
    ITRiASSearchObjects * This,
    /* [in] */ BSTR Command,
    /* [in] */ SAFEARRAY * Params);


void __RPC_STUB ITRiASSearchObjects_ConsiderSearch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASSearchObjects_SearchObjects_Proxy( 
    ITRiASSearchObjects * This,
    /* [in] */ BSTR Command,
    /* [in] */ ITRiASObjects *Objs,
    /* [in] */ SAFEARRAY * Params);


void __RPC_STUB ITRiASSearchObjects_SearchObjects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASSearchObjects_ConstraintObjects_Proxy( 
    ITRiASSearchObjects * This,
    /* [in] */ ITRiASObjects *Obj);


void __RPC_STUB ITRiASSearchObjects_ConstraintObjects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASSearchObjects_INTERFACE_DEFINED__ */


#ifndef __ITRiASRelations_INTERFACE_DEFINED__
#define __ITRiASRelations_INTERFACE_DEFINED__

/* interface ITRiASRelations */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASRelations;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1CB3AB75-2E87-11D1-969D-00A024D6F582")
    ITRiASRelations : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ITRiASRelationsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASRelations * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASRelations * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASRelations * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASRelations * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASRelations * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASRelations * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASRelations * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } ITRiASRelationsVtbl;

    interface ITRiASRelations
    {
        CONST_VTBL struct ITRiASRelationsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASRelations_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASRelations_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASRelations_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASRelations_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASRelations_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASRelations_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASRelations_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITRiASRelations_INTERFACE_DEFINED__ */


#ifndef __ITRiASRelation_INTERFACE_DEFINED__
#define __ITRiASRelation_INTERFACE_DEFINED__

/* interface ITRiASRelation */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASRelation;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1CB3AB77-2E87-11D1-969D-00A024D6F582")
    ITRiASRelation : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ITRiASRelationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASRelation * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASRelation * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASRelation * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASRelation * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASRelation * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASRelation * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASRelation * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } ITRiASRelationVtbl;

    interface ITRiASRelation
    {
        CONST_VTBL struct ITRiASRelationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASRelation_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASRelation_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASRelation_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASRelation_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASRelation_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASRelation_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASRelation_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITRiASRelation_INTERFACE_DEFINED__ */


#ifndef __ITRiASProperties_INTERFACE_DEFINED__
#define __ITRiASProperties_INTERFACE_DEFINED__

/* interface ITRiASProperties */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASProperties;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9A9E8F26-3D7F-11D1-96C0-00A024D6F582")
    ITRiASProperties : public ITRiASBase
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT Which,
            /* [retval][out] */ ITRiASProperty **Property) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE _NewEnum( 
            /* [retval][out] */ IUnknown **ppIEnum) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ VARIANT Which,
            /* [retval][out] */ ITRiASProperty **Property) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT Which) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE _Add( 
            /* [in] */ ITRiASProperty *Prop,
            /* [defaultvalue][in] */ VARIANT_BOOL FullAdd = ( VARIANT_BOOL  )0xffff) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE _Clone( 
            /* [retval][out] */ ITRiASProperties **Props) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [restricted][hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEventSink( 
            /* [in] */ IUnknown *pIUnk,
            /* [in] */ VARIANT_BOOL fAdvise) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASPropertiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASProperties * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASProperties * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASProperties * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASProperties * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASProperties * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASProperties * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASProperties * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            ITRiASProperties * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Application )( 
            ITRiASProperties * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            ITRiASProperties * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][restricted][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Parent )( 
            ITRiASProperties * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITRiASProperties * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            ITRiASProperties * This,
            /* [in] */ VARIANT Which,
            /* [retval][out] */ ITRiASProperty **Property);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *_NewEnum )( 
            ITRiASProperties * This,
            /* [retval][out] */ IUnknown **ppIEnum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ITRiASProperties * This,
            /* [in] */ VARIANT Which,
            /* [retval][out] */ ITRiASProperty **Property);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ITRiASProperties * This,
            /* [in] */ VARIANT Which);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *_Add )( 
            ITRiASProperties * This,
            /* [in] */ ITRiASProperty *Prop,
            /* [defaultvalue][in] */ VARIANT_BOOL FullAdd);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *_Clone )( 
            ITRiASProperties * This,
            /* [retval][out] */ ITRiASProperties **Props);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            ITRiASProperties * This);
        
        /* [restricted][hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEventSink )( 
            ITRiASProperties * This,
            /* [in] */ IUnknown *pIUnk,
            /* [in] */ VARIANT_BOOL fAdvise);
        
        END_INTERFACE
    } ITRiASPropertiesVtbl;

    interface ITRiASProperties
    {
        CONST_VTBL struct ITRiASPropertiesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASProperties_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASProperties_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASProperties_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASProperties_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASProperties_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASProperties_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASProperties_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASProperties_get_Application(This,pVal)	\
    (This)->lpVtbl -> get_Application(This,pVal)

#define ITRiASProperties_put_Application(This,newVal)	\
    (This)->lpVtbl -> put_Application(This,newVal)

#define ITRiASProperties_get_Parent(This,pVal)	\
    (This)->lpVtbl -> get_Parent(This,pVal)

#define ITRiASProperties_put_Parent(This,newVal)	\
    (This)->lpVtbl -> put_Parent(This,newVal)


#define ITRiASProperties_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define ITRiASProperties_Item(This,Which,Property)	\
    (This)->lpVtbl -> Item(This,Which,Property)

#define ITRiASProperties__NewEnum(This,ppIEnum)	\
    (This)->lpVtbl -> _NewEnum(This,ppIEnum)

#define ITRiASProperties_Add(This,Which,Property)	\
    (This)->lpVtbl -> Add(This,Which,Property)

#define ITRiASProperties_Remove(This,Which)	\
    (This)->lpVtbl -> Remove(This,Which)

#define ITRiASProperties__Add(This,Prop,FullAdd)	\
    (This)->lpVtbl -> _Add(This,Prop,FullAdd)

#define ITRiASProperties__Clone(This,Props)	\
    (This)->lpVtbl -> _Clone(This,Props)

#define ITRiASProperties_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define ITRiASProperties_SetEventSink(This,pIUnk,fAdvise)	\
    (This)->lpVtbl -> SetEventSink(This,pIUnk,fAdvise)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASProperties_get_Count_Proxy( 
    ITRiASProperties * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITRiASProperties_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASProperties_Item_Proxy( 
    ITRiASProperties * This,
    /* [in] */ VARIANT Which,
    /* [retval][out] */ ITRiASProperty **Property);


void __RPC_STUB ITRiASProperties_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE ITRiASProperties__NewEnum_Proxy( 
    ITRiASProperties * This,
    /* [retval][out] */ IUnknown **ppIEnum);


void __RPC_STUB ITRiASProperties__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASProperties_Add_Proxy( 
    ITRiASProperties * This,
    /* [in] */ VARIANT Which,
    /* [retval][out] */ ITRiASProperty **Property);


void __RPC_STUB ITRiASProperties_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASProperties_Remove_Proxy( 
    ITRiASProperties * This,
    /* [in] */ VARIANT Which);


void __RPC_STUB ITRiASProperties_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASProperties__Add_Proxy( 
    ITRiASProperties * This,
    /* [in] */ ITRiASProperty *Prop,
    /* [defaultvalue][in] */ VARIANT_BOOL FullAdd);


void __RPC_STUB ITRiASProperties__Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASProperties__Clone_Proxy( 
    ITRiASProperties * This,
    /* [retval][out] */ ITRiASProperties **Props);


void __RPC_STUB ITRiASProperties__Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASProperties_Refresh_Proxy( 
    ITRiASProperties * This);


void __RPC_STUB ITRiASProperties_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASProperties_SetEventSink_Proxy( 
    ITRiASProperties * This,
    /* [in] */ IUnknown *pIUnk,
    /* [in] */ VARIANT_BOOL fAdvise);


void __RPC_STUB ITRiASProperties_SetEventSink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASProperties_INTERFACE_DEFINED__ */


#ifndef __ITRiASProperty_INTERFACE_DEFINED__
#define __ITRiASProperty_INTERFACE_DEFINED__

/* interface ITRiASProperty */
/* [unique][helpstring][dual][uuid][object] */ 

#if !defined(_PROPERTY_TYPE_DEFINED)
#define _PROPERTY_TYPE_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagPROPERTY_TYPE
    {	PROPERTY_TYPE_Normal	= 0,
	PROPERTY_TYPE_System	= 0x1,
	PROPERTY_TYPE_ReadOnly	= 0x2,
	PROPERTY_TYPE_Dynamic	= 0x4,
	PROPERTY_TYPE_NeedsSavingHelp	= 0x8,
	PROPERTY_TYPE_Hidden	= 0x10
    } 	PROPERTY_TYPE;

#endif // _PROPERTY_TYPE_DEFINED

EXTERN_C const IID IID_ITRiASProperty;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9A9E8F24-3D7F-11D1-96C0-00A024D6F582")
    ITRiASProperty : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ PROPERTY_TYPE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ PROPERTY_TYPE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Inherited( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetValueAndType( 
            /* [out][in] */ VARIANT *pVal,
            /* [out][in] */ PROPERTY_TYPE *pType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetValueAndType( 
            /* [in] */ VARIANT Val,
            /* [in] */ PROPERTY_TYPE Type) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASPropertyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASProperty * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASProperty * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASProperty * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASProperty * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASProperty * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASProperty * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASProperty * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            ITRiASProperty * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            ITRiASProperty * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ITRiASProperty * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            ITRiASProperty * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            ITRiASProperty * This,
            /* [retval][out] */ PROPERTY_TYPE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Type )( 
            ITRiASProperty * This,
            /* [in] */ PROPERTY_TYPE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Inherited )( 
            ITRiASProperty * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            ITRiASProperty * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            ITRiASProperty * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetValueAndType )( 
            ITRiASProperty * This,
            /* [out][in] */ VARIANT *pVal,
            /* [out][in] */ PROPERTY_TYPE *pType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetValueAndType )( 
            ITRiASProperty * This,
            /* [in] */ VARIANT Val,
            /* [in] */ PROPERTY_TYPE Type);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            ITRiASProperty * This);
        
        END_INTERFACE
    } ITRiASPropertyVtbl;

    interface ITRiASProperty
    {
        CONST_VTBL struct ITRiASPropertyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASProperty_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASProperty_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASProperty_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASProperty_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASProperty_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASProperty_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASProperty_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASProperty_get_Value(This,pVal)	\
    (This)->lpVtbl -> get_Value(This,pVal)

#define ITRiASProperty_put_Value(This,newVal)	\
    (This)->lpVtbl -> put_Value(This,newVal)

#define ITRiASProperty_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define ITRiASProperty_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define ITRiASProperty_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define ITRiASProperty_put_Type(This,newVal)	\
    (This)->lpVtbl -> put_Type(This,newVal)

#define ITRiASProperty_get_Inherited(This,pVal)	\
    (This)->lpVtbl -> get_Inherited(This,pVal)

#define ITRiASProperty_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#define ITRiASProperty_put_Description(This,newVal)	\
    (This)->lpVtbl -> put_Description(This,newVal)

#define ITRiASProperty_GetValueAndType(This,pVal,pType)	\
    (This)->lpVtbl -> GetValueAndType(This,pVal,pType)

#define ITRiASProperty_SetValueAndType(This,Val,Type)	\
    (This)->lpVtbl -> SetValueAndType(This,Val,Type)

#define ITRiASProperty_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASProperty_get_Value_Proxy( 
    ITRiASProperty * This,
    /* [retval][out] */ VARIANT *pVal);


void __RPC_STUB ITRiASProperty_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASProperty_put_Value_Proxy( 
    ITRiASProperty * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB ITRiASProperty_put_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASProperty_get_Name_Proxy( 
    ITRiASProperty * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASProperty_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASProperty_put_Name_Proxy( 
    ITRiASProperty * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITRiASProperty_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASProperty_get_Type_Proxy( 
    ITRiASProperty * This,
    /* [retval][out] */ PROPERTY_TYPE *pVal);


void __RPC_STUB ITRiASProperty_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASProperty_put_Type_Proxy( 
    ITRiASProperty * This,
    /* [in] */ PROPERTY_TYPE newVal);


void __RPC_STUB ITRiASProperty_put_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASProperty_get_Inherited_Proxy( 
    ITRiASProperty * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASProperty_get_Inherited_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASProperty_get_Description_Proxy( 
    ITRiASProperty * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASProperty_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASProperty_put_Description_Proxy( 
    ITRiASProperty * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITRiASProperty_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASProperty_GetValueAndType_Proxy( 
    ITRiASProperty * This,
    /* [out][in] */ VARIANT *pVal,
    /* [out][in] */ PROPERTY_TYPE *pType);


void __RPC_STUB ITRiASProperty_GetValueAndType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASProperty_SetValueAndType_Proxy( 
    ITRiASProperty * This,
    /* [in] */ VARIANT Val,
    /* [in] */ PROPERTY_TYPE Type);


void __RPC_STUB ITRiASProperty_SetValueAndType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASProperty_Refresh_Proxy( 
    ITRiASProperty * This);


void __RPC_STUB ITRiASProperty_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASProperty_INTERFACE_DEFINED__ */


#ifndef __ITRiASPropertySupport_INTERFACE_DEFINED__
#define __ITRiASPropertySupport_INTERFACE_DEFINED__

/* interface ITRiASPropertySupport */
/* [hidden][restricted][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITRiASPropertySupport;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("25FEBCA5-3DC3-11D1-96C0-00A024D6F582")
    ITRiASPropertySupport : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateProperty( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ ITRiASProperty **Property) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FillWithProperties( 
            /* [out][in] */ IUnknown **Props) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveProperty( 
            /* [in] */ BSTR Name) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASPropertySupportVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASPropertySupport * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASPropertySupport * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASPropertySupport * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateProperty )( 
            ITRiASPropertySupport * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ ITRiASProperty **Property);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FillWithProperties )( 
            ITRiASPropertySupport * This,
            /* [out][in] */ IUnknown **Props);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveProperty )( 
            ITRiASPropertySupport * This,
            /* [in] */ BSTR Name);
        
        END_INTERFACE
    } ITRiASPropertySupportVtbl;

    interface ITRiASPropertySupport
    {
        CONST_VTBL struct ITRiASPropertySupportVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASPropertySupport_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASPropertySupport_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASPropertySupport_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASPropertySupport_CreateProperty(This,Name,Property)	\
    (This)->lpVtbl -> CreateProperty(This,Name,Property)

#define ITRiASPropertySupport_FillWithProperties(This,Props)	\
    (This)->lpVtbl -> FillWithProperties(This,Props)

#define ITRiASPropertySupport_RemoveProperty(This,Name)	\
    (This)->lpVtbl -> RemoveProperty(This,Name)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASPropertySupport_CreateProperty_Proxy( 
    ITRiASPropertySupport * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ ITRiASProperty **Property);


void __RPC_STUB ITRiASPropertySupport_CreateProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASPropertySupport_FillWithProperties_Proxy( 
    ITRiASPropertySupport * This,
    /* [out][in] */ IUnknown **Props);


void __RPC_STUB ITRiASPropertySupport_FillWithProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASPropertySupport_RemoveProperty_Proxy( 
    ITRiASPropertySupport * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASPropertySupport_RemoveProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASPropertySupport_INTERFACE_DEFINED__ */


#ifndef __ITRiASPropertyMapHandler_INTERFACE_DEFINED__
#define __ITRiASPropertyMapHandler_INTERFACE_DEFINED__

/* interface ITRiASPropertyMapHandler */
/* [hidden][restricted][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITRiASPropertyMapHandler;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("32E4EC75-3D14-11D2-9EB6-006008447800")
    ITRiASPropertyMapHandler : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ChangeMapEntry( 
            /* [in] */ BSTR EntryKey,
            /* [in] */ INT_PTR NewData,
            /* [in] */ DWORD NewFlags,
            /* [in] */ VARIANT InitData) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddMapEntry( 
            /* [in] */ BSTR EntryKey,
            /* [in] */ INT_PTR NewData,
            /* [in] */ DWORD NewFlags,
            /* [in] */ VARIANT InitData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASPropertyMapHandlerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASPropertyMapHandler * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASPropertyMapHandler * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASPropertyMapHandler * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ChangeMapEntry )( 
            ITRiASPropertyMapHandler * This,
            /* [in] */ BSTR EntryKey,
            /* [in] */ INT_PTR NewData,
            /* [in] */ DWORD NewFlags,
            /* [in] */ VARIANT InitData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddMapEntry )( 
            ITRiASPropertyMapHandler * This,
            /* [in] */ BSTR EntryKey,
            /* [in] */ INT_PTR NewData,
            /* [in] */ DWORD NewFlags,
            /* [in] */ VARIANT InitData);
        
        END_INTERFACE
    } ITRiASPropertyMapHandlerVtbl;

    interface ITRiASPropertyMapHandler
    {
        CONST_VTBL struct ITRiASPropertyMapHandlerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASPropertyMapHandler_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASPropertyMapHandler_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASPropertyMapHandler_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASPropertyMapHandler_ChangeMapEntry(This,EntryKey,NewData,NewFlags,InitData)	\
    (This)->lpVtbl -> ChangeMapEntry(This,EntryKey,NewData,NewFlags,InitData)

#define ITRiASPropertyMapHandler_AddMapEntry(This,EntryKey,NewData,NewFlags,InitData)	\
    (This)->lpVtbl -> AddMapEntry(This,EntryKey,NewData,NewFlags,InitData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASPropertyMapHandler_ChangeMapEntry_Proxy( 
    ITRiASPropertyMapHandler * This,
    /* [in] */ BSTR EntryKey,
    /* [in] */ INT_PTR NewData,
    /* [in] */ DWORD NewFlags,
    /* [in] */ VARIANT InitData);


void __RPC_STUB ITRiASPropertyMapHandler_ChangeMapEntry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASPropertyMapHandler_AddMapEntry_Proxy( 
    ITRiASPropertyMapHandler * This,
    /* [in] */ BSTR EntryKey,
    /* [in] */ INT_PTR NewData,
    /* [in] */ DWORD NewFlags,
    /* [in] */ VARIANT InitData);


void __RPC_STUB ITRiASPropertyMapHandler_AddMapEntry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASPropertyMapHandler_INTERFACE_DEFINED__ */


#ifndef __ITRiASPropertyCallback_INTERFACE_DEFINED__
#define __ITRiASPropertyCallback_INTERFACE_DEFINED__

/* interface ITRiASPropertyCallback */
/* [hidden][restricted][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITRiASPropertyCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("25FEBCA6-3DC3-11D1-96C0-00A024D6F582")
    ITRiASPropertyCallback : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PutValue( 
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetValue( 
            /* [in] */ BSTR Name,
            /* [out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PutType( 
            /* [in] */ BSTR Name,
            /* [in] */ PROPERTY_TYPE newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetType( 
            /* [in] */ BSTR Name,
            /* [out] */ PROPERTY_TYPE *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PutValueAndType( 
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Val,
            /* [in] */ PROPERTY_TYPE Type) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetValueAndType( 
            /* [in] */ BSTR Name,
            /* [out] */ VARIANT *pVal,
            /* [out] */ PROPERTY_TYPE *pType) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Refresh( 
            /* [in] */ BSTR Name) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASPropertyCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASPropertyCallback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASPropertyCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASPropertyCallback * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PutValue )( 
            ITRiASPropertyCallback * This,
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetValue )( 
            ITRiASPropertyCallback * This,
            /* [in] */ BSTR Name,
            /* [out] */ VARIANT *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PutType )( 
            ITRiASPropertyCallback * This,
            /* [in] */ BSTR Name,
            /* [in] */ PROPERTY_TYPE newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetType )( 
            ITRiASPropertyCallback * This,
            /* [in] */ BSTR Name,
            /* [out] */ PROPERTY_TYPE *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PutValueAndType )( 
            ITRiASPropertyCallback * This,
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Val,
            /* [in] */ PROPERTY_TYPE Type);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetValueAndType )( 
            ITRiASPropertyCallback * This,
            /* [in] */ BSTR Name,
            /* [out] */ VARIANT *pVal,
            /* [out] */ PROPERTY_TYPE *pType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            ITRiASPropertyCallback * This,
            /* [in] */ BSTR Name);
        
        END_INTERFACE
    } ITRiASPropertyCallbackVtbl;

    interface ITRiASPropertyCallback
    {
        CONST_VTBL struct ITRiASPropertyCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASPropertyCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASPropertyCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASPropertyCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASPropertyCallback_PutValue(This,Name,newVal)	\
    (This)->lpVtbl -> PutValue(This,Name,newVal)

#define ITRiASPropertyCallback_GetValue(This,Name,pVal)	\
    (This)->lpVtbl -> GetValue(This,Name,pVal)

#define ITRiASPropertyCallback_PutType(This,Name,newVal)	\
    (This)->lpVtbl -> PutType(This,Name,newVal)

#define ITRiASPropertyCallback_GetType(This,Name,pVal)	\
    (This)->lpVtbl -> GetType(This,Name,pVal)

#define ITRiASPropertyCallback_PutValueAndType(This,Name,Val,Type)	\
    (This)->lpVtbl -> PutValueAndType(This,Name,Val,Type)

#define ITRiASPropertyCallback_GetValueAndType(This,Name,pVal,pType)	\
    (This)->lpVtbl -> GetValueAndType(This,Name,pVal,pType)

#define ITRiASPropertyCallback_Refresh(This,Name)	\
    (This)->lpVtbl -> Refresh(This,Name)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASPropertyCallback_PutValue_Proxy( 
    ITRiASPropertyCallback * This,
    /* [in] */ BSTR Name,
    /* [in] */ VARIANT newVal);


void __RPC_STUB ITRiASPropertyCallback_PutValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASPropertyCallback_GetValue_Proxy( 
    ITRiASPropertyCallback * This,
    /* [in] */ BSTR Name,
    /* [out] */ VARIANT *pVal);


void __RPC_STUB ITRiASPropertyCallback_GetValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASPropertyCallback_PutType_Proxy( 
    ITRiASPropertyCallback * This,
    /* [in] */ BSTR Name,
    /* [in] */ PROPERTY_TYPE newVal);


void __RPC_STUB ITRiASPropertyCallback_PutType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASPropertyCallback_GetType_Proxy( 
    ITRiASPropertyCallback * This,
    /* [in] */ BSTR Name,
    /* [out] */ PROPERTY_TYPE *pVal);


void __RPC_STUB ITRiASPropertyCallback_GetType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASPropertyCallback_PutValueAndType_Proxy( 
    ITRiASPropertyCallback * This,
    /* [in] */ BSTR Name,
    /* [in] */ VARIANT Val,
    /* [in] */ PROPERTY_TYPE Type);


void __RPC_STUB ITRiASPropertyCallback_PutValueAndType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASPropertyCallback_GetValueAndType_Proxy( 
    ITRiASPropertyCallback * This,
    /* [in] */ BSTR Name,
    /* [out] */ VARIANT *pVal,
    /* [out] */ PROPERTY_TYPE *pType);


void __RPC_STUB ITRiASPropertyCallback_GetValueAndType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASPropertyCallback_Refresh_Proxy( 
    ITRiASPropertyCallback * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ITRiASPropertyCallback_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASPropertyCallback_INTERFACE_DEFINED__ */


#ifndef __ITRiASDataServerRegEntries_INTERFACE_DEFINED__
#define __ITRiASDataServerRegEntries_INTERFACE_DEFINED__

/* interface ITRiASDataServerRegEntries */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASDataServerRegEntries;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F4B3F945-810E-11D1-9776-00A024D6F582")
    ITRiASDataServerRegEntries : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ITRiASDataServerRegEntry **Entry) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE _NewEnum( 
            /* [retval][out] */ IUnknown **Enum) = 0;
        
        virtual /* [helpstring][hidden][id] */ HRESULT STDMETHODCALLTYPE _Clone( 
            /* [retval][out] */ ITRiASDataServerRegEntries **Entries) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindFromServerProgID( 
            /* [in] */ BSTR ProgID,
            /* [retval][out] */ ITRiASDataServerRegEntry **Entry) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASDataServerRegEntriesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASDataServerRegEntries * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASDataServerRegEntries * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASDataServerRegEntries * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASDataServerRegEntries * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASDataServerRegEntries * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASDataServerRegEntries * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASDataServerRegEntries * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITRiASDataServerRegEntries * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            ITRiASDataServerRegEntries * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ ITRiASDataServerRegEntry **Entry);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *_NewEnum )( 
            ITRiASDataServerRegEntries * This,
            /* [retval][out] */ IUnknown **Enum);
        
        /* [helpstring][hidden][id] */ HRESULT ( STDMETHODCALLTYPE *_Clone )( 
            ITRiASDataServerRegEntries * This,
            /* [retval][out] */ ITRiASDataServerRegEntries **Entries);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            ITRiASDataServerRegEntries * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FindFromServerProgID )( 
            ITRiASDataServerRegEntries * This,
            /* [in] */ BSTR ProgID,
            /* [retval][out] */ ITRiASDataServerRegEntry **Entry);
        
        END_INTERFACE
    } ITRiASDataServerRegEntriesVtbl;

    interface ITRiASDataServerRegEntries
    {
        CONST_VTBL struct ITRiASDataServerRegEntriesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASDataServerRegEntries_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASDataServerRegEntries_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASDataServerRegEntries_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASDataServerRegEntries_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASDataServerRegEntries_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASDataServerRegEntries_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASDataServerRegEntries_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASDataServerRegEntries_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define ITRiASDataServerRegEntries_Item(This,Index,Entry)	\
    (This)->lpVtbl -> Item(This,Index,Entry)

#define ITRiASDataServerRegEntries__NewEnum(This,Enum)	\
    (This)->lpVtbl -> _NewEnum(This,Enum)

#define ITRiASDataServerRegEntries__Clone(This,Entries)	\
    (This)->lpVtbl -> _Clone(This,Entries)

#define ITRiASDataServerRegEntries_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define ITRiASDataServerRegEntries_FindFromServerProgID(This,ProgID,Entry)	\
    (This)->lpVtbl -> FindFromServerProgID(This,ProgID,Entry)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntries_get_Count_Proxy( 
    ITRiASDataServerRegEntries * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB ITRiASDataServerRegEntries_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntries_Item_Proxy( 
    ITRiASDataServerRegEntries * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ ITRiASDataServerRegEntry **Entry);


void __RPC_STUB ITRiASDataServerRegEntries_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntries__NewEnum_Proxy( 
    ITRiASDataServerRegEntries * This,
    /* [retval][out] */ IUnknown **Enum);


void __RPC_STUB ITRiASDataServerRegEntries__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][hidden][id] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntries__Clone_Proxy( 
    ITRiASDataServerRegEntries * This,
    /* [retval][out] */ ITRiASDataServerRegEntries **Entries);


void __RPC_STUB ITRiASDataServerRegEntries__Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntries_Refresh_Proxy( 
    ITRiASDataServerRegEntries * This);


void __RPC_STUB ITRiASDataServerRegEntries_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntries_FindFromServerProgID_Proxy( 
    ITRiASDataServerRegEntries * This,
    /* [in] */ BSTR ProgID,
    /* [retval][out] */ ITRiASDataServerRegEntry **Entry);


void __RPC_STUB ITRiASDataServerRegEntries_FindFromServerProgID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASDataServerRegEntries_INTERFACE_DEFINED__ */


#ifndef __ITRiASDataServerRegEntry_INTERFACE_DEFINED__
#define __ITRiASDataServerRegEntry_INTERFACE_DEFINED__

/* interface ITRiASDataServerRegEntry */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASDataServerRegEntry;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F4B3F947-810E-11D1-9776-00A024D6F582")
    ITRiASDataServerRegEntry : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DataServerClass( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DatabaseClass( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultExtension( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FilterString( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ShortName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LongName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileDescription( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsReadWrite( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NameIsFile( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NameIsDirectory( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SourceStringUsed( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SourceStringDescription( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TempName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastDirUsed( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LastDirUsed( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ToolboxBitmap32( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MultipleFiles( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OpenWizPages( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NameIsSubStorage( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RestrictInstances( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NeedsCoordSystemExisting( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NeedsCoordSystemNew( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ReconnectDialog( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CreateDatabase( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASDataServerRegEntryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASDataServerRegEntry * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASDataServerRegEntry * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASDataServerRegEntry * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASDataServerRegEntry * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASDataServerRegEntry * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASDataServerRegEntry * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASDataServerRegEntry * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            ITRiASDataServerRegEntry * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DataServerClass )( 
            ITRiASDataServerRegEntry * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DatabaseClass )( 
            ITRiASDataServerRegEntry * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultExtension )( 
            ITRiASDataServerRegEntry * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FilterString )( 
            ITRiASDataServerRegEntry * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ShortName )( 
            ITRiASDataServerRegEntry * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LongName )( 
            ITRiASDataServerRegEntry * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FileDescription )( 
            ITRiASDataServerRegEntry * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsReadWrite )( 
            ITRiASDataServerRegEntry * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NameIsFile )( 
            ITRiASDataServerRegEntry * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NameIsDirectory )( 
            ITRiASDataServerRegEntry * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SourceStringUsed )( 
            ITRiASDataServerRegEntry * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SourceStringDescription )( 
            ITRiASDataServerRegEntry * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TempName )( 
            ITRiASDataServerRegEntry * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LastDirUsed )( 
            ITRiASDataServerRegEntry * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LastDirUsed )( 
            ITRiASDataServerRegEntry * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ToolboxBitmap32 )( 
            ITRiASDataServerRegEntry * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MultipleFiles )( 
            ITRiASDataServerRegEntry * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OpenWizPages )( 
            ITRiASDataServerRegEntry * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NameIsSubStorage )( 
            ITRiASDataServerRegEntry * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RestrictInstances )( 
            ITRiASDataServerRegEntry * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NeedsCoordSystemExisting )( 
            ITRiASDataServerRegEntry * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NeedsCoordSystemNew )( 
            ITRiASDataServerRegEntry * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ReconnectDialog )( 
            ITRiASDataServerRegEntry * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CreateDatabase )( 
            ITRiASDataServerRegEntry * This,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } ITRiASDataServerRegEntryVtbl;

    interface ITRiASDataServerRegEntry
    {
        CONST_VTBL struct ITRiASDataServerRegEntryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASDataServerRegEntry_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASDataServerRegEntry_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASDataServerRegEntry_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASDataServerRegEntry_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASDataServerRegEntry_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASDataServerRegEntry_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASDataServerRegEntry_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASDataServerRegEntry_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define ITRiASDataServerRegEntry_get_DataServerClass(This,pVal)	\
    (This)->lpVtbl -> get_DataServerClass(This,pVal)

#define ITRiASDataServerRegEntry_get_DatabaseClass(This,pVal)	\
    (This)->lpVtbl -> get_DatabaseClass(This,pVal)

#define ITRiASDataServerRegEntry_get_DefaultExtension(This,pVal)	\
    (This)->lpVtbl -> get_DefaultExtension(This,pVal)

#define ITRiASDataServerRegEntry_get_FilterString(This,pVal)	\
    (This)->lpVtbl -> get_FilterString(This,pVal)

#define ITRiASDataServerRegEntry_get_ShortName(This,pVal)	\
    (This)->lpVtbl -> get_ShortName(This,pVal)

#define ITRiASDataServerRegEntry_get_LongName(This,pVal)	\
    (This)->lpVtbl -> get_LongName(This,pVal)

#define ITRiASDataServerRegEntry_get_FileDescription(This,pVal)	\
    (This)->lpVtbl -> get_FileDescription(This,pVal)

#define ITRiASDataServerRegEntry_get_IsReadWrite(This,pVal)	\
    (This)->lpVtbl -> get_IsReadWrite(This,pVal)

#define ITRiASDataServerRegEntry_get_NameIsFile(This,pVal)	\
    (This)->lpVtbl -> get_NameIsFile(This,pVal)

#define ITRiASDataServerRegEntry_get_NameIsDirectory(This,pVal)	\
    (This)->lpVtbl -> get_NameIsDirectory(This,pVal)

#define ITRiASDataServerRegEntry_get_SourceStringUsed(This,pVal)	\
    (This)->lpVtbl -> get_SourceStringUsed(This,pVal)

#define ITRiASDataServerRegEntry_get_SourceStringDescription(This,pVal)	\
    (This)->lpVtbl -> get_SourceStringDescription(This,pVal)

#define ITRiASDataServerRegEntry_get_TempName(This,pVal)	\
    (This)->lpVtbl -> get_TempName(This,pVal)

#define ITRiASDataServerRegEntry_get_LastDirUsed(This,pVal)	\
    (This)->lpVtbl -> get_LastDirUsed(This,pVal)

#define ITRiASDataServerRegEntry_put_LastDirUsed(This,newVal)	\
    (This)->lpVtbl -> put_LastDirUsed(This,newVal)

#define ITRiASDataServerRegEntry_get_ToolboxBitmap32(This,pVal)	\
    (This)->lpVtbl -> get_ToolboxBitmap32(This,pVal)

#define ITRiASDataServerRegEntry_get_MultipleFiles(This,pVal)	\
    (This)->lpVtbl -> get_MultipleFiles(This,pVal)

#define ITRiASDataServerRegEntry_get_OpenWizPages(This,pVal)	\
    (This)->lpVtbl -> get_OpenWizPages(This,pVal)

#define ITRiASDataServerRegEntry_get_NameIsSubStorage(This,pVal)	\
    (This)->lpVtbl -> get_NameIsSubStorage(This,pVal)

#define ITRiASDataServerRegEntry_get_RestrictInstances(This,pVal)	\
    (This)->lpVtbl -> get_RestrictInstances(This,pVal)

#define ITRiASDataServerRegEntry_get_NeedsCoordSystemExisting(This,pVal)	\
    (This)->lpVtbl -> get_NeedsCoordSystemExisting(This,pVal)

#define ITRiASDataServerRegEntry_get_NeedsCoordSystemNew(This,pVal)	\
    (This)->lpVtbl -> get_NeedsCoordSystemNew(This,pVal)

#define ITRiASDataServerRegEntry_get_ReconnectDialog(This,pVal)	\
    (This)->lpVtbl -> get_ReconnectDialog(This,pVal)

#define ITRiASDataServerRegEntry_get_CreateDatabase(This,pVal)	\
    (This)->lpVtbl -> get_CreateDatabase(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntry_get_Version_Proxy( 
    ITRiASDataServerRegEntry * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASDataServerRegEntry_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntry_get_DataServerClass_Proxy( 
    ITRiASDataServerRegEntry * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASDataServerRegEntry_get_DataServerClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntry_get_DatabaseClass_Proxy( 
    ITRiASDataServerRegEntry * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASDataServerRegEntry_get_DatabaseClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntry_get_DefaultExtension_Proxy( 
    ITRiASDataServerRegEntry * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASDataServerRegEntry_get_DefaultExtension_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntry_get_FilterString_Proxy( 
    ITRiASDataServerRegEntry * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASDataServerRegEntry_get_FilterString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntry_get_ShortName_Proxy( 
    ITRiASDataServerRegEntry * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASDataServerRegEntry_get_ShortName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntry_get_LongName_Proxy( 
    ITRiASDataServerRegEntry * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASDataServerRegEntry_get_LongName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntry_get_FileDescription_Proxy( 
    ITRiASDataServerRegEntry * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASDataServerRegEntry_get_FileDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntry_get_IsReadWrite_Proxy( 
    ITRiASDataServerRegEntry * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASDataServerRegEntry_get_IsReadWrite_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntry_get_NameIsFile_Proxy( 
    ITRiASDataServerRegEntry * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASDataServerRegEntry_get_NameIsFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntry_get_NameIsDirectory_Proxy( 
    ITRiASDataServerRegEntry * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASDataServerRegEntry_get_NameIsDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntry_get_SourceStringUsed_Proxy( 
    ITRiASDataServerRegEntry * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASDataServerRegEntry_get_SourceStringUsed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntry_get_SourceStringDescription_Proxy( 
    ITRiASDataServerRegEntry * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASDataServerRegEntry_get_SourceStringDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntry_get_TempName_Proxy( 
    ITRiASDataServerRegEntry * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASDataServerRegEntry_get_TempName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntry_get_LastDirUsed_Proxy( 
    ITRiASDataServerRegEntry * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASDataServerRegEntry_get_LastDirUsed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntry_put_LastDirUsed_Proxy( 
    ITRiASDataServerRegEntry * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITRiASDataServerRegEntry_put_LastDirUsed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntry_get_ToolboxBitmap32_Proxy( 
    ITRiASDataServerRegEntry * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB ITRiASDataServerRegEntry_get_ToolboxBitmap32_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntry_get_MultipleFiles_Proxy( 
    ITRiASDataServerRegEntry * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASDataServerRegEntry_get_MultipleFiles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntry_get_OpenWizPages_Proxy( 
    ITRiASDataServerRegEntry * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASDataServerRegEntry_get_OpenWizPages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntry_get_NameIsSubStorage_Proxy( 
    ITRiASDataServerRegEntry * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASDataServerRegEntry_get_NameIsSubStorage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntry_get_RestrictInstances_Proxy( 
    ITRiASDataServerRegEntry * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITRiASDataServerRegEntry_get_RestrictInstances_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntry_get_NeedsCoordSystemExisting_Proxy( 
    ITRiASDataServerRegEntry * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASDataServerRegEntry_get_NeedsCoordSystemExisting_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntry_get_NeedsCoordSystemNew_Proxy( 
    ITRiASDataServerRegEntry * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB ITRiASDataServerRegEntry_get_NeedsCoordSystemNew_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntry_get_ReconnectDialog_Proxy( 
    ITRiASDataServerRegEntry * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASDataServerRegEntry_get_ReconnectDialog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASDataServerRegEntry_get_CreateDatabase_Proxy( 
    ITRiASDataServerRegEntry * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASDataServerRegEntry_get_CreateDatabase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASDataServerRegEntry_INTERFACE_DEFINED__ */


#ifndef __ITRiASOpenWizardPropExt_INTERFACE_DEFINED__
#define __ITRiASOpenWizardPropExt_INTERFACE_DEFINED__

/* interface ITRiASOpenWizardPropExt */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASOpenWizardPropExt;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4DD970F4-A20F-11D1-BA29-080036D63803")
    ITRiASOpenWizardPropExt : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InitForOpenDialog( 
            /* [in] */ BSTR ProgID,
            /* [in] */ BSTR Caption,
            /* [in] */ VARIANT_BOOL fCreate,
            /* [in] */ IComposeStringPairs *Pairs) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASOpenWizardPropExtVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASOpenWizardPropExt * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASOpenWizardPropExt * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASOpenWizardPropExt * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *InitForOpenDialog )( 
            ITRiASOpenWizardPropExt * This,
            /* [in] */ BSTR ProgID,
            /* [in] */ BSTR Caption,
            /* [in] */ VARIANT_BOOL fCreate,
            /* [in] */ IComposeStringPairs *Pairs);
        
        END_INTERFACE
    } ITRiASOpenWizardPropExtVtbl;

    interface ITRiASOpenWizardPropExt
    {
        CONST_VTBL struct ITRiASOpenWizardPropExtVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASOpenWizardPropExt_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASOpenWizardPropExt_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASOpenWizardPropExt_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASOpenWizardPropExt_InitForOpenDialog(This,ProgID,Caption,fCreate,Pairs)	\
    (This)->lpVtbl -> InitForOpenDialog(This,ProgID,Caption,fCreate,Pairs)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASOpenWizardPropExt_InitForOpenDialog_Proxy( 
    ITRiASOpenWizardPropExt * This,
    /* [in] */ BSTR ProgID,
    /* [in] */ BSTR Caption,
    /* [in] */ VARIANT_BOOL fCreate,
    /* [in] */ IComposeStringPairs *Pairs);


void __RPC_STUB ITRiASOpenWizardPropExt_InitForOpenDialog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASOpenWizardPropExt_INTERFACE_DEFINED__ */


#ifndef __ITRiASObjectHandleMap_INTERFACE_DEFINED__
#define __ITRiASObjectHandleMap_INTERFACE_DEFINED__

/* interface ITRiASObjectHandleMap */
/* [unique][helpstring][dual][uuid][object] */ 

#if !defined(_OBJECTMAPMODE_DEFINED)
#define _OBJECTMAPMODE_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagOBJECTMAPMODE
    {	OBJECTMAPMODE_GetObjectHandle	= 0,
	OBJECTMAPMODE_CreateObjectHandle	= 1,
	OBJECTMAPMODE_GetObjectFromHandle	= 2,
	OBJECTMAPMODE_GetObjectFromNativeHandle	= 3,
	OBJECTMAPMODE_UsePredefinedHandle	= 0x80,
	OBJECTMAPMODE_WeakRegistration	= 0,
	OBJECTMAPMODE_RegistrationKeepsAlive	= 0x100,
	OBJECTMAPMODE_NameIdentifiesObject	= 0,
	OBJECTMAPMODE_NameDoesNotIdentifyObject	= 0x200,
	OBJECTMAPMODE_RegisterNativeHandle	= 0,
	OBJECTMAPMODE_DoNotRegisterNativeHandle	= 0x400,
	OBJECTMAPMODE_RemoveThisReference	= 0,
	OBJECTMAPMODE_RemoveAllReferences	= 2,
	OBJECTMAPMODE_RemoveAllObjects	= 4
    } 	OBJECTMAPMODE;

#endif // _OBJECTMAPMODE_DEFINED

EXTERN_C const IID IID_ITRiASObjectHandleMap;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D4C24AD5-A5EA-11D1-BA31-080036D63803")
    ITRiASObjectHandleMap : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetObjectHandle( 
            /* [in] */ VARIANT NameOrHandle,
            /* [in] */ IUnknown *Object,
            /* [in] */ OBJECTMAPMODE Mode,
            /* [out][in] */ INT_PTR *Handle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetObject( 
            /* [in] */ INT_PTR Handle,
            /* [retval][out] */ IUnknown **Object) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveObject( 
            /* [in] */ INT_PTR Handle,
            /* [defaultvalue][in] */ OBJECTMAPMODE Mode = OBJECTMAPMODE_RemoveThisReference) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShutDown( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetObjectEx( 
            /* [in] */ INT_PTR Handle,
            /* [defaultvalue][in] */ OBJECTMAPMODE Mode,
            /* [retval][out] */ IUnknown **Object) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASObjectHandleMapVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASObjectHandleMap * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASObjectHandleMap * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASObjectHandleMap * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASObjectHandleMap * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASObjectHandleMap * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASObjectHandleMap * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASObjectHandleMap * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetObjectHandle )( 
            ITRiASObjectHandleMap * This,
            /* [in] */ VARIANT NameOrHandle,
            /* [in] */ IUnknown *Object,
            /* [in] */ OBJECTMAPMODE Mode,
            /* [out][in] */ INT_PTR *Handle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetObject )( 
            ITRiASObjectHandleMap * This,
            /* [in] */ INT_PTR Handle,
            /* [retval][out] */ IUnknown **Object);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveObject )( 
            ITRiASObjectHandleMap * This,
            /* [in] */ INT_PTR Handle,
            /* [defaultvalue][in] */ OBJECTMAPMODE Mode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ShutDown )( 
            ITRiASObjectHandleMap * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetObjectEx )( 
            ITRiASObjectHandleMap * This,
            /* [in] */ INT_PTR Handle,
            /* [defaultvalue][in] */ OBJECTMAPMODE Mode,
            /* [retval][out] */ IUnknown **Object);
        
        END_INTERFACE
    } ITRiASObjectHandleMapVtbl;

    interface ITRiASObjectHandleMap
    {
        CONST_VTBL struct ITRiASObjectHandleMapVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASObjectHandleMap_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASObjectHandleMap_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASObjectHandleMap_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASObjectHandleMap_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASObjectHandleMap_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASObjectHandleMap_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASObjectHandleMap_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASObjectHandleMap_GetObjectHandle(This,NameOrHandle,Object,Mode,Handle)	\
    (This)->lpVtbl -> GetObjectHandle(This,NameOrHandle,Object,Mode,Handle)

#define ITRiASObjectHandleMap_GetObject(This,Handle,Object)	\
    (This)->lpVtbl -> GetObject(This,Handle,Object)

#define ITRiASObjectHandleMap_RemoveObject(This,Handle,Mode)	\
    (This)->lpVtbl -> RemoveObject(This,Handle,Mode)

#define ITRiASObjectHandleMap_ShutDown(This)	\
    (This)->lpVtbl -> ShutDown(This)

#define ITRiASObjectHandleMap_GetObjectEx(This,Handle,Mode,Object)	\
    (This)->lpVtbl -> GetObjectEx(This,Handle,Mode,Object)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjectHandleMap_GetObjectHandle_Proxy( 
    ITRiASObjectHandleMap * This,
    /* [in] */ VARIANT NameOrHandle,
    /* [in] */ IUnknown *Object,
    /* [in] */ OBJECTMAPMODE Mode,
    /* [out][in] */ INT_PTR *Handle);


void __RPC_STUB ITRiASObjectHandleMap_GetObjectHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjectHandleMap_GetObject_Proxy( 
    ITRiASObjectHandleMap * This,
    /* [in] */ INT_PTR Handle,
    /* [retval][out] */ IUnknown **Object);


void __RPC_STUB ITRiASObjectHandleMap_GetObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjectHandleMap_RemoveObject_Proxy( 
    ITRiASObjectHandleMap * This,
    /* [in] */ INT_PTR Handle,
    /* [defaultvalue][in] */ OBJECTMAPMODE Mode);


void __RPC_STUB ITRiASObjectHandleMap_RemoveObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjectHandleMap_ShutDown_Proxy( 
    ITRiASObjectHandleMap * This);


void __RPC_STUB ITRiASObjectHandleMap_ShutDown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjectHandleMap_GetObjectEx_Proxy( 
    ITRiASObjectHandleMap * This,
    /* [in] */ INT_PTR Handle,
    /* [defaultvalue][in] */ OBJECTMAPMODE Mode,
    /* [retval][out] */ IUnknown **Object);


void __RPC_STUB ITRiASObjectHandleMap_GetObjectEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASObjectHandleMap_INTERFACE_DEFINED__ */


#ifndef __IObjectWithName_INTERFACE_DEFINED__
#define __IObjectWithName_INTERFACE_DEFINED__

/* interface IObjectWithName */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IObjectWithName;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("70168376-7737-11D2-9EF1-006008447800")
    IObjectWithName : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IObjectWithNameVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IObjectWithName * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IObjectWithName * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IObjectWithName * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IObjectWithName * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IObjectWithName * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IObjectWithNameVtbl;

    interface IObjectWithName
    {
        CONST_VTBL struct IObjectWithNameVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IObjectWithName_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IObjectWithName_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IObjectWithName_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IObjectWithName_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IObjectWithName_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IObjectWithName_get_Name_Proxy( 
    IObjectWithName * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IObjectWithName_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IObjectWithName_put_Name_Proxy( 
    IObjectWithName * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IObjectWithName_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IObjectWithName_INTERFACE_DEFINED__ */


#ifndef __ITRiASObjectsOperations_INTERFACE_DEFINED__
#define __ITRiASObjectsOperations_INTERFACE_DEFINED__

/* interface ITRiASObjectsOperations */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASObjectsOperations;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F45F28D7-7D2F-11D2-9EF6-006008447800")
    ITRiASObjectsOperations : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MakeNewObjects( 
            /* [in] */ IDispatch *Parent,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Type,
            /* [in] */ OBJECTSCOLLECTIONTYPE CollType,
            /* [retval][out] */ ITRiASObjects **ObjsOut) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Union( 
            /* [in] */ ITRiASObjects *Objs1,
            /* [in] */ ITRiASObjects *Objs2,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Type,
            /* [in] */ OBJECTSCOLLECTIONTYPE CollType,
            /* [retval][out] */ ITRiASObjects **ObjsOut) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Intersection( 
            /* [in] */ ITRiASObjects *Obj1,
            /* [in] */ ITRiASObjects *Objs2,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Type,
            /* [in] */ OBJECTSCOLLECTIONTYPE CollType,
            /* [retval][out] */ ITRiASObjects **ObjsOut) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Difference( 
            /* [in] */ ITRiASObjects *Obj1,
            /* [in] */ ITRiASObjects *Objs2,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Type,
            /* [in] */ OBJECTSCOLLECTIONTYPE CollType,
            /* [retval][out] */ ITRiASObjects **ObjsOut) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SymmetricDifference( 
            /* [in] */ ITRiASObjects *Obj1,
            /* [in] */ ITRiASObjects *Objs2,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Type,
            /* [in] */ OBJECTSCOLLECTIONTYPE CollType,
            /* [retval][out] */ ITRiASObjects **ObjsOut) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Includes( 
            /* [in] */ ITRiASObjects *Objs1,
            /* [in] */ ITRiASObjects *Objs2,
            /* [retval][out] */ VARIANT_BOOL *Includes) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASObjectsOperationsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASObjectsOperations * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASObjectsOperations * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASObjectsOperations * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASObjectsOperations * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASObjectsOperations * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASObjectsOperations * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASObjectsOperations * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MakeNewObjects )( 
            ITRiASObjectsOperations * This,
            /* [in] */ IDispatch *Parent,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Type,
            /* [in] */ OBJECTSCOLLECTIONTYPE CollType,
            /* [retval][out] */ ITRiASObjects **ObjsOut);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Union )( 
            ITRiASObjectsOperations * This,
            /* [in] */ ITRiASObjects *Objs1,
            /* [in] */ ITRiASObjects *Objs2,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Type,
            /* [in] */ OBJECTSCOLLECTIONTYPE CollType,
            /* [retval][out] */ ITRiASObjects **ObjsOut);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Intersection )( 
            ITRiASObjectsOperations * This,
            /* [in] */ ITRiASObjects *Obj1,
            /* [in] */ ITRiASObjects *Objs2,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Type,
            /* [in] */ OBJECTSCOLLECTIONTYPE CollType,
            /* [retval][out] */ ITRiASObjects **ObjsOut);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Difference )( 
            ITRiASObjectsOperations * This,
            /* [in] */ ITRiASObjects *Obj1,
            /* [in] */ ITRiASObjects *Objs2,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Type,
            /* [in] */ OBJECTSCOLLECTIONTYPE CollType,
            /* [retval][out] */ ITRiASObjects **ObjsOut);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SymmetricDifference )( 
            ITRiASObjectsOperations * This,
            /* [in] */ ITRiASObjects *Obj1,
            /* [in] */ ITRiASObjects *Objs2,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Type,
            /* [in] */ OBJECTSCOLLECTIONTYPE CollType,
            /* [retval][out] */ ITRiASObjects **ObjsOut);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Includes )( 
            ITRiASObjectsOperations * This,
            /* [in] */ ITRiASObjects *Objs1,
            /* [in] */ ITRiASObjects *Objs2,
            /* [retval][out] */ VARIANT_BOOL *Includes);
        
        END_INTERFACE
    } ITRiASObjectsOperationsVtbl;

    interface ITRiASObjectsOperations
    {
        CONST_VTBL struct ITRiASObjectsOperationsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASObjectsOperations_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASObjectsOperations_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASObjectsOperations_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASObjectsOperations_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASObjectsOperations_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASObjectsOperations_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASObjectsOperations_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASObjectsOperations_MakeNewObjects(This,Parent,Name,Type,CollType,ObjsOut)	\
    (This)->lpVtbl -> MakeNewObjects(This,Parent,Name,Type,CollType,ObjsOut)

#define ITRiASObjectsOperations_Union(This,Objs1,Objs2,Name,Type,CollType,ObjsOut)	\
    (This)->lpVtbl -> Union(This,Objs1,Objs2,Name,Type,CollType,ObjsOut)

#define ITRiASObjectsOperations_Intersection(This,Obj1,Objs2,Name,Type,CollType,ObjsOut)	\
    (This)->lpVtbl -> Intersection(This,Obj1,Objs2,Name,Type,CollType,ObjsOut)

#define ITRiASObjectsOperations_Difference(This,Obj1,Objs2,Name,Type,CollType,ObjsOut)	\
    (This)->lpVtbl -> Difference(This,Obj1,Objs2,Name,Type,CollType,ObjsOut)

#define ITRiASObjectsOperations_SymmetricDifference(This,Obj1,Objs2,Name,Type,CollType,ObjsOut)	\
    (This)->lpVtbl -> SymmetricDifference(This,Obj1,Objs2,Name,Type,CollType,ObjsOut)

#define ITRiASObjectsOperations_Includes(This,Objs1,Objs2,Includes)	\
    (This)->lpVtbl -> Includes(This,Objs1,Objs2,Includes)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsOperations_MakeNewObjects_Proxy( 
    ITRiASObjectsOperations * This,
    /* [in] */ IDispatch *Parent,
    /* [in] */ BSTR Name,
    /* [in] */ BSTR Type,
    /* [in] */ OBJECTSCOLLECTIONTYPE CollType,
    /* [retval][out] */ ITRiASObjects **ObjsOut);


void __RPC_STUB ITRiASObjectsOperations_MakeNewObjects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsOperations_Union_Proxy( 
    ITRiASObjectsOperations * This,
    /* [in] */ ITRiASObjects *Objs1,
    /* [in] */ ITRiASObjects *Objs2,
    /* [in] */ BSTR Name,
    /* [in] */ BSTR Type,
    /* [in] */ OBJECTSCOLLECTIONTYPE CollType,
    /* [retval][out] */ ITRiASObjects **ObjsOut);


void __RPC_STUB ITRiASObjectsOperations_Union_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsOperations_Intersection_Proxy( 
    ITRiASObjectsOperations * This,
    /* [in] */ ITRiASObjects *Obj1,
    /* [in] */ ITRiASObjects *Objs2,
    /* [in] */ BSTR Name,
    /* [in] */ BSTR Type,
    /* [in] */ OBJECTSCOLLECTIONTYPE CollType,
    /* [retval][out] */ ITRiASObjects **ObjsOut);


void __RPC_STUB ITRiASObjectsOperations_Intersection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsOperations_Difference_Proxy( 
    ITRiASObjectsOperations * This,
    /* [in] */ ITRiASObjects *Obj1,
    /* [in] */ ITRiASObjects *Objs2,
    /* [in] */ BSTR Name,
    /* [in] */ BSTR Type,
    /* [in] */ OBJECTSCOLLECTIONTYPE CollType,
    /* [retval][out] */ ITRiASObjects **ObjsOut);


void __RPC_STUB ITRiASObjectsOperations_Difference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsOperations_SymmetricDifference_Proxy( 
    ITRiASObjectsOperations * This,
    /* [in] */ ITRiASObjects *Obj1,
    /* [in] */ ITRiASObjects *Objs2,
    /* [in] */ BSTR Name,
    /* [in] */ BSTR Type,
    /* [in] */ OBJECTSCOLLECTIONTYPE CollType,
    /* [retval][out] */ ITRiASObjects **ObjsOut);


void __RPC_STUB ITRiASObjectsOperations_SymmetricDifference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASObjectsOperations_Includes_Proxy( 
    ITRiASObjectsOperations * This,
    /* [in] */ ITRiASObjects *Objs1,
    /* [in] */ ITRiASObjects *Objs2,
    /* [retval][out] */ VARIANT_BOOL *Includes);


void __RPC_STUB ITRiASObjectsOperations_Includes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASObjectsOperations_INTERFACE_DEFINED__ */


#ifndef __ITRiASHandle_INTERFACE_DEFINED__
#define __ITRiASHandle_INTERFACE_DEFINED__

/* interface ITRiASHandle */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITRiASHandle;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9D793C97-B60C-11D2-95A8-006008447800")
    ITRiASHandle : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetHandle( 
            /* [retval][out] */ INT_PTR *Handle) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PutHandle( 
            /* [in] */ INT_PTR Handle) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASHandleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASHandle * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASHandle * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASHandle * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetHandle )( 
            ITRiASHandle * This,
            /* [retval][out] */ INT_PTR *Handle);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PutHandle )( 
            ITRiASHandle * This,
            /* [in] */ INT_PTR Handle);
        
        END_INTERFACE
    } ITRiASHandleVtbl;

    interface ITRiASHandle
    {
        CONST_VTBL struct ITRiASHandleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASHandle_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASHandle_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASHandle_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASHandle_GetHandle(This,Handle)	\
    (This)->lpVtbl -> GetHandle(This,Handle)

#define ITRiASHandle_PutHandle(This,Handle)	\
    (This)->lpVtbl -> PutHandle(This,Handle)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASHandle_GetHandle_Proxy( 
    ITRiASHandle * This,
    /* [retval][out] */ INT_PTR *Handle);


void __RPC_STUB ITRiASHandle_GetHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITRiASHandle_PutHandle_Proxy( 
    ITRiASHandle * This,
    /* [in] */ INT_PTR Handle);


void __RPC_STUB ITRiASHandle_PutHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASHandle_INTERFACE_DEFINED__ */


#ifndef __ITRiASQueryVisInfo_INTERFACE_DEFINED__
#define __ITRiASQueryVisInfo_INTERFACE_DEFINED__

/* interface ITRiASQueryVisInfo */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ITRiASQueryVisInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("83650330-3389-11D3-94F9-0080C786297B")
    ITRiASQueryVisInfo : public IUnknown
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VisInfo( 
            /* [defaultvalue][in] */ OBJECTTYPE Type,
            /* [retval][out] */ DVisInfo **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASQueryVisInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASQueryVisInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASQueryVisInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASQueryVisInfo * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VisInfo )( 
            ITRiASQueryVisInfo * This,
            /* [defaultvalue][in] */ OBJECTTYPE Type,
            /* [retval][out] */ DVisInfo **pVal);
        
        END_INTERFACE
    } ITRiASQueryVisInfoVtbl;

    interface ITRiASQueryVisInfo
    {
        CONST_VTBL struct ITRiASQueryVisInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASQueryVisInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASQueryVisInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASQueryVisInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASQueryVisInfo_get_VisInfo(This,Type,pVal)	\
    (This)->lpVtbl -> get_VisInfo(This,Type,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASQueryVisInfo_get_VisInfo_Proxy( 
    ITRiASQueryVisInfo * This,
    /* [defaultvalue][in] */ OBJECTTYPE Type,
    /* [retval][out] */ DVisInfo **pVal);


void __RPC_STUB ITRiASQueryVisInfo_get_VisInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASQueryVisInfo_INTERFACE_DEFINED__ */


#ifndef __IReconnectDialog_INTERFACE_DEFINED__
#define __IReconnectDialog_INTERFACE_DEFINED__

/* interface IReconnectDialog */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IReconnectDialog;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("96EE4262-A649-40E6-A51E-6F51C13E0D03")
    IReconnectDialog : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetReconnectParams( 
            /* [in] */ INT_PTR hWnd,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Desc,
            /* [in] */ BSTR ConnectString,
            /* [in] */ BSTR bstrPath,
            /* [out][in] */ BSTR *NewName,
            /* [out][in] */ BSTR *NewConnectString,
            /* [out][in] */ BSTR *NewPath) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IReconnectDialogVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IReconnectDialog * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IReconnectDialog * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IReconnectDialog * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetReconnectParams )( 
            IReconnectDialog * This,
            /* [in] */ INT_PTR hWnd,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Desc,
            /* [in] */ BSTR ConnectString,
            /* [in] */ BSTR bstrPath,
            /* [out][in] */ BSTR *NewName,
            /* [out][in] */ BSTR *NewConnectString,
            /* [out][in] */ BSTR *NewPath);
        
        END_INTERFACE
    } IReconnectDialogVtbl;

    interface IReconnectDialog
    {
        CONST_VTBL struct IReconnectDialogVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IReconnectDialog_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IReconnectDialog_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IReconnectDialog_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IReconnectDialog_GetReconnectParams(This,hWnd,Name,Desc,ConnectString,bstrPath,NewName,NewConnectString,NewPath)	\
    (This)->lpVtbl -> GetReconnectParams(This,hWnd,Name,Desc,ConnectString,bstrPath,NewName,NewConnectString,NewPath)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IReconnectDialog_GetReconnectParams_Proxy( 
    IReconnectDialog * This,
    /* [in] */ INT_PTR hWnd,
    /* [in] */ BSTR Name,
    /* [in] */ BSTR Desc,
    /* [in] */ BSTR ConnectString,
    /* [in] */ BSTR bstrPath,
    /* [out][in] */ BSTR *NewName,
    /* [out][in] */ BSTR *NewConnectString,
    /* [out][in] */ BSTR *NewPath);


void __RPC_STUB IReconnectDialog_GetReconnectParams_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IReconnectDialog_INTERFACE_DEFINED__ */


#ifndef __ICreateDatabase_INTERFACE_DEFINED__
#define __ICreateDatabase_INTERFACE_DEFINED__

/* interface ICreateDatabase */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ICreateDatabase;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AC060987-CE9F-45A4-9E5F-0184B0A4CA24")
    ICreateDatabase : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateDatabase( 
            /* [in] */ BSTR name,
            /* [in] */ BSTR Locale,
            /* [in] */ BSTR Source) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICreateDatabaseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICreateDatabase * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICreateDatabase * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICreateDatabase * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateDatabase )( 
            ICreateDatabase * This,
            /* [in] */ BSTR name,
            /* [in] */ BSTR Locale,
            /* [in] */ BSTR Source);
        
        END_INTERFACE
    } ICreateDatabaseVtbl;

    interface ICreateDatabase
    {
        CONST_VTBL struct ICreateDatabaseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICreateDatabase_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICreateDatabase_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICreateDatabase_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICreateDatabase_CreateDatabase(This,name,Locale,Source)	\
    (This)->lpVtbl -> CreateDatabase(This,name,Locale,Source)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICreateDatabase_CreateDatabase_Proxy( 
    ICreateDatabase * This,
    /* [in] */ BSTR name,
    /* [in] */ BSTR Locale,
    /* [in] */ BSTR Source);


void __RPC_STUB ICreateDatabase_CreateDatabase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICreateDatabase_INTERFACE_DEFINED__ */


#ifndef __ITRiASConnectionFilter_INTERFACE_DEFINED__
#define __ITRiASConnectionFilter_INTERFACE_DEFINED__

/* interface ITRiASConnectionFilter */
/* [unique][helpstring][dual][uuid][object] */ 

#if !defined(_CONNECTIONFILTERTYPE_DEFINED)
#define _CONNECTIONFILTERTYPE_DEFINED
typedef /* [helpstring][v1_enum][public] */ 
enum _tagCONNECTIONFILTERTYPE
    {	CONNECTIONFILTERTYPE_Unknown	= 0,
	CONNECTIONFILTERTYPE_Rectangle_OverlappedContainers	= 0x1,
	CONNECTIONFILTERTYPE_Rectangle_ContainedContainers	= 0x2,
	CONNECTIONFILTERTYPE_Rectangle_OverlappedPoints	= 0x3,
	CONNECTIONFILTERTYPE_Rectangle_ContainedPoints	= 0x4,
	CONNECTIONFILTERTYPE_Rectangle_OverlappedObjects	= 0x5,
	CONNECTIONFILTERTYPE_Rectangle_ContainedObjects	= 0x6,
	CONNECTIONFILTERTYPE_Polygon_OverlappedContainers	= 0x11,
	CONNECTIONFILTERTYPE_Polygon_ContainedContainers	= 0x12,
	CONNECTIONFILTERTYPE_Polygon_OverlappedPoints	= 0x13,
	CONNECTIONFILTERTYPE_Polygon_ContainedPoints	= 0x14,
	CONNECTIONFILTERTYPE_Polygon_OverlappedObjects	= 0x15,
	CONNECTIONFILTERTYPE_Polygon_ContainedObjects	= 0x16
    } 	CONNECTIONFILTERTYPE;

#endif // _CONNECTIONFILTERTYPE_DEFINED

EXTERN_C const IID IID_ITRiASConnectionFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2878DC6F-0786-4643-8D89-3672898B8DDB")
    ITRiASConnectionFilter : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Geometry( 
            /* [retval][out] */ IDispatch **Geometry) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Geometry( 
            /* [in] */ IDispatch *Geometry) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ CONNECTIONFILTERTYPE *prgType) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ CONNECTIONFILTERTYPE rgType) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASConnectionFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASConnectionFilter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASConnectionFilter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASConnectionFilter * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASConnectionFilter * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASConnectionFilter * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASConnectionFilter * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASConnectionFilter * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ITRiASConnectionFilter * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            ITRiASConnectionFilter * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Geometry )( 
            ITRiASConnectionFilter * This,
            /* [retval][out] */ IDispatch **Geometry);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Geometry )( 
            ITRiASConnectionFilter * This,
            /* [in] */ IDispatch *Geometry);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            ITRiASConnectionFilter * This,
            /* [retval][out] */ CONNECTIONFILTERTYPE *prgType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Type )( 
            ITRiASConnectionFilter * This,
            /* [in] */ CONNECTIONFILTERTYPE rgType);
        
        END_INTERFACE
    } ITRiASConnectionFilterVtbl;

    interface ITRiASConnectionFilter
    {
        CONST_VTBL struct ITRiASConnectionFilterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASConnectionFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASConnectionFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASConnectionFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASConnectionFilter_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASConnectionFilter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASConnectionFilter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASConnectionFilter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASConnectionFilter_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define ITRiASConnectionFilter_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define ITRiASConnectionFilter_get_Geometry(This,Geometry)	\
    (This)->lpVtbl -> get_Geometry(This,Geometry)

#define ITRiASConnectionFilter_put_Geometry(This,Geometry)	\
    (This)->lpVtbl -> put_Geometry(This,Geometry)

#define ITRiASConnectionFilter_get_Type(This,prgType)	\
    (This)->lpVtbl -> get_Type(This,prgType)

#define ITRiASConnectionFilter_put_Type(This,rgType)	\
    (This)->lpVtbl -> put_Type(This,rgType)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASConnectionFilter_get_Name_Proxy( 
    ITRiASConnectionFilter * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASConnectionFilter_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASConnectionFilter_put_Name_Proxy( 
    ITRiASConnectionFilter * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITRiASConnectionFilter_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASConnectionFilter_get_Geometry_Proxy( 
    ITRiASConnectionFilter * This,
    /* [retval][out] */ IDispatch **Geometry);


void __RPC_STUB ITRiASConnectionFilter_get_Geometry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASConnectionFilter_put_Geometry_Proxy( 
    ITRiASConnectionFilter * This,
    /* [in] */ IDispatch *Geometry);


void __RPC_STUB ITRiASConnectionFilter_put_Geometry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASConnectionFilter_get_Type_Proxy( 
    ITRiASConnectionFilter * This,
    /* [retval][out] */ CONNECTIONFILTERTYPE *prgType);


void __RPC_STUB ITRiASConnectionFilter_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASConnectionFilter_put_Type_Proxy( 
    ITRiASConnectionFilter * This,
    /* [in] */ CONNECTIONFILTERTYPE rgType);


void __RPC_STUB ITRiASConnectionFilter_put_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASConnectionFilter_INTERFACE_DEFINED__ */


#ifndef __ITRiASConnectionFilters_INTERFACE_DEFINED__
#define __ITRiASConnectionFilters_INTERFACE_DEFINED__

/* interface ITRiASConnectionFilters */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASConnectionFilters;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FC0EEE23-5A65-4131-AA9E-D231A97C5A9A")
    ITRiASConnectionFilters : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ ITRiASConnectionFilter **Filter) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASConnectionFiltersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASConnectionFilters * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASConnectionFilters * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASConnectionFilters * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASConnectionFilters * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASConnectionFilters * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASConnectionFilters * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASConnectionFilters * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ITRiASConnectionFilters * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ ITRiASConnectionFilter **Filter);
        
        END_INTERFACE
    } ITRiASConnectionFiltersVtbl;

    interface ITRiASConnectionFilters
    {
        CONST_VTBL struct ITRiASConnectionFiltersVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASConnectionFilters_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASConnectionFilters_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASConnectionFilters_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASConnectionFilters_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASConnectionFilters_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASConnectionFilters_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASConnectionFilters_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASConnectionFilters_Add(This,Name,Filter)	\
    (This)->lpVtbl -> Add(This,Name,Filter)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASConnectionFilters_Add_Proxy( 
    ITRiASConnectionFilters * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ ITRiASConnectionFilter **Filter);


void __RPC_STUB ITRiASConnectionFilters_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASConnectionFilters_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_TRiASDB_0330 */
/* [local] */ 

#pragma once










extern RPC_IF_HANDLE __MIDL_itf_TRiASDB_0330_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_TRiASDB_0330_v0_0_s_ifspec;

#ifndef __ITRiASMainDBEngine_INTERFACE_DEFINED__
#define __ITRiASMainDBEngine_INTERFACE_DEFINED__

/* interface ITRiASMainDBEngine */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASMainDBEngine;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1CB3AB7D-2E87-11D1-969D-00A024D6F582")
    ITRiASMainDBEngine : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Projects( 
            /* [retval][out] */ ITRiASProjects **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ActiveProject( 
            /* [retval][out] */ ITRiASProject **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProjectToOpen( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenProject( 
            /* [in] */ BSTR Name,
            /* [defaultvalue][in] */ OPENMODE Mode,
            /* [retval][out] */ ITRiASProject **Project) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateProject( 
            /* [defaultvalue][in] */ BSTR Name,
            /* [defaultvalue][in] */ OPENMODE Mode,
            /* [retval][out] */ ITRiASProject **Project) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenProjectStg( 
            /* [in] */ IUnknown *Stg,
            /* [in] */ BSTR bstrName,
            /* [defaultvalue][in] */ OPENMODE Mode,
            /* [retval][out] */ ITRiASProject **Project) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateProjectStg( 
            /* [in] */ IUnknown *Stg,
            /* [in] */ BSTR bstrName,
            /* [defaultvalue][in] */ OPENMODE Mode,
            /* [retval][out] */ ITRiASProject **Project) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASMainDBEngineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASMainDBEngine * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASMainDBEngine * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASMainDBEngine * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASMainDBEngine * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASMainDBEngine * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASMainDBEngine * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASMainDBEngine * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Projects )( 
            ITRiASMainDBEngine * This,
            /* [retval][out] */ ITRiASProjects **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ActiveProject )( 
            ITRiASMainDBEngine * This,
            /* [retval][out] */ ITRiASProject **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProjectToOpen )( 
            ITRiASMainDBEngine * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OpenProject )( 
            ITRiASMainDBEngine * This,
            /* [in] */ BSTR Name,
            /* [defaultvalue][in] */ OPENMODE Mode,
            /* [retval][out] */ ITRiASProject **Project);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateProject )( 
            ITRiASMainDBEngine * This,
            /* [defaultvalue][in] */ BSTR Name,
            /* [defaultvalue][in] */ OPENMODE Mode,
            /* [retval][out] */ ITRiASProject **Project);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OpenProjectStg )( 
            ITRiASMainDBEngine * This,
            /* [in] */ IUnknown *Stg,
            /* [in] */ BSTR bstrName,
            /* [defaultvalue][in] */ OPENMODE Mode,
            /* [retval][out] */ ITRiASProject **Project);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateProjectStg )( 
            ITRiASMainDBEngine * This,
            /* [in] */ IUnknown *Stg,
            /* [in] */ BSTR bstrName,
            /* [defaultvalue][in] */ OPENMODE Mode,
            /* [retval][out] */ ITRiASProject **Project);
        
        END_INTERFACE
    } ITRiASMainDBEngineVtbl;

    interface ITRiASMainDBEngine
    {
        CONST_VTBL struct ITRiASMainDBEngineVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASMainDBEngine_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASMainDBEngine_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASMainDBEngine_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASMainDBEngine_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASMainDBEngine_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASMainDBEngine_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASMainDBEngine_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASMainDBEngine_get_Projects(This,pVal)	\
    (This)->lpVtbl -> get_Projects(This,pVal)

#define ITRiASMainDBEngine_get_ActiveProject(This,pVal)	\
    (This)->lpVtbl -> get_ActiveProject(This,pVal)

#define ITRiASMainDBEngine_get_ProjectToOpen(This,pVal)	\
    (This)->lpVtbl -> get_ProjectToOpen(This,pVal)

#define ITRiASMainDBEngine_OpenProject(This,Name,Mode,Project)	\
    (This)->lpVtbl -> OpenProject(This,Name,Mode,Project)

#define ITRiASMainDBEngine_CreateProject(This,Name,Mode,Project)	\
    (This)->lpVtbl -> CreateProject(This,Name,Mode,Project)

#define ITRiASMainDBEngine_OpenProjectStg(This,Stg,bstrName,Mode,Project)	\
    (This)->lpVtbl -> OpenProjectStg(This,Stg,bstrName,Mode,Project)

#define ITRiASMainDBEngine_CreateProjectStg(This,Stg,bstrName,Mode,Project)	\
    (This)->lpVtbl -> CreateProjectStg(This,Stg,bstrName,Mode,Project)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASMainDBEngine_get_Projects_Proxy( 
    ITRiASMainDBEngine * This,
    /* [retval][out] */ ITRiASProjects **pVal);


void __RPC_STUB ITRiASMainDBEngine_get_Projects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASMainDBEngine_get_ActiveProject_Proxy( 
    ITRiASMainDBEngine * This,
    /* [retval][out] */ ITRiASProject **pVal);


void __RPC_STUB ITRiASMainDBEngine_get_ActiveProject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASMainDBEngine_get_ProjectToOpen_Proxy( 
    ITRiASMainDBEngine * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITRiASMainDBEngine_get_ProjectToOpen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASMainDBEngine_OpenProject_Proxy( 
    ITRiASMainDBEngine * This,
    /* [in] */ BSTR Name,
    /* [defaultvalue][in] */ OPENMODE Mode,
    /* [retval][out] */ ITRiASProject **Project);


void __RPC_STUB ITRiASMainDBEngine_OpenProject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASMainDBEngine_CreateProject_Proxy( 
    ITRiASMainDBEngine * This,
    /* [defaultvalue][in] */ BSTR Name,
    /* [defaultvalue][in] */ OPENMODE Mode,
    /* [retval][out] */ ITRiASProject **Project);


void __RPC_STUB ITRiASMainDBEngine_CreateProject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASMainDBEngine_OpenProjectStg_Proxy( 
    ITRiASMainDBEngine * This,
    /* [in] */ IUnknown *Stg,
    /* [in] */ BSTR bstrName,
    /* [defaultvalue][in] */ OPENMODE Mode,
    /* [retval][out] */ ITRiASProject **Project);


void __RPC_STUB ITRiASMainDBEngine_OpenProjectStg_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASMainDBEngine_CreateProjectStg_Proxy( 
    ITRiASMainDBEngine * This,
    /* [in] */ IUnknown *Stg,
    /* [in] */ BSTR bstrName,
    /* [defaultvalue][in] */ OPENMODE Mode,
    /* [retval][out] */ ITRiASProject **Project);


void __RPC_STUB ITRiASMainDBEngine_CreateProjectStg_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASMainDBEngine_INTERFACE_DEFINED__ */


#ifndef __ITRiASSimpleDBEngine_INTERFACE_DEFINED__
#define __ITRiASSimpleDBEngine_INTERFACE_DEFINED__

/* interface ITRiASSimpleDBEngine */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASSimpleDBEngine;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1724BC8F-E51D-11D2-9BD8-E6AA20524153")
    ITRiASSimpleDBEngine : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ITRiASSimpleDBEngineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASSimpleDBEngine * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASSimpleDBEngine * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASSimpleDBEngine * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASSimpleDBEngine * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASSimpleDBEngine * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASSimpleDBEngine * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASSimpleDBEngine * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } ITRiASSimpleDBEngineVtbl;

    interface ITRiASSimpleDBEngine
    {
        CONST_VTBL struct ITRiASSimpleDBEngineVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASSimpleDBEngine_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASSimpleDBEngine_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASSimpleDBEngine_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASSimpleDBEngine_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASSimpleDBEngine_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASSimpleDBEngine_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASSimpleDBEngine_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITRiASSimpleDBEngine_INTERFACE_DEFINED__ */


#ifndef __ITRiASSimpleObject_INTERFACE_DEFINED__
#define __ITRiASSimpleObject_INTERFACE_DEFINED__

/* interface ITRiASSimpleObject */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASSimpleObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("90378E23-C54C-11D1-85D2-00600875138A")
    ITRiASSimpleObject : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LocalHandle( 
            /* [retval][out] */ INT_PTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitTarget( 
            /* [in] */ INT_PTR lONr,
            /* [in] */ OBJECTTYPE ObjType,
            /* [in] */ INT_PTR lIdent,
            /* [in] */ INT_PTR hObjs,
            /* [out][in] */ INT_PTR *phObj) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RelatedObject( 
            /* [retval][out] */ ITRiASObject **Obj) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RelatedObject( 
            /* [in] */ ITRiASObject *Obj) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASSimpleObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASSimpleObject * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASSimpleObject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASSimpleObject * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASSimpleObject * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASSimpleObject * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASSimpleObject * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASSimpleObject * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LocalHandle )( 
            ITRiASSimpleObject * This,
            /* [retval][out] */ INT_PTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InitTarget )( 
            ITRiASSimpleObject * This,
            /* [in] */ INT_PTR lONr,
            /* [in] */ OBJECTTYPE ObjType,
            /* [in] */ INT_PTR lIdent,
            /* [in] */ INT_PTR hObjs,
            /* [out][in] */ INT_PTR *phObj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RelatedObject )( 
            ITRiASSimpleObject * This,
            /* [retval][out] */ ITRiASObject **Obj);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RelatedObject )( 
            ITRiASSimpleObject * This,
            /* [in] */ ITRiASObject *Obj);
        
        END_INTERFACE
    } ITRiASSimpleObjectVtbl;

    interface ITRiASSimpleObject
    {
        CONST_VTBL struct ITRiASSimpleObjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASSimpleObject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASSimpleObject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASSimpleObject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASSimpleObject_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASSimpleObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASSimpleObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASSimpleObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASSimpleObject_get_LocalHandle(This,pVal)	\
    (This)->lpVtbl -> get_LocalHandle(This,pVal)

#define ITRiASSimpleObject_InitTarget(This,lONr,ObjType,lIdent,hObjs,phObj)	\
    (This)->lpVtbl -> InitTarget(This,lONr,ObjType,lIdent,hObjs,phObj)

#define ITRiASSimpleObject_get_RelatedObject(This,Obj)	\
    (This)->lpVtbl -> get_RelatedObject(This,Obj)

#define ITRiASSimpleObject_put_RelatedObject(This,Obj)	\
    (This)->lpVtbl -> put_RelatedObject(This,Obj)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleObject_get_LocalHandle_Proxy( 
    ITRiASSimpleObject * This,
    /* [retval][out] */ INT_PTR *pVal);


void __RPC_STUB ITRiASSimpleObject_get_LocalHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleObject_InitTarget_Proxy( 
    ITRiASSimpleObject * This,
    /* [in] */ INT_PTR lONr,
    /* [in] */ OBJECTTYPE ObjType,
    /* [in] */ INT_PTR lIdent,
    /* [in] */ INT_PTR hObjs,
    /* [out][in] */ INT_PTR *phObj);


void __RPC_STUB ITRiASSimpleObject_InitTarget_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleObject_get_RelatedObject_Proxy( 
    ITRiASSimpleObject * This,
    /* [retval][out] */ ITRiASObject **Obj);


void __RPC_STUB ITRiASSimpleObject_get_RelatedObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleObject_put_RelatedObject_Proxy( 
    ITRiASSimpleObject * This,
    /* [in] */ ITRiASObject *Obj);


void __RPC_STUB ITRiASSimpleObject_put_RelatedObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASSimpleObject_INTERFACE_DEFINED__ */


#ifndef __ITRiASSimpleObjects_INTERFACE_DEFINED__
#define __ITRiASSimpleObjects_INTERFACE_DEFINED__

/* interface ITRiASSimpleObjects */
/* [unique][helpstring][dual][uuid][object] */ 

#if !defined(_ENSURELOADEDPARAM_DEFINED)
#define _ENSURELOADEDPARAM_DEFINED

enum _tagENSURELOADEDPARAM
    {	ENSURELOADEDPARAM_ObjectTypes	= 0,
	ENSURELOADEDPARAM_Window	= 1
    } ;
#endif // _ENSURELOADEDPARAM_DEFINED

EXTERN_C const IID IID_ITRiASSimpleObjects;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("578D0E93-932B-11D1-BA04-080036D63803")
    ITRiASSimpleObjects : public ITRiASObjectsEx
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitTarget( 
            /* [in] */ LONG lIdent,
            /* [in] */ OBJECTTYPE rgObjType,
            /* [in] */ VARIANT_BOOL fCreate,
            /* [out][in] */ INT_PTR *phObjs) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnsureLoaded( 
            /* [in] */ INT_PTR hObj,
            /* [in] */ BSTR GeomName,
            /* [out][in] */ SAFEARRAY * *Constraints,
            /* [retval][out] */ ITRiASObject **Obj) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MayUnload( 
            /* [in] */ INT_PTR Obj) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASSimpleObjectsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASSimpleObjects * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASSimpleObjects * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASSimpleObjects * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASSimpleObjects * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASSimpleObjects * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASSimpleObjects * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASSimpleObjects * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LocalHandle )( 
            ITRiASSimpleObjects * This,
            /* [retval][out] */ INT_PTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITRiASSimpleObjects * This,
            /* [defaultvalue][in] */ OBJECTTYPE rgType,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Handles )( 
            ITRiASSimpleObjects * This,
            /* [in] */ long Count,
            /* [size_is][out][in] */ INT_PTR *pHandles);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InitTarget )( 
            ITRiASSimpleObjects * This,
            /* [in] */ LONG lIdent,
            /* [in] */ OBJECTTYPE rgObjType,
            /* [in] */ VARIANT_BOOL fCreate,
            /* [out][in] */ INT_PTR *phObjs);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnsureLoaded )( 
            ITRiASSimpleObjects * This,
            /* [in] */ INT_PTR hObj,
            /* [in] */ BSTR GeomName,
            /* [out][in] */ SAFEARRAY * *Constraints,
            /* [retval][out] */ ITRiASObject **Obj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MayUnload )( 
            ITRiASSimpleObjects * This,
            /* [in] */ INT_PTR Obj);
        
        END_INTERFACE
    } ITRiASSimpleObjectsVtbl;

    interface ITRiASSimpleObjects
    {
        CONST_VTBL struct ITRiASSimpleObjectsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASSimpleObjects_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASSimpleObjects_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASSimpleObjects_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASSimpleObjects_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASSimpleObjects_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASSimpleObjects_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASSimpleObjects_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASSimpleObjects_get_LocalHandle(This,pVal)	\
    (This)->lpVtbl -> get_LocalHandle(This,pVal)

#define ITRiASSimpleObjects_get_Count(This,rgType,pVal)	\
    (This)->lpVtbl -> get_Count(This,rgType,pVal)

#define ITRiASSimpleObjects_get_Handles(This,Count,pHandles)	\
    (This)->lpVtbl -> get_Handles(This,Count,pHandles)


#define ITRiASSimpleObjects_InitTarget(This,lIdent,rgObjType,fCreate,phObjs)	\
    (This)->lpVtbl -> InitTarget(This,lIdent,rgObjType,fCreate,phObjs)

#define ITRiASSimpleObjects_EnsureLoaded(This,hObj,GeomName,Constraints,Obj)	\
    (This)->lpVtbl -> EnsureLoaded(This,hObj,GeomName,Constraints,Obj)

#define ITRiASSimpleObjects_MayUnload(This,Obj)	\
    (This)->lpVtbl -> MayUnload(This,Obj)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleObjects_InitTarget_Proxy( 
    ITRiASSimpleObjects * This,
    /* [in] */ LONG lIdent,
    /* [in] */ OBJECTTYPE rgObjType,
    /* [in] */ VARIANT_BOOL fCreate,
    /* [out][in] */ INT_PTR *phObjs);


void __RPC_STUB ITRiASSimpleObjects_InitTarget_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleObjects_EnsureLoaded_Proxy( 
    ITRiASSimpleObjects * This,
    /* [in] */ INT_PTR hObj,
    /* [in] */ BSTR GeomName,
    /* [out][in] */ SAFEARRAY * *Constraints,
    /* [retval][out] */ ITRiASObject **Obj);


void __RPC_STUB ITRiASSimpleObjects_EnsureLoaded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleObjects_MayUnload_Proxy( 
    ITRiASSimpleObjects * This,
    /* [in] */ INT_PTR Obj);


void __RPC_STUB ITRiASSimpleObjects_MayUnload_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASSimpleObjects_INTERFACE_DEFINED__ */


#ifndef __ITRiASSimpleObjectsCollection_INTERFACE_DEFINED__
#define __ITRiASSimpleObjectsCollection_INTERFACE_DEFINED__

/* interface ITRiASSimpleObjectsCollection */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASSimpleObjectsCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5F20C606-B87C-11D2-95A8-006008447800")
    ITRiASSimpleObjectsCollection : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ITRiASSimpleObjectsCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASSimpleObjectsCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASSimpleObjectsCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASSimpleObjectsCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASSimpleObjectsCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASSimpleObjectsCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASSimpleObjectsCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASSimpleObjectsCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } ITRiASSimpleObjectsCollectionVtbl;

    interface ITRiASSimpleObjectsCollection
    {
        CONST_VTBL struct ITRiASSimpleObjectsCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASSimpleObjectsCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASSimpleObjectsCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASSimpleObjectsCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASSimpleObjectsCollection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASSimpleObjectsCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASSimpleObjectsCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASSimpleObjectsCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITRiASSimpleObjectsCollection_INTERFACE_DEFINED__ */


#ifndef __ITRiASSimpleFeatures_INTERFACE_DEFINED__
#define __ITRiASSimpleFeatures_INTERFACE_DEFINED__

/* interface ITRiASSimpleFeatures */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASSimpleFeatures;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1B52E2A5-EA84-11D1-861E-00600875138A")
    ITRiASSimpleFeatures : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Feature( 
            /* [in] */ INT_PTR hLocalFeat,
            /* [retval][out] */ ITRiASFeature **Feat) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASSimpleFeaturesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASSimpleFeatures * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASSimpleFeatures * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASSimpleFeatures * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASSimpleFeatures * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASSimpleFeatures * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASSimpleFeatures * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASSimpleFeatures * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Feature )( 
            ITRiASSimpleFeatures * This,
            /* [in] */ INT_PTR hLocalFeat,
            /* [retval][out] */ ITRiASFeature **Feat);
        
        END_INTERFACE
    } ITRiASSimpleFeaturesVtbl;

    interface ITRiASSimpleFeatures
    {
        CONST_VTBL struct ITRiASSimpleFeaturesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASSimpleFeatures_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASSimpleFeatures_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASSimpleFeatures_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASSimpleFeatures_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASSimpleFeatures_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASSimpleFeatures_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASSimpleFeatures_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASSimpleFeatures_get_Feature(This,hLocalFeat,Feat)	\
    (This)->lpVtbl -> get_Feature(This,hLocalFeat,Feat)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleFeatures_get_Feature_Proxy( 
    ITRiASSimpleFeatures * This,
    /* [in] */ INT_PTR hLocalFeat,
    /* [retval][out] */ ITRiASFeature **Feat);


void __RPC_STUB ITRiASSimpleFeatures_get_Feature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASSimpleFeatures_INTERFACE_DEFINED__ */


#ifndef __ITRiASSimpleGeoFeatures_INTERFACE_DEFINED__
#define __ITRiASSimpleGeoFeatures_INTERFACE_DEFINED__

/* interface ITRiASSimpleGeoFeatures */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASSimpleGeoFeatures;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("701CD5C4-FB01-11D1-863E-00600875138A")
    ITRiASSimpleGeoFeatures : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ITRiASSimpleGeoFeaturesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASSimpleGeoFeatures * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASSimpleGeoFeatures * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASSimpleGeoFeatures * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASSimpleGeoFeatures * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASSimpleGeoFeatures * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASSimpleGeoFeatures * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASSimpleGeoFeatures * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } ITRiASSimpleGeoFeaturesVtbl;

    interface ITRiASSimpleGeoFeatures
    {
        CONST_VTBL struct ITRiASSimpleGeoFeaturesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASSimpleGeoFeatures_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASSimpleGeoFeatures_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASSimpleGeoFeatures_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASSimpleGeoFeatures_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASSimpleGeoFeatures_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASSimpleGeoFeatures_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASSimpleGeoFeatures_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITRiASSimpleGeoFeatures_INTERFACE_DEFINED__ */


#ifndef __ITRiASSimpleFeature_INTERFACE_DEFINED__
#define __ITRiASSimpleFeature_INTERFACE_DEFINED__

/* interface ITRiASSimpleFeature */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITRiASSimpleFeature;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1B52E2A3-EA84-11D1-861E-00600875138A")
    ITRiASSimpleFeature : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LocalHandle( 
            /* [retval][out] */ INT_PTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitTarget( 
            /* [in] */ VARIANT InitData,
            /* [in] */ FEATURETYPE Type) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITRiASSimpleFeatureVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITRiASSimpleFeature * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITRiASSimpleFeature * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITRiASSimpleFeature * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITRiASSimpleFeature * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITRiASSimpleFeature * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITRiASSimpleFeature * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITRiASSimpleFeature * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LocalHandle )( 
            ITRiASSimpleFeature * This,
            /* [retval][out] */ INT_PTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InitTarget )( 
            ITRiASSimpleFeature * This,
            /* [in] */ VARIANT InitData,
            /* [in] */ FEATURETYPE Type);
        
        END_INTERFACE
    } ITRiASSimpleFeatureVtbl;

    interface ITRiASSimpleFeature
    {
        CONST_VTBL struct ITRiASSimpleFeatureVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITRiASSimpleFeature_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITRiASSimpleFeature_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITRiASSimpleFeature_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITRiASSimpleFeature_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITRiASSimpleFeature_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITRiASSimpleFeature_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITRiASSimpleFeature_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITRiASSimpleFeature_get_LocalHandle(This,pVal)	\
    (This)->lpVtbl -> get_LocalHandle(This,pVal)

#define ITRiASSimpleFeature_InitTarget(This,InitData,Type)	\
    (This)->lpVtbl -> InitTarget(This,InitData,Type)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleFeature_get_LocalHandle_Proxy( 
    ITRiASSimpleFeature * This,
    /* [retval][out] */ INT_PTR *pVal);


void __RPC_STUB ITRiASSimpleFeature_get_LocalHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITRiASSimpleFeature_InitTarget_Proxy( 
    ITRiASSimpleFeature * This,
    /* [in] */ VARIANT InitData,
    /* [in] */ FEATURETYPE Type);


void __RPC_STUB ITRiASSimpleFeature_InitTarget_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITRiASSimpleFeature_INTERFACE_DEFINED__ */



#ifndef __TRiASDB_LIBRARY_DEFINED__
#define __TRiASDB_LIBRARY_DEFINED__

/* library TRiASDB */
/* [helpstring][lcid][version][uuid] */ 


enum TRIASDB_VERSIONS
    {	TYPELIB_TRiASDB_VERSION_MAJOR	= 1,
	TYPELIB_TRiASDB_VERSION_MINOR	= 0
    } ;


typedef /* [helpstring][v1_enum][public] */ enum _tagEVALEXPARAM EVALEXPARAM;


EXTERN_C const IID LIBID_TRiASDB;

EXTERN_C const CLSID CLSID_TRiASProjects;

#ifdef __cplusplus

class DECLSPEC_UUID("1CB3AB7A-2E87-11D1-969D-00A024D6F582")
TRiASProjects;
#endif

EXTERN_C const CLSID CLSID_TRiASProject;

#ifdef __cplusplus

class DECLSPEC_UUID("E09B634E-8494-4236-A666-98113F02FEFD")
TRiASProject;
#endif

EXTERN_C const CLSID CLSID_OleDocumentWrapper;

#ifdef __cplusplus

class DECLSPEC_UUID("1CB3AB64-2E87-11D1-969D-00A024D6F582")
OleDocumentWrapper;
#endif

EXTERN_C const CLSID CLSID_TRiASConnections;

#ifdef __cplusplus

class DECLSPEC_UUID("191A9AF8-37FE-11D1-96B6-00A024D6F582")
TRiASConnections;
#endif

EXTERN_C const CLSID CLSID_TRiASConnection;

#ifdef __cplusplus

class DECLSPEC_UUID("191A9AF5-37FE-11D1-96B6-00A024D6F582")
TRiASConnection;
#endif

EXTERN_C const CLSID CLSID_TRiASDatabaseOnFile;

#ifdef __cplusplus

class DECLSPEC_UUID("6ACC24A4-3969-11D1-96B8-00A024D6F582")
TRiASDatabaseOnFile;
#endif

EXTERN_C const CLSID CLSID_TRiASDatabaseOnStg;

#ifdef __cplusplus

class DECLSPEC_UUID("5A28AAC2-D4B3-4A72-90FA-6DDE007EF5BD")
TRiASDatabaseOnStg;
#endif

EXTERN_C const CLSID CLSID_TRiASCompatibleDatabase;

#ifdef __cplusplus

class DECLSPEC_UUID("AD0D7076-39B0-11D1-96B9-00A024D6F582")
TRiASCompatibleDatabase;
#endif

EXTERN_C const CLSID CLSID_TRiASViews;

#ifdef __cplusplus

class DECLSPEC_UUID("1CB3AB68-2E87-11D1-969D-00A024D6F582")
TRiASViews;
#endif

EXTERN_C const CLSID CLSID_TRiASView;

#ifdef __cplusplus

class DECLSPEC_UUID("1CB3AB66-2E87-11D1-969D-00A024D6F582")
TRiASView;
#endif

EXTERN_C const CLSID CLSID_TRiASViewItems;

#ifdef __cplusplus

class DECLSPEC_UUID("1CB3AB6A-2E87-11D1-969D-00A024D6F582")
TRiASViewItems;
#endif

EXTERN_C const CLSID CLSID_TRiASViewItem;

#ifdef __cplusplus

class DECLSPEC_UUID("1CB3AB6C-2E87-11D1-969D-00A024D6F582")
TRiASViewItem;
#endif

EXTERN_C const CLSID CLSID_TRiASObjects;

#ifdef __cplusplus

class DECLSPEC_UUID("1CB3AB6E-2E87-11D1-969D-00A024D6F582")
TRiASObjects;
#endif

EXTERN_C const CLSID CLSID_TRiASSimpleObjects;

#ifdef __cplusplus

class DECLSPEC_UUID("578D0E94-932B-11D1-BA04-080036D63803")
TRiASSimpleObjects;
#endif

EXTERN_C const CLSID CLSID_TRiASObjectsCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("48172D65-AB72-11D1-858D-00600875138A")
TRiASObjectsCollection;
#endif

EXTERN_C const CLSID CLSID_TRiASSimpleObjectsCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("5F20C607-B87C-11D2-95A8-006008447800")
TRiASSimpleObjectsCollection;
#endif

EXTERN_C const CLSID CLSID_TRiASObject;

#ifdef __cplusplus

class DECLSPEC_UUID("1CB3AB70-2E87-11D1-969D-00A024D6F582")
TRiASObject;
#endif

EXTERN_C const CLSID CLSID_TRiASSimpleObject;

#ifdef __cplusplus

class DECLSPEC_UUID("90378E24-C54C-11D1-85D2-00600875138A")
TRiASSimpleObject;
#endif

EXTERN_C const CLSID CLSID_TRiASFeatures;

#ifdef __cplusplus

class DECLSPEC_UUID("1CB3AB72-2E87-11D1-969D-00A024D6F582")
TRiASFeatures;
#endif

EXTERN_C const CLSID CLSID_TRiASSimpleFeatures;

#ifdef __cplusplus

class DECLSPEC_UUID("1B52E2A6-EA84-11D1-861E-00600875138A")
TRiASSimpleFeatures;
#endif

EXTERN_C const CLSID CLSID_TRiASSimpleGeoFeatures;

#ifdef __cplusplus

class DECLSPEC_UUID("701CD5C3-FB01-11D1-863E-00600875138A")
TRiASSimpleGeoFeatures;
#endif

EXTERN_C const CLSID CLSID_TRiASFeature;

#ifdef __cplusplus

class DECLSPEC_UUID("1CB3AB74-2E87-11D1-969D-00A024D6F582")
TRiASFeature;
#endif

EXTERN_C const CLSID CLSID_TRiASSimpleFeature;

#ifdef __cplusplus

class DECLSPEC_UUID("1B52E2A4-EA84-11D1-861E-00600875138A")
TRiASSimpleFeature;
#endif

EXTERN_C const CLSID CLSID_TRiASGuidFeature;

#ifdef __cplusplus

class DECLSPEC_UUID("BED66F36-7351-11D2-9EF1-006008447800")
TRiASGuidFeature;
#endif

EXTERN_C const CLSID CLSID_TRiASSimpleGeoFeature;

#ifdef __cplusplus

class DECLSPEC_UUID("701CD5C5-FB01-11D1-863E-00600875138A")
TRiASSimpleGeoFeature;
#endif

EXTERN_C const CLSID CLSID_TRiASRelations;

#ifdef __cplusplus

class DECLSPEC_UUID("1CB3AB76-2E87-11D1-969D-00A024D6F582")
TRiASRelations;
#endif

EXTERN_C const CLSID CLSID_TRiASRelation;

#ifdef __cplusplus

class DECLSPEC_UUID("1CB3AB78-2E87-11D1-969D-00A024D6F582")
TRiASRelation;
#endif

EXTERN_C const CLSID CLSID_TRiASDBEngine;

#ifdef __cplusplus

class DECLSPEC_UUID("1CB3AB7C-2E87-11D1-969D-00A024D6F582")
TRiASDBEngine;
#endif

EXTERN_C const CLSID CLSID_TRiASProperty;

#ifdef __cplusplus

class DECLSPEC_UUID("9A9E8F25-3D7F-11D1-96C0-00A024D6F582")
TRiASProperty;
#endif

EXTERN_C const CLSID CLSID_TRiASProperties;

#ifdef __cplusplus

class DECLSPEC_UUID("9A9E8F27-3D7F-11D1-96C0-00A024D6F582")
TRiASProperties;
#endif

EXTERN_C const CLSID CLSID_TRiASDataServerRegEntries;

#ifdef __cplusplus

class DECLSPEC_UUID("F4B3F946-810E-11D1-9776-00A024D6F582")
TRiASDataServerRegEntries;
#endif

EXTERN_C const CLSID CLSID_TRiASDataServerRegEntry;

#ifdef __cplusplus

class DECLSPEC_UUID("F4B3F948-810E-11D1-9776-00A024D6F582")
TRiASDataServerRegEntry;
#endif

EXTERN_C const CLSID CLSID_TRiASVariantProperty;

#ifdef __cplusplus

class DECLSPEC_UUID("8C34B585-9FBA-11D1-BA1E-080036D63803")
TRiASVariantProperty;
#endif

EXTERN_C const CLSID CLSID_TRiASAutoSaveProperty;

#ifdef __cplusplus

class DECLSPEC_UUID("9A869E25-584B-11D2-9ED0-006008447800")
TRiASAutoSaveProperty;
#endif

EXTERN_C const CLSID CLSID_OpenWizPropExt;

#ifdef __cplusplus

class DECLSPEC_UUID("C81DD8C5-A235-11D1-BA2A-080036D63803")
OpenWizPropExt;
#endif

EXTERN_C const CLSID CLSID_TRiASObjectHandleMap;

#ifdef __cplusplus

class DECLSPEC_UUID("D4C24AD6-A5EA-11D1-BA31-080036D63803")
TRiASObjectHandleMap;
#endif

EXTERN_C const CLSID CLSID_TRiASObjectsHandleMap;

#ifdef __cplusplus

class DECLSPEC_UUID("CD579673-AA9D-11D1-858C-00600875138A")
TRiASObjectsHandleMap;
#endif

EXTERN_C const CLSID CLSID_TRiASFeatureHandleMap;

#ifdef __cplusplus

class DECLSPEC_UUID("95F58F33-DF2C-11D1-8606-00600875138A")
TRiASFeatureHandleMap;
#endif

EXTERN_C const CLSID CLSID_TRiASGenericHandleMap;

#ifdef __cplusplus

class DECLSPEC_UUID("76D74B66-D3E4-41B8-A4AA-9FF2F383CBCE")
TRiASGenericHandleMap;
#endif

EXTERN_C const CLSID CLSID_TRiASMetaDataMap;

#ifdef __cplusplus

class DECLSPEC_UUID("733F03EE-CECA-4E3B-ACEF-0920F7DB996F")
TRiASMetaDataMap;
#endif

EXTERN_C const CLSID CLSID_TRiASObjectsOperations;

#ifdef __cplusplus

class DECLSPEC_UUID("F45F28D8-7D2F-11D2-9EF6-006008447800")
TRiASObjectsOperations;
#endif

EXTERN_C const CLSID CLSID_TRiASConnectionFilters;

#ifdef __cplusplus

class DECLSPEC_UUID("8513C94D-D792-4286-B21B-AADAC2A8DCE7")
TRiASConnectionFilters;
#endif

EXTERN_C const CLSID CLSID_TRiASConnectionFilter;

#ifdef __cplusplus

class DECLSPEC_UUID("52A74060-48AB-4FA0-A4DE-186A0C30FE4E")
TRiASConnectionFilter;
#endif
#endif /* __TRiASDB_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

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


