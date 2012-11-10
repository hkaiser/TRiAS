//	Datei:	Linie.cpp
//	Stand:	30.08.1995
//	Autor:	Denkewitz
//	(c) 1995 uve GmbH FEZ Potsdam

#include "stdafx.h"
#include <string.h>
#include "koorpaar.h"
#include "objpool.hpp"
#include "linie.h"
#include "MetaData.h"

CLinie :: CLinie()
{
	m_cSplineKennung = ' ';
}	// Konstruktion

CLinie :: ~CLinie()
{
	short	i, n = m_Funktionen.GetSize();

	for ( i = 0; i < n; i++ )
		delete (CFunktion*)m_Funktionen[i];

	n = m_Punkte.GetSize();
	for ( i = 0; i < n; i++ )
		delete (CKoordPaar*)m_Punkte[i];
}	// Destruktion

short CLinie :: Lesen( const char *daten )
{
	short		i, j, n, result = 0;
	CString		buffer, Str = daten;
	CFunktion	*pFkt;
	CKoordPaar	*pPkt;

	m_EndPunkt.Setzen( daten );
	result += 20;
	Str = Str.Mid( 20 );

	m_Art[0] = Str[0];
	m_Art[1] = Str[1];
	m_Art[2] = '\0';
	result += 2;
	Str = Str.Mid( 2 );

	n = m_Funktionen.GetSize();
	for ( i = 0; i < n; i++ )
		delete (CFunktion*)m_Funktionen[i];
	m_Funktionen.RemoveAll();

	buffer = Str.Left( 4 ); Str = Str.Mid( 4 ); result += 4;
	n = atoi( buffer );
	for ( i = 0; i < n; i++ )
	{	pFkt = new CFunktion;
		if ( !pFkt ) {	m_bGueltig = FALSE; return result; }
		j = pFkt -> Lesen( Str ); Str = Str.Mid( j );
		result += j;
		m_Funktionen.Add( pFkt );
	}

	n = m_Punkte.GetSize();
	for ( i = 0; i < n; i++ )
		delete (CKoordPaar*)m_Punkte[i];
	m_Punkte.RemoveAll();

	buffer = Str.Left( 4 ); Str = Str.Mid( 4 ); result += 4;
	m_cSplineKennung = Str[0];
	n = atoi( buffer );
	for ( i = 0; i < n; i++ )
	{	pPkt = new CKoordPaar;
		if ( !pPkt ) {	m_bGueltig = FALSE; return result; }
		pPkt -> Setzen( Str ); Str = Str.Mid( 20 );
		result += 20;
		m_Punkte.Add( pPkt );
	}

	m_bGueltig = TRUE;
	return result;
}	// Lesen

short CLinie :: LesenALK( const char *daten )
{
	short		i, j, n, result = 0;
	CString		buffer, Str = daten;
	CFunktion	*pFkt;
	CKoordPaar	*pPkt;

	m_EndPunkt.Setzen( daten );
	result += 20;
	Str = Str.Mid( 20 );

	m_Art[0] = Str[0];
	m_Art[1] = Str[1];
	m_Art[2] = '\0';
	result += 2;
	Str = Str.Mid( 2 );

	n = m_Funktionen.GetSize();
	for ( i = 0; i < n; i++ )
		delete (CFunktion*)m_Funktionen[i];
	m_Funktionen.RemoveAll();

	buffer = Str.Left( 4 );
	Str = Str.Mid( 4 );
	result += 4;
	n = atoi( buffer );	// WHF Funktion der Linie
	for ( i = 0; i < n; i++ ) {
		pFkt = new CFunktion;
		if ( NULL == pFkt ) {	m_bGueltig = FALSE; return result; }
		j = pFkt -> LesenALK( Str ); Str = Str.Mid( j );
		result += j;
		m_Funktionen.Add( pFkt );
	}

	n = m_Punkte.GetSize();
	for ( i = 0; i < n; i++ )
		delete (CKoordPaar*)m_Punkte[i];
	m_Punkte.RemoveAll();

	buffer = Str.Left( 4 );
	Str = Str.Mid( 4 );
	result += 4;
	m_cSplineKennung = Str[0];
	n = atoi( buffer );
	for ( i = 0; i < n; i++ )
	{	pPkt = new CKoordPaar;
		if ( !pPkt ) {	m_bGueltig = FALSE; return result; }
		pPkt -> Setzen( Str ); Str = Str.Mid( 20 );
		result += 20;
		m_Punkte.Add( pPkt );
	}

	m_bGueltig = TRUE;
	return result;
}	// LesenALK

