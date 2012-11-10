///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			objpool.cpp
//
//	Stand:			02.12.1994
//	Beschreibung:	ObjektPool-Objekt
//					- Erzeugen der GeoObjekte
//					- Verändern der GeoObjekte
//					- Schreiben der GeoObjekte nach TRIAS
//	Entwicklung:	02.12.94	Beginn der Kodierung
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "geoobj.hpp"
#include "objpool.hpp"
#include "trif.hpp"

#include "resource.h"

#include "istatus.h"
#include "edbs.hpp"
#include "cxstring.h"

#include <xtension.h>

extern CTriasInterface	*g_pTriasInterface;

extern void		Kommentar( const char*, const int );
extern void		Kommentar( int, const int );
extern void		Kommentar( long, const int );
extern void		Kommentar( double, const int );
extern void		Kommentar( char, const int );
extern void		Meldung( const char* );
extern void		Meldung( int );
extern void		Meldung( long );
extern void		KommNL( const char*, const int );
extern void		KommNL( int, const int );
extern void		KommNL( long, const int );
extern void		KommNL( double, const int );
extern void		KommNL( char, const int );
extern void		MeldNL( const char* );
extern void		MeldNL( int );
extern void		MeldNL( long );
extern void		MeldNL( double );


CObjektPool::CObjektPool()
{
	m_pgoReady = NULL;
}

CObjektPool::~CObjektPool()
{
	for (POSITION pos = m_omGeoObjekte.GetStartPosition(); pos != NULL; /**/)
	{
	CString		key;
	CGeoObj		*pGO;

		m_omGeoObjekte.GetNextAssoc( pos, key, (CObject *&)pGO );
		delete pGO;
	}
	m_omGeoObjekte.RemoveAll();
}

void CObjektPool::Clear()
{
	for (POSITION pos = m_omGeoObjekte.GetStartPosition(); pos != NULL; /**/)
	{
	CString		key;
	CGeoObj		*pGO;

		m_omGeoObjekte.GetNextAssoc(pos, key, (CObject *&)pGO );
		if (pGO -> ObjNr())
			g_pTriasInterface -> DeleteObjekt(pGO -> ObjNr());
	}
}	// Clear


/*	AddLine  **************************************************************/
/*				Fügt eine gelesene Punktfolge an ein existierendes GeoOb- */
/*	jekt an bzw. erzeugt ein neues GeoObjekt, wenn zur übergebenen ID     */
/*	kein GeoObjekt gefunden wird.                                         */
/*	Außerdem werden Folie und ObjektArt gesetzt.                          */
/**************************************************************************/
void CObjektPool::AddLine(
	const char* pID, CPunktFolge* pP, const char* teil, const char* folie, const char* art)
{
CGeoObj		*pGO = NULL;
CString		strObjID;

	strObjID = pID;
	if (( NULL != teil ) && ('\0' != *teil))
	{
		m_mapMultiObj.SetAt( pID, NULL );

		strObjID += "-";
		strObjID += teil;
	}

//	m_omGeoObjekte.Lookup( pID, (CObject*&)pGO );
//	if ( !pGO )
//		m_omGeoObjekte.SetAt( pID, pGO = new CGeoObj( pID ));
	m_omGeoObjekte.Lookup(strObjID, (CObject*&)pGO );
	if (!pGO)
		m_omGeoObjekte.SetAt(strObjID, pGO = new CGeoObj( strObjID ));

	m_pgoReady = pGO -> AddFolge(pP, folie, art);
}	// AddLine

static BOOL HideRedefError = FALSE;

