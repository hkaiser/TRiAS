/*
Module : DDXGETFILE.CPP
Purpose: implementation for a MFC DDX_ routine to get a filename
         Using the file open/save as common dialogs
Created: PJN / DDXGETFILE/1 / 19-03-1997
History: None

Copyright (c) 1996 by PJ Naughter.  
All rights reserved.

*/

/////////////////////////////////  Includes  //////////////////////////////////
#include "StdAfx.h"

#include <dlgs.h>
#include "resource.h"
#include "DDXGetFile.h"

///////////////////////////////// defines /////////////////////////////////////

#define GETFILENAME_EDIT_ID 100


BEGIN_MESSAGE_MAP(CModifyButton, CButton)
  //{{AFX_MSG_MAP(CModifyButton)
  ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	ON_WM_CREATE()
	ON_WM_DESTROY()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

       
CModifyButton::CModifyButton()
{
	m_pBuddy = NULL;
	m_bFirstCall = TRUE;
	m_fTTCreated = FALSE;
}

void CModifyButton::SetBuddy(CGetFilenameControl* pBuddy)
{
  m_pBuddy = pBuddy;
}

int CModifyButton::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_ToolTip.Create(this);		// Fehler nicht fatal
	m_fTTCreated = TRUE;
	return 0;
}

void CModifyButton::OnDestroy() 
{
	CButton::OnDestroy();
	m_ToolTip.DestroyWindow();
}

void CModifyButton::Reset()
{
	m_pBuddy = NULL;
	m_bFirstCall = TRUE;
	m_ToolTip.DelTool(this);
	m_ToolTip.Activate(FALSE);
}

BOOL CModifyButton::PreTranslateMessage(MSG* pMsg) 
{                     
  //create the tooltip
  if (m_bFirstCall && m_fTTCreated)
  {
    m_ToolTip.Activate(TRUE);
    m_ToolTip.AddTool(this, IDS_DDX_GF_TT_MODIFY);
    m_bFirstCall = FALSE;
  }
  
  //give the tooltip a chance to handle the message
	if (m_fTTCreated) m_ToolTip.RelayEvent(pMsg);

  return CButton::PreTranslateMessage(pMsg);
}


void CModifyButton::OnClicked() 
{
  if (m_pBuddy)
    m_pBuddy->Edit((GetAsyncKeyState(VK_CONTROL) < 0) ? FALSE : TRUE);
  else
    TRACE0("CModifyButton: No auto buddy defined\n");
}                        

IMPLEMENT_DYNAMIC(CGetFileNameDialog, CFileDialog)

CGetFileNameDialog::CGetFileNameDialog(
		BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName, 
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) 
	: CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
}


BEGIN_MESSAGE_MAP(CGetFileNameDialog, CFileDialog)
	//{{AFX_MSG_MAP(CGetFileNameDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CGetFileNameDialog::OnInitDialog() 
{
	CFileDialog::OnInitDialog();

  //modify the text on the IDOK button to ok
  //if we are using the old style common dialog
	if ( ((m_ofn.Flags & OFN_EXPLORER) == 0) || ((GetVersion() & 0xff) < 4) )
	{
	CString sText;
	
		VERIFY(sText.LoadString (IDS_DDX_GF_OK));

	CWnd* pOkButton = GetDlgItem(IDOK);
		
		ASSERT(NULL != pOkButton);
		if (pOkButton)
			pOkButton->SetWindowText(sText);
	}
	return TRUE;
}


void CGetFileNameDialog::OnOK()
{
  BOOL bCallParent = TRUE;

  if ( ((m_ofn.Flags & OFN_EXPLORER) == 0) || ((GetVersion() & 0xff) < 4) )
  {
    //check for overwrite if that flag is used
    if (m_ofn.Flags & OFN_OVERWRITEPROMPT)
    {
      //Retrieve the filename selected
      TCHAR sPath[_MAX_PATH];
      GetDlgItemText(edt1, sPath, _MAX_PATH);

      //check to see if the file already exists
      CFileStatus fs;
      if (CFile::GetStatus(sPath, fs))
      {
        CString sMessage;
        AfxFormatString1(sMessage, IDS_DDX_GF_OVERWRITE_PROMPT, sPath);

        //ensure the title is the same as the common dialog caption
        CString sCaption;
        GetWindowText(sCaption);
        bCallParent = (MessageBox(sMessage, sCaption, MB_YESNO | MB_ICONQUESTION) == IDYES);
      }
    }
  }

  if (bCallParent)
    CFileDialog::OnOK();
}



