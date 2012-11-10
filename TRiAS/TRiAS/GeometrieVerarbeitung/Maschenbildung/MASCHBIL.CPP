/*
Datei: MASCHBIL.CPP

Maschenbildung auf der Grundlage eines Linienverfolgungsverfahrens:
Es werden solange Linien (Kante) in math. positiver/negativer Richtung vereinigt,
bis ein Masche (Fläche) ensteht, die an TRiAS ausgegeben wird und deren Objekt-
nummer im Ausgabestrom gespeichert wird.

Erarbeitet: J. Benkenstein							Stand vom: 15.10.1996
*/

#include "pheader.h"			// vorübersetzter Header
#include "resource.h"			// Resource-Konstanten

//	STL-Header
#include <ospace/std/list>		// list
#include <ospace/std/map>		// map
#include <ospace/std/algorithm>	// for_each 

//	TRiAS-Header
#include <IGeometr.hxx>			// IObjektGeometrie

//	GUID-Header
#include <objgguid.h>			// CLSID_ObjektGeometrie, IID_IInitObjektGeometrie
#include <operguid.h>			// CLSID_GeometrieOperationen
#include <eonrguid.h>
#include <triashelper.h>
#include <initguid.h>           
#include <reinguid.h>

//	Standard-Header
#include <ospace/com/smartif.h>			
#include <math.h>				// sin (), cos () ...
#include <float.h>				// DBL_MIN, DBL_MAX

//	Projekt-Header
#include "tools.hpp"			// FlaechenInhalt (), OutputFlaeche ()
#include "objkante.hpp"			// CObjektKante
#include "ParamDlg.hpp"			// CParameters

#include <hpp/progrsst.hpp>		// CProgressIndicator

#include "maschbil.hpp"			// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	Datentypen
// typedef subdomain<CObjektKantenListe, CMaschenBildung> viewlist_t;
// typedef viewlist_t::iterator viewlist_tit;
typedef map<double, CObjektKante *, less<double> > CObjektKantenMap_t;
typedef CObjektKantenMap_t::iterator CObjektKantenMap_tit;
typedef CMerkmalsListe::iterator CMerkmalsListe_it;


///////////////////////////////////////////////////////////////////////////////////////////////
struct MerkmalInfos 
{
	CMerkmalsListe *pListe;
	long lObjNr;			// Objektnummer eines "Eltern"-Objektes
	HPROJECT hPr;			// ProjectHandle des neu erzeugten Objektes
	BOOL bOutputMerkmal;	// Vererbung aller "Eltern"-Merkmale (true) oder nur des
							// UniqueIdent (false) (#WM990618)
};


///////////////////////////////////////////////////////////////////////////////////////////////
//	Konstanten
const short MaxMerkmalsLen = 255;			// max. Länge für UniqueIdent-Merkmal
const char MerkmalsSep [] = "/";			// Separator zweier Merkmale
const short MaxMaschUseCnt = MaxUseCnt - 1;	// max. Benutzung einer Kante, um Ausgangspunkt für
											// eine Masche zu sein

///////////////////////////////////////////////////////////////////////////////////////////////
// benötigte InterfaceWrapper
DefineSmartInterface (ExtendObjOper);
DefineSmartInterface (ConnectionPoint);
DefineSmartInterface (ConnectionPointContainer);
DefineSmartInterface (EnumLONG);


///////////////////////////////////////////////////////////////////////////////////////////////
// globale Funktionen
// alle Merkmalscodes ulMCode eines Objektes geben lassen und die Merkmalsinhalte in einer
// Liste sammeln; Sortierschlüssel ist der MerkmalsKurztext (wegen der Möglichkeit
// verschiedener Datenquellen NICHT mehr der Merkmalscode !) (#WM990616)
BOOL CALLBACK EnumMerkmaleProc (ULONG ulMCode, DWORD dwData, void *pData)
{
	ASSERT (NULL != pData);

MerkmalInfos *pInfo = (MerkmalInfos*) pData;

long lOrigONr = pInfo->lObjNr;					// Objektnummer und (#WM990616)
HPROJECT hPr = DEX_GetObjectProject (lOrigONr);	// ProjectHandle eines "Eltern"-Objektes
BOOL bOutputMerkmal = pInfo->bOutputMerkmal;	// alle Merkmale (true) oder nur UniqueIdent
												// (false) vererben (#WM990618)

#if _MSC_VER < 1200
	// die Einträge im Merkmal "OldObjUniqueIdent" werden nicht in die Liste mit übernommen
	if (ulMCode == DEX_GetOldUniqueIdentMCode() ||
		(!bOutputMerkmal && ulMCode != DEX_GetUniqueIdentMCode()))
#else
	// die Einträge der Merkmale "OldObjUniqueIdent" und "Eindeutige Objektkennung" werden
	// nicht in die Liste mit übernommen
	if (ulMCode == DEX_GetOldUniqueIdentMCodeEx (hPr) ||
		ulMCode == DEX_GetObjGuidMCode (DEX_GetObjIdent (lOrigONr)) ||
		(!bOutputMerkmal && ulMCode != DEX_GetUniqueIdentMCodeEx (hPr)))
#endif // _MSC_VER < 1200
	return TRUE;


// der Kurztext strMKTListe, unter dem der Text des ulMCode-Merkmals in der Liste abgespeichert
// wird, ist i.d.R. mit dem Kurztext des ulMCode-Merkmals identisch; nur für das Merkmal
// "UniqueIdent" werden die Texte gleich unter dem Kurztext "OldObjUniqueIdent" abgelegt;
// dies ist jetzt erforderlich, da die "Eltern"-Objekte aus verschiedenen Datenquellen
// stammen können und das neue Objekt in noch einer anderen Datenquelle abgespeichert sein kann
CString strMKTListe;

	// Kurztext des Merkmalscodes ulMCode ermitteln; auch wenn er nicht ermittelbar ist, kein
	// Abbruch der Enumeration, deshalb Rückgabe von TRUE
	if (false == GetKurzText (ulMCode, 'm', strMKTListe))
		return TRUE;	// Kurztext nicht ermittelbar

#if _MSC_VER < 1200
	if (ulMCode == DEX_GetUniqueIdentMCode() &&
		false == GetKurzText (DEX_GetOldUniqueIdentMCode(), 'm', strMKTListe))
#else
	if (ulMCode == DEX_GetUniqueIdentMCodeEx (hPr) &&
		false == GetKurzText (DEX_GetOldUniqueIdentMCodeEx (pInfo->hPr), 'm', strMKTListe))
#endif // _MSC_VER < 1200
		return TRUE;

//	ulMCode-Merkmal lesen
TARGETMERKMAL TM;

	memset (&TM, 0, sizeof (TARGETMERKMAL));
	TM.dwSize = sizeof (TARGETMERKMAL);
	TM.lTarget = pInfo->lObjNr;
	TM.lMCode = ulMCode;
	char Buffer [MaxMerkmalsLen] = "";
	TM.imaxLen = MaxMerkmalsLen-1;
	TM.iTTyp = TT_Objekt;
	TM.pMText = Buffer;         

//	wenn ulMCode-Merkmal am lOrigONr-Objekt vorhanden und belegt ...
	if (DEX_GetTextMerkmal (TM) && Buffer [0] != '\0')
	{
		ASSERT (NULL != pInfo -> pListe);

	CMerkmalsListe *pListe = pInfo -> pListe;
	CMerkmalsListe_it map_it;
	// der neu zu bildende Merkmalsinhalt wird am Anfang und am Ende mit dem Separator
	// ergänzt, um beim Test, ob dieser Merkmalstext schon vorhanden ist, nicht durch
	// "Untermengen"-Strings zu einer falschen Aussage zu kommen. In OutputMerkmale() werden
	// diese beiden Separatoren wieder entfernt (#WM990617)
	CString strInhaltMitSep = MerkmalsSep;

		strInhaltMitSep += Buffer;
		strInhaltMitSep += MerkmalsSep;

		// ... dann dieses Merkmal in der Map suchen
//		map_it = pListe->find (ulMCode);
		map_it = pListe->find (strMKTListe);

		if (map_it != pListe->end ())				//	Merkmal schon vorhanden
		{
		CString *pstrFind = &(*map_it).second;

			ASSERT (NULL != pstrFind);
//			if (pstrFind->Find (Buffer) >= 0)
			if (pstrFind->Find (strInhaltMitSep) >= 0)
				return TRUE;						//	Merkmalsinhalt schon vorhanden

			if (pstrFind->IsEmpty ())
//				*pstrFind = Buffer;
				*pstrFind = strInhaltMitSep;
			else
			{
//				if (Buffer [0] != MerkmalsSep [0])
//					*pstrFind += MerkmalsSep;
				*pstrFind += Buffer;
				*pstrFind += MerkmalsSep;
			}
		}
		else
		//	neuen Eintrag in Map erzeugen
//			pListe->insert (ulMCode, CString (Buffer));						
			pListe->insert (strMKTListe, strInhaltMitSep);						
	}
		
	return TRUE;
}


