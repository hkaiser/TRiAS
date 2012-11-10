///////////////////////////////////////////////////////////////////////////////
// File: Helper.h

#if !defined(_HELPER_H)
#define _HELPER_H

// StreamHelper
HRESULT LoadLong (IStream *pIStm, long &riVal);
HRESULT LoadString (IStream *pIStm, os_string &rStr);

HRESULT SaveLong (IStream *pIStm, long iVal);
HRESULT SaveString (IStream *pIStm, os_string str);

DWORD GetSizeMax (os_string &rStr);

#endif // _HELPER_H