/*	DefType  **************************************************************/
/*				Setzt ObjektTyp, ObjektArt und Folie für das übergebene   */
/*	Objekt (ID), wird kein Objekt mit dieser ID gefunden, so wird ein     */
/*	GeoObjekt mit der übergebenen ID erzeugt.                             */
/**************************************************************************/
void CObjektPool::DefType( const char *pID, const char *typ,
								const char *art, const char *folie )
{
	CGeoObj		*pGO = NULL;
	CString		text;

	m_omGeoObjekte.Lookup( pID, (CObject*&)pGO );
	if ( !pGO )
		m_omGeoObjekte.SetAt( pID, pGO = new CGeoObj( pID ));

	if (( pGO -> ObjTyp() != 'U' ) &&
		( pGO -> ObjTyp() != *typ ))
	{
		text = "Typ Redefinition!  '";
		text += pGO -> ObjTyp();
		text += "' wird '";
		text += typ;
		text += "'  ";
		text += pGO -> UniqueIdent();
		if ( !HideRedefError )
			if ( AfxMessageBox ( text, MB_OKCANCEL ) != IDOK )
				HideRedefError = TRUE;

		// Nur Linien, die irrtümlich als Flächen gespeichert wurden!!
		// ==> geschlossener Polygonzug
		if ( *typ == 'L' )
			pGO -> ReDefType( typ );

		pGO -> ObjTyp() = *typ;
	}
	else
		pGO -> ObjTyp() = *typ;

	if ( pGO -> Folie().IsEmpty())
		pGO -> Folie() = folie;
	else
		if ( pGO -> Folie().Find( folie ) < 0 )
		{	pGO -> Folie() += ", ";
			pGO -> Folie() += folie;
		}

	if ( pGO -> ObjektArt().IsEmpty())
		pGO -> ObjektArt() = art;
	else
		if ( pGO -> ObjektArt().Find( art ) < 0 )
		{
			text = art;
			text += ", ";
			text += pGO -> ObjektArt();
			pGO -> ObjektArt() = text;
		}
}	// DefType

/*	BesondInfo  ***********************************************************/
/*					Fügt Informationen aus dem Bereich BesondInfo des     */
/*	EDBS-Satzes an das GeoObjekt an. Wird kein Objekt mit der entsprechen-*/
/*	den ID gefunden, so wird ein neues Objekt erzeugt.                    */
/**************************************************************************/
void CObjektPool::BesondInfo(
	const char *pID, const char *infoart, const char *objart,
	const char *text, double lH, double lR)
{	
CGeoObj *pGO = NULL;
CString key, newkey, strText, txt;
CxString strNewKey;

	m_omGeoObjekte.Lookup(pID, (CObject *&)pGO);
	if (!pGO)
		m_omGeoObjekte.SetAt(pID, pGO = new CGeoObj(pID));

	strText = text;
	if (!strText.IsEmpty() && (strText != "NNNN")) {	
		if (!g_pTriasInterface -> GetAlias(objart, infoart, newkey))
			newkey = infoart;

		pGO -> AddTextMerkmal(newkey, text);
		g_pTriasInterface -> NeuesMerkmal(newkey);

		key = infoart;
		key += ":";
		key += text;
		if (g_pTriasInterface -> GetAlias(objart, key, newkey))
		{
			if ( !newkey.IsEmpty())
			{
				strNewKey = newkey;
				strNewKey.Teilen(newkey, strText, '#');

				pGO -> AddTextMerkmal(newkey, strText);
				g_pTriasInterface -> NeuesMerkmal(newkey);
			}
		}
	}

	if (( lH != 0.0 ) && ( lR != 0.0 ))
		pGO -> SetzPunkt( lH, lR );

	if (pGO -> ObjektArt().IsEmpty())
		pGO -> ObjektArt() = objart;
	else if (pGO -> ObjektArt().Find(objart) < 0)
	{
		txt = objart;
		txt += ", ";
		txt += pGO -> ObjektArt();
		pGO -> ObjektArt() = txt;
	}
}	// BesondInfo


/*	AddMerkmal  ***********************************************************/
/*				Fügt ein Merkmal an das GeoObjekt an. Wird kein Objekt    */
/*	mit der entsprechenden ID gefunden, erfolgt die Rückgabe von FALSE.   */
/**************************************************************************/
BOOL CObjektPool::AddMerkmal( const char *pID, const char *k, const char *t )
{	
CGeoObj		*pGO = NULL;
BOOL		res = FALSE;

	m_omGeoObjekte.Lookup( pID, (CObject*&)pGO );
	if ( !pGO )
		m_omGeoObjekte.SetAt( pID, pGO = new CGeoObj( pID ));

	if ( pGO )
	{
		pGO -> AddTextMerkmal( k, t );
		g_pTriasInterface -> NeuesMerkmal( k );
		res = TRUE;
	}

	return res;
}	// AddMerkmal


