// Auswahl aller Objekte verschiedener Objektklassen --------------------------
// File: SELIDENT.CXX

#include "trias03p.hxx"
#include "trias03.h"

#include <xtsnguid.h>
#include <eonrguid.h>
#include <propguid.h>
#include <statguid.h>

#include <eieruhr.hxx>
#include <funcs03.h>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "enumonr.hxx"
#include "selident.hxx"
#include "selidprp.hxx"

// Konstruktor/Destruktor/Initialisierung -------------------------------------
#pragma warning (disable: 4355)

CSelectIdentDlg :: CSelectIdentDlg (CSelIDPropAct *pParent, ResID uiDlg, 
									LPCSTR pcCaption)
		 : CPropertyPage (uiDlg, pcCaption),
		   m_pbSelAll (this, IDB_SELALLCLASSES),
		   m_dwFlags(0), m_pParent(pParent)
{
	m_pIdents = NULL;	// ListViewCtrl

	m_fResultPrepared = false;
}

#pragma warning (default: 4355)

CSelectIdentDlg :: ~CSelectIdentDlg (void)
{
	DELETE_OBJ (m_pIdents);
}

CSelectIdentDlg *CSelectIdentDlg :: CreateInstance (
		CSelIDPropAct *pParent, ResID resID, LPCSTR pcCaption)
{
	try {
	CSelectIdentDlg *pDlg = NULL;
	
		pDlg = new CSelectIdentDlg (pParent, resID, pcCaption);
		if (pDlg == NULL || !pDlg -> FInit()) {
			DELETE_OBJ (pDlg);
			return NULL;
		}
		return pDlg;
	} catch (...) {
		return NULL;
	}
}

bool CSelectIdentDlg :: FInit (void)
{
// IdentifikatorListBox füllen
	m_pIdents = new CSelIdentListView (this, IDC_LISTIDENTS);
	if (m_pIdents == NULL) return false;

	return true;
}

// Vergleichsfunktion, um Reihenfolge festzulegen
int CALLBACK CmpEntries (LPARAM lParam1, LPARAM lParam2, LPARAM dwData)
{
CSelIdentItem *pItem1 = reinterpret_cast<CSelIdentItem *>(lParam1);
CSelIdentItem *pItem2 = reinterpret_cast<CSelIdentItem *>(lParam2);
char cbBuffer1[MAX_OKS_LEN];
char cbBuffer2[MAX_OKS_LEN];

// bei Fehler Reihenfolge beibehalten
	if (NULL == pItem1 || NULL == pItem2)
		return -1;
	if (FAILED(ClassFromIdent (pItem1->m_ulIdent, cbBuffer1)))
		return -1;
	if (FAILED(ClassFromIdent (pItem2->m_ulIdent, cbBuffer2)))
		return -1;

	return strcmp (cbBuffer1, cbBuffer2);
}

// Der wohl wichtigste Unterschied zu einem normalen Dialogfenster besteht
// darin, daß alle Controls dieser Dialogseite explizit im WindowInit()-Event-
// handler initialisiert werden müssen (s.u.). Alle inhaltlichen Initialisierungen
// können erst danach erfolgen (und nicht wie gewohnt im Konstruktor)
void CSelectIdentDlg :: WindowInit (Event)
{
CEierUhr Wait (this);		// EierUhr anzeigen

// ListViewCtrl initialisieren/Identifikatoren laden
	if (NULL == m_pIdents ||
		!m_pIdents -> InitControl(OTPunkt|OTLinie|OTFlaeche|OTText, 
								m_caSelIds.ulSelectFrom, //fje
								/*SELIDMODE_NOICONS|SELIDMODE_ALLIDENTSPBD,*/
								/*SELIDMODE_SINGLETYPE,*/ NULL, CmpEntries, 
								  reinterpret_cast<DWORD>(m_pIdents)))
	{
		return;
	}

// new for 'Nashville' (#HK960823)
#if defined(ListView_GetExtendedListViewStyle)
	if (IsWin40()) {
	DWORD dwStyleEx = m_pIdents -> GetExtendedStyle();

		m_pIdents -> SetExtendedStyle (dwStyleEx | LVS_EX_FULLROWSELECT);
	}
#endif 

// Button SelectAll initialisieren und richten
	m_pbSelAll.FInit();
	if (m_pIdents -> GetItemCount())
		m_pbSelAll.Enable();
	else
		m_pbSelAll.Disable();

	AdjustOK();

// Einträge vorselektieren
int iIndex = -1;

	for (ULONG ul = 0; ul < m_caSelIds.cElems; ul++) 
		iIndex = SelectIdent (m_caSelIds.pElems[ul].m_lIdent, m_caSelIds.pElems[ul].m_iOTyp);
	
	if (-1 != iIndex) {	// letzten selektierten mit Focus versehen
		m_pIdents -> EnsureVisible (iIndex, false);
		m_pIdents -> SelectItemFocus (iIndex);
	}
}

///////////////////////////////////////////////////////////////////////////////
// EventHandler ---------------------------------------------------------------
void CSelectIdentDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDB_SELALLCLASSES:	// alle markieren
		m_pIdents -> ChangeSelectedAll (true);
		SetDirty();
		AdjustOK();
		break;
	}
}

void CSelectIdentDlg :: OnItemChanged (NotifyEvt e)
{
NM_LISTVIEW *pNfyData = reinterpret_cast<NM_LISTVIEW *>(e.GetNotifyInfo());

	if (!(pNfyData -> uChanged & LVIF_STATE))
		return;		// Status nicht geändert

// Selektion erhalten/verloren
	if (pNfyData -> uOldState & LVIS_SELECTED ||
		pNfyData -> uNewState & LVIS_SELECTED)
	{
		SetDirty();
		AdjustOK();
	}

//	if (((NM_LISTVIEW *)e.GetNotifyInfo()) -> uChanged & LVIF_STATE)
//		AdjustOK();
}

int CSelectIdentDlg :: OnSetActive (NotifyEvt)
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

// HilfeRoutine ---------------------------------------------------------------
void CSelectIdentDlg::HelpRequest (HelpRequestEvt e)
{
const HELPINFO *pHI = e.GetHelpInfo();

	TX_ASSERT(pHI);
}

///////////////////////////////////////////////////////////////////////////////
// Hilfsfunktionen, um Objekte aufzusammeln -----------------------------------
extern "C" 
BOOL PASCAL GetObjectsFromIdentDoc (long lONr, DWORD dwOTyp, void *pData)
{
	((IEnum<LONG> *)pData) -> AddItem (lONr);

return true;	// immer weiter machen
}

bool FillTrees (long lIdent, short iOTyp, IEnum<LONG> *pIEnum)
{
// Enumerator füllen
ENUMLONGKEYEX ELK;

	ELK.eKey = lIdent;
	ELK.eFcn = (ENUMLONGKEYEXPROC)GetObjectsFromIdentDoc;
	ELK.ePtr = pIEnum;
	ELK.eData = (DWORD)iOTyp;
	
return DEX_EnumIdentObjectsEx (ELK);
}

