// Dialog, welcher einen Ident auswählbar macht, um Objekte umzuklassifizieren
// File: MODIDENT.CXX

#include "trias03p.hxx"
#include "trias03.h"

#include <funcs02.h>
#include <funcs03.h>
#include <xtsnguid.h>
#include <eonrguid.h>
#include <propguid.h>
#include <statguid.h>

#include <eieruhr.hxx>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "enumonr.hxx"
#include "modident.hxx"
#include "modidprp.hxx"

// JG 980918
#include "ownmacros.h"

///////////////////////////////////////////////////////////////////////////////
//
short OTypToBits (ObjTyp iOTyp);

///////////////////////////////////////////////////////////////////////////////
//
extern char g_pDLLName[_MAX_PATH];

// Konstruktor/Destruktor/Initialisierung -------------------------------------
#pragma warning (disable: 4355)

CModifyIdentDlg::CModifyIdentDlg (CModIDPropAct *pParent, ResID uiDlg, 
									LPCSTR pcCaption)
		 : CPropertyPage (uiDlg, pcCaption),
		   m_cbAddToView (this, IDC_ADDTOVIEW),
		   m_ftAdjustIdent (this, IDC_STATIC_SELECTIDENT),
		   m_cbAdjustIdent (this, IDC_CHECK_SELECTIDENT),
		   m_pbDefine (this, IDC_DEFINENEW),
		   m_dwFlags(0), m_pParent(pParent)
{
	m_pIdents = NULL;	// ListViewCtrl

	m_lResult = 0;		// ErgebnisIdent
	m_fAddToView = true;

	m_pIEnumObjs = NULL;
}

#pragma warning (default: 4355)

CModifyIdentDlg::~CModifyIdentDlg (void)
{
	DELETE_OBJ (m_pIdents);
	if (m_pIEnumObjs) m_pIEnumObjs -> Release();
}

CModifyIdentDlg *CModifyIdentDlg::CreateInstance (
		CModIDPropAct *pParent, ResID resID, LPCSTR pcCaption)
{
	try {
	CModifyIdentDlg *pDlg = NULL;
	
		pDlg = new CModifyIdentDlg (pParent, resID, pcCaption);
		if (pDlg == NULL || !pDlg -> FInit()) {
			DELETE_OBJ (pDlg);
			return NULL;
		}
		return pDlg;
	} catch (...) {
		return NULL;
	}
}

bool CModifyIdentDlg::FInit (void)
{
// IdentifikatorListBox füllen
	m_pIdents = new CSelIdentListView (this, IDC_LISTDESTIDENTS);
	if (m_pIdents == NULL) return false;

	m_pIEnumObjs = NULL;
	CoCreateInstance (CLSID_EnumObjectsByNumber, NULL, CLSCTX_INPROC_SERVER,
					  IID_IEnumLONG, (LPVOID *)&m_pIEnumObjs);

	return (NULL != m_pIEnumObjs) ? true : false;
}

void CModifyIdentDlg::SetFlags (DWORD dwFlags)
{
	m_dwFlags = dwFlags;
}

// Der wohl wichtigste Unterschied zu einem normalen Dialogfenster besteht
// darin, daß alle Controls dieser Dialogseite explizit im WindowInit()-Event-
// handler initialisiert werden müssen (s.u.). Alle inhaltlichen Initialisierungen
// können erst danach erfolgen (und nicht wie gewohnt im Konstruktor)
void CModifyIdentDlg::WindowInit (Event)
{
CEierUhr Wait (this);		// EierUhr anzeigen

// ListViewCtrl initialisieren/Identifikatoren laden
	if (NULL == m_pIdents || 
		!m_pIdents -> InitControl(OTPunkt|OTLinie|OTFlaeche|OTText, 
								  SELIDMODE_NOICONS|SELIDMODE_ALLIDENTSPBD,
								  NULL, CmpEntries, reinterpret_cast<DWORD>(m_pIdents)))
	{
		return;
	}
	
// Mode voreinstellen: Text ist eingeblendet und Checkbox ist aus (alter Mode)
	m_ftAdjustIdent.FInit();
	m_cbAdjustIdent.FInit();
	AdjustCheckMode();

	m_cbAddToView.FInit();
	m_cbAddToView.SetChecked (true);

	m_pbDefine.FInit();
	m_pbDefine.Disable();

	AdjustOK();

// vorhergehende Einstellungen wieder einstellen
	if (0 != m_lResult) {
	int iIndex = SelectIdent (m_lResult);

		if (-1 != iIndex) {	// Focus setzen, ins Bild rollen
			m_pIdents -> EnsureVisible (iIndex, false);
			m_pIdents -> SelectItemFocus (iIndex);
		}
		m_cbAddToView.SetChecked (m_fAddToView);
	}
}

