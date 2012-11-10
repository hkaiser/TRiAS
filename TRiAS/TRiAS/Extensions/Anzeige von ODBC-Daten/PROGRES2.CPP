/* 
	File: PROGRESS.CPP (Version für MFC 4.2)
	Statusanzeige der verarbeiteten Objekte.

	Erarbeitet: J. Benkenstein						Stand vom 23.10.1996
*/

#include "pheader.h"			// vorübersetzte Header
#include "odbcext.hr"			// Resource Konstanten

//	TRIAS-Header
#include <xtsnaux.hxx>			// ExtOleRegisterClass () u.a.

//	STL-Header
#include <ospace/com/smartif.h>			

#include <triashelper.h>
//#include <initguid.h>

#include <progrsst.hpp>			//	zugeh. Header	

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CProgressIndicator -----------------------------------------------
CProgressIndicator :: CProgressIndicator (HWND hWndParent /*=NULL*/, IProgressIndicator2 *pPI /*=NULL*/)
{
	if (pPI)
		m_wIndicator = pPI;
	else
	{		
	//	prüfe Parameter
		ASSERT (NULL != g_pTE);
		ASSERT (NULL != g_pTE -> m_pXtnSite);

		HRESULT hr = g_pTE -> m_pXtnSite -> CreateInstance (NULL, CLSID_ProgressIndicator, 
															IID_IProgressIndicator2, m_wIndicator.ppv ());
		if (FAILED(hr)) 
			throw hr;
	
		HWND hWndRet = NULL;
		hr = m_wIndicator -> InitNew (hWndParent ? hWndParent : g_pTE -> MWind () -> m_hWnd, 0, &hWndRet);
		if (FAILED(hr))
			throw E_UNEXPECTED;
	}
}	

void CProgressIndicator :: InitStatusDialog (ULONG MaxSize, const char *strCaption, const char *pAdjustText)
{	
//	prüfe interne Parameter
	ASSERT (NULL != (IProgressIndicator2 *) m_wIndicator);

//	prüfe übergebene Parameter
	ASSERT (NULL != strCaption && AfxIsValidString (strCaption));
	HRESULT hr = m_wIndicator -> Restart (0, MaxSize, //PIFLAGS_FILE|PIFLAGS_FILENAME| PIFLAGS_RESULT |
										  (PIFLAGS)(PIFLAGS_STATUS| PIFLAGS_TIME | 
										  PIFLAGS_ADJUSTPERCENT|PIFLAGS_INIT_SHOWWINDOW));
					  //				  PIFLAG_ALL|PIFLAG_INIT_SHOWWINDOW);
	if (FAILED(hr)) 
		throw hr;

	COleVariant varText (strCaption);
	hr = m_wIndicator -> ChangeText (PIFLAGS_CAPTION, (BSTR) varText.pbVal);
	if (FAILED(hr)) 
		throw hr;

	if (pAdjustText && *pAdjustText)
	{
		COleVariant varText (pAdjustText);
		hr = m_wIndicator -> ChangeText (PIFLAGS_ADJUSTPERCENT, (BSTR) varText.pbVal);
	}
	else
	{
		CString strAdjust;
		VERIFY (strAdjust.LoadString (IDS_STATUS_STAND));
		COleVariant varText (strAdjust);
		hr = m_wIndicator -> ChangeText (PIFLAGS_ADJUSTPERCENT, (BSTR) varText.pbVal);
	}

	if (FAILED(hr)) 
		throw hr;
}

int CProgressIndicator :: SetupStatus (ULONG pos)
{	
	ASSERT (NULL != (IProgressIndicator2 *)m_wIndicator);

	int iPercent = 0;
	HRESULT hr = m_wIndicator -> SetPosition (pos, &iPercent);
	if (FAILED(hr))
		throw hr;

	return iPercent;
}

BOOL CProgressIndicator :: WasCanceled ()
{
	ASSERT (NULL != (IProgressIndicator2 *)m_wIndicator);
	HRESULT hr = m_wIndicator -> IsCanceled ();
	if (FAILED(hr))
		throw hr;

	return hr == S_OK ? TRUE : FALSE;
}


