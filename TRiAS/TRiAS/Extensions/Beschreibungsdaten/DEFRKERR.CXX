// Dialogfenster, welches hochkommt, wenn WC_NORELATION gemeldet wird
// File: DEFRKERR.CXX

#include "idntsdbp.hxx"

#if defined(WIN32)
#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#endif

#include <helptxtx.hxx>

#include "Strings.h"
#include "identsdb.h"
#include "defiderr.h"
#include "defident.h"

#include "rkignore.hxx"
#include "defrkerr.hxx"

#include "identsdb.hxx"
#include "defrelat.hxx"

#include "identres.h"

// Überprüfen des fehlenden MCodes und bei Bedarf Aufbauen des Dialogfensters -
// Result:	1 - ok, try again
//		2 - ok, do not try again
//		0 - cancel
short CIdentsDBExtension :: DefineNewRCode (long lRCode, bool preDefine)
{
// wenn kein RelCode gegeben ist 
	if (lRCode == -1L) return 0;	// erstmal wieder raus

// wenn ohne zu fragen definiert werden soll
	if (preDefine) {
	CDefineRelationDlg DRCDlg (MWind(), ResID (DEFINERELATION, &RF()), lRCode);

		DRCDlg.Show (Centre);
		return 1;	// immer alles ok
	}

	if (pIRL == NULL) 
		return 0;	// Fehler

// wenn alles ignoriert werden soll dann sofort wieder raus
	if (_AllRCodeIgnore)
		return 2;

// Überprüfen, ob wir diesen MCode bereits kennen
	if (pIRL -> Find (lRCode))
		return 2;	// immer ignorieren

// Fenster aufbauen und abfragen, was gemacht werden soll
short iResult = 0;

	if (m_lRCodeHandled == -1L) {
		m_lRCodeHandled = lRCode;

	CDefRCodeError DRkErrDlg (MWind(), RF(), ResID (UNDEFINEDRELATION, &RF()), lRCode);

		DRkErrDlg.Show();
		iResult = DRkErrDlg.Result();
	} else if (m_lRCodeHandled == lRCode)
		return 2;
	else
		return 0;

	switch (iResult) {
	case 1:		// neu definieren
		{
		CDefineRelationDlg DRCDlg (MWind(), ResID (DEFINERELATION, &RF()), lRCode);

			DRCDlg.Show (Centre);
			m_lRCodeHandled = -1L;
			return DRCDlg.Result();
		}
		break;

	case 2:		// im weiteren ignorieren
		m_lRCodeHandled = -1L;
		if (!pIRL -> Add (lRCode)) 
			return 0;
		break;

	case 3:		// im weiteren alles ignorieren
		m_lRCodeHandled = -1L;
		_AllRCodeIgnore = TRUE;
		break;

	case 0:	
		m_lRCodeHandled = -1L;
		return 2;	// Message ignorieren
	}

return 2;	// ok, do not try again
}


// Löschen eines Satzes aus der PBD -------------------------------------------
bool CIdentsDBExtension :: DeleteRCode (long lRCode, bool fUndo)
{
PBDDATA pbdData;

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'r';
	pbdData.pbdCode = lRCode;

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
				pIUndo -> InitDelete (PBDDATATYPE_RELATION, lRCode);
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

return EC_OKAY == DEX_DelPBDData (pbdData);		// löschen
}

// löschen aller Sätze aus der PBD --------------------------------------------
extern "C" 
BOOL _XTENSN_EXPORT PASCAL DeleteRCodeFromPBD (long lRCode, BOOL, void *pData)
{
	return EC_OKAY == ((CIdentsDBExtension *)pData) -> DeleteRCode (lRCode, false);
}

bool CIdentsDBExtension :: DeleteAllRCodes (void)
{
ENUMLONGKEY ENK;

	ENK.eKey = 'r';
	ENK.eFcn = (ENUMNOKEYLONGPROC)DeleteRCodeFromPBD;
	ENK.ePtr = this;

return DEX_EnumPBDData (ENK);
}


// Kontextsensitive Hilfe -----------------------------------------------------
#if defined(WIN32)

#include "dlghelp.h"

static DWORD s_dwHelp[] = {
	IDOK,			IDH_DEFRKERR_OK,
	IDCANCEL,		IDH_DEFRKERR_CANCEL,
	IDB_DEFRELERRIGNORE,	IDH_DEFRKERR_IGNORE,
	IDB_DEFRELERRALLIGNORE,	IDH_DEFRKERR_IGNOREALL,
	IDT_DEFRELERRTEXT,	IDH_DEFRKERR_ERRTEXT,
	IDF_RERRORLOGO,		IDH_DEFRKERR_ERRTEXT,
	0,			0,		// EndeKennung
};

void CDefRCodeError :: HelpRequest (HelpRequestEvt e)
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

CDefRCodeError :: CDefRCodeError (pWindow pW, ResourceFile &RF, ResID res, long lRCode)
	        : DialogWindow (pW, res),
		  DefineButton (this, IDOK),
		  IgnoreButton (this, IDCANCEL),
		  CIgnoreButton (this, IDB_DEFRELERRIGNORE),
#if !defined(WIN32)
		  HelpButton (this, IDB_DEFRELERRHELP),
#endif // !WIN32
		  m_RLogo (this, ResID (IDF_RERRORLOGO, &RF), 
		 		 ResID (IDBMP_RERRORLOGO, &RF))
{
#if !defined(WIN32)
// Controls initialisieren
	HelpButton.Disable();
#endif // !WIN32

// RelCode merken
	m_lRCode = lRCode;

// Text aktualisieren
	m_pMessage = CHelpTextX :: CreateInstance (this, IDT_DEFRELERRTEXT);
	if (m_pMessage) 
		m_pMessage -> SetHelpTextV (ResID (IDS_UNDEFINEDRCODE, &RF), g_cbTRiAS, lRCode);
	
// Bildchen initialisieren
	m_RLogo.Init();
}

#pragma warning (default: 4355)

CDefRCodeError :: ~CDefRCodeError (void)
{
	DELETE_OBJ(m_pMessage);
}

void _XTENSN_EXPORT CDefRCodeError :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		EndDlg (1);		// Definieren
		break;

	case IDCANCEL:
		EndDlg (0);		// ignorieren
		break;

	case IDB_DEFRELERRHELP:
		break;

	case IDB_DEFRELERRIGNORE:	// im weiteren ignorieren
		EndDlg (2);	// ok
		break;

	case IDB_DEFRELERRALLIGNORE:
		EndDlg (3);		// im weiteren alles ignorieren
		break;
	}
}
