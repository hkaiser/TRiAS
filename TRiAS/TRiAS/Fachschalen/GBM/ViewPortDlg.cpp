// ViewPortDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "ViewPortDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewPortDlg dialog


CViewPortDlg::CViewPortDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CViewPortDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CViewPortDlg)
	m_lVPoldOrgX = 0;
	m_lVPoldOrgY = 0;
	m_lVPoldExtX = 0;
	m_lVPoldExtY = 0;
	m_lVPnewOrgX = 0;
	m_lVPnewOrgY = 0;
	m_lVPnewExtX = 0;
	m_lVPnewExtY = 0;
	//}}AFX_DATA_INIT
}


void CViewPortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewPortDlg)
	DDX_Text(pDX, IDC_EDIT1, m_lVPoldOrgX);
	DDX_Text(pDX, IDC_EDIT2, m_lVPoldOrgY);
	DDX_Text(pDX, IDC_EDIT3, m_lVPoldExtX);
	DDX_Text(pDX, IDC_EDIT4, m_lVPoldExtY);
	DDX_Text(pDX, IDC_EDIT5, m_lVPnewOrgX);
	DDX_Text(pDX, IDC_EDIT6, m_lVPnewOrgY);
	DDX_Text(pDX, IDC_EDIT7, m_lVPnewExtX);
	DDX_Text(pDX, IDC_EDIT8, m_lVPnewExtY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewPortDlg, CDialog)
	//{{AFX_MSG_MAP(CViewPortDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewPortDlg message handlers
