#include "stdafx.h"
#include "MapMgrApp.h"
#include "FrameStatus.h"

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
initial version
RCS}}*/
static char* pszRCS = "$Id: framestatus.cpp 1.1 1996/07/12 10:50:05 andy Exp andy $";
/* $Log: framestatus.cpp $
// Revision 1.1  1996/07/12  10:50:05  andy
// initial version
//
//
*/
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CFrameStatus layout

static UINT pIndicators[] = {
		ID_SEPARATOR,
		ID_SEPARATOR, 
		ID_STS_PICTSIZE,
		ID_STS_PICTCOORD,
		ID_STS_TIME
	};

static const PANE_SIZE	= 2;
static const PANE_POS	= 3;
static const PANE_TIME	= 4;

/////////////////////////////////////////////////////////////////////////////
// CFrameStatus

CFrameStatus::CFrameStatus()
{
}

CFrameStatus::~CFrameStatus()
{
}

void CFrameStatus::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	switch(lpDrawItemStruct->itemID)
	{
	case 1:
		CDC dc;
		dc.Attach(lpDrawItemStruct->hDC);
		CRect rect(&lpDrawItemStruct->rcItem);
		CBitmap* pBitmap = &m_bitmap;
		CDC srcDC;
		srcDC.CreateCompatibleDC(NULL);
		CBitmap* pOldBitmap = srcDC.SelectObject(pBitmap);
		dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(),
			&srcDC, 0, 0, SRCCOPY);
		srcDC.SelectObject(pOldBitmap);
		// Detach from the CDC object, otherwise the hDC will be
		// destroyed when the CDC object goes out of scope
		dc.Detach();
		return;
	}
	CStatusBar::DrawItem(lpDrawItemStruct);
}

BEGIN_MESSAGE_MAP(CFrameStatus, CStatusBar)
	//{{AFX_MSG_MAP(CFrameStatus)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CFrameStatus::SetPaneText( int nIndex, LPCTSTR lpszNewText, BOOL bUpdate)
{
	CSize size;

	HGDIOBJ hOldFont = NULL;
	HFONT hFont = (HFONT)SendMessage(WM_GETFONT);
	CClientDC dc(NULL);
	if (hFont != NULL) 
		hOldFont = dc.SelectObject(hFont);
	size = dc.GetTextExtent(lpszNewText);
	if (hOldFont != NULL) 
		dc.SelectObject(hOldFont);

	UINT nID, nStyle;
	int nWidth;

	GetPaneInfo(nIndex, nID, nStyle, nWidth);
	SetPaneInfo(nIndex, nID, nStyle, size.cx);
	return CStatusBar::SetPaneText( nIndex, lpszNewText, bUpdate );
}

void CFrameStatus::UpdateTime( const CTime& rTime )
{
	CString strTime = rTime.Format(_T(" %H:%M "));
	SetPaneText(PANE_TIME, strTime);
}

void CFrameStatus::UpdateSize( const LPSIZE lpSize )
{
	CString	S;
	S.Format( "%05lu X %05lu ", lpSize->cx, lpSize->cy );
	SetPaneText(PANE_SIZE, S );		// os.str());
}

void CFrameStatus::UpdatePos( const LPPOINT lpPoint )
{
	CString	S;
	S.Format( "%05lu , %05lu ", lpPoint->x, lpPoint->y );
	SetPaneText(PANE_POS, S );	// os.str());
}

/////////////////////////////////////////////////////////////////////////////
// CFrameStatus message handlers

int CFrameStatus::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatusBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	if( !SetIndicators( pIndicators, sizeof( pIndicators ) / sizeof( UINT ) ) )
		return -1;
	if( 0 == SetTimer(0x1000, 2 * 1000, NULL) )
		return -1;

	VERIFY( m_bitmap.LoadBitmap( IDB_COLORPAL ) );
	BITMAP	bmp;
	m_bitmap.GetObject( sizeof( BITMAP ), &bmp );
	UINT nID, nStyle;
	int nWidth;

	GetPaneInfo( 1, nID, nStyle, nWidth);
	SetPaneInfo( 1, nID, nStyle | SBT_OWNERDRAW, bmp.bmWidth - 4 );
	UpdateTime( CTime::GetCurrentTime() );
	return 0;
}

void CFrameStatus::OnTimer(UINT nIDEvent) 
{
	CTime time = CTime::GetCurrentTime();
	CRect	rcPane;
	GetItemRect( 1, rcPane );
	InvalidateRect( rcPane );
	if( 0 != time.GetSecond() )
		return;
	UpdateTime( time );
}

void CFrameStatus::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int	nPanes = sizeof( pIndicators ) / sizeof( UINT );
	CRect	rcPane;
	GetItemRect( 1, rcPane );
	if( rcPane.PtInRect( point ) )
	{
		CMenu bar;
		if (bar.LoadMenu(IDR_COLORCMDS))
		{
			CMenu& popup = *bar.GetSubMenu(0);
			ASSERT(popup.m_hMenu != NULL);

			ClientToScreen(&point);
			popup.TrackPopupMenu(TPM_RIGHTBUTTON,
				point.x, point.y,
				AfxGetMainWnd()); // route commands through main window
		}
		return;
	}
	CStatusBar::OnRButtonDown(nFlags, point);
}
