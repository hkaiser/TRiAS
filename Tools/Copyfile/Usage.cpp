///////////////////////////////////////////////////////////////////////////////
// Kommandozeile auswerten, Help ausgeben

#include "StdAfx.h"

#include "resource.h"
#include "CopyFileApp.h"

///////////////////////////////////////////////////////////////////////////////
// StartupLogo ausgeben
string CThisApp::LoadStringRes (UINT uiID)
{
char cbBuffer[_MAX_PATH];
string str;

	if (!::LoadString (m_hInstance, uiID, cbBuffer, sizeof(cbBuffer)))
		throw false;

	str = cbBuffer;
	return str;
}

bool CThisApp::PrintStartupLogo (void)
{
	try {
	string strLogo = LoadStringRes (IDS_STARTUP);		// throws bool
	string strVersion = LoadStringRes (IDS_VERSION);
	string strCopyright = LoadStringRes (IDS_COPYRIGHT);
	char cbBuffer[_MAX_PATH];

		sprintf (cbBuffer, strLogo.c_str(), strVersion.c_str(), strCopyright.c_str());
		fprintf (stdout, cbBuffer);
	} catch (bool fResult) {
		return fResult;
	}

return true;
}

///////////////////////////////////////////////////////////////////////////////
// Help ausgeben
const char *cbUsage[] =
{
	"Usage: CopyFile [options] infile",
	"Options:",
	"	-cn	Copies n files as input[1..n]",
	"	-fn	Specifies the first used filenumber",
	"	-h	Outputs this message",
	"	-n	Print no logo on startup",
	NULL,
};

int CThisApp::PrintUsage (void)
{
const char **pT = cbUsage;

	while (NULL != *pT) {
		fprintf (stderr, "%s\n", *pT);
		pT++;
	}
	return 2;
}
