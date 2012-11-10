// $Header: $
// Copyright© 1999-2001 VNS GmbH Potsdam, All rights reserved
// Created: 27.08.2002 10:50:44
//
// @doc
// @module LimitPacketsDlg.cpp | Implementation of the <c CLimitPacketsDlg> class

#include "trias03p.hxx"

#include <limits.h>
#include <ScopeVar.h>

#include "trias03.h"
#include "LimitPacketsDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char g_pDLLName[_MAX_PATH];

/////////////////////////////////////////////////////////////////////////////
// CLimitPacketsDlg

CLimitPacketsDlg* CLimitPacketsDlg::CreateInstance (LPCSTR pcCaption)
{
CLimitPacketsDlg *pCfgDlg = NULL;

	COM_TRY {
	// Dialog erzeugen
	ResourceFile RF (g_pDLLName);

		pCfgDlg = new CLimitPacketsDlg(ResID(CLimitPacketsDlg::IDD, &RF), pcCaption);

		if (NULL == pCfgDlg || !pCfgDlg -> FInit()) {
			DELETE_OBJ(pCfgDlg);
			return NULL;
		}

	} COM_CATCH_OP_RETURN(delete pCfgDlg, NULL);
	return pCfgDlg; 
}

CLimitPacketsDlg::CLimitPacketsDlg(ResID uiResID, LPCSTR pcCaption) :
	CPropertyPage(uiResID, pcCaption),
	m_rbAll(this, IDC_NOLIMIT),
	m_rbLimit(this, IDC_ADDITIONAL_LIMIT),
	m_cbRelate(this, IDC_COMPARE),
	m_spinCount(this, IDC_OBJCOUNT, IDC_SPIN_COUNT, Range(0, UD_MAXVAL)),
	m_ftCount(this, IDC_OBJECTCOUNT),
	m_ftDesc(this, IDC_LIMITPACKETS_DESC),
	m_spinCountORWnds(this, IDC_COUNT_ORWNDS, IDC_SPIN_COUNT_ORWNDS, Range(0, MAX_ORWNDS)),
	m_cbLimitORWnds(this, IDC_LIMIT_ORWNDS)
{
	m_dwFlags = 0;
	m_lLastLimitObjs = 0;
	m_lLastLimitORWnds = 0;
}

BOOL CLimitPacketsDlg::FInit()
{
	m_fSemaphore = FALSE;
	return TRUE;
}

CLimitPacketsDlg::~CLimitPacketsDlg()
{
}

void CLimitPacketsDlg::AdjustSheetButtons()
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

BOOL CLimitPacketsDlg::GetDisableNextPage()
{
	return FALSE;
}

HRESULT CLimitPacketsDlg::PrepareResult (void)
{
	m_selData.lLimitObjs = m_spinCount.GetValue();
	m_selData.rgLimit = (LIMITPACKETS)m_cbRelate.GetCurrentIndex();
	_ASSERTE(m_selData.rgLimit >= -1 && m_selData.rgLimit <= 4);

	if (m_cbLimitORWnds.isChecked())
		m_selData.lLimitORWnds = m_spinCountORWnds.GetValue();
	else
		m_selData.lLimitORWnds = 0;

	return S_OK;
}

