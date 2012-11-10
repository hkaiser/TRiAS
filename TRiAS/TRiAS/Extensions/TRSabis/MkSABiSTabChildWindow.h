// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 01.06.2002 09:53:13 
//
// @doc
// @module MkSABiSTabChildWindow.h | Declaration of the <c CMkSABiSTabChildWindow> class

#if !defined(_MKSABISTABCHILDWINDOW_H__CFAC156D_E3BD_424E_BEBD_F669BBB9EE25__INCLUDED_)
#define _MKSABISTABCHILDWINDOW_H__CFAC156D_E3BD_424E_BEBD_F669BBB9EE25__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Com/MkBase.h>
#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMkSABiSTabChildWindow
class ATL_NO_VTABLE CMkSABiSTabChildWindow : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CMkSABiSTabChildWindow, &CLSID_MkSabisTabChildWindow>,
	public CComMoniker<&CLSID_MkSabisTabChildWindow>
{
public:
	CMkSABiSTabChildWindow() :
		m_fUse2ndOne(false)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CMkSABiSTabChildWindow)
	DECLARE_REGISTRY_RESOURCEID(IDR_MKSABISTABCHILDWINDOW)
	DECLARE_NOT_AGGREGATABLE(CMkSABiSTabChildWindow)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CMkSABiSTabChildWindow)
		COM_INTERFACE_ENTRY(IPersist)
		COM_INTERFACE_ENTRY(IPersistStream)
		COM_INTERFACE_ENTRY(IMoniker)
		COM_INTERFACE_ENTRY(IParseDisplayName)
		COM_INTERFACE_ENTRY(IROTData)
		COM_INTERFACE_ENTRY(IMarshal)
	END_COM_MAP()

// IMoniker
public:
    STDMETHOD(BindToObject) (IBindCtx *pbc, IMoniker *pmkToLeft, REFIID riidResult, void **ppvResult);
	STDMETHOD(GetDisplayName) (IBindCtx *pbc, IMoniker *pmkToLeft, LPOLESTR *ppszDisplayName);
	STDMETHOD(ParseDisplayName) (IBindCtx *pbc, IMoniker *pmkToLeft, LPOLESTR pszDisplayName, ULONG *pchEaten, IMoniker **ppmkOut);

protected:
// Display Name Helpers
	virtual const wchar_t *ProgID() { return L"TRiAS.SABiSTabChildWindow.1"; }
	virtual const wchar_t *VersionIndependentProgID() { return L"TRiAS.SABiSTabChildWindow"; }

private:
	CComBSTR m_bstrInit;
	bool m_fUse2ndOne;
};

#endif // !defined(_MKSABISTABCHILDWINDOW_H__CFAC156D_E3BD_424E_BEBD_F669BBB9EE25__INCLUDED_)
