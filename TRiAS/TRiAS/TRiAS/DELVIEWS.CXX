// Loeschen einer/mehrerer Sichten nach Vorgabe -------------------------------
// File: DELVIEWS.CXX

#include "triaspre.hxx"

#if !defined(WIN16)
#include <dirisole.h>
#include "extmain3.hxx"
#endif

#include "delviews.h"
#include "delviews.hxx"

// ---------------------------------------------------------------------------
bool IrisWind :: DeleteViews (void) 
{
char cbActualSight[MAXVIEWNAMESIZE+1];

	DBO().GetActiveSightName (cbActualSight, sizeof(cbActualSight));

CDeleteViewsDlg *pDVDlg = new CDeleteViewsDlg (this, DBO());

// Dialogfenster anzeigen
	if (pDVDlg && pDVDlg -> Init (cbActualSight)) {
		pDVDlg -> Show (Centre);          // Sichten löschen
		if (pDVDlg -> Result()) {
#if !defined(WIN16)
		ExtDirisWindow *pFrame = GetFrame();

			pDVDlg -> DeleteSelectedViews (pFrame ? pFrame -> MainMenu() : NULL);
#else
			pDVDlg -> DeleteSelectedViews (MainMenu());
#endif // WIN16
			DELETE_OBJ (pDVDlg);
			return true;
		}
	}

	DELETE_OBJ (pDVDlg);

return false;
}


// Eigentliches DialogFenster -------------------------------------------------
extern "C" {

BOOL WINAPI EXPORTTRIAS FillToDeleteViewList (char *pPtr, BOOL, void *pLB)
{
	if (pLB && pPtr) {
		((MultiSelListBox *)pLB) -> AddString (pPtr);
		return TRUE;
	}
	
return FALSE;
}

}

#pragma warning (disable: 4355)

CDeleteViewsDlg :: CDeleteViewsDlg (pWindow pW, DatenBasisObjekt &rDBO)
		 : DialogWindow (pW, DELETEVIEWDLG),
		   m_ViewList (this, IDL_DELETEVIEWLIST),
		   m_OKButton (this, IDOK),
#if defined(WIN16)
		   m_HelpButton (this, IDB_DELETEVIEWHELP),
#endif // WIN16
		   m_rDBO (rDBO)
{
	m_OKButton.Disable();
#if defined(WIN16)
	m_HelpButton.Disable();
#endif // WIN16
}

#pragma warning (default: 4355)

CDeleteViewsDlg :: ~CDeleteViewsDlg (void)
{
	// nothing to do
}


BOOL CDeleteViewsDlg :: Init (char * /*pActView*/)
{
// ListBox füllen
ENUMNOKEY ENK;

	ENK.eFcn = (ENUMNOKEYPROC)FillToDeleteViewList;
	ENK.ePtr = &m_ViewList;
	if (!DEX_EnumSights (ENK))
		return FALSE;
	
// aktuelle Sicht voreinstellen
// short iIndex = m_ViewList.FindString (pActView);

//	if (iIndex != -1) {
//		m_ViewList.ChangeSelected (iIndex, On);
//		m_OKButton.Enable();
//	}

return TRUE;
}


void CDeleteViewsDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		EndDlg (1);
		break;
		
	case IDCANCEL:
		EndDlg (0);
		break;
		
	case IDB_DELETEVIEWHELP:
		break;
	}
}


void CDeleteViewsDlg :: ListBoxSel (ControlEvt)
{
	if (m_ViewList.GetNoSelected() > 0)
		m_OKButton.Enable();
	else
		m_OKButton.Disable();
}


int CDeleteViewsDlg :: DeleteSelectedViews (pMenu pM)
{
int iCnt = m_ViewList.GetNoSelected();

	if (iCnt > 0) {
	CEierUhr Wait (GetParent());
	short iIndex = m_ViewList.GetFirstSelected();
	
#if defined(_FORCE_LEGACY_CODE)
		m_rDBO.DB().SetDirty();
#endif // _FORCE_LEGACY_CODE
		while (iIndex != -1) {
			DeleteSight (pM, iIndex);
			iIndex = m_ViewList.GetNextSelected();		
		}
	}
	
return iCnt;
}


void CDeleteViewsDlg :: DeleteSight (pMenu pM, short iIndex) 
{
// Namen der aktuellen Ansicht holen
char cbSight[SIGHTMENUITEM+1];

	m_ViewList.GetString (cbSight, iIndex, SIGHTMENUITEM+1);
	m_rDBO.DeleteView (pM, cbSight);
}
