// $Header: $
// Copyright© 1999-2001 VNS GmbH Potsdam, All rights reserved
// Created: 04.12.2002 09:44:34
//
// @doc
// @module CCodeStatDlg.h | Declaration of the <c CCCodeStatDlg> class

#if !defined(__CCODESTATDLG_H_)
#define __CCODESTATDLG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCCodeStatDlg dialog

class CCCodeStatDlg : 
	public CPropertyPage

{
	DECLARE_DYNCREATE(CCCodeStatDlg)

// Construction
public:
	CCCodeStatDlg();
	~CCCodeStatDlg();

// Dialog Data
	//{{AFX_DATA(CCCodeStatDlg)
	enum { IDD = IDD_CCODESTAT_OPTIONS };
	CButton	m_btnNoKey;
	CButton	m_btnSyntax;
	CButton	m_btnDuplicateKey;
	CButton	m_btnOtherFeature;
	CButton	m_btnDuplGeometry;
	CButton	m_btnMultiGeometry;
	CButton m_btnUND;
	CButton m_btnODER;

	CButton m_btnErrorStatist;

	CEdit m_nTextLink;
	CEdit m_nTextError;
	CEdit m_nTextOriginal;
	CEdit m_nTextHelp;
	CString m_nDescription;

	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCCodeStatDlg)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	static CCCodeStatDlg *CreateInstance (LPCSTR pcCaption);

	void OnSetButton(void);
	void OnSetErrorCode(void);
	void SetInformation(void);

	int bNoKey(void) { return m_bNoKey; }
	int bSyntax(void) { return m_bSyntax; }
	int bDuplicateKey(void) { return m_bDuplicateKey; }
	int bOtherFeature(void) { return m_bOtherFeature; }
	int bDuplGeometry(void) { return m_bDuplGeometry; }
	int bMultiGeometry(void) { return m_bMultiGeometry; }
	int bErrorStatist(void) { return m_bErrorStatist; }
	int bShowErrors(void) { return m_bShowErrors; }
	int GetErrorCode(void) { return m_iErrorCode; }
	int UND(void) { return m_bUND; }
	STDMETHODIMP SetConfigData (CComBSTR strLink,CComBSTR strOriginal,CComBSTR strError, bool bUseAll,bool bShowErrors);


// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCCodeStatDlg)
	afx_msg void OnNokey();
	afx_msg void OnSyntaxerror();
	afx_msg void OnDuplicatekey();
	afx_msg void OnOtherfeature();
	afx_msg void OnDuplgeometry();
	afx_msg void OnMultigeometry();
	afx_msg void OnUndverknuepfung();
	afx_msg void OnOderverknuepfung();
	afx_msg void OnErrorstatist();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void AdjustSheetButtons();
	BOOL GetDisableNextPage();

private:
	DWORD m_dwFlags;

	CComBSTR m_bstrGCO;
	CComBSTR m_bstrGCOriginal;
	CComBSTR m_bstrError;

	int m_iErrorCode;
	int m_bNoKey;
	int m_bSyntax;
	int m_bDuplicateKey;
	int m_bOtherFeature;
	int m_bDuplGeometry;
	int m_bMultiGeometry;

	int m_bErrorStatist;
	int m_bShowErrors;

	int m_bUND;
	int m_bODER;

	bool m_bUseAll;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__CCODESTATDLG_H_)
