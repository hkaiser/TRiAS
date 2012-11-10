// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.03.2001 13:47:11 
//
// @doc
// @module ManageTabWindow.h | Declaration of the <c CManageTabWindows> class

#if !defined(_MANAGETABWINDOW_H__C239C131_DBD5_4B9B_BA2A_3EF5943E40EB__INCLUDED_)
#define _MANAGETABWINDOW_H__C239C131_DBD5_4B9B_BA2A_3EF5943E40EB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Atl/CieThis.h>

#include "fakemfc.h"       // main symbols
#include "DockingTabFrame.h"

/////////////////////////////////////////////////////////////////////////////
// B306A258-9632-4A2C-93F1-6BE65A176455
EXTERN_C const GUID __declspec(selectany) CLSID_ManageTabWindows = 
	{ 0xB306A258, 0x9632, 0x4A2C, 0x93, 0xF1, 0x6B, 0xE6, 0x5A, 0x17, 0x64, 0x55 };

/////////////////////////////////////////////////////////////////////////////
// CManageTabWindows
class ATL_NO_VTABLE CManageTabWindows : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CManageTabWindows, &CLSID_ManageTabWindows>,
	public ISupportErrorInfo,
	public IDispatchImpl<IManageTabWindows, &IID_IManageTabWindows, &LIBID_ToolBarLib, 
				TOOLBAR_TYPELIB_VERSION_MAJOR, TOOLBAR_TYPELIB_VERSION_MINOR>
{
public:
	CManageTabWindows() :
		m_pDockingTab(NULL)
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_MANAGETABWINDOW)
	DECLARE_NOT_AGGREGATABLE(CManageTabWindows)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CManageTabWindows)
		COM_INTERFACE_ENTRY(IManageTabWindows)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_THIS_EX(CLSID_ManageTabWindows)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

public:
	HRESULT InitDockingTab (CDockingTabFrame *pDockingTab)
	{
		m_pDockingTab = pDockingTab;
		return S_OK;
	}

// IManageTabWindows
public:
	STDMETHOD(get_Visible)(THIS_ VARIANT_BOOL *pfVisible);
	STDMETHOD(put_Visible)(THIS_ VARIANT_BOOL fVisible);
	STDMETHOD(get_Count)(THIS_ int *pfCount);
	STDMETHOD(get_ActiveTabWindow)(THIS_ INT_PTR *phHandle);
	STDMETHOD(get_ParentWindow)(THIS_ INT_PTR *phHandle);
	STDMETHOD(FindTabWindow) (THIS_ BSTR Name, INT_PTR *Handle);
	STDMETHOD(AddTabWindow) (THIS_ INT_PTR hWnd, BSTR Name, VARIANT vPict, INT_PTR *Handle);
	STDMETHOD(DeleteTabWindow) (THIS_ INT_PTR Handle);
	STDMETHOD(ActivateTabWindow) (THIS_ INT_PTR Handle);
	STDMETHOD(AddTabWindowDelayed) (THIS_ BSTR bstrName, ITabWindowCallback *pICallback);
	STDMETHOD(SetTabIcon) (THIS_ INT_PTR hHandle, VARIANT vIcon);
	STDMETHOD(RenameTabWindow) (THIS_ BSTR bstrOldName, BSTR bstrNewName);
	STDMETHOD(DeleteTabWindowDelayed) (THIS_ INT_PTR Handle);

private:
	CDockingTabFrame *m_pDockingTab;
};

#endif // !defined(_MANAGETABWINDOW_H__C239C131_DBD5_4B9B_BA2A_3EF5943E40EB__INCLUDED_)
