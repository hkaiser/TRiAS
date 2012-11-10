// Dialogfenster zur Einstellung der Darstellungsreihenfolge ------------------
// File: SELPRIO.CXX

#include "triaspre.hxx"

// STL stuff ------------------------------------------------------------------
#define NOMINMAX
#pragma warning (disable: 4304)
#pragma warning (disable: 4114)
#pragma warning (disable: 4786)		// debug info truncated
#include <ospace/std/list>

#include <funcs03.h>				// UndoCreateInstance
#include <undoguid.h>				// GUID
#include <iunredo.hxx>				// Undo-Interface's

#include "triasres.h"
#include "selprio.hxx"

#if defined(_DEBUG) && !defined(WIN16)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define PRIORITY_STEP	20			// Schrittweite der neu verteilte Prioritäten

///////////////////////////////////////////////////////////////////////////////
// globale Funktion, die von IRISMAIN aus gerufen wird ------------------------
bool IrisWind::PrioritySelect ()
{
CPrioritySelDlg PSDlg (this, DBO().Idents());

	PSDlg.Show (Centre);
	if (PSDlg.Result() != 0) {
		DBO().WriteBackVisInfos();
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// Reihenfolge der Einträge der Liste festlegen
VisType BitsToVTyp (int iOTypes)
{
	if (iOTypes & OTPunkt) return VT_Punkt;
	if (iOTypes & OTLinie) return VT_Linie;
	if (iOTypes & OTFlaeche) return VT_Flaeche;
	if (iOTypes & OTText) return VT_Text;

	return VT_Default;
}

int CmpIdents (ULONG ulIdent1, ULONG ulIdent2)
{
	if (ulIdent1 > ulIdent2)
		return 1;
	if (ulIdent1 < ulIdent2)
		return -1;

return 0;
}

int WINAPI CmpPriorities (LPARAM lItem1, LPARAM lItem2, LPARAM dwData)
{
CTree &rIdP = (reinterpret_cast<CPrioritySelDlg *>(dwData) -> IdTree()).IdentTree();
CTable t(rIdP);
CSelIdentItem *pItem1 = reinterpret_cast<CSelIdentItem *>(lItem1);
CSelIdentItem *pItem2 = reinterpret_cast<CSelIdentItem *>(lItem2);
int iPrio1 = 0;
int iPrio2 = 0;
VisType iVTyp1 = VT_Default;
VisType iVTyp2 = VT_Default;

// Priorität des 1. Items
	if (t.Find(&(pItem1 -> m_ulIdent))) {
	CIdentifikatorLock l(t);
	
		TX_ASSERT(NULL != (CIdentifikator *)l);
		if (l) {
			iVTyp1 = BitsToVTyp (pItem1 -> m_iOTypes);
			iPrio1 = l -> Priority (iVTyp1);
		}
	} 

// Priorität des 2. Items
	if (t.Find(&(pItem2 -> m_ulIdent))) {
	CIdentifikatorLock l(t);

		TX_ASSERT(NULL != (CIdentifikator *)l);
		if (l) {
			iVTyp2 = BitsToVTyp (pItem2 -> m_iOTypes);
			iPrio2 = l -> Priority (iVTyp2);
		}
	}

	if (iPrio1 != iPrio2)
		return iPrio1-iPrio2;

// gleiche Priorität: zuerst Punkte, dann LFT
	if (pItem1 -> m_ulIdent == pItem2 -> m_ulIdent)
		return iVTyp1-iVTyp2;

// last resort: Idents vergleichen
	return CmpIdents (pItem1 -> m_ulIdent, pItem2 -> m_ulIdent);
}

///////////////////////////////////////////////////////////////////////////////
// Konstruktor/Destruktor
#pragma warning (disable: 4355)

CPrioritySelDlg::CPrioritySelDlg (pWindow pW, CIdTree &rIds)
	: DialogWindow (pW, 
		IsWin40() ? IDD_PRIORITY_SELECT : IDD_PRIORITY_SELECT_WIN32S),
	  m_pbUp (this, IDC_UP), m_pbDown (this, IDC_DOWN),
	  m_lvIdentList (this, IDL_PRIORITY),
	  m_pbOK (this, IDOK), m_pbTest (this, IDC_TEST),
	  m_rIds(rIds)
{
// Identifikatoren laden
DWORD dwMode = SELIDMODE_SINGLETYPE;

	if (DEX_GetOpenConnectionCount (QDCAllOpen|QDCCountQueryDefs) > 1)
		dwMode |= SELIDMODE_SHOWCONNECTIONS;

	m_lvIdentList.FInit();
	m_lvIdentList -> InitControl (OTPunkt|OTLinie|OTFlaeche|OTText, dwMode, NULL, CmpPriorities, reinterpret_cast<LPARAM>(this));
	
// new for 'Nashville' (#HK960823)
#if defined(ListView_GetExtendedListViewStyle)
	if (IsWin40()) {
	DWORD dwStyleEx = m_lvIdentList -> GetExtendedStyle();

		m_lvIdentList -> SetExtendedStyle (dwStyleEx | LVS_EX_FULLROWSELECT);
	}
#endif

// Controls initialisieren
	if (m_lvIdentList -> GetItemCount() > 0) { 
		m_lvIdentList -> SelectItem (0);
		m_lvIdentList -> SelectItemFocus (0);
	} else {
		m_pbOK.Disable();
		m_pbTest.Disable();
	}

	m_fUp = false;
	m_fDown = false;
	AdjustUpDown();
		
	m_pbTest.Disable();

// OwnerDraw Knöpfe initialisieren
	if (m_pbUp.LoadBitmaps (IDB_UP, IDB_UP_SEL, IDB_UP_FOCUS, IDB_UP_DISABLED))
		m_pbUp.SizeToContent(); 
	if (m_pbDown.LoadBitmaps (IDB_DOWN, IDB_DOWN_SEL, IDB_DOWN_FOCUS, IDB_DOWN_DISABLED))
		m_pbDown.SizeToContent(); 

	FillPrioList();		// derzeitige Prioritäten zwischenspeichern
}

#pragma warning (default: 4355)

CPrioritySelDlg::~CPrioritySelDlg (void)
{
}

///////////////////////////////////////////////////////////////////////////////
// Eventhandler
void CPrioritySelDlg::ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		EndDlg (ApplyPrioritiesWithUndo());
		break;

	case IDCANCEL:
		RestorePriorities();
		EndDlg();
		break;

	case IDC_UP:
		MoveItemUp();
		m_pbTest.Enable();
		break;

	case IDC_DOWN:
		MoveItemDown();
		m_pbTest.Enable();
		break;

	case IDC_TEST:
		m_pbTest.Disable();
		ApplyPriorities();
		break;
	}
}

