// Kommandozeilen-BasicScript compiler
// File: BSL.CPP

#include "bslp.h"

#include <ospace/file/path.h>

#include "ExtList.h"
#include "BslApp.h"

///////////////////////////////////////////////////////////////////////////////
// Routine liefert jeweils nächsten zu ladenden ExtensionModule
ebBOOL ebCALLBACK GetNextModule (ebLPSTR lpFileName, long lParam)
{
os_string str;
CExtList *pList = reinterpret_cast<CExtList *>(lParam);
bool fRet = pList -> GetNext (str);
	
	if (fRet) {
	// nächste zu ladende extension übergeben
		strcpy (lpFileName, str.c_str());
		if (pList -> GetVerbose())
			fprintf(stderr, "bsl: Loading extension: %s\n", lpFileName);

	// Arbeitsverzeichnis auf die zu ladende extension setzen
	os_path path = os_string (lpFileName);

		path.filename("");
		SetCurrentDirectory (os_string(path).c_str());
	}
	else {
	// ursprünglichews Arbeitsverzeichnis wieder einstellen
		SetCurrentDirectory (pList -> GetCurDir());
	}
	return fRet;
}

///////////////////////////////////////////////////////////////////////////////
// Hier geht's los
void main (int iArgc, char *cbArgv[])
{
	try {
	CThisApp BslApp;

	// Kommandozeile auswerten
	int iRet = BslApp.AnalyzeCmdLine (iArgc, cbArgv);

		if (0 != iRet) throw iRet;
		cbArgv += BslApp.OptIndex();
		iArgc -= BslApp.OptIndex();

	// Eingabedatei rauslösen
		if (iArgc < 1) {
			fprintf (stderr, "bsl: No input filename specified!\n");
			throw BCL_FATAL_NOINPUTFILE;
		}

	// StartupLogo ausgeben
		if (!BslApp.NoLogo() && !BslApp.PrintStartupLogo())
			throw BCL_FATAL_COULDNTPRINTLOGO;

	// BasicScript initialisieren
	os_string strIniPath = BslApp.GenIniPath();
	CExtList xtnList (strIniPath.c_str(), BslApp.GetVerbose());
	CebInstance ebInst (EBINIT_USECOMPILER|EBINIT_SEARCH_DIRECTORY|EBINIT_SEARCH_PROC,
						GetNextModule, (ebDWORD)&xtnList);

		if (ebInst.Create()) {
			fprintf (stderr, "bsl: Could not initialize BasicScript!\n");
			throw BCL_FATAL_COULDNTINITBASIC;
		}
		ebInst.SetPublicSpace (0x00100000L);			// 1MByte StringSpace

	// eigentliche Arbeit
		iRet = BslApp.CompileAndSave (ebInst, cbArgv[0]);
		if (0 != iRet) throw iRet;

	} catch (int iRet) {
		exit (iRet);
	}

// alles ok, wir sind fertig
	exit(0);
}

