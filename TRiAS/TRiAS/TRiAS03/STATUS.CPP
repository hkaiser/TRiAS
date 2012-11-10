// StatusDialog ---------------------------------------------------------------
// File: STATUS.CPP

#include "trias03p.hxx"

#include <time.h>
#include <containr.hxx>

#include <istatus.h>		// Konstanten, InterfaceDeklaration

#include "trias03.h"		// ResourceKonstanten
#include "status.hxx"		// DialogKlasse

extern char g_pDLLName[_MAX_PATH];

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#pragma warning (disable: 4355)
#pragma warning (disable: 4245)

CStatusDlg::CStatusDlg (pWindow pW, ResID uiRes)
	    : ModeLessDialog (pW, uiRes),
	      CancelButton (this, IDCANCEL),
	      m_gStatus (this, IDPB_STATUS),
	      m_ftFileName (this, IDT_FILENAME), m_ftFile (this, IDT_FILE),
	      m_ftStatus (this, IDT_PERCENT), m_ftResult (this, IDT_OBJECTNUMBER),
	      m_ftTimeText (this, IDT_TIMETEXT), m_ftTime (this, IDT_TIME),
		  m_aviAction (this, IDC_ANIMATE)
{
// Variablen initialisieren
	m_lRangeMin = 0;
	m_lRange = 0;
	m_lKoeff = 1L;

	m_lActPos = -1L;
	m_lLastSetting = -1L;

	m_tUpdateTime = 0;
	m_tStartTime = 0;
	m_tActTime = 0;
	for (int i = 0; i < NUMLASTTIMES; i++) 
		m_tTimes[i] = 0;
	
	m_fWasInterrupted = false;

	m_gStatus.SetRange (0, 1000);
	m_gStatus.SetPos (0);

	m_ftFile.SetText("");
	m_ftFileName.SetText("");
	m_ftStatus.SetText ("");
	m_ftResult.SetText("");

	m_ftTimeText.Hide();
	m_ftTime.Hide();
	m_fTimeShown = false;
	m_fAVIStarted = false;
	m_fDoNotShowTimeAnyFurther = false;
	m_fTimeWasShownOnce = false;		// Zeit war schon angezeigt

	m_fUpdate = true;	// auf jeden Fall Prozente aktualisieren

	m_fIsShown = false;

	pW -> Disable();
}

#pragma warning (default: 4355)

CStatusDlg::~CStatusDlg (void) 
{
	if (m_fAVIStarted) {
		m_aviAction.Stop();
		m_aviAction.Open ((LPCSTR)NULL);
	}
	GetParent() -> Enable();
}

inline void HandleFT (FixedText &ft, bool fFlag)
{
	if (fFlag) ft.Show();
	else	   ft.Hide();
}

bool CStatusDlg::FInit (LONG ulMin, LONG ulMax, DWORD dwFlags, bool fFlagsOnly)
{
	if (!fFlagsOnly) {
	// Controls initialisieren
		CancelButton.Enable();
		m_fWasInterrupted = false;

		if (dwFlags & PIFLAG_RESETCANCEL)
			return true;		// nur 'Abbrechen' rücksetzen

	// Zeit rücksetzen
		m_fTimeShown = false;
		m_fDoNotShowTimeAnyFurther = false;
		m_tUpdateTime = m_tStartTime = GetTickCount();
		m_fUpdate = true;

		m_tActTime = 0;
		for (int i = 0; i < NUMLASTTIMES; i++) 
			m_tTimes[i] = 0;

	// Scrollbereich für ProgressBar initialisieren
		m_lRangeMin = ulMin;
		m_lRange = ulMax - ulMin;

		if (0 == m_lRange) m_lRange = 1;

		m_lKoeff = 1L;
		if (m_lRange > 100000000L) m_lKoeff = 10000L;
		else if (m_lRange > 10000000L) m_lKoeff = 1000L;
		else if (m_lRange > 1000000L) m_lKoeff = 100L;
		else if (m_lRange > 100000L) m_lKoeff = 10L;

		TX_ASSERT(0 != m_lKoeff);	// Division durch 0 verhindern
		m_lRange /= m_lKoeff;

		m_ftFileName.SetText ("");
		m_ftStatus.SetText ("");
		m_ftResult.SetText("");
		m_strStatusText.remove();

		m_ftTimeText.Hide();
		m_ftTime.Hide();
		m_fTimeWasShownOnce = false;

		m_gStatus.SetPos (0);
		m_lActPos = 0L;
		m_lLastSetting = 0L;

		m_fAVIStarted = false;
	}
	
	return HandleFlags (dwFlags);
}

