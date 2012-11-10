// CulcuDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "CulcuDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCulcuDlg dialog


CCulcuDlg::CCulcuDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCulcuDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCulcuDlg)
	m_strText1 = _T("");
	m_strText2 = _T("");
	m_strText3 = _T("");
	m_strText4 = _T("");
	m_strText5 = _T("");
	m_strText6 = _T("");
	m_strText7 = _T("");
	m_strText8 = _T("");
	m_strText9 = _T("");
	m_strText10 = _T("");
	m_strText11 = _T("");
	m_strtext12 = _T("");
	m_strText13 = _T("");
	m_strText20 = _T("");
	m_strText21 = _T("");
	m_strText22 = _T("");
	m_strText23 = _T("");
	m_strText24 = _T("");
	m_strText25 = _T("");
	m_strText26 = _T("");
	//}}AFX_DATA_INIT
}


void CCulcuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCulcuDlg)
	DDX_Text(pDX, IDC_TEXT1, m_strText1);
	DDX_Text(pDX, IDC_TEXT2, m_strText2);
	DDX_Text(pDX, IDC_TEXT3, m_strText3);
	DDX_Text(pDX, IDC_TEXT4, m_strText4);
	DDX_Text(pDX, IDC_TEXT5, m_strText5);
	DDX_Text(pDX, IDC_TEXT6, m_strText6);
	DDX_Text(pDX, IDC_TEXT7, m_strText7);
	DDX_Text(pDX, IDC_TEXT8, m_strText8);
	DDX_Text(pDX, IDC_TEXT9, m_strText9);
	DDX_Text(pDX, IDC_TEXT10, m_strText10);
	DDX_Text(pDX, IDC_TEXT11, m_strText11);
	DDX_Text(pDX, IDC_TEXT12, m_strtext12);
	DDX_Text(pDX, IDC_TEXT13, m_strText13);
	DDX_Text(pDX, IDC_TEXT20, m_strText20);
	DDX_Text(pDX, IDC_TEXT21, m_strText21);
	DDX_Text(pDX, IDC_TEXT22, m_strText22);
	DDX_Text(pDX, IDC_TEXT23, m_strText23);
	DDX_Text(pDX, IDC_TEXT24, m_strText24);
	DDX_Text(pDX, IDC_TEXT25, m_strText25);
	DDX_Text(pDX, IDC_TEXT26, m_strText26);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCulcuDlg, CDialog)
	//{{AFX_MSG_MAP(CCulcuDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCulcuDlg message handlers
