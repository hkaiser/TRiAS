///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			trif.h
//
//	Stand:			02.12.1994
//	Beschreibung:	TRIAS-Interface-Objekt
//					- Header-Update
//					- IdentsDB-Update
//					- GeoObjekt-Zugriff
//	Entwicklung:	02.12.94	Beginn der Kodierung
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#if defined(_USE_B_REGELN)

#include "cxstring.h"
#include "trif.hpp"
#include "regeln.hpp"

extern CTriasInterface*	g_pTriasInterface;

extern int AllTrimm( CString& );
extern BOOL IsHexDigit( char );


/**************************************************************************/
/*	CRegel  ***************************************************************/
/**************************************************************************/
CRegel :: CRegel( const char *eintrag )
{
CxString	strK, strKey, strText, strTemp, strEintrag;
CxString	strW, strI;
CxString	strIniFileName;
int			i;

	strIniFileName = g_pTriasInterface->GetIniFileName();
	strEintrag = eintrag;
	strEintrag.Teilen( strKey, strText, ',' );
	i = 1;
	strTemp.printf( "B%d", i++ );
	while ( strText.GetPrivateProfileString( strKey, strTemp, "", 255, strIniFileName ))
	{	strText.Teilen( strK, strText, ',' );
		strText.Teilen( strW, strI, ',' );
		if ( !strK.IsEmpty() && !strI.IsEmpty())
		{	strText  = strK;
			strText += "#";
			if ( !strW.IsEmpty()) strText += strW;
			m_mapWerte.SetAt( strText, strI );
			if ( !m_listMerkmale.Find( strK ))
				m_listMerkmale.AddHead( strK );
		}
		strTemp.printf( "B%d", i++ );
	}
}

void CRegel :: And( CString &id, const char *m )
{
char	*z, *q;
CString	Q = m;
BOOL	fertig = TRUE;

	for ( q = Q.GetBuffer( Q.GetLength()); *q; q++ )
		if ( !IsHexDigit( *q )) fertig = FALSE;
	Q.ReleaseBuffer();
	if ( fertig )
	{	id = m;		// Sonderfall 1: Neuer ID ist eindeutig und
		return;		//   dominiert bisherige Angaben!
	}

	fertig = TRUE;
	for ( z = id.GetBuffer( id.GetLength()); *z; z++ )
		if ( IsHexDigit( *z )) fertig = FALSE;
	id.ReleaseBuffer();
	if ( fertig )
	{				// Sonderfall 2: Alter ID ist eindeutig und
		return;		//   dominiert neue Angaben!
	}

	z = id.GetBuffer( id.GetLength());
	q = Q.GetBuffer( Q.GetLength());
	while ( *z && *q )
	{	if ( *z != *q )		// Nur wenn die Zeichen sich unterscheiden
			if ( IsHexDigit( *q )) *z = *q;
		z++;
		q++;
	}
	id.ReleaseBuffer();
	Q.ReleaseBuffer();
}

void CRegel :: LiesRegel( const char *name, char &c, const char *id )
{
CxString	strBuffer, strId1, strId2, strIdent;
CxString	strE, strR, strK, strT;
BOOL		neu;
int			i = lstrlen( id );

	strBuffer.GetPrivateProfileString( "Bedingungen", name, "", 255, g_pTriasInterface->GetIniFileName() );

	strId1 = id;
	strId1.Teilen( strId1, strId2, c );
	while (( !strId2.IsEmpty()) && ( strId2.GetAt( 0 ) == c )) 
		strId2 = strId2.Mid( 1 );

	strR = strBuffer;
	neu = TRUE;
	while ( !strR.IsEmpty())
	{	strR.Teilen( strE, strR );
		strE.Teilen( strK, strT, ':' );
		if ( strId1.GetLength() + strId2.GetLength() + strT.GetLength() == i )
		{	strIdent  = strId1;
			strIdent += strT;
			strIdent += strId2;
		}
		else
		{	strIdent = strT;
			c--;				// Bedingungen die nichts ersetzen zählen nicht!
		}

		m_mapWerte.SetAt( strK, strIdent );
		strK.Teilen( strK, strT, '#' );

		if ( !strK.IsEmpty() && neu )
		{	m_listMerkmale.AddHead( strK );
			neu = FALSE;
		}
	}
}

BOOL CRegel :: GetIdent( CMapStringToString *mapMerkmale, CString &ident )
{
BOOL		result = FALSE;
POSITION	pos;
CString		strKey, strText, strTemp, strDefa;

	ident.Empty();
	for ( pos = m_listMerkmale.GetHeadPosition(); pos != NULL; )
	{
		strKey = m_listMerkmale.GetNext( pos );
		strText.Empty();
		mapMerkmale -> Lookup( strKey, strText );
		strKey += '#';
		strDefa.Empty();
		m_mapWerte.Lookup( strKey, strDefa );
		strKey += strText;
		strTemp.Empty();
		m_mapWerte.Lookup( strKey, strTemp );
		if ( strTemp.IsEmpty()) strTemp = strDefa;

		if ( ident.IsEmpty())	ident = strTemp;
		else					And( ident, strTemp );

		if ( !ident.IsEmpty()) result = TRUE;
	}

	return result;
}

/**************************************************************************/
/*	CMapRegeln  ***********************************************************/
/**************************************************************************/

CMapRegeln :: ~CMapRegeln()
{
	Tidy();
}

void CMapRegeln::Tidy()
{
POSITION	pos;
CString		key;
CRegel		*regel;

	for ( pos = GetStartPosition(); pos != NULL; )
	{
		GetNextAssoc( pos, key, (void*&)regel );
		delete regel;
	}
	RemoveAll();
}

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
void CMapRegeln :: AddEintrag( const char* eintrag )
{	
CxString	strK, strKey, strText, strTemp, strEintrag;
CxString	strIniFileName;

	strIniFileName = g_pTriasInterface->GetIniFileName();
	strEintrag = eintrag;
	strEintrag.Teilen( strKey, strText, ',' );
	if ( strText.GetPrivateProfileString( strKey, "B1", "",	255, strIniFileName ))
		SetAt( strKey, new CRegel( strKey ));
}

#endif // defined(_USE_B_REGELN)
