// Auswahl aller Objekte verschiedener Objektklassen --------------------------
// File: SELIDENT.CXX

#include "triaspre.hxx"
	
#include <selidlst.hxx>

#include "selident.h"
#include "selident.hxx"

#include "triasres.h"

// Konstruktor/Destruktor/Initialisierung -------------------------------------
#pragma warning (disable: 4355)

CSelectIdentDlg :: CSelectIdentDlg (pWindow pW, uint uiDlg)
		 : DialogWindow (pW, uiDlg),
		   m_pbOK (this, IDOK),
#if !defined(WIN32)
		   m_pbHelp (this, IDHELP),
#endif // WIN32
		   m_pbSelAll (this, IDB_ALLCLASSES)
{
	m_pIdents = NULL;
	
#if !defined(WIN32)
	m_pbHelp.Disable();
#endif // WIN32
	m_pbOK.Disable();
	m_pbSelAll.Disable();
}

#pragma warning (default: 4355)

CSelectIdentDlg :: ~CSelectIdentDlg (void)
{
	DELETE (m_pIdents);
}

CSelectIdentDlg *CSelectIdentDlg :: CreateInstance (pWindow pW, uint uiDlg, uint uiList)
{
CEierUhr Wait (pW);
CSelectIdentDlg *pDlg = new CSelectIdentDlg (pW, uiDlg);

	if (pDlg == NULL || !pDlg -> FInit (uiList)) {
		DELETE (pDlg);
		return NULL;
	}
	
return pDlg;
}

bool CSelectIdentDlg :: FInit (uint uiList)
{
// IdentifikatorListBox füllen
	m_pIdents = CSelIdentList :: CreateInstance (this, uiList);
	if (m_pIdents == NULL) return false;

// Button SelectAll richten
	if (m_pIdents -> GetCount())
		m_pbSelAll.Enable();
	
return true;
}

// EventHandler ---------------------------------------------------------------
void CSelectIdentDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		EndDlg (1);
		break;
		
	case IDCANCEL:
		EndDlg (0);	// abbrechen
		break;
		
	case IDB_ALLCLASSES:	// alle markieren
		m_pIdents -> ChangeSelected (Range (0, m_pIdents -> GetCount() -1));
		AdjustOK();
		break;
		
	case IDHELP:
		break;
	}
}


void CSelectIdentDlg :: ListBoxSel (ControlEvt)
{
	AdjustOK();
}


// HilfsRoutinen --------------------------------------------------------------
void CSelectIdentDlg :: AdjustOK (void)
{
	if (!m_pIdents || m_pIdents -> GetNoSelected() == 0)
		m_pbOK.Disable();
	else
		m_pbOK.Enable();
}


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

bool CSelectIdentDlg :: SelectIdent (long lIdent, short iOTyp, bool fSel)
{
	if (m_pIdents) {
	bool fResult = m_pIdents -> SelectIdent (lIdent, iOTyp, fSel);

		AdjustOK();
		return fResult;
	}
		
return false;
}

#if defined(WIN32)
///////////////////////////////////////////////////////////////////////////////
// Durchschreiben der Visinfo in eine andere Sicht
//
#pragma warning (disable: 4355)

CCopyVisInfoDlg :: CCopyVisInfoDlg (pWindow pW, uint uiDlg)
		 : CSelectIdentDlg (pW, uiDlg),
		   m_rbDefaultView (this, IDR_DEFAULTVIEW),
		   m_rbOtherView (this, IDR_VIEWNAME),
		   m_cbViewNames (this, IDCB_VIEWNAMES)
{
	m_rbDefaultView.SetState (true);	// am Anfang StandardSicht
	m_rbOtherView.SetState (false);
	m_cbViewNames.Disable();
}

#pragma warning (default: 4355)

CCopyVisInfoDlg :: ~CCopyVisInfoDlg (void)
{
	// nothing else do do
}

CCopyVisInfoDlg *CCopyVisInfoDlg :: CreateInstance (pWindow pW, uint uiDlg, uint uiList)
{
CEierUhr Wait (pW);
CCopyVisInfoDlg *pDlg = new CCopyVisInfoDlg (pW, uiDlg);

	if (pDlg == NULL || !pDlg -> FInit (uiList)) {
		DELETE (pDlg);
		return NULL;
	}

return pDlg;
}

extern "C" bool WINAPI FillViewList (char *pPtr, bool, void *pCB);

bool CCopyVisInfoDlg :: FInit (uint uiList)
{
// Initialisierung der BasisKlasse
	if (!CSelectIdentDlg :: FInit (uiList)) return false;

// ComboBox mit allen SichtNamen füllen
ENUMNOKEY ENK;

	ENK.eFcn = (ENUMNOKEYPROC)FillViewList;
	ENK.ePtr = &m_cbViewNames;

bool fResult = DEX_EnumSights (ENK);
char cbActView[64];

	if (DEX_GetActiveSight (cbActView)) {
	int iIndex = m_cbViewNames.FindString (cbActView, true);

		if (iIndex != -1) m_cbViewNames.DelString (iIndex);
	}
	m_cbViewNames.ChangeCurrentIndex (0);
	AdjustOK();

return fResult;
}

// EventHandler ---------------------------------------------------------------
void CCopyVisInfoDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDR_DEFAULTVIEW:
		m_cbViewNames.Disable();
		AdjustOK();
		break;

	case IDR_VIEWNAME:
		m_cbViewNames.Enable();
		AdjustOK();
		break;

	default:
		CSelectIdentDlg :: ButtonClick (e);
	}
}

// HilfsRoutinen --------------------------------------------------------------
void CCopyVisInfoDlg :: AdjustOK (void)
{
	if (m_rbOtherView.GetState() &&
	    (m_cbViewNames.GetCount() == 0 || m_cbViewNames.GetCurrentIndex() == -1))
		m_pbOK.Disable();
	else
		CSelectIdentDlg :: AdjustOK();
}

bool CCopyVisInfoDlg :: GetViewName (char *pView, int iLen)
{
	if (m_rbDefaultView.GetState()) {
		strncpy (pView, ResString (IDS_DEFAULTVISINFO, 40), iLen-1);
		pView[iLen-1] = '\0';
		return true;
	}

	if (m_rbOtherView.GetState()) {
	int iIndex = m_cbViewNames.GetCurrentIndex();

		if (iIndex != -1) {
			m_cbViewNames.GetString (pView, iIndex, iLen);
			return true;
		}
	}

return false;
}

#endif // WIN32
