/*
Module : DDXGETFILE.H
Purpose: Defines the interface to a for a MFC DDX_ routine to get a filename
         Using the file open/save as common dialogs
Created: PJN / DDXGETFILE/1 / 19-03-1997
History: None

Copyright (c) 1997 by PJ Naughter.  
All rights reserved.

*/

///////////////////////////////////////////////////////////////////////////////
// Macros 
#ifndef _DDXGETFILE_H__
#define _DDXGETFILE_H__

#include <ospace/std/set>

///////////////////////////////////////////////////////////////////////////////
// Consts 
// flags used to control how the DDX_GetFilenameControl routine works
const DWORD GF_OVERWRITEPROMPT  = 0x0001;   //User will be prompted about overwriting existing file 
                                            //prior to allowing selection
const DWORD GF_FILEMUSTEXIST    = 0x0002;   //File must exist to be selected
const DWORD GF_OLD_STYLE_DIALOG = 0x0004;   //Use the old style file open dialog instead of the
                                            //style as used in Windows Explorer
const DWORD GF_HIDEREADONLY     = 0x0008;   //Hide Readonly Checkbox
const DWORD GF_SAVEASDIALOG		= 0x0010;	// show SaveAsDialog
const DWORD GF_MULTIPLESELECTION = 0x0020;	// MultiSel

const UINT WM_FILESELECTED		= WM_USER+1000;		// Notification

///////////////////////////////////////////////////////////////////////////////
// foward declaration 
class CGetFilenameControl;

///////////////////////////////////////////////////////////////////////////////
// Classes 
class CModifyButton : public CButton
{
public:
  CModifyButton();
  void SetBuddy(CGetFilenameControl* pBuddy);
	void Reset();

protected:
  //{{AFX_VIRTUAL(CModifyButton)
  public:
  virtual BOOL PreTranslateMessage(MSG* pMsg);
  //}}AFX_VIRTUAL

  //{{AFX_MSG(CModifyButton)
  afx_msg void OnClicked();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP()

  CGetFilenameControl* m_pBuddy;
  BOOL m_bFirstCall;
	BOOL m_fTTCreated;
  CToolTipCtrl m_ToolTip;
};

class CGetFileNameDialog : public CFileDialog
{
	DECLARE_DYNAMIC(CGetFileNameDialog)

public:
	CGetFileNameDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt = NULL, LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,	LPCTSTR lpszFilter = NULL, CWnd* pParentWnd = NULL);

protected:
  virtual void OnInitDone();
  virtual BOOL OnFileNameOK();

	//{{AFX_MSG(CGetFileNameDialog)
	//}}AFX_MSG
  virtual BOOL OnInitDialog();
  virtual void OnOK();

	DECLARE_MESSAGE_MAP()
};

class CGetFilenameControl : 
	public CStatic
{
public:
	CGetFilenameControl();

	BOOL SubclassEdit(HWND hEdit);
	void SetFlags(DWORD dwFlags, const CString& sTitle, const CString& sExtFilter, const CString& sDefExt, const CString &sDir);
	void Edit(BOOL fShowDlg = TRUE);
	BOOL Reset (void);

	BOOL GetReadOnly() { return m_fReadOnly; }
	int GetCount() { return m_iCnt; }
	CFiles &GetFiles() { return m_Files; }

protected:
  //{{AFX_VIRTUAL(CGetFilenameControl)
  //}}AFX_VIRTUAL

  //{{AFX_MSG(CGetFilenameControl)
  //}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	BOOL AddEditButton();
	BOOL RemoveEditButton();
	CString GetPathName(CGetFileNameDialog &rDlg);

	CModifyButton m_Edit;
	DWORD m_dwFlags;
	CString m_sTitle;
	CString	m_sExtFilter;
	CString	m_sDefExt;
	CString	m_sDir;
	BOOL m_fReadOnly;
	
public:
	int m_iCnt;			// Anzahl der selektierten Dateien
	CFiles m_Files;
};

///////////////////////////////////////////////////////////////////////////////
// MFC Data exchange routines 
void DDX_GetFilenameControl(CDataExchange* pDX, int nIDC, CGetFilenameControl& rCGetFilenameControl, DWORD dwFlags, const CString& sTitle, const CString& sExtFilter, const CString& sDefExt, const CString &sDir);

#endif //_GETFILE_H__