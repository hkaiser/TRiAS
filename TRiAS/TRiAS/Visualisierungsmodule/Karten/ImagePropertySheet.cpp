// ImagePropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "karten.h"
#include "ImagePropertySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImagePropertySheet

IMPLEMENT_DYNAMIC(CImagePropertySheet, CPropertySheet)

CImagePropertySheet::CImagePropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage), m_iLastActivePage(iSelectPage)
{
}

CImagePropertySheet::CImagePropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CImagePropertySheet::~CImagePropertySheet()
{
}


BEGIN_MESSAGE_MAP(CImagePropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CImagePropertySheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImagePropertySheet message handlers

BOOL CImagePropertySheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
    SetActivePage(m_iLastActivePage);

	return bResult;
}

BOOL CImagePropertySheet::OnCommand(WPARAM wParam, LPARAM lParam) 
{
    if (LOWORD(wParam) == IDOK)
        m_iLastActivePage = GetPageIndex(GetActivePage());

	return CPropertySheet::OnCommand(wParam, lParam);
}
