///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			geoobj.cpp
//
//	Stand:			15.11.1994
//	Beschreibung:	Klassen für Geoobjekte
//	Entwicklung:	15.11.94	Beginn der Kodierung
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "geoobj.hpp"
#include "trif.hpp"
#include "cxstring.h"

CPunkt :: CPunkt( CPunkt &Muster )
{
	m_lHoch   = Muster.Hoch();
	m_lRechts = Muster.Rechts();
}


CPunkt :: operator == ( CPunkt &P )
{
	return (( m_lHoch == P.Hoch()) && ( m_lRechts == P.Rechts()));
}


CPunktPaar :: CPunktPaar( double h1, double r1, double h2, double r2 ) :
	m_Punkt1( h1, r1 ),
	m_Punkt2( h2, r2 )
{}


CPunktPaar :: CPunktPaar( CPunkt &p1, CPunkt &p2 ) :
	m_Punkt1( p1 ),
	m_Punkt2( p2 )
{}


CPunktFolge :: CPunktFolge( int iAnzahl )
{
	if ( iAnzahl > 0 )	SetSize( iAnzahl );
}	// Kontruktion


CPunktFolge :: CPunktFolge( CPunktFolge& Muster, BOOL bReverse )
{
int i, n = Muster.GetSize();

	if ( n ) SetSize( n );
	if ( bReverse )
	{	for ( i = 0; i < n; i++ )
			if ( Muster[i] ) SetAt( n - i - 1, new CPunkt( *(CPunkt*)Muster.GetAt( i )));
	}
	else
	{	for ( i = 0; i < n; i++ )
			if ( Muster[i] ) SetAt( i, new CPunkt( *(CPunkt*)Muster[i] ));
	}
}	// Konstruktion


CPunktFolge :: ~CPunktFolge()
{
//	for ( int i = 0; i < GetSize(); i++ ) if ( GetAt( i )) delete (CPunkt*)GetAt( i );
CPunkt	*pPT;

	for ( int i = 0; i < GetSize(); i++ ) {
		if ( pPT = (CPunkt*)GetAt( i ))
			delete pPT;
	}
	RemoveAll();
}


BOOL CPunktFolge :: AddFolge( CPunktFolge* pP )
{
BOOL	result = FALSE;
int		i;

//	Sonderfall 1: Die zu addierende Folge ist leer. ==> ignorieren! -------
	if ( pP -> GetSize() == 0 ) return result;

//	Sonderfall 2: Die aufnehmende Folge ist (noch) leer. ==> aufnehmen! ---
	if ( GetSize() == 0 )
	{
		result = TRUE;
		for ( i = 0; i < pP -> GetSize(); i++ )
			Add( new CPunkt( *(CPunkt*)(pP -> GetAt( i ))));
		return result;
	}

//	Sonderfall 3: Die zu addierende Folge schließt die Kontur. ------------
//				Wird im folgenden automatisch berücksichtigt! -------------

//	Normalfall: Beide Folgen sind nicht leer. ==> Gemeinsame Endpunkte ----
//				suchen. ---------------------------------------------------
//	Sonderfall 4: Folgen die lediglich aus einem Punkt bestehen werden ----
//				jeweils bei Existenz eines gemeinsamen Endpuktes be- ------
//				rücksichtigt. ---------------------------------------------

	if ( pP -> First() == Last())		// einfach anhängen!
	{
		result = TRUE;					// -> erster Punkt in pP fällt unter
		if ( pP -> GetSize() > 1 )		//	  den Tisch!
			for ( i = 1; i < pP -> GetSize(); i++ )
				Add( new CPunkt( *(CPunkt*)(pP -> GetAt( i ))));
	}
	else if ( pP -> Last() == First())	// vorn einfügen
	{
		result = TRUE;					// erster Punkt via InsertAt
		if ( pP -> GetSize() > 1 )		// der Rest folgt via SetAt, nur der letzte
		{
			InsertAt( 0, new CPunkt( pP -> First()), pP -> GetSize() - 1 );
			for ( i = 1; i <= pP ->	GetSize() - 2; i++ )	// fällt weg!
				SetAt( i, new CPunkt( *(CPunkt*)(pP -> GetAt( i ))));
		}
	}
	else if ( pP -> Last() == Last())	// umdrehen und anhängen
	{
		result = TRUE;					// -> letzter Punkt wird durch Umdrehen
		if ( pP -> GetSize() > 1 )		//    erster und fällt weg!
			for ( i = pP -> GetSize() - 2; i >= 0; i-- )
				Add( new CPunkt( *(CPunkt*)(pP -> GetAt( i ))));
	}
	else if ( pP -> First() == First())	// umdrehen und vorn einfügen
	{
		result = TRUE;					// letzter Punkt via InsertAt
		if ( pP -> GetSize() > 1 )		// der Rest folgt via SetAt, nur der erste
		{	InsertAt( 0, new CPunkt( pP -> Last()), pP -> GetSize() - 1 );
			for ( i = pP ->	GetSize() - 2; i > 0; i-- )	// fällt weg
				SetAt( pP -> GetSize() - i - 1, new CPunkt( *(CPunkt*)(pP -> GetAt( i ))));
		}
	}
	return result;
}