void CPrioritySelDlg::OnItemChanged (NotifyEvt e)
{
NM_LISTVIEW *pNfyData = reinterpret_cast<NM_LISTVIEW *>(e.GetNotifyInfo());

	if (!(pNfyData -> uChanged & LVIF_STATE))
		return;		// Status nicht geändert

// Selektion erhalten/verloren
	if (pNfyData -> uOldState & LVIS_SELECTED ||
		pNfyData -> uNewState & LVIS_SELECTED)
	{
		AdjustUpDown();
	}
}

// Zeichenroutinen ------------------------------------------------------------
BOOL CPrioritySelDlg::DrawEntireItem (DrawItemEvt e)
{
	return m_pbUp.DrawItem(e) || m_pbDown.DrawItem(e);
}

BOOL CPrioritySelDlg::DrawItemFocus (DrawItemEvt e)
{
	return m_pbUp.DrawItem(e) || m_pbDown.DrawItem(e);
}

BOOL CPrioritySelDlg::DrawItemSelect (DrawItemEvt e)
{
	return m_pbUp.DrawItem(e) || m_pbDown.DrawItem(e);
}

// HilfeRoutine ---------------------------------------------------------------
void CPrioritySelDlg::HelpRequest (HelpRequestEvt e)
{
const HELPINFO *pHI = e.GetHelpInfo();

	TX_ASSERT(pHI);
}

// Ein Eintrag wurde aus der Liste gelöscht -----------------------------------
void CPrioritySelDlg::OnDeleteItem (NotifyEvt e)
{
NM_LISTVIEW *pNLV = reinterpret_cast<NM_LISTVIEW *>(e.GetNotifyInfo());

	if (0 == pNLV -> iSubItem)	// ItemData freigeben
		m_lvIdentList -> OnDeleteItem (pNLV);
}

void CPrioritySelDlg::OnDeleteAllItems (NotifyEvt)
{
	m_lvIdentList -> OnDeleteAllItems();
}

///////////////////////////////////////////////////////////////////////////////
// sonstige Member
void CPrioritySelDlg::AdjustUpDown (void)
{
	if (IsWin40()) {
		if (!m_fUp) {
			m_pbUp.Enable();
			m_fUp = true;
		}
		if (!m_fDown) {
			m_pbDown.Enable();
			m_fDown = true;
		}
		return;
	}

int iCnt = m_lvIdentList -> GetItemCount();

	if (iCnt > 0) {
	int iIndex = m_lvIdentList -> GetItemFocus();

		if (iIndex >= 0) {
			if (0 == iIndex) {
				m_pbUp.Disable();
				m_fUp = false;
			} else if (!m_fUp) {
				m_pbUp.Enable();
				m_fUp = true;
			}

			if (iCnt-1 == iIndex) {
				m_pbDown.Disable();
				m_fDown = false;
			} else if (!m_fDown) {
				m_pbDown.Enable();
				m_fDown = true;
			}

			return;
		}
	} 

// ansonsten alles passivieren
	m_pbUp.Disable();
	m_pbUp.Disable();
}

bool CPrioritySelDlg::MoveItemUp (void)
{
int iFocus = m_lvIdentList -> GetItemFocus();
int iIndex = m_lvIdentList -> GetFirstSelected();

	if (iIndex <= 0) {
		MessageBeep (MB_ICONHAND);
		return false;
	}

int iFocusN = iFocus;
int iFirst = iIndex-1;
int iLast = iIndex;

	do {
	int iIndexN = iIndex-1;

		iLast = max(iLast, iIndex);
		if (iIndex == iFocus)
			iFocusN = iIndexN;		// muß am Schluß sichtbar bleiben

		if (!SwapItems (iIndex, iIndexN)) 
			return false;

		iIndex = m_lvIdentList -> GetNextSelected();
	} while (iIndex > 0);

	m_lvIdentList -> EnsureVisible (iFocusN, false);

return m_lvIdentList -> RedrawItems (iFirst, iLast);
}

bool CPrioritySelDlg::MoveItemDown (void)
{
int iFocus = m_lvIdentList -> GetItemFocus();
int iIndex = m_lvIdentList -> GetLastSelected();	// beim letzten anfangen

	if (iIndex >= m_lvIdentList -> GetItemCount()-1) {
		MessageBeep (MB_ICONHAND);
		return false;
	}

int iFocusN = iFocus;
int iFirst = iIndex;
int iLast = iIndex+1;

	do {
	int iIndexN = iIndex+1;

		iFirst = min(iFirst, iIndex);
		if (iIndex == iFocus)
			iFocusN = iIndexN;		// muß am Schluß sichtbar bleiben

		if (!SwapItems (iIndex, iIndexN))
			return false;	 // Fehler

		iIndex = m_lvIdentList -> GetPrevSelected();
	} while (iIndex >= 0);

	m_lvIdentList -> EnsureVisible (iFocusN, false);

return m_lvIdentList -> RedrawItems (iFirst, iLast);
}

