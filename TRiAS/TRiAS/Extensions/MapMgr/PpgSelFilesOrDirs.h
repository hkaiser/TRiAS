// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 18.03.2002 22:00:49 
//
// @doc
// @module PpgSelFilesOrDirs.h | Declaration of the <c CPpgSelFilesOrDirs> class

#if !defined(_PPGSELFILESORDIRS_H__4F2ABFE1_46B3_4A67_983E_263531457BDE__INCLUDED_)
#define _PPGSELFILESORDIRS_H__4F2ABFE1_46B3_4A67_983E_263531457BDE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "DDXGetFile.h"
#include "DDXGetFolder.h"

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CPpgSelFilesOrDirs dialog

class CPpgSelFilesOrDirs : 
	public CPropertyPage
{
	DECLARE_DYNCREATE(CPpgSelFilesOrDirs)

// Construction
public:
	CPpgSelFilesOrDirs();
	~CPpgSelFilesOrDirs();

	virtual void UpdateControls();

// Dialog Data
	//{{AFX_DATA(CPpgSelFilesOrDirs)
	enum { IDD = IDD_PPGSELFILES };
	CStatic	m_ftAltFiles;
	CStatic	m_ftDest;
	CString	m_strDestDir;
	CString	m_strRefDir;
	CString	m_strSrcDir;
	CString	m_strFileOrDir;
	//}}AFX_DATA

	CGetFilenameControl m_sleGetFileName;
	CGetFolderControl m_sleSrcFolder;
	CGetFolderControl m_sleDestFolder;
	CGetFolderControl m_sleAltFolder;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpgSelFilesOrDirs)
	public:
	virtual LRESULT OnWizardNext();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpgSelFilesOrDirs)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg LRESULT OnFileOrDirSelected (WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

	void AdjustButtons();
	void AdjustControls();
	void AdjustNextPage();

	COPYFLAG m_rgFlags;
	BOOL m_fSelectedRefDir;
	BOOL m_fSelectedDestDir;

private:
	BOOL ValidateSourceDirectory (LPCTSTR pcSrcDir);
	BOOL ValidateSourceFiles(CFiles &rFiles);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_PPGSELFILESORDIRS_H__4F2ABFE1_46B3_4A67_983E_263531457BDE__INCLUDED_)
