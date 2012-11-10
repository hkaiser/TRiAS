// DlgOptions.cpp : implementation file
//

#include "stdafx.h"
#include "PictView.h"
#include "DlgOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOptions

IMPLEMENT_DYNAMIC(CDlgOptions, CPropertySheet)

CDlgOptions::CDlgOptions(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CDlgOptions::CDlgOptions(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CDlgOptions::~CDlgOptions()
{
}


BEGIN_MESSAGE_MAP(CDlgOptions, CPropertySheet)
	//{{AFX_MSG_MAP(CDlgOptions)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptions message handlers
