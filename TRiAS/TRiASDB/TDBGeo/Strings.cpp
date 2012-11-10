///////////////////////////////////////////////////////////////////////////
// Stringkonstanten
// File: Strings.cpp

#include "StdAfx.h"
#include "TDBGeoImpl.h"

/////////////////////////////////////////////////////////////////////////////
// Fehlermeldungen bei schweren Fehlern
const OLECHAR g_cbNoMemory[] = L"Kein Speicherplatz!";

/////////////////////////////////////////////////////////////////////////////
// GeometrieTypen
const OLECHAR g_cbBoundaryGeometry[] = L"BoundaryGeometry";
const OLECHAR g_cbCompositePolygonGeometry[] = L"CompositePolygonGeometry";
const OLECHAR g_cbCompositePolylineGeometry[] = L"CompositePolylineGeometry";
const OLECHAR g_cbGeometryCollection[] = L"GeometryCollection";
const OLECHAR g_cbLineGeometry[] = L"LineGeometry";
const OLECHAR g_cbOrientedPointGeometry[] = L"OrientedPointGeometry";
const OLECHAR g_cbPointGeometry[] = L"PointGeometry";
const OLECHAR g_cbPolygonGeometry[] = L"PolygonGeometry";
const OLECHAR g_cbPolylineGeometry[] = L"PolylineGeometry";
const OLECHAR g_cbRasterGeometry[] = L"RasterGeometry";
const OLECHAR g_cbRectangleGeometry[] = L"RectangleGeometry";
const OLECHAR g_cbTextPointGeometry[] = L"TextPointGeometry";

// sonstiges
const TCHAR g_cbTRiASDefaultName[] = TEXT("TRiAS®");
#if _TRiAS_VER < 0x0400
const TCHAR g_cbTRiASDefaultNameT[] = TEXT("InterTRiAS®");
#endif // _TRiAS_VER < 0x0400
const TCHAR g_cbNil[] = TEXT("");

const OLECHAR g_cbPerfCtx[] = L"TDBGeo";

///////////////////////////////////////////////////////////////////////////////
// GeometrieMoniker
const OLECHAR g_cbMkGeom[] = L"TRiAS.MkGeometry.1";
const OLECHAR g_cbColon[] = L":";
const OLECHAR g_cbComma[] = L",";
const OLECHAR g_cbSpace[] = L" ";

///////////////////////////////////////////////////////////////////////////////
// Globale Zeichenketten (nicht konstant)
TCHAR g_cbTRiAS[_MAX_PATH];
