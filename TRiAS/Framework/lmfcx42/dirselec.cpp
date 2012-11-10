#include	"stdafx.h"
#include	<dlgs.h>
#ifdef _WIN32
#include	<shlobj.h>
#endif

#ifdef LAFX_WINC_SEG
#pragma code_seg(LAFX_WINC_SEG)
#endif

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
added support for Win95 Controls in CDirSelectDialog
RCS}}*/
static char* pszRCS = "$Id: dirselec.cpp 1.2 1996/08/20 19:10:15 andy Exp andy $";
/* $Log: dirselec.cpp $
// Revision 1.2  1996/08/20  19:10:15  andy
// added support for Win95 Controls in CDirSelectDialog
//
// Revision 1.1  1996/07/12  17:16:09  andy
// initial version
//
*/
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CDirSelectDialog,CFileDialog)

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDirSelectDialog dialog

CDirSelectDialog::CDirSelectDialog(CWnd* pParent /*=NULL*/)
	: CFileDialog( TRUE, NULL, NULL, OFN_HIDEREADONLY, NULL, pParent)
{
	//{{AFX_DATA_INIT(CDirSelectDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_strTitle.LoadString( IDS_DIRSELECTTITLE );
	m_ofn.lpstrTitle = m_strTitle;
}

void CDirSelectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDirSelectDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDirSelectDialog, CFileDialog)
	//{{AFX_MSG_MAP(CDirSelectDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CDirSelectDialog::DoModal()
{
	m_strDirectory.Empty();

#ifdef _WIN32
	OSVERSIONINFO	vi;
	memset( &vi, 0x00, sizeof( vi ) );
	vi.dwOSVersionInfoSize = sizeof( vi );
	if( ::GetVersionEx( &vi ) 
		&& ( ( VER_PLATFORM_WIN32_NT == vi.dwPlatformId && vi.dwMajorVersion > 3 )
		|| ( VER_PLATFORM_WIN32_WINDOWS == vi.dwPlatformId ) ) )
	{
		BROWSEINFO	bi;
		
		memset( &bi, 0x00, sizeof( bi ) );
		bi.lpszTitle = m_strTitle;

		ASSERT_VALID(this);

		if (vi.dwMajorVersion >= 5)
			bi.ulFlags |= BIF_NEWDIALOGSTYLE;

		// WINBUG: This is a special case for the file open/save dialog,
		//  which sometimes pumps while it is coming up but before it has
		//  disabled the main window.
		HWND hWndFocus = ::GetFocus();
		BOOL bEnableParent = FALSE;
		bi.hwndOwner = PreModal();
		AfxUnhookWindowCreate();
		if (bi.hwndOwner != NULL && ::IsWindowEnabled(bi.hwndOwner))
		{
			bEnableParent = TRUE;
			::EnableWindow(bi.hwndOwner, FALSE);
		}

		_AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
		ASSERT(pThreadState->m_pAlternateWndInit == NULL);

		AfxHookWindowCreate(this);

		LPCITEMIDLIST	idl = SHBrowseForFolder( &bi );

//		if (nResult)
//			ASSERT(pThreadState->m_pAlternateWndInit == NULL);
		pThreadState->m_pAlternateWndInit = NULL;

		// WINBUG: Second part of special case for file open/save dialog.
		if (bEnableParent)
			::EnableWindow(bi.hwndOwner, TRUE);
		if (::IsWindow(hWndFocus))
			::SetFocus(hWndFocus);

		if( NULL != idl )
		{
			SHGetPathFromIDList( idl, m_strDirectory.GetBufferSetLength( MAX_PATH ) );
			m_strDirectory.ReleaseBuffer( -1 );
			if( '\\' != m_strDirectory.GetAt( m_strDirectory.GetLength() - 1 ) )
				m_strDirectory += '\\';
		}

		PostModal();
		return NULL != idl && !m_strDirectory.IsEmpty() ? IDOK : IDCANCEL;
	}
#endif
	return CFileDialog::DoModal() ;
}

/////////////////////////////////////////////////////////////////////////////
// CDirSelectDialog message handlers

BOOL CDirSelectDialog::OnInitDialog() 
{
	// TODO: Add extra initialization here
	
	CRect	dlgRect, childRect;
	CWnd	*childWnd;
	int		offX, maxX;
	
	GetWindowRect( dlgRect );
	GetDlgItem( stc1 )->GetWindowRect( childRect );
	offX = childRect.left - ( dlgRect.left + 10 );

	maxX = 0;
	for( childWnd = GetWindow( GW_CHILD ); childWnd; childWnd = childWnd->GetNextWindow( GW_HWNDNEXT ) )
	{
		if( IsChild( childWnd ) )
		{
			childWnd->GetWindowRect( childRect );
			childRect.left   -= ( dlgRect.left + offX );
			childRect.right  -= ( dlgRect.left + offX );
			childRect.top    -= ( dlgRect.top + 20 );
			childRect.bottom -= ( dlgRect.top + 20 );
			if( childRect.left > 0 )
			{
				childWnd->MoveWindow( childRect.left, childRect.top, childRect.Width(), childRect.Height() );
				maxX = max( maxX, childRect.right );
			}
		}
	}

	MoveWindow( dlgRect.left, dlgRect.top, maxX + 20, dlgRect.Height() );

	GetDlgItem( stc3 )->ShowWindow( SW_HIDE );
	GetDlgItem( edt1 )->ShowWindow( SW_HIDE );
	GetDlgItem( lst1 )->ShowWindow( SW_HIDE );
	GetDlgItem( stc2 )->ShowWindow( SW_HIDE );
	GetDlgItem( cmb1 )->ShowWindow( SW_HIDE );
	GetDlgItem( chx1 )->ShowWindow( SW_HIDE );

	static CString	strFullPath = m_strDirectory + "*.*";
	m_ofn.lpstrInitialDir = m_strDirectory;
	m_ofn.lpstrFile = (char*) (const char*) strFullPath;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDirSelectDialog::OnOK() 
{
	OSVERSIONINFO	vi;
	memset( &vi, 0x00, sizeof( vi ) );
	vi.dwOSVersionInfoSize = sizeof( vi );
	if( ::GetVersionEx( &vi ) 
		&& ( ( VER_PLATFORM_WIN32_NT == vi.dwPlatformId && vi.dwMajorVersion > 3 )
		|| ( VER_PLATFORM_WIN32_WINDOWS == vi.dwPlatformId ) ) )
	{
		CFileDialog::OnOK();
	}
	else
	{
		CString		S;
		CListBox	*pLBDir = (CListBox*) GetDlgItem( lst2 );

		pLBDir->GetText( 0, m_strDirectory );					// Laufwerksname
	
		for( int i = 1; i < pLBDir->GetCurSel() + 1; i++ )
		{
			pLBDir->GetText( i, S );
			m_strDirectory += S;
			m_strDirectory += '\\';
		}
		CFileDialog::EndDialog( IDOK );
	}
}
