///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			trmmdia.cpp
//
//	Stand:			20.03.1995
//	Beschreibung:	Dialog zu Definition von TRiAS-Merkmalen
//	Entwicklung:	20.03.95	Beginn der Kodierung
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#if defined(_USE_CONFIG_DIALOGS)

#include "resource.h"
#include "trmmdia.hpp"
#include "cxstring.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

CTriasMerkmaleDialog :: CTriasMerkmaleDialog( CWnd* pParent )
	: CDialog( CTriasMerkmaleDialog::IDD, pParent )
{	//{{AFX_DATA_INIT(CTriasMerkmaleDialog)
	//}}AFX_DATA_INIT
}

void CTriasMerkmaleDialog :: OnOK()
{	POSITION	pos;
	CxString	key, wert;

	if ( m_MMKgeaendert || m_MMBgeaendert )
	{	wert = "Nicht gespeicherte Änderungen verwerfen?";
		if ( wert.MessageBox( this, "Beenden", MB_YESNO | MB_ICONQUESTION ) == IDNO )
			return;
	}

	if ( m_bListeGeaendert )
	{	pOriginalMap -> RemoveAll();
		for ( pos = MerkmalMap.GetStartPosition(); pos != NULL; )
		{	MerkmalMap.GetNextAssoc( pos, key, wert );
			pOriginalMap -> SetAt( key, wert );
	}	}

	EndDialog( IDOK );
}

void CTriasMerkmaleDialog :: OnCancel()
{	CxString	text;

	if ( m_bListeGeaendert )
	{	text = "Änderungen verwerfen?";
		if ( text.MessageBox( this, "Abbrechen", MB_YESNO | MB_ICONQUESTION ) == IDYES )
			EndDialog( IDCANCEL );
	}
	else
		EndDialog( IDCANCEL );
}	// OnCancel

