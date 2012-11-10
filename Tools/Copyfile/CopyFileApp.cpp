// Diese Applikation
// File COPYFILEAPP.CPP

#include "StdAfx.h"
#include "CopyFileApp.h"
#include "CopyFileError.h"

CThisApp::CThisApp (void)
{
	m_hInstance = ::GetModuleHandle(NULL);

	m_pOptArg = NULL;
	m_iOptIndex = 1;
	m_iOptError = 1;

	m_fNoLogo = false;
	m_iMax = 1;
	m_iFirst = 1;
	m_iAppendChar = '\0';

	m_iInOpt = 0;
}

int CThisApp::GetNextOption (int argc, char *argv[], char *optstring)
{
char *opt;
	
	m_iInOpt = 0;
	
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
				fprintf(stderr, "Illegal option flag: %c, use '-h' for list of options\n", *opt);
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

	while ((c = GetNextOption (iArgc, cbArgv, "hnc:f:a:")) != EOF) {
		switch (c) {
		case 'n':		// -nologo
			m_fNoLogo = true;
			break;

		case 'c':		// Anzahl der Kopien
			if (NULL == m_pOptArg || *m_pOptArg == '\0') {
				fprintf (stderr, "Bad count option specified.\n");
				return COPYFILE_CMDLINEERROR_BADCOUNT;
			}
			m_iMax = atol (m_pOptArg);
			break;

		case 'f':		// erste Nummer
			if (NULL == m_pOptArg || *m_pOptArg == '\0') {
				fprintf (stderr, "Bad first count option specified.\n");
				return COPYFILE_CMDLINEERROR_BADCOUNT;
			}
			m_iFirst = atol (m_pOptArg);
			break;

		case 'a':		// append character
			if (NULL == m_pOptArg || *m_pOptArg == '\0') {
				fprintf (stderr, "Bad first count option specified.\n");
				return COPYFILE_CMDLINEERROR_BADCOUNT;
			}
			m_iAppendChar = *m_pOptArg;
			break;

		case 'h':
		case '?':
			return PrintUsage(); 

		default:
			return 1;
		}
	}

	return 0;		// alles ok
}

