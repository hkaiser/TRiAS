// debfdlg.cpp : implementation file
//
#include "bscriptp.hxx"
#include "bscript.h"
#include "debfdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////
// globale Funktionen
BOOL LoadString(CString & str, int IDS);

/////////////////////////////////////////////////////////////////////////////
// CDebFileDialog

IMPLEMENT_DYNAMIC(CDebFileDialog, CFileDialog)

CDebFileDialog::CDebFileDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd, LPCSTR lpcstrCaption) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
	m_strCaption = lpcstrCaption;
	if (m_strCaption.IsEmpty()) 
		LoadString (m_strCaption, IDS_OPEN);
	m_ofn.lpstrTitle = m_strCaption;
	m_fCheckLink = false;
	m_fAutoStart = false;

#if defined(OFN_ENABLESIZING)
	if (IsWin41() || (IsWin50() && IsWinNT())) {
		m_ofn.Flags |= OFN_ENABLESIZING;
#if defined(OFN_DONTADDTORECENT)
		m_ofn.Flags |= OFN_DONTADDTORECENT;
#endif // defined(OFN_DONTADDTORECENT)
	}
#endif // defined(OFN_ENABLESIZING)
}


BEGIN_MESSAGE_MAP(CDebFileDialog, CFileDialog)
	//{{AFX_MSG_MAP(CDebFileDialog)
	ON_BN_CLICKED(IDC_CHECKLINK, OnChecklink)
	ON_BN_CLICKED(IDC_CHECKAUTO, OnCheckauto)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CDebFileDialog::OnInitDialog() 
{
	CFileDialog::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDebFileDialog::OnChecklink() 
{
	if (true == m_fCheckLink)
		m_fCheckLink = false;
	else
		m_fCheckLink = true;
}

void CDebFileDialog::OnCheckauto() 
{
	if (true == m_fAutoStart)
		m_fAutoStart = false;
	else
		m_fAutoStart = true;	
}


