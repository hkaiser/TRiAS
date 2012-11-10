// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.12.2000 22:22:26 
//
// @doc
// @module LoadXmlService.h | Declaration of the <c CLoadXmlService> class

#if !defined(_LOADXMLSERVICE_H__73ECC5A5_E9FF_43E1_933D_7D044F3BDF3E__INCLUDED_)
#define _LOADXMLSERVICE_H__73ECC5A5_E9FF_43E1_933D_7D044F3BDF3E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLoadXmlService
class ATL_NO_VTABLE CLoadXmlService : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLoadXmlService, &CLSID_LoadXmlService>,
	public CErrSupport<CLoadXmlService, &IID_ILoadXmlService>,
	public IDispatchImpl<ILoadXmlService, &IID_ILoadXmlService, &LIBID_TRiASCFG>
{
public:
	CLoadXmlService()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_LOADXMLSERVICE)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CLoadXmlService)
		COM_INTERFACE_ENTRY(ILoadXmlService)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ILoadXmlService
public:
	STDMETHOD(get_ResourceModule)(BSTR *pbstrModule);
	STDMETHOD(put_ResourceModule)(BSTR bstrModule);

	STDMETHOD(LoadXmlFromResource)(BSTR Rsc, IDispatch **ppIXmlDoc);
	STDMETHOD(LoadXmlFromFile)(BSTR Rsc, IDispatch **ppIXmlDoc);

protected:
	HRESULT LoadXml (BSTR bstrPath, BSTR bstrRsc, IXMLDOMDocument *pIXmlDoc);

private:
	CComBSTR m_bstrModule;
};

///////////////////////////////////////////////////////////////////////////////
// globale Funktionen
HRESULT EnsureXmlPath (BSTR *pbstrXmlPath);

#endif // !defined(_LOADXMLSERVICE_H__73ECC5A5_E9FF_43E1_933D_7D044F3BDF3E__INCLUDED_)
