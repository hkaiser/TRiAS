// RectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "RectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRectDlg dialog


CRectDlg::CRectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRectDlg)
	m_lFrameLeft = 0;
	m_lFrameTop = 0;
	m_lFrameRight = 0;
	m_lFrameBottom = 0;
	m_lClipLeft = 0;
	m_lClipTop = 0;
	m_lClipRight = 0;
	m_lClipBottom = 0;
	m_lPageLeft = 0;
	m_lPageTop = 0;
	m_lPageRight = 0;
	m_lPageBottom = 0;
	m_lRectLeft = 0;
	m_lRectTop = 0;
	m_lRectRight = 0;
	m_lRectBottom = 0;
	m_bUseMetaFile = FALSE;
	//}}AFX_DATA_INIT
	m_bEditClipBox = TRUE;
}


void CRectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRectDlg)
	DDX_Text(pDX, IDC_EDIT1, m_lFrameLeft);
	DDX_Text(pDX, IDC_EDIT2, m_lFrameTop);
	DDX_Text(pDX, IDC_EDIT3, m_lFrameRight);
	DDX_Text(pDX, IDC_EDIT4, m_lFrameBottom);
	DDX_Text(pDX, IDC_EDIT53, m_lClipLeft);
	DDX_Text(pDX, IDC_EDIT9, m_lClipTop);
	DDX_Text(pDX, IDC_EDIT10, m_lClipRight);
	DDX_Text(pDX, IDC_EDIT11, m_lClipBottom);
	DDX_Text(pDX, IDC_EDIT12, m_lPageLeft);
	DDX_Text(pDX, IDC_EDIT13, m_lPageTop);
	DDX_Text(pDX, IDC_EDIT14, m_lPageRight);
	DDX_Text(pDX, IDC_EDIT15, m_lPageBottom);
	DDX_Text(pDX, IDC_EDIT5, m_lRectLeft);
	DDX_Text(pDX, IDC_EDIT6, m_lRectTop);
	DDX_Text(pDX, IDC_EDIT7, m_lRectRight);
	DDX_Text(pDX, IDC_EDIT8, m_lRectBottom);
	DDX_Check(pDX, IDC_CHECK1, m_bUseMetaFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRectDlg, CDialog)
	//{{AFX_MSG_MAP(CRectDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnSetPage)
	ON_BN_CLICKED(IDC_BUTTON2, OnSetRect)
	ON_BN_CLICKED(IDC_BUTTON3, OnSetFrame)
	ON_BN_CLICKED(IDC_BUTTON4, OnSetClipBox)
	ON_BN_CLICKED(IDC_BUTTON6, OnChangeTB)
	ON_BN_CLICKED(IDC_BUTTON5, OnChangeLR)
	ON_EN_SETFOCUS(IDC_EDIT1, OnSetfocusEdit1)
	ON_EN_SETFOCUS(IDC_EDIT2, OnSetfocusEdit2)
	ON_EN_SETFOCUS(IDC_EDIT3, OnSetfocusEdit3)
	ON_EN_SETFOCUS(IDC_EDIT4, OnSetfocusEdit4)
	ON_EN_SETFOCUS(IDC_EDIT5, OnSetfocusEdit5)
	ON_EN_SETFOCUS(IDC_EDIT6, OnSetfocusEdit6)
	ON_EN_SETFOCUS(IDC_EDIT7, OnSetfocusEdit7)
	ON_EN_SETFOCUS(IDC_EDIT8, OnSetfocusEdit8)
	ON_EN_SETFOCUS(IDC_EDIT9, OnSetfocusEdit9)
	ON_EN_SETFOCUS(IDC_EDIT10, OnSetfocusEdit10)
	ON_EN_SETFOCUS(IDC_EDIT11, OnSetfocusEdit11)
	ON_EN_SETFOCUS(IDC_EDIT12, OnSetfocusEdit12)
	ON_EN_SETFOCUS(IDC_EDIT13, OnSetfocusEdit13)
	ON_EN_SETFOCUS(IDC_EDIT14, OnSetfocusEdit14)
	ON_EN_SETFOCUS(IDC_EDIT15, OnSetfocusEdit15)
	ON_EN_SETFOCUS(IDC_EDIT53, OnSetfocusEdit53)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRectDlg message handlers