void CGetFileNameDialog::OnInitDone()
{
CString sText;

	VERIFY(sText.LoadString(IDS_DDX_GF_OK));

LPTSTR pszBuffer = sText.GetBuffer(sText.GetLength());

  //modify the text on the IDOK button to ok
  CommDlg_OpenSave_SetControlText(GetParent()->m_hWnd, IDOK, pszBuffer);

  sText.ReleaseBuffer();
}


BOOL CGetFileNameDialog::OnFileNameOK()
{
  BOOL rVal = CFileDialog::OnFileNameOK();

  if (!rVal && ((m_ofn.Flags & OFN_EXPLORER) == 0) || ((GetVersion() & 0xff) < 4))
  //if the filename passed the parent tests
  //then put it throught our own tests
  {
    //check for overwrite if that flag is used, since the file open
    //common dialog will not bother looking at this flag
    if (m_ofn.Flags & OFN_OVERWRITEPROMPT)
    {
      //Retrieve the filename selected
      TCHAR sPath[_MAX_PATH];
      CommDlg_OpenSave_GetFilePath(GetParent()->m_hWnd, sPath, _MAX_PATH);

      //check to see if the file already exists
      CFileStatus fs;
      if (CFile::GetStatus(sPath, fs))
      {
        CString sMessage;
        AfxFormatString1(sMessage, IDS_DDX_GF_OVERWRITE_PROMPT, sPath);

        //ensure the title is the same as the common dialog caption
        CString sCaption;
        GetParent()->GetWindowText(sCaption);
        rVal = (MessageBox(sMessage, sCaption, MB_YESNO | MB_ICONQUESTION) != IDYES);
      }
    }
  }


  return rVal;
}



BEGIN_MESSAGE_MAP(CGetFilenameControl, CStatic)
  //{{AFX_MSG_MAP(CGetFilenameControl)
  ON_WM_ENABLE()
  ON_WM_SHOWWINDOW()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()


CGetFilenameControl::CGetFilenameControl()
{
	m_fReadOnly = FALSE;
	m_iCnt = 1;
}

// remove macro from windowsx.h
#undef SubclassWindow	

BOOL CGetFilenameControl::SubclassEdit(HWND hEdit)
{   
  //test our inputs
  ASSERT(this);
  if (!IsWindow(hEdit))
  {
    ASSERT(FALSE);
    TRACE0("CGetFilenameControl::SubclassEdit -- window handle is invalid!\n");
    return FALSE;
  }                
  
  //subclass the control
  if (SubclassWindow(hEdit))
  {
    //This control can only be used with a read only edit control
    LONG lStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);
    if (!(lStyle & ES_READONLY))
    {
      TRACE0("CGetFilenameControl::SubclassEdit -- ES_READONLY style should be set for the edit control\n");
      ASSERT(FALSE);
      return FALSE;
    }

    return AddEditButton();
  }
  else
  {
    TRACE0("CGetFilenameControl::SubclassEdit -- Could not subclass edit control!\n");
    ASSERT(FALSE);
    return FALSE;
  }
}


BOOL CGetFilenameControl::AddEditButton()
{
CRect Rect;

  GetWindowRect(Rect);		// EditControl
  GetParent()->ScreenToClient(Rect);

// Größe des Buttons feststellen
  Rect.left = Rect.right - (Rect.Height()*8/10);	// width is 8/10 of height

//dynamically create the edit button control
  CString sEditControlText;
  VERIFY(sEditControlText.LoadString(IDS_DDX_GF_EDIT_TEXT));
 
BOOL bSuccess = m_Edit.Create(sEditControlText, WS_VISIBLE | WS_CHILD | WS_GROUP, Rect, GetParent(), GETFILENAME_EDIT_ID);

	if (!bSuccess) return FALSE;

CRect rcRectEdit;

	GetWindowRect(rcRectEdit);
	rcRectEdit.right -= Rect.Width() + 3;
	SetWindowPos (NULL, 0, 0, rcRectEdit.Width(), rcRectEdit.Height(), 
		SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE);

	m_Edit.SetBuddy(this);	// tell the button to call this class when it is clicked
	m_Edit.SetFont(GetParent()->GetFont());	// ensure it is using the same font as the parent
	return bSuccess;
}

BOOL CGetFilenameControl::UnsubclassEdit()
{
	if (!IsWindow(m_hWnd)) {
		ASSERT(FALSE);
		TRACE0("CGetFilenameControl::UnsubclassEdit -- window handle is not subclassed!\n");
		return FALSE;
	}

	if (RemoveEditButton()) {
		UnsubclassWindow();
		return TRUE;
	}
	return FALSE;
}

void CGetFilenameControl::Edit(BOOL fShowDlg)
{
//bring up the common file open dialog to select the filename

//retreive the current filename to use as the initial value
CString sCurrentFilename;

	if (m_sDir.IsEmpty())
		GetWindowText(sCurrentFilename);
	else
		sCurrentFilename = m_sDir;

	if (fShowDlg || 0 == sCurrentFilename.GetLength()) {
	// work out the flags to use
	DWORD dwFlags = 0;
	BOOL fOpenFile = TRUE;

	  if (m_dwFlags & GF_HIDEREADONLY)
		dwFlags |= OFN_HIDEREADONLY;
	  if (m_dwFlags & GF_OVERWRITEPROMPT)
	    dwFlags |= OFN_OVERWRITEPROMPT;
	  if (m_dwFlags & GF_FILEMUSTEXIST)
	    dwFlags |= OFN_FILEMUSTEXIST;
	  if (m_dwFlags & GF_SAVEASDIALOG) {
		fOpenFile = FALSE;
		m_dwFlags |= OFN_NOREADONLYRETURN;
	  }
	  if (m_dwFlags & GF_MULTIPLESELECTION)
		dwFlags |= OFN_ALLOWMULTISELECT;

		if (IsWin40())
			dwFlags |= OFN_EXPLORER;
		else
			dwFlags |= OFN_LONGNAMES;

#if defined(OFN_ENABLESIZING)
		if (IsWin41() || (IsWinNT() && IsWin50())) {		// Win98 oder WinNT50
			dwFlags |= OFN_ENABLESIZING;
#if defined(OFN_DONTADDTORECENT)
			dwFlags |= OFN_DONTADDTORECENT;
#endif // defined(OFN_DONTADDTORECENT)
		}
#endif // OFN_ENABLESIZING

	CGetFileNameDialog dlg (fOpenFile, m_sDefExt, sCurrentFilename, dwFlags, m_sExtFilter, GetParent());

	  //Modify the title to the desired value
	  dlg.m_ofn.lpstrTitle = m_sTitle;
	  
	  //uncomment the following line if you want to use the old style file open common dialog
	  if (m_dwFlags & GF_OLD_STYLE_DIALOG)
	    dlg.m_ofn.Flags &= ~OFN_EXPLORER;

	// evtl. Verzeichnis voreinstellen
	CString strFiles;

		if (m_dwFlags & GF_MULTIPLESELECTION) {
		LPTSTR pBuffer = strFiles.GetBufferSetLength(_MAX_PATH*255);

			if (NULL != pBuffer) {
				dlg.m_ofn.lpstrFile = pBuffer;
				dlg.m_ofn.nMaxFile = _MAX_PATH*255;
			}
		}

		if (!m_sDir.IsEmpty())
			dlg.m_ofn.lpstrInitialDir = m_sDir;

	// bring up the dialog and if hit ok set the text in this control to the new filename
	  if (dlg.DoModal() == IDOK) {
	    SetWindowText (GetPathName (dlg));
		if (!(m_dwFlags & GF_HIDEREADONLY) && !(m_dwFlags & GF_SAVEASDIALOG)) {
			m_fReadOnly = (dlg.m_ofn.Flags & OFN_READONLY) ? TRUE: FALSE;

		// testen, ob die Datei evtl. schreibgeschützt ist
			if (!m_fReadOnly) {
			DWORD dwAttr = ::GetFileAttributes (GetPathName (dlg));

				if ((UINT)(-1) != dwAttr)
					m_fReadOnly = (dwAttr & FILE_ATTRIBUTE_READONLY) ? TRUE : FALSE;
			}
		}
		GetParent()->PostMessage (WM_FILESELECTED, GetDlgCtrlID());
	  }
	} else {
		SetWindowText(sCurrentFilename);
		m_Files.insert(os_string(sCurrentFilename));
		GetParent()->PostMessage (WM_FILESELECTED, GetDlgCtrlID());
	}
}

