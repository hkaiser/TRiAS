// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: $$date_n_time$$
//
// @doc
// @module Usage.cpp | Kommandozeile auswerten, Help ausgeben

#include "stdafx.h"

#include "resource.h"
#include "$$safe_root$$App.h"

///////////////////////////////////////////////////////////////////////////////
// StartupLogo ausgeben
string C$$safe_root$$App::LoadStringRes (UINT uiID)
{
TCHAR cbBuffer[_MAX_PATH];
string str;

	if (!::LoadString (m_hInstance, uiID, cbBuffer, sizeof(cbBuffer)))
		throw false;

	str = cbBuffer;
	return str;
}

bool C$$safe_root$$App::PrintStartupLogo (void)
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
	_T("Usage: $$root$$ [options] infile"),
	_T("Options:"),
	_T("	-h	Outputs this message"),
	_T("	-oFile	Writes output to this file"),
	_T("	-n	print no logo"),
	NULL,
};

int C$$safe_root$$App::PrintUsage (void)
{
const TCHAR **pT = cbUsage;

	while (NULL != *pT) {
		fprintf (stderr, "%s\n", *pT);
		pT++;
	}
	return 2;
}
