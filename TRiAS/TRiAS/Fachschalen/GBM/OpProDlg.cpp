// OpProDlg.cpp : implementation file
//

#include <bool.h>
#include "stdafx.h"
#include "GbmTRiAS.h"
#include "OpProDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenProjektDlg dialog


COpenProjektDlg::COpenProjektDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COpenProjektDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COpenProjektDlg)
	m_strIDE = _T("");
	//}}AFX_DATA_INIT
	m_pSetVerz = NULL;
	m_pSetTriDB = NULL;
	m_pmapStrassen = NULL;
	m_iCurrOISY = -1;
}


void COpenProjektDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COpenProjektDlg)
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_TEXT4, m_txtProjekt);
	DDX_Control(pDX, IDC_TEXT3, m_txtStrasse);
	DDX_Control(pDX, IDC_TEXT2, m_txtOrt);
	DDX_Control(pDX, IDC_TEXT1, m_txtIDE);
	DDX_Control(pDX, IDC_EDIT1, m_edIDE);
	DDX_Control(pDX, IDC_COMBO2, m_cbStrasse);
	DDX_Control(pDX, IDC_COMBO1, m_cbOrt);
	DDX_Control(pDX, IDC_COMBO3, m_cbProjekt);
	DDX_Text(pDX, IDC_EDIT1, m_strIDE);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COpenProjektDlg, CDialog)
	//{{AFX_MSG_MAP(COpenProjektDlg)
	ON_CBN_SELCHANGE(IDC_COMBO3, OnSelchangeProjekt)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeOrt)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeStrasse)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeIDE)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenProjektDlg message handlers

BOOL COpenProjektDlg::OnInitDialog() 
{
	short	i;
	CString	pfad;

	BeginWaitCursor();

	CDialog::OnInitDialog();

	if ( m_pSetTriDB == NULL )
	{
		m_edIDE.EnableWindow( FALSE );
		m_cbOrt.EnableWindow( FALSE );
		m_cbStrasse.EnableWindow( FALSE );
		m_txtIDE.EnableWindow( FALSE );
		m_txtOrt.EnableWindow( FALSE );
		m_txtStrasse.EnableWindow( FALSE );
	}
	else
	{
		m_edIDE.EnableWindow( TRUE );
		m_cbOrt.EnableWindow( TRUE );
		m_cbStrasse.EnableWindow( FALSE );
		m_txtIDE.EnableWindow( TRUE );
		m_txtOrt.EnableWindow( TRUE );
		m_txtStrasse.EnableWindow( FALSE );

		m_pSetTriDB -> InitListen();
	}

	if ( m_pSetVerz != NULL )
	{
		m_pSetVerz -> MoveFirst();
		while ( !m_pSetVerz -> IsEOF())
		{
			m_arrVerz.SetAtGrow( atoi( m_pSetVerz -> m_TRIDB_NR ), m_pSetVerz -> m_TRIDB_VZ );
			m_arrProjName.SetAtGrow( atoi( m_pSetVerz -> m_TRIDB_NR ), m_pSetVerz -> m_TRIDB_BZ );
			m_pSetVerz -> MoveNext();
		}
	}

	if ( m_pSetOrte != NULL )
	{
		m_pSetOrte -> InitListen();
		m_pSetOrte -> MoveFirst();
		while ( !m_pSetOrte -> IsEOF())
		{
			m_arrOrte.SetAtGrow((int)m_pSetOrte -> m_ORT_ISY, m_pSetOrte -> m_ORT_NAM );
			m_pSetOrte -> MoveNext();
		}
	}

	for ( i = 0; i < m_arrProjName.GetSize(); i++ )
	{
		pfad.Empty();
		pfad = m_arrProjName[i];
		if ( !pfad.IsEmpty())
		{
			m_cbProjekt.AddString( pfad );
		}

		if ( m_cbProjekt.GetCount() > 0 )	m_cbProjekt.SetCurSel( 0 );
		OnSelchangeProjekt();
	}

	for ( i = 0; i < m_arrOrte.GetSize(); i++ )
	{
		pfad.Empty();
		pfad = m_arrOrte[i];
		if ( !pfad.IsEmpty())
		{
			m_cbOrt.AddString( pfad );
		}
	}

	EndWaitCursor();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COpenProjektDlg::OnSelchangeProjekt() 
{
	InitOkButton();
}

void COpenProjektDlg::OnSelchangeOrt() 
{
	POSITION	pos;
	CString		item, key, text;
	short		i, n;

	BeginWaitCursor();

	if ( m_cbOrt.GetCurSel() != CB_ERR )
	{
		m_cbOrt.GetLBText( m_cbOrt.GetCurSel(), item );
		for ( i = 0; i < m_arrOrte.GetSize(); i++ )
			if ( m_arrOrte[i] == item )
				break;

		if ( i < m_arrOrte.GetSize())
		{
			// Ort nicht verändert?
			if ( i == m_iCurrOISY )		return;

			m_iCurrOISY = i;
			m_strPfad.Empty();

			m_pSetStrasse -> InitListen();
			n = m_pSetStrasse -> GetZahlStrassen( i );
			if ( n > 0 )
				m_pmapStrassen = m_pSetStrasse -> GetStrassen( i );
			else
				m_pmapStrassen = NULL;
		}
		else
		{
			m_iCurrOISY = -1;
			m_strPfad.Empty();
			m_pmapStrassen = NULL;
		}
	}
	else
	{
		m_iCurrOISY = -1;
		m_strPfad.Empty();
		m_pmapStrassen = NULL;
	}

	m_cbStrasse.ResetContent();

	if ( m_pmapStrassen != NULL )
	{
		m_cbStrasse.EnableWindow( TRUE );
		m_txtStrasse.EnableWindow( TRUE );

		for( pos = m_pmapStrassen -> GetStartPosition(); pos != NULL; )
		{
			m_pmapStrassen -> GetNextAssoc( pos, key, text );
			if ( !text.IsEmpty())
				m_cbStrasse.AddString( text );
		}
	}
	else
	{
		m_cbStrasse.EnableWindow( FALSE );
		m_txtStrasse.EnableWindow( FALSE );
	}

	m_iCurrISY = -1;
	m_strIDE.Empty();
	if ( m_iCurrOISY >= 0 )
	{
		OISY2String( m_iCurrOISY, text );
		m_strIDE = text;
	}
	UpdateData( FALSE );

	SetupProjektListe();
	InitOkButton();
	EndWaitCursor();
}	// OnSelchangeOrt

void COpenProjektDlg::OnSelchangeStrasse() 
{
	POSITION	pos;
	CString		item, key, text;

	BeginWaitCursor();

	m_iCurrISY = -1;
	m_strIDE.Empty();
	if ( m_iCurrOISY >= 0 )
	{
		OISY2String( m_iCurrOISY, text );
		m_strIDE = text;
	}

	if ( m_cbStrasse.GetCurSel() != CB_ERR )
	{
		m_cbStrasse.GetLBText( m_cbStrasse.GetCurSel(), item );
		for ( pos = m_pmapStrassen -> GetStartPosition(); pos != NULL; )
		{
			m_pmapStrassen -> GetNextAssoc( pos, key, text );
			if ( text == item )
			{
				m_iCurrISY = String2ISY( m_iCurrOISY, key );
				m_strIDE += key;
				break;
			}
		}
	}

	UpdateData( FALSE );

	SetupProjektListe();
	InitOkButton();
	EndWaitCursor();
 }	// OnSelchangeStrasse

void COpenProjektDlg::SetupProjektListe()
{
	CString		strOISY, strISY, strListe;
	CString		name;
	CxString	id, rest;
	short		i;

	if ( m_iCurrOISY < 0 )	return;
	OISY2String( m_iCurrOISY, strOISY );
	if ( strOISY.IsEmpty())	return;

	m_cbProjekt.ResetContent();

	if ( m_iCurrISY >= 0 )
	{
		ISY2String( m_iCurrOISY, m_iCurrISY, strISY );
		if ( !strISY.IsEmpty())
			strOISY += strISY;
	}
	m_pSetTriDB -> GetProjekte( strOISY, strListe );

	rest = strListe;
	while ( !rest.IsEmpty())
	{
		rest.Teilen( id, rest, ';' );
		i = atoi( id );
		if (( i > 0 ) && ( i < m_arrProjName.GetSize()))
		{
			name = m_arrProjName[i];
			m_cbProjekt.AddString( name );
		}
	}

	OISY2String2( m_iCurrOISY, strOISY );
	if ( !strISY.IsEmpty())		strOISY += strISY;
	m_pSetTriDB -> GetProjekte( strOISY, strListe );

	rest = strListe;
	while ( !rest.IsEmpty())
	{
		rest.Teilen( id, rest, ';' );
		i = atoi( id );
		if (( i > 0 ) && ( i < m_arrProjName.GetSize()))
		{
			name = m_arrProjName[i];
			m_cbProjekt.AddString( name );
		}
	}

	if ( m_cbProjekt.GetCount() > 0 )
	{
		m_txtProjekt.EnableWindow( TRUE );
		m_cbProjekt.EnableWindow( TRUE );
		m_cbProjekt.SetCurSel( 0 );
	}
	else
	{
		m_txtProjekt.EnableWindow( FALSE );
		m_cbProjekt.EnableWindow( FALSE );
	}
/*
	if ( m_cbProjekt.GetCount() > 0 )
	{
		m_txtProjekt.EnableWindow( TRUE );
		m_cbProjekt.SetCurSel( 0 );
	}
	else
		m_txtProjekt.EnableWindow( FALSE );

	if ( m_cbProjekt.GetCount() > 1 )
		m_cbProjekt.EnableWindow( TRUE );
	else
		m_cbProjekt.EnableWindow( FALSE );
*/
 }	//	SetupProjektListe

void COpenProjektDlg::OnChangeIDE() 
{
	CString	pfad, text;
	short	i;

	UpdateData( TRUE );

	if ( m_strIDE.GetLength() == 0 )
	{
		m_cbProjekt.ResetContent();

		for ( i = 0; i < m_arrProjName.GetSize(); i++ )
		{
			pfad.Empty();
			pfad = m_arrProjName[i];
			if ( !pfad.IsEmpty())
				m_cbProjekt.AddString( pfad );
		}
		if ( m_cbProjekt.GetCount() > 0 )	m_cbProjekt.SetCurSel( 0 );
		m_iCurrISY = -1;
		m_cbOrt.SetCurSel( -1 );
		m_cbStrasse.ResetContent();
		m_cbStrasse.EnableWindow( FALSE );
		m_txtStrasse.EnableWindow( FALSE );
		OnSelchangeProjekt();
		return;
	}

	if ( m_strIDE.GetLength() >= 2 )
	{
		pfad = m_strIDE.Left( 2 );
		i = String2OISY( pfad );
		if ( i != m_iCurrOISY )
		{
			pfad.Empty();
			if (( i >= 0 ) && ( i < m_arrOrte.GetSize()))
				pfad = m_arrOrte[i];
			m_cbOrt.SelectString( -1, pfad );

			OnSelchangeOrt();
		}
	}

	if ( m_strIDE.GetLength() >= 5 )
	{
		pfad = m_strIDE.Mid( 2, 3 );
		i = String2ISY( m_iCurrOISY, pfad );
		if ( i != m_iCurrISY )
		{
			m_iCurrISY = i;
			if ( m_pmapStrassen )
			{
				if ( m_pmapStrassen -> Lookup( pfad, text ))
					m_cbStrasse.SelectString( -1, text );
				else
					m_cbStrasse.SetCurSel( -1 );
			}
			OnSelchangeStrasse();
		}
	}
	else
		m_iCurrISY = -1;

	InitOkButton();
}	// OnChangeIDE

void COpenProjektDlg::InitOkButton()
{
	CString		item;
	short		i;

	m_strPfad.Empty();
	if ( m_cbProjekt.GetCurSel() != CB_ERR )
	{
		m_cbProjekt.GetLBText( m_cbProjekt.GetCurSel(), item );
		for ( i = 0; i < m_arrProjName.GetSize(); i++ )
			if ( m_arrProjName[i] == item )
				m_strPfad = m_arrVerz[i];
	}

	if ( m_strPfad.IsEmpty())	m_btnOK.EnableWindow( FALSE );
	else						m_btnOK.EnableWindow( TRUE );
}	// InitOkButton
