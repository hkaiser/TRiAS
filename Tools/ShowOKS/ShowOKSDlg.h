// ShowOKSDlg.h : header file
//

#if !defined(AFX_SHOWOKSDLG_H__0AC131D9_C5EF_11D0_9595_00A024D6F582__INCLUDED_)
#define AFX_SHOWOKSDLG_H__0AC131D9_C5EF_11D0_9595_00A024D6F582__INCLUDED_

#include "OksTreeCtrl.h"	// Added by ClassView

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CShowOKSDlg dialog

class CShowOKSDlg : public CDialog
{
// Construction
public:
	CShowOKSDlg(CWnd* pParent = NULL);	// standard constructor
	 ~CShowOKSDlg();

// Dialog Data
	//{{AFX_DATA(CShowOKSDlg)
	enum { IDD = IDD_SHOWOKS_DIALOG };
	COksTreeCtrl	m_OKSList;
	CString	m_strGenText;
	CString	m_strGenCode;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowOKSDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CShowOKSDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpenfile();
	afx_msg void OnSelchangedOkstree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnCheckStateChangedOkstree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSavecompiled();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void UpdateText (void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWOKSDLG_H__0AC131D9_C5EF_11D0_9595_00A024D6F582__INCLUDED_)
