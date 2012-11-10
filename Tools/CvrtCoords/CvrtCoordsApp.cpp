// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 05.09.2002 11:39:36 
//
// @doc
// @module CvrtCoordsApp.cpp | Definition of the <c CCvrtCoordsApp> class

#include "stdafx.h"

#include <Atl/Ciid.h>
#include <ospace/file/path.h>

#include "CvrtCoords.h"
#include "CvrtCoords_i.h"
#include "CvrtCoordsApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const TCHAR g_cbProgIdPrefix[] = _T("CvrtCoords.");
const TCHAR g_cbDefaultProgId[] = _T("Bna");

/////////////////////////////////////////////////////////////////////////////
// CCvrtCoordsApp

CCvrtCoordsApp::CCvrtCoordsApp() 
{
// command line support
	m_pOptArg = NULL;
	m_iOptIndex = 1;
	m_iOptError = 0;
	m_iInOpt = 0;

	m_fNoLogo = false;
	m_pCallback = NULL;

	m_hInstance = GetModuleHandle(NULL);
}

CCvrtCoordsApp::~CCvrtCoordsApp()
{
	if (NULL != m_pCallback) {
		m_Transform -> put_Callback(NULL);
		m_pCallback -> Release();
		m_pCallback = NULL;
	}
}

int CCvrtCoordsApp::doWork (LPCTSTR pcInFile, LPCSTR pcOutFile)
{
// Koordinatensysteme initialisieren
	if (0 != m_strInCoordFile.size() || 0 != m_strOutCoordFile.size()) {
		if (0 == m_strInCoordFile.size())
			m_strInCoordFile = _T("BeGk12_3");
		if (0 == m_strOutCoordFile.size())
			m_strOutCoordFile = _T("BeGk12_3");
	}

HRESULT hr = S_OK;

	if (0 != m_strInCoordFile.size() && 0 != m_strOutCoordFile.size()) {
		if (FAILED(hr = m_CoordSys.LoadCSIn(m_strInCoordFile.c_str()))) {
			fprintf (stderr, (CLASS_E_NOTLICENSED == hr) ? 
				"%sDie Koordinatensystemmodule sind nicht lizensiert." :
				"%sKann Eingabe-Koordinatensystem '%s' nicht laden.", 
				m_fNoLogo ? "" : "\n", m_strInCoordFile.c_str());
			return 2;
		}
		if (FAILED(m_CoordSys.LoadCSOut(m_strOutCoordFile.c_str()))) {
			fprintf (stderr, (CLASS_E_NOTLICENSED == hr) ? 
				"%sDie Koordinatensystemmodule sind nicht lizensiert." :
				"%sKann Ausgabe-Koordinatensystem '%s' nicht laden.", 
				m_fNoLogo ? "" : "\n", m_strOutCoordFile.c_str());
			return 2;
		}
	}

// TransformationsEngine laden
	if (0 == m_strFormatProgId.size()) {
	os_path infile = string(pcInFile);

		m_strFormatProgId = g_cbProgIdPrefix;
		if (0 != infile.has_extension())
			m_strFormatProgId += infile.extension();
		else
			m_strFormatProgId += g_cbDefaultProgId;
	}
	else {
		m_strFormatProgId = string(g_cbProgIdPrefix) + m_strFormatProgId;
	}

CIID Guid (m_strFormatProgId.c_str(), CIID::INITCIID_InitFromProgId);

	if (FAILED(m_Transform.CreateInstance(Guid))) {
		fprintf(stderr, "%sKann Dateiformatsmodule '%s' nicht laden.\n", 
			m_fNoLogo ? "" : "\n", m_strFormatProgId.c_str());
		return 3;
	}

CComObject<CTransformCallback> *pCallback;

	if (FAILED(hr = CComObject<CTransformCallback>::CreateInstance(&pCallback))) {
		fprintf (stderr, "%sInterner Fehler: %lx.", 
			m_fNoLogo ? "" : "\n", hr);
		return 4;
	}

	pCallback->SetParent(this);
	m_pCallback = pCallback;
	m_pCallback->AddRef();
	if (FAILED(m_Transform->put_Callback(pCallback))) {
		fprintf (stderr, "%sInterner Fehler: %lx.", 
			m_fNoLogo ? "" : "\n", hr);
		return 4;
	}

// ggf. Version der Engine anzeigen	
	if (!m_fNoLogo) 
		PrintModuleVersion();

// jetzt eigentliche Verarbeitung
	return ConvertCoords(pcInFile, pcOutFile);
}

