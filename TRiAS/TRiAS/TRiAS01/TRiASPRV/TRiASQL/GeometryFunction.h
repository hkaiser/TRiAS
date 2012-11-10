// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 10.08.2001 22:21:22 
//
// @doc
// @module GeometryFunction.h | Declaration of the <c CGeometryFunction> class

#if !defined(_GEOMETRYFUNCTION_H__1FC50F49_C297_4233_A3C4_4E316D0A3D21__INCLUDED_)
#define _GEOMETRYFUNCTION_H__1FC50F49_C297_4233_A3C4_4E316D0A3D21__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGeometryFunction
class ATL_NO_VTABLE CGeometryFunction : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CGeometryFunction, &CLSID_GeometryFunction>,
	public ISupportErrorInfo,
	public IDispatchImpl<IGeometryFunction, &IID_IGeometryFunction, &LIBID_TRiASOleDB, 
		TYPELIB_TRiASOLEDB_VERSION_MAJOR, TYPELIB_TRiASOLEDB_VERSION_MINOR>
{
public:
	CGeometryFunction();
	
	CString GetAsString();
	void SetGeomFunction(GEOMETRY_FUNCTION rgGeomFunction);

protected:
	GEOMETRY_FUNCTION m_rgGeomFunction;

public:
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CGeometryFunction)
		COM_INTERFACE_ENTRY(IExpressionItem)
		COM_INTERFACE_ENTRY(IGeometryFunction)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IExpressionItem
	STDMETHOD(get_AsString)(BSTR *bstrRet)
	{
	CComBSTR bstrRet2 = GetAsString();
	
		*bstrRet = bstrRet2.Detach();
		return S_OK;
	}
	STDMETHOD(get_ItemType)(EXPRESSIONITEM_TYPE *pVal)
	{
		*pVal = EXPRESSIONITEM_TYPE_GEOMETRYFUNCTION;
		return S_OK;
	}

// IGeometryFunction
public:
	STDMETHOD(get_GeometryFunction)(/*[out, retval]*/ GEOMETRY_FUNCTION *pVal);
};

#endif // !defined(_GEOMETRYFUNCTION_H__1FC50F49_C297_4233_A3C4_4E316D0A3D21__INCLUDED_)
