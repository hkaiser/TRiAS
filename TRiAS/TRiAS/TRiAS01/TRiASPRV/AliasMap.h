// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.06.2001 09:48:17 
//
// @doc
// @module AliasMap.h | Declaration of the <c CAliasMap> class

#if !defined(_ALIASMAP_H__A695314C_A29B_44E4_8D4F_D15033C1ABE0__INCLUDED_)
#define _ALIASMAP_H__A695314C_A29B_44E4_8D4F_D15033C1ABE0__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if defined(_DEBUG)
#undef THIS_FILE
#define THIS_FILE __FILE__
#endif // defined(_DEBUG)

#include <ospace/std/map>

///////////////////////////////////////////////////////////////////////////////
// Map von ALiasNamen auf zugehörigen Rowset
class CAliasMap :
	public map<CComBSTR, CComBSTR, less<CComBSTR> > 
{
public:
	CAliasMap() : m_fIsInitialized(false) {}
	~CAliasMap() { Tidy(); }

	void Tidy() { m_fIsInitialized = false; clear(); }
	bool IsInitialized() { return m_fIsInitialized; }
	void SetInitialized(bool fFlag = true) { m_fIsInitialized = fFlag; }

	HRESULT AddAlias(UINT uiResId, BSTR bstrAlias)
	{
	CComBSTR bstrValue;

		bstrValue.LoadString(uiResId);
		_ASSERTE(bstrValue.Length() > 0);
		return AddAlias(bstrValue, bstrAlias);
	}
	HRESULT AddAlias(LPCOLESTR bstrValue, BSTR bstrAlias)
	{
		if (NULL == bstrAlias || 0 == SysStringLen(bstrAlias))
			return S_FALSE;		// no alias, no fun

	CComBSTR bstr(RemoveQuotes(bstrAlias));
	iterator it = find(bstr);

		if (it != end())		// bereits verwendet
			return DB_E_ERRORSINCOMMAND;

		COM_TRY {
			insert(CAliasMap::value_type(bstr, bstrValue));
		} COM_CATCH;
		return S_OK;
	}

	CComBSTR ResolveAlias(BSTR bstrAlias)
	{
		_ASSERTE(IsInitialized());

	CComBSTR bstrTable;

		if (S_OK == GetTableName(bstrAlias, &bstrTable))
			return bstrTable;
		return bstrAlias;
	}
	bool ResolveName (BSTR bstrAlias, BSTR *pbstrName)
	{
		for (iterator it = begin(); it != end(); ++it) {
			if ((*it).second == (LPCOLESTR)bstrAlias) {
			CComBSTR bstr ((*it).first);

				*pbstrName = bstr.Detach();
				return true;
			}
		}
		return false;
	}

	HRESULT InitTableAliases(ISelectStmt *pISelect)
	{
		_ASSERTE(!m_fIsInitialized);

	CComPtr<ITableIdentList> TableIdentList;

		RETURN_ERROR(pISelect -> get_TableIdentList(&TableIdentList));
		if (TableIdentList == NULL) return DB_E_ERRORSINCOMMAND;

	CComPtr<IUnknown> UnkEnum;
	CComVariant v;

		RETURN_ERROR(TableIdentList -> get__NewEnum(&UnkEnum));

	CComQIPtr<IEnumVARIANT> Tables(UnkEnum);

		_ASSERTE(Tables != NULL);
		for (Tables -> Reset(); S_OK == Tables -> Next(1, &v, NULL); /**/) {
			_ASSERTE(V_ISDISPATCH(&v));

		CComQIPtr<ITableIdent> Table (V_DISPATCH(&v));
		CComBSTR bstrTable, bstrAlias;
		INT_PTR lIdent = NULL;

			if (Table == NULL) return E_UNEXPECTED;

			RETURN_ERROR(Table -> get_Name(&bstrTable));
			bstrTable = RemoveQuotes(bstrTable);

			if (S_OK == Table -> get_Alias(&bstrAlias)) {
				bstrAlias = RemoveQuotes(bstrAlias);
				ATLTRY(insert(CAliasMap::value_type(bstrAlias, bstrTable)));
			}
		}
		m_fIsInitialized = true;
		return S_OK;
	}

protected:
	HRESULT GetTableName(BSTR bstrAlias, BSTR *pbstrTable)
	{
	CComBSTR bstr(RemoveQuotes(bstrAlias));
	iterator it = find(bstr);

		if (it == end())
			return S_FALSE;

		*pbstrTable = CComBSTR((*it).second).Detach();
		return S_OK;
	}

private:
	bool m_fIsInitialized;
};

#endif // !defined(_ALIASMAP_H__A695314C_A29B_44E4_8D4F_D15033C1ABE0__INCLUDED_)