///////////////////////////////////////////////////////////////////////////////
// Helper functions (command line support
int CCvrtCoordsApp::GetNextOption (int argc, char *argv[], char *optstring)
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
			if(m_iOptError) {
				fprintf(stderr, _T("%sCvrtCoords: Nicht erlaubte Option: %c,\n"
					"benutzen Sie '-h' um eine Liste der gültigen Optionen zu "
					"erhalten.\n"), m_fNoLogo ? "" : "\n", *opt);
				return('?');
			}
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
int CCvrtCoordsApp::AnalyzeCmdLine (int iArgc, char *cbArgv[])
{
int c = EOF;

	while ((c = GetNextOption (iArgc, cbArgv, "hH?o:O:i:I:t:T:vVnNlL")) != EOF) {
		switch (c) {
		case 'h':
		case 'H':
		case '?':
			return PrintUsage(); 

		case 'o':		// output filename
		case 'O':
			if (NULL == m_pOptArg || *m_pOptArg == '\0') {
				fprintf (stderr, _T("%sCvrtCoords: Kein Ausgabe-Koordinatensystem"
					" angegeben.\n"), m_fNoLogo ? "" : "\n");
				return 2;
			}
			m_strOutCoordFile = m_pOptArg;
			break;

		case 'v':		// print version info
		case 'V':
			return PrintStartupLogo();

		case 'n':		// nologo
		case 'N':
			m_fNoLogo = true;
			break;

		case 'i':
		case 'I':
			if (NULL == m_pOptArg || *m_pOptArg == '\0') {
				fprintf (stderr, _T("%sCvrtCoords: Kein Eingabe-Koordinatensystem"
					" angegeben.\n"), m_fNoLogo ? "" : "\n");
				return 2;
			}
			m_strInCoordFile = m_pOptArg;
			break;

		case 'e':
		case 'E':
			if (NULL == m_pOptArg || *m_pOptArg == '\0') {
				fprintf (stderr, _T("%sCvrtCoords: Kein Dateiformat angegeben.\n"),
					m_fNoLogo ? "" : "\n");
				return 2;
			}
			m_strFormatProgId = m_pOptArg;
			break;

		case 'l':
		case 'L':
			if (!m_fNoLogo)
				PrintStartupLogo();
			return PrintCoordSystems();
			
		default:
			break;
		}
	}
	return 0;		// alles ok
}

///////////////////////////////////////////////////////////////////////////////
// workhorses
int CCvrtCoordsApp::ConvertCoords(LPCSTR pcInFile, LPCSTR pcOutFile)
{
FILE *pInFile = fopen(pcInFile, "rt");

	if (NULL == pcInFile) {
		fprintf (stderr, _T("%sCvrtCoords: Kann Eingabedatei '%s' nicht öffnen.\n"),
			m_fNoLogo ? "" : "\n", pcInFile);
		return 5;
	}

FILE *pOutFile = fopen(pcOutFile, "w+t");

	if (NULL == pcOutFile) {
		fprintf (stderr, _T("%sCvrtCoords: Kann Ausgabedatei '%s' nicht öffnen.\n"),
			m_fNoLogo ? "" : "\n", pcOutFile);
		fclose(pInFile);
		return 6;
	}

// Alle Zeilen der Datei transformieren lassen
char cbBuffer[5*_MAX_PATH];

	USES_CONVERSION;
	while (NULL != fgets(cbBuffer, sizeof(cbBuffer), pInFile)) {
	CComBSTR bstrOut(cbBuffer);

		if (FAILED(m_Transform->TransformLineOfText(CComBSTR(cbBuffer), &bstrOut)))
			break;

		if (EOF == fputs(ATLW2AHELPER((LPSTR)cbBuffer, bstrOut, (bstrOut.Length()+1)*2), pOutFile)) {
			fprintf (stderr, _T("%sCvrtCoords: Kann in Ausgabedatei '%s' nicht mehr schreiben.\n"),
				m_fNoLogo ? "" : "\n", pcOutFile);
			break;
		}
	}
	fclose(pOutFile);
	fclose(pInFile);
	return 0;
}

HRESULT CCvrtCoordsApp::TransformCoords (double *pdX, double *pdY)
{
	_ASSERTE(NULL != pdX && NULL != pdY);

	if (m_CoordSys.IsValid()) 
	{
		RETURN_FAILED_HRESULT(m_CoordSys.Transform (1, pdX, pdY));
	}
	return S_OK;
}