// --------------------------------------------------------------------------------------------
//	CMaschenBildung
CMaschenBildung::CMaschenBildung (CObjektKantenListe &InputListe,	//	STL-Liste der zu vereinigenden Kanten
								  WEnumObjectsByNumber &WEnumObjs,	//	Objektnummern-Ausgabe-Strom
								  CParameters &Params,				//	weitere Parameter
								  CObjektKante &InputKante)		//	Predikat-Kante
			   : m_InputListe (InputListe),
				 m_Params (Params),
				 m_PredikatKante (InputKante)
{
//	ggf. TRIAS-Merkmale lesen
	m_WEnumObjs = WEnumObjs;

	Reset ();					// allg. Parameter rücksetzen
}


// --------------------------------------------------------------------------------------------
//	allg. Parameter rücksetzen
void CMaschenBildung::Reset (void)
{
	m_dDrehWi = -1.0;			// akt. Drehwinkel auf ungültigen Wert setzen
	m_bDirection = TRUE;		// 1. Versuch ist immer math. positiv
}


// --------------------------------------------------------------------------------------------
//	liegen übergebene Punkte im Bereich der Fuzzy-Toleranze: Aspectratio berücksichtigen
BOOL CMaschenBildung::ImFangBereich (long lX1, long lY1, long lX2, long lY2)
{
// durch die Konvertierungen long -> double, double -> long in TRiAS kann es zu kleinen
// Differenzen kommen; deshalb nachfolgende Korrektur: auch wenn als Toleranz 0 vorgegeben
// ist, werden Punkte noch als gleich angesehen, wenn sich deren x- bzw. y-Koordinaten
// höchstens um ulEps (in pheader.h definiert) unterscheiden (#WM990622)
ULONG ulXFuzzy, ulYFuzzy;

	(m_Params.m_ulXFuzzy > 0) ? (ulXFuzzy = m_Params.m_ulXFuzzy) : (ulXFuzzy = ulEps);
	(m_Params.m_ulYFuzzy > 0) ? (ulYFuzzy = m_Params.m_ulYFuzzy) : (ulYFuzzy = ulEps);

	// return m_dFuzzy >= sqrt ((double)(((lX1-lX2)*(lX1-lX2)) + ((lY1-lY2)*(lY1-lY2))));
	return ((ULONG (labs (lX1 - lX2)) <= ulXFuzzy) && 
			(ULONG (labs (lY1 - lY2)) <= ulYFuzzy));
}


// --------------------------------------------------------------------------------------------
// die beiden Kanten haben im "Inneren" (d.h. ohne Beachtung der Endpunkte) eine Gemeinsamkeit
// (TRUE)
BOOL CMaschenBildung::Community (long* pXOld, long* pYOld, long lCntOld, long* pXNew,
								 long* pYNew, long lCntNew)
{
	for (long l1 = 0; l1 < lCntOld-1; l1++)
		for (long l2 = 0; l2 < lCntNew-1; l2++)
			if (Intersection (pXOld[l1], pYOld[l1], pXOld[l1+1], pYOld[l1+1],
							  pXNew[l2], pYNew[l2], pXNew[l2+1], pYNew[l2+1]))
			{
				if (0 == l1 && 0 == l2 && ImFangBereich (pXOld[0], pYOld[0], pXNew[0], pYNew[0])) // #WM991018
					continue;	// Gemeinsamkeit an jeweils einem  Endpunkt
				if (0 == l1 && lCntNew-2 == l2 &&
					ImFangBereich (pXOld[0], pYOld[0], pXNew[lCntNew-1], pYNew[lCntNew-1]))	// #WM991018
					continue;	// Gemeinsamkeit an jeweils einem  Endpunkt
				if (lCntOld-2 == l1 && 0 == l2 &&
					ImFangBereich (pXOld[lCntOld-1], pYOld[lCntOld-1], pXNew[0], pYNew[0]))	// #WM991018
					continue;	// Gemeinsamkeit an jeweils einem  Endpunkt
				if (lCntOld-2 == l1 && lCntNew-2 == l2 &&
					ImFangBereich (pXOld[lCntOld-1], pYOld[lCntOld-1], pXNew[lCntNew-1], pYNew[lCntNew-1]))	// #WM991018
					continue;	// Gemeinsamkeit an jeweils einem  Endpunkt

				return TRUE;
			}
	return FALSE;
}


// --------------------------------------------------------------------------------------------
//	Kanten vereinigen
//	InputFirst ist die zu vergrößernde Kante
BOOL CMaschenBildung::UnionLines (CObjektKante &InputFirst, CObjektKante &InputNext,
								  short sAppendType)								   
{
	switch (sAppendType)
	{
		case LastFirst:			// der herzustellende Standardfall
		break;
		case LastLast:
			InputNext.ChangeDirection ();
		break;
		case FirstLast:
		{
			InputFirst.ChangeDirection ();
			InputNext.ChangeDirection ();
		}
		break;
		case FirstFirst:
			InputFirst.ChangeDirection ();
		break;
		default:
		{
			ASSERT (FALSE);
			return FALSE;
		}
	}

//	Vereinigung durchführen
	return UnionKanten (InputFirst, InputNext, FALSE/*, TRUE*/);
}


// --------------------------------------------------------------------------------------------
//	Kanten vereinigen
BOOL CMaschenBildung::UnionKanten (CObjektKante &InputFirst, CObjektKante &InputNext, 
								   BOOL bCheckDirection/*, BOOL fUseGeoRein*/)
{
//	Geometrie der zu vergrößernden Kante lesen
	long lCnt = 0;
	long *pX = NULL;
	long *pY = NULL;

	InputFirst.GetGeometrie (&pX, &pY, &lCnt);
	ASSERT ((lCnt > 1) && (NULL != pX) && (NULL != pY));

//	die Koordinaten des 1. Punktes der alten/neuen Kante speichern
	long lLastX = pX [lCnt - 1];
	long lLastY = pY [lCnt - 1];

//	Geometrie der anzuhängenden Kante lesen
	InputNext.GetGeometrie (&pX, &pY, &lCnt);
	ASSERT ((lCnt > 1) && (NULL != pX) && (NULL != pY));

//	Richtung der anzuhängenden Kante ggf. tauschen
	if (bCheckDirection)
	{
		if (!ImFangBereich (lLastX, lLastY, pX[0], pY[0]))
			InputNext.ChangeDirection ();		// für spätere Richtungsbestimmung wichtig !
	}

// hier noch testen, ob die beiden Linien sich schneiden, wenn ja, dann Ende
//
// Vereinigung durchführen
	HRESULT hr = S_OK;

// wichtige Korrektur: der 1. Punkt der anzuhängenden Kante wird NICHT übernommen, da er im
// Normalfall gleich dem letzten der zu vergrößernden Kante sein müßte; sollten diese beiden
// Punkte nicht identisch sein, dann muß ihr Abstand aber im Fangbereich liegen; wenn die
// beiden dazugehörigen Strecken eine Lücke bilden, könnte man beide Punkte übernehmen; um aber
// auch den Fall abzufangen, daß die beiden dazugehörigen Strecken sich überschneiden, wird
// eben einer der beiden Punkte (nämlich der 1. Punkt der anzuhängenden Kante) nicht übernommen
// (#WM991018)
	for (long lIndex = 1; lIndex < lCnt; lIndex++)
	{
		hr = InputFirst.m_wIObjGeo -> AddPunkt (pX [lIndex], pY [lIndex], -1, -1);
		if (FAILED(hr))
			_com_issue_error (hr);
	}

	return TRUE;
}


// --------------------------------------------------------------------------------------------
//	Kann die Kante in eine Fläche umgewandelt werden
BOOL CMaschenBildung::CanCreateFlaeche (CObjektKante &Kante)
{
	long lCnt = 0;
	long *pX = NULL;
	long *pY = NULL;

//	lese Geometrie-Infos von Kante
	Kante.GetGeometrie (&pX, &pY, &lCnt);
	ASSERT ((NULL != pX) && (NULL != pY) && (lCnt > 1));

	return ((lCnt >= (MinAreaVerticeCnt-1)) &&
			ImFangBereich (pX [0], pY [0], pX [lCnt-1], pY [lCnt-1]));
}


// --------------------------------------------------------------------------------------------
//	Fläche erzeugen
void CMaschenBildung::CreateFlaeche (CObjektKante &Kante)
{
	long lCnt = 0;
	long *pX = NULL;
	long *pY = NULL;

//	lese Geometrie-Infos von Kante
	Kante.GetGeometrie (&pX, &pY, &lCnt);
	ASSERT ((NULL != pX) && (NULL != pY) && (lCnt > 1));

//	Repräsentiert diese Kante bereits eine Fläche
	if (IsFlaeche (pX, pY, lCnt))
		return;
	
	HRESULT hr = Kante.m_wIObjGeo -> AddPunkt (pX [0], pY [0], -1, -1);
	if (FAILED(hr))
		_com_issue_error (hr);
}


// --------------------------------------------------------------------------------------------
//	hat diese Fläche den richtigen Umlaufsinn ?
BOOL CMaschenBildung::DirectionOK (CObjektKante &Kante)
{
	long lCnt = 0;
	long *pX = NULL;
	long *pY = NULL;

//	lese Geometrie-Infos von Kante
	Kante.GetGeometrie (&pX, &pY, &lCnt);
	ASSERT ((NULL != pX) && (NULL != pY) && (lCnt > 1));

//	nur positiven Flächeninhalt berücksichtigen
	return (FlaechenInhalt (pX, pY, lCnt) > 0.0);
}


// --------------------------------------------------------------------------------------------
//	Objektmerkmale der Kante in m_MerkmalsListe sammeln
void CMaschenBildung::GetObjFeatures (CObjektKante &Kante, BOOL bOutputMerkmal)
{
//	lese Objektnummer der Kante
	long lObjNr = Kante.GetObjNummer ();
	ASSERT (lObjNr > 0);

ENUMLONGKEYEX key;

	memset (&key, 0, sizeof (ENUMLONGKEYEX));
	key.eKey = lObjNr;
	key.eFcn = (ENUMLONGKEYEXPROC)EnumMerkmaleProc;
	key.eData = MPObjectFeature;

MerkmalInfos Info;

	Info.pListe = &m_MerkmalsListe;
	Info.lObjNr = lObjNr;
	Info.hPr = m_Params.m_hPr;				// #WM990616
	Info.bOutputMerkmal = bOutputMerkmal;	// #WM990618
	key.ePtr = &Info;
	DEX_EnumObjektMerkmaleEx (key);
}


// --------------------------------------------------------------------------------------------
//	berechne "Anstieg" zwischen den beiden Strecken (lX1,lY1)-(lX2,lY2) und (lX2,lY2)-(lX3,lY3)
//	als Höhe des gedachten Dreiecks; wird TRUE zurück gegeben, haben die beiden Strecken nur
// (lX2,lY2) gemeinsam, anderenfalls überlappen sie sich
BOOL CMaschenBildung::Anstieg (long lX1, long lY1, long lX2, long lY2, long lX3, long lY3,
							   double& dAnstieg)
{
	if (labs (lX1 - lX3) <= ulEps && labs (lY1 - lY3) <= ulEps)
		return FALSE;	// Überlappung, beide Strecken sind ulEps-identisch

long lX [MinAreaVerticeCnt];
long lY [MinAreaVerticeCnt];

	lX [0] = lX1; lY [0] = lY1;
	lX [1] = lX2; lY [1] = lY2;
	lX [2] = lX3; lY [2] = lY3;
	lX [3] = lX1; lY [3] = lY1;

//	Flächeninhalt berechnen
//double dInhalt = fabs (FlaechenInhalt (&dX[0], &dY[0], MinAreaVerticeCnt));
double dInhalt = fabs (FlaechenInhalt (lX, lY, MinAreaVerticeCnt));

	if (0. == dInhalt)	// die 3 Punkte sind kollinear
	{
		// Strecken überlappen sich, (lX1,lY1)-(lX2,lY2) ist kürzer als (lX2,lY2)-(lX3,lY3)
		if ((lX2 <= lX1 && lX1 <= lX3) || (lX2 >= lX1 && lX1 >= lX3))
			return FALSE;

		if ((lY2 <= lY1 && lY1 <= lY3) || (lY2 >= lY1 && lY1 >= lY3))
			return FALSE;

		// Strecken überlappen sich, (lX1,lY1)-(lX2,lY2) ist länger als (lX2,lY2)-(lX3,lY3)
		if ((lX1 <= lX3 && lX3 <= lX2) || (lX1 >= lX3 && lX3 >= lX2))
			return FALSE;

		if ((lY1 <= lY3 && lY3 <= lY2) || (lY1 >= lY3 && lY3 >= lY2))
			return FALSE;

		dAnstieg = 0.;		// Strecken liegen hintereinander
		return TRUE;
	}

//	Höhe berechnen: h = 2 * A / c
//double dC = sqrt (((lX3-lX1)*(lX3-lX1)) + ((lY3-lY1)*(lY3-lY1)));
	// #AK990811 ... verhindern wir mal lieber 'nen Überlauf...
double dC = sqrt( ( (double)(lX3-lX1) * (double)(lX3-lX1) ) + ( (double)(lY3-lY1) * (double)(lY3-lY1) ) );

	ASSERT (dC != 0.);

	dAnstieg = (2. * dInhalt) / dC;

	if (DtoL (dAnstieg) <= ulEps)
		return FALSE;	// ulEps-Überlappung beider Strecken
	return TRUE;
}


