///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			setupdlg.cpp
//
//	Stand:			20.02.1995
//	Beschreibung:	Setup - Dialog
//	Entwicklung:	20.02.95	Beginn der Kodierung
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#if defined(_USE_CONFIG_DIALOGS)

#include "afxdlgs.h"

#include "resource.h"
#include "regeln.hpp"
#include "setupdlg.hpp"
#include "cxstring.h"

#include "cwc.h"

#include "triddia.hpp"
#include "attrdia.hpp"
#include "artdia.hpp"

extern "C" {
extern HWND __hWndM;
}

///////////////////////////////////////////////////////////////////////
//	CSetupDialog

BEGIN_MESSAGE_MAP( CSetupDialog, CDialog )
	ON_CBN_EDITUPDATE( IDC_COMBO1, OnEditEdbsIdent )
	ON_CBN_SELCHANGE( IDC_COMBO1, OnAuswahlEdbsIdent )
	ON_LBN_SELCHANGE( IDC_LIST1, OnAuswahlAttribut )
	ON_LBN_SELCHANGE( IDC_LIST2, OnAuswahlAlias )
	ON_BN_CLICKED( IDC_BTN_BEARB1, OnDefineObjArt )
	ON_BN_CLICKED( IDC_BTN_BEARB2, OnDefineTriasIdent )
	ON_BN_CLICKED( IDC_BTN_BEARB3, OnDefineAttribute )
	ON_BN_CLICKED( IDC_BTN_BEARB4, OnDefineMerkmale )
	ON_BN_CLICKED( IDC_BTN_BEARB5, OnDefineTriasXIdent )
	ON_BN_CLICKED( IDC_SAVE_AS, OnSaveFile )
	ON_BN_CLICKED( IDC_LOAD, OnLoadFile )
	ON_BN_CLICKED( IDC_CHECK1, OnIgnoreUndef )
	ON_BN_CLICKED( IDOK, OnOK )
	ON_BN_CLICKED( IDCANCEL, OnCancel )
END_MESSAGE_MAP()

//	Konstruktion  -----------------------------------------------------
CSetupDialog :: CSetupDialog()
: CDialog( IDD_DIALOG2, CWnd::FromHandle( __hWndM ))
{
	modified = FALSE;
	pCBIdent = NULL;
	LoadFile( "EDBS.INI" );
}

void CSetupDialog :: OnOK()
{	if ( modified )		OnOKFrage();
	if ( !modified )	EndDialog( IDOK );
}	// OnOK


void CSetupDialog :: OnCancel()
{	if ( modified )		OnCancelFrage();
	if ( !modified )	EndDialog( IDCANCEL );
}	// OnCancel

void CSetupDialog :: OnOKFrage()
{	if ( MessageBox( "Sollen die vorgenommenen Änderungen übernommen werden?\n\n"
					 "Die bisherigen Einstellungen werden dadurch überschrieben und gehen verloren!\n\n"
					 "Wollen Sie verschiedene Varianten der Importeinstellungen dauerhaft speichern, "
					 "so verwenden Sie bitte die Knöpfe 'Laden ...' und 'Speichern ...'!",
					 "Einstellungen ändern",
		MB_ICONQUESTION | MB_OKCANCEL ) == IDOK )
	{	SaveFile( "EDBS.INI" );
		modified = FALSE;
	}
}	// OnOKFrage

void CSetupDialog :: OnCancelFrage()
{	if ( MessageBox( "Sollen die vorgenommenen Änderungen verworfen werden?", "Einstellungen abbrechen",
		MB_ICONQUESTION | MB_OKCANCEL ) == IDOK )	modified = FALSE;
}	// OnCancelFrage

