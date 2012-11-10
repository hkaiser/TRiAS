// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 05.09.2002 12:45:54 
//
// @doc
// @module ConvertBnaCoords.h | Declaration of the <c CConvertBnaCoords> class

#if !defined(_CONVERTBNACOORDS_H__F746BF4C_4F6B_4BF2_BCCC_48144833AC37__INCLUDED_)
#define _CONVERTBNACOORDS_H__F746BF4C_4F6B_4BF2_BCCC_48144833AC37__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols
#include "..\TransformLineOfTextEngine.h"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TransformLineOfTextCallback)

/////////////////////////////////////////////////////////////////////////////
// CConvertBnaCoords
class ATL_NO_VTABLE CConvertBnaCoords : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CConvertBnaCoords, &CLSID_ConvertBnaCoords>,
	public ISupportErrorInfo,
	public IDispatchImpl<ITransformLineOfText, &IID_ITransformLineOfText, &LIBID_CvrtBna>
{
public:
	CConvertBnaCoords()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_CONVERTBNACOORDS)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CConvertBnaCoords)
		COM_INTERFACE_ENTRY(ITransformLineOfText)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	BEGIN_CATEGORY_MAP(CConvertBnaCoords)
		IMPLEMENTED_CATEGORY(CATID_TransformLineOfTextEngine)
	END_CATEGORY_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITransformLineOfText
public:
	STDMETHODIMP put_Callback(ITransformLineOfTextCallback *pVal);
	STDMETHODIMP get_Version(BSTR *pVal);

	STDMETHODIMP TransformLineOfText(BSTR bstrIn, BSTR *bstrOut);

private:
	WTransformLineOfTextCallback m_Callback;
};

#endif // !defined(_CONVERTBNACOORDS_H__F746BF4C_4F6B_4BF2_BCCC_48144833AC37__INCLUDED_)
