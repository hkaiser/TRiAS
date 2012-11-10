#include "stdafx.h"
#include "resource.h"
#include "ImportDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPpgIntergraph property page

IMPLEMENT_DYNCREATE(CPpgIntergraph, CPropertyPage)

CPpgIntergraph::CPpgIntergraph()
	: CPropertyPage(CPpgIntergraph::IDD)
{
	//{{AFX_DATA_INIT(CPpgIntergraph)
	m_scale = _T("");
	//}}AFX_DATA_INIT
}

CPpgIntergraph::~CPpgIntergraph() {
}

void CPpgIntergraph::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpgIntergraph)
	DDX_Control(pDX, IDC_TRANSFORMMATRIX, m_matrix);
	DDX_Control(pDX, IDC_ORIGX, m_origX);
	DDX_Control(pDX, IDC_ORIGY, m_origY);
	DDX_Control(pDX, IDC_ORIGZ, m_origZ);
	DDX_CBString(pDX, IDC_COMBO_SCALE, m_scale);
	//}}AFX_DATA_MAP
}

static void SetItem( CListCtrlEx &rctl, int r, int c, const double &val ) {
	CString	S;
	S.Format( _T("%.3lf"), val );
	rctl.SetItemText( r, c, S );
}

void CPpgIntergraph::UpdateControls() {
	TRANSFORMINFO	&I = m_pParent->m_mapInfo.m_transform;
	I.m_scale = atof(m_scale);
	_ASSERT( 0 != I.m_scale );
	SetItem( m_matrix, 0, 0, T1_S(I) );
	SetItem( m_matrix, 0, 1, A11_S(I) );
	SetItem( m_matrix, 0, 2, A12_S(I) );
	SetItem( m_matrix, 0, 3, A13_S(I) );

	SetItem( m_matrix, 1, 0, T2_S(I) );
	SetItem( m_matrix, 1, 1, A21_S(I) );
	SetItem( m_matrix, 1, 2, A22_S(I) );
	SetItem( m_matrix, 1, 3, A23_S(I) );

	SetItem( m_matrix, 2, 0, T3_S(I) );
	SetItem( m_matrix, 2, 1, A31_S(I) );
	SetItem( m_matrix, 2, 2, A32_S(I) );
	SetItem( m_matrix, 2, 3, A33_S(I) );

	DWORD dwButtons = PSWIZB_NEXT | PSWIZB_BACK;
	m_pParent->m_nNextStep = CPpgMapInfo::IDD;
	m_pParent->SetWizardButtons( dwButtons );
}

BEGIN_MESSAGE_MAP(CPpgIntergraph, CPropertyPage)
	//{{AFX_MSG_MAP(CPpgIntergraph)
	ON_CBN_SELCHANGE(IDC_COMBO_SCALE, OnSelchangeComboScale)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpgIntergraph message handlers

BOOL CPpgIntergraph::OnInitDialog()  {
	CPropertyPage::OnInitDialog();
	CRect	rc;
	m_matrix.GetClientRect( rc );
	UINT	widthOfColumn = ( rc.Width() + 4 ) / 4;
	int	r, c;
	for( c = 0; c < 4; c++ ) {
		VERIFY( c == m_matrix.InsertColumn( c, _T(""), LVCFMT_LEFT, widthOfColumn ) );
		for( r = 0; r < 4; r++ ) {
			m_matrix.AddItem( r, c, _T("") );
		}
	}
	m_scale = _T("100");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPpgIntergraph::OnKillActive()  {
	UpdateData();
	TRANSFORMINFO	&I = m_pParent->m_mapInfo.m_transform;
	SIZE			&S = m_pParent->m_mapInfo.m_sizeOfPicture;
	MEGetValue( I.m_origin.X, m_origX );
	MEGetValue( I.m_origin.Y, m_origY );
	MEGetValue( I.m_origin.Z, m_origZ );
	GEOPOINT	LO, RO, RU, LU;
	LO.X = T1_S(I) - I.m_origin.X;
	LO.Y = T2_S(I) - I.m_origin.Y;
	RU.X = LO.X + A11_S(I) * S.cx;
	RU.Y = LO.Y - A22_S(I) * S.cy;
	RO.X = RU.X; RO.Y = LO.Y;
	LU.X = LO.X; LU.Y = RU.Y;
	m_pParent->m_mapInfo.m_listOfGCP[0].m_ptGeoCoord = LU;
	m_pParent->m_mapInfo.m_listOfGCP[1].m_ptGeoCoord = RU;
	m_pParent->m_mapInfo.m_listOfGCP[2].m_ptGeoCoord = RO;
	m_pParent->m_mapInfo.m_listOfGCP[3].m_ptGeoCoord = LO;
	return CPropertyPage::OnKillActive();
}

BOOL CPpgIntergraph::OnSetActive()  {
	MEInitMask( m_origX );
	MEInitMask( m_origY );
	MEInitMask( m_origZ );
	TRANSFORMINFO	&I = m_pParent->m_mapInfo.m_transform;
	MESetValue( m_origX, I.m_origin.X );
	MESetValue( m_origY, I.m_origin.Y );
	MESetValue( m_origZ, I.m_origin.Z );
	UpdateData(FALSE);
	UpdateControls();
	return CPropertyPage::OnSetActive();
}

LRESULT CPpgIntergraph::OnWizardNext()  {
//	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
	return CPropertyPage::OnWizardNext(m_pParent->m_nNextStep);
}

BEGIN_EVENTSINK_MAP(CPpgIntergraph, CPropertyPage)
    //{{AFX_EVENTSINK_MAP(CPpgIntergraph)
	ON_EVENT(CPpgIntergraph, IDC_ORIGX, 2 /* AdvanceFocusNext */, OnAdvanceFocusNextOrigx, VTS_NONE)
	ON_EVENT(CPpgIntergraph, IDC_ORIGY, 2 /* AdvanceFocusNext */, OnAdvanceFocusNextOrigy, VTS_NONE)
	ON_EVENT(CPpgIntergraph, IDC_ORIGZ, 2 /* AdvanceFocusNext */, OnAdvanceFocusNextOrigz, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CPpgIntergraph::OnAdvanceFocusNextOrigx()  {
	GetNextDlgTabItem( &m_origX )->SetFocus();
}

void CPpgIntergraph::OnAdvanceFocusNextOrigy()  {
	GetNextDlgTabItem( &m_origY )->SetFocus();
}

void CPpgIntergraph::OnAdvanceFocusNextOrigz()  {
	GetNextDlgTabItem( &m_origZ )->SetFocus();
}

void CPpgIntergraph::OnSelchangeComboScale()  {
	UpdateData();
	UpdateControls();
}
