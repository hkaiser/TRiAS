// Auswahl von Objekten verschiedener Recherchefenster ------------------------
// File: DSTOBDLG.CXX

#include "trias03p.hxx"
#include "trias03.h"

#include <xtsnguid.h>
#include <eonrguid.h>
#include <propguid.h>

#include <eieruhr.hxx>

#include "enumonr.hxx"
#include "dstobdlg.hxx"
#include "dstobwnd.hxx"

// Konstruktor/Destruktor/Initialisierung -------------------------------------
#pragma warning (disable: 4355)

CDestObjWndDlg :: CDestObjWndDlg (ResID uiDlg, LPCSTR pcCaption, DWORD dwFlags)
		: CPropertyPage (uiDlg, pcCaption),
		  m_lbObjWnds (this, IDC_LISTOBJWND),
		  m_rbCreateNew (this, IDC_CREATENEWOBJWND),
		  m_rbSelectOld (this, IDC_SELECTOBJWND),
		  m_cbRetainSelection (this, IDC_RETAINSELECTION),
		  m_cbSelectNew (this, IDC_SELECTNEW),
		  m_dwFlags(dwFlags)
{
	m_hWnd = NULL;

	m_fRetainSelection = false;
	m_fSelectNew = true;
}

#pragma warning (default: 4355)

CDestObjWndDlg :: ~CDestObjWndDlg (void)
{
}

CDestObjWndDlg *CDestObjWndDlg :: CreateInstance (
		UINT uiDlg, LPCSTR pcCaption, DWORD dwFlags)
{
	try {
	CDestObjWndDlg *pDlg = NULL;
	
		pDlg = new CDestObjWndDlg (uiDlg, pcCaption, dwFlags);
		if (pDlg == NULL || !pDlg -> FInit()) {
			DELETE (pDlg);
			return NULL;
		}
		return pDlg;
	} catch (...) {
		return NULL;
	}
}

bool CDestObjWndDlg :: FInit (void)
{
	return true;
}

// Der wohl wichtigste Unterschied zu einem normalen Dialogfenster besteht
// darin, daß alle Controls dieser Dialogseite explizit im WindowInit()-Event-
// handler initialisiert werden müssen (s.u.). Alle inhaltlichen Initialisierungen
// können erst danach erfolgen (und nicht wie gewohnt im Konstruktor)
void CDestObjWndDlg :: WindowInit (Event)
{
CEierUhr Wait (this);		// EierUhr anzeigen

// Liste mit ORFenstern initialisieren
	m_lbObjWnds.FInit();

	if (!FillObjWnds()) return;	// m_ObjWnds mit Recherchefenstern füllen

// alle Captions in Listbox eintragen
	for (CObjWnds::const_iterator it = m_ObjWnds.begin();
	     it != m_ObjWnds.end(); it++)
	{
		m_lbObjWnds.AddString ((*it).first.c_str());
	}

// sonstige Controls initialisieren
	m_rbCreateNew.FInit();
	m_rbSelectOld.FInit();
	m_cbRetainSelection.FInit();
	m_cbSelectNew.FInit();

	m_rbCreateNew.SetState (NULL == m_hWnd);
	m_rbSelectOld.SetState (NULL != m_hWnd);

	m_cbRetainSelection.SetChecked (m_fRetainSelection);
	m_cbSelectNew.SetChecked (m_fSelectNew);

	AdjustLB();
	AdjustOK();
}

///////////////////////////////////////////////////////////////////////////////
// Map der Recherchefenster füllen --------------------------------------------
bool PASCAL GetORWnds (LONG hWnd, bool, void *pData);

bool CDestObjWndDlg :: FillObjWnds (void)
{
ENUMNOKEYLONG ENK;

	ENK.eFcn = (ENUMNOKEYLONGPROC)GetORWnds;
	ENK.ePtr = &m_ObjWnds;

return DEX_EnumORWindows (ENK);
}

///////////////////////////////////////////////////////////////////////////////
// EventHandler ---------------------------------------------------------------
void CDestObjWndDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDC_CREATENEWOBJWND:	// neues Fenster erzeugen
	case IDC_SELECTOBJWND:		// existierendes Fenster verwenden
		AdjustLB();
		AdjustOK();
		break;
	}
}

void CDestObjWndDlg :: ListBoxSel (ControlEvt e)
{
	AdjustOK();
}

int CDestObjWndDlg :: OnSetActive (NotifyEvt e)
{
	AdjustOK();
	return 0;
}

// Der Dialog wurde mit Cancel geschlossen ------------------------------------
void CDestObjWndDlg :: OnCancel (NotifyEvt)
{
	// hier evtl. Aufräumarbeiten durchführen
}

int CDestObjWndDlg :: OnWizNext (NotifyEvt)
{
	if (PrepareResult())	// Ergebnisse zwischenspeichern
		return 0;
	
return -1;
}

