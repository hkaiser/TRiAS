/*
Datei: OBJKANTE.CPP

Das Modul stellt elementare Datenstrukturen und Methoden zur Realisierung
der Linienverfolgung bereit.

Erarbeitet: J.Benkenstein		Stand vom: 15. Oktober 1996
*/

#include "pheader.h"			// vorübersetzte Header
#include "resource.h"			// Ressource-Konstanten

//	GUID-Header
#include <xtsnguid.h>
#include <initguid.h>           
#include <objgguid.h>			//	CLSID_ObjektGeometrie, IID_IInitObjektGeometrie

//	TRiAS-Header
#include <IGeometr.hxx>			//	IObjektGeometrie
#include <xtensnx.h>			//	DEX_DeleteObject ()

//	STL-Header
#include <ospace/com/smartif.h>			

//	allg. Header
#include <math.h>				//	asin ()
#include <float.h>				//	DBL_MIN, DBL_MAX

//	Projekt-Header
#include "objkante.hpp"			//	zugeh. Header
#include "tools.hpp"			//	OutputMerkmal (#HK971218)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// enum Direction { NoDirection = -1, Positiv = TRUE, Negativ = FALSE };



// --------------------------------------------------------------------------------------------
//	CInitAllKanten
void CInitAllKanten :: operator ()(CObjektKante &Kante)
{
	if (m_bSetAussenKante)
	{
		if (Kante.m_bIsInUnion)
			Kante.m_bAussenKante = TRUE;

		return;
	}

//	erhöhe Anzahl BuildCnt bei gerade vereinigten
	if (m_bIncBuildCnt && Kante.m_bIsInUnion)
	{
	//	eine Kante darf nicht mehr als 2 mal benutzt worden sein
		ASSERT (Kante.m_sBuildCnt < MaxUseCnt);
		Kante.m_sBuildCnt++; 

	//	Richtung setzen
		Kante.m_bIsDirChangedArea = Kante.m_bIsDirChanged;
	}

//	dieses Flag ggf. setzen
	if (m_bResetIsInUnion)
		Kante.m_bIsInUnion = FALSE;

//	Winkel rücksetzen	
	if (m_bSetWinkelMin)
		Kante.SetWinkelMin (/*m_bDirection*/);
}


// --------------------------------------------------------------------------------------------
DefineSmartInterface (InitObjektGeometrie);
//	CObjektKante
// Interface und Abmaße Erzeugen --> kein try/catch
CObjektKante::CObjektKante (long lObjNr)	
{
	ASSERT (lObjNr > 0);

	m_bIsDirChanged = FALSE;
	m_iChangeCounter = 0;	// #WM990701
	m_bIsDirChangedArea = FALSE;
	m_bIsInUnion = FALSE;
	m_sBuildCnt = 0;
	m_dWi = -1.0;			// ungültiger Wert
	m_bAussenKante = FALSE;
	m_sAppendType = NoAppend;
	
//	Objekt im Speicher erzeugen
	WInitObjektGeometrie Init (CLSID_ObjektGeometrie, CLSCTX_INPROC_SERVER, NULL); // throw hr

//	Geometrie init. (alles 0 setzen)
	HRESULT hr = Init -> InitObjGeometry (lObjNr);
	if (FAILED(hr))
		_com_issue_error (hr);

//	eigentliche Interface besorgen
	m_wIObjGeo = Init;	// throw hr
}


// --------------------------------------------------------------------------------------------
//	default Konstruktor
CObjektKante::CObjektKante ()	
{
	m_bIsDirChanged = FALSE;
	m_iChangeCounter = 0;
	m_bIsDirChangedArea = FALSE;
	m_bIsInUnion = FALSE;
	m_sBuildCnt = 0;
	m_dWi = -1.0;			// ungültiger Wert
	m_bAussenKante = FALSE;
	m_sAppendType = NoAppend;
}


// --------------------------------------------------------------------------------------------
//	Copy-Konstruktor
CObjektKante::CObjektKante (const CObjektKante &OK)	
{
	m_bIsDirChanged = OK.m_bIsDirChanged;
	m_iChangeCounter = OK.m_iChangeCounter;		// #WM990701
	m_bIsDirChangedArea = OK.m_bIsDirChangedArea;
	m_bIsInUnion = OK.m_bIsInUnion;
	m_sBuildCnt = OK.m_sBuildCnt;
	m_dWi = OK.m_dWi;
	m_bAussenKante = OK.m_bAussenKante;
	m_sAppendType = OK.m_sAppendType;
	((CObjektKante &)OK).GetInterface (m_wIObjGeo.ppi ());
}


