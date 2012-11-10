// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 02.11.2002 19:34:17 
//
// @doc
// @module TagMap.h | Declaration of the <c CTagMap> class

#if !defined(_TAGMAP_H__8A5ECC66_19E9_4831_A6EA_CC738DC909EC__INCLUDED_)
#define _TAGMAP_H__8A5ECC66_19E9_4831_A6EA_CC738DC909EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Com/BSTRHelpers.h>

///////////////////////////////////////////////////////////////////////////////
// Map, die die Tagdaten für ein Objekt verwaltet
class CTagData
{
	typedef map<CComBSTR, CComVariant, less<CComBSTR> > CTagMap;

public:
	CTagData() {}
	~CTagData() {}

	HRESULT AddTag (BSTR bstrName, VARIANT vData)
	{
		COM_TRY {
		CComBSTR bstr(bstrName);
		CTagMap::iterator it = m_mapTags.find(bstr);

			if (it != m_mapTags.end()) 
				m_mapTags.erase(it);
			m_mapTags.insert(CTagMap::value_type(bstr, CComVariant(vData)));

		} COM_CATCH;
		return S_OK;
	}
	HRESULT GetTag (BSTR bstrName, VARIANT *pvData)
	{
	HRESULT hr = E_FAIL;

		COM_TRY {
		CComBSTR bstr(bstrName);
		CTagMap::iterator it = m_mapTags.find(bstr);

			if (it != m_mapTags.end()) {
			CComVariant vData((*it).second);

				THROW_FAILED_HRESULT(vData.Detach(pvData));
				hr = S_OK;
			}

		} COM_CATCH;
		return hr;
	}
	HRESULT DeleteTag (BSTR bstrName)
	{
		COM_TRY {
		CComBSTR bstr(bstrName);
		CTagMap::iterator it = m_mapTags.find(bstr);

			if (it != m_mapTags.end()) 
				m_mapTags.erase(it);

		} COM_CATCH;
		return S_OK;
	}
	HRESULT DeleteAll()
	{
		COM_TRY {
			m_mapTags.clear();
		} COM_CATCH;
		return S_OK;
	}

private:
	CTagMap m_mapTags;
};

#endif // !defined(_TAGMAP_H__8A5ECC66_19E9_4831_A6EA_CC738DC909EC__INCLUDED_)