BOOL CRectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRectDlg::OnSetPage() 
{
	UpdateData( TRUE );
	if ( m_bEditClipBox )
	{
		m_lClipLeft   = m_lPageLeft;
		m_lClipTop    = m_lPageTop;
		m_lClipRight  = m_lPageRight;
		m_lClipBottom = m_lPageBottom;
	}
	else
	{
		m_lFrameLeft   = m_lPageLeft;
		m_lFrameTop    = m_lPageTop;
		m_lFrameRight  = m_lPageRight;
		m_lFrameBottom = m_lPageBottom;
	}
	UpdateData( FALSE );
}

void CRectDlg::OnSetRect() 
{
	UpdateData( TRUE );
	if ( m_bEditClipBox )
	{
		m_lClipLeft   = m_lRectLeft;
		m_lClipTop    = m_lRectTop;
		m_lClipRight  = m_lRectRight;
		m_lClipBottom = m_lRectBottom;
	}
	else
	{
		m_lFrameLeft   = m_lRectLeft;
		m_lFrameTop    = m_lRectTop;
		m_lFrameRight  = m_lRectRight;
		m_lFrameBottom = m_lRectBottom;
	}
	UpdateData( FALSE );
}

void CRectDlg::OnSetFrame() 
{
	UpdateData( TRUE );
	if ( m_bEditClipBox )
	{
		m_lClipLeft   = m_lFrameLeft;
		m_lClipTop    = m_lFrameTop;
		m_lClipRight  = m_lFrameRight;
		m_lClipBottom = m_lFrameBottom;
	}
	UpdateData( FALSE );
}

void CRectDlg::OnSetClipBox() 
{
	UpdateData( TRUE );
	if ( !m_bEditClipBox )
	{
		m_lFrameLeft   = m_lClipLeft;
		m_lFrameTop    = m_lClipTop;
		m_lFrameRight  = m_lClipRight;
		m_lFrameBottom = m_lClipBottom;
	}
	UpdateData( FALSE );
}

void CRectDlg::OnChangeTB() 
{
	long	temp;

	UpdateData( TRUE );
	if ( m_bEditClipBox )
	{
		temp = m_lClipTop;
		m_lClipTop    = m_lClipBottom;
		m_lClipBottom = temp;
	}
	else
	{
		temp = m_lFrameTop;
		m_lFrameTop    = m_lFrameBottom;
		m_lFrameBottom = temp;
	}
	UpdateData( FALSE );
}

void CRectDlg::OnChangeLR() 
{
	long	temp;

	UpdateData( TRUE );
	if ( m_bEditClipBox )
	{
		temp = m_lClipLeft;
		m_lClipLeft  = m_lClipRight;
		m_lClipRight = temp;
	}
	else
	{
		temp = m_lFrameLeft;
		m_lFrameLeft  = m_lFrameRight;
		m_lFrameRight = temp;
	}
	UpdateData( FALSE );
}

void CRectDlg::OnSetfocusEdit1()	{	m_bEditClipBox = FALSE;	}
void CRectDlg::OnSetfocusEdit2()	{	m_bEditClipBox = FALSE;	}
void CRectDlg::OnSetfocusEdit3()	{	m_bEditClipBox = FALSE;	}
void CRectDlg::OnSetfocusEdit4()	{	m_bEditClipBox = FALSE;	}

void CRectDlg::OnSetfocusEdit5()	{}
void CRectDlg::OnSetfocusEdit6()	{}
void CRectDlg::OnSetfocusEdit7()	{}
void CRectDlg::OnSetfocusEdit8()	{}

void CRectDlg::OnSetfocusEdit53()	{	m_bEditClipBox = TRUE;	}
void CRectDlg::OnSetfocusEdit9()	{	m_bEditClipBox = TRUE;	}
void CRectDlg::OnSetfocusEdit10()	{	m_bEditClipBox = TRUE;	}
void CRectDlg::OnSetfocusEdit11()	{	m_bEditClipBox = TRUE;	}

void CRectDlg::OnSetfocusEdit12()	{}
void CRectDlg::OnSetfocusEdit13()	{}
void CRectDlg::OnSetfocusEdit14()	{}
void CRectDlg::OnSetfocusEdit15()	{}