CString CGetFilenameControl::GetPathName(CGetFileNameDialog &rDlg)
{
	m_Files.erase();
	if (!(m_dwFlags & GF_MULTIPLESELECTION)) {
		m_iCnt = 1;
		m_Files.insert(os_string(rDlg.GetPathName()));
		return rDlg.GetPathName();
	}

// MultiSelDlg
POSITION pos = rDlg.GetStartPosition();

	while (NULL != pos) {
	CString str (rDlg.GetNextPathName (pos));

		m_Files.insert(os_string(str));
	}

// erste Datei liefern
	if (m_Files.size() > 0)
		return (*m_Files.begin()).c_str();
	else
		return "";
}

void CGetFilenameControl::SetFlags(
	DWORD dwFlags, const CString& sTitle, const CString& sExtFilter, const CString& sDefExt, 
	const CString &sDir) 
{ 
	m_dwFlags = dwFlags; 
	m_sTitle = sTitle;

	m_sExtFilter = sExtFilter;
	m_sDefExt = sDefExt;
	if (m_sDefExt[0] == '.')	// evtl. führenden Punkt beseitigen
		m_sDefExt = m_sDefExt.Right (m_sDefExt.GetLength()-1);

CString allFilter;

	VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
	m_sExtFilter += allFilter;
	m_sExtFilter += (TCHAR)'|';   // next string please
	m_sExtFilter += _T("*.*");
	m_sExtFilter += (TCHAR)'|';   // last string

	m_sDir = sDir;
}

BOOL CGetFilenameControl::Reset (void)
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

BOOL CGetFilenameControl::RemoveEditButton()
{
// Größe wiederherstellen
CRect rcRectEdit, rcBttn;

	m_Edit.GetWindowRect(rcBttn);
	GetWindowRect(rcRectEdit);
	rcRectEdit.right += rcBttn.Width() + 3;
	SetWindowPos (NULL, 0, 0, rcRectEdit.Width(), rcRectEdit.Height(), 
		SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE);

// Button wieder zerlegen
	m_Edit.Reset();		// reset the button context
	return m_Edit.DestroyWindow();
}

void CGetFilenameControl::OnEnable(BOOL bEnable)
{
	CStatic::OnEnable(bEnable);
	m_Edit.EnableWindow(bEnable);
}

void CGetFilenameControl::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CStatic::OnShowWindow(bShow, nStatus);
	m_Edit.ShowWindow(bShow ? SW_SHOW : SW_HIDE);
}

void DDX_GetFilenameControl(
	CDataExchange* pDX, int nIDC, CGetFilenameControl& rCGetFilenameControl, 
	DWORD dwFlags, const CString& sTitle, const CString& sExtFilter, 
	const CString& sDefExt, const CString &sDir)
{
  HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
  if (!pDX->m_bSaveAndValidate && rCGetFilenameControl.m_hWnd == NULL)    // not subclassed yet
  {
    if (!rCGetFilenameControl.SubclassEdit(hWndCtrl))
    {
      ASSERT(FALSE);      // possibly trying to subclass twice ?
      AfxThrowNotSupportedException();
    }
  }
  rCGetFilenameControl.SetFlags(dwFlags, sTitle, sExtFilter, sDefExt, sDir);
}

void DDX_PrepareFilenameControl(CDataExchange* pDX, int nIDC, CGetFilenameControl& rCGetFilenameControl)
{
HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	if (rCGetFilenameControl.m_hWnd == NULL)    // not subclassed yet
	{
		if (!rCGetFilenameControl.SubclassEdit(hWndCtrl))
		{
			ASSERT(FALSE);      // possibly trying to subclass twice ?
			AfxThrowNotSupportedException();
		}
	}
}
