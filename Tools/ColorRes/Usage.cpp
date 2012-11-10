// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 09.09.2002 10:01:19
//
// @doc
// @module Usage.cpp | Kommandozeile auswerten, Help ausgeben

#include "stdafx.h"

#include "resource.h"
#include "ColorResApp.h"

///////////////////////////////////////////////////////////////////////////////
// StartupLogo ausgeben
string CColorResApp::LoadStringRes (UINT uiID)
{
TCHAR cbBuffer[_MAX_PATH];
string str;

	if (!::LoadString (m_hInstance, uiID, cbBuffer, sizeof(cbBuffer)))
		throw false;

	str = cbBuffer;
	return str;
}

bool CColorResApp::PrintStartupLogo (void)
{
	try {
	string strLogo = LoadStringRes (IDS_STARTUP);		// throws bool
	string strVersion = LoadStringRes (IDS_VERSION);
	string strCopyright = LoadStringRes (IDS_COPYRIGHT);
	char cbBuffer[_MAX_PATH];

		sprintf (cbBuffer, strLogo.c_str(), strVersion.c_str(), strCopyright.c_str());
		fprintf (stdout, cbBuffer);
	} 
	catch (bool fResult) {
		return fResult;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Help ausgeben
const TCHAR *cbUsage[] =
{
	_T("Usage: ColorRes [Optionen] Eingabedatei Ausgabedatei"),
	_T("Mˆgliche Optionen:"),
	_T("    -h	       Gibt diese Meldung aus"),
	_T("    -n	       UnterdrÅckt die Ausgabe des Programmlogos"),
	_T("    -t         Kopiert ggf. existierende *.tfw Datei"),
	_T("    -rKoeffs   Liste der Grî·enkoeffizienten (z.B. -r2,5,10)"),
	_T("    -iMode     Art der Interpolation (0: normal, 1: linear, 2: bikubisch)"),
	_T("    -c[-]      Farbreduktion [nicht] durchfÅhren"),
	NULL,
};

int CColorResApp::PrintUsage (void)
{
const TCHAR **pT = cbUsage;

	while (NULL != *pT) {
		fprintf (stderr, "%s\n", *pT);
		pT++;
	}
	return 2;
}
