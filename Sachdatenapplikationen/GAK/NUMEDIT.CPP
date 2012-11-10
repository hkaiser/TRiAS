/*
DATEI: NUMEDIT.CPP

Realisiert die Ziffereingaben in einem Editfeld.

Erarbeitet: 	J. Benkenstein				Stand vom: 22.8.1997
*/
                  
#include "stdafx.h" 		//	prec. Header
#include "ctype.h"			//	isdigit ()	
#include "numedit.h"		//	zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif  

BEGIN_MESSAGE_MAP(CNumEdit, CEdit)
	//{{AFX_MSG_MAP(CNumEdit)
	ON_WM_CHAR ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CRealEdit, CNumEdit)
	//{{AFX_MSG_MAP(CRealEdit)
	ON_WM_CHAR ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CRealEditBegrenzt, CRealEdit)
	//{{AFX_MSG_MAP(CRealEditBegrenzt)
	ON_WM_CHAR ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CErzNrEdit, CNumEdit)
	//{{AFX_MSG_MAP(CErzNrEdit)
	ON_WM_CHAR ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//	CNumEdit--------------------------------------------------          
void CNumEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if ((0 == nChar) || iscntrl (nChar) || isdigit (nChar))            
		CWnd::OnChar(nChar, nRepCnt, nFlags);
	else
		:: MessageBeep (MB_ICONHAND);		
}

//	CRealEdit--------------------------------------------------          
void CRealEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
#pragma MSG("JG Nur ein Komma zulassen ()")	

	// den aktuellen Text aus dem Ctrl holen
	CString strEditText;
	GetWindowText(strEditText);
	
	// wenn ein Komma eingelesen wurde, und im String noch kein Komma existiert 
	if ((('.' == nChar) || (',' == nChar)) && (-1 == strEditText.Find('.')))
	{
		nChar = '.';
		DefWindowProc (WM_CHAR, (WPARAM) nChar, MAKELONG (nRepCnt, nFlags));
		// CWnd::OnChar(nChar, nRepCnt, nFlags);
	}
	else
		CNumEdit::OnChar(nChar, nRepCnt, nFlags); 
}       

//	CRealEditBegrenzt--------------------------------------------------          
void CRealEditBegrenzt::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CRealEdit::OnChar(nChar, nRepCnt, nFlags);

	// den neuen Text aus dem Ctrl holen
	CString strEditText;
	GetWindowText(strEditText);
	int nKommaPos = strEditText.Find('.');

	// wenn breits ein Komma eingelesen wurde und zwischen diesem und dem Ende des Wortes 3 Stellen liegen 
	if ((-1 != nKommaPos) && (strEditText.GetLength() - nKommaPos > 3))
	{
		// mir für den Fall der Fälle die aktuelle Cursorposition merken
		long dwGetSel = SendMessage(EM_GETSEL, 0, 0L);   
		WORD nStart = LOWORD(dwGetSel);
		WORD nEnd   = HIWORD(dwGetSel);

		strEditText = strEditText.Left(nKommaPos + 4);
		SetWindowText(strEditText);
		
		// Cursor nicht hinter das Ende setzen
		if (nStart > strEditText.GetLength())
			nStart = strEditText.GetLength();
		if (nEnd > strEditText.GetLength())
			nEnd = strEditText.GetLength();
//			nEnd = strEditText.GetLength();
		
		SendMessage(EM_SETSEL, 
					static_cast<LPARAM> (nStart), 
					static_cast<WPARAM> (nEnd));

//		Komma weggefangen
//		nChar = '.';
//		DefWindowProc (WM_CHAR, (WPARAM) nChar, MAKELONG (nRepCnt, nFlags));
		// CWnd::OnChar(nChar, nRepCnt, nFlags);
	}
}       

//	CErzNrEdit --------------------------------------------------          
void CErzNrEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (isalpha(toupper(nChar)))                      
		CWnd::OnChar(nChar, nRepCnt, nFlags);
	else
		CNumEdit::OnChar(nChar, nRepCnt, nFlags); 
}       

		

                  