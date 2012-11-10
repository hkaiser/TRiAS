#include "stdafx.h"
#include "lafxpriv.h"

#ifdef LAFX_WINC_SEG
#pragma code_seg(LAFX_WINC_SEG)
#endif

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
initial version
RCS}}*/
static char* pszRCS = "$Id: listupdn.cpp 1.2 1996/08/14 11:39:45 andy Exp $";
/* $Log: listupdn.cpp $
// Revision 1.2  1996/08/14  11:39:45  andy
// initial version
//
// Revision 1.1  1996/07/12  17:16:23  andy
// initial version
//
*/
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// CStaticLoc window

class CStaticLoc : public CStatic {
// Construction
public:
	CStaticLoc();
	CString	m_strText;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticLoc)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStaticLoc();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStaticLoc)
	afx_msg void OnPaint();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CStaticLoc

CStaticLoc::CStaticLoc() {
}

CStaticLoc::~CStaticLoc() {
}

BEGIN_MESSAGE_MAP(CStaticLoc, CStatic)
	//{{AFX_MSG_MAP(CStaticLoc)
	ON_WM_PAINT()
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticLoc message handlers

void CStaticLoc::OnPaint()  {
	CPaintDC dc(this); // device context for painting
	CRect	rc;

	GetClientRect( rc );
	rc.right -= 1;
	rc.bottom -= 1;

	CPen	*pOldPen;
	CPen	ps( PS_SOLID, 1, ::GetSysColor( COLOR_BTNSHADOW ) );
	pOldPen = dc.SelectObject( &ps );
	dc.MoveTo( rc.left, rc.top );
	dc.LineTo( rc.left, rc.bottom );
	dc.LineTo( rc.right, rc.bottom );
	dc.LineTo( rc.right, rc.top );
	dc.LineTo( rc.left, rc.top );
	dc.SelectObject( pOldPen );

	rc.OffsetRect( 1, 1 );

	CPen	ph( PS_SOLID, 1, ::GetSysColor( COLOR_BTNHILIGHT ) );
	pOldPen = dc.SelectObject( &ph );
	dc.MoveTo( rc.left, rc.top );
	dc.LineTo( rc.left, rc.bottom );
	dc.LineTo( rc.right, rc.bottom );
	dc.LineTo( rc.right, rc.top );
	dc.LineTo( rc.left, rc.top );
	dc.SelectObject( pOldPen );

	rc.OffsetRect( 1, 1 );
	rc.right -= 2;
	rc.bottom -= 2;
	CWnd	*pParent = GetParent();
	ASSERT_VALID( pParent );
	
	CFont	*pOldFont = dc.SelectObject( pParent->GetFont() );
	dc.SetBkColor( ::GetSysColor( COLOR_BTNFACE ) );
	dc.DrawText( m_strText, -1, &rc, DT_VCENTER | DT_LEFT );
	dc.SelectObject( pOldFont );

	// Do not call CStatic::OnPaint() for painting messages
}

/////////////////////////////////////////////////////////////////////////////
// CUpDownList

IMPLEMENT_DYNAMIC(CUpDownList,CListBox);

#define	m_btnUp		((CBmpBtn*) m_lstCtrls.GetAt(0))
#define	m_btnDown	((CBmpBtn*) m_lstCtrls.GetAt(1))
#define	m_btnAdd	((CBmpBtn*) m_lstCtrls.GetAt(2))
#define	m_btnDel	((CBmpBtn*) m_lstCtrls.GetAt(3))
#define	m_txtHead	((CStaticLoc*) m_lstCtrls.GetAt(4))

CUpDownList::CUpDownList() {
	m_bUseBitmapButtons = m_bUp = m_bDn = m_bAdd = m_bDel = TRUE;
	m_nBorderSize = 10;
	m_nButtonDistance = 10;
	m_lstCtrls.SetAtGrow( 0, new CBmpBtn );	// add
	m_lstCtrls.SetAtGrow( 1, new CBmpBtn );	// del
	m_lstCtrls.SetAtGrow( 2, new CBmpBtn );	// up
	m_lstCtrls.SetAtGrow( 3, new CBmpBtn );	// down
	m_lstCtrls.SetAtGrow( 4, new CStaticLoc );
}

