// Dialogfenster, welches hochkommt, wenn PBDFehler gemeldet werden
// File: PBDERR.CXX

#include "idntsdbp.hxx"

#include "identsdb.h"
#include "pbderr.h"

#include <helptxtx.hxx>

#include "idignore.hxx"
#include "identsdb.hxx"
#include "pbderr.hxx"

#include "identres.h"

// Überprüfen der fehlenden Pbd und bei Bedarf Aufbauen des Dialogfensters -
// Result:	1 - ok, try again
//		2 - ok, do not try again
//		0 - cancel
short CIdentsDBExtension::DefineNewPbd (HPROJECT hPr)
{
// bei neuen Projekten wird gar nicht mehr gefragt ...
IStorage *pIStg = NULL;

	if (DEX_GetDataSourceStorage(hPr, pIStg)) {
		pIStg -> Release();
		return GenerateNewPbd (hPr) ? 1 : 0;
	}

CPbdError PbdErrDlg (MWind(), RF(), ResID (UNDEFINEDPBD, &RF()));

	if (!PbdErrDlg.Init()) 
		return 0;
		
	PbdErrDlg.Show();
	switch (PbdErrDlg.Result()) {
	case 1:
		return GenerateNewPbd(hPr) ? 1 : 0;
		
	case 0:
		break;

	case 2:
		return SelectNewPbdName(hPr) ? 1 : 0;
	}
	return 2;	// ok, do not try again
}


// Kontextsensitive Hilfe -----------------------------------------------------
#if defined(WIN32)

#include "dlghelp.h"

static DWORD s_dwHelp[] = {
	IDOK,			IDH_PBDERROR_OK,
	IDCANCEL,		IDH_PBDERROR_CANCEL,
	IDB_SELECTPBD,		IDH_PBDERROR_SELECTPBD,
	IDT_UNDEFINEDPBD,	IDH_PBDERROR_ERRTEXT,
	IDF_PERRORLOGO,		IDH_PBDERROR_ERRTEXT,
	0,			0,		// EndeKennung
};

void CPbdError::HelpRequest (HelpRequestEvt e)
{
	if (HelpWmHelp == e.RequestType()) {
	const HELPINFO *pHI = e.GetHelpInfo();
	char cbHelpFile[_MAX_PATH];

		strcpy (cbHelpFile, g_cbHelpPath);
		strcat (cbHelpFile, DIALOG_HELP_FILE);

		WinHelp ((HWND)pHI -> hItemHandle, cbHelpFile, 
			 HELP_WM_HELP, (DWORD)s_dwHelp);
	}
}

#endif // WIN32

// Konstruktor ----------------------------------------------------------------
#pragma warning (disable: 4355)
#pragma warning (disable: 4245)

CPbdError::CPbdError (pWindow pW, ResourceFile &RF, ResID res)
	   : DialogWindow (pW, res),
	     m_DefineButton (this, IDOK),
	     m_IgnoreButton (this, IDCANCEL),
		 m_pbSelectPbd (this, IDB_SELECTPBD),
#if !defined(WIN32)
	     m_HelpButton (this, IDB_UNDEFINEDPBDHELP),
#endif // !WIN32
	     m_PLogo (this, ResID (IDF_PERRORLOGO, &RF), 
		 ResID (IDBMP_PERRORLOGO, &RF))
{
#if !defined(WIN32)
// Controls initialisieren
	m_HelpButton.Disable();
#endif // !WIN32

// wenn COM-Projekt, dann nur neu erzeugen oder ignorieren
IStorage *pIStg = NULL;

	DEX_GetProjectStorage (pIStg);
	if (NULL != pIStg) {
		m_pbSelectPbd.Hide();
		pIStg -> Release();
	}

// Text ausgeben
	m_pMessage = CHelpTextX::CreateInstance (this, IDT_UNDEFINEDPBD);
	if (m_pMessage) 
		m_pMessage -> SetHelpText (ResID (IDS_UNDEFINEDPBD, &RF));
		
// Bildchen initialisieren
	m_PLogo.Init();
}

#pragma warning (default: 4355)
#pragma warning (default: 4245)

CPbdError::~CPbdError (void)
{
	DELETE_OBJ(m_pMessage);
}

bool CPbdError::Init (void)
{
	return true;
}


void _XTENSN_EXPORT CPbdError::ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		EndDlg (1);		// neu anlegen
		break;

	case IDCANCEL:
		EndDlg (0);		// ignorieren
		break;

	case IDB_SELECTPBD:		// andere auswählen
		EndDlg (2);
		break;
		
	case IDB_UNDEFINEDPBDHELP:
	default:
		break;
	}
}


