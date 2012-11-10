// Objekte, die verschiedene Suchalgorithmen implementieren
// File: MatchingObjects.h

#include "trias03p.hxx"

#include <math.h>		// floor
#include "MatchingObjects.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// sonstige Member
HRESULT CMatchStringBase::put_MatchText (BSTR bstrMatching)
{
	try {
		m_bstrToMatch = bstrMatching;
		if (!m_bstrToMatch) _com_issue_error(E_OUTOFMEMORY);
	
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

return S_OK;
}

HRESULT CMatchStringBase::get_MatchText (BSTR *pbstrMatching)
{
	if (NULL == pbstrMatching)
		return E_POINTER;

	try {
		*pbstrMatching = m_bstrToMatch.Copy();
		if (NULL == *pbstrMatching) _com_issue_error(E_OUTOFMEMORY);
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

return S_OK;
}

HRESULT CMatchStringBase::put_MatchCase (VARIANT_BOOL fMatchCase)
{
	TX_ASSERT(NULL != (BSTR)m_bstrToMatch);		// muß VOR Case gesetzt werden !

	m_fIgnoreCase = fMatchCase ? false : true;
	return S_OK;
}

HRESULT CMatchStringBase::get_MatchCase (VARIANT_BOOL *pfMatchCase)
{
	if (NULL == pfMatchCase) return E_POINTER;

	*pfMatchCase = m_fIgnoreCase ? 0 : -1;
	return S_OK;
}

HRESULT CMatchStringBase::put_NegateMatch (VARIANT_BOOL fNegateMatch)
{
	TX_ASSERT(NULL != (BSTR)m_bstrToMatch);		// muß VOR Case gesetzt werden !

	m_fNegateMatch = fNegateMatch ? true : false;
	return S_OK;
}

HRESULT CMatchStringBase::get_NegateMatch (VARIANT_BOOL *pfNegateMatch)
{
	if (NULL == pfNegateMatch) return E_POINTER;

	*pfNegateMatch = m_fNegateMatch ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Exaktes Matching (mit/ohne CaseTest)
STDMETHODIMP CMatchPlainTextExakt::MatchString (BSTR bstrToMatch, int *piMatched)
{
	if (NULL == piMatched) return E_POINTER;
	if (IsNotValid()) return E_UNEXPECTED;		// not initialised

bool fMatched = false;

	if (m_fExistanceOnly) {
		fMatched = true;		// ObjProp exitiert, also matched
	} else {
		if (m_fFullMatch) {
			if (m_fIgnoreCase)
				fMatched = _wcsicmp(m_bstrToMatch, bstrToMatch) != 0 ? false : true;
			else
				fMatched = wcscmp(m_bstrToMatch, bstrToMatch) != 0 ? false : true;
		} else if (m_fTestBOB) {
		size_t iLen = min (SysStringLen(bstrToMatch), m_iMatchLen);

			if (m_fIgnoreCase)
				fMatched = _wcsnicmp(m_bstrToMatch, bstrToMatch, iLen) != 0 ? false : true;
			else
				fMatched = wcsncmp(m_bstrToMatch, bstrToMatch, iLen) != 0 ? false : true;
		} else {
		// in diesem Fall ist m_bstrToMatch bereits in Großbuchstaben gewandelt
			if (m_fIgnoreCase)
				wcsupr (bstrToMatch);
			fMatched = (NULL == wcsstr(bstrToMatch, m_bstrToMatch)) ? false : true;
		}
	}

	if (m_fNegateMatch)
		*piMatched = !fMatched;
	else
		*piMatched = fMatched;

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Exaktes Matching (mit/ohne CaseTest)
HRESULT CMatchPlainTextExakt::put_MatchText (BSTR bstrMatching)
{
	USES_CONVERSION;
	m_iMatchLen = SysStringLen(bstrMatching);
	return CMatchStringBase::put_MatchText(bstrMatching);
}

HRESULT CMatchPlainTextExakt::put_MatchCase (VARIANT_BOOL fMatchCase)
{
	if (!fMatchCase && !m_fFullMatch && !m_fTestBOB)
		wcsupr(m_bstrToMatch);	// Teilzeichenkette in der Mitte
	return CMatchStringBase::put_MatchCase(fMatchCase);
}

///////////////////////////////////////////////////////////////////////////////
// RegExpression Matching (mit/ohne CaseTest)
void CRegExpr::MatchCase (bool fMatch)
{
	DELETE_OBJ(pattern_buf_->translate);

	if (!fMatch) {
	// ACHTUNG: nur für ASCII-Zeichensatz
	char *case_fold = NULL;
	
		TX_TRY(case_fold = new char[256]);
		if (NULL != case_fold) {
			for (int i = 0; i < 256; i++)
				case_fold[i] = i;
			for (int j = 'a'; j <= 'z'; j++)
				case_fold[j] = j - ('a' - 'A');
		}

		pattern_buf_->translate = case_fold;
	}
}

CRegExpr::~CRegExpr (void)
{
	DELETE_OBJ(pattern_buf_->translate);
}

STDMETHODIMP CMatchRegExprExakt::MatchString (BSTR bstrToMatch, int *piMatched)
{
	if (NULL == piMatched) return E_POINTER;
	if (IsNotValid()) return E_UNEXPECTED;		// not initialised

	USES_CONVERSION;

os_string str (OLE2A(bstrToMatch));
bool fMatched = false;

	if (m_fFullMatch) 	// gesamtes String Matchen
		fMatched = m_regxToMatch.match (str) > 0 ? true : false;
	else {				// Teilzeichenkette suchen
	os_substring substr (m_regxToMatch.search (str));

		fMatched = substr.size() > 0 ? true : false;
	}

	if (m_fNegateMatch)
		*piMatched = !fMatched;
	else
		*piMatched = fMatched;

	return S_OK;
}

STDMETHODIMP CMatchRegExprExakt::put_MatchText (BSTR bstrMatching)
{
	USES_CONVERSION;

	try {
		m_regxToMatch.pattern(OLE2A(bstrMatching), true);

	} catch (os_invalid_argument) {
	// bad regexpr
		return E_INVALIDARG;
	} catch (...) {
	// out of memory
		return E_OUTOFMEMORY;
	}

	return CMatchStringBase::put_MatchText(bstrMatching);
}

STDMETHODIMP CMatchRegExprExakt::put_MatchCase (VARIANT_BOOL fFlag)
{
HRESULT hr = CMatchStringBase::put_MatchCase(fFlag);

	if (FAILED(hr)) return hr;

	try {
		m_regxToMatch.MatchCase (fFlag != 0 ? true : false);	// use translation table
		if (!fFlag) {
			USES_CONVERSION;

			wcsupr(m_bstrToMatch);	// SuchString in Großbuchstaben wandeln
			m_regxToMatch.pattern(OLE2A(m_bstrToMatch), true);
		}
	} catch (os_invalid_argument) {
	// bad regexpr
		return E_INVALIDARG;
	} catch (...) {
	// out of memory
		return E_OUTOFMEMORY;
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Fuzzy Matching
HRESULT CMatchFuzzy::put_MatchText (BSTR bstrMatching)
{
	m_iLen = wcslen (bstrMatching);
	if (m_iLen > COMP_LEN) 
		m_iLen = COMP_LEN;
	m_iThreshold = (int) floor((double) 1 + ((m_iLen + 2) / 4));

	m_distance[0][0] = 0;
	for (int i = 1; i < ARR_SIZE ; i++)
		m_distance[0][i] = m_distance[0][i-1] + addition;
	for (int j = 1; j < ARR_SIZE ; j++)
		m_distance[j][0] = m_distance[j-1][0] + deletion;

	return CMatchStringBase::put_MatchText(bstrMatching);
}

STDMETHODIMP CMatchFuzzy::MatchString (BSTR bstrToMatch, int *piMatched)
{
	if (NULL == piMatched) return E_POINTER;
	if (IsNotValid()) return E_UNEXPECTED;		// not initialised

int iLen = wcslen (bstrToMatch);

	if (iLen > COMP_LEN) iLen = COMP_LEN;
	if (abs(m_iLen - iLen) > m_iThreshold) {
		*piMatched = false; 
		return S_OK;		// length difference too big 
	}

	for (int i = 1; i <= m_iLen; i++) {
		for (int j = 1; j <= iLen; j++) {
			m_distance[i][j] = SMALLEST_OF(
				(m_distance[i-1][j-1] + ZERO_IF_EQUAL (bstrToMatch, i, j)),
				(m_distance[i][j-1]   + addition),
				(m_distance[i-1][j]   + deletion));
		}
	}

// Levenstein distance within threshold limit ?
	if (m_distance[m_iLen][iLen] <= m_iThreshold )
		*piMatched = true;		// distance within limits
	else
		*piMatched = false;		// distance too big
	
	if (m_fNegateMatch)
		*piMatched = !*piMatched;
	return S_OK;
}
