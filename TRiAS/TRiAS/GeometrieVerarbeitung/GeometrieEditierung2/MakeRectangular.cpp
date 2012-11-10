// Definitionen: Fläche rechtwinklig machen
// File: MakeRectangular.cpp
// W. Mörtl


#include "GeoEditP.h"

#include "GeometrR.h"			// IDS_WINKELKORR, ...
#include "strecke.hxx"			// Winkel()
#include "MakeRectangular.h"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern ResourceFile* pRF;



///////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktor
CMakeRectangular::CMakeRectangular (void)
{
    m_pWink = NULL;
}


// --------------------------------------------------------------------------------------------
// Destruktor
CMakeRectangular::~CMakeRectangular (void)
{
	DELETE_VEC (m_pWink);
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Verbindung zur CObjectModify-Klasse über das Interface IModifyClassSite herstellen;
// es wird also von der Klasse CMakeRectangular KEINE (!!) direkte Verbindung zu TRiAS über
// Interface ITriasExtension hergestellt
STDMETHODIMP CMakeRectangular::SetModifyClassSite (IEditExtensionSite* pIEdExSite,
    											   IModifyClassSite* pIModClSite)
{
    try
    {
    	if (pIEdExSite != NULL)
    	{
    		THROW_FAILED_HRESULT (pIEdExSite->CreateInterfaceTO (m_wTopObjs.ppi()));

    		m_wEdExSite = pIEdExSite;
    	}
    	else
    	{
    		m_wTopObjs.Assign (NULL);	// freigeben
    		m_wEdExSite.Assign (NULL);	// freigeben
    	}
    	m_wModClSite = pIModClSite;
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    return S_OK;

} // SetModifyClassSite


// --------------------------------------------------------------------------------------------
STDMETHODIMP CMakeRectangular::LineElongation (IEnumObjektGeometrie*, long, long)
{
    ATLTRACENOTIMPL("CMakeRectangular::LineElongation");
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CMakeRectangular::AreaPartition (long, POINT)
{
    ATLTRACENOTIMPL("CMakeRectangular::AreaPartition");
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CMakeRectangular::IslandAddition (IEnumObjektGeometrie*)
{
    ATLTRACENOTIMPL("CMakeRectangular::IslandAddition");
}


// --------------------------------------------------------------------------------------------
// lONr-Fläche rechtwinklig machen;
// dabei sind lStartInd der Index des ersten Stützpunktes der Bezugsstrecke (Startindex) und
// iKInd der Index der Kontur, die rechtwinklig gemacht werden soll; es sind
//   dEps90   Epsilon für rechte Winkel
//   dEps180  Epsilon für gestreckte Winkel
//   dEpsCom  Epsilon Gleichheit der angrenzenden Objekte
// in ppEnumOut werden, wenn *ppEnumOut != NULL ist, die modifizierten Objekte zurückgegeben
STDMETHODIMP CMakeRectangular::Rectangularity (long lONr, int iKInd, long lStartInd,
    		   double dEps90, double dEps180, double dEpsCom, IEnumObjectsByNumber** ppEnumOut)
{
WObjektGeometrie wObj;	// ObjektGeometrie der lONr-Fläche

    m_lAktONr = lONr;
    m_lStartInd = lStartInd;

    // aktive (blinkende) lONr-Fläche bestimmen
    try
    {
    WInitObjektGeometrie wIObj (CLSID_ObjektGeometrie);	// throws_com_error

    	THROW_FAILED_HRESULT (wIObj->InitObjGeometry (lONr));

    	wObj = wIObj;

    // *ppEnumOut als leere Kiste anlegen
    WEnumObjectsByNumber wOutObjs (CLSID_EnumObjectsByNumber);

    	*ppEnumOut = wOutObjs.detach();
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

short iOT, iKCnt;	// Parameter des lONr-Objektes
long lCnt;
long* plCnt;

    wObj->GetObjTyp (&iOT);
    if (iOT != OT_FLAECHE) return E_UNEXPECTED;

    wObj->GetCnt (&lCnt);
    wObj->GetX ((void**)&m_plX);
    wObj->GetY ((void**)&m_plY);
    wObj->GetKCnt (&iKCnt);
    wObj->GetLPCnt (&plCnt);

    // Vorarbeiten für die Erzeugung der Rechtwinkligkeit
    m_lAInd = 0;		// Index des 1. Stützpunktes der zu behandelnden Kontur
    for (int i = 0; i < iKInd; i++)
    	m_lAInd += plCnt[i];

    m_lEInd = m_lAInd + plCnt[iKInd] - 1;	// Index des letzten Stützpunktes

    m_lStopInd = -1;	// Endindex für ContourUp() und ContourDown(); wird in
    					// AngleClassification() ermittelt

	DELETE_VEC (m_pWink);	// vorsichtshalber
    m_pWink = new StrWinkel[m_lEInd + 1];	// wird in AngleClassification() gefüllt
    if (! m_pWink)
    {
    	DEX_Error (RC_MakeRectangular, EC_NOMEMORY);
    	return E_OUTOFMEMORY;
    }

RectMode rMode = AngleClassification (dEps90, dEps180);

HRESULT hrRet = SaveOriginalCoordinates (iKInd, lCnt);	// Ursprungskoordinaten retten

    if (FAILED(hrRet)) return hrRet;

    if (RECHTW == rMode)		// es gibt etwas rechtwinklig zu machen
    	MakeRightAngles();
    else if (EXAKT == rMode)	// es gibt nichts rechtwinklig zu machen, aber das Objekt			
    	AddAngleFeature();		// enthält mindestens einen exakten rechten Winkel

	DELETE_VEC (m_pWink);

// wenn als 1. Kontur die Außenkontur ausgewählt wurde und es noch Innenkonturen gibt, dann
// diese ebenfalls rechtwinklig machen
RectMode rModeIn = KEINRW;	// (Ausgangs-)Situation möglicher Innenkonturen

    if (0 == iKInd && iKCnt > 1)
    	hrRet = AdjustInsideContours (iKCnt, plCnt, dEps90, dEps180, rModeIn);

    if (RECHTW == rMode ||	// die 1. Kontur bzw.
    	RECHTW == rModeIn)	// eine der Innenkonturen wurde rechtwinklig gemacht
    {
    Rectangle AllRec;			// rechteckiger Bereich für Neuzeichnen nach Rechtwinkligkeit
    bool bAllRecInit = false;	// AllRec (noch) nicht initialisiert

    	// angegrabte Objekte nachziehen
    	ModifyCommonVertices (lCnt, iKInd, dEpsCom, AllRec, bAllRecInit, ppEnumOut);

    	// korrigierte Fläche abspeichern
    	hrRet = RectangularAreaToTRiAS (wObj, lCnt, AllRec, bAllRecInit);
    	if (SUCCEEDED (hrRet))	// m_lAktONr-Objekt wurde rechtwinklig gemacht
    	{
    		if (*ppEnumOut)
    			(*ppEnumOut)->AddItem (m_lAktONr);
    		else
    			_ASSERTE (*ppEnumOut != NULL);
    	}
    }

	DELETE_VEC (m_plUrX);
	DELETE_VEC (m_plUrY);

    return hrRet;

} // Rectangularity


// --------------------------------------------------------------------------------------------
STDMETHODIMP CMakeRectangular::MakeCommonBorder (IEnumObjektGeometrie*, long, long)
{
    ATLTRACENOTIMPL("CMakeRectangular::MakeCommonBorder");
}


// --------------------------------------------------------------------------------------------
// Klasseneinteilung der Winkel entsprechend ihrer Größe
// return-Werte können sein
//	RECHTW	es gibt Winkel, die rechtwinklig zu machen sind
//	KEINRW	es gibt keinen Winkel, der rechtwinklig zu machen ist und es gibt auch keinen,
//			der schon exakt rechtwinklig ist
//	EXAKT	es gibt keinen Winkel, der rechtwinklig zu machen ist, aber es gibt mindestens
//			einen, der schon exakt rechtwinklig ist
RectMode CMakeRectangular::AngleClassification (double dEps90, double dEps180)
{
    dEps90 *= Pi/180.;
    dEps180 *= Pi/180.;

RectMode rMode = KEINRW;
double dWinkel;
long j, j1, j2;			// Stützpunktindizes

bool bAllgm = false;	// es gibt/keine allgemeinen Winkel (true/false)

    m_bGestr = false;	// es gibt (noch) keine Winkel "nahe" 180°

    m_dMaxDiv90 = 0.;

    for (long j0 = m_lAInd; j0 < m_lEInd; j0++)
    {
    	j1 = j0 + 1;
    	(j1 < m_lEInd) ? (j2 = j1 + 1) : (j2 = m_lAInd + 1);

    	if (! Winkel (m_plX[j0], m_plY[j0], m_plX[j1], m_plY[j1], m_plX[j2], m_plY[j2],
    				  dWinkel))
    		_ASSERTE (false);

    	(j1 < m_lEInd) ? (j = j1) : (j = m_lAInd);
//double ww = dWinkel*180./Pi;
    	if (0.5*Pi == dWinkel || 1.5*Pi == dWinkel)
    	{
    		m_pWink[j] = RECHTER;
    		rMode = EXAKT;
    	}
    	else if (0.5*Pi-dEps90 < dWinkel && dWinkel < 0.5*Pi+dEps90)
    	{
    	double dDiv90 = fabs (0.5*Pi - dWinkel);

    		if (m_dMaxDiv90 < dDiv90) m_dMaxDiv90 = dDiv90;
    		m_pWink[j] = RECHTER;
    		rMode = RECHTW;
    	}
    	else if (1.5*Pi-dEps90 < dWinkel && dWinkel < 1.5*Pi+dEps90)
    	{
    	double dDiv90 = fabs (1.5*Pi - dWinkel);

    		if (m_dMaxDiv90 < dDiv90) m_dMaxDiv90 = dDiv90;
    		m_pWink[j] = RECHTER;
    		rMode = RECHTW;
    	}
    	else if (Pi-dEps180 < dWinkel && dWinkel < Pi+dEps180)
    	{
    		m_pWink[j] = GESTRECKT;
    		m_bGestr = true;		// es gibt Winkel "nahe" 180°
    	}
    	else if (0. == dWinkel || 2.*Pi == dWinkel)
    	{
    		m_pWink[j] = ENTARTET;
    		_ASSERTE (m_pWink[j] != ENTARTET);	// dürfte bei TRiAS-Objekten nicht auftreten
    	}
    	else
    	{
    		m_pWink[j] = ALLGEMEIN;
    		bAllgm = true;		// es gibt allgemeine Winkel
    	}
    }

    if (RECHTW != rMode)
    	return rMode;	// es ist nichts rechtwinklig zu machen

// m_lStopInd ermitteln
long lKL = m_lEInd - m_lAInd + 1;	// volle Konturlänge

// der Verlußt der Kommastelle bei lKL/2 für ungerades lKL ist gewollt !!!
// der Module-Operator hat nur den Sinn, daß trotz eines evtl. Überschreiten des
// Konturschlosses durch die Addition mit lKL/2 der Index innerhalb der Kontur bleibt
long lRelInd = (m_lStartInd + lKL/2) % m_lEInd;	// relativer Startindex innerhalb der
    											// Kontur
    m_lStopInd = m_lAInd + lRelInd;

    if (!bAllgm && !m_bGestr)	// es gibt nur rechte bzw. Winkel "nahe" 90°/270°
    	return rMode;

// zuerst den Index eines allgemeinen Winkels suchen, der möglichst dicht bei m_lStopInd liegt
long lVInd = m_lStopInd;	// Indizes vor bzw.
long lNInd;					//  nach m_lStopInd

    (m_lStopInd > m_lAInd) ? (lNInd = m_lStopInd - 1) : (lNInd = m_lEInd - 1);

    if (bAllgm)
    {
    	do
    	{
    		(lNInd < m_lEInd - 1) ? (lNInd++) : (lNInd = m_lAInd);
    		if (ALLGEMEIN == m_pWink[lNInd])
    		{
    			m_lStopInd = lNInd;
    			return rMode;
    		}

    		(lVInd > m_lAInd) ? (lVInd--) : (lVInd = m_lEInd - 1);
    		if (ALLGEMEIN == m_pWink[lVInd])
    		{
    			m_lStopInd = lVInd;
    			return rMode;
    		}
    	}
    	while (lVInd != m_lStartInd || lNInd != m_lStartInd);

    	_ASSERTE (false);	// hierhin dürfte das Programm nicht kommen !!!
    }

    // wenn es keinen allgemeinen Winkel gibt, dann den Index eines Winkels ("nahe") 90°
    // suchen, der möglichst dicht bei m_lStopInd liegt
    _ASSERTE (m_bGestr == true);

    if (RECHTER == m_pWink[m_lStopInd])
    	return rMode;

    do
    {
    	(lNInd < m_lEInd - 1) ? (lNInd++) : (lNInd = m_lAInd);
    	if (RECHTER == m_pWink[lNInd])
    	{
    		m_lStopInd = lNInd;
    		return rMode;
    	}

    	(lVInd > m_lAInd) ? (lVInd--) : (lVInd = m_lEInd - 1);
    	if (RECHTER == m_pWink[lVInd])
    	{
    		m_lStopInd = lVInd;
    		return rMode;
    	}
    }
    while (lVInd != m_lStartInd || lNInd != m_lStartInd);

    _ASSERTE (false);	// hierhin dürfte das Programm nicht kommen !!!

    return rMode;

} // AngleClassification


// --------------------------------------------------------------------------------------------
// hier wird nun wirklich die Rechtwinkligkeit erzeugt
void CMakeRectangular::MakeRightAngles (void)
{
/*
// Anstieg und inversen Anstieg der Bezugsstrecke ermitteln
long lSt1;		// lSt1 = m_lStartInd + 1

    (m_lStartInd < m_lEInd - 1) ? (lSt1 = m_lStartInd + 1) : (lSt1 = m_lAInd);

double dx = m_plX[lSt1] - m_plX[m_lStartInd];
double dy = m_plY[lSt1] - m_plY[m_lStartInd];

    if (0. != dx)
    	m_dGradient = dy / dx;
    else
    	m_dGradient = DBL_MAX;

    if (0. != dy)
    	m_dInvGradient = - dx / dy;
    else
    	m_dInvGradient = DBL_MAX;

    m_bParallel = false;

    ContourUp (lSt1);	// den 1. Teil der Kontur bearbeiten
*/
    ContourUp();	// den 1. Teil der Kontur bearbeiten
    ContourDown();	// den 2. Teil der Kontur bearbeiten

    m_plX[m_lEInd] = m_plX[m_lAInd];	// Kontur evtl. wieder
    m_plY[m_lEInd] = m_plY[m_lAInd];	// schließen

    LineProportions();

} // MakeRightAngles


// --------------------------------------------------------------------------------------------
// Zwischenspeichern der Ursprungskoordinaten für die Routinen LineProportions() und
// ModifyCommonVertices()
HRESULT CMakeRectangular::SaveOriginalCoordinates (int iKInd, long lCnt)
{
    _ASSERTE (m_plX != NULL);
    _ASSERTE (m_plY != NULL);

long lEI;		// Endindex des zu rettenden Bereiches

    if (0 == iKInd)	// wenn 1. Kontur eine Außenkontur ist, dann ALLE Koordinaten retten
    	lEI = lCnt - 1;
    else			// sonst nur die Koordinaten der betreffenden Innenkontur
    	lEI = m_lEInd;

    m_plUrX = new KoOrd[lEI+1];		// Speicher für Retten
    m_plUrY = new KoOrd[lEI+1];		//  der Ursprungskoordinaten

    if (!m_plUrX || !m_plUrY)
    {
    	DEX_Error (RC_MakeRectangular, EC_NOMEMORY);
	 	DELETE_VEC (m_plUrX);
    	return E_OUTOFMEMORY;
    }

    for (long j = m_lAInd; j <= lEI; j++)
    {
    	// ist nur eine Innenkontur rechtwinklig zu  machen, dann werden nur deren Koordinaten
    	// wirklich zwischengespeichert; der Speicherbereich für die davorliegenden Konturen
    	// ist aus Bequemlichkeitsgründen mit angelegt, wird aber nicht genutzt
    	m_plUrX[j/*-m_lAInd*/] = m_plX[j];
    	m_plUrY[j/*-m_lAInd*/] = m_plY[j];
    }

    return S_OK;

} // SaveOriginalCoordinates


// --------------------------------------------------------------------------------------------
// den Nachfolger von lInd ermitteln, bei dem kein Winkel "nahe" 180° ist
long CMakeRectangular::NextInterestingUpVertex (long lInd)
{
long lNext = lInd;

    do
    	(lNext < m_lEInd - 1) ? (lNext++) : (lNext = m_lAInd);
    while (GESTRECKT == m_pWink[lNext]);

    return lNext;
} // NextInterestingUpVertex


// --------------------------------------------------------------------------------------------
// den Vorgänger von lInd ermitteln, bei dem kein Winkel "nahe" 180° ist
long CMakeRectangular::NextInterestingDownVertex (long lInd)
{
long lNext = lInd;

    do
    	(lNext > m_lAInd) ? (lNext--) : (lNext = m_lEInd - 1);
    while (GESTRECKT == m_pWink[lNext]);

    return lNext;
} // NextInterestingDownVertex


// --------------------------------------------------------------------------------------------
// den 1. Teil der Kontur (m_plX,m_plY) beginnend bei Index m_lStartInd mit aufsteigenden
// Indizes rechtwinklig machen
void CMakeRectangular::ContourUp (void)
{
    _ASSERTE (m_lStartInd >= 0);

// wenn der Winkel bei lSt1 = m_lStartInd + 1 der einzige allgemeine ist, gilt
// m_lStopInd == lSt1, d.h. die gesamte Kontur wird mit ContourDown() bearbeitet
long lSt1;		// lSt1 = m_lStartInd + 1

    (m_lStartInd < m_lEInd - 1) ? (lSt1 = m_lStartInd + 1) : (lSt1 = m_lAInd);

    if (m_lStopInd == lSt1) return;

    _ASSERTE (m_plX != NULL);
    _ASSERTE (m_plY != NULL);
    _ASSERTE (m_lAInd >= 0);
    _ASSERTE (m_lEInd > 0);
    _ASSERTE (m_lEInd > m_lAInd);

long j0, j1, j2;	// Stützpunktindizes

    (m_lStartInd > m_lAInd) ? (j0 = m_lStartInd - 1) : (j0 = m_lEInd - 1);
    j1 = m_lStartInd;
    j2 = NextInterestingUpVertex (j1);

// wenn zwischen Pj1 und Pj2 mindestens ein Winkel "nahe" 180° liegt, ist dieser
// Konturabschnitt zuerst mit dem gleichen Anstieg wie die Bezugsstrecke zu versehen
long jh1;	// Hilfsindex: jh1 = j2 - 1

    (j2 > m_lAInd) ? (jh1 = j2 - 1) : (jh1 = m_lEInd - 1);

    if (jh1 != j1)	// zwischen j1 und j2 liegt mindestens ein Winkel "nahe" 180°
    {
    long j3;
    double dGradient = DBL_MAX;	// Anstieg der Bezugsstrecke
    double xs, ys;				// Koordinaten des Geradenschnittpunktes

    	j3 = NextInterestingUpVertex (j2);

    	if (m_plX[lSt1] != m_plX[m_lStartInd])
    		dGradient = ((double)m_plY[lSt1] - m_plY[m_lStartInd]) /
    					 (m_plX[lSt1] - m_plX[m_lStartInd]);

    	if (! GeradenSchnittPunkt (m_plX[j2], m_plY[j2], m_plX[j3], m_plY[j3], m_plX[lSt1],
    							   m_plY[lSt1], dGradient, xs, ys))
    		_ASSERTE (false);

    	m_plX[j2] = DtoL (xs);
    	m_plY[j2] = DtoL (ys);
    }

    m_bContUp = true;	// Kontur wird mit steigendem Index abgearbeitet
    m_bAllgm = false;	// (noch) keinen allgemeinen Winkel erreicht 
    m_xm = m_plX[j2];	// Startwerte
    m_ym = m_plY[j2];

    do
    {
    	j0 = j1;
    	j1 = j2;
    	j2 = NextInterestingUpVertex (j1);

    	AngleTest (j0, j1, j2);
    }
    while (j1 != m_lStopInd);

} // ContourUp


// --------------------------------------------------------------------------------------------
// den 2. Teil der Kontur (m_plX,m_plY) ausgehend von dem "anderen Ende" (m_lStartInd+1) der
// Bezugsstrecke mit fallenden Indizes rechtwinklig machen
void CMakeRectangular::ContourDown (void)
{
    _ASSERTE (m_lStartInd >= 0);

    // wenn der Winkel bei m_lStartInd der einzige allgemeine ist, gilt
    // m_lStopInd == m_lStartInd, d.h. die gesamte Kontur wurde schon mit ContourUp()
    // bearbeitet
    if (m_lStopInd == m_lStartInd)
    	return;

    _ASSERTE (m_plX != NULL);
    _ASSERTE (m_plY != NULL);
    _ASSERTE (m_lAInd >= 0);
    _ASSERTE (m_lEInd > 0);
    _ASSERTE (m_lEInd > m_lAInd);

long j0, j1, j2;		// Stützpunktindizes

    (m_lStartInd < m_lEInd - 1) ? (j1 = m_lStartInd + 1) : (j1 = m_lAInd);
    (j1 < m_lEInd - 1) ? (j0 = j1 + 1) : (j0 = m_lAInd);
    j2 = NextInterestingDownVertex (j1);

// wenn zwischen Pj1 und Pj2 mindestens ein Winkel "nahe" 180° liegt, ist dieser
// Konturabschnitt zuerst mit dem gleichen Anstieg wie die Bezugsstrecke zu versehen
long jh;	// Hilfsindex: jh = j2 + 1

    (j2 < m_lEInd - 1) ? (jh = j2 + 1) : (jh = m_lAInd);

    if (jh != j1)	// zwischen j1 und j2 liegt mindestens ein Winkel "nahe" 180°
    {
    long j3;
    double dGradient = DBL_MAX;	// Anstieg der Bezugsstrecke
    double xs, ys;				// Koordinaten des Geradenschnittpunktes

    	j3 = NextInterestingDownVertex (j2);

    	if (m_plX[j1] != m_plX[m_lStartInd])
    		dGradient = ((double)m_plY[j1] - m_plY[m_lStartInd]) /
    					 (m_plX[j1] - m_plX[m_lStartInd]);

    	if (! GeradenSchnittPunkt (m_plX[j2], m_plY[j2], m_plX[j3], m_plY[j3], m_plX[m_lStartInd],
    							   m_plY[m_lStartInd], dGradient, xs, ys))
    		_ASSERTE (false);

    	m_plX[j2] = DtoL (xs);
    	m_plY[j2] = DtoL (ys);
    }

    m_bContUp = false;	// Kontur wird mit fallendem Index abgearbeitet
    m_bAllgm = false;	// (noch) keinen allgemeinen Winkel erreicht 
    m_xm = m_plX[j2];	// Startwerte
    m_ym = m_plY[j2];

    do
    {
    	j0 = j1;
    	j1 = j2;
    	j2 = NextInterestingDownVertex (j1);

    	AngleTest (j0, j1, j2);
    }
    while (j2 != m_lStopInd);

} // ContourDown


// --------------------------------------------------------------------------------------------
// Hilfsroutine für ContourUp() bzw. ContourDown()
void CMakeRectangular::AngleTest (long j0, long j1, long j2)
{
    switch (m_pWink[j1])
    {
    	case RECHTER:
    		// m_bAllgm == false heißt, daß der VORHERgehende Winkel ein allgemeiner ist;
    		// dies kann nicht von m_pWink[j0] abhängig gemacht werden, da bei den beiden
    		// Winkeln , die an der Bezugsstrecke liegen auf jeden Fall der if-Zweig 
    		// "m_bAllgm == false" abzuarbeiten ist, da die Lage der Bezugsstrecke erhalten
    		// bleiben muß
    		if (! m_bAllgm)	// der vorhergehende Winkel ist nicht allgemein
    			Angle90 (j0, j1, j2);
    		else			// der vorhergehende Winkel ist allgemein
    		{
    			Angle90Back (j0, j1, j2);
    			m_bAllgm = false;
    		}
    		break;		// Winkel wurde rechtwinklig gemacht

    	case ALLGEMEIN:
    		m_bAllgm = true;
    		break;		// hier ist nichts weiter zu tun

    	default:
    		_ASSERTE (false);
    }

} // AngleTest


// --------------------------------------------------------------------------------------------
// Korrektur des Winkels bei Pj1, der "nahe" 90° bzw. "nahe" 270° ist, wenn der VORHERgehende
// Winkel kein allgemeiner ist
void CMakeRectangular::Angle90 (long j0, long j1, long j2)
{
    _ASSERTE (m_pWink[j2] != GESTRECKT);

double xl, yl;		// Koordinaten des Lotpunktes

    if (ALLGEMEIN != m_pWink[j2])	// der NACHfolgende ist kein allgemeiner 
    {
    double xml, yml;	// Koordinaten des drauf gezogenen Mittelpunktes

    	// diesen Mittelpunkt auf eine der Strecken zwischen Pj1 und Pj2 ziehen
    	SegmentCentre (j1, j2, xml, yml);

    	if (! GeradenLotPunkt (xml, yml, m_plX[j0], m_plY[j0], m_xm, m_ym, xl, yl))
    		_ASSERTE (false);

    	m_plX[j1] = DtoL (xl);
    	m_plY[j1] = DtoL (yl);
    	m_xm = xml;
    	m_ym = yml;
    	return;
    }

    // wenn bei Pj2 ein allgemeiner Winkel ist, der außerdem noch "ziemlich nahe" bei 180° ist,
    // kann der errechnete Geradenschnittpunkt "weit draußen" liegen; deshalb nur das Lot von
    // Pj2 auf die Strecke Pj0-Pj1
    if (! GeradenLotPunkt (m_plX[j2], m_plY[j2], m_plX[j0], m_plY[j0], m_xm, m_ym, xl, yl))
    	_ASSERTE (false);

    m_plX[j1] = DtoL (xl);
    m_plY[j1] = DtoL (yl);
    // m_xm und m_ym brauchen hier nicht gesetzt zu werden, da als nächstes ein allgemeiner
    // Winkel kommt und danach Angle90Back() abgearbeitet wird; diese Routine benötigt m_xm und
    // m_ym nicht, setzt diese Werte aber neu

} // Angle90


// --------------------------------------------------------------------------------------------
// Korrektur des Winkels bei Pj1, der "nahe" 90° bzw. "nahe" 270° ist, wenn der vorhergehende
// Winkel ein allgemeiner ist
void CMakeRectangular::Angle90Back (long j0, long j1, long j2)
{
// es wird unterschieden, ob das Lot von P0 auf P1-P2 oder von P2 auf P1-P0 gefällt wird;
// entscheidend ist das Verhältnis der beiden Streckenlängen: es wird das Lot der kürzeren auf
// die längere Strecke gefällt
double dLen01 = AbstandPktPktE (m_plX[j0], m_plY[j0], m_plX[j1], m_plY[j1]);
double dLen12 = AbstandPktPktE (m_plX[j1], m_plY[j1], m_plX[j2], m_plY[j2]);
double xl, yl;		// Koordinaten des Lotpunktes

    if (dLen01 < dLen12)
    {
    	if (! GeradenLotPunkt (m_plX[j0], m_plY[j0], m_plX[j1], m_plY[j1], m_plX[j2],
    						   m_plY[j2], xl, yl))
    		_ASSERTE (false);
    	m_xm = m_plX[j2];
    	m_ym = m_plY[j2];
    }
    else
    {
    double xml, yml;	// Koordinaten des drauf gezogenen Mittelpunktes

    	// diesen Mittelpunkt auf eine der Strecken zwischen Pj1 und Pj2 ziehen
    	SegmentCentre (j1, j2, xml, yml);

    	if (! GeradenLotPunkt (xml, yml, m_plX[j1], m_plY[j1], m_plX[j0], m_plY[j0], xl, yl))
    		_ASSERTE (false);
    	m_xm = xml;
    	m_ym = yml;
    }

    m_plX[j1] = DtoL (xl);
    m_plY[j1] = DtoL (yl);

} // Angle90Back


// --------------------------------------------------------------------------------------------
// ausgehend von dem Mittelpunkt der gedachten Verbindungslinie Pj1-Pj2 wird auf dieser Linie
// die Senkrechte errichtet und mit den einzelnen Teilstrecken geschnitten; dieser
// draufgezogene Mittelpunkt wird in (xml, yml) zurückgegeben;
// es wird hier bewußt mit den URSPRUNGSKoordinaten gearbeitet !!
void CMakeRectangular::SegmentCentre (long j1, long j2, double& xml, double& yml)
{
// Mittelpunkt eines ("fast") gestreckten Konturabschnitts
double xm = ((double)m_plUrX[j1] + m_plUrX[j2]) / 2.;
double ym = ((double)m_plUrY[j1] + m_plUrY[j2]) / 2.;

long jj1 = j1;	// Hilfsindizes
long jj2;		// Nachbar von j1

    if (m_bContUp)		// Kontur wird aufsteigend abgearbeitet
    	(j1 < m_lEInd - 1) ? (jj2 = j1 + 1) : (jj2 = m_lAInd);
    else				// Kontur wird absteigend abgearbeitet
    	(j1 > m_lAInd) ? (jj2 = j1 - 1) : (jj2 = m_lEInd - 1);

    if (jj2 == j2)	// nur EINE Strecke
    {
    	xml = xm;
    	yml = ym;
    	return;
    }

double dGradient;	// negativer inverser Anstieg von Pj1-Pj2

    if (m_plUrY[j2] != m_plUrY[j1])
    	dGradient = - ((double)m_plUrX[j2] - m_plUrX[j1]) / (m_plUrY[j2] - m_plUrY[j1]);
    else
    	dGradient = DBL_MAX;

    do
    {
    	if (! GeradenSchnittPunkt (m_plUrX[jj1], m_plUrY[jj1], m_plUrX[jj2], m_plUrY[jj2], xm,
    							   ym, dGradient, xml, yml))
    		_ASSERTE (false);

    	if (min (m_plUrX[jj1], m_plUrX[jj2]) <= xml && xml <= max (m_plUrX[jj1], m_plUrX[jj2]) &&
    		min (m_plUrY[jj1], m_plUrY[jj2]) <= yml && yml <= max (m_plUrY[jj1], m_plUrY[jj2]))
    		return;		// drauf gezogener Mittelpunkt liegt auf der Strecke Pjj1-Pjj2

    	jj1 = jj2;
    	if (m_bContUp)
    		(jj2 < m_lEInd - 1) ? (jj2++) : (jj2 = m_lAInd);
    	else
    		(jj2 > m_lAInd) ? (jj2--) : (jj2 = m_lEInd - 1);
    }
    while (jj1 != j2);

    _ASSERTE (false);

} // SegmentCentre


// --------------------------------------------------------------------------------------------
// das Verhältnis zwischen den Strecken auf den "fast" kerzengeraden Konturabschnitten wieder
// herstellen
void CMakeRectangular::LineProportions (void)
{
    if (! m_bGestr)		// es gibt keine Winkel "nahe" 180°
    	return;

// den ersten "fast" gestreckten Konturabschnitt suchen; ja ist dabei der 1. Index, je der
// letzte Index
long ja = m_lAInd;	// Startwert für Suche des 1. Index
long ja1, je;		// ja1 = ja + 1
long jaa;			// der Anfangsindex des 1. bearbeiteten "fast" gestreckten Konturabschnitts

    for (; ja < m_lEInd; ja++)
    	if (GESTRECKT == m_pWink[ja]) break;

    if (ja > m_lAInd)
    	ja--;
    else	// "fast" gestreckter Konturabschnitt beginnt vor Kontur-"Schloß"
    {
    	ja = m_lEInd - 1;
    	for (; ja >= m_lAInd; ja--)
    		if (GESTRECKT != m_pWink[ja]) break;
    }

    jaa = ja;	// retten für Abbruchbedingung der nachfolgenden äußeren do-while-Schleife

DoublePair DP0, DP2, DPT;

    do	// Bearbeitung ALLER "fast" gestreckten Konturabschnitte
    {
    	(ja < m_lEInd - 1) ? (ja1 = ja + 1) : (ja1 = m_lAInd);	// den Nachfolger von ja

    	// letzten Index suchen
    	(ja < m_lEInd - 1) ? (je = ja + 1) : (je = m_lAInd);
    	do
    		(je < m_lEInd - 1) ? (je++) : (je = m_lAInd);
    	while (GESTRECKT == m_pWink[je]);

    	DP0.X() = m_plX[ja];
    	DP0.Y() = m_plY[ja];
    	DP2.X() = m_plX[je];
    	DP2.Y() = m_plY[je];

    	do	// Bearbeitung der einzelnen Strecken EINES "fast" gestreckten Konturabschnittes
    	{
    	double dL1 = AbstandPktPktE (m_plUrX[ja], m_plUrY[ja], m_plUrX[ja1],
    								 m_plUrY[ja1]);
    	double dL2 = AbstandPktPktE (m_plUrX[ja1], m_plUrY[ja1], m_plUrX[je],
    								 m_plUrY[je]);

    		_ASSERTE (dL2 != 0.);

    		// Konturabschnitt Pja-Pje im Verhältnis dL1 : dL2 teilen
    		StreckenTeilung (DP0, DP2, DPT,  dL1 / dL2);
    		m_plX[ja1] = DtoL (DPT.X());
    		m_plY[ja1] = DtoL (DPT.Y());

    		(ja1 < m_lEInd - 1) ? (ja1++) : (ja1 = m_lAInd);
    	}
    	while (ja1 != je);

    	ClearCollinear (ja, je);	// Bereinigung evtl. Kollinearitäten

    	// Anfang eines evtl. weiteren "fast" gestreckten Konturabschnittes suchen
    	(je > m_lAInd) ? (ja = je - 1) : (ja = m_lEInd - 1);
    	do
    		(ja < m_lEInd - 1) ? (ja++) : (ja = m_lAInd);
    	while (GESTRECKT != m_pWink[ja]);
    	(ja > m_lAInd) ? (ja--) : (ja = m_lEInd - 1);
    }
    while (ja != jaa);

    m_plX[m_lEInd] = m_plX[m_lAInd];	// Kontur evtl. wieder
    m_plY[m_lEInd] = m_plY[m_lAInd];	// schließen

} // LineProportions


// --------------------------------------------------------------------------------------------
// Bereinigung evtl. Kollinearitäten, die durch das Bemühen entstehen, exakte gestreckte Winkel
// zu erzeugen, werden durch eine winzigen Unsauberkeit aus der Welt geschafft
void CMakeRectangular::ClearCollinear (long ja, long je)
{
long jj2 = ja;
long jj1, jj3;

    (jj2 < m_lEInd) ? (jj3 = jj2 + 1) : (jj3 = m_lAInd + 1);

EPunkt Pkt1, Pkt2, Pkt3;

    do
    {
    	jj1 = jj2;
    	jj2 = jj3;
    	(jj3 < m_lEInd - 1) ? (jj3++) : (jj3 = m_lAInd);
    	Pkt1.X() = m_plX[jj1];
    	Pkt1.Y() = m_plY[jj1];
    	Pkt2.X() = m_plX[jj2];
    	Pkt2.Y() = m_plY[jj2];
    	Pkt3.X() = m_plX[jj3];
    	Pkt3.Y() = m_plY[jj3];

    	if (Kollinear (Pkt1, Pkt2, Pkt3))
    	{
    		if (m_plX[jj1] == m_plX[jj3])		// senkrechter Konturabschnitt
    			m_plX[jj2] += 1;	// das ist besagte Unsauberkeit
    		else if (m_plY[jj1] == m_plY[jj3])	// waagrechter Konturabschnitt
    			m_plY[jj2] += 1;
    		else
    		{
    		double dGradient = ((double)m_plY[jj3] - m_plY[jj1]) / (m_plX[jj3] - m_plX[jj1]);

    			if (fabs (dGradient) <= 1.)		// flacher Konturabschnitt
    				m_plX[jj2] += 1;
    			else							// steiler Konturabschnitt
    				m_plY[jj2] += 1;
    		}
    	}
    }
    while (jj3 != je);

} // ClearCollinear


// --------------------------------------------------------------------------------------------
// die maximale vorgefundene Abweichung eines Winkels vom Idealfall 90°/270°, die auf eben
// diesen Idealfall korrigiert wurde, als Merkmal an das korrigierte Objekt anhängen
bool CMakeRectangular::AddAngleFeature (void)
{
ulong ulMCode = GetHeaderMCode (true, IDS_WINKELKORR, IDS_WINKELKORRKT, IDS_WINKELKORRLT,
								DEX_GetObjIdent(m_lAktONr));

    if (0 == ulMCode || (ulong)-1 == ulMCode)
    	return false;

string sBuffer;	// Konvertierungspuffer

    Format (sBuffer, "%-4.1f", m_dMaxDiv90*180./Pi);
    sBuffer += "°";	// Gradmaßsymbol anfügen
    return WriteFeatureText (m_lAktONr, ulMCode, TT_Objekt, sBuffer);

} // AddAngleFeature


// --------------------------------------------------------------------------------------------
// Merkmal an das lONr-Objekt anhängen, wenn durch das Rechtwinkligmachen lVtLoss Stützpunkte
// verloren gegangen sind;
// beim Rechtwinkligmachen können Konturabschnitte, die "fast" kollinear sind, jetzt exakt
// kollinear sein; diese Stützpunkte würden dann bei DEX_ModObjGeometrie() in GeoRein.ext
// gelöscht werden
bool CMakeRectangular::AddGrabFeature (long lONr, long lVtLoss)
{
ulong ulMCode = GetHeaderMCode (true, IDS_GRABPUNKTVERLUST, IDS_GRABPUNKTVERLUSTKT,
								IDS_GRABPUNKTVERLUSTLT, DEX_GetObjIdent(lONr));

    if (0 == ulMCode || (ulong)-1 == ulMCode)
    	return false;

string sBuffer;	// Konvertierungspuffer

	Format (sBuffer, "%ld", lVtLoss);
    return WriteFeatureText (lONr, ulMCode, TT_Objekt, sBuffer);

} // AddGrabFeature


// --------------------------------------------------------------------------------------------
// Nachziehen von Stützpunkten der m_wTopObjs-Objekte
HRESULT CMakeRectangular::ModifyCommonVertices (long lSaveCnt, int iKInd, double dEpsCom,
    					Rectangle& AllRec, bool& bAllRecInit, IEnumObjectsByNumber** ppEnumOut)
{
long lCntTopObjs;		// Anzahl der nachzuziehenden Objekte

    m_wTopObjs->GetCount (&lCntTopObjs);
    if (0 == lCntTopObjs)	// es ist nichts nachzuziehen
    	return S_FALSE;

    if (1 == lCntTopObjs) // nur ein m_wTopObjs-Objekt
    {
	BOOL bContain;

    	// Testen, ob das einzige m_wTopObjs-Objekt das m_lAktONr-Objekt ist
    	m_wTopObjs->IsTopicalObject (m_lAktONr, &bContain);
    	if (bContain)
    		return S_FALSE;	// kein Test mit "sich selbst"
    }

HRESULT hrRet = S_OK;	// return-Wert
WEnumObjectsByNumber wEnum;

    if (m_wTopObjs.IsValid())
	{
	    RETURN_FAILED_HRESULT (m_wTopObjs->GetEnumTopicalObjects (wEnum.ppi()));
	}
    else
    {
    	_ASSERTE (m_wTopObjs.IsValid());
    	return E_POINTER;
    }

long lONr = 0, lTopCnt;		// Parameter eines m_wTopObjs-Objektes
KoOrd* plTopX; KoOrd* plTopY;
short iKCnt;
long* plCnt;

Rectangle Rec;		// Bereich für Neuzeichnen nach dem Nachziehen
bool bMod = true;	// beim Stützpunkt-Nachziehen keine Probleme (true)
bool bVtDraw;		// Stützpunkt wurde nicht/nachgezogen (false/true)
ResString resText (ResID (IDS_DRAGVERTEX, pRF), 50);

long lEI;			// Endindex des zu vergleichenden Bereiches

    if (0 == iKInd)	// wenn 1. Kontur eine Außenkontur ist, dann ALLE Koordinaten vergleichen
    	lEI = lSaveCnt - 1;
    else			// sonst nur die Koordinaten der betreffenden Innenkontur
    	lEI = m_lEInd;

    DEX_BeginUndoLevel (resText.Addr());

WObjektGeometrie wObj;	// ObjektGeometrie des lONr-Objektes

    try
    {
    // Objektnummern der m_wTopObjs-Objekte
    WEnumObjectsByNumber wOutObjs (CLSID_EnumObjectsByNumber);
    WInitObjektGeometrie wIObj (CLSID_ObjektGeometrie);

//		for (wEnum->Reset(); S_OK == wEnum->Next (1, wUnk.ppi(), NULL); )
    	for (wEnum->Reset(); S_OK == wEnum->Next (1, &lONr, NULL); )
    	{
//		WObjektGeometrie wObjGeom (wUnk);	// throws_com_error

//			wObjGeom->GetONr (&lONr);

			_ASSERTE (lONr != 0);
			_ASSERTE (lONr != -1);

    		if (lONr == m_lAktONr) continue;	// kein Test mit "sich selbst"

    		THROW_FAILED_HRESULT (wIObj->InitObjGeometry (lONr));	// ... initialisieren

    		wObj = wIObj;
    		wObj->GetCnt (&lTopCnt);
    		wObj->GetX ((void**)&plTopX);
    		wObj->GetY ((void**)&plTopY);
    		wObj->GetKCnt (&iKCnt);
    		wObj->GetLPCnt (&plCnt);

    		bVtDraw = false;	// noch kein Stützpunkt des lONr-Objektes nachgezogen

    		// Indizes eines angrenzenden Objektes
    		for (long tj = 0; tj < lTopCnt-1; tj++)
    			// Indizes der rechtwinklig gemachten Kontur des Bezugsobjektes
    			for (long j = m_lAInd; j <= lEI; j++)
    			{
    				if ((m_plUrX[j] != m_plX[j] ||		// Veränderung im Bezugsobjekt
    					m_plUrY[j] != m_plY[j]) &&		//  und dies betrifft einen
    					(plTopX[tj] == m_plUrX[j] &&	// gemeinsamen Stützpunkt
    					plTopY[tj] == m_plUrY[j]))		//  eines angrenzenden Objektes
    				{
    					if (m_wModClSite.IsValid())
    						m_wModClSite->SectorToDraw (wObj, plTopX[tj], plTopY[tj], tj,
    													false, (RECT*)&Rec);
    						else
    							_ASSERTE (m_wModClSite.IsValid());
    					if (!bAllRecInit)
    					{
    						AllRec = Rec;
    						bAllRecInit = true;
    					}
    					else
    						AllRec = AllRec.Union (Rec);

    					plTopX[tj] = m_plX[j];	// Stützpunkt im angrenzenden
    					plTopY[tj] = m_plY[j];	// Objekt nachziehen
    					bVtDraw = true;			// Stützpunkt des lONr-Objektes nachgezogen
    				}
    			}

    	long lTopAInd = 0;	// Anfangsindex einer Kontur eines angrenzenden Objektes

    		for (int i = 0; i < iKCnt; i++)
    		{
    		long lTopEInd = lTopAInd + plCnt[i] - 1;	// Endindex einer Kontur

    			plTopX[lTopEInd] = plTopX[lTopAInd];	// mit Konturende in
    			plTopY[lTopEInd] = plTopY[lTopAInd];	// Übereinstimmung bringen

    			lTopAInd = lTopEInd + 1;
    		}

    		wObj->SetFlags (OGModObject | OGForceGeometry | OGForceGeoError);

#if _TRiAS_VER < 0x0300
    		THROW_FAILED_HRESULT (wObj->GeometrieAnTRiAS (true, (RECT*)&AllRec));
#else
		INT_PTR hPr = reinterpret_cast<INT_PTR>(DEX_GetObjectProject (lONr));

    		THROW_FAILED_HRESULT (wObj->GeometrieAnTRiASEx (hPr, true, (RECT*)&AllRec));
#endif // _TRiAS_VER < 0x0300

#if defined(_DEBUG)
    	long lCt;

    		wObj->GetCnt (&lCt);
    		if (lTopCnt > lCt)
    			AddGrabFeature (lONr, lTopCnt - lCt);
#endif // _DEBUG

    		if (bVtDraw)	// lONr-Objekt wurde modifiziert
    			wOutObjs->AddItem (lONr);

    	} // Ende der Berarbeitung eines angrenzenden Objektes

    	*ppEnumOut = wOutObjs.detach();
    }

    catch (_com_error& e)
    {
		hrRet = _COM_ERROR(e);
    	bMod = false;
    }

    if (bMod)	// Nachziehen ohne Probleme verlaufen
    	DEX_EndUndoLevel();
    else
    	DEX_CancelUndoLevel (true);

    return hrRet;

} // ModifyCommonVertices


// --------------------------------------------------------------------------------------------
// wenn die Außenkontur rechtwinklig gemacht wurde, dann sämtliche Innenkonturen nachziehen
HRESULT CMakeRectangular::AdjustInsideContours (int iKCnt, long* plCnt, double dEps90,
    											double dEps180, RectMode& rModeIn)
{
HRESULT hrRet = S_OK;

    rModeIn = KEINRW;	// noch ist an keine Innenkontur etwas rechtwinklig zu machen

long lOCStartInd = m_lStartInd;	// Startindex der Außenkontur retten

    for (int i = 1; i < iKCnt; i++)
    {
    	m_lAInd = m_lEInd + 1;	// Index des 1. Stützpunktes der zu behandelnden Innenkontur
    	m_lEInd = m_lAInd + plCnt[i] - 1;	// Index des letzten Stützpunktes
    	m_lStopInd = -1;
		m_lStartInd = 0;	// Startindex der Innenkontur (18.10.99)

	 	DELETE_VEC (m_pWink);
    	m_pWink = new StrWinkel[m_lEInd + 1];
    	if (! m_pWink)
    	{
    		DEX_Error (RC_MakeRectangular, EC_NOMEMORY);
    		return E_OUTOFMEMORY;
    	}

    RectMode rMode = AngleClassification (dEps90, dEps180);

    	// bei der i-ten Innenkontur gibt es etwas rechtwinklig zu machen
    	if (RECHTW == rMode)
    	{
    		hrRet = MakeInsideContourRectangular (lOCStartInd);
    		rModeIn = RECHTW;	// an mindestens einer Innenkontur ist etwas rechtwinklig zu
    							// machen
    	}

	 	DELETE_VEC (m_pWink);

    }

    return hrRet;

} // AdjustInsideContours


// --------------------------------------------------------------------------------------------
// Innenkonturen werden automatisch nachgezogen, wenn die Außenkontur rechtwinklig gemacht
// werden soll; Bezugsstrecke für die Innenkontur ist dabei die Strecke, die der Bezugsstrecke
// der Außenkontur am nächsten liegt (deren Lage wurde ja nicht verändert)
HRESULT CMakeRectangular::MakeInsideContourRectangular (long lOCStartInd)
{
    GetInsideContourStartIndex (lOCStartInd);	// Startindex der Innenkontur ermitteln

    ContourUp();	// den 1. Teil der Innenkontur bearbeiten
    ContourDown();	// den 2. Teil der Innenkontur bearbeiten

    m_plX[m_lEInd] = m_plX[m_lAInd];	// Innenkontur evtl. wieder
    m_plY[m_lEInd] = m_plY[m_lAInd];	// schließen

    LineProportions();

    return S_OK;

} // MakeInsideContourRectangular


// --------------------------------------------------------------------------------------------
// Startindex einer automatisch nachgezogenen Innenkontur ermitteln; dazu wird die Strecke der
// Innenkontur gesucht, die der Bezugsstrecke der Außenkontur am nächsten liegt
void CMakeRectangular::GetInsideContourStartIndex (long lOCStartInd)
{
// Abstand für den Stützpunkt der Innenkontur, der der Bezugsstrecke der Außenkontur am
// nächsten liegt; Bezugsstrecke der Außenkontur beginnt mit dem lOCStartInd-Stützpunkt
double dMinAbst = DBL_MAX;
double dAbst;		// Abstand des j-ten Stützpunktes
DoublePair DP0 (m_plX[lOCStartInd], m_plY[lOCStartInd]);		// Bezugsstrecke
DoublePair DP1 (m_plX[lOCStartInd+1], m_plY[lOCStartInd+1]);	// der Außenkontur

    m_lStartInd = 0;	// Startindex der Innenkontur

    // den an der Bezugsstrecke der Außenkontur am nächsten liegenden Stützpunkt ermitteln
    for (long j = m_lAInd; j < m_lEInd; j++)
    {
    	AbstandPktStrecke (DoublePair(m_plX[j],m_plY[j]), DP0, DP1, dAbst);

    	if (dAbst < dMinAbst)
    	{
    		dMinAbst = dAbst;
    		m_lStartInd = j;
    	}
    }


// liegt die Strecke (m_lStartInd,m_lStartInd-1) oder (m_lStartInd,m_lStartInd+1) näher an der
// Bezugsstrecke der Außenkontur?
long lStInd1; // den Index vor bzw. nach dem m_lStartInd-ten Index

    // Strecke (m_lStartInd,m_lStartInd+1) testen 
    (m_lStartInd < m_lEInd - 1) ? (lStInd1 = m_lStartInd + 1) : (lStInd1 = m_lAInd);

    AbstandPktStrecke (DoublePair(m_plX[lStInd1],m_plY[lStInd1]), DP0, DP1, dMinAbst);

    // Strecke (m_lStartInd,m_lStartInd-1) testen 
    (m_lStartInd > m_lAInd) ? (lStInd1 = m_lStartInd - 1) : (lStInd1 = m_lEInd - 1);

    AbstandPktStrecke (DoublePair(m_plX[lStInd1],m_plY[lStInd1]), DP0, DP1, dAbst);

    if (dAbst < dMinAbst)
    	m_lStartInd = lStInd1;

} // GetInsideContourStartIndex


// --------------------------------------------------------------------------------------------
// Speicherung der rechtwinklig gemachten pIOG-Fläche nach TRiAS
HRESULT CMakeRectangular::RectangularAreaToTRiAS (IObjektGeometrie* pIOG, long lCnt,
    											  Rectangle AllRec, bool bAllRecInit)
{
    _ASSERTE (pIOG != NULL);

    pIOG->SetFlags (OGModObject | OGForceGeometry | OGForceGeoError);

ResString resText (ResID (IDS_UNDORECTANGULAR, pRF), 50);

    DEX_BeginUndoLevel (resText.Addr());

#if _TRiAS_VER < 0x0300
HRESULT hrRet = pIOG->GeometrieAnTRiAS (true, NULL);
#else
INT_PTR hPr = reinterpret_cast<INT_PTR>(DEX_GetObjectProject (m_lAktONr));
HRESULT hrRet = pIOG->GeometrieAnTRiASEx (hPr, true, NULL);
#endif // _TRiAS_VER < 0x0300

    if (SUCCEEDED (hrRet))
    {
    	AddAngleFeature();

#if defined(_DEBUG)
    long lCt;

    	pIOG->GetCnt (&lCt);
    	if (lCnt > lCt)
    		AddGrabFeature (m_lAktONr, lCnt - lCt);
#endif // _DEBUG

	Rectangle Rec;
	int iMarkGr;

		m_wTopObjs->GetMarkerSizeBS (&iMarkGr);
    	pIOG->RectangleToDraw2 ((RECT*)&Rec, iMarkGr);
    	if (!bAllRecInit)
    		AllRec = Rec;
    	else
    		AllRec = AllRec.Union (Rec);
    	DEX_RePaintRectWait (AllRec);
    	DEX_EndUndoLevel();
    }
    else
    	DEX_CancelUndoLevel (true);

    return hrRet;

} // RectangularAreaToTRiAS