bool CPrioritySelDlg::SwapItems (int iIndexO, int iIndexN)
{
	if (iIndexO == iIndexN) return false;

// beteiligte Items besorgen
LV_ITEM lviCurr, lviCurrSub, lviCurrSub2, lviCurrSrc;
char cbCurr[64], cbCurrSub[64], cbCurrSub2[64], cbCurrSrc[64];
int iConnCnt = DEX_GetOpenConnectionCount (QDCAllOpen|QDCCountQueryDefs);

	lviCurr.mask = LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM|LVIF_STATE;
	lviCurr.stateMask = LVIS_FOCUSED|LVIS_SELECTED;
	lviCurr.iItem = iIndexO;
	lviCurr.iSubItem = 0;
	lviCurr.pszText = cbCurr;
	lviCurr.cchTextMax = sizeof(cbCurr);
	m_lvIdentList -> GetItem (&lviCurr);

	lviCurrSub.mask = LVIF_TEXT;
	lviCurrSub.iItem = iIndexO;
	lviCurrSub.iSubItem = 1;
	lviCurrSub.pszText = cbCurrSub;
	lviCurrSub.cchTextMax = sizeof(cbCurrSub);
	m_lvIdentList -> GetItem (&lviCurrSub);

	lviCurrSub2.mask = LVIF_TEXT;
	lviCurrSub2.iItem = iIndexO;
	lviCurrSub2.iSubItem = 2;
	lviCurrSub2.pszText = cbCurrSub2;
	lviCurrSub2.cchTextMax = sizeof(cbCurrSub2);
	m_lvIdentList -> GetItem (&lviCurrSub2);

	if (iConnCnt > 1) {
		lviCurrSrc.mask = LVIF_TEXT;
		lviCurrSrc.iItem = iIndexO;
		lviCurrSrc.iSubItem = 3;
		lviCurrSrc.pszText = cbCurrSrc;
		lviCurrSrc.cchTextMax = sizeof(cbCurrSrc);
		m_lvIdentList -> GetItem (&lviCurrSrc);
	}

LV_ITEM lviPrev, lviPrevSub, lviPrevSub2, lviPrevSrc;
char cbPrev[64], cbPrevSub[64], cbPrevSub2[64], cbPrevSrc[64];

	lviPrev.mask = LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM|LVIF_STATE;
	lviPrev.stateMask = LVIS_FOCUSED|LVIS_SELECTED;
	lviPrev.iItem = iIndexN;
	lviPrev.iSubItem = 0;
	lviPrev.pszText = cbPrev;
	lviPrev.cchTextMax = sizeof(cbPrev);
	m_lvIdentList -> GetItem (&lviPrev);

	lviPrevSub.mask = LVIF_TEXT;
	lviPrevSub.iItem = iIndexN;
	lviPrevSub.iSubItem = 1;
	lviPrevSub.pszText = cbPrevSub;
	lviPrevSub.cchTextMax = sizeof(cbPrevSub);
	m_lvIdentList -> GetItem (&lviPrevSub);

	lviPrevSub2.mask = LVIF_TEXT;
	lviPrevSub2.iItem = iIndexN;
	lviPrevSub2.iSubItem = 2;
	lviPrevSub2.pszText = cbPrevSub2;
	lviPrevSub2.cchTextMax = sizeof(cbPrevSub2);
	m_lvIdentList -> GetItem (&lviPrevSub2);

	if (iConnCnt > 1) {
		lviPrevSrc.mask = LVIF_TEXT;
		lviPrevSrc.iItem = iIndexN;
		lviPrevSrc.iSubItem = 3;
		lviPrevSrc.pszText = cbPrevSrc;
		lviPrevSrc.cchTextMax = sizeof(cbPrevSrc);
		m_lvIdentList -> GetItem (&lviPrevSrc);
	}

// beteiligte Items vertauschen
	lviCurr.iItem = lviCurrSub.iItem = lviCurrSub2.iItem = lviCurrSrc.iItem = iIndexN;
	if (iConnCnt > 1) 
		m_lvIdentList -> SetItem (&lviCurrSrc);
	m_lvIdentList -> SetItem (&lviCurrSub2);
	m_lvIdentList -> SetItem (&lviCurrSub);
	m_lvIdentList -> SetItem (&lviCurr);

	lviPrev.iItem = lviPrevSub.iItem = lviPrevSub2.iItem = lviPrevSrc.iItem = iIndexO;
	if (iConnCnt > 1) 
		m_lvIdentList -> SetItem (&lviPrevSrc);
	m_lvIdentList -> SetItem (&lviPrevSub2);
	m_lvIdentList -> SetItem (&lviPrevSub);
	m_lvIdentList -> SetItem (&lviPrev);
	return true;
}


///////////////////////////////////////////////////////////////////////////////
// Aufbauen des lokalen Prioritätsbaumes
BOOL EXPORTTRIAS FillListWithPriorities (void *pObj, void *pData) 
{
CIdentifikator *pId = & ((CIdRef *)pObj) -> rCId();
VisType iVTyp = ((CIdRef *)pObj) -> FVisTyp();
CPriorityEntry PE (pId -> Priority(iVTyp), pId -> Id(), iVTyp);

// In Baum einhängen
	static_cast<CPriorities *>(pData) -> push_back(PE);

return true;
}

// Baum aufbauen --------------------------------------------------------------
void CPrioritySelDlg::FillPrioList (void)
{
	IdTree().PrioTree().Every (FillListWithPriorities, &m_PrioList);
}

bool CPrioritySelDlg::ApplyPriorities (void)
{
// für alle Identifikatoren der aktuellen Sicht Prioritäten neu einstellen
int iCnt = m_lvIdentList -> GetItemCount();
bool fRO = DEX_GetROModeEx(HACTPROJECT);
long lIdent = 0;
short iOType = 0;

	for (int i = 0; i < iCnt; i++) {
		if (!m_lvIdentList -> DecodeEntry (i, lIdent, iOType))
			return false;	// Fehler

		if (!IdTree().ChangePriority (lIdent, (i+1)*PRIORITY_STEP, 
					 BitsToVTyp(iOType), !fRO))
			return false;
	}

// Hauptfenster neu zeichnen
	DEX_RePaint();

return true;
}

bool CPrioritySelDlg::ApplyPrioritiesWithUndo (void)
{
	if (DEX_GetROModeEx(HACTPROJECT))
		return ApplyPriorities();

// für alle Identifikatoren der aktuellen Sicht Prioritäten neu einstellen
int iCnt = m_lvIdentList -> GetItemCount();
long lIdent = 0;
short iOType = 0;

// UndoLevel anlegen
HRESULT hr = NOERROR;
ResString resUndo (IDS_UNDOPRIORITY, 128);
LPUNDOREDOVISINFO pIUndo = NULL;

	DEX_BeginUndoLevel (resUndo.Addr());

	for (int i = 0; i < iCnt; i++) {
		if (!m_lvIdentList -> DecodeEntry (i, lIdent, iOType))
			return false;	// Fehler

	// UndoObjekt registrieren
	int iPrio = (i+1)*PRIORITY_STEP;
	VisType rgVTyp = BitsToVTyp(iOType);
	HANDLEVISINFO *pHVI = ctHANDLEVISINFO (rgVTyp);

		if (NULL != pHVI) {
			pHVI -> m_lIdent = lIdent;
			pHVI -> m_iVTyp = rgVTyp;
			pHVI -> m_fFlags = DO_PriorityChanged;
			pHVI -> m_pVI -> m_Priority = iPrio;

			pIUndo = NULL;
			hr = UndoCreateInstance (IID_IUndoRedoVisInfo, (LPVOID *)&pIUndo);
			if (SUCCEEDED(hr) && NOERROR == pIUndo -> Init (pHVI, NULL)) 
				DEX_AddUndoRedo (pIUndo);

			if (pIUndo) pIUndo -> Release();
			dtHANDLEVISINFO (pHVI);
		}

	// Priorität ändern
		if (!IdTree().ChangePriority (lIdent, iPrio, rgVTyp, true))
		{
			DEX_CancelUndoLevel (false);
			return false;
		}
	}

// Hauptfenster neu zeichnen
	DEX_EndUndoLevel();
	DEX_RePaint();

return true;
}

bool CPrioritySelDlg::RestorePriorities (void)
{
// für alle Identifikatoren der aktuellen Sicht Prioritäten rücksetzen
	for (CPriorities::iterator it = m_PrioList.begin();
		 it != m_PrioList.end(); ++it)
	{
		if (!IdTree().ChangePriority (
				(*it).GetIdent(), (*it).GetPriority(), (*it).FVisTyp(), false))
			return false;
	}

// Hauptfenster neu zeichnen
	DEX_RePaint();

return true;
}
