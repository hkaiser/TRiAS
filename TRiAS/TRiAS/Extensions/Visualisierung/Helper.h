///////////////////////////////////////////////////////////////////////////////
// File: Helper.h

#if !defined(_HELPER_H)
#define _HELPER_H

// StreamHelper
HRESULT LoadShort (IStream *pIStm, short &riVal);
HRESULT LoadLong (IStream *pIStm, long &riVal);
HRESULT LoadString (IStream *pIStm, string &rStr);
HRESULT LoadChunk (IStream *pIStm, void *pv, DWORD dwSize);

HRESULT SaveShort (IStream *pIStm, short iVal);
HRESULT SaveLong (IStream *pIStm, long iVal);
HRESULT SaveString (IStream *pIStm, string str);
HRESULT SaveChunk (IStream *pIStm, void *pv, DWORD dwSize);

DWORD GetSizeMax (string &rStr);

#endif // _HELPER_H