double CLinie :: PunktHoch( short pnr )
{
	if ( pnr < m_Punkte.GetSize())
		return ((CKoordPaar*)m_Punkte[pnr]) -> Hoch();
	else
		return 0.0;
}	// PunktHoch

double CLinie :: PunktRechts( short pnr )
{
	if ( pnr < m_Punkte.GetSize())
		return ((CKoordPaar*)m_Punkte[pnr]) -> Rechts();
	else
		return 0.0;
}	// PunktRechts

//	CFunktion
CFunktion :: CFunktion()
{
}	// Konstruktion

CFunktion :: ~CFunktion()
{
}	// Destruktion

short CFunktion :: Lesen( const char *daten )
{
	short		i, n, result = 0;
	CString		B, S = daten;
	const char	*pos = daten;

	B = S.Left( 4 ); S = S.Mid( 4 );
//	if ( atoi( B ) != 1 ) return result;
	result += 4; pos += 4;

	n = 0;
	for ( i = 0; i < 3; m_Folie[i++] = *pos++ );
	m_Folie[3] = '\0'; result += 3; n += 3;
	for ( i = 0; i < 4; m_ObjArt[i++] = *pos++ );
	m_ObjArt[4] = '\0'; result += 4; n += 4;
	for ( i = 0; i < 7; m_ObjNr1[i++] = *pos++ );
	m_ObjNr1[7] = '\0'; result += 7; n += 7;
	for ( i = 0; i < 7; m_ObjNr2[i++] = *pos++ );
	m_ObjNr2[7] = '\0'; result += 7; n += 7;
	for ( i = 0; i < 3; m_ObjTeilNr1[i++] = *pos++ );
	m_ObjTeilNr1[3] = '\0'; result += 3; n += 3;
	for ( i = 0; i < 3; m_ObjTeilNr2[i++] = *pos++ );
	m_ObjTeilNr2[3] = '\0'; result += 3; n += 3;
	m_LinienTeilung1[0] = *pos++; m_LinienTeilung1[1] = '\0';
	m_LinienTeilung2[0] = *pos++; m_LinienTeilung2[1] = '\0';
	result += 2; n += 2;
	S = S.Mid( n );

/*
	m_Folie          = S.Left( 3 ); S = S.Mid( 3 ); result += 3;
	m_ObjArt         = S.Left( 4 ); S = S.Mid( 4 ); result += 4;
	m_ObjNr1         = S.Left( 7 ); S = S.Mid( 7 ); result += 7;
	m_ObjNr2         = S.Left( 7 ); S = S.Mid( 7 ); result += 7;
	m_ObjTeilNr1     = S.Left( 3 ); S = S.Mid( 3 ); result += 3;
	m_ObjTeilNr2     = S.Left( 3 ); S = S.Mid( 3 ); result += 3;
	m_LinienTeilung1 = S.Left( 1 ); S = S.Mid( 1 ); result += 1;
	m_LinienTeilung2 = S.Left( 1 ); S = S.Mid( 1 ); result += 1;
*/
	B = S.Left( 4 ); S = S.Mid( 4 ); result += 4;
	if ( n = 9 * atoi( B ))
	{	m_FachParam = S.Left( n ); S = S.Mid( n ); result += n;
	}

	return result;
}	// Lesen

short CFunktion :: LesenALK( const char *daten )
{
	short		i, n, result = 0;
	CString		B, S = daten;
	const char	*pos = daten;

	n = 0;
	for ( i = 0; i < 3; m_Folie[i++] = *pos++ );
	m_Folie[3] = '\0';
	result += 3;
	n += 3;
	for ( i = 0; i < 4; m_ObjArt[i++] = *pos++ );
	m_ObjArt[4] = '\0';
	result += 4;
	n += 4;
/*
	if( m_ObjArt[0] == 'N' )	// L,R,A,Z in Objektart ausblenden
		m_ObjArt[0] = 'F';
	else if( m_ObjArt[0] > '9' )
		m_ObjArt[0] = '0';
*/
	for ( i = 0; i < 7; m_ObjNr1[i++] = *pos++ );
	m_ObjNr1[7] = '\0';
	result += 7;
	n += 7;
	for ( i = 0; i < 7; m_ObjNr2[i++] = *pos++ );
	m_ObjNr2[7] = '\0';
	result += 7;
	n += 7;
//	for ( i = 0; i < 3; m_ObjTeilNr1[i++] = *pos++ );
//	m_ObjTeilNr1[3] = '\0'; result += 3; n += 3;
	m_ObjTeilNr1[0] = '\0';
//	for ( i = 0; i < 3; m_ObjTeilNr2[i++] = *pos++ );
//	m_ObjTeilNr2[3] = '\0'; result += 3; n += 3;
	m_ObjTeilNr2[0] = '\0';
	m_LinienTeilung1[0] = *pos++; m_LinienTeilung1[1] = '\0';
	m_LinienTeilung2[0] = *pos++; m_LinienTeilung2[1] = '\0';
	result += 2; n += 2;
	S = S.Mid( n );

/*	B = S.Left( 4 ); S = S.Mid( 4 ); result += 4;
	if ( n = 9 * atoi( B ))
	{	m_FachParam = S.Left( n ); S = S.Mid( n ); result += n;
	}
*/
	return result;
}	// LesenALK

// CObjekt
CEDBSObjekt :: CEDBSObjekt()
{
	m_bGueltig = FALSE;
}	// Konstruktion

CEDBSObjekt :: ~CEDBSObjekt()
{
}	// Destruktion

short CEDBSObjekt :: Lesen( const char *daten )
{	short		i, result = 0;
	CString		Str = daten;
	const char	*pos = daten;
	CGeoObj		*pGO = NULL;

	for ( i = 0; i < 3; m_Folie[i++] = *pos++ );
	m_Folie[3] = '\0'; result += 3;
	for ( i = 0; i < 4; m_ObjArt[i++] = *pos++ );
	m_ObjArt[4] = '\0'; result += 4;
	for ( i = 0; i < 2; m_Aktuali[i++] = *pos++ );
	m_Aktuali[2] = '\0'; result += 2;
	m_ObjTyp[0] = *pos++;
	m_ObjTyp[1] = '\0'; result++;
	for ( i = 0; i < 7; m_ObjNr[i++] = *pos++ );
	m_ObjNr[7] = '\0'; result += 7;
	for ( i = 0; i < 2; m_ModellTyp[i++] = *pos++ );
	m_ModellTyp[2] = '\0'; result += 2;
	for ( i = 0; i < 6; m_EDatum[i++] = *pos++ );
	m_EDatum[6] = '\0'; result += 6;
	m_ModKenn[0] = *pos++;
	m_ModKenn[1] = '\0'; result++;
	m_bGueltig = TRUE;

	return result;
}	// Lesen

