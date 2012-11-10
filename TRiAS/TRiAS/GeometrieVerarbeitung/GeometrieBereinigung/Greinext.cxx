// Definition des Interface für die Erweiterung "Geometriebereinigung"
// File: GReinExt.cxx


#include "GeoReinP.hxx"

#include <limits.h>			// ULONG_MAX

#include "GeometrR.h"		// IDS_INTERSPITZE, ...
#include "objgext.hxx"		// CreateInterfaceOG (muß NACH ctfxmfc.h stehen !!!)
#include "datbank.hxx"		// GetHeaderMCode()

#include "GeoReinR.h"		// IDS_LONGCLASSNAME
#include "georein.hxx"		// GeoReinExtension


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern ResourceFile* pRF;



///////////////////////////////////////////////////////////////////////////////////////////////
// MemberFunctions für Interface-Routinen
// --------------------------------------------------------------------------------------------
// Test zwischen den Geometrien des pIOG1- und des pIOG2-Objektes
HRESULT GeoReinExtension :: InterGeometryTest (IObjektGeometrie* pIOG1, int iOT1,
						 IObjektGeometrie* pIOG2, int iOT2, ErrorTextMode etText, BOOL* pbSucc)
{
string sObjName1, sObjName2;	// Objektnamen des pIOG1- und des pIOG2-Objektes

long lONr1, lONr2;
ulong ulIdent1, ulIdent2;

	pIOG1->GetONr (&lONr1);
	pIOG2->GetONr (&lONr2);
	pIOG1->GetIdent (&ulIdent1);
	pIOG2->GetIdent (&ulIdent2);

	if (!ReadFeatureText (lONr1, DEX_GetObjNameMCode(ulIdent1), TT_Objekt, sObjName1))
		return E_OUTOFMEMORY;	// nicht genügend dynamischer Speicher

	if (!ReadFeatureText (lONr2, DEX_GetObjNameMCode(ulIdent2), TT_Objekt, sObjName2))
		return E_OUTOFMEMORY;

bool bSucc1, bSucc2, bSucc3;
bool bNear;		// Near-Fehler nicht/gefunden (false/true)

HRESULT hrRet = VerticesLoops (pIOG1, iOT1, pIOG2, iOT2, sObjName1, sObjName2, etText, bNear,
							   bSucc1);

	if (!bNear)
		hrRet = SmallDistance (pIOG1, pIOG2, sObjName1, sObjName2, etText, bSucc2);

	hrRet = OverLapping (pIOG1, pIOG2, sObjName1, sObjName2, etText, bSucc3);

	*pbSucc = (bSucc1 && bSucc2 && bSucc3);

	return hrRet;

} // InterGeometryTest


// --------------------------------------------------------------------------------------------
// Test der einzelnen Stützpunkte der pIOG1- und pIOG2-Objekte
HRESULT GeoReinExtension :: VerticesLoops (IObjektGeometrie* pIOG1, int iOT1,
							  IObjektGeometrie* pIOG2, int iOT2, string sObjName1,
							  string sObjName2, ErrorTextMode etText, bool& bNear, bool& bSucc)
{
	_ASSERTE (pIOG1 != NULL);
	_ASSERTE (pIOG2 != NULL);

	bNear = false;		// (noch) kein Near-Fehler gefunden

long lCnt1, lCnt2;		// weitere Parameter der pIOG1- und pIOG2-Objekte
KoOrd* plXK1; KoOrd* plYK1; KoOrd* plXK2; KoOrd* plYK2;

	pIOG1->GetCnt (&lCnt1);
	pIOG1->GetX ((void**)&plXK1);
	pIOG1->GetY ((void**)&plYK1);
	pIOG2->GetCnt (&lCnt2);
	pIOG2->GetX ((void**)&plXK2);
	pIOG2->GetY ((void**)&plYK2);

KoOrd xmin1, ymin1, xmax1, ymax1, xmin2, ymin2, xmax2, ymax2;

	pIOG1->GetCont (&xmin1, &ymin1, &xmax1, &ymax1);
	pIOG2->GetCont (&xmin2, &ymin2, &xmax2, &ymax2);

KoOrd xmin = min (xmin1, xmin2);
KoOrd ymin = min (ymin1, ymin2);
KoOrd xmax = max (xmax1, xmax2);
KoOrd ymax = max (ymax1, ymax2);
DoublePair dpUF = UmrechnungsFaktor (xmin, ymax, xmax, ymin, m_pCT);
string sAnalyseText;	// Ergebnis der Fehleranalyse

	if (OT_FLAECHE == iOT1) lCnt1--;	// bei Flächenkontur
	if (OT_FLAECHE == iOT2) lCnt2--;

	for (long j1 = 0; j1 < lCnt1; j1++)
		for (long j2 = 0; j2 < lCnt2; j2++)
		{
			if ((plXK1[j1] != plXK2[j2] || plYK1[j1] != plYK2[j2]) &&	// kein Test auf IDENTISCHE Punkte 
				isNear (m_dDPEps, dpUF, m_bMetric, plXK1[j1], plYK1[j1], plXK2[j2],
						plYK2[j2]))
			{
				AnalysePuffern (sAnalyseText, plXK1[j1], plYK1[j1], plXK2[j2], plYK2[j2]);
				bNear = true;	// Near-Fehler gefunden
			}

			if (AcuteAngle (m_dSpEps, pIOG1, iOT1, lCnt1, plXK1, plYK1, j1, pIOG2, iOT2,
							lCnt2, plXK2, plYK2, j2))
				AnalysePuffern (sAnalyseText, plXK1[j1], plYK1[j1]);
		}

	if (0 == sAnalyseText.length())	// kein Fehlertext
	{
		bSucc = true;
		return S_OK;
	}

	if (REIN_BOTH == etText || REIN_FIRST == etText)
		InterErrorToFeature (pIOG1, sAnalyseText, sObjName2);
	if (REIN_BOTH == etText || REIN_SECOND == etText)
		InterErrorToFeature (pIOG2, sAnalyseText, sObjName1);
	bSucc = false;

	return S_FALSE;

} // VerticesLoops