bool CStatusDlg::HandleFlags (DWORD dwFlags)
{
// Flags behandeln
	m_dwFlags = dwFlags & ~PIFLAG_INIT_SHOWWINDOW;

	HandleFT (m_ftFile, dwFlags & PIFLAG_FILE);
	HandleFT (m_ftFileName, dwFlags & PIFLAG_FILENAME);
	HandleFT (m_ftStatus, dwFlags & PIFLAG_STATUS);
	HandleFT (m_ftResult, dwFlags & PIFLAG_RESULT);
	
ResourceFile RF (g_pDLLName);

	if (dwFlags & PIFLAG_FILE) {
	ResString resFTpl (ResID (IDS_FILETEMPLATE, &RF), 64);

		m_ftFile.SetText(resFTpl);
	}

	switch (dwFlags & PIFLAG_AVI_MASK) {
	case PIFLAG_AVI_COPY:
		if (m_aviAction.Open (IDR_COPY_AVI))
			m_fAVIStarted = true;
		break;
		
	case PIFLAG_AVI_MOVE:
		if (m_aviAction.Open (IDR_MOVE_AVI))
			m_fAVIStarted = true;
		break;
		
	case PIFLAG_AVI_DELETE:
		if (m_aviAction.Open (IDR_DELETE_AVI))
			m_fAVIStarted = true;
		break;
	}

	if (dwFlags & PIFLAG_INIT_SHOWWINDOW) {
		Show();
		Update();
		m_fIsShown = true;
	}
	
	return true;
}

HRESULT CStatusDlg::GetRange (ULONG *plMin, ULONG *plMax)
{
	if (NULL == plMin || NULL == plMax) return E_POINTER;
	
	*plMin = (ULONG)m_lRangeMin;
	*plMax = (ULONG)(m_lRangeMin+m_lRange);
	return S_OK;
}

int CStatusDlg::SetPos (ULONG lActCnt) 
{
	if (!m_fIsShown) {	// spätestens bei erstem SetPos Fenster anzeigen
		Show();
		Update();
		m_fIsShown = true;
	}

	TX_ASSERT(0 != m_lRange);

LONG lCurrVal = (((lActCnt - m_lRangeMin)/m_lKoeff) * 1000)/m_lRange;

	if (lCurrVal != m_lActPos) {
		m_lActPos = lCurrVal;
		m_gStatus.SetPos (int(lCurrVal));
	}

// evtl. automatisch verbleibende Zeit berechnen und anzeigen
time_t lActTime = GetTickCount();

	if (m_dwFlags & PIFLAG_TIME)
		UpdateTime (lActCnt, lActTime);

// evtl. automatisch den Text aktualisieren
	if (m_dwFlags & PIFLAG_ADJUSTPERCENT) {
		if (m_fUpdate || lActTime - m_tUpdateTime > PI_MIN_UPDATETIME) {
		// nur nach Ablauf einer gewissen Zeit ändern, oder wenn neuer Text
			if (UpdateStatus (lCurrVal/10)) 
				m_tUpdateTime = lActTime;

			m_fUpdate = false;
		}
	}

	m_lLastSetting = lActCnt;		// letzter gesetzter Wert
	return int(lCurrVal/10);
}

HRESULT CStatusDlg::SetFile (LPCSTR pcText)
{
	if (m_dwFlags & PIFLAG_FILE) {
		m_ftFile.SetText (pcText);
		Update();
		return NOERROR;
	}

	return E_UNEXPECTED;
}

// Verkürzt einen Dateinamen --------------------------------------------------
static LPCSTR ShortenPath (LPCSTR pcName, int iMaxLen, LPSTR cbBuffer)
{
	TX_ASSERT(iMaxLen > 4);

char cbOut[_MAX_PATH];
int iLen = strlen (pcName);

	strcpy (cbBuffer, pcName);

	if (iLen > 4) {
		iMaxLen = min (iLen, iMaxLen);

	char *cptr = strchr (cbBuffer + iLen - iMaxLen + 4, '\\');
	char *cptr1 = strchr (cbBuffer, '\\');

		if (cptr && cptr1 && cptr > cptr1) {
		        *cptr1 = '\0';
			wsprintf (cbOut, "%s\\...%s", cbBuffer, cptr);
		} else
			strcpy (cbOut, cbBuffer);
	} else
		strcpy (cbOut, cbBuffer);

char pFormat[80];

        wsprintf (pFormat, "%%-%d.%ds", iMaxLen, iMaxLen);
        wsprintf (cbBuffer, pFormat, cbOut);

	return cbBuffer;
}

HRESULT CStatusDlg::SetFileName (LPCSTR pcText)
{
	if (m_dwFlags & PIFLAG_FILENAME) {
	char cbBuffer[_MAX_PATH];

		m_ftFileName.SetText (ShortenPath (pcText, 32, cbBuffer));
		Update();
		return NOERROR;
	}

	return E_UNEXPECTED;
}

HRESULT CStatusDlg::SetStatus (LPCSTR pcText)
{
	if (m_dwFlags & PIFLAG_STATUS) {
		if (!(m_strStatusText == string(pcText))) {
			m_strStatusText = pcText;
			m_ftStatus.SetText (pcText);
			Update();
		}
		return NOERROR;
	}

	return E_UNEXPECTED;
}

HRESULT CStatusDlg::SetStatusText (LPCSTR pcText)
{
	m_strStatusText = pcText;
	m_fUpdate = true;	// nächstes Update durchführen
	return NOERROR;
}

HRESULT CStatusDlg::SetResult (LPCSTR pcText)
{
	if (m_dwFlags & PIFLAG_RESULT) {
		m_ftResult.SetText (pcText);
		Update();
		return NOERROR;
	}
	return E_UNEXPECTED;
}

bool CStatusDlg::UpdateTime (LONG lActCnt, time_t tActTime)
{
	if (!(m_dwFlags & PIFLAG_TIME))
		return false;

// verbleibende Zeit berechnen
time_t lTime = tActTime - m_tStartTime;	// Zeit seit Importbeginn

// über die letzten Zeiten integrieren
	if (lActCnt != 0 && !IntegrateTime (long(lTime * (((double(m_lKoeff)*m_lRange)/lActCnt) - 1)), lTime))	
		return false;		// noch nicht gültig, keine Zeit ausgeben

	if (m_fDoNotShowTimeAnyFurther)
		return true;		// Flackern am Ende verhindern

	if (!m_fTimeShown && lTime > 20) {
		m_ftTimeText.Show();
		m_ftTime.Show();
		m_fTimeShown = true;
	}
	if (m_fTimeShown && m_tActTime != lTime) {
	string strTime;

		m_tActTime = lTime;
		if (!SetTime (lTime, strTime, false)) {
			if (m_fTimeWasShownOnce) {
				m_ftTimeText.Hide();	// am Schluß wieder ausblenden
				m_ftTime.Hide();
				m_fTimeShown = false;
				m_fDoNotShowTimeAnyFurther = true;
				return false;
			}
		} else {
		string old;
		char cbBuffer[_MAX_PATH];

			m_ftTime.GetText (cbBuffer, _MAX_PATH);
			old = cbBuffer;
			if (!(old == strTime)) {
				m_ftTime.SetText (strTime.c_str());
				Update();
				m_fTimeWasShownOnce = true;
			}
		}
	}
	return true;
}

