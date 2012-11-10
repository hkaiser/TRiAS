// InterDialog.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "InterDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInterDialog dialog


CInterDialog::CInterDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CInterDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInterDialog)
	m_strBez = _T("");
	m_strPfad = _T("");
	//}}AFX_DATA_INIT
}


void CInterDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInterDialog)
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Text(pDX, IDC_EDIT1, m_strBez);
	DDX_Text(pDX, IDC_TXTPFAD, m_strPfad);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInterDialog, CDialog)
	//{{AFX_MSG_MAP(CInterDialog)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInterDialog message handlers

BOOL CInterDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_btnOK.EnableWindow( FALSE );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInterDialog::OnChangeEdit() 
{
	CxString	bez;

	UpdateData( TRUE );

	bez = m_strBez;
	bez.AllTrimm();
	if ( bez.IsEmpty())	m_btnOK.EnableWindow( FALSE );
	else				m_btnOK.EnableWindow( TRUE );
}