// --------------------------------------------------------------------------------------------
// !!!!! das neue isDoppel !!!!!
// Test, ob 2 Stützpunkte nahe beieinander liegen
bool GeoReinExtension :: isNear (double dEps, DoublePair dpUF, bool bMetric, KoOrd x1,
								 KoOrd y1, KoOrd x2, KoOrd y2)
{
	if (bMetric)	// metrische Datenbank
		return (AbstandPktPktE (x1, y1, x2, y2) <= dpUF.X() * dEps);

	// geodätische Datenbank
	_ASSERTE (dpUF.X() > 0.);
	_ASSERTE (dpUF.Y() > 0.);

double dx = (x2 - x1) / dpUF.X();	// aus Datenbank-Verhältnissen zurück
double dy = (y2 - y1) / dpUF.Y();	// zu Werten in Metern

	return (dx*dx + dy*dy <= dEps*dEps);	// sqrt auf beiden Seiten spare ich mir

} // isNear


// --------------------------------------------------------------------------------------------
// Test, ob das pIOG1- und das pIOG2-Objekt beim Stützpunkt j1(j2) eine Spitze bilden
bool GeoReinExtension :: AcuteAngle (double dSpEps, IObjektGeometrie* pIOG1, int iOT1,
					  long lCnt1, KoOrd* plXK1, KoOrd* plYK1, long j1, IObjektGeometrie* pIOG2,
					  int iOT2, long lCnt2, KoOrd* plXK2, KoOrd* plYK2, long j2)
{
	_ASSERTE (pIOG1 != NULL);
	_ASSERTE (pIOG2 != NULL);
	_ASSERTE (plXK1 != NULL);
	_ASSERTE (plYK1 != NULL);
	_ASSERTE (plXK2 != NULL);
	_ASSERTE (plYK2 != NULL);

	// nur Test auf Spitze, wenn j1- und j2-Stützpunkt identisch sind
	if (plXK1[j1] != plXK2[j2] || plYK1[j1] != plYK2[j2])
		return false;

long j1v = j1 - 1;	// vorhergehender Index  } führt bei Linie zu einem
long j1n = j1 + 1;	// nachfolgender Index   } einkalkulierten Indexfehler

	if (OT_FLAECHE == iOT1)
		pIOG1->IndexVorNach (j1, &j1v, &j1n);

long j2v = j2 - 1;
long j2n = j2 + 1;

	if (OT_FLAECHE == iOT2)
		pIOG2->IndexVorNach (j2, &j2v, &j2n);	

	// es gibt 4 mögliche Kombinationen
	if (j1v >= 0 && j2v >= 0 &&
		isAcute (dSpEps, plXK1[j1v], plYK1[j1v], plXK1[j1], plYK1[j1], plXK2[j2v], plYK2[j2v],
				 false))
		return true;

	if (j1v >= 0 && j2n < lCnt2 &&
		isAcute (dSpEps, plXK1[j1v], plYK1[j1v], plXK1[j1], plYK1[j1], plXK2[j2n], plYK2[j2n],
				 false))
		return true;

	if (j1n < lCnt1 && j2v >= 0 &&
		isAcute (dSpEps, plXK1[j1n], plYK1[j1n], plXK1[j1], plYK1[j1], plXK2[j2v], plYK2[j2v],
				 false))
		return true;

	if (j1n < lCnt1 && j2n < lCnt2 &&
		isAcute (dSpEps, plXK1[j1n], plYK1[j1n], plXK1[j1], plYK1[j1], plXK2[j2n], plYK2[j2n],
				 false))
		return true;

	return false;

} // AcuteAngle


