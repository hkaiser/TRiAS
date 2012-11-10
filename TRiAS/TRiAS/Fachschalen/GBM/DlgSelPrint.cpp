// DlgSelPrint.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "DlgSelPrint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSelPrint dialog


CDlgSelPrint::CDlgSelPrint(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelPrint::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSelPrint)
	m_strObjekt = _T("");
	//}}AFX_DATA_INIT
	m_bSort = FALSE;

	m_bDok1 = m_bVoll1 = TRUE;
	m_bDok2 = m_bVoll2 = TRUE;
	m_bDok3 = m_bVoll3 = TRUE;
	m_bDok4 = m_bVoll4 = TRUE;
	m_bD1S1 = m_bD1S2 = m_bD1S3 = TRUE;
	m_bD2S1 = m_bD2S2 = m_bD2S3 = TRUE;
	m_bD3S1 = m_bD3S2 = m_bD3S3 = TRUE;
	m_bD4S1 = TRUE;

	m_bExist7 = m_bExist8 = m_bExist9 = m_bExistA = m_bExistB = FALSE;
}


void CDlgSelPrint::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSelPrint)
	DDX_Control(pDX, IDC_LIST2, m_lbListe2);
	DDX_Control(pDX, IDC_LIST1, m_lbListe1);
	DDX_Control(pDX, IDC_COMBO1, m_cbUmfang);
	DDX_Text(pDX, IDC_TEXT1, m_strObjekt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSelPrint, CDialog)
	//{{AFX_MSG_MAP(CDlgSelPrint)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeListe1)
	ON_LBN_SELCHANGE(IDC_LIST2, OnSelchangeListe2)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelectUmfang)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSelPrint message handlers

BOOL CDlgSelPrint::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString		text;
//	char*		txt;

	if ( !m_strCaption.IsEmpty())
		SetWindowText( m_strCaption );

//	text.Empty();	txt = text.GetBuffer( 256 );
//	GetPrivateProfileString( "Texte", "7", "", txt, 256, "GBM.INI" );
//	text.ReleaseBuffer();
	text = GetVorlageFileName( '7' );
	if ( !text.IsEmpty())	m_bExist7 = FileExist( text );

//	text.Empty();	txt = text.GetBuffer( 256 );
//	GetPrivateProfileString( "Texte", "8", "", txt, 256, "GBM.INI" );
//	text.ReleaseBuffer();
	text = GetVorlageFileName( '8' );
	if ( !text.IsEmpty())	m_bExist8 = FileExist( text );

//	text.Empty();	txt = text.GetBuffer( 256 );
//	GetPrivateProfileString( "Texte", "9", "", txt, 256, "GBM.INI" );
//	text.ReleaseBuffer();
	text = GetVorlageFileName( '9' );
	if ( !text.IsEmpty())	m_bExist9 = FileExist( text );

//	text.Empty();	txt = text.GetBuffer( 256 );
//	GetPrivateProfileString( "Texte", "A", "", txt, 256, "GBM.INI" );
//	text.ReleaseBuffer();
	text = GetVorlageFileName( 'A' );
	if ( !text.IsEmpty())	m_bExistA = FileExist( text );

//	text.Empty();	txt = text.GetBuffer( 256 );
//	GetPrivateProfileString( "Texte", "B", "", txt, 256, "GBM.INI" );
//	text.ReleaseBuffer();
	text = GetVorlageFileName( 'B' );
	if ( !text.IsEmpty())	m_bExistB = FileExist( text );

	m_lbListe1.AddString( "Erfassungsblätter" );
	m_lbListe1.AddString( "Beitragsbescheid" );
	m_lbListe1.AddString( "Gebührenbescheid" );
	m_lbListe1.AddString( "Lageskizze" );
	m_lbListe1.SetCheck( 0, m_bDok1 ? 1 : 0 );
	m_lbListe1.SetCheck( 1, m_bDok2 ? 1 : 0 );
	m_lbListe1.SetCheck( 2, m_bDok3 ? 1 : 0 );
	if ( m_bExistB )
		m_lbListe1.SetCheck( 3, 1 );
	else
	{
		m_lbListe1.SetCheck( 3, 0 );
		m_lbListe1.Enable( 3, FALSE );
	}
	m_lbListe1.SetCurSel( 0 );
	OnSelchangeListe1();
	
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

	m_iUmfang = -1;
	m_iVonAnlage = 0;
	m_iBisAnlage = 0;

	UpdateData( FALSE );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSelPrint::OnSelchangeListe1() 
{
	int		idx = m_lbListe1.GetCurSel();
	int		check;

	m_lbListe2.ResetContent();
	if ( idx < 0 )		return;
	check = m_lbListe1.GetCheck( idx );

	switch ( idx )
	{
	case 0:
		m_lbListe2.AddString( "Blatt 1" );
		m_lbListe2.AddString( "Blatt 2" );
		m_lbListe2.AddString( "Blatt 3" );
		if (( m_bDok1 && ( check == 0 )) ||
			( !m_bDok1 && ( check == 1 )))
		{
			m_bDok1 = ( check == 1 );
			m_bD1S1 = ( check == 1 );
			m_bD1S2 = ( check == 1 );
			m_bD1S3 = ( check == 1 );
		}
		m_lbListe2.SetCheck( 0, m_bD1S1 ? 1 : 0 );
		m_lbListe2.SetCheck( 1, m_bD1S2 ? 1 : 0 );
		m_lbListe2.SetCheck( 2, m_bD1S3 ? 1 : 0 );
		break;
	case 1:
		m_lbListe2.AddString( "Beitragsbescheid" );
		m_lbListe2.AddString( "Infobrief" );
		m_lbListe2.AddString( "Anlage" );
		if (( m_bDok2 && ( check == 0 )) ||
			( !m_bDok2 && ( check == 1 )))
		{
			m_bDok2 = ( check == 1 );
			m_bD2S1 = (( check == 1 ) && m_bExist7 );
			m_bD2S2 = (( check == 1 ) && m_bExist8 );
			m_bD2S3 = ( check == 1 );
		}
		if ( m_bExist7 )	m_lbListe2.SetCheck( 0, m_bD2S1 ? 1 : 0 );
		else
		{
			m_lbListe2.SetCheck( 0, 0 );
			m_lbListe2.Enable( 0, FALSE );
		}
		if ( m_bExist8 )	m_lbListe2.SetCheck( 1, m_bD2S2 ? 1 : 0 );
		else
		{
			m_lbListe2.SetCheck( 1, 0 );
			m_lbListe2.Enable( 1, FALSE );
		}
		m_lbListe2.SetCheck( 2, m_bD2S3 ? 1 : 0 );
		break;
	case 2:
		m_lbListe2.AddString( "Gebührenbescheid" );
		m_lbListe2.AddString( "Infobrief" );
		m_lbListe2.AddString( "Anlage" );
		if (( m_bDok3 && ( check == 0 )) ||
			( !m_bDok3 && ( check == 1 )))
		{
			m_bDok3 = ( check == 1 );
			m_bD3S1 = (( check == 1 ) && m_bExist9 );
			m_bD3S2 = (( check == 1 ) && m_bExistA );
			m_bD3S3 = ( check == 1 );
		}
		if ( m_bExist9 )	m_lbListe2.SetCheck( 0, m_bD3S1 ? 1 : 0 );
		else
		{
			m_lbListe2.SetCheck( 0, 0 );
			m_lbListe2.Enable( 0, FALSE );
		}
		if ( m_bExistA )	m_lbListe2.SetCheck( 1, m_bD3S2 ? 1 : 0 );
		else
		{
			m_lbListe2.SetCheck( 1, 0 );
			m_lbListe2.Enable( 1, FALSE );
		}
		m_lbListe2.SetCheck( 2, m_bD3S3 ? 1 : 0 );
		break;
	case 3:
		m_lbListe2.AddString( "massstabsgerechte Lageskizze" );
		if (( m_bDok4 && ( check == 0 )) ||
			( !m_bDok4 && ( check == 1 )))
		{
			m_bDok4 = ( check == 1 );
			m_bD4S1 = (( check == 1 ) && m_bExistB );
		}
		if ( m_bExistB )	m_lbListe2.SetCheck( 0, m_bD4S1 ? 1 : 0 );
		else				m_lbListe2.SetCheck( 0, 2 );
		break;
	}
}

