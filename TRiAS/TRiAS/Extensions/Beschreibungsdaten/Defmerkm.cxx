// Dialogfenster zur Definition einer MerkmalsBeschreibung in einer PBD
// File: DEFMERKM.CXX

#include "idntsdbp.hxx"

#include <versions.h>
#include <errinstx.hxx>
#include <eieruhr.hxx>

#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface

#include "defident.h"
#include "identres.h"
#include "defmerkm.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define TEXTLEN 	_MAX_PATH

// Notvariante für TRiAS-DB
#define TRIASTEXTLEN 		32			// KK991108

// Kontextsensitive Hilfe -----------------------------------------------------
#include "dlghelp.h"

static DWORD s_dwHelp[] = {
	IDOK,			IDH_DEFMCODEDLG_OK,
	IDCANCEL,		IDH_DEFMCODEDLG_CANCEL,
	IDF_AUXINFO,		IDH_DEFMCODEDLG_AUXINFO,
	IDT_PBDDB,		IDH_DEFMCODEDLG_PBDNAME,
	IDT_DEFMKDBNAME,	IDH_DEFMCODEDLG_PBDNAME,
	IDT_MCODE,		IDH_DEFMCODEDLG_MCODE,
	IDT_DEFMKMCODE,		IDH_DEFMCODEDLG_MCODE,
	IDG_MCODETYP,		IDH_DEFMCODEDLG_MCODETYP,
	IDR_DEFMKTEXT,		IDH_DEFMCODEDLG_DEFMKTEXT,
	IDR_DEFMKINT,		IDH_DEFMCODEDLG_DEFMKINT,
	IDR_DEFMKFLOAT,		IDH_DEFMCODEDLG_DEFMKFLOAT,
	IDG_MCODETARGET,	IDH_DEFMCODEDLG_MCODETARGET,
	IDR_OBJMERKMAL,		IDH_DEFMCODEDLG_OBJMERKMAL,
	IDR_IDENTMERKMAL,	IDH_DEFMCODEDLG_IDENTMERKMAL,
	IDR_SICHTMERKMAL,	IDH_DEFMCODEDLG_SICHTMERKMAL,
	IDCB_SYSTEMFLAG,	IDH_DEFMCODEDLG_SYSTEMFLAG,
	IDC_READONLY,		IDH_DEFMCODEDLG_READONLY,
	IDG_MCODEDESC,		IDH_DEFMCODEDLG_MCODEDESC,
	IDT_SHORTDESC,		IDH_DEFMCODEDLG_SHORTDESC,
	IDE_DEFMKSHORT,		IDH_DEFMCODEDLG_SHORTDESC,
	IDT_LONGDESC,		IDH_DEFMCODEDLG_LONGDESC,
	IDE_DEFMKLONG,		IDH_DEFMCODEDLG_LONGDESC,
	0,			0,		// EndeKennung
};

void DefineMerkmalDlg::HelpRequest (HelpRequestEvt e)
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

// Konstruktor ----------------------------------------------------------------
#pragma warning (disable: 4355)

