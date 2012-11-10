#include "stdafx.h"
#include "resource.h"
#include "ImportDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPpgRefPoints property page

IMPLEMENT_DYNCREATE(CPpgRefPoints, CPropertyPage)

CPpgRefPoints::CPpgRefPoints() 
	: CPropertyPage(CPpgRefPoints::IDD)
	, m_p0x(0)
	, m_p0y(0)
	, m_p1x(0)
	, m_p1y(0)
{
	//{{AFX_DATA_INIT(CPpgRefPoints)
	m_nSelected = -1;
	//}}AFX_DATA_INIT
}

CPpgRefPoints::~CPpgRefPoints() {
}

void CPpgRefPoints::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpgRefPoints)
	DDX_CBIndex(pDX, IDC_COMBOPOINTSCHEMA, m_nSelected);
	DDX_Control(pDX, IDC_P0X, m_P0X);
	DDX_Control(pDX, IDC_P0Y, m_P0Y);
	DDX_Control(pDX, IDC_P1X, m_P1X);
	DDX_Control(pDX, IDC_P1Y, m_P1Y);
	DDX_Control(pDX, IDC_TRIASCSUI1, m_csUI);
	//}}AFX_DATA_MAP
}

void CPpgRefPoints::UpdateControls() {
	MEInitMask( m_P0X );
	MEInitMask( m_P0Y );
	MEInitMask( m_P1X );
	MEInitMask( m_P1Y );
	MESetValue( m_P0X, m_p0x );
	MESetValue( m_P0Y, m_p0y );
	MESetValue( m_P1X, m_p1x );
	MESetValue( m_P1Y, m_p1y );

	DWORD dwButtons = PSWIZB_NEXT | PSWIZB_BACK;
	m_pParent->m_nNextStep = CPpgMapInfo::IDD;
	m_pParent->SetWizardButtons( dwButtons );
}

BEGIN_MESSAGE_MAP(CPpgRefPoints, CPropertyPage)
	//{{AFX_MSG_MAP(CPpgRefPoints)
	ON_BN_CLICKED(IDC_BUTTONDEFCS, OnButtondefcs)
	ON_CBN_SELCHANGE(IDC_COMBOPOINTSCHEMA, OnSelchangeCombopointschema)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpgRefPoints message handlers

DefineSmartInterface2( IOleObject, IID_IOleObject )

void CPpgRefPoints::OnButtondefcs()  {
	HRESULT	hr = E_FAIL;
	try {
		IUnknown	*pUnknown = m_csUI.GetControlUnknown();
		WIOleObject	obj(pUnknown);
		if( obj ) {
			hr = obj->DoVerb( OLEIVERB_PROPERTIES, NULL, NULL, NULL, GetSafeHwnd(), NULL );
		}
		hr = S_OK;
	} catch(_com_error e) {
		hr = _COM_ERROR(e);
	} catch(...) {
		hr = E_UNEXPECTED;
	}
}

void CPpgRefPoints::OnSelchangeCombopointschema()  {
	UpdateData();
}

BOOL CPpgRefPoints::OnInitDialog()  {
	CPropertyPage::OnInitDialog();
	HRESULT	hr = E_FAIL;
	m_nSelected = 0;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPpgRefPoints::OnKillActive() {
	UpdateData();

	double	p0x, p0y, p1x, p1y;
	MEGetValue( p0x, m_P0X );
	MEGetValue( p0y, m_P0Y );
	MEGetValue( p1x, m_P1X );
	MEGetValue( p1y, m_P1Y );
	
	GEOPOINT	LO, RO, RU, LU;

	if( 0 == m_nSelected ) {
		/////////////////////////////////////////////
		// links unten / rechts oben
		LO.X = p0x; LO.Y = p1y;
		RU.X = p1x; RU.Y = p0y;
	} else {
		/////////////////////////////////////////////
		// links oben / rechts unten
		LO.X = p0x; LO.Y = p0y;
		RU.X = p1x; RU.Y = p1y;
	}
	RO.X = RU.X; RO.Y = LO.Y;
	LU.X = LO.X; LU.Y = RU.Y;
	MC::ArrayDouble	coords(MC::Dim(4 * 3));
	coords[0] = LU.X; coords[1] = LU.Y; coords[2] = 0;
	coords[3] = RU.X; coords[4] = RU.Y; coords[5] = 0;
	coords[6] = RO.X; coords[7] = RO.Y; coords[8] = 0;
	coords[9] = LO.X; coords[10] = LO.Y; coords[11] = 0;
	m_pParent->m_pTopoMap->PutFixPoints( *coords );
	return CPropertyPage::OnKillActive();
}

BOOL CPpgRefPoints::OnSetActive() {
	UpdateData(FALSE);
	UpdateControls();
	return CPropertyPage::OnSetActive();
}

#include <locale.h>

LRESULT CPpgRefPoints::OnWizardNext()  {
	return CPropertyPage::OnWizardNext(m_pParent->m_nNextStep);
}

BEGIN_EVENTSINK_MAP(CPpgRefPoints, CPropertyPage)
    //{{AFX_EVENTSINK_MAP(CPpgRefPoints)
	ON_EVENT(CPpgRefPoints, IDC_P0X, 2 /* AdvanceFocusNext */, OnAdvanceFocusNextP0x, VTS_NONE)
	ON_EVENT(CPpgRefPoints, IDC_P0Y, 2 /* AdvanceFocusNext */, OnAdvanceFocusNextP0y, VTS_NONE)
	ON_EVENT(CPpgRefPoints, IDC_P1X, 2 /* AdvanceFocusNext */, OnAdvanceFocusNextP1x, VTS_NONE)
	ON_EVENT(CPpgRefPoints, IDC_P1Y, 2 /* AdvanceFocusNext */, OnAdvanceFocusNextP1y, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CPpgRefPoints::OnAdvanceFocusNextP0x()  {
	GetNextDlgTabItem( &m_P0X )->SetFocus();
}

void CPpgRefPoints::OnAdvanceFocusNextP0y()  {
	GetNextDlgTabItem( &m_P0Y )->SetFocus();
}

void CPpgRefPoints::OnAdvanceFocusNextP1x()  {
	GetNextDlgTabItem( &m_P1X )->SetFocus();
}

void CPpgRefPoints::OnAdvanceFocusNextP1y()  {
	GetNextDlgTabItem( &m_P1Y )->SetFocus();
}
