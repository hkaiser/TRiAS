// listext.cpp : implementation of the CListBoxExt class
//
#include "stdafx.h"			//	prec. Header
#include "gak.h"			//	Resource-Konstanten	
#include <listext.hpp>		//	zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CListBoxExt, CListBox)
	//{{AFX_MSG_MAP(CListBoxExt)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CListBoxExt::OnRButtonDown(UINT nFlags, CPoint point)
{
// 	TODO: Add your message handler code here and/or call default
	CDC *pCDC = GetDC ();
	ASSERT (NULL != pCDC);
	TEXTMETRIC tm;
	VERIFY (pCDC -> GetTextMetrics (&tm));
	ReleaseDC (pCDC);

	int iSel = point.y / tm.tmAscent;

//	Scrollbereich berücksichtigen
	int iScroll = GetScrollPos (SB_VERT);	
	if (iScroll > 0)
		iSel += iScroll;
	
	if ((iSel < 0) || (iSel >= GetCount ()))
		return;
		
//	Parent benachrichtigen                                     
	GetParent () -> PostMessage (IDM_RB_DOWN, (WPARAM) GetDlgCtrlID (), (LPARAM) iSel);

// 	CWnd::OnRButtonDown(nFlags, point);
}   