// --------------------------------------------------------------------------------------------
// !!!!! das neue isSpitz !!!!!
// Test, ob P1(x1,y1), P2(x2,y2) und P3(x3,y3) bei P2 einen spitzen Winkel kleiner oder gleich
// dSpEps (in Gradmaß) bilden; dann Rückgabe von true, sonst false;
// P1 und P3 können von ein und demselben (bSingle == true) bzw. von zwei verschiedenen
// Objekten (bSingle == false) sein; im letzteren Fall gilt 0° nicht als Spitze
// !!!!!!!!!!!!!!
// der in EKante::isSpitz() behandelte Fall, ob eine aus 3 Stützpunkten bestehende Kante
// geschlossen ist, kann hier jedoch nicht abgetestet werden und muß deshalb AUßERHALB von
// isAcute() geprüft werden
bool GeoReinExtension :: isAcute (double dSpEps, KoOrd x1, KoOrd y1, KoOrd x2, KoOrd y2,
								  KoOrd x3, KoOrd y3, bool bSingle)
{
	// es muß gelten P1 != P2 und P2 != P3
	if ((x1 == x2 && y1 == y2) || (x2 == x3 && y2 == y3))
		return false;

	if ((x1 == x3 && y1 == y3) ||			// die beiden Basispunkte P1 und P3 sind gleich
		Kollinear (x1, y1, x2, y2, x3, y3))	// bzw. kollinear
	{
		if (bSingle)		// P1 und P3 sind von ein und demselben Objekt,
			return true;	// dann ist bei P2 eine Spitze;
		return false;		// P1 und P3 sind von zwei verschiedenen Objekten, dann bei P2
							// keine Spitze
	}

double d1x = x2 - x1;
double d1y = y2 - y1;
double d2x = x2 - x3;
double d2y = y2 - y3;

double hw2 = d1x*d2x+d1y*d2y;
double hw3 = cos(dSpEps*Pi/180.)*sqrt((d1x*d1x+d1y*d1y)*(d2x*d2x+d2y*d2y));

	// mit dem Test hw2 >= hw3 werden sowohl der Winkel dSpEps als auch der Winkel 360°-dSpEps
	// geprüft, da für den Test für 360°-dSpEps nur P1 und P3 vertauscht werden müßten, was
	// nur zum Vertauschen von d1x (d1y) mit d2x (d2y) führen würde: also nichts Neues im
	// Westen
	return (hw2 >= hw3);

} // isAcute


// --------------------------------------------------------------------------------------------
// Schnellschuß für Fehlerausgabe bei "zu enger Nachbarschaft" und "zu kleinem Winkel"
void GeoReinExtension :: AnalysePuffern (string& sAnalyseText, KoOrd x1, KoOrd y1, KoOrd x2,
										 KoOrd y2)
{
ResString resText (ResID (IDS_INTERSPITZE, pRF), 70);
double XOut1, YOut1, XOut2, YOut2;	// Real-Koordinaten
string sBuffer;

	// Konvertierung der Datenbank- in Real-Koordinaten
	DBKoordInReal (x1, y1, XOut1, YOut1, m_pCT);

	if (x2 > 0 && y2 > 0)	// zu enge Nachbarschaft
	{
		DBKoordInReal (x2, y2, XOut2, YOut2, m_pCT);
		resText = ResString (ResID (IDS_INTERNACHBAR, pRF), 100);
		Format (sBuffer, (char*)resText.Addr(), DtoL(XOut1), DtoL(YOut1), DtoL(XOut2),
				DtoL(YOut2));
	}
	else					// zu kleiner Winkel
		Format (sBuffer, (char*)resText.Addr(), DtoL(XOut1), DtoL(YOut1));

	sAnalyseText += sBuffer;
	sAnalyseText += "'%s'\r\n";

} // AnalysePuffern


// --------------------------------------------------------------------------------------------
// Test auf zu geringem Abstand zwischen pIOG1- und pIOG2-Objekt
HRESULT GeoReinExtension :: SmallDistance (IObjektGeometrie* pIOG1, IObjektGeometrie* pIOG2,
						 string sObjName1, string sObjName2, ErrorTextMode etText, bool& bSucc)
{
	bSucc = true;	// kein Fehler, d. h. Abstand zwischen pIOG1- und pIOG2-Objekt ausreichend
					// groß

	if (! m_wAbstand.IsValid())	// (wenn noch nicht, dann) IExtendAbstand2-Interface für
	{							//  DistanceObjObj_Geom() zuschalten
	WUnknown wAbstand;

		AbstandInterface (wAbstand.ppi());
		m_wAbstand = wAbstand;
	}

double dAbst;		// Abstand 

	if (m_wAbstand.IsValid())
		m_wAbstand->DistanceObjObj_Geom (pIOG1, pIOG2, &dAbst, DISTTYP_EXACT, ABST_MIN);
	else return E_POINTER;
	
	if (dAbst > 0 && dAbst < m_dDPEps)
	{
	string sAnalyseText;
	ResString resText (ResID (IDS_INTERABSTAND, pRF), 50);

		sAnalyseText = resText.Addr();
		sAnalyseText += "'%s'\r\n";

		if (REIN_BOTH == etText || REIN_FIRST == etText)
			InterErrorToFeature (pIOG1, sAnalyseText, sObjName2);
		if (REIN_BOTH == etText || REIN_SECOND == etText)
			InterErrorToFeature (pIOG2, sAnalyseText, sObjName1);

		bSucc = false;	// Abstand zwischen pIOG1- und pIOG2-Objekt zu klein
		return S_FALSE;
	}

	return S_OK;

} // SmallDistance


