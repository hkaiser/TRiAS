// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 01.11.2002 19:22:17 
//
// @doc
// @module MkVBGeoComponent.h | Declaration of the <c CMkVBGeoComponent> class

#if !defined(_MKVBGEOCOMPONENT_H__A2A0438B_A423_430E_84FE_D17E10ED74E7__INCLUDED_)
#define _MKVBGEOCOMPONENT_H__A2A0438B_A423_430E_84FE_D17E10ED74E7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Com/MkBase.h>
#include "trias03.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMkVBGeoComponent
class ATL_NO_VTABLE CMkVBGeoComponent : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CMkVBGeoComponent, &CLSID_MkVBGeoComponent>,
	public CComMoniker<&CLSID_MkVBGeoComponent>
{
public:
	CMkVBGeoComponent()
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CMkVBGeoComponent)

	DECLARE_REGISTRY_RESOURCEID(IDR_MKVBGEOCOMPONENT)
	DECLARE_NOT_AGGREGATABLE(CMkVBGeoComponent)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CMkVBGeoComponent)
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
	virtual const wchar_t *ProgID() { return L"TRiAS.MkVBGeoComponent.1"; }
	virtual const wchar_t *VersionIndependentProgID() { return L"TRiAS.MkVBGeoComponent"; }

private:
	CComBSTR m_bstrInit;
};

#endif // !defined(_MKVBGEOCOMPONENT_H__A2A0438B_A423_430E_84FE_D17E10ED74E7__INCLUDED_)
