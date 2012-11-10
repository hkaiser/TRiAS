#include "stdafx.h"
#include "MapMgr.h"
#include "MapMgrApp.h"

#include "MapMgrDoc.h"
#include "mainfrm.h"

#include "ViewPict.h"
#include "ViewMapList.h"
#include "DlgNewDocument.h"

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
initial version
RCS}}*/
static char* pszRCS = "$Id: mainfrm.cpp 1.1 1996/07/12 10:48:54 andy Exp andy $";
/* $Log: mainfrm.cpp $
// Revision 1.1  1996/07/12  10:48:54  andy
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
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame() {
    m_wndPlacement.length = sizeof( WINDOWPLACEMENT );
    m_wndPlacement.flags = 0 ;
	m_wndPlacement.showCmd = SW_SHOWNORMAL;
	m_wndPlacement.ptMinPosition.x = 0;
	m_wndPlacement.ptMinPosition.y = 0;
	m_wndPlacement.ptMaxPosition.x = 0;
	m_wndPlacement.ptMaxPosition.y = 0;
	m_wndPlacement.rcNormalPosition.left = 0;
	m_wndPlacement.rcNormalPosition.top = 0;
	m_wndPlacement.rcNormalPosition.right = 320;
	m_wndPlacement.rcNormalPosition.bottom = 240;

	m_nRestore = -1;
}

CMainFrame::~CMainFrame() {
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame operations

void CMainFrame::LoadMapIdents( CMapMgrDoc* pDoc, LPCTSTR lpszSelectedItem ) {
	LPCTSTR	lpszItem;
	m_tbMaps.ResetState();
	if( NULL == lpszSelectedItem )
		return;
	pDoc->ResetItems();
	while( pDoc->NextItem( &lpszItem ) )
		m_tbMaps.AddMapName( lpszItem );
	m_tbMaps.SetCurSel( lpszSelectedItem );
}

BOOL CMainFrame::SavePosition() {
    CString szSection ;
    CString szKey ;

    VERIFY( szSection.LoadString( IDS_INI_SECTION ) );
    VERIFY( szKey.LoadString( IDS_INI_WNDPOS ) );
    WINDOWPLACEMENT wp;
    CString szValue ;
    wp.length = sizeof( WINDOWPLACEMENT );
    GetWindowPlacement( &wp );
    int nHeight = 0, n = 0;
//	m_splitHorz.GetRowInfo( 0, nHeight, n ) ;
    szValue.Format( _T("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d"),
        wp.showCmd,
		wp.ptMinPosition.x, wp.ptMinPosition.y,
        wp.ptMaxPosition.x, wp.ptMaxPosition.y,
        wp.rcNormalPosition.left, wp.rcNormalPosition.top,
        wp.rcNormalPosition.right, wp.rcNormalPosition.bottom,
        nHeight, 
        (m_wndStatusBar.GetStyle() & WS_VISIBLE) ? TRUE : FALSE
		);
    AfxGetApp()->WriteProfileString( szSection, szKey, szValue );
    return TRUE ;
}

BOOL CMainFrame::RestorePosition( int nCmdShow ) {
    CString	szValue ;
    CString	szSection ;
    CString	szKey ;
    BOOL	bStatusBar = TRUE ;
    int		nHeight;

    VERIFY( szSection.LoadString( IDS_INI_SECTION ) );
    VERIFY( szKey.LoadString( IDS_INI_WNDPOS ) );

    TRY {
		long	l;
		szValue = AfxGetApp()->GetProfileString(szSection, szKey, _T("") ) ;
		if( szValue.IsEmpty() )
		return FALSE;

		LAfxExtractSubLong( l = 0, szValue, 0, ',' );
		m_wndPlacement.showCmd = (int) l;
		LAfxExtractSubLong( l = 0, szValue, 1, ',' );
		m_wndPlacement.ptMinPosition.x = (int) l;
		LAfxExtractSubLong( l = 0, szValue, 2, ',' );
		m_wndPlacement.ptMinPosition.y = (int) l;
		LAfxExtractSubLong( l = 0, szValue, 3, ',' );
		m_wndPlacement.ptMaxPosition.x = 0;	// (int) l;
		LAfxExtractSubLong( l = 0, szValue, 4, ',' );
		m_wndPlacement.ptMaxPosition.y = 0;	// (int) l;
		LAfxExtractSubLong( l = 0, szValue, 5, ',' );
		m_wndPlacement.rcNormalPosition.left = (int) l;
		LAfxExtractSubLong( l = 0, szValue, 6, ',' );
		m_wndPlacement.rcNormalPosition.top = (int) l;
		LAfxExtractSubLong( l = 0, szValue, 7, ',' );
		m_wndPlacement.rcNormalPosition.right = (int) l;
		LAfxExtractSubLong( l = 0, szValue, 8, ',' );
		m_wndPlacement.rcNormalPosition.bottom = (int) l;

		LAfxExtractSubLong( l = 0, szValue, 9, ',' );
		nHeight = (int) l;
		LAfxExtractSubLong( l = 0, szValue, 11, ',' );
		bStatusBar = (BOOL) l;

		// Always strip off minimize.
		//
		if(m_wndPlacement.showCmd == SW_SHOWMINIMIZED)
			m_wndPlacement.showCmd = SW_SHOWNORMAL ;
//		if(nCmdShow != SW_SHOWNORMAL || nCmdShow != SW_NORMAL)
//			m_wndPlacement.showCmd = nCmdShow ;
//		m_splitHorz.SetRowInfo( 0, nHeight, 0 ) ;
	} CATCH(CException, pException) {
		bStatusBar = TRUE ;
		ShowControlBar( &m_wndStatusBar, bStatusBar, TRUE ) ;
		ShowWindow( SW_SHOWNORMAL );
		return FALSE ;
	} END_CATCH
	bStatusBar = TRUE ;
	m_nRestore = m_wndPlacement.showCmd;
	m_wndPlacement.showCmd = SW_SHOWMINIMIZED;
	SetWindowPlacement( &m_wndPlacement );
	ShowControlBar( &m_wndStatusBar, bStatusBar, TRUE );
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const			{ CFrameWnd::AssertValid(); }
void CMainFrame::Dump(CDumpContext& dc) const	{ CFrameWnd::Dump(dc); }
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_APPSTART, OnAppstart)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_CHANGE_MAP( )
	ON_UPDATE_COMMAND_UI(ID_STS_TIME, OnUpdateTime)
	ON_UPDATE_COMMAND_UI(ID_STS_PICTCOORD, OnUpdatePictCoord)
	ON_UPDATE_COMMAND_UI(ID_STS_PICTSIZE, OnUpdatePictSize)
END_MESSAGE_MAP()

void CMainFrame::OnChangeMap( LPCTSTR lpszNewName ) {
	CMapMgrDoc	*pDoc = (CMapMgrDoc*) GetActiveDocument();
	if( NULL == pDoc )
		return;
	ASSERT_VALID( pDoc );
	pDoc->ChangeMapIdent( lpszNewName );
}

void CMainFrame::OnUpdatePictCoord(CCmdUI* pCmdUI)
	{ pCmdUI->Enable(TRUE); }

void CMainFrame::OnUpdatePictSize(CCmdUI* pCmdUI)
	{ pCmdUI->Enable(TRUE); }

void CMainFrame::OnUpdateTime(CCmdUI* pCmdUI)
	{ pCmdUI->Enable(TRUE); }

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (!m_wndStatusBar.Create(this) )
		return -1;

	SendMessageToDescendants( WM_INIT_STATUSBAR, (WPARAM) 0, (LPARAM) &m_wndStatusBar );

	// TODO: If you have a call to EnableDocking() and DockControlBar()
	// before this line, move them to right after this comment.  This
	// insures that the docking area remains above the status bar.

	EnableDocking( CBRS_ALIGN_TOP );

	VERIFY( m_tbMaps.Create(this) );
	VERIFY( m_tbModes.Create( this ) );
	VERIFY( m_tbObjects.Create(this) );

	m_tbMaps.EnableDocking( CBRS_ALIGN_TOP );
	m_tbModes.EnableDocking( CBRS_ALIGN_TOP );

	CRect	rcCtl, rcOff;
	GetWindowRect( rcCtl );
//	ScreenToClient( &rcCtl );
	DockControlBar(&m_tbModes, AFX_IDW_DOCKBAR_TOP,rcCtl);
	m_tbModes.GetWindowRect(rcOff);
//	rcCtl.right = rcCtl.left + rcOff.Width();
//	rcCtl.bottom = rcOff.top + rcOff.Height();
	rcCtl.OffsetRect(rcOff.Width() + 1, 0);
	DockControlBar(&m_tbMaps, AFX_IDW_DOCKBAR_TOP,rcCtl);
	return 0;
}

void CMainFrame::OnDestroy() {
	CFrameWnd::OnDestroy();
    SavePosition() ;
}

void CMainFrame::OnAppstart() {
	CDlgNewDocument	dlg( this );
	if( ID_WIZFINISH == dlg.DoModal() ) {
		switch( dlg.m_nStartAction ) {
		case 0 :			// open other
			AfxGetApp()->OnCmdMsg( ID_FILE_OPEN, 0, NULL, NULL );
			break;
		case 1 :			// open last
			AfxGetApp()->OnCmdMsg( ID_FILE_MRU_FILE1, 0, NULL, NULL );
			break;
		case 2 : {			// new created
				CMapMgrDoc	*pDoc = (CMapMgrDoc*) GetActiveDocument();
				ASSERT_KINDOF( CMapMgrDoc, pDoc );
				pDoc->LoadFromDialog( (CDialog*) &dlg );
			}
			break;
		}
	}
	CMapMgrDoc	*pDoc = (CMapMgrDoc*) GetActiveDocument();
	ASSERT_KINDOF( CMapMgrDoc, pDoc );
	pDoc->ResetStartState();
	m_wndPlacement.showCmd = m_nRestore;
	m_nRestore = -1;
	SetWindowPlacement( &m_wndPlacement );
}
