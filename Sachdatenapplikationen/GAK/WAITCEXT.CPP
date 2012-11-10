/*
Datei: WAITCEXT.CPP

Das Modul realisiert neben dem Umschalten des Cursors in eine Sanduhr
die Ausgabe eines Textes in die Statusbar der Applikation.

Erarbeitet: J.Benkenstein				Stand vom: 4.6.1996

*/

#include "stdafx.h"		// prec. Header
#include "gak.h"		// CGakApp u. Ressourcen
#include "statbare.h"	// CStatusBarExt
#include "MainFrm.h"	// CMainFrame	
#include "waitcext.h"	// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CWaitCursorExt ----------------------------------------------------
CWaitCursorExt :: CWaitCursorExt (const char *pText, UINT uiOldText)
{
	try
	{
		ASSERT (NULL != pText);
		CString strText (pText);
		Init (strText, uiOldText);
	}
	catch (CMemoryException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}
}

CWaitCursorExt :: CWaitCursorExt (UINT uiResID, UINT uiOldText)
{
	try
	{
	//	neuen Text laden
		CString strText;
		VERIFY (strText.LoadString (uiResID));
		Init (strText, uiOldText);
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}
}

void CWaitCursorExt :: Init (const CString &strText, UINT uiOldText)
{
	try
	{
	//	alten Text lesen
		CMainFrame *pFrame = GetFrame ();
		if (0 != uiOldText)
			VERIFY (m_strOldText.LoadString (uiOldText));
		else
			pFrame -> GetStatusBarText (m_strOldText);

		pFrame -> SetStatusBarText (strText, TRUE);	// neuen Text setzen

	//	anhängende Nachrichten erst abarbeiten
		CallMessageQueue ();

		AfxGetApp () -> BeginWaitCursor();
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}
}


CWaitCursorExt :: ~CWaitCursorExt (void)
{
//	alten Text wieder ausgeben
//	anhängende Nachrichten erst abarbeiten
	// CallMessageQueue ();
	GetFrame () -> SetStatusBarText (m_strOldText, FALSE);	

	AfxGetApp () -> EndWaitCursor();
}

void CWaitCursorExt :: Restore (void)
{
	AfxGetApp () -> RestoreWaitCursor ();
}

CMainFrame *CWaitCursorExt :: GetFrame (void)
{
	CMainFrame * pFrame = (CMainFrame *) AfxGetApp () -> m_pMainWnd;
	ASSERT (NULL != pFrame);
	ASSERT_VALID (pFrame);
	ASSERT (pFrame -> IsWindowVisible ());
	return pFrame;
}

