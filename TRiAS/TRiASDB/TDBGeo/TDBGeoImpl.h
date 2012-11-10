////////////////////////////////////////////////////////////////////////////
// hier alles(?) was zur Implementation von TDBGeo notwendig ist

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"	   // main symbols

#include "TDBGeo.h"			// kommt vom MIDL
#include "TDBGeo.hmc"		// Fehlerkonstanten

#include "GeoUtil.h"
#include "Strings.h"

#include "com/VariantHelpers.h"

#include <float.h>			// wegen DBL_MAX #AK981119

////////////////////////////////////////////////////////////////////////////
// Startwerte für Minimum / Maximum - Berechnung von Containern
// Halbierung, weil bei Containern oft mit der Breite (!!) gerechnet wird;
// somit übersteigt Container.XMax - Container.XMin nicht den double-Bereich
#ifndef _M_M68K
#define	INIT_DBL_MIN		(DBL_MAX/2)
#define	INIT_DBL_MAX		-(DBL_MAX/2)
#else
#define	INIT_DBL_MIN		(LDBL_MAX/2)
#define	INIT_DBL_MAX		-(LDBL_MAX/2)
#endif

typedef struct CSCOORD CSCOORD;						// aus TRiASCS.tlb

#define SIZEOF_POINT	sizeof(CSCOORD)

#define FUNC_NOT_IMPL()	{ _ASSERTE(SUCCEEDED(E_NOTIMPL)); return E_NOTIMPL; }
#define	TLB_TDBGEO_SIGNAT	&LIBID_TDBGEO, TYPELIB_TDBGEO_VERSION_MAJOR, TYPELIB_TDBGEO_VERSION_MINOR

///////////////////////////////////////////////////////////////////////////////
// OGC specifics
enum wkbGeometryType {   
	wkbUserDefined = 0,
	wkbPoint = 1,
	wkbLineString = 2,
	wkbPolygon = 3,
	wkbMultiPoint = 4,
	wkbMultiLineString = 5,
	wkbMultiPolygon = 6,
	wkbGeometryCollection = 7,
	wkbPoint25D = 8,
	wkbLineString25D = 9,
	wkbPolygon25D = 10,
	wkbMultiPoint25D = 11,
	wkbMultiLineString25D = 12,
	wkbMultiPolygon25D = 13, 
};

enum wkbByteOrder {
	wkbXDR = 0,				// Big Endian
	wkbNDR = 1				// Little Endian
};

/////////////////////////////////////////////////////////////////////////////
// Interfacewrapper

// System
DefineSmartInterface(Stream);
DefineSmartInterface(PersistStream);
DefineSmartInterface(PersistMemory);
DefineSmartInterface(PersistStreamInit);
DefineSmartInterface(Dispatch);												// WDispatch

// Enumeratoren
DefineSmartInterface(EnumVARIANT);											// W_EnumVARIANT

// Koordinatentransformation
DefineSmartInterface(TRiASRawCoordTransform)
DefineSmartInterface(TRiASTransformGeometry)
DefineSmartInterface(TRiASCSTransform)
DefineSmartInterface(TRiASCS)
DefineSmartInterface(TRiASCSGCS)
DefineSmartInterface(TRiASCSPCS)
DefineSmartInterface(TRiASCSDatumTransformation)

// unsere eigenen
DefineSmartInterface(TRiASCSGeometryProperties)
DefineSmartInterface(TRiASSimpleRectangle)
DefineSmartInterface(TRiASSimplePoints)
DefineSmartInterface(TRiASSimplePoint)
DefineSmartInterface(TRiASCloneGeometry)
DefineSmartInterface(TRiASCSMBRAccess);										// WTRiASCSMBRAccess
DefineSmartInterface(PersistMemoryGDO);
DefineSmartInterface(PersistMemoryWks);

// Geomedia
//DefineSmartInterface2(DGMGeometryStorageService, IID_DGMGeometryStorageService);
DefineSmartInterface2(_DGMGeometry , IID__DGMGeometry);
DefineSmartInterface2(_DGMPoint , IID__DGMPoint);							// W_DGMPoint
DefineSmartInterface2(_DGMPoints , IID__DGMPoints);							// W_DGMPoints
DefineSmartInterface2(_DGMBoundaryGeometry , IID__DGMBoundaryGeometry)		// W_DGMBoundaryGeometry
DefineSmartInterface2(_DGMRectangleGeometry , IID__DGMRectangleGeometry);	// W_DGMRectangleGeometry
DefineSmartInterface2(_DGMPointGeometry , IID__DGMPointGeometry);			// W_DGMPointGeometry
DefineSmartInterface2(_DGMLineGeometry , IID__DGMLineGeometry);				// W_DGMLineGeometry
DefineSmartInterface2(_DGMGeometryCollection , IID__DGMGeometryCollection);	// W_DGMGeometryCollection
DefineSmartInterface2(_DGMOrientedPointGeometry , IID__DGMOrientedPointGeometry);	// W_DGMPointGeometry
DefineSmartInterface2(_DGMPolygonGeometry , IID__DGMPolygonGeometry);		// W_DGMPolygonGeometry
DefineSmartInterface2(_DGMPolylineGeometry , IID__DGMPolylineGeometry);		// W_DGMPolylineGeometry
DefineSmartInterface2(_DGMRectangleGeometry , IID__DGMRectangleGeometry);	// W_DGMRectangleGeometry
DefineSmartInterface2(_DGMTextPointGeometry , IID__DGMTextPointGeometry);	// W_DGMTextPointGeometry
DefineSmartInterface2(_DGMVector , IID__DGMVector);							// W_DGMVector

#define _CSPOINT_ALREADY_PRESENT_
#define _CSRECT_ALREADY_PRESENT_
#include <CSRectGeom.h>
