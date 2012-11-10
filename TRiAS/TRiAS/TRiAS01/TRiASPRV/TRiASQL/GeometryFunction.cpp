// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 10.08.2001 22:19:00 
//
// @doc
// @module GeometryFunction.cpp | Definition of the <c CGeometryFunction> class

#include "stdafx.h"
#include "GeometryFunction.h"

#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeometryFunction
CGeometryFunction::CGeometryFunction() :
	m_rgGeomFunction(GEOMETRY_FUNCTION_UNKNOWN)
{
}

CString CGeometryFunction::GetAsString() 
{ 
	switch (m_rgGeomFunction) {
	case GEOMETRY_FUNCTION_UNKNOWN:
		break;

	case GEOMETRY_FUNCTION_ASTEXT:
		return "ASTEXT";

	case GEOMETRY_FUNCTION_ASBINARY:
		return "ASBINARY";

	case GEOMETRY_FUNCTION_DIMENSION:
		return "DIMENSION";

	case GEOMETRY_FUNCTION_GEOMETRYTYPE:
		return "GEOMETRYTYPE";

	case GEOMETRY_FUNCTION_SRID:
		return "SRID";

	case GEOMETRY_FUNCTION_ISEMPTY:
		return "ISEMPTY";
	}

	_ASSERTE(FALSE);
	return "!!!ERROR!!!"; 
}

void CGeometryFunction::SetGeomFunction (GEOMETRY_FUNCTION rgGeomFunction)
{
	m_rgGeomFunction = rgGeomFunction;
}

STDMETHODIMP CGeometryFunction::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IGeometryFunction
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CGeometryFunction::get_GeometryFunction(GEOMETRY_FUNCTION *pVal)
{
	*pVal = m_rgGeomFunction;
	return S_OK;
}