BOOL CSetupDialog :: SaveFile( const char* name )
{	BOOL				result = TRUE;
	CxString			strSection, strEntry, strText, strFile;
	CxString			strKey, strT1, strT2, strT3, strT4, strNr;
	CMapStringToString	mapTemp;
	CWaitCur			wc;
	int					nr, i;
	BOOL				exist  = TRUE;
	POSITION			pos;
	CButton				*pCB;
	char				*txt;

	strFile.Empty();
	if ( *name == '\0' )	return FALSE;	// kein Name
	if ( *(name + 1) != ':' )					// kein Pfad
	{	txt = strFile.GetBuffer( 255 );
		GetWindowsDirectory( txt, 255 );
		strFile.ReleaseBuffer();
		if ( strFile.GetLength() > 3 )	strFile += '\\';
		else
			if ( strFile[2] != '\\' )	strFile += '\\';
	}

	strFile += name;

/*
	TRY
	{
		CFile f( name, CFile::modeRead );
	}
	CATCH( CFileException, e )
	{
		exist = FALSE;
	}
	END_CATCH
*/

	pCBIdent = NULL;

	pCB = (CButton*)GetDlgItem( IDC_CHECK1 );
	ASSERT( pCB );
	if ( pCB -> GetCheck())	strKey = "ja";
	else					strKey = "nein";
	strSection = "EDBS Allgemein";
	strEntry   = "nicht definierte Objekte ignorieren";
	strKey.WritePrivateProfileString( strSection, strEntry, strFile );

	nr = 1;
	strSection = "Idents";
	WritePrivateProfileString( strSection, NULL, NULL, strFile );
	strEntry.printf( "I%d", nr );
	pos = mapTRIAS_Ident.GetStartPosition();
	while ( pos )
	{	mapTRIAS_Ident.GetNextAssoc( pos, strKey, strText );
		strKey += ',';
		strKey += strText;
		strKey.WritePrivateProfileString( strSection, strEntry,
				strFile );
		strEntry.printf( "I%d", ++nr );
	}

	nr = 1;
	strSection = "xIdents";
	WritePrivateProfileString( strSection, NULL, NULL, strFile );
	strEntry.printf( "I%d", nr );
	pos = mapTRIAS_xIdent.GetStartPosition();
	while ( pos )
	{	mapTRIAS_xIdent.GetNextAssoc( pos, strKey, strText );
		strKey += ',';
		strKey += strText;
		strKey.WritePrivateProfileString( strSection, strEntry,
				strFile );
		strEntry.printf( "I%d", ++nr );
	}

	nr = 1;
	strSection = "Merkmale";
	WritePrivateProfileString( strSection, NULL, NULL, strFile );
	strEntry.printf( "M%d", nr );
	pos = mapTRIAS_MM.GetStartPosition();
	while ( pos )
	{	mapTRIAS_MM.GetNextAssoc( pos, strKey, strText );
		strKey += ',';
		strKey += strText;
		strKey.WritePrivateProfileString( strSection, strEntry,
				strFile );
		strEntry.printf( "M%d", ++nr );
	}

	nr = 1;
	strSection = "Typen";
	WritePrivateProfileString( strSection, NULL, NULL, strFile );
	strEntry.printf( "T%d", nr );
	pos = mapEDBS_Ident.GetStartPosition();
	while ( pos )
	{	mapEDBS_Ident.GetNextAssoc( pos, strKey, strT1 );
		mapArtTexte.Lookup( strKey, strText );
		strT2 = strKey;
		strT2 += ',';
		strT2 += strT1;
		strT2 += ',';
		strT2 += strText;
		strT2.WritePrivateProfileString( strSection, strEntry, strFile );
		WritePrivateProfileString( strKey, NULL, NULL, strFile );
	//	Aliase schreiben ----------------------------------------------
		i = 1;
		strEntry.printf( "A%d", i );
		strT2.printf( "%s+%d", (const char*)strKey, i++ );
		strT3.Empty();
		mapAlias.Lookup( strT2, strT3 );
		while ( !strT3.IsEmpty())
		{	strT3.Replace( " => ", ":" );
			strT3.WritePrivateProfileString( strKey, strEntry, strFile );
			strEntry.printf( "A%d", i );
			strT2.printf( "%s+%d", (const char*)strKey, i++ );
			strT3.Empty();
			mapAlias.Lookup( strT2, strT3 );
		}

	//	Bedingungen schreiben -----------------------------------------
		i = 1;
		strEntry.printf( "B%d", i );
		strT2.printf( "%s+%d", (const char*)strKey, i++ );
		strText.Empty();
		mapBedingungen.Lookup( strT2, strText );
		while ( !strText.IsEmpty())
		{	strText.Teilen( strText, strT3, ':' );
			strText.Replace( " = ", "," );
			strText.Replace( " => ", "," );
			strText.Replace( "sonst", "" );
			strText.WritePrivateProfileString( strKey, strEntry, strFile );
			strEntry.printf( "B%d", i );
			strT2.printf( "%s+%d", (const char*)strKey, i++ );
			strText.Empty();
			mapBedingungen.Lookup( strT2, strText );
		}

		strEntry.printf( "T%d", ++nr );
	}

	nr = 1;
	strSection = "Attribute";
	WritePrivateProfileString( strSection, NULL, NULL, strFile );
	strEntry.printf( "A%d", nr );
	pos = mapAttribTexte.GetStartPosition();
	while ( pos )
	{	mapAttribTexte.GetNextAssoc( pos, strKey, strText );
		strT2 = strKey;
		strT2 += ',';
		strT2 += strText;
		strT2.WritePrivateProfileString( strSection, strEntry, strFile );
		WritePrivateProfileString( strKey, NULL, NULL, strFile );
		strEntry.printf( "A%d", ++nr );
	}

	//	Attributwerte schreiben ---------------------------------------
	pos = mapWertTexte.GetStartPosition();
	while ( pos )
	{	mapWertTexte.GetNextAssoc( pos, strT1, strText );
		strT1.Replace( " = ", "," );
		strT1.Teilen( strKey, strT1, ',' );
		strT1 += ',';
		strT1 += strText;
		i = 1;
		strEntry.printf( "W%d", i++ );
		while ( strT2.GetPrivateProfileString( strKey, strEntry,
						"", 256, strFile ))
			strEntry.printf( "W%d", i++ );
		strT1.WritePrivateProfileString( strKey, strEntry, strFile );
	}

	return result;
}	// SaveFile


