// DlgMapProperties.cpp : implementation file
//

#include "stdafx.h"
#include "mapmgr.h"
#include "DlgMapProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListCtrlGCP

CListCtrlGCP::CListCtrlGCP()
{
	memset( &m_widthColumns[0], 0x00, sizeof(m_widthColumns) );
}

CListCtrlGCP::~CListCtrlGCP()
{
}

static char szHeaders[] = _T("Punkt;X Karte;Y Karte;X Bild;Y Bild");

void CListCtrlGCP::CommonConstruct()
{
	CDC *pDC = GetDC( );
	ASSERT_VALID( pDC );
	CSize	sz;
	int	i;
	CString	S;

	for( i = 0; i < 5; i++ )
	{
		::AfxExtractSubString( S, szHeaders, i, ';' );
		AddColumn( S, i );
		sz = pDC->GetTextExtent( S, S.GetLength() );
		m_widthColumns[i] = __max( m_widthColumns[i], sz.cx );
	}
}

void CListCtrlGCP::RecalcLayout()
{
	for( int i = 0; i < 5; i++ )
		SetColumnWidth( i, m_widthColumns[i] + 2 );
}

BOOL CListCtrlGCP::AddGCP(GCP& gcp, int nImageIndex)
{
	CDC *pDC = GetDC( );
	ASSERT_VALID( pDC );
	CSize	sz;
	int lastItem = GetItemCount();
	CString	S;
	S.Format( _T("GCP #%d"), lastItem );
	sz = pDC->GetTextExtent( S, S.GetLength() );
	m_widthColumns[0] = __max( m_widthColumns[0], sz.cx );
	AddItem(lastItem,0,S,nImageIndex);

	S = FormatCoord( -1 == gcp.m_ptGeoCoord.X ? 0 : gcp.m_ptGeoCoord.X, m_mapType );
	sz = pDC->GetTextExtent( S, S.GetLength() );
	m_widthColumns[1] = __max( m_widthColumns[1], sz.cx );
	AddItem(lastItem,1,S,nImageIndex);

	S = FormatCoord( -1 == gcp.m_ptGeoCoord.Y ? 0 : gcp.m_ptGeoCoord.Y, m_mapType );
	sz = pDC->GetTextExtent( S, S.GetLength() );
	m_widthColumns[2] = __max( m_widthColumns[2], sz.cx );
	AddItem(lastItem,2,S,nImageIndex);

	S = FormatCoord( -1 == gcp.m_ptPictPoint.X ? 0 : gcp.m_ptPictPoint.X );
	sz = pDC->GetTextExtent( S, S.GetLength() );
	m_widthColumns[3] = __max( m_widthColumns[3], sz.cx );
	AddItem(lastItem,3,S,nImageIndex);

	S = FormatCoord( -1 == gcp.m_ptPictPoint.Y ? 0 : gcp.m_ptPictPoint.Y );
	sz = pDC->GetTextExtent( S, S.GetLength() );
	m_widthColumns[4] = __max( m_widthColumns[4], sz.cx );
	AddItem(lastItem,4,S,nImageIndex);
	ReleaseDC( pDC );
	return TRUE;
}

GCP CListCtrlGCP::GetGCP( int idx )
{
	GCP	gcp;
	return gcp;
}

CString CListCtrlGCP::FormatCoord(double val, TOPOMAPTYPE mapType )
{
	CString S;
	ostrstream	s;
	COORDTYPE	ct = COORD_XY;
	const MAPTYPE *mt = GetTypeFromType( mapType );
	if( NULL != mt )
		ct = mt->m_coordType;

	switch( ct )
	{
	case COORD_DMS :
		s << DMS( val ); //  << ends;
		break;
	case COORD_XY : 
	case COORD_GK :
		s << (ULONG) val;	// S.Format( _T("%lu"), val ); // os << (ULONG) val << ends;
		break;
	default :
		s << _T("???");	// S = _T( "???" );
	}
	S.ReleaseBuffer( -1 );
	s << ends;
	return s.str();
}