// --------------------------------------------------------------------------------------------
BOOL CObjektKante :: operator = (const CObjektKante &OK) 
{
	m_bIsDirChanged = OK.m_bIsDirChanged;
	m_iChangeCounter = OK.m_iChangeCounter;		// #WM990701
	m_bIsDirChangedArea = OK.m_bIsDirChangedArea;
	m_bIsInUnion = OK.m_bIsInUnion;
	m_sBuildCnt = OK.m_sBuildCnt;
	m_dWi = OK.m_dWi;
	m_bAussenKante = OK.m_bAussenKante;
	m_sAppendType = OK.m_sAppendType;
	return (NOERROR == ((CObjektKante &)OK).GetInterface (m_wIObjGeo.ppi ()));
}


// --------------------------------------------------------------------------------------------
//	Geoemtrie der Kante kopieren
void CObjektKante :: InitObjectGeometrie (CObjektKante &Kante)
{
	long lCnt = 0;
	long *pX = NULL;
	long *pY = NULL;

//	lese Geometrie
	Kante.GetGeometrie (&pX, &pY, &lCnt);
	ASSERT ((lCnt >= 2) && (NULL != pX) && (NULL != pY));

//	Geometrie init. (alles 0 setzen)
	WInitObjektGeometrie Init (CLSID_ObjektGeometrie, CLSCTX_INPROC_SERVER, NULL); // throw hr
	HRESULT hr = Init -> InitObjGeometry (pX, pY, lCnt, OGLinie);
	if (FAILED(hr))
		_com_issue_error (hr);

//	eigentliche Interface besorgen
	m_wIObjGeo = Init;	// throw hr
}


// --------------------------------------------------------------------------------------------
HRESULT CObjektKante :: GetInterface (IObjektGeometrie **ppIOG) 
{
	if (NULL == ppIOG)
		return E_POINTER;

	ASSERT (NULL != (IObjektGeometrie *)m_wIObjGeo); 
	
	*ppIOG = m_wIObjGeo;
	if (NULL != *ppIOG)
		(*ppIOG) -> AddRef ();
	else
		return E_UNEXPECTED;

	return NOERROR;
}


// --------------------------------------------------------------------------------------------
//	Geometrie-Infos lesen
void CObjektKante :: GetGeometrie (long **pplX, long **pplY, long *plCnt /*=NULL*/,
								   short *psKCnt/*=NULL*/, long **pplLPCnt/*=NULL*/)
{
//	prüfe interne Parameter
	ASSERT (NULL != (IObjektGeometrie *)m_wIObjGeo); 

//	prüfe übergebene Parameter
	ASSERT ((NULL != pplX) && (NULL != pplY));

//	Zeiger auf Geometrie holen
	HRESULT hr = m_wIObjGeo -> GetX ((VOID **)pplX);
	if (FAILED(hr))
		_com_issue_error (hr);
	ASSERT (NULL != *pplX);

	hr = m_wIObjGeo -> GetY ((VOID **)pplY);
	if (FAILED(hr))
		_com_issue_error (hr);
	ASSERT (NULL != *pplY);

//	ggf. Stützpunktanzahl lesen
	if (plCnt)
	{
		hr = m_wIObjGeo -> GetCnt (plCnt);
		if (FAILED(hr))
			_com_issue_error (hr);
	}

//	ggf. Konturgröße lesen
	if (psKCnt)
	{
		hr = m_wIObjGeo -> GetKCnt (psKCnt);
		if (FAILED(hr))
			_com_issue_error (hr);
	}

//	ggf. Konturfeld lesen
	if (pplLPCnt)
	{
		hr = m_wIObjGeo -> GetLPCnt (pplLPCnt);
		if (FAILED(hr))
			_com_issue_error (hr);
	}
}