///////////////////////////////////////////////////////////////////////////////
// EventHandler ---------------------------------------------------------------
void CModifyIdentDlg::OnItemChanged (NotifyEvt e)
{
NM_LISTVIEW *pNfyData = reinterpret_cast<NM_LISTVIEW *>(e.GetNotifyInfo());

	if (!(pNfyData -> uChanged & LVIF_STATE))
		return;		// Status nicht geändert

// Selektion erhalten/verloren
	if (pNfyData -> uOldState & LVIS_SELECTED ||
		pNfyData -> uNewState & LVIS_SELECTED)
	{
		AdjustOK();
	}
}

int CModifyIdentDlg::OnSetActive (NotifyEvt)
{
	AdjustOK();
	return 0;
}

// Der Dialog wurde mit Cancel geschlossen ------------------------------------
void CModifyIdentDlg::OnCancel (NotifyEvt)
{
	// hier evtl. Aufräumarbeiten durchführen
}

int CModifyIdentDlg::OnWizNext (NotifyEvt)
{
	if (PrepareResult()) 	// Ergebnisse zwischenspeichern
		return 0;

	return -1;
}

// Finish wurde gedrückt ------------------------------------------------------
int CModifyIdentDlg::OnWizFinish (NotifyEvt)
{
	PrepareResult();	// Ergebnisse zwischenspeichern
	return 0;
}

void CModifyIdentDlg::ButtonClick (ControlEvt e)
{
	if (!m_fCheckMode || IDC_CHECK_SELECTIDENT != (uint)e.GetControlID())
		return;

	CPropertyPage::ButtonClick(e);
	m_fCheckModeChecked = m_cbAdjustIdent.isChecked();
	AdjustCheckMode();
	AdjustOK();
}


void CModifyIdentDlg::OnClick (NotifyEvt e)
{
NMHDR *pNMHdr = e.GetNotifyInfo();
POINT pt;

	GetCursorPos (&pt);
	ScreenToClient (pNMHdr -> hwndFrom, &pt);
	pt.x = 1;	// ganz am linken Rand testen

UINT uiFlags = 0L;
int iIndex = m_pIdents -> HitTest ((Point &)pt, &uiFlags);

	if (uiFlags & LVHT_ONITEM && 0 <= iIndex) {
		m_pIdents -> SetItemState (iIndex, LVIS_SELECTED|LVIS_FOCUSED, 
								   LVIS_SELECTED|LVIS_FOCUSED);
		m_pIdents -> Update (iIndex);
	}
}

// HilfeRoutine ---------------------------------------------------------------
void CModifyIdentDlg::HelpRequest (HelpRequestEvt e)
{
const HELPINFO *pHI = e.GetHelpInfo();

	TX_ASSERT(pHI);
}

///////////////////////////////////////////////////////////////////////////////
// Fragt den Dialog nach seinen Daten -----------------------------------------
HRESULT CModifyIdentDlg::GetEnumLONG (IEnum<LONG> **ppIEnum)
{
	if (NULL == ppIEnum) return E_POINTER;
	if (NULL == m_pIEnumObjs) return E_OUTOFMEMORY;

	// IEnumLONG abfragen
	RETURN_FAILED_HRESULT(m_pIEnumObjs -> QueryInterface (IID_IEnumLONG, (LPVOID *)ppIEnum));

	// Verarbeitungteil
	MODOBJIDENT MOI;
	LONG lONr;

	ResourceFile RF (g_pDLLName);
	ResString resUndo (ResID(IDS_UNDOMODIDENTS, &RF), 128);

	// JG980914 Ermitteln der Anzahl der Operationen
	long counter = m_pIEnumObjs -> Count();
	long ind = 0;		// zum Abbruch testen
	SetMaxTicks(counter);	

	DEX_BeginUndoLevel(resUndo.Addr());
	INITSTRUCT(MOI, MODOBJIDENT);

	for (m_pIEnumObjs -> Reset(); S_OK == m_pIEnumObjs -> Next (1, &lONr, NULL); Tick()) 
	{
//		TX_ASSERT(IsValidONr(lONr));
	
	// umklassifizieren
		MOI.lONr = lONr;
		MOI.lNewIdent = m_lResult;
		MOI.iMode = OTypToBits ((ObjTyp)DEX_GetObjectType(lONr));
		if (m_cbAddToView.isChecked())
			MOI.iMode |= MODIDENT_ADDTOVIEW;
		DEX_ModObjectIdentEx (MOI);		// mit Undo

		// JG Abbruchhandling
		// aller 50 Objekte mal nachgucken
		if (++ind >= 50)
		{
			HRESULT hr = GoOn();
			if (S_OK != hr)
			{
				// den aktuellen Undo Level zurücksetzen
				DEX_CancelUndoLevel(true);
				return hr;
			}
			ind = 0;				// Zähler neu starten
		}
	}

	DEX_EndUndoLevel();
	DEX_RefreshLegend();
	DEX_RepaintLegend();
	
// explizit Statusanzeige auf 100 %
	TickToEnd();
	return S_OK;
}

