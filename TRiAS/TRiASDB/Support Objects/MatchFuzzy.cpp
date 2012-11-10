// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 11/18/1998 08:30:41 PM
//
// @doc
// @module MatchFuzzy.cpp | Description goes here

#include "stdafx.h"

#include <math.h>

#include "Helper.h"
#include "MatchFuzzy.h"

/////////////////////////////////////////////////////////////////////////////
// CMatchFuzzy

STDMETHODIMP CMatchFuzzy::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_DMatchString,
		&IID_IMatchFuzzy,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Fuzzy Matching
HRESULT CMatchFuzzy::put_MatchText (BSTR bstrMatching)
{
	m_iLen = ::SysStringLen(bstrMatching);
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

int iLen = ::SysStringLen(bstrToMatch);

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
	
	if (m_NegateMatch)
		*piMatched = !*piMatched;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Exaktes Matching (mit/ohne CaseTest) mit anschließendem Replace (wenn möglich)
STDMETHODIMP CMatchFuzzy::MatchAndReplaceString (
	BSTR bstrToMatch, BSTR bstrToReplace, int *piMatched, BSTR *pbstrResult)
{
	_ASSERTE(SUCCEEDED(E_NOTIMPL));
	return E_NOTIMPL;
}