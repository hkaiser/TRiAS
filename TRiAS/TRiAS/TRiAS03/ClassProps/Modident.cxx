// Dialog, welcher einen Ident auswählbar macht, um Objekte umzuklassifizieren
// File: MODIDENT.CXX

#include "trias03p.hxx"
#include "trias03.h"

#include <funcs02.h>
#include <xtsnguid.h>
#include <eonrguid.h>
#include <propguid.h>

#include <eieruhr.hxx>

#include "enumonr.hxx"
#include "modident.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
//
short OTypToBits (ObjTyp iOTyp);

///////////////////////////////////////////////////////////////////////////////
//
extern char g_pDLLName[260];

// Konstruktor/Destruktor/Initialisierung -------------------------------------
#pragma warning (disable: 4355)

CModifyIdentDlg :: CModifyIdentDlg (ResID uiDlg, LPCSTR pcCaption, DWORD dwFlags)
		 : CPropertyPage (uiDlg, pcCaption),
		   m_cbAddToView (this, IDC_ADDTOVIEW),
		   m_pbDefine (this, IDC_DEFINENEW),
		   m_dwFlags(dwFlags)
{
	m_pIdents = NULL;	// ListViewCtrl

	m_lResult = 0;		// ErgebnisIdent
	m_fAddToView = true;

	m_pIEnumObjs = NULL;
}

#pragma warning (default: 4355)

CModifyIdentDlg :: ~CModifyIdentDlg (void)
{
	DELETE (m_pIdents);
	if (m_pIEnumObjs) m_pIEnumObjs -> Release();
}

CModifyIdentDlg *CModifyIdentDlg :: CreateInstance (
		ResID resID, LPCSTR pcCaption, DWORD dwFlags)
{
	try {
	CModifyIdentDlg *pDlg = NULL;
	
		pDlg = new CModifyIdentDlg (resID, pcCaption, dwFlags);
		if (pDlg == NULL || !pDlg -> FInit()) {
			DELETE (pDlg);
			return NULL;
		}
		return pDlg;
	} catch (...) {
		return NULL;
	}
}

bool CModifyIdentDlg :: FInit (void)
{
// IdentifikatorListBox füllen
	m_pIdents = new CSelIdentListView (this, IDC_LISTDESTIDENTS);
	if (m_pIdents == NULL) return false;

return true;
}

// Der wohl wichtigste Unterschied zu einem normalen Dialogfenster besteht
// darin, daß alle Controls dieser Dialogseite explizit im WindowInit()-Event-
// handler initialisiert werden müssen (s.u.). Alle inhaltlichen Initialisierungen
// können erst danach erfolgen (und nicht wie gewohnt im Konstruktor)
void CModifyIdentDlg :: WindowInit (Event)
{
CEierUhr Wait (this);		// EierUhr anzeigen

// ListViewCtrl initialisieren/Identifikatoren laden
	if (NULL == m_pIdents || 
		!m_pIdents -> InitControl(OTPunkt|OTLinie|OTFlaeche|OTText, 
								  SELIDMODE_NOICONS|SELIDMODE_ALLIDENTSPBD))
	{
		return;
	}
	
	m_pIEnumObjs = CEnumObjectNumbers::CreateInstance();

	m_cbAddToView.FInit();
	m_cbAddToView.SetChecked (m_fAddToView);

	m_pbDefine.FInit();
	m_pbDefine.Disable();

	AdjustOK();
}

///////////////////////////////////////////////////////////////////////////////
// EventHandler ---------------------------------------------------------------
void CModifyIdentDlg :: OnItemChanged (NotifyEvt e)
{
NM_LISTVIEW *pNfyData = static_cast<NM_LISTVIEW *>(e.GetNotifyInfo());

	if (!(pNfyData -> uChanged & LVIF_STATE))
		return;		// Status nicht geändert

// Selektion erhalten/verloren
	if (pNfyData -> uOldState & LVIS_SELECTED ||
		pNfyData -> uNewState & LVIS_SELECTED)
	{
		AdjustOK();
	}
}

int CModifyIdentDlg :: OnSetActive (NotifyEvt)
{
	AdjustOK();
	return 0;
}

// Der Dialog wurde mit Cancel geschlossen ------------------------------------
void CModifyIdentDlg :: OnCancel (NotifyEvt)
{
	// hier evtl. Aufräumarbeiten durchführen
}

int CModifyIdentDlg :: OnWizNext (NotifyEvt)
{
	if (PrepareResult()) 	// Ergebnisse zwischenspeichern
		return 0;

return -1;
}

// Finish wurde gedrückt ------------------------------------------------------
int CModifyIdentDlg :: OnWizFinish (NotifyEvt)
{
	PrepareResult();	// Ergebnisse zwischenspeichern

// wir sind die letzten, also Rückkehrwert aus PropertySheet setzen
CPropertySheet *pSheet = GetPropertySheet();

	if (NULL != pSheet)
		pSheet -> EndDialog(1);	

return 0;
}

void CModifyIdentDlg :: OnClick (NotifyEvt e)
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
HRESULT CModifyIdentDlg :: GetEnumLONG (IEnum<LONG> **ppIEnum)
{
	if (NULL == ppIEnum) return ResultFromScode (E_POINTER);
	if (NULL == m_pIEnumObjs) return ResultFromScode (E_OUTOFMEMORY);

// IEnumLONG abfragen
return m_pIEnumObjs -> QueryInterface (IID_IEnumLONG, (LPVOID *)ppIEnum);
}

// Übergibt die zu verarbeitende Objektmenge ----------------------------------
HRESULT CModifyIdentDlg :: SetEnumLONG (IEnum<LONG> *pIEnum)
{
MODOBJIDENT MOI;
LONG lONr;
ResourceFile RF (g_pDLLName);
ResString resUndo (ResID(IDS_UNDOMODIDENTS, &RF), 128);

	DEX_BeginUndoLevel(resUndo.Addr());
	INITSTRUCT(MOI, MODOBJIDENT);

	for (pIEnum -> Reset(); S_OK == pIEnum -> Next (1, &lONr, NULL); /**/) {
		TX_ASSERT(IsValidONr(lONr));
	
	// umklassifizieren
		MOI.lONr = lONr;
		MOI.lNewIdent = m_lResult;
		MOI.iMode = OTypToBits ((ObjTyp)DEX_GetObjectType(lONr));
		if (m_cbAddToView.isChecked())
			MOI.iMode |= MODIDENT_ADDTOVIEW;
		DEX_ModObjectIdentEx (MOI);		// mit Undo

	// und zu lokalem Enumerator aller umklassifizieren Objekte hinzufügen
		if (m_pIEnumObjs)
			m_pIEnumObjs -> AddObject (lONr);
	}

	DEX_EndUndoLevel();
	DEX_RefreshLegend();
	DEX_RepaintLegend();

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// HilfsRoutinen --------------------------------------------------------------
void CModifyIdentDlg :: AdjustOK (bool fDisableNext)
{
CPropertySheet *pSheet = GetPropertySheet();

	if (NULL == pSheet || NULL == m_pIdents) return;

DWORD dwBttns = 0;
int iCnt = m_pIdents -> GetSelectedCount();

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns |= PSWIZB_BACK;

	if (0 < iCnt && !fDisableNext) {
		if (m_dwFlags & ADDPAGES_LASTPAGE)
			dwBttns |= PSWIZB_FINISH;
		else
			dwBttns |= PSWIZB_NEXT;
	} else if (m_dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	pSheet -> SetWizardButtons (dwBttns);
}

// Ergebnisdaten aus Controls lesen und zwischenspeichern ---------------------
bool CModifyIdentDlg :: PrepareResult (void)
{
// Daten (Ident) aus Page lesen und speichern
	if (!GetSelectedIdent (m_lResult))
		return false;

	TX_ASSERT(IsValidIdent(m_lResult));

return true;
}

///////////////////////////////////////////////////////////////////////////////
// AbfrageRoutinen ------------------------------------------------------------
bool CModifyIdentDlg :: GetSelectedIdent (long &rlIdent)
{
short iOTyp = 0;	// dummy

	if (m_pIdents) 
		return m_pIdents -> GetFirstIdent (rlIdent, iOTyp);
		
return false;
}

int CModifyIdentDlg :: GetItemCount (void)
{
	if (m_pIdents) 
		return m_pIdents -> GetItemCount();
		
return 0;
}

bool CModifyIdentDlg :: SelectIdent (long lIdent, bool fSel)
{
	if (m_pIdents) {
	bool fResult = m_pIdents -> SelectIdent (lIdent, 0, fSel);

		AdjustOK();
		return fResult;
	}
		
return false;
}

