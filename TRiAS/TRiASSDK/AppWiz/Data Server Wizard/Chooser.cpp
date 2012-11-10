// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.01.2000 00:03:58
//
// @doc
// @module Chooser.cpp | Implementation of the <c CChooser> class

#include "stdafx.h"
#include "TRiASDBDS.h"
#include "TRiASDBDSaw.h"
#include "Chooser.h"
#include "ConfigDlg.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// On construction, create instances of each step we can pop up.
CDialogChooser::CDialogChooser()
{
	m_pDlgs[0] = NULL;
	m_pDlgs[DLG_CONFIG] = new CConfigDlg;

	m_nCurrDlg = 0;     // We start with the New Project dialog
}

// On deconstruction, destroy instances of each step.
CDialogChooser::~CDialogChooser()
{
	for (int i=1; i <= NUM_DLGS; i++)
	{
		ASSERT(m_pDlgs[i] != NULL);
		delete m_pDlgs[i];
	}
}

void CDialogChooser::UpdateTitleIfNecessary()
{
	static CString strPreviousRoot;
	CString strCurrentRoot;
	TRiASDBDSaw.m_Dictionary.Lookup(_T("Root"), strCurrentRoot);
	if (strCurrentRoot != strPreviousRoot)
	{
		((CConfigDlg*) m_pDlgs[DLG_CONFIG]) -> UpdateTitle(strCurrentRoot);
		strPreviousRoot = strCurrentRoot;
	}
}

// On Next, use the custom AppWizard type we're generating to determine what
//  dialog to pop up.
CAppWizStepDlg* CDialogChooser::Next(CAppWizStepDlg* pDlg)
{
	ASSERT(pDlg == m_pDlgs[m_nCurrDlg]);
	ASSERT(0 == m_nCurrDlg || m_nCurrDlg == DLG_CONFIG);

	if (pDlg == NULL)   // i.e., if the New Project Dialog is present,
	{
		m_nCurrDlg = DLG_CONFIG;    // Then pop up our first step
		UpdateTitleIfNecessary();   // and update title's default
	}
	return m_pDlgs[m_nCurrDlg];
}

// On Back, determine whether we should go back to the New Project
//  dialog, or back to step 1.
CAppWizStepDlg* CDialogChooser::Back(CAppWizStepDlg* pDlg)
{
	ASSERT(pDlg == m_pDlgs[m_nCurrDlg]);
	ASSERT(0 < m_nCurrDlg && m_nCurrDlg <= NUM_DLGS);

	if (m_nCurrDlg == DLG_CONFIG)
		m_nCurrDlg = 0;					// If we're on step 1, go to New Project dialog

	return m_pDlgs[m_nCurrDlg];
}