BOOL CSetupDialog :: OnInitDialog()
{	CxString	strKey, strText, strTemp;
	BOOL		result = FALSE;
	CListBox	*pLB;
	CStatic		*pST;
	CButton		*pCB;

	pST = (CStatic*)GetDlgItem( IDC_STEXT1 );
	pST -> SetWindowText( "" );
	pST = (CStatic*)GetDlgItem( IDC_STEXT2 );
	pST -> SetWindowText( "" );
	pST = (CStatic*)GetDlgItem( IDC_STEXT3 );
	pST -> SetWindowText( "" );
	pST = (CStatic*)GetDlgItem( IDC_STEXT4 );
	pST -> SetWindowText( "" );
	pST = (CStatic*)GetDlgItem( IDC_STEXT5 );
	pST -> SetWindowText( "" );
	pST = (CStatic*)GetDlgItem( IDC_STEXT6 );
	pST -> SetWindowText( "" );

	pCB = (CButton*)GetDlgItem( IDC_CHECK1 );
	ASSERT( pCB );
	pCB -> SetCheck( m_bIgnoreUndef );

	InitZuordnungsListe();

	pLB = (CListBox*)GetDlgItem( IDC_LIST1 );
	ASSERT( pLB );
	pLB -> ResetContent();

	pLB = (CListBox*)GetDlgItem( IDC_LIST2 );
	ASSERT( pLB );
	pLB -> ResetContent();

	result = TRUE;
	return result;
}	// OnInitDialog

void CSetupDialog :: InitZuordnungsListe()
{	CComboBox	*pCB;
	POSITION	pos;
	CxString	strKey, strText, strTemp;
	short		i;

	pCB = (CComboBox*)GetDlgItem( IDC_COMBO1 );
	ASSERT( pCB );
	i = pCB -> GetCurSel();
	pCB -> ResetContent();

	for ( pos = mapEDBS_Ident.GetStartPosition(); pos != NULL; )
	{	mapEDBS_Ident.GetNextAssoc( pos, strKey, strText );
		strKey += " ==> ";
		if ( mapTRIAS_Ident.Lookup( strText, strTemp ))
		{	strText += ": ";
			strText += strTemp;
		}
		else
		if ( mapTRIAS_xIdent.Lookup( strText, strTemp ))
		{	strText += ": ";
			strText += strTemp;
		}
		strKey += strText;
		pCB -> AddString( strKey );
	}

	if ( i != CB_ERR )
	{	pCB -> SetCurSel( i );
		OnAuswahlEdbsIdent();
	}
}	// InitZuordnungsListe


void CSetupDialog :: OnEditEdbsIdent()
{	CComboBox	*pCB;
	CListBox	*pLB;
	CxString	strText;
	int			i;

	pCB = (CComboBox*)GetDlgItem( IDC_COMBO1 );
	pLB = (CListBox*)GetDlgItem( IDC_LIST1 );
	pLB -> ResetContent();

	pLB = (CListBox*)GetDlgItem( IDC_LIST2 );
	pLB -> ResetContent();

	pCB -> GetWindowText( strText );
	if ( strText.GetLength() == 4 )
	{	i = pCB -> FindString( -1, strText );
		if ( i != CB_ERR )
		{	pCB -> SelectString( -1, strText );
			OnAuswahlEdbsIdent();
	}	}
}	// OnEditEdbsIdent

void CSetupDialog :: OnAuswahlEdbsIdent()
{	CComboBox	*pCB;
	CListBox	*pLB;
	CStatic		*pST;
	CxString	strText, strKey, strT1, strT2, strT3;
	int			i;

	pCB = (CComboBox*)GetDlgItem( IDC_COMBO1 );
	pLB = (CListBox*)GetDlgItem( IDC_LIST1 );

	pST = (CStatic*)GetDlgItem( IDC_STEXT3 );
	pST -> SetWindowText( "" );
	pST = (CStatic*)GetDlgItem( IDC_STEXT4 );
	pST -> SetWindowText( "" );
	pST = (CStatic*)GetDlgItem( IDC_STEXT5 );
	pST -> SetWindowText( "" );
	pST = (CStatic*)GetDlgItem( IDC_STEXT6 );
	pST -> SetWindowText( "" );
	pST = (CStatic*)GetDlgItem( IDC_STEXT2 );
	pST -> SetWindowText( "" );
	pST = (CStatic*)GetDlgItem( IDC_STEXT1 );
	pST -> SetWindowText( "" );

	i = pCB -> GetCurSel();
	if ( i == CB_ERR ) return;
	pST -> SetWindowText( "Objektart:" );

	pCB -> GetLBText( i, strText );
	pLB -> ResetContent();

	strText.Teilen( strKey, strT1, ' ' );
	pST = (CStatic*)GetDlgItem( IDC_STEXT2 );
	strT2 = strKey;
	if ( mapArtTexte.Lookup( strKey, strT3 ))
	{	strT2 += ": ";
		strT2 += strT3;
	}
	else
		strT2 = ": unbekannt";

	pST -> SetWindowText( strT2 );

	i = 0;
	strT1.printf( "%s+%d", (const char*)strKey, ++i );
	strText.Empty();
	mapBedingungen.Lookup( strT1, strText );
	while ( !strText.IsEmpty())
	{	pLB -> AddString( strText );
		strT1.printf( "%s+%d", (const char*)strKey, ++i );
		strText.Empty();
		mapBedingungen.Lookup( strT1, strText );
	}

	pLB = (CListBox*)GetDlgItem( IDC_LIST2 );

	i = pCB -> GetCurSel();
	pCB -> GetLBText( i, strText );
	pLB -> ResetContent();

	strText.Teilen( strKey, strT1, ' ' );
	i = 0;
	strT1.printf( "%s+%d", (const char*)strKey, ++i );
	strText.Empty();
	mapAlias.Lookup( strT1, strText );
	while ( !strText.IsEmpty())
	{	pLB -> AddString( strText );
		strT1.printf( "%s+%d", (const char*)strKey, ++i );
		strText.Empty();
		mapAlias.Lookup( strT1, strText );
	}
}	// OnAuswahlEdbsIdent

void CSetupDialog :: OnAuswahlAttribut()
{	CListBox	*pLB;
	CStatic		*pST;
	CxString	strKey, strText, strT1, strT2;
	int			i;

	pST = (CStatic*)GetDlgItem( IDC_STEXT3 );
	pST -> SetWindowText( "" );
	pST = (CStatic*)GetDlgItem( IDC_STEXT4 );
	pST -> SetWindowText( "" );
	pST = (CStatic*)GetDlgItem( IDC_STEXT5 );
	pST -> SetWindowText( "" );
	pST = (CStatic*)GetDlgItem( IDC_STEXT6 );
	pST -> SetWindowText( "" );

	pLB = (CListBox*)GetDlgItem( IDC_LIST1 );
	ASSERT( pLB );
	i = pLB -> GetCurSel();
	if ( i != LB_ERR )
	{	pST = (CStatic*)GetDlgItem( IDC_STEXT3 );
		pST -> SetWindowText( "Attribut:" );
		pLB -> GetText( i, strText );
		strText.Teilen( strKey, strText, '=' );
		strKey.AllTrimm();
		strText.AllTrimm();
		if ( mapAttribTexte.Lookup( strKey, strT1 ))
		{	strT2 = strKey;
			strT2 += ": ";
			strT2 += strT1;
			pST = (CStatic*)GetDlgItem( IDC_STEXT4 );
			pST -> SetWindowText( strT2 );

			pST = (CStatic*)GetDlgItem( IDC_STEXT5 );
			pST -> SetWindowText( "Attributwert:" );
			strText.Teilen( strT1, strText, ' ' );
			strKey += " = ";
			strKey += strT1;
			if ( mapWertTexte.Lookup( strKey, strT2 ))
			{	strT1 += ": ";
				strT1 += strT2;
			}
			else
			{	if ( strT1 == "sonst" )
					strT1 = "alle anderen Werte";
				else
					strT1 += ": unbekannt";
			}

			pST = (CStatic*)GetDlgItem( IDC_STEXT6 );
			pST -> SetWindowText( strT1 );
	}	}
}	// OnAuswahlAttribut