// --------------------------------------------------------------------------------------------
// Test auf Überlappung zwischen pIOG1- und pIOG2-Objekt
HRESULT GeoReinExtension :: OverLapping (IObjektGeometrie* pIOG1, IObjektGeometrie* pIOG2,
						 string sObjName1, string sObjName2, ErrorTextMode etText, bool& bSucc)
{
	bSucc = true;	// kein Fehler, d. h. keine Überlappung zwischen pIOG1- und pIOG2-Objekt

	if (! m_wTopoRel.IsValid())	// (wenn noch nicht, dann) IExtendTopRel2-Interface für
	{							//  TopoRelationObjObj_Geom() zuschalten
	WUnknown wTopoRel;

		TopoRelInterface (wTopoRel.ppi());
		m_wTopoRel = wTopoRel;
	}

	if (! m_wTopoRel.IsValid()) return E_POINTER;

// Lage von pIOG2 bzgl. pIOG1
Relat rTR;

	m_wTopoRel->TopoRelationObjObj_Geom (pIOG1, pIOG2, &rTR);

	if (REL_UNKLAR == rTR) return E_UNEXPECTED;

	if (REL_AUSS == rTR)
		// wenn pIOG2 außerhalb von pIOG1 liegt, dann Test, ob evtl. pIOG1 von pIOG2 bzw. pIOG2
		// von pIOG1 umschlossen wird
		return EnclosingTest (pIOG1, pIOG2, sObjName1, sObjName2, etText, bSucc);

string sAnalyseText;	// Ergebnis der Fehleranalyse
ResString resText (ResID (IDS_INTEROVERLAP, pRF), 50);	// rTR == REL_INAUS

	if (REL_INN == rTR)
		resText = ResString (ResID (IDS_INTERINSIDE, pRF), 50);

	sAnalyseText = resText.Addr();
	sAnalyseText += "'%s'\r\n";

	if (REIN_BOTH == etText || REIN_SECOND == etText)
		InterErrorToFeature (pIOG2, sAnalyseText, sObjName1);


// Lage von pIOG1 bzgl. pIOG2
	m_wTopoRel->TopoRelationObjObj_Geom (pIOG2, pIOG1, &rTR);

	if (REL_UNKLAR == rTR) return E_UNEXPECTED;

	_ASSERTE (rTR != REL_AUSS);

	resText = ResString (ResID (IDS_INTEROVERLAP, pRF), 50);	// rTR == REL_INAUS

	if (REL_INN == rTR)
		resText = ResString (ResID (IDS_INTERINSIDE, pRF), 50);

	sAnalyseText = resText.Addr();
	sAnalyseText += "'%s'\r\n";

	if (REIN_BOTH == etText || REIN_FIRST == etText)
		InterErrorToFeature (pIOG1, sAnalyseText, sObjName2);

	bSucc = false;	// Überlappung zwischen pIOG1- und pIOG2-Objekt

	return S_FALSE;

} // Overlapping


// --------------------------------------------------------------------------------------------
// Test, ob pIOG1 von pIOG2 bzw. pIOG2 von pIOG1 umschlossen wird
HRESULT GeoReinExtension :: EnclosingTest (IObjektGeometrie* pIOG1, IObjektGeometrie* pIOG2,
						 string sObjName1, string sObjName2, ErrorTextMode etText, bool& bSucc)
{
	_ASSERTE (pIOG1 != NULL);
	_ASSERTE (pIOG2 != NULL);
	_ASSERTE (m_wTopoRel.IsValid());

HRESULT hrRet = S_OK;	// return-Wert
short iKCnt1, iKCnt2;	// Größe der Konturfelder

	pIOG1->GetKCnt (&iKCnt1);
	pIOG2->GetKCnt (&iKCnt2);

	if (iKCnt1 <= 1 && iKCnt2 <= 1)	// kein Umschließen möglich
		return S_OK;

WObjektGeometrie wAKont;	// Außenkontur von pIOG.
WObjektGeometrie wPkt;		// 1. Stützpunkt von pIOG.
KoOrd* plXK1; KoOrd* plYK1; KoOrd* plXK2; KoOrd* plYK2;
long* plCnt;				// Anzahl der Stützpunkte in den pIOG.-Konturen

	pIOG1->GetX ((void**)&plXK1);
	pIOG1->GetY ((void**)&plYK1);
	pIOG2->GetX ((void**)&plXK2);
	pIOG2->GetY ((void**)&plYK2);

Relat rTR;
string sAnalyseText;
ResString resText1 (ResID (IDS_INTERENCLOSE1, pRF), 50);
ResString resText2 (ResID (IDS_INTERENCLOSE2, pRF), 50);

// wird pIOG2 von pIOG1 umschlossen?
	if (iKCnt1 > 1)		// pIOG1 ist eine Fläche und hat mindestens 1 Insel
	{
		pIOG1->GetLPCnt (&plCnt);

		hrRet = CreateInterfaceOG (wAKont.ppi(), plXK1, plYK1, plCnt[0], OT_FLAECHE);
		if (FAILED(hrRet)) return hrRet;

		hrRet = CreateInterfaceOG (wPkt.ppi(), plXK2[0], plYK2[0], OT_PUNKT);
		if (FAILED(hrRet)) return hrRet;

		m_wTopoRel->TopoRelationObjObj_Geom (wAKont, wPkt, &rTR);

		if (REL_INN == rTR)
		{
			if (REIN_BOTH == etText || REIN_FIRST == etText)
			{
				sAnalyseText = resText1.Addr();
				sAnalyseText += "'%s'\r\n";
				InterErrorToFeature (pIOG1, sAnalyseText, sObjName2);
			}

			if (REIN_BOTH == etText || REIN_SECOND == etText)
			{
				sAnalyseText = resText2.Addr();
				sAnalyseText += "'%s'\r\n";
				InterErrorToFeature (pIOG2, sAnalyseText, sObjName1);
			}

			bSucc = false;	// Umschließung zwischen pIOG1- und pIOG2-Objekt
			return hrRet;
		}
	}


// wird pIOG1 von pIOG2 umschlossen?
	if (iKCnt2 > 1)		// pIOG2 ist eine Fläche und hat mindestens 1 Insel
	{
		pIOG2->GetLPCnt (&plCnt);

		hrRet = CreateInterfaceOG (wAKont.ppi(), plXK2, plYK2, plCnt[0], OT_FLAECHE);
		if (FAILED(hrRet)) return hrRet;

		hrRet = CreateInterfaceOG (wPkt.ppi(), plXK1[0], plYK1[0], OT_PUNKT);
		if (FAILED(hrRet)) return hrRet;

		m_wTopoRel->TopoRelationObjObj_Geom (wAKont, wPkt, &rTR);

		if (REL_INN == rTR)
		{
			if (REIN_BOTH == etText || REIN_FIRST == etText)
			{
				sAnalyseText = resText1.Addr();
				sAnalyseText += "'%s'\r\n";
				InterErrorToFeature (pIOG2, sAnalyseText, sObjName1);
			}

			if (REIN_BOTH == etText || REIN_SECOND == etText)
			{
				sAnalyseText = resText2.Addr();
				sAnalyseText += "'%s'\r\n";
				InterErrorToFeature (pIOG1, sAnalyseText, sObjName2);
			}

			bSucc = false;	// Umschließung zwischen pIOG2- und pIOG1-Objekt
		}
	}

	return hrRet;

} // EnclosingTest


