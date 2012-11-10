// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 11.07.2002 14:56:26 
//
// @doc
// @module ConvertGuid.h | Declaration of the <c CConvertGuid> class

#if !defined(_CONVERTGUID_H__B1880BB8_255D_4FE9_A6D9_04FA827E719B__INCLUDED_)
#define _CONVERTGUID_H__B1880BB8_255D_4FE9_A6D9_04FA827E719B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CConvertGuid
class ATL_NO_VTABLE CConvertGuid : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CConvertGuid, &CLSID_ConvertGuid>,
	public ISupportErrorInfo,
	public IDispatchImpl<IConvertGuid, &IID_IConvertGuid, &LIBID_ConvertGuid>
{
public:
	CConvertGuid()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_CONVERTGUID)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CConvertGuid)
		COM_INTERFACE_ENTRY(IConvertGuid)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IConvertGuid
public:
	STDMETHOD(Guid32StringToGuid)(/*[in]*/ BSTR bstrGuidStr, /*[out, retval]*/ BSTR *pbstrGuid);
	STDMETHOD(GuidToGuid32String)(/*[in]*/ BSTR bstrGuid, /*[out, retval]*/ BSTR *pbstrGuidStr);
	STDMETHOD(CreateGuid32String)(/*[out, retval]*/ BSTR *pbstrGuidStr);

private:
	HRESULT GuidToGuid32String (REFGUID rGuid, BSTR *pbstrGuid);
	HRESULT Guid32StringToGuid (BSTR bstrGuid, GUID *pGuid);
};

#endif // !defined(_CONVERTGUID_H__B1880BB8_255D_4FE9_A6D9_04FA827E719B__INCLUDED_)
