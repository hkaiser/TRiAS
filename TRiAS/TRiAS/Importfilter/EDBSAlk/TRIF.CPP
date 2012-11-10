///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			trif.cpp
//
//	Stand:			02.12.1994
//	Beschreibung:	TRIAS-Interface-Objekt
//					- Header-Update
//					- IdentsDB-Update
//					- GeoObjekt-Zugriff
//	Entwicklung:	02.12.94	Beginn der Kodierung
///////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include <errcodes.hxx>                 // Fehlermeldungen
#include <hdrentrx.hxx>                 // HeaderEntryX

extern "C"
{
#include <xtension.h>
#include <xtensnn.h>
#include <xtensnx.h>
}

#include "edbs.hpp"
#include "trif.hpp"
#include <errinstx.hxx>					// ErrInstall
#include "cxstring.h"
#include "MetaData.h"
#include "ObjectAttributeTRiAS.h"
#include "resource.h"


extern int AllTrimm( CString& );
extern BOOL g_bKurzeIdents;

//	Konstruktor  ------------------------------------------------------

CTriasInterface :: CTriasInterface()
{
	HeaderEntryX	*pHD;
	CxString	strTemp;
	HPROJECT 	hPr;

	m_tUpdateHeader = false;
//	m_lUniqueIdent = DEX_GetUniqueIdentMCodeEx(DEX_GetDataSourceHandle());

// Header - Daten, 1. vorhandene Einträge
// in der Datenquelle testen
	hPr = DEX_GetDataSourceHandle();
	m_dKoeff11 = 0;
	if( DEX_GetTRiASDataSourceEx(hPr) ) {	// nur bei TRiAS-Datenquelle
		if ( strTemp.LoadString( IDS_KOEFF11 )) {
			pHD = new HeaderEntryX( strTemp, hPr );
			m_dKoeff11 = pHD -> EntryDouble();
			delete pHD;
		}
		else
			m_dKoeff11 = 0L;
		if( 0 == m_dKoeff11 )
			m_tUpdateHeader = true;
		else {
			if ( strTemp.LoadString( IDS_KOEFF12 )) {
				pHD = new HeaderEntryX( strTemp, hPr );
				m_dKoeff12 = pHD -> EntryDouble();
				delete pHD;
			}
			else
				m_dKoeff12 = 0L;

			if ( strTemp.LoadString( IDS_KOEFF21 )) {
				pHD = new HeaderEntryX( strTemp, hPr );
				m_dKoeff21 = pHD -> EntryDouble();
				delete pHD;
			}
			else
				m_dKoeff21 = 0L;

			if ( strTemp.LoadString( IDS_KOEFF22 )) {
				pHD = new HeaderEntryX( strTemp, hPr );
				m_dKoeff22 = pHD -> EntryDouble();
				delete pHD;
			}
			else
				m_dKoeff22 = 0L;

			if ( strTemp.LoadString( IDS_OFFSETX )) {
				pHD = new HeaderEntryX( strTemp, hPr );
				m_lOffsetX = pHD -> EntryLong();
				delete pHD;
			}
			else
				m_lOffsetX = 0L;

			if ( strTemp.LoadString( IDS_OFFSETY )) {
				pHD = new HeaderEntryX( strTemp, hPr );
				m_lOffsetY = pHD -> EntryLong();
				delete pHD;
			}
			else
				m_lOffsetY = 0L;
		}
	}	

// im Projekt testen
	if(	m_tUpdateHeader == false ) {
		hPr = HACTPROJECT;

		if ( strTemp.LoadString( IDS_KOEFF11 )) {
			pHD = new HeaderEntryX( strTemp, hPr );
			m_dKoeff11 = pHD -> EntryDouble();
			delete pHD;
		}
		else
			m_dKoeff11 = 0L;
		if( 0 == m_dKoeff11 )
			m_tUpdateHeader = true;
		else {
			if ( strTemp.LoadString( IDS_KOEFF12 )) {
				pHD = new HeaderEntryX( strTemp, hPr );
				m_dKoeff12 = pHD -> EntryDouble();
				delete pHD;
			}
			else
				m_dKoeff12 = 0L;

			if ( strTemp.LoadString( IDS_KOEFF21 )) {
				pHD = new HeaderEntryX( strTemp, hPr );
				m_dKoeff21 = pHD -> EntryDouble();
				delete pHD;
			}
			else
				m_dKoeff21 = 0L;

			if ( strTemp.LoadString( IDS_KOEFF22 )) {
				pHD = new HeaderEntryX( strTemp, hPr );
				m_dKoeff22 = pHD -> EntryDouble();
				delete pHD;
			}
			else
				m_dKoeff22 = 0L;

			if ( strTemp.LoadString( IDS_OFFSETX )) {
				pHD = new HeaderEntryX( strTemp, hPr );
				m_lOffsetX = pHD -> EntryLong();
				delete pHD;
			}
			else
				m_lOffsetX = 0L;

			if ( strTemp.LoadString( IDS_OFFSETY )) {
				pHD = new HeaderEntryX( strTemp, hPr );
				m_lOffsetY = pHD -> EntryLong();
				delete pHD;
			}
			else
				m_lOffsetY = 0L;
		}
	}
//	pHD = new HeaderEntryX( ResString( ResID( IDS_UNIQUEIDENT ), 20 ));
}


CTriasInterface :: ~CTriasInterface()
{
}

/*
long CTriasInterface :: TextMMK( const char* kurz )
{
	return m_tabMMK.FindeKode( kurz );
}
*/
//	ProjectOpen  ------------------------------------------------------
bool CTriasInterface :: ProjectOpen()
{
	bool result = TRUE;

	return result;
}	// ProjectOpen

void CTriasInterface::ConfigCoord(  HPROJECT hPr )
{
	CxString		strBuffer, strPar, strVal;
	int				i;
	int				nSize;
	char			section[32767];
	HeaderEntryX	*pHD;
	CxString		strTemp, strText;

	nSize = ::GetPrivateProfileSection( "Koordinatensystem", section, 32767, g_pMetaData->strIniFileName2 );
	if( nSize == 32765 )
		MessageBox(NULL, "Abschnitt [Koordinatensystem] in INI-Datei grösser 32767","ALK-Import",0);
	else if( nSize == 0 ) {
		if ( strTemp.LoadString( IDS_KOEFF11, TRUE )) {
			strText.Empty();
			strText.printf( "%lf", g_pMetaData->m_dKoeff11 );
			pHD = new HeaderEntryX( strTemp, strText, HEADER_NORMAL, hPr );
			pHD -> WriteBack();
			delete pHD;
		}

		if ( strTemp.LoadString( IDS_KOEFF12, TRUE )) {
			strText.Empty();
			strText.printf( "%lf", g_pMetaData->m_dKoeff12 );
			pHD = new HeaderEntryX( strTemp, strText, HEADER_NORMAL, hPr );
			pHD -> WriteBack();
			delete pHD;
		}

		if ( strTemp.LoadString( IDS_KOEFF21, TRUE )) {
			strText.Empty();
			strText.printf( "%lf", g_pMetaData->m_dKoeff21 );
			pHD = new HeaderEntryX( strTemp, strText, HEADER_NORMAL, hPr );
			pHD -> WriteBack();
			delete pHD;
		}

		if ( strTemp.LoadString( IDS_KOEFF22, TRUE )) {
			strText.Empty();
			strText.printf( "%lf", g_pMetaData->m_dKoeff22 );
			pHD = new HeaderEntryX( strTemp, strText, HEADER_NORMAL, hPr );
			pHD -> WriteBack();
			delete pHD;
		}
		if ( strTemp.LoadString( IDS_OFFSETX, TRUE )) {
			strText.Empty();
			strText.printf( "%ld", g_pMetaData->m_lOffsetX );
			pHD = new HeaderEntryX( strTemp, strText, HEADER_NORMAL, hPr );
			pHD -> WriteBack();
			delete pHD;
		}

		if ( strTemp.LoadString( IDS_OFFSETY, TRUE )) {
			strText.Empty();
			strText.printf( "%ld", g_pMetaData->m_lOffsetY );
			pHD = new HeaderEntryX( strTemp, strText, HEADER_NORMAL, hPr );
			pHD -> WriteBack();
			delete pHD;
		}
		if( g_pMetaData->m_sKoordinatensystem == 1
			|| g_pMetaData->m_sKoordinatensystem == 2 ) {
			pHD = new HeaderEntryX( "CoordTransform", "BESSELGK", HEADER_NORMAL, hPr );
			pHD -> WriteBack();
			delete pHD;
			strText.Empty();
			strText.printf( "%ld", g_pMetaData->m_lOffsetX * 3 / 1000000 );
			pHD = new HeaderEntryX( "CoordMeridian", strText, HEADER_NORMAL, hPr );
			pHD -> WriteBack();
			delete pHD;
			pHD = new HeaderEntryX( "CoordStrBreite", "3", HEADER_NORMAL, hPr );
			pHD -> WriteBack();
			delete pHD;
		}

	}
	else {
		i = 0;
		while( i < nSize ) {
			strBuffer = &section[i];
			i += strBuffer.GetLength() + 1;
			if( strBuffer.Left(1) != "§" ) {
				strBuffer.Teilen(strPar,strVal,"=",true);
				pHD = new HeaderEntryX( strPar, strVal, HEADER_NORMAL, hPr );
				pHD -> WriteBack();
				delete pHD;
			}
		}
	}
/*
*/
}

void CTriasInterface :: UpdateHeaders( void )
{
 HPROJECT hPr;
 HeaderEntryX	*pHD;
 double dTest;
 CxString		strTemp;
	if( m_tUpdateHeader == false )
		return;
	m_tUpdateHeader = false;

	// in der Datenquelle testen
	hPr = DEX_GetDataSourceHandle();

	dTest = 0;
	if( DEX_GetTRiASDataSourceEx(hPr) ) {	// nur bei TRiAS-Datenquelle
		if ( strTemp.LoadString( IDS_KOEFF11 )) {
			pHD = new HeaderEntryX( strTemp, hPr );
			dTest = pHD -> EntryDouble();
			delete pHD;
		}
		if( 0 == dTest )
			ConfigCoord( hPr );
	}	
	if( 0 == dTest ) {
// im Projekt testen
		hPr = HACTPROJECT;

		if ( strTemp.LoadString( IDS_KOEFF11 )) {
			pHD = new HeaderEntryX( strTemp, hPr );
			dTest = pHD -> EntryDouble();
			delete pHD;
		}
		else
			dTest = 0;

		if( 0 == dTest )
			ConfigCoord( hPr );
	}

	DEXN_ReReadHeader();
	DEXN_ReReadContainer();
	DEXN_ReScale();

	m_dKoeff11 = g_pMetaData->m_dKoeff11;
	m_dKoeff12 = g_pMetaData->m_dKoeff12;
	m_dKoeff21 = g_pMetaData->m_dKoeff21;
	m_dKoeff22 = g_pMetaData->m_dKoeff22;
	m_lOffsetX = g_pMetaData->m_lOffsetX;
	m_lOffsetY = g_pMetaData->m_lOffsetY;

}

//	UpdateHeader  -----------------------------------------------------
/*
void CTriasInterface :: UpdateHeader( HPROJECT hPr )
{
	HeaderEntryX	*pHD;
	CxString	strTemp, strText;

//	pHD = new HeaderEntryX( ResString( ResID( IDS_OFFSETX ), 20 ));
	if ( strTemp.LoadString( IDS_OFFSETX, TRUE )) {
		strText.Empty();
		strText.printf( "%ld", g_pMetaData->m_lOffsetX );
		pHD = new HeaderEntryX( strTemp, strText, HEADER_NORMAL, hPr );
		pHD -> WriteBack();
		delete pHD;
	}

//	pHD = new HeaderEntryX( ResString( ResID( IDS_OFFSETY ), 20 ));
	if ( strTemp.LoadString( IDS_OFFSETY, TRUE )) {
		strText.Empty();
		strText.printf( "%ld", g_pMetaData->m_lOffsetY );
		pHD = new HeaderEntryX( strTemp, strText, HEADER_NORMAL, hPr );
		pHD -> WriteBack();
		delete pHD;
	}

//	pHD = new HeaderEntryX( ResString( ResID( IDS_KOEFF11 ), 20 ));
	if ( strTemp.LoadString( IDS_KOEFF11, TRUE )) {
		strText.Empty();
		strText.printf( "%lf", g_pMetaData->m_dKoeff11 );
		pHD = new HeaderEntryX( strTemp, strText, HEADER_NORMAL, hPr );
		pHD -> WriteBack();
		delete pHD;
	}

//	pHD = new HeaderEntryX( ResString( ResID( IDS_KOEFF12 ), 20 ));
	if ( strTemp.LoadString( IDS_KOEFF12, TRUE )) {
		strText.Empty();
		strText.printf( "%lf", g_pMetaData->m_dKoeff12 );
		pHD = new HeaderEntryX( strTemp, strText, HEADER_NORMAL, hPr );
		pHD -> WriteBack();
		delete pHD;
	}

//	pHD = new HeaderEntryX( ResString( ResID( IDS_KOEFF21 ), 20 ));
	if ( strTemp.LoadString( IDS_KOEFF21, TRUE )) {
		strText.Empty();
		strText.printf( "%lf", g_pMetaData->m_dKoeff21 );
		pHD = new HeaderEntryX( strTemp, strText, HEADER_NORMAL, hPr );
		pHD -> WriteBack();
		delete pHD;
	}

//	pHD = new HeaderEntryX( ResString( ResID( IDS_KOEFF22 ), 20 ));
	if ( strTemp.LoadString( IDS_KOEFF22, TRUE )) {
		strText.Empty();
		strText.printf( "%lf", g_pMetaData->m_dKoeff22 );
		pHD = new HeaderEntryX( strTemp, strText, HEADER_NORMAL, hPr );
		pHD -> WriteBack();
		delete pHD;
	}

	DEXN_ReReadHeader();
	DEXN_ReReadContainer();
	DEXN_ReScale();
//	DEX_FlushModifications();	#fje990617

}	// UpdateHeader
*/

//	GetHeaderEntry  ---------------------------------------------------
CString CTriasInterface :: GetHeaderEntry( const char* K )
{
	CString result;
/*
	HeaderEntryX	*pHD;

	if ( K )
		if ( lstrlen( K ))
		{
//			pHD = new HeaderEntryX( ResString( ResID( IDS_KOEFF22 ), 20 ));
			if ( result.LoadString( IDS_IDENTBASE ))
			{	pHD = new HeaderEntryX( strTemp );
			result = pHD -> EntryText();
			delete pHD;
		}
*/
	return result;
}	// GetHeaderEntry


//	SetHeaderEntry  ---------------------------------------------------
void CTriasInterface :: SetHeaderEntry( const char* K, const char* T )
{
}	// SetHeaderEntry

/*
bool CTriasInterface::Get_A_Rule( const char *k, CString &s )
{
	if( g_pMetaData->Get_A_Rule( k, s ) ) 
		return true;
	else {
		CxString tmp1, tmp2;
		tmp1 = k;
		tmp1.Teilen( tmp1, tmp2, '/', true );
		if ( tmp2.IsEmpty() )
			return false;
		else
			return g_pMetaData->Get_A_Rule( tmp1, s );
	}
}
*/

bool CTriasInterface :: NeuesMerkmal( const char *key )
{
	bool		res = FALSE;
	POSITION	pos = NULL;

	pos = MerkmalList().Find( key );
	if ( pos == NULL ) {
		MerkmalList().AddTail( key );
		res = TRUE;
	}
	return res;
}


void CTriasInterface :: Flush()
{
	IStorage	*pIStorage = NULL;

	DEXN_ReScale();
	DEXN_ReReadIdents();

	if ( DEX_GetProjectStorage( pIStorage ))
		pIStorage -> Release();
	else
		DEX_FlushModifications();

	DEXN_ReReadContainer();
}	// Flush

void CTriasInterface :: DeleteObjekt( long onr )
{
	DEX_DeleteObject( onr );
}	// DeleteObjekt

//	-------------------------------------------------------------------
//	CMerkmalsKode
//	-------------------------------------------------------------------
CMerkmalsKode :: CMerkmalsKode( unsigned long ulObjectClassTRiAS, char typ, long mmk, const char* kurz,
									const char* lang )
{
	char*	txt;

	m_ulObjectClassTRiAS = ulObjectClassTRiAS;
	m_Typ  = typ;
	m_MMK  = mmk;
	m_Kurz = kurz;
	m_Lang = lang;
	m_Gueltig = FALSE;
	if (( typ != 'i' ) && ( typ != 'm' )) return;
	if ( mmk == 0L ) return;

	m_Gueltig = TRUE;		// wird bei MemError in Read() oder WriteBack()
							// ggf. wieder gelöscht!!
	if ( !Read())
	{	if( m_Kurz.IsEmpty())
		{	txt = m_Kurz.GetBuffer( 32 );
			sprintf( txt, "EDBS_%ld", mmk );
			m_Kurz.ReleaseBuffer();
		}
		WriteBack();
	}
}	// Konstruktor

void CMerkmalsKode :: WriteBack()
{
	ErrInstall	*ErrInst;

	if ( !Gueltig()) return;		// Falschen Typ abfangen!

	if ( m_Typ == 'i' ) {
		PBDDATA*	pbdi;
		pbdi = new PBDDATA;
		if ( pbdi ) {
			memset( pbdi, '\0', sizeof( PBDDATA ));

			ASSERT( m_MMK );

			ErrInst = new ErrInstall( WC_NOIDENT );

			pbdi -> dwSize = sizeof( PBDDATA );
			pbdi -> pbdTyp = m_Typ;
			pbdi -> pbdCode = m_MMK;
			pbdi -> pbdKText = m_Kurz.GetBuffer( KURZTEXT_LEN );
			pbdi -> pbdLText = m_Lang.GetBuffer( MAX_LANGTEXT_LEN );
			pbdi -> pbdTemp  = 0;
			pbdi -> pbdKTextLen = m_Kurz.GetLength();
			pbdi -> pbdLTextLen = m_Lang.GetLength();
			
			DEX_ModPBDDataEx( DEX_GetDataSourceHandle(), *pbdi );
			DEXN_PBDIdentChanged( m_MMK );
			if ( ErrInst ) delete ErrInst;
			m_Kurz.ReleaseBuffer();
			m_Lang.ReleaseBuffer();
			delete pbdi;
		}
		else
			m_Gueltig = FALSE;
	}
	else if ( m_Typ == 'm' ) {
#if _TRiAS_VER < 0x300
		PBDMERKMAL*	pbdm;
		pbdm = new PBDMERKMAL;
		if ( pbdm ) {
			memset( pbdm, '\0', sizeof( PBDMERKMAL ));
			pbdm -> dwSize = sizeof( PBDMERKMAL );
#else
		PBDMERKMALEX*	pbdm;
		pbdm = new PBDMERKMALEX;
		if ( pbdm ) {
			memset( pbdm, '\0', sizeof( PBDMERKMALEX ));
			pbdm -> dwSize = sizeof( PBDMERKMALEX );
#endif

			ASSERT( m_MMK );

			ErrInst = new ErrInstall( WC_NOMERKMAL );

			pbdm -> ipbdMTyp = 'a';
			pbdm -> ipbdMLen = 256;
			pbdm -> pbdTyp = m_Typ;
			pbdm -> pbdCode = m_MMK;
			pbdm -> pbdKText = m_Kurz.GetBuffer( KURZTEXT_LEN );
			pbdm -> pbdLText = m_Lang.GetBuffer( MAX_LANGTEXT_LEN );
			pbdm -> pbdKTextLen = m_Kurz.GetLength();
			pbdm -> pbdLTextLen = m_Lang.GetLength();
#if _TRiAS_VER >= 0x300
			pbdm -> lIdent = m_ulObjectClassTRiAS;
#endif
			DEX_ModPBDDataEx( DEX_GetDataSourceHandle(), *pbdm );
			DEXN_PBDMCodeChanged( m_MMK );
			if ( ErrInst ) delete ErrInst;
			m_Kurz.ReleaseBuffer();
			m_Lang.ReleaseBuffer();
			delete pbdm;
		}
		else
			m_Gueltig = FALSE;
	}
}	// WriteBack

bool CMerkmalsKode :: Read()
{
	bool result = FALSE;
	ErrCode ec;
	PBDDATA		*pbd;
	ErrInstall	*ErrInst;
	CString		strKurz, strLang;

	if ( !Gueltig())
		return result;	// falschen Typ abfangen!
	pbd = new PBDDATA;
	if ( pbd ) {
		if ( m_Typ == 'i' )
			ErrInst = new ErrInstall( WC_NOIDENT );
		else if ( m_Typ == 'm' )
			ErrInst = new ErrInstall( WC_NOMERKMAL );

		memset( pbd, '\0', sizeof( PBDDATA ));
		pbd -> dwSize = sizeof( PBDDATA );
		pbd -> pbdTyp = m_Typ;
		pbd -> pbdCode = m_MMK;
		pbd -> pbdKText = strKurz.GetBuffer( KURZTEXT_LEN );
		pbd -> pbdLText = strLang.GetBuffer( MAX_LANGTEXT_LEN );
		pbd -> pbdTemp  = 0;
		pbd -> pbdKTextLen = KURZTEXT_LEN - 1;
		pbd -> pbdLTextLen = MAX_LANGTEXT_LEN - 1;
		pbd -> pbdKText[0] = '\0';
		pbd -> pbdLText[0] = '\0';
		ec = DEX_GetPBDData( *pbd );
		strKurz.ReleaseBuffer();
		strLang.ReleaseBuffer();
		result = !strKurz.IsEmpty();
		if ( ErrInst )
			delete ErrInst;
		if ( EC_OKAY == ec  && result ) {
			m_Kurz = strKurz;
			m_Lang = strLang;
		}	
		else
			result = false;
	}
	else
		m_Gueltig = FALSE;

	delete pbd;
	return result;
}	// Read

//	-------------------------------------------------------------------
//	CKodeTabelle
//	-------------------------------------------------------------------
CKodeTabelle :: ~CKodeTabelle()
{
	for ( int i = 0; i < GetSize(); i++ )
		if ( GetAt( i ))
			delete (CMerkmalsKode*)GetAt( i );
}	// Destruktor

long CKodeTabelle :: FindeKode( const char* kurz )
{
	long kode = 0L;
	CMerkmalsKode* pMerkmalsKode;

	for ( int i = 0; i < GetSize(); i++ ) {
		pMerkmalsKode = (CMerkmalsKode*)GetAt( i );
		if (pMerkmalsKode->KurzText() == kurz ) {
			kode = ((CMerkmalsKode*)GetAt( i )) -> Kode();
			i = GetSize();
		}
	}
	return kode;
}	// FindeKode

bool CKodeTabelle :: KodeExist( long k )
{
	bool result = FALSE;

	for ( int i = 0; i < GetSize(); i++ )
		if (((CMerkmalsKode*)GetAt( i )) -> Kode() == k ) {
			result = TRUE;
			i = GetSize();
		}
	return result;
}	// KodeExist

bool CKodeTabelle :: Add( unsigned long ulObjectClassTRiAS, long kode, const char* kurz,
						const char* lang )
{
	bool		result = FALSE;
	CMerkmalsKode	*pMMK;

	if ( m_Typ == '\0' )
		return result;
	pMMK = new CMerkmalsKode( ulObjectClassTRiAS, m_Typ, kode, kurz, lang );

	if ( !pMMK )
		return result;
	if ( !pMMK -> Gueltig()) {
		delete pMMK;
		return result;
	}
	CObArray::Add( pMMK );
	result = TRUE;
	return result;
}	// Add

bool CKodeTabelle :: AddMMK( unsigned long ulObjectClassTRiAS, const char* def, bool hexbase )
{
	bool			result = FALSE;
	CMerkmalsKode	*pMMK;
	long			kode;
	CxString		strDef, strKey, strKurz, strLang;
	char			*stop;

	if ( m_Typ != 'm' )
		return result;
	if ( !def )
		return result;

	strDef = def;
	strDef.Teilen( strKey, strDef, ";" );
	if ( hexbase )
		kode = strtol( strKey, &stop, 16 );
	else
		kode = atol( strKey );

	if ( !kode )
		return result;
	if ( "/*" == strDef.Left( 2 )) {
		strDef = strDef.Mid( 2 );
		strDef.Teilen( strKurz, strLang, "*/" );
	}
	else
		strKurz = strDef;
	if ( strLang.IsEmpty())
		strLang = strKurz;

	pMMK = new CMerkmalsKode( ulObjectClassTRiAS, m_Typ, kode, strKurz, strLang );

	if ( !pMMK )
		return result;
	if ( !pMMK -> Gueltig() ) {
		delete pMMK;
		return result;
	}
	CObArray::Add( pMMK );
	result = TRUE;
	return result;
}	// Add

bool CKodeTabelle :: Mod( long kode, const char* kurz,
						const char* lang )
{	bool			result = FALSE;
	CMerkmalsKode	*pK;

	if ( kode == 0L )
		return result;
	if ( lstrlen( kurz ) == 0 )
		return result;

	for ( int i = 0; i < GetSize(); i++ )
		if (((CMerkmalsKode*)GetAt( i )) -> Kode() == kode ) {
			pK = (CMerkmalsKode*)GetAt( i );
			if ( pK -> Gueltig()) {
				pK -> KurzText() = kurz;
				if ( lstrlen( lang ))
					pK -> LangText() = lang;
				else
					pK -> LangText().Empty();
				pK -> WriteBack();
			}
			result = pK -> Gueltig();
			i = GetSize();
		}
	return result;
}	// Mod

//	-------------------------------------------------------------------
//	CTriasObjekt
//	-------------------------------------------------------------------
CTriasObjekt :: CTriasObjekt( CGeoObj* pGO )
{	
	m_pGO		= pGO;	
	m_lONr		= 0L;
	m_lIdent	= 0L;
	m_iObjTyp   = OGUnknown;
	m_lCnt		= 0L;
	m_iKCnt		= 0;
	m_pdblX		= NULL;
	m_pdblY		= NULL;
	m_plCnt		= NULL;
}	// Konstruktor

CTriasObjekt :: ~CTriasObjekt()
{
	if ( m_pdblX )
		delete [] m_pdblX;
	if ( m_pdblY )
		delete [] m_pdblY;
	if ( m_plCnt )
		delete [] m_plCnt;
	m_lONr		= 0L;
	m_lIdent	= 0L;
	m_iObjTyp   = OGUnknown;
	m_lCnt		= 0L;
	m_iKCnt		= 0;
	m_pdblX		= NULL;
	m_pdblY		= NULL;
	m_plCnt		= NULL;
}	// Destruktor

bool CTriasObjekt :: ReadyForRead()
{
	return ( ONr() != 0L );
//	return ((( ONr() != 0L ) && ( Ident() != 0L ) && ( ObjTyp() != OGUnknown ))
//			|| ( !UniqueIdent().IsEmpty()));
}	// ReadyForRead

bool CTriasObjekt :: ReadyForWrite()
{
	return	(( ONr() != 0L ) && ( Ident() != 0L ) && ( ObjTyp() != OGUnknown ));
//	return	(( ONr() != 0L ) && ( Ident() != 0L ) && ( ObjTyp() != OGUnknown )
//			&& ( AnzahlPunkte() > 0 ) && ( XKoord() != NULL ) && ( YKoord() != NULL )
//			&& ( AnzahlKonturen() > 0 ) && ( KonturPunkte() != NULL ));
}	// ReadyForWrite

static BOOL LeseStatusZeigen = TRUE;

bool CTriasObjekt :: Read()
{
	bool		result = FALSE;

	if ( !ReadyForRead())
		return result;

	if ( ONr() != 0L ) {
		// Objekt lesen
		OBJGEOMETRIE	*og;
		CString			key, text;
	
		og = new OBJGEOMETRIE;
	
		if ( og ) {
			memset( og, '\0', sizeof( OBJGEOMETRIE ));
			og -> dwSize  = sizeof( OBJSTATISTIK );
			og -> lONr    = ONr();
			result = DEX_GetObjStatistik( *og );
			if ( !result ) {
				delete og;
				return result;
			}

			XKoord( new double[og -> lCnt]);
			YKoord( new double[og -> lCnt]);
			KonturPunkte( new long[og -> iKCnt]);
			memset( og, '\0', sizeof( OBJGEOMETRIE ));
			og -> dwSize  = sizeof( OBJGEOMETRIE );
			og -> lONr    = ONr();
			og -> iFlags  = (short)( OGConverted );
			og -> pdblX   = XKoord();
			og -> pdblY   = YKoord();
			og -> plCnt   = KonturPunkte();

			result = DEX_GetObjGeometrie( *og );

			Ident() = og -> lIdent;
			ObjTyp() = og -> iObjTyp;
			AnzahlPunkte() = og -> lCnt;
			AnzahlKonturen() = og -> iKCnt;

			delete og;
		}
	}
	else {
		// Objekt über UniqueIdent suchen!
	}
	return result;
}	// Read
/*
void CTriasObjekt :: AddAttribute( const char *key, const char *text, bool add )
{	
	CString		temp;
	CAttribute* pAttr;

	temp = key;
	if ( temp.IsEmpty() )
		return;
	temp = text;
	if ( temp.IsEmpty() )
		return;

	pAttr = GetAttribute( key );
	if( pAttr ) {						// Schon vorhanden??
		if ( add ) {					// Ja! Neuen Text anfügen?
			pAttr->strValue += '\n';				// Ja!
			pAttr->strValue += text;
		}
		else							// Nicht anfügen ==> Ersetzen!
			pAttr->strValue = text;
	}
	else								// Noch nicht vorhanden!
		m_Attributes.SetAt( key, new CAttribute( key, text) );
}	// AddTextMerkmal
*/

bool CTriasObjekt :: WriteUniqueIdent()
{
 TARGETMERKMALEX	*m;
 CxString			strUniqueIdent;

	strUniqueIdent.printf("%s#%lu",UniqueIdent().Left(8),ONr());

	m  = new TARGETMERKMALEX;
	
	memset( m, '\0', sizeof( TARGETMERKMALEX ));
	m -> dwSize = sizeof( TARGETMERKMALEX );
	m -> lTarget = ONr();
	m -> lMCode = DEX_GetUniqueIdentMCodeEx(DEX_GetDataSourceHandle());
	ASSERT( m -> lMCode );
	m -> imaxLen = strUniqueIdent.GetLength();
	m -> iTTyp = TT_Objekt;
	m -> pMText = strUniqueIdent.GetBuffer( 256 );
	m -> iFlags = TMNoCaching;
	DEX_ModTextMerkmal( *m );
	strUniqueIdent.ReleaseBuffer();

	delete m;
	
	return true;
}

//void WriteAttribute( long lObjektnummer, CString strAttribute, CString strValue )
void CTriasObjekt :: WriteAttribute( CString strAttribute, CString strValue )
{
 TARGETMERKMALEX	*m = NULL;
 CObjectAttributeTRiAS	*pAttributeTRiAS;
	
	if ( !strAttribute.IsEmpty() && !strValue.IsEmpty() ) {
		if( !m_pGO->ObjectClassTRiAS()->Attributes().Lookup( strAttribute, (CObject*&)pAttributeTRiAS ) ) {
			pAttributeTRiAS = new CObjectAttributeTRiAS( strAttribute );
			m_pGO->ObjectClassTRiAS()->Attributes().SetAt( strAttribute, pAttributeTRiAS );
		}
		if( NULL != pAttributeTRiAS ) {
			if( 0 == pAttributeTRiAS->Ident() ) {
				ErrInstall	*ErrInst;
				pAttributeTRiAS->Ident() = DEX_GetMCodeFromFeatureNameEx( DEX_GetDataSourceHandle(), strAttribute.GetBuffer(strAttribute.GetLength()) );
				if( 0 == pAttributeTRiAS->Ident() )
					pAttributeTRiAS->Ident() = DEX_GetUniqueMCode();
				strAttribute.ReleaseBuffer();

#if _TRiAS_VER < 0x300
				PBDMERKMAL*	pbdm;
				pbdm = new PBDMERKMAL;
				if ( pbdm ) {
					memset( pbdm, '\0', sizeof( PBDMERKMAL ));
					pbdm -> dwSize = sizeof( PBDMERKMAL );
#else
				PBDMERKMALEX*	pbdm;
				pbdm = new PBDMERKMALEX;
				if ( pbdm ) {
					memset( pbdm, '\0', sizeof( PBDMERKMALEX ));
					pbdm -> dwSize = sizeof( PBDMERKMALEX );
#endif

					ErrInst = new ErrInstall( WC_NOMERKMAL );

					pbdm -> ipbdMTyp = 'a';
					pbdm -> ipbdMLen = 256;
					pbdm -> pbdTyp = 'm';
					pbdm -> pbdCode = pAttributeTRiAS->Ident();
					pbdm -> pbdKText = pAttributeTRiAS->Name().GetBuffer( KURZTEXT_LEN );
					pbdm -> pbdLText = pAttributeTRiAS->Description().GetBuffer( MAX_LANGTEXT_LEN );
					pbdm -> pbdKTextLen = pAttributeTRiAS->Name().GetLength();
					pbdm -> pbdLTextLen = pAttributeTRiAS->Description().GetLength();
#if _TRiAS_VER >= 0x300
					pbdm -> lIdent = m_pGO->ObjectClassTRiAS()->ClassIdentTRiAS();
#endif
					DEX_ModPBDDataEx( DEX_GetDataSourceHandle(), *pbdm );
					DEXN_PBDMCodeChanged( pAttributeTRiAS->Ident() );
					if ( ErrInst ) delete ErrInst;
					pAttributeTRiAS->Name().ReleaseBuffer();
					pAttributeTRiAS->Description().ReleaseBuffer();
					delete pbdm;
				}
			}
			if( NULL != pAttributeTRiAS->Ident() ) {
				m  = new TARGETMERKMALEX;
				memset( m, '\0', sizeof( TARGETMERKMALEX ));
				m -> dwSize = sizeof( TARGETMERKMALEX );
				m -> lTarget = ONr();
				m -> lMCode = pAttributeTRiAS->Ident();
				m -> imaxLen = strValue.GetLength();
				m -> iTTyp = TT_Objekt;
				m -> pMText = strValue.GetBuffer( m -> imaxLen );
				m -> iFlags = TMNoCaching;
				DEX_ModTextMerkmal( *m );
				strValue.ReleaseBuffer();
				delete m;
			}
		}
	}
}

bool CTriasObjekt :: WriteAttributes()
{
	CCfg	*pConfiguration;
	POSITION		pos;
	CString		key;

	pConfiguration = &((CEDBSExtension*)g_pTE)->Configuration;

	if( true == pConfiguration->m_tImportAttr && NULL != m_pGO ) {
		if ( true == pConfiguration->m_tCreateEDBSattr ) {
			if( pConfiguration->m_tCreateAttributeDateiname )
				WriteAttribute( "ALK-Dateiname", g_pTriasInterface->strImportFileName );	//fje
			if( pConfiguration->m_tCreateAttributeFolie )
				WriteAttribute( "ALK-Folie", m_pGO->Folie() );
			if( pConfiguration->m_tCreateAttributeObjektart )
				WriteAttribute( "ALK-Objektart", m_pGO->Objektart() );
			if( pConfiguration->m_tCreateAttributeAktualitaet )
				WriteAttribute( "ALK-Aktualität", m_pGO->Aktualitaet() );
			if( pConfiguration->m_tCreateAttributeObjektnummer )
				WriteAttribute( "ALK-Objektnummer", m_strUniqueIdent.Left(7) );
		}
		if ( true == pConfiguration->m_tCreateBIattr 
			 && true == m_pGO->hasAttributes() ) {
			CAttribute* pAttr;
			pos = m_pGO->m_Attributes.GetStartPosition();
			while ( pos != NULL ) {
				m_pGO->m_Attributes.GetNextAssoc( pos, key, (CObject*&)pAttr );
				WriteAttribute( key, pAttr->strValue );
			}
		}
	}
	return true;			
}

bool CTriasObjekt :: WriteErrorLog()
{
 CFile*			pErrorLog;

	if( g_pMetaData->CreateErrorLog() ) {
		POSITION pos;
		CAttribute* pAttr;
		if( !g_pTriasInterface->strImportFullErrorLogFileName.IsEmpty() ) {
			pErrorLog = new CFile( g_pTriasInterface->strImportFullErrorLogFileName, CFile::modeCreate | CFile::modeNoTruncate |CFile::modeWrite );
			pErrorLog->SeekToEnd();
			if( !UniqueIdent().IsEmpty() ) {
				pErrorLog->Write( "\"",1 );
				pErrorLog->Write( UniqueIdent(),UniqueIdent().GetLength() );
				pErrorLog->Write( "\"",1 );
			}
			for( pos = g_pMetaData->ErrorLogAttributes.GetHeadPosition(); pos != NULL;g_pMetaData->ErrorLogAttributes.GetNext(pos) ) {
				pErrorLog->Write( ";",1 );
				pAttr = m_pGO->GetAttribute(g_pMetaData->ErrorLogAttributes.GetAt(pos));
				if( pAttr ) {
					pErrorLog->Write( "\"",1 );
					pErrorLog->Write( pAttr->strValue,pAttr->strValue.GetLength() );
					pErrorLog->Write( "\"",1 );
				}
			}
			pErrorLog->Write( "\r\n",2 );
			pErrorLog->Close();
			delete pErrorLog;
		}
	}
	return true;
}

bool CTriasObjekt :: WriteBack()
{
	CCfg	*pConfiguration;
	bool			result = FALSE;
	OBJGEOMETRIE	*og;
	CxString		key;
	int ix;
	int cntp;


	pConfiguration = &((CEDBSExtension*)g_pTE)->Configuration;
	if ( !ReadyForWrite())
		return result;
	if( ObjTyp() == OGFlaeche && pConfiguration->m_tImportAreas == false )
		return result;
	if( ObjTyp() == OGLinie && pConfiguration->m_tImportLines == false )
		return result;
	if( ObjTyp() == OGPunkt && pConfiguration->m_tImportPoints == false )
		return result;
	if( ObjTyp() == OGText && pConfiguration->m_tImportText == false )
		return result;

	if( AnzahlKonturen() > 1 && ObjTyp() == OGFlaeche && g_pMetaData->Komplexobjekt(m_pGO->Folie() + m_pGO->Objektart()) ) {
		og = new OBJGEOMETRIE;
		if ( og ) {
			memset( og, '\0', sizeof( OBJGEOMETRIE ));
			og -> dwSize  = sizeof( OBJGEOMETRIE );
			for( ix = 0, cntp = 0; ix < AnzahlKonturen(); ix++ ) {
				og -> lONr    = -1;
				og -> lIdent  = Ident();
				og -> iObjTyp = ObjTyp();
				og -> iFlags  = (short)( OGNewObject
								| OGConverted
								| OGNoMemoryObject
								| OGForceGeometry );
				og -> lCnt    = *(KonturPunkte()+ix);
				og -> pdblX   = (double*)XKoord() + cntp;
				og -> pdblY   = (double*)YKoord() + cntp;
				
				og -> iKCnt   = 1;
				og -> plCnt   = KonturPunkte()+ix;
				cntp += *(KonturPunkte()+ix);
// Seiteneffekt: KonturPunkte() ändert sich in DEX_ModObjGeometrieEx
				if ( og -> lCnt > 0) {
				GEOMETRIEWITHCS GCS;

					INITSTRUCT(GCS, GEOMETRIEWITHCS);
					GCS.pOG = og;
					GCS.pICS = ((CEDBSExtension *)g_pTE)->get_CS();

					if( !DEX_ModObjGeometrieEx( DEX_GetDataSourceHandle(), GCS ) )
						WriteErrorLog();
					ONr() = og -> lONr;

					if ( ONr() > 0 ) {
						WriteAttributes();				
						if( pConfiguration->m_tCreateAttributeObjektteilnummerK ) {
							key.printf("%d",ix + 1);
							WriteAttribute( "ALK-ObjektteilnummerK", key );
						}
						CxString strUniqueIdent;
						strUniqueIdent.printf("%s#%lu",UniqueIdent().Left(8),ONr());
						WriteAttribute( "ObjUniqueIdent (intern)", strUniqueIdent );
//						WriteUniqueIdent();
					}
				}
			}
			delete og;
		}
	}
	else {
		og = new OBJGEOMETRIE;

		if ( og ) {
			memset( og, '\0', sizeof( OBJGEOMETRIE ));
			og -> dwSize  = sizeof( OBJGEOMETRIE );
			og -> lONr    = ONr();
			og -> lIdent  = Ident();
			og -> iObjTyp = ObjTyp();
			if ( Neu())
				og -> iFlags  = (short)( OGNewObject
								| OGConverted
								| OGNoMemoryObject
								| OGForceGeometry );
			else
				og -> iFlags  = (short)( OGModObject
								| OGConverted
								| OGNoMemoryObject
								| OGForceGeometry );

			og -> lCnt    = AnzahlPunkte();
			og -> pdblX   = XKoord();
			og -> pdblY   = YKoord();
			
			if( ObjTyp() == OGText ) {
				og -> iKCnt   = m_pGO->ObjLabel().GetLength();
				og -> plCnt   = (long*)(const char*)m_pGO->ObjLabel();
			}
			else {
				og -> iKCnt   = AnzahlKonturen();
				og -> plCnt   = KonturPunkte();
			}
			if ( AnzahlPunkte()) {
			GEOMETRIEWITHCS GCS;

				INITSTRUCT(GCS, GEOMETRIEWITHCS);
				GCS.pOG = (OBJGEOMETRIE *)og;
				GCS.pICS = ((CEDBSExtension *)g_pTE)->get_CS();

				if( !DEX_ModObjGeometrieEx( DEX_GetDataSourceHandle(), GCS) )
					WriteErrorLog();
//				XKoord( og -> pdblX );
//				YKoord( og -> pdblY );

				if( ONr() < 0 )
					ONr() = og -> lONr;

				if ( ONr() > 0 ) {
					WriteAttributes();				
					CxString strUniqueIdent;
					strUniqueIdent.printf("%s#%lu",UniqueIdent().Left(8),ONr());
					WriteAttribute( "ObjUniqueIdent", strUniqueIdent );
//					WriteUniqueIdent();
				}
			}
			delete og;
		}
	}
	return result;
}	// WriteBack




/**************************************************************************/
/*	CMapAliase  ***********************************************************/
/**************************************************************************/
/*
CMapAliase :: ~CMapAliase()
{
}
*/
/**************************************************************************/
/*	Format eines Eintrages: (veraltete Version)                           */
/*                                                                        */
/*	[EDBS]                                                                */
/*	...                                                                   */
/*	In=edbs-code,m,trias-id{,regel|alias{,regel|alias,...}}               */
/*	...                                                                   */
/*	                                                                      */
/*	In                          - nummerierter Eintrag                    */
/*	edbs-code                   - EDBS-Objektklasse (vierstellig)         */
/*	m                           - Anzahl der Regeln/Aliase                */
/*	trias-id                    - TRIAS-Objektklasse (ggf. mit x, y usw.  */
/*	                              für variable Codeteile. Treten vari-    */
/*	                              able Codeteile auf, so werden die x     */
/*	                              durch die erste Regel determiniert, y   */
/*	                              durch die zweite usw.)                  */
/*	regel                       - Name einer Regel                        */
/*	alias                       - Definition eines Alias der Form:        */
/*	                                 fkt:name                             */
/*	Dabei steht fkt für die Funktionsart und name für die Merkmalskurz-   */
/*	bezeichnung unter der der Text dieser Objektfunktion abgelegt wird.   */
/*	Weitere Besonderheit: Bei Funktionsart 44 werden automatisch und ohne */
/*	Definition eines Alias die ersten beiden Zeichen des Textes als Funk- */
/*	tionsart verwendet. Der eigentliche Text wird entsprechend gekürzt:   */
/*	Beispiel:                                                             */
/*	                       Funktionsart      Text                         */
/*	                           44            GNMagdeburg                  */
/*	                           44            ZNRothensee                  */
/*	wird umgewandelt in:                                                  */
/*	                           GN            Magdeburg                    */
/*	                           ZN            Rothensee                    */
/**************************************************************************/
/*	Format eines Eintrages: (aktuelle Version)                            */
/*                                                                        */
/*	[TYPEN]                                                               */
/*	...                                                                   */
/*	Tn=edbs-code,trias-id,text                                            */
/*	...                                                                   */
/*                                                                        */
/*	[edbs-code]                                                           */
/*	A1=attr:merkmal                                                       */
/*	...                                                                   */
/*	B1=attr,wert,trias-id                                                 */
/*	...                                                                   */
/*	                                                                      */
/**************************************************************************/
/*void CMapAliase :: AddEintrag( const char* eintrag )
{	CxString	strK, strKey, strText, strTemp, strEintrag;
	CxString	strWert, strMerkName;
	CxString	strIniFileName;
	int			i;

	strIniFileName = "EDBSALK.INI";
	strEintrag = eintrag;
	strEintrag.Teilen( strKey, strText, ',' );
	i = 1;
	strTemp.printf( "A%d", i++ );
	while ( strText.GetPrivateProfileString( strKey, strTemp, "",
					255, strIniFileName ))
	{	strText.Teilen( strK, strText, ':' );
		if ( !strK.IsEmpty() && !strText.IsEmpty())
		{	strTemp = strKey;
			strTemp += strK;
			SetAt( strTemp, strText );
		}
		strTemp.printf( "A%d", i++ );
	}
	i = 1;
	strTemp.printf( "C%d", i++ );
	while ( strText.GetPrivateProfileString( strKey, strTemp, "",
					255, strIniFileName ))
	{	strText.Teilen( strK, strText, ',' );
		strWert.Empty();
		strMerkName.Empty();
		if ( !strText.IsEmpty())
			strText.Teilen( strWert, strText, ',' );
		if ( !strText.IsEmpty())
			strText.Teilen( strMerkName, strText, ',' );

		if ( !strK.IsEmpty() && !strWert.IsEmpty() && !strText.IsEmpty())
		{
			strTemp = strMerkName;
			strTemp += "#";
			strTemp += strText;
			strText = strTemp;
			strTemp = strKey;
			strTemp += strK;
			strTemp += ":";
			strTemp += strWert;
			SetAt( strTemp, strText );
		}
		strTemp.printf( "C%d", i++ );
	}
}	// AddEintrag
*/
#include "crtdbg.h"

void CTriasInterface::EnableCrtMemDbgFlag( BOOL flag )
{
/*
	DWORD	flg = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );

	if ( flag )
	{
		_CrtSetDbgFlag( 5 );
		m_dwDbgFlag = flg;
	}
	else
		_CrtSetDbgFlag( m_dwDbgFlag );
*/
}

