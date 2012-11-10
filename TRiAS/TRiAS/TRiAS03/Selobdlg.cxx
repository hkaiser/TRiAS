// Auswahl von Objekten verschiedener Recherchefenster ------------------------
// File: SELOBDLG.CXX

#include "trias03p.hxx"
#include "trias03.h"

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
#include "selobdlg.hxx"
#include "selobwnd.hxx"

// Konstruktor/Destruktor/Initialisierung -------------------------------------
#pragma warning (disable: 4355)

CSelectObjWndDlg::CSelectObjWndDlg (CSelObjWndPropAct *pParent, ResID uiDlg, 
									  LPCSTR pcCaption, HWND hWndToIgnore)
		  : CPropertyPage (uiDlg, pcCaption),
		    m_mslbObjWnds (this, IDC_LISTOBJWND),
		    m_pbSelAll (this, IDC_SELECTALL),
		    m_rbSelectedObjs (this, IDC_SELECTEDOBJECTS),
		    m_rbAllObjs (this, IDC_ALLOBJECTS),
			m_rbActivated (this, IDC_ACTIVATED),
			m_cbCloseWhenReady (this, IDC_CLOSEWHENREADY),
		    m_dwFlags(0), m_pParent(pParent), m_hWndToIgnore(hWndToIgnore)
{
	m_rgMode = SELECTMODE_Selected;
	m_hORWnd = NULL;
	m_fCloseWhenReady = false;
	m_fDisableCloseWhenReady = false;
	m_fAllowForOneObjectSelection = false;
	m_hORWndToClose = NULL;
}

#pragma warning (default: 4355)

CSelectObjWndDlg::~CSelectObjWndDlg (void)
{
	if (NULL != m_hORWndToClose) {
		DEX_RemoveORWnd(m_hORWndToClose);
		m_hORWndToClose = NULL;
	}
}

CSelectObjWndDlg *CSelectObjWndDlg::CreateInstance (
	CSelObjWndPropAct *pParent, ResID uiDlg, LPCSTR pcCaption, HWND hWndToIgnore)
{
	try {
	CSelectObjWndDlg *pDlg = NULL;
	
		pDlg = new CSelectObjWndDlg (pParent, uiDlg, pcCaption, hWndToIgnore);
		if (pDlg == NULL || !pDlg -> FInit()) {
			DELETE_OBJ (pDlg);
			return NULL;
		}
		return pDlg;
	} catch (...) {
		return NULL;
	}
}

bool CSelectObjWndDlg::FInit (void)
{
	return true;
}

// Der wohl wichtigste Unterschied zu einem normalen Dialogfenster besteht
// darin, daß alle Controls dieser Dialogseite explizit im WindowInit()-Event-
// handler initialisiert werden müssen (s.u.). Alle inhaltlichen Initialisierungen
// können erst danach erfolgen (und nicht wie gewohnt im Konstruktor)
void CSelectObjWndDlg::WindowInit (Event)
{
CEierUhr Wait (this);		// EierUhr anzeigen

// Liste mit ORFenstern initialisieren
	m_mslbObjWnds.FInit();

	if (!FillObjWnds()) return;	// m_ObjWnds mit Recherchefenstern füllen

// alle Captions in Listbox eintragen
int iIndex = -1;
int i = 0;

	for (CObjWnds::const_iterator it = m_ObjWnds.begin(); it != m_ObjWnds.end(); it++, i++)
	{
		m_mslbObjWnds.AddString ((*it).first.c_str());
		if (NULL != m_hORWnd && m_hORWnd == (*it).second)
			iIndex = i;
	}
	if (1 == m_ObjWnds.size() || -1 == iIndex)	// wenn nur einer, dann diesen markieren
		m_mslbObjWnds.ChangeSelected (0);
	else
		m_mslbObjWnds.ChangeSelected (iIndex);	// ansonsten TargetWnd

// Button SelectAll initialisieren und richten
	m_pbSelAll.FInit();
	if (m_mslbObjWnds.GetCount() && !m_fAllowForOneObjectSelection)
		m_pbSelAll.Enable();
	else
		m_pbSelAll.Disable();

// sonstige Controls initialisieren
	m_rbSelectedObjs.FInit();
	m_rbAllObjs.FInit();
	m_rbActivated.FInit();
	m_cbCloseWhenReady.FInit();

	m_rbSelectedObjs.SetState (false);
	m_rbAllObjs.SetState (false);
	m_rbActivated.SetState (false);

	switch (m_rgMode) {
	case SELECTMODE_Activated:
		m_rbActivated.SetState (true);
		break;

	case SELECTMODE_Selected:
		m_rbSelectedObjs.SetState (true);
		break;

	case SELECTMODE_All:
		m_rbAllObjs.SetState (true);
		break;
	}
	if (m_fDisableCloseWhenReady) {
		m_cbCloseWhenReady.Disable();
		m_fCloseWhenReady = false;
	} else
		m_cbCloseWhenReady.SetChecked(m_fCloseWhenReady);

	if (m_fAllowForOneObjectSelection) {
		m_rbActivated.SetState(1);
		m_rbSelectedObjs.SetState(0);
		m_rbSelectedObjs.Disable();
		m_rbAllObjs.SetState(0);
		m_rbAllObjs.Disable();
	}

	AdjustOK();
}

