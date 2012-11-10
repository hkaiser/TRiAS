// PgBWPictures.cpp : implementation file
//

#include "stdafx.h"
#include "PictView.h"
#include "BasePpg.h"
#include "PgBWPictures.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPgBWPictures property page

IMPLEMENT_DYNCREATE(CPgBWPictures, CBasePpg)

CPgBWPictures::CPgBWPictures() : CBasePpg(CPgBWPictures::IDD) {
	//{{AFX_DATA_INIT(CPgBWPictures)
	m_bTransparent = FALSE;
	m_nChannel = -1;
	m_rgbRed = 0;
	m_rgbGreen = 0;
	m_rgbBlue = 0;
	//}}AFX_DATA_INIT
}

CPgBWPictures::~CPgBWPictures()
{
}

void CPgBWPictures::DoDataExchange(CDataExchange* pDX)
{
	CBasePpg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPgBWPictures)
	DDX_Control(pDX, IDC_BUTTON_SELCOLOR, m_btnSelColor);
	DDX_Control(pDX, IDC_RADIO_BLACK, m_btnChannel);
	DDX_Check(pDX, IDC_CHECK_TRANSP, m_bTransparent);
	DDX_Radio(pDX, IDC_RADIO_BLACK, m_nChannel);
	DDX_Control(pDX, IDC_COLORSCTRL1, m_colorCtrl);
	DDX_OCShort(pDX, IDC_COLORSCTRL1, DISPID(1), m_rgbRed);
	DDX_OCShort(pDX, IDC_COLORSCTRL1, DISPID(2), m_rgbGreen);
	DDX_OCShort(pDX, IDC_COLORSCTRL1, DISPID(3), m_rgbBlue);
	//}}AFX_DATA_MAP
	UpdateControls();
}


BEGIN_MESSAGE_MAP(CPgBWPictures, CBasePpg)
	//{{AFX_MSG_MAP(CPgBWPictures)
	ON_BN_CLICKED(IDC_CHECK_TRANSP, OnCheckTransp)
	ON_BN_CLICKED(IDC_BUTTON_SELCOLOR, OnButtonSelcolor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPgBWPictures message handlers

void CPgBWPictures::OnCheckTransp() 
{
	// TODO: Add your control notification handler code here
	m_bTransparent = m_bTransparent ? FALSE : TRUE;
	UpdateData( FALSE );
}

BOOL CPgBWPictures::OnInitDialog() 
{
	CBasePpg::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPgBWPictures::OnButtonSelcolor() 
{
	// TODO: Add your control notification handler code here
	IUnknown	*pUnknown = m_colorCtrl.GetControlUnknown();
	IOleObject	*pObject;
	if( NULL != pUnknown && S_OK == pUnknown->QueryInterface( IID_IOleObject, (void**) &pObject ) ) {
		pObject->DoVerb( OLEIVERB_PROPERTIES, NULL, NULL, 0, GetSafeHwnd(), NULL );
		pObject->Release();
//		m_shape.SetBackColor( RGB( m_colorCtrl.GetRGBRed(), m_colorCtrl.GetRGBGreen(), m_colorCtrl.GetRGBBlue() ) );
	}
}

void CPgBWPictures::UpdateControls()
{
	GetDlgItem( IDC_RADIO_BLACK )->EnableWindow( m_bTransparent );
	GetDlgItem( IDC_RADIO_WHITE )->EnableWindow( m_bTransparent );
	m_colorCtrl.EnableWindow( m_bTransparent );
	m_btnSelColor.EnableWindow( m_bTransparent );
}
