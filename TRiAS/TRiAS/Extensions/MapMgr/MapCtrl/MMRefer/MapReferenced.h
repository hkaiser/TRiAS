// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 18.03.2002 09:16:02 
//
// @doc
// @module MapReferenced.h | Declaration of the <c CMapReferenced> class

#if !defined(_MAPREFERENCED_H__7658B5B0_D63A_469A_BD35_F68DE4AE2B66__INCLUDED_)
#define _MAPREFERENCED_H__7658B5B0_D63A_469A_BD35_F68DE4AE2B66__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMapReferenced
class ATL_NO_VTABLE CMapReferenced
	: public CComObjectRootEx<CComSingleThreadModel>
	, public CComCoClass<CMapReferenced, &CLSID_MapReferenced>
	, public IConnectionPointContainerImpl<CMapReferenced>
	, public IDispatchImpl<IMapReferenced, &IID_IMapReferenced, &LIBID_MMREFERLib>
	, public ITopoMapImpl
{
public:
	CMapReferenced() {}

	HRESULT FinalConstruct();
	void FinalRelease();

	DECLARE_REGISTRY_RESOURCEID(IDR_MAPREFERENCED)

	BEGIN_COM_MAP(CMapReferenced)
		COM_INTERFACE_ENTRY(IMapReferenced)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ITopoMap)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	END_COM_MAP()
	BEGIN_CONNECTION_POINT_MAP(CMapReferenced)
	END_CONNECTION_POINT_MAP()

public:
// IMapImport
	STDMETHOD(GetDisplayName)(/*[out]*/ BSTR* strDisplay);
	STDMETHOD(NeedFixPoints)(/*[in,out]*/ long* pNeedPoints );
};

#endif // !defined(_MAPREFERENCED_H__7658B5B0_D63A_469A_BD35_F68DE4AE2B66__INCLUDED_)
