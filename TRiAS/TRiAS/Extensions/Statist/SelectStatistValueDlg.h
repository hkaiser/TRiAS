// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 29.08.99 21:21:16 
//
// @doc
// @module SelectStatistValueDlg.h | Declaration of the <c CSelectStatistValueDlg> class

#if !defined(__SELECTSTATISTVALUEDLG_H_)
#define __SELECTSTATISTVALUEDLG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Com/ComBool.h>

#include "resource.h"       // main symbols
#include "Separator.h"

/////////////////////////////////////////////////////////////////////////////
// CSelectStatistValueDlg dialog

class CSelectStatistValueDlg : 
	public CAxPropertyPageImpl<CSelectStatistValueDlg>,
	public IDispEventImpl<IDC_OBJPROPTREE, CSelectStatistValueDlg>,
	public IDispEventImpl<IDC_STATISTPROPTREE, CSelectStatistValueDlg>
{
// Construction
public:
	CSelectStatistValueDlg(LPCSTR pcCaption);
	~CSelectStatistValueDlg();

// Dialog Data
	enum { IDD = IDD_SELECTSTATISTVALUE_OPTIONS };

	BEGIN_MSG_MAP_EX(CSelectStatistValueDlg)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_DESTROY(OnDestroy)
		COMMAND_HANDLER_EX(IDC_EVALRELATION, BN_CLICKED, OnEvalRelation)
		CHAIN_MSG_MAP(CAxPropertyPageImpl<CSelectStatistValueDlg>)
	END_MSG_MAP()

	BOOL OnSetActive();
	int OnWizardNext();
	BOOL OnWizardFinish();

	BEGIN_SINK_MAP(CSelectStatistValueDlg)
		SINK_ENTRY(IDC_OBJPROPTREE, 1, OnObjPropSelected)
		SINK_ENTRY(IDC_STATISTPROPTREE, 1, OnStatFuncSelected)
	END_SINK_MAP()

	void __stdcall OnObjPropSelected()
	{
	CComBool fHasSel;

		_ASSERTE(m_ObjPropTree.IsValid());
		if (SUCCEEDED(m_ObjPropTree -> get_HasSelection(&fHasSel)) && bool(fHasSel)) {
			m_strObjProp.remove();
			if (SUCCEEDED(m_ObjPropTree -> get_Selection(__uuidof(IObjectProperty), m_ObjProp.ppu()))) {
			char cbBuffer[_MAX_PATH];

				if (SUCCEEDED(m_ObjProp -> GetPropInfo(cbBuffer, sizeof(cbBuffer), NULL)))
					m_strObjProp = cbBuffer;
			} 
		}
		AdjustSheetButtons();
	}
	void __stdcall OnStatFuncSelected()
	{
	CComBool fHasSel;

		_ASSERTE(m_StatFuncTree.IsValid());
		if (SUCCEEDED(m_StatFuncTree -> get_HasSelection(&fHasSel)) && bool(fHasSel)) {
			m_strStatFunc.remove();
			if (SUCCEEDED(m_StatFuncTree -> get_Selection(__uuidof(IGenericStatistics), m_StatFunc.ppu()))) {
			CComBSTR bstrName;

				if (SUCCEEDED(m_StatFunc -> get_Name(&bstrName))) {
					USES_CONVERSION;
					m_strStatFunc = OLE2A(bstrName);
				}
			}
		}
		AdjustSheetButtons();
	}

public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	static CSelectStatistValueDlg *CreateInstance (LPCSTR pcCaption);

	const os_string &GetSelectedStatFuncName() const { return m_strStatFunc; }
	const os_string &GetSelectedObjPropName() const { return m_strObjProp; }
	IObjectProperty *GetObjProp() { return m_ObjProp; }
	IGenericStatistics *GetStatFunc() { return m_StatFunc; }

	bool GetEvalRelation() { return m_fEvalRelation; }
	bool GetInvertValue() { return m_fInvertValue; }

	void SetInitData (LPCSTR pcObjProp, LPCSTR pcStatFunc, bool fEvalRelation, bool fInvertValue)
	{
		m_strObjProp = pcObjProp;
		if (m_fIsInitialized && !m_strObjProp.empty()) {
			_ASSERTE(m_ObjPropTree.IsValid());
			m_ObjPropTree -> SetSelection(CComBSTR(m_strObjProp.c_str()));
		}
		m_strStatFunc = pcStatFunc;
		if (m_fIsInitialized && !m_strStatFunc.empty()) {
			_ASSERTE(m_StatFuncTree.IsValid());
			m_StatFuncTree -> SetSelection(CComBSTR(m_strStatFunc.c_str()));
		}
		m_fEvalRelation = fEvalRelation;
		m_fInvertValue = fInvertValue;

		if (m_fIsInitialized) {
			m_cbCalcRelation.SetCheck(m_fEvalRelation ? 1 : 0);
			m_cbInvertValue.SetCheck(m_fInvertValue ? 1 : 0);
			m_cbInvertValue.EnableWindow(m_fEvalRelation);
		}
	}

// Implementation
protected:
	LRESULT OnInitDialog(HWND hWnd, LPARAM lParam);
	void OnDestroy();
	void OnEvalRelation(UINT wNotifyCode, int iCtrlId, HWND hCtrl);

	void AdjustSheetButtons();
	BOOL GetDisableNextPage();

private:
	CSeparator m_Delimiter;
	CSeparator m_Options;
	CButton m_cbCalcRelation;
	CButton m_cbInvertValue;

	DWORD m_dwFlags;

	WPopupTree m_ObjPropTree;
	WPopupTree m_StatFuncTree;

	WObjectProperty m_ObjProp;
	WGenericStatistics m_StatFunc;

	os_string m_strObjProp;
	os_string m_strStatFunc;
	bool m_fEvalRelation;
	bool m_fInvertValue;
	bool m_fIsInitialized;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__SELECTSTATISTVALUEDLG_H_)
