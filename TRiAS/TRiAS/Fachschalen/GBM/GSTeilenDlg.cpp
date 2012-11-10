// GSTeilenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "GSTeilenDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGSTeilenDlg dialog


CGSTeilenDlg::CGSTeilenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGSTeilenDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGSTeilenDlg)
	m_strBez1 = _T("");
	m_strBez2 = _T("");
	m_strBez3 = _T("");
	m_strIdent1 = _T("");
	m_strIdent2 = _T("");
	m_strIdent3 = _T("");
	m_strONr1 = _T("");
	m_strONr2 = _T("");
	m_strONr3 = _T("");
	//}}AFX_DATA_INIT
}


void CGSTeilenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGSTeilenDlg)
	DDX_Text(pDX, IDC_BEZ1, m_strBez1);
	DDX_Text(pDX, IDC_BEZ2, m_strBez2);
	DDX_Text(pDX, IDC_BEZ3, m_strBez3);
	DDX_Text(pDX, IDC_IDENT1, m_strIdent1);
	DDX_Text(pDX, IDC_IDENT2, m_strIdent2);
	DDX_Text(pDX, IDC_IDENT3, m_strIdent3);
	DDX_Text(pDX, IDC_ONR1, m_strONr1);
	DDX_Text(pDX, IDC_ONR2, m_strONr2);
	DDX_Text(pDX, IDC_ONR3, m_strONr3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGSTeilenDlg, CDialog)
	//{{AFX_MSG_MAP(CGSTeilenDlg)
	ON_BN_CLICKED(IDOK, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGSTeilenDlg message handlers

void CGSTeilenDlg::OnOK() 
{
	if ( !IsIDEok( m_strIdent2, TRUE ))
		return;
	if ( !IsIDEok( m_strIdent3, TRUE ))
		return;

	CDialog::OnOK();
}
