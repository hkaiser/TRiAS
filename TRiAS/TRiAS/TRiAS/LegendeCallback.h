// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 28.03.2001 14:43:29 
//
// @doc
// @module LegendeCallback.h | Declaration of the <c CLegendeCallback> class

#if !defined(_LEGENDECALLBACK_H__08D67175_D53E_4F3C_A942_B691E2DD481C__INCLUDED_)
#define _LEGENDECALLBACK_H__08D67175_D53E_4F3C_A942_B691E2DD481C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <dtoolbar.h>

/////////////////////////////////////////////////////////////////////////////
// CLegendeCallback

// EEACBE52-13D7-4B25-B548-3F4C50F6F9B8
EXTERN_C const GUID __declspec(selectany) CLSID_LegendeCallback = 
	{ 0xEEACBE52, 0x13D7, 0x4B25, 0xB5, 0x48, 0x3F, 0x4C, 0x50, 0xF6, 0xF9, 0xB8 };

class ATL_NO_VTABLE CLegendeCallback : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLegendeCallback, &CLSID_LegendeCallback>,
	public ISupportErrorInfo,
	public IDispatchImpl<ITabWindowCallback, &IID_ITabWindowCallback, &LIBID_ToolBarLib,
				TOOLBAR_TYPELIB_VERSION_MAJOR, TOOLBAR_TYPELIB_VERSION_MINOR>
{
public:
// Construction
	CLegendeCallback() : m_pCmdTarget(NULL) {}
	~CLegendeCallback() {}

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
	BEGIN_COM_MAP(CLegendeCallback)
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

#endif // !defined(_LEGENDECALLBACK_H__08D67175_D53E_4F3C_A942_B691E2DD481C__INCLUDED_)