void CSetupDialog :: OnAuswahlAlias()
{	CListBox	*pLB;
	CStatic		*pST;
	CxString	strKey, strText, strT1, strT2;
	int			i;

	pST = (CStatic*)GetDlgItem( IDC_STEXT3 );
	pST -> SetWindowText( "" );
	pST = (CStatic*)GetDlgItem( IDC_STEXT4 );
	pST -> SetWindowText( "" );
	pST = (CStatic*)GetDlgItem( IDC_STEXT5 );
	pST -> SetWindowText( "" );
	pST = (CStatic*)GetDlgItem( IDC_STEXT6 );
	pST -> SetWindowText( "" );

	pLB = (CListBox*)GetDlgItem( IDC_LIST2 );
	ASSERT( pLB );
	i = pLB -> GetCurSel();
	if ( i != LB_ERR )
	{	pST = (CStatic*)GetDlgItem( IDC_STEXT3 );
		pST -> SetWindowText( "Attribut:" );
		pLB -> GetText( i, strText );
		strText.Teilen( strKey, strText, '=' );
		strKey.AllTrimm();
		strText.AllTrimm();
		if ( mapAttribTexte.Lookup( strKey, strT1 ))
		{	strT2 = strKey;
			strT2 += ": ";
			strT2 += strT1;
			pST = (CStatic*)GetDlgItem( IDC_STEXT4 );
			pST -> SetWindowText( strT2 );
	}	}
}	// OnAuswahlAlias

void CSetupDialog :: OnDefineMerkmale()
{	CTriasIdentDialog	dia( this );
	CListBox	*pLB;
	CxString	strText, strKey;
	short		i;

	pLB = (CListBox*)GetDlgItem( IDC_LIST2 );
	ASSERT( pLB );

	i = pLB -> GetCurSel();
	if ( i != LB_ERR )
	{	pLB -> GetText( i, strText );

		strText.Teilen( strKey, strText, ' ' );
		strText.Teilen( strKey, strText, ' ' );
		strKey = FindMMK( strText );
	}

	dia.SetCaptText( "TRiAS - Merkmale" );
	dia.SetText1( "Merkmalskode" );
	dia.SetText2( "Kurztext" );
	dia.SetTestProc( 1 );		// 8 Stellen, Hex
	dia.SetStartIdent( strKey );
	dia.pOriginalMap = &mapTRIAS_MM;

	modified = ( dia.DoModal() == IDOK );
}	// OnDefineMerkmale

void CSetupDialog :: OnDefineTriasIdent()
{	CTriasIdentDialog	dia( this );
	CComboBox	*pCB;
	CListBox	*pLB;
	CxString	strText, strKey;
	int			i;

	pCB = (CComboBox*)GetDlgItem( IDC_COMBO1 );
	ASSERT( pCB );

	pLB = (CListBox*)GetDlgItem( IDC_LIST1 );
	ASSERT( pLB );

	i = pLB -> GetCurSel();
	if ( i != LB_ERR )
	{	pLB -> GetText( i, strText );
		strText.Teilen( strKey, strText, ' ' );
		strText.Teilen( strKey, strText, ' ' );
		strText.Teilen( strKey, strText, ' ' );
		strText.Teilen( strKey, strText, ' ' );
		strText.Teilen( strKey, strText, ':' );
	}

	if ( strKey.IsEmpty())
	{	i = pCB -> GetCurSel();
		if ( i != CB_ERR )
		{	pCB -> GetLBText( i, strText );

			strText.Teilen( strText, strKey, ' ' );
			strKey.Teilen( strText, strKey, ' ' );
			strKey.Teilen( strKey, strText, ':' );
	}	}

	dia.SetCaptText( "TRiAS - Identifikatoren" );
	dia.SetText1( "Identifikatorkode" );
	dia.SetText2( "Kurztext" );
	dia.SetTestProc( 1 );		// 8 Stellen, Hex
	dia.SetStartIdent( strKey );
	dia.pOriginalMap = &mapTRIAS_Ident;

	if ( dia.DoModal() == IDOK )
	{	InitZuordnungsListe();
		modified = TRUE;
	}

}	// OnDefineTriasIdent

