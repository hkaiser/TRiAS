// @doc
// @module AutoListComboBox.h | Declaration of ComboBox with autowidth-dropdownlist

#if !defined(AFX_AUTOLISTCOMBOBOX_H__5CE402C8_D57C_11D2_9BC1_FCB620524153__INCLUDED_)
#define AFX_AUTOLISTCOMBOBOX_H__5CE402C8_D57C_11D2_9BC1_FCB620524153__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAutoListComboBox window

class CAutoListComboBox : public CComboBox
{
// Construction
public:
	CAutoListComboBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoListComboBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAutoListComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAutoListComboBox)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOLISTCOMBOBOX_H__5CE402C8_D57C_11D2_9BC1_FCB620524153__INCLUDED_)
