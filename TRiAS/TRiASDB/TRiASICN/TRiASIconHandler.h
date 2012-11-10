// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/03/1998 08:09:48 PM
//
// @doc
// @module TRiASIconHandler.h | Declaration of the <c CTRiASIconHandler> class

#if !defined(_TRIASICONHANDLER_H__710B2C48_890F_11D2_9EFB_006008447800__INCLUDED_)
#define _TRIASICONHANDLER_H__710B2C48_890F_11D2_9EFB_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTRiASIconHandler
class ATL_NO_VTABLE CTRiASIconHandler : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASIconHandler, &CLSID_TRiASIconHandler>,
	public IExtractIcon,
	public IPersistFile
{
public:
	CTRiASIconHandler()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASICONHANDLER)
	DECLARE_NOT_AGGREGATABLE(CTRiASIconHandler)

	BEGIN_COM_MAP(CTRiASIconHandler)
		COM_INTERFACE_ENTRY(IExtractIcon)
		COM_INTERFACE_ENTRY(IPersistFile)
		COM_INTERFACE_ENTRY2(IPersist, IPersistFile)
	END_COM_MAP()

// IExtractIcon
public:
	STDMETHOD(GetIconLocation)(UINT uFlags, LPSTR szIconFile, UINT cchMax, int *piIndex, UINT *pwFlags); 
	STDMETHOD(Extract)(LPCSTR pszFile, UINT nIconIndex, HICON *phiconLarge, HICON *phiconSmall, UINT nIconSize); 
 
// IPersistFile methods 
	STDMETHOD(GetClassID)(LPCLSID lpClassID); 
	STDMETHOD(IsDirty)(); 
	STDMETHOD(Load)(LPCOLESTR lpszFileName, DWORD grfMode); 
	STDMETHOD(Save)(LPCOLESTR lpszFileName, BOOL fRemember); 
	STDMETHOD(SaveCompleted)(LPCOLESTR lpszFileName); 
	STDMETHOD(GetCurFile)(LPOLESTR FAR* lplpszFileName); 

private:
	CComBSTR m_bstrFileName;
};

#endif // !defined(_TRIASICONHANDLER_H__710B2C48_890F_11D2_9EFB_006008447800__INCLUDED_)
