// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 22.12.2000 16:45:03 
//
// @doc
// @module UnitsOfMeasureDlg.h | Declaration of the <c CUnitsOfMeasureDlg> class

#if !defined(_UNITSOFMEASUREDLG_H__3D6E9AB6_88ED_4218_90F9_517291BCEFB1__INCLUDED_)
#define _UNITSOFMEASUREDLG_H__3D6E9AB6_88ED_4218_90F9_517291BCEFB1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "Separator.h"

/////////////////////////////////////////////////////////////////////////////
// synchronize the following with DLGINIT data

enum UNITOFLENGTH {
	UoL_Unknown = -2,
	UoL_BestFit = -1,
	UoL_CentiMeter = 0,
	UoL_DeciMeter = 1,
	UoL_Meter = 2,
	UoL_KiloMeter = 3,
};
const int MAX_UNIT_OF_LENGTH = UoL_KiloMeter+1;
const int UNIT_METER = UoL_Meter;

enum UNITOFAREA {
	UoA_Unknown = -2,
	UoA_BestFit = -1,
	UoA_SquareCentiMeter = 0,
	UoA_SquareDeciMeter = 1,
	UoA_SquareMeter = 2,
	UoA_Hektar = 3,
	UoA_SquareKiloMeter = 4,
};

const int MAX_UNIT_OF_AREA = UoA_SquareKiloMeter+1;
const int UNIT_SQUARE_METER = UoA_SquareMeter;

///////////////////////////////////////////////////////////////////////////////
// CUnitsOfMeasureDlg dialog
class CUnitsOfMeasureDlg : 
	public CPropertyPageImpl<CUnitsOfMeasureDlg>
//	public CWinDataExchange<CUnitsOfMeasureDlg>
{
// Construction
public:
	CUnitsOfMeasureDlg();
	~CUnitsOfMeasureDlg();

// Dialog Data
	enum { IDD = IDD_UNITSOFMEASURE };
	CStatic	m_ftStaticLength;
	CStatic	m_ftStaticArea;
	CButton	m_cbAppendUnits;
	CComboBox	m_cbUnitsOfLength;
	CComboBox	m_cbUnitsOfArea;
	CSeparator	m_StaticOptions;
	CSeparator	m_StaticLength;
	CSeparator	m_StaticDesc;

	BEGIN_MSG_MAP_EX(CUnitsOfMeasureDlg)
		MSG_WM_INITDIALOG(OnInitDialog)
		COMMAND_HANDLER_EX(IDC_AUTO_SELECT, BN_CLICKED, OnAutoSelect)
		COMMAND_HANDLER_EX(IDC_SELECT_UNITS, BN_CLICKED, OnSelectUnit)
		COMMAND_HANDLER_EX(IDC_UNIT_OF_AREA, CBN_SELCHANGE, OnSelchangeUnitOfArea)
		COMMAND_HANDLER_EX(IDC_UNIT_OF_LENGTH, CBN_SELCHANGE, OnSelchangeUnitOfLength)
		COMMAND_ID_HANDLER_EX(IDC_APPENDUNITS, OnAppendunits)

		CHAIN_MSG_MAP(CPropertyPageImpl<CUnitsOfMeasureDlg>)
	END_MSG_MAP()

	BOOL OnApply();

// Implementation
protected:
	void OnAutoSelect(UINT wNotifyCode, int iCtrlId, HWND hCtrl);
	void OnSelectUnit(UINT wNotifyCode, int iCtrlId, HWND hCtrl);
	void OnAppendunits(UINT wNotifyCode, int iCtrlId, HWND hCtrl);
	LRESULT OnInitDialog(HWND hWnd, LPARAM lParam);
	void OnSelchangeUnitOfArea(UINT wNotifyCode, int iCtrlId, HWND hCtrl);
	void OnSelchangeUnitOfLength(UINT wNotifyCode, int iCtrlId, HWND hCtrl);

	void AdjustButtons();
	BOOL FillComboBox (UINT uiId, CComboBox &rcb);

private:
	int m_iUnitOfLength;
	int m_iUnitOfArea;
	bool m_fAppendUnits;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_UNITSOFMEASUREDLG_H__3D6E9AB6_88ED_4218_90F9_517291BCEFB1__INCLUDED_)
