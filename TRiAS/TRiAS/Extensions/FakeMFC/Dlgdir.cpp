/* 
Module:  dlgdir.cpp
Purpose: override of CFileDialog to allow just a directory to be selected
Created: PJN / DDXGETFOLDER/1 / 26-03-1997
History: EMPTY

Copyright (c) 1997 by PJ Naughter.  
All rights reserved.

*/

///////////////////////////////////////////////////////////////////////////////
// Includes 
#include "fakemfcp.hxx"

#include "dlgdir.h"           
#include "dlgs.h"

///////////////////////////////////////////////////////////////////////////////
// Macros 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Implementation 
CFileDirDialog::CFileDirDialog(
		BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName, 
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) 
	: CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName,
				  dwFlags, lpszFilter, pParentWnd)
{
  //{{AFX_DATA_INIT(CFileDirDialog)
  //}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CFileDirDialog, CFileDialog)
  //{{AFX_MSG_MAP(CFileDirDialog)
  ON_WM_PAINT()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CFileDirDialog::OnInitDialog()
{  
  //CenterWindow();

  //Let's hide these windows so the user cannot tab to them.  Note that in
  //the private template the coordinates for these guys are
  //*outside* the coordinates of the dlg window itself.  Without the following
  //ShowWindow()'s you would not see them, but could still tab to them.
    
  GetDlgItem(stc2)->ShowWindow(SW_HIDE);
  GetDlgItem(stc3)->ShowWindow(SW_HIDE);
  GetDlgItem(edt1)->ShowWindow(SW_HIDE);
  GetDlgItem(lst1)->ShowWindow(SW_HIDE);
  GetDlgItem(cmb1)->ShowWindow(SW_HIDE);
    
  //We must put something in this field, even though it is hidden.  This is
  //because if this field is empty, or has something like "*.txt" in it,
  //and the user hits OK, the dlg will NOT close.  We'll jam something in
  //there (like "Junk") so when the user hits OK, the dlg terminates.
  //Note that we'll deal with the "Junk" during return processing (see below)

  SetDlgItemText(edt1, _T("Junk"));

  //Now set the focus to the directories listbox.  Due to some painting
  //problems, we *must* also process the first WM_PAINT that comes through
  //and set the current selection at that point.  Setting the selection
  //here will NOT work.  See comment below in the on paint handler.
            
  GetDlgItem(lst2)->SetFocus();
            
  m_bDlgJustCameUp=TRUE;
               
  CFileDialog::OnInitDialog();
     
  return(FALSE);
}
  
void CFileDirDialog::OnPaint()
{
  CPaintDC dc(this); // device context for painting
    
  //This code makes the directory listbox "highlight" an entry when it first
  //comes up.  W/O this code, the focus is on the directory listbox, but no
  //focus rectangle is drawn and no entries are selected.  Ho hum.

  if (m_bDlgJustCameUp)
  {
    m_bDlgJustCameUp=FALSE;
    SendDlgItemMessage(lst2, LB_SETCURSEL, 0, 0L);
  }
    
  // Do not call CFileDialog::OnPaint() for painting messages
}
