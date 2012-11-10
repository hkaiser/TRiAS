// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 09.09.2002 10:01:19
//
// @doc
// @module ColorResApp.cpp | Implementation of the <c CColorResApp> class

#include "stdafx.h"

#include <ospace/file/path.h>
#include <ospace/string/tokenize.h>

#include "ColorRes.h"
#include "ColorResApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorResApp

IMPLEMENT_DYNCREATE(CColorResApp, CWinApp)

CColorResApp::CColorResApp()
{
// command line support
	m_pOptArg = NULL;
	m_iOptIndex = 1;
	m_iOptError = 1;
	m_iInOpt = 0;

	m_fNoLogo = false;
	m_fCopyTfw = false;
    m_fReduceColors = false;
	m_uiResizeMode = SIZE_NORMAL;
	m_vecKoeffs.push_back(1.0);

	m_LeadTools.EnsureLoaded();
}

CColorResApp::~CColorResApp()
{
}

BOOL CColorResApp::InitInstance()
{
	return TRUE;
}

int CColorResApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}

BEGIN_MESSAGE_MAP(CColorResApp, CWinApp)
	//{{AFX_MSG_MAP(CColorResApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
// CColorResApp message handlers

int CColorResApp::doWork (LPCTSTR pcInFile, LPCSTR pcOutFile)
{
// Parameter des Eingabebildes abfragen
L_INT nErrorCode;
LBitmapBase InPict;

	nErrorCode = InPict.Load(const_cast<LPTSTR>(pcInFile));
	if (nErrorCode < 1) {
		fprintf (stderr, LBase::GetErrorString (nErrorCode));
		return nErrorCode;
	}
		
// einzelne Bilder erzeugen
LBitmapList ResultPicts;

	nErrorCode = ResultPicts.Create();
	if (nErrorCode < 1) {
		fprintf (stderr, LBase::GetErrorString (nErrorCode));
		return nErrorCode;
	}

	for (vector<double>::iterator it = m_vecKoeffs.begin(); it != m_vecKoeffs.end(); ++it) {
	// Resample 
	LBitmapBase PictToCvrt;
	L_INT iWidth = InPict.GetWidth();
	L_INT iHeight = InPict.GetHeight();
    FILEINFO fileinfo;

        fileinfo.Flags = 0;
		nErrorCode = PictToCvrt.LoadResize(const_cast<LPTSTR>(pcInFile), 
			L_INT(iWidth * (*it)), L_INT(iHeight * (*it)), 0, 
			m_uiResizeMode, ORDER_RGB, NULL, &fileinfo);

		if (nErrorCode < 1) {
			fprintf (stderr, LBase::GetErrorString (nErrorCode));
			return nErrorCode;
		}

	// Farbreduktion (nur, wenn gefordert)
        if (m_fReduceColors) {
		    nErrorCode = PictToCvrt.ColorRes(8, CRF_OPTIMIZEDPALETTE|CRF_NODITHERING);
		    if (nErrorCode < 1) {
			    fprintf (stderr, LBase::GetErrorString (nErrorCode));
			    return nErrorCode;
		    }
        }

	// in Ausgabeliste einbauen
		nErrorCode = ResultPicts.InsertItem(&PictToCvrt);
		if (nErrorCode < 1) {
			fprintf (stderr, LBase::GetErrorString (nErrorCode));
			return nErrorCode;
		}

	// nächstes Bild 
	} 

	nErrorCode = ResultPicts.Save(const_cast<LPTSTR>(pcOutFile), FILE_TIFLZW, 8, 1);
	if (nErrorCode < 1) {
		fprintf (stderr, LBase::GetErrorString (nErrorCode));
		return nErrorCode;
	}

	if (m_fCopyTfw) {
	// ggf. *.tfw mitkopieren
	os_path tfwfile (pcInFile);
	os_path outtfwfile (pcOutFile);

		tfwfile.extension("tfw");
		outtfwfile.extension("tfw");

		if (tfwfile != outtfwfile) 
			CopyFile (os_string(tfwfile).c_str(), os_string(outtfwfile).c_str(), FALSE);
	}

	return 0;	// TODO: return error code
}

///////////////////////////////////////////////////////////////////////////////
// Helper functions (command line support
int CColorResApp::GetNextOption (int argc, char *argv[], char *optstring)
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
				fprintf(stderr, _T("ColorRes: Ungültige Option: %c.\n"
					"Benutzen Sie die Option '-h' um eine Liste der gültigen Opeten zu erhalten.\n"), 
					*opt);
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
int CColorResApp::AnalyzeCmdLine (int iArgc, char *cbArgv[])
{
int c = EOF;

	while ((c = GetNextOption (iArgc, cbArgv, "hH?vVnNtTr:R:i:I:c:C:")) != EOF) {
		switch (c) {
		case 'h':
		case 'H':
		case '?':
			return PrintUsage(); 

		case 'v':		// print version info
		case 'V':
			return PrintStartupLogo();

		case 'n':		// nologo
		case 'N':
			m_fNoLogo = true;
			break;

		case 't':
		case 'T':
			m_fCopyTfw = true;
			break;

		case 'c':
		case 'C':
			if (NULL == m_pOptArg || *m_pOptArg == '\0') 
			    m_fReduceColors = true;
            else if ('-' == *m_pOptArg)
                m_fReduceColors = false;
			break;

		case 'r':
		case 'R':
			if (NULL == m_pOptArg || *m_pOptArg == '\0') 
				return PrintUsage();
			if (!FillResolutions(m_pOptArg))
				return PrintUsage();
			break;

		case 'i':
		case 'I':
			if (NULL == m_pOptArg || *m_pOptArg == '\0') 
				m_uiResizeMode = SIZE_NORMAL;
			else {
			int iMode = atol(m_pOptArg);

				switch (iMode) {
				case 0:
				default:
					m_uiResizeMode = SIZE_NORMAL;
					break;

				case 1:
					m_uiResizeMode = SIZE_RESAMPLE;
					break;

				case 2:
					m_uiResizeMode = SIZE_BICUBIC;
					break;
				}
			}
			break;

		default:
			break;
		}
	}
	return 0;		// alles ok
}

bool CColorResApp::FillResolutions(LPCSTR pcOptArgs)
{
os_tokenizer token(",", false, "", "", "", false);
vector<os_string> tokens = token.tokenize(pcOptArgs);

	if (0 == tokens.size())
		return false;

	m_vecKoeffs.clear();
	//m_vecKoeffs.push_back(1.0);

	for (vector<os_string>::iterator it = tokens.begin();
		 it != tokens.end(); ++it)
	{
	int iKoeff = atol((*it).c_str());

		if (0 != iKoeff)
			m_vecKoeffs.push_back(1.0/iKoeff);
	}
	return true;
}
