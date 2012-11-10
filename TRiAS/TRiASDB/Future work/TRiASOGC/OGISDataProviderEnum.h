// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 30.04.2001 14:27:49 
//
// @doc
// @module OGISDataProviderEnum.h | Declaration of the <c COGISDataProviderEnum> class

#if !defined(_OGISDATAPROVIDERENUM_H__A9892939_877D_47D2_8A09_9BBF474568CA__INCLUDED_)
#define _OGISDATAPROVIDERENUM_H__A9892939_877D_47D2_8A09_9BBF474568CA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <AtlDbCli.h>
#include <Atl/Ciid.h>

///////////////////////////////////////////////////////////////////////////////
// RootEnumerator, der zusätzlich unterscheiden kann, welcher provider OGC 
// kompatibel ist
class COGISDataProviderEnum : 
	public CEnumerator
{
public:
    bool IsOGISProvider()
	{
	CRegKey regKey;

		USES_CONVERSION;
		if (ERROR_SUCCESS == regKey.Open(HKEY_CLASSES_ROOT, "CLSID") &&
			ERROR_SUCCESS == regKey.Open(regKey, OLE2A(m_szParseName)) && // CATID_OGISDataProvider
			ERROR_SUCCESS == regKey.Open(regKey, "Implemented Categories") &&
			ERROR_SUCCESS == regKey.Open(regKey, "{A0690A28-FAF5-11D1-BAF5-080036DB0B03}"))
		{
			return true;
		}
		return false;
	}

	HRESULT GetProgId(BSTR *pbstrProgId)
	{
		if (NULL == pbstrProgId)
			return E_POINTER;

	CIID Guid (m_szParseName, CIID::INITCIID_InitFromGuid);
	CComBSTR bstr (Guid.ProgID().c_str());

		*pbstrProgId = bstr.Detach();
		return S_OK;
	}
};

#endif // !defined(_OGISDATAPROVIDERENUM_H__A9892939_877D_47D2_8A09_9BBF474568CA__INCLUDED_)