// --------------------------------------------------------------------------------------------
//	können Linien vereinigt werden ?
short CMaschenBildung::CanLinesUnion (CObjektKante &NewKante)
{
//	lese Geometrie der neuen Kante
	long lCntNew = 0;
	long *pXNew = NULL;
	long *pYNew = NULL;

	NewKante.GetGeometrie (&pXNew, &pYNew, &lCntNew);
	ASSERT ((lCntNew > 1) && (NULL != pXNew) && (NULL != pYNew));

//	lese Geometrie der Predikat-Kante
	long lCntOld = 0;
	long *pXOld = NULL;
	long *pYOld = NULL;
	m_PredikatKante.GetGeometrie (&pXOld, &pYOld, &lCntOld);
	ASSERT ((lCntOld > 1) && (NULL != pXOld) && (NULL != pYOld));

//	Test, ob mindestens eine der beiden Kanten geschlossen ist; wenn ja, dann ist keine
//	Vereinigung möglich (#WM990921)
	if (pXOld[0] == pXOld[lCntOld-1] && pYOld[0] == pYOld[lCntOld-1])
		return NoAppend;
	if (pXNew[0] == pXNew[lCntNew-1] && pYNew[0] == pYNew[lCntNew-1])
		return NoAppend;

//	Test, ob die beiden Kanten im "Inneren" (d.h. ohne Beachtung der Endpunkte) eine
//	Gemeinsamkeit haben; wenn ja, dann ist keine Vereinigung möglich (#WM990622)
	if (Community (pXOld, pYOld, lCntOld, pXNew, pYNew, lCntNew))
	{
		NewKante.m_sAppendType = NoAppend;
		NewKante.m_dWi = DBL_MAX;
		return NoAppend;
	}


//	Return-Wert init.
short sRet = NoAppend;
double dAnstieg = DBL_MAX;

	if (ImFangBereich (pXOld[lCntOld-1], pYOld[lCntOld-1], pXNew[0], pYNew[0]) &&
		Anstieg (pXOld[lCntOld-2], pYOld[lCntOld-2], pXOld[lCntOld-1], pYOld[lCntOld-1],
				 pXNew[1], pYNew[1], dAnstieg))
		sRet = LastFirst;

	else if (ImFangBereich (pXOld[lCntOld-1], pYOld[lCntOld-1], pXNew[lCntNew-1],
							pYNew[lCntNew-1]) &&
			 Anstieg (pXOld[lCntOld-2], pYOld[lCntOld-2], pXOld[lCntOld-1], pYOld[lCntOld-1],
					  pXNew[lCntNew-2], pYNew[lCntNew-2], dAnstieg))
		sRet = LastLast;

	else if (ImFangBereich (pXOld[0], pYOld[0], pXNew[lCntNew-1], pYNew[lCntNew-1]) &&
			 Anstieg (pXOld[1], pYOld[1], pXOld[0], pYOld[0], pXNew[lCntNew-2],
					  pYNew[lCntNew-2], dAnstieg))
		sRet = FirstLast;

	else if (ImFangBereich (pXOld[0], pYOld[0], pXNew[0], pYNew[0]) &&
			 Anstieg (pXOld[1], pYOld[1], pXOld[0], pYOld[0], pXNew[1], pYNew[1], dAnstieg))
		sRet = FirstFirst;				

//	wenn möglicher Nachfolgepunkt gefunden
	NewKante.m_sAppendType = sRet;
	if (NoAppend != sRet)
	{
	//	Anstieg speichern
		NewKante.m_dWi = dAnstieg;
		m_PredikatKante.m_dWi = min (m_PredikatKante.m_dWi, dAnstieg);
	}
	else
		NewKante.m_dWi = DBL_MAX;

	return sRet;
}


// --------------------------------------------------------------------------------------------
//	Predikat: 
//	0. Objekt nicht mit sich selbst testen
//	1. Nur die Kanten, die innerhalb der Toleranz liegen, filtern.
//	2. Den Winkel berechnen und ggf. in beiden Kanten speichern
BOOL CMaschenBildung::IsKanteOK (CObjektKante &NewKante)
{
//	lese Geometrie der neuen Kante
	long lCntNew = 0;
	long *pXNew = NULL;
	long *pYNew = NULL;

	NewKante.GetGeometrie (&pXNew, &pYNew, &lCntNew);
	ASSERT ((lCntNew > 1) && (NULL != pXNew) && (NULL != pYNew));

//	lese Geometrie der Predikat-Kante
	long lCntOld = 0;
	long *pXOld = NULL;
	long *pYOld = NULL;
	m_PredikatKante.GetGeometrie (&pXOld, &pYOld, &lCntOld);
	ASSERT ((lCntOld > 1) && (NULL != pXOld) && (NULL != pYOld));
	
//	liegen Anfangs/Endpunkt der Folgelinie am Endpunkt der akt. Linie (im Fangbereich)
	BOOL bRet = FALSE;
	
//	wenn im Fangbereich, Winkelberechnung durchführen
	// ((CObjektKante &)NewKante).SetWinkelMin (m_bDirection);// Winkel auf jeden Fall rücksetzen
	
	long dA = pXOld[lCntOld-1];		// x/y-Verschiebung
	long dB = pYOld[lCntOld-1];		// hier wird nur vom Endpunkt aus geprüft
	int iIndex = 0;					// Vergleichsindex

//	teste Anfangspunkt
	bRet = ImFangBereich (dA, dB, pXNew[iIndex], pYNew[iIndex]);

//	ggf. noch Endpunkt testen
// u. z. nur, wenn die NewKante noch niemals eingebaut wurde (NewKante.m_sBuildCnt == 0); nach
// dem 1. Einbau hat sie die richtige Richtung und kann deshalb bei einem eventuellen 2. Einbau
// nur noch mit ihrem Anfangspunkt an die PredikatKante angehangen werden; deswegen wird eben
// nicht mehr getestet, ob der Endpunkt im Fangbereich liegt  (#WM991020)
	if (!bRet &&
		0 == NewKante.m_sBuildCnt)	// #WM991020
	{
		iIndex = lCntNew-1; 
		bRet = ImFangBereich (dA, dB, pXNew[iIndex], pYNew[iIndex]);
	}		

//	prüfe Ergebnis
	if (!bRet)
		return FALSE;

//	Translation und Rotation des gefundenen mögl. Fortsetzungspunktes
	double dXa = ((pXNew[iIndex] - dA) * cos (m_dDrehWi)) + ((pYNew[iIndex] - dB) * sin (m_dDrehWi));
	double dYa = (-(pXNew[iIndex] - dA) * sin (m_dDrehWi)) + ((pYNew[iIndex] - dB) * cos (m_dDrehWi));

//	Translation und Rotation des zu diesem Punkt gehörenden Folge/Vorgängerpunktes
	if (0 == iIndex)		// Index entsprechend setzen
		iIndex++;
	else
		iIndex--;
	double dXe = ((pXNew[iIndex] - dA) * cos (m_dDrehWi)) + ((pYNew[iIndex] - dB) * sin (m_dDrehWi));
	double dYe = (-(pXNew[iIndex] - dA) * sin (m_dDrehWi)) + ((pYNew[iIndex] - dB) * cos (m_dDrehWi));		

//	diese beiden Punkte bilden eine Strecke im neuen Koordinatensystem, deren Winkel zur X-Achse
//	jetzt berechnet werden soll
	NewKante.m_dWi = QuasiWinkel (dXa, dYa, dXe, dYe);
	
//	diesen Winkel ggf. speichern --> später als Key verwendet
	if (NewKante.m_dWi > m_PredikatKante.m_dWi) 						// bei math. pos. Richtung
		// (!m_bDirection && (NewKante.m_dWi < m_PredikatKante.m_dWi)))	// bei math. neg. Richtung
		m_PredikatKante.m_dWi = NewKante.m_dWi;

	return bRet;
}


// --------------------------------------------------------------------------------------------
//	Init. der akt. Kante und aller weiteren für die Suche wichtigen Parameter
void CMaschenBildung::InitSearch (CObjektKante &Kante, BOOL bDirection, BOOL bIgnoreChange,
								  BOOL bOutputMerkmal, BOOL bOutputParent)
{
//	"globale" Parameter init.
	// m_bDirection = bDirection;		// möglicher Umlaufsinn der zu bildenden Masche
	m_dDrehWi = -1.0;					// Drehwinkel wird für jede Kante neu berechnet
	//m_strUnIdent.Empty ();				// erstmal leeren	

//	ggf. Merkmale der 1. Kante lesen und speichern
	if (bOutputMerkmal || bOutputParent)
	{
		m_MerkmalsListe.clear ();		// lösche alte Merkmalsliste
		GetObjFeatures (Kante, bOutputMerkmal);
	}

//	Kantenspezifische Merkmale setzen
	Kante.SetWinkelMin (/*bDirection*/);	// Suchwinkel auf ungültigen Wert setzen	
	Kante.m_bIsInUnion = TRUE;				// diese Kante wird gerade vereinigt

//	ggf. Richtung der Kante ändern 
	if (!bIgnoreChange && !bDirection)
		Kante.ChangeDirection ();
}