// --------------------------------------------------------------------------------------------
// Fehlertext als Merkmal an Objekt pIOG wegschreiben
HRESULT GeoReinExtension :: InterErrorToFeature (IObjektGeometrie* pIOG, string sAnalyseText,
												 string sObjName)
{
	_ASSERTE (pIOG != NULL);

long lONr;

	pIOG->GetONr (&lONr);

// #WM021210
//	// Identifikator für Merkmal "Verschnitt" evtl. neu bilden
//	if (0 == m_ulMCodeInterSect || -1 == m_ulMCodeInterSect)
//	{
//		m_ulMCodeInterSect = GetHeaderMCode (true, IDS_INTERSECT, IDS_INTERSECTKT,
//											 IDS_INTERSECTLT, DEX_GetObjIdent(lONr));
//		if (0 == m_ulMCodeInterSect || -1 == m_ulMCodeInterSect)
//			return E_FAIL;
//	}

	ObjNameInsert (sAnalyseText, sObjName);

string sAnalyseTextOld;	// evtl. schon vorhandener Fehlertext

	ReadFeatureText (lONr, m_ulMCodeInterSect, TT_Objekt, sAnalyseTextOld);
	if (sAnalyseTextOld.length() > 0)	// schon Fehlertext vorhanden
		sAnalyseText += sAnalyseTextOld;

	WriteFeatureText (lONr, m_ulMCodeInterSect, TT_Objekt, sAnalyseText);

	return S_OK;

} // InterErrorToFeature


// --------------------------------------------------------------------------------------------
// die Zeichenkette "%s" in sAnalyseText durch den Objektnamen sObjName ersetzen
void GeoReinExtension :: ObjNameInsert (string& sAnalyseText, string sObjName)
{
string sTrenn = "%s";			// der zu suchende und zu ersetzende String
int iLen = sTrenn.length();		// dessen Länge
int iPos = -iLen;

	for (;;)
	{
		iPos = sAnalyseText.find (sTrenn, iPos + iLen);
		if (NPOS == iPos) return;	// sTrenn nicht mehr gefunden
		sAnalyseText.replace (iPos, iLen, sObjName);
	}

} // ObjNameInsert


// --------------------------------------------------------------------------------------------
// Bezug zur Erweiterung "Abstandsmessung" herstellen
HRESULT GeoReinExtension :: AbstandInterface (IUnknown** ppIAbstand)
{
HRESULT hr = S_OK;
WExtendAbstand2 wAbstand;	// Interface für Ankopplung von Abstand.ext

	if (m_pXtnSite)
	{
		hr = m_pXtnSite->GetXtension (CLSID_Abstand, IID_IExtendAbstand2,
									  (LPVOID*)wAbstand.ppi());

		// "detach": Weiterreichen des Pointers ohne Release() und erneutes AddRef()
		*ppIAbstand = wAbstand.detach();
	}
	else hr = E_UNEXPECTED;

	if (FAILED (hr) ||	// Fehler, z.B. Abstand.ext nicht verfügbar
		! m_pXtnSite)
	{
	ResString resText1 (ResID (IDS_NOABSTAND, pRF), 250);
	ResString resText2 (ResID (IDS_LONGCLASSNAME, pRF), 50);
		
		MessageBox (__hWndM, resText1.Addr(), resText2.Addr(), MB_ICONEXCLAMATION | MB_OK);
		return hr;
	}

	return hr;

} // AbstandInterface   


