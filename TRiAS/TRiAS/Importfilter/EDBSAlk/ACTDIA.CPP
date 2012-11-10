///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			actdia.cpp
//
//	Stand:			08.12.1994
//	Beschreibung:	Import - Dialog
//	Entwicklung:	08.12.94	Beginn der Kodierung
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#if defined(_USE_CONFIG_DIALOGS)

#include "resource.h"
#include "actdia.hpp"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

CActiDialog :: CActiDialog( CWnd* pParent )
//	: CDialog( CActiDialog::IDD, pParent )
{	//{{AFX_DATA_INIT(CActiDialog)
	//}}AFX_DATA_INIT
	m_Break = FALSE;
	Create( CActiDialog::IDD, CWnd::FromHandle( __hWndM ));
}

void CActiDialog :: Open()
{
	ShowWindow( SW_NORMAL );
}

void CActiDialog :: Close()
{	DestroyWindow();
}

void CActiDialog :: SetFileName( const char* txt )
{	SetDlgItemText( IDC_FILENAME, txt );
}

void CActiDialog :: SetFileSize( const char* txt )
{	SetDlgItemText( IDC_FILESIZE, txt );
}

void CActiDialog :: SetFilePos( const char* txt )
{	SetDlgItemText( IDC_FILEPOS, txt );
}

void CActiDialog :: DoDataExchange( CDataExchange* pDX )
{	CDialog :: DoDataExchange( pDX );
	//{{AFX_DATA_MAP(CActiDialog)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP( CActiDialog, CDialog )
	ON_BN_CLICKED( IDCANCEL, OnCancelClicked )
END_MESSAGE_MAP()

void CActiDialog :: OnCancelClicked()
{	m_Break = TRUE;
}

#endif // defined(_USE_CONFIG_DIALOGS)