CGeoObj *CObjektPool::Fertig()
{	
CGeoObj *pGO = m_pgoReady;

	m_pgoReady = NULL;
	return pGO;

//CTriasObjekt	*pTO;
//CPunktFolge		*pPF;
//CPunkt			*pPT;
//POSITION		posMM;
//CString			key, text;
//int				j;
//long			l, z, kp;
//
//	if ( pGO )
//	{	
////	------------------------------------------------------------------------------------
////	Hier ansetzen um Objekte mit Löchern zu identifizieren!
////	------------------------------------------------------------------------------------
//		for ( j = 0; j < pGO -> AnzahlLinien(); j++ )
//		{	if (( pPF = pGO -> Punkte( j )) -> Geschlossen())
//			{	
//				pTO = new CTriasObjekt();
//				if ( pTO )
//				{	
//					pTO -> ONr() = -1;				// neues Objekt!
//					pTO -> Ident() = g_pTriasInterface -> GetIdent( pGO -> ObjektArt(), pGO -> Merkmale());
//					if (( z = pGO -> AnzahlPunkte( j )) == 1 )
//					{
//						pTO -> ObjTyp() = OGPunkt;
//						pGO -> ObjTyp() = 'P';
//					}
//					else
//					{
//						pTO -> ObjTyp() = OGFlaeche;
//						pGO -> ObjTyp() = 'F';
//					}
//					kp = pTO -> AnzahlPunkte() = z;
//					pTO -> AnzahlKonturen() = 1;
//					pTO -> XKoord( new double[z+1] );
//					pTO -> YKoord( new double[z+1] );
//					pTO -> KonturPunkte( &kp );
//					pTO -> UniqueIdent() = pGO -> UniqueIdent();
//
//				bool fHasFolie = false;
//				bool fHasObjektArt = false;
//				bool fHasFileName = false;
//
//					posMM = pGO -> GetMMStartPos();
//					while ( posMM )
//					{
//						pGO -> GetMMNext( posMM, key, text );
//
//					// alle bekommen einen gleichartigen Satz von Attributen
//						if (key == "ATKIS-Folie") {
//							if (!pGO -> Folie().IsEmpty()) {
//								pTO -> AddTextMerkmal(key, pGO -> Folie());
//								fHasFolie = true;
//							}
//						} else if (key == "ATKIS-Objektart") {
//							if (!pGO -> ObjektArt().IsEmpty()) {
//								pTO -> AddTextMerkmal(key, pGO -> ObjektArt());
//								fHasObjektArt = true;
//							}
//						} else if (key == "ATKIS-Dateiname") {
//							pTO -> AddTextMerkmal(key, g_pTriasInterface -> GetActFileName());
//							fHasFileName = true;
//						} else
//							pTO -> AddTextMerkmal( key, text );
//					}
//
//					if (!fHasFolie)
//						pTO -> AddTextMerkmal("ATKIS-Folie", pGO -> Folie());
//					if (!fHasObjektArt)
//						pTO -> AddTextMerkmal("ATKIS-Objektart", pGO -> ObjektArt());
//					if (!fHasFileName)
//						pTO -> AddTextMerkmal("ATKIS-Dateiname", g_pTriasInterface -> GetActFileName());
//						
//					pTO -> Neu() = TRUE;
//					for ( l = 0; l < pPF -> GetSize(); l++ )
//					{
//						pPT = (CPunkt*)pPF -> GetAt( (int)l );
//						*((double*)pTO -> XKoord() + l) = pPT -> Rechts();
//						*((double*)pTO -> YKoord() + l) = pPT -> Hoch();
//					}
//					pTO -> WriteBack();
//					pTO -> KonturPunkte( NULL );	// weil: &kp nicht freigeben!!!
//					pGO -> ObjNr() = pTO -> ONr();
//					pGO -> DelFolge( j );			// Achtung! Hinterlässt Lücke!
//													// unbedingt mit Pack() vollenden!!!
//					delete pTO;
//				}
//			}
//		}
//		pGO -> Pack();
//	}
//	return pGO;
}	// Fertig

