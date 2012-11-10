///////////////////////////////////////////////////////////////////////////
// @doc 
// @module StreamHelper.h | StreamHelper

#if !defined(_STREAMHELPER_H__42990694_B83F_11D1_85B5_00600875138A__INCLUDED_)
#define _STREAMHELPER_H__42990694_B83F_11D1_85B5_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

inline
HRESULT LoadShort (IStream *pIStm, short &riVal)
{
	return pIStm -> Read (&riVal, sizeof(short), NULL);
}

inline
HRESULT LoadLong (IStream *pIStm, long &riVal)
{
	return pIStm -> Read (&riVal, sizeof(long), NULL);
}

inline
HRESULT LoadString (IStream *pIStm, os_string &rStr)
{
long lCnt = 0;
HRESULT hr = pIStm -> Read (&lCnt, sizeof(long), NULL);

	if (FAILED(hr)) return hr;

char cbBuffer[256];

	ASSERT(lCnt < sizeof(cbBuffer));
	ZeroMemory (cbBuffer, sizeof(cbBuffer));

	hr = pIStm -> Read (cbBuffer, lCnt, NULL);
	if (FAILED(hr)) return hr;

	rStr = cbBuffer;
	return S_OK;
}

inline
HRESULT LoadChunk (IStream *pIStm, void *pv, DWORD dwSize)
{
DWORD lCnt = 0;
HRESULT hr = pIStm -> Read (&lCnt, sizeof(DWORD), NULL);

	if (FAILED(hr)) return hr;
	if (lCnt > dwSize)
		return E_INVALIDARG;

	ZeroMemory (pv, dwSize);

ULONG lRead = 0;

	hr = pIStm -> Read (pv, lCnt, &lRead);
	if (lRead != lCnt) hr = E_FAIL;

	return hr;
}

inline
HRESULT SaveShort (IStream *pIStm, short iVal)
{
	return pIStm -> Write (&iVal, sizeof(short), NULL);
}

inline
HRESULT SaveLong (IStream *pIStm, long iVal)
{
	return pIStm -> Write (&iVal, sizeof(long), NULL);
}

inline
HRESULT SaveString (IStream *pIStm, os_string str)
{
long lCnt = str.length()+1;
HRESULT hr = pIStm -> Write (&lCnt, sizeof(long), NULL);

	if (FAILED(hr)) return hr;

	return pIStm -> Write (str.c_str(), lCnt, NULL);
}

inline
HRESULT SaveChunk (IStream *pIStm, void *pv, DWORD dwSize)
{
HRESULT hr = pIStm -> Write (&dwSize, sizeof(DWORD), NULL);

	if (FAILED(hr)) return hr;

	return pIStm -> Write (pv, dwSize, NULL);
}

inline
DWORD GetSizeMax (os_string &rStr)
{
	return rStr.length() + sizeof(long) + 1;
}

#endif // !defined(_STREAMHELPER_H__42990694_B83F_11D1_85B5_00600875138A__INCLUDED_)
