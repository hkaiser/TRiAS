// Auswahl eines Sicht aus einer Liste ---------------------------------------
// File: SELNVIEW.CXX

#include "triaspre.hxx"

#include "triasres.h"

#include "selnview.hxx"

// ---------------------------------------------------------------------------
bool IrisWind :: SelectView (void) 
{
char cbActualSight[MAXVIEWNAMESIZE+1];

	DBO().GetActiveSightName (cbActualSight, sizeof(cbActualSight));

CSelectViewDlg *pSVDlg = new CSelectViewDlg (this, DBO());

// Dialogfenster anzeigen
	if (pSVDlg && pSVDlg -> Init (cbActualSight)) {
		pSVDlg -> Show (Centre);          // Sichten löschen
		if (pSVDlg -> Result()) { 
			pSVDlg -> SelectView();

			SetShouldRedraw();
			InitWndScrollBars();		// Rollbalken zuschalten
			DEX_ReReadCaption();
			RePaint();
		}
		DELETE_OBJ (pSVDlg);
		return true;
	}

	DELETE_OBJ (pSVDlg);

return false;
}


// Eigentliches DialogFenster -------------------------------------------------
#if !defined(WIN16)

#include "dlghelp.h"

static DWORD s_dwHelp[] = {
	IDC_SELECTVIEWLIST,	IDH_SELECTVIEWDLG_SELECTVIEWLIST,
	IDT_SELECTVIEW,		IDH_SELECTVIEWDLG_SELECTVIEWLIST,
	IDOK,			IDH_SELECTVIEWDLG_OK,
	IDB_STANDARD,		IDH_SELECTVIEWDLG_STANDARD,
	IDCANCEL, 		IDH_SELECTVIEWDLG_IDCANCEL, 
	0,			0,		// EndeKennung
};

void CSelectViewDlg :: HelpRequest (HelpRequestEvt e)
{
	if (HelpWmHelp == e.RequestType()) {
	const HELPINFO *pHI = e.GetHelpInfo();
	char cbHelpFile[_MAX_PATH];

		strcpy (cbHelpFile, g_cbHelpPath);
		strcat (cbHelpFile, DIALOG_HELP_FILE);

		WinHelp ((HWND)pHI -> hItemHandle, cbHelpFile, 
			 HELP_WM_HELP, (DWORD)s_dwHelp);
	}
}

#endif // WIN16

extern "C" {

BOOL WINAPI EXPORTTRIAS FillSelectViewList (char *pPtr, BOOL, void *pLB)
{
	if (pLB && pPtr) {
		((ListBox *)pLB) -> AddString (pPtr);
		return true;
	}
	
return false;
}

}

#pragma warning (disable: 4355)

CSelectViewDlg :: CSelectViewDlg (pWindow pW, DatenBasisObjekt &rDBO)
		: DialogWindow (pW, IDD_SELECTVIEW),
		  m_ViewList (this, IDC_SELECTVIEWLIST),
		  m_OKButton (this, IDOK),
		  m_cbDefView (this, IDB_STANDARD),
#if defined(WIN16)
		  m_HelpButton (this, IDB_DELETEVIEWHELP),
#endif // WIN16
		  m_rDBO (rDBO)
{
	m_OKButton.Disable();
	m_cbDefView.Disable();
	m_cbDefView.SetChecked (false);

#if defined(WIN16)
	m_HelpButton.Disable();
#endif // WIN16
}

#pragma warning (default: 4355)

CSelectViewDlg :: ~CSelectViewDlg (void)
{
	// nothing to do
}


bool CSelectViewDlg :: Init (LPCSTR pActView)
{
// ListBox füllen
ENUMNOKEY ENK;

	ENK.eFcn = (ENUMNOKEYPROC)FillSelectViewList;
	ENK.ePtr = &m_ViewList;
	if (!DEX_EnumSights (ENK))
		return false;
	
// aktuelle Sicht voreinstellen
short iIndex = -1;

	if (pActView && ('\0' != *pActView))
		iIndex = m_ViewList.FindString (pActView);

	m_ViewList.ChangeCurrentIndex (-1);

// OKButton freigeben
	if (m_ViewList.GetCount() > 0) {
	// Namen der StandardSicht einlesen
	char cbBuffer[64];

		if (DEX_GetDefaultView (cbBuffer))
			m_strDefView = cbBuffer;

	// OK Knopf richten
		if (iIndex != -1) {
			m_ViewList.ChangeCurrentIndex (iIndex);
			m_OKButton.Enable();
			m_cbDefView.Enable();
		} 

		AdjustDefView();
	}

return true;
}


void CSelectViewDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		EndDlg (1);
		break;
		
	case IDCANCEL:
		EndDlg (0);
		break;

	case IDB_STANDARD:
		HandleDefView();
		break;
		
//	case IDB_SELECTVIEWHELP:
//		break;
	}
}


void CSelectViewDlg :: ListBoxSel (ControlEvt)
{
	AdjustDefView();
	
	if (m_ViewList.GetCurrentIndex() != -1) {
		m_OKButton.Enable();
		m_cbDefView.Enable();
	} else {
		m_OKButton.Disable();
		m_cbDefView.Disable();
	}
}

void CSelectViewDlg :: ListBoxClk (ControlEvt)
{
	EndDlg (1);
}

void CSelectViewDlg :: AdjustDefView (void)
{
char cbNewView[MAXVIEWNAMESIZE+1];

	if (GetNewView (cbNewView, sizeof(cbNewView)))
		m_cbDefView.SetChecked (!strcmp (cbNewView, m_strDefView.c_str()));
}

bool CSelectViewDlg :: SelectView (void)
{
char cbNewView[MAXVIEWNAMESIZE+1];

	if (GetNewView (cbNewView, sizeof(cbNewView))) {
		if (m_cbDefView.isChecked())
		// neue Startansicht einstellen
			DEX_SetDefaultView (cbNewView);
		else if (0 == m_strDefView.length())
		// alte Startansicht löschen
			DEX_SetDefaultView (NULL);

		DEX_SelectNewSight (cbNewView);
		return true;
	}

return false;
}

bool CSelectViewDlg :: GetNewView (char *pBuffer, int iLen)
{
int iIndex = m_ViewList.GetCurrentIndex();

	if (iIndex >= 0) {
		m_ViewList.GetString (pBuffer, iIndex, iLen);
		return true;
	}

return false;
}

void CSelectViewDlg :: HandleDefView (void)
{
char cbNewView[MAXVIEWNAMESIZE+1];

	if (GetNewView (cbNewView, sizeof(cbNewView))) {
		if (m_cbDefView.isChecked())
		// eine Sicht soll Startansicht sein
			m_strDefView = cbNewView;
		else {
		// Wenn die aktuelle StandardAnsicht ausgewählt ist, dann
		// soll keine Ansicht mehr StartAnsicht sein, ansonsten wieder
		// die vorherige StartAnsicht.
		char cbBuffer[MAXVIEWNAMESIZE+1];

			DEX_GetDefaultView (cbBuffer);
			if (!strcmp (cbNewView, cbBuffer)) 
				m_strDefView.remove();
			else
				m_strDefView = cbBuffer;
		}
	}
}

