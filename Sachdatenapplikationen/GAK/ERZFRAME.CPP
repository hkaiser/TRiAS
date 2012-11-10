// ErzFrame.cpp : implementation file
//

#include "stdafx.h"			// prec. Header
#include "gak.h"			// CGakApp
#include "childfrm.h"		// CChildFrame
#include "ErzFrame.h"		// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Konstanten
const int iErzXpos = 0;
const int iErzYpos = 0;

/////////////////////////////////////////////////////////////////////////////
// CErzFrame

IMPLEMENT_DYNCREATE(CErzFrame, CChildFrame)
BEGIN_MESSAGE_MAP(CErzFrame, CChildFrame)
	//{{AFX_MSG_MAP(CErzFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CErzFrame message handlers
void CErzFrame::ActivateFrame(int nCmdShow) 
{
	// TODO: Add your specialized code here and/or call the base class
	CChildFrame :: ActivateFrameExt (nCmdShow, iErzXpos, iErzYpos);	
}
