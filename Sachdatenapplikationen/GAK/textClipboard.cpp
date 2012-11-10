//	String ins Clipboard ausgeben

#include "stdafx.h"
#include "textClipboard.h"
#include "resource.h"

HRESULT CTextClipboard::SetText(CString& str)
{
	HRESULT hr = E_FAIL;

	CWnd* pWnd = AfxGetMainWnd();
	if (NULL == pWnd)
		return E_FAIL;

	try 
	{
		if (!pWnd->OpenClipboard () || !EmptyClipboard ())
			AfxThrowUserException ();

		// globalen Speicherblock holen
		HGLOBAL hText = ::GlobalAlloc (GMEM_MOVEABLE | GMEM_DDESHARE,
										str.GetLength () + 1);
		if (!hText)
			AfxThrowMemoryException ();

		char *pText = (char *) :: GlobalLock (hText);
		if (!pText)
			AfxThrowMemoryException ();

		strcpy (pText, str);	

		if (GlobalUnlock (hText) == TRUE)
			AfxThrowMemoryException ();
		if (!SetClipboardData (CF_TEXT, hText))
			AfxThrowUserException ();

		hr = S_OK;
	}
	catch (CUserException *e)	// Clipboard-Fehler
	{
		CString strError;
		VERIFY (strError.LoadString (IDS_CLIPB_ERROR));
		pWnd->MessageBox (strError, AfxGetAppName (), MB_OK | MB_ICONSTOP);		
		e -> Delete ();
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}

	 CloseClipboard ();	// auf jeden Fall schlieﬂen
	 return hr;
}