CUpDownList::~CUpDownList() {
	int	nCtrls = m_lstCtrls.GetSize();
	for( int i = 0; i < nCtrls; ++i ) {
		delete m_lstCtrls.GetAt( i );
	}
	m_lstCtrls.RemoveAll();
}

BEGIN_MESSAGE_MAP(CUpDownList, CListBox)
	//{{AFX_MSG_MAP(CUpDownList)
	ON_BN_CLICKED(LAFX_BUTTON_UP, OnButtonUp)
	ON_BN_CLICKED(LAFX_BUTTON_DOWN, OnButtonDown)
	ON_BN_CLICKED(LAFX_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(LAFX_BUTTON_DEL, OnButtonDel)
	ON_BN_DOUBLECLICKED(LAFX_BUTTON_DOWN, OnDoubleclickedButtonDown)
	ON_BN_DOUBLECLICKED(LAFX_BUTTON_UP, OnDoubleclickedButtonUp)
	ON_BN_DOUBLECLICKED(LAFX_BUTTON_ADD, OnDoubleclickedButtonAdd)
	ON_BN_DOUBLECLICKED(LAFX_BUTTON_DEL, OnDoubleclickedButtonDel)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_IDLEUPDATECMDUI, OnIdleUpdateCmdUI)
	ON_UPDATE_COMMAND_UI( LAFX_BUTTON_UP, OnUpdateBtnUp )
	ON_UPDATE_COMMAND_UI( LAFX_BUTTON_DOWN, OnUpdateBtnDown )
	ON_UPDATE_COMMAND_UI( LAFX_BUTTON_ADD, OnUpdateBtnAdd )
	ON_UPDATE_COMMAND_UI( LAFX_BUTTON_DEL, OnUpdateBtnDel )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpDownList operations

void CUpDownList::UseBitmapButtons() {
	m_bUseBitmapButtons = TRUE;
}

void CUpDownList::UseTextButtons() {
	m_bUseBitmapButtons = FALSE;
}

void CUpDownList::EnableButtons( BOOL bEnable, BOOL bBtnUp, BOOL bBtnDn, BOOL bBtnAdd, BOOL bBtnDel ) {
	m_bUp = TRUE == bBtnUp ? bEnable : m_bUp;
	m_bDn = TRUE == bBtnDn ? bEnable : m_bDn;
	m_bAdd = TRUE == bBtnAdd ? bEnable : m_bAdd;
	m_bDel = TRUE == bBtnDel ? bEnable : m_bDel;
}

void CUpDownList::ShowButtons( BOOL bShow, BOOL bBtnUp, BOOL bBtnDn, BOOL bBtnAdd, BOOL bBtnDel ) {
	int show = TRUE == bShow ? SW_SHOWNORMAL : SW_HIDE;
	TRUE == bBtnUp ? m_btnUp->ShowWindow( show ) : FALSE ;
	TRUE == bBtnDn ? m_btnDown->ShowWindow( show ) : FALSE ;
	TRUE == bBtnAdd ? m_btnAdd->ShowWindow( show ) : FALSE ;
	TRUE == bBtnDel ? m_btnDel->ShowWindow( show ) : FALSE ;
}

void CUpDownList::UpdateButtons() {
	int	idx = GetCurSel();
	m_btnUp->EnableWindow( TRUE == m_bUp && ( idx > 0 ) );
	m_btnDown->EnableWindow( TRUE == m_bDn && ( LB_ERR != idx && idx < GetCount() - 1 ) );
	m_btnAdd->EnableWindow( TRUE == m_bAdd );
	m_btnDel->EnableWindow( TRUE == m_bDel && ( GetCount() > 0 ) );
}

#define BUTTON_STYLE	WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW

BOOL CUpDownList::CreateCommon( CWnd* pDialogWnd ) {
	CRect	rc( 0, 0, 0, 0 );

	VERIFY( m_btnUp->Create( "UP", BUTTON_STYLE, rc, pDialogWnd, LAFX_BUTTON_UP ) );
	VERIFY( m_btnDown->Create( "DN", BUTTON_STYLE, rc, pDialogWnd, LAFX_BUTTON_DOWN ) );
	VERIFY( m_btnAdd->Create( "ADD", BUTTON_STYLE, rc, pDialogWnd, LAFX_BUTTON_ADD ) );
	VERIFY( m_btnDel->Create( "DEL", BUTTON_STYLE, rc, pDialogWnd, LAFX_BUTTON_DEL ) );
	VERIFY( m_txtHead->Create( "", WS_CHILD | WS_VISIBLE | SS_USERITEM, rc, pDialogWnd, LAFX_BUTTON_DEL + 1 ) );
	
	if( m_bUseBitmapButtons ) {
		if( !m_btnUp->LoadBitmaps( "LAFX_BUTTON_UPU", "LAFX_BUTTON_UPD", "LAFX_BUTTON_UPF", "LAFX_BUTTON_UPX" ) )
			return FALSE;
		m_btnUp->SizeToContent();
		if( !m_btnDown->LoadBitmaps( "LAFX_BUTTON_DNU", "LAFX_BUTTON_DND", "LAFX_BUTTON_DNF", "LAFX_BUTTON_DNX" ) )
			return FALSE;
		m_btnDown->SizeToContent();
		if( !m_btnAdd->LoadBitmaps( "LAFX_BUTTON_ADDU", "LAFX_BUTTON_ADDD", "LAFX_BUTTON_ADDF", "LAFX_BUTTON_ADDX" ) )
			return FALSE;
		m_btnAdd->SizeToContent();
		if( !m_btnDel->LoadBitmaps( "LAFX_BUTTON_DELU", "LAFX_BUTTON_DELD", "LAFX_BUTTON_DELF", "LAFX_BUTTON_DELX" ) )
			return FALSE;
		m_btnDel->SizeToContent();
	} else {
		if( !m_btnUp->SubclassDlgItem( LAFX_BUTTON_UP, pDialogWnd ) )
			return FALSE;
		if( !m_btnDown->SubclassDlgItem( LAFX_BUTTON_DOWN, pDialogWnd ) )
			return FALSE;
		if( !m_btnAdd->SubclassDlgItem( LAFX_BUTTON_ADD, pDialogWnd ) )
			return FALSE;
		if( !m_btnDel->SubclassDlgItem( LAFX_BUTTON_DEL, pDialogWnd ) )
			return FALSE;
	}

	m_btnUp->SetOwner( this );
	m_btnDown->SetOwner( this );
	m_btnAdd->SetOwner( this );
	m_btnDel->SetOwner( this );

	GetWindowRect( rc );
	GetParent()->ScreenToClient( rc );

	RecalcLayout( rc );
	UpdateButtons();
	return TRUE;
}

void CUpDownList::SwitchItems( int nFromItem, int nToItem ) {
	CString	F, T;
	DWORD	dwF, dwT;
	GetText( nFromItem, F ); dwF = GetItemData( nFromItem );
	GetText( nToItem, T ); dwT = GetItemData( nToItem );
	DeleteString( nFromItem ); InsertString( nFromItem, T ); SetItemData( nFromItem, dwT );
	DeleteString( nToItem ); InsertString( nToItem, F ); SetItemData( nToItem, dwF );
}

void CUpDownList::ResetContent() {
	CListBox::ResetContent();
	UpdateButtons();
}

int CUpDownList::SetCurSel( int select ) {
	select = CListBox::SetCurSel( select );
	UpdateButtons();
	return select;
}

int CUpDownList::AddString( LPCSTR lpszItem ) {
	int	idx = CListBox::AddString( lpszItem );
	SetCurSel( idx );
	UpdateButtons();
	return idx;
}

void CUpDownList::MoveWindow( int x, int y, int nWidth, int nHeight, BOOL bRepaint ) {
	CRect rc( x, y, x + nWidth, y + nHeight );
	RecalcLayout( rc, bRepaint );
}

