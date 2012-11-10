// $Header: $
// Copyright© 1999 Fernerkundungszentrum Potsdam GmbH, All rights reserved
//
// @doc
// @module MergeTwoSourcesDlg.h | Declaration of the <c CMergeTwoSourcesDlg> class

#if !defined(__MERGETWOSOURCESDLG_H_)
#define __MERGETWOSOURCESDLG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMergeTwoSourcesDlg dialog

class CMergeTwoSourcesDlg : 
	public CPropertyPage
{
	DECLARE_DYNCREATE(CMergeTwoSourcesDlg)

// Construction
public:
	CMergeTwoSourcesDlg();
	~CMergeTwoSourcesDlg();

// Dialog Data
	//{{AFX_DATA(CMergeTwoSourcesDlg)
	enum { IDD = IDD_MERGETWOSOURCES_OPTIONS };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMergeTwoSourcesDlg)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	static CMergeTwoSourcesDlg *CreateInstance (LPCSTR pcCaption);

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMergeTwoSourcesDlg)
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

#endif // !defined(__MERGETWOSOURCESDLG_H_)