void CObjektPool::WriteBack(bool fStatus)
{
CTriasObjekt *pTO;
CGeoObj *pGO;
CPunktFolge *pPF;
CPunkt *pPT;
CString text, id, key;
POSITION pos, posMM;
int a, j, nr, anzahl;
long l, z, max, kp = 1L;
long *pkp = NULL;

CString strPrepared;

	VERIFY(strPrepared.LoadString(IDS_OBJECTSPREPARED));
	anzahl = m_omGeoObjekte.GetCount();
	((CEDBSExtension*)g_pTE) -> SetDefaultStatusTexte(strPrepared, NULL, NULL, "  ");

CString strPrepare;

	VERIFY(strPrepare.LoadString(IDS_PREPAREOBJECTS));
	((CEDBSExtension*)g_pTE) -> InitStatusDialog(strPrepare, (ULONG)anzahl, NULL );

	if (PrepareObjTeile()) {
	// nicht abgebrochen
	CString strSaved;

		VERIFY(strSaved.LoadString(IDS_OBJECTSSAVED));
		((CEDBSExtension*)g_pTE) -> SetDefaultStatusTexte(strSaved, NULL, NULL, "  ");

	CString strSave;

		VERIFY(strSave.LoadString(IDS_SAVEOBJECTS));
		nr = 0;
		anzahl = m_omGeoObjekte.GetCount();			// sind jetzt u.U. weniger
		((CEDBSExtension*)g_pTE) -> InitStatusDialog(strSave, (ULONG)anzahl, NULL );

		for (pos = m_omGeoObjekte.GetStartPosition(); pos != NULL; /**/)
		{
			m_omGeoObjekte.GetNextAssoc(pos, id, (CObject *&)pGO);

		//	------------------------------------------------------------------------------------
		//	Hier ansetzen um Objekte mit Löchern zu identifizieren!
		//	------------------------------------------------------------------------------------
			((CEDBSExtension *)g_pTE) -> SetupStatus((ULONG)nr++);
			if (((CEDBSExtension *)g_pTE) -> NutzerAbbruch())
				break;		// abgebrochen

		//	------------------------------------------------------------------------------------
		//	Fallunterscheidung: Linienobjekte mit mehreren, nicht verbundenen Linienabschnitten
		//						werden in mehrere Objekte gesplittet!
		//	------------------------------------------------------------------------------------
			if (( pGO -> AnzahlLinien() == 1 ) && ( pGO -> ObjTyp() != 'L' ))
				if ( pGO -> Punkte(0) -> Geschlossen())
					pGO -> ObjTyp() = 'F';

			if (( pGO -> ObjTyp() == 'F' ) && ( pGO -> AnzahlLinien() > 1 ))
			{
				// Flächen mit nicht geschlossenen Konturen aussondern!
				for ( j = 0; j < pGO -> AnzahlLinien(); j++ )
					if ( !pGO -> Punkte( j ) -> Geschlossen())
						pGO -> ObjTyp() = 'L';
			}
			if (( pGO -> ObjTyp() == 'L' ) && ( pGO -> AnzahlLinien() > 1 ))
			{
			CxString strUID;

				for (int loop = 0; loop < pGO -> AnzahlLinien(); loop++)
				{
					pTO = new CTriasObjekt();
					pkp = &kp;

					if ( pTO ) {
						pTO -> ONr() = 0L;				// neues Objekt!
						pTO -> Neu() = TRUE;

						pTO -> Ident() = g_pTriasInterface -> GetIdent (pGO -> Folie(), pGO -> ObjektArt(), pGO -> Merkmale());
						max = z = 0L;
						a = 0;
						z = pGO -> AnzahlPunkte( loop );
						pTO -> AnzahlPunkte() = z;
						pTO -> XKoord( new double[z+1]);
						pTO -> YKoord( new double[z+1]);
						pTO -> KonturPunkte( pkp );
						pkp[0] = z;
						z = 0L;

						pPF = pGO -> Punkte( loop );
						for ( l = 0; l < pPF -> GetSize(); l++ )
						{	
							pPT = (CPunkt*)pPF -> GetAt( (int)l );
							*((double*)pTO -> XKoord() + z) = pPT -> Rechts();
							*((double*)pTO -> YKoord() + z) = pPT -> Hoch();
							z++;
						}

						pTO -> ObjTyp() = OGLinie;
						pTO -> AnzahlKonturen() = 1;
						strUID.Empty();
						strUID.printf( "%s_%d", (const char*)pGO -> UniqueIdent(), loop );
						pTO -> UniqueIdent() = strUID;

						if (!pGO -> Folie().IsEmpty())
							pTO -> AddTextMerkmal ("ATKIS-Folie", pGO -> Folie());
						if (!pGO -> ObjektArt().IsEmpty())
							pTO -> AddTextMerkmal ("ATKIS-Objektart", pGO -> ObjektArt());
						pTO -> AddTextMerkmal ("ATKIS-Dateiname", g_pTriasInterface -> GetActFileName());

						posMM = pGO -> GetMMStartPos();
						while ( posMM )
						{	
							pGO -> GetMMNext( posMM, key, text );
							pTO -> AddTextMerkmal( key, text );
						}

						pTO -> WriteBack();
						pTO -> KonturPunkte( NULL );	// weil: &kp nicht freigeben!!!
						delete pTO;
					}	
				}	
			}
			else {
				pTO = new CTriasObjekt();
				if ( pGO -> AnzahlLinien() || pGO -> ObjNr())
				{	
					if ( pGO -> AnzahlLinien() > 1 )	
						pkp = new long[pGO -> AnzahlLinien()];
					else
						pkp = &kp;

					if ( pTO )
					{	
						if ( pGO -> ObjNr())
							pTO -> ONr() = pGO -> ObjNr();
						else
							pTO -> ONr() = 0L;				// neues Objekt!

						pTO -> Ident() = g_pTriasInterface -> GetIdent(pGO -> Folie(), pGO -> ObjektArt(), pGO -> Merkmale());
						max = z = 0L;
						a = 0;

					// Gesamtzahl Punkte und Hypothese für Aussenkontur ermitteln
						for ( j = 0; j < pGO -> AnzahlLinien(); j++)
						{	
							z += pGO -> AnzahlPunkte( j );
							if (pGO -> AnzahlPunkte(j) > max)
							{
								max = pGO -> AnzahlPunkte( j );
								a = j;
							}	
						}

						pTO -> AnzahlPunkte() = z;
						pTO -> XKoord(new double[z+1]);
						pTO -> YKoord(new double[z+1]);
						pTO -> KonturPunkte(pkp);
						z = 0L;

						if (pGO -> AnzahlLinien())
						{	
						// zuerst die Aussenkontur eintragen!
							pPF = pGO -> Punkte( a );
							for ( l = 0; l < pPF -> GetSize(); l++ )
							{
								pPT = (CPunkt*)pPF -> GetAt( (int)l );
								*((double*)pTO -> XKoord() + z) = pPT -> Rechts();
								*((double*)pTO -> YKoord() + z) = pPT -> Hoch();
								z++;
							}	
						}
						pkp[0] = max;

						if ( pGO -> ObjTyp() == 'F' )
						{	
							if ( pGO -> AnzahlLinien())
							{	if ( pGO -> AnzahlPunkte( 0 ) == 1 )
									pTO -> ObjTyp() = OGPunkt;
								else
									pTO -> ObjTyp() = OGFlaeche;
							}	
						}
						else if (pGO -> ObjTyp() == 'L')
							pTO -> ObjTyp() = OGLinie;
						else if (pGO -> ObjTyp() == 'P') {
						// ggf. Textobjekt draus machen
							if (!g_pTriasInterface -> MakeText(pGO -> ObjektArt())) 
								pTO -> ObjTyp() = OGPunkt;
							else 
								ConvertToText (pGO, pTO);

						} else if (pGO -> AnzahlLinien()) {	
							if (pGO -> AnzahlPunkte( 0 ) == 1) {
							// ggf. Textobjekt draus machen
								if (!g_pTriasInterface -> MakeText(pGO -> ObjektArt())) 
									pTO -> ObjTyp() = OGPunkt;
								else 
									ConvertToText (pGO, pTO);
							} else {
								if (pGO -> Punkte(0) -> Geschlossen())
									pTO -> ObjTyp() = OGFlaeche;
								else
									pTO -> ObjTyp() = OGLinie;
							}
						}

						pTO -> AnzahlKonturen() = pGO -> AnzahlLinien();
						pTO -> UniqueIdent() = pGO -> UniqueIdent();

					// Standard-Attribute erzeugen
						if (!pGO -> ObjNr())
						{	
							pTO -> Neu() = TRUE;
							if (!pGO -> Folie().IsEmpty())
								pTO -> AddTextMerkmal ("ATKIS-Folie", pGO -> Folie());
							if (!pGO -> ObjektArt().IsEmpty())
								pTO -> AddTextMerkmal ("ATKIS-Objektart", pGO -> ObjektArt());
							pTO -> AddTextMerkmal ("ATKIS-Dateiname", g_pTriasInterface -> GetActFileName());
						}

					// alle sonstigen Attribute übernehmen
						posMM = pGO -> GetMMStartPos();
						while ( posMM )
						{
							text.Empty();
							pGO -> GetMMNext( posMM, key, text );
							pTO -> AddTextMerkmal( key, text );
						}

						for ( j = 0; j < pGO -> AnzahlLinien(); j++ ) {	
							if ( j != a ) {	
								if ( j < a )
									pkp[j+1] = pGO -> AnzahlPunkte( j );
								else
									pkp[j]   = pGO -> AnzahlPunkte( j );

								pPF = pGO -> Punkte( j );
								for ( l = 0; l < pPF -> GetSize(); l++ )
								{	
									pPT = (CPunkt*)pPF -> GetAt( (int)l );
									*((double*)pTO -> XKoord() + z) = pPT -> Rechts();
									*((double*)pTO -> YKoord() + z) = pPT -> Hoch();
									z++;
								}	
							}	
						}
					}	
				}
				else if (pGO -> IsFloeDelta()) { 
				HOBJECT lONr = g_pTriasInterface -> FindObject(pGO -> UniqueIdent());

					if (INVALID_HOBJECT != lONr) {
					// ggf. reine Attributkorrektur (#HK011114)
					// war in einem FLOE-Satz (DLTA1001) und muß Bezug haben
						pTO -> UniqueIdent() = pGO -> UniqueIdent();

					// Standard-Attribute erzeugen
//						pTO -> ONr() = pGO -> ObjNr();
						if (!pGO -> Folie().IsEmpty())
							pTO -> AddTextMerkmal ("ATKIS-Folie", pGO -> Folie());
						if (!pGO -> ObjektArt().IsEmpty())
							pTO -> AddTextMerkmal ("ATKIS-Objektart", pGO -> ObjektArt());
						pTO -> AddTextMerkmal ("ATKIS-Dateiname", g_pTriasInterface -> GetActFileName());

					// alle sonstigen Attribute übernehmen
						posMM = pGO -> GetMMStartPos();
						while (posMM)
						{
							text.Empty();
							pGO -> GetMMNext( posMM, key, text );
							pTO -> AddTextMerkmal( key, text );
						}

						pTO -> ONr() = lONr;
						pTO -> Neu() = FALSE;
					}
				}

				if ((pTO -> ObjTyp() == OGLinie) && (pTO -> AnzahlKonturen() > 1))
				{
				CString	text = "Nicht verbundene Linienabschnitte! UID: ";

					text += pTO -> UniqueIdent();
					AfxMessageBox(text);
				}

				pTO -> WriteBack();
				pTO -> KonturPunkte( NULL );	// weil: &kp nicht freigeben!!!
				if ( pGO -> AnzahlLinien() > 1 )
					delete pkp;
				delete pTO;
			}
		}
	}

	for (pos = m_omGeoObjekte.GetStartPosition(); pos != NULL; )
	{	
		m_omGeoObjekte.GetNextAssoc( pos, id, (CObject*&)pGO );
		delete pGO;
	}
	m_omGeoObjekte.RemoveAll();
}	// WriteBack

