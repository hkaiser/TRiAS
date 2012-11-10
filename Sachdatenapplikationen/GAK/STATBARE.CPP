// StatBarE.cpp : implementation file
//

#include "stdafx.h"		// prec. Header
#include "gak.h"		// CGakApp und Ressourcen
#include "StatBarE.h"	// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatusBarExt
BEGIN_MESSAGE_MAP(CStatusBarExt, CStatusBar)
	//{{AFX_MSG_MAP(CStatusBarExt)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_MESSAGE (WM_SETTEXT, OnSetText)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CStatusBarExt message handlers
LRESULT CStatusBarExt :: OnSetText (WPARAM wParam, LPARAM lParam)
{
	if (!m_bIgnoreSetText)
		return CStatusBar :: OnSetText (wParam, lParam);
	return 0;		// Nachricht abgearbeitet
}