CString CSetupDialog :: FindMMK( const char *bez )
{	POSITION	pos;
	CString		strKey, strBez;

	for ( pos = mapTRIAS_MM.GetStartPosition(); pos != NULL; )
	{	mapTRIAS_MM.GetNextAssoc( pos, strKey, strBez );
		if ( strBez == bez )	pos = NULL;
		else					strKey.Empty();
	}

	return strKey;
}	// FindMMK

void CSetupDialog :: OnDefineObjArt()
{	CArtDialog	dia( this );
	CComboBox	*pCB;
	CxString	strText, strKey;
	int			i;

	pCB = (CComboBox*)GetDlgItem( IDC_COMBO1 );
	ASSERT( pCB );

	i = pCB -> GetCurSel();
	if ( i != CB_ERR )
	{	pCB -> GetLBText( i, strText );
		strText.Teilen( strKey, strText, ' ' );
	}

	dia.SetStartIdent( strKey );
	dia.pmapArtTexte     = &mapArtTexte;
	dia.pmapTRIAS_Ident  = &mapTRIAS_Ident;
	dia.pmapTRIAS_xIdent = &mapTRIAS_xIdent;
	dia.pmapTRIAS_MM     = &mapTRIAS_MM;
	dia.pmapEDBS_Ident   = &mapEDBS_Ident;
	dia.pmapAttribTexte  = &mapAttribTexte;
	dia.pmapWertTexte    = &mapWertTexte;
	dia.pmapBedingungen  = &mapBedingungen;
	dia.pmapAlias        = &mapAlias;

	if ( dia.DoModal() == IDOK )
	{	InitZuordnungsListe();
		modified = TRUE;
	}

}	// OnDefineObjArt

void CSetupDialog :: OnDefineAttribute()
{	CAttributeDialog	dia( this );
	CListBox			*pLB;
	CxString			strText, strKey;
	int					i;

	pLB = (CListBox*)GetDlgItem( IDC_LIST1 );
	ASSERT( pLB );

	i = pLB -> GetCurSel();
	if ( i != LB_ERR )
	{	pLB -> GetText( i, strText );
		strText.Teilen( strKey, strText, ' ' );
	}

	dia.SetStartIdent( strKey );
	dia.pOrigAttrMap = &mapAttribTexte;
	dia.pOrigWertMap = &mapWertTexte;

	if ( dia.DoModal() == IDOK )
	{	InitZuordnungsListe();
		modified = TRUE;
	}

}	// OnDefineAttribute

void CSetupDialog :: OnDefineTriasXIdent()
{	CTriasIdentDialog	dia( this );
	CComboBox	*pCB;
	CListBox	*pLB;
	CxString	strText, strKey;
	int			i;

	pCB = (CComboBox*)GetDlgItem( IDC_COMBO1 );
	ASSERT( pCB );

	pLB = (CListBox*)GetDlgItem( IDC_LIST1 );
	ASSERT( pLB );

	i = pLB -> GetCurSel();
	if ( i != LB_ERR )
	{	pLB -> GetText( i, strText );
		strText.Teilen( strKey, strText, ' ' );
		strText.Teilen( strKey, strText, ' ' );
		strText.Teilen( strKey, strText, ' ' );
		strText.Teilen( strKey, strText, ' ' );
		strText.Teilen( strKey, strText, ':' );
	}

	if ( strKey.IsEmpty())
	{	i = pCB -> GetCurSel();
		if ( i != CB_ERR )
		{	pCB -> GetLBText( i, strText );

			strText.Teilen( strText, strKey, ' ' );
			strKey.Teilen( strText, strKey, ' ' );
			strKey.Teilen( strKey, strText, ':' );
	}	}
	else
	{	if ( strKey.AnzahlHexZiffern() >= 8 )
		{	i = pCB -> GetCurSel();
			if ( i != CB_ERR )
			{	pCB -> GetLBText( i, strText );

				strText.Teilen( strText, strKey, ' ' );
				strKey.Teilen( strText, strKey, ' ' );
				strKey.Teilen( strKey, strText, ':' );
	}	}	}

	dia.SetCaptText( "TRiAS - Identifikatoren" );
	dia.SetText1( "Identifikatorkode" );
	dia.SetText2( "Kurztext" );
	dia.SetTestProc( 2 );		// 8 Stellen, Hex
	dia.SetStartIdent( strKey );
	dia.pOriginalMap = &mapTRIAS_xIdent;

	if ( dia.DoModal() == IDOK )
	{	InitZuordnungsListe();
		modified = TRUE;
	}

}	// OnDefineTriasXIdent

