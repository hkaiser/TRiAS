///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			artdia.cpp
//
//	Stand:			01.06.1995
//	Beschreibung:	Dialog zur Zuordnung von EDBS- und TRiAS-Ident.
//	Entwicklung:	01.06.95	Beginn der Kodierung
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#if defined(_USE_CONFIG_DIALOGS)

#include "resource.h"
#include "artdia.hpp"
#include "cxstring.h"
#include <ctype.h>
#include "editmerk.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

CArtDialog :: CArtDialog( CWnd* pParent )
	: CDialog( CArtDialog::IDD, pParent )
{	//{{AFX_DATA_INIT(CArtDialog)
	//}}AFX_DATA_INIT
	m_modified = FALSE;
}

void CArtDialog :: OnOK()
{	CxString	key, wert;

	if ( m_DL.NotSavedEdit())
	{	wert = "Nicht gespeicherte Änderungen verwerfen?";
		if ( wert.MessageBox( this, "Beenden", MB_YESNO | MB_ICONQUESTION ) == IDNO )
			return;
	}

	if ( Modified())
	{	CopyMap( pmapArtTexte, &ArtTexteMap );
		CopyMap( pmapTRIAS_Ident, &TriasIdentMap );
		CopyMap( pmapTRIAS_xIdent, &TriasXIdentMap );
		CopyMap( pmapTRIAS_MM, &TriasMMMap );
		CopyMap( pmapEDBS_Ident, &EdbsIdentMap );
		CopyMap( pmapAttribTexte, &AttribTexteMap );
		CopyMap( pmapWertTexte, &WertTexteMap );
		CopyMap( pmapBedingungen, &BedingungenMap );
		CopyMap( pmapAlias, &AliasMap );
	}

	EndDialog( IDOK );
}

void CArtDialog :: CopyMap( CMapStringToString *z, CMapStringToString *q )
{	POSITION	pos;
	CString		key, wert;

	z -> RemoveAll();
	for ( pos = q -> GetStartPosition(); pos != NULL; )
	{	q -> GetNextAssoc( pos, key, wert );
		z -> SetAt( key, wert );
	}
}	// CopyMap

BOOL CArtDialog :: Modified()
{	BOOL	result;

	result = ( m_DL.Modified() || m_modified );
	return result;
}	// Modified

void CArtDialog :: OnCancel()
{	CxString	text;

	if ( Modified())
	{	text = "Änderungen verwerfen?";
		if ( text.MessageBox( this, "Abbrechen", MB_YESNO | MB_ICONQUESTION ) == IDYES )
			EndDialog( IDCANCEL );
	}
	else
		EndDialog( IDCANCEL );
}	// OnCancel

void CArtDialog :: DoDataExchange( CDataExchange* pDX )
{	CDialog :: DoDataExchange( pDX );
	//{{AFX_DATA_MAP(CArtDialog)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP( CArtDialog, CDialog )
	ON_BN_CLICKED( IDC_BUTTON1, OnClickedDelMerkmal )
	ON_BN_CLICKED( IDC_BUTTON2, OnClickedModMerkmal )
	ON_BN_CLICKED( IDOK, OnOK )
	ON_BN_CLICKED( IDCANCEL, OnCancel )
	ON_BN_CLICKED( IDC_CHECK1, OnChangeXMark )
	ON_BN_CLICKED( IDC_BUTTON3, OnClickedModBed )
	ON_BN_CLICKED( IDC_BUTTON4, OnClickedDelBed )
	ON_BN_CLICKED( IDC_BUTTON5, OnClickedModAlias )
	ON_BN_CLICKED( IDC_BUTTON6, OnClickedDelAlias )
	ON_BN_CLICKED( IDC_BUTTON7, OnClickedAdvBed )
	ON_BN_CLICKED( IDC_BUTTON8, OnClickedAdvAlias )
	ON_CBN_EDITUPDATE( IDC_COMBO1, OnEditIdentKode )
	ON_CBN_SELCHANGE( IDC_COMBO1, OnAuswahlIdentKode )
	ON_EN_CHANGE( IDC_EDIT1, OnEditIdentBez )
	ON_CBN_SELCHANGE( IDC_COMBO2, OnAuswahlTriasIdent )
END_MESSAGE_MAP()

void CArtDialog :: OnClickedDelMerkmal()
{	CxString	eintrag, old_ident;
	CComboBox	*pCB;
	int			i;

	if ( !m_strCurrIdent.IsEmpty())
	{	EdbsIdentMap.RemoveKey( m_strCurrIdent );
	}

	m_DL.OnClickedDel();

	pCB = (CComboBox*)GetDlgItem( IDC_COMBO1 );
	ASSERT( pCB );
	i = pCB -> GetCurSel();
	if ( i == CB_ERR )
		m_strCurrIdent.Empty();
	else
	{	pCB -> GetLBText( i, eintrag );
		eintrag.Teilen( m_strCurrIdent, old_ident, ':' );
	}

}	// OnClickedDelMerkmal()

void CArtDialog :: OnClickedModMerkmal()
{	CxString	key, eintrag, old_ident;
	CComboBox	*pCB;
	int			i;
	CButton		*pB;

	m_DL.OnClickedMod();

	pCB = (CComboBox*)GetDlgItem( IDC_COMBO1 );
	ASSERT( pCB );
	i = pCB -> GetCurSel();
	if ( i == CB_ERR )
		key.Empty();
	else
	{	pCB -> GetLBText( i, eintrag );
		eintrag.Teilen( key, old_ident, ':' );
	}

	if ( key != m_strCurrIdent ) m_strCurrIdent = key;

	if ( !m_strCurrIdent.IsEmpty())
	{	old_ident.Empty();
		EdbsIdentMap.Lookup( m_strCurrIdent, old_ident );
		pCB = (CComboBox*)GetDlgItem( IDC_COMBO2 );
		ASSERT( pCB );
		i = pCB -> GetCurSel();
		if ( i != CB_ERR )
		{	pCB -> GetLBText( i, eintrag );
			if ( eintrag != old_ident )
			{	m_modified = TRUE;
				if ( eintrag == "*** ohne ***" )
				{	ArtTexteMap.RemoveKey( m_strCurrIdent );
					EdbsIdentMap.RemoveKey( m_strCurrIdent );
				}
				else
					EdbsIdentMap.SetAt( m_strCurrIdent, eintrag );
	}	}	}


	pB = (CButton*)GetDlgItem( IDC_BUTTON1 );
	ASSERT( pB );
	pB -> EnableWindow( FALSE );


	pB = (CButton*)GetDlgItem( IDC_BUTTON2 );
	ASSERT( pB );
	pB -> EnableWindow( FALSE );

}	// OnClickedModMerkmal()

void CArtDialog :: OnChangeXMark()
{	InitTriasIdents();
}	// OnChangeXMark

BOOL CArtDialog :: OnInitDialog()
{	POSITION	pos;
	CxString	key, wert, eintrag;
	CComboBox	*pBox;
	CButton		*pBtn1, *pBtn2;
	CEdit		*pED;

	m_strCurrIdent.Empty();

	pBtn1 = (CButton*)GetDlgItem( IDC_BUTTON1 );
	if ( pBtn1 ) pBtn1 -> EnableWindow( FALSE );

	pBtn2 = (CButton*)GetDlgItem( IDC_BUTTON2 );
	if ( pBtn2 ) pBtn2 -> EnableWindow( FALSE );

	pBox = (CComboBox*)GetDlgItem( IDC_COMBO1 );
	if ( CDialog::OnInitDialog())
	{	ArtTexteMap.RemoveAll();
		for ( pos = pmapArtTexte -> GetStartPosition();
				pos != NULL; )
		{	pmapArtTexte -> GetNextAssoc( pos, key, wert );
			ArtTexteMap.SetAt( key, wert );
			eintrag = key;
			eintrag += ": ";
			eintrag += wert;
			pBox -> AddString( eintrag );
		}

		CopyMap( &TriasIdentMap, pmapTRIAS_Ident );
		CopyMap( &TriasXIdentMap, pmapTRIAS_xIdent );
		CopyMap( &TriasMMMap, pmapTRIAS_MM );
		CopyMap( &EdbsIdentMap, pmapEDBS_Ident );
		CopyMap( &AttribTexteMap, pmapAttribTexte );
		CopyMap( &WertTexteMap, pmapWertTexte );
		CopyMap( &BedingungenMap, pmapBedingungen );
		CopyMap( &AliasMap, pmapAlias );
	}
	else
		return FALSE;

	pED = (CEdit*)GetDlgItem( IDC_EDIT1 );
	m_DL.SetElements( pBox, pED, pBtn1, pBtn2,
					&ArtTexteMap, CDefMMList::TestMode4 );

	key = m_strStartIdent;
	if ( !key.IsEmpty())
	{	if (( pBox -> SelectString( -1, key )) == CB_ERR )
			pBox -> SetWindowText( key );
		else
			OnAuswahlIdentKode();
	}

	pmapLastMap = NULL;
	InitTriasIdents();
	return TRUE;
}	// OnInitDialog

void CArtDialog :: InitTriasIdents()
{	CButton				*pCheck;
	CComboBox			*pCB;
	CListBox			*pLB;
	CMapStringToString	*pIdentMap;
	POSITION			pos;
	CxString			key, wert, eintrag;
	BOOL				nicht_leer;
	int					i;

	pCheck = (CButton*)GetDlgItem( IDC_CHECK1 );
	pCB = (CComboBox*)GetDlgItem( IDC_COMBO2 );
	ASSERT( pCheck );
	ASSERT( pCB );

	if ( pCheck -> GetCheck())
		pIdentMap = &TriasXIdentMap;
	else
		pIdentMap = &TriasIdentMap;

	if ( pmapLastMap != pIdentMap )
	{	pCB -> ResetContent();
		pmapLastMap = pIdentMap;
		pCB -> AddString( "*** ohne ***" );
		for ( pos = pIdentMap -> GetStartPosition();
					pos != NULL; )
		{	pIdentMap -> GetNextAssoc( pos, key, wert );
			eintrag = key;
			eintrag += ": ";
			eintrag += wert;
			pCB -> AddString( eintrag );
	}	}

	pCB -> SetCurSel( 0 );
	if ( !m_strCurrIdent.IsEmpty())
		if ( EdbsIdentMap.Lookup( m_strCurrIdent, eintrag ))
			pCB -> SelectString( -1, eintrag );

	pLB = (CListBox*)GetDlgItem( IDC_LIST1 );
	ASSERT( pLB );

	i = 0;
	nicht_leer = FALSE;
	pLB -> ResetContent();
	key = m_strCurrIdent;
	wert.printf( "%s+%d", (const char*)key, ++i );
	eintrag.Empty();
	BedingungenMap.Lookup( wert, eintrag );
	while ( !eintrag.IsEmpty())
	{	pLB -> AddString( eintrag );
		wert.printf( "%s+%d", (const char*)key, ++i );
		eintrag.Empty();
		BedingungenMap.Lookup( wert, eintrag );
		nicht_leer = TRUE;
	}

	if ( nicht_leer )
	{	pLB -> SetCurSel( 0 );
		EnableButton( IDC_BUTTON3 );
		EnableButton( IDC_BUTTON4 );
		EnableButton( IDC_BUTTON7 );
	}
	else
	{	EnableButton( IDC_BUTTON3, FALSE );
		EnableButton( IDC_BUTTON4, FALSE );
		EnableButton( IDC_BUTTON7, FALSE );
	}

	pLB = (CListBox*)GetDlgItem( IDC_LIST2 );
	ASSERT( pLB );

	i = 0;
	nicht_leer = FALSE;
	pLB -> ResetContent();
	wert.printf( "%s+%d", (const char*)key, ++i );
	eintrag.Empty();
	AliasMap.Lookup( wert, eintrag );
	while ( !eintrag.IsEmpty())
	{	pLB -> AddString( eintrag );
		wert.printf( "%s+%d", (const char*)key, ++i );
		eintrag.Empty();
		AliasMap.Lookup( wert, eintrag );
		nicht_leer = TRUE;
	}

	if ( nicht_leer )
	{	pLB -> SetCurSel( 0 );
		EnableButton( IDC_BUTTON5 );
		EnableButton( IDC_BUTTON6 );
		EnableButton( IDC_BUTTON8 );
	}
	else
	{	EnableButton( IDC_BUTTON5, FALSE );
		EnableButton( IDC_BUTTON6, FALSE );
		EnableButton( IDC_BUTTON8, FALSE );
	}

}	// InitTriasIdents

void CArtDialog :: OnEditIdentKode()
{	CComboBox	*pCB;
	CListBox	*pLB;
	CxString	strText, strKey, strT1, strT2, strT3;
	int			i;

	pCB = (CComboBox*)GetDlgItem( IDC_COMBO1 );
	pLB = (CListBox*)GetDlgItem( IDC_LIST1 );
	ASSERT( pCB );
	ASSERT( pLB );

	i = pCB -> GetCurSel();
	if ( i != CB_ERR )
	{
		pCB -> GetLBText( i, strText );
		strText.Teilen( strKey, strT1, ' ' );
	}

	m_DL.OnEditKode();
}	// OnEditIdentKode

void CArtDialog :: OnAuswahlIdentKode()
{	CComboBox	*pCB;
	CButton		*pCheck;
	CxString	strText, strKey;
	int			i;

	pCB = (CComboBox*)GetDlgItem( IDC_COMBO1 );
	pCheck = (CButton*)GetDlgItem( IDC_CHECK1 );
	ASSERT( pCB );
	ASSERT( pCheck );

	m_DL.OnAuswahlKode();

	i = pCB -> GetCurSel();
	if ( i != CB_ERR )
	{	pCB -> GetLBText( i, strText );
		strText.Teilen( strKey, strText, ':' );
		m_strCurrIdent = strKey;
	}
	else
		m_strCurrIdent.Empty();

	if ( !m_strCurrIdent.IsEmpty())
		if ( EdbsIdentMap.Lookup( m_strCurrIdent, strKey ))
			pCheck -> SetCheck( strKey.AnzahlHexZiffern() < 8 );

	InitTriasIdents();
}	// OnAuswahlIdentKode

void CArtDialog :: OnAuswahlTriasIdent()
{	CButton		*pB;

	pB = (CButton*)GetDlgItem( IDC_BUTTON2 );
	ASSERT( pB );
	pB -> EnableWindow();

}	// OnAuswahlTriasIdent

void CArtDialog :: OnEditIdentBez()
{	m_DL.OnEditBez();
}	// OnEditIdentBez

void CArtDialog :: SetStartIdent( const char *txt )
{	if ( txt )	m_strStartIdent = txt;
	else		m_strStartIdent = "";
}	// SetStartIdent

void CArtDialog :: OnClickedDelBed()
{	CListBox	*pLB;
	CxString	eintrag, key, wert, tag;
	int			i;
	BOOL		loesch;

	m_modified = TRUE;

	pLB = (CListBox*)GetDlgItem( IDC_LIST1 );
	ASSERT( pLB );

	i = pLB -> GetCurSel();		// zu löschender Eintrag
	if ( i != LB_ERR )
	{	pLB -> GetText( i, tag );
		pLB -> DeleteString( i );
		if ( pLB -> GetCount())
		{	if ( pLB -> GetCount() < ( i + 1 ))
				pLB -> SetCurSel( i - 1 );	// am Ende
			else
				pLB -> SetCurSel( i );		// aus der Mitte
		}
		else		// der letzte Eintrag
		{	EnableButton( IDC_BUTTON3, FALSE );
			EnableButton( IDC_BUTTON4, FALSE );
			EnableButton( IDC_BUTTON7, FALSE );
		}

		i = 0;
		loesch = FALSE;
		key.printf( "%s+%d", (const char*)m_strCurrIdent, ++i );
		eintrag.Empty();
		BedingungenMap.Lookup( key, eintrag );
		while ( !eintrag.IsEmpty())
		{	if ( loesch )	// ==> vorherigen Eintrag überschreiben
			{	BedingungenMap.RemoveKey( key );
				key.printf( "%s+%d",
					(const char*)m_strCurrIdent, ( i-1 ));
				BedingungenMap.SetAt( key, eintrag );
			}
			else
				if ( eintrag == tag ) loesch = TRUE;

			if ( loesch )	// ==> aktuellen Eintrag löschen
			{	key.printf( "%s+%d", (const char*)m_strCurrIdent, i );
				BedingungenMap.RemoveKey( key );
			}

			key.printf( "%s+%d", (const char*)m_strCurrIdent, ++i );
			eintrag.Empty();
			BedingungenMap.Lookup( key, eintrag );
	}	}
}	// OnClickedDelBed

void CArtDialog :: OnClickedModBed()
{
	CEditMerkmal	dlg;

	dlg.DoModal();
	m_modified = TRUE;

}	// OnClickedModBed

void CArtDialog :: OnClickedAdvBed()
{
	m_modified = TRUE;

}	// OnClickedAdvBed

void CArtDialog :: OnClickedDelAlias()
{	CListBox	*pLB;
	CxString	eintrag, key, wert, tag;
	int			i;
	BOOL		loesch;

	m_modified = TRUE;

	pLB = (CListBox*)GetDlgItem( IDC_LIST2 );
	ASSERT( pLB );

	i = pLB -> GetCurSel();		// zu löschender Eintrag
	if ( i != LB_ERR )
	{	pLB -> GetText( i, tag );
		pLB -> DeleteString( i );
		if ( pLB -> GetCount())
		{	if ( pLB -> GetCount() < ( i + 1 ))
				pLB -> SetCurSel( i - 1 );	// am Ende
			else
				pLB -> SetCurSel( i );		// aus der Mitte
		}
		else		// der letzte Eintrag
		{	EnableButton( IDC_BUTTON5, FALSE );
			EnableButton( IDC_BUTTON6, FALSE );
			EnableButton( IDC_BUTTON8, FALSE );
		}

		i = 0;
		loesch = FALSE;
		key.printf( "%s+%d", (const char*)m_strCurrIdent, ++i );
		eintrag.Empty();
		AliasMap.Lookup( key, eintrag );
		while ( !eintrag.IsEmpty())
		{	if ( loesch )	// ==> vorherigen Eintrag überschreiben
			{	AliasMap.RemoveKey( key );
				key.printf( "%s+%d",
					(const char*)m_strCurrIdent, ( i-1 ));
				AliasMap.SetAt( key, eintrag );
			}
			else
				if ( eintrag == tag ) loesch = TRUE;

			if ( loesch )	// ==> aktuellen Eintrag löschen
			{	key.printf( "%s+%d", (const char*)m_strCurrIdent, i );
				AliasMap.RemoveKey( key );
			}

			key.printf( "%s+%d", (const char*)m_strCurrIdent, ++i );
			eintrag.Empty();
			AliasMap.Lookup( key, eintrag );
	}	}
}	// OnClickedDelAlias

void CArtDialog :: OnClickedModAlias()
{
	m_modified = TRUE;

}	// OnClickedModAlias

void CArtDialog :: OnClickedAdvAlias()
{
	m_modified = TRUE;

}	// OnClickedAdvAlias

void CArtDialog :: EnableButton( int id, BOOL flag )
{	CButton		*pB;

	pB = (CButton*)GetDlgItem( id );
	ASSERT( pB );
	pB -> EnableWindow( flag );
}	// EnableButton

#endif // defined(_USE_CONFIG_DIALOGS)

