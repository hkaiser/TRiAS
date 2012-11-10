// TRiASMDSMap.cpp : Implementation of CTRiASMDSMap

#include "stdafx.h"

#include <Com/ComBool.h>

#include "TRiASMDSImpl.h"
#include "TRiASMDSMap.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTRiASMDSMap

class FillBSTREnum 
{
	WEnumBSTR&	m_e;
public:
	FillBSTREnum(WEnumBSTR& e) : m_e(e) { }
	void operator()(const pair < CComBSTR, MDSValue >& p) 
	{
		m_e->AddItem(CComBSTR(p.first).Detach());
	}
};

IMPLEMENT_DEBUG_FUNCENTRY_1(CTRiASMDSMap, _NewEnum, IUnknown **, ppIEnum)
{
	CHECKINPOINTER(ppIEnum);
	COM_TRY {
	ObjectLock	l(this);
	WEnumBSTR enumOfStrings (new NEnumBSTR);

		enumOfStrings->Release();
		for_each(m_mapOfKeys.begin(), m_mapOfKeys.end(), FillBSTREnum(enumOfStrings));
		MakeEnumVARIANT(enumOfStrings, GetUnknown(), ppIEnum);

	} COM_CATCH;
	return S_OK;
}


IMPLEMENT_DEBUG_FUNCENTRY_5(CTRiASMDSMap, SetAt,
		/*[in]*/ BSTR, strKey,
		/*[in]*/ BSTR, strName,
		/*[in]*/ BSTR, strValue,
		/*[in, optional, defaultvalue(NULL)]*/ BSTR, strDescription,
		/*[in, optional, defaultvalue(vtMissing)]*/ VARIANT, vData
)
{
	COM_TRY {
	// Events vorher
	CComBool fVal;
	HRESULT hr;

		ERROR_FAILED_HRESULT(hr = Fire_ModifyingValue (strKey, &fVal), hr); 
		if (fVal)
			return S_FALSE;
		ERROR_FAILED_HRESULT(hr = Fire_ValueToModify (strKey), hr);

	ObjectLock	l(this);
	int erased = m_mapOfKeys.erase(strKey);
	pair<MapOfKeys::iterator, bool> p = m_mapOfKeys.insert(strKey, MDSValue(strName, strValue, strDescription, vData));

		ERROR_EXPR_TRUE(m_mapOfKeys.end() == p.first, E_OUTOFMEMORY);
		SetDirty();

	// Event hinterher
		ERROR_FAILED_HRESULT(hr = Fire_ValueModified (strKey), hr);

	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_5(CTRiASMDSMap, GetAt,
		/*[in]*/ BSTR, strKey,
		/*[out]*/ BSTR*, pbstrName,
		/*[out]*/ BSTR*, pbstrValue,
		/*[out]*/ BSTR*, pbstrDescription,
		/*[out]*/ VARIANT*, pvData
)
{
	COM_TRY {
	ObjectLock	l(this);
	MapOfKeys::iterator i = m_mapOfKeys.find(strKey);

//		ERROR_EXPR_TRUE( m_mapOfKeys.end() == i, MAP_E_ELEMENTNOTFOUND );
		if (m_mapOfKeys.end() == i)
			return MAP_E_ELEMENTNOTFOUND;

		if (pbstrName)
			*pbstrName = ::SysAllocString((*i).second.m_strName);
		if (pbstrValue)
			*pbstrValue = ::SysAllocString((*i).second.m_strShort);
		if (pbstrDescription)
			*pbstrDescription = ::SysAllocString((*i).second.m_strLong);
		if (pvData)
			CComVariant((*i).second.m_vData).Detach(pvData);

	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CTRiASMDSMap, RemoveAt, /*[in]*/ BSTR, strKey)
{
size_t iRemoved = 0;

	COM_TRY {
	// Events vorher
	CComBool fVal;
	HRESULT hr;

		ERROR_FAILED_HRESULT(hr = Fire_ModifyingValue (strKey, &fVal), hr); 
		if (fVal)
			return S_FALSE;
		ERROR_FAILED_HRESULT(hr = Fire_ValueToModify (strKey), hr);

	// eigentliche Aktion
	ObjectLock l(this);

		iRemoved = m_mapOfKeys.erase(strKey);
		SetDirty();

	// Event hinterher
		ERROR_FAILED_HRESULT(hr = Fire_ValueModified (strKey), hr);

	} COM_CATCH;
	return (1 == iRemoved) ? S_OK : S_FALSE;
}

typedef const CComBSTR&(*prep_string)(const CComBSTR& s1, CComBSTR& strHelp);
typedef CComBSTR&(*GetData)(const MapOfKeys::iterator& it);

const CComBSTR& prep_makelower(const CComBSTR& s1, CComBSTR& strHelp) 
{
	strHelp = s1;
	if (strHelp.m_str)
		_wcslwr(strHelp.m_str);
	return strHelp;
}

const CComBSTR& prep_letraw(const CComBSTR& s1, CComBSTR& strHelp) 
{
	return s1;
}

CComBSTR& GetIteratorKey(const MapOfKeys::iterator& it, CComBSTR &strHelp) 
{
	return (*it).first;
}
CComBSTR& GetIteratorShort(const MapOfKeys::iterator& it, CComBSTR &strHelp) 
{
	return (*it).second.m_strShort;
}
CComBSTR& GetIteratorName(const MapOfKeys::iterator& it, CComBSTR &strHelp) 
{
	return (*it).second.m_strName;
}

CComBSTR& GetIteratorNameLong(const MapOfKeys::iterator& it, CComBSTR &strHelp) 
{
	strHelp = (*it).second.m_strName;
	strHelp.AppendBSTR((*it).second.m_strLong);
	return strHelp;
}

HRESULT CTRiASMDSMap::SearchItem(const BSTR& bstrSearch, GetIteratorData itData, long lSearchMode, WTRiASMDSStringColl& coll) 
{
CComBSTR strSearch, strHelp, strHelp2;
prep_string	pf;

	strSearch = bstrSearch;
	if (mdsSM_NoCase & lSearchMode) {
		pf = prep_makelower;
		_wcslwr(strSearch.m_str);
	} else {
		pf = prep_letraw;
	}

HRESULT	hresFound = S_FALSE;

	if (mdsSM_Compare & lSearchMode)
	{
		for (MapOfKeys::iterator i = m_mapOfKeys.begin(); m_mapOfKeys.end() != i; i++)
		{
			if (0 == wcscmp (pf(itData(i, strHelp2), strHelp), strSearch))
			{
				coll->Add((*i).first);
				hresFound = S_OK;
			}
		}
	}
	else if (mdsSM_RegExp & lSearchMode) {
		USES_CONVERSION;
		os_regexp	rex(W2A(strSearch));
		int	nMatch;
		LPCTSTR	psz;
		for (MapOfKeys::iterator i = m_mapOfKeys.begin(); m_mapOfKeys.end() != i; i++)
		{
			{ psz = W2A(pf(itData(i, strHelp2), strHelp)); }
			nMatch = rex.match(psz);
			if (-1 != nMatch)
			{
				RETURN_FAILED_HRESULT(coll->Add((*i).first));
				hresFound = S_OK;
			}
		}
	}
	return hresFound;
}

IMPLEMENT_DEBUG_FUNCENTRY_3(CTRiASMDSMap, Search
		, /*[in]*/ BSTR, bstrSearch
		, /*[in, defaultvalue(mdsSM_Compare)]*/ long, lSearchMode
		, /*[in, out]*/ ITRiASMDSStringColl**, pValues
) 
{
	CHECKINPOINTER(pValues);

HRESULT	hrFound = S_FALSE;
	
	COM_TRY {
	ObjectLock l(this);
	HRESULT	hr;
	WTRiASMDSStringColl	coll(CLSID_TRiASMDSStringColl);

		ERROR_EXPR_TRUE(!(lSearchMode & mdsSM_ItemMask), MAP_E_INVALIDSEARCHITEM);
		ERROR_EXPR_TRUE(!(lSearchMode & mdsSM_ModeMask), MAP_E_INVALIDSEARCHMODE);

		switch (lSearchMode & mdsSM_ItemMask) {
		case mdsSM_SrchKey:
			{
				ERROR_FAILED_HRESULT(hr = SearchItem(bstrSearch, GetIteratorKey, lSearchMode, coll), E_FAIL);
				hrFound = S_OK == hr ? S_OK : S_FALSE;
			}
			break;

		case mdsSM_SrchShort:
			{
				ERROR_FAILED_HRESULT(hr = SearchItem(bstrSearch, GetIteratorShort, lSearchMode, coll), E_FAIL);
				hrFound = S_OK == hr ? S_OK : S_FALSE;
			}
			break;

		case mdsSM_SrchName:
			{
				ERROR_FAILED_HRESULT(hr = SearchItem(bstrSearch, GetIteratorName, lSearchMode, coll), E_FAIL);
				hrFound = S_OK == hr ? S_OK : S_FALSE;
			}
			break;

		case mdsSM_SrchName|mdsSM_SrchLong:
			{
				ERROR_FAILED_HRESULT(hr = SearchItem(bstrSearch, GetIteratorNameLong, lSearchMode, coll), E_FAIL);
				hrFound = S_OK == hr ? S_OK : S_FALSE;
			}
			break;

		default:
			_ASSERTE(SUCCEEDED(E_NOTIMPL));
			_com_issue_error(E_NOTIMPL);
			break;
		}
		*pValues = coll.Detach();

	} COM_CATCH;
	return hrFound;
}

IMPLEMENT_DEBUG_FUNCENTRY_0(CTRiASMDSMap, Clear) 
{
ObjectLock l(this);

	m_mapOfKeys.clear();
	return S_OK;
}

////////////////////////////////////////////////////////////////////
// CPersistStreamInitImpl

HRESULT	CTRiASMDSMap::OnInitNew() 
{ 
	m_mapOfKeys.clear();
	return S_OK;
}

HRESULT CTRiASMDSMap::LoadData(LPSTREAM pStm, DWORD dwVersion) 
{ 
long nItems;
ObjectLock l(this);

	LoadItem(pStm, nItems);
	for (/**/; nItems; --nItems) {
	CComBSTR strKey;
	CComBSTR strName;
	CComBSTR strShrt;
	CComBSTR strLong;
	CComVariant	vData;

		LoadItem(pStm, strKey);
		if (dwVersion < MAP_VERSION_NAME)
		{
			LoadItem(pStm, strShrt);
			strName = strShrt;
		}
		else {
			LoadItem(pStm, strName);
			LoadItem(pStm, strShrt);
		}
		LoadItem(pStm, strLong);
		vData.ChangeType(VT_EMPTY);

		if (dwVersion >= MAP_VERSION_DATA)
			LoadItem(pStm, vData);

		m_mapOfKeys.insert((BSTR) strKey, MDSValue((BSTR) strName, (BSTR) strShrt, (BSTR) strLong, (VARIANT) vData));
	}
	return S_OK;
}

HRESULT CTRiASMDSMap::SaveData(LPSTREAM pStm, BOOL bClearDirty) 
{
ObjectLock l(this);
MapOfKeys::iterator i = m_mapOfKeys.begin();
long nItems = m_mapOfKeys.size();

	SaveItem(pStm, nItems);
	for (/**/; m_mapOfKeys.end() != i; ++i)
	{
		SaveItem(pStm, (const BSTR&)(*i).first);
		SaveItem(pStm, (const BSTR&)(*i).second.m_strName);
		SaveItem(pStm, (const BSTR&)(*i).second.m_strShort);
		SaveItem(pStm, (const BSTR&)(*i).second.m_strLong);
		SaveItem(pStm, (const VARIANT&)(*i).second.m_vData);
	}
	return S_OK;
}

ULONG	CTRiASMDSMap::GetDataSize() 
{ 
ObjectLock l(this);
ULONG	size = 0;
MapOfKeys::iterator i = m_mapOfKeys.begin();

	for (/**/; m_mapOfKeys.end() != i; ++i)
	{
		size += SIZEOF((*i).first);
		size += SIZEOF((*i).second.m_strName);
		size += SIZEOF((*i).second.m_strShort);
		size += SIZEOF((*i).second.m_strLong);
		size += SIZEOF((*i).second.m_vData);
	}
	return size;
}