void CTriasMerkmaleDialog :: DoDataExchange( CDataExchange* pDX )
{	CDialog :: DoDataExchange( pDX );
	//{{AFX_DATA_MAP(CTriasMerkmaleDialog)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP( CTriasMerkmaleDialog, CDialog )
	ON_BN_CLICKED( IDC_BUTTON1, OnClickedDelMerkmal )
	ON_BN_CLICKED( IDC_BUTTON2, OnClickedModMerkmal )
	ON_BN_CLICKED( IDOK, OnOK )
	ON_BN_CLICKED( IDCANCEL, OnCancel )
	ON_CBN_EDITUPDATE( IDC_COMBO1, OnEditMerkmalsKode )
	ON_CBN_SELCHANGE( IDC_COMBO1, OnAuswahlMerkmalsKode )
	ON_EN_CHANGE( IDC_EDIT1, OnEditMerkmalsBez )
END_MESSAGE_MAP()

void CTriasMerkmaleDialog :: OnClickedDelMerkmal()
{	CComboBox	*pCB;
	CButton		*pBtn;
	CEdit		*pED;
	CxString	strKode, strText;
	BOOL		geloescht = FALSE;
	POSITION	pos;
	int			i;

	pCB = (CComboBox*)GetDlgItem( IDC_COMBO1 );
	pED = (CEdit*)GetDlgItem( IDC_EDIT1 );
	ASSERT( pCB );
	ASSERT( pED );

	if ( m_MMKgeaendert )		// eingegebener Kode
	{	pCB -> GetWindowText( strText );
		strText.Teilen( strKode, strText, ':' );
		if ( MerkmalMap.RemoveKey( strKode ))
			geloescht = TRUE;
	}
	else						// ausgewählter Kode
	{	i = pCB -> GetCurSel();
		if ( i != CB_ERR )
		{	pCB -> GetLBText( i, strKode );
			strKode.Teilen( strKode, strText, ':' );
			if ( MerkmalMap.RemoveKey( strKode ))
				geloescht = TRUE;
	}	}

	if ( geloescht )
	{	pCB -> ResetContent();
		for ( pos = MerkmalMap.GetStartPosition(); pos != NULL; )
		{	MerkmalMap.GetNextAssoc( pos, strKode, strText );
			strKode += ": ";
			strKode += strText;
			pCB -> AddString( strKode );
		}
		pED -> SetWindowText( "" );

		pBtn = (CButton*)GetDlgItem( IDC_BUTTON2 );
		if ( pBtn ) pBtn -> EnableWindow( FALSE );

		m_MMKgeaendert = m_MMBgeaendert = FALSE;
		m_bListeGeaendert = TRUE;
	}

	m_MMKgeaendert = FALSE;
	m_MMBgeaendert = FALSE;
	m_strMerk.Empty();
}	// OnClickedDelMerkmal()

void CTriasMerkmaleDialog :: OnClickedModMerkmal()
{	CComboBox	*pCB;
	CButton		*pBtn;
	CEdit		*pED;
	CxString	strKode, strText, strEdit;
	BOOL		geaendert = FALSE;
	POSITION	pos;
	int		i;

	pCB = (CComboBox*)GetDlgItem( IDC_COMBO1 );
	pED = (CEdit*)GetDlgItem( IDC_EDIT1 );
	ASSERT( pCB );
	ASSERT( pED );

	if ( !EingabeOK())	return;

	pED -> GetWindowText( strEdit );
	if ( m_MMKgeaendert )		// eingegebener Kode
	{	pCB -> GetWindowText( strText );
		strText.Teilen( strKode, strText, ':' );
		MerkmalMap.SetAt( strKode, strEdit );
		geaendert = TRUE;
		strEdit = strKode;
	}
	else						// ausgewählter Kode
	{	i = pCB -> GetCurSel();
		if ( i != CB_ERR )
		{	pCB -> GetLBText( i, strKode );
			strKode.Teilen( strKode, strText, ':' );
			MerkmalMap.SetAt( strKode, strEdit );
			geaendert = TRUE;
			strEdit = strKode;
	}	}

	if ( geaendert )
	{	pCB -> ResetContent();
		for ( pos = MerkmalMap.GetStartPosition(); pos != NULL; )
		{	MerkmalMap.GetNextAssoc( pos, strKode, strText );
			strKode += ": ";
			strKode += strText;
			pCB -> AddString( strKode );
		}
		pCB -> SelectString( -1, strEdit );

		pBtn = (CButton*)GetDlgItem( IDC_BUTTON2 );
		if ( pBtn ) pBtn -> EnableWindow( FALSE );

		m_MMKgeaendert = m_MMBgeaendert = FALSE;
		m_bListeGeaendert = TRUE;
	}

	m_MMKgeaendert = FALSE;
	m_MMBgeaendert = FALSE;
	m_strMerk.Empty();
}	// OnClickedModMerkmal()

BOOL CTriasMerkmaleDialog :: OnInitDialog()
{	POSITION	pos;
	CString		key, wert, eintrag;
	CComboBox	*pBox;
	CButton		*pBtn;

	pBtn = (CButton*)GetDlgItem( IDC_BUTTON1 );
	if ( pBtn ) pBtn -> EnableWindow( FALSE );

	pBtn = (CButton*)GetDlgItem( IDC_BUTTON2 );
	if ( pBtn ) pBtn -> EnableWindow( FALSE );

	pBox = (CComboBox*)GetDlgItem( IDC_COMBO1 );
	if ( CDialog::OnInitDialog())
	{	MerkmalMap.RemoveAll();
		for ( pos = pOriginalMap -> GetStartPosition();
				pos != NULL; )
		{	pOriginalMap -> GetNextAssoc( pos, key, wert );
			MerkmalMap.SetAt( key, wert );
			eintrag = key;
			eintrag += ": ";
			eintrag += wert;
			pBox -> AddString( eintrag );
	}	}
	else
		return FALSE;


	m_MMKgeaendert = m_MMBgeaendert = FALSE;
	m_bListeGeaendert = FALSE;
	return TRUE;
}	// OnInitDialog

void CTriasMerkmaleDialog :: OnEditMerkmalsKode()
{	CComboBox	*pCB;
	CButton		*pBtn;
	CEdit		*pED;
	CxString	strKode, strText;
	int			i, j;

	m_MMKgeaendert = TRUE;

	pBtn = (CButton*)GetDlgItem( IDC_BUTTON2 );
	if ( pBtn ) pBtn -> EnableWindow( FALSE );

	pBtn = (CButton*)GetDlgItem( IDC_BUTTON1 );
	if ( pBtn ) pBtn -> EnableWindow( FALSE );

	pCB = (CComboBox*)GetDlgItem( IDC_COMBO1 );
	pED = (CEdit*)GetDlgItem( IDC_EDIT1 );
	ASSERT( pCB );
	ASSERT( pED );

	if ( !m_MMBgeaendert ) pED -> SetWindowText( "" );
	if ( !m_strMerk.IsEmpty())
	{	pED -> SetWindowText( m_strMerk );
		m_strMerk.Empty();
	}

	pCB -> GetWindowText( strText );
	i = pCB -> FindString( -1, strText );
	if ( i != CB_ERR )
	{	j = pCB -> FindString( i, strText );
		if (( j == CB_ERR ) || ( j == i ))
		{	pCB -> GetLBText( i, strKode );
			strKode.Teilen( strKode, strText, ':' );
			pED -> SetWindowText( strText );

	}	}

	pBtn = (CButton*)GetDlgItem( IDC_BUTTON2 );
	if ( pBtn )
	{	if ( EingabeOK())
			pBtn -> EnableWindow( TRUE );
		else
			pBtn -> EnableWindow( FALSE );
	}
}	// OnEditMerkmalsKode

BOOL CTriasMerkmaleDialog :: EingabeOK()
{	BOOL		result = FALSE;
	CxString	strKode, strText, strEdit;
	CComboBox	*pCB;
	CEdit		*pED;

	pCB = (CComboBox*)GetDlgItem( IDC_COMBO1 );
	pED = (CEdit*)GetDlgItem( IDC_EDIT1 );
	ASSERT( pCB );
	ASSERT( pED );

//	1. mindestens eine Eingabe  -------------------------------------------
	result = (m_MMKgeaendert || m_MMBgeaendert);

	if ( result )
//	2. Kurztext vorhanden  ------------------------------------------------
	{	pED -> GetWindowText( strEdit );
		result = !strEdit.IsEmpty();
	}

	if ( result )
//	3. Kode (8 Stellen und nicht 0L)  -------------------------------------
	{	pCB -> GetWindowText( strText );
		strText.Teilen( strKode, strText, ':' );
		strKode.AllTrimm();
		if ( strKode.GetLength() != 8 ) result = FALSE;
		if ( strKode.AnzahlHexZiffern() != 8 ) result = FALSE;
	}

	if ( result )
//	4. Kode noch nicht vergeben oder Kurztext geändert  -------------------
	{	strEdit.AllTrimm();
		if ( MerkmalMap.Lookup( strKode, strText ))
			if ( strEdit == strText )
				result = FALSE;
	}
	return result;
}	// EingabeOK

void CTriasMerkmaleDialog :: OnAuswahlMerkmalsKode()
{	CComboBox	*pCB;
	CEdit		*pED;
	CButton		*pBtn;
	CxString	strText, strTemp;
	int			i;

	pCB = (CComboBox*)GetDlgItem( IDC_COMBO1 );
	pED = (CEdit*)GetDlgItem( IDC_EDIT1 );

	i = pCB -> GetCurSel();
	if ( i == CB_ERR )
	{	pBtn = (CButton*)GetDlgItem( IDC_BUTTON1 );
		if ( pBtn ) pBtn -> EnableWindow( FALSE );

		pBtn = (CButton*)GetDlgItem( IDC_BUTTON2 );
		if ( pBtn ) pBtn -> EnableWindow( FALSE );

		return;
	}

	pCB -> GetLBText( i, strText );
	strText.Teilen( strText, strTemp, ':' );
	if ( MerkmalMap.Lookup( strText, strTemp ))
		pED -> SetWindowText( strTemp );

	pBtn = (CButton*)GetDlgItem( IDC_BUTTON1 );
	if ( pBtn ) pBtn -> EnableWindow();

	pBtn = (CButton*)GetDlgItem( IDC_BUTTON2 );
	if ( pBtn ) pBtn -> EnableWindow( FALSE );

	m_MMKgeaendert = FALSE;
	m_MMBgeaendert = FALSE;
	m_strMerk.Empty();
}	// OnAuswahlMerkmalsKode

void CTriasMerkmaleDialog :: OnEditMerkmalsBez()
{	CComboBox	*pCB;
	CButton		*pBtn;
	short		i;

	m_MMBgeaendert = TRUE;
	pCB = (CComboBox*)GetDlgItem( IDC_COMBO1 );
	if ( pCB )
	{	i = pCB -> GetCurSel();
		if ( i != CB_ERR )
		{	pBtn = (CButton*)GetDlgItem( IDC_BUTTON1 );
			if ( pBtn ) pBtn -> EnableWindow();
	}	}

	pBtn = (CButton*)GetDlgItem( IDC_BUTTON2 );
	if ( pBtn )
	{	if ( EingabeOK())
			pBtn -> EnableWindow( TRUE );
		else
			pBtn -> EnableWindow( FALSE );
	}
}	// OnEditMerkmalsBez

#endif // defined(_USE_CONFIG_DIALOGS)