// --------------------------------------------------------------------------------------------
//	Richtung schon durchlaufen ?
BOOL CMaschenBildung::KantenDirectionOK (CObjektKante &Kante)
{
long lCntOld = 0;
long *pXOld = NULL;
long *pYOld = NULL;

	m_PredikatKante.GetGeometrie (&pXOld, &pYOld, &lCntOld);
	ASSERT ((lCntOld > 1) && (NULL != pXOld) && (NULL != pYOld));

long lCnt = 0;
long *pX = NULL;
long *pY = NULL;

	Kante.GetGeometrie (&pX, &pY, &lCnt);
	ASSERT ((lCnt > 1) && (NULL != pX) && (NULL != pY));

	// bei einer inneren Kante, die schon einmal verwendet wurde, muß getestet werden, wie oft
	// sie nach dem 1. Einbau noch gedreht wurde, um nachfolgenden FangbereichsTest exakt
	// durchführen zu können; bei einer ungeraden Anzahl von Drehungen muß mit dem ANFANGSpunkt
	// der neuen Kante verglichen werden (#WM990701)
	if (FALSE == Kante.m_bAussenKante && 1 == Kante.m_sBuildCnt &&
		(Kante.m_iChangeCounter & 1))	// ungerade Anzahl
		return ImFangBereich (pX[0], pY[0], pXOld[lCntOld-1], pYOld[lCntOld-1]);

//	Endpunkte beider Kanten müssen im Fangbereich sein
	return ImFangBereich (pX[lCnt-1], pY[lCnt-1], pXOld[lCntOld-1], pYOld[lCntOld-1]);
}


