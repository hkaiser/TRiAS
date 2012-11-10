// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 11.10.2002 12:02:01 
//
// @doc
// @module Wrapper.h | Declaration of the <c CWrapper> class

#if !defined(_WRAPPER_H__8332F969_D7C0_48F5_88EE_90E815F19FF1__INCLUDED_)
#define _WRAPPER_H__8332F969_D7C0_48F5_88EE_90E815F19FF1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Standard - Objekte

DefineSmartInterface(EnumVARIANT)			// WEnumVariant
DefineSmartInterface(EnumString)			// WEnumString
DefineSmartInterface(ErrorInfo)				// WErrorInfo

///////////////////////////////////////////////////////////////////////////////
// GeoMedia - Objekte

DefineSmartInterface2(IGMCoordSystem,IID_IGMCoordSystem)			// WIGMCoordSystem
DefineSmartInterface2(DGMCoordSystem,IID_DGMCoordSystem)			// WDGMCoordsystem
DefineSmartInterface2(DGMCoordSystemsMgr,IID_DGMCoordSystemsMgr)	// WDGMCoordSystemsMgr
	DefineSmartInterface2(RefSpaceMgr,DIID_RefSpaceMgr)				// WIGMRefSpaceMgr
	DefineSmartInterface2(ProjSpace,DIID_ProjSpace)					// WIGMProjSpace
	DefineSmartInterface2(GeogSpace,DIID_GeogSpace)					// WIGMGeogSpace
	DefineSmartInterface2(PaperSpace,DIID_PaperSpace)				// WIGMPaperSpace
	DefineSmartInterface2(UnitFormatSpec,DIID_UnitFormatSpec)		// WUnitFormatSpec
	DefineSmartInterface2(DGMUnitsOfMeasure,DIID_DGMUnitsOfMeasure)	// WDGMUnitsOfMeasure

///////////////////////////////////////////////////////////////////////////////
// TRiAS - Geometrieobjekte
DefineSmartInterface(TRiASCSStorageServiceGDO)
DefineSmartInterface(TRiASCSGeometryProperties)
DefineSmartInterface(TRiASCloneGeometry)
DefineSmartInterface(TRiASSimpleRectangle)
	DefineSmartInterface2(_DGMPoint,IID__DGMPoint)
	DefineSmartInterface2(_DGMVector,IID__DGMVector)
	DefineSmartInterface2(_DGMMatrix,IID__DGMMatrix)
	DefineSmartInterface2(_DGMPoints,IID__DGMPoints)
	DefineSmartInterface2(_DGMGeometry,IID__DGMGeometry)
	DefineSmartInterface2(_DGMPointGeometry,IID__DGMPointGeometry)
	DefineSmartInterface2(_DGMLineGeometry,IID__DGMLineGeometry)
	DefineSmartInterface2(_DGMPolylineGeometry,IID__DGMPolylineGeometry)
	DefineSmartInterface2(_DGMPolygonGeometry,IID__DGMPolygonGeometry)
	DefineSmartInterface2(_DGMBoundaryGeometry,IID__DGMBoundaryGeometry)
	DefineSmartInterface2(_DGMGeometryCollection,IID__DGMGeometryCollection)
	DefineSmartInterface2(_DGMRectangleGeometry,IID__DGMRectangleGeometry)
	DefineSmartInterface2(_DGMOrientedPointGeometry,IID__DGMOrientedPointGeometry)
	DefineSmartInterface2(_DGMTextPointGeometry,IID__DGMTextPointGeometry)
	DefineSmartInterface2(_DGMArcGeometry,IID__DGMArcGeometry)
	DefineSmartInterface2(_DGMCompositePolylineGeometry,IID__DGMCompositePolylineGeometry)
	DefineSmartInterface2(_DGMCompositePolygonGeometry,IID__DGMCompositePolygonGeometry)

DefineSmartInterface2(DGMLegends,IID_DGMLegends )
	DefineSmartInterface2(DGMLegend,IID_DGMLegend )

DefineSmartInterface2(_MetadataService,IID__MetadataService)
	DefineSmartInterface2(_TableProperty,IID__TableProperty)
	DefineSmartInterface2(_FieldProperty,IID__FieldProperty)

