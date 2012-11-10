// $Header: $
// Copyright© 2003 Hartmut Kaiser, All rights reserved
// Created: 19.05.2003 12:31:57 
//
// @doc
// @module ConvertAscCoords.h | Declaration of the <c CConvertAscCoords> class

#if !defined(_CONVERTASCCOORDS_H__C21B1813_30B1_46BF_992E_9E437540B7AD__INCLUDED_)
#define _CONVERTASCCOORDS_H__C21B1813_30B1_46BF_992E_9E437540B7AD__INCLUDED_

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
// CConvertAscCoords
class ATL_NO_VTABLE CConvertAscCoords : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CConvertAscCoords, &CLSID_ConvertAscCoords>,
	public ISupportErrorInfo,
	public IDispatchImpl<ITransformLineOfText, &IID_ITransformLineOfText, &LIBID_CvrtAsc>
{
public:
	CConvertAscCoords()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_CONVERTASCCOORDS)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CConvertAscCoords)
		COM_INTERFACE_ENTRY(ITransformLineOfText)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	BEGIN_CATEGORY_MAP(CConvertAscCoords)
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

#endif // !defined(_CONVERTASCCOORDS_H__C21B1813_30B1_46BF_992E_9E437540B7AD__INCLUDED_)
