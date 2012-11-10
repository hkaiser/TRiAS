// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 11/18/1998 08:26:55 PM
//
// @doc
// @module MatchRegExprExakt.cpp | Description goes here

#include "stdafx.h"

#include "Helper.h"
#include "MatchRegExprExakt.h"

/////////////////////////////////////////////////////////////////////////////
// CMatchRegExprExakt

STDMETHODIMP CMatchRegExprExakt::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_DMatchString,
		&IID_IMatchRegExpr,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// IMatchRegExpr
IMPLEMENT_PROPERTY_ACCESS(CMatchRegExprExakt, FullMatch, VARIANT_BOOL);

STDMETHODIMP CMatchRegExprExakt::MatchString (BSTR bstrToMatch, int *piMatched)
{
	if (NULL == piMatched) return E_POINTER;
	if (IsNotValid()) return E_UNEXPECTED;		// not initialised

	USES_CONVERSION;

os_string str (OLE2A(bstrToMatch));
bool fMatched = false;

	if (m_FullMatch) {	// gesamtes String Matchen
	int iMatchCnt = m_regxToMatch.match(str);

		fMatched = (iMatchCnt > 0 && iMatchCnt == ::SysStringLen(bstrToMatch)) ? true : false;
	} 
	else {				// Teilzeichenkette suchen
	os_substring substr (m_regxToMatch.search (str));

		fMatched = substr.size() > 0 ? true : false;
	}

	if (m_NegateMatch)
		*piMatched = !fMatched;
	else
		*piMatched = fMatched;

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Exaktes Matching (mit/ohne CaseTest) mit anschließendem Replace (wenn möglich)
STDMETHODIMP CMatchRegExprExakt::MatchAndReplaceString (
	BSTR bstrToMatch, BSTR bstrToReplace, int *piMatched, BSTR *pbstrResult)
{
	if (NULL == piMatched || NULL == pbstrResult) 
		return E_POINTER;
	if (IsNotValid()) 
		return E_UNEXPECTED;		// not initialised

	USES_CONVERSION;

os_string str (OLE2A(bstrToMatch));
os_string strReplaceWith (OLE2A(bstrToReplace));
bool fMatched = false;

// jetzt eigentliches Ersetzen
	if (m_FullMatch) {	// gesamtes String Matchen
	int iMatchCnt = m_regxToMatch.match(str);

		if (iMatchCnt > 0 && iMatchCnt == ::SysStringLen(bstrToMatch)) {
		// ggf. back-Referenzen auflösen
		size_t iPos = strReplaceWith.find_first_of ('\\');

			if (os_npos != iPos && isdigit(strReplaceWith[iPos+1])) 
				strReplaceWith = m_regxToMatch.ExpandBackReferences(strReplaceWith.c_str());
			
			m_regxToMatch.replace(str, 0, str.size(), strReplaceWith.c_str());

		CComBSTR bstr (str.c_str());

			*pbstrResult = bstr.Detach();
			fMatched = true;
		}

	} else {
	// Teilzeichenkette suchen
	os_substring substr (m_regxToMatch.search (str));

		if (substr.size() > 0) {
		// ggf. back-Referenzen auflösen
		size_t iPos = strReplaceWith.find_first_of ('\\');

			if (os_npos != iPos && isdigit(strReplaceWith[iPos+1])) 
				strReplaceWith = m_regxToMatch.ExpandBackReferences(strReplaceWith.c_str());
			
			m_regxToMatch.replace(str, substr.position(), substr.size(), strReplaceWith.c_str(), true);

		CComBSTR bstr (str.c_str());

			*pbstrResult = bstr.Detach();
			fMatched = true;
		}
	}

	if (m_NegateMatch)
		*piMatched = !fMatched;
	else
		*piMatched = fMatched;

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// 
STDMETHODIMP CMatchRegExprExakt::put_MatchText (BSTR bstrMatching)
{
	COM_TRY {
		USES_CONVERSION;
		m_regxToMatch.pattern(OLE2A(bstrMatching), true);
	} catch (os_invalid_argument) {
		_ASSERTE(SUCCEEDED(E_INVALIDARG));
		return E_INVALIDARG;	// bad regexpr
	} COM_CATCH;

	return CMatchStringBase::put_MatchText(bstrMatching);
}

STDMETHODIMP CMatchRegExprExakt::put_MatchCase (VARIANT_BOOL fFlag)
{
	RETURN_FAILED_HRESULT(CMatchStringBase::put_MatchCase(fFlag));
	COM_TRY {
		m_regxToMatch.MatchCase (fFlag != 0 ? true : false);	// use translation table
		if (!fFlag) {
			USES_CONVERSION;

			wcsupr(m_MatchText);	// SuchString in Großbuchstaben wandeln
			m_regxToMatch.pattern(OLE2A(m_MatchText), true);
		}
	} catch (os_invalid_argument) {
	// bad regexpr
		_ASSERTE(SUCCEEDED(E_INVALIDARG));
		return E_INVALIDARG;
	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// RegExpression Matching (mit/ohne CaseTest)
void CMatchRegExprExakt::
CRegExpr::MatchCase (bool fMatch)
{
	if (NULL != pattern_buf_->translate) {
		delete [] pattern_buf_->translate;
		pattern_buf_->translate = NULL;
	}

	if (!fMatch) {
	// ACHTUNG: nur für ASCII-Zeichensatz
	char *case_fold = NULL;
	
		ATLTRY(case_fold = new char[256]);
		if (NULL != case_fold) {
			for (int i = 0; i < 256; i++)
				case_fold[i] = i;
			for (int j = 'a'; j <= 'z'; j++)
				case_fold[j] = j - ('a' - 'A');
		}
		pattern_buf_->translate = case_fold;
	}
}

CMatchRegExprExakt::
CRegExpr::~CRegExpr (void)
{
	if (NULL != pattern_buf_->translate) {
		delete [] pattern_buf_->translate;
		pattern_buf_->translate = NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Back-Referenzen ("\[:digit:]") auflösen
os_string CMatchRegExprExakt::
CRegExpr::ExpandBackReferences (const char *pcSrc)
{
os_string strDest;

	while ('\0' != *pcSrc) {
	int c = *pcSrc++;

		if ('\\' == c) {
		// Sonderfeld soll eingefügt werden
		int cNext = *pcSrc++;
		
			switch (cNext) {
			// Back-Referenz
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if ((cNext - '0') <= groups())
					strDest.append(group(cNext - '0').to_string());
				break;

			default:
				strDest.append(pcSrc-2, 2);
				break;
			}
		} 
		else {
		// normaler Buchstabe --> in Ausgabe übernehmen
			strDest.append(pcSrc-1, 1);
		}
	}
	return strDest;
}