void CUpDownList::MoveWindow( LPCRECT lpRect, BOOL bRepaint ) {
	CRect rc = *lpRect;
	RecalcLayout( rc, bRepaint );
}

void CUpDownList::RecalcLayout( CRect& rcc, BOOL bRepaint ) {
	CRect	rc = rcc;
	CRect	rcHead = rcc;

	CRect	rcBtn;
	m_btnAdd->GetClientRect( rcBtn );
	CPoint	pt( rc.right - rcBtn.Width(), rc.top + 2 );
	rc.top += rcBtn.Height() + 4;
	CWnd::MoveWindow( &rc, bRepaint );		// die Listbox selbst
	rcBtn.SetRect( pt.x, pt.y, pt.x + rcBtn.Width(), pt.y + rcBtn.Height() );
	m_btnDown->MoveWindow( &rcBtn, bRepaint );
	rcBtn.OffsetRect( -rcBtn.Width(), 0 );
	m_btnUp->MoveWindow( &rcBtn, bRepaint );
	rcBtn.OffsetRect( -rcBtn.Width(), 0 );
	m_btnDel->MoveWindow( &rcBtn, bRepaint );
	rcBtn.OffsetRect( -rcBtn.Width(), 0 );
	m_btnAdd->MoveWindow( &rcBtn, bRepaint );
	rcHead.SetRect( rcHead.left, rcHead.top + 2, rcBtn.left - 2, rc.top - 2 );
	m_txtHead->MoveWindow( &rcHead, bRepaint );
	m_txtHead->SetFont( GetFont(), bRepaint );
	m_txtHead->SetWindowText( "Hallo" );
}

void CUpDownList::SetWindowText( LPCTSTR lpszText ) {
	m_txtHead->m_strText = lpszText;
}

/////////////////////////////////////////////////////////////////////////////
// CUpDownList message handlers

LRESULT CUpDownList::OnIdleUpdateCmdUI( WPARAM, LPARAM ) {
	UpdateButtons();
	return 0;
}

void CUpDownList::OnButtonUp() {
	int idx = GetCurSel();
	ASSERT( LB_ERR != idx );
	SwitchItems( idx, idx - 1 );
	SetCurSel( idx - 1 );
	UpdateButtons();
#ifdef WIN32
	GetParent()->SendMessage( WM_COMMAND, MAKELONG( (WORD) GetDlgCtrlID(), (WORD) LBN_MOVEUP), (LPARAM) GetSafeHwnd() );
#else
	GetParent()->SendMessage( WM_COMMAND, GetDlgCtrlID(), (LPARAM) MAKELONG( (WORD) GetSafeHwnd(), (WORD) LBN_MOVEUP ) );
#endif
}

void CUpDownList::OnButtonDown() {
	int idx = GetCurSel();
	ASSERT( LB_ERR != idx );
	SwitchItems( idx, idx + 1 );
	SetCurSel( idx + 1 );
	UpdateButtons();
#ifdef WIN32
	GetParent()->SendMessage( WM_COMMAND, MAKELONG( (WORD) GetDlgCtrlID(), (WORD) LBN_MOVEDOWN), (LPARAM) GetSafeHwnd() );
#else
	GetParent()->SendMessage( WM_COMMAND, GetDlgCtrlID(), (LPARAM) MAKELONG( (WORD) GetSafeHwnd(), (WORD) LBN_MOVEDOWN ) );
#endif
}

void CUpDownList::OnButtonAdd() {
#ifdef WIN32
	GetParent()->SendMessage( WM_COMMAND, MAKELONG( (WORD) GetDlgCtrlID(), (WORD) LBN_ADDITEM ), (LPARAM) GetSafeHwnd() );
#else
	GetParent()->SendMessage( WM_COMMAND, GetDlgCtrlID(), (LPARAM) MAKELONG( (WORD) GetSafeHwnd(), (WORD) LBN_ADDITEM ) );
#endif
	UpdateButtons();
}

