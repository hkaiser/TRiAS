// Auswahl von Objekten verschiedener Recherchefenster ------------------------
// File: SELOBDLG.CXX

#include "featurep.hxx"
#include "feature.h"

#include <eieruhr.hxx>

#include "enumonr.hxx"
#include "selobdlg.hxx"

// Konstruktor/Destruktor/Initialisierung -------------------------------------
#pragma warning (disable: 4355)

CSelectObjWndDlg :: CSelectObjWndDlg (ResID uiDlg, LPCSTR pcCaption, DWORD dwFlags)
		  : CPropertyPage (uiDlg, pcCaption),
		    m_mslbObjWnds (this, IDC_LISTOBJWND),
		    m_pbSelAll (this, IDC_SELECTALL),
		    m_rbSelectedObjs (this, IDC_SELECTEDOBJECTS),
		    m_rbAllObjs (this, IDC_ALLOBJECTS),
		    m_dwFlags(dwFlags)
{
	m_fSelected = false;
}

#pragma warning (default: 4355)

CSelectObjWndDlg :: ~CSelectObjWndDlg (void)
{
}

CSelectObjWndDlg *CSelectObjWndDlg :: CreateInstance (
		UINT uiDlg, LPCSTR pcCaption, DWORD dwFlags, ResourceFile &rRF)
{
	try {
	CSelectObjWndDlg *pDlg = NULL;
	
		pDlg = new CSelectObjWndDlg (ResID (uiDlg, &rRF), pcCaption, dwFlags);
		if (pDlg == NULL || !pDlg -> FInit(rRF)) {
			DELETE (pDlg);
			return NULL;
		}
		return pDlg;
	} catch (...) {
		return NULL;
	}
}

bool CSelectObjWndDlg :: FInit (ResourceFile &rRF)
{
	return true;
}

// Der wohl wichtigste Unterschied zu einem normalen Dialogfenster besteht
// darin, daß alle Controls dieser Dialogseite explizit im WindowInit()-Event-
// handler initialisiert werden müssen (s.u.). Alle inhaltlichen Initialisierungen
// können erst danach erfolgen (und nicht wie gewohnt im Konstruktor)
void CSelectObjWndDlg :: WindowInit (Event)
{
CEierUhr Wait (this);		// EierUhr anzeigen

// Liste mit ORFenstern initialisieren
	m_mslbObjWnds.FInit();

	if (!FillObjWnds()) return;	// m_ObjWnds mit Recherchefenstern füllen

// alle Captions in Listbox eintragen
	for (CObjWnds::const_iterator it = m_ObjWnds.begin();
	     it != m_ObjWnds.end(); it++)
	{
		m_mslbObjWnds.AddString ((*it).first.c_str());
	}
	if (1 == m_ObjWnds.size())	// wenn nur einer, dann diesen markieren
		m_mslbObjWnds.ChangeSelected (0);

// Button SelectAll initialisieren und richten
	m_pbSelAll.FInit();
	if (m_mslbObjWnds.GetCount())
		m_pbSelAll.Enable();
	else
		m_pbSelAll.Disable();

// sonstige Controls initialisieren
	m_rbSelectedObjs.FInit();
	m_rbAllObjs.FInit();

	m_rbSelectedObjs.SetState (true);
	m_rbAllObjs.SetState (false);

	AdjustOK();
}

///////////////////////////////////////////////////////////////////////////////
// Map der Recherchefenster füllen --------------------------------------------
// extern "C" 
bool PASCAL GetORWnds (LONG hWnd, bool, void *pData)
{
char cbCaption[128];
os_string strCaption;

	::GetWindowText ((HWND)hWnd, cbCaption, sizeof(cbCaption));
	strCaption = cbCaption;
	((CObjWnds *)pData) -> insert (make_pair (strCaption, (HWND)hWnd));

return true;
}

