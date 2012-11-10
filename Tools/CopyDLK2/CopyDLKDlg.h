// CopyDLKDlg.h : header file
//

#if !defined(AFX_COPYDLKDLG_H__85F0743D_4BFA_4FCA_80C2_ABB1FBA35195__INCLUDED_)
#define AFX_COPYDLKDLG_H__85F0743D_4BFA_4FCA_80C2_ABB1FBA35195__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCopyDLKDlgAutoProxy;

#include "Separator.h"
#include "DDXGetFolder.h"
#include "DDXGetFile.h"
#include "CopyDLK2Thread.h"
#include "FilesToCopyTree.h"
#include "Inventory.h"
#include "DlkList.h"
#include "DestList.h"

///////////////////////////////////////////////////////////////////////////////
//  
#define UPDATE_INVENTORY        0x1
#define UPDATE_DLKLIST          0x2
#define UPDATE_DESTLIST         0x4
#define UPDATE_ALL              0x7

/////////////////////////////////////////////////////////////////////////////
// CCopyDLKDlg dialog

class CCopyDLKDlg : public CDialog
{
	DECLARE_DYNAMIC(CCopyDLKDlg);
	friend class CCopyDLKDlgAutoProxy;

// Construction
public:
	CCopyDLKDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CCopyDLKDlg();

// Dialog Data
	//{{AFX_DATA(CCopyDLKDlg)
	enum { IDD = IDD_COPYDLK2_DIALOG };
	CProgressCtrl	m_Status;
	CSeparator	m_Parameters;
	CSeparator	m_SourceData;
	CString	m_strSourcePath;
	CString	m_strDestPath;
	CString	m_strFilesToCopy;
	CString	m_strInventarFile;
	CString	m_strPrompt;
    CFilesToCopyTree m_FilesToCopy;
    CButton m_pbAction;
    CButton m_pbClose;
    CButton m_cbSkipExisting;
	//}}AFX_DATA
    
	CGetFolderControl	m_sleSourcePath;
	CGetFolderControl	m_sleDestPath;
	CGetFilenameControl m_sleInventar;
	CGetFilenameControl m_sleFileList;
	 
	CCopyDLK2Thread m_threadCopy;
    CMapInventory m_Inventory;
    CDlkList m_DlkList;
    CDestList m_DestList;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCopyDLKDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CCopyDLKDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	//{{AFX_MSG(CCopyDLKDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnStop();
	virtual void OnOK();
	virtual void OnCancel();
    afx_msg void OnBnClickedCopy();
	afx_msg LRESULT OnThreadCallback(WPARAM, LPARAM);
	afx_msg LRESULT OnCopyDLKStatus(WPARAM, LPARAM);
	afx_msg LRESULT OnCopyError(WPARAM, LPARAM);
	afx_msg LRESULT OnFileCopied(WPARAM, LPARAM);
    afx_msg void OnBnClickedClipboard();
    afx_msg void OnBnClickedSkipexisting();
    afx_msg LRESULT OnDirSelected(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnFileSelected(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
    
	DECLARE_MESSAGE_MAP()

protected:
    void ReadDataFromRegistry();
    void WriteDataToRegistry();
    BOOL FillFilesToCopy(BOOL fUpdateData = TRUE, DWORD dwUpdate = UPDATE_ALL);
    void AdjustOK();

    BOOL LoadInventory(BOOL fUpdateData, CMapInventory &rmapInventory);
    BOOL LoadDlkList(BOOL fUpdateData);
    BOOL LoadDestDir(BOOL fUpdateData, CDestList &rmapDestList);
    
private:
	int m_iMinRange;
	int m_iMaxRange;
	CCopyData m_CopyData;
	bool m_fSkipExisting;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COPYDLKDLG_H__85F0743D_4BFA_4FCA_80C2_ABB1FBA35195__INCLUDED_)