///////////////////////////////////////////////////////////////////////////////
// ein Objekt hinzufügen, welches als reines AttributDelta vorkommen wird
BOOL CObjektPool::AddFloeDelta (const char *pObjNr, const char *pObjTeilNr)
{
// neues GeoObj erzeugen
CString strUId = pObjNr;

	if (NULL != pObjTeilNr && '\0' != pObjTeilNr[0]) {
		strUId += '-';
		strUId += pObjTeilNr;
	}

CGeoObj	*pGO = NULL;

	m_omGeoObjekte.Lookup (strUId, (CObject *&)pGO);
	if (!pGO)
		m_omGeoObjekte.SetAt(strUId, pGO = new CGeoObj (strUId, TRUE));
	if (NULL == pGO)
		return FALSE;

	return TRUE;
}

BOOL CObjektPool::ConvertToText (CGeoObj *pGO, CTriasObjekt *pTO)
{
// Textmerkmal finden
CString strText (g_pTriasInterface -> GetTextAttr(pGO -> ObjektArt()));
BOOL fResult = FALSE;

	if (strText.IsEmpty())
		strText = "No text for EDBSID: " + pGO -> ObjektArt();
	else {
	CString strWert;

		if (pGO -> TextMerkmal(strText, strWert)) {
			pGO -> RemoveMerkmal(strText);
			strText = strWert;
			fResult = TRUE;
		} else
			strText = "No text for EDBSID: " + pGO -> ObjektArt();
	}
	pTO -> TextObjekt() = strText;
	pTO -> ObjTyp() = OGText;
	return fResult;
}