// --------------------------------------------------------------------------------------------
//	Bildung der Maschen
//	kein try/catch
//BOOL CMaschenBildung::CreateMaschen (HPROJECT hPr, CProgressIndicator *pIndicator /*=NULL*/, 
HRESULT CMaschenBildung::CreateMaschen (HPROJECT hPr, CProgressIndicator *pIndicator /*=NULL*/, 
										BOOL bOutputMerkmal /*=TRUE*/)
{
// ProjectHandle setzen
	m_Params.m_hPr = hPr;

// Merkmalskode für UniqueIdent der urspünglichen Objekte bestimmen (#WM990623)
#if _MSC_VER < 1200
	m_Params.m_ulOldUnIdent = DEX_GetUniqueIdentMCode();
#else
	m_Params.m_ulOldUnIdent = DEX_GetUniqueIdentMCodeEx (hPr);
#endif // _MSC_VER < 1200

	ASSERT (0 != m_Params.m_ulOldUnIdent);
	ASSERT ((ULONG)-1 != m_Params.m_ulOldUnIdent);

//	prüfe interne Parameter
	if (m_InputListe.empty ())
		return S_FALSE;

long lPos = 1;
long lFlCnt = 0;
long lObjNr = -1;					// akt. Objektnummer
short sUnionType = NotUnion;		// Vereinigungstyp
int iUnionCnt = 0;					// Anzahl der Vereinigten
CObjektKantenList_tit list_it;		// Listiterator
CInitAllKanten AllKanten;			// Init. Klasse

//	Progress-Indicator akt.
CString strUndoFormat, strUndo;

	VERIFY (strUndoFormat.LoadString (IDS_OBJECT_UNDO_AREA));

//	ggf. Caption akt.
	if (pIndicator)
	{
	CString strCaption;

		VERIFY (strCaption.LoadString (IDS_CAPTION_STATUS_MASCH));
		if (pIndicator)
			pIndicator -> InitStatusDialog (m_InputListe.size (), strCaption);
	}

//	Merkmal in PBD erzeugen
	if (0 == m_Params.m_ulNewUnIdent || (ULONG)-1 == m_Params.m_ulNewUnIdent)	// #WM990618
	{
		m_Params.m_ulNewUnIdent = DEX_GetOldUniqueIdentMCodeEx(m_Params.m_hPr);
		if (0 == m_Params.m_ulNewUnIdent || (ULONG)-1 == m_Params.m_ulNewUnIdent)
			return E_UNEXPECTED;
	}

BOOL bIgnoreChanged = FALSE;
BOOL bRO = FALSE;	// Zieldatenquelle ist nicht schreibgeschützt

	for (list_it = m_InputListe.begin(); list_it != m_InputListe.end(); ++list_it, lPos++) {
	//	ggf. Progress-Indicator akt.
		if (pIndicator)	{
			pIndicator -> SetupStatus (lPos);
			if (pIndicator -> WasCanceled ())
				return E_FAIL;
		}

	//	Referenz auf akt. Kante speichern und init.
	CObjektKante *pActKante = &(*list_it);

#ifdef _DEBUG
		lObjNr = pActKante -> GetObjNummer ();
#endif
		if ((pActKante->m_sBuildCnt > MaxMaschUseCnt) ||
		   ((1 == pActKante->m_sBuildCnt) && pActKante->m_bAussenKante)) 
		    continue;							// kann kein Ausgangspunkt für eine neue Masche sein

	//	prüfe und setze Richtung dieser Kante
		if (1 == pActKante->m_sBuildCnt) {
		//	eine einmal verbaute Kante muß auf jeden Fall entgegen der Baurichtung (und nur noch einmal)
		//	verarbeitet werden
			m_bDirection = FALSE;				//	nur noch ein Durchlauf

			if (pActKante -> m_bIsDirChanged == pActKante -> m_bIsDirChangedArea)
				pActKante -> ChangeDirection ();
			bIgnoreChanged = TRUE;				//	Richtung bei InitSearch nicht ändern
		} else {
			m_bDirection = TRUE;
			bIgnoreChanged = FALSE;
		}

		AllKanten.m_bIncBuildCnt = FALSE;		// Anzahl BuildCnt nicht erhöhen
		AllKanten.m_bResetIsInUnion = TRUE;		// dieses Flag bei Kanten rücksetzen

	//	Init. der akt. Kante und aller weiteren für die Suche wichtigen Parameter
	//	jede der einzelnen Kanten kann max. 2 mal zur Bildung einer Masche beitragen,
	//	wobei zuerst versucht wird, in math. positiver Richtung eine solche zu bilden
		InitSearch (*pActKante, m_bDirection, bIgnoreChanged, bOutputMerkmal);	
		
	//	jetzt beginnt die eigentliche Maschenbildung, d.h., daß Vereinigen von Linien, bis eine
	//	Fläche entsteht, die in angegebener Richtung orientiert ist
		m_PredikatKante = *pActKante;			// Vereinigte Kante
		iUnionCnt = 1;							// bisher eine Kante

	//	Ist diese Kante bereits eine Fläche: Setze sUnionType
		sUnionType = CanCreateFlaeche (m_PredikatKante) ? FlaechenUnion : NotUnion;
		if (FlaechenUnion == sUnionType)		//	Fläche erzeugen: Anfangspunkt als Endpunkt hinzufügen
		{
			CreateFlaeche (m_PredikatKante);	//	Richtung braucht bei einzelner Kante nicht geprüft werden
			m_PredikatKante.m_sBuildCnt++;
		}

	CObjektKante UnionKante;				// Vereinigungskante
		
	//	innerhalb  dieser Schleife erfolgt das Vereinigen der Kanten, bis eine Masche entsteht
		while (FlaechenUnion != sUnionType)
		{
		//	Vergleichskante init.
			m_PredikatKante.SetWinkelMin (/*m_bDirection*/);			// Suchwinkel auf ungültigen Wert setzen
			
		//	berechne Drehwinkel des 1. Segments der Kante zur x-Achse
			m_dDrehWi = m_PredikatKante.GetDrehWinkel ();				

		//	Suchvar. init.
			CObjektKantenMap_t Map;								// Ergebnismap
			CObjektKantenMap_tit map_it;						// Mapiterator

		//	Kantenliste init.
			AllKanten.m_bDirection = m_bDirection;				// akt. Richtung übergeben
			if (FlaechenUnion != sUnionType)					
				for_each (m_InputListe.begin(), m_InputListe.end(), AllKanten);
				
			pActKante -> m_bIsInUnion = TRUE;					// wird immer gerade benutzt
			
		//	alle möglichen Folgestrecken der akt. Kante speichern
		CObjektKantenList_tit Iter (list_it);

			for (Iter = m_InputListe.begin(); Iter != m_InputListe.end(); ++Iter)
			{
#ifdef _DEBUG
				CObjektKante Kante = (*Iter);
				long lObjNr1 = Kante.GetObjNummer ();
#endif
				if ((*Iter).m_bIsInUnion ||				// diese Kante wird gerade vereinigt oder 
				   ((*Iter).m_sBuildCnt >= MaxUseCnt))	// wurde schon 2 mal verwendet
					continue;

				if (IsKanteOK ((*Iter)))
					Map.insert ((*Iter).m_dWi, &(*Iter));		// nur Zeiger speichern
			}
				
		//	wenn wenigstens eine Kante vorhanden, dann Vereinigung durchführen
			if (Map.empty ())
			//	keine Folge-Kante gefunden: auch hier ist eine Suche in umgekehrter Richtung notwendig	
				sUnionType = NotUnion;							// keine Kante 
			else
			{
				map_it = Map.find (m_PredikatKante.m_dWi);		// suche zugeh. Folgekante
				ASSERT (map_it != Map.end ());
				CObjektKante *pNextKante = (*map_it).second;	// Zeiger speichern
				ASSERT (NULL != pNextKante);
#ifdef _DEBUG
			long lObjNr2 = pNextKante -> GetObjNummer ();
#endif
			//	Richtung schon durchlaufen ?
				if ((1 == pNextKante->m_sBuildCnt) &&	
					(pNextKante->m_bAussenKante || !KantenDirectionOK (*pNextKante)))		
					sUnionType = NotUnion;
				else
				{
					pNextKante -> m_bIsInUnion = TRUE;				// wird gerade vereinigt
				
				//	Merkmale der Folgekante speichern
					if (bOutputMerkmal)
						GetObjFeatures (*pNextKante, bOutputMerkmal);

				//	Vereinigung der Kanten durchführen
					UnionKante = m_PredikatKante;						//	Klassenparameter kopieren
					UnionKante.InitObjectGeometrie (m_PredikatKante);	//	Geoemetrie kopieren	
					VERIFY (UnionKanten (UnionKante, *pNextKante));
					m_PredikatKante = UnionKante;					
					iUnionCnt++;										// eine Kante ist dazu gekommen
				
				//	Kann diese Kante in eine Fläche umgewandelt werden ?
					if (CanCreateFlaeche (m_PredikatKante))
					{
						CreateFlaeche (m_PredikatKante);	// Fläche erzeugen: Anfangspunkt als Endpunkt hinzufügen

						if (DirectionOK (m_PredikatKante))	// Orientierung der Fläche enstpr. Vorgabe ?
							sUnionType = FlaechenUnion;
						else	
							//	es konnte eine Fläche gebildet werden, aber der Umlaufsinn war falsch,
							//	d.h., es muß versucht werden, mit der 1. Kante in umgekehrter Richtung eine solche zu bilden
						{
							AllKanten.m_bSetAussenKante = TRUE;
							for_each (m_InputListe.begin(), m_InputListe.end(), AllKanten);		
							AllKanten.m_bSetAussenKante = FALSE;
							sUnionType = NotUnion;															
						}
					}
					else
						sUnionType = LinienUnion;			// Linien wurden vereinigt: weiter mit der Suche
				}
			}
			
		//	Auswertung der Vereinigung und ggf. Neu-Init.
			if (NotUnion == sUnionType)
			{
				AllKanten.m_bIncBuildCnt = FALSE;		// Anzahl BuildCnt nicht erhöhen
				AllKanten.m_bResetIsInUnion = TRUE;		// dieses Flag bei Kanten rücksetzen
				
				if ((1 == m_PredikatKante.m_sBuildCnt) ||	// hier kein 2. Versuch
				    (FALSE == m_bDirection))			// wenn schon beim 2. Versuch,
				{
					for_each (m_InputListe.begin(), m_InputListe.end(), AllKanten);		
					AllKanten.m_bResetIsInUnion = FALSE;		
					break;								// dann weiter mit der nächsten Kante	
				}
				m_bDirection = FALSE; 
				InitSearch (*pActKante, m_bDirection, FALSE, bOutputMerkmal);	// Init. aller Parameter
				m_PredikatKante = *pActKante;			// die 1. Kante wird wieder als 1. benutzt
				iUnionCnt = 1;							// #WM991020
			}
			else
				if (LinienUnion == sUnionType)
				{
					AllKanten.m_bIncBuildCnt = FALSE;		// Anzahl BuildCnt nicht erhöhen
					AllKanten.m_bResetIsInUnion = FALSE;	// dieses Flag bei Kanten nicht rücksetzen
				}
		}		// end_while

	//	ggf. Masche ausgeben
		if (FlaechenUnion == sUnionType)
		{
		//	Objekt-UNDO beginnen
			strUndo.Format (strUndoFormat, ++lFlCnt);
			DEX_BeginUndoLevel ((const char*)strUndo);

		//	Geometrie und UniqueIdent an TRiAS ausgeben
			if (1 == iUnionCnt)
			{
				CObjektKante Kante (m_PredikatKante);
				Kante.InitObjectGeometrie (m_PredikatKante);	//	Geoemetrie kopieren	
				lObjNr = Kante.OutputFlaeche (m_Params.m_hPr, bRO);
			}
			else
				lObjNr = m_PredikatKante.OutputFlaeche (m_Params.m_hPr, bRO);

			if (bRO)	// #WM990713
				return ERROR_WRITE_PROTECT;
#ifdef _DEBUG
			TRACE3 ("Fläche %ld, Richtung: %d, Objektnummer: %ld\n", lFlCnt, m_bDirection, lObjNr);
#endif
			if (lObjNr > 0)		//	nur wenn TRiAS diese Fläche mag
			{
			//	alle Merkmale der Vereinigten ausgeben
				OutputMerkmale (lObjNr);	// #WM990622
				OutputUniqueIdent (lObjNr, m_Params.m_ulOldUnIdent);	// UniqueIdent immer ausgeben

			//	Objekt-Nummer im Ausgabe-Strom speichern
				m_WEnumObjs->AddItem (lObjNr);

				DEX_EndUndoLevel ();
			}
			else
				DEX_CancelUndoLevel (TRUE);
			
		//	Flag Vereinigte in Anzahl benutzte umwandeln und Vereinigte rücksetzen
		//	auch eine nicht an TRiAS ausgegebene Fläche wird nicht mehr behandelt
		//	Spezialfall: Fläche besteht nur aus der Ausgangslinie
			/*
			if (1 == sUnionCnt)			
			{
				pActKante -> m_bIsInUnion = FALSE;
				if (lObjNr > 0)				//	nur wenn wirklich eine Fläche gebildet wurde
					pActKante -> m_sBuildCnt++;
				else
					pActKante -> m_bIsInUnion = FALSE;
			}
			else
			{
			*/
			AllKanten.m_bIncBuildCnt = lObjNr > 0;			// Anzahl BuildCnt erhöhen, wenn Fläche in TRiAS ausgegeben
			AllKanten.m_bResetIsInUnion = TRUE;				// dieses Flag bei Kanten rücksetzen
			AllKanten.m_bDirection = m_bDirection;			// akt. Richtung übergeben
			for_each (m_InputListe.begin(), m_InputListe.end(), AllKanten);		// muß jetzt gemacht werden
			AllKanten.m_bIncBuildCnt = FALSE;				//	Flags wieder zurücksetzen
			AllKanten.m_bResetIsInUnion = FALSE;
			//}
		}	//	end_if
	}		//	end_for		  

//	return TRUE;
	return S_OK;
}			//	end_function


