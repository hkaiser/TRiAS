// StatusDialog ---------------------------------------------------------------
// File: STATUS.CPP

#include "ascimpp.hpp"

#include "ascimp.h"		// ResourceKonstanten
#include "status.hxx"		// DialogKlasse

#pragma warning (disable: 4355)

CStatusDlg :: CStatusDlg (pWindow pW)
	    : ModeLessDialog (pW, ResID (IDD_STATUSDLG, &g_pTE -> RF())),
	      CancelButton (this, IDCANCEL),
	      m_gStatus (this, IDPB_STATUS),
	      m_ftFileName (this, IDT_FILENAME), m_ftStatus (this, IDT_PERCENT),
	      m_ftONr (this, IDC_OBJECTNUMBER),
	      m_ftTimeText (this, IDT_TIMETEXT), m_ftTime (this, IDT_TIME)
{
// Variablen initialisieren
	m_lRange = 0;
	m_lActPos = -1L;
	m_lONr = 0L;
	m_lActTime = 0;

	m_lKoeff = 1L;
	
	m_fWasInterrupted = false;
	m_gStatus.SetRange (0, 1000);
	m_gStatus.SetPos (0);

	m_ftFileName.SetText("");
	m_ftStatus.SetText ("");
	m_ftONr.SetText("");

	m_ftTimeText.Hide();
	m_ftTime.Hide();
	m_fTimeShown = false;

	for (int i = 0; i < NUMLASTTIMES; i++) 
		m_lTimes[i] = 0;

	pW -> Disable();
}

#pragma warning (default: 4355)

CStatusDlg :: ~CStatusDlg (void) 
{
	GetParent() -> Enable();
}

bool CStatusDlg :: FInit (long lSize, LPCSTR pFile)
{
	m_lONr = 0L;
	m_lActTime = 0;

	m_lRange = lSize;
	m_lKoeff = 1L;

	if (m_lRange > 100000000L) m_lKoeff = 10000L;
	else if (m_lRange > 10000000L) m_lKoeff = 1000L;
	else if (m_lRange > 1000000L) m_lKoeff = 100L;
	else if (m_lRange > 100000L) m_lKoeff = 10L;

	m_lRange /= m_lKoeff;

char cbBuffer[_MAX_PATH];
ResourceFile &rRF = g_pTE -> RF();
ResString resFTpl (ResID (IDS_FILETEMPLATE, &rRF), 64);

	wsprintf (cbBuffer, resFTpl.Addr(), pFile);
	m_ftFileName.SetText(cbBuffer);
	m_ftStatus.SetText (ResString (ResID (IDS_IMPORTHEADER, &rRF), 64));
	m_ftONr.SetText("");

	m_ftTimeText.Hide();
	m_ftTime.Hide();
	m_fTimeShown = false;

	for (int i = 0; i < NUMLASTTIMES; i++) 
		m_lTimes[i] = 0;

	m_gStatus.SetPos (0);

return true;
}

void CStatusDlg :: SetPos (long lActCnt, long lONr) 
{
long lCurrVal = ((lActCnt/m_lKoeff) * 1000)/m_lRange;
char cbBuffer[_MAX_PATH];

	if (lCurrVal != m_lActPos) {
	ResString resPTpl (ResID (IDS_PERCENTTEMPLATE, &g_pTE -> RF()), 64);

		wsprintf (cbBuffer, resPTpl.Addr(), lCurrVal/10); 
		m_ftStatus.SetText (cbBuffer);
		::UpdateWindow(m_ftStatus.Handle());
		m_lActPos = lCurrVal;

		m_gStatus.SetPos (int(lCurrVal));
	}
	if (m_lONr != lONr) {
	ResString resOTpl (ResID (IDS_OBJECTNUMBERTEMPLATE, &g_pTE -> RF()), 64);

		wsprintf (cbBuffer, resOTpl.Addr(), lONr); 
		m_ftONr.SetText (cbBuffer);
		::UpdateWindow(m_ftONr.Handle());
		m_lONr = lONr;
	}

// verbleibende zeit berechnen
long lTime = timeGetTime() - g_lTime;	// Zeit seit Importbeginn

	if (!IntegrateTime (long(lTime * (((double(m_lKoeff)*m_lRange)/lActCnt) - 1)), lTime))	// ¸ber die letzten Zeiten integrieren
		return;			// noch nicht g¸ltig, keine Zeit ausgeben

	if (!m_fTimeShown && lTime > 20) {
		m_ftTimeText.Show();
		m_ftTime.Show();
		m_fTimeShown = true;
	}
	if (m_fTimeShown && m_lActTime != lTime) {
		if (!SetTime (lTime, m_ftTime, false)) {
			m_ftTimeText.Hide();	// am Schluﬂ wieder ausblenden
			m_ftTime.Hide();
		} else
			::UpdateWindow (m_ftTime.Handle());
		m_lActTime = lTime;
	}
}

void CStatusDlg :: ButtonClick (ControlEvt) 
{
	m_fWasInterrupted = true;		// Export abbrechen
}

bool CStatusDlg :: IntegrateTime (long lTime, long &rlAvTime)
{
long lSumTime = 0L;
bool fValid = true;

	for (int i = 0; i < NUMLASTTIMES-1; i++) {
		m_lTimes[i] = m_lTimes[i+1];
		lSumTime += m_lTimes[i];
		if (0 == m_lTimes[i])
			fValid = false;
	}
	m_lTimes[NUMLASTTIMES-1] = lTime;
	lSumTime += lTime;

	if (fValid) rlAvTime = lSumTime/NUMLASTTIMES;

return fValid;
}

// Zeit in einem FixedText darstellen -----------------------------------------
bool SetTime (long lCnt, FixedText &ft, bool fFullTime)
{
char cbBuffer[64];
string str;

	lCnt /= 1000;		// [ms] interessieren nicht

long lHours = lCnt/3600;

	if (lHours > 0) {
		ltoa (lHours, cbBuffer, 10);
		str += cbBuffer;
		str += " h ";
	}
	lCnt -= lHours*3600;

long lMins = lCnt/60;

	if (lHours > 0 || lMins > 0) {
		if (lMins > 0) {
			ltoa (lMins, cbBuffer, 10);
			str += cbBuffer;
			str += " min";
		}
		if (!fFullTime) {
			ft.SetText (str.c_str());
			return str.length() > 0 ? true : false;
		}
	}

long lSecs = lCnt - lMins*60;

	if (lHours > 0 || lMins > 0 || lSecs > 0) {
		ltoa (lSecs, cbBuffer, 10);
		str += " ";
		str += cbBuffer;
		str += " sek";
	}

	ft.SetText (str.c_str());

return str.length() > 0 ? true : false;
}