void CStatusDlg::ButtonClick (ControlEvt) 
{
	m_fWasInterrupted = true;	// 'Abbrechen' wurde gedrückt
	CancelButton.Disable();		// 'Abbrechen' grau machen
}

bool CStatusDlg::IntegrateTime (time_t lTime, time_t &rlAvTime)
{
time_t lSumTime = 0L;
bool fValid = true;

	for (int i = 0; i < NUMLASTTIMES-1; i++) {
		m_tTimes[i] = m_tTimes[i+1];
		lSumTime += m_tTimes[i];
		if (0 == m_tTimes[i])
			fValid = false;
	}
	m_tTimes[NUMLASTTIMES-1] = lTime;
	lSumTime += lTime;

	if (fValid) 
		rlAvTime = lSumTime/NUMLASTTIMES;

	return fValid;
}

// Zeit in einem FixedText darstellen -----------------------------------------
bool CStatusDlg::SetTime (time_t lTime, string &rStr, bool fFullTime)
{
char cbBuffer[64];

	lTime /= 1000;		// [ms] interessieren nicht

long lHours = lTime/3600;

	if (lHours > 0) {
		ltoa (lHours, cbBuffer, 10);
		rStr += cbBuffer;
		rStr += " h ";
	}
	lTime -= lHours*3600;

long lMins = lTime/60;

	if (lHours > 0 || lMins > 0) {
		if (lMins > 0) {
			ltoa (lMins, cbBuffer, 10);
			rStr += cbBuffer;
			rStr += " min";
		}
		if (!fFullTime)
			return rStr.length() > 0 ? true : false;
	}

long lSecs = lTime - lMins*60;

	if (lHours > 0 || lMins > 0 || lSecs > 0) {
		ltoa (lSecs, cbBuffer, 10);
		rStr += " ";
		rStr += cbBuffer;
		rStr += " sek";
	}

	return rStr.length() > 0 ? true : false;
}

bool CStatusDlg::UpdateStatus (int iPercent)
{
char cbBuffer[_MAX_PATH];
string str;

	if ((m_dwFlags & PIFLAG_STATUS) && m_strStatusText.length() > 0) {
		wsprintf (cbBuffer, m_strStatusText.c_str(), iPercent);

		str = cbBuffer;
		m_ftStatus.GetText (cbBuffer, _MAX_PATH);

	string old (cbBuffer);

		if (!(old == str)) {
			m_ftStatus.SetText (str.c_str());
			Update();
		}
		return true;
	}

	return false;
}

LRESULT CStatusDlg::Dispatch (Event e)
{
	switch (e.Msg()) {
	case WM_CTLCOLORSTATIC:
		if ((HWND)e.LParam() == m_aviAction.Handle()) {
			SetBkColor ((HDC)e.WParam(), GetSysColor (COLOR_3DFACE)); //GetSysColor (COLOR_3DFACE));
			return (LRESULT)GetSysColorBrush(COLOR_3DFACE);
		}
		break;

	default:
		break;
	}
	return ModeLessDialog::Dispatch(e);
}

#if defined(_USE_TIMEGETTIME)
///////////////////////////////////////////////////////////////////////////////
// Dynamisches Binden der WINMM.DLL
CWinMMBind::CWinMMBind (void)
	: DLLBind (TEXT("WINMM.DLL")), m_fIsValid(false)
{
	if (NULL == hLib()) return;		// Initialisierungs-Fehler

	m_pTimeGetTime = (TIMEGETTIMEPROC)GetProcAddress (TEXT("timeGetTime"));
	if (NULL != m_pTimeGetTime)
		m_fIsValid = true;
}

DWORD CWinMMBind::timeGetTime (void)
{
	TX_ASSERT(NULL != m_pTimeGetTime);
	return m_pTimeGetTime();
}
#endif // _USE_TIMEGETTIME