DefineSmartInterface2(DGMGeometryStorageService,IID_GMGeometryStorageService)
DefineSmartInterface2(DGMServerTransService,IID_DGMServerTransService)
	DefineSmartInterface2(OriginatingPipe,IID_OriginatingPipe )			// WOriginatingPipe
	DefineSmartInterface2(AltCoordSystemPath,IID_AltCoordSystemPath)
	DefineSmartInterface2(ISpatialFilterPipe,IID_ISpatialFilterPipe )	// WISpatialFilterPipe
	DefineSmartInterface2(DGMCSSTransformPipe,IID_DGMCSSTransformPipe )

DefineSmartInterface2(DGMConnections,IID_DGMConnections )				// WDGMConnections
	DefineSmartInterface2(DGMConnection,IID_DGMConnection )				// WDGMConnection

DefineSmartInterface2(GDatabase,IID_GDatabase )							// WGDatabase
	DefineSmartInterface2(GErrors,IID_GErrors )							// WGErrors
	DefineSmartInterface2(GError,IID_GError )							// WGError
	DefineSmartInterface2(GRecordsets,IID_GRecordsets )					// WGRecordsets
	DefineSmartInterface2(GRecordset,IID_GRecordset )					// WGRecordset
	DefineSmartInterface2(GTableDefs,IID_GTableDefs )					// WGTableDefs
	DefineSmartInterface2(GTableDef,IID_GTableDef )						// WGTableDef
	DefineSmartInterface2(GFields,IID_GFields )							// WGFields
	DefineSmartInterface2(GField,IID_GField )							// WGField
	DefineSmartInterface2(GIndexes,IID_GIndexes )						// WGIndexes
	DefineSmartInterface2(GIndex,IID_GIndex )							// WGIndex

DefineSmartInterface2(DGDOServerRegEntries,IID_DGDOServerRegEntries )
DefineSmartInterface2(DGDOServerRegEntry,IID_DGDOServerRegEntry )

///////////////////////////////////////////////////////////////////////////////
// Helper - Objekte

DefineSmartInterface(ParseStringPairs);			// WParseStringPairs
DefineSmartInterface(ParseStringPairs2);		// WParseStringPairs2
DefineSmartInterface(ComposeStringPairs);		// WComposeStringPairs

///////////////////////////////////////////////////////////////////////////////
// Koordinatensysteme
DefineSmartInterface(TRiASCS)
DefineSmartInterface(TRiASCSGCS)
DefineSmartInterface(TRiASCSPCS)
DefineSmartInterface(TRiASCSDatumTransformation)
DefineSmartInterface(TRiASCSTransform)
DefineSmartInterface(TRiASTransformGeometry)

///////////////////////////////////////////////////////////////////////////////
// Hasgenerator
//DefineSmartInterface(TRiASHashGen)

///////////////////////////////////////////////////////////////////////////////
// TRiAS Datenbank
DefineSmartInterface(TRiASHandle)				// WTRiASHandle
DefineSmartInterface(TRiASBase)					// WTRiASBase
DefineSmartInterface(TRiASDatabase)				// WTRiASDatabase
DefineSmartInterface(TRiASConnection)			// WTRiASConnection

DefineSmartInterface(TRiASObjectHandleMap)		// WTRiASObjectHandleMap
DefineSmartInterface(TRiASObjectsCollection)	// WTRiASObjectsCollection
DefineSmartInterface(TRiASObject)				// WTRiASObject
DefineSmartInterface(TRiASObjects)				// WTRiASObjects
DefineSmartInterface(TRiASFeature)				// WTRiASFeature
DefineSmartInterface(TRiASFeatures)				// WTRiASFeatures
DefineSmartInterface(TRiASFeatureCallback)		// WTRiASFeatureCallback
DefineSmartInterface(TRiASFeaturesCallback)		// WTRiASFeaturesCallback
DefineSmartInterface(TRiASDataServerRegEntries)
DefineSmartInterface(TRiASDataServerRegEntry)

///////////////////////////////////////////////////////////////////////////////
// Metadatenservice
DefineSmartInterface(TRiASMDSMap)
DefineSmartInterface(TRiASMDSStringColl)
DefineSmartInterface(TRiASMDSKey)

///////////////////////////////////////////////////////////////////////////////
// ich selber
DefineSmartInterface(GDODBEngine)
DefineSmartInterface(GDODatabase)

DefineSmartInterface(GDOObjectsCollection)
DefineSmartInterface(GDOObject)
DefineSmartInterface(GDOObjects)
DefineSmartInterface(GDOFeature)
DefineSmartInterface(GDOFeatures)

#endif // !defined(_WRAPPER_H__8332F969_D7C0_48F5_88EE_90E815F19FF1__INCLUDED_)
