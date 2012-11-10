// RegExpr.cpp : Implementation of CRegExpr

#include "stdafx.h"

#include "Helper.h"
#include "RegExpr.h"
#include "PersistHelper.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegExpr

STDMETHODIMP CRegExpr::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IParseRegularExpression,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// IPersist 
STDMETHODIMP CRegExpr::GetClassID (CLSID *pClsID)
{
	if (NULL == pClsID) return E_POINTER;

	*pClsID = CLSID_ParseRegularExpression;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPersistStream 

STDMETHODIMP CRegExpr::IsDirty (void)
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CRegExpr::Load (IStream *pStm)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;

	COM_TRY {
	LONG lDummy = 0;

		THROW_FAILED_HRESULT(LoadString(pStm, m_strPattern));
		THROW_FAILED_HRESULT(LoadLong(pStm, lDummy));
		m_fIsCompiled = lDummy ? true : false;
		THROW_FAILED_HRESULT(LoadLong(pStm, lDummy));
		m_fIsMatched = lDummy ? true : false;

	} COM_CATCH;

	m_fIsDirty = false;
	m_fIsInitialized = true;
	m_fIsCompiled = true;
	return S_OK;
}

STDMETHODIMP CRegExpr::Save (IStream *pStm, BOOL fClearDirty)
{
	COM_TRY {
		THROW_FAILED_HRESULT(SaveString (pStm, m_strPattern));
		THROW_FAILED_HRESULT(SaveLong(pStm, m_fIsCompiled));
		THROW_FAILED_HRESULT(SaveLong(pStm, m_fIsMatched));
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CRegExpr::GetSizeMax (ULARGE_INTEGER * pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;

	pcbSize -> QuadPart = ::GetSizeMax (m_strPattern) + 2*sizeof(long);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit 

STDMETHODIMP CRegExpr::InitNew (void)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IParseRegularExpression

STDMETHODIMP CRegExpr::Match(
	BSTR ToMatch, VARIANT StartAt, VARIANT MatchLen, long *plMatched)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (!m_fIsInitialized || !m_fIsCompiled)
		return E_UNEXPECTED;	// nicht vollständig initialisiert

	USES_CONVERSION;

size_t iStartAt = 0;
size_t iLen = os_npos;
CComVariant vStartAt, vMatchLen;

	if (SUCCEEDED(vStartAt.ChangeType (VT_I4, &StartAt)))
		iStartAt = V_I4(&vStartAt);
	if (SUCCEEDED(vMatchLen.ChangeType (VT_I4, &MatchLen)))
		iLen = V_I4(&vMatchLen);

	m_strSearch = OLE2A(ToMatch);

int iMatched = m_strRegExpr.match (m_strSearch, iStartAt, iLen);

	if (NULL != plMatched)
		*plMatched = iMatched;

	m_fIsMatched = true;
	return S_OK;
}

STDMETHODIMP CRegExpr::Search(
	BSTR ToSearch, VARIANT *StartAt, VARIANT *SearchLen, BSTR *pbstrFound)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (!m_fIsInitialized || !m_fIsCompiled)
		return E_UNEXPECTED;	// nicht vollständig initialisiert
	if (NULL == pbstrFound)
		return E_POINTER;

	USES_CONVERSION;

size_t iStartAt = 0;
size_t iLen = os_npos;
CComVariant vStartAt, vSearchLen;

	if (SUCCEEDED(vStartAt.ChangeType (VT_I4, StartAt)))
		iStartAt = V_I4(&vStartAt);
	if (SUCCEEDED(vSearchLen.ChangeType (VT_I4, SearchLen)))
		iLen = V_I4(&vSearchLen);

	m_strSearch = OLE2A(ToSearch);

os_substring strRes = m_strRegExpr.search (m_strSearch, iStartAt, iLen);

// Resultate liefern
int iStrLen = strRes.size();
CComBSTR bstrFound (strRes.to_string().c_str());

	*pbstrFound = bstrFound.Detach();

	V_VT(StartAt) = VT_I4;
	V_I4(StartAt) = (iStrLen > 0) ? m_strRegExpr.GetRegisters() -> start[0] : -1;

	V_VT(SearchLen) = VT_I4;
	V_I4(SearchLen) = (iStrLen > 0) ? 
		m_strRegExpr.GetRegisters() -> end[0] - m_strRegExpr.GetRegisters() -> start[0] 
		: -1;

	m_fIsMatched = true;
	return S_OK;
}

STDMETHODIMP CRegExpr::Replace (
	BSTR ToReplace, BSTR NewString, VARIANT StartAt, VARIANT ReplaceLen, 
	VARIANT Global, BSTR *pbstrResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (!m_fIsInitialized || !m_fIsCompiled)
		return E_UNEXPECTED;	// nicht vollständig initialisiert
	if (NULL == pbstrResult)
		return E_POINTER;

	USES_CONVERSION;

size_t iStartAt = 0;
size_t iLen = os_npos;
CComVariant vStartAt, vReplaceLen;

	if (SUCCEEDED(vStartAt.ChangeType (VT_I4, &StartAt)))
		iStartAt = V_I4(&vStartAt);
	if (SUCCEEDED(vReplaceLen.ChangeType (VT_I4, &ReplaceLen)))
		iLen = V_I4(&vReplaceLen);

CComVariant vGlobal;
VARIANT_BOOL fGlobal = VARIANT_TRUE;

	if (SUCCEEDED(vGlobal.ChangeType (VT_BOOL, &Global)))
		fGlobal = V_BOOL(&vGlobal);

os_string str (OLE2A(ToReplace));
os_string strRepl (OLE2A(NewString));

	m_strRegExpr.replace (str, iStartAt, iLen, strRepl, fGlobal);

CComBSTR bstrRes (str.c_str());

	*pbstrResult = bstrRes.Detach();
	m_fIsMatched = true;
	return S_OK;
}

STDMETHODIMP CRegExpr::get_Pattern(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (!m_fIsInitialized || !m_fIsCompiled)
		return E_UNEXPECTED;	// nicht vollständig initialisiert
	if (NULL == pVal) return E_POINTER;

CComBSTR bstrPattern (m_strPattern.c_str());

	if (!bstrPattern)
		return E_OUTOFMEMORY;

	*pVal = bstrPattern.Detach();
	return S_OK;
}

STDMETHODIMP CRegExpr::put_Pattern(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (!m_fIsInitialized)
		return E_UNEXPECTED;	// nicht vollständig initialisiert

	m_fIsMatched = false;

	USES_CONVERSION;
	COM_TRY {
		m_strPattern = OLE2A(newVal);
		m_strRegExpr.pattern(m_strPattern);

	} catch (os_invalid_argument) {
		return E_INVALIDARG;	// invalid pattern
	} COM_CATCH;

	m_fIsCompiled = true;
	return S_OK;
}

STDMETHODIMP CRegExpr::get_Groups(long * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (!m_fIsInitialized || !m_fIsCompiled || !m_fIsMatched)
		return E_UNEXPECTED;	// nicht vollständig initialisiert
	if (NULL == pVal) 
		return E_POINTER;

	*pVal = m_strRegExpr.groups();
	return S_OK;
}

STDMETHODIMP CRegExpr::get_Group(long lIndex, BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (!m_fIsInitialized || !m_fIsCompiled || !m_fIsMatched)
		return E_UNEXPECTED;	// nicht vollständig initialisiert
	if (NULL == pVal) 
		return E_POINTER;
	if (0 > lIndex || (size_t)lIndex > m_strRegExpr.groups())
		return E_INVALIDARG;

	if (m_strRegExpr.group(lIndex).size() > 0) {
	CComBSTR bstrGroup (m_strRegExpr.group(lIndex).to_string().c_str());

		if (!bstrGroup) 
			return E_OUTOFMEMORY;

		*pVal = bstrGroup.Detach();
		return S_OK;
	}

// Gruppe wurde nicht gematched
	*pVal = SysAllocString(L"");
	return S_OK;
}

