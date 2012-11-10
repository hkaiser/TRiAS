// Funktionen zum Schreiben/Lesen in/von einen(m) Stream
// File: PERSISTHELPER.H

///////////////////////////////////////////////////////////////////////////////
// Deklarationen
HRESULT LoadString (IStream *pIStm, os_string &rStr);
HRESULT LoadLong (IStream *pIStm, long &riVal);

HRESULT SaveString (IStream *pIStm, os_string str);
HRESULT SaveLong (IStream *pIStm, long iVal);
DWORD GetSizeMax (os_string &rStr);

///////////////////////////////////////////////////////////////////////////////
// Definitionen
inline HRESULT LoadString (IStream *pIStm, os_string &rStr)
{
long lCnt = 0;
HRESULT hr = pIStm -> Read (&lCnt, sizeof(long), NULL);

	if (FAILED(hr)) return hr;

char cbBuffer[256];

	ASSERT(lCnt < sizeof(cbBuffer));
	hr = pIStm -> Read (cbBuffer, lCnt, NULL);
	if (FAILED(hr)) return hr;

	rStr = cbBuffer;
	return S_OK;
}

inline HRESULT LoadLong (IStream *pIStm, long &riVal)
{
	return pIStm -> Read (&riVal, sizeof(long), NULL);
}

inline HRESULT SaveString (IStream *pIStm, os_string str)
{
long lCnt = str.size()+1;
HRESULT hr = pIStm -> Write (&lCnt, sizeof(long), NULL);

	if (FAILED(hr)) return hr;

	return pIStm -> Write (str.c_str(), lCnt, NULL);
}

inline HRESULT SaveLong (IStream *pIStm, long iVal)
{
	return pIStm -> Write (&iVal, sizeof(long), NULL);
}

inline DWORD GetSizeMax (os_string &rStr)
{
	return rStr.size() + sizeof(long) + 1;
}
