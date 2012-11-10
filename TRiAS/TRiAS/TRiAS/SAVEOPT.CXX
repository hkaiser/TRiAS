// DialogFenster zur Einstellung der Speicheroptionen -------------------------
// File: SAVEOPT.CXX

#include "triaspre.hxx"
#include "TRiASRes.h"

#include <registry.hxx>

#include "extmain3.hxx"
#include "saveopt.hxx"

extern short g_iMinutes;
extern Timer *g_pT;			// aller x Minuten speichern
extern short g_iMinutes;	
extern short g_iTicks;

// Konstruktor/Destruktor -----------------------------------------------------
#pragma warning (disable: 4355)

CSaveOptionsDlg::CSaveOptionsDlg (pWindow pW)
		 : CPropertyPage (IDD_SAVEOPTIONS, ResString (IDS_OPTIONSCAP, 32)),
		   m_scMinutes (this, IDC_MINUTE_SPIN),
		   m_cbAutoSave (this, IDB_AUTOSAVE),
		   m_sleMinutes (this, IDE_AUTOSAVE),
		   m_cbStartDlg (this, IDC_SHOWSTARTDLG),
		   m_cbTipOfTheDay (this, IDC_TIPOFTHEDAY),
		   m_cbBackupFiles (this, IDC_BACKUPDATAFILES),
		   m_pW(pW)
{
}

void CSaveOptionsDlg::WindowInit(Event e)
{
	m_scMinutes.FInit();
	m_cbAutoSave.FInit();
	m_sleMinutes.FInit();
	m_cbTipOfTheDay.FInit();
	m_cbStartDlg.FInit();
	m_cbBackupFiles.FInit();

// Zeit zwischen Speicheroperationen setzen
	if (NULL != DEX_GetActiveProjectHandle()) {
		if (g_iMinutes > 0)
			m_cbAutoSave.SetChecked (TRUE);
		else
			m_cbAutoSave.SetChecked (FALSE);
			
		m_scMinutes.SetRange (0, 1000);
		m_scMinutes.SetPos (g_iMinutes);
	} else {
		m_cbAutoSave.SetChecked (FALSE);
		m_cbAutoSave.Disable();

		m_scMinutes.SetPos (0);
		m_scMinutes.Disable();
		m_sleMinutes.Disable();
	}
	m_iMinutes = g_iMinutes;

// TipOfTheDay
CCurrentUser regTip (g_cbTipOfTheDay);
DWORD dwData = 0;	// Defaultwert 0

	if (regTip.GetDWORD(g_cbTipOfTheDayStartUp, dwData) && 0 != dwData)
		m_cbTipOfTheDay.SetChecked(TRUE);
	else
		m_cbTipOfTheDay.SetChecked(FALSE);

// StartupDlg
CCurrentUser regStartDlg (g_cbRegOpenMRU);

	dwData = 0;		// Defaultwert 0
	if (regStartDlg.GetDWORD(g_cbHideOpenWizard, dwData) && 1 == dwData)
		m_cbStartDlg.SetChecked(FALSE);
	else
		m_cbStartDlg.SetChecked(TRUE);

// Text im Backupknopf enthält 'TRiAS'
//char cbFormat[_MAX_PATH];
//char cbBuffer[_MAX_PATH];
//
//	m_cbBackupFiles.GetText(cbFormat, sizeof(cbFormat));
//	wsprintf (cbBuffer, cbFormat, g_cbTRiAS);
//	m_cbBackupFiles.SetText(cbBuffer);

CCurrentUser regBackup (g_cbRegConfig);

	dwData = 0;		// Defaultwert 0
	if (regBackup.GetDWORD(g_cbBackupDatafiles, dwData) && 0 != dwData)
		m_cbBackupFiles.SetChecked(TRUE);
	else
		m_cbBackupFiles.SetChecked(FALSE);

	SetModified (false);		// für alle Fälle
}

#pragma warning (default: 4355)

CSaveOptionsDlg::~CSaveOptionsDlg (void)
{
}

///////////////////////////////////////////////////////////////////////////////
// EventHandler

///////////////////////////////////////////////////////////////////////////////
// OK oder Apply 
BOOL CSaveOptionsDlg::OnOK (NotifyEvt e)
{
	if (NULL != DEX_GetActiveProjectHandle()) {
		if (m_cbAutoSave.isChecked()) 
			g_iMinutes = m_scMinutes.GetPos();
		else
			g_iMinutes = 0;

		TX_ASSERT(NULL != m_pW);
		if (NULL != g_pT) {
			m_pW -> CancelStrobe (g_pT);
			DELETE_OBJ(g_pT);
		}

		if (g_iMinutes > 0) 
			TX_TRY(g_pT = new Timer (6000, TIMER_MINUTE));
		if (NULL != g_pT) 
			m_pW -> SetStrobe (g_pT);

		g_iTicks = 0;
	}

// TipOfTheDay
CCurrentUser regTip (g_cbTipOfTheDay);
DWORD dwData = m_cbTipOfTheDay.isChecked() ? 1 : 0;

	regTip.SetDWORD(g_cbTipOfTheDayStartUp, dwData);

// StartupDlg
CCurrentUser regStartDlg (g_cbRegOpenMRU);

	dwData = m_cbStartDlg.isChecked() ? 0 : 1;
	regStartDlg.SetDWORD(g_cbHideOpenWizard, dwData);

// BackupData
CCurrentUser regBackup (g_cbRegConfig);

	dwData = m_cbBackupFiles.isChecked() ? 1 : 0;
	regBackup.SetDWORD(g_cbBackupDatafiles, dwData);

	SetModified (FALSE);
	return FALSE;		// always allow operation
}

void CSaveOptionsDlg::EditFocusChg (EditFocusChgEvt e)
{
	if (e.gotFocus()) return;
	
	if (NULL != DEX_GetActiveProjectHandle() && 
		(uint)e.GetControlID() == IDE_AUTOSAVE) 
	{
	char cbBuffer[64];

		m_sleMinutes.GetText (cbBuffer, sizeof(cbBuffer));

	long lNewPos = atol (cbBuffer);

		if (m_iMinutes != lNewPos) {
			m_scMinutes.SetPos(lNewPos);

			if (m_scMinutes.GetPos() > 0)
				m_cbAutoSave.SetChecked (TRUE);
			else
				m_cbAutoSave.SetChecked (FALSE);

			SetModified (TRUE);
		}
	}
}

void CSaveOptionsDlg::ButtonClick (ControlEvt e)
{
	switch (e.GetControlID()) {
	case IDC_SHOWSTARTDLG:
	case IDC_TIPOFTHEDAY:
	case IDB_AUTOSAVE:
	case IDC_BACKUPDATAFILES:
		SetModified (TRUE);		// page is dirty
		break;
	}
}

void CSaveOptionsDlg::VertScroll (ScrollEvt e)
{
	CPropertyPage::VertScroll (e);		// erstmal verarbeiten lassen

	if (NULL != DEX_GetActiveProjectHandle()) {
		if (m_scMinutes.GetPos() > 0)
			m_cbAutoSave.SetChecked (TRUE);
		else
			m_cbAutoSave.SetChecked (FALSE);

		SetModified (TRUE);
	}
}