//	CGeoObj  --------------------------------------------------------------
CGeoObj :: ~CGeoObj()
{
	for ( int i = 0; i < m_oaPunktFolgen.GetSize(); i++ ) 
		delete (CPunktFolge*)m_oaPunktFolgen[i];
	m_oaPunktFolgen.RemoveAll();
}


CGeoObj *CGeoObj :: AddFolge( CPunktFolge* pP, const char* folie, const char* art )
{
	BOOL	found = FALSE;
	CGeoObj	*pGO = NULL;
	CPunkt	*pP1, *pP2, *pP3, *pP4;
	int		i = 0;

//	#AD990902#
//	Anfangs- und Endpunkt der neuen Punktfolge merken
	pP1 = &pP -> First();
	pP2 = &pP -> Last();
//	Fehlerhafte PunktFolgen ( mit nur einem Punkt ) hier wieder löschen!
	while ( i < m_oaPunktFolgen.GetSize())
	{
		if (((CPunktFolge*)m_oaPunktFolgen[i]) -> GetSize() < 2 )
		{
			delete (CPunktFolge*)m_oaPunktFolgen[i];
			m_oaPunktFolgen.RemoveAt( i );
		}
		i++;
	}

	i = 0;
	while ( !found && ( i < m_oaPunktFolgen.GetSize()))
	{
//		#AD990902#
//		Anfangs- und Endpunkt der getesteten Folge merken
		pP3 = &((CPunktFolge*)m_oaPunktFolgen[i]) -> First();
		pP4 = &((CPunktFolge*)m_oaPunktFolgen[i]) -> Last();
		found = ((CPunktFolge*)m_oaPunktFolgen[i++]) -> AddFolge( pP );
//		#AD990902#
//		War der Test erfolgreich, Verknüpfungspunkt merken
		if ( found )
		{
			if ( *pP1 == *pP4 )			m_VPunkte.Add( new CPunkt( *pP1 ));
			else if ( *pP2 == *pP3 )	m_VPunkte.Add( new CPunkt( *pP2 ));
			else if ( *pP1 == *pP3 )	m_VPunkte.Add( new CPunkt( *pP1 ));
			else if ( *pP2 == *pP4 )	m_VPunkte.Add( new CPunkt( *pP2 ));
		}
	}

	if ( !found ) {	
		m_oaPunktFolgen.Add( new CPunktFolge( *pP ));
		if (pP -> Geschlossen()) 
			pGO = this;
	}
	else {
		if ( m_oaPunktFolgen.GetSize() > 1 )	
			i = Zusammenfassen( i - 1 );
		else
			i--;

		if ( i >= 0 ) {
			if (((CPunktFolge*)m_oaPunktFolgen[i]) -> Geschlossen())
			{
//			#AD990902#
//			Wenn eine geschlossene Kontur entstanden ist, prüfen und behandeln.
				TestSelbstinzidenz( i );
				pGO = this;
			}
		}
	}

	if ( m_strFolie.IsEmpty())
		m_strFolie = folie;
	else if ( m_strFolie.Find( folie ) < 0 )
	{
		m_strFolie += ", ";
		m_strFolie += folie;
	}

	if ( m_strObjektArt.IsEmpty())
		m_strObjektArt = art;
	else if ( m_strObjektArt.Find( art ) < 0 )
	{
		m_strObjektArt += ", ";
		m_strObjektArt += art;
	}

	return pGO;
}	// AddFolge

int CGeoObj :: Zusammenfassen( int idx )
{
CPunktFolge	*pP = ((CPunktFolge*)m_oaPunktFolgen[idx]);
BOOL		found = FALSE;
int			i = 0;
int			result = -1;

	while ( !found && ( i < m_oaPunktFolgen.GetSize()))
	{
		if ( i != idx )
			found = ((CPunktFolge*)m_oaPunktFolgen[i]) -> AddFolge( pP );
		if ( found )
			result = i;
		i++;
	}
	if ( found )		// erfolgreich zusammengefasst!
	{
		delete pP;
		m_oaPunktFolgen.RemoveAt( idx );
		if ( result > idx ) result--;
	}

	return result;
}	// Zusammenfassen

void CGeoObj :: Pack()
{
	for ( int i = 0; i < m_oaPunktFolgen.GetSize(); i++ )
		if ( !m_oaPunktFolgen[i] ) 
			m_oaPunktFolgen.RemoveAt(i--);
}	// Pack


