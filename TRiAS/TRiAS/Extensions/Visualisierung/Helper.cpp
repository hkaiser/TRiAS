// File Helper.cpp

#include "visobjp.hxx"
#include "visobj.h"
#include "resource.h"

#include "Helper.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// StreamHelper
HRESULT LoadShort (IStream *pIStm, short &riVal)
{
	return pIStm -> Read (&riVal, sizeof(short), NULL);
}

HRESULT LoadLong (IStream *pIStm, long &riVal)
{
	return pIStm -> Read (&riVal, sizeof(long), NULL);
}

HRESULT LoadString (IStream *pIStm, string &rStr)
{
long lCnt = 0;
HRESULT hr = pIStm -> Read (&lCnt, sizeof(long), NULL);

	if (FAILED(hr)) return hr;

char cbBuffer[256];

	TX_ASSERT(lCnt < sizeof(cbBuffer));
	ZeroMemory (cbBuffer, sizeof(cbBuffer));

	hr = pIStm -> Read (cbBuffer, lCnt, NULL);
	if (FAILED(hr)) return hr;

	rStr = cbBuffer;
	return S_OK;
}

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

HRESULT SaveShort (IStream *pIStm, short iVal)
{
	return pIStm -> Write (&iVal, sizeof(short), NULL);
}

HRESULT SaveLong (IStream *pIStm, long iVal)
{
	return pIStm -> Write (&iVal, sizeof(long), NULL);
}

HRESULT SaveString (IStream *pIStm, string str)
{
long lCnt = str.length()+1;
HRESULT hr = pIStm -> Write (&lCnt, sizeof(long), NULL);

	if (FAILED(hr)) return hr;

	return pIStm -> Write (str.c_str(), lCnt, NULL);
}

HRESULT SaveChunk (IStream *pIStm, void *pv, DWORD dwSize)
{
HRESULT hr = pIStm -> Write (&dwSize, sizeof(DWORD), NULL);

	if (FAILED(hr)) return hr;

	return pIStm -> Write (pv, dwSize, NULL);
}

DWORD GetSizeMax (string &rStr)
{
	return rStr.length() + sizeof(long) + 1;
}

