// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 17.01.2002 13:16:18 
//
// @doc
// @module OGCPoint.cpp | Definition of the <c COGCPoint> class

#include "stdafx.h"
#include "TDBGeoImpl.h"

#if defined(_INCLUDE_OGC_OBJECTS)

#include "OGCPoint.h"

/////////////////////////////////////////////////////////////////////////////
// COGCPoint

// Constructor
COGCPoint::COGCPoint()
{
}

// Destructor
COGCPoint::~COGCPoint()
{
}

/////////////////////////////////////////////////////////////////////////////
// IGeometry

// Implementation of get_Dimension
STDMETHODIMP COGCPoint::get_Dimension(long * dimension)
{
	return E_NOTIMPL;
}

// Implementation of get_SpatialReference
STDMETHODIMP COGCPoint::get_SpatialReference(ISpatialReference** spatialRef)
{
	return E_NOTIMPL;
}

// Implementation of putref_SpatialReference
STDMETHODIMP COGCPoint::putref_SpatialReference(ISpatialReference* spatialRef)
{
	return E_NOTIMPL;
}

// Implementation of get_IsEmpty
STDMETHODIMP COGCPoint::get_IsEmpty(VARIANT_BOOL * isEmpty)
{
	return E_NOTIMPL;
}

// Implementation of SetEmpty
STDMETHODIMP COGCPoint::SetEmpty()
{
	return E_NOTIMPL;
}

// Implementation of get_IsSimple
STDMETHODIMP COGCPoint::get_IsSimple(VARIANT_BOOL * isSimple)
{
	return E_NOTIMPL;
}

// Implementation of Envelope
STDMETHODIMP COGCPoint::Envelope(IGeometry** envelope)
{
	return E_NOTIMPL;
}

// Implementation of Clone
STDMETHODIMP COGCPoint::Clone(IGeometry ** newShape)
{
	return E_NOTIMPL;
}

// Implementation of Project
STDMETHODIMP COGCPoint::Project(ISpatialReference * newSystem, IGeometry **result)
{
	return E_NOTIMPL;
}

// Implementation of Extent2D
STDMETHODIMP COGCPoint::Extent2D(double* minX, double* minY, double* maxX, double* maxY)
{
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
// IPoint

// Implementation of Coords
STDMETHODIMP COGCPoint::Coords(double* x, double * y)
{
	return E_NOTIMPL;
}

// Implementation of get_X
STDMETHODIMP COGCPoint::get_X(double * x)
{
	return E_NOTIMPL;
}

// Implementation of get_Y
STDMETHODIMP COGCPoint::get_Y(double * y)
{
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
//// ISpatialOperator
//
//// Implementation of Distance
//STDMETHODIMP COGCPoint::Distance(IGeometry* other, double* distance)
//{
//	return E_NOTIMPL;
//}
//
//// Implementation of Boundary
//STDMETHODIMP COGCPoint::Boundary(IGeometry ** boundary)
//{
//	return E_NOTIMPL;
//}
//
//// Implementation of Buffer
//STDMETHODIMP COGCPoint::Buffer(double distance, IGeometry** result)
//{
//	return E_NOTIMPL;
//}
//
//// Implementation of ConvexHull
//STDMETHODIMP COGCPoint::ConvexHull(IGeometry ** result)
//{
//	return E_NOTIMPL;
//}
//
//// Implementation of Intersection
//STDMETHODIMP COGCPoint::Intersection(IGeometry* other, IGeometry ** result)
//{
//	return E_NOTIMPL;
//}
//
//// Implementation of Union
//STDMETHODIMP COGCPoint::Union(IGeometry* other,  IGeometry ** result)
//{
//	return E_NOTIMPL;
//}
//
//// Implementation of Difference
//STDMETHODIMP COGCPoint::Difference(IGeometry* other, IGeometry ** result)
//{
//	return E_NOTIMPL;
//}
//
//// Implementation of SymmetricDifference
//STDMETHODIMP COGCPoint::SymmetricDifference(IGeometry* other, IGeometry ** result)
//{
//	return E_NOTIMPL;
//}

///////////////////////////////////////////////////////////////////////////////
//// ISpatialRelation
//
//// Implementation of Equals
//STDMETHODIMP COGCPoint::Equals(IGeometry* other, VARIANT_BOOL * equals)
//{
//	return E_NOTIMPL;
//}
//
//// Implementation of Touches
//STDMETHODIMP COGCPoint::Touches(IGeometry* other, VARIANT_BOOL * touches)
//{
//	return E_NOTIMPL;
//}
//
//// Implementation of Contains
//STDMETHODIMP COGCPoint::Contains(IGeometry* other, VARIANT_BOOL * contains)
//{
//	return E_NOTIMPL;
//}
//
//// Implementation of Within
//STDMETHODIMP COGCPoint::Within(IGeometry* other, VARIANT_BOOL * within)
//{
//	return E_NOTIMPL;
//}
//
//// Implementation of Disjoint
//STDMETHODIMP COGCPoint::Disjoint(IGeometry* other, VARIANT_BOOL * disjoint)
//{
//	return E_NOTIMPL;
//}
//
//// Implementation of Crosses
//STDMETHODIMP COGCPoint::Crosses(IGeometry* other, VARIANT_BOOL * crosses)
//{
//	return E_NOTIMPL;
//}
//
//// Implementation of Overlaps
//STDMETHODIMP COGCPoint::Overlaps(IGeometry* other, VARIANT_BOOL * overlaps)
//{
//	return E_NOTIMPL;
//}
//
//// Implementation of Intersects
//STDMETHODIMP COGCPoint::Intersects(IGeometry* other, VARIANT_BOOL * overlaps)
//{
//	return E_NOTIMPL;
//}

///////////////////////////////////////////////////////////////////////////////
//// ISpatialRelation2
//
//// Implementation of Relate
//STDMETHODIMP COGCPoint::Relate(IGeometry* other, 
//                  BSTR patternMatrix, VARIANT_BOOL* isRelated)
//{
//	return E_NOTIMPL;
//}

///////////////////////////////////////////////////////////////////////////////
//// IWks
//
//// Implementation of ExportToWKB
//STDMETHODIMP COGCPoint::ExportToWKB(VARIANT* wkb)
//{
//	return E_NOTIMPL;
//}
//
//// Implementation of ExportToWKT
//STDMETHODIMP COGCPoint::ExportToWKT(BSTR* wkt)
//{
//	return E_NOTIMPL;
//}
//
//// Implementation of ImportFromWKB
//STDMETHODIMP COGCPoint::ImportFromWKB(VARIANT wkb, ISpatialReference* spatialRef)
//{
//	return E_NOTIMPL;
//}
//
//// Implementation of ImportFromWKT
//STDMETHODIMP COGCPoint::ImportFromWKT(BSTR wkt, ISpatialReference* spatialRef)
//{
//	return E_NOTIMPL;
//}

#endif // defined(_INCLUDE_OGC_OBJECTS)
