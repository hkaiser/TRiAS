// CopyDLKWDlg.h : header file
//

#if !defined(AFX_COPYDLKWDLG_H__1149A4E2_7503_4670_9AF7_A307F4F20D0D__INCLUDED_)
#define AFX_COPYDLKWDLG_H__1149A4E2_7503_4670_9AF7_A307F4F20D0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DDXGetFolder.h"
#include "CopyDLKThread.h"

class CCopyDLKWDlgAutoProxy;

/////////////////////////////////////////////////////////////////////////////
// CCopyDLKWDlg dialog

class CCopyDLKWDlg : public CDialog
{
	DECLARE_DYNAMIC(CCopyDLKWDlg);
	friend class CCopyDLKWDlgAutoProxy;

// Construction
public:
	CCopyDLKWDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CCopyDLKWDlg();

// Dialog Data
	//{{AFX_DATA(CCopyDLKWDlg)
	enum { IDD = IDD_COPYDLKW_DIALOG };
	CProgressCtrl	m_Status;
	CButton	m_pbClose;
	CButton	m_pbAction;
	CString	m_strDestPath;
	CString	m_strSourcePath;
	CString	m_strPrompt;
	//}}AFX_DATA

	CGetFolderControl	m_sleSourcePath;
	CGetFolderControl	m_sleDestPath;

	CCopyDLKThread m_threadCopy;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCopyDLKWDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CCopyDLKWDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	//{{AFX_MSG(CCopyDLKWDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnStop();
	afx_msg void OnChangeDestinationdir();
	afx_msg void OnChangeSourcedir();
	afx_msg void OnCloseApp();
	afx_msg LRESULT OnThreadCallback(WPARAM, LPARAM);
	afx_msg LRESULT OnCopyDLKStatus(WPARAM, LPARAM);
	afx_msg LRESULT OnCopyError(WPARAM, LPARAM);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void AdjustOK();

private:
	int m_iMinRange;
	int m_iMaxRange;

	CCopyData m_CopyData;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COPYDLKWDLG_H__1149A4E2_7503_4670_9AF7_A307F4F20D0D__INCLUDED_)
