/* 
Module:  dlgdir.h
Purpose: override of CFileDialog to allow just a directory to be selected
Created: PJN / DDXGETFOLDER/1 / 26-03-1997
History: EMPTY

Copyright (c) 1997 by PJ Naughter.  
All rights reserved.

*/

#ifndef __DLGDIR_H__
#define __DLGDIR_H__

///////////////////////////////////////////////////////////////////////////////
// Includes 
#include "dlgs.h"                           

///////////////////////////////////////////////////////////////////////////////
// Classes 
class CFileDirDialog : public CFileDialog
{
public:
// Public data members
  BOOL m_bDlgJustCameUp;
    
// Constructors
  CFileDirDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
                 LPCTSTR lpszDefExt = NULL,
                 LPCTSTR lpszFileName = NULL,
                 DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
                 LPCTSTR lpszFilter = NULL,
                 CWnd* pParentWnd = NULL);
                                          
// Implementation
protected:
  //{{AFX_MSG(CFileDirDialog)
  virtual BOOL OnInitDialog();
  afx_msg void OnPaint();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

#endif //__DLGDIR_H__