///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			defmm.cpp
//
//	Stand:			18.05.1995
//	Beschreibung:	Elemente zur Editierung einer Liste aus Identi-
//					fikator und Bezeichnung
//
//	Entwicklung:	18.05.95	Beginn der Kodierung
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "defmm.hpp"
#include "cxstring.h"
#include <ctype.h>

CDefMMList :: CDefMMList()
{	m_MMKgeaendert = FALSE;
	m_MMBgeaendert = FALSE;
	m_bListeGeaendert = FALSE;
	pCB  = NULL;
	pED  = NULL;
	pMod = NULL;
	pDel = NULL;
	pMap = NULL;
}

CDefMMList :: ~CDefMMList()
{}

void CDefMMList :: Reset()
{	m_MMKgeaendert = FALSE;
	m_MMBgeaendert = FALSE;
	m_bListeGeaendert = FALSE;
	if ( pCB )  pCB -> ResetContent();
	if ( pED )  pED -> SetWindowText( "" );
	if ( pMod ) pMod -> EnableWindow( FALSE );
	if ( pDel ) pDel -> EnableWindow( FALSE );
}

void CDefMMList :: SetElements( CComboBox *pC, CEdit *pE,
									 CButton *pD, CButton *pM,
									 CMapStringToString *pL, tTestModus m )
{	pCB  = pC; 	pED  = pE;
	pMod = pM;	pDel = pD;
	pMap = pL;	m_Mode = m;

	ASSERT( pCB );
	ASSERT( pED );
	ASSERT( pMod );
	ASSERT( pDel );
	ASSERT( pMap );
}

BOOL CDefMMList :: EingabeOK()
{	BOOL	result = FALSE;
	CxString	strKode, strText, strEdit;
	char		*txt;
	short		i;

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

		switch ( m_Mode )
		{	case TestMode8:		// 
				if ( strKode.GetLength() != 8 ) result = FALSE;
				if ( strKode.AnzahlHexZiffern() != 8 ) result = FALSE;
				if ( atol( strKode ) == 0L ) result = FALSE;
				break;
			case TestMode8x:
				if ( strKode.GetLength() != 8 ) result = FALSE;
				i = 0;
				for ( txt = strKode.GetBuffer( 8 ); *txt; txt++ )
					if ( *txt )
					{	if ( !isxdigit( *txt ) && !( *txt == 'x' ) &&
							 !( *txt == 'y' ) && !( *txt == 'z' ))
							 	result = FALSE;
						if (( *txt == 'x' ) ||
							( *txt == 'y' ) || ( *txt == 'z' ))
							 	i++;
					}
				if ( i == 0 ) result = FALSE;
				strKode.ReleaseBuffer();
				if ( atol( strKode ) == 0L ) result = FALSE;
				break;
			case TestMode4:
				result = (( strKode.AnzahlHexZiffern() > 2 ) &&
							( strKode.AnzahlHexZiffern() < 5 ));
			case TestModeA3:
				result = (( strKode.GetLength() > 2 ) &&
							( strKode.GetLength() < 5 ));
	}	}

	if ( result )
//	4. Kode noch nicht vergeben oder Kurztext geändert  -------------------
	{	strEdit.AllTrimm();
		if ( pMap -> Lookup( strKode, strText ))
			if ( strEdit == strText )
				result = FALSE;
	}
	return result;
}	// EingabeOK

void CDefMMList :: OnClickedDel()
{	CxString	strKode, strText;
	BOOL		geloescht = FALSE;
	POSITION	pos;
	int			i;

	if ( m_MMKgeaendert )		// eingegebener Kode
	{	pCB -> GetWindowText( strText );
		strText.Teilen( strKode, strText, ':' );
		if ( pMap -> RemoveKey( strKode ))
			geloescht = TRUE;
	}
	else						// ausgewählter Kode
	{	i = pCB -> GetCurSel();
		if ( i != CB_ERR )
		{	pCB -> GetLBText( i, strKode );
			strKode.Teilen( strKode, strText, ':' );
			if ( pMap -> RemoveKey( strKode ))
				geloescht = TRUE;
	}	}

	if ( geloescht )
	{	pCB -> ResetContent();
		for ( pos = pMap -> GetStartPosition(); pos != NULL; )
		{	pMap -> GetNextAssoc( pos, strKode, strText );
			strKode += ": ";
			strKode += strText;
			pCB -> AddString( strKode );
		}
		pED -> SetWindowText( "" );

		pMod -> EnableWindow( FALSE );

		m_MMKgeaendert = m_MMBgeaendert = FALSE;
		m_bListeGeaendert = TRUE;
	}

	m_MMKgeaendert = FALSE;
	m_MMBgeaendert = FALSE;
	m_strMerk.Empty();
}