short CEDBSObjekt :: LesenALK( const char *daten )
{	short		i, result = 0;
	CString		Str = daten;
	const char	*pos = daten;

	for ( i = 0; i < 3; m_Folie[i++] = *pos++ );
	m_Folie[3] = '\0'; result += 3;
	for ( i = 0; i < 4; m_ObjArt[i++] = *pos++ );
	m_ObjArt[4] = '\0'; result += 4;
	for ( i = 0; i < 2; m_Aktuali[i++] = *pos++ );
	m_Aktuali[2] = '\0'; result += 2;
	m_ObjTyp[0] = *pos++;
	m_ObjTyp[1] = '\0'; result++;
	for ( i = 0; i < 7; m_ObjNr[i++] = *pos++ );
	m_ObjNr[7] = '\0'; result += 7;
//	for ( i = 0; i < 2; m_ModellTyp[i++] = *pos++ );
//	m_ModellTyp[2] = '\0'; result += 2;
	for ( i = 0; i < 6; m_EDatum[i++] = *pos++ );
	m_EDatum[6] = '\0'; result += 6;
//	m_ModKenn[0] = *pos++;
//	m_ModKenn[1] = '\0'; result++;
	m_ModKenn[0] = '\0';
	m_bGueltig = TRUE;

	return result;
}	// LesenALK

// CInfo
CInfo :: CInfo()
{
	m_bGueltig = FALSE;
	m_bGeoAngaben = FALSE;
	m_pPoints = NULL;
}	// Konstruktion

CInfo :: ~CInfo()
{
	if( m_pPoints )
		delete m_pPoints;
}	// Destruktion

short CInfo :: Lesen( const char *daten )
{	short		i, result = 0;
	char	strNumPoints[5];
	char	strPointAttr[21];
	int		iArtGeo;
	int		iNumPoints;
	const char	*pos = daten;

	for ( i = 0; i < 2; m_ArtInfo[i++] = *pos++ );
	m_ArtInfo[2] = '\0'; result += 2;
	for ( i = 0; i < 2; m_KartenTyp[i++] = *pos++ );
	m_KartenTyp[2] = '\0'; result += 2;
	for ( i = 0; i < 6; m_ObjArt[i++] = *pos++ );
	m_ObjArt[6] = '\0'; result += 6;
	for ( i = 0; i < 33; m_Text[i++] = *pos++ );
	m_Text[33] = '\0'; result += 33;
	for ( i = 0; i < 2; m_ArtGeo[i++] = *pos++ );
	m_ArtGeo[2] = '\0'; result += 2;
	for ( i = 0; i < 3; m_ObjTeilNr[i++] = *pos++ );
	m_ObjTeilNr[3] = '\0'; result += 3;

	m_bGeoAngaben = FALSE;
	strncpy( strNumPoints, pos, 4 );
	strNumPoints[4] = '\0';
	pos += 4;
	result += 4;
	iNumPoints = atoi( strNumPoints );
	iArtGeo = atoi( m_ArtGeo );
	iNumPoints = atoi( strNumPoints );
	if( iArtGeo == 53 ) {
		CKoordPaar Punkt;
		_ASSERT( iNumPoints == 2 );
		iNumPoints = 1;
		memcpy( strPointAttr, pos, 20 );
		strPointAttr[20] = '\0';
		pos += 20;
		result += 20;
		m_pPoints = new CPunktFolge(1);
		Punkt.Setzen( pos );
		pos += 20;
		result += 20;
		(*m_pPoints)[0] = new CPunkt( Punkt.Hoch(), Punkt.Rechts(), atoi(&strPointAttr[2]) );
		m_bGeoAngaben = TRUE;
	}
	else if( iNumPoints > 0 ) {
		m_pPoints = new CPunktFolge(iNumPoints);
		CKoordPaar Punkt;
		for( i = 0; i < iNumPoints; i++ ) {
			Punkt.Setzen( pos );
			pos += 20;
			result += 20;
			(*m_pPoints)[i] = new CPunkt( Punkt.Hoch(), Punkt.Rechts() );
		}
		m_bGeoAngaben = TRUE;
	}

	m_bGueltig = TRUE;

	return result;
}	// Lesen

