// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 22.12.2000 16:45:12 
//
// @doc
// @module UnitsOfMeasureDlg.cpp | Definition of the <c CUnitsOfMeasureDlg> class

#include "stdafx.h"
#include "statist.h"
#include "UnitsOfMeasureDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUnitsOfMeasureDlg property page

CUnitsOfMeasureDlg::CUnitsOfMeasureDlg() 
{
	m_iUnitOfArea = ((CStatist *)g_pTE) -> GetUnitOfArea();
	m_iUnitOfLength = ((CStatist *)g_pTE) -> GetUnitOfLength();
	m_fAppendUnits = ((CStatist *)g_pTE) -> GetAppendUnits();
}

CUnitsOfMeasureDlg::~CUnitsOfMeasureDlg()
{
	if (IsWindow()) {
		DestroyWindow();
		_ASSERTE(NULL == m_hWnd);
	}
}

BOOL CUnitsOfMeasureDlg::FillComboBox (UINT uiId, CComboBox &rcb)
{
CString str;

	str.LoadString(uiId);
	_ASSERTE(str.GetLength() > 0);

int iPos = str.Find('\n');

	while (-1 != iPos) {
		rcb.AddString(str.Mid(0, iPos));
		str = str.Mid(iPos+1);
		iPos = str.Find('\n');
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CUnitsOfMeasureDlg message handlers

LRESULT CUnitsOfMeasureDlg::OnInitDialog(HWND hWnd, LPARAM lParam) 
{
	m_cbUnitsOfArea.Attach(GetDlgItem(IDC_UNIT_OF_AREA));
	m_cbUnitsOfLength.Attach(GetDlgItem(IDC_UNIT_OF_LENGTH));
	m_ftStaticArea.Attach(GetDlgItem(IDC_STATIC_AREA));
	m_ftStaticLength.Attach(GetDlgItem(IDC_STATIC_LENGTH));
	m_cbAppendUnits.Attach(GetDlgItem(IDC_APPENDUNITS));

	m_StaticOptions.SubclassWindow(GetDlgItem(IDC_STATIC_OPTIONS));
	m_StaticLength.SubclassWindow(GetDlgItem(IDC_STATIC_UNITS));
	m_StaticDesc.SubclassWindow(GetDlgItem(IDC_STATIC_DESC));

// ComboBoxen füllen
	FillComboBox (IDS_UNIT_OF_LENGTH, m_cbUnitsOfLength);
	FillComboBox (IDS_UNIT_OF_AREA, m_cbUnitsOfArea);
	
// Controls initialisieren
	if (-1 == m_iUnitOfArea) {
		_ASSERTE(-1 == m_iUnitOfLength);
		CButton(GetDlgItem(IDC_AUTO_SELECT)).SetCheck(1);
		CButton(GetDlgItem(IDC_SELECT_UNITS)).SetCheck(0);

		m_cbUnitsOfArea.EnableWindow(FALSE);
		m_cbUnitsOfLength.EnableWindow(FALSE);
		m_ftStaticArea.EnableWindow(FALSE);
		m_ftStaticLength.EnableWindow(FALSE);

		m_cbAppendUnits.SetCheck(1);
		m_cbAppendUnits.EnableWindow(FALSE);
	} 
	else {
		_ASSERTE(-1 != m_iUnitOfLength);
		CButton(GetDlgItem(IDC_AUTO_SELECT)).SetCheck(0);
		CButton(GetDlgItem(IDC_SELECT_UNITS)).SetCheck(1);

		_ASSERTE(0 <= m_iUnitOfArea && m_iUnitOfArea < MAX_UNIT_OF_AREA);
		_ASSERTE(0 <= m_iUnitOfLength && m_iUnitOfLength < MAX_UNIT_OF_LENGTH);
		m_cbUnitsOfArea.SetCurSel(m_iUnitOfArea);
		m_cbUnitsOfLength.SetCurSel(m_iUnitOfLength);

		m_cbAppendUnits.SetCheck(m_fAppendUnits ? 1 : 0);
	}
	return TRUE; 
}

void CUnitsOfMeasureDlg::OnAutoSelect(UINT wNotifyCode, int iCtrlId, HWND hCtrl) 
{
	if (m_cbUnitsOfArea.IsWindowEnabled()) 
		m_iUnitOfArea = m_cbUnitsOfArea.GetCurSel();
	m_cbUnitsOfArea.SetCurSel(-1);
	m_cbUnitsOfArea.EnableWindow(FALSE);
	m_ftStaticArea.EnableWindow(FALSE);

	if (m_cbUnitsOfLength.IsWindowEnabled()) 
		m_iUnitOfLength = m_cbUnitsOfLength.GetCurSel();
	m_cbUnitsOfLength.SetCurSel(-1);
	m_cbUnitsOfLength.EnableWindow(FALSE);
	m_ftStaticLength.EnableWindow(FALSE);

	if (m_cbAppendUnits.IsWindowEnabled())
		m_fAppendUnits = m_cbAppendUnits.GetCheck() ? true : false;
	m_cbAppendUnits.SetCheck(1);
	m_cbAppendUnits.EnableWindow(FALSE);

	SetModified(TRUE);
}

void CUnitsOfMeasureDlg::OnSelectUnit(UINT wNotifyCode, int iCtrlId, HWND hCtrl) 
{	
	m_cbUnitsOfArea.EnableWindow(TRUE);
	m_cbUnitsOfLength.EnableWindow(TRUE);
	m_ftStaticArea.EnableWindow(TRUE);
	m_ftStaticLength.EnableWindow(TRUE);
	m_cbAppendUnits.EnableWindow(TRUE);

	m_cbUnitsOfArea.SetCurSel(-1 != m_iUnitOfArea ? m_iUnitOfArea : UNIT_METER);
	m_cbUnitsOfLength.SetCurSel(-1 != m_iUnitOfLength ? m_iUnitOfLength : UNIT_SQUARE_METER);
	m_cbAppendUnits.SetCheck(m_fAppendUnits ? 1 : 0);

	SetModified(TRUE);
}

BOOL CUnitsOfMeasureDlg::OnApply() 
{
	if (m_cbUnitsOfLength.IsWindowEnabled())
		m_iUnitOfLength = m_cbUnitsOfLength.GetCurSel();
	else
		m_iUnitOfLength = -1;

	if (m_cbUnitsOfArea.IsWindowEnabled())
		m_iUnitOfArea = m_cbUnitsOfArea.GetCurSel();
	else
		m_iUnitOfArea = -1;

	if (m_cbUnitsOfArea.IsWindowEnabled())
		m_fAppendUnits = m_cbAppendUnits.GetCheck() ? true : false;
	else
		m_fAppendUnits = true;

	((CStatist *)g_pTE) -> SetUnitOfArea (m_iUnitOfArea);
	((CStatist *)g_pTE) -> SetUnitOfLength (m_iUnitOfLength);
	((CStatist *)g_pTE) -> SetAppendUnits (m_fAppendUnits, true);

	SetModified(FALSE);
	return CPropertyPageImpl<CUnitsOfMeasureDlg>::OnApply();
}

void CUnitsOfMeasureDlg::OnSelchangeUnitOfArea(UINT wNotifyCode, int iCtrlId, HWND hCtrl) 
{
	SetModified(TRUE);
}

void CUnitsOfMeasureDlg::OnSelchangeUnitOfLength(UINT wNotifyCode, int iCtrlId, HWND hCtrl) 
{
	SetModified(TRUE);
}

void CUnitsOfMeasureDlg::OnAppendunits(UINT wNotifyCode, int iCtrlId, HWND hCtrl) 
{
	SetModified(TRUE);
}

