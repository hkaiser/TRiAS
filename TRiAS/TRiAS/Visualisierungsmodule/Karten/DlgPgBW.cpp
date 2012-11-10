// DlgPgBW.cpp : implementation file
//

#include "stdafx.h"
#include "KartenImpl.h"
#include "DlgPgBW.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPgBW property page

IMPLEMENT_DYNCREATE(CDlgPgBW, CPropertyPage)

CDlgPgBW::CDlgPgBW() : CPropertyPage(CDlgPgBW::IDD)
{
	//{{AFX_DATA_INIT(CDlgPgBW)
	m_bTransparent = FALSE;
	m_nChannel = 0;	// #fje19991101	-1 -> 0
	//}}AFX_DATA_INIT
}

CDlgPgBW::~CDlgPgBW()
{
}

void CDlgPgBW::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPgBW)
	DDX_Check(pDX, IDC_CHECK_TRANSPARENT, m_bTransparent);
	DDX_Radio(pDX, IDC_RADIO_BLACK, m_nChannel);
	//}}AFX_DATA_MAP
	UpdateControls();
}


BEGIN_MESSAGE_MAP(CDlgPgBW, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgPgBW)
	ON_BN_CLICKED(IDC_CHECK_TRANSPARENT, OnCheckTransparent)
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPgBW message handlers

BOOL CDlgPgBW::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPgBW::OnCheckTransparent() {
	m_bTransparent = m_bTransparent ? FALSE : TRUE;
	UpdateData( FALSE );
}

BEGIN_EVENTSINK_MAP(CDlgPgBW, CPropertyPage)
    //{{AFX_EVENTSINK_MAP(CDlgPgBW)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CDlgPgBW::UpdateControls() {
	GetDlgItem( IDC_RADIO_BLACK )->EnableWindow( m_bTransparent );
	GetDlgItem( IDC_RADIO_WHITE )->EnableWindow( m_bTransparent );
}

#if 0 // obsolete
CColorWnd::CColorWnd()
{
}

CColorWnd::~CColorWnd()
{
}

BEGIN_MESSAGE_MAP(CColorWnd, CStatic)
	//{{AFX_MSG_MAP(CColorWnd)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorWnd message handlers

void CColorWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect	rc, rcBord;
	GetClientRect( rc );
	rcBord = rc;
	dc.Draw3dRect( &rc, ::GetSysColor( COLOR_BTNSHADOW ), ::GetSysColor( COLOR_BTNHILIGHT ) );
	rc.InflateRect( -3, -3 );

	CBrush	br( m_color );
	dc.FillRect( rc, &br );
	// Do not call CStatic::OnPaint() for painting messages
}

void CColorWnd::Draw( int R, int G, int B )
{
	m_color = RGB( R, G, B );
	Invalidate();
}
#endif // obsolete