// --------------------------------------------------------------------------------------------
// Bezug zur Erweiterung "Topologische Relationen" herstellen
HRESULT GeoReinExtension :: TopoRelInterface (IUnknown** ppITopoRel)
{
HRESULT hr = S_OK;
WExtendTopRel2 wTopoRel;	// Interface für Ankopplung von TopoRel.ext

	if (m_pXtnSite)
	{
		hr = m_pXtnSite->GetXtension (CLSID_Topologie, IID_IExtendTopRel2,
									  (LPVOID*)wTopoRel.ppi());

		// "detach": Weiterreichen des Pointers ohne Release() und erneutes AddRef()
		*ppITopoRel = wTopoRel.detach();
	}
	else hr = E_UNEXPECTED;

	if (FAILED (hr) ||	// Fehler, z.B. TopoRel.ext nicht verfügbar
		! m_pXtnSite)
	{
	ResString resText1 (ResID (IDS_NOTOPOREL, pRF), 250);
	ResString resText2 (ResID (IDS_LONGCLASSNAME, pRF), 50);
		
		MessageBox (__hWndM, resText1.Addr(), resText2.Addr(), MB_ICONEXCLAMATION | MB_OK);
		return hr;
	}

	return hr;

} // TopoRelInterface   



///////////////////////////////////////////////////////////////////////////////////////////////
// IExtendGeoRein-Methoden
// --------------------------------------------------------------------------------------------
// vollständiger Test auf Fehlerfreiheit OHNE Bereinigung von Fehlern, da ich noch nicht weiß,
// wie ich bei "LONG lONr" die möglicherweise korrigierte Geometrie zurückreichen kann;
// benötigt für schreibgeschützte Datenquellen bzw. Objektklassen;
// bei Fehlerfreiheit ist *pbSucc = true
STDMETHODIMP_ (HRESULT) GeoReinExtension :: WholeAnalysis_ONr (LONG lONr, BOOL* pbSucc)
{
	_ASSERTE (0 != lONr);
	_ASSERTE (-1 != lONr);
			
ErrInstall EI (WC_MESSAGE_REIN);	// keine Anzeige der Fehlermeldung WC_MESSAGE_REIN

#if _TRiAS_VER >= 0x0300
// #HK000311: Test auf Schreibschutz rausgenommen, da evtl. auch für nicht schreibgeschützte Objekte
// bzw. Objektklassen diese Funktion sinnvoll eingesetzt werden kann
//ulong ulIdent = DEX_GetObjIdent (lONr);
////HPROJECT hPr = DEX_GetObjectsProject (ulIdent);
//
//	if (/*0 == DEX_GetROModeEx (hPr) &&		// Datenquelle nicht schreibgeschützt (R/W-Modus)*/
//		0 == DEX_GetROModeIdent (ulIdent))	// Objektklasse nicht schreibgeschützt
//		return E_NOTIMPL;

WObjektGeometrie wObj;

	COM_TRY
	{
	WInitObjektGeometrie wIObj (CLSID_ObjektGeometrie);	// throws_com_error

		THROW_FAILED_HRESULT (wIObj->InitObjGeometry (lONr));
		wObj = wIObj;
	}
	COM_CATCH;

	*pbSucc = GeometrieAnalysieren (wObj);

	if (*pbSucc)
		return S_OK;
	return E_FAIL;

#else
	return E_NOTIMPL;
#endif // _TRiAS_VER >= 0x0300

} // WholeAnalysis_ONr


// --------------------------------------------------------------------------------------------
// vollständiger Geometrietest und (bei nicht schreibgeschützten Datnquellen) Dokumentation der
// Geometriefehler, die nicht automatisch bereinigt werden können;
// sinnvoll bei Datenimport und bei manueller Modifikation eines fehlerhaften Objektes durch
// den Anwender bzw. Test auf Fehlerfreiheit bei schreibgeschützten Datenquellen bzw.
// Objektklassen;
// bei Fehlerfreiheit ist *pbSucc = true
STDMETHODIMP_ (HRESULT) GeoReinExtension :: WholeAnalysis_Geom (IObjektGeometrie* pIOG,
																BOOL* pbSucc)
{
	if (NULL == pIOG) return E_POINTER;
			
ErrInstall EI (WC_MESSAGE_REIN);	// keine Anzeige der Fehlermeldung WC_MESSAGE_REIN

#if _TRiAS_VER >= 0x0300
ulong ulIdent;

	pIOG->GetIdent (&ulIdent);

	if (/*DEX_GetROModeEx (hPr) ||		// Datenquelle schreibgeschützt (R/O-Modus) oder nicht geöffnet*/
		DEX_GetROModeIdent (ulIdent))	// Objektklasse schreibgeschützt
		*pbSucc = GeometrieAnalysieren (pIOG);
	else
#endif // _TRiAS_VER >= 0x0300

	*pbSucc = GeometriePutzen (pIOG);

	if (*pbSucc)
		return S_OK;
	return E_FAIL;

} // WholeAnalysis_Geom


