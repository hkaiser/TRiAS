// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 09.12.2002 09:00:50
//
// @doc
// @module LoadObjectCollectionDlg.cpp | Implementation of the <c CLoadObjectCollectionDlg> class

#include "trias03p.hxx"
#include "trias03.h"

#include "LoadObjectCollectionDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// globale variablen
extern TCHAR g_pDLLName[_MAX_PATH];

/////////////////////////////////////////////////////////////////////////////
// CLoadObjectCollectionDlg

CLoadObjectCollectionDlg* CLoadObjectCollectionDlg::CreateInstance (
	LPCSTR pcCaption)
{
CLoadObjectCollectionDlg *pCfgDlg = NULL;

	COM_TRY {
	// Dialog erzeugen
	ResourceFile RF (g_pDLLName);

		pCfgDlg = new CLoadObjectCollectionDlg(ResID(IDD, &RF), pcCaption);
		if (NULL == pCfgDlg || !pCfgDlg -> FInit()) {
			DELETE_OBJ(pCfgDlg);
			return NULL;
		}

	} COM_CATCH_OP_RETURN(delete pCfgDlg, NULL);
	return pCfgDlg; 
}

CLoadObjectCollectionDlg::CLoadObjectCollectionDlg(ResID uiResID, LPCSTR pcCaption) 
	: CPropertyPage(uiResID, pcCaption)
{
	m_dwFlags = 0;
}

CLoadObjectCollectionDlg::~CLoadObjectCollectionDlg()
{
}

BOOL CLoadObjectCollectionDlg::FInit (void)
{
	return TRUE;
}

void CLoadObjectCollectionDlg::AdjustSheetButtons()
{
CPropertySheet *pSheet = GetPropertySheet();

	_ASSERTE(NULL != pSheet);	

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

BOOL CLoadObjectCollectionDlg::GetDisableNextPage()
{
	// TODO: return TRUE, if 'Next >' - button should be disabled
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CLoadObjectCollectionDlg message handlers

BOOL CLoadObjectCollectionDlg::OnSetActive() 
{
	AdjustSheetButtons();
	return 0;
}
