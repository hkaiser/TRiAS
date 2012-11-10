// Dialogfenster zur Definition einer RelationsBeschreibung in einer PBD
// File: DEFRELAT.CXX

#include "idntsdbp.hxx"

#if defined(WIN32)
#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#endif

#include <versions.h>
#include <errinstx.hxx>

#include "identres.h"
#include "defident.h"
#include "defrelat.hxx"

#define TEXTLEN 	32

// Kontextsensitive Hilfe -----------------------------------------------------
#if defined(WIN32)

#include "dlghelp.h"

static DWORD s_dwHelp[] = {
	IDOK,			IDH_DEFRCODEDLG_OK,
	IDCANCEL,		IDH_DEFRCODEDLG_CANCEL,
	IDF_AUXINFO,		IDH_DEFRCODEDLG_AUXINFO,
	IDT_PBDDB,		IDH_DEFRCODEDLG_PBDNAME,
	IDT_DEFRELDBNAME,	IDH_DEFRCODEDLG_PBDNAME,
	IDT_RCODE,		IDH_DEFRCODEDLG_RCODE,
	IDT_DEFRELRCODE,	IDH_DEFRCODEDLG_RCODE,
	IDG_RCODETYP,		IDH_DEFRCODEDLG_RCODETYP,
	IDR_DEFRELHORIZ,	IDH_DEFRCODEDLG_RELHORIZ,
	IDR_DEFRELKOMPLEX,	IDH_DEFRCODEDLG_RELKOMPLEX,
	IDG_RCODEDESC,		IDH_DEFRCODEDLG_RCODEDESC,
	IDT_SHORTDESC,		IDH_DEFRCODEDLG_SHORTDESC,
	IDE_DEFRELSHORT,	IDH_DEFRCODEDLG_SHORTDESC,
	IDT_LONGDESC,		IDH_DEFRCODEDLG_LONGDESC,
	IDE_DEFRELLONG,		IDH_DEFRCODEDLG_LONGDESC,
	0,			0,		// EndeKennung
};

void CDefineRelationDlg :: HelpRequest (HelpRequestEvt e)
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

CDefineRelationDlg :: CDefineRelationDlg (pWindow pW, ResID res, long lRCode)
		    : DialogWindow (pW, res),
		      m_OKButton (this, IDOK),
		      m_CancelButton (this, IDCANCEL),
#if !defined(WIN32)
		      m_HelpButton (this, IDB_DEFRELHELP),
#endif // !WIN32
		      m_EDRelation (this, IDT_DEFRELRCODE),
		      m_EDKurzText (this, IDE_DEFRELSHORT),
		      m_EDLangText (this, IDE_DEFRELLONG),
		      m_PBDName (this, IDT_DEFRELDBNAME),
		      m_RHorizRel (this, IDR_DEFRELHORIZ),
		      m_RKomplexRel (this, IDR_DEFRELKOMPLEX),
		      m_fIsValid (false)
{
#if !defined(WIN32)
// HelpButton passivieren
	m_HelpButton.Disable();
#endif // !WIN32

// Variablen initialisieren
char Buffer[20];

	m_lActRel = lRCode;
	m_EDRelation.SetText (ltoa (m_lActRel, Buffer, 10));

// PBDNamen setzen
char cbPbdName[_MAX_PATH];

	if (NULL != DEX_GetPBDName (cbPbdName)) 
		m_PBDName.SetText (cbPbdName);

// Einträge initialisieren
	if (lRCode == -1L) return;

	m_EDKurzText.SetTextLimit (TEXTLEN);

	{
	ErrInstall EI (WC_NORELATION);
	PBDRELATION pbdData;
	ErrCode RC; 

		INITSTRUCT(pbdData, PBDRELATION);
		pbdData.pbdTyp = 'r';
		pbdData.pbdCode = lRCode;
		pbdData.pbdKText = new char [TEXTLEN+2];	// gesucht
		pbdData.pbdLText = new char [1025];
		pbdData.pbdKTextLen = TEXTLEN+1;
		pbdData.pbdLTextLen = 1024;

	// PBD-Info holen
		if (pbdData.pbdKText) pbdData.pbdKText[0] = '\0';
		if (pbdData.pbdLText) pbdData.pbdLText[0] = '\0';
		if ((RC = DEX_GetPBDData (pbdData)) != EC_OKAY && 
		    RC != WC_NOTFOUND)
			return;

		if (pbdData.pbdKTextLen > 0) {
			pbdData.pbdKText[TEXTLEN] = '\0';
			m_EDKurzText.SetText (pbdData.pbdKText);
		}
		if (pbdData.pbdLTextLen > 0) 
			m_EDLangText.SetText (pbdData.pbdLText);

		switch (tolower (pbdData.ipbdRTyp)) {
		case 'h':	// gleichrangige Relation
		default:
			m_RHorizRel.SetState (true);
			break;

		case 'k':	// KomplexRelation
			m_RKomplexRel.SetState (true);
			break;
		}

	// Speicher wieder freigeben
		DELETE_OBJ(pbdData.pbdKText);
		DELETE_OBJ(pbdData.pbdLText);
	}
	m_EDKurzText.SetFocus();
	m_fIsValid = true;
}

