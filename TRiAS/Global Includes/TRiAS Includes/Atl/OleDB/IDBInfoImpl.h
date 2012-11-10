// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 16.05.2001 17:33:23 
//
// @doc
// @module IDBInfoImpl.h | Declaration of the <c CIDBInfoImpl> class

#if !defined(_IDBINFOIMPL_H__1679F11A_35B8_44B4_8BB9_51350A71121E__INCLUDED_)
#define _IDBINFOIMPL_H__1679F11A_35B8_44B4_8BB9_51350A71121E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// IDBInfo implementation
template <class T>
class ATL_NO_VTABLE IDBInfoImpl : 
	public IDBInfo
{
public:
	STDMETHODIMP GetKeywords(LPOLESTR *ppwszKeywords)
	{
		ATLTRACE2(atlTraceDBProvider, 0, "IDBInfoImpl::GetKeywords\n");
		if (ppwszKeywords != NULL)
			*ppwszKeywords = NULL;
		if (ppwszKeywords == NULL)
			return E_INVALIDARG;

	T *pT = static_cast<T *>(this);

		if (!(pT->m_dwStatus & DSF_INITIALIZED))
			return E_UNEXPECTED;

	ULONG ulCnt = 0;
	LPCOLESTR *ppkws = pT -> _KeywordSupport(&ulCnt);

	// calculate size of required memory
	size_t iLen = 1;	// null char at the end

		for (ULONG i = 0; i < ulCnt; ++i)
			iLen += wcslen(ppkws[i]) + 2;		// account for additional L"," 

		if (iLen > 1) {
		// return keywords
		LPOLESTR poleT = (LPOLESTR)CoTaskMemAlloc(iLen * sizeof(OLECHAR));
		
			if (NULL == poleT) return E_OUTOFMEMORY;

			for (ULONG i = 0; i < ulCnt; ++i) {
				wcscat(poleT, ppkws[i]);
				if (i < ulCnt-1)
					wcscat(poleT, OLESTR(","));
			}
			*ppwszKeywords = poleT;
		}
		return S_OK;
	}
	STDMETHODIMP GetLiteralInfo(
		ULONG cLiterals, const DBLITERAL rgLiterals[], ULONG *pcLiteralInfo, 
		DBLITERALINFO **prgLiteralInfo, OLECHAR **ppCharBuffer)
	{
		ATLTRACE2(atlTraceDBProvider, 0, "IDBInfoImpl::GetLiteralInfo\n");

	// Check in-params and NULL out-params in case of error
		if (pcLiteralInfo)
			*pcLiteralInfo = 0;
		if (prgLiteralInfo)
			*prgLiteralInfo = NULL;
		if (ppCharBuffer)
			*ppCharBuffer = NULL;

	// Check input and output values pointers
		if (cLiterals && !rgLiterals)
			return E_INVALIDARG;
		if (!pcLiteralInfo || !prgLiteralInfo || !ppCharBuffer)
			return E_INVALIDARG;

	// Check to see if initialized
	T *pT = static_cast<T *>(this);

		if (!(pT->m_dwStatus & DSF_INITIALIZED))
			return  E_UNEXPECTED;

	// If cLiterals is 0, ignore rgLiterals return all supported values
	const DBLITERALINFO *pSupportedLiterals = NULL;

		if (0 == cLiterals) 
			pSupportedLiterals = pT -> _LiteralSupport(&cLiterals);	// get count of supported literals

	// Process each of the DBLITERAL values that are in the restriction array
		*prgLiteralInfo = (DBLITERALINFO *)CoTaskMemAlloc(sizeof(DBLITERALINFO)*cLiterals);
		if (NULL == *prgLiteralInfo) return E_OUTOFMEMORY;

		*pcLiteralInfo = cLiterals;

	// the first loop calculates the amount of required string memory
	ULONG ulRequired = 0;

		for(ULONG ulIndex = 0; ulIndex < cLiterals; ++ulIndex) {
		const DBLITERALINFO *plitDefined = NULL;
		
			if (NULL == pSupportedLiterals)
				plitDefined = HasPredefinedLiteral(rgLiterals[ulIndex]);	// test if literal is supported
			else
				plitDefined = &pSupportedLiterals[ulIndex];					// return all supported

			if (NULL != plitDefined) {
				if (NULL != plitDefined -> pwszLiteralValue)
					ulRequired += wcslen(plitDefined -> pwszLiteralValue)+1;
				if (NULL != plitDefined -> pwszInvalidChars)
					ulRequired += wcslen(plitDefined -> pwszInvalidChars)+1;
				if (NULL != plitDefined -> pwszInvalidStartingChars)
					ulRequired += wcslen(plitDefined -> pwszInvalidStartingChars)+1;
			}
		}

	// the second loop does the actual work ...
	OLECHAR *pCharBuffer = (OLECHAR *)CoTaskMemAlloc(ulRequired*sizeof(OLECHAR)+1);
	bool fOneSupported = false;
	HRESULT hr = S_OK;

		if (NULL != pCharBuffer) {
		OLECHAR *pCurr = pCharBuffer;

			for(ULONG ulIndex = 0; ulIndex < cLiterals; ++ulIndex) {
				_ASSERTE(pCurr <= pCharBuffer+ulRequired);		// avoid buffer overrun

				if (rgLiterals && !(DBLITERAL_INVALID < rgLiterals[ulIndex] && rgLiterals[ulIndex] <= DBLITERAL_QUOTE_SUFFIX))
					hr = DB_S_ERRORSOCCURRED;		// invalid literal

			const DBLITERALINFO *plitDefined = NULL;
			
				if (NULL == pSupportedLiterals) {
					plitDefined = HasPredefinedLiteral(rgLiterals[ulIndex]);	// test if literal is supported
					if (NULL == plitDefined)
						hr = DB_S_ERRORSOCCURRED;	// not supported literal
					else
						fOneSupported = true;
				} else
					plitDefined = &pSupportedLiterals[ulIndex];					// return all supported

				if (NULL != plitDefined) {
					(*prgLiteralInfo)[ulIndex] = *plitDefined;					// return predefined values
					if (NULL != plitDefined -> pwszLiteralValue) {
						wcscpy (pCurr, plitDefined -> pwszLiteralValue);
						(*prgLiteralInfo)[ulIndex].pwszLiteralValue = pCurr;
						pCurr += wcslen(pCurr)+1;
					}
					if (NULL != plitDefined -> pwszInvalidChars) {
						wcscpy (pCurr, plitDefined -> pwszInvalidChars);
						(*prgLiteralInfo)[ulIndex].pwszInvalidChars = pCurr;
						pCurr += wcslen(pCurr)+1;
					}
					if (NULL != plitDefined -> pwszInvalidStartingChars) {
						wcscpy (pCurr, plitDefined -> pwszInvalidStartingChars);
						(*prgLiteralInfo)[ulIndex].pwszInvalidStartingChars = pCurr;
						pCurr += wcslen(pCurr)+1;
					}
				} 
				else {
				// not supported literal
					(*prgLiteralInfo)[ulIndex].lt = rgLiterals[ulIndex];
					(*prgLiteralInfo)[ulIndex].fSupported = FALSE;
					(*prgLiteralInfo)[ulIndex].pwszLiteralValue = NULL;
					(*prgLiteralInfo)[ulIndex].pwszInvalidChars = NULL;
					(*prgLiteralInfo)[ulIndex].pwszInvalidStartingChars = NULL;
					(*prgLiteralInfo)[ulIndex].cchMaxLen = 0;
				}
			}
		} else
			hr = E_OUTOFMEMORY;

		if (FAILED(hr)) {
			CoTaskMemFree(*prgLiteralInfo);
			CoTaskMemFree(pCharBuffer);
			*pcLiteralInfo = 0;
			*prgLiteralInfo = NULL;
		}
		else if (NULL != pCharBuffer) 
			*ppCharBuffer = pCharBuffer;

		if (!fOneSupported && DB_S_ERRORSOCCURRED == hr) {
			hr = DB_E_ERRORSOCCURRED;		// no valid or supported literals returned
			CoTaskMemFree(pCharBuffer);
			*ppCharBuffer = NULL;
		}
		return hr;
	}

protected:
	const DBLITERALINFO *HasPredefinedLiteral(DBLITERAL lit)
	{
	T *pT = static_cast<T *>(this);
	ULONG ulCnt = 0;
	const DBLITERALINFO *plit = pT -> _LiteralSupport(&ulCnt);

		for (ULONG i = 0; i < ulCnt; ++i) {
			if (lit == plit[i].lt)
				return &plit[i];
		}
		return NULL;		// not found
	}
};

///////////////////////////////////////////////////////////////////////////////
// supporting macros for keyword map
#define BEGIN_DBINFO_KEYWORD_MAP(DataSource)	\
	static LPCOLESTR *_KeywordSupport(ULONG *pulKeywordCnt) { \
	static LPCOLESTR _rgKeywords[] = { 

#define KEYWORD_ENTRY(keyword) \
		(LPOLESTR)keyword,

#define END_DBINFO_KEYWORD_MAP() \
		NULL, }; *pulKeywordCnt = sizeof(_rgKeywords)/sizeof(_rgKeywords[0])-1; return _rgKeywords; }

// supporting macros for literal map
#define BEGIN_DBINFO_LITERAL_MAP(DataSource) \
	static const DBLITERALINFO *_LiteralSupport(ULONG *pulLiteralCnt) { \
	static const DBLITERALINFO _rgLiterals[] = {

#define LITERAL_ENTRY(literal, value, invchars, invstartchars, maxlen) \
		{ value, invchars, invstartchars, literal, TRUE, maxlen, }, 

#define END_DBINFO_LITERAL_MAP() \
		{NULL, NULL, NULL, DBLITERAL_INVALID, FALSE, 0}, }; \
		*pulLiteralCnt = sizeof(_rgLiterals)/sizeof(_rgLiterals[0])-1; return _rgLiterals; }

#endif // !defined(_IDBINFOIMPL_H__1679F11A_35B8_44B4_8BB9_51350A71121E__INCLUDED_)
