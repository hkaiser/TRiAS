// Dialogfenster, welches hochkommt, wenn WC_NOIDENT gemeldet wird
// File: DEFIDERR.CXX

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

#include "idignore.hxx"
#include "defiderr.hxx"
#include "identsdb.hxx"
#include "defident.hxx"

#include "identres.h"

// Überprüfen des fehlenden Idents und bei Bedarf Aufbauen des Dialogfensters -
// Result:	1 - ok, try again
//		2 - ok, do not try again
//		0 - cancel
short CIdentsDBExtension :: DefineNewIdent (long Ident, bool preDefine)
{
// wenn kein Ident gegeben ist 
	if (Ident == -1L) return 0;	// erstmal wieder raus

// wenn ohne zu fragen definiert werden soll
	if (preDefine) {
	DefineIdentDlg DIDlg (MWind(), ResID (DEFINEIDENT, &RF()));

		if (0 != Ident) {
			if (!DIDlg.FInit (Ident))
				return 0;
		} else {
			if (!DIDlg.FInit (""))		// neuen Ident erzeugen
				return 0;
		}
		DIDlg.Show (Centre);
		return DIDlg.GetIdent();	// liefert Ident
	}

	if (pIIL == NULL) 
		return 0;	// Fehler

// wenn alles ignoriert werden soll dann sofort wieder raus
	if (_AllIdentIgnore)
		return 2;

// Überprüfen, ob wir diesen Ident bereits kennen
	if (pIIL -> Find (Ident))
		return 2;	// immer ignorieren

// Fenster aufbauen und abfragen, was gemacht werden soll
short iResult = 0;

	if (m_lIdentHandled == -1L) {
		m_lIdentHandled = Ident;	// dieser Ident wird behandelt

	DefIdentError DIdErrDlg (MWind(), RF(), ResID (UNDEFINEDIDENT, &RF()), Ident);

		DIdErrDlg.Show();
		iResult = DIdErrDlg.Result();
	} else if (m_lIdentHandled == Ident) 
		return 2;
	else 
		return 0;

	switch (iResult) {
	case 1:		// neu definieren
		{
		DefineIdentDlg DIDlg (MWind(), ResID (DEFINEIDENT, &RF()));

			if (!DIDlg.FInit(Ident))
				return 0;
			DIDlg.Show (Centre);
			m_lIdentHandled = -1L;
			return DIDlg.Result();
		}
		break;

	case 2:		// im weiteren ignorieren
		m_lIdentHandled = -1L;
		if (!pIIL -> Add (Ident)) 
			return 0;
		break;

	case 3:		// im weiteren alles ignorieren
		m_lIdentHandled = -1L;
		_AllIdentIgnore = TRUE;
		break;

	case 0:	
		m_lIdentHandled = -1L;
		return 2;	// Message ignorieren
	}

return 2;	// ok, do not try again
}


// Löschen eines Satzes aus der PBD -------------------------------------------
bool CIdentsDBExtension :: DeleteIdent (long lIdent, bool fUndo)
{

	IDENTOBJECTCOUNT IDOC;

	INITSTRUCT(IDOC,IDENTOBJECTCOUNT);
	IDOC.ulIdent = (ulong) lIdent;
	IDOC.iOTypes = OTPunkt | OTLinie | OTFlaeche | OTText | OTKO;

	if (0 != DEX_GetIdentObjectCount(IDOC))
		return true;	// wenn Objektklasse noch Objekte besitzt, dann weiter

PBDDATA pbdData;

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;

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
				pIUndo -> InitDelete (PBDDATATYPE_IDENT, lIdent);
		}

#if _MSC_VER < 1100
		if (EC_OKAY == DEX_DelPBDData (pbdData)) {		// löschen
#else
		HPROJECT hPr = DEX_GetObjectsProject(lIdent);
		if (EC_OKAY == DEX_DelPBDDataEx (hPr,pbdData)) {		// löschen
#endif


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

#if _MSC_VER < 1100
	DEX_DelPBDData (hPr,pbdData);		// löschen
#else
	HPROJECT hPr = DEX_GetObjectsProject(lIdent);

	DEX_DelPBDDataEx (hPr,pbdData);		// löschen
#endif

	return TRUE;					// immer weiter machen (evtl. Fehler ignorieren)
}

// löschen aller Sätze aus der PBD --------------------------------------------
extern "C" 
BOOL _XTENSN_EXPORT PASCAL DeleteIdentFromPBD (long lIdent, BOOL, void *pData)
{
	return ((CIdentsDBExtension *)pData) -> DeleteIdent (lIdent, false);
}

bool CIdentsDBExtension :: DeleteAllIdents (HPROJECT hPr)
{
ENUMLONGKEY ENK;

	ENK.eKey = 'i';
	ENK.eFcn = (ENUMNOKEYLONGPROC)DeleteIdentFromPBD;
	ENK.ePtr = this;
	return DEX_EnumPBDDataEx (hPr, ENK);
}

// Kontextsensitive Hilfe -----------------------------------------------------
#if defined(WIN32)

#include "dlghelp.h"

static DWORD s_dwHelp[] = {
	IDOK,			IDH_DEFIDERR_OK,
	IDCANCEL,		IDH_DEFIDERR_CANCEL,
	IDB_DEFIDERRIGNORE,	IDH_DEFIDERR_IGNORE,
	IDB_DEFIDERRALLIGNORE,	IDH_DEFIDERR_IGNOREALL,
	IDT_DEFIDERRTEXT,	IDH_DEFIDERR_ERRTEXT,
	IDF_IERRORLOGO,		IDH_DEFIDERR_ERRTEXT,
	0,			0,		// EndeKennung
};

void DefIdentError :: HelpRequest (HelpRequestEvt e)
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

DefIdentError :: DefIdentError (pWindow pW, ResourceFile &RF, 
				ResID res, long Ident)
	       : DialogWindow (pW, res),
		 DefineButton (this, IDOK),
		 IgnoreButton (this, IDCANCEL),
		 CIgnoreButton (this, IDB_DEFIDERRIGNORE),
#if !defined(WIN32)
		 HelpButton (this, IDB_DEFIDERRHELP),
#endif
		 m_ILogo (this, ResID (IDF_IERRORLOGO, &RF), 
		 		ResID (IDBMP_IERRORLOGO, &RF))
{
#if !defined(WIN32)
// Controls initialisieren
	HelpButton.Disable();
#endif // !WIN32

// Ident merken
	_Ident = Ident;

// Texte aktualisieren
	m_pMessage = CHelpTextX :: CreateInstance (this, IDT_DEFIDERRTEXT);
	if (m_pMessage) {
	char tmpBuff[MAX_OKS_LENX];
	
		ClassFromIdentX (Ident, tmpBuff);
		m_pMessage -> SetHelpTextV (ResID (IDS_UNDEFINEDIDENT, &RF), g_cbTRiAS, tmpBuff);
	}

// Bildchen initialisieren
	m_ILogo.Init();
}

#pragma warning (default: 4355)

DefIdentError :: ~DefIdentError (void)
{
	DELETE_OBJ(m_pMessage);
}

void _XTENSN_EXPORT DefIdentError :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		EndDlg (1);		// Definieren
		break;

	case IDCANCEL:
		EndDlg (0);		// ignorieren
		break;

	case IDB_DEFIDERRHELP:
		break;

	case IDB_DEFIDERRIGNORE:	// im weiteren ignorieren
		EndDlg (2);	// ok
		break;

	case IDB_DEFIDERRALLIGNORE:
		EndDlg (3);		// im weiteren alles ignorieren
		break;
	}
}