///////////////////////////////////////////////////////////////////////////////
// Map der Recherchefenster füllen 
namespace {

	typedef struct tagENUMOBJWNDDATA {
		CObjWnds *pObjWnds;
		HWND hWndToIgnore;
	} ENUMOBJWNDDATA;

	// extern "C" 
	BOOL PASCAL GetORWnds (LONG hWnd, BOOL, void *pData)
	{
	ENUMOBJWNDDATA *pEOWD = reinterpret_cast<ENUMOBJWNDDATA *>(pData);
	
		if (pEOWD -> hWndToIgnore == reinterpret_cast<HWND>(hWnd))
			return TRUE;

	char cbCaption[128];
	os_string strCaption;

		::GetWindowText ((HWND)hWnd, cbCaption, sizeof(cbCaption));
		strCaption = cbCaption;
		pEOWD -> pObjWnds -> insert (make_pair (strCaption, (HWND)hWnd));
		return true;
	}
}

bool CSelectObjWndDlg::FillObjWnds (void)
{
	m_ObjWnds.erase();
	m_itcurr = m_ObjWnds.end();

ENUMNOKEYLONG ENK;
ENUMOBJWNDDATA EOWD;

	EOWD.pObjWnds = &m_ObjWnds;
	EOWD.hWndToIgnore = m_hWndToIgnore;

	ENK.eFcn = (ENUMNOKEYLONGPROC)GetORWnds;
	ENK.ePtr = &EOWD;
	if (DEX_EnumORWindows (ENK)) {
		m_itcurr = m_ObjWnds.begin();
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// EventHandler 
void CSelectObjWndDlg::ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDC_SELECTALL:	// alle markieren
		{
		int iCnt = m_mslbObjWnds.GetCount();

			if (iCnt > 0) {
				m_mslbObjWnds.ChangeSelected (Range (0, iCnt-1));
				AdjustOK();
			}
		}
		break;

	case IDC_SELECTEDOBJECTS:
		break;

	case IDC_ALLOBJECTS:
		break;
	}
}

void CSelectObjWndDlg::ListBoxSel (ControlEvt e)
{
	AdjustOK();
}

int CSelectObjWndDlg::OnSetActive (NotifyEvt e)
{
	if (m_mslbObjWnds.GetCount() != m_ObjWnds.size()) 
		FillObjWnds();

	AdjustOK();
	return 0;
}

// Der Dialog wurde mit Cancel geschlossen ------------------------------------
void CSelectObjWndDlg::OnCancel (NotifyEvt)
{
	// hier evtl. Aufräumarbeiten durchführen
}

int CSelectObjWndDlg::OnWizNext (NotifyEvt)
{
	if (PrepareResult())	// Ergebnisse zwischenspeichern
		return 0;
	return -1;
}

