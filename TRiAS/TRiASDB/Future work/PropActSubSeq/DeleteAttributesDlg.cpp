// $Header: $
// Copyright© 1999-2000 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 30.07.2000 20:24:06
//
// @doc
// @module DeleteAttributesDlg.cpp | Implementation of the <c CDeleteAttributesDlg> class

#include "stdafx.h"

#include "PropActSubSeq.h"
#include "DeleteAttributesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeleteAttributesDlg

CDeleteAttributesDlg* CDeleteAttributesDlg::CreateInstance (LPCSTR pcCaption)
{
CDeleteAttributesDlg *pCfgDlg = NULL;

	COM_TRY {
	// Dialog erzeugen
		pCfgDlg = new CDeleteAttributesDlg();

	// Caption setzen
		pCfgDlg -> m_strCaption = pcCaption;
		pCfgDlg -> m_psp.pszTitle = pCfgDlg -> m_strCaption;
		pCfgDlg -> m_psp.dwFlags |= PSP_USETITLE;

	} COM_CATCH_OP_RETURN(delete pCfgDlg, NULL);
	return pCfgDlg; 
}

IMPLEMENT_DYNCREATE(CDeleteAttributesDlg, CPropertyPage)

CDeleteAttributesDlg::CDeleteAttributesDlg() 
	: CPropertyPage(CDeleteAttributesDlg::IDD)
{
	//{{AFX_DATA_INIT(CDeleteAttributesDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_dwFlags = 0;
}

CDeleteAttributesDlg::~CDeleteAttributesDlg()
{
}

void CDeleteAttributesDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeleteAttributesDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDeleteAttributesDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CDeleteAttributesDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CDeleteAttributesDlg::AdjustSheetButtons()
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

BOOL CDeleteAttributesDlg::GetDisableNextPage()
{
	// TODO: return TRUE, if 'Next >' - button should be disabled

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CDeleteAttributesDlg message handlers

BOOL CDeleteAttributesDlg::OnSetActive() 
{
	AdjustSheetButtons();
	return CPropertyPage::OnSetActive();
}
