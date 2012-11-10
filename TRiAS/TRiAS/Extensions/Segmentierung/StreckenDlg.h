// $Header: $
// Copyright© 1999-2001 Geopunkt GmbH Potsdam, All rights reserved
// Created: 19.07.2002 09:47:45
//
// @doc
// @module StreckenDlg.h | Declaration of the <c CStreckenDlg> class

#if !defined(__STRECKENDLG_H_)
#define __STRECKENDLG_H_


#import "TRiASCS.tlb" raw_interfaces_only raw_dispinterfaces no_implementation \
	no_namespace named_guids


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CStreckenDlg dialog

class CStreckenDlg : 
	public CPropertyPage
{
	DECLARE_DYNCREATE(CStreckenDlg)

// Construction
public:
	CStreckenDlg();
	~CStreckenDlg();

// Dialog Data
	//{{AFX_DATA(CStreckenDlg)
	enum { IDD = IDD_STRECKEN_OPTIONS };
	CButton	m_btnKnoten;
//	CButton	m_btnKanten;
	CComboBoxEx	m_cbDataSources;
	CEdit m_nText;
	CString m_nDescription;


		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CStreckenDlg)
	public:
	virtual BOOL OnWizardFinish();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	static CStreckenDlg *CreateInstance (LPCSTR pcCaption);

	int bKnoten(void) { return m_bKnoten; }
	int bKanten(void) { return m_bKanten; }
	HPROJECT bProjectHandle(void) { return m_hPr; }

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CStreckenDlg)
		// NOTE: the ClassWizard will add member functions here
		virtual BOOL OnInitDialog();
		afx_msg void OnKnoten();
//		afx_msg void OnKanten();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void AdjustSheetButtons();
	BOOL GetDisableNextPage();
	BOOL FillDataSources();

private:
	DWORD m_dwFlags;

	int	m_bKnoten;	// Knoten bilden
	int	m_bKanten;	// Kanten bilden

	HPROJECT m_hPr;	// ProjectHandle

	CImageList m_ilImages;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__STRECKENDLG_H_)
