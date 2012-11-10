///////////////////////////////////////////////////////////////////////////
// Stringkonstanten
// File: Strings.h

#if !defined(_STRINGS_H__BC145185_013F_11D2_864C_00600875138A__INCLUDED_)
#define _STRINGS_H__BC145185_013F_11D2_864C_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Fehlermeldungen bei schweren Fehlern
extern const OLECHAR g_cbNoMemory[];			// TEXT("Kein Speicherplatz!");

/////////////////////////////////////////////////////////////////////////////
// GeometrieTypen
extern const OLECHAR g_cbBoundaryGeometry[];	// TEXT("BoundaryGeometry");
extern const OLECHAR g_cbCompositePolygonGeometry[];	// TEXT("CompositePolygonGeometry");
extern const OLECHAR g_cbCompositePolylineGeometry[];	// TEXT("CompositePolylineGeometry");
extern const OLECHAR g_cbGeometryCollection[];	// TEXT("GeometryCollection");
extern const OLECHAR g_cbLineGeometry[];		// TEXT("LineGeometry");
extern const OLECHAR g_cbOrientedPointGeometry[];	// TEXT("OrientedPointGeometry");
extern const OLECHAR g_cbPointGeometry[];		// TEXT("PointGeometry");
extern const OLECHAR g_cbPolygonGeometry[];		// TEXT("PolygonGeometry");
extern const OLECHAR g_cbPolylineGeometry[];	// TEXT("PolylineGeometry");
extern const OLECHAR g_cbRasterGeometry[];		// TEXT("RasterGeometry");
extern const OLECHAR g_cbRectangleGeometry[];	// TEXT("RectangleGeometry");
extern const OLECHAR g_cbTextPointGeometry[];	// TEXT("TextPointGeometry");

// sonstiges
extern const TCHAR g_cbTRiASDefaultName[];		// TEXT("TRiAS®");
#if _TRiAS_VER < 0x0400
extern const TCHAR g_cbTRiASDefaultNameT[];		// TEXT("InterTRiAS®");
#endif // _TRiAS_VER < 0x0400
extern const TCHAR g_cbNil[];					// TEXT("");

extern const OLECHAR g_cbPerfCtx[];				// L"TDBGeo";

///////////////////////////////////////////////////////////////////////////////
// GeometrieMoniker
extern const OLECHAR g_cbMkGeom[];				// L"TRiAS.MkGeometry.1";
extern const OLECHAR g_cbColon[];				// L":";
extern const OLECHAR g_cbComma[];				// L",";
extern const OLECHAR g_cbSpace[];				// L" ";

///////////////////////////////////////////////////////////////////////////////
// Globale Zeichenketten (nicht konstant)
extern TCHAR g_cbTRiAS[_MAX_PATH];

#endif // !defined(_STRINGS_H__BC145185_013F_11D2_864C_00600875138A__INCLUDED_)
