// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 30.07.2000 20:24:06
//
// @doc
// @module DeleteAttributesDlg.h | Declaration of the <c CDeleteAttributesDlg> class

#if !defined(__DELETEATTRIBUTESDLG_H_)
#define __DELETEATTRIBUTESDLG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDeleteAttributesDlg dialog

class CDeleteAttributesDlg : 
	public CPropertyPage
{
	DECLARE_DYNCREATE(CDeleteAttributesDlg)

// Construction
public:
	CDeleteAttributesDlg();
	~CDeleteAttributesDlg();

// Dialog Data
	//{{AFX_DATA(CDeleteAttributesDlg)
	enum { IDD = IDD_DELETEATTRIBUTES_OPTIONS };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDeleteAttributesDlg)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	static CDeleteAttributesDlg *CreateInstance (LPCSTR pcCaption);

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDeleteAttributesDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void AdjustSheetButtons();
	BOOL GetDisableNextPage();

private:
	DWORD m_dwFlags;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__DELETEATTRIBUTESDLG_H_)