// --------------------------------------------------------------------------------------------
//	berechne Drehwinkel des letzten Segments der Kante zur x-Achse
double CObjektKante :: GetDrehWinkel (void)
{
	long lCnt = 0;
	long *pX = NULL;
	long *pY = NULL;

	GetGeometrie (&pX, &pY, &lCnt);	
	ASSERT ((lCnt > 1) && (NULL != pX) && (NULL != pY));

	long lLastInd = lCnt-1;
	long lPrevInd = lLastInd-1;

	double dDeltaX = pX [lLastInd] - pX [lPrevInd];
	double dDeltaY = pY [lLastInd] - pY [lPrevInd];

//	teste Spezial-Fälle
	double dPi = 2.0 * asin (1.0);
	double dDrehWi = -1.0;
	if (0.0 == dDeltaX)
		dDrehWi = pX [lLastInd] > pX [lPrevInd] ? dPi / 2 : 3 * dPi / 2;
	else
	{
		if (0.0 == dDeltaY)
			dDrehWi = pY [lLastInd] > pY [lPrevInd] ? 0 : dPi;
		else
		{
			dDrehWi = atan (dDeltaY / dDeltaX);	// im Bogenmaß
			if (dDeltaX > 0.0)
				dDrehWi += dPi;
			else
			{
				if (dDeltaY > 0.0)
					dDrehWi += (2.0*dPi);					
			}			
		}
	}

	return dDrehWi;
}


// --------------------------------------------------------------------------------------------
//	lese Objektnummer der Kante
long CObjektKante :: GetObjNummer (void)
{
//	prüfe interne Parameter
	ASSERT (NULL != (IObjektGeometrie *)m_wIObjGeo); 
	
	long lObjNr = 0;
	HRESULT hr = m_wIObjGeo -> GetONr (&lObjNr);
	if (FAILED(hr))
		_com_issue_error (hr);

	return lObjNr;
}


// --------------------------------------------------------------------------------------------
//	Setze Winkelminimum in Abhängigkeit von der Suchrichtung
void CObjektKante :: SetWinkelMin (void/*BOOL bDir*/)
{
/*
	if (bDir)
		m_dWi = -1.0;
	else
		m_dWi = DBL_MAX;
*/
//	nur gößter Winkel 
	m_dWi = -1.0;
}


// --------------------------------------------------------------------------------------------
//	Geometrie-Vektor tauschen
void CObjektKante :: ChangeDirection (void)
{
	long lCnt = 0;
	long *pX = NULL;
	long *pY = NULL;

//	lese Geometrie
	GetGeometrie (&pX, &pY, &lCnt);	
	ASSERT ((lCnt > 1) && (NULL != pX) && (NULL != pY));

	long lOldX = 0;
	long lOldY = 0;
	for (long lIndex = 0; lIndex < lCnt / 2; lIndex++)
	{
		lOldX = pX [lIndex];
		lOldY = pY [lIndex];
		pX [lIndex] = pX [lCnt-lIndex-1];
		pY [lIndex] = pY [lCnt-lIndex-1];
		pX [lCnt-lIndex-1] = lOldX;
		pY [lCnt-lIndex-1] = lOldY;
	}

//	Flag neu setzen
	m_bIsDirChanged = m_bIsDirChanged ? FALSE : TRUE;

	// es wird gezählt, wie oft die Richtung einer inneren Kante nach dem 1. Einbau noch
	// geändert wurde; dies ist notwendig, da eine innere Kante zweimal verwendet werden kann,
	// beim zweiten Mal jedoch in der entgegengesetzten Richtung durchlaufen werden muß; nun
	// kommt es aber vor, daß zwischen dem 1. und dem 2. Einbau die Kante bei erfolglosen
	// Einbauversuchen gedreht wurde, dadurch ist aber ohne den nachfolgenden Zähler beim 2.
	// Einbau nicht klärbar, ob sie in der entgegengesetzten Richtung durchlaufen wird (#WM990701)
	if (FALSE == m_bAussenKante && 1 == m_sBuildCnt)	// innere Kante und schon einmal verwendet
		m_iChangeCounter++;
}


// --------------------------------------------------------------------------------------------
//	Geometrie des Objektes löschen
BOOL CObjektKante :: DeleteGeometrie (BOOL fUndo)
{
	long lObjNr = GetObjNummer ();
	ASSERT (lObjNr > 0);

	if (fUndo)
		return DEX_DeleteObjectEx (lObjNr);		// undo berücksichtigen
	return DEX_DeleteObject(lObjNr);
}


// --------------------------------------------------------------------------------------------
// #HK971217
//	Objekt als benutzt kennzeichnen
BOOL CObjektKante :: MarkObject (ULONG ulMCode)
{
	ASSERT (0 != ulMCode);
	ASSERT ((ULONG)-1 != ulMCode);

	long lObjNr = GetObjNummer ();
	ASSERT (lObjNr > 0);

CString str;

	VERIFY(str.LoadString (IDS_MARK_OBJECT));
	return (EC_OKAY == OutputMerkmal (lObjNr, ulMCode, str)) ? TRUE : FALSE; 
}


