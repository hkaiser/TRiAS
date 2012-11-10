[!if=(FileExists, "FALSE")]
// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: [!DateAndTime]
//
// @doc
// @module [!DlgCPPName] | Implementation of the <c [!DlgClassName]> class

[!crlf]
#include "stdafx.h"

[!crlf]
#include "[!ProjectName].h"
#include "[!DlgHeaderName]"
[!else]
[!AddIncludeFile(TargetFile, "stdafx.h")]
[!AddStringToSymbol(ProjectName.h, ProjectName, ".h")]
[!AddIncludeFile(TargetFile, ProjectName.h)]
[!AddIncludeFile(TargetFile, HeaderName)]
[!endif]

[!crlf]
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

[!crlf]
/////////////////////////////////////////////////////////////////////////////
// [!DlgClassName]

[!crlf]
[!DlgClassName]* [!DlgClassName]::CreateInstance (LPCSTR pcCaption)
{
[!DlgClassName] *pCfgDlg = NULL;

[!crlf]
	COM_TRY {
	// Dialog erzeugen
		pCfgDlg = new [!DlgClassName]();

[!crlf]
	// Caption setzen
		pCfgDlg -> m_strCaption = pcCaption;
		pCfgDlg -> m_psp.pszTitle = pCfgDlg -> m_strCaption;
		pCfgDlg -> m_psp.dwFlags |= PSP_USETITLE;

[!crlf]
	} COM_CATCH_OP_RETURN(delete pCfgDlg, NULL);
	return pCfgDlg; 
}

[!crlf]
IMPLEMENT_DYNCREATE([!DlgClassName], CPropertyPage)

[!crlf]
[!DlgClassName]::[!DlgClassName]() 
	: CPropertyPage([!DlgClassName]::IDD)
{
	//{{AFX_DATA_INIT([!DlgClassName])
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_dwFlags = 0;
}

[!crlf]
[!DlgClassName]::~[!DlgClassName]()
{
}

[!crlf]
void [!DlgClassName]::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP([!DlgClassName])
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

[!crlf]
BEGIN_MESSAGE_MAP([!DlgClassName], CPropertyPage)
	//{{AFX_MSG_MAP([!DlgClassName])
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

[!crlf]
void [!DlgClassName]::AdjustSheetButtons()
{
CPropertySheet *pSheet = DYNAMIC_DOWNCAST(CPropertySheet, GetParent());

[!crlf]
	ASSERT(NULL != pSheet);	

[!crlf]
DWORD dwBttns = 0;

[!crlf]
	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns = PSWIZB_BACK;			// nicht erste Seite

[!crlf]
	if (!GetDisableNextPage()) {
		if (m_dwFlags & ADDPAGES_LASTPAGE) 
			dwBttns |= PSWIZB_FINISH;	// letzte Seite
		else 
			dwBttns |= PSWIZB_NEXT;		// nicht letzte seite
	} else if (m_dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

[!crlf]
	pSheet -> SetWizardButtons(dwBttns);
}

[!crlf]
BOOL [!DlgClassName]::GetDisableNextPage()
{
	// TODO: return TRUE, if 'Next >' - button should be disabled

[!crlf]
	return FALSE;
}

[!crlf]
/////////////////////////////////////////////////////////////////////////////
// [!DlgClassName] message handlers

[!crlf]
BOOL [!DlgClassName]::OnSetActive() 
{
	AdjustSheetButtons();
	return CPropertyPage::OnSetActive();
}

