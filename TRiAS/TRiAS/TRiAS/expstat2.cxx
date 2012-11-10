// Fenster, welchesden ExportStatus anzeigt (in Prozent)
// File: EXPSTAT2.CXX

#include "triaspre.hxx"

#include "triasres.h"
#include "expstat.hxx"

#pragma warning (disable: 4355)

ExportStatus :: ExportStatus (pWindow pW, long lAllCnt, LPCSTR pcFName)
	      : m_pIStatus (NULL)
{
// Variablen initialisieren
HRESULT hr = PiCreateInstance (IID_IProgressIndicator, (LPVOID *)&m_pIStatus);

	if (FAILED(hr)) return;

HWND hNewWnd = m_pIStatus -> InitNew (pW -> Handle (API_WINDOW_HWND), 0L);

	if (NULL == hNewWnd) return;

	hr = m_pIStatus -> Restart (0L, (ULONG)lAllCnt, PIFLAG_ALL);
	if (FAILED(hr)) {
		m_pIStatus -> Release();
		m_pIStatus = NULL;
		return;
	}

// diverse Texte initialisieren
ResString resCaption (IDS_EXPORTCAP, 64);
ResString resStatus (IDS_EXPORTSTATUS, 64);

	m_pIStatus -> ChangeText (PIFLAG_CAPTION, resCaption);
	m_pIStatus -> ChangeText (PIFLAG_ADJUSTPERCENT, resStatus);
	m_pIStatus -> ChangeText (PIFLAG_FILENAME, pcFName);
	m_pIStatus -> ChangeText (PIFLAG_RESULT, "");
}

#pragma warning (default: 4355)

ExportStatus :: ~ExportStatus (void) 
{
	if (m_pIStatus) m_pIStatus -> Release();
}

void ExportStatus :: SetValue (long lCurrCnt, long lONr) 
{
	if (NULL == m_pIStatus) return;
	m_pIStatus -> SetPosition (lCurrCnt);

	if (lONr != -1) {
	ResString resObj (IDS_EXPORTOBJEKT, 32);
	char cbBuffer[32];

		wsprintf (cbBuffer, resObj, lONr);
		m_pIStatus -> ChangeText (PIFLAG_RESULT, cbBuffer);
	}
}

bool ExportStatus :: Break (void)
{
	if (NULL != m_pIStatus)
		return m_pIStatus -> WasCanceled();

return false;
}

