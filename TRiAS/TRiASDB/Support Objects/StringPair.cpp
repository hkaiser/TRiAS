// StringPairs.cpp : Implementation of CStringPairs

#include "stdafx.h"
#include <ospace/string/tokenize.h>

#include "Helper.h"
#include "StringPair.h"

///////////////////////////////////////////////////////////////////////////////
//
DefineSmartInterface(PersistStreamInit);
DefineSmartInterface(PersistPropertyBag);
DefineSmartInterface(ErrorLog);

///////////////////////////////////////////////////////////////////////////////
// CStringPairs

HRESULT CStringPairs::FinalConstruct (void)
{
	COM_TRY {
	WUnknown RegExpr (CLSID_ParseRegularExpression);
	WPersistStreamInit Init (RegExpr);

		THROW_FAILED_HRESULT(Init -> InitNew());
		m_RegExpr = RegExpr;

	} COM_CATCH;
	return S_OK;
}

void CStringPairs::FinalRelease()
{
	m_RegExpr.Assign(NULL);
}

///////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CStringPairs::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IParseStringPairs,
		&IID_IComposeStringPairs,
		&IID_ITRiASPropertyBag,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// sonstige Member

HRESULT CStringPairs::GenRegExpr (os_string &rStr)
{
// erstes Element im Pattern finden
size_t iFirst = m_strPattern.find (TEXT("%1"));
size_t iSecond = m_strPattern.find (TEXT("%2"));

	if (os_npos == iFirst || os_npos == iSecond) 
		return E_INVALIDARG;

// ersetzen der Platzhalter durch RegExprGroups
size_t iMin = min(iFirst, iSecond);
size_t iMax = max(iFirst, iSecond);

	rStr = m_strPattern.substr (1, iMin-1);
	rStr += TEXT("\\(.*\\)");		// zugehörige Gruppe

	rStr += m_strPattern.substr (iMin+2, iMax-(iMin+2));
	rStr += TEXT("\\(.*\\)");		// zugehörige Gruppe

	rStr += m_strPattern.substr (iMax+2);

// speichern, welche der Gruppen die erste ist
	m_l1st = (iMin == iFirst) ? 1 : 2;		// merken der GruppenNummer,
	m_l2nd = (iMin == iFirst) ? 2 : 1;		// die rauskommen muß
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IParseStringPairs

STDMETHODIMP CStringPairs::get_Pattern(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (!m_fHasPattern)	return E_UNEXPECTED;
	if (NULL == pVal) return E_POINTER;

CComBSTR bstrPattern (m_strPattern.c_str());

	if (!bstrPattern)
		return E_OUTOFMEMORY;

	*pVal = bstrPattern.Detach();
	return S_OK;
}

STDMETHODIMP CStringPairs::put_Pattern(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	USES_CONVERSION;
	COM_TRY {
		m_strPattern = OLE2A(newVal);

	os_string strRegExpr;

		THROW_FAILED_HRESULT(GenRegExpr (strRegExpr));
		THROW_FAILED_HRESULT(m_RegExpr -> put_Pattern (A2OLE(strRegExpr.c_str())));
		
		m_fHasPattern = true;

	} catch (os_invalid_argument) {
		return E_INVALIDARG;	// invalid pattern
	} COM_CATCH;

	return S_OK;
}

STDMETHODIMP CStringPairs::get_Value(BSTR Key, BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if ((!m_fHasPattern || !m_fIsParsed) && !m_fHasDataSet)
		return E_UNEXPECTED;
	if (NULL == pVal) return E_POINTER;

CStringPairList::iterator it = m_Pairs.find (CComBSTR(Key));

	if (it != m_Pairs.end()) {
	CComBSTR bstrValue ((*it).second);

		if (!bstrValue)
			return E_OUTOFMEMORY;
		*pVal = bstrValue.Detach();
		return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CStringPairs::Parse (BSTR ToParse, long *plPairs)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fHasPattern)
		return E_UNEXPECTED;
	if (NULL == plPairs) return E_POINTER;

	m_Pairs.erase(m_Pairs.begin(), m_Pairs.end());	// alles bisherige vergessen

HRESULT hr = S_OK;

	USES_CONVERSION;
	COM_TRY {
	os_tokenizer tokenizer;

		tokenizer.allow_empty_tokens (true);
		tokenizer.separators (os_string(m_strPattern[0]));	// das erste Zeichen trennt die Paare
		tokenizer.include_separators (false);

	vector<os_string> tokens = tokenizer.tokenize (os_string(OLE2A(ToParse)));

		for (vector<os_string>::iterator it = tokens.begin(); it != tokens.end(); ++it)
		{
		CComVariant vStartAt (0, VT_I4);
		CComVariant vSearchLen (os_npos, VT_I4);
		CComBSTR bstrFound;

			hr = m_RegExpr -> Search (CComBSTR((*it).c_str()), &vStartAt, &vSearchLen, CLEARED(&bstrFound));
			if (FAILED(hr) || -1 == V_I4(&vStartAt)) 
				continue;

		long lGroups = 0;

			m_RegExpr -> get_Groups(&lGroups);
			if (2 != lGroups) 
				_com_issue_error(E_INVALIDARG);
	
		CComBSTR bstrKey, bstrValue;

			THROW_FAILED_HRESULT(m_RegExpr -> get_Group (m_l1st, CLEARED(&bstrKey)));
			THROW_FAILED_HRESULT(m_RegExpr -> get_Group (m_l2nd, CLEARED(&bstrValue)));

		// neues Paar einfügen
			m_Pairs.insert (bstrKey, bstrValue);
		}

	// Anzahl der Paare liefern
		*plPairs = m_Pairs.size();

	} COM_CATCH_OP((m_Pairs.erase(m_Pairs.begin(), m_Pairs.end()), m_fIsParsed = false));	// alles bisherige vergessen

	m_fIsParsed = true;
	return S_OK;
}

STDMETHODIMP CStringPairs::GetKeyStrings(IUnknown **ppIKeys)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fHasPattern || !m_fIsParsed)
		return E_UNEXPECTED;
	if (NULL == ppIKeys) return E_POINTER;

