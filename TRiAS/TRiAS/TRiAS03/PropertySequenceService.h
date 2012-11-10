// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 08.03.2001 10:42:48 
//
// @doc
// @module PropertySequenceService.h | Declaration of the <c CPropertySequenceService> class

#if !defined(_PROPERTYSEQUENCESERVICE_H__13521472_BF21_4A6B_970C_CDE3856981AA__INCLUDED_)
#define _PROPERTYSEQUENCESERVICE_H__13521472_BF21_4A6B_970C_CDE3856981AA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "trias03.h"       // main symbols

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(DataObject);

/////////////////////////////////////////////////////////////////////////////
// CPropertySequenceService
class ATL_NO_VTABLE CPropertySequenceService : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPropertySequenceService, &CLSID_PropertySequenceService>,
	public CErrSupport<CPropertySequenceService, &IID_IPropertySequenceService>,
	public IDispatchImpl<IPropertySequenceService, &IID_IPropertySequenceService, &LIBID_TRiASHelperLib,
		TYPELIB_HELPER_VERSION_MAJOR, TYPELIB_HELPER_VERSION_MINOR>
{
public:
	CPropertySequenceService()
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CPropertySequenceService)

	DECLARE_REGISTRY_RESOURCEID(IDR_PROPERTYSEQUENCESERVICE)
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	
	BEGIN_COM_MAP(CPropertySequenceService)
		COM_INTERFACE_ENTRY(IPropertySequenceService)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

// IPropertySequenceService
public:
	STDMETHODIMP RunActionSequence (INT_PTR hWnd, BSTR bstrRsc, BSTR bstrDesc, 
		BSTR bstrSaveAs, IProgressIndicator2 *pIStatus, IDataObject *pIInData, 
		VARIANT_BOOL fInitNew, IDataObject **ppIOutData);
	STDMETHODIMP RunActionSequenceFromFile (INT_PTR hWnd, BSTR bstrFile, BSTR bstrDesc, 
		BSTR bstrSaveAs, IProgressIndicator2 *pIStatus, IDataObject *pIInData, 
		VARIANT_BOOL fInitNew, IDataObject **ppIOutData);

	STDMETHOD(get_ResourceModule)(BSTR *pbstrModule);
	STDMETHOD(put_ResourceModule)(BSTR bstrModule);
	STDMETHODIMP putref_ContextData(ITRiASDataObject *CtxData);
	STDMETHODIMP get_ContextData(ITRiASDataObject **CtxData);

private:
	CComBSTR m_bstrModule;
	WDataObject m_CtxData;
};

#endif // !defined(_PROPERTYSEQUENCESERVICE_H__13521472_BF21_4A6B_970C_CDE3856981AA__INCLUDED_)