// Übergibt die zu verarbeitende Objektmenge ----------------------------------
HRESULT CModifyIdentDlg::SetEnumLONG (IEnum<LONG> *pIEnum)
{
	// JG
	LONG lONr;
	if (m_pIEnumObjs)
	{
		for (pIEnum -> Reset(); S_OK == pIEnum -> Next (1, &lONr, NULL);/**/)
		{
			// und zu lokalem Enumerator aller umklassifizieren Objekte hinzufügen
			m_pIEnumObjs -> AddItem (lONr);
		}
	}

	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// HilfsRoutinen 
void CModifyIdentDlg::AdjustCheckMode()
{
	if (m_fCheckMode) {
		m_ftAdjustIdent.Disable();
		m_ftAdjustIdent.Hide();
		m_cbAdjustIdent.Enable();
		m_cbAdjustIdent.Show();
		if (m_fCheckModeChecked) {
			m_cbAdjustIdent.SetChecked (TRUE);
			m_pIdents -> Enable();
			m_cbAddToView.Enable();
		} else {
			m_cbAdjustIdent.SetChecked (FALSE);
			m_pIdents -> Disable();
			m_cbAddToView.Disable();
		}
	} else {
		m_ftAdjustIdent.Enable();
		m_ftAdjustIdent.Show();
		m_cbAdjustIdent.Disable();
		m_cbAdjustIdent.Hide();

		m_cbAddToView.Enable();
		m_pIdents -> Enable();
	}
}

void CModifyIdentDlg::AdjustOK (bool fDisableNext)
{
DWORD dwBttns = 0;
int iCnt = m_pIdents -> GetSelectedCount();
bool fEnable = (0 < iCnt) || (m_fCheckMode && !m_fCheckModeChecked);

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns |= PSWIZB_BACK;

	if (fEnable && !fDisableNext) {
		if (m_dwFlags & ADDPAGES_LASTPAGE)
			dwBttns |= PSWIZB_FINISH;
		else
			dwBttns |= PSWIZB_NEXT;
	} else if (m_dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	SetSheetWizardButtons (dwBttns);
}

// Ergebnisdaten aus Controls lesen und zwischenspeichern ---------------------
bool CModifyIdentDlg::PrepareResult (void)
{
// Daten (Ident) aus Page lesen und speichern
bool fHasIdent = GetSelectedIdent (m_lResult);

	TX_ASSERT(!fHasIdent || IsValidIdent(m_lResult));

	m_fAddToView = m_cbAddToView.isChecked() ? true : false;
	if (m_fCheckMode) {
		m_fCheckModeChecked = m_cbAdjustIdent.isChecked() ? true : false;
		if (!m_fCheckModeChecked) return true;
	}
	return fHasIdent;
}

///////////////////////////////////////////////////////////////////////////////
// AbfrageRoutinen ------------------------------------------------------------
bool CModifyIdentDlg::GetSelectedIdent (long &rlIdent)
{
short iOTyp = 0;	// dummy

	if (m_pIdents) 
		return m_pIdents -> GetFirstIdent (rlIdent, iOTyp);
		
	return false;
}

int CModifyIdentDlg::GetItemCount (void)
{
	if (m_pIdents) 
		return m_pIdents -> GetItemCount();
		
return 0;
}

int CModifyIdentDlg::SelectIdent (long lIdent, bool fSel)
{
	if (m_pIdents) {
	int fResult = m_pIdents -> SelectIdent (lIdent, 0, fSel);

		AdjustOK();
		return fResult;
	} else if (fSel)
		m_lResult = lIdent;		// lediglich vormerken
		
return -1;
}

///////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CModifyIdentDlg::SetDirty (bool fDirty)
{ 
	if (m_pParent) m_pParent -> SetDirty (fDirty); 
}
