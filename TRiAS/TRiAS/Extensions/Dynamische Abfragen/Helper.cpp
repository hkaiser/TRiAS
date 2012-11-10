// File Helper.cpp

#include "stdafx.h"
#include "DynQueryRes.h"

#include "Helper.h"

///////////////////////////////////////////////////////////////////////////////
// StreamHelper
HRESULT LoadLong (IStream *pIStm, long &riVal)
{
	return pIStm -> Read (&riVal, sizeof(long), NULL);
}

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

HRESULT SaveLong (IStream *pIStm, long iVal)
{
	return pIStm -> Write (&iVal, sizeof(long), NULL);
}

HRESULT SaveString (IStream *pIStm, os_string str)
{
long lCnt = str.size()+1;
HRESULT hr = pIStm -> Write (&lCnt, sizeof(long), NULL);

	if (FAILED(hr)) return hr;

	return pIStm -> Write (str.c_str(), lCnt, NULL);
}

DWORD GetSizeMax (os_string &rStr)
{
	return rStr.size() + sizeof(long) + 1;
}

