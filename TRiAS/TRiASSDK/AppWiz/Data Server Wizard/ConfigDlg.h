// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 11.01.2000 22:43:46 
//
// @doc
// @module ConfigDlg.h | Declaration of the <c CConfigDlg> class

#if !defined(AFX_CONFIGDLG_H__69787412_8186_43B4_AF07_BE0DBB599A20__INCLUDED_)
#define AFX_CONFIGDLG_H__69787412_8186_43B4_AF07_BE0DBB599A20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog

class CConfigDlg : public CAppWizStepDlg
{
// Construction
public:
	CConfigDlg();   // standard constructor
	virtual BOOL OnDismiss();

// Dialog Data
	//{{AFX_DATA(CConfigDlg)
	enum { IDD = IDD_CONFIG };
	CStatic	m_FileExt;
	CString	m_Name;
	CString	m_EditFileExt;
	int		m_AccessMode;
	int		m_AccessType;
	BOOL	m_fEmitSampleCode;
	//}}AFX_DATA

public:
	void UpdateTitle(const CString& strRoot);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetSeqBitmap();

	// Generated message map functions
	//{{AFX_MSG(CConfigDlg)
	afx_msg void OnClickedAccessMode(UINT nID);
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	UINT m_nSeqBitmap;      // IDB_ of bitmap to show
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGDLG_H__69787412_8186_43B4_AF07_BE0DBB599A20__INCLUDED_)
