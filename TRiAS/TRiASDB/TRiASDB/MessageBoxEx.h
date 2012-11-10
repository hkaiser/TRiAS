// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 11.01.2001 22:37:57 
//
// @doc
// @module MessageBoxEx.h | Declaration of the <c CMessageBoxEx> class

#if !defined(_MESSAGEBOXEX_H__EE5D6F55_2E4C_4896_8EC5_47B5C8B618AF__INCLUDED_)
#define _MESSAGEBOXEX_H__EE5D6F55_2E4C_4896_8EC5_47B5C8B618AF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CMessageBoxEx dialog

class CMessageBoxEx : public CDialog
{
// Construction
public:
	CMessageBoxEx(LPCSTR pcPrompt, LPCSTR pcCaption, bool fHasCancel = false, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMessageBoxEx)
	enum { IDD = IDD_MESSAGEBOXEX };
	CStatic	m_PromptStatic;
	CEdit	m_Prompt;
	//}}AFX_DATA
	enum { IDDCANCEL = IDD_MESSAGEBOXEXCANCEL };
	CString m_strCaption;
	CString m_strPrompt;
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessageBoxEx)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	int Show() { return DoModal(); }

// Implementation
protected:
	bool MoveButton (UINT uiId, int iDelta);

	// Generated message map functions
	//{{AFX_MSG(CMessageBoxEx)
	afx_msg void OnYes();
	afx_msg void OnYesall();
	afx_msg void OnNo();
	afx_msg void OnNoall();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_MESSAGEBOXEX_H__EE5D6F55_2E4C_4896_8EC5_47B5C8B618AF__INCLUDED_)
