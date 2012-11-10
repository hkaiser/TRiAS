// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 25.06.2001 21:39:29 
//
// @doc
// @module TRiASOleDBGetSession.h | Declaration of the <c CTRiASOleDBGetSession> class

#if !defined(_TRIASOLEDBGETSESSION_H__BBE3D00B_C906_460D_952A_573950AD9548__INCLUDED_)
#define _TRIASOLEDBGETSESSION_H__BBE3D00B_C906_460D_952A_573950AD9548__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Liefert zu einem Rowset gehörende Session
template<typename T>
HRESULT GetSessionObject (T *pRowSet, CTRiASOleDBSession **ppSession)
{
T::ObjectLock cab(pRowSet);
CComPtr<IDBCreateCommand> spSession = NULL;
	
HRESULT hr = pRowSet->GetSite(IID_IDBCreateCommand, (void **)&spSession);
CComPtr<IUnknown> spUnk;
	
	if (FAILED(hr)) {	// The Rowset was not created from an IOpenRowset::OpenRowset()...
	// The Rowset was created from ICommand::Execute()
	CComPtr<ICommand> spCommand = NULL;

		hr = pRowSet->GetSite(IID_ICommand, (void **)&spCommand);
		if(FAILED(hr)) {
			ATLTRACE2(atlTraceDBProvider,0,"FATAL ERROR: Cannot get to the ICommand of the Rowset...\n");
			return E_FAIL;
		}	
		
	CComPtr<IObjectWithSite> spCreator = NULL;
	
		if (FAILED(hr = spCommand->QueryInterface(IID_IObjectWithSite, (void **)&spCreator))) {
			ATLTRACE2(atlTraceDBProvider,0,"FATAL ERROR: Cannot get to the IObjectWithSite from ICommand...\n");
			return E_FAIL;
		}
		if (FAILED(hr = spCreator->GetSite(IID_IDBCreateCommand, (void **)&spSession))) {
			ATLTRACE2(atlTraceDBProvider,0,"FATAL ERROR: Cannot get to the IDBCreateCommand from ICommand...\n");
			return E_FAIL;
		}
	}
	return QueryImplementation(spSession, CLSID_TRiASOleDBSession, ppSession);
}

#endif // !defined(_TRIASOLEDBGETSESSION_H__BBE3D00B_C906_460D_952A_573950AD9548__INCLUDED_)
