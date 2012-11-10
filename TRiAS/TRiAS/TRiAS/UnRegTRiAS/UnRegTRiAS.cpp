// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 20.12.2000 11:45:48 
//
// @doc
// @module UnRegTRiAS.cpp | Definition of the <c CUnRegTRiAS> class

#include "StdAfx.h"
#include "Strings.h"

#include <initguid.h>
#include <TrCatIDs.h>
#include <WrongTrCatIDs.h>

bool TriasRegUnInit (bool fSilent = false, bool fFull = false);

bool ParseCmdString (const int argc, const char *argv[]) 
{
register int i;
register char *p;

/* Kommandozeile auswerten */
	for (i = 1; i < argc; ++i) {
		p = (char *)argv[i];
		if (*p == '-' || *p == '/') {
			++p; 
			switch (*p++) {
			case 's':
			case 'S':
				return true;		// do it silent

			default:
				break;
			}
		} 
	}
	return false;
}

void App::Start (const int argc, const char *argv[]) 
{
	CoInitialize(NULL);
	strcpy (g_cbTRiAS, g_cbCopyrightName);
	TriasRegUnInit(ParseCmdString(argc, argv), true);
	CoUninitialize();
}

///////////////////////////////////////////////////////////////////////////////
// Fake TRiAS
LRESULT EXPORTTRIAS WINAPI DexExtensionProc (WPARAM w, LPARAM l)
{
	_ASSERTE(FALSE);
	return FALSE;
}


