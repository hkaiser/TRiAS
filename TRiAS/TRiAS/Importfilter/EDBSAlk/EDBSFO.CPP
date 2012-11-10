///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			edbsfo.cpp
//
//	Stand:			15.11.1994
//	Beschreibung:	EDBS-Datei öffnen
//	Entwicklung:	15.11.94	Beginn der Kodierung
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "edbsfo.hpp"

extern "C" {
extern HWND __hWndM;
}

///////////////////////////////////////////////////////////////////////
//	COpenEDBSFile

static char BASED_CODE szFilter[] = "EDBS-Daten (*.e)|*.e?; *.e??| Alle Dateien (*.*)|*.*||";

//	Konstruktion  -----------------------------------------------------
COpenEDBSFile :: COpenEDBSFile()
{	
	CFileDialog* m_pCFileDialog = new CFileDialog( TRUE, NULL, NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, CWnd::FromHandle( __hWndM ) /*AfxGetMainWnd()*/);

	m_strFileName = new CString;

	if ( m_pCFileDialog )
	{	m_pCFileDialog -> DoModal();
		*m_strFileName = m_pCFileDialog -> GetPathName();
		delete m_pCFileDialog;
		m_pCFileDialog = NULL;;
	}
}

//	Destruktion  ------------------------------------------------------
COpenEDBSFile :: ~COpenEDBSFile()
{	if ( m_strFileName ) delete m_strFileName;
	m_strFileName = NULL;
}

//	GetPathName  ------------------------------------------------------
CString COpenEDBSFile :: GetPathName()
{	return *m_strFileName;
}	// GetPathName
