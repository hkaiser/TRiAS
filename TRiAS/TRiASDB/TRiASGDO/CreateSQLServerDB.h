// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 30.10.2002 11:36:56 
//
// @doc
// @module CreateSQLServerDB.h | Declaration of the <c CCreateSQLServerDB> class

#if !defined(_CREATESQLSERVERDB_H__E28098FA_D24A_469C_BD75_F69C2AF31CA5__INCLUDED_)
#define _CREATESQLSERVERDB_H__E28098FA_D24A_469C_BD75_F69C2AF31CA5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCreateSQLServerDB
class ATL_NO_VTABLE CCreateSQLServerDB : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCreateSQLServerDB, &CLSID_CreateSQLServerDB>,
	public ICreateDatabase
{
public:
	CCreateSQLServerDB()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_CREATESQLSERVERDB)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CCreateSQLServerDB)
		COM_INTERFACE_ENTRY(ICreateDatabase)
	END_COM_MAP()

// ICreateDatabase
public:
	STDMETHODIMP CreateDatabase(BSTR bstrName, BSTR bstrLocale, BSTR bstrSource);
};

#endif // !defined(_CREATESQLSERVERDB_H__E28098FA_D24A_469C_BD75_F69C2AF31CA5__INCLUDED_)
