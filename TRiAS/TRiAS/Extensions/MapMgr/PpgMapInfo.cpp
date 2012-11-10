#include "stdafx.h"
#include "resource.h"
#include "ImportDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "McKinney/OleType.h"

/////////////////////////////////////////////////////////////////////////////
// CPpgMapInfo property page

IMPLEMENT_DYNCREATE(CPpgMapInfo, CPropertyPage)

CPpgMapInfo::CPpgMapInfo() : CPropertyPage(CPpgMapInfo::IDD) {
	//{{AFX_DATA_INIT(CPpgMapInfo)
	//}}AFX_DATA_INIT
}

CPpgMapInfo::~CPpgMapInfo() {
}

void CPpgMapInfo::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpgMapInfo)
	DDX_Control(pDX, IDC_LISTGCPS, m_listOfGCPs);
	//}}AFX_DATA_MAP
}

void CPpgMapInfo::UpdateControls() {
	FillListControl();
	CComBSTR	strName;
	CComBSTR	strIdent;
	CPath	p( m_pParent->m_strSrcMap );
	HRESULT	hr = m_pParent->m_pTopoMap->GetNameAndIdent( CComBSTR( p.Prefix() ), &strName, &strIdent );
	_ASSERTE( S_OK == hr );
	if( S_OK != hr )
		return;
	m_pParent->m_strName = strName;
	m_pParent->m_strIdent = strIdent;
	
	m_pParent->m_nNextStep = CPpgImportFile::IDD;

	DWORD dwButtons = PSWIZB_BACK | PSWIZB_NEXT;
	m_pParent->SetWizardButtons( dwButtons );
}

/////////////////////////////////////////////////////////////////////////////
// unser List-Control füllen; zugleich die GCP-Liste des Dialogs füllen

static LPCTSTR strS[] = { _T("LU"), _T("RU"), _T("RO"), _T("LO"), NULL };

void CPpgMapInfo::FillListControl() {
	SAFEARRAY	*pCoords = NULL;
	HRESULT	hr = m_pParent->m_pTopoMap->GetCoordinates( &pCoords );
	_ASSERTE( S_OK == hr );
	if( S_OK != hr )
		return;
	MC::ArrayDouble	geoPoints(pCoords);
	hr = m_pParent->m_pTopoMap->GetRefPoints( &pCoords );
	_ASSERTE( S_OK == hr );
	if( S_OK != hr )
		return;
	MC::ArrayDouble	picPoints(pCoords);
	_ASSERTE( geoPoints.Elements() == picPoints.Elements() );
	_ASSERTE( 0 == geoPoints.Elements() % 3 );
	_ASSERTE( geoPoints.Elements() >= 4 );
	long	coord, nCoords = geoPoints.Elements() / 3, geoIdx, picIdx;
	m_listOfGCPs.DeleteAllItems();
	m_pParent->m_gcpList.clear();
	GCP	gcp;
	LPCTSTR	*pStr = strS;
	int ptIndex = 1;
	for( coord = 0, geoIdx = 0, picIdx = 0; coord < nCoords; coord++ ) {
		CString	S;
		if( *pStr )
			S = *pStr++;
		else
			S.Format( _T("P%ld"), ptIndex++ );
		m_listOfGCPs.AddItem(coord,0,S);
		gcp.m_ptGeoCoord.X = geoPoints[geoIdx];
			S.Format( _T("%.3lf"), geoPoints[geoIdx++] );
			m_listOfGCPs.AddItem(coord,1,S);
		gcp.m_ptGeoCoord.Y = geoPoints[geoIdx];
			S.Format( _T("%.3lf"), geoPoints[geoIdx++] );
			m_listOfGCPs.AddItem(coord,2,S);
		gcp.m_ptGeoCoord.Z = geoPoints[geoIdx];
			S.Format( _T("%.3lf"), geoPoints[geoIdx++] );
			m_listOfGCPs.AddItem(coord,3,S);
		gcp.m_ptPictPoint.X = picPoints[picIdx];
			S.Format( _T("%.3lf"), picPoints[picIdx++] );
			m_listOfGCPs.AddItem(coord,4,S);
		gcp.m_ptPictPoint.Y = picPoints[picIdx];
			S.Format( _T("%.3lf"), picPoints[picIdx++] );
			m_listOfGCPs.AddItem(coord,5,S);
		gcp.m_ptPictPoint.Z = picPoints[picIdx];
			S.Format( _T("%.3lf"), picPoints[picIdx++] );
			m_listOfGCPs.AddItem(coord,6,S);
		m_pParent->m_gcpList.push_back( gcp );
	}
}

BEGIN_MESSAGE_MAP(CPpgMapInfo, CPropertyPage)
	//{{AFX_MSG_MAP(CPpgMapInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpgMapInfo message handlers

BOOL CPpgMapInfo::OnInitDialog()  {
	CPropertyPage::OnInitDialog();
	CRect	rc;
	m_listOfGCPs.GetClientRect( rc );
	UINT	widthOfColumn = ( rc.Width() + 3 ) / 3;
	VERIFY( 0 == m_listOfGCPs.InsertColumn( 0, _T("Punkt"), LVCFMT_LEFT, widthOfColumn / 3 ) );
	VERIFY( 1 == m_listOfGCPs.InsertColumn( 1, _T("Geo X"), LVCFMT_LEFT, widthOfColumn ) );
	VERIFY( 2 == m_listOfGCPs.InsertColumn( 2, _T("Geo Y"), LVCFMT_LEFT, widthOfColumn ) );
	VERIFY( 3 == m_listOfGCPs.InsertColumn( 3, _T("Geo Z"), LVCFMT_LEFT, widthOfColumn / 3 ) );
	VERIFY( 4 == m_listOfGCPs.InsertColumn( 4, _T("Pic X"), LVCFMT_LEFT, widthOfColumn ) );
	VERIFY( 5 == m_listOfGCPs.InsertColumn( 5, _T("Pic Y"), LVCFMT_LEFT, widthOfColumn ) );
	VERIFY( 6 == m_listOfGCPs.InsertColumn( 6, _T("Pic Z"), LVCFMT_LEFT, widthOfColumn / 3 ) );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
