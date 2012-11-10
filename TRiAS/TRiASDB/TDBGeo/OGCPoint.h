// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 17.01.2002 13:11:40 
//
// @doc
// @module OGCPoint.h | Declaration of the <c COGCPoint> class

#if !defined(_OGCPOINT_H__FCF89054_81C2_4500_84DE_31E67E90A191__INCLUDED_)
#define _OGCPOINT_H__FCF89054_81C2_4500_84DE_31E67E90A191__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if defined(_INCLUDE_OGC_OBJECTS)

#include "resource.h"
#include <Atl/DelegatingDispatch.h>

/////////////////////////////////////////////////////////////////////////////
// COGCPoint

class ATL_NO_VTABLE COGCPoint : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<COGCPoint, &CLSID_OGCPoint>,
	public IDelegatingDispImpl<DPoint, IPoint, &IID_IPoint, TLB_TDBGEO_SIGNAT>
//	public ISpatialOperator,
//	public ISpatialRelation,
//	public ISpatialRelation2,
//	public IWks
{
public:
// Construction
	COGCPoint();
	virtual ~COGCPoint();

// Initialisation

// Operations
	DECLARE_REGISTRY_RESOURCEID(IDR_OGCPOINT)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

// Interface map
	BEGIN_COM_MAP(COGCPoint)
		COM_INTERFACE_ENTRY(IGeometry)
		COM_INTERFACE_ENTRY(IPoint)
		COM_INTERFACE_ENTRY(DPoint)
//		COM_INTERFACE_ENTRY(ISpatialOperator)
//		COM_INTERFACE_ENTRY(ISpatialRelation)
//		COM_INTERFACE_ENTRY(ISpatialRelation2)
//		COM_INTERFACE_ENTRY(IWks)
	END_COM_MAP()

// Implementation
protected:
// Attributes

// Operations

// Interfaces
public:
// IGeometry
	STDMETHODIMP get_Dimension(long * dimension);
	STDMETHODIMP get_SpatialReference(ISpatialReference** spatialRef);
	STDMETHODIMP putref_SpatialReference(ISpatialReference* spatialRef);
	STDMETHODIMP get_IsEmpty(VARIANT_BOOL * isEmpty);
	STDMETHODIMP SetEmpty();
	STDMETHODIMP get_IsSimple(VARIANT_BOOL * isSimple);
	STDMETHODIMP Envelope(IGeometry** envelope);
	STDMETHODIMP Clone(IGeometry ** newShape);
	STDMETHODIMP Project(ISpatialReference * newSystem, IGeometry **result);
	STDMETHODIMP Extent2D(double* minX, double* minY, double* maxX, double* maxY);

// IPoint
	STDMETHODIMP Coords(double* x, double * y);
	STDMETHODIMP get_X(double * x);
	STDMETHODIMP get_Y(double * y);

//// ISpatialOperator
//	STDMETHODIMP Distance(IGeometry* other, double* distance);
//	STDMETHODIMP Boundary(IGeometry ** boundary);
//	STDMETHODIMP Buffer(double distance, IGeometry** result);
//	STDMETHODIMP ConvexHull(IGeometry ** result);
//	STDMETHODIMP Intersection(IGeometry* other, IGeometry ** result);
//	STDMETHODIMP Union(IGeometry* other,  IGeometry ** result);
//	STDMETHODIMP Difference(IGeometry* other, IGeometry ** result);
//	STDMETHODIMP SymmetricDifference(IGeometry* other, IGeometry ** result);

//// ISpatialRelation
//	STDMETHODIMP Equals(IGeometry* other, VARIANT_BOOL * equals);
//	STDMETHODIMP Touches(IGeometry* other, VARIANT_BOOL * touches);
//	STDMETHODIMP Contains(IGeometry* other, VARIANT_BOOL * contains);
//	STDMETHODIMP Within(IGeometry* other, VARIANT_BOOL * within);
//	STDMETHODIMP Disjoint(IGeometry* other, VARIANT_BOOL * disjoint);
//	STDMETHODIMP Crosses(IGeometry* other, VARIANT_BOOL * crosses);
//	STDMETHODIMP Overlaps(IGeometry* other, VARIANT_BOOL * overlaps);
//	STDMETHODIMP Intersects(IGeometry* other, VARIANT_BOOL * overlaps);

//// ISpatialRelation2
//	STDMETHODIMP Relate(IGeometry* other, 
//                  BSTR patternMatrix, VARIANT_BOOL* isRelated);

//// IWks
//	STDMETHODIMP ExportToWKB(VARIANT* wkb);
//	STDMETHODIMP ExportToWKT(BSTR* wkt);
//	STDMETHODIMP ImportFromWKB(VARIANT wkb, ISpatialReference* spatialRef);
//	STDMETHODIMP ImportFromWKT(BSTR wkt, ISpatialReference* spatialRef);

private:
//	W
};

#endif // defined(_INCLUDE_OGC_OBJECTS)

#endif // !defined(_OGCPOINT_H__FCF89054_81C2_4500_84DE_31E67E90A191__INCLUDED_)