// Finish wurde gedrückt ------------------------------------------------------
int CSelectObjWndDlg::OnWizFinish (NotifyEvt)
{
	PrepareResult(); 	// Ergebnisse zwischenspeichern
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Hilfsfunktionen, um Objekte aufzusammeln -----------------------------------
extern "C" 
BOOL PASCAL GetObjectsFromObjWnd (long lONr, BOOL, void *pData)
{
	((IEnum<LONG> *)pData) -> AddItem (lONr);
	return true;	// immer weiter machen
}

bool FillTrees (SELECTMODE rgMode, HWND hORWnd, IEnum<LONG> *pIEnum)
{
// Enumerator füllen
ENUMLONGKEY ELK;

	ELK.eKey = (DWORD)(void *)hORWnd;
	ELK.eFcn = (ENUMLONGKEYPROC)GetObjectsFromObjWnd;
	ELK.ePtr = pIEnum;

	if (SELECTMODE_Selected == rgMode) {	// nur selektierte Objekte
		return DEX_EnumSelectedObjects(ELK);
	}
	else if (SELECTMODE_Activated == rgMode) {
	LONG lONr = DEX_GetActiveObject (hORWnd);

		return GetObjectsFromObjWnd (lONr, false, pIEnum);
	}

// alle Objekte
	_ASSERTE(SELECTMODE_All == rgMode);
	return DEX_EnumAllORObjects(ELK);
}

// Fragt den Dialog nach seinen Daten -----------------------------------------
HRESULT CSelectObjWndDlg::GetEnumLONG (IEnum<LONG> **ppIEnum)
{
	if (NULL == ppIEnum) 
		return E_POINTER;

	if (NULL != m_hORWndToClose) {
		DEX_RemoveORWnd(m_hORWndToClose);	// dieses ORWnd jetzt schließen
		m_hORWndToClose = NULL;
	}

	COM_TRY {
	WEnumLONG IObjs (CLSID_EnumObjectsByNumber);	// Enumerator generieren

	// ProgInd handeln
		SetMaxTicks(m_ObjWnds.size());

	// Enumerator füllen
		if (m_itcurr != m_ObjWnds.end()) {
			FillTrees (m_rgMode, (*m_itcurr).second, IObjs);
			if (!m_fDisableCloseWhenReady && m_fCloseWhenReady)
				m_hORWndToClose = (*m_itcurr).second;	// bem nächsten mal schließen

			++m_itcurr;
			Tick();			// ProgInd handeln
			if (FAILED(GoOn()))
				_com_issue_error(E_ABORT);
		}
		*ppIEnum = IObjs.detach();

	} COM_CATCH_NOASSERT_ON(E_ABORT);

	if (m_itcurr == m_ObjWnds.end())
		return S_OK;

	return S_FALSE;		// es kommt noch was
}

///////////////////////////////////////////////////////////////////////////////
// HilfsRoutinen 
void CSelectObjWndDlg::AdjustOK (bool fDisableNext)
{
// Knöpfe des Dialoges richten (Next, Previous, Finish)
DWORD dwBttns = 0;
int iCnt = m_mslbObjWnds.GetNoSelected();

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns |= PSWIZB_BACK;

	if (0 < iCnt && !fDisableNext) {
		if (m_dwFlags & ADDPAGES_LASTPAGE)
			dwBttns |= PSWIZB_FINISH;
		else
			dwBttns |= PSWIZB_NEXT;
	} else if (m_dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	if (m_mslbObjWnds.GetCount() > 0)
		m_pbSelAll.Enable();
	else
		m_pbSelAll.Disable();

	SetSheetWizardButtons (dwBttns);
}

// Ergebnisdaten aus Controls lesen und zwischenspeichern ---------------------
bool CSelectObjWndDlg::PrepareResult (void)
{
	if (0 == m_mslbObjWnds.GetNoSelected()) 
		return false;

int iCnt = m_mslbObjWnds.GetCount();

	for (int i = 0; i < iCnt; i++) {
	// nicht selektierte Einträge aus der map löschen
		if (!m_mslbObjWnds.GetSelection(i)) {
		char cbBuffer[128];

			m_mslbObjWnds.GetString (cbBuffer, i, sizeof(cbBuffer));
			m_ObjWnds.erase (os_string (cbBuffer));
		}
	}
	m_itcurr = m_ObjWnds.begin();
	
// Merken, ob alle Objekte oder nur selektierte
	if (m_rbSelectedObjs.GetState())
		m_rgMode = SELECTMODE_Selected;
	else if (m_rbActivated.GetState())
		m_rgMode = SELECTMODE_Activated;
	else 
		m_rgMode = SELECTMODE_All;

	if (!m_fDisableCloseWhenReady)
		m_fCloseWhenReady = m_cbCloseWhenReady.isChecked();
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CSelectObjWndDlg::SetDirty (bool fDirty)
{ 
	if (m_pParent) m_pParent -> SetDirty (fDirty); 
}
