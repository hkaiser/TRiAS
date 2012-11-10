// exportre.cpp : implementation file
//

#include "stdafx.h"				//	prec. Header
#include "gak.h"				// 	CGakApp
//#include "resource.h"			//	Resource-Konstanten

#include "exportre.h"			// 	zugeh. Header

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExportResultDlg dialog
CExportResultDlg::CExportResultDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExportResultDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExportResultDlg)
	m_strAbfCnt = "";
	m_strErzCnt = "";
	m_strSumCnt = "";
	//}}AFX_DATA_INIT
}

void CExportResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExportResultDlg)
	DDX_Text(pDX, IDC_ABF_CNT, m_strAbfCnt);
	DDX_Text(pDX, IDC_ERZ_CNT, m_strErzCnt);
	DDX_Text(pDX, IDC_SUM_CNT, m_strSumCnt);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExportResultDlg, CDialog)
	//{{AFX_MSG_MAP(CExportResultDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CExportResultDlg message handlers

BOOL CExportResultDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CenterWindow ();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}
