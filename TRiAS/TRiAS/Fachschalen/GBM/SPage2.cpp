// SPage2.cpp : implementation file
//

#include <bool.h>
#include "stdafx.h"
#include "GbmTRiAS.h"
#include "SPage2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int g_iMessageStatus;

/////////////////////////////////////////////////////////////////////////////
// CStartPage2 property page

IMPLEMENT_DYNCREATE(CStartPage2, CPropertyPage)

CStartPage2::CStartPage2() : CPropertyPage(CStartPage2::IDD)
{
	//{{AFX_DATA_INIT(CStartPage2)
	m_strIDE = _T("");
	//}}AFX_DATA_INIT
	m_strIDE2 = _T("");
	m_pSetVerz = NULL;
	m_pSetTriDB = NULL;
	m_pmapStrassen = NULL;
	m_iCurrOISY = -1;
	m_iCurrISY = -1;
	m_bInit = FALSE;
}

CStartPage2::~CStartPage2()
{
}

void CStartPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStartPage2)
	DDX_Control(pDX, IDC_TEXT4, m_txtProjekt);
	DDX_Control(pDX, IDC_TEXT3, m_txtStrasse);
	DDX_Control(pDX, IDC_TEXT2, m_txtOrt);
	DDX_Control(pDX, IDC_TEXT1, m_txtIDE);
	DDX_Control(pDX, IDC_COMBO3, m_cbProjekt);
	DDX_Control(pDX, IDC_COMBO2, m_cbStrasse);
	DDX_Control(pDX, IDC_COMBO1, m_cbOrt);
	DDX_Control(pDX, IDC_EDIT1, m_edIDE);
	DDX_Text(pDX, IDC_EDIT1, m_strIDE);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStartPage2, CPropertyPage)
	//{{AFX_MSG_MAP(CStartPage2)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeOrt)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeStrasse)
	ON_CBN_SELCHANGE(IDC_COMBO3, OnSelchangeProjekt)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeIDE)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStartPage2 message handlers

BOOL CStartPage2::OnSetActive() 
{
	short	i;
	CString	pfad, text;

	BOOL	result = CPropertyPage::OnSetActive();

	((CPropertySheet*)GetParent()) -> SetWizardButtons( PSWIZB_BACK|PSWIZB_FINISH );

	if ( m_bInit )	return result;
	m_bInit = TRUE;

	BeginWaitCursor();

	if ( g_iMessageStatus >= 3 )
	{
		text = "Lesen TriDB";
		DEX_SetMessageString((const char*)text );
	}

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

	if ( g_iMessageStatus >= 3 )
	{
		text = "Lesen Verz";
		DEX_SetMessageString((const char*)text );
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

	if ( g_iMessageStatus >= 3 )
	{
		text = "Lesen Orte";
		DEX_SetMessageString((const char*)text );
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

	if ( g_iMessageStatus >= 3 )
	{
		text = "Lesen Projektnamen";
		DEX_SetMessageString((const char*)text );
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

	if ( g_iMessageStatus >= 3 )
	{
		text = "Lesen OrteArray";
		DEX_SetMessageString((const char*)text );
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

	text.LoadString( IDS_BEREIT );
	DEX_SetMessageString((const char*)text );

	EndWaitCursor();

	return result;
}

void CStartPage2::OnSelchangeOrt() 
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
//			if ( i == m_iCurrOISY )		return;

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
	m_strIDE2.Empty();
	if ( m_iCurrOISY >= 0 )
	{
		OISY2String( m_iCurrOISY, text );
		m_strIDE = text;
		text.Empty();
		OISY2String2( m_iCurrOISY, text );
		m_strIDE2 = text;
	}
	UpdateData( FALSE );

	SetupProjektListe();
	InitOkButton();
	EndWaitCursor();
}

void CStartPage2::OnSelchangeStrasse() 
{
	POSITION	pos;
	CString		item, key, text;

	BeginWaitCursor();

	m_iCurrISY = -1;
	m_strIDE.Empty();
	m_strIDE2.Empty();
	if ( m_iCurrOISY >= 0 )
	{
		OISY2String( m_iCurrOISY, text );
		m_strIDE = text;
		OISY2String2( m_iCurrOISY, text );
		m_strIDE2 = text;
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
				m_strIDE  += key;
				m_strIDE2 += key;
				break;
			}
		}
	}

	UpdateData( FALSE );

	SetupProjektListe();
	InitOkButton();
	EndWaitCursor();
}

void CStartPage2::OnSelchangeProjekt() 
{
	m_iCurrISY = -1;
	m_iCurrOISY = -1;
	InitOkButton();
}

void CStartPage2::OnChangeIDE() 
{
	CString	pfad, text;
	short	i;

	UpdateData( TRUE );

	m_strIDE2.Empty();
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

	if ( m_strIDE.GetLength() == 10 )
	{
		if ( m_cbProjekt.GetCount() > 1 )
			SetupProjektListe();
	}

	InitOkButton();
}

void CStartPage2::SetupProjektListe()
{
	CString		strOISY, strISY, strListe;
	CString		name;
	CxString	id, rest;
	short		i;

	if ( m_iCurrOISY < 0 )	return;
	OISY2String( m_iCurrOISY, strOISY );
	if ( strOISY.IsEmpty())	return;

	m_cbProjekt.ResetContent();

	if ( m_strIDE.GetLength() == 10 )
	{
		strOISY = m_strIDE;
		m_pSetTriDB -> GetProjekte( strOISY, strListe );
	}
	else
	{
		if ( m_iCurrISY >= 0 )
		{
			ISY2String( m_iCurrOISY, m_iCurrISY, strISY );
			if ( !strISY.IsEmpty())
				strOISY += strISY;
		}
		m_pSetTriDB -> GetProjekte( strOISY, strListe );
	}

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

void CStartPage2::InitOkButton()
{
	CString		item;
	short		i, iTriDBNr = 0;

	m_strPfad.Empty();
	if ( m_cbProjekt.GetCurSel() != CB_ERR )
	{
		m_cbProjekt.GetLBText( m_cbProjekt.GetCurSel(), item );
		for ( i = 0; i < m_arrProjName.GetSize(); i++ )
			if ( m_arrProjName[i] == item )
		{
				m_strPfad = m_arrVerz[i];
				iTriDBNr = i;
				break;
		}
	}

	if ( m_strPfad.IsEmpty())
		((CPropertySheet*)GetParent()) -> SetWizardButtons( PSWIZB_DISABLEDFINISH|PSWIZB_BACK );
	else
		((CPropertySheet*)GetParent()) -> SetWizardButtons( PSWIZB_FINISH|PSWIZB_BACK );

	if (( iTriDBNr > 0 ) && ( m_iCurrOISY < 0 ))
		m_iCurrOISY = m_pSetTriDB -> FindOISY( iTriDBNr );
}	// InitOkButton