BOOL CObjektPool::PrepareObjTeile()
{
	CGeoObj		*pGO;
	CString		key;
	POSITION	pos;
	void*		ptr;
	long		nr = 0;

	m_omObsoleteGO.RemoveAll();

	for ( pos = m_omGeoObjekte.GetStartPosition(); pos != NULL; )
	{
		m_omGeoObjekte.GetNextAssoc( pos, key, (CObject*&)pGO );

		((CEDBSExtension *)g_pTE) -> SetupStatus( (ULONG)nr++ );
		if (((CEDBSExtension *)g_pTE) -> NutzerAbbruch(IDS_CANCELIMPORT)) {
			m_omObsoleteGO.RemoveAll();
			return FALSE;	// abgebrochen
		}
		if ( key.Find( "-" ) <= 0 )
			if ( m_mapMultiObj.Lookup( key, ptr ))
				SetupObjTeile( key, pGO );
	}

	for ( pos = m_omObsoleteGO.GetStartPosition(); pos != NULL; )
	{
		m_omObsoleteGO.GetNextAssoc( pos, key, (CObject*&)pGO );
		m_omGeoObjekte.RemoveKey( key );
	}
	m_omObsoleteGO.RemoveAll();
	return TRUE;
}

void CObjektPool::SetupObjTeile( const char* objID, CGeoObj *pGO )
{
	CGeoObj		*pGTO;
	CString		key, strObjID( objID );
	CString		k, t;
	POSITION	pos, posMM;
	int			n;

	for ( pos = m_omGeoObjekte.GetStartPosition(); pos != NULL; )
	{
		m_omGeoObjekte.GetNextAssoc( pos, key, (CObject*&)pGTO );

		if (( n = key.Find( "-" )) > 0 )
			if ( key.Left( n ) == strObjID )
		{
			posMM = pGO -> GetMMStartPos();
			while ( posMM )
			{
				pGO -> GetMMNext( posMM, k, t );
				pGTO -> AddTextMerkmal( k, t );
			}

			m_omObsoleteGO.SetAt( objID, pGO );
		}
	}
}
