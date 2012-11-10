///////////////////////////////////////////////////////////////////////////////
// Kommandozeile auswerten, Help ausgeben

#include "bslp.h"

#include "bslr.h"
#include "BslApp.h"

///////////////////////////////////////////////////////////////////////////////
// StartupLogo ausgeben
os_string CThisApp::LoadStringRes (UINT uiID)
{
char cbBuffer[_MAX_PATH];
os_string str;

	if (!::LoadString (m_hInstance, uiID, cbBuffer, sizeof(cbBuffer)))
		throw false;

	str = cbBuffer;
	return str;
}

bool CThisApp::PrintStartupLogo (void)
{
	try {
	os_string strLogo = LoadStringRes (IDS_STARTUP);		// throws bool
	os_string strVersion = LoadStringRes (IDS_VERSION);
	os_string strCopyright = LoadStringRes (IDS_COPYRIGHT);
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
const char *cbUsage[] =
{
	"Usage: bsl [options] infile",
	"Options:",
	"	-c	Generate code only",
	"	-DCONSTANT[=VALUE]	Define preprocessor constant",
	"	-uCONSTANT		Undefine preprocessor constant",
	"	-U	Undefine all preprocessor constants",
	"	-h	Outputs this message",
	"	-n	Print no logo on startup",
	"	-oFile	Writes output to this file",
	"	-iFile	Use this File as bsl.ini",
	"	-v	Verbose",
	NULL,
};

int CThisApp::PrintUsage (void)
{
	if (m_fVerbose) {
		PrintStartupLogo();
		fprintf (stderr, "\n");
	}

const char **pT = cbUsage;

	while (NULL != *pT) {
		fprintf (stderr, "%s\n", *pT);
		pT++;
	}
	return 2;
}