BEGIN_MESSAGE_MAP(CListCtrlGCP, CListCtrl)
	//{{AFX_MSG_MAP(CListCtrlGCP)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlGCP message handlers

void AFXAPI DDX_Control(CDataExchange* pDX, int nIDC, CListCtrlGCP& rControl, CGCPArray& gcpArray)
{
	if (rControl.m_hWnd == NULL)    // not subclassed yet
	{
		ASSERT(!pDX->m_bSaveAndValidate);

		HWND hWndCtrl = pDX->PrepareCtrl(nIDC);

		if (!rControl.SubclassWindow(hWndCtrl))
		{
			ASSERT(FALSE);      // possibly trying to subclass twice?
			AfxThrowNotSupportedException();
		}
#ifndef _AFX_NO_OCC_SUPPORT
		else
		{
			// If the control has reparented itself (e.g., invisible control),
			// make sure that the CWnd gets properly wired to its control site.
			if (pDX->m_pDlgWnd->m_hWnd != ::GetParent(rControl.m_hWnd))
				rControl.AttachControlSite(pDX->m_pDlgWnd);
		}
#endif //!_AFX_NO_OCC_SUPPORT
		rControl.CommonConstruct();
		for( int i = 0; i < gcpArray.GetSize(); i++ )
			rControl.AddGCP( gcpArray.GetAt( i ) );
		rControl.RecalcLayout();
	}
	if( pDX->m_bSaveAndValidate )
	{
/*
		for( int i = 0; i < gcpArray.GetSize(); i++ )
			gcpArray[i] = rControl.GetGCP( i );
		for( ; i < rControl.GetItemCount(); i++ )
			gcpArray.SetAtGrow( i, rControl.GetGCP( i ) );
*/
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPgMappropCommon property page

IMPLEMENT_DYNCREATE(CPgMappropCommon, CPropertyPage)

CPgMappropCommon::CPgMappropCommon() : CPropertyPage(CPgMappropCommon::IDD)
{
	//{{AFX_DATA_INIT(CPgMappropCommon)
	m_strXBtm = __T("");
	m_strYBtm = __T("");
	m_strXTop = __T("");
	m_strYTop = __T("");
	m_strM1 = __T("");
	m_strM2 = __T("");
	m_strM3 = __T("");
	m_strM4 = __T("");
	//}}AFX_DATA_INIT
}

CPgMappropCommon::~CPgMappropCommon()
{
}

void CPgMappropCommon::DoDataExchange(CDataExchange* pDX)
{
	if( !pDX->m_bSaveAndValidate )
		PrepareValues();
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPgMappropCommon)
	DDX_Control(pDX, IDC_EDIT_Y_TOP, m_editYTop);
	DDX_Control(pDX, IDC_EDIT_Y_BTM, m_editYBtm);
	DDX_Control(pDX, IDC_EDIT_X_TOP, m_editXTop);
	DDX_Control(pDX, IDC_EDIT_X_BTM, m_editXBtm);
	DDX_OCText(pDX, IDC_EDIT_X_BTM, DISPID(4), m_strM1);
	DDX_OCText(pDX, IDC_EDIT_X_TOP, DISPID(4), m_strM2);
	DDX_OCText(pDX, IDC_EDIT_Y_BTM, DISPID(4), m_strM3);
	DDX_OCText(pDX, IDC_EDIT_Y_TOP, DISPID(4), m_strM4);
	DDX_OCText(pDX, IDC_EDIT_X_TOP, DISPID(-517), m_strXTop);
	DDX_OCText(pDX, IDC_EDIT_X_BTM, DISPID(-517), m_strXBtm);
	DDX_OCText(pDX, IDC_EDIT_Y_BTM, DISPID(-517), m_strYBtm);
	DDX_OCText(pDX, IDC_EDIT_Y_TOP, DISPID(-517), m_strYTop);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_LIST_GCP, m_listGCP, m_gcpArray);
	if( pDX->m_bSaveAndValidate )
		RetrieveValues();
}

