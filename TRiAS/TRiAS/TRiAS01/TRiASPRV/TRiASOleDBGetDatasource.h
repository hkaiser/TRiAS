// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 11.05.2001 09:49:43 
//
// @doc
// @module TRiASOleDBGetDatasource.h | Declaration of GetDataSource functions

#if !defined(_TRIASOLEDBGETDATASOURCE_H__0C04DBFB_0B65_4A61_B176_A19FF55F043F__INCLUDED_)
#define _TRIASOLEDBGETDATASOURCE_H__0C04DBFB_0B65_4A61_B176_A19FF55F043F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// liefert das übergeordnete DataSource-Objekt
template<typename T>
HRESULT GetDataSource (T *pThis, REFIID riid, void **ppIUnk)
{
T::ObjectLock cab(pThis);
CComPtr<IDBCreateCommand> spSession;
CComPtr<IRowset> spRowset;
	
HRESULT hr = pThis->GetSite(IID_IDBCreateCommand, (void **)&spSession);

CComPtr<IUnknown> spUnk;
	
	if (SUCCEEDED(hr)) { // The Rowset was created from an IOpenRowset::OpenRowset( )...
	// Get to DBPROP_INIT_DATASOURCE property
	CComPtr<IObjectWithSite> spCreator2;
		
		if (FAILED(hr = spSession->QueryInterface(&spCreator2))) {
			ATLTRACE2(atlTraceDBProvider,0,"FATAL ERROR: Cannot get to the IObjectWithSite from Session...\n");
			return hr;
		}
		if (FAILED(hr = spCreator2->GetSite(riid, (void **)&spUnk))) {
			ATLTRACE2(atlTraceDBProvider,0,"FATAL ERROR: Cannot get to the DataSource from Session...\n");
			return hr;
		}
	}
	else {
	// The Rowset was created from ICommand::Execute( )
	CComPtr<ICommand> spCommand;

		hr = pThis->GetSite(IID_ICommand, (void **)&spCommand);
		if(FAILED(hr)) {
			ATLTRACE2(atlTraceDBProvider,0,"FATAL ERROR: Cannot get to the ICommand of the Rowset...\n");
			return hr;
		}	
		
	CComPtr<IObjectWithSite> spCreator;
	
		if (FAILED(hr = spCommand->QueryInterface(&spCreator))) {
			ATLTRACE2(atlTraceDBProvider,0,"FATAL ERROR: Cannot get to the IObjectWithSite from ICommand...\n");
			return hr;
		}
		if (FAILED(hr = spCreator->GetSite(IID_IDBCreateCommand, (void **)&spSession))) {
			ATLTRACE2(atlTraceDBProvider,0,"FATAL ERROR: Cannot get to the IDBCreateCommand from ICommand...\n");
			return hr;
		}
		
	CComPtr<IObjectWithSite> spCreator2 = NULL;

		if (FAILED(hr = spSession->QueryInterface(&spCreator2))) {
			ATLTRACE2(atlTraceDBProvider,0,"FATAL ERROR: Cannot get to the IObjectWithSite from ICommand...\n");
			return E_FAIL;
		}
		if (FAILED(hr = spCreator2->GetSite(riid, (void **)&spUnk))) {
			ATLTRACE2(atlTraceDBProvider,0,"FATAL ERROR: Cannot get to the DataSource from ICommand...\n");
			return E_FAIL;
		}
	}
	if (NULL != ppIUnk)
		*ppIUnk = spUnk.Detach();
	return S_OK;
}

template<typename T, typename Interface>
HRESULT GetDataSource (T *pThis, Interface **ppIOut)
{
	return GetDataSource (pThis, __uuidof(Interface), (void **)ppIOut);
}

template<typename T>
HRESULT GetDataSourceObject (T *pThis, CTRiASOleDBSource **ppDataSource)
{
CComPtr<IDBCreateSession> spCreate;
HRESULT hr = E_FAIL;

	if (FAILED(hr = GetDataSource (pThis, &spCreate))) {
		ATLTRACE2(atlTraceDBProvider, 0, "FATAL ERROR: Cannot get to the DataSource from Recordset...\n");
		return hr;
	}
	return QueryImplementation(spCreate, ppDataSource);
}

#endif // !defined(_TRIASOLEDBGETDATASOURCE_H__0C04DBFB_0B65_4A61_B176_A19FF55F043F__INCLUDED_)
