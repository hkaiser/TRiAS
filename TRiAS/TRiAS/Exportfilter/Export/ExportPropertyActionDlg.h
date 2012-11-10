// $Header: $
// Copyright© 1999 Fernerkundungszentrum Potsdam GmbH, All rights reserved
//
// @doc
// @module ExportPropertyActionDlg.h | Declaration of the <c CExportPropertyActionDlg> class

#if !defined(AFX_EXPORTPROPERTYACTIONDLG_H__908934E0_00B8_11D3_94C8_0080C786297B__INCLUDED_)
#define AFX_EXPORTPROPERTYACTIONDLG_H__908934E0_00B8_11D3_94C8_0080C786297B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma HDR_ON()

/////////////////////////////////////////////////////////////////////////////
// CExportPropertyActionDlg dialog

#include "Separator.h"
#include "StaticFileSpec.h"
#include "SelectObjPropsToExport.h"
#include "SelectCoordSysActionDlg.h"

class CExportPropertyActionDlg : 
	public CPropertyPage 
{
	DECLARE_DYNCREATE(CExportPropertyActionDlg)

	HRESULT	SelectExportfile();
	HRESULT SelectExportCoordsys();
	void RereadControldata();

// Construction
public:
	CExportPropertyActionDlg();
	~CExportPropertyActionDlg();

// Dialog Data
	//{{AFX_DATA(CExportPropertyActionDlg)
	enum { IDD = IDD_EXPORT_OPTIONS };
	CButton	m_btnCoordsys00;
	CButton	m_btnCoordsys;
	CButton	m_btnSeparate;
	CButton	m_btnSelect;
	CComboBox	m_boxOfExportFormats;
	CSeparator	m_SeparateFormat;
	CSeparator	m_SeparateFilename;
	CSeparator	m_SeparateOptions;
	CSeparator	m_SeparateCoordsys;
	CStaticFilespec	m_StaticFilename;
	CStaticFilespec	m_StaticCoordsys;
	CString	m_strFilename;
	BOOL	m_bSeparate;
	BOOL	m_bSelect;
	CString	m_strCoordsys;
	int		m_nSelectedEngine;
	//}}AFX_DATA

	WTRiASExtDataEngine	m_pTRiASExtDataEngine;
	vector<WTRiASExtDataEngine>	m_vecOfEngines;
	CSelectObjPropsToExport *m_pObjPropDlg;
	CSelectCoordSysActionDlg *m_pSelCsDlg;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CExportPropertyActionDlg)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	static CExportPropertyActionDlg* CreateInstance (LPCSTR pcCaption);

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CExportPropertyActionDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectexportfile();
	afx_msg void OnCoordsys();
	afx_msg void OnSelchangeExportformats();
	afx_msg void OnSeparate();
	afx_msg void OnBtnexportcoordsys00();
	afx_msg void OnSelect();
	afx_msg void OnExportobjprops();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void OnSelect(BOOL fUpdate);
	void OnSelchangeExportformats(BOOL fUpdate);
	void OnSeparate(BOOL fUpdate);

	void AdjustControls();
	void AdjustSheetButtons();
	BOOL GetDisableNextPage();

private:
	DWORD m_dwFlags;
};

#pragma HDR_OFF()

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPORTPROPERTYACTIONDLG_H__908934E0_00B8_11D3_94C8_0080C786297B__INCLUDED_)
