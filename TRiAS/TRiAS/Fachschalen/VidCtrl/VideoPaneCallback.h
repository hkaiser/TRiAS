// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 27.06.2002 09:06:46 
//
// @doc
// @module VideoPaneCallback.h | Declaration of the <c CVideoPaneCallback> class

#if !defined(_VIDEOPANECALLBACK_H__2A2BAF0C_284D_49FF_BDB4_7BE6E9BA4CFA__INCLUDED_)
#define _VIDEOPANECALLBACK_H__2A2BAF0C_284D_49FF_BDB4_7BE6E9BA4CFA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <dtoolbar.h>

#include "resource.h"
#include "VidCtrlExt.h"

///////////////////////////////////////////////////////////////////////////////
// 
// C20126A1-DB5B-4674-A6C5-3FD300D97467
EXTERN_C const GUID __declspec(selectany) CLSID_VideoPaneCallback = 
	{ 0xC20126A1, 0xDB5B, 0x4674, 0xA6, 0xC5, 0x3F, 0xD3, 0x00, 0xD9, 0x74, 0x67 };

/////////////////////////////////////////////////////////////////////////////
// CVideoPaneCallback
class CVidCtrlExtension;

class ATL_NO_VTABLE CVideoPaneCallback : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CVideoPaneCallback, &CLSID_VideoPaneCallback>,
	public ISupportErrorInfo,
	public IDispatchImpl<ITabWindowCallback, &IID_ITabWindowCallback, &LIBID_ToolBarLib,
		TOOLBAR_TYPELIB_VERSION_MAJOR, TOOLBAR_TYPELIB_VERSION_MINOR>
{
public:
// Construction
	CVideoPaneCallback();
	~CVideoPaneCallback();

// Initialisation

// Operations
	DECLARE_NOT_AGGREGATABLE(CVideoPaneCallback)
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_NO_REGISTRY()

// Interface map
	BEGIN_COM_MAP(CVideoPaneCallback)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(ITabWindowCallback)
	END_COM_MAP()

// Initialisation
	void SetCmdTarget (CVidCtrlExtension *pCmdTarget)
	{
		_ASSERTE(NULL == m_pCmdTarget && NULL != pCmdTarget);	// nur einmal und dann richtig rufen
		m_pCmdTarget = pCmdTarget;
	}

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
	CVidCtrlExtension *m_pCmdTarget;
};

#endif // !defined(_VIDEOPANECALLBACK_H__2A2BAF0C_284D_49FF_BDB4_7BE6E9BA4CFA__INCLUDED_)
