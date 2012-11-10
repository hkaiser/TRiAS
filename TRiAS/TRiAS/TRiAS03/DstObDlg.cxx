// Auswahl von Objekten verschiedener Recherchefenster ------------------------
// File: DSTOBDLG.CXX

#include "trias03p.hxx"
#include "trias03.h"

#include <xtsnguid.h>
#include <eonrguid.h>
#include <propguid.h>
#include <statguid.h>

#include <eieruhr.hxx>
#include <TrCatIds.h>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "enumonr.hxx"
#include "dstobdlg.hxx"
#include "dstobwnd.hxx"

extern char g_pDLLName[_MAX_PATH];		// dieser Modul

// Konstruktor/Destruktor/Initialisierung -------------------------------------
#pragma warning (disable: 4355)

CDestObjWndDlg :: CDestObjWndDlg (CDestObjWndPropAct *pParent, 
								  ResID uiDlg, LPCSTR pcCaption)
		: CPropertyPage (uiDlg, pcCaption),
		  m_lbObjWnds (this, IDC_LISTOBJWND),
		  m_rbCreateNew (this, IDC_CREATENEWOBJWND),
		  m_rbSelectOld (this, IDC_SELECTOBJWND),
		  m_cbRetainSelection (this, IDC_RETAINSELECTION),
		  m_cbSelectNew (this, IDC_SELECTNEW),
		  m_dwFlags(0), m_pParent(pParent)
{
	m_hWnd = NULL;

	m_fRetainSelection = false;
	m_fSelectNew = false;
}

#pragma warning (default: 4355)

CDestObjWndDlg :: ~CDestObjWndDlg (void)
{
}

CDestObjWndDlg *CDestObjWndDlg :: CreateInstance (CDestObjWndPropAct *pParent,
		ResID uiRes, LPCSTR pcCaption)
{
	try {
	CDestObjWndDlg *pDlg = NULL;
	
		pDlg = new CDestObjWndDlg (pParent, uiRes, pcCaption);
		if (pDlg == NULL || !pDlg -> FInit()) {
			DELETE_OBJ (pDlg);
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
namespace {
	BOOL PASCAL GetORWnds (LONG hWnd, BOOL, void *pData)
	{
	char cbCaption[128];
	os_string strCaption;

		::GetWindowText ((HWND)hWnd, cbCaption, sizeof(cbCaption));
		strCaption = cbCaption;
		((CObjWnds *)pData) -> insert (make_pair (strCaption, (HWND)hWnd));
		return true;
	}
}

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
		SetDirty();
		AdjustLB();
		AdjustOK();
		break;

	case IDC_SELECTOBJWND:		// existierendes Fenster verwenden
		SetDirty();
		AdjustLB();
		AdjustOK();
		break;
	}
}

void CDestObjWndDlg :: ListBoxSel (ControlEvt e)
{
	SetDirty();
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
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Hilfsfunktionen, um Objekte aufzusammeln -----------------------------------
extern "C" bool PASCAL GetObjectsFromObjWnd (long lONr, bool, void *pData);

///////////////////////////////////////////////////////////////////////////////
// HilfsRoutinen --------------------------------------------------------------
void CDestObjWndDlg :: AdjustOK (bool fDisableNext)
{
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

	SetSheetWizardButtons (dwBttns);
}

void CDestObjWndDlg :: AdjustLB (void)
{
int iCnt = m_lbObjWnds.GetCount();

	if (m_rbCreateNew.GetState() || 0 == iCnt) {
		m_lbObjWnds.Disable();
		m_cbRetainSelection.Disable();
		m_cbSelectNew.SetChecked(FALSE);	// neue Objekte nicht selektieren
	} 
	else {
		m_lbObjWnds.Enable();
		m_cbRetainSelection.Enable();
		m_cbSelectNew.SetChecked(TRUE);		// neue Objekte selektieren
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

	m_hWnd = NULL;		// default: neues Fenster erzeugen
	if (!m_rbCreateNew.GetState() && -1 != iIndex) {
	char cbBuffer[128];

		m_lbObjWnds.GetString (cbBuffer, iIndex, sizeof(cbBuffer));

	CObjWnds::const_iterator it = m_ObjWnds.find (os_string (cbBuffer));

		if (it != m_ObjWnds.end())
			m_hWnd = (*it).second;

		if (NULL != m_hWnd && (!IsWindow(m_hWnd) || !DEX_IsORWindow(m_hWnd)))
			m_hWnd = NULL;		// ORFenster existiert nicht mehr, neues erzeugen
	}

return true;
}

///////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CDestObjWndDlg::SetDirty (bool fDirty)
{ 
	if (m_pParent) m_pParent -> SetDirty (fDirty); 
}
