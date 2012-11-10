// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 09.06.99 08:50:03 
//
// @doc
// @module NotifBar.h | Declaration of the <c CNotifBar> class

#if !defined(AFX_NOTIFBAR_H__23F4BDE0_1E37_11D3_94ED_0080C786297B__INCLUDED_)
#define AFX_NOTIFBAR_H__23F4BDE0_1E37_11D3_94ED_0080C786297B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CNotifBar dialog

class CNotifBar : 
	public CDialogBar
{
// Construction
public:
// Overrides
	BOOL Create (CWnd*);
	BOOL OnSelChange (CString &strType, CString &strDecl, CString &strName, CString &strParams, CString &strComment);
	BOOL OnDestroy (void);
	BOOL GetItems (CString &strType, CString &strDecl, CString &strName, CString &strParams, CString &strComment);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNotifBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNotifBar)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	afx_msg bool OnToolTipText(UINT uiID, NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()

private:	
	HRESULT FillCombo	(void);
	HRESULT SetTemplatePieces(void);

	CString	m_strType;
	CString	m_strParams;
	CString m_strDeclaration;
	CString m_strName;
	CString m_strComment;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTIFBAR_H__23F4BDE0_1E37_11D3_94ED_0080C786297B__INCLUDED_)
