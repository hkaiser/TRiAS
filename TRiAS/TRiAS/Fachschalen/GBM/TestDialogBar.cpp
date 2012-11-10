// TestDialogBar.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "TestDialogBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIntegrateDialog dialog


CIntegrateDialog::CIntegrateDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CIntegrateDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIntegrateDialog)
	m_strBez = _T("");
	m_strPfad = _T("");
	//}}AFX_DATA_INIT
}


void CIntegrateDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIntegrateDialog)
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Text(pDX, IDC_EDIT1, m_strBez);
	DDX_Text(pDX, IDC_TXTPFAD, m_strPfad);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIntegrateDialog, CDialog)
	//{{AFX_MSG_MAP(CIntegrateDialog)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIntegrateDialog message handlers

BOOL CIntegrateDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_btnOK.EnableWindow( FALSE );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CIntegrateDialog::OnChangeEdit() 
{
	UpdateData( TRUE );
	if ( m_strBez.IsEmpty())	m_btnOK.EnableWindow( FALSE );
	else						m_btnOK.EnableWindow( TRUE );
}