// --------------------------------------------------------------------------------------------
//	interne Linien-Vereinigung
int CMaschenBildung::CreateUnionLines (CInitAllKanten *pAllKanten, CObjektKante &ActKante,
									   BOOL bOutputMerkmal, BOOL bOutputParent,
									   CObjektKante **ppLastKante)
{	
	ASSERT (NULL != pAllKanten);

//	Init.
CObjektKante UnionKante;
int iUnionCnt = 1;						// eine Kante bis Dato bearbeitet

	InitSearch (ActKante, m_bDirection, FALSE, bOutputMerkmal, bOutputParent);	
	m_PredikatKante = ActKante;			// Vereinigte Kante
	
//	ggf. letzte Kante merken
	if (ppLastKante)
		*ppLastKante = &ActKante;

//	Kantenfeld init.
	pAllKanten->m_bIncBuildCnt = FALSE;			// Anzahl BuildCnt nicht erhöhen
	pAllKanten->m_bResetIsInUnion = TRUE;		// dieses Flag bei Kanten rücksetzen
	for_each (m_InputListe.begin(), m_InputListe.end(), *pAllKanten);

//	innerhalb  dieser Schleife erfolgt das Vereinigen der Kanten, 
//	bis keine weitere mehr gefunden wird
short sUnionType = LinienUnion;

	while (NotUnion != sUnionType) {
		ActKante.m_bIsInUnion = TRUE;					// akt. Kante wird immer gerade benutzt
		m_PredikatKante.m_dWi = DBL_MAX;				// Anstiegshöhe init.

	//	suche eine mögliche Folgekante vom Anfang/Ende der akt. Kante, 
	//	die die kleinste Richtungsänderung hat 
	CObjektKantenMap_t Map;								// Ergebnismap
	CObjektKantenMap_tit map_it;						// Mapiterator

	CObjektKantenList_tit list_it;		//	Listiterator
	CObjektKantenList_tit Iter;

		for (Iter = m_InputListe.begin(); Iter != m_InputListe.end(); ++Iter) {
	#ifdef _DEBUG
		CObjektKante Kante = (*Iter);
		long lObjNr = Kante.GetObjNummer ();
	#endif
			if ((*Iter).m_bIsInUnion ||			// diese Kante wird gerade vereinigt oder
			   ((*Iter).m_sBuildCnt > 0))		// wurde schon mindestens einmal verwendet
				continue;

		//	kann Linie angehängt werden
			if (NoAppend != CanLinesUnion ((*Iter)))
				Map.insert ((*Iter).m_dWi, &(*Iter));			// nur Zeiger speichern					
		}
			
	//	Folgekante gefunden ?
		if (Map.empty ())
			sUnionType = NotUnion;								// nein, diese Kante ausgeben
		else {
			map_it = Map.find (m_PredikatKante.m_dWi);			// suche zugeh. Folgekante
			ASSERT (map_it != Map.end ());
			CObjektKante *pNextKante = (*map_it).second;		// Zeiger speichern
			ASSERT (NULL != pNextKante);
	#ifdef _DEBUG
			long lObjNr1 = pNextKante -> GetObjNummer ();
	#endif
		BOOL fOldState = pNextKante -> m_bIsInUnion;

			pNextKante -> m_bIsInUnion = TRUE;					// wird gerade vereinigt
			
		//	Vereinigung der Kanten durchführen
			UnionKante = m_PredikatKante;						//	Klassenparameter kopieren
			UnionKante.InitObjectGeometrie (m_PredikatKante);	//	Geoemetrie kopieren	

			if (!UnionLines (UnionKante, *pNextKante, pNextKante->m_sAppendType)) {
			// Vereinigung würde zu Selbstinzidenz führen, also abbrechen
				sUnionType = NotUnion;
				pNextKante -> m_bIsInUnion = fOldState;			// war doch nichts
				break;
			}

		//	ggf. Merkmale der 2., 3. usw. Kante (Folgekante) speichern
			if (bOutputMerkmal || bOutputParent)
				GetObjFeatures (*pNextKante, bOutputMerkmal);

			m_PredikatKante = UnionKante;						

		//	ggf. letzte Kante merken
			if (ppLastKante)
				*ppLastKante = pNextKante;
			
			iUnionCnt++;						// Kantenzähler erhöhen
		}
	}		// end_while
	return iUnionCnt;
}


