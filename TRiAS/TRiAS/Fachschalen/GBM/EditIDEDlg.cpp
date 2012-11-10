// EditIDEDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "EditIDEDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditIDEDlg dialog


CEditIDEDlg::CEditIDEDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditIDEDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditIDEDlg)
	m_strOldIDE = _T("");
	m_strNeueIDE = _T("");
	//}}AFX_DATA_INIT
}


void CEditIDEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditIDEDlg)
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Text(pDX, IDC_EDIT1, m_strOldIDE);
	DDX_Text(pDX, IDC_EDIT2, m_strNeueIDE);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditIDEDlg, CDialog)
	//{{AFX_MSG_MAP(CEditIDEDlg)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditIDEDlg message handlers

BOOL CEditIDEDlg::OnInitDialog() 
{
	CWnd	*pWnd;

	CDialog::OnInitDialog();

	if ( !m_bInDB )
	{
		pWnd = GetDlgItem( IDC_RADIO1 );
		if ( pWnd )	pWnd -> EnableWindow( FALSE );
		pWnd = GetDlgItem( IDC_RADIO3 );
		if ( pWnd )	pWnd -> EnableWindow( FALSE );
		CheckRadioButton( IDC_RADIO1, IDC_RADIO3, IDC_RADIO2 );
	}
	else
		CheckRadioButton( IDC_RADIO1, IDC_RADIO3, IDC_RADIO1 );

	m_btnOK.EnableWindow( FALSE );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditIDEDlg::OnChangeEdit() 
{
	UpdateData( TRUE );
	if ( m_strNeueIDE.IsEmpty() ||
		( m_strOldIDE == m_strNeueIDE ))
		m_btnOK.EnableWindow( FALSE );
	else
		m_btnOK.EnableWindow( TRUE );
}

void CEditIDEDlg::OnRadio() 
{
}

void CEditIDEDlg::OnOK() 
{
	UpdateData( TRUE );
	UINT	id = GetCheckedRadioButton( IDC_RADIO1, IDC_RADIO3 );

	m_bModGS = FALSE;
	m_bModDB = FALSE;
	switch ( id )
	{
	case IDC_RADIO1:
		m_bModDB = TRUE;
		m_bModGS = TRUE;
		break;
	case IDC_RADIO2:
		m_bModDB = FALSE;
		m_bModGS = TRUE;
		break;
	case IDC_RADIO3:
		m_bModDB = TRUE;
		m_bModGS = FALSE;
		break;
	}

	if ( IsIDEok( m_strNeueIDE, TRUE ))
		CDialog::OnOK();
}

BOOL IsIDEok( const char* ide, BOOL melden )
{
	ASSERT( AfxIsValidString( ide ));

	BOOL		result;
	CString		strMeldung;
	CString		strIDE( ide );

	result = TRUE;
	if ( 10 != strIDE.GetLength())
	{
		strMeldung = "Die Identifikationsnummer hat genau 10 Stellen!";
		result = FALSE;
	}
	if ( result )
		if ( String2OISY( strIDE.Left( 2 )) <= 0 )
	{
		strMeldung = "Unbekannter Ortskode in der Identifikationsnummer!";
		result = FALSE;
	}
//	if ( result )
//		if ( String2ISY( strIDE.Left( 5 )) <= 0 )
//	{
//		strMeldung = "Unbekannter Straßenkode in der Identifikationsnummer!";
//		result = FALSE;
//	}

	if ( !result )
		if ( melden && !strMeldung.IsEmpty())
			AfxMessageBox( strMeldung );

	return result;
}