void CSetupDialog :: OnIgnoreUndef()
{	modified = TRUE;
}	// OnIgnoreUndef

void CSetupDialog :: OnSaveFile()
{	CString		name;
	CFileDialog	dia( FALSE );		// Open "File Save As" Dialog

	if ( dia.DoModal() == IDOK )
	{	name = dia.GetPathName();
		if ( !name.IsEmpty())
		{	SaveFile( name );
			modified = FALSE;
	}	}
}	// OnSaveFile

void CSetupDialog :: OnLoadFile()
{	CString		name;
	CFileDialog	dia( TRUE );		// Open "File Load" Dialog

	if ( dia.DoModal() == IDOK )
	{	name = dia.GetPathName();
		if ( !name.IsEmpty())
		{	if ( TestFile( name ))
			{	ResetListen();
				LoadFile( name );
				OnInitDialog();
				modified = TRUE;
			}
			else
				MessageBox( "Angegebene Datei enthält keine Einstellungen zum EDBS-Import!\n\n"
					"Lesen abgebrochen!", "Dateifehler", MB_ICONHAND );
	}	}
}	// OnLoadFile

BOOL CSetupDialog :: TestFile( const char *name )
{	BOOL		result = TRUE;
	CxString	strFile, strText;
	char		*txt;

	strFile.Empty();
	if ( *name == '\0' )	return FALSE;	// kein Name
	if ( *(name + 1) != ':' )				// kein Pfad
	{	txt = strFile.GetBuffer( 255 );
		GetWindowsDirectory( txt, 255 );
		strFile.ReleaseBuffer();
		if ( strFile.GetLength() > 3 )	strFile += '\\';
		else
			if ( strFile[2] != '\\' )	strFile += '\\';
	}

	strFile += name;

	strText.Empty();
	strText.GetPrivateProfileString( "Idents", "I1", "", 256, strFile );
	if ( strText.IsEmpty()) result = FALSE;

	if ( result )
	{	strText.Empty();
		strText.GetPrivateProfileString( "Typen", "T1", "", 256, strFile );
		if ( strText.IsEmpty()) result = FALSE;
	}

	if ( result )
	{	strText.Empty();
		strText.GetPrivateProfileString( "Attribute", "A1", "", 256, strFile );
		if ( strText.IsEmpty()) result = FALSE;
	}

	return result;
}	// TestFile

void CSetupDialog :: ResetListen()
{	mapTRIAS_Ident.RemoveAll();
	mapTRIAS_xIdent.RemoveAll();
	mapTRIAS_MM.RemoveAll();
	mapEDBS_Ident.RemoveAll();
	mapArtTexte.RemoveAll();
	mapAttribTexte.RemoveAll();
	mapWertTexte.RemoveAll();
	mapBedingungen.RemoveAll();
	mapAlias.RemoveAll();
}	// ResetListen

