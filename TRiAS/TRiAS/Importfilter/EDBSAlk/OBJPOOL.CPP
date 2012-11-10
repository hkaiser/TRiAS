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


//#include "statimpl.hxx"
#include "istatus.h"
#include "edbs.hpp"
#include "cxstring.h"
#include "GeoCvt.h"
/*
extern "C" {
#include <xtension.h>
#include <Ixtensn.hxx>
#include <Ixtnext.hxx>
}
*/

extern CTriasInterface	*g_pTriasInterface;
//#fje980727//=====================================================================
//#include "W:\Projekte\GeoCvt\GeometryConversionService.h"
//extern IArcConversion *g_pIArcConversion;

CObjektPool :: CObjektPool()
{
	m_pgoReady = NULL;
	m_strLastGetGeoObj.Empty();
	m_pLastGetGeoObj = NULL;
}

CObjektPool :: ~CObjektPool()
{
	POSITION	pos;
	CString		key;
	CGeoObj		*pGO;

	for ( pos = m_omGeoObjekte.GetStartPosition(); pos != NULL; )
	{	m_omGeoObjekte.GetNextAssoc( pos, key, (CObject*&)pGO );
		delete pGO;
	}
	m_omGeoObjekte.RemoveAll();
}

CGeoObj *CObjektPool :: GetGeoObj(const char* pID)
{
	if( m_strLastGetGeoObj != pID ) {
		if(!m_omGeoObjekte.Lookup( pID, (CObject*&)m_pLastGetGeoObj ) )
			m_omGeoObjekte.SetAt( pID, m_pLastGetGeoObj = new CGeoObj( pID ));
		m_strLastGetGeoObj = pID;
	}
	return m_pLastGetGeoObj;
}

void CObjektPool :: Clear()
{
	POSITION	pos;
	CString		key;
	CGeoObj		*pGO;

	for ( pos = m_omGeoObjekte.GetStartPosition(); pos != NULL; ) {
		m_omGeoObjekte.GetNextAssoc( pos, key, (CObject*&)pGO );
		if ( pGO -> ObjNr())
			g_pTriasInterface -> DeleteObjekt( pGO -> ObjNr());
	}
	m_strLastGetGeoObj.Empty();
	m_pLastGetGeoObj = NULL;
}	// Clear


/*	AddLine  **************************************************************/
/*				Fügt eine gelesene Punktfolge an ein existierendes GeoOb- */
/*	jekt an bzw. erzeugt ein neues GeoObjekt, wenn zur übergebenen ID     */
/*	kein GeoObjekt gefunden wird.                                         */
/*	Außerdem werden Folie und ObjektArt gesetzt.                          */
/**************************************************************************/
void CObjektPool :: AddLine( const char* pID, CPunktFolge* pP, CGeoObj *pGO, 
							const char* teil, const char* folie, const char* art )
{
	CCfg	*pConfiguration= &((CEDBSExtension*)g_pTE)->Configuration;
	CRule_Layer	*pRule_Layer;
	CRule_Line	*pRule_Line;
	CString		strRule;
	CString		strKey;
	CGeoObj		*pGOnew = pGO;
	CGeoObj		*pGO_Line;
	CxString strRegeln("ALK-Regeln");

try {
	strRule = folie;
	pRule_Layer = g_pMetaData->GetRule_Layer( strRule );
	if( pRule_Layer ) {
		if( pRule_Layer->ImportMode()  != 0 ) {
			strRule += art;
			pRule_Line = g_pMetaData->GetRule_Line( strRule );
			if( pRule_Line ) {
				if( pRule_Line->Importmodus_Hauptgeometrie() != 0 ) {
					if( !pGOnew ) {
						strKey = pID;
						strKey = strKey.Left(7) + "H";
						pGOnew = g_pObjektPool->GetGeoObj( strKey );
						if( pConfiguration->m_tCreateAttributeRegeln )
							pGOnew->AddAttribute( strRegeln, strRule );
					}
					m_pgoReady = pGOnew -> AddFolge( pP /*, folie, art*/ );
				}
				if( pGOnew ) {
					if( !pGOnew->tBI && pRule_Line->FunktionDerLinieBestimmtObjektklasse_Hauptgeometrie() ) {
//						pGOnew->Folie() = folie;
//						pGOnew->Objektart() = art;
			//			pGOnew->Aktualitaet() = m_Aktuali;
						g_pMetaData->ObjectClassesTRiAS().Lookup( pRule_Line->Objektklasse_Zusatzgeometrie(), (CObject*&)pGOnew->ObjectClassTRiAS() );
					}
				}
				if( pRule_Line->Importmodus_Zusatzgeometrie() != 0 ) {
					strKey = pID;
					strKey = strKey.Left(7) + "Z";
					strKey += "_";
					strKey += art;
					
					pGO_Line = g_pObjektPool->GetGeoObj( strKey );
					if( pConfiguration->m_tCreateAttributeRegeln )
						pGO_Line->AddAttribute( strRegeln, strRule );
					pGO_Line->Folie() = folie;
					pGO_Line->Objektart() = art;
					g_pMetaData->ObjectClassesTRiAS().Lookup( pRule_Line->Objektklasse_Zusatzgeometrie(), (CObject*&)pGO_Line->ObjectClassTRiAS() );
					m_pgoReady = pGO_Line->AddFolge( pP );
				}
			}
			else {
				if( !pGOnew ) {
					strKey = pID;
					strKey = strKey.Left(7) + "H";
					pGOnew = g_pObjektPool->GetGeoObj( strKey );
					if( pConfiguration->m_tCreateAttributeRegeln )
						pGO->AddAttribute( strRegeln, strRule );
				}
				m_pgoReady = pGOnew -> AddFolge( pP /*, folie, art*/ );
			}
		}
	}
	else {
		// wenn es keine Regel für die Folie gibt, wird die Linie nicht verarbeitet
		// für den automatischen Import werden auch die Regeln automatisch erzeugt
	}
}
catch( ... ) {
	AfxMessageBox( "Unerwarteter Fehler in AddLine",0,0);
}
}	// AddLine