#pragma warning (default: 4355)

// EventHandler ----------------------------------------------------------------
void _XTENSN_EXPORT CDefineRelationDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		{
		ErrInstall EI (WC_NORELATION);
		PBDRELATION pbdData;

			INITSTRUCT(pbdData, PBDRELATION);
			pbdData.pbdTyp = 'r';
			pbdData.pbdCode = m_lActRel;
			pbdData.pbdReserved = 0;
		
		// RelationsTyp setzen
			if (m_RHorizRel.GetState()) 
				pbdData.ipbdRTyp = 'H';
			else 
				pbdData.ipbdRTyp = 'K';

		char KT[TEXTLEN+1];
		int maxLen = 0;
		char *lT = new char [maxLen = m_EDLangText.GetTextLen()+1];
				
			m_EDKurzText.GetText (KT, TEXTLEN+1);
			pbdData.pbdKText = KT;
			pbdData.pbdKTextLen = strlen (KT);
			if (lT != NULL) {
				m_EDLangText.GetText (lT, maxLen);
				pbdData.pbdLText = lT;
				pbdData.pbdLTextLen = maxLen -1;
			}
#if defined(WIN32)
		ITriasXtensionSite *pXtsnSite = NULL;
		HRESULT hr = g_pTE -> GetXtensionSite (&pXtsnSite);
		LPUNDOREDOPBDDATA pIUndo = NULL;

			if (SUCCEEDED(hr)) {
				hr = pXtsnSite -> CreateInstance (NULL, CLSID_UndoRedoObject, 
							IID_IUndoRedoPBDData, (LPVOID *)&pIUndo);
				pXtsnSite -> Release();
				if (SUCCEEDED(hr))
					hr = pIUndo -> InitModify ((const PBDDATA *)&pbdData, NULL);
				if (FAILED(hr)) {
					pIUndo -> Release();
					pIUndo = NULL;
				}
			}
			if (EC_OKAY == DEX_ModPBDData (pbdData)) {
				if (pIUndo) 
					DEX_AddUndoRedo (pIUndo);
			}
			if (pIUndo) pIUndo -> Release();
#else
			DEX_ModPBDData (pbdData);
#endif // WIN32
			DEXN_PBDRCodeChanged (m_lActRel);
			App :: Exec (ExecWhileEvent);
			DELETE_OBJ(lT);
			EndDlg (1);	// ok und raus
		}
		break;

	case IDCANCEL:
		EndDlg (0);	// abbrechen
		break;

	case IDB_DEFIDHELP:
		break;
	}
}
