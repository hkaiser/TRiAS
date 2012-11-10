// Liste der zu ladenden Erweiterungsmodule
// File: EXTLIST.H

#include "bslp.h"

#include <ospace/file/path.h>

#include "ExtList.h"

///////////////////////////////////////////////////////////////////////////////
// Initialisierung
CExtList::CExtList (LPCSTR pcIniName, bool fVerbose)
	: m_it(end()), m_fVerbose(fVerbose)
{
// aktuelles Arbeitsverzeichnis speichern
char cbBuffer[_MAX_PATH];

	GetCurrentDirectory (sizeof(cbBuffer), cbBuffer);
	m_strCurDir = cbBuffer;

// Ini Datei laden
char *pBuffer = NULL;

	try {
	// Section einlesen
		pBuffer = new char [32*_MAX_PATH];
	
	int iRet = GetPrivateProfileSection ("Extensions", pBuffer, 32*_MAX_PATH, pcIniName);

		if (0 == iRet) {
		char cbBuffer[_MAX_PATH];

			GetModuleFileName (NULL, cbBuffer, sizeof(cbBuffer));

		os_path modulepath = os_string (cbBuffer);
		os_path path = os_string (pcIniName);

			modulepath.filename (path.filename());

			if (GetVerbose()) 
				fprintf (stderr, "bsl: Could'nt find %s.\nbsl: Trying to load %s.\n", pcIniName, os_string(modulepath).c_str());

			iRet = GetPrivateProfileSection ("Extensions", pBuffer, 32*_MAX_PATH, os_string(modulepath).c_str());
			if (0 == iRet) {
				if (GetVerbose()) 
					fprintf(stderr, "Could'nt find %s. Ignoring config file.\n", os_string(modulepath).c_str());
				throw BCL_MESSAGE_NOINISECTION;
			}
		}

	// Section auseinandernehmen
	size_type iPos = os_npos;
	char *pT = pBuffer;

		while ('\0' != *pT) {
		os_string str = pT;

			iPos = str.find ('=');
			pT += str.length()+1;

			if (os_npos != iPos) 
				push_back(str.substr(iPos+1));
		}

	// iterator auf ersten Eintrag stellen
		Reset();

	// aufräumen
		delete pBuffer;
		pBuffer = NULL;

	} catch (...) {
		if (NULL != pBuffer) 
			delete pBuffer;
	}
}

void CExtList::Reset (void)
{
	if (size() > 0) 
		m_it = begin();
	else
		m_it = end();
}

bool CExtList::GetNext (os_string &rStr)
{
	if (m_it != end()) {
		rStr = *m_it++;
		return true;
	}

	return false;
}

