// DlgFileProp.cpp : implementation file
//

#include "stdafx.h"
#include "mapmgr.h"
#include "MapMgrDoc.h"
#include "DlgFileProp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPgFileGeometry property page

IMPLEMENT_DYNCREATE(CPgFileGeometry, CPropertyPage)

CPgFileGeometry::CPgFileGeometry() : CPropertyPage(CPgFileGeometry::IDD)
{
	//{{AFX_DATA_INIT(CPgFileGeometry)
	m_nOffsetX = 0.0;
	m_nOffsetY = 0.0;
	m_nScale11 = 0.0;
	m_nScale12 = 0.0;
	m_nScale21 = 0.0;
	m_nScale22 = 0.0;
	m_nMapType = -1;
	m_strCoordTrans = _T("");
	//}}AFX_DATA_INIT
}

CPgFileGeometry::~CPgFileGeometry()
{
}

void CPgFileGeometry::DoDataExchange(CDataExchange* pDX)
{
	if( !pDX->m_bSaveAndValidate )
		PrepareValues();
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPgFileGeometry)
	DDX_Control(pDX, IDC_MAPTYPE, m_listMapTypes);
	DDX_Text(pDX, IDC_OFFSET_X, m_nOffsetX);
	DDX_Text(pDX, IDC_OFFSET_Y, m_nOffsetY);
	DDX_Text(pDX, IDC_S11, m_nScale11);
	DDX_Text(pDX, IDC_S12, m_nScale12);
	DDX_Text(pDX, IDC_S21, m_nScale21);
	DDX_Text(pDX, IDC_S22, m_nScale22);
	DDX_CBIndex(pDX, IDC_MAPTYPE, m_nMapType);
	DDX_Text(pDX, IDC_TEXT_COORDTRANS, m_strCoordTrans);
	//}}AFX_DATA_MAP
	if( pDX->m_bSaveAndValidate )
		RetrieveValues();
}

void CPgFileGeometry::PrepareValues()
{
	m_nOffsetX = m_ascHeader.m_dwOffsetX;
	m_nOffsetY = m_ascHeader.m_dwOffsetY;
	m_nScale11 = m_ascHeader.m_dwScale11;
	m_nScale12 = m_ascHeader.m_dwScale12;
	m_nScale21 = m_ascHeader.m_dwScale21;
	m_nScale22 = m_ascHeader.m_dwScale22;
	m_strCoordTrans.Format( _T("Koordinatentransformator: %s"), m_ascHeader.m_strCoordTrans );
}

void CPgFileGeometry::RetrieveValues()
{
	m_ascHeader.m_dwOffsetX = m_nOffsetX;
	m_ascHeader.m_dwOffsetY = m_nOffsetY;
	m_ascHeader.m_dwScale11 = m_nScale11;
	m_ascHeader.m_dwScale12 = m_nScale12;
	m_ascHeader.m_dwScale21 = m_nScale21;
	m_ascHeader.m_dwScale22 = m_nScale22;
	m_ascHeader.m_strCoordTrans = mapTypes[m_nMapType].m_strCtf;
}

BEGIN_MESSAGE_MAP(CPgFileGeometry, CPropertyPage)
	//{{AFX_MSG_MAP(CPgFileGeometry)
	ON_CBN_SELCHANGE(IDC_MAPTYPE, OnSelchangeMaptype)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPgFileGeometry message handlers

BOOL CPgFileGeometry::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	for( MAPTYPE *mapType = mapTypes; MPT_INVALID != mapType->m_mtType; mapType++ )
		m_listMapTypes.AddString( mapType->m_strLongName );

	// TODO: Add extra initialization here

	UpdateData( FALSE );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPgFileGeometry::OnSelchangeMaptype() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	UpdateData( FALSE );
}

/////////////////////////////////////////////////////////////////////////////
// CPgVisdata property page

IMPLEMENT_DYNCREATE(CPgVisdata, CPropertyPage)

CPgVisdata::CPgVisdata() : CPropertyPage(CPgVisdata::IDD)
{
	//{{AFX_DATA_INIT(CPgVisdata)
	m_nIdentBase = -1;
	m_nMcodeBase = -1;
	m_strMapVcode = _T("");
	m_strMapMcode = _T("");
	m_strIdent = _T("");
	m_strMapIcode = _T("");
	m_nVersion = -1;
	//}}AFX_DATA_INIT
}

CPgVisdata::~CPgVisdata()
{
}

void CPgVisdata::DoDataExchange(CDataExchange* pDX)
{
	if( !pDX->m_bSaveAndValidate )
		PrepareValues();
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPgVisdata)
	DDX_Radio(pDX, IDC_IDENT_DEC, m_nIdentBase);
	DDX_Radio(pDX, IDC_MCODE_DEC, m_nMcodeBase);
	DDX_Text(pDX, IDC_MAPVCODE, m_strMapVcode);
	DDX_Text(pDX, IDC_MAPMCODE, m_strMapMcode);
	DDX_Text(pDX, IDC_IDENT, m_strIdent);
	DDX_Text(pDX, IDC_MAPICODE, m_strMapIcode);
	DDX_Radio(pDX, IDC_VERSION_5, m_nVersion);
	//}}AFX_DATA_MAP
	if( pDX->m_bSaveAndValidate )
		RetrieveValues();
}

static char szHexFormat[] = TEXT( "0x%08lx" );
static char szDecFormat[] = TEXT( "%lu" );

void CPgVisdata::PrepareValues()
{
	m_nIdentBase = 10 == m_ascHeader.m_nIdentBase ? 0 : 1;
	m_nMcodeBase = 10 == m_ascHeader.m_nMcodeBase ? 0 : 1;
	m_nVersion = HDRVER_OLD == m_ascHeader.m_nVersion ? 0 :
				HDRVER_5 == m_ascHeader.m_nVersion ? 1 :
				0;
	m_strIdent.Format( 0 == m_nIdentBase ? szDecFormat : szHexFormat, m_dwTKIdent );
	m_strMapIcode.Format( 0 == m_nMcodeBase ? szDecFormat : szHexFormat, m_dwTKIcode );
	m_strMapMcode.Format( 0 == m_nMcodeBase ? szDecFormat : szHexFormat, m_dwTKMcode );
	m_strMapVcode.Format( 0 == m_nMcodeBase ? szDecFormat : szHexFormat, m_dwTKVcode );
}

void CPgVisdata::RetrieveValues()
{
	m_ascHeader.m_nIdentBase = 0 == m_nIdentBase ? 10 : 16;
	m_ascHeader.m_nMcodeBase = 0 == m_nMcodeBase ? 10 : 16;
	m_ascHeader.m_nVersion = 0 == m_nVersion ? HDRVER_OLD :
							1 == m_nVersion ? HDRVER_5 :
							HDRVER_OLD;
	sscanf( m_strIdent, 0 == m_nIdentBase ? szDecFormat : szHexFormat, &m_dwTKIdent );
	sscanf( m_strMapIcode, 0 == m_nMcodeBase ? szDecFormat : szHexFormat, &m_dwTKIcode );
	sscanf( m_strMapMcode, 0 == m_nMcodeBase ? szDecFormat : szHexFormat, &m_dwTKMcode );
	sscanf( m_strMapVcode, 0 == m_nMcodeBase ? szDecFormat : szHexFormat, &m_dwTKVcode );
	m_ascHeader.m_dwTKIdent = m_dwTKIdent;
	m_ascHeader.m_dwTKIcode = m_dwTKIcode;
	m_ascHeader.m_dwTKMcode = m_dwTKMcode;
	m_ascHeader.m_dwTKVcode = m_dwTKVcode;
}

BEGIN_MESSAGE_MAP(CPgVisdata, CPropertyPage)
	//{{AFX_MSG_MAP(CPgVisdata)
	ON_BN_CLICKED(IDC_IDENT_DEC, OnIdent10)
	ON_BN_CLICKED(IDC_IDENT_HEX, OnIdent16)
	ON_BN_CLICKED(IDC_MCODE_DEC, OnMcode10)
	ON_BN_CLICKED(IDC_MCODE_HEX, OnMcode16)
	ON_EN_KILLFOCUS(IDC_MAPICODE, OnKillfocusUniqueident)
	ON_EN_KILLFOCUS(IDC_MAPMCODE, OnKillfocusMapmcode)
	ON_EN_KILLFOCUS(IDC_MAPVCODE, OnKillfocusMapvcode)
	ON_EN_KILLFOCUS(IDC_IDENT, OnKillfocusIdent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPgVisdata message handlers

BOOL CPgVisdata::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	m_dwTKIdent = m_ascHeader.m_dwTKIdent;
	m_dwTKIcode = m_ascHeader.m_dwTKIcode;
	m_dwTKMcode = m_ascHeader.m_dwTKMcode;
	m_dwTKVcode = m_ascHeader.m_dwTKVcode;
	UpdateData( FALSE );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPgVisdata::OnIdent10() 
	{ m_ascHeader.m_nIdentBase = 10; UpdateData(FALSE); }
void CPgVisdata::OnIdent16() 
	{ m_ascHeader.m_nIdentBase = 16; UpdateData(FALSE); }
void CPgVisdata::OnMcode10() 
	{ m_ascHeader.m_nMcodeBase = 10; UpdateData(FALSE); }
void CPgVisdata::OnMcode16() 
	{ m_ascHeader.m_nMcodeBase = 16; UpdateData(FALSE); }

void CPgVisdata::OnKillfocusUniqueident() 
	{ UpdateData(); }
void CPgVisdata::OnKillfocusMapmcode() 
	{ UpdateData(); }
void CPgVisdata::OnKillfocusMapvcode() 
	{ UpdateData(); }
void CPgVisdata::OnKillfocusIdent() 
	{ UpdateData(); }

/////////////////////////////////////////////////////////////////////////////
// CPgFileOpt property page

IMPLEMENT_DYNCREATE(CPgFileOpt, CPropertyPage)

CPgFileOpt::CPgFileOpt() : CPropertyPage(CPgFileOpt::IDD)
{
	//{{AFX_DATA_INIT(CPgFileOpt)
	m_nJumpX = 0;
	m_nJumpY = 0;
	//}}AFX_DATA_INIT
}

CPgFileOpt::~CPgFileOpt()
{
}

void CPgFileOpt::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPgFileOpt)
	DDX_Text(pDX, IDC_EDIT1, m_nJumpX);
	DDX_Text(pDX, IDC_EDIT2, m_nJumpY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPgFileOpt, CPropertyPage)
	//{{AFX_MSG_MAP(CPgFileOpt)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPgFileOpt message handlers

/////////////////////////////////////////////////////////////////////////////
// CDlgFileProp

IMPLEMENT_DYNAMIC(CDlgFileProp, CPropertySheet)

CDlgFileProp::CDlgFileProp(CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(IDD, pParentWnd, iSelectPage)
{
	AddPage( &m_pgGeometry );
	AddPage( &m_pgVisdata );
	AddPage( &m_pgFileOpt );
}

CDlgFileProp::~CDlgFileProp()
{
}

BEGIN_MESSAGE_MAP(CDlgFileProp, CPropertySheet)
	//{{AFX_MSG_MAP(CDlgFileProp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFileProp message handlers

