// Laden einer nutzerdefinierten Ressource ------------------------------------
// File: RESOURCE.CXX

#include "triaspre.hxx"

// Liest eine nutzerdefinierte Resource ein und kopiert diese in einen 
// dynamisch allozierten Speicherbereich

#if !defined(WIN32)
#pragma function (memcpy)	// memcpy als Funktion rufen
#endif

#if !defined(__min)
#define __min(a,b)	((a) < (b) ? (a) : (b))
#endif

#if defined(__WATCOMC__)
#pragma warning 604 5;		// lookahead required
#pragma warning 595 5;		// resolved as an expression
#endif

char *ReadResource (HINSTANCE hInstance, int iResID, DWORD &dwResSize) 
{
char *lpResult;

//  Resource laden
HRSRC hFindRes = FindResource (hInstance, MAKEINTRESOURCE (iResID), 
					  MAKEINTRESOURCE (ID_DBDTEMPLATE));
HGLOBAL hRes = LoadResource (hInstance, hFindRes);

	if (!hFindRes || !hRes) return NULL;

//  Resource im Speicher festhalten
char *lpResource = (char *)LockResource (hRes);

	if (lpResource) {	    // wenn Resource erfolgreich geladen
	// Resource in Buffer kopieren
		if ((dwResSize = SizeofResource (hInstance, hFindRes)) == 0)
			return NULL;

		if (dwResSize > UINT_MAX) {
		HGLOBAL hGbl = GlobalAlloc (GHND, dwResSize);

			if (hGbl == 0) {
				UnlockResource (hRes);
				FreeResource (hRes);
				return NULL;
			}
			lpResult = (char *)GlobalLock (hGbl);
		} else
			lpResult = new char [dwResSize];

		if (lpResult == NULL) {
			UnlockResource (hRes);
			FreeResource (hRes);
			return NULL;
		}

	// Resource umkopieren
	DWORD dwTSize = dwResSize;
	char *lpT = lpResult;
	
		while (dwTSize > 0) {
		short iLen = short (__min (long(SHRT_MAX), dwTSize));
		
			memcpy (lpT, lpResource, iLen);
			lpT = (char __huge *)lpT + iLen;
			lpResource = (char __huge *)lpResource + iLen;
			dwTSize -= iLen;
		}
		
	// Resource wieder freigeben
		UnlockResource (hRes);
		FreeResource (hRes);
	} else {
	// Resource existiert nicht
		FreeResource (hRes);
		return NULL;
	}

return lpResult;
}