// Finish wurde gedrückt ------------------------------------------------------
int CDestObjWndDlg :: OnWizFinish (NotifyEvt)
{
	PrepareResult();	// Ergebnisse zwischenspeichern

// wir sind die letzten, also Rückkehrwert aus PropertySheet setzen
CPropertySheet *pSheet = GetPropertySheet();

	if (NULL != pSheet)
		pSheet -> EndDialog(1);	

return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Hilfsfunktionen, um Objekte aufzusammeln -----------------------------------
extern "C" bool PASCAL GetObjectsFromObjWnd (long lONr, bool, void *pData);

// Setzt Objektmenge, die später angezeigt werden soll ------------------------
HRESULT CDestObjWndDlg :: SetEnumLONG (IEnum<LONG> *pEnum)
{
// Objektfeld anlegen
long lCnt = pEnum -> Count();
long *plObjs = NULL;
HRESULT hr = E_OUTOFMEMORY;

	if (0 == lCnt) return S_FALSE;
	try {
		plObjs = new long [lCnt];
		if (NULL == plObjs) throw E_OUTOFMEMORY;
		
		pEnum -> Reset();
		if (S_OK != pEnum -> Next(lCnt, plObjs, NULL))
			throw E_UNEXPECTED;

	} catch (...) {
		DELETE(plObjs);
		return hr;
	}

// evtl. alte Objekte deselektieren
	if (NULL != m_hWnd && !m_fRetainSelection)
		DEXOR_UnselectObject (m_hWnd, -1);	// alles deselektieren

// RechercheFenster anlegen
CREATEOBJEKTINFOEX2 COI;
ResString resCaption (ResID (IDS_NEWOBJCAPTION, &g_pTE -> RF()), 64);
POINT pt;

	pt.x = 0, pt.y = 0;
	
	INITSTRUCT (COI, CREATEOBJEKTINFOEX2);
	COI.lpCaption = (char *)resCaption.Addr();
	COI.plObjs = plObjs;
	COI.iNumObjs = short(lCnt);
	COI.cMColor = RGB(255, 0, 0);
	COI.pntPos = pt;
	COI.m_iFlags = ROSortText;
	COI.m_hWnd = m_hWnd;

	m_hWnd = DEX_CreateObjektInfo(COI);
	if (NULL == m_hWnd) {
		DELETE (plObjs);
		return ResultFromScode (E_FAIL);
	}

// neue Objekte selektieren
	DELETE (plObjs);
	if (!m_fSelectNew) return NOERROR;

LONG lONr = 0;

	for (pEnum -> Reset(); 
	     S_OK == pEnum -> Next (1, &lONr, NULL); /**/)
	{
		DEXOR_SelectObject (m_hWnd, lONr);
	}

return NOERROR;
}		        

///////////////////////////////////////////////////////////////////////////////
// HilfsRoutinen --------------------------------------------------------------
void CDestObjWndDlg :: AdjustOK (bool fDisableNext)
{
CPropertySheet *pSheet = GetPropertySheet();

	if (NULL == pSheet) return;

// Knöpfe des Dialoges richten (Next, Previous, Finish)
DWORD dwBttns = 0;
bool fEnable = m_rbCreateNew.GetState() || (-1 != m_lbObjWnds.GetCurrentIndex());

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns |= PSWIZB_BACK;

	if (fEnable && !fDisableNext) {
		if (m_dwFlags & ADDPAGES_LASTPAGE)
			dwBttns |= PSWIZB_FINISH;
		else
			dwBttns |= PSWIZB_NEXT;
	}

	pSheet -> SetWizardButtons (dwBttns);
}

void CDestObjWndDlg :: AdjustLB (void)
{
int iCnt = m_lbObjWnds.GetCount();

	if (m_rbCreateNew.GetState() || 0 == iCnt) {
		m_lbObjWnds.Disable();
		m_cbRetainSelection.Disable();
	} else {
		m_lbObjWnds.Enable();
		m_cbRetainSelection.Enable();
	}

	if (0 < iCnt) 
		m_rbSelectOld.Enable();
	else
		m_rbSelectOld.Disable();
}

// Ergebnisdaten aus Controls lesen und zwischenspeichern ---------------------
bool CDestObjWndDlg :: PrepareResult (void)
{
// sonstige Flags merken
	m_fRetainSelection = m_cbRetainSelection.isChecked() ? true : false;
	m_fSelectNew = m_cbSelectNew.isChecked() ? true : false;

// Fensterhandle des Zielfensters merken
int iIndex = m_lbObjWnds.GetCurrentIndex();

	m_hWnd = NULL;
	if (-1 != iIndex) {
	char cbBuffer[128];

		m_lbObjWnds.GetString (cbBuffer, iIndex, sizeof(cbBuffer));

	CObjWnds::const_iterator it = m_ObjWnds.find (os_string (cbBuffer));

		if (it != m_ObjWnds.end())
			m_hWnd = (*it).second;
	}

return true;
}

