// DialogFenster zur Einstellung der Speicheroptionen -------------------------
// File: SAVEOPT.CXX

#include "triaspre.hxx"

#include "saveopt.hxx"

extern short g_iMinutes;

// Konstruktor/Destruktor -----------------------------------------------------
#pragma warning (disable: 4355)

CSaveOptionsDlg *CSaveOptionsDlg :: CreateInstance (pWindow pW)
{
CSaveOptionsDlg *pDlg = new CSaveOptionsDlg(pW);

	if (NULL == pDlg || !pDlg -> Init()) {
		DELETE(pDlg);
		return NULL;
	}

return pDlg;
}

CSaveOptionsDlg :: CSaveOptionsDlg (pWindow pW)
		 : DialogWindow (pW, SAVEOPTDLG),
#if !defined(WIN32)
		   m_pbHelp (this, IDB_SAVEHELP),
#endif // WIN32
		   m_scMinutes (this, IDE_AUTOSAVE, IDMS_AUTOSAVE, Range (0, 1000)),
		   m_cbAutoSave (this, IDB_AUTOSAVE),
		   m_cbAutoUpdate (this, IDB_AUTOUPDATE),
		   m_cbAutoUpdateClose (this, IDB_AUTOCLOSEUPDATE),
		   m_cbAutoRecovery (this, IDB_AUTORECOVERY)
{
#if !defined(WIN32)
	m_pbHelp.Disable();
#endif // WIN32

// Zeit zwischen Speicheroperationen setzen
	if (g_iMinutes > 0)
		m_cbAutoSave.SetChecked (TRUE);
	else
		m_cbAutoSave.SetChecked (FALSE);
		
	m_scMinutes.SetValue (g_iMinutes);

	m_cbAutoUpdate.Disable();	// alles andere disable'n
	m_cbAutoUpdateClose.Disable();
	m_cbAutoRecovery.Disable();

	m_iMinutes = g_iMinutes;
}

#pragma warning (default: 4355)

BOOL CSaveOptionsDlg :: Init (void)
{
	return TRUE;
}


CSaveOptionsDlg :: ~CSaveOptionsDlg (void)
{
	// nothing to do
}


// EventHandler ---------------------------------------------------------------
void CSaveOptionsDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		if (m_cbAutoSave.isChecked()) {
			m_scMinutes.CopyToSpin();
			m_iMinutes = m_scMinutes.GetValue();
		} else
			m_iMinutes = 0;
		EndDlg (1);
		break;
		
	case IDCANCEL:
		EndDlg ();
		break;
		
	case IDB_AUTOSAVE:
	case IDB_AUTOUPDATE:
	case IDB_AUTOCLOSEUPDATE:
	case IDB_AUTORECOVERY:
	case IDB_SAVEHELP:
		break;
	}
}


void CSaveOptionsDlg :: VertScroll (ScrollEvt e)
{
	if ((uint)e.GetScrollBar() -> GetID() == IDMS_AUTOSAVE) {
		m_scMinutes.CopyToEdit();
		if (m_scMinutes.GetValue() > 0)
			m_cbAutoSave.SetChecked (TRUE);
		else
			m_cbAutoSave.SetChecked (FALSE);
	}
}


void CSaveOptionsDlg :: EditFocusChg (EditFocusChgEvt e)
{
	if (e.gotFocus()) return;
	
	if ((uint)e.GetControlID() == IDE_AUTOSAVE) {
		m_scMinutes.CopyToSpin();
		if (m_scMinutes.GetValue() > 0)
			m_cbAutoSave.SetChecked (TRUE);
		else
			m_cbAutoSave.SetChecked (FALSE);
	}
}

