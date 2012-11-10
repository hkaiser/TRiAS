// $Header: $
// Copyright© 1999 Fernerkundungszentrum Potsdam GmbH, All rights reserved
//
// @doc
// @module MergeTwoSourcesDlg.cpp | Implementation of the <c CMergeTwoSourcesDlg> class

#include "stdafx.h"

#include "PropActSubSeq.h"
#include "MergeTwoSourcesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMergeTwoSourcesDlg

CMergeTwoSourcesDlg* CMergeTwoSourcesDlg::CreateInstance (LPCSTR pcCaption)
{
CMergeTwoSourcesDlg *pCfgDlg = NULL;

	COM_TRY {
	// Dialog erzeugen
		pCfgDlg = new CMergeTwoSourcesDlg();

	// Caption setzen
		pCfgDlg -> m_strCaption = pcCaption;
		pCfgDlg -> m_psp.pszTitle = pCfgDlg -> m_strCaption;
		pCfgDlg -> m_psp.dwFlags |= PSP_USETITLE;

	} COM_CATCH_OP_RETURN(delete pCfgDlg, NULL);
	return pCfgDlg; 
}

IMPLEMENT_DYNCREATE(CMergeTwoSourcesDlg, CPropertyPage)

CMergeTwoSourcesDlg::CMergeTwoSourcesDlg() 
	: CPropertyPage(CMergeTwoSourcesDlg::IDD)
{
	//{{AFX_DATA_INIT(CMergeTwoSourcesDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_dwFlags = 0;
}

CMergeTwoSourcesDlg::~CMergeTwoSourcesDlg()
{
}

void CMergeTwoSourcesDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMergeTwoSourcesDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMergeTwoSourcesDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CMergeTwoSourcesDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CMergeTwoSourcesDlg::AdjustSheetButtons()
{
CPropertySheet *pSheet = DYNAMIC_DOWNCAST(CPropertySheet, GetParent());

	ASSERT(NULL != pSheet);	

DWORD dwBttns = 0;

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns = PSWIZB_BACK;			// nicht erste Seite

	if (!GetDisableNextPage()) {
		if (m_dwFlags & ADDPAGES_LASTPAGE) 
			dwBttns |= PSWIZB_FINISH;	// letzte Seite
		else 
			dwBttns |= PSWIZB_NEXT;		// nicht letzte seite
	} else if (m_dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	pSheet -> SetWizardButtons(dwBttns);
}

BOOL CMergeTwoSourcesDlg::GetDisableNextPage()
{
	// TODO: return TRUE, if 'Next >' - button should be disabled

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CMergeTwoSourcesDlg message handlers

BOOL CMergeTwoSourcesDlg::OnSetActive() 
{
	AdjustSheetButtons();
	return CPropertyPage::OnSetActive();
}