bool CSelectObjWndDlg :: FillObjWnds (void)
{
ENUMNOKEYLONG ENK;

	ENK.eFcn = (ENUMNOKEYLONGPROC)GetORWnds;
	ENK.ePtr = &m_ObjWnds;

return DEX_EnumORWindows (ENK);
}

///////////////////////////////////////////////////////////////////////////////
// EventHandler ---------------------------------------------------------------
void CSelectObjWndDlg :: ButtonClick (ControlEvt e)
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

void CSelectObjWndDlg :: ListBoxSel (ControlEvt e)
{
	AdjustOK();
}

int CSelectObjWndDlg :: OnSetActive (NotifyEvt e)
{
	AdjustOK();
	return 0;
}

// Der Dialog wurde mit Cancel geschlossen ------------------------------------
void CSelectObjWndDlg :: OnCancel (NotifyEvt)
{
	// hier evtl. Aufräumarbeiten durchführen
}

int CSelectObjWndDlg :: OnWizNext (NotifyEvt)
{
	if (PrepareResult())	// Ergebnisse zwischenspeichern
		return 0;

return -1;
}

// Finish wurde gedrückt ------------------------------------------------------
int CSelectObjWndDlg :: OnWizFinish (NotifyEvt)
{
	PrepareResult(); 	// Ergebnisse zwischenspeichern

// wir sind die letzten, also Rückkehrwert aus PropertySheet setzen
CPropertySheet *pSheet = GetPropertySheet();

	if (NULL != pSheet)
		pSheet -> EndDialog(1);	

return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Hilfsfunktionen, um Objekte aufzusammeln -----------------------------------
extern "C" 
bool PASCAL GetObjectsFromObjWnd (long lONr, bool, void *pData)
{
	((CEnumObjectNumbers *)pData) -> AddObject (lONr);

return true;	// immer weiter machen
}

bool FillTrees (bool fSelected, HWND hORWnd, CEnumObjectNumbers *pEnum)
{
// Enumerator füllen
ENUMLONGKEY ELK;

	ELK.eKey = (DWORD)(void *)hORWnd;
	ELK.eFcn = (ENUMLONGKEYPROC)GetObjectsFromObjWnd;
	ELK.ePtr = pEnum;

	if (fSelected)	// nur selektierte Objekte
		return DEX_EnumSelectedObjects(ELK);

// alle Objekte
return DEX_EnumAllORObjects(ELK);
}

// Fragt den Dialog nach seinen Daten -----------------------------------------
HRESULT CSelectObjWndDlg :: GetEnumLONG (IEnum<LONG> **ppEnum)
{
	if (NULL == ppEnum) return ResultFromScode (E_POINTER);

// Enumerator generieren
CEnumObjectNumbers *pEnum = CEnumObjectNumbers::CreateInstance();

	if (NULL == pEnum) return ResultFromScode (E_OUTOFMEMORY);

// Enumerator füllen
	for (CObjWnds::const_iterator it = m_ObjWnds.begin();
		 it != m_ObjWnds.end(); it++)
	{
		FillTrees (m_fSelected, (*it).second, pEnum);
	}

// IEnumLONG abfragen
HRESULT hr = pEnum -> QueryInterface (IID_IEnumLONG, (LPVOID *)ppEnum);

	pEnum -> Release();

return hr;
}

///////////////////////////////////////////////////////////////////////////////
// HilfsRoutinen --------------------------------------------------------------
void CSelectObjWndDlg :: AdjustOK (bool fDisableNext)
{
CPropertySheet *pSheet = GetPropertySheet();

	if (NULL == pSheet) return;

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
	} 

	if (m_mslbObjWnds.GetCount() > 0)
		m_pbSelAll.Enable();
	else
		m_pbSelAll.Disable();

	pSheet -> SetWizardButtons (dwBttns);
}

// Ergebnisdaten aus Controls lesen und zwischenspeichern ---------------------
bool CSelectObjWndDlg :: PrepareResult (void)
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

// Merken, ob alle Objekte oder nur selektierte
	m_fSelected = m_rbSelectedObjs.GetState() ? true : false;

return true;
}

