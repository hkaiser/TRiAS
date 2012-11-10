///////////////////////////////////////////////////////////////////////////
// @doc
// @module GMGeometryBLOB.h | Geometrie-BLOB-Formate von GeoMedia

#if !defined(_GMGEOMETRYBLOB_H__BD75C183_E3E2_11D1_860E_00600875138A__INCLUDED_)
#define _GMGEOMETRYBLOB_H__BD75C183_E3E2_11D1_860E_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// GUID's
// {0FD2FFC0-8CBC-11cf-ABDE-08003601B769}
extern "C" const IID __declspec(selectany) CLSID_GMPointGeometryBlob = 
	{0x0FD2FFC0,0x8CBC,0x11cf,{0xAB,0xDE,0x08,0x00,0x36,0x01,0xB7,0x69}};

// {0FD2FFC1-8CBC-11cf-ABDE-08003601B769}
extern "C" const IID __declspec(selectany) CLSID_GMLineGeometryBlob = 
	{0x0FD2FFC1,0x8CBC,0x11cf,{0xAB,0xDE,0x08,0x00,0x36,0x01,0xB7,0x69}};

// {0FD2FFC2-8CBC-11cf-ABDE-08003601B769}
extern "C" const IID __declspec(selectany) CLSID_GMPolylineGeometryBlob = 
	{0x0FD2FFC2,0x8CBC,0x11cf,{0xAB,0xDE,0x08,0x00,0x36,0x01,0xB7,0x69}};

// {0FD2FFC3-8CBC-11cf-ABDE-08003601B769}
extern "C" const IID __declspec(selectany) CLSID_GMPolygonGeometryBlob = 
	{0x0FD2FFC3,0x8CBC,0x11cf,{0xAB,0xDE,0x08,0x00,0x36,0x01,0xB7,0x69}};

// {0FD2FFC5-8CBC-11cf-ABDE-08003601B769}
extern "C" const IID __declspec(selectany) CLSID_GMBoundaryGeometryBlob = 
	{0x0FD2FFC5,0x8CBC,0x11cf,{0xAB,0xDE,0x08,0x00,0x36,0x01,0xB7,0x69}};

// {0FD2FFC6-8CBC-11cf-ABDE-08003601B769}
extern "C" const IID __declspec(selectany) CLSID_GMGeometryCollectionBlob = 
	{0x0FD2FFC6,0x8CBC,0x11cf,{0xAB,0xDE,0x08,0x00,0x36,0x01,0xB7,0x69}};

// {0FD2FFC7-8CBC-11cf-ABDE-08003601B769}
extern "C" const IID __declspec(selectany) CLSID_GMRectangleGeometryBlob = 
	{0x0FD2FFC7,0x8CBC,0x11cf,{0xAB,0xDE,0x08,0x00,0x36,0x01,0xB7,0x69}};

// {0FD2FFC8-8CBC-11cf-ABDE-08003601B769}
extern "C" const IID __declspec(selectany) CLSID_GMOrientedPointGeometryBlob = 
	{0x0FD2FFC8,0x8CBC,0x11cf,{0xAB,0xDE,0x08,0x00,0x36,0x01,0xB7,0x69}};

// {0FD2FFC9-8CBC-11cf-ABDE-08003601B769}
extern "C" const IID __declspec(selectany) CLSID_GMTextPointGeometryBlob = 
	{0x0FD2FFC9,0x8CBC,0x11cf,{0xAB,0xDE,0x08,0x00,0x36,0x01,0xB7,0x69}};

// {0FD2FFCA-8CBC-11cf-ABDE-08003601B769}
extern "C" const IID __declspec(selectany) CLSID_GMArcGeometryBlob = 
	{0x0FD2FFCA,0x8CBC,0x11cf,{0xAB,0xDE,0x08,0x00,0x36,0x01,0xB7,0x69}};

// {0FD2FFCB-8CBC-11cf-ABDE-08003601B769}
extern "C" const IID __declspec(selectany) CLSID_GMCompositePolylineGeometryBlob = 
	{0x0FD2FFCB,0x8CBC,0x11cf,{0xAB,0xDE,0x08,0x00,0x36,0x01,0xB7,0x69}};

// {0FD2FFCC-8CBC-11cf-ABDE-08003601B769}
extern "C" const IID __declspec(selectany) CLSID_GMCompositePolygonGeometryBlob = 
	{0x0FD2FFCC,0x8CBC,0x11cf,{0xAB,0xDE,0x08,0x00,0x36,0x01,0xB7,0x69}};

/////////////////////////////////////////////////////////////////////////////
// Eine Punktkoordinate
typedef tagGMPOINT {
	double x;
	double y;
	double z;
} GMPOINT;

/////////////////////////////////////////////////////////////////////////////
// PointGeometry
typedef tagGMPOINTBLOB {
	GUID guid;			// CLSID_GMPointGeometryBlob
	GMPOINT origin;
} GMPOINTBLOB;

/////////////////////////////////////////////////////////////////////////////
// LineGeometry
typedef tagGMLINEBLOB {
	GUID guid;			// CLSID_GMLineGeometryBlob
	GMPOINT start;
	GMPOINT end;
} GMLINEBLOB;

/////////////////////////////////////////////////////////////////////////////
// PolylineGeometry
typedef tagGMPOLYLINEBLOB {
	GUID guid;			// CLSID_GMPolylineGeometryBlob
	long numPoints;
	GMPOINT line[1];	// size_is(numpoints)
} GMPOLYLINEBLOB;

/////////////////////////////////////////////////////////////////////////////
// PolylineGeometry
typedef tagGMPOLYGONBLOB {
	GUID guid;			// CLSID_GMPolygonGeometryBlob
	long numPoints;
	GMPOINT line[1];	// size_is(numpoints)
} GMPOLYGONBLOB;

/////////////////////////////////////////////////////////////////////////////
// OrientedPointGeometry
typedef tagGMORIENTEDPOINTBLOB {
	GUID guid;			// CLSID_GMOrientedPointGeometryBlob
	GMPOINT origin;
	GMPOINT orientation;
} GMORIENTEDPOINTBLOB;

/////////////////////////////////////////////////////////////////////////////
// TextPointGeometry
typedef tagGMTEXTPOINTBLOB {
	GUID guid;			// CLSID_GMOrientedPointGeometryBlob
	GMPOINT origin;
	double rotation;
	GMPOINT normal;
	BYTE unused[2];
	BYTE formatted;
	BYTE alignement;
	long textsize;
	void *ptext;
} GMTEXTPOINTBLOB;

/////////////////////////////////////////////////////////////////////////////
// RectangleGeometry
typedef tagGMLINEBLOB {
	GUID guid;			// CLSID_GMRectangleGeometryBlob
	GMPOINT origin;
	double width;
	double height;
	double rotation;
	GMPOINT normal;
} GMLINEBLOB;

#endif // !defined(_GMGEOMETRYBLOB_H__BD75C183_E3E2_11D1_860E_00600875138A__INCLUDED_)
