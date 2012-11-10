// Dialogfenster, welches hochkommt, wenn WC_NOMERKMAL gemeldet wird
// File: DEFMKERR.CXX

#include "idntsdbp.hxx"

#if defined(WIN32)
#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#endif

#include "Strings.h"
#include "identsdb.h"
#include "defiderr.h"
#include "defident.h"

#include <helptxtx.hxx>

#include "mkignore.hxx"
#include "defmkerr.hxx"

#include "identsdb.hxx"
#include "defmerkm.hxx"

#include "identres.h"


#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


// Überprüfen des fehlenden MCodes und bei Bedarf Aufbauen des Dialogfensters -
// Result:	1 - ok, try again
//		2 - ok, do not try again
//		0 - cancel
short CIdentsDBExtension :: DefineNewMCode (long MCode, bool preDefine)
{
// wenn kein MCode gegeben ist 
	if (MCode == -1L) return 0;	// erstmal wieder raus

#pragma MESSAGE("Wo kriege ich denn hier den Ident her ?")
LONG lIdent = 0L;

// wenn ohne zu fragen definiert werden soll
	if (preDefine) {
	DefineMerkmalDlg DMCDlg (MWind(), ResID (DEFINEMERKMAL, &RF()), MCode, lIdent, NULL, NULL);

		DMCDlg.Show (Centre);
		return 1;	// immer alles ok
	}

	if (pIML == NULL) 
		return 0;	// Fehler

// wenn alles ignoriert werden soll dann sofort wieder raus
	if (_AllMCodeIgnore)
		return 2;

// Überprüfen, ob wir diesen MCode bereits kennen
	if (pIML -> Find (MCode))
		return 2;	// immer ignorieren

// Fenster aufbauen und abfragen, was gemacht werden soll
short iResult = 0;

	if (m_lMCodeHandled == -1L) {
		m_lMCodeHandled = MCode;

	DefMCodeError DMkErrDlg (MWind(), RF(), ResID (UNDEFINEDMERKMAL, &RF()), 
				 MCode, NULL);

		DMkErrDlg.Show();
		iResult = DMkErrDlg.Result();
	} else if (m_lMCodeHandled == MCode)
		return 2;
	else 
		return 0;
		

	switch (iResult) {
	case 1:		// neu definieren
		{
		DefineMerkmalDlg DMCDlg (MWind(), ResID (DEFINEMERKMAL, &RF()), 
					 MCode, lIdent, NULL, NULL);

			DMCDlg.Show (Centre);
			m_lMCodeHandled = -1L;
			return DMCDlg.Result();
		}
		break;

	case 2:		// im weiteren ignorieren
		m_lMCodeHandled = -1L;
		if (!pIML -> Add (MCode)) 
			return 0;
		break;

	case 3:		// im weiteren alles ignorieren
		m_lMCodeHandled = -1L;
		_AllMCodeIgnore = TRUE;
		break;

	case 0:	
		m_lMCodeHandled = -1L;
		return 2;	// Message ignorieren
	}

return 2;	// ok, do not try again
}


// Löschen eines Satzes aus der PBD -------------------------------------------
bool CIdentsDBExtension :: DeleteMCode (long lMCode, long lIdent,bool fUndo)
{
//PBDDATA pbdData;
PBDMERKMALEX pbdData;

//	INITSTRUCT(pbdData, PBDDATA);
	INITSTRUCT(pbdData, PBDMERKMALEX);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = lMCode;
	pbdData.lIdent = lIdent;

#if defined(WIN32)
	if (fUndo) {
	ITriasXtensionSite *pXtsnSite = NULL;
	HRESULT hr = g_pTE -> GetXtensionSite (&pXtsnSite);
	LPUNDOREDOPBDDATA pIUndo = NULL;

		if (SUCCEEDED(hr)) {
			hr = pXtsnSite -> CreateInstance (NULL, CLSID_UndoRedoObject, 
						IID_IUndoRedoPBDData, (LPVOID *)&pIUndo);
			pXtsnSite -> Release();
			if (SUCCEEDED(hr))
				pIUndo -> InitDelete (PBDDATATYPE_FEATURE, lMCode);
		}

		if (EC_OKAY == DEX_DelPBDData (pbdData)) {		// löschen

			if (pIUndo) {
				DEX_AddUndoRedo (pIUndo);
				pIUndo -> Release();
			}
			return true;
		}
		if (pIUndo) pIUndo -> Release();

		return false;
	} 
#endif // WIN32

	DEX_DelPBDData (pbdData);		// löschen
	return TRUE;					// immer weiter machen
}

