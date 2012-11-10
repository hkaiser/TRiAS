// Fenster, welches den CStatus anzeigt (in Prozent)
// File: KPSTATUS.CXX

#include "kompp.hxx"
#include "version.h"
#include "kompdef.h"  
#include "kompias.h"
#include <triashelper_i.c>
#include <statguid.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


#include "about.hxx"

#include <igeometr.hxx> 
#include "triasdef.h"  

#include "kpstatus.hxx"

#pragma warning (disable: 4355)

CStatus :: CStatus (pWindow pW, ResourceFile *pResTarget , long lAllCnt, LPCSTR pcFName)
	     : m_pIStatus (NULL)
{
	_pResTarget = pResTarget;

// Variablen initialisieren
	HRESULT hr = 0;

	if (g_pTE->m_pXtnSite)
		hr = g_pTE->m_pXtnSite->CreateInstance (NULL, CLSID_ProgressIndicator, 
					   IID_IProgressIndicator, (LPVOID *)&m_pIStatus);

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
	ResString resCaption ( ResID(IDS_EXPORTCAP,_pResTarget),64);	 	// Status des aktuellen Exports

	ResString resStatus ( ResID(IDS_CSTATUS,_pResTarget), 64);		// Es wurden bereits %d%% der Objekte exportiert

	m_pIStatus -> ChangeText (PIFLAG_CAPTION, resCaption);

	m_pIStatus -> ChangeText (PIFLAG_ADJUSTPERCENT, resStatus);

	m_pIStatus -> ChangeText (PIFLAG_FILE, "");

	m_pIStatus -> ChangeText (PIFLAG_FILENAME, pcFName);	// Dateiname
	m_pIStatus -> ChangeText (PIFLAG_RESULT, "");
}

#pragma warning (default: 4355)

CStatus :: ~CStatus (void) 
{
	if (m_pIStatus) m_pIStatus -> Release();
}

void CStatus :: SetValue (long lCurrCnt, long lONr) 
{
	if (NULL == m_pIStatus) return;
	m_pIStatus -> SetPosition (lCurrCnt);

	if (lONr != -1) {
	ResString resObj (ResID(IDS_EXPORTOBJEKT, _pResTarget), 32);		// Objekt: %ld
	char cbBuffer[32];

		wsprintf (cbBuffer, resObj, lONr);
		m_pIStatus -> ChangeText (PIFLAG_RESULT, cbBuffer);
	}
}

bool CStatus :: Break (void)
{
	if (NULL != m_pIStatus)
		return m_pIStatus -> WasCanceled();

return false;
}
//------------KPSTATUS.CXX----------------------------------------