void CDlgSelPrint::OnOK() 
{
	UpdateData( TRUE );

	m_iUmfang = m_cbUmfang.GetCurSel();

	m_iSelAnlaMode = 0;
	if ( m_bD1S1 )				m_iSelAnlaMode +=   1;
	if ( m_bD1S2 )				m_iSelAnlaMode +=   2;
	if ( m_bD1S3 )				m_iSelAnlaMode +=   4;
	if ( m_bD2S1 && m_bExist7 )	m_iSelAnlaMode +=   8;
	if ( m_bD2S2 && m_bExist8 )	m_iSelAnlaMode +=  16;
	if ( m_bD2S3 )				m_iSelAnlaMode +=  32;
	if ( m_bD3S1 && m_bExist9 )	m_iSelAnlaMode +=  64;
	if ( m_bD3S2 && m_bExistA )	m_iSelAnlaMode += 128;
	if ( m_bD3S3 )				m_iSelAnlaMode += 256;
	if ( m_bD4S1 && m_bExistB )	m_iSelAnlaMode += 512;

	CDialog::OnOK();
}

void CDlgSelPrint::OnSelchangeListe2() 
{
	int		idx = m_lbListe1.GetCurSel();
	int		check;

	if ( idx < 0 )		return;

	switch ( idx )
	{
	case 0:
		m_bD1S1 = ( m_lbListe2.GetCheck( 0 ) == 1 );
		m_bD1S2 = ( m_lbListe2.GetCheck( 1 ) == 1 );
		m_bD1S3 = ( m_lbListe2.GetCheck( 2 ) == 1 );
		check = 0;
		if ( m_bD1S1 && m_bD1S2 && m_bD1S3 )		check = 1;
		else if ( m_bD1S1 || m_bD1S2 || m_bD1S3 )	check = 2;
		m_lbListe1.SetCheck( 0, check );
		break;
	case 1:
		m_bD2S1 = ( m_lbListe2.GetCheck( 0 ) == 1 );
		m_bD2S2 = ( m_lbListe2.GetCheck( 1 ) == 1 );
		m_bD2S3 = ( m_lbListe2.GetCheck( 2 ) == 1 );
		check = 0;
		if ( m_bD2S1 && m_bD2S2 && m_bD2S3 )		check = 1;
		else if ( m_bD2S1 || m_bD2S2 || m_bD2S3 )	check = 2;
		m_lbListe1.SetCheck( 1, check );
		break;
	case 2:
		m_bD3S1 = ( m_lbListe2.GetCheck( 0 ) == 1 );
		m_bD3S2 = ( m_lbListe2.GetCheck( 1 ) == 1 );
		m_bD3S3 = ( m_lbListe2.GetCheck( 2 ) == 1 );
		check = 0;
		if ( m_bD3S1 && m_bD3S2 && m_bD3S3 )		check = 1;
		else if ( m_bD3S1 || m_bD3S2 || m_bD3S3 )	check = 2;
		m_lbListe1.SetCheck( 2, check );
		break;
	case 3:
		m_bD4S1 = ( m_lbListe2.GetCheck( 0 ) == 1 );
		check = 0;
		if ( m_bD1S1 )		check = 1;
		m_lbListe1.SetCheck( 0, check );
		break;
	}
}

void CDlgSelPrint::OnSelectUmfang() 
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

	UpdateData( FALSE );
}