void CPgMappropCommon::PrepareValues()
{
	static char buf[256];
	ostrstream	os( buf, sizeof(buf) );

	os.flags( ( os.flags() & ~ios::scientific ) | ios::fixed );
	os.precision( 5 );

	COORDTYPE	coordType = COORD_XY;

	const MAPTYPE	*pMapType = GetTypeFromType( m_mapType );
	if( NULL != pMapType )
		coordType = pMapType->m_coordType;

	switch( coordType )
	{
	case COORD_DMS :
		m_strM1 = m_strM2 = m_strM3 = m_strM4 = __T("59°59\'59,99\"");
		os.seekp(0); os << DMS( m_ptBtmLeft.X ) << ends; m_strXBtm = os.str();
		os.seekp(0); os << DMS( m_ptBtmLeft.Y ) << ends; m_strYBtm = os.str();
		os.seekp(0); os << DMS( m_ptTopRight.X ) << ends; m_strXTop = os.str();
		os.seekp(0); os << DMS( m_ptTopRight.Y ) << ends; m_strYTop = os.str();
		break;
	case COORD_GK :
		m_strM1 = m_strM2 = _T("9 - 999.999,999");
		m_strM3 = m_strM4 = _T("9.999.999,999");
		if( m_ptBtmLeft.X > 0 ) {
			os.seekp(0); os.width( 7 ); os.fill( '0' );
			os << m_ptBtmLeft.X << ends; m_strXBtm = os.str();
		}
		if( m_ptTopRight.X > 0 ) {
			os.seekp(0); os.width( 7 ); os.fill( '0' );
			os << m_ptTopRight.X << ends; m_strXTop = os.str();
		}
		if( m_ptBtmLeft.Y > 0 ) {
			os.seekp(0); os.width( 7 ); os.fill( '0' );
			os << m_ptBtmLeft.Y << ends; m_strYBtm = os.str();
		}
		if( m_ptTopRight.Y > 0 ) {
			os.seekp(0); os.width( 7 ); os.fill( '0' );
			os << m_ptTopRight.Y << ends; m_strYTop = os.str();
		}
		break;
	case COORD_XY :
		m_strM1 = m_strM2 = m_strM3 = m_strM4 = _T("99.999.999,999");
		m_strXBtm = m_strYBtm = m_strXTop = m_strYTop = _T("");
		os.width( 8 ); os.fill( '0' );
		if( m_ptBtmLeft.X > 0 )
			{ os.seekp(0); os << m_ptBtmLeft.X << ends; m_strXBtm = os.str(); }
		os.width( 8 ); os.fill( '0' );
		if( m_ptBtmLeft.Y > 0 )
			{ os.seekp(0); os << m_ptBtmLeft.Y << ends; m_strYBtm = os.str(); }
		os.width( 8 ); os.fill( '0' );
		if( m_ptTopRight.X > 0 )
			{ os.seekp(0); os << m_ptTopRight.X << ends; m_strXTop = os.str(); }
		os.width( 8 ); os.fill( '0' );
		if( m_ptTopRight.Y > 0 )
			{ os.seekp(0); os << m_ptTopRight.Y << ends; m_strYTop = os.str(); }
		break;
	default :
		break;
	}
	m_listGCP.m_mapType = m_mapType;
}

static double DMS2Dbl( LPCTSTR lpszText )
{
	double	val = 0;
	CString	S( lpszText );
	val += 3600 * atof( S.Mid( 0, 2 ) );
	val += 60 * atof( S.Mid( 2, 2 ) );
	val += atof( S.Mid( 4, 2 ) );
	val += atof( S.Mid( 6 ) ) / 100;
	return val;
}

static double XY2Dbl( LPCTSTR lpszText )
{
	double	val = 0;
	val = atof( lpszText ) / 1000;
	return val;
}

