#include "bscriptp.hxx"
#include "bscript.h"

#include "toolbarx.h"
#include "splitter.h"
#include "split.h"

/////////////////////////////////////////////////////////////////////////////
// CBSSplitterWnd

IMPLEMENT_DYNAMIC(CBSSplitterWnd, CSplitterWnd)

BEGIN_MESSAGE_MAP(CBSSplitterWnd, CSplitterWnd)
	//{{AFX_MSG_MAP(CBSSplitterWnd)
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBSSplitterWnd construction/destruction

CBSSplitterWnd::CBSSplitterWnd()
	: CSplitterWnd()
{
}

CBSSplitterWnd::~CBSSplitterWnd()
{
}

///////////////////////////////////////////////////////////////////////////
// Messages

void CBSSplitterWnd::OnSetFocus(CWnd* pOldWnd) 
{
	CSplitterWnd::OnSetFocus(pOldWnd);
	
	CWnd *pWnd = GetPane(0,1);// DebuggerCtrl
	ASSERT(NULL != pWnd);
	pWnd -> SetFocus();
}

void CBSSplitterWnd::OnSize(UINT nType, int cx, int cy) 
{
	CSplitterWnd::OnSize(nType, cx, cy);
	if (NULL != m_pColInfo && NULL != m_pRowInfo)
		RecalcLayout();
}


