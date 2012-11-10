// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 25.05.2000 21:27:22 
//
// @doc
// @module PathDialog.h | Declaration of the <c CPathDialog> class

#if !defined(_PATHDIALOG_H__F97D3689_0EEA_4637_B2A9_97811F3C3192__INCLUDED_)
#define _PATHDIALOG_H__F97D3689_0EEA_4637_B2A9_97811F3C3192__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <shlobj.h>

class CPathDialog;

// CPathDialogSub - intercepts messages from child controls
class CPathDialogSub : public CWnd
{
public:
	friend CPathDialog;
	CPathDialog *m_pPathDialog;

protected:
	afx_msg void OnOK();			  // OK button clicked
	afx_msg void OnChangeEditPath();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CPathDialog dialog

class CPathDialog
{
// Construction
public:
	friend CPathDialogSub;
	CPathDialog(BOOL fOpenDlg = TRUE, LPCTSTR lpszCaption = NULL, LPCTSTR lpszTitle = NULL, LPCTSTR lpszInitialPath = NULL, CWnd* pParent = NULL);

	CString GetPathName();
	virtual int DoBrowse();

	static Touch (LPCTSTR lpPath, BOOL bValidate = TRUE);
	static BOOL IsFileNameValid (LPCTSTR lpFileName);
	static int ConcatPath (LPTSTR lpRoot, LPCTSTR lpMorePath);

	BOOL IsOpenDlg() { return m_fOpenDlg; }
	int MakeSurePathExists (LPCTSTR lpPath);

private:
	static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM pData);

	LPCTSTR m_lpszCaption;
	LPCTSTR m_lpszInitialPath;

	TCHAR m_szPathName[MAX_PATH];

	BROWSEINFO m_bi;
	HWND m_hWnd;
	CWnd *m_pParentWnd;
	BOOL m_bParentDisabled;
	BOOL m_bGetSuccess;
	BOOL m_fOpenDlg;

	CPathDialogSub m_PathDialogSub;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_PATHDIALOG_H__F97D3689_0EEA_4637_B2A9_97811F3C3192__INCLUDED_)