// --------------------------------------------------------------------------------------------
// verkürzter Geometrietest (sinnvoll bei manueller Modifikation eines fehlerfreien Objektes
// durch den Anwender)
// da möglicherweise der Umlaufsinn korrigiert wurde, wird in plSInd der dadurch veränderte
// Stützpunktindex zurückgegeben
// mögliche return-Werte sind
//   S_OK:	 Objekt ist fehlerfrei
//   E_FAIL: Objekt enthält einen Geometriefehler, der nicht automatisch bereinigt werden kann
//   E_INVALIDARG, E_POINTER: unerlaubte Parameter
STDMETHODIMP_ (HRESULT) GeoReinExtension :: ShortAnalysis (IObjektGeometrie* pIOG,
														   TestRicht trRicht, LONG* plSInd)
{
	_ASSERTE (pIOG != NULL);

	if (NULL == pIOG) return E_POINTER;

	_ASSERTE (*plSInd >= 0);

	if (*plSInd < 0) return E_INVALIDARG;

ErrInstall EI (WC_MESSAGE_REIN);	// keine Anzeige der Fehlermeldung WC_MESSAGE_REIN

	if (KurzAnalyse (pIOG, trRicht, *plSInd))
		return S_OK;
	return E_FAIL;

} // ShortAnalysis


// --------------------------------------------------------------------------------------------
// Test zwischen den Geometrien des lONr1- und des lONr2-Objektes
STDMETHODIMP_ (HRESULT) GeoReinExtension :: InterObjectsAnalysis_ONr (LONG lONr1, LONG lONr2,
															ErrorTextMode etText, BOOL* pbSucc)
{
	_ASSERTE (lONr1 != 0);
	_ASSERTE (lONr1 != -1);
	_ASSERTE (lONr2 != 0);
	_ASSERTE (lONr2 != -1);

int iOT1 = DEX_GetObjectType (lONr1);
int iOT2 = DEX_GetObjectType (lONr2);

	if ((OT_KANTE != iOT1 && OT_FLAECHE != iOT1) ||
		(OT_KANTE != iOT2 && OT_FLAECHE != iOT2))
		return E_UNEXPECTED;	// Test nur für Linien und Flächenkonturen

ErrInstall EI (WC_MESSAGE_REIN);	// keine Anzeige der Fehlermeldung WC_MESSAGE_REIN

WObjektGeometrie wObj1, wObj2;		// ObjektGeometrie'n des lONr1- und des lONr2-Objektes

	try
	{
	WInitObjektGeometrie wIObj1 (CLSID_ObjektGeometrie);	// throws_com_error
	WInitObjektGeometrie wIObj2 (CLSID_ObjektGeometrie);	// throws_com_error

		THROW_FAILED_HRESULT (wIObj1->InitObjGeometry (lONr1));
		THROW_FAILED_HRESULT (wIObj2->InitObjGeometry (lONr2));

		wObj1 = wIObj1;
		wObj2 = wIObj2;
	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}

	return InterGeometryTest (wObj1, iOT1, wObj2, iOT2, etText, pbSucc);

} // InterObjectsAnalysis_ONr


// --------------------------------------------------------------------------------------------
// Test zwischen den Geometrien des pIOG1- und des pIOG2-Objektes
STDMETHODIMP_ (HRESULT) GeoReinExtension :: InterObjectsAnalysis_Geom (IObjektGeometrie* pIOG1,
								   IObjektGeometrie* pIOG2, ErrorTextMode etText, BOOL* pbSucc)
{
	_ASSERTE (pIOG1 != NULL);
	_ASSERTE (pIOG2 != NULL);

	return E_NOTIMPL;

} // InterObjectsAnalysis_Geom


