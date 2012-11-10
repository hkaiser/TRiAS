// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"		// prec. Header
#include "gak.h"		// CGakApp
#include "recview.h"	// CDaoRecordViewExt	

#include "ChildFrm.h"	// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Konstanten
const int iChildExt = 5;		// Fenstererweiterung

/////////////////////////////////////////////////////////////////////////////
// CChildFrame
IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)
BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction
BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIChildWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers
void CChildFrame::ActivateFrameExt (int nCmdShow, int iXpos, int iYpos) 
{
//	TODO: Add your specialized code here and/or call the base class
//	lese Dokument
	if (!IsWindowVisible ())
	{
		CDocument* pDoc = GetActiveDocument ();
		ASSERT (NULL != pDoc);
		ASSERT_VALID (pDoc);

	//	jetzt View holen
		POSITION pos = pDoc -> GetFirstViewPosition();
		ASSERT (NULL != pos);
		CDaoRecordViewExt * pView = (CDaoRecordViewExt *) pDoc -> GetNextView (pos);
		ASSERT (NULL != pView);
		ASSERT_VALID (pView);
	
	//	jetzt Sheet lesen
		CPropertySheet *pSheet = pView -> GetSheet ();
		ASSERT (NULL != pSheet);
		ASSERT_VALID (pSheet);

	//	Resize the Window
		CRect rectClient, rectWindow;
		pSheet -> GetWindowRect (rectClient);
		rectWindow = rectClient;

	//	CChildFrameWnd::CalcWindowRect adds the extra width and height
	//	needed from the mini frame.
		CalcWindowRect(rectWindow);
		rectWindow.right += iChildExt;
		rectWindow.bottom += iChildExt;
		m_ptMaxPoint = CPoint (rectWindow.Width(), rectWindow.Height());

		SetWindowPos (NULL, iXpos, iYpos,
					  rectWindow.Width(), rectWindow.Height(),
					SWP_NOZORDER);
	}

	CMDIChildWnd::ActivateFrame(SW_SHOWNORMAL);
}


void CChildFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	ASSERT (NULL != lpMMI);

	lpMMI -> ptMaxSize = m_ptMaxPoint;
	lpMMI -> ptMinTrackSize = CPoint (m_ptMaxPoint.x/2, m_ptMaxPoint.y/2);
	lpMMI -> ptMaxTrackSize = m_ptMaxPoint;
	
	CMDIChildWnd::OnGetMinMaxInfo(lpMMI);
}
