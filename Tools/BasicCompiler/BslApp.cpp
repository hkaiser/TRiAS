// Diese Applikation
// File BSLAPP.H

#include "bslp.h"
#include "BslApp.h"

#include <ospace/file/path.h>

CThisApp::CThisApp (void)
{
	m_hInstance = ::GetModuleHandle(NULL);
	m_fNoLogo = false;
	m_fCodeOnly = false;
	m_fVerbose = false;

	m_pOptArg = NULL;
	m_iOptIndex = 1;
	m_iOptError = 1;

	m_iInOpt = 0;
}

int CThisApp::GetNextOption (int argc, char *argv[], char *optstring)
{
char *opt;
	
	if(m_iOptIndex >= argc || *argv[m_iOptIndex] != '-' && m_iInOpt == 0)
		return(EOF);
	
	opt = argv[m_iOptIndex] + 1 + m_iInOpt;
	if(*opt == '-') {
		m_iOptIndex++;
		return(EOF);
	}
	
	if(*opt == '\0')
		opt = " ";
	
	while(*optstring++ != *opt) {
		if(*optstring == '\0') {
			if(m_iOptError)
				fprintf(stderr, "bsl: Illegal option flag: %c, use '-h' for list of options\n", *opt);
			return('?');
		}
	}
	if(*optstring == ':') {
		m_iInOpt = 0;
		m_iOptIndex++;
		if(opt[1] != '\0')
			m_pOptArg = &opt[1];
		else
			m_pOptArg = argv[m_iOptIndex++];
	} else {
		if(opt[1] != '\0')
			m_iInOpt++;
		else {
			m_iInOpt = 0;
			m_iOptIndex++;
		}
	}
	return(*opt);
}
		
///////////////////////////////////////////////////////////////////////////////
// Kommandozeile auswerten
int CThisApp::AnalyzeCmdLine (int iArgc, char *cbArgv[])
{
int c = EOF;

	while ((c = GetNextOption (iArgc, cbArgv, "cCD:d:hHnNo:O:u:Ui:I:vV")) != EOF) {
		switch (c) {
		case 'd':
		case 'D':
			if (NULL == m_pOptArg || *m_pOptArg == '\0') {
				fprintf (stderr, "bsl: Bad define option specified.\n");
				return BCL_CMDLINEERROR_BADDEFINE;
			}
			AddDefine (m_pOptArg);
			break;

		case 'U':
			RemoveAllDefines();
			break;

		case 'u':
			if (NULL == m_pOptArg || *m_pOptArg == '\0') {
				fprintf (stderr, "bsl: Bad undefine option specified.\n");
				return BCL_CMDLINEERROR_BADUNDEFINE;
			}
			RemoveDefine (m_pOptArg);
			break;

		case 'n':		// -nologo
		case 'N':
			m_fNoLogo = true;
			break;

		case 'c':		// code only
		case 'C':
			m_fCodeOnly = true;
			break;

		case 'h':
		case 'H':
		case '?':
			return PrintUsage(); 

		case 'o':		// output filename
		case 'O':
			if (NULL == m_pOptArg || *m_pOptArg == '\0') {
				fprintf (stderr, "bsl: No output filename specified.\n");
				return BCL_CMDLINEERROR_NOINPUTFILE;
			}
			m_strOutFile = m_pOptArg;
			break;

		case 'i':		// use this INI-File
		case 'I':
			if (NULL == m_pOptArg || *m_pOptArg == '\0') {
				fprintf (stderr, "bsl: No config filename specified.\n");
				return BCL_CMDLINEERROR_NOCONFIGFILE;
			}
			m_strIniFile = m_pOptArg;
			break;

		case 'v':		// Verbose
		case 'V':
			m_fVerbose = true;
			break;

		default:
			break;
		}
	}

	return 0;		// alles ok
}

bool CThisApp::AddDefine (const char *pcDefine)
{
	try {
	os_string str (pcDefine);
	int iPos = str.find_first_of("#=");

		if (os_npos != iPos) {
		os_string strKey = str.substr(0, iPos);
		os_string strValue = str.substr(iPos+1);

			if (strValue.size() == 0)
				strValue = "1";
			m_Defines.insert(strKey, strValue);
		} else {
			m_Defines.insert(str, "1");
		}
	} catch (...) {
		return false;
	}

	return true;
}

bool CThisApp::RemoveDefine (const char *pcDefine)
{
CDefines::iterator it = m_Defines.find (pcDefine);

	if (it != m_Defines.end()) {
		m_Defines.erase(it);
		return true;
	}
	return false;
}

bool CThisApp::RemoveAllDefines (void)
{
	m_Defines.erase();
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Helperroutine zum erzeugen des INI-Pfades
os_string CThisApp::GenIniPath (void)
{
	if (m_strIniFile.size() > 0)
		return m_strIniFile;

char cbBuffer[_MAX_PATH];
os_path inipath;

	GetModuleFileName (NULL, cbBuffer, sizeof(cbBuffer));
	inipath = os_string(cbBuffer);
	inipath.base ("bsl");
	inipath.extension ("ini");
	return os_string(inipath);
}

