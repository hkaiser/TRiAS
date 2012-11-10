// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 02.06.2002 08:26:47 
//
// @doc
// @module SABiSTabChildWindowCallback.h | Declaration of the <c CSABiSTabChildWindowCallback> class

#if !defined(_SABISTABCHILDWINDOWCALLBACK_H__3FA37DB2_2520_4C8A_9E7C_0646E5BCABC9__INCLUDED_)
#define _SABISTABCHILDWINDOWCALLBACK_H__3FA37DB2_2520_4C8A_9E7C_0646E5BCABC9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols
#import "tlb/toolbar.tlb" raw_interfaces_only raw_dispinterfaces no_namespace named_guids

/////////////////////////////////////////////////////////////////////////////
// CSABiSTabChildWindowCallback
class CSabisTabChildWindow;		// forward decl only

class ATL_NO_VTABLE CSABiSTabChildWindowCallback : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSABiSTabChildWindowCallback, &CLSID_SabisTabChildWindowCallback>,
	public IDispatchImpl<ITabWindowCallback, &IID_ITabWindowCallback, &LIBID_ToolBarLib,
		TYPELIB_TOOLBAR_VERSION_MAJOR, TYPELIB_TOOLBAR_VERSION_MINOR>
{
public:
	CSABiSTabChildWindowCallback() :
		m_fIsDeleting(FALSE)
	{
	}
	~CSABiSTabChildWindowCallback()
	{
	}

//	DECLARE_REGISTRY_RESOURCEID(IDR_SABISTABCHILDWINDOWCALLBACK)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CSABiSTabChildWindowCallback)
		COM_INTERFACE_ENTRY(ITabWindowCallback)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

	HRESULT InitTarget (CSabisTabChildWindow *pParent);

public:
// ITabWindowCallback
	STDMETHODIMP get_MayAddTabWindow(VARIANT_BOOL *pfMayAdd);
	STDMETHODIMP AddTabWindow();
	STDMETHODIMP DeleteTabWindow();

private:
	CSabisTabChildWindow *m_pParent;
	BOOL m_fIsDeleting;
};

#endif // !defined(_SABISTABCHILDWINDOWCALLBACK_H__3FA37DB2_2520_4C8A_9E7C_0646E5BCABC9__INCLUDED_)