DefineMerkmalDlg::DefineMerkmalDlg (
	pWindow pW, ResID res, long MCode, long lIdent, LPCSTR pcClass, 
	LPCSTR pcNewProp, bool fShowAdminDlg)
		  : DialogWindow (pW, res),
		    OKButton (this, IDOK),
		    CancelButton (this, IDCANCEL),
		    m_cbReadOnly (this, IDC_READONLY),
		    EDKurzText (this, IDE_DEFMKSHORT),
		    EDLangText (this, IDE_DEFMKLONG),
		    PBDName (this, IDT_DEFMKDBNAME),
		    m_cbSystemFlag (this, IDCB_SYSTEMFLAG),
			m_rbObject(this, IDC_OBJECTPROP),
			m_rbView (this, IDC_VIEWPROP),
			m_rbClass (this, IDC_CLASSPROP),
		    isValid (false), m_fShowAdminDlg(fShowAdminDlg)
{
CEierUhr Wait(this);

	if (!(QMSysAdmin & DEX_QueryMode())) {
		m_cbSystemFlag.Disable();
		m_cbSystemFlag.Hide();
	}

	if (!m_fShowAdminDlg) {
		m_rbObject.Hide();
		m_rbObject.Disable();
		m_rbView.Hide();
		m_rbView.Disable();
		m_rbClass.Hide();
		m_rbClass.Disable();
	}

// Variablen initialisieren
	TX_ASSERT(MCode != -1L);
	_actMC = MCode;
	_actID = lIdent;
	m_fIsSystem = false;

// PBDName enthält jetzt Objektklassennamen
	if (NULL != pcClass) PBDName.SetText (pcClass);

// KK991109 - Notlösung für TRiAS
// Einträge initialisieren
	EDKurzText.SetTextLimit (TRIASTEXTLEN);

	{
	ErrInstall EI (WC_NOMERKMAL);
	PBDMERKMAL pbdData;
	ErrCode RC;
	char cbKText[TEXTLEN+2];
	char cbLText[1024];

		INITSTRUCT(pbdData, PBDMERKMAL);
		pbdData.pbdTyp = 'm';
		pbdData.pbdCode = MCode;
		pbdData.pbdKText = cbKText;	// gesucht
		pbdData.pbdLText = cbLText;
		pbdData.pbdKTextLen = TEXTLEN+1;
		pbdData.pbdLTextLen = 1024;
		pbdData.ipbdMTyp = 'u';			// unknown

	// PBD-Info holen
		pbdData.pbdKText[0] = '\0';
		pbdData.pbdLText[0] = '\0';

		RC = DEX_GetPBDData (pbdData);
		if (EC_OKAY == RC || WC_RETURN == RC) {
			if (pbdData.pbdKTextLen > 0) {
				pbdData.pbdKText[TEXTLEN] = '\0';
				EDKurzText.SetText (pbdData.pbdKText);
			}
			if (pbdData.pbdLTextLen > 0) 
				EDLangText.SetText (pbdData.pbdLText);

		short mkTyp = pbdData.ipbdMTyp;
		
			m_fIsSystem = (mkTyp & PBDMERKMAL_SYSTEMFLAG) ? true : false;
			if (QMSysAdmin & DEX_QueryMode()) {
				m_cbSystemFlag.SetChecked (m_fIsSystem);
				mkTyp &= ~PBDMERKMAL_SYSTEMFLAG;
			}

			if (m_fShowAdminDlg) {
				m_rgType = mkTyp & 0x7f;
				AdjustRadios(m_rgType);
			} 

			m_cbReadOnly.SetChecked (mkTyp & PBDMERKMAL_READONLY);
			mkTyp &= ~PBDMERKMAL_READONLY;

		ResString resCap (ResID (IDS_EXISTINGOPROPDESC, &g_pTE -> RF()), 128);

			SetCaption (resCap);
		} 
		else if (NULL != pcNewProp) {
			EDKurzText.SetText (pcNewProp);
			if (m_fShowAdminDlg) {
				m_rgType = MPObjectFeature;
				AdjustRadios(m_rgType);
			} 
		} 
		else {
		ResString resCap (ResID (IDS_NEWOPROPDESC, &g_pTE -> RF()), 128);

			SetCaption (resCap);
			if (m_fShowAdminDlg) {
				m_rgType = MPObjectFeature;
				AdjustRadios(m_rgType);
			} 
		}
	}
	EDKurzText.SetFocus();

// ROMode einstellen
	if (DEX_GetROModeIdent (_actID)) {
		m_cbReadOnly.SetChecked (TRUE);
		m_cbReadOnly.Disable();
		if (QMSysAdmin & DEX_QueryMode())
			m_cbSystemFlag.Disable();

	HPROJECT hPr = DEX_GetObjectsProject(_actID);

		if (!DEX_GetGDODataSourceEx(hPr)) {
		// DEX_GetGDODataSourceEx(m_hPr) steht für Editierbarkeit der Beschreibungsdaten von
		// Objektklassen trotz Schreibschutz
			EDKurzText.ForwardEvent (EM_SETREADONLY, TRUE);
			EDLangText.ForwardEvent (EM_SETREADONLY, TRUE);
		}
	}

	AdjustOK();
	isValid = true;
}