void CUpDownList::OnButtonDel() {
	int	idx = GetCurSel();
	ASSERT( LB_ERR != idx );
	DeleteString( idx );
	SetCurSel( min( idx, GetCount() - 1 ) );
	UpdateButtons();
#ifdef WIN32
	GetParent()->SendMessage( WM_COMMAND, MAKELONG( (WORD) GetDlgCtrlID(), (WORD) LBN_DELITEM ), (LPARAM) GetSafeHwnd() );
#else
	GetParent()->SendMessage( WM_COMMAND, GetDlgCtrlID(), (LPARAM) MAKELONG( (WORD) GetSafeHwnd(), (WORD) LBN_DELITEM ) );
#endif
}

void CUpDownList::OnDoubleclickedButtonDown()
	{ OnButtonDown(); }

void CUpDownList::OnDoubleclickedButtonUp()
	{ OnButtonUp(); }

void CUpDownList::OnDoubleclickedButtonAdd()
	{ OnButtonAdd(); }

void CUpDownList::OnDoubleclickedButtonDel()
	{ OnButtonDel(); }

BOOL CUpDownList::OnChildNotify(UINT msg, WPARAM wp, LPARAM lp, LRESULT* pLRes)  {
	if (msg == WM_COMMAND) {
		int nCode;
#ifdef WIN32
		nCode = HIWORD(wp);
#else
		nCode = HIWORD(lp);
#endif
		if (nCode == LBN_SELCHANGE )
			UpdateButtons();
	}
	return CListBox::OnChildNotify(msg,wp,lp,pLRes);
}

void CUpDownList::OnUpdateBtnUp( CCmdUI *pCmdUI )
	{ pCmdUI->Enable( GetCurSel() > 0 ); }
	
void CUpDownList::OnUpdateBtnDown( CCmdUI *pCmdUI )
	{ pCmdUI->Enable( LB_ERR != GetCurSel() && GetCurSel() < GetCount() - 1 ); }
	
void CUpDownList::OnUpdateBtnDel( CCmdUI *pCmdUI )
	{ pCmdUI->Enable( GetCount() > 0 ); }

void CUpDownList::OnUpdateBtnAdd( CCmdUI *pCmdUI )
	{ pCmdUI->Enable( ); }

/////////////////////////////////////////////////////////////////////////////
// CBitmapButton - DDX

void AFX_EXT_API DDX_Control( CDataExchange* pDX, int nIDC, CBitmapButton& rControl ) {
	BOOL	bDoInit = NULL == rControl.m_hWnd;
	DDX_Control( pDX, nIDC, (CWnd&) rControl );
	if( bDoInit ) {
		if (!rControl.AutoLoad( nIDC, pDX->m_pDlgWnd ) ) {
			ASSERT(FALSE);      // possibly trying to subclass twic»
			AfxThrowNotSupportedException();
		}
		ASSERT( 0 != ( rControl.GetStyle() & BS_OWNERDRAW ) );	// don't forget this for BitmapButtons
		rControl.SizeToContent();
	}
/*
	if (rControl.m_hWnd == NULL) {    // not subclassed yet
		ASSERT(!pDX->m_bSaveAndValidate);
		HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
		if (!rControl.AutoLoad( nIDC, pDX->m_pDlgWnd ) )
		{
			ASSERT(FALSE);      // possibly trying to subclass twic»
			AfxThrowNotSupportedException();
		}
		ASSERT( 0 != ( rControl.GetStyle() & BS_OWNERDRAW ) );	// don't forget this for BitmapButtons
		rControl.SizeToContent();
	}
*/
}

/////////////////////////////////////////////////////////////////////////////
// CUpDownList - DDX

void AFX_EXT_API DDX_Control( CDataExchange* pDX, int nIDC, CUpDownList& rControl ) {
	BOOL	bDoInit = rControl.m_hWnd == NULL;
	DDX_Control( pDX, nIDC, (CWnd&) rControl );

	if( bDoInit ) {
		if( !rControl.CreateCommon( pDX->m_pDlgWnd ) ) {
			ASSERT(FALSE);
			AfxThrowNotSupportedException();
		}
	}
}

void CStaticLoc::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)  {
	// TODO: Add your message handler code here and/or call default
	CStatic::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
