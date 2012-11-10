// $Header: $
// Copyright© 1999-2001 VNS GmbH Potsdam, All rights reserved
// Created: 27.01.2003 08:38:45
//
// @doc
// @module CodeLineDlg.h | Declaration of the <c CCodeLineDlg> class

#if !defined(__CODELINEDLG_H_)
#define __CODELINEDLG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCodeLineDlg dialog

class CCodeLineDlg : 
	public CPropertyPage
{
	DECLARE_DYNCREATE(CCodeLineDlg)

// Construction
public:
	CCodeLineDlg();
	~CCodeLineDlg();

// Dialog Data
	//{{AFX_DATA(CCodeLineDlg)
	enum { IDD = IDD_CODELINE_OPTIONS };
	CButton	m_btnNotCtrl;
	CButton	m_btnFeature;
	CButton	m_btnIntern;

	CEdit m_nTextLink;
	CEdit m_nTextHelp;
	CString m_nDescription;

		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCodeLineDlg)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	static CCodeLineDlg *CreateInstance (LPCSTR pcCaption);

	void SetInformation(void);

	int GetErrorCode(void) { return m_iErrorCode; }
	STDMETHODIMP SetConfigData (CComBSTR strLink);

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCodeLineDlg)
	afx_msg void OnCheckfirstctrl();
	afx_msg void OnCheckfeature();
	afx_msg void OnCheckintern();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void AdjustSheetButtons();
	BOOL GetDisableNextPage();

private:
	DWORD m_dwFlags;

	int m_iNotCtrl;
	int m_iFeature;
	int m_iIntern;

	int m_iErrorCode;
	CComBSTR m_bstrCheckFeature;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__CODELINEDLG_H_)
