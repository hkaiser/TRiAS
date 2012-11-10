// Auswahl aller Objekte verschiedener Objektklassen --------------------------
// File: SELIDENT.CXX

#include "featurep.hxx"
#include "feature.h"

#include <eieruhr.hxx>

#include "enumonr.hxx"
#include "selidlst.hxx"
#include "selident.hxx"

// Konstruktor/Destruktor/Initialisierung -------------------------------------
#pragma warning (disable: 4355)

CSelectIdentDlg :: CSelectIdentDlg (ResID uiDlg, LPCSTR pcCaption, DWORD dwFlags)
		 : CPropertyPage (uiDlg, pcCaption),
		   m_pbSelAll (this, IDB_SELALLCLASSES),
		   m_dwFlags(dwFlags)
{
	m_pIdents = NULL;	// ListViewCtrl

	m_pResult = NULL;	// ErgebnisDaten
	m_iCnt = 0;
}

#pragma warning (default: 4355)

CSelectIdentDlg :: ~CSelectIdentDlg (void)
{
	DELETE (m_pIdents);
	DELETE (m_pResult);
}

CSelectIdentDlg *CSelectIdentDlg :: CreateInstance (
		UINT uiDlg, LPCSTR pcCaption, DWORD dwFlags, ResourceFile &rRF)
{
	try {
	CSelectIdentDlg *pDlg = NULL;
	
		pDlg = new CSelectIdentDlg (ResID (uiDlg, &rRF), pcCaption, dwFlags);
		if (pDlg == NULL || !pDlg -> FInit(rRF)) {
			DELETE (pDlg);
			return NULL;
		}
		return pDlg;
	} catch (...) {
		return NULL;
	}
}

bool CSelectIdentDlg :: FInit (ResourceFile &rRF)
{
// IdentifikatorListBox füllen
	m_pIdents = new CSelIdentList (this, IDC_LISTIDENTS, rRF);
	if (m_pIdents == NULL) return false;

return true;
}

// Der wohl wichtigste Unterschied zu einem normalen Dialogfenster besteht
// darin, daß alle Controls dieser Dialogseite explizit im WindowInit()-Event-
// handler initialisiert werden müssen (s.u.). Alle inhaltlichen Initialisierungen
// können erst danach erfolgen (und nicht wie gewohnt im Konstruktor)
void CSelectIdentDlg :: WindowInit (Event)
{
CEierUhr Wait (this);		// EierUhr anzeigen

// ListViewCtrl initialisieren
	if (NULL == m_pIdents || !m_pIdents -> InitControl())
		return;

// Button SelectAll initialisieren und richten
	m_pbSelAll.FInit();
	if (m_pIdents -> GetItemCount())
		m_pbSelAll.Enable();
	else
		m_pbSelAll.Disable();

	AdjustOK();
}

///////////////////////////////////////////////////////////////////////////////
// EventHandler ---------------------------------------------------------------
void CSelectIdentDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDB_SELALLCLASSES:	// alle markieren
		m_pIdents -> ChangeSelectedAll (true);
		AdjustOK();
		break;
	}
}

void CSelectIdentDlg :: OnItemChanged (NotifyEvt e)
{
	if (((NM_LISTVIEW *)e.GetNotifyInfo()) -> uChanged & LVIF_STATE)
		AdjustOK();
}

int CSelectIdentDlg :: OnSetActive (NotifyEvt e)
{
	AdjustOK();
	return 0;
}

// Der Dialog wurde mit Cancel geschlossen ------------------------------------
void CSelectIdentDlg :: OnCancel (NotifyEvt)
{
	// hier evtl. Aufräumarbeiten durchführen
}

int CSelectIdentDlg :: OnWizNext (NotifyEvt)
{
	if (PrepareResult()) 	// Ergebnisse zwischenspeichern
		return 0;

return -1;
}

// Finish wurde gedrückt ------------------------------------------------------
int CSelectIdentDlg :: OnWizFinish (NotifyEvt)
{
	PrepareResult();	// Ergebnisse zwischenspeichern

// wir sind die letzten, also Rückkehrwert aus PropertySheet setzen
CPropertySheet *pSheet = GetPropertySheet();

	if (NULL != pSheet)
		pSheet -> EndDialog(1);	

return 0;
}

