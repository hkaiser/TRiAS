// EdPage6.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "EdPage6.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditPage6 property page

IMPLEMENT_DYNCREATE(CEditPage6, CPropertyPage)

CEditPage6::CEditPage6() : CPropertyPage(CEditPage6::IDD)
{
	//{{AFX_DATA_INIT(CEditPage6)
	m_strBem = _T("");
	//}}AFX_DATA_INIT
}

CEditPage6::~CEditPage6()
{
}

void CEditPage6::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditPage6)
	DDX_Text(pDX, IDC_EDIT2, m_strBem);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditPage6, CPropertyPage)
	//{{AFX_MSG_MAP(CEditPage6)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditPage6 message handlers
