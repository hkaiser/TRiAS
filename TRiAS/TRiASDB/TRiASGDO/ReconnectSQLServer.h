// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 24.10.2002 16:06:48 
//
// @doc
// @module ReconnectSQLServer.h | Declaration of the <c CReconnectSQLServer> class

#if !defined(_RECONNECTSQLSERVER_H__A155D9B1_8B90_4051_8BDA_5BD62D1FFB1D__INCLUDED_)
#define _RECONNECTSQLSERVER_H__A155D9B1_8B90_4051_8BDA_5BD62D1FFB1D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CReconnectSQLServer
class ATL_NO_VTABLE CReconnectSQLServer : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CReconnectSQLServer, &CLSID_ReconnectSQLServer>,
	public IReconnectDialog
{
public:
	CReconnectSQLServer()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_RECONNECTSQLSERVER)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CReconnectSQLServer)
		COM_INTERFACE_ENTRY(IReconnectDialog)
	END_COM_MAP()

// IReconnectDialog
public:
	STDMETHODIMP GetReconnectParams(INT_PTR hWnd, BSTR Name, BSTR Desc, 
		BSTR ConnectString, BSTR Path, BSTR *NewName, BSTR *NewConnectString,
		BSTR *NewPath);
};

#endif // !defined(_RECONNECTSQLSERVER_H__A155D9B1_8B90_4051_8BDA_5BD62D1FFB1D__INCLUDED_)