/*
BOOL CInfo::PktGueltig( short n )
{
	if ( n == 1 )	return m_Pkt1.Gueltig();
	if ( n == 2 )	return m_Pkt2.Gueltig();
	if ( n == 3 )	return m_Pkt3.Gueltig();
	return FALSE;
}
*/
short CInfo :: LesenALK( const char *daten )
{	short		i, result = 0;
	char	strNumPoints[5];
	char	strPointAttr[21];
	int		iNumPoints;
	int		iArtGeo;
	const char	*pos = daten;

	for ( i = 0; i < 2; m_ArtInfo[i++] = *pos++ );
	m_ArtInfo[2] = '\0'; result += 2;
	for ( i = 0; i < 2; m_KartenTyp[i++] = *pos++ );
	m_KartenTyp[2] = '\0'; result += 2;
	for ( i = 0; i < 6; m_ObjArt[i++] = *pos++ );
	m_ObjArt[6] = '\0'; result += 6;
/*
	if( m_ObjArt[2] == 'N' )	// L,R,A,Z in Objektart ausblenden
		m_ObjArt[2] = 'F';
	if( m_ObjArt[2] > '9' )
		m_ObjArt[2] = '0';
*/
	for ( i = 0; i < 33; m_Text[i++] = *pos++ );
	m_Text[33] = '\0'; result += 33;
	for ( i = 0; i < 2; m_ArtGeo[i++] = *pos++ );
	m_ArtGeo[2] = '\0'; result += 2;
//	for ( i = 0; i < 3; m_ObjTeilNr[i++] = *pos++ );
//	m_ObjTeilNr[3] = '\0'; result += 3;
	m_ObjTeilNr[0] = '\0';

	m_bGeoAngaben = FALSE;
	strncpy( strNumPoints, pos, 4 );
	strNumPoints[4] = '\0';
	pos += 4;
	result += 4;
	iArtGeo = atoi( m_ArtGeo );
	iNumPoints = atoi( strNumPoints );
	if( iArtGeo == 53 ) {
		CKoordPaar Punkt;
		_ASSERT( iNumPoints == 2 );
		iNumPoints = 1;
		memcpy( strPointAttr, pos, 20 );
		strPointAttr[20] = '\0';
		pos += 20;
		result += 20;
		m_pPoints = new CPunktFolge(1);
		Punkt.Setzen( pos );
		pos += 20;
		result += 20;
		(*m_pPoints)[0] = new CPunkt( Punkt.Hoch(), Punkt.Rechts(), atoi(&strPointAttr[2]) );
		m_bGeoAngaben = TRUE;
	}
	else if( iNumPoints > 0 ) {
		m_pPoints = new CPunktFolge(iNumPoints);
		CKoordPaar Punkt;
		if( iArtGeo == 15 ) {
			Punkt.Setzen( pos );
			pos += 20;
			result += 20;
			(*m_pPoints)[0] = new CPunkt( Punkt.Hoch(), Punkt.Rechts() );
			if( iNumPoints > 1 ) {
				Punkt.Setzen( pos );
				pos += 20;
				result += 20;
				(*m_pPoints)[iNumPoints-1] = new CPunkt( Punkt.Hoch(), Punkt.Rechts() );
				for( i = 1; i < iNumPoints-1; i++ ) {
					Punkt.Setzen( pos );
					pos += 20;
					result += 20;
					(*m_pPoints)[i] = new CPunkt( Punkt.Hoch(), Punkt.Rechts() );
				}
			}
		}
		else
		for( i = 0; i < iNumPoints; i++ ) {
			Punkt.Setzen( pos );
			pos += 20;
			result += 20;
			(*m_pPoints)[i] = new CPunkt( Punkt.Hoch(), Punkt.Rechts() );
		}

		m_bGeoAngaben = TRUE;
	}
	m_bGueltig = TRUE;

	return result;
}	// LesenALK


char CLinie::SplineKennung()
{
	return m_cSplineKennung;
}