#pragma warning (default: 4355)

void DefineMerkmalDlg::AdjustRadios (int rgType)
{
	m_rbObject.SetState(false);
	m_rbView.SetState(false);
	m_rbClass.SetState(false);
	switch (rgType) {
	case MPObjectFeature:
		m_rbObject.SetState(true);
		break;

	case MPViewFeature:
		m_rbView.SetState(true);
		break;

	case MPIdentFeature:
		m_rbClass.SetState(true);
		break;

	default:
		_ASSERTE(MPUnknownFeature != rgType);
		break;
	}
}

// EventHandler ----------------------------------------------------------------
void _XTENSN_EXPORT DefineMerkmalDlg::ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		{
			TX_ASSERT(!DEX_GetROModeIdent(_actID) || DEX_GetGDODataSourceEx(DEX_GetObjectsProject(_actID)));

		CEierUhr Wait(this);
		ErrInstall EI (WC_NOMERKMAL);
		PBDMERKMALEX pbdData;

			INITSTRUCT(pbdData, PBDMERKMALEX);
			pbdData.pbdTyp = 'm';
			pbdData.pbdCode = _actMC;
			pbdData.lIdent = _actID;
			pbdData.pbdReserved = 0;

		// BezugsTyp setzen, MerkmalsTyp ist TextMerkmal
			if (m_fShowAdminDlg) {
				pbdData.ipbdMTyp = m_rgType;
				if (MPObjectFeature != m_rgType)
					pbdData.ipbdMTyp |= MPForceForTRiASDBs;
			} else
				pbdData.ipbdMTyp = MPObjectFeature;

			if (QMSysAdmin & DEX_QueryMode()) {
				if (m_cbSystemFlag.isChecked())
					pbdData.ipbdMTyp |= PBDMERKMAL_SYSTEMFLAG;
			} else if (m_fIsSystem)
				pbdData.ipbdMTyp |= PBDMERKMAL_SYSTEMFLAG;

			if (m_cbReadOnly.isChecked())
				pbdData.ipbdMTyp |= PBDMERKMAL_READONLY;

		char LT[1024];
		char KT[TEXTLEN+1];
		int maxLen = 0;

			maxLen = sizeof(LT);
			EDKurzText.GetText (KT, sizeof(KT));
			pbdData.pbdKText = KT;
			pbdData.pbdKTextLen = strlen(KT);

			EDLangText.GetText (LT, maxLen);
			pbdData.pbdLText = LT;
			pbdData.pbdLTextLen = maxLen -1;

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

			_actMC = pbdData.pbdCode;		// kann sich geändert haben	!!

			DEXN_PBDMCodeChanged (_actMC);
			App::Exec (ExecWhileEvent);

			EndDlg (1);	// ok und raus
		}
		break;

	case IDCANCEL:
		EndDlg (0);	// abbrechen
		break;

	case IDB_DEFIDHELP:
		break;

	case IDC_OBJECTPROP:
		_ASSERTE(m_fShowAdminDlg);		// nur im AdminMode auswerten
		m_rgType = MPObjectFeature;
		AdjustRadios(m_rgType);
		break;

	case IDC_VIEWPROP:
		_ASSERTE(m_fShowAdminDlg);		// nur im AdminMode auswerten
		m_rgType = MPViewFeature;
		AdjustRadios(m_rgType);
		break;

	case IDC_CLASSPROP:
		_ASSERTE(m_fShowAdminDlg);		// nur im AdminMode auswerten
		m_rgType = MPIdentFeature;
		AdjustRadios(m_rgType);
		break;
	}
}

void DefineMerkmalDlg::EditChange (ControlEvt e)
{
	if (IDE_DEFMKSHORT == (uint)e.GetControlID()) 
		AdjustOK();
}

void DefineMerkmalDlg::AdjustOK()
{
HPROJECT hPr = DEX_GetObjectsProject(_actID);

	if ((!DEX_GetROModeIdent(_actID) || DEX_GetGDODataSourceEx(hPr)) && EDKurzText.GetTextLen() > 0)
		OKButton.Enable();
	else
		OKButton.Disable();
}

