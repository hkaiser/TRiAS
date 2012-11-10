// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/11/1998 08:28:25 PM
//
// @doc
// @module Resource.cpp | Laden einer nutzerdefinierten Ressource

#include "trias03p.hxx"

#include <limits.h>
#include <dbdtempl.h>
#include <funcs03.h>

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

BYTE *ReadResource (HINSTANCE hInstance, int iResID, DWORD &dwResSize) 
{
BYTE *lpResult = NULL;

//  Resource laden
HRSRC hFindRes = FindResource (hInstance, MAKEINTRESOURCE (iResID), MAKEINTRESOURCE (ID_DBDTEMPLATE));
HGLOBAL hRes = LoadResource (hInstance, hFindRes);

	if (!hFindRes || !hRes) return NULL;

//  Resource im Speicher festhalten
BYTE *lpResource = (BYTE *)LockResource (hRes);

	if (lpResource) {	    // wenn Resource erfolgreich geladen
	// Resource in Buffer kopieren
		if ((dwResSize = SizeofResource (hInstance, hFindRes)) == 0)
			return NULL;

	// einfach umkopieren
		TX_TRY(lpResult = new BYTE [dwResSize]);
		if (NULL == lpResult) return NULL;

		CopyMemory(lpResult, lpResource, dwResSize);

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

