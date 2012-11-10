// RechStat.cpp : implementation file
//

#include "pheader.h"
#include "odbcext.hr"
#include "RechStat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRechStat dialog


CRechStat::CRechStat(CWnd* pParent /*=NULL*/)
	: CDialog(CRechStat::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRechStat)
	m_strNumber = _T("");
	//}}AFX_DATA_INIT
}

void CRechStat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRechStat)
	DDX_Text(pDX, IDT_RECORD_NUMBER, m_strNumber);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRechStat, CDialog)
	//{{AFX_MSG_MAP(CRechStat)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRechStat message handlers

void CRechStat::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	CDialog::PostNcDestroy();
	delete this;
}
