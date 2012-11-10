// DlgMapSpecial.cpp : implementation file
//

#include "stdafx.h"
#include "mapmgr.h"
#include "DlgMapSpecial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMapSpecial dialog


CDlgMapSpecial::CDlgMapSpecial(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMapSpecial::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMapSpecial)
	m_X = 0;
	m_Y = 0;
	//}}AFX_DATA_INIT
}


void CDlgMapSpecial::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMapSpecial)
	DDX_Control(pDX, IDC_BMP2, m_bmp2);
	DDX_Control(pDX, IDC_BMP1, m_bmp1);
	DDX_Text(pDX, IDC_EDIT_X, m_X);
	DDX_Text(pDX, IDC_EDIT_Y, m_Y);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMapSpecial, CDialog)
	//{{AFX_MSG_MAP(CDlgMapSpecial)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMapSpecial message handlers
