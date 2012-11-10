// PrintAnlaDialog.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "PrintAnlaDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrintAnlaDialog dialog


CPrintAnlaDialog::CPrintAnlaDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPrintAnlaDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrintAnlaDialog)
	m_bSort = TRUE;
	m_strObjekt = _T("");
	//}}AFX_DATA_INIT
}


void CPrintAnlaDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrintAnlaDialog)
	DDX_Control(pDX, IDC_COMBO1, m_cbUmfang);
	DDX_Check(pDX, IDC_CHECK1, m_bSort);
	DDX_Text(pDX, IDC_TEXT1, m_strObjekt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrintAnlaDialog, CDialog)
	//{{AFX_MSG_MAP(CPrintAnlaDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelectUmfang)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	ON_BN_CLICKED(IDC_RADIO7, OnRadio7)
	ON_BN_CLICKED(IDC_RADIO8, OnRadio8)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrintAnlaDialog message handlers

void CPrintAnlaDialog::OnSelectUmfang() 
{
	short		id = m_cbUmfang.GetCurSel();
	short		anla;
	CxString	text;

	anla = GetCheckedRadioButton( IDC_RADIO1, IDC_RADIO8 );
	if (( anla == IDC_RADIO8 ) && (( id == 0 ) ||	// Anlage - öff.Flächen - für ein GS
		( id == 4 ) || ( id == 5 )))				// bzw. für willkürliche Selektion
	{												// nicht definiert!
		m_cbUmfang.SetCurSel( 1 );
		MessageBeep( 0xFFFFFFFF );
		OnSelectUmfang();
		return;
	}

	switch ( id )
	{
		case 0:		// Einzelgrundstück
			m_strObjekt = m_strGrund;
			break;
		case 1:		// Straße
			m_strObjekt = m_strStr;
			if ( m_iA1 == 1 )
				text = "  ( 1 Grundstück)";
			else
				text.printf( "  ( %d Grundstücke)", m_iA1 );
			m_strObjekt += text;
			break;
		case 2:		// Ortslage
			m_strObjekt = m_strOrt;
			if ( m_iA2 == 1 )
				text = "  ( 1 Grundstück)";
			else
				text.printf( "  ( %d Grundstücke)", m_iA2 );
			m_strObjekt += text;
			break;
		case 3:		// Gesamt
			m_strObjekt = m_strOrte;
			if ( m_iA3 == 1 )
				text = "  ( 1 Grundstück)";
			else
				text.printf( "  ( %d Grundstücke)", m_iA3 );
			m_strObjekt += text;
			break;
		case 4:		// selektierte GS
			m_strObjekt = m_strSelected;
			if ( m_iA4 == 1 )	text.printf( " (%s)", m_strIDE );
			else				text.printf( " ( %d Grundstücke )", m_iA4 );
			m_strObjekt += text;
			break;
		case 5:		// markierte GS
			m_strObjekt = m_strMarked;
			if ( m_iA5 == 1 )	text.printf( " ( %s )", m_strIDE );
			else				text.printf( " ( %d Grundstücke )", m_iA5 );
			m_strObjekt += text;
			break;
	}

	SelectAnlage( 0 );
	UpdateData( FALSE );
}

void CPrintAnlaDialog::OnOK() 
{
	int		id;

	UpdateData( TRUE );

	m_iUmfang = m_cbUmfang.GetCurSel();

	id = GetCheckedRadioButton( IDC_RADIO1, IDC_RADIO8 );
	switch ( id )
	{
		case IDC_RADIO1:
			m_iSelAnlaMode = 1;
			m_iVonAnlage = 1;
			m_iBisAnlage = 1;
			break;
		case IDC_RADIO2:
			m_iSelAnlaMode = 2;
			m_iVonAnlage = 2;
			m_iBisAnlage = 2;
			break;
		case IDC_RADIO3:
			m_iSelAnlaMode = 3;
			m_iVonAnlage = 3;
			m_iBisAnlage = 3;
			break;
		case IDC_RADIO4:
			m_iSelAnlaMode = 4;
			m_iVonAnlage = 1;
			m_iBisAnlage = 3;
			break;
		case IDC_RADIO5:
			m_iSelAnlaMode = 5;
			m_iVonAnlage = 4;
			m_iBisAnlage = 4;
			break;
		case IDC_RADIO6:
			m_iSelAnlaMode = 6;
			m_iVonAnlage = 5;
			m_iBisAnlage = 5;
			break;
		case IDC_RADIO7:
			m_iSelAnlaMode = 7;
			m_iVonAnlage = 4;
			m_iBisAnlage = 5;
			break;
		case IDC_RADIO8:
			m_iSelAnlaMode = 8;
			m_iVonAnlage = 6;
			m_iBisAnlage = 6;
			break;
	}

	CDialog::OnOK();
}

void CPrintAnlaDialog::OnRadio1()	{	SelectAnlage( 1 );	}
void CPrintAnlaDialog::OnRadio2()	{	SelectAnlage( 2 );	}
void CPrintAnlaDialog::OnRadio3()	{	SelectAnlage( 3 );	}
void CPrintAnlaDialog::OnRadio4()	{	SelectAnlage( 4 );	}
void CPrintAnlaDialog::OnRadio5()	{	SelectAnlage( 5 );	}
void CPrintAnlaDialog::OnRadio6()	{	SelectAnlage( 6 );	}
void CPrintAnlaDialog::OnRadio7()	{	SelectAnlage( 7 );	}
void CPrintAnlaDialog::OnRadio8()	{	SelectAnlage( 8 );	}

BOOL CPrintAnlaDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_cbUmfang.ResetContent();
	m_cbUmfang.AddString( "Einzelgrundstück" );
	m_cbUmfang.AddString( "Straßenzug" );
	m_cbUmfang.AddString( "Ortslage" );
	m_cbUmfang.AddString( "Gesamtprojekt" );
	if ( m_iA4 > 0 )	m_cbUmfang.AddString( "Ausgewählte Grundstücke" );
	if ( m_iA5 > 0 )	m_cbUmfang.AddString( "Markierte Grundstücke" );

	if ( m_iA5 > 0 )		m_cbUmfang.SetCurSel( 5 );
	else if ( m_iA4 > 0 )	m_cbUmfang.SetCurSel( 4 );
	else					m_cbUmfang.SetCurSel( 0 );
	OnSelectUmfang();		// wird bei SetCurSel nicht(!) automatisch
							// gerufen.

	CheckRadioButton( IDC_RADIO1, IDC_RADIO8, IDC_RADIO1 );

	CWnd	*pW = GetDlgItem( IDC_CHECK1 );
	ASSERT( pW );
	pW -> EnableWindow( FALSE );

	m_iUmfang = -1;
	m_iVonAnlage = 0;
	m_iBisAnlage = 0;
	m_bSort = TRUE;

	UpdateData( FALSE );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPrintAnlaDialog::SelectAnlage( short id )
{
	CButton		*pW = (CButton*)GetDlgItem( IDC_CHECK1 );
	short		u = m_cbUmfang.GetCurSel();

	ASSERT( pW );

	if ( id == 0 )
	{
		id = GetCheckedRadioButton( IDC_RADIO1, IDC_RADIO8 );
		switch ( id )
		{	case IDC_RADIO1:	id = 1;		break;
			case IDC_RADIO2:	id = 2;		break;
			case IDC_RADIO3:	id = 3;		break;
			case IDC_RADIO4:	id = 4;		break;
			case IDC_RADIO5:	id = 5;		break;
			case IDC_RADIO6:	id = 6;		break;
			case IDC_RADIO7:	id = 7;		break;
			case IDC_RADIO8:	id = 8;		break;
	}	}

	switch ( id )
	{
		case 1:		// Anlage 1
			pW -> EnableWindow( FALSE );
			break;
		case 2:		// Anlage 2
			pW -> EnableWindow( FALSE );
			break;
		case 3:		// Anlage 3
			pW -> EnableWindow( FALSE );
			break;
		case 4:		// Anlage 1 bis 3
			pW -> EnableWindow( u > 0 );
			pW -> SetCheck( 1 );
			break;
		case 5:		// Anlage 4  (Gebührenbescheid Bl.1)
			pW -> EnableWindow( FALSE );
			break;
		case 6:		// Anlage 5  (Gebührenbescheid Bl.2)
			pW -> EnableWindow( FALSE );
			break;
		case 7:		// Anlage 4 & 5  (Gebührenbescheid Bl.1/2)
			pW -> EnableWindow( u > 0 );
			pW -> SetCheck( 1 );
			break;
		case 8:		// Anlage - öffentliche Flächen -
			pW -> EnableWindow( FALSE );
			if (( u == 0 ) || ( u == 4 ) || ( u == 5 ))
			{
				m_cbUmfang.SetCurSel( 1 );
				MessageBeep( 0xFFFFFFFF );
				OnSelectUmfang();
			}
			break;
	}
}	// SelectAnlage
