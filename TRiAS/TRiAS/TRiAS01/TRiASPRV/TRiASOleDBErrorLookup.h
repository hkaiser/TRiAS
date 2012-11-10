// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 31.05.2001 20:26:44 
//
// @doc
// @module TRiASOleDBErrorLookup.h | Declaration of the <c CTRiASOleDBErrorLookup> class

#if !defined(_TRIASOLEDBERRORLOOKUP_H__966713B1_63ED_4807_A1FB_F54C4026BED0__INCLUDED_)
#define _TRIASOLEDBERRORLOOKUP_H__966713B1_63ED_4807_A1FB_F54C4026BED0__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASOleDBErrorLookup
class ATL_NO_VTABLE CTRiASOleDBErrorLookup : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASOleDBErrorLookup, &CLSID_TRiASOleDBErrorLookup>,
	public IErrorLookup
{
public:
// Construction
	CTRiASOleDBErrorLookup() {}
	~CTRiASOleDBErrorLookup() {}

// Initialisation
	HRESULT FinalConstruct()
	{
		return CComObjectRootEx<_ThreadModel>::FinalConstruct();
	}
	void FinalRelease()
	{
	}

// Operations
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASOLEDBERRORLOOKUP)
//	DECLARE_NOT_AGGREGATABLE(CTRiASOleDBErrorLookup)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

// Interface map
	BEGIN_COM_MAP(CTRiASOleDBErrorLookup)
		COM_INTERFACE_ENTRY(IErrorLookup)
	END_COM_MAP()

// Implementation
protected:
// Attributes

// Operations

// Interfaces
public:
// IErrorLookup
	STDMETHODIMP GetErrorDescription(HRESULT hrError, DWORD dwLookupID, DISPPARAMS *pdispparams, LCID lcid, BSTR *pbstrSource, BSTR *pbstrDescription);
	STDMETHODIMP GetHelpInfo(HRESULT hrError, DWORD dwLookupID, LCID lcid, BSTR *pbstrHelpFile, DWORD *pdwHelpContext);
	STDMETHODIMP ReleaseErrors(const DWORD dwDynamicErrorID);
};

#endif // !defined(_TRIASOLEDBERRORLOOKUP_H__966713B1_63ED_4807_A1FB_F54C4026BED0__INCLUDED_)
