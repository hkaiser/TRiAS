///////////////////////////////////////////////////////////////////////////////
// Hier geht's los
// File: CopyFileMain.cpp

#include "StdAfx.h"
#include "CopyFileApp.h"
#include "CopyFileError.h"
#include "MakeName.h"

void main (int iArgc, char *cbArgv[])
{
	try {
	CThisApp CopyFileApp;

	// Kommandozeile auswerten
	int iRet = CopyFileApp.AnalyzeCmdLine (iArgc, cbArgv);

		if (0 != iRet) throw iRet;
		cbArgv += CopyFileApp.OptIndex();
		iArgc -= CopyFileApp.OptIndex();

	// Eingabedatei rauslösen
		if (iArgc < 1) {
			fprintf (stderr, "No input filename specified!\n");
			throw COPYFILE_FATAL_NOINPUTFILE;
		}

	// StartupLogo ausgeben
		if (!CopyFileApp.NoLogo() && !CopyFileApp.PrintStartupLogo())
			throw COPYFILE_FATAL_COULDNTPRINTLOGO;

		if (!CopyFileApp.doWork(cbArgv[0]))
			throw COPYFILE_ERROR_ONWORK;

	} catch (int iRet) {
		exit (iRet);
	}

// alles ok, wir sind fertig
	exit(0);
}

// Eigentliches Kopieren
bool CThisApp::doWork(LPCSTR pcInput)
{
string str;
CMakeName Name (pcInput, GetFirstCount(), GetMaxCount(), GetAppendChar());
int i = 0;

	while (Name.GetNextName (str)) {
		if (0 == (i%10))  {
			fprintf (stderr, "FileName: %s\r", str.c_str());
			fflush (stderr);
		}
		i++;
		CopyFile (pcInput, str.c_str(), false);
	}
	fprintf(stderr, "\n");
	return true;
}