// --------------------------------------------------------------------------------------------
//	Geometrie als Linie an TRiAS ausgeben: liefert Objektnummer zurück
//	in bRO wird zurückgegeben, ob die Zieldatenquelle schreibgeschützt ist (TRUE) oder nicht
//	(FALSE) #WM990713
long CObjektKante :: Output (HPROJECT hPr, BOOL& bRO, int iFlags/* = sGeoOutputFlags*/,
							 BOOL fUndo)
{
	bRO = FALSE;	// Zieldatenquelle nicht schreibgeschützt

//	prüfe interne Parameter
	ASSERT (NULL != (IObjektGeometrie *)m_wIObjGeo); 
	
//	Flags für Ausgabe setzen
	HRESULT hr = m_wIObjGeo -> SetFlags (iFlags);
	if (FAILED(hr))
		return -1;

//	Objekt an Trias ausgeben: mit Undo
	hr = m_wIObjGeo -> GeometrieAnTRiASEx (reinterpret_cast<INT_PTR>(hPr), fUndo, NULL);
	if (ERROR_WRITE_PROTECT == hr)
	{
		bRO = TRUE;	// Zieldatenquelle schreibgeschützt
		return -1;
	}

	if (FAILED (hr))
		return -1;

	return GetObjNummer ();
}


// --------------------------------------------------------------------------------------------
//	Geometrie als Fläche an TRiAS ausgeben: liefert Objektnummer zurück
//	in bRO wird zurückgegeben, ob die Zieldatenquelle schreibgeschützt ist (TRUE) oder nicht
//	(FALSE) #WM990713
long CObjektKante :: OutputFlaeche (HPROJECT hPr, BOOL& bRO)
{
//	prüfe interne Parameter
	ASSERT (NULL != (IObjektGeometrie *)m_wIObjGeo); 

//	setze Konturen-Anzahl
	HRESULT hr = m_wIObjGeo -> SetKCnt (KonturSize); // immer nur eine Masche
	if (FAILED(hr))
		return -1;

//	lese Stützpunktanzahl
	long lCnt = 0;
	hr = m_wIObjGeo -> GetCnt (&lCnt);
	if (FAILED(hr))
		return -1;

//	setze Konturfeld
	long CntField [KonturSize];
	CntField [0] = lCnt;
	hr = m_wIObjGeo -> SetLPCnt (CntField, KonturSize);
	if (FAILED(hr))
		return -1;

//	Typ umdefinieren
	hr = m_wIObjGeo -> SetObjTyp (OGFlaeche);
	if (FAILED(hr))
		return -1;

	return Output (hPr, bRO);
}


// --------------------------------------------------------------------------------------------
//	lese Anzahl Stützpunkte
long CObjektKante ::  GetASP (void)
{
//	prüfe interne Parameter
	ASSERT (NULL != (IObjektGeometrie *)m_wIObjGeo); 

//	Stützpunktanzahl lesen
	long lCnt = 0;
	HRESULT hr = m_wIObjGeo -> GetCnt (&lCnt);
	if (FAILED(hr))
		_com_issue_error (hr);
	
	return lCnt;
}


// --------------------------------------------------------------------------------------------
//	lese ObjektContainer
CObjContainer CObjektKante :: GetCont (void)
{
//	prüfe interne Parameter
	ASSERT (NULL != (IObjektGeometrie *)m_wIObjGeo); 

//	Objektcontainer lesen
	long lXmin, lXmax, lYmin, lYmax;
	HRESULT hr = m_wIObjGeo -> GetCont (&lXmin, &lXmax, &lYmin, &lYmax);
	if (FAILED(hr))
		_com_issue_error (hr);

	CObjContainer OC;
	OC.XMin () = lXmin;
	OC.XMax () = lXmax;
	OC.YMin () = lXmin;
	OC.YMax () = lXmax;
	
	return OC;
}


// --------------------------------------------------------------------------------------------
//	lese Objekttyp
short CObjektKante :: GetType (void)
{
//	prüfe interne Parameter
	ASSERT (NULL != (IObjektGeometrie *)m_wIObjGeo); 

//	Typ lesen
	short sType = 0;
	HRESULT hr = m_wIObjGeo -> GetObjTyp (&sType);
	if (FAILED(hr))
		_com_issue_error (hr);
	
	return sType;
}
