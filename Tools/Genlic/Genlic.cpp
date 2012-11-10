// $Header: $
// Copyright© 2003 Hartmut Kaiser, All rights reserved
// Created: 13.12.2003 19:54:19
//
// @doc
// @module Genlic.cpp | Defines the entry point for the console application.

#include "stdafx.h"
#include "Genlic.h"
#include "GenlicApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CGenlicApp theApp;

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
				fprintf (stderr, _T("Genlic: No license date specified!\n"));
				nRetCode = 3;
			}

			if (0 == nRetCode)
				nRetCode = theApp.doWork (cbArgv[0]);
		}
	}
	return nRetCode;
}