CComObject<CEnumString> *pIEnum = NULL;

	ATLTRY(pIEnum = new CComObject<CEnumString>());
	if (NULL == pIEnum) return E_OUTOFMEMORY;

// Zeiger umkopieren, damit ein zusammenhängender Vektor entsteht,
// dazu auf dem Stack den Speicher anfordern (gibt sich selbst frei!)
LPOLESTR *ppOleStr = (LPOLESTR *)alloca(sizeof(LPOLESTR) * m_Pairs.size());
int i = 0;

	for (CStringPairList::iterator it = m_Pairs.begin(); 
		 it != m_Pairs.end(); ++it)
	{
		ppOleStr[i++] = (*it).first.m_str;	// kein Kopieren hier, sondern in Init
	}

// die Funktion Init des EnumTemplates erwartet die Adressen des ersten und 
// letzten+1 Elementes eines Vektors
HRESULT hr = pIEnum -> Init (&ppOleStr[0], &ppOleStr[m_Pairs.size()], (IParseStringPairs *)this, AtlFlagCopy);

	if (SUCCEEDED(hr))
		hr = pIEnum -> QueryInterface(IID_IEnumString, (LPVOID *)ppIKeys);

	if (FAILED(hr))		// bei Fehler alles freigeben
		delete pIEnum;

	return hr;
}

