// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 02.11.2000 12:48:39 
//
// @doc
// @module MacroIntroDlg.h | Declaration of the <c CMacroIntroDlg> class

#if !defined(_MACROINTRODLG_H__D3B69BE9_5D6E_4E4F_96F9_9A6562728861__INCLUDED_)
#define _MACROINTRODLG_H__D3B69BE9_5D6E_4E4F_96F9_9A6562728861__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

/////////////////////////////////////////////////////////////////////////////
// CMacroIntroDlg dialog

class CMacroIntroDlg : public CDialog
{
// Construction
public:
	CMacroIntroDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMacroIntroDlg)
	enum { IDD = IDD_MACROINTRO };
	BOOL	m_fDoNotShowAnyFurther;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMacroIntroDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMacroIntroDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_MACROINTRODLG_H__D3B69BE9_5D6E_4E4F_96F9_9A6562728861__INCLUDED_)