void CLimitPacketsDlg::SelectMode(LIMITPACKETS rgLimit)
{
CScopeVar<BOOL> Sem(m_fSemaphore, TRUE);

	if (Sem.GetOldValue())
		return;		// Rekursion verhindern

ResourceFile RF (g_pDLLName);

	if (LIMITPACKETS_None == rgLimit) {
		m_rbLimit.SetState(FALSE);
		m_rbAll.SetState(TRUE);

		m_rgLastLimit = (LIMITPACKETS)m_cbRelate.GetCurrentIndex();
		m_lLastLimitObjs = m_spinCount.GetValue();

		m_cbRelate.ChangeCurrentIndex(-1);
		m_spinCount.SetValue(0);

	ResString resDesc (ResID(IDS_NOLIMIT_PACKETS, &RF), 255);

		m_ftDesc.SetText(resDesc);
	}
	else {
		m_rbLimit.SetState(TRUE);
		m_rbAll.SetState(FALSE);

		_ASSERTE(rgLimit >= 0 && rgLimit <= 4);
		m_cbRelate.ChangeCurrentIndex(rgLimit);
		m_spinCount.SetValue(m_lLastLimitObjs > 0 ? m_lLastLimitObjs : 1);

	ResString resDesc (ResID(IDS_LIMIT_PACKETS, &RF), 255);

		m_ftDesc.SetText(resDesc);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CLimitPacketsDlg message handlers
namespace {
	UINT uiIds[] = {
		IDS_LESSER, 
		IDS_LESSEREQUAL, 
		IDS_EQUAL, 
		IDS_MOREEQUAL, 
		IDS_MORE
	};
}

void CLimitPacketsDlg::WindowInit(Event e) 
{
	m_rbAll.FInit();
	m_rbLimit.FInit();
	m_cbRelate.FInit();
	m_spinCount.FInit();
	m_ftCount.FInit();
	m_ftDesc.FInit();
	m_cbLimitORWnds.FInit();
	m_spinCountORWnds.FInit();
	
// ComboBox6 füllen
ResourceFile RF (g_pDLLName);

	for (int i = 0; i < _countof(uiIds); ++i) {
	ResString resItem (ResID(uiIds[i], &RF), 32);

		m_cbRelate.AddString(resItem);
	}

	SelectMode(m_rgLastLimit);

	if (m_lLastLimitORWnds > 0) {
		m_cbLimitORWnds.SetChecked(TRUE);
		m_spinCountORWnds.SetValue(m_lLastLimitORWnds);
	}
}

int CLimitPacketsDlg::OnWizNext (NotifyEvt)
{
	if (SUCCEEDED(PrepareResult()))		// Ergebnisse zwischenspeichern
		return 0;
	return -1;
}

// Finish wurde gedrückt 
int CLimitPacketsDlg::OnWizFinish (NotifyEvt)
{
	PrepareResult(); 					// Ergebnisse zwischenspeichern
	return 0;
}

int CLimitPacketsDlg::OnSetActive (NotifyEvt e)
{
	AdjustSheetButtons();
	return 0;
}

void CLimitPacketsDlg::ButtonClick(ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDC_ADDITIONAL_LIMIT:
	case IDC_NOLIMIT:
		{
			if (!m_rbLimit.GetState()) 
				SelectMode();
			else
				SelectMode(LIMITPACKETS_None == m_rgLastLimit ? 
					LIMITPACKETS_More : m_rgLastLimit);
		}
		break;

	case IDC_LIMIT_ORWNDS:
		{
		CScopeVar<BOOL> Sem(m_fSemaphore, TRUE);

			if (Sem.GetOldValue())
				return;		// Rekursion verhindern

			if (m_cbLimitORWnds.isChecked()) {
				m_spinCountORWnds.SetValue(
					m_lLastLimitORWnds > 0 ? m_lLastLimitORWnds : 1);
			}
			else {
				m_lLastLimitORWnds = m_spinCountORWnds.GetValue();
				m_spinCountORWnds.SetValue(0);
			}
		}
		break;

	default:
		_ASSERTE(FALSE);
		return;
	}

	PrepareResult();
	AdjustSheetButtons();
}

void CLimitPacketsDlg::ListBoxSel(ControlEvt e)
{
	_ASSERTE(IDC_COMPARE == (uint)e.GetControlID());

int iIndex = m_cbRelate.GetCurrentIndex();

	if (iIndex >= 0) {
		m_rbLimit.SetState(TRUE);
		m_rbAll.SetState(FALSE);
		SelectMode((LIMITPACKETS)iIndex);
	}

	PrepareResult();
	AdjustSheetButtons();
}

void CLimitPacketsDlg::EditChange(ControlEvt e)
{
	if (IDC_OBJCOUNT == (uint)e.GetControlID()) {
		m_spinCount.CopyToSpin();
		if (0 == m_spinCount.GetValue()) {
			m_rbLimit.SetState(FALSE);
			m_rbAll.SetState(TRUE);
			SelectMode();
		} 
		else {
			m_lLastLimitObjs = m_spinCount.GetValue();
			m_rbLimit.SetState(TRUE);
			m_rbAll.SetState(FALSE);
			SelectMode(LIMITPACKETS_None == m_rgLastLimit ? 
				LIMITPACKETS_More : m_rgLastLimit);
		}
	}
	else if (IDC_COUNT_ORWNDS == (uint)e.GetControlID()) {
	CScopeVar<BOOL> Sem(m_fSemaphore, TRUE);

		if (Sem.GetOldValue())
			return;		// Rekursion verhindern

		m_spinCountORWnds.CopyToSpin();
		if (0 == m_spinCountORWnds.GetValue()) {
			m_cbLimitORWnds.SetChecked(FALSE);
		}
		else {
			m_lLastLimitORWnds = m_spinCountORWnds.GetValue();
			m_cbLimitORWnds.SetChecked(TRUE);
			m_spinCountORWnds.SetValue(
				m_lLastLimitORWnds > 0 ? m_lLastLimitORWnds : 1);
		}
	}
	else {
		_ASSERTE(FALSE);
		return;
	}

	PrepareResult();
	AdjustSheetButtons();
}

