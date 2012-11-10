// NewProjectAdvancedDlg.cpp : implementation file
//

#include "fakemfcp.hxx"
#include "fakemfc.h"
#include "NewProjectAdvancedDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewProjectAdvancedDlg dialog


CNewProjectAdvancedDlg::CNewProjectAdvancedDlg(CWnd* pParent, int iIdBase)
	: CDialog(CNewProjectAdvancedDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewProjectAdvancedDlg)
	//}}AFX_DATA_INIT
	m_iIdBase = iIdBase;
	m_fCompatible = false;
}


void CNewProjectAdvancedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewProjectAdvancedDlg)
	DDX_Control(pDX, IDC_COMPATIBILITYMODE, m_cbCompatibility);
	DDX_Control(pDX, IDC_DEZIMAL, m_rbDezimal);
	DDX_Control(pDX, IDC_HEXADEZ, m_rbHexaDez);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewProjectAdvancedDlg, CDialog)
	//{{AFX_MSG_MAP(CNewProjectAdvancedDlg)
	ON_BN_CLICKED(IDC_DEZIMAL, OnDezimal)
	ON_BN_CLICKED(IDC_HEXADEZ, OnHexadezimal)
	ON_BN_CLICKED(IDC_COMPATIBILITYMODE, OnCompatibilitymode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewProjectAdvancedDlg message handlers

BOOL CNewProjectAdvancedDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (10 == m_iIdBase) {
		m_rbDezimal.SetCheck (true);
		m_rbHexaDez.SetCheck (false);
	} else if (16 == m_iIdBase) {
		m_rbDezimal.SetCheck (false);
		m_rbHexaDez.SetCheck (true);
	} else
		ASSERT(m_iIdBase == 10 || m_iIdBase == 16);

	m_cbCompatibility.SetCheck (false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CNewProjectAdvancedDlg::OnDezimal() 
{
	m_iIdBase = m_rbDezimal.GetCheck() ? 10 : 16;
}

void CNewProjectAdvancedDlg::OnHexadezimal() 
{
	m_iIdBase = m_rbHexaDez.GetCheck() ? 16 : 10;
}

void CNewProjectAdvancedDlg::OnCompatibilitymode() 
{
	m_fCompatible = m_cbCompatibility.GetCheck() ? 1 : 0;
}
