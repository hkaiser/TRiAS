// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 18.10.2000 19:56:29 
//
// @doc
// @module ObjekteVereinigenDlg.cpp | Definition of the <c CObjekteVereinigenDlg> class

#include "trias03p.hxx"
#include "trias03.h"

#include <ObjekteVereinigenGuid.h>
#include <ScriptPropActGuid.h>
#include <TrCatIds.h>

#include <ipropseq.hxx>
#include <ibscript.hxx>

#include <eieruhr.hxx>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "propactb.hxx"
#include "ObjekteVereinigen.h"
#include "ObjekteVereinigenDlg.h"

/////////////////////////////////////////////////////////////////////////////
// externe Daten
extern char g_pDLLName[_MAX_PATH];		// dieser Modul

/////////////////////////////////////////////////////////////////////////////
// CObjekteVereinigenDlg

CObjekteVereinigenDlg* CObjekteVereinigenDlg::CreateInstance (LPCSTR pcCaption)
{
CObjekteVereinigenDlg *pCfgDlg = NULL;

	COM_TRY {
	// Dialog erzeugen
	ResourceFile RF (g_pDLLName);

		pCfgDlg = new CObjekteVereinigenDlg(ResID(IDD, &RF), pcCaption);
		if (NULL == pCfgDlg || !pCfgDlg -> FInit()) {
			DELETE_OBJ(pCfgDlg);
			return NULL;
		}

	} COM_CATCH_OP_RETURN(delete pCfgDlg, NULL);
	return pCfgDlg; 
}

CObjekteVereinigenDlg::CObjekteVereinigenDlg(ResID uiDlg, LPCSTR pcCaption) :
	CPropertyPage(uiDlg, pcCaption),
	m_cbDeleteObjs(this, IDC_ORIGINDEL),
	m_cbMarkObjs(this, IDC_ORIGINMARK),
	m_cbCopyObjs(this, IDC_COPYNOTUSED),
	m_ftComment(this, IDT_OPTDESCRIPT)
{
	m_dwFlags = 0;
}

CObjekteVereinigenDlg::~CObjekteVereinigenDlg()
{
}

BOOL CObjekteVereinigenDlg::FInit (void)
{
	return TRUE;
}

void CObjekteVereinigenDlg::AdjustSheetButtons()
{
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

	SetSheetWizardButtons(dwBttns);
}

BOOL CObjekteVereinigenDlg::GetDisableNextPage()
{
	return FALSE;
}

// Ergebnisdaten aus Controls lesen und zwischenspeichern ---------------------
HRESULT CObjekteVereinigenDlg::PrepareResult (void)
{
	m_fDeleteObjs = m_cbDeleteObjs.isChecked();
	m_fMarkObjs = m_cbMarkObjs.isChecked();
	m_fCopyObjs = m_cbCopyObjs.isChecked();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CObjekteVereinigenDlg message handlers

void CObjekteVereinigenDlg::WindowInit (Event e)
{
	m_cbDeleteObjs.FInit();
	m_cbMarkObjs.FInit();
	m_cbCopyObjs.FInit();
	m_ftComment.FInit();
	
	m_cbDeleteObjs.SetChecked(m_fDeleteObjs);
	m_cbMarkObjs.SetChecked(m_fMarkObjs);
	m_cbCopyObjs.SetChecked(m_fCopyObjs);

	AdjustSheetButtons();
}

int CObjekteVereinigenDlg::OnWizNext (NotifyEvt)
{
	if (SUCCEEDED(PrepareResult()))		// Ergebnisse zwischenspeichern
		return 0;
	return -1;
}

// Finish wurde gedrückt 
int CObjekteVereinigenDlg::OnWizFinish (NotifyEvt)
{
	PrepareResult(); 					// Ergebnisse zwischenspeichern
	return 0;
}

int CObjekteVereinigenDlg::OnSetActive (NotifyEvt e)
{
	AdjustSheetButtons();
	return 0;
}

void CObjekteVereinigenDlg::ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDC_ORIGINDEL:
		{
			if (m_cbDeleteObjs.isChecked())
				m_cbMarkObjs.SetChecked(false);

		ResourceFile RF (g_pDLLName);
		ResString resComment (ResID (IDS_ORIGINDEL_COMMENT, &RF), 200);

			m_ftComment.SetText(resComment);			
		}
		break;

	case IDC_ORIGINMARK:
		{
			if (m_cbMarkObjs.isChecked()) 
				m_cbDeleteObjs.SetChecked(false);

		ResourceFile RF (g_pDLLName);
		ResString resComment (ResID (IDS_ORIGINMARK_COMMENT, &RF), 200);

			m_ftComment.SetText(resComment);			
		}
		break;

	case IDC_COPYNOTUSED:
		{
		ResourceFile RF (g_pDLLName);
		ResString resComment (ResID (IDS_COPYNOTUSED_COMMENT, &RF), 200);

			m_ftComment.SetText(resComment);			
		}
		break;
	
	default:
		break;
	}
}

