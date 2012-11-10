// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 24.05.2000 09:30:34 
//
// @doc
// @module GeometryMoniker.h | Declaration of the <c CGeometryMoniker> class

#if !defined(_GEOMETRYMONIKER_H__32F5591A_AB58_4D4B_B42B_C9B5D93B8A0F__INCLUDED_)
#define _GEOMETRYMONIKER_H__32F5591A_AB58_4D4B_B42B_C9B5D93B8A0F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Atl/Ciid.h>
#include <Com/MkBase.h>

#include "resource.h"       // main symbols
#include "Strings.h"

/////////////////////////////////////////////////////////////////////////////
// CGeometryMoniker
class ATL_NO_VTABLE CGeometryMoniker : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CGeometryMoniker, &CLSID_GeometryMoniker>,
	public CComMoniker<&CLSID_GeometryMoniker>
{
public:
	CGeometryMoniker()
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CGeometryMoniker)
	DECLARE_REGISTRY_RESOURCEID(IDR_GEOMETRYMONIKER)
	DECLARE_NOT_AGGREGATABLE(CGeometryMoniker)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CGeometryMoniker)
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
	virtual const wchar_t *ProgID() { return g_cbMkGeom; }
	virtual const wchar_t *VersionIndependentProgID() { return g_cbMkGeom; }

private:
	CIID m_Guid;
	CComBSTR m_bstrInit;
};

#endif // !defined(_GEOMETRYMONIKER_H__32F5591A_AB58_4D4B_B42B_C9B5D93B8A0F__INCLUDED_)