void CGeoObj :: AddTextMerkmal( const char* art, const char* text )
{	
CString		oldtext;

	m_TextMerkmale.Lookup( art, oldtext );
	if ( !oldtext.IsEmpty())
	{
		if ( text == oldtext )	return;
		if ( -1 == oldtext.Find( text ))
		{
			oldtext += ", ";
			oldtext += text;
		}
	}
	else
		oldtext = text;

	m_TextMerkmale.SetAt( art, oldtext );
}	// AddTextMerkmal


void CGeoObj :: SetzPunkt( double lH, double lR )
{
CPunktFolge		*pPF;

	if ( AnzahlLinien() || ObjNr() ) return;	// nur für Objekte ohne Geometrie

	m_oaPunktFolgen.Add( pPF = new CPunktFolge( 1 ));
	(*pPF)[0] = new CPunkt( lH, lR );
}	// SetzPunkt

static BOOL ZeigeLeseFehler = TRUE;

void CGeoObj :: ReDefType( const char *type )
{
CTriasObjekt	TO;
CxString	text;

	ASSERT( ObjNr() != 0L );
	TO.ONr() = ObjNr();
	TO.ObjTyp() = ObjTyp();
	if ( TO.Read())	{
		if ( ZeigeLeseFehler ) {
			text.printf( "Objekt gelesen: %s, (Punkte: %d, Linien: %d, ID: %ld)", (const char*)UniqueIdent(), TO.AnzahlPunkte(), TO.AnzahlKonturen(), TO.Ident());
			if ( AfxMessageBox( text, MB_OKCANCEL ) != IDOK ) 
				ZeigeLeseFehler = FALSE; 
		}

		TO.ObjTyp() = *type;
		TO.ONr()  = 0L;
		TO.Neu() = TRUE;
		TO.WriteBack();

		if ( ZeigeLeseFehler ) {
			text.printf( "Objekt gelesen und geschrieben: %s, (alt: %ld) (neu: %ld)", (const char*)UniqueIdent(), ObjNr(), TO.ONr());
			if ( AfxMessageBox( text, MB_OKCANCEL ) != IDOK ) 
				ZeigeLeseFehler = FALSE; 
		}

		ASSERT( TO.ONr() != 0L );
//		DEX_DeleteObject( ObjNr());
		if (TO.ONr() != 0L)
			ObjNr() = TO.ONr();
	} 
	else if ( ZeigeLeseFehler ) {
		text = "Objekt nicht gelesen: ";
		text += UniqueIdent();
		if ( AfxMessageBox( text, MB_OKCANCEL ) != IDOK ) 
			ZeigeLeseFehler = FALSE; 
	}
}	// ReDefType

// #AD990902#
// Testet die übergebene Folge, ob sie einen der registrierten Verknüpfungspunkte
// mehrfach enthält (außer am Anfang und Ende) und behandelt diese Selbstinzidenz durch
// Aufspaltung in mehrere Konturen.
void CGeoObj::TestSelbstinzidenz( int idx )
{
CPunktFolge	*pP = ((CPunktFolge*)m_oaPunktFolgen[idx]);
CPunkt		*pPTest;
int			i, j, k, k1, k2;

	for ( i = 0; i < m_VPunkte.GetSize()-1; i++ )
	{
		pPTest = (CPunkt*)m_VPunkte[i];
		for ( j = i+1; j < m_VPunkte.GetSize(); j++ )
			if ( *pPTest == *(CPunkt*)m_VPunkte[j])
		{
			k1 = k2 = -1;
			for ( k = 0; k < pP -> GetSize(); k++ )
				if ( *pPTest == *((CPunkt*)pP -> GetAt( k )))
			{
				if ( k1 < 0 )		k1 = k;
				else
				{
					if ( k2 < 0 )	k2 = k;
					else
						AfxMessageBox( "Ich passe! Mehrfachüberschneidung in einem Punkt!" );
				}
			}
			if (( k1 >= 0 ) && ( k2 >= 0 ))
			{
				// 1. Geschlossene Kontur aufspalten
				if (( k1 > 0 ) || ( k2 < ( pP -> GetSize()-1 )))
					KonturAufspalten( idx, k1, k2 );
			}
		}
	}
}

// #AD990902#
void CGeoObj::KonturAufspalten( int idx, int k1, int k2 )
{
CPunktFolge	*pP = ((CPunktFolge*)m_oaPunktFolgen[idx]);
CPunktFolge	*pPNeu = NULL;
int			i;

	pPNeu = new CPunktFolge;
	for ( i = k1; i <= k2; i++ )
		pPNeu -> Add( new CPunkt( *((CPunkt*)pP -> GetAt( i ))));
	for ( i = k2; i > k1; i-- )
		pP -> RemoveAt( i );
	m_oaPunktFolgen.Add( pPNeu );
}
