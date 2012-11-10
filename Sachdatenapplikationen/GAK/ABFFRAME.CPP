// AbfFrame.cpp : implementation file
//

#include "stdafx.h"		// prec. Header
#include "gak.h"		// CGakApp
#include "childfrm.h"	// CChildFrame
#include "AbfFrame.h"	// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Konstanten
const int iAbfXpos = 20;
const int iAbfYpos = 30;

/////////////////////////////////////////////////////////////////////////////
// CAbfFrame
IMPLEMENT_DYNCREATE(CAbfFrame, CChildFrame)

BEGIN_MESSAGE_MAP(CAbfFrame, CChildFrame)
	//{{AFX_MSG_MAP(CAbfFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAbfFrame message handlers

void CAbfFrame::ActivateFrame(int nCmdShow) 
{
	// TODO: Add your specialized code here and/or call the base class
	CChildFrame::ActivateFrameExt(nCmdShow, iAbfXpos, iAbfYpos);
}