void CSelectIdentDlg :: OnClick (NotifyEvt e)
{
// UINT uiResID = e.GetControlID();
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

///////////////////////////////////////////////////////////////////////////////
// Hilfsfunktionen, um Objekte aufzusammeln -----------------------------------
extern "C" 
bool PASCAL GetObjectsFromIdentDoc (long lONr, DWORD dwOTyp, void *pData)
{
	((CEnumObjectNumbers *)pData) -> AddObject (lONr);

return true;	// immer weiter machen
}

bool FillTrees (long lIdent, short iOTyp, CEnumObjectNumbers *pEnum)
{
// Enumerator füllen
ENUMLONGKEYEX ELK;

	ELK.eKey = lIdent;
	ELK.eFcn = (ENUMLONGKEYEXPROC)GetObjectsFromIdentDoc;
	ELK.ePtr = pEnum;
	ELK.eData = (DWORD)iOTyp;
	
return DEX_EnumIdentObjectsEx (ELK);
}

// Fragt den Dialog nach seinen Daten -----------------------------------------
HRESULT CSelectIdentDlg :: GetEnumLONG (IEnum<LONG> **ppEnum)
{
	if (NULL == ppEnum) return ResultFromScode (E_POINTER);

// Enumerator generieren
CEnumObjectNumbers *pEnum = CEnumObjectNumbers::CreateInstance();

	if (NULL == pEnum || NULL == m_pResult) 
		return ResultFromScode (E_OUTOFMEMORY);

// Enumerator füllen
        for (int i = 0; i < m_iCnt; i++) 
		FillTrees (m_pResult[i].m_lIdent, m_pResult[i].m_iOTyp, pEnum);

// IEnumLONG abfragen
HRESULT hr = pEnum -> QueryInterface (IID_IEnumLONG, (LPVOID *)ppEnum);

	pEnum -> Release();

return hr;
}

///////////////////////////////////////////////////////////////////////////////
// HilfsRoutinen --------------------------------------------------------------
void CSelectIdentDlg :: AdjustOK (bool fDisableNext)
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
	}

	pSheet -> SetWizardButtons (dwBttns);
}

// Ergebnisdaten aus Controls lesen und zwischenspeichern ---------------------
bool CSelectIdentDlg :: PrepareResult (void)
{
int iCnt = GetSelectedCount();

	DELETE (m_pResult);		// evtl. vorherigen Stand löschen
	if (0 == iCnt) return false;

	try {
	// Feld aufbauen und mit selektierten Einträgen füllen
		m_pResult = new SELIDRESULT[iCnt];
		m_iCnt = iCnt;
	} catch (...) {
		return false;
	}

// Daten aus Page lesen und speichern
long lIdent = 0;
short iOTyp = 0;
int i = 0;

// liefert alle Objekte die selektierten Einträgen entsprechen
        if (GetFirstIdent (lIdent, iOTyp)) {
                do {
			m_pResult[i].m_lIdent = lIdent;
			m_pResult[i].m_iOTyp = iOTyp;
                } while (i++ < m_iCnt && GetNextIdent (lIdent, iOTyp));
        }

return true;
}

///////////////////////////////////////////////////////////////////////////////
// AbfrageRoutinen ------------------------------------------------------------
bool CSelectIdentDlg :: GetFirstIdent (long &rlIdent, short &riOTyp)
{
	if (m_pIdents) 
		return m_pIdents -> GetFirstIdent (rlIdent, riOTyp);
		
return false;
}

bool CSelectIdentDlg :: GetNextIdent (long &rlIdent, short &riOTyp)
{
	if (m_pIdents) 
		return m_pIdents -> GetNextIdent (rlIdent, riOTyp);
		
return false;
}

int CSelectIdentDlg :: GetItemCount (void)
{
	if (m_pIdents) 
		return m_pIdents -> GetItemCount();
		
return 0;
}

int CSelectIdentDlg :: GetSelectedCount (void)
{
	if (m_pIdents) 
		return m_pIdents -> GetSelectedCount();
		
return 0;
}

bool CSelectIdentDlg :: SelectIdent (long lIdent, short iOTyp, bool fSel)
{
	if (m_pIdents) {
	bool fResult = m_pIdents -> SelectIdent (lIdent, iOTyp, fSel);

		AdjustOK();
		return fResult;
	}
		
return false;
}

