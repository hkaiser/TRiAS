// SuchDialog.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "SuchDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuchDialog dialog


CSuchDialog::CSuchDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSuchDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSuchDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSuchDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSuchDialog)
	DDX_Control(pDX, IDC_TAB1, m_tabSuch);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSuchDialog, CDialog)
	//{{AFX_MSG_MAP(CSuchDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuchDialog message handlers