// --------------------------------------------------------------------------------------------
//	führe Linienvereinigung durch
//BOOL CMaschenBildung::CreateLines (HPROJECT hPr, CProgressIndicator *pIndicator,
HRESULT CMaschenBildung::CreateLines (HPROJECT hPr, CProgressIndicator *pIndicator,
									  BOOL bOutputMerkmal)
{
// ProjectHandle setzen
	m_Params.m_hPr = hPr;

// Merkmalskode für UniqueIdent der urspünglichen Objekte bestimmen (#WM990623)
#if _MSC_VER < 1200
	m_Params.m_ulOldUnIdent = DEX_GetUniqueIdentMCode();
#else
	m_Params.m_ulOldUnIdent = DEX_GetUniqueIdentMCodeEx (hPr);
#endif // _MSC_VER < 1200

	ASSERT (0 != m_Params.m_ulOldUnIdent);
	ASSERT ((ULONG)-1 != m_Params.m_ulOldUnIdent);

//	prüfe interne Parameter
	if (m_InputListe.empty ())
		return S_FALSE;

	long lObjNr = -1;					//	akt. Objektnummer
	int iUnionCnt = 0;					//	Anzahl der akt. Vereinigten
	short sUnionType = NotUnion;		//	Vereinigungstyp
	CObjektKantenList_tit list_it;		//	Listiterator

	CInitAllKanten AllKanten;			//	Init. Klasse
	AllKanten.m_bSetWinkelMin = FALSE;	//	Winkel bei Kanten nicht init.
	AllKanten.m_bResetIsInUnion = TRUE;	// dieses Flag bei Kanten rücksetzen
	for_each (m_InputListe.begin(), m_InputListe.end(), AllKanten);

	long lLineCnt = 0;

//	Progress-Indicator akt.
	CString strCaption, strUndoFormat, strUndo;
	VERIFY (strUndoFormat.LoadString (IDS_OBJECT_UNDO_LINIE));
	VERIFY (strCaption.LoadString (IDS_CAPTION_STATUS_LINES));
	if (pIndicator)
		pIndicator -> InitStatusDialog (m_InputListe.size (), strCaption);
	long lPos = 1;			// akt. Position

//	ggf. Merkmal in PBD ausgeben
	if (0 == m_Params.m_ulNewUnIdent || (ULONG)-1 == m_Params.m_ulNewUnIdent)	// #WM990618
	{
		m_Params.m_ulNewUnIdent = DEX_GetOldUniqueIdentMCodeEx(hPr);
		if (0 == m_Params.m_ulNewUnIdent || (ULONG)-1 == m_Params.m_ulNewUnIdent)
			return E_UNEXPECTED;
	}

HRESULT hrRet = S_OK;

	try
	{
		m_bDirection = TRUE;	// Richtung spielt hier keine Rolle

	//	Verschnitt Interface besorgen
		WExtendObjOper wObjOper;
		ASSERT (NULL != g_pTE);
		HRESULT hr = g_pTE -> m_pXtnSite -> GetXtension (CLSID_GeometrieOperationen, 
														 IID_IExtendObjOper, wObjOper.ppv ());
		if (FAILED(hr)) _com_issue_error(hr);

	BOOL bRO = FALSE;	// Zieldatenquelle ist nicht schreibgeschützt

		for (list_it = m_InputListe.begin(); list_it != m_InputListe.end(); ++list_it, lPos++)
		{
		//	ggf. Progress-Indicator akt.
			if (pIndicator)
			{
				pIndicator -> SetupStatus (lPos);
				if (pIndicator -> WasCanceled ())
					return E_FAIL;
			}
			
		//	Referenz auf akt. Kante speichern und init.
			CObjektKante *pActKante = &(*list_it);
			if (pActKante->m_sBuildCnt > 0)			// nur nicht benutzte Linien vereinigen
				continue;							

#if _MSC_VER < 1200
			//	Progress-Indicator mit Objektnummer aktualisieren (#WM990413)
			if (pIndicator)
				pIndicator -> SetObjNr (pActKante->GetObjNummer());
#endif

		//	vereinige Linien 
			CObjektKante *pLastKante = NULL;
			int iUnionCnt = CreateUnionLines (&AllKanten, *pActKante, FALSE, FALSE,
											  &pLastKante);

		//	ggf. jetzt nochmal vereinigen, u. z. beginnend mit der letzten Linie pLastKante,
		//	weil die Linie pActKante, mit der beim ersten Mal begonnen wurde, mitten drin in
		//	einem vereinigungsfähigen Bereich liegen kann; mit dem 2. Versuch wird nun dieser
		//	Bereich komplett zusammengefaßt
			if (iUnionCnt > 1)	// mindestens 2 Linien vereinigt
			{
				ASSERT (NULL != pLastKante);

				iUnionCnt = CreateUnionLines (&AllKanten, *pLastKante, bOutputMerkmal, TRUE);

				ASSERT (iUnionCnt > 1);
			}

		//	ggf. Linie an TRIAS ausgeben
			if (iUnionCnt > 1)
			{
			//	Objekt-UNDO beginnen
				strUndo.Format (strUndoFormat, ++lLineCnt);
				DEX_BeginUndoLevel ((const char*)strUndo);

			//	auch bei Geofehler ausgeben
				lObjNr = m_PredikatKante.Output (m_Params.m_hPr, bRO, sLineOutputFlags);

				if (bRO)	// #WM990713
					return ERROR_WRITE_PROTECT;
#ifdef _DEBUG
				TRACE2 ("Linie %ld, Objektnummer: %ld\n", lLineCnt, lObjNr);
#endif
				if (lObjNr <= 0)
					DEX_CancelUndoLevel (TRUE);			//	UNDO Canceln
				else
				{
					DEX_EndUndoLevel ();				//	UNDO beenden

				//	Geofehler ?
					if (S_OK != m_PredikatKante.m_wIObjGeo -> IsClear ())
					{
					//	Linie zerschneiden
						WEnumObjectsByNumber WEnumInObjs (CLSID_EnumObjectsByNumber);
						WEnumInObjs -> AddItem (lObjNr);
						WEnumLONG wInput (WEnumInObjs), wEnumOutObjs;
						HRESULT hr = wObjOper -> Splitting (wInput, 0, 0, 0, 
															wEnumOutObjs.ppi(), NULL);
					
					//	alte vereinigte Linie Löschen
						if (FAILED (hr))
							_com_issue_error(hr);

					//	Objekt löschen
						m_PredikatKante.DeleteGeometrie ();

					//	an alle erzeugten Objekte Merkmale ausgeben
						for (wEnumOutObjs->Reset(); S_OK == wEnumOutObjs->Next (1, &lObjNr, NULL);) 
						{
							OutputUniqueIdent (lObjNr, m_Params.m_ulOldUnIdent);

						//	alle Merkmale der Vereinigten ausgeben
							OutputMerkmale (lObjNr);	// #WM990618
						}
					
					//	Objektnummern in Ausgabe-Strom speichern
						for (wEnumOutObjs->Reset(); S_OK == wEnumOutObjs->Next (1, &lObjNr, NULL);) 
							m_WEnumObjs->AddItem (lObjNr);
					}
					else
					{
						DEX_EndUndoLevel ();		//	UNDO beenden

					//	Ausgabe des UniqueIdent
						OutputUniqueIdent (lObjNr, m_Params.m_ulOldUnIdent);

					//	alle Merkmale der Vereinigten ausgeben
						OutputMerkmale (lObjNr);	// #WM990618

						m_WEnumObjs->AddItem (lObjNr);
					}
				}

			//	Flag Vereinigte in Anzahl benutzte umwandeln und Vereinigte rücksetzen
			//	auch eine nicht an TRiAS ausgegebene Linie wird nicht mehr behandelt
			//	Spezialfall: Linie besteht nur aus der Ausgangslinie
				AllKanten.m_bIncBuildCnt = lObjNr > 0;	// Anzahl BuildCnt erhöhen, wenn Linie gebildet wurde
				AllKanten.m_bResetIsInUnion = TRUE;		// dieses Flag bei Kanten rücksetzen
			}	//	end_if
			else
			{
				AllKanten.m_bIncBuildCnt = FALSE;		// Flags wieder zurücksetzen
				AllKanten.m_bResetIsInUnion = TRUE;		// dieses Flag bei Kanten rücksetzen
			}

		//	Flags an Kanten speichern
			for_each (m_InputListe.begin(), m_InputListe.end(), AllKanten);		
		}		//	end_for		  

		if (0 == iUnionCnt)					// #WM990923
			hrRet = S_FALSE;	// keine Vereinigung
	}
	catch (_com_error& e)
	{
		DEX_Error (RC_Maschenbildung, EC_SYSERROR);
		hrRet = _COM_ERROR (e);
	}			
	catch (CUserException *ue)
	{
		ue -> Delete ();	//	Abbruch
		hrRet = E_FAIL;
	}

	return hrRet;
}


// --------------------------------------------------------------------------------------------
//	alle Merkmale eines Objekts ausgeben
void CMaschenBildung::OutputMerkmale (long lObjNr)
{
	if (m_MerkmalsListe.empty ())
		return;

CMerkmalsListe_it map_it;					// Iterator von m_MerkmalsListe
CString strMInhalt;							// Merkmalsinhalt und
ULONG ulIdent = DEX_GetObjIdent (lObjNr);	// Identifikator des neuen Objektes

	for (map_it = m_MerkmalsListe.begin(); map_it != m_MerkmalsListe.end(); map_it++)
	{
	CString strKText = (*map_it).first;	// Kurztext

		strMInhalt = (*map_it).second;	// Merkmalsinhalt

		// der 1. und letzte Separator des neu gebildeten Merkmalsinhaltes entfernen (diese
		// wurden bewußt hinzugenommen, um beim Test, ob dieser Merkmalstext schon vorhanden
		// ist, nicht durch "Untermengen"-Strings zu einer falschen Aussage zu kommen 
		strMInhalt = strMInhalt.Mid (1, strMInhalt.GetLength()-2);

#if _MSC_VER < 1200
	ULONG ulMCode = DEX_GetMCodeFromFeatureName ((const char*)strKText);

		ASSERT (0 != ulMCode);
		ASSERT ((ULONG)-1 != ulMCode);

		OutputMerkmal (lObjNr, ulMCode, (const char*)strMInhalt)
#else
	ErrCode EC = EC_OKAY;	// return-Wert von CreateMerkmal()
	ULONG ulMCode = DEX_GetMCodeFromFeatureNameEx (m_Params.m_hPr, (const char*)strKText);

		// Merkmal strKText existiert noch nicht in der Zieldatenquelle
		if (0 == ulMCode || (ULONG)-1 == ulMCode)
		{
			// neuen Merkmalscode geben lassen und Merkmal in PBD anlegen
			ulMCode = DEX_GetUniqueMCode();
			EC = CreateMerkmal (ulIdent, ulMCode, (char*)(const char*)strKText,
								strKText.GetLength()+1, false, false);
		}

		if (EC_OKAY == EC)
			OutputMerkmal (lObjNr, ulMCode, (const char*)strMInhalt);
#endif // _MSC_VER < 1200
	}
}
