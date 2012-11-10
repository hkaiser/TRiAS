/* 
	File: PROGRESS.CPP (Version für MFC 4.2)
	Statusanzeige der verarbeiteten Objekte.

	Erarbeitet: J. Benkenstein						Stand vom 23.10.1996
	Ergänzt:	W. Mörtl								  ab  09.04.1999
*/

#include "pheader.h"			// vorübersetzte Header
#include "resource.h"			// Resource Konstanten

//	TRIAS-Header
#include <xtsnaux.hxx>			// ExtOleRegisterClass () u.a.

//	STL-Header
#include <ospace/com/smartif.h>			
#include <triashelper.h>
#include <initguid.h>

#include <hpp/progrsst.hpp>			//	zugeh. Header	

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// CProgressIndicator
CProgressIndicator::CProgressIndicator (HWND hWndParent, IProgressIndicator2 *pPI) 
{
	if (pPI) 
		m_wIndicator = pPI;
	else {		
	//	prüfe Parameter
		_ASSERTE (NULL != g_pTE);
		_ASSERTE (NULL != g_pTE -> m_pXtnSite);

	HRESULT hr = g_pTE -> m_pXtnSite -> CreateInstance (NULL, CLSID_ProgressIndicator, 
														IID_IProgressIndicator2, m_wIndicator.ppv ());
		if (FAILED(hr)) 
			_com_issue_error (hr);
	
		HWND hWndRet = NULL;
		hr = m_wIndicator -> InitNew ((LONG)(hWndParent ? hWndParent : g_pTE -> MWind () -> m_hWnd),
									  0, (LONG *)&hWndRet);
		if (FAILED(hr))
			_com_issue_error (E_UNEXPECTED);
	}
}	

CProgressIndicator::CProgressIndicator (IProgressIndicator2 *pPI) 
{
	if (pPI) 
		m_wIndicator = pPI;
}	

void CProgressIndicator::InitStatusDialog (ULONG MaxSize, const char *strCaption, const char *pAdjustText)
{	
//	prüfe interne Parameter
	if (!m_wIndicator.IsValid())
		return;

//	prüfe übergebene Parameter
	_ASSERTE (NULL != strCaption && AfxIsValidString (strCaption));
	HRESULT hr = m_wIndicator -> Restart (0, MaxSize, //PIFLAGS_FILE|PIFLAGS_FILENAME| PIFLAGS_RESULT |
										  (PIFLAGS)(PIFLAGS_STATUS| PIFLAGS_TIME |
#if _MSC_VER < 1200
										  PIFLAGS_RESULT |		// #WM990409
#endif
										  PIFLAGS_ADJUSTPERCENT|PIFLAGS_INIT_SHOWWINDOW));
					  //				  PIFLAG_ALL|PIFLAG_INIT_SHOWWINDOW);
	if (FAILED(hr)) 
		_com_issue_error (hr);

	COleVariant varText (strCaption);
	hr = m_wIndicator -> ChangeText (PIFLAGS_CAPTION, (BSTR) varText.pbVal);
	if (FAILED(hr)) 
		_com_issue_error (hr);

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
		_com_issue_error (hr);
}

int CProgressIndicator::SetupStatus (ULONG pos)
{	
	if (!m_wIndicator.IsValid())
		return 0;

	int iPercent = 0;
	HRESULT hr = m_wIndicator -> SetPosition (pos, &iPercent);
	if (FAILED(hr))
		_com_issue_error (hr);

	return iPercent;
}

BOOL CProgressIndicator::WasCanceled ()
{
	if (!m_wIndicator.IsValid())
		return FALSE;

	HRESULT hr = m_wIndicator -> IsCanceled ();
	if (FAILED(hr))
		_com_issue_error (hr);

	return hr == S_OK ? TRUE : FALSE;
}

int CProgressIndicator::IncrementPosition ()
{
	if (!m_wIndicator.IsValid())
		return 0;

	int iPercent = 0;
	HRESULT hr = m_wIndicator -> IncrementPosition(&iPercent);
	if (FAILED(hr))
		_com_issue_error (hr);

	return iPercent;
}

// Objektnummer des gerade bearbeiteten Objektes an der Position PIFLAGS_RESULT anzeigen
// (#WM990413)
HRESULT CProgressIndicator::SetObjNr (long lONr)
{
	if (!m_wIndicator.IsValid())
		return S_OK;

CString strObjNr;

	strObjNr.Format (IDS_BEARB_OBJEKT, lONr);

COleVariant varObjNr (strObjNr);

HRESULT hr = m_wIndicator -> ChangeText (PIFLAGS_RESULT, (BSTR) varObjNr.pbVal);

	if (FAILED(hr))
		_com_issue_error (hr);
	return hr;
} // SetObjNr