// Fragt den Dialog nach seinen Daten -----------------------------------------
HRESULT CSelectIdentDlg :: GetEnumLONG (IEnum<LONG> **ppIEnum)
{
	if (NULL == ppIEnum) return ResultFromScode (E_POINTER);

	try {
	WEnumLONG IObjs (CLSID_EnumObjectsByNumber); // Enumerator generieren

	// Enumerator füllen
	// JG 980915  ProgIndicator behandeln
		SetMaxTicks(m_caSelIds.cElems);

		for (ULONG i = 0; i < m_caSelIds.cElems; i++) 
		{
			FillTrees (m_caSelIds.pElems[i].m_lIdent, m_caSelIds.pElems[i].m_iOTyp, IObjs);
			Tick();
		}
		*ppIEnum = IObjs.detach();

		// explizit Statusanzeige auf 100 %
		TickToEnd();

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// HilfsRoutinen --------------------------------------------------------------
void CSelectIdentDlg :: AdjustOK (bool fDisableNext)
{
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

	SetSheetWizardButtons (dwBttns);
}

// Ergebnisdaten aus Controls lesen und zwischenspeichern ---------------------
bool CSelectIdentDlg :: PrepareResult (void)
{
int iCnt = GetSelectedCount();

	try {
	// Feld aufbauen und mit selektierten Einträgen füllen
		m_caSelIds.SetData (iCnt, (SELIDRESULT *)CoTaskMemAlloc (iCnt*sizeof(SELIDRESULT)));
		if (NULL == m_caSelIds.pElems)
			_com_issue_error(E_OUTOFMEMORY);

		m_fResultPrepared = true;
	
	} catch (...) {
		return false;
	}

// Daten aus Page lesen und speichern
long lIdent = 0;
short iOTyp = 0;
int i = 0;

// liefert alle Objekte die selektierten Einträgen entsprechen
	iCnt = 0;
	if (GetFirstIdent (lIdent, iOTyp, i)) {
		do {
			m_caSelIds.pElems[iCnt].m_lIdent = lIdent;
			m_caSelIds.pElems[iCnt].m_iOTyp = iOTyp;
			iCnt++;
		} while (i < (int)m_caSelIds.cElems && GetNextIdent (lIdent, iOTyp, i));
	}

	m_caSelIds.cElems = iCnt;	// wahre Anzahl

return true;
}

///////////////////////////////////////////////////////////////////////////////
// AbfrageRoutinen ------------------------------------------------------------
bool CSelectIdentDlg :: GetFirstIdent (long &rlIdent, short &riOTyp, int &riCnt)
{
	if (m_pIdents) 
		return m_pIdents -> GetFirstIdentEx (rlIdent, riOTyp, riCnt);
		
return false;
}

bool CSelectIdentDlg :: GetNextIdent (long &rlIdent, short &riOTyp, int &riCnt)
{
	if (m_pIdents) 
		return m_pIdents -> GetNextIdentEx (rlIdent, riOTyp, riCnt);
		
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

int CSelectIdentDlg :: SelectIdent (long lIdent, short iOTyp, bool fSel)
{
	if (m_pIdents) {
	int fResult = -1;
	
		if (iOTyp & OTPunkt) 
			fResult = m_pIdents -> SelectIdent (lIdent, OTPunkt, fSel);
		if (iOTyp & OTLinie) 
			fResult = m_pIdents -> SelectIdent (lIdent, OTLinie, fSel);
		if (iOTyp & OTFlaeche) 
			fResult = m_pIdents -> SelectIdent (lIdent, OTFlaeche, fSel);
		if (iOTyp & OTText) 
			fResult = m_pIdents -> SelectIdent (lIdent, OTText, fSel);

		AdjustOK();
		return fResult;
	}
		
return -1;
}

// Setzen und Abfragen der Dialoginformationen
HRESULT CSelectIdentDlg::GetSelectedInfo (CCaSelIdResult *pSelInfo)
{
	if (!m_fResultPrepared)	return S_FALSE;

	try {
		*pSelInfo = m_caSelIds;		// throws hr
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return NOERROR;
}

HRESULT CSelectIdentDlg::SetSelectedInfo (CCaSelIdResult *pSelInfo, bool fNoShow)
{
// AnfangsInitialisierung
	m_fResultPrepared = fNoShow;

	if (NULL == pSelInfo) return E_POINTER;

	try {
		m_caSelIds = *pSelInfo;		// umkopieren
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CSelectIdentDlg::SetDirty (bool fDirty)
{ 
	if (m_pParent) m_pParent -> SetDirty (fDirty); 
}
