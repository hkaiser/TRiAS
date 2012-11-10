// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 28.03.2001 15:04:28 
//
// @doc
// @module OverviewCallback.h | Declaration of the <c COverviewCallback> class

#if !defined(_OVERVIEWCALLBACK_H__F5CBD4AF_A91B_44B7_B1FF_DCFCEC5B9772__INCLUDED_)
#define _OVERVIEWCALLBACK_H__F5CBD4AF_A91B_44B7_B1FF_DCFCEC5B9772__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <dtoolbar.h>

/////////////////////////////////////////////////////////////////////////////
// COverviewCallback

// 4890BC47-BF13-4923-8B75-9440F15B6B16
EXTERN_C const GUID __declspec(selectany) CLSID_OverviewCallback = 
	{ 0x4890BC47, 0xBF13, 0x4923, 0x8B, 0x75, 0x94, 0x40, 0xF1, 0x5B, 0x6B, 0x16 };

class ATL_NO_VTABLE COverviewCallback : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<COverviewCallback, &CLSID_OverviewCallback>,
	public ISupportErrorInfo,
	public IDispatchImpl<ITabWindowCallback, &IID_ITabWindowCallback, &LIBID_ToolBarLib,
				TOOLBAR_TYPELIB_VERSION_MAJOR, TOOLBAR_TYPELIB_VERSION_MINOR>
{
public:
// Construction
	COverviewCallback() : m_pCmdTarget(NULL) {}
	~COverviewCallback() {}

// Initialisation
	void SetCmdTarget (Window *pCmdTarget)
	{
		_ASSERTE(NULL == m_pCmdTarget && NULL != pCmdTarget);	// nur einmal und dann richtig rufen
		m_pCmdTarget = pCmdTarget;
	}

// Operations
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_NO_REGISTRY()

// Interface map
	BEGIN_COM_MAP(COverviewCallback)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(ITabWindowCallback)
	END_COM_MAP()

// Implementation
protected:
// Attributes

// Operations

// Interfaces
public:
// ISupportsErrorInfo
	STDMETHODIMP InterfaceSupportsErrorInfo(REFIID riid);

// ITabWindowCallback
	STDMETHODIMP get_MayAddTabWindow(VARIANT_BOOL *pfMayAdd);
	STDMETHODIMP AddTabWindow();
	STDMETHODIMP DeleteTabWindow();

private:
	Window *m_pCmdTarget;
};

#endif // !defined(_OVERVIEWCALLBACK_H__F5CBD4AF_A91B_44B7_B1FF_DCFCEC5B9772__INCLUDED_)
