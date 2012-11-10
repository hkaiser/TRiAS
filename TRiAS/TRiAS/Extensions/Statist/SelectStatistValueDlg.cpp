// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 29.08.99 21:21:10
//
// @doc
// @module SelectStatistValueDlg.cpp | Implementation of the <c CSelectStatistValueDlg> class

#include "stdafx.h"

#include "StatistApp.h"
#include "SelectStatistValueDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectStatistValueDlg

CSelectStatistValueDlg* CSelectStatistValueDlg::CreateInstance (LPCSTR pcCaption)
{
CSelectStatistValueDlg *pCfgDlg = NULL;

// Dialog erzeugen
	ATLTRY(pCfgDlg = new CSelectStatistValueDlg(pcCaption));
	return pCfgDlg; 
}

CSelectStatistValueDlg::CSelectStatistValueDlg(LPCSTR pcCaption) 
	: CAxPropertyPageImpl<CSelectStatistValueDlg>(pcCaption)
{
	m_dwFlags = 0;
	m_fEvalRelation = false;
	m_fInvertValue = false;
	m_fIsInitialized = false;
}

CSelectStatistValueDlg::~CSelectStatistValueDlg()
{
}

LRESULT CSelectStatistValueDlg::OnInitDialog(HWND hWnd, LPARAM lParam) 
{
// subclass controls
	m_Delimiter.SubclassWindow(GetDlgItem(IDC_STATIC_DELIMITER));
	m_Options.SubclassWindow(GetDlgItem(IDC_STATIC_OPTIONS));
	m_cbCalcRelation.Attach(GetDlgItem(IDC_EVALRELATION));
	m_cbInvertValue.Attach(GetDlgItem(IDC_INVERTVALUE));

	m_cbCalcRelation.SetCheck(m_fEvalRelation ? 1 : 0);
	m_cbInvertValue.SetCheck(m_fInvertValue ? 1 : 0);
	m_cbInvertValue.EnableWindow(m_fEvalRelation);

// attach controls
    GetDlgControl(IDC_OBJPROPTREE, IID_IPopupTree, m_ObjPropTree.ppv());
	_ASSERTE(m_ObjPropTree.IsValid());

    GetDlgControl(IDC_STATISTPROPTREE, IID_IPopupTree, m_StatFuncTree.ppv());
	_ASSERTE(m_StatFuncTree.IsValid());

    AtlAdviseSinkMap(this, true);

CComBSTR bstrToolTip;

	if (m_ObjPropTree.IsValid()) {
		m_ObjPropTree -> put_Caption(CComBSTR(""));
		m_ObjPropTree -> put_PopupTreeMode(POPUPTREEMODE_SHOWOBJPROPS);
		if (!m_strObjProp.empty())
			m_ObjPropTree -> SetSelection(CComBSTR(m_strObjProp.c_str()));

		bstrToolTip.LoadString(IDS_SELECT_OBJPROP);
		m_ObjPropTree -> put_ButtonTooltipText(bstrToolTip);
	}
	if (m_StatFuncTree.IsValid()) {
		m_StatFuncTree -> put_Caption(CComBSTR(""));
		m_StatFuncTree -> put_PopupTreeMode(POPUPTREEMODE_SHOWSTATFUNCS);
		if (!m_strStatFunc.empty())
			m_StatFuncTree -> SetSelection(CComBSTR(m_strStatFunc.c_str()));

		bstrToolTip.LoadString(IDS_SELECT_STATFUNC);
		m_StatFuncTree -> put_ButtonTooltipText(bstrToolTip);
	}

	m_fIsInitialized = true;
	return TRUE;
}

void CSelectStatistValueDlg::OnDestroy()
{
// detach controls
    AtlAdviseSinkMap(this, false);
	SetMsgHandled(FALSE);
}

// Button clicked
void CSelectStatistValueDlg::OnEvalRelation(UINT wNotifyCode, int iCtrlId, HWND hCtrl)
{
	m_cbInvertValue.EnableWindow(m_cbCalcRelation.GetCheck());
}

void CSelectStatistValueDlg::AdjustSheetButtons()
{
DWORD dwBttns = 0;

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns = PSWIZB_BACK;			// nicht erste Seite

	if (!GetDisableNextPage()) {
		if (m_dwFlags & ADDPAGES_LASTPAGE) 
			dwBttns |= PSWIZB_FINISH;	// letzte Seite
		else 
			dwBttns |= PSWIZB_NEXT;		// nicht letzte Seite
	} else if (m_dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	GetPropertySheet().SetWizardButtons(dwBttns);
}

BOOL CSelectStatistValueDlg::GetDisableNextPage()
{
	return !m_ObjProp.IsValid() || !m_StatFunc.IsValid();
}

/////////////////////////////////////////////////////////////////////////////
// CSelectStatistValueDlg message handlers

BOOL CSelectStatistValueDlg::OnSetActive() 
{
	AdjustSheetButtons();
	return CAxPropertyPageImpl<CSelectStatistValueDlg>::OnSetActive();
}

// Implementation of OnWizardNext
int CSelectStatistValueDlg::OnWizardNext()
{
	m_fEvalRelation = m_cbCalcRelation.GetCheck() ? true : false;
	m_fInvertValue = m_cbInvertValue.GetCheck() ? true : false;
	return 0;		// goto next page
}

// Implementation of OnWizardFinish
BOOL CSelectStatistValueDlg::OnWizardFinish()
{
	m_fEvalRelation = m_cbCalcRelation.GetCheck() ? true : false;
	m_fInvertValue = m_cbInvertValue.GetCheck() ? true : false;
	return TRUE;
}

