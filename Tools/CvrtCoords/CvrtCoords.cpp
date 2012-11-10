// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 05.09.2002 11:39:44 
//
// @doc
// @module CvrtCoords.cpp | Definition of the <c CCvrtCoords> class

#include "stdafx.h"

#include "CvrtCoords.h"
#include "CvrtCoords_i.h"
#include "CvrtCoordsApp.h"
#include "TransformCallback.h"

#include "CvrtCoords_i.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY_NON_CREATEABLE(CTransformCallback)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

///////////////////////////////////////////////////////////////////////////////
class CInitCom
{
public:
	CInitCom() { CoInitialize(NULL); }
	~CInitCom() { CoUninitialize(); }
};
CInitCom g_InitCom;

CCvrtCoordsApp theApp;

int _tmain(int iArgc, TCHAR* cbArgv[], TCHAR* envp[])
{
	int nRetCode = 0;

// Kommandozeile auswerten
	nRetCode = theApp.AnalyzeCmdLine (iArgc, cbArgv);
	if (0 == nRetCode) {
		cbArgv += theApp.OptIndex();
		iArgc -= theApp.OptIndex();

	// StartupLogo ausgeben
		if (!theApp.GetNoLogo() && !theApp.PrintStartupLogo())
			nRetCode = 3;

	// Eingabedatei rauslösen
		if (iArgc < 1) {
			fprintf (stderr, _T("%sCvrtCoords: Keine Eingabedatei angegeben!\n"),
				theApp.GetNoLogo() ? "" : "\n");
			nRetCode = 3;
		}
		else if (iArgc < 2) {
			fprintf (stderr, _T("%sCvrtCoords: Keine Ausgabedatei angegeben!\n"),
				theApp.GetNoLogo() ? "" : "\n");
			nRetCode = 4;
		}

		if (0 == nRetCode)
			nRetCode = theApp.doWork (cbArgv[0], cbArgv[1]);
	}
	return nRetCode;
}


