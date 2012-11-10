// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: $$date_n_time$$
//
// @doc
// @module $$root$$.cpp | Defines the entry point for the console application.

#include "stdafx.h"
#include "$$root$$.h"
#include "$$safe_root$$App.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

C$$safe_root$$App theApp;

using namespace std;

int _tmain(int iArgc, TCHAR* cbArgv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else {
	// Kommandozeile auswerten
		nRetCode = theApp.AnalyzeCmdLine (iArgc, cbArgv);
		if (0 == nRetCode) {
			cbArgv += theApp.OptIndex();
			iArgc -= theApp.OptIndex();

		// StartupLogo ausgeben
			if (!theApp.NoLogo() && !theApp.PrintStartupLogo())
				nRetCode = 3;

		// Eingabedatei rauslösen
			if (iArgc < 1) {
				fprintf (stderr, _T("$$root$$: No input filename specified!\n"));
				nRetCode = 3;
			}

			if (0 == nRetCode)
				nRetCode = theApp.doWork (cbArgv[0]);
		}
	}
	return nRetCode;
}


