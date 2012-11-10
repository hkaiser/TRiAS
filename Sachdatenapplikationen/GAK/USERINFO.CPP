// UserInfo.cpp : implementation file
//

#include "stdafx.h"			// vorübers. Header
#include "gak.h"			// CGakApp
#include "numedit.h"		// CErzNrEdit
#include "UserInfo.h"		// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserInfoDlg dialog


CUserInfoDlg::CUserInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserInfoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CUserInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserInfoDlg)
	DDX_Control(pDX, IDE_USER_NAME, m_edUserName);
	DDX_Control(pDX, IDOK, m_btOk);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CUserInfoDlg)
	ON_EN_CHANGE(IDE_USER_NAME, OnChangeUserName)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserInfoDlg message handlers

void CUserInfoDlg::OnChangeUserName() 
{
	// TODO: Add your control notification handler code here
	if (m_edUserName.LineLength () > 0)
		m_btOk.EnableWindow (TRUE);
	else
		m_btOk.EnableWindow (FALSE);
}

void CUserInfoDlg::OnOK() 
{
	// TODO: Add extra validation here
	m_edUserName.GetWindowText (m_strUserName);
	
	CDialog::OnOK();
}

BOOL CUserInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_edUserName.LimitText (UserNameLen);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CUserInfoDlg::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	
	// return CDialog::OnHelpInfo(pHelpInfo);
	ASSERT (pHelpInfo != NULL);

	if (pHelpInfo -> dwContextId)
		WinHelp (pHelpInfo -> dwContextId, HELP_CONTEXTPOPUP);

	return TRUE;
}