void CObjektPool :: AddLineBI( const char* pID, CPunktFolge* pP, CGeoObj *pGO, 
							const char* teil, const char* folie, const char* art )
{
	CGeoObj		*pGOnew = pGO;
	CString strKey;

	if( !pGOnew ) {
		strKey = pID;
		strKey = strKey.Left(7) + "H";
		pGOnew = g_pObjektPool->GetGeoObj( strKey );
	}
	m_pgoReady = pGOnew -> AddFolge( pP /*, folie, art*/ );

}	// AddLine
/*
void CObjektPool::AddGeometry( const char* pID, CGeometry* pG,
							const char* teil, const char* folie, const char* art )
{
	CGeoObj		*pGO = NULL;

	pGO = g_pObjektPool->GetGeoObj( pID );
//	pGO->Folie() = folie;
//	pGO->Objektart() = art;
//	pGO->Aktualitaet() = m_Aktuali;
/ *
	m_omGeoObjekte.Lookup( pID, (CObject*&)pGO );
	if ( !pGO )
		m_omGeoObjekte.SetAt( pID, pGO = new CGeoObj( pID, folie, art ));
* /
	pGO->Geometries().Add( pG );
}	// AddGeometry
*/
static BOOL HideRedefError = FALSE;
/*	DefType  **************************************************************/
/*				Setzt ObjektTyp, ObjektArt und Folie für das übergebene   */
/*	Objekt (ID), wird kein Objekt mit dieser ID gefunden, so wird ein     */
/*	GeoObjekt mit der übergebenen ID erzeugt.                             */
/**************************************************************************/
void CObjektPool :: DefType( const char *pID, const char *typ,
								const char *art, const char *folie )
{
	CGeoObj		*pGO = NULL;
	CString		text;

	pGO = g_pObjektPool->GetGeoObj( pID );
//	pGO->Folie() = folie;
//	pGO->Objektart() = art;
//	pGO->Aktualitaet() = m_Aktuali;
/*
	m_omGeoObjekte.Lookup( pID, (CObject*&)pGO );
	if ( !pGO ) {
		pGO = new CGeoObj( pID, folie, art );
		m_omGeoObjekte.SetAt( pID, pGO );
	}
*/
	if (( pGO -> ObjTyp() != 'U' ) &&
		( pGO -> ObjTyp() != *typ )) {
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
	else if ( pGO -> Folie().Find( folie ) < 0 )	{
		pGO -> Folie() += ", ";
		pGO -> Folie() += folie;
	}

	if ( pGO -> Objektart().IsEmpty())
		pGO -> Objektart() = art;
	else if ( pGO -> Objektart().Find( art ) < 0 ) {
		text = art;
		text += ", ";
		text += pGO -> Objektart();
		pGO -> Objektart() = text;
	}
}	// DefType

/*	BesondInfo  ***********************************************************/
/*					Fügt Informationen aus dem Bereich BesondInfo des     */
/*	EDBS-Satzes an das GeoObjekt an. Wird kein Objekt mit der entsprechen-*/
/*	den ID gefunden, so wird ein neues Objekt erzeugt.                    */
/**************************************************************************/
void CObjektPool :: BesondInfo( const short j, const short k, CAtkisSatz* pSatz )
{
	CCfg	*pConfiguration= &((CEDBSExtension*)g_pTE)->Configuration;
	CRule_Layer *pRule_Layer;
	CGeoObj		*pGOBI = NULL;
	CPunktFolge* pBIpoints1 = NULL;
	CPunktFolge* pBIpoints2 = NULL;
	CxString	strTemp;
	CxString	strText, txt;

	CRule_Info	*pRule_Info = NULL;

	CxString strRegeln("ALK-Regeln");
	CxString strRule;

	CxString strObjNum;
	CxString strAktualitaet;
	CxString strObjNumBI;
	CxString strInfoArt;
	CxString strArtBI;
	CxString strFolie, strObjArt, strObjArtBI;
	int iArtGeo;
	bool tText_erzeugt;
	
	try {

		strObjNum = pSatz->OF_Objektnummer( j );
		strAktualitaet = pSatz->OF_Aktuali( j );
	//	strObjNum.TrimAll();
		strFolie = pSatz -> OF_Folie(j);
		strFolie.TrimAll();
		
		pRule_Layer = g_pMetaData->GetRule_Layer( strFolie );
		if( NULL == pRule_Layer )
			return;

		if( 0 == pRule_Layer->ImportMode() ) 
			return;

		strObjArt = pSatz -> OF_Objektart( j );
		strObjArt.TrimAll();
		strObjArtBI = pSatz -> OF_BI_Objektart( j, k );
		strObjArtBI.TrimAll();
		strArtBI = pSatz -> OF_BI_Art( j, k );	
		strArtBI.TrimAll();
		strInfoArt = strArtBI;
		strInfoArt += "/";									//#FJE980805
		strInfoArt += strObjArtBI;
		
	/*
		if ( strArtBI == "44" ) {	// UNIX-Umlaute ausbauen
			strInfoArt = strText.Left( 2 );
			strText = strText.Mid( 2 );
			strText.Transform(2);
		}
	*/
	//	pGO = g_pObjektPool->GetGeoObj( strObjNum + "H" );
	//	pGO->Folie() = strFolie;
	//	pGO->Objektart() = strObjArt;
	//	pGO->Aktualitaet() = m_Aktuali;


//=== Regeln für besondere Informationen suchen ========================================

		strRule = strFolie + strObjArt + strObjArtBI + strArtBI;
		pRule_Info = g_pMetaData->GetRule_Info( strRule );
		if( NULL == pRule_Info )
			return;

		strText = pSatz -> OF_BI_Text( j, k );
		strText.TrimAll();
		if( pConfiguration->m_sCodePage )
			strText.Transform(pConfiguration->m_sCodePage);

		if( pRule_Info->ObjektartBI_bestimmt_Objektklasse_Hauptgeometrie() ) {
			CGeoObj	*pGO;

			pGO = g_pObjektPool->GetGeoObj( strObjNum + "H" );
			if( pConfiguration->m_tCreateAttributeRegeln )
				pGO->AddAttribute( strRegeln, strRule );
			pGO->Folie() = strFolie;
			pGO->Objektart() = strObjArtBI;
			g_pMetaData->ObjectClassesTRiAS().Lookup( pRule_Info->ObjectClassTRiAS_Hauptgeometrie(), (CObject*&)pGO->ObjectClassTRiAS() );
		}

	//=== Regeln für Texte ============================================================
		tText_erzeugt = false;
		if( pConfiguration->m_tCreateBItext) {
			if( 0 != pRule_Info->Importmodus_Attr() ) {
				CxString strTextToCreate;

				strTemp = pRule_Info->Konvertierung_Text().Left(1);
				if( strTemp == "\"" ) {
					strTextToCreate = pRule_Info->Konvertierung_Text().Mid( 1, pRule_Info->Konvertierung_Text().GetLength() - 2 );
				}
				else if( !strText.IsEmpty() ) { 
					if( strTemp == "§" ) {
	//--- Konvertierung für Hausnummern ------------------------------------------------
						if( "§Hausnummer" == pRule_Info->Konvertierung_Text() ) {
							if( strText.Left(2) == "HA" ) {
								CxString strHANR, strHANRZ, strArt, strObjArt;
								int ix1, ix2;
								strHANR = strText;
								strHANR = strHANR.Mid(23,3);
								if( strHANR == "P01" || strHANR == " 01" || strHANR == "001") {
									strHANR = strText;
									strHANR = strHANR.Mid(15,8);
									strHANRZ = strHANR;
									while( isdigit((int)*strHANRZ.Left(1)) )
										strHANRZ = strHANRZ.Mid(1);
									strHANRZ.TrimAll();
									strHANR.Format("%ld", strHANR.Long());
									if( !strHANRZ.IsEmpty() )
										strHANR += strHANRZ;
									for( ix1 = 0,ix2 = pSatz -> OF_AnzahlBesInfo( j );
										ix1 < ix2;
										ix1++ ) {
										strArt = pSatz -> OF_BI_Art( j, ix1 );
										strObjArt = pSatz -> OF_BI_Objektart( j, ix1 );
										if(  strArt == "21" ) {
											if( strObjArt == "  1031" ) {
												strHANR.Empty();
												break;
											}
										}
										else
											continue;
									}	
									strTextToCreate = strHANR;
								}
							}
							else
								strTextToCreate = strText;
						}
	//--- Konvertierung für Flurstückskennzeichen -------------------------------------
						else if( "§Flurstückskennzeichen" == pRule_Info->Konvertierung_Text() ) {
							if( strText.Left(2) == "FS" ) {
								long z, n;
								z = ((CxString)strText.Mid(11,5)).Long();
								n = ((CxString)strText.Mid(16,3)).Long();
								if( 0 == n )							
									strTextToCreate.printf( "%lu", z );
								else							
									strTextToCreate.printf( "%lu/%lu", z, n );
							}
							else
								strTextToCreate = strText;
						}
	//--- Konvertierung für Flurkennzeichen -------------------------------------
						else if( "§Flurkennzeichen" == pRule_Info->Konvertierung_Text() ) {
							if( strText.Left(2) == "FL" ) {
								long f;
								f = ((CxString)strText.Mid(8,3)).Long();
								strTextToCreate.printf( "Fl. %lu", f );
							}
							else
								strTextToCreate = strText;
						}
					}
					else {
						strTextToCreate = strText;
					}
				}

				if( strTextToCreate.IsEmpty() )
					tText_erzeugt = false;
				else {
					tText_erzeugt = true;
					strObjNumBI = strObjNum + "T";
					strObjNumBI += "_";
					txt.Format("%03d", j);
					strObjNumBI += txt;
					strObjNumBI += "_";
					txt.Format("%03d", k);
					strObjNumBI += txt;
	/*
					strObjNumBI = strObjNum;
					strObjNumBI += "_";
			//		txt.Format("%06ld", pSatz->m_lEDBSSatzNummer);
					txt.Format("%08ld", pSatz->m_lNumParserCalls);
					strObjNumBI += txt;
					strObjNumBI += "_";
					txt.Format("%03d", k);
					strObjNumBI += txt;
					strObjNumBI += "_";
					strObjNumBI += key;
					strObjNumBI += "T";
					strObjNumBI += pSatz->OF_BI_ArtGeo(j,k);
					strObjNumBI += "T";
	*/

					pBIpoints1 = pSatz -> OF_BI_Points( j, k );
					if( pBIpoints1 ) {
						pGOBI = g_pObjektPool->GetGeoObj( strObjNumBI );
						if( pConfiguration->m_tCreateAttributeRegeln )
							pGOBI->AddAttribute( strRegeln, strRule );
						pGOBI->tBI = true;
						pGOBI->Folie() = strFolie;
						pGOBI->Objektart() = strObjArtBI;
			//			pGOBI->Aktualitaet() = m_Aktuali;
						g_pMetaData->ObjectClassesTRiAS().Lookup( pRule_Info->Objektklasse_Text(), (CObject*&)pGOBI->ObjectClassTRiAS() );
						if( pBIpoints1->GetSize() > 1 ) {
							pBIpoints2 = new CPunktFolge( 1 );
							if(	pBIpoints1->GetPoint(1).Hoch() == pSatz -> GrundPunktHoch()
								&& pBIpoints1->GetPoint(1).Rechts() == pSatz -> GrundPunktRechts() ) {
								(*pBIpoints2)[0] = new CPunkt( pBIpoints1->GetPoint(0).Hoch(), pBIpoints1->GetPoint(1).Rechts(), pBIpoints1->GetPoint(1).Dreh() );
							}
							else {
								(*pBIpoints2)[0] = new CPunkt( pBIpoints1->GetPoint(0).Hoch(), pBIpoints1->GetPoint(0).Rechts(), pBIpoints1->GetPoint(0).Dreh() );
							}
							AddLineBI( strObjNumBI, pBIpoints2, pGOBI,
								"BI", strFolie, strObjArtBI );
							delete pBIpoints2;
							pBIpoints2 = NULL;
						}
						else
							AddLineBI( strObjNumBI, pBIpoints1, pGOBI,
								"BI", strFolie, strObjArtBI );

						pGOBI->ObjTyp() = 'T';
						pGOBI->ObjLabel() = strTextToCreate;
					}
				}
			}
		}

	//=== Regeln für Attribute ========================================================
		if( pConfiguration->m_tCreateBIattr && !strText.IsEmpty() ) {
			CMapStringToString	mapAttrToCreate;
			CxString	strAttrToCreate;

			if( 0 != pRule_Info->Importmodus_Attr() ) {
				strTemp = pRule_Info->Konvertierung_Attr().Left(1);
				if( strTemp == "\"" ) {
					strAttrToCreate = pRule_Info->Konvertierung_Attr().Mid( 1, pRule_Info->Konvertierung_Attr().GetLength() - 2 );
					mapAttrToCreate.SetAt( pRule_Info->AttributeName(), strAttrToCreate );
				}
				else if( strTemp == "§" ) {
	//--- Konvertierungen -------------------------------------------------------------
					if( "{" == pRule_Info->Konvertierung_Attr().Mid(1,1) ) { // Attributmenge
						CxString strAttrNames(pRule_Info->AttributeName() + ";");
						if( "§{Gebaeudekennzeichen}" == pRule_Info->Konvertierung_Attr() ) {
							if( strText.Left(2) == "HA" ) {
								if( 0 <= strAttrNames.Find("Laenderschluessel;") )
									mapAttrToCreate.SetAt( "Laenderschluessel", strText.Mid( 2, 2 ) );
								if( 0 <= strAttrNames.Find("Regierungsbeziksschluessel;") )
									mapAttrToCreate.SetAt( "Regierungsbeziksschluessel", strText.Mid( 4, 1 ) );
								if( 0 <= strAttrNames.Find("Kreisschluessel;") )
									mapAttrToCreate.SetAt( "Kreisschluessel", strText.Mid( 5, 2 ) );
								if( 0 <= strAttrNames.Find("Gemeindeschluessel;") )
									mapAttrToCreate.SetAt( "Gemeindeschluessel", strText.Mid( 7, 3 ) );
								if( 0 <= strAttrNames.Find("Strassenschluessel;") )
									mapAttrToCreate.SetAt( "Strassenschluessel", strText.Mid( 10, 5 ) );
								if( 0 <= strAttrNames.Find("Hausnummer;") )
									mapAttrToCreate.SetAt( "Hausnummer", strText.Mid( 15, 4 ) );
								if( 0 <= strAttrNames.Find("Hausnummernzusatz;") )
									mapAttrToCreate.SetAt( "Hausnummernzusatz", strText.Mid( 19, 4 ) );
								if( 0 <= strAttrNames.Find("Gebaeudenummer;") )
									mapAttrToCreate.SetAt( "Gebaeudenummer", strText.Mid( 23, 3 ) );
							}
						}	
						if( "§{Flurstueckskennzeichen}" == pRule_Info->Konvertierung_Attr() ) {
							if( strText.Left(2) == "FS" ) {
								if( 0 <= strAttrNames.Find("Bundeslandschluessel;") )
									mapAttrToCreate.SetAt( "Bundeslandschluessel", strText.Mid( 2, 2 ) );
								if( 0 <= strAttrNames.Find("Gemarkungsschluessel;") )
									mapAttrToCreate.SetAt( "Gemarkungsschluessel", strText.Mid( 4, 4 ) );
								if( 0 <= strAttrNames.Find("Flur;") )
									mapAttrToCreate.SetAt( "Flur", strText.Mid( 8, 3 ) );
								if( 0 <= strAttrNames.Find("Flurstueckszaehler;") )
									mapAttrToCreate.SetAt( "Flurstueckszaehler", strText.Mid( 11, 5 ) );
								if( 0 <= strAttrNames.Find("Flurstuecksnenner;") )
									mapAttrToCreate.SetAt( "Flurstuecksnenner", strText.Mid( 16, 3 ) );
								if( 0 <= strAttrNames.Find("Flurstuecksfolgenummer;") )
									mapAttrToCreate.SetAt( "Flurstuecksfolgenummer", strText.Mid( 19, 2 ) );
							}
						}	
					}
					else {										// Einzelattribut
						if( "§WLDGE-Flurstueckskennzeichen" == pRule_Info->Konvertierung_Attr() ) {
							strAttrToCreate = strText.Mid( 2, 6 )
								+ "-" + strText.Mid( 8, 3 ) + "-"
								+ strText.Mid( 11, 5 ) + "/" + strText.Mid( 16, 3 )
								+ "." + strText.Mid( 19, 2 );
							mapAttrToCreate.SetAt( pRule_Info->AttributeName(), strAttrToCreate );
						}	
					}
				}
				else
					mapAttrToCreate.SetAt( pRule_Info->AttributeName(), strText );

				if( !mapAttrToCreate.IsEmpty() ) {
					CGeoObj	*pGO;

					pGO = g_pObjektPool->GetGeoObj( strObjNum + "H" );
					if( pConfiguration->m_tCreateAttributeRegeln )
						pGO->AddAttribute( strRegeln, strRule );
					if( 0 == pGO->AnzahlLinien() && !tText_erzeugt ) {
						double dblH;
						double dblR; 

						if( pGO->Folie().IsEmpty() )
							pGO->Folie() = strFolie;
						if( pGO->Objektart().IsEmpty() )
							pGO->Objektart() = strObjArt;
	//					pGO->Aktualitaet() = m_Aktuali;
						dblH = pSatz -> GrundPunktHoch();
						dblR = pSatz -> GrundPunktRechts();
						if (( dblH != 0.0 ) && ( dblR != 0.0 ))
							pGO -> SetzPunkt( dblH, dblR );
					}

					POSITION pos;
					CString strAttrName;
					CString strAttrValue;
					for ( pos = mapAttrToCreate.GetStartPosition();
						pos != NULL; ) {
						mapAttrToCreate.GetNextAssoc( pos, strAttrName, strAttrValue  );
						pGO -> AddAttribute( strAttrName, strAttrValue );
						g_pTriasInterface -> NeuesMerkmal( strAttrName );
					}
					mapAttrToCreate.RemoveAll();
				}
			}
		}

	//=== Regeln für Geometrien =======================================================
		if( pConfiguration->m_tCreateBIgeom && strText.IsEmpty() && !tText_erzeugt ) {
			if( 0 != pRule_Info->Importmodus_Detailgeometrie() ) {
				strObjNumBI = strObjNum + "D";
				strObjNumBI += "_";
				txt.Format("%03d", j);
				strObjNumBI += txt;
				txt.Format("%03d", k);
				strObjNumBI += txt;
				strObjNumBI += strObjArtBI;
				txt.Format("%08ld", pSatz->m_lNumParserCalls);
				strObjNumBI += txt;
	/*
					strObjNumBI = strObjNum;
					strObjNumBI += "_";
			//		txt.Format("%06ld", pSatz->m_lEDBSSatzNummer);
					txt.Format("%08ld", pSatz->m_lNumParserCalls);
					strObjNumBI += txt;
					strObjNumBI += "_";
					txt.Format("%03d", k);
					strObjNumBI += txt;
					strObjNumBI += "_";
					strObjNumBI += strObjArt + strInfoArt;
					strObjNumBI += "T";
					strObjNumBI += pSatz->OF_BI_ArtGeo(j,k);
	*/
				pBIpoints1 = pSatz -> OF_BI_Points( j, k );
				if( pBIpoints1 ) {
					int iAnzahlPunkte = 0;

					iArtGeo = atoi(pSatz->OF_BI_ArtGeo(j,k));
					switch( iArtGeo ) {
					case _EinzelpunktInBesondererAusrichtung:
			#pragma message( "Einzelpunkte verarbeiten" )
						pBIpoints2 = new CPunktFolge( *pBIpoints1, false );
						break;
					case _Gerade:
						pBIpoints2 = new CPunktFolge( *pBIpoints1, false );
						break;
					case _Polygonzug:
						pBIpoints2 = new CPunktFolge( *pBIpoints1, false );
						break;
					case _Kreisbogen_rechts:
						{
							if( pBIpoints1->GetSize() == 3 ) {
								SAFEARRAY *psa = NULL;
								ConvertArc1(
										(pBIpoints1->GetPoint(1)).Hoch(), (pBIpoints1->GetPoint(1)).Rechts(),
										(pBIpoints1->GetPoint(2)).Hoch(), (pBIpoints1->GetPoint(2)).Rechts(),
										(pBIpoints1->GetPoint(0)).Hoch(), (pBIpoints1->GetPoint(0)).Rechts(),
										&psa );
								if( psa ) {
									iAnzahlPunkte = psa->rgsabound[0].cElements / 2;
									if( iAnzahlPunkte > 0 ) {
										pBIpoints2 = new CPunktFolge( iAnzahlPunkte );
										do {
											--iAnzahlPunkte;
											(*pBIpoints2)[iAnzahlPunkte] = new CPunkt( *(((double*)psa->pvData) + iAnzahlPunkte*2), *(((double*)psa->pvData) + iAnzahlPunkte*2 + 1) );
										} while( iAnzahlPunkte > 0);
									}
									SafeArrayDestroy( psa );
									psa = NULL;
								}
							}
							else {	//Korrektur für Kreise aus zwei Punkten
								pBIpoints2 = new CPunktFolge( *pBIpoints1, false );
							}
						}
						break;
					case _Kreisbogen_links:
						{
							if( pBIpoints1->GetSize() == 3 ) {
								SAFEARRAY *psa = NULL;
								ConvertArc1(
										(pBIpoints1->GetPoint(0)).Hoch(), (pBIpoints1->GetPoint(0)).Rechts(),
										(pBIpoints1->GetPoint(2)).Hoch(), (pBIpoints1->GetPoint(2)).Rechts(),
										(pBIpoints1->GetPoint(1)).Hoch(), (pBIpoints1->GetPoint(1)).Rechts(),
										&psa );
								if( psa ) {
									iAnzahlPunkte = psa->rgsabound[0].cElements / 2;
									if( iAnzahlPunkte > 0 ) {
										pBIpoints2 = new CPunktFolge( iAnzahlPunkte );
										do {
											--iAnzahlPunkte;
											(*pBIpoints2)[iAnzahlPunkte] = new CPunkt( *(((double*)psa->pvData) + iAnzahlPunkte*2), *(((double*)psa->pvData) + iAnzahlPunkte*2 + 1) );
										} while( iAnzahlPunkte > 0);
									}
									SafeArrayDestroy( psa );
									psa = NULL;
								}
							}
							else {	//Korrektur für Kreise aus zwei Punkten
								pBIpoints2 = new CPunktFolge( *pBIpoints1, false );
							}
						}
						break;
			/*
					case _Kurve:
						iAnzahlPunkte = 0;

						pPF = new CPunktFolge( iAnzahlPunkte + 2 );
						(*pPF)[0] = new CPunkt( pSatz -> GrundPunktHoch(), pSatz -> GrundPunktRechts());
						(*pPF)[iAnzahlPunkte + 1] = new CPunkt( pSatz -> EndPunktHoch( i ), pSatz -> EndPunktRechts( i ));
						break;
			*/		default:
			//			_ASSERT(0);
						break;
					}
				}
				if( pBIpoints2 ) {
					pGOBI = g_pObjektPool->GetGeoObj( strObjNumBI );
					if( pConfiguration->m_tCreateAttributeRegeln )
						pGOBI->AddAttribute( strRegeln, strRule );
					pGOBI->tBI = true;
					pGOBI->Folie() = strFolie;
					if( pRule_Info->Objektart_bestimmt_Objektklasse_Detailgeometrie() ) {
						pGOBI->Objektart() = strObjArt;
						g_pMetaData->ObjectClassesTRiAS().Lookup( g_pMetaData->m_strObjectClassesTRiAS + strFolie + strObjArt, (CObject*&)pGOBI->ObjectClassTRiAS() );
					}
					else {
						pGOBI->Objektart() = strObjArtBI;
						g_pMetaData->ObjectClassesTRiAS().Lookup( pRule_Info->Objektklasse_Detailgeometrie(), (CObject*&)pGOBI->ObjectClassTRiAS() );
					}
					AddLineBI( strObjNumBI, pBIpoints2, pGOBI,
						"BI", strFolie, strObjArtBI );
					delete pBIpoints2;
					pBIpoints2 = NULL;
				}
			}
		}


	/*		
		if( pConfiguration->m_tDefaultObjectMapping ) {
	//==========================================================================
	/ *		lH = pSatz -> GrundPunktHoch();
			lR = pSatz -> GrundPunktRechts();
			if (( lH != 0.0 ) && ( lR != 0.0 ))
				pGO -> SetzPunkt( lH, lR );

			if ( pGO -> Objektart().IsEmpty())
				pGO -> Objektart() = strObjArt;
			else if ( pGO -> Objektart().Find( strObjArt ) < 0 )	{
				txt = strObjArt;
				txt += ", ";
				txt += pGO -> Objektart();
				pGO -> Objektart() = txt;
			}
	* /
	//=== Standard D-Regeln =============================================================================
		}
		else {
			if ( !strText.IsEmpty() && ( strText != "NNNN" )) {
		//=== C-Regeln =============================================================================
		/ *
				key = strObjArt;
				key += strInfoArt;
				key += ":";
				key += strText;
				if ( g_pTriasInterface -> Get_C_Rule( key, newkey )) {
					if ( !newkey.IsEmpty())	{
						strNewKey = newkey;
						strNewKey.Teilen( newkey, strText, '#' );

						pGO -> AddAttribute( newkey, strText );
						g_pTriasInterface -> NeuesMerkmal( newkey );
					}
				}
		* /
			}
			lH = pSatz -> GrundPunktHoch();
			lR = pSatz -> GrundPunktRechts();
			if (( lH != 0.0 ) && ( lR != 0.0 ))
				pGO -> SetzPunkt( lH, lR );

			if ( pGO -> Objektart().IsEmpty())
				pGO -> Objektart() = strObjArt;
			else if ( pGO -> Objektart().Find( strObjArt ) < 0 )	{
				txt = strObjArt;
				txt += ", ";
				txt += pGO -> Objektart();
				pGO -> Objektart() = txt;
			}

		//=== D-Regeln =============================================================================
		}
	*/
	} 
	catch( ... ) {
		AfxMessageBox( "Unerwarteter Fehler in BesondInfo",0,0);
	}
}	// BesondInfo


/*	AddMerkmal  ***********************************************************/
/*				Fügt ein Merkmal an das GeoObjekt an. Wird kein Objekt    */
/*	mit der entsprechenden ID gefunden, erfolgt die Rückgabe von FALSE.   */
/**************************************************************************/
BOOL CObjektPool :: AddMerkmal( CString &pID, CString &k, CString &t )
{	CGeoObj		*pGO = NULL;
	BOOL		res = FALSE;

	pGO = g_pObjektPool->GetGeoObj( pID );
//	pGO->Folie() = m_Folie;
//	pGO->Objektart() = m_Objektart;
//	pGO->Aktualitaet() = m_Aktuali;
/*
	m_omGeoObjekte.Lookup( pID, (CObject*&)pGO );
	if ( !pGO )
		m_omGeoObjekte.SetAt( pID, pGO = new CGeoObj( pID ));
*/
	if ( pGO ) {
		pGO -> AddAttribute( k, t );
		g_pTriasInterface -> NeuesMerkmal( k );
		res = TRUE;
	}

	return res;
}	// AddMerkmal


CGeoObj *CObjektPool :: Fertig()
{	
	CGeoObj*		pGO = m_pgoReady;
/*
	CTriasObjekt	*pTO;
	CPunktFolge		*pPF;
	CPunkt			*pPT;
	POSITION		posMM;
	CString			key, text;
	int				j;
	long			l, z, kp;
	m_pgoReady = NULL;

	if ( pGO )
	{	
//	------------------------------------------------------------------------------------
//	Hier ansetzen um Objekte mit Löchern zu identifizieren!
//	------------------------------------------------------------------------------------
		for ( j = 0; j < pGO -> AnzahlLinien(); j++ )
		{	if (( pPF = pGO -> Punkte( j )) -> Geschlossen())
			{	pTO = new CTriasObjekt();
				if ( pTO )
				{	pTO -> ONr() = -1;				// neues Objekt!
					pTO -> Ident() = g_pMetaData -> GetObjectClassIdTRiAS( *pGO );
					if (( z = pGO -> AnzahlPunkte( j )) == 1 )
					{
						pTO -> ObjTyp() = OGPunkt;
						pGO -> ObjTyp() = 'P';
					}
					else
					{
						pTO -> ObjTyp() = OGFlaeche;
						pGO -> ObjTyp() = 'F';
					}
					kp = pTO -> AnzahlPunkte() = z;
					pTO -> AnzahlKonturen() = 1;
					pTO -> XKoord( new double[z+1] );
					pTO -> YKoord( new double[z+1] );
					pTO -> KonturPunkte( &kp );
					pTO -> UniqueIdent() = pGO -> UniqueIdent();

					posMM = pGO -> GetMMStartPos();
					while ( posMM )
					{	pGO -> GetMMNext( posMM, key, text );
						pTO -> AddTextMerkmal( key, text );
					}
					if ( !pGO -> Folie().IsEmpty())
						pTO -> AddTextMerkmal( "Folie", pGO -> Folie() );
					if ( !pGO -> ObjektArt().IsEmpty())
						pTO -> AddTextMerkmal( "Objektart", pGO -> ObjektArt() );
					pTO -> Neu() = TRUE;
//					pPF = pGO -> Punkte( j );
					for ( l = 0; l < pPF -> GetSize(); l++ )
					{	pPT = (CPunkt*)pPF -> GetAt( (int)l );
//						*((double*)pTO -> XKoord() + l) = double( pPT -> Rechts() / 100.0 );
//						*((double*)pTO -> YKoord() + l) = double( pPT -> Hoch() / 100.0 );
						*((double*)pTO -> XKoord() + l) = pPT -> Rechts();
						*((double*)pTO -> YKoord() + l) = pPT -> Hoch();
					}
					pTO -> WriteBack();
					pTO -> KonturPunkte( NULL );	// weil: &kp nicht freigeben!!!
					pGO -> ObjNr() = pTO -> ONr();
					pGO -> DelFolge( j );			// Achtung! Hinterlässt Lücke!
													// unbedingt mit Pack() vollenden!!!
					delete pTO;
		}	}	}
		pGO -> Pack();
	}
*/
  return pGO;

}	// Fertig

void CObjektPool::WriteBack( bool fStatus )
{
	CTriasObjekt	*pTO;
//	CObjectClassEDBS *pOCE;
	CGeoObj			*pGO;
	CPunktFolge		*pPF;
	CPunkt			*pPT;
	CString			text, id, key;
	POSITION		pos;
	int			a, j, nr, anzahl;
	long			l, z, max, kp = 1L;
	long			*pkp = NULL;

	g_pTriasInterface->UpdateHeaders();

	nr = 0;
	anzahl = m_omGeoObjekte.GetCount();
	text = "Gelesene Objekte zu %d%% in ";
	text += ((CEDBSExtension*)g_pTE)->Configuration.m_strTRiASName;
	text += " gespeichert!";
	((CEDBSExtension*)g_pTE) -> SetDefaultStatusTexte( text, NULL, "Datei:",   NULL );

	((CEDBSExtension*)g_pTE) -> InitStatusDialog( g_pTriasInterface->strImportFullFileName,
					(ULONG)anzahl, NULL );

	for ( pos = m_omGeoObjekte.GetStartPosition(); pos != NULL; ) {	
		m_omGeoObjekte.GetNextAssoc( pos, id, (CObject*&)pGO );
		
		((CEDBSExtension*)g_pTE) -> SetupStatus( (ULONG)++nr );

		if( !g_pMetaData->ClassifyGeoObject( *pGO ) ) {
			delete pGO;
			continue;
		}
/*		pOCE = g_pMetaData->GetObjectClassEDBS(pGO->Objektart());
		if( pOCE )
			if( pOCE->Ignored() ) 
				continue;
		if( g_pMetaData->IgnoreFolie( pGO->Folie() ) )
			continue;	
*/
		if( !g_pMetaData->Filter.IsEmpty() )
			if( strcmp(pGO -> UniqueIdent().Left(g_pMetaData->Filter.GetLength()), g_pMetaData->Filter) ) {
				delete pGO;
				continue;
			}
//	------------------------------------------------------------------------------------
//	Hier ansetzen um Objekte mit Löchern zu identifizieren!
//	------------------------------------------------------------------------------------

//	------------------------------------------------------------------------------------
//	Fallunterscheidung: Linienobjekte mit mehreren, nicht verbundenen Linienabschnitten
//						werden in mehrere Objekte gesplittet!
//	------------------------------------------------------------------------------------
		if (( pGO -> AnzahlLinien() == 1 ) && ( pGO -> ObjTyp() != 'L' ))
			if ( pGO -> Punkte(0) -> Geschlossen())
				pGO -> ObjTyp() = 'F';

		if (( pGO -> ObjTyp() == 'F' ) && ( pGO -> AnzahlLinien() > 1 )) {
			// Flächen mit nicht geschlossenen Konturen aussondern!
			for ( j = 0; j < pGO -> AnzahlLinien(); j++ )
				if ( !pGO -> Punkte( j ) -> Geschlossen())
					pGO -> ObjTyp() = 'L';
		}
		
		if (( pGO -> ObjTyp() == 'L' ) && ( pGO -> AnzahlLinien() > 1 )) {
			CxString	strUID;
			for ( short loop = 0; loop < pGO -> AnzahlLinien(); loop++ ) {
				pTO = new CTriasObjekt( pGO );
				pkp = &kp;

				if ( pTO ) {
					pTO -> Neu() = TRUE;
					pTO -> ONr() = -1;				// neues Objekt!

					pTO -> Ident() = pGO->ObjectClassTRiAS()->ClassIdentTRiAS();

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
					{	pPT = (CPunkt*)pPF -> GetAt( (int)l );
						*((double*)pTO -> XKoord() + z) = pPT -> Rechts();
						*((double*)pTO -> YKoord() + z) = pPT -> Hoch();
						z++;
					}

					pTO -> ObjTyp() = OGLinie;
					pTO -> AnzahlKonturen() = 1;
					strUID.Empty();
					strUID.printf( "%s_%d", (const char*)pGO -> UniqueIdent(), loop );
					pTO -> UniqueIdent() = strUID;
					pTO -> WriteBack();
					pTO -> KonturPunkte( NULL );	// weil: &kp nicht freigeben!!!
					delete pTO;
				}
			}	
		}
		else {
			pTO = new CTriasObjekt( pGO );
			if ( pGO -> AnzahlLinien() || pGO -> ObjNr()) {
				if ( pGO -> AnzahlLinien() > 1 )
					pkp = new long[pGO -> AnzahlLinien()];
				else
					pkp = &kp;

				if ( pTO ) {
					if ( pGO -> ObjNr()) {
						pTO->Neu() = FALSE;
						pTO -> ONr() = pGO -> ObjNr();
					}
					else {	// neues Objekt!
						pTO->Neu() = TRUE;
						pTO -> ONr() = -1;				
					}

					pTO -> Ident() = pGO->ObjectClassTRiAS()->ClassIdentTRiAS();

					max = z = 0L;
					a = 0;
					// Gesamtzahl Punkte und Hypothese für Aussenkontur ermitteln
					for ( j = 0; j < pGO -> AnzahlLinien(); j++ )
					{	z += pGO -> AnzahlPunkte( j );
						if ( pGO -> AnzahlPunkte( j ) > max )
						{	max = pGO -> AnzahlPunkte( j );
							a = j;
					}	}
					pTO -> AnzahlPunkte() = z;
					pTO -> XKoord( new double[z+1] );
					pTO -> YKoord( new double[z+1] );
					pTO -> KonturPunkte( pkp );
					z = 0L;

					if ( pGO -> AnzahlLinien())
					{	// zuerst die Aussenkontur eintragen!
						pPF = pGO -> Punkte( a );
						for ( l = 0; l < pPF -> GetSize(); l++ )
						{	pPT = (CPunkt*)pPF -> GetAt( (int)l );
							*((double*)pTO -> XKoord() + z) = pPT -> Rechts();
							*((double*)pTO -> YKoord() + z) = pPT -> Hoch();
							z++;
					}	}
					pkp[0] = max;

					if ( pGO -> ObjTyp() == 'F' ) {
						if ( pGO -> AnzahlLinien()) {
							if ( pGO -> AnzahlPunkte( 0 ) == 1 )
								pTO -> ObjTyp() = OGPunkt;
							else
								pTO -> ObjTyp() = OGFlaeche;
						}	
					}
					else if ( pGO -> ObjTyp() == 'L' )
						pTO -> ObjTyp() = OGLinie;
					else if ( pGO -> ObjTyp() == 'P' )
						pTO -> ObjTyp() = OGPunkt;
					else if ( pGO -> ObjTyp() == 'T' ) {
						pTO -> ObjTyp() = OGText;
					}
					else
						if ( pGO -> AnzahlLinien())
						{	if ( pGO -> AnzahlPunkte( 0 ) == 1 )
								pTO -> ObjTyp() = OGPunkt;
							else
								if ( pGO -> Punkte(0) -> Geschlossen())
									pTO -> ObjTyp() = OGFlaeche;
								else
									pTO -> ObjTyp() = OGLinie;
						}

					pTO -> AnzahlKonturen() = pGO -> AnzahlLinien();
					pTO -> UniqueIdent() = pGO -> UniqueIdent();

					for ( j = 0; j < pGO -> AnzahlLinien(); j++ )
					{	if ( j != a )
						{	if ( j < a )	pkp[j+1] = pGO -> AnzahlPunkte( j );
							else		pkp[j]   = pGO -> AnzahlPunkte( j );

							pPF = pGO -> Punkte( j );
							for ( l = 0; l < pPF -> GetSize(); l++ )
							{	pPT = (CPunkt*)pPF -> GetAt( (int)l );
	//							*((double*)pTO -> XKoord() + z) = double( pPT -> Rechts() / 100.0 );
	//							*((double*)pTO -> YKoord() + z) = double( pPT -> Hoch() / 100.0 );
								*((double*)pTO -> XKoord() + z) = pPT -> Rechts();
								*((double*)pTO -> YKoord() + z) = pPT -> Hoch();
								z++;
							}
						}
					}
				}	
			}

/*#fje
	if (( pTO -> ObjTyp() == OGLinie ) && ( pTO -> AnzahlKonturen() > 1 )) {
		CString	text = "Nicht verbundene Linienabschnitte! UID: ";
		text += pTO -> UniqueIdent();
		AfxMessageBox( text );
	}
*/

			pTO -> WriteBack();
			pTO -> KonturPunkte( NULL );	// weil: &kp nicht freigeben!!!
			if ( pGO -> AnzahlLinien() > 1 )
				delete pkp;
			delete pTO;
		}	
		delete pGO;

		if (((CEDBSExtension*)g_pTE) -> NutzerAbbruch()) {
			if ( AfxMessageBox( "Alle bisher gelesenen Informationen gehen beim Abbruch verloren!\nTatsächlich abbrechen?",
				MB_ICONQUESTION|MB_YESNO ) == IDYES ) {
				break;
			}
			else
				((CEDBSExtension*)g_pTE) -> ResetAbbruch();
		}	
	}

/*
	for ( pos = m_omGeoObjekte.GetStartPosition(); pos != NULL; )
	{	m_omGeoObjekte.GetNextAssoc( pos, id, (CObject*&)pGO );
		delete pGO;
	}
*/
	m_omGeoObjekte.RemoveAll();
}	// WriteBack
