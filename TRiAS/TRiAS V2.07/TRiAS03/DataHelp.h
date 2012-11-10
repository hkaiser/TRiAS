// Diverse Hilfsfunktionen
// File: DATAHELP.H

#if !defined(_DATAHELP_H)
#define _DATAHELP_H

HRESULT LoadLong (IStream *pIStm, long &riVal);
HRESULT LoadString (IStream *pIStm, os_string &rStr);
HRESULT SaveLong (IStream *pIStm, long iVal);
HRESULT SaveString (IStream *pIStm, os_string str);
DWORD GetSizeMax (os_string &rStr);

#endif // _DATAHELP_H
