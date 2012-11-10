// myfiledg.cpp : implementation file
//

#include "bscriptp.hxx"
#include "bscript.h"
#include "myfiledg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////
// globale Funktionen
BOOL	LoadString(CString & str, int IDS);

/////////////////////////////////////////////////////////////////////////////
// CMyFileDialog

IMPLEMENT_DYNAMIC(CMyFileDialog, CFileDialog)

CMyFileDialog::CMyFileDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) 
		:		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
	m_fOpen = bOpenFileDialog;
#if defined(OFN_ENABLESIZING)
	if (IsWin41() || (IsWin50() && IsWinNT())) {
		m_ofn.Flags |= OFN_ENABLESIZING;
#if defined(OFN_DONTADDTORECENT)
		m_ofn.Flags |= OFN_DONTADDTORECENT;
#endif // defined(OFN_DONTADDTORECENT)
	}
#endif // defined(OFN_ENABLESIZING)
}


BEGIN_MESSAGE_MAP(CMyFileDialog, CFileDialog)
	//{{AFX_MSG_MAP(CMyFileDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CMyFileDialog::OnInitDialog() 
{
	CFileDialog::OnInitDialog();
	
	SetGermanCaption();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
	
void CMyFileDialog::SetGermanCaption()
{
	CString str;
	if (m_fOpen) LoadString (str, IDS_OPEN);
	else LoadString (str, IDS_SAVEAS);
	SetWindowText (str);
}