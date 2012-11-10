// DlgEditVorlage.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "DlgEditVorlage.h"

#include "SetVorlagen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSetVorlagen	*g_pSetVorlagen = NULL;

/////////////////////////////////////////////////////////////////////////////
// CDlgEditVorlage dialog
CDlgEditVorlage::CDlgEditVorlage(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEditVorlage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEditVorlage)
	m_strPfad = _T("");
	m_strSelectedVName = _T("");
	//}}AFX_DATA_INIT
	if ( NULL == g_pSetVorlagen )	g_pSetVorlagen = new CSetVorlagen;
	ASSERT( g_pSetVorlagen );
}


void CDlgEditVorlage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEditVorlage)
	DDX_Control(pDX, IDC_SELECT, m_btnSelect);
	DDX_Control(pDX, IDC_PREVIEW, m_btnPreview);
	DDX_Control(pDX, IDC_NEU, m_btnNeu);
	DDX_Control(pDX, IDC_EDIT, m_btnEdit);
	DDX_Control(pDX, IDC_LIST1, m_lbListe);
	DDX_Text(pDX, IDC_EDIT1, m_strPfad);
	DDX_LBString(pDX, IDC_LIST1, m_strSelectedVName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEditVorlage, CDialog)
	//{{AFX_MSG_MAP(CDlgEditVorlage)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_BN_CLICKED(IDC_NEU, OnNeu)
	ON_BN_CLICKED(IDC_PREVIEW, OnPreview)
	ON_BN_CLICKED(IDC_SELECT, OnSelect)
	ON_LBN_DBLCLK(IDC_LIST1, OnEdit)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeListe)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEditVorlage message handlers

void CDlgEditVorlage::OnEdit() 
{
	int			idx = GetSelIndex();
	CString		cmd, param;

	if ( idx < 0 )	return;
	if ( !( "vorhanden" == m_strarrStatus[idx]))	return;

	cmd = "NotePad";
	param = m_strarrPfade[idx];

	::ShellExecute( NULL, "open", cmd, param, NULL, SW_SHOWNORMAL );
}

static char BASED_CODE szFilter[] = "GBM-Vorlagen (*.gbm)|*.gbm|All Files (*.*)|*.*||";

void CDlgEditVorlage::OnNeu() 
{
	int			idx = GetSelIndex();
	CxString	cmd, param;

	if ( idx < 0 )	return;

	CFileDialog		*pDlg;
	
	if ( !( "vorhanden" == m_strarrStatus[idx]))
		pDlg = new CFileDialog( FALSE, "GBM", m_strStandardPfad,
						 OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|
						 OFN_EXPLORER,
						 szFilter, this );
	else
		pDlg = new CFileDialog( FALSE, "GBM", m_strarrPfade[idx],
						 OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|
						 OFN_EXPLORER,
						 szFilter, this );

	if ( IDOK == pDlg -> DoModal())
	{
		m_strarrPfade[idx] = pDlg -> GetPathName();
		param = pDlg -> GetPathName();

		CreateVorlage( param, m_nVType[idx]);

		if ( param.FileExist())
			m_strarrStatus[idx] = "vorhanden";
		else if (( "//" == param.Left( 2 )) || ( "\\\\" == param.Left( 2 )))
			m_strarrStatus[idx] = "netz";
		else
			m_strarrStatus[idx] = "fehler";

		if ( g_pSetVorlagen -> SelectVorlage( m_cKode[idx]))
		{
			g_pSetVorlagen -> m_Pfad = param;
			g_pSetVorlagen -> UpdateVorlage();
		}

		OnSelchangeListe();
	}
	delete pDlg;
}

void CDlgEditVorlage::OnPreview() 
{
}
  
void CDlgEditVorlage::OnSelect() 
{
	int			idx = GetSelIndex();
	CString		cmd, param;

	if ( idx < 0 )	return;

	CFileDialog		*pDlg;
	
	if ( !( "vorhanden" == m_strarrStatus[idx]))
		pDlg = new CFileDialog( TRUE, "GBM", m_strStandardPfad,
						 OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|
						 OFN_EXPLORER|OFN_FILEMUSTEXIST,
						 szFilter, this );
	else
		pDlg = new CFileDialog( TRUE, "GBM", m_strarrPfade[idx],
						 OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|
						 OFN_EXPLORER|OFN_FILEMUSTEXIST,
						 szFilter, this );

	if ( IDOK == pDlg -> DoModal())
	{
		m_strarrPfade[idx] = pDlg -> GetPathName();
		param = pDlg -> GetPathName();
		m_strarrStatus[idx] = "vorhanden";

		if ( g_pSetVorlagen -> SelectVorlage( m_cKode[idx]))
		{
			g_pSetVorlagen -> m_Pfad = param;
			g_pSetVorlagen -> UpdateVorlage();
		}

		OnSelchangeListe();
	}
	delete pDlg;
}

BOOL CDlgEditVorlage::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString	kode;
	char	c;
	short	i;

/*
	InitVorlage( "1", "Erfassungsblatt 1", 1 );
	InitVorlage( "2", "Erfassungsblatt 2", 1 );
	InitVorlage( "3", "Erfassungsblatt 3", 1 );
	InitVorlage( "4", "Anlage 1 zum Beitragsbescheid", 3 );
	InitVorlage( "5", "Anlage 2 zum Beitragsbescheid", 3 );
	InitVorlage( "7", "Beitragsbescheid", 4 );
	InitVorlage( "8", "InfoBrief zum Beitragsbescheid", 5 );
	InitVorlage( "9", "Gebührenbescheid", 4 );
	InitVorlage( "A", "InfoBrief zum Gebührenbescheid", 5 );
*/
	i = 0;
	for ( c = '1'; c <= '9'; c++ )
		if ( g_pSetVorlagen -> SelectVorlage( c ))
			if ( !g_pSetVorlagen -> m_NurLesen )
		{
			kode = c;
			InitVorlage( kode, g_pSetVorlagen -> m_Name, (short)g_pSetVorlagen -> m_Typ );
			m_cKode[i++] = c;
		}
	for ( c = 'A'; c <= 'Z'; c++ )
		if ( g_pSetVorlagen -> SelectVorlage( c ))
			if ( !g_pSetVorlagen -> m_NurLesen )
		{
			kode = c;
			InitVorlage( kode, g_pSetVorlagen -> m_Name, (short)g_pSetVorlagen -> m_Typ );
			m_cKode[i++] = c;
		}
/*
	if ( m_pSetVorlagen -> SelectVorlage( '2' ))
	{
		InitVorlage( "2", m_pSetVorlagen -> m_Name, (short)m_pSetVorlagen -> m_Typ );
		m_cKode[1] = '2';
	}
	if ( m_pSetVorlagen -> SelectVorlage( '3' ))
	{
		InitVorlage( "3", m_pSetVorlagen -> m_Name, (short)m_pSetVorlagen -> m_Typ );
		m_cKode[2] = '3';
	}
	if ( m_pSetVorlagen -> SelectVorlage( '4' ))
	{
		InitVorlage( "4", m_pSetVorlagen -> m_Name, (short)m_pSetVorlagen -> m_Typ );
		m_cKode[3] = '4';
	}
	if ( m_pSetVorlagen -> SelectVorlage( '5' ))
	{
		InitVorlage( "5", m_pSetVorlagen -> m_Name, (short)m_pSetVorlagen -> m_Typ );
		m_cKode[4] = '5';
	}
	if ( m_pSetVorlagen -> SelectVorlage( '7' ))
	{
		InitVorlage( "7", m_pSetVorlagen -> m_Name, (short)m_pSetVorlagen -> m_Typ );
		m_cKode[5] = '7';
	}
	if ( m_pSetVorlagen -> SelectVorlage( '8' ))
	{
		InitVorlage( "8", m_pSetVorlagen -> m_Name, (short)m_pSetVorlagen -> m_Typ );
		m_cKode[6] = '8';
	}
	if ( m_pSetVorlagen -> SelectVorlage( '9' ))
	{
		InitVorlage( "9", m_pSetVorlagen -> m_Name, (short)m_pSetVorlagen -> m_Typ );
		m_cKode[7] = '9';
	}
	if ( m_pSetVorlagen -> SelectVorlage( 'A' ))
	{
		InitVorlage( "A", m_pSetVorlagen -> m_Name, (short)m_pSetVorlagen -> m_Typ );
		m_cKode[8] = 'A';
	}
*/
	SetupListe();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgEditVorlage::InitVorlage( const char* key, const char* name, short type )
{
	ASSERT( AfxIsValidString( key ));
	ASSERT( AfxIsValidString( name ));

	if ( !AfxIsValidString( key ))	return;
	if ( !AfxIsValidString( name ))	return;
	if ( *name == '\0' )	return;

	CxString	item;

	m_nVType[m_strarrVListe.GetSize()] = type;
	m_strarrVListe.Add( name );

	item.Empty();
//	item.GetPrivateProfileString( "Texte", key, "GBM.INI" );
	item = g_pSetVorlagen -> m_Pfad;
	if ( item.IsEmpty())
		m_strarrPfade.Add( "" );
	else
		m_strarrPfade.Add( item );


	if ( item.IsEmpty())
		m_strarrStatus.Add( "neu" );
	else if ( item.FileExist())
		m_strarrStatus.Add( "vorhanden" );
	else if (( "//" == item.Left( 2 )) || ( "\\\\" == item.Left( 2 )))
		m_strarrStatus.Add( "netz" );
	else
		m_strarrStatus.Add( "fehler" );
}

void CDlgEditVorlage::SetupListe()
{
	m_strStandardPfad.Empty();

	m_lbListe.ResetContent();
	for ( int i = 0; i < m_strarrVListe.GetSize(); i++ )
	{
		m_lbListe.AddString( m_strarrVListe[i]);
		if ( m_strStandardPfad.IsEmpty())
			m_strStandardPfad = m_strarrPfade[i];
	}

	if ( m_lbListe.GetCount())
	{
		m_lbListe.SetCurSel( 0 );
		OnSelchangeListe();
	}
	if ( 4 < m_strStandardPfad.GetLength())
	{
		while ( !m_strStandardPfad.IsEmpty() &&
				( "/" != m_strStandardPfad.Right(1)) &&
				( "\\" != m_strStandardPfad.Right(1)))
		{
			m_strStandardPfad = m_strStandardPfad.Left( m_strStandardPfad.GetLength() - 1 );
		}
		if ( !m_strStandardPfad.IsEmpty())
			m_strStandardPfad = m_strStandardPfad.Left( m_strStandardPfad.GetLength() - 1 );
	}
	UpdateData( FALSE );
}

void CDlgEditVorlage::OnSelchangeListe() 
{
	UpdateData( TRUE );

/*
	int		idx = -1;

	for ( int i = 0; i < m_strarrVListe.GetSize(); i++ )
		if ( m_strarrVListe[i] == m_strSelectedVName )
	{
		idx = i;
		break;
	}
*/
	int		idx = GetSelIndex();
	if ( idx < 0 )	return;
	m_strPfad = m_strarrPfade[idx];

	m_btnNeu.EnableWindow( !("vorhanden" == m_strarrStatus[idx]));
	m_btnEdit.EnableWindow( "vorhanden" == m_strarrStatus[idx]);
	m_btnPreview.EnableWindow( FALSE );
	m_btnSelect.EnableWindow( TRUE );

	UpdateData( FALSE );
}

int CDlgEditVorlage::GetSelIndex()
{
	int		idx = -1;

	for ( int i = 0; i < m_strarrVListe.GetSize(); i++ )
		if ( m_strarrVListe[i] == m_strSelectedVName )
	{
		idx = i;
		break;
	}
	return idx;
}

BOOL CDlgEditVorlage::CreateVorlage( const char* filename, short type )
{
	BOOL			result = FALSE;
	CFile			file;
	CFileException	e;
	HRSRC			hRes; // resource handle to MDB-File
	HGLOBAL			hData;
	HINSTANCE		hInst;
	DWORD			size;
	CString			name;
	void			*ptr;
	BOOL			bOk = FALSE;
	BOOL			bOpen = FALSE;
	UINT			nResID = 0;

	switch ( type )
	{
	case 1:	nResID = IDR_ERFASS;
			break;
	case 2:	nResID = IDR_ERFASS;
			break;
	case 3:	nResID = IDR_ANLAGE;
			break;
	case 4:	nResID = IDR_BESCHEID;
			break;
	case 5:	nResID = IDR_INFOBRIEF;
			break;
	}

	if ( nResID )
		if ( hInst = AfxFindResourceHandle( MAKEINTRESOURCE( nResID ), "VORLAGE" ))
			if (( hRes = ::FindResource( hInst, MAKEINTRESOURCE( nResID ), "VORLAGE" )) != NULL )
				if (( hData = ::LoadResource( hInst, hRes )) != NULL)
	{
		name = filename;
		if ( name.IsEmpty())	return FALSE;

		if ( !name.IsEmpty())
		{
			ptr  = ::LockResource( hData );
			size = ::SizeofResource( AfxGetResourceHandle(), hRes );
			if ( !file.Open( name, CFile::modeWrite|CFile::modeCreate|CFile::shareExclusive, &e ))
			{
				#ifdef _DEBUG
				afxDump << "Datei " << name << " kann nicht geöffnet werden. " << e.m_cause << "\n";
				#endif
			}
			else
			{
				file.WriteHuge( ptr, size );
				file.Close();
			}
			FreeResource(hData);

	}	}

	return result;
}
