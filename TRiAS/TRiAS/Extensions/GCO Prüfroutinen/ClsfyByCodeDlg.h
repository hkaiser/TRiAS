// $Header: $
// Copyright© 1999-2001 VNS GmbH Potsdam, All rights reserved
// Created: 28.01.2003 11:54:08
//
// @doc
// @module ClsfyByCodeDlg.h | Declaration of the <c CClsfyByCodeDlg> class

#if !defined(__CLSFYBYCODEDLG_H_)
#define __CLSFYBYCODEDLG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CClsfyByCodeDlg dialog

class CClsfyByCodeDlg : 
	public CPropertyPage
{
	DECLARE_DYNCREATE(CClsfyByCodeDlg)

// Construction
public:
	CClsfyByCodeDlg();
	~CClsfyByCodeDlg();

// Dialog Data
	//{{AFX_DATA(CClsfyByCodeDlg)
	enum { IDD = IDD_CLSFYBYCODE_OPTIONS };
	CButton	m_btnAreaCtrl;
	CButton	m_btnLineCtrl;

	CEdit m_nTextLink;
	CEdit m_nTextHelp;
	CEdit m_nCaption;
	CString m_nDescription;
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CClsfyByCodeDlg)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	static CClsfyByCodeDlg *CreateInstance (LPCSTR pcCaption);

	int GetAreaCode(void) { return m_iAreaCtrl; }
	void SetInformation(void);
	STDMETHODIMP SetConfigData (CComBSTR strLink, int iIndex);


// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CClsfyByCodeDlg)
	afx_msg void OnAreaConstruction();
	afx_msg void OnLineConstructiomn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void AdjustSheetButtons();
	BOOL GetDisableNextPage();

private:
	DWORD m_dwFlags;
	int m_iAreaCtrl;
	int m_iListIndex;


	CComBSTR m_bstrCheckFeature;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__CLSFYBYCODEDLG_H_)
