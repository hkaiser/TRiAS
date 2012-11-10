// $Header: $
// Copyright© 2001 Hartmut Kaiser, All rights reserved
// Created: 11.04.2001 11:09:47 
//
// @doc
// @module Util.cpp | Definition of some helper functions

#include "StdAfx.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// FileHandling
bool TestFileRO (LPCSTR pcName, BOOL &rRO)
{
DWORD dwAttr = ::GetFileAttributes (pcName);

	if ((DWORD)-1 == dwAttr)
		return false;

	rRO = (FILE_ATTRIBUTE_READONLY & dwAttr) ? TRUE : FALSE;
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// eine beliebige Resource laden
BYTE *ReadResource (int iResID, DWORD &dwResSize, HINSTANCE hInstance)
{
	if (NULL == hInstance)
		hInstance = _Module.GetResourceInstance();

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
		ATLTRY(lpResult = new BYTE [dwResSize]);
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

