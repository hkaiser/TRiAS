// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: $$date_n_time$$
//
// @doc
// @module $$safe_root$$App.cpp | Implementation of the <c C$$safe_root$$App> class

#include "stdafx.h"
#include "$$root$$.h"
#include "$$safe_root$$App.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C$$safe_root$$App

IMPLEMENT_DYNCREATE(C$$safe_root$$App, CWinApp)

C$$safe_root$$App::C$$safe_root$$App()
{
// command line support
	m_pOptArg = NULL;
	m_iOptIndex = 1;
	m_iOptError = 1;
	m_iInOpt = 0;

	m_fNoLogo = false;
}

C$$safe_root$$App::~C$$safe_root$$App()
{
}

BOOL C$$safe_root$$App::InitInstance()
{
	return TRUE;
}

int C$$safe_root$$App::ExitInstance()
{
	return CWinApp::ExitInstance();
}

BEGIN_MESSAGE_MAP(C$$safe_root$$App, CWinApp)
	//{{AFX_MSG_MAP(C$$safe_root$$App)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
// C$$safe_root$$App message handlers

int C$$safe_root$$App::doWork (LPCTSTR pcInFile)
{
	// TODO: do the main application work
	return 0;	// TODO: return error code
}

///////////////////////////////////////////////////////////////////////////////
// Helper functions (command line support
int C$$safe_root$$App::GetNextOption (int argc, char *argv[], char *optstring)
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
				fprintf(stderr, _T("$$root$$: Illegal option flag: %c, use '-h' for list of options\n"), *opt);
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
int C$$safe_root$$App::AnalyzeCmdLine (int iArgc, char *cbArgv[])
{
int c = EOF;

	while ((c = GetNextOption (iArgc, cbArgv, "hH?o:O:vVnN")) != EOF) {
		switch (c) {
		case 'h':
		case 'H':
		case '?':
			return PrintUsage(); 

		case 'o':		// output filename
		case 'O':
			if (NULL == m_pOptArg || *m_pOptArg == '\0') {
				fprintf (stderr, _T("$$root$$: No output filename specified.\n"));
				return 2;
			}
			m_strOutFile = m_pOptArg;
			break;

		case 'v':		// print version info
		case 'V':
			return PrintStartupLogo();

		case 'n':		// nologo
		case 'N':
			m_fNoLogo = true;
			break;

		default:
			break;
		}
	}
	return 0;		// alles ok
}

