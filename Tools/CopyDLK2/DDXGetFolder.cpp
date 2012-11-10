/*
Module : DDXGETFOLDER.CPP
Purpose: implementation for a MFC DDX_ routine to get a directory/folder
         Using the file open/save as common dialogs or the newer Shell API
         SHBrowseForFolder

Created: PJN / DDXGETFOLDER/1 / 26-03-1997
History: None

Copyright (c) 1997 by PJ Naughter.  
All rights reserved.

*/

///////////////////////////////////////////////////////////////////////////////
// Includes  

#include "StdAfx.h"
#include "resource.h"

#include <shlobj.h>

#include "DDXGetFolder.h"
#include "dlgdir.h"

///////////////////////////////////////////////////////////////////////////////
// defines 
#define GETFOLDER_EDIT_ID 101

BEGIN_MESSAGE_MAP(CModifyButtonFolder, CButton)
  //{{AFX_MSG_MAP(CModifyButtonFolder)
  ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	ON_WM_CREATE()
	ON_WM_DESTROY()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

        
CModifyButtonFolder::CModifyButtonFolder()
{
	m_pBuddy = NULL;
	m_bFirstCall = TRUE;
	m_fTTCreated = FALSE;
}

int CModifyButtonFolder::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_ToolTip.Create(this);		// Fehler nicht fatal
	m_fTTCreated = TRUE;
	return 0;
}

void CModifyButtonFolder::OnDestroy() 
{
	CButton::OnDestroy();
	m_ToolTip.DestroyWindow();
}

void CModifyButtonFolder::SetBuddy(CGetFolderControl* pBuddy)
{
  m_pBuddy = pBuddy;
}

void CModifyButtonFolder::Reset()
{
	m_pBuddy = NULL;
	m_bFirstCall = TRUE;
	m_ToolTip.DelTool(this);
	m_ToolTip.Activate(FALSE);
}

BOOL CModifyButtonFolder::PreTranslateMessage(MSG* pMsg) 
{                     
  //create the tooltip
  if (m_bFirstCall && m_fTTCreated)
  {
    m_ToolTip.Activate(TRUE);
    m_ToolTip.AddTool(this, IDS_DDX_GFLDR_TT_MODIFY);
    m_bFirstCall = FALSE;
  }
  
  //give the tooltip a chance to handle the message
  if (m_fTTCreated) m_ToolTip.RelayEvent(pMsg);

  return CButton::PreTranslateMessage(pMsg);
}


void CModifyButtonFolder::OnClicked() 
{
  if (m_pBuddy)
    m_pBuddy->Edit((GetAsyncKeyState(VK_CONTROL) < 0) ? FALSE : TRUE);
  else
    TRACE0("CModifyButtonFolder: No auto buddy defined\n");
}                        

BEGIN_MESSAGE_MAP(CGetFolderControl, CStatic)
  //{{AFX_MSG_MAP(CGetFolderControl)
	ON_WM_ENABLE()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()


CGetFolderControl::CGetFolderControl()
{
}

// remove macro from windowsx.h
#undef SubclassWindow	

BOOL CGetFolderControl::SubclassEdit(HWND hEdit)
{   
  //test our inputs
  ASSERT(this);
  if (!IsWindow(hEdit))
  {
    ASSERT(FALSE);
    TRACE0("CGetFolderControl::SubclassEdit -- window handle is invalid!\n");
    return FALSE;
  }                
  
  //subclass the control
  if (SubclassWindow(hEdit))
  {
    //This control can only be used with a read only edit control
    LONG lStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);
    if (!(lStyle & ES_READONLY))
    {
      TRACE0("CGetFolderControl::SubclassEdit -- ES_READONLY style should be set for the edit control\n");
      ASSERT(FALSE);
      return FALSE;
    }

    return AddEditButton();
  }
  else
  {
    TRACE0("CGetFolderControl::SubclassEdit -- Could not subclass edit control!\n");
    ASSERT(FALSE);
    return FALSE;
  }
}

BOOL CGetFolderControl::AddEditButton()
{
CRect Rect;

  GetWindowRect(Rect);		// EditControl
  GetParent()->ScreenToClient(Rect);

// Größe des Buttons feststellen
  Rect.left = Rect.right - (Rect.Height()*8/10);	// width is 8/10 of height

//dynamically create the edit button control
  CString sEditControlText;
  VERIFY(sEditControlText.LoadString(IDS_DDX_GF_EDIT_TEXT));
 
BOOL bSuccess = m_Edit.Create(sEditControlText, WS_VISIBLE | WS_CHILD | WS_GROUP, Rect, GetParent(), GETFOLDER_EDIT_ID);

	if (!bSuccess) return FALSE;

CRect rcRectEdit;

	GetWindowRect(rcRectEdit);
	rcRectEdit.right -= Rect.Width() + 3;
	SetWindowPos (NULL, 0, 0, rcRectEdit.Width(), rcRectEdit.Height(), SWP_NOZORDER|SWP_NOMOVE);

	m_Edit.SetBuddy(this);	// tell the button to call this class when it is clicked
	m_Edit.SetFont(GetParent()->GetFont());	// ensure it is using the same font as the parent
	return bSuccess;
}

// CallBack für BrowseForFolder
int __stdcall BrowseCallbackProc (HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	if (BFFM_INITIALIZED == uMsg) 
		::SendMessage (hwnd, BFFM_SETSELECTION, TRUE, lpData);

	return 0;
} 

void CGetFolderControl::Edit(BOOL fShowDlg)
{
CString sInitialDir;

	if (m_sDir.IsEmpty())
		GetWindowText(sInitialDir);
	else
		sInitialDir = m_sDir;

	if (fShowDlg || 0 == sInitialDir.GetLength()) {
	// bring up the common file open dialog to select the folder
	BYTE WinMajorVersion = LOBYTE(LOWORD(GetVersion()));
		
		if ((WinMajorVersion >= 4) && ((m_dwFlags & GFLDR_OLD_STYLE_DIALOG) == 0))
		{
		// Running on Windows 95 shell and new style requested
		TCHAR sDisplayName[_MAX_PATH];
		BROWSEINFO bi;
			
			bi.hwndOwner = m_hWnd;
			bi.pidlRoot = NULL;
			bi.lpszTitle =  m_sTitle;
			bi.pszDisplayName = sDisplayName;
			bi.ulFlags = BIF_RETURNONLYFSDIRS;
#if defined(BIF_NEWDIALOGSTYLE)
			if (WinMajorVersion >= 5 && (m_dwFlags & GFLDR_SAVEASDIALOG))
				bi.ulFlags |= BIF_NEWDIALOGSTYLE;
#endif // defined(BIF_NEWDIALOGSTYLE)
			bi.lpfn = m_sDir.IsEmpty() ? NULL : BrowseCallbackProc;
			bi.lParam = m_sDir.IsEmpty() ? 0 :(LPARAM)(LPCTSTR)m_sDir;
			
			LPITEMIDLIST pItemIDList = SHBrowseForFolder(&bi);
			
			if (pItemIDList) {
			TCHAR sPath[_MAX_PATH];
				
				if (SHGetPathFromIDList(pItemIDList, sPath)) {
					if (sPath[strlen(sPath)-1] != '\\')
						_tcscat(sPath, "\\");		// als Verzeichnis kennzeichnen
					SetWindowText(sPath);
					GetParent()->PostMessage(WM_DIRSELECTED, GetWindowLong(m_hWnd, GWL_ID));
				}
			// avoid memory leaks by deleting the PIDL
			// using the shells task allocator
			IMalloc* pMalloc;

				if (SHGetMalloc(&pMalloc) != NOERROR)
				{
					TRACE("Failed to get pointer to shells task allocator");
					return;
				}
				pMalloc->Free(pItemIDList);
				if (pMalloc)
					pMalloc->Release();
			}
		}
		else  // Use old style if requested or when running on NT 3.51 where we have no choice
		{
		CFileDirDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ENABLETEMPLATE, NULL, this);
			
			dlg.m_ofn.Flags &= ~OFN_EXPLORER; // Turn of the explorer style customisation
			dlg.m_ofn.hInstance = AfxGetInstanceHandle();
			dlg.m_ofn.lpTemplateName = MAKEINTRESOURCE(FILEOPENORD);
			dlg.m_ofn.lpstrInitialDir = sInitialDir;
			dlg.m_ofn.lpstrTitle = m_sTitle;
			if (dlg.DoModal() == IDOK)
			{
				dlg.m_ofn.lpstrFile[dlg.m_ofn.nFileOffset - 1] = 0; // Nuke the "Junk" text filename
				SetWindowText(dlg.m_ofn.lpstrFile);
				GetParent()->PostMessage(WM_DIRSELECTED, GetWindowLong(m_hWnd, GWL_ID));
			}
		}
	} else {
	// nur so tun als ob
		SetWindowText (sInitialDir);
		GetParent()->PostMessage(WM_DIRSELECTED, GetWindowLong(m_hWnd, GWL_ID));
	}
}


void CGetFolderControl::SetFlags(DWORD dwFlags, const CString& sTitle, const CString &sDir) 
{ 
  m_dwFlags = dwFlags; 
  m_sTitle = sTitle;
  m_sDir = sDir;
}

BOOL CGetFolderControl::Reset (void)
{
// test our inputs
	ASSERT(this);
	if (!IsWindow(m_Edit.GetSafeHwnd()))
	{
		ASSERT(FALSE);
		TRACE0("CGetFilenameControl::Reset -- EditButton window handle is invalid!\n");
		return FALSE;
	}
  
// remove the button
	if (!RemoveEditButton()) {
		TRACE0("CGetFilenameControl::Reset -- Failure to remove button control!\n");
		ASSERT(FALSE);
		return FALSE;
	}

// subclass the control
HWND hWnd = UnsubclassWindow();

	if (NULL == hWnd)
	{
		TRACE0("CGetFilenameControl::Reset -- Failure to Unsubclass edit control!\n");
		ASSERT(FALSE);
		return FALSE;
	}

	m_sDir.Empty();
	return TRUE;
}

BOOL CGetFolderControl::RemoveEditButton()
{
// Größe wiederherstellen
CRect rcRectEdit, rcBttn;

	m_Edit.GetWindowRect(rcBttn);
	GetWindowRect(rcRectEdit);
	rcRectEdit.right += rcBttn.Width() + 3;
	SetWindowPos (NULL, 0, 0, rcRectEdit.Width(), rcRectEdit.Height(), 
		SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE);

// Button wieder zerlegen
	m_Edit.Reset();			// reset the button context
	return m_Edit.DestroyWindow();
}

void CGetFolderControl::OnEnable(BOOL bEnable)
{
	CStatic::OnEnable(bEnable);
	m_Edit.EnableWindow(bEnable);
}

void DDX_GetFolderControl(CDataExchange* pDX, int nIDC, CGetFolderControl& rCGetFolderControl, DWORD dwFlags, const CString& sTitle, const CString &sDir)
{
  HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
  if (!pDX->m_bSaveAndValidate && rCGetFolderControl.m_hWnd == NULL)    // not subclassed yet
  {
    if (!rCGetFolderControl.SubclassEdit(hWndCtrl))
    {
      ASSERT(FALSE);      // possibly trying to subclass twice ?
      AfxThrowNotSupportedException();
    }
  }
  rCGetFolderControl.SetFlags(dwFlags, sTitle, sDir);
}