void CPgMappropCommon::RetrieveValues()
{
	COORDTYPE	CT = COORD_XY;

	const MAPTYPE	*pMT = GetTypeFromType( m_mapType );
	if( NULL != pMT )
		CT = pMT->m_coordType;

	if( COORD_DMS == CT ) {
		m_ptBtmLeft.X = DMS2Dbl( m_strXBtm );
		m_ptBtmLeft.Y = DMS2Dbl( m_strYBtm );
		m_ptTopRight.X = DMS2Dbl( m_strXTop );
		m_ptTopRight.Y = DMS2Dbl( m_strYTop );
	}
	else
	{
		m_ptBtmLeft.X = XY2Dbl( m_strXBtm );
		m_ptBtmLeft.Y = XY2Dbl( m_strYBtm );
		m_ptTopRight.X = XY2Dbl( m_strXTop );
		m_ptTopRight.Y = XY2Dbl( m_strYTop );
	}
}

BEGIN_MESSAGE_MAP(CPgMappropCommon, CPropertyPage)
	//{{AFX_MSG_MAP(CPgMappropCommon)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPgMappropCommon message handlers

BOOL CPgMappropCommon::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	m_editXBtm.SetPromptChar( _T("0") );
	m_editYBtm.SetPromptChar( _T("0") );
	m_editXTop.SetPromptChar( _T("0") );
	m_editYTop.SetPromptChar( _T("0") );

	const MAPTYPE	*pMT = GetTypeFromType( m_mapType );

	if( NULL == pMT || FALSE == pMT->m_bHaveParser )
	{
//		m_editXBtm.SetReadOnly( FALSE );
//		m_editYBtm.SetReadOnly( FALSE );
//		m_editXTop.SetReadOnly( FALSE );
//		m_editYTop.SetReadOnly( FALSE );
	}
	
	// TODO: Add extra initialization here
	UpdateData( FALSE );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// CDlgMapProperties

IMPLEMENT_DYNAMIC(CDlgMapProperties, CPropertySheet)

CDlgMapProperties::CDlgMapProperties(CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(IDD, pParentWnd, iSelectPage)
{
	AddPage( &m_pgComm );
	AddPage( &m_pgPictProp );
}

CDlgMapProperties::~CDlgMapProperties()
{
}

BEGIN_MESSAGE_MAP(CDlgMapProperties, CPropertySheet)
	//{{AFX_MSG_MAP(CDlgMapProperties)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgMapProperties::OnInitDialog() 
{
	// TODO: Add your specialized code here and/or call the base class
	return CPropertySheet::OnInitDialog();
}

/////////////////////////////////////////////////////////////////////////////
// CDlgMapProperties message handlers


BEGIN_EVENTSINK_MAP(CPgMappropCommon, CPropertyPage)
    //{{AFX_EVENTSINK_MAP(CPgMappropCommon)
	ON_EVENT(CPgMappropCommon, IDC_EDIT_X_BTM, 3 /* TextChanged */, OnTextChangedEditXBtm, VTS_NONE)
	ON_EVENT(CPgMappropCommon, IDC_EDIT_X_TOP, 3 /* TextChanged */, OnTextChangedEditXTop, VTS_NONE)
	ON_EVENT(CPgMappropCommon, IDC_EDIT_Y_BTM, 3 /* TextChanged */, OnTextChangedEditYBtm, VTS_NONE)
	ON_EVENT(CPgMappropCommon, IDC_EDIT_Y_TOP, 3 /* TextChanged */, OnTextChangedEditYTop, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CPgMappropCommon::OnTextChangedEditXBtm() 
{
//	CString	S = m_editXBtm.GetText( );
}

void CPgMappropCommon::OnTextChangedEditYBtm() 
{
//	CString	S = m_editYBtm.GetText( );
}

void CPgMappropCommon::OnTextChangedEditXTop() 
{
//	CString	S = m_editXTop.GetText( );
}

void CPgMappropCommon::OnTextChangedEditYTop() 
{
//	CString	S = m_editYTop.GetText( );
}