BOOL CSetupDialog :: LoadFile( const char *name )
{	CxString			strSection, strEntry, strText, strFile;
	CxString			strKey, strT1, strT2, strT3, strT4, strNr;
	CMapStringToString	mapTemp;
	CWaitCur			wc;
	int					nr, i;
	char				*txt;

	strFile.Empty();
	if ( *name == '\0' )	return FALSE;	// kein Name
	if ( *(name + 1) != ':' )				// kein Pfad
	{	txt = strFile.GetBuffer( 255 );
		GetWindowsDirectory( txt, 255 );
		strFile.ReleaseBuffer();
		if ( strFile.GetLength() > 3 )	strFile += '\\';
		else
			if ( strFile[2] != '\\' )	strFile += '\\';
	}

	strFile += name;

	strSection = "EDBS Allgemein";
	strEntry   = "nicht definierte Objekte ignorieren";
	if ( strText.GetPrivateProfileString( strSection, strEntry, "", 256, strFile ))
		m_bIgnoreUndef = ( strText == "ja" );

	nr = 1;
	strSection = "Idents";
	strEntry.printf( "I%d", nr );
	while (( strText.GetPrivateProfileString( strSection, strEntry,
						"", 256, strFile )) && nr < 1000 )
	{	strText.Teilen( strKey, strText, ',' );
//	Langtext abtrennen ------------------------------------------------
		if (( strText.Find( "/*" ) >= 0 ) && ( strText.Find( "*/" ) >= 0 ))
			strText = strText.Left( strText.Find( "/*" ));	// "*/"
//	-------------------------------------------------------------------
		mapTRIAS_Ident.SetAt( strKey, strText );
		strEntry.printf( "I%d", ++nr );
	}

	nr = 1;
	strSection = "xIdents";
	strEntry.printf( "I%d", nr );
	while (( strText.GetPrivateProfileString( strSection, strEntry,
						"", 256, strFile )) && nr < 1000 )
	{	strText.Teilen( strKey, strText, ',' );
		mapTRIAS_xIdent.SetAt( strKey, strText );
		strEntry.printf( "I%d", ++nr );
	}

	nr = 1;
	strSection = "Merkmale";
	strEntry.printf( "M%d", nr );
	while (( strText.GetPrivateProfileString( strSection, strEntry,
						"", 256, strFile )) && nr < 1000 )
	{	strText.Teilen( strKey, strText, ',' );
		mapTRIAS_MM.SetAt( strKey, strText );
		strEntry.printf( "M%d", ++nr );
	}

	nr = 1;
	strSection = "Typen";
	strEntry.printf( "T%d", nr );
	while (( strText.GetPrivateProfileString( strSection, strEntry,
						"", 256, strFile )) && nr < 1000 )
	{	strText.Teilen( strKey, strText, ',' );
		strText.Teilen( strT1, strText, ',' );
		mapEDBS_Ident.SetAt( strKey, strT1 );
		mapArtTexte.SetAt( strKey, strText );
	//	Aliase lesen --------------------------------------------------
		i = 1;
		strEntry.printf( "A%d", i );
		while ( strText.GetPrivateProfileString( strKey, strEntry,
						"", 256, strFile ))
		{	strT2.printf( "%s+%d", (const char*)strKey, i++ );
			strText.Teilen( strT3, strText, ':' );
			if ( !strT3.IsEmpty() && !strText.IsEmpty())
			{	strT3 += " => ";
				strT3 += strText;
			}
			else
			{	if ( strT3.IsEmpty()) strT3 = "??";
				if ( strText.IsEmpty()) strText = "???";
			}
			mapAlias.SetAt( strT2, strT3 );
			strEntry.printf( "A%d", i );
		}
	//	Bedingungen lesen ---------------------------------------------
		i = 1;
		strEntry.printf( "B%d", i );
		while ( strText.GetPrivateProfileString( strKey, strEntry,
						"", 256, strFile ))
		{	strT2.printf( "%s+%d", (const char*)strKey, i++ );
			strText.Teilen( strT3, strText, ',' );
			strText.Teilen( strT4, strText, ',' );
			if ( strT4.IsEmpty()) strT4 = "sonst";

			if ( !strT3.IsEmpty() && !strText.IsEmpty())
			{	strT3 += " = ";
				strT3 += strT4;
			}
			else
			{	if ( strT3.IsEmpty()) strT3 = "??";
				if ( strText.IsEmpty()) strText = "???";
			}
			strT3 += " => ";
			strText.MakeLower();
			if ( mapTRIAS_Ident.Lookup( strText, strT4 ))
			{	strText += ": ";
				strText += strT4;
			}
			else
				if ( mapTRIAS_xIdent.Lookup( strText, strT4 ))
				{	strText += ": ";
					strText += strT4;
				}
			
			strT3 += strText;
			mapBedingungen.SetAt( strT2, strT3 );
			strEntry.printf( "B%d", i );
		}

		strEntry.printf( "T%d", ++nr );
	}

	nr = 1;
	strSection = "Attribute";
	strEntry.printf( "A%d", nr );
	while (( strText.GetPrivateProfileString( strSection, strEntry,
						"", 256, strFile )) && nr < 1000 )
	{	strText.Teilen( strKey, strText, ',' );
		mapAttribTexte.SetAt( strKey, strText );
	//	Attributwerte lesen -------------------------------------------
		i = 1;
		strEntry.printf( "W%d", i );
		while ( strText.GetPrivateProfileString( strKey, strEntry,
						"", 256, strFile ))
		{	strText.Teilen( strT2, strText, ',' );
			strT3  = strKey;
			strT3 += " = ";
			strT3 += strT2;
			mapWertTexte.SetAt( strT3, strText );
			strEntry.printf( "W%d", ++i );
		}
		strEntry.printf( "A%d", ++nr );
	}
	return TRUE;
}	// LoadFile

#endif // defined(_USE_CONFIG_DIALOGS)