// --------------------------------------------------------------------------------------------
// Eingeschränkte Bereinigung von Geometriefehlern (doppelte Punkte, Spitzen, Kollinearitäten
// und Umlaufsinn) an Linien- bzw. Flächenobjekten; vorrangig gedacht für Objekte, die in eine
// schreibgeschützte Datenquelle importiert werden;
// return-Werte sind
//   S_OK:		    pIOG wurde nicht verändert, d.h. war von vornherein fehlerfrei bzw. besitzt
//                  Fehler, die mit dieser Routine nicht geprüft werden, oder ist kein Linien-/
//                  Flächenobjekt
//   S_FALSE:	    pIOG hatte einen der o.g. Geometriefehler, die aber jetzt bereinigt sind
//   E_FAIL:        Test und Bereinigung konnte nicht durchgeführt werden, da ein Fehler
//                  aufgetreten ist
//   E_POINTER:     pIOG == NULL
//   E_OUTOFMEMORY: nicht genügend dynamischer Speicher
STDMETHODIMP_ (HRESULT) GeoReinExtension :: ReducedGeometryCleaning (IObjektGeometrie* pIOG)
{
	_ASSERTE (NULL != pIOG);

	if (! pIOG) return E_POINTER;

short iOT;

	pIOG->GetObjTyp (&iOT);

	if (OT_KANTE != iOT && OT_FLAECHE != iOT)
		return S_OK;	// nur Linien- bzw. Flächenobjekte

	// wenn pIOG-Koordinaten noch im double-Format sind, werden sie in IObjGeometrieInEObj() in
	// das KoOrd-Format umgewandelt; dazu wird CoordTransX() benötigt
	if (! m_pCT)
	{
	short iFlags;	// Modi von ModGI

		pIOG->GetFlags (&iFlags);

		if (iFlags & OGConverted)	// Koordinaten noch im double-Format
		{
			m_pCT = new CoordTransX();	// KoordinatenTransformation
			if (! m_pCT)
			{                                                                      
				DEX_Error (RC_GReinExt, EC_NOMEMORY);
				return E_OUTOFMEMORY;
			}
		}
	}

EObjekt* pEO = 0;	// zu testendes pIOG-Objekt

	if (!IObjGeometrieInEObj (pIOG, pEO, m_pCT))
	{
		DELETE_OBJ (pEO);
		return E_FAIL;
	}

HRESULT hrRet = S_OK;	// return-Wert dieser Routine

	if (OT_KANTE == iOT)
	{
		if (PartialCleaningForLines ((EKante*)pEO))	// Bereinigung vorgenommen
		{
			if (EObjInIObjGeometrie ((EKante*)pEO, pIOG))	// pIOG korrigieren
				hrRet = S_FALSE;
			else
				hrRet = E_FAIL;		// Korrektur fehlgeschlagen
		}
	}

	else	// OT_FLAECHE == iOT
	{
	EFlaeche* pFl = (EFlaeche*)pEO;
	int iKCnt = pFl->KantenAnz();

		for (int i = 0; i < iKCnt; i++)	// Konturen einzeln testen und ggf. bereinigen
			if (PartialCleaningForLines (&pFl->KA(i), i))	// Bereinigung vorgenommen
				hrRet = S_FALSE;

		if (S_FALSE == hrRet &&	!EObjInIObjGeometrie (pFl, pIOG))	// pIOG korrigieren
			hrRet = E_FAIL;		// Korrektur fehlgeschlagen
	}

	DELETE_OBJ (pEO);

	return hrRet;

} // ReducedGeometryCleaning




///////////////////////////////////////////////////////////////////////////////////////////////
// IAdjustValues-Methoden
// --------------------------------------------------------------------------------------------
// Rückgabe von einstellbaren Parametern
STDMETHODIMP_ (HRESULT) GeoReinExtension :: GetAdjustValue (AdjValue avKey, LONG* plValue)
{
	switch (avKey)
	{
		case REIN_AUTOCLEAR:	// automatische bzw. keine Bereinigung von Geometriefehlern,
								// die guten Gewissens auch automatisch bereinigt werden können
			if (m_bClear) *plValue = 1;
			else *plValue = 0;
			break;

		case REIN_DOUBLE:		// Grenzwert für Test auf "doppelte Punkte"
			*plValue = DtoL (10. * m_dDPEps);
			break;

		case REIN_ACUTEANGLE:	// Grenzwert für Test auf "Spitze"
			*plValue = DtoL (10. * m_dSpEps);
			break;

		case REIN_LOOP:			// min. Stützpunktanzahl für abzutrennende Schleife
			*plValue = m_iLoopLen;

		case REIN_VERTREDUCE:	// Wert für die Reduzierung der Stützpunktanzahl bei der
								// Polygonapproximation
			*plValue = DtoL (100. * m_dReduz);
			break;

		default:		// unzulässiger Key
			return E_INVALIDARG;
	}
	
	return S_OK;

} // GetAdjustValue


// --------------------------------------------------------------------------------------------
// Setzen von einstellbaren Parametern
STDMETHODIMP_ (HRESULT) GeoReinExtension :: SetAdjustValue (AdjValue avKey, LONG lValue)
{
	switch (avKey)
	{
		case REIN_DEFAULT:		// für alle Parameter die default-Werte einstellen
			m_bClear = bClear;
			m_dDPEps = dDopEps;
			m_dSpEps = dSpiEps;
			m_iLoopLen = iLoopLen;
			m_dReduz = dRedEps;
			break;

		case REIN_AUTOCLEAR:	// automatische bzw. keine Bereinigung von Geometriefehlern,
								// die guten Gewissens auch automatisch bereinigt werden können
			if (1 == lValue) m_bClear = true;
			else m_bClear = false;
			break;

		case REIN_DOUBLE:		// Grenzwert für Test auf "doppelte Punkte"
			m_dDPEps = lValue / 10.;
			break;

		case REIN_ACUTEANGLE:	// Grenzwert für Test auf "Spitze"
			m_dSpEps = lValue / 10.;
			break;

		case REIN_LOOP:			// min. Stützpunktanzahl für abzutrennende Schleifen
			m_iLoopLen = lValue;
			break;

		case REIN_VERTREDUCE:	// Wert für die Reduzierung der Stützpunktanzahl bei der
								// Polygonapproximation
			m_dReduz = lValue / 100.;
			break;

		default:		// unzulässiger Key
			return E_INVALIDARG;
	}
	
	return S_OK;

} // SetAdjustValue
