// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 02.05.2002 19:48:35 
//
// @doc
// @module DummyUIOwner.h | Declaration of the <c CDummyUIOwner> class

#if !defined(_DUMMYUIOWNER_H__9BA15921_2916_4F4F_B3CC_735122D654D0__INCLUDED_)
#define _DUMMYUIOWNER_H__9BA15921_2916_4F4F_B3CC_735122D654D0__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#import "tlb/toolbar.tlb" raw_interfaces_only raw_dispinterfaces no_namespace named_guids

#include <Com/ComBool.h>
#include "resource.h"       // main symbols

///////////////////////////////////////////////////////////////////////////////
// spezielle SmartInterfaces
DefineSmartInterface2(DToolBarUIOwner, IID_DToolBarUIOwner);

/////////////////////////////////////////////////////////////////////////////
// CDummyUIOwner
class ATL_NO_VTABLE CDummyUIOwner : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDummyUIOwner, &CLSID_DummyUIOwner>,
	public ISupportErrorInfo,
	public IDispatchImpl<IDummyUIOwner, &IID_IDummyUIOwner, &LIBID_TRSABiS>,
	public IDispatchImpl<DToolBarUIOwner, &IID_DToolBarUIOwner, &LIBID_ToolBarLib>
{
public:
	CDummyUIOwner()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_DUMMYUIOWNER)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CDummyUIOwner)
		COM_INTERFACE_ENTRY(IDummyUIOwner)
		COM_INTERFACE_ENTRY2(IDispatch, IDummyUIOwner)
		COM_INTERFACE_ENTRY(DToolBarUIOwner)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IDummyUIOwner
public:
	STDMETHOD(putref_TargetUIOwner)(/*[in]*/ IDispatch *newVal);
	STDMETHOD(get_DebugMode)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_DebugMode)(/*[in]*/ VARIANT_BOOL newVal);

// DToolBarUIOwner
	STDMETHODIMP SetToolBarUIOwnerSite(int uiID, DControlToolBar *pIToolBar);
	STDMETHODIMP UpdateUI(DTRiASCmdUI *pICmdUI);
	STDMETHODIMP GetDescription(int uiID, BSTR *pbstrDesc);
	STDMETHODIMP FireCommand(int uiID, int nCode);

private:
	WDToolBarUIOwner m_TargetUIOwner;
	CComBool m_fDebugMode;
};

#endif // !defined(_DUMMYUIOWNER_H__9BA15921_2916_4F4F_B3CC_735122D654D0__INCLUDED_)
