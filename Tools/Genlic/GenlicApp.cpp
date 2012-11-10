// $Header: $
// Copyright© 2003 Hartmut Kaiser, All rights reserved
// Created: 13.12.2003 19:54:19
//
// @doc
// @module GenlicApp.cpp | Implementation of the <c CGenlicApp> class

#include "stdafx.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>    
#include <io.h>        

#include "Genlic.h"
#include "GenlicApp.h"

#include "lmclient.h"
#include "lm_code.h"
#include "lm_attr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGenlicApp

IMPLEMENT_DYNCREATE(CGenlicApp, CWinApp)

CGenlicApp::CGenlicApp()
{
// command line support
	m_pOptArg = NULL;
	m_iOptIndex = 1;
	m_iOptError = 1;
	m_iInOpt = 0;

	m_fNoLogo = true;
}

CGenlicApp::~CGenlicApp()
{
}

BOOL CGenlicApp::InitInstance()
{
	return TRUE;
}

int CGenlicApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}

BEGIN_MESSAGE_MAP(CGenlicApp, CWinApp)
	//{{AFX_MSG_MAP(CGenlicApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
// CGenlicApp message handlers

int CGenlicApp::doWork (LPCTSTR pcLicenseDate)
{
	string strYear(pcLicenseDate);
	string strDay(pcLicenseDate);
	string strLicenseTemplate("FEATURE all TRiAS 20");
	
	strLicenseTemplate += strYear.substr(2, 2);
	strLicenseTemplate += ".";
	strLicenseTemplate += strDay.substr(4, 4);
	strLicenseTemplate += " permanent uncounted HOSTID=ANY ck=0 SIGN=0\n";

	return GenerateLicenseFile(strLicenseTemplate.c_str());	
}

///////////////////////////////////////////////////////////////////////////////
// Lizenzdatei erzeugen
int (*l_prikey_sign)() = 0;
static unsigned char lm_prikey[3][40] = {{0}};
static unsigned int lm_prisize[3] = {0x0, 0x0, 0x0};

int CGenlicApp::GenerateLicenseFile(char const *pcLicense)
{
	LM_HANDLE *lm_job = 0;

	LM_CODE(site_code, ENCRYPTION_SEED1, ENCRYPTION_SEED2, VENDOR_KEY1, 
		VENDOR_KEY2, VENDOR_KEY3, VENDOR_KEY4, VENDOR_KEY5); 

	LM_CODE_GEN_INIT(&site_code); 

	if (lc_init(0, VENDOR_NAME, &site_code, &lm_job)) 
	{
		lc_perror(lm_job, "lc_init failed");
		return -1;
	}

	char *outstr = 0;
	char *errs = 0;
	int retval = lc_cryptstr(lm_job, (char *)pcLicense, &outstr, &site_code, 
		LM_CRYPT_FORCE, 0, &errs);

	if (0 != retval) {
		fprintf(stderr, "%s\n", errs);
	}
	else {
		if (m_strOutFile.size() > 0) {
			FILE *of = fopen(m_strOutFile.c_str(), "w");

			if (0 != of)
			{
				fprintf(of, "%s\n", outstr);
				fclose(of);
			}
			else
			{
				retval = -2;
			}
		}
		else {
			fprintf(stdout, "%s\n", outstr);
		}
	}

	if (0 != errs)
	{
		lc_free_mem(lm_job, errs);
	}
	if (0 != outstr)
	{
		lc_free_mem(lm_job, outstr);
	}
	lc_free_job(lm_job);
	return retval;
}

///////////////////////////////////////////////////////////////////////////////
// Helper functions (command line support
int CGenlicApp::GetNextOption (int argc, char *argv[], char *optstring)
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
				fprintf(stderr, _T("Genlic: Illegal option flag: %c, use '-h' for list of options\n"), *opt);
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
int CGenlicApp::AnalyzeCmdLine (int iArgc, char *cbArgv[])
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
				fprintf (stderr, _T("Genlic: No output filename specified.\n"));
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

