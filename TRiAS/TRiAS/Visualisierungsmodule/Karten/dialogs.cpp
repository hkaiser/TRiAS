#include "stdafx.h"
#include "KartenImpl.h"
#include "dialogs.h"

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
initial version
RCS}}*/
static char* pszRCS = "$Id: dialogs.cpp 1.1 1996/07/12 17:30:29 andy Exp $";
/* $Log: dialogs.cpp $
// Revision 1.1  1996/07/12  17:30:29  andy
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
// CDlgPgColor property page

IMPLEMENT_DYNCREATE(CDlgPgColor, CPropertyPage)

CDlgPgColor::CDlgPgColor() 
	: CPropertyPage(CDlgPgColor::IDD)
{
	//{{AFX_DATA_INIT(CDlgPgColor)
	m_chkSingleMap = -1;
	m_bTransparent = FALSE;
	//}}AFX_DATA_INIT
}

CDlgPgColor::~CDlgPgColor()
	{ }

void CDlgPgColor::DoDataExchange(CDataExchange* pDX)
{
	if( !pDX->m_bSaveAndValidate )
		PrepareValues();
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPgColor)
	DDX_Control(pDX, IDC_LISTOFPALETTES, m_lbPalettes);
	DDX_Radio(pDX, IDC_CHKSINGLEMAP, m_chkSingleMap);
	DDX_Check(pDX, IDC_TRANSPARndENT, m_bTransparent);
	//}}AFX_DATA_MAP
	if( pDX->m_bSaveAndValidate )
		RetrieveValues();
}

void CDlgPgColor::PrepareValues()
	{ }

void CDlgPgColor::RetrieveValues()
	{ }

BEGIN_MESSAGE_MAP(CDlgPgColor, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgPgColor)
	ON_LBN_SELCHANGE(IDC_LISTOFPALETTES, OnSelchangeListofpalettes)
	ON_BN_CLICKED(IDC_CHKALLMAPS, OnChkallmaps)
	ON_BN_CLICKED(IDC_CHKSINGLEMAP, OnChksinglemap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPgColor message handlers

BOOL CDlgPgColor::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_lbPalettes.ResetContent();
	for( int i = 0; i < m_strPalettes.GetSize(); ++i )
		m_lbPalettes.AddString( m_strPalettes.GetAt( i ) );
	if( m_strMapPalette.IsEmpty() )
		VERIFY( m_strMapPalette.LoadString( IDS_DEFAULTPALETTE ) );
	if( m_strViewPalette.IsEmpty() )
		m_strViewPalette = m_strMapPalette;
	int idx = m_lbPalettes.FindStringExact( -1, 0 == m_chkSingleMap ? m_strMapPalette : m_strViewPalette );
	m_lbPalettes.SetCurSel( LB_ERR == idx ? 0 : idx );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPgColor::OnSelchangeListofpalettes() 
{
	m_lbPalettes.GetText( m_lbPalettes.GetCurSel(), 0 == m_chkSingleMap ? m_strMapPalette : m_strViewPalette );
}

void CDlgPgColor::OnChkallmaps() 
{
	UpdateData();
	int idx = m_lbPalettes.FindStringExact( -1, m_strViewPalette );
	m_lbPalettes.SetCurSel( LB_ERR == idx ? 0 : idx );
}

void CDlgPgColor::OnChksinglemap() 
{
	UpdateData();
	int idx = m_lbPalettes.FindStringExact( -1, m_strMapPalette );
	m_lbPalettes.SetCurSel( LB_ERR == idx ? 0 : idx );
}

/////////////////////////////////////////////////////////////////////////////
// CDlgPgDirectories property page

IMPLEMENT_DYNCREATE(CDlgPgDirectories, CPropertyPage)

CDlgPgDirectories::CDlgPgDirectories() 
	: CPropertyPage(CDlgPgDirectories::IDD)
{
	//{{AFX_DATA_INIT(CDlgPgDirectories)
	//}}AFX_DATA_INIT

// KK010108
	m_iPos = -1;
}

CDlgPgDirectories::~CDlgPgDirectories()
	{ }

void CDlgPgDirectories::DoDataExchange(CDataExchange* pDX)
{
	if( !pDX->m_bSaveAndValidate )
		PrepareValues();
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPgDirectories)
	DDX_Control(pDX, IDC_LIST_MAPDIRS, m_lbMapDirs);
	//}}AFX_DATA_MAP
	if( pDX->m_bSaveAndValidate )
		RetrieveValues();
}

void CDlgPgDirectories::PrepareValues()
	{ }

void CDlgPgDirectories::RetrieveValues( )
{
	m_iPos ++;

	CString	S;
	m_strMapDirs.RemoveAll();
	for( int i = 0; i < m_lbMapDirs.GetCount(); i++ )
	{
		m_lbMapDirs.GetText( i, S );
		m_strMapDirs.Add( S );
	}
}

BEGIN_MESSAGE_MAP(CDlgPgDirectories, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgPgDirectories)
	//}}AFX_MSG_MAP
	ON_LBN_ADDITEM( IDC_LIST_MAPDIRS, OnAddDir )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPgDirectories message handlers

BOOL CDlgPgDirectories::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	// TODO: Add extra initialization here
	ASSERT_VALID( &m_strMapDirs );
	for( int i = 0; i < m_strMapDirs.GetSize(); i++ )
		m_lbMapDirs.AddString( m_strMapDirs[i] );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPgDirectories::OnAddDir()
{
	CDirSelectDialog	dlg(this);
	if( IDOK == dlg.DoModal() )
	{
		CString strDir = dlg.m_strDirectory;
		int idx = m_lbMapDirs.GetCurSel();
		m_lbMapDirs.InsertString( idx + 1, strDir );
		m_lbMapDirs.SetCurSel( idx + 1 );
	}
}

void CDlgPgDirectories::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData( TRUE );
	CPropertyPage::OnOK();
}

/////////////////////////////////////////////////////////////////////////////
// CDlgPgVisparam property page

IMPLEMENT_DYNCREATE(CDlgPgVisparam, CPropertyPage)

CDlgPgVisparam::CDlgPgVisparam() 
	: CPropertyPage(CDlgPgVisparam::IDD)
{
	//{{AFX_DATA_INIT(CDlgPgVisparam)
	m_bMapsVisible = FALSE;
	m_strFromScale = _T("");
	m_strToScale = _T("");
	//}}AFX_DATA_INIT
}

CDlgPgVisparam::~CDlgPgVisparam()
	{ }

void CDlgPgVisparam::DoDataExchange(CDataExchange* pDX)
{
	if( !pDX->m_bSaveAndValidate )
		PrepareValues();
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPgVisparam)
	DDX_Control(pDX, IDC_TO_SCALE, m_cbToScale);
	DDX_Control(pDX, IDC_FROM_SCALE, m_cbFromScale);
	DDX_Check(pDX, IDC_CHKVISIBLE, m_bMapsVisible);
	DDX_CBString(pDX, IDC_FROM_SCALE, m_strFromScale);
	DDX_CBString(pDX, IDC_TO_SCALE, m_strToScale);
	//}}AFX_DATA_MAP
	if( pDX->m_bSaveAndValidate )
		RetrieveValues();
}

static TCHAR szShowEver[] = "<beliebig>";

void CDlgPgVisparam::PrepareValues()
{
	long l = atol(m_strFromScale);
	long fScale = szShowEver == m_strFromScale ? 0 : atol( m_strFromScale );
	long tScale = szShowEver == m_strToScale ? 0 : atol( m_strToScale );

	if( 0 != fScale && 0 != tScale && tScale > fScale )
		m_strToScale = m_strFromScale;
}

void CDlgPgVisparam::RetrieveValues()
	{ }

BEGIN_MESSAGE_MAP(CDlgPgVisparam, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgPgVisparam)
	ON_CBN_SELCHANGE(IDC_FROM_SCALE, OnSelchangeFromScale)
	ON_CBN_SELCHANGE(IDC_TO_SCALE, OnSelchangeToScale)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPgVisparam message handlers

void CDlgPgVisparam::OnSelchangeFromScale() 
{
	UpdateData();
	UpdateData(FALSE);
}

void CDlgPgVisparam::OnSelchangeToScale() 
{
	UpdateData();
	UpdateData(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CDlgSheetMapParam

IMPLEMENT_DYNAMIC(CDlgSheetMapParam, CPropertySheet)

CDlgSheetMapParam::CDlgSheetMapParam(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	: CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	CreateCommon();
}

CDlgSheetMapParam::CDlgSheetMapParam(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	: CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	CreateCommon();
}

CDlgSheetMapParam::~CDlgSheetMapParam()
{
}

BEGIN_MESSAGE_MAP(CDlgSheetMapParam, CPropertySheet)
	//{{AFX_MSG_MAP(CDlgSheetMapParam)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSheetMapParam message handlers

void CDlgSheetMapParam::CreateCommon()
{
	AddPage( &m_pgColor );
	AddPage( &m_pgVisparam );
	AddPage( &m_pgDirs );
}
