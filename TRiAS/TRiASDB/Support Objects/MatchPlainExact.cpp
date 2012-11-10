// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 11/18/1998 08:21:48 PM
//
// @doc
// @module MatchObjects.cpp | Description goes here

#include "stdafx.h"

#include "Helper.h"
#include "MatchPlainExact.h"

/////////////////////////////////////////////////////////////////////////////
// CMatchPlainTextExakt

STDMETHODIMP CMatchPlainTextExakt::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_DMatchString,
		&IID_IMatchPlainText,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// IMatchPlainText
IMPLEMENT_PROPERTY_ACCESS(CMatchPlainTextExakt, TestBOB, VARIANT_BOOL);
IMPLEMENT_PROPERTY_ACCESS(CMatchPlainTextExakt, ExistanceOnly, VARIANT_BOOL);
IMPLEMENT_PROPERTY_ACCESS(CMatchPlainTextExakt, FullMatch, VARIANT_BOOL);

///////////////////////////////////////////////////////////////////////////////
// Exaktes Matching (mit/ohne CaseTest)
STDMETHODIMP CMatchPlainTextExakt::put_MatchText (BSTR bstrMatching)
{
	USES_CONVERSION;
	m_iMatchLen = SysStringLen(bstrMatching);
	return CMatchStringBase::put_MatchText(bstrMatching);
}

STDMETHODIMP CMatchPlainTextExakt::put_MatchCase (VARIANT_BOOL fMatchCase)
{
	if (!fMatchCase && !m_FullMatch && !m_TestBOB)
		wcsupr(m_MatchText);			// Teilzeichenkette in der Mitte
	return CMatchStringBase::put_MatchCase(fMatchCase);
}

///////////////////////////////////////////////////////////////////////////////
// Exaktes Matching (mit/ohne CaseTest)
STDMETHODIMP CMatchPlainTextExakt::MatchString (BSTR bstrToMatch, int *piMatched)
{
	if (NULL == piMatched) return E_POINTER;
	if (IsNotValid()) return E_UNEXPECTED;		// not initialised

bool fMatched = false;

	if (m_ExistanceOnly) {
		fMatched = true;		// ObjProp exitiert, also matched
	} else {
		if (m_FullMatch) {
			if (!m_MatchCase)
				fMatched = _wcsicmp(m_MatchText, bstrToMatch) != 0 ? false : true;
			else
				fMatched = wcscmp(m_MatchText, bstrToMatch) != 0 ? false : true;
		} else if (m_TestBOB) {
		size_t iLen = min (SysStringLen(bstrToMatch), m_iMatchLen);

			if (!m_MatchCase)
				fMatched = _wcsnicmp(m_MatchText, bstrToMatch, iLen) != 0 ? false : true;
			else
				fMatched = wcsncmp(m_MatchText, bstrToMatch, iLen) != 0 ? false : true;
		} else {
		// in diesem Fall ist m_MatchText bereits in Großbuchstaben gewandelt
			if (!m_MatchCase)
				wcsupr (bstrToMatch);
			fMatched = (NULL == wcsstr(bstrToMatch, m_MatchText)) ? false : true;
		}
	}

	if (m_NegateMatch)
		*piMatched = !fMatched;
	else
		*piMatched = fMatched;

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Exaktes Matching (mit/ohne CaseTest) mit anschließendem Replace (wenn möglich)
STDMETHODIMP CMatchPlainTextExakt::MatchAndReplaceString (
	BSTR bstrToMatch, BSTR bstrToReplace, int *piMatched, BSTR *pbstrResult)
{
	if (NULL == piMatched || NULL == pbstrResult) 
		return E_POINTER;
	if (IsNotValid()) 
		return E_UNEXPECTED;		// not initialised

bool fMatched = false;

	*pbstrResult = NULL;
	if (m_ExistanceOnly) 
		return E_UNEXPECTED;	// kein Replace möglich (sinnvoll)
	else {
		if (m_FullMatch) {
			if (!m_MatchCase)
				fMatched = _wcsicmp(m_MatchText, bstrToMatch) != 0 ? false : true;
			else
				fMatched = wcscmp(m_MatchText, bstrToMatch) != 0 ? false : true;

			if (fMatched) {
			CComBSTR bstr (bstrToReplace);

				*pbstrResult = bstr.Detach();
			}
			
		} else if (m_TestBOB) {
		size_t iLen = min (SysStringLen(bstrToMatch), m_iMatchLen);

			if (!m_MatchCase)
				fMatched = _wcsnicmp(m_MatchText, bstrToMatch, iLen) != 0 ? false : true;
			else
				fMatched = wcsncmp(m_MatchText, bstrToMatch, iLen) != 0 ? false : true;

			if (fMatched) {
			CComBSTR bstr (iLen, bstrToReplace);

				bstr.Append((LPCOLESTR)(m_MatchText + iLen));
				*pbstrResult = bstr.Detach();
			}

		} else {
		// in diesem Fall ist m_MatchText bereits in Großbuchstaben gewandelt
			if (!m_MatchCase)
				wcsupr (bstrToMatch);

		// wenn der Ersetzungstext gleich dem Suchtext ist, dann gleich wieder raus
		CComBSTR bstr (bstrToMatch);

			if (m_MatchText == bstrToMatch) 
				fMatched = true;
			else {
			// Suchen und Ersetzen global ausführen
				while (true) {
				LPCOLESTR pT = wcsstr(bstr, m_MatchText);

					if (NULL != pT) {
					int iLen = pT-bstr;
					CComBSTR bstrT (iLen, bstr);

						bstrT.AppendBSTR(bstrToReplace);
						iLen += m_MatchText.Length();
						bstrT.Append((LPCOLESTR)(bstrToMatch+iLen));

						fMatched = true;
						bstr = bstrT;
					}
					else
						break;
				}
			}
			if (fMatched)
				*pbstrResult = bstr.Detach();
		}
	}
	*piMatched = fMatched;
	return S_OK;
}