STDMETHODIMP CStringPairs::InitObject (IUnknown *pITarget, VARIANT ErrorLog)
{
	COM_TRY {
	WPersistPropertyBag Bag (pITarget);

		Bag -> InitNew();		// ignore error (may be already initialized)

	CComVariant v;
	WErrorLog Log;				// Log ist evtl. nicht gegeben

		if (SUCCEEDED(v.ChangeType (VT_UNKNOWN, &ErrorLog)))
			Log = V_UNKNOWN(&v);
		THROW_FAILED_HRESULT(Bag -> Load (this, Log));

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IComposeStringPairs
HRESULT CStringPairs::GenOutputFormat (
	LPCSTR pcPattern, BSTR bstrFirst, BSTR bstrSecond, BSTR *pbstr)
{
	USES_CONVERSION;

// erstes Element im Pattern finden
os_string strPattern (pcPattern);
size_t iFirst = strPattern.find (TEXT("%1"));
size_t iSecond = strPattern.find (TEXT("%2"));

	if (os_npos == iFirst || os_npos == iSecond) 
		return E_INVALIDARG;

// ersetzen der Platzhalter durch RegExprGroups
size_t iMin = min(iFirst, iSecond);
size_t iMax = max(iFirst, iSecond);
os_string rStr;

	rStr = strPattern.substr (0, iMin);
	rStr += OLE2A(bstrFirst);	

	rStr += strPattern.substr (iMin+2, iMax-(iMin+2));
	rStr += OLE2A(bstrSecond);		// zugehörige Gruppe

	rStr += strPattern.substr (iMax+2);

// speichern, welche der Gruppen die erste ist
CComBSTR bstr (rStr.c_str());

	*pbstr = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CStringPairs::get_ComposedData (BSTR Pattern, BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) return E_POINTER;
	
	USES_CONVERSION;

CComBSTR bstrRes;
LPCSTR pcPattern = OLE2A(Pattern);
	
	for (CStringPairList::iterator it = m_Pairs.begin(); it != m_Pairs.end(); ++it)
	{
	CComBSTR bstr;

		RETURN_FAILED_HRESULT(GenOutputFormat (pcPattern, (*it).first, (*it).second, CLEARED(&bstr)));
		bstrRes += bstr;
	}
	*pVal = bstrRes.Detach();
	return S_OK;
}

STDMETHODIMP CStringPairs::SetValue (BSTR Key, BSTR Val, VARIANT_BOOL fCreate)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	COM_TRY {
	CComBSTR bstrVal;
	
		if (S_OK != get_Value (Key, CLEARED(&bstrVal))) {
			if (!fCreate)
				return S_FALSE;		// existiert noch nicht
		} else {
		// existierenden Key rauslöschen
			m_Pairs.erase (CComBSTR(Key));
		}

	// Wert neu erzeugen
		m_Pairs.insert (CComBSTR(Key), CComBSTR(Val));

	} COM_CATCH;

	m_fHasDataSet = true;
	return S_OK;
}

STDMETHODIMP CStringPairs::DeletePair (BSTR Key)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	COM_TRY {
	// existierenden Key rauslöschen
		m_Pairs.erase (CComBSTR(Key));

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyBag
STDMETHODIMP CStringPairs::Read (LPCOLESTR pszPropName, VARIANT *pVar, IErrorLog *pErrorLog)
{
	if (NULL == pVar) 
		return E_POINTER;

CComBSTR bstr;
HRESULT hr = get_Value (CComBSTR(pszPropName), CLEARED(&bstr));

	if (S_OK == hr) {
		V_VT(pVar) = VT_BSTR;
		V_BSTR(pVar) = bstr.Detach();
	}
	return hr;
}

STDMETHODIMP CStringPairs::Write (LPCOLESTR pszPropName, VARIANT *pVar)
{
	ATLTRACENOTIMPL("CStringPairs::Write");
}

// ITRiASPropertyBag
STDMETHODIMP CStringPairs::ReadProperty(BSTR bstrDataName, VARIANT vDefaultValue, 
	VARIANT *pvData)
{
	ATLTRACE(_T("CStringPairs::ReadProperty\n"));
	if (NULL == pvData) 
		return E_POINTER;

CComBSTR bstr;
HRESULT hr = get_Value (bstrDataName, CLEARED(&bstr));

	if (S_OK == hr) {
	CComVariant vResult (bstr);

		return vResult.Detach(pvData);
	}

// ggf. Defaultvalue kopieren
	if (V_VT(&vDefaultValue) != VT_EMPTY)
		return VariantCopy(pvData, &vDefaultValue);
	return hr;
}

// Implementation of WriteProperty
STDMETHODIMP CStringPairs::WriteProperty(BSTR bstrDataName, VARIANT vData, 
	VARIANT vDefaultValue)
{
	ATLTRACE(_T("CStringPairs::WriteProperty\n"));

	RETURN_FAILED_HRESULT(VariantChangeType(&vData, &vData, 0, VT_BSTR));
	RETURN_FAILED_HRESULT(SetValue(bstrDataName, V_BSTR(&vData), VARIANT_TRUE));
	return S_OK;
}