void CDefMMList :: OnClickedMod()
{	CxString	strKode, strText, strEdit;
	BOOL		geaendert = FALSE;
	POSITION	pos;
	int			i;

	if ( !EingabeOK())	return;

	pED -> GetWindowText( strEdit );
	if ( m_MMKgeaendert )		// eingegebener Kode
	{	pCB -> GetWindowText( strText );
		strText.Teilen( strKode, strText, ':' );
		pMap -> SetAt( strKode, strEdit );
		geaendert = TRUE;
		strEdit = strKode;
	}
	else						// ausgewählter Kode
	{	i = pCB -> GetCurSel();
		if ( i != CB_ERR )
		{	pCB -> GetLBText( i, strKode );
			strKode.Teilen( strKode, strText, ':' );
			pMap -> SetAt( strKode, strEdit );
			geaendert = TRUE;
			strEdit = strKode;
		}
		else					// neuer Kode
		{	pCB -> GetWindowText( strText );
			strText.Teilen( strKode, strText, ':' );
			pMap -> SetAt( strKode, strEdit );
			geaendert = TRUE;
			strEdit = strKode;
	}	}

	if ( geaendert )
	{	pCB -> ResetContent();
		for ( pos = pMap -> GetStartPosition(); pos != NULL; )
		{	pMap -> GetNextAssoc( pos, strKode, strText );
			strKode += ": ";
			strKode += strText;
			pCB -> AddString( strKode );
		}
		pCB -> SelectString( -1, strEdit );

		pMod -> EnableWindow( FALSE );

		m_MMKgeaendert = m_MMBgeaendert = FALSE;
		m_bListeGeaendert = TRUE;
	}

	m_MMKgeaendert = FALSE;
	m_MMBgeaendert = FALSE;
	m_strMerk.Empty();
}

void CDefMMList :: OnEditKode()
{	CxString	strKode, strText;
	BOOL		EnableDel = FALSE;
	int			i, j;
	DWORD		dw;

	m_MMKgeaendert = TRUE;

	if ( !m_MMBgeaendert )
	{	pED -> SetWindowText( "" );
		m_MMBgeaendert = FALSE;
	}

	if ( !m_strMerk.IsEmpty())
	{	pED -> SetWindowText( m_strMerk );
		m_strMerk.Empty();
	}

	pCB -> GetWindowText( strText );
	if ( !strText.IsEmpty())
	{	dw = pCB -> GetEditSel();
//		strText.MakeUpper();
		strText.MakeLower();
		pCB -> SetWindowText( strText );
		pCB -> SetEditSel( LOWORD( dw ), HIWORD( dw ));
	}

	i = pCB -> FindString( -1, strText );
	if ( i != CB_ERR )
	{	j = pCB -> FindString( i, strText );
		if (( j == CB_ERR ) || ( j == i ))
		{	pCB -> GetLBText( i, strKode );
			strKode.Teilen( strKode, strText, ':' );
			pED -> GetWindowText( m_strMerk );
			pED -> SetWindowText( strText );
			m_MMBgeaendert = FALSE;
			EnableDel = TRUE;
	}	}

	pDel -> EnableWindow( EnableDel );
	pMod -> EnableWindow( EingabeOK());
}

void CDefMMList :: OnEditBez()
{	m_MMBgeaendert = TRUE;
	pDel -> EnableWindow( FALSE );
	pMod -> EnableWindow( EingabeOK());
}

void CDefMMList :: OnAuswahlKode()
{	CxString	strText, strTemp;
	int			i;

	i = pCB -> GetCurSel();
	if ( i == CB_ERR )
	{	pMod -> EnableWindow( FALSE );
		pDel -> EnableWindow( FALSE );
		return;
	}

	pCB -> GetLBText( i, strText );
	strText.Teilen( strText, strTemp, ':' );
	if ( pMap -> Lookup( strText, strTemp ))
	{	pED -> SetWindowText( strTemp );
		m_MMBgeaendert = FALSE;
	}

	pDel -> EnableWindow();
	pMod -> EnableWindow( FALSE );

	m_MMKgeaendert = FALSE;
	m_MMBgeaendert = FALSE;
	m_strMerk.Empty();
}

