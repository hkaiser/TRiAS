// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 09.12.2002 09:00:07
//
// @doc
// @module SaveObjectCollectionDlg.cpp | Implementation of the <c CSaveObjectCollectionDlg> class

#include "trias03p.hxx"
#include "trias03.h"

#include "SaveObjectCollectionDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// globale variablen
extern TCHAR g_pDLLName[_MAX_PATH];

/////////////////////////////////////////////////////////////////////////////
// CSaveObjectCollectionDlg

CSaveObjectCollectionDlg* CSaveObjectCollectionDlg::CreateInstance (
	LPCSTR pcCaption)
{
CSaveObjectCollectionDlg *pCfgDlg = NULL;

	COM_TRY {
	// Dialog erzeugen
	ResourceFile RF (g_pDLLName);

		pCfgDlg = new CSaveObjectCollectionDlg(ResID(IDD, &RF), pcCaption);
		if (NULL == pCfgDlg || !pCfgDlg -> FInit()) {
			DELETE_OBJ(pCfgDlg);
			return NULL;
		}

	} COM_CATCH_OP_RETURN(delete pCfgDlg, NULL);
	return pCfgDlg; 
}

CSaveObjectCollectionDlg::CSaveObjectCollectionDlg(ResID uiResID, LPCSTR pcCaption) 
	: CPropertyPage(uiResID, pcCaption)
{
	m_dwFlags = 0;
}

CSaveObjectCollectionDlg::~CSaveObjectCollectionDlg()
{
}

BOOL CSaveObjectCollectionDlg::FInit (void)
{
	return TRUE;
}

void CSaveObjectCollectionDlg::AdjustSheetButtons()
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

BOOL CSaveObjectCollectionDlg::GetDisableNextPage()
{
	// TODO: return TRUE, if 'Next >' - button should be disabled
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CSaveObjectCollectionDlg message handlers

BOOL CSaveObjectCollectionDlg::OnSetActive() 
{
	AdjustSheetButtons();
	return 0;
}