// löschen aller Sätze aus der PBD --------------------------------------------
extern "C" 
BOOL _XTENSN_EXPORT PASCAL DeleteMCodeFromPBD (long lMCode, BOOL, void *pData)
{
	long lIdent = 0L;
	return EC_OKAY == ((CIdentsDBExtension *)pData) -> DeleteMCode (lMCode, lIdent, false);
}

bool CIdentsDBExtension :: DeleteAllMCodes (HPROJECT hPr)
{
ENUMLONGKEY ENK;

	ENK.eKey = 'm';
	ENK.eFcn = (ENUMNOKEYLONGPROC)DeleteMCodeFromPBD;
	ENK.ePtr = this;
	return DEX_EnumPBDDataEx (hPr, ENK);
}


// Kontextsensitive Hilfe -----------------------------------------------------
#if defined(WIN32)

#include "dlghelp.h"

static DWORD s_dwHelp[] = {
	IDOK,			IDH_DEFMKERR_OK,
	IDCANCEL,		IDH_DEFMKERR_CANCEL,
	IDB_DEFMKERRIGNORE,	IDH_DEFMKERR_IGNORE,
	IDB_DEFMKERRALLIGNORE,	IDH_DEFMKERR_IGNOREALL,
	IDT_DEFMKERRTEXT,	IDH_DEFMKERR_ERRTEXT,
	IDF_MERRORLOGO,		IDH_DEFMKERR_ERRTEXT,
	0,			0,		// EndeKennung
};

void DefMCodeError :: HelpRequest (HelpRequestEvt e)
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

DefMCodeError :: DefMCodeError (pWindow pW, ResourceFile &RF, ResID res, 
				long MCode, short iMkBase)
	       : DialogWindow (pW, res),
		 DefineButton (this, IDOK),
		 IgnoreButton (this, IDCANCEL),
		 CIgnoreButton (this, IDB_DEFMKERRIGNORE),
#if !defined(WIN32)
		 HelpButton (this, IDB_DEFMKERRHELP),
#endif // !WIN32
		 m_MLogo (this, ResID (IDF_MERRORLOGO, &RF), 
		 		ResID (IDBMP_MERRORLOGO, &RF))
{
#if !defined(WIN32)
// Controls initialisieren
	HelpButton.Disable();
#endif // !WIN32

// MCode merken
	_MCode = MCode;

// Text aktualisieren
	m_pMessage = CHelpTextX :: CreateInstance (this, IDT_DEFMKERRTEXT);
	if (m_pMessage) {
	char tmpBuff[30];
	
		m_pMessage -> SetHelpTextV (ResID (IDS_UNDEFINEDMCODE, &RF), g_cbTRiAS,
					    ultoa (MCode, tmpBuff, iMkBase));
	}
	
// Bildchen initialisieren
	m_MLogo.Init();
}

#pragma warning (default: 4355)

DefMCodeError :: ~DefMCodeError (void)
{
	DELETE_OBJ(m_pMessage);
}


void _XTENSN_EXPORT DefMCodeError :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		EndDlg (1);		// Definieren
		break;

	case IDCANCEL:
		EndDlg (0);		// ignorieren
		break;

	case IDB_DEFMKERRHELP:
		break;

	case IDB_DEFMKERRIGNORE:	// im weiteren ignorieren
		EndDlg (2);	// ok
		break;

	case IDB_DEFMKERRALLIGNORE:
		EndDlg (3);		// im weiteren alles ignorieren
		break;
	}
}
