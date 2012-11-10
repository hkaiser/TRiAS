// Buffering für Elementarobjekte EPunkt, EKante und EFlaeche
// File: BUFFERING.CXX
// W. Mörtl


#include "BufferP.hxx"

#include "BasicFunctions.hxx"	// TurnDirection()
#include "ErrorCorrection.hxx"	// DoublePointCleaning()
#include "Koord.hxx"			// UmrechnungsFaktor()
#include "Strecke.hxx"			// GeradenSchnittPunkt()
#include "ClipList.hxx"			// ClipList

#include "Buffer.hxx"			// BufferExtension



#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG_HEAP)
// DebugHilfe
#include <malloc.h>
bool HEAPCHECK (void)
{
int iStatus = _heapchk();

	if (iStatus != _HEAPOK) 
		return false;

	return true;
}
#else
#define HEAPCHECK()
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// Puffer der Breite "dWidth" um den Punkt (x, y)
EFlaeche* BufferExtension :: PointBuffering (KoOrd x, KoOrd y, double dWidth, double dPrec,
											 CPIProxy* pPSt)
{
	_ASSERTE (dWidth > 0);

	if (dWidth <= 0) return NULL;

double dSekW = asin(dPrec/(2.*dWidth));	// halber Sektorwinkel (asin liefert 0 ... Pi)

	_ASSERTE (dSekW > 0.);

long lCnt = DtoL (Pi / dSekW) + 1;	// Anzahl der Stützpunkte des Kreispuffers
									// "+ 1", weil Anfangs- und Endpunkt gleich sind (27.10.98)

KoOrd* plXK = new KoOrd[lCnt];
KoOrd* plYK = new KoOrd[lCnt];

	if (! plXK || ! plYK)
	{
		DELETE_VEC (plXK);
		DEX_Error (RC_Buffering, EC_NOMEMORY);
		return NULL;
	}

DoublePair dUF = UmrechnungsFaktor (x, y, x, y, m_pCT);

	for (int i = 0; i < lCnt; i++)
	{
	double wi = 2.*Pi/(lCnt-1)*i;	// Pi ist in geokonst.hxx definiert

		plXK[i] = DtoL (x + dWidth*cos(wi)*dUF.X());
		plYK[i] = DtoL (y + dWidth*sin(wi)*dUF.Y());

		if (pPSt)
		{
		HRESULT hr = pPSt->IsCanceled();	// Abfrage, ob Pufferung abgebrochen werden soll

			if (FAILED(hr) || S_OK == hr) return NULL;

			hr = pPSt->IncrementPosition (NULL);
			if (FAILED(hr)) return NULL;
		}
	}

EFlaeche* pGO = new EFlaeche (plXK, plYK, lCnt);

	DELETE_VEC (plXK);
	DELETE_VEC (plYK);

	if (! pGO)
		DEX_Error (RC_Buffering, EC_NOMEMORY);

	return pGO;

} // PointBuffering


// --------------------------------------------------------------------------------------------
// Puffer der Breite "dWidth" um die Kante (plXK, plYK, lCnt)
// !!!! Kante darf keine Kollinearitäten besitzen !!!!
EFlaeche* BufferExtension :: LineBuffering (KoOrd* plXK, KoOrd* plYK, long lCnt, double dWidth,
							  BuffSide bsSide, ConvexMode cmMode, double dPrec, CPIProxy* pPSt)
{
	_ASSERTE (plXK != NULL);
	_ASSERTE (plYK != NULL);
	_ASSERTE (dWidth > 0.);	// pPSt kann NULL sein

	if (!plXK || !plYK ||
	    dWidth <= 0.)			// Breite ist ungültig
		return NULL;

// nachfolgend kann nicht DEX_GetObjContainer (lONr, ...) verwendet werden, da auch Puffer um
// Objekte möglich ist, die sich NICHT in der Datenbank befinden und somit auch auch keine
// Objektnummer besitzen
KoOrd xmin = MAXKOORD;
KoOrd xmax = -1;
KoOrd ymin = MAXKOORD;
KoOrd ymax = -1;

	for (long i = 0; i < lCnt; i++)
	{
		if (plXK[i] < xmin) xmin = plXK[i];
		if (plXK[i] > xmax) xmax = plXK[i];
		if (plYK[i] < ymin) ymin = plYK[i];
		if (plYK[i] > ymax) ymax = plYK[i];
	}

DoublePair dUF = UmrechnungsFaktor (xmin, ymax, xmax, ymin, m_pCT);

bool bAbbr;				// Operation wurde durch Anwender abgebrochen (true), sonst false
EFlaeche* pBE = NULL;	// Pufferelement

	if (BUFF_PLAIN != cmMode)
	{
	KoOrd lxv = -1, lyv = -1;	// plXK[lCnt-2], plYK[lCnt-2]

		if (plXK[0] == plXK[lCnt-1] && plYK[0] == plYK[lCnt-1])	// Kante geschlossen
		{
			lxv = plXK[lCnt-2];	// Stützpunkt VOR dem Anfangs-/Endpunkt
			lyv = plYK[lCnt-2];
		}

		pBE = BufferElement4 (lxv, lyv, plXK[0], plYK[0], plXK[1], plYK[1], dWidth, bsSide,
							  cmMode, dPrec, dUF);
	}
	else
	{
	int iBR = TurnDirection (plXK[0], plYK[0], plXK[1], plYK[1], plXK[2], plYK[2]);

		_ASSERTE (iBR != 0);

		if (1 == iBR)
			pBE = BufferElement2 (plXK[0], plYK[0], plXK[1], plYK[1], plXK[2], plYK[2], dWidth,
								  bsSide, cmMode, dPrec, dUF);
		else		// TurnDirection() == -1
			pBE = BufferElement3 (plXK[0], plYK[0], plXK[1], plYK[1], plXK[2], plYK[2], dWidth,
								  bsSide, cmMode, dPrec, dUF);
	}

	if (NULL == pBE) return NULL;	// Anfangsfläche des Puffers nicht bildbar

EFlaeche BuffArea = EFlaeche (*pBE);	// Anfangsfläche des Puffers

	DELETE_OBJ (pBE);


// Anfangsfläche schrittweise mit Pufferelementen zur Pufferfläche vereinen; mit Routine
// TurnDirection() wird festgestellt, ob am mittleren der 3 Punkte eine Konvex- (+1) oder
// Konkav-Ecke (-1) vorliegt
long lAInd;		// Index von plXK und plYK , mit dem begonnen werden soll

	(BUFF_PLAIN != cmMode) ? (lAInd = 0) : (lAInd = 1);

	for (i = lAInd; i < lCnt-2; i++)
	{
	int iBR = TurnDirection (plXK[i], plYK[i], plXK[i+1], plYK[i+1], plXK[i+2], plYK[i+2]);

		_ASSERTE (iBR != 0);

		if (1 == iBR)
			pBE = BufferElement2 (plXK[i], plYK[i], plXK[i+1], plYK[i+1], plXK[i+2], plYK[i+2],
								  dWidth, bsSide, cmMode, dPrec, dUF);
		else		// TurnDirection() == -1
			pBE = BufferElement3 (plXK[i], plYK[i], plXK[i+1], plYK[i+1], plXK[i+2], plYK[i+2],
								  dWidth, bsSide, cmMode, dPrec, dUF);

		if (NULL == pBE) continue;	// entartetes Pufferelement
			
	EFlaeche* pBA = BuffArea.FlaechenVereinigung (pBE, bAbbr, NULL, true);	// Zwischenergebnis

		if (NULL == pBA)	// keine gültige Flächenvereinigung
		{
			DEX_Error (RC_Buffering, EC_NOBUFFER);
			DELETE_OBJ (pBE);
			return NULL;
		}	

		BuffArea = EFlaeche (*pBA);
		DELETE_OBJ (pBA);

		PartialCleaningForLines (&BuffArea.KA(0));

		DELETE_OBJ (pBE);

		if (pPSt)
		{		
		HRESULT hr = pPSt->IsCanceled();	// Abfrage, ob Pufferung abgebrochen werden soll

			if (FAILED(hr) || S_OK == hr) return NULL;

			hr = pPSt->IncrementPosition (NULL);
			if (FAILED(hr)) return NULL;
		}
	}

// Einbeziehung des letzten Pufferelements
KoOrd lxn = -1, lyn = -1;	// plXK[1], plYK[1]

	if (BUFF_PLAIN == cmMode &&								// Ecke abgeflacht und
		plXK[0] == plXK[lCnt-1] && plYK[0] == plYK[lCnt-1])	// Kante geschlossen
	{
		lxn = plXK[1];	// Stützpunkt NACH dem Anfangs-/Endpunkt
		lyn = plYK[1];
	}
	
	pBE = BufferElement5 (plXK[lCnt-2], plYK[lCnt-2], plXK[lCnt-1], plYK[lCnt-1], lxn, lyn,
						  dWidth, bsSide, cmMode, dPrec, dUF);

EFlaeche* pBA = NULL;	// zurückgegebene Pufferfläche

	if (pBE)       // Pufferelement nicht entartet
	{
		pBA = BuffArea.FlaechenVereinigung (pBE, bAbbr, NULL, true);

		DELETE_OBJ (pBE);

		if (NULL == pBA)	// keine gültige Flächenvereinigung
		{
			DEX_Error (RC_Buffering, EC_NOBUFFER);
			return NULL;
		}	

		PartialCleaningForLines (&pBA->KA(0));

		if (pPSt && FAILED(pPSt->IncrementPosition(NULL)))
			return NULL;
	}

	return pBA;

} // LineBuffering


// --------------------------------------------------------------------------------------------
// Puffer der Breite "dWidth" um die Fläche (plXK, plYK, lCnt);
// !!!! Außenkontur der Fläche darf keine Kollinearitäten besitzen !!!!
EFlaeche* BufferExtension :: AreaBuffering (KoOrd* plXK, KoOrd* plYK, long lCnt, double dWidth,
							  BuffSide bsSide, ConvexMode cmMode, double dPrec, CPIProxy* pPSt)
{
	_ASSERTE (plXK != NULL);
	_ASSERTE (plYK != NULL);	// pPSt kann NULL sein
	_ASSERTE (dWidth != 0.);

	if (!plXK || !plYK || 0 == dWidth)
		return NULL;

// Ermittlung des Umrechnungsfaktors
// nachfolgend kann nicht DEX_GetObjContainer (lONr, ...) verwendet werden, da auch Puffer um
// Objekte möglich ist, die sich NICHT in der Datenbank befinden und somit auch auch keine
// Objektnummer besitzen
KoOrd xmin = MAXKOORD;
KoOrd xmax = -1;
KoOrd ymin = MAXKOORD;
KoOrd ymax = -1;

	for (long i = 0; i < lCnt; i++)
	{
		if (plXK[i] < xmin) xmin = plXK[i];
		if (plXK[i] > xmax) xmax = plXK[i];
		if (plYK[i] < ymin) ymin = plYK[i];
		if (plYK[i] > ymax) ymax = plYK[i];
	}

DoublePair dUF = UmrechnungsFaktor (xmin, ymax, xmax, ymin, m_pCT);


// Pufferbildung
bool bAbbr;				// Operation wurde durch Anwender abgebrochen (true), sonst false
EFlaeche* pBE = NULL;	// Pufferelement
EFlaeche BuffArea = EFlaeche();	// die vereinten Pufferelemente

	if (BUFF_TIP == cmMode)
		StartValuesForTipMode (plXK[lCnt-2], plYK[lCnt-2], plXK[0], plYK[0], plXK[1], plYK[1],
							   fabs(dWidth), dUF);

	// Pufferelemente schritweise vereinen; mit Routine TurnDirection() wird festgestellt, ob
	// am mittleren der 3 Punkte eine Konvex- (+1) oder Konkav-Ecke (-1) vorliegt
	for (i = 0; i < lCnt-2; i++)
	{
	int iBR = TurnDirection (plXK[i], plYK[i], plXK[i+1], plYK[i+1], plXK[i+2], plYK[i+2]);

		_ASSERTE (0 != iBR);

		if (1 == iBR)
			pBE = BufferElement2 (plXK[i], plYK[i], plXK[i+1], plYK[i+1], plXK[i+2], plYK[i+2],
								  fabs(dWidth), bsSide, cmMode, dPrec, dUF);
		else	// TurnDirection() == -1
			pBE = BufferElement3 (plXK[i], plYK[i], plXK[i+1], plYK[i+1], plXK[i+2], plYK[i+2],
								  fabs(dWidth), bsSide, cmMode, dPrec, dUF);

		if (NULL == pBE) continue;	// Pufferelement ist entartet

		if (BuffArea.ASP() > 0)
		{
		EFlaeche* pBA = BuffArea.FlaechenVereinigung (pBE, bAbbr, NULL, true);	// Zwischenergebnis mit Inseln

			if (NULL == pBA)	// keine gültige Flächenvereinigung
			{
				DEX_Error (RC_Buffering, EC_NOBUFFER);
				DELETE_OBJ (pBE);
				return NULL;
			}	

			BuffArea = EFlaeche (*pBA);
			DELETE_OBJ (pBA);

			PartialCleaningForLines (&BuffArea.KA(0));
		}
		else
			BuffArea = EFlaeche (*pBE);

		DELETE_OBJ (pBE);

		if (pPSt)
		{
		HRESULT hr = pPSt->IsCanceled();	// Abfrage, ob Pufferung abgebrochen werden soll

			if (FAILED(hr) || S_OK == hr) return NULL;

			hr = pPSt->IncrementPosition (NULL);
			if (FAILED(hr)) return NULL;
		}
	} //for


// Einbeziehung des letzten Pufferelements
int iBR = TurnDirection (plXK[lCnt-2], plYK[lCnt-2], plXK[0], plYK[0], plXK[1], plYK[1]);

	_ASSERTE (0 != iBR);

	if (1 == iBR)
		pBE = BufferElement2 (plXK[lCnt-2], plYK[lCnt-2], plXK[0], plYK[0], plXK[1], plYK[1],
							  fabs(dWidth), bsSide, cmMode, dPrec, dUF);
	else	// TurnDirection() == -1
		pBE = BufferElement3 (plXK[lCnt-2], plYK[lCnt-2], plXK[0], plYK[0], plXK[1], plYK[1],
							  fabs(dWidth), bsSide, cmMode, dPrec, dUF);

	if (pBE)	// letztes Pufferelement nicht entartet
	{
		if (BuffArea.ASP() > 0)
		{
		EFlaeche* pBA = BuffArea.FlaechenVereinigung (pBE, bAbbr, NULL, true);

			if (NULL == pBA)	// keine gültige Flächenvereinigung
			{
				DEX_Error (RC_Buffering, EC_NOBUFFER);
				DELETE_OBJ (pBE);
				return NULL;
			}	

			BuffArea = EFlaeche (*pBA);
			DELETE_OBJ (pBA);

			PartialCleaningForLines (&BuffArea.KA(0));
		}
		else
			BuffArea = EFlaeche (*pBE);

		DELETE_OBJ (pBE);

		if (pPSt && FAILED(pPSt->IncrementPosition(NULL)))
			return NULL;
	}

// Die vereinigten Pufferelemente BuffArea in Abhängigkeit vom Vorzeichen der Pufferbreite mit
// dem zu puffernden Objekt RefObject vereinigen oder schneiden.
EFlaeche RefObject = EFlaeche (plXK, plYK, lCnt);
EFlaeche* pBA = NULL;

	if (dWidth > 0.)
		pBA = BuffArea.FlaechenVereinigung (&RefObject, bAbbr, NULL, false);	// ohne Inseln
	else
		pBA = BuildInsideBuffer (&BuffArea, &RefObject);

	if (NULL == pBA)
		DEX_Error (RC_Buffering, EC_NOBUFFER);

	return pBA;

} // AreaBuffering



///////////////////////////////////////////////////////////////////////////////////////////////
/*
// Pufferelement an einer konkaven Ecke der Außenkontur einer Fläche;
// Pufferelement wird aus einem Rechteck der Länge der Strecke (lX1,lY1)-(lX2,lY2) und der
// Breite "2*dWidth" gebildet, an dessen Querseite bei (lX2,lY2) entsprechend cmMode verschiedene
// Näherungen gewählt werden
EFlaeche* BufferExtension :: BufferElement1 (KoOrd lX1, KoOrd lY1, KoOrd lX2, KoOrd lY2, 
	   KoOrd lX3, KoOrd lY3, double dWidth, BuffSide bsSide, ConvexMode cmMode, DoublePair dUF)
{
	_ASSERTE (dWidth > 0);

double dFak = dUF.Y() / dUF.X();	// Relation bei geodätischen Koordinaten
double x1 = lX1 * dFak;
double y1 = lY1;
double x2 = lX2 * dFak;
double y2 = lY2;
double x3 = lX3 * dFak;
double y3 = lY3;
double dLength = sqrt ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

	if (0. == dLength) return NULL;     // entartetes Pufferelement

double k0 = dWidth / dLength;	// Hilfswerte
double k1 = k0 * (x2 - x1);
double k2 = k0 * (y2 - y1);
KoOrd lxb[6], lyb[6];     // Koordinaten des Pufferelementes

	lxb[0] = DtoL (lX1 - k2*dUF.X());	lyb[0] = DtoL (y1 + k1*dUF.Y());
	lxb[1] = DtoL (lX1 + k2*dUF.X());	lyb[1] = DtoL (y1 - k1*dUF.Y());
	lxb[2] = DtoL (lX2 + k2*dUF.X());	lyb[2] = DtoL (y2 - k1*dUF.Y());

	// Für den Fall, daß (lX1,lY1),(lX2,lY2),(lX3,lY3) "fast" kollinear sind (Außenwinkel am
	// Punkt (lX2,lY2) ist fast genau 180°), wird aus Rundungsgründen noch der Punkt
	// lxb[3],lyb[3] eingefügt. Dies ist i.d.R. der Punkt (lX3,lY3).
	lxb[3] = lX3;	                    lyb[3] = lY3;
	lxb[4] = DtoL (lX2 - k2*dUF.X());	lyb[4] = DtoL (y2 + k1*dUF.Y());

// Wenn aber der Außenwinkel bei (lX2,lY2) kleiner/gleich als 90° ist, würde sich das
// Pufferelement selbst überschneiden. Die Bewegungsrichtung von
// lxb/lyb[2],lxb/lyb[3],lxb/lyb[4] ist in diesem Fall mathematisch negativ oder Null.
int n;	// Anzahl der Ecken des Pufferelements

	if (TurnDirection (lxb[2], lyb[2], lxb[3], lyb[3], lxb[4], lyb[4]) > 0)
	{
		lxb[5] = lxb[0];	lyb[5] = lyb[0];
		n = 6;
	}
	else
	{
		lxb[3] = lxb[4];	lyb[3] = lyb[4];
		lxb[4] = lxb[0];	lyb[4] = lyb[0];
		n = 5;
	}

	if (BUFF_TIP == cmMode)	// konvexe Ecken sollen "spitz" ausgeformt werden
	{
		if (m_bPosTurn)		// aktuelle Kantenstrecke dreht sich im Vergleich zur
		{					// VORHERGEHENDEN Strecke mathematisch positiv
			lxb[1] = m_px;
			lyb[1] = m_py;
		}

		m_bPosTurn = false;
		m_px = lxb[n-2];
		m_py = lyb[n-2];
	}

EFlaeche* pBE = new EFlaeche (lxb, lyb, n);    // Pufferelement

	if (pBE)
		DoublePointCleaning (&pBE->KA(0));	// 02.03.99
	else
		DEX_Error (RC_Buffering, EC_NOMEMORY);

	return pBE;

} // BufferElement1
*/

// --------------------------------------------------------------------------------------------
// Pufferelement an einer konvexen Ecke der Außenkontur einer Fläche bzw. für Strecke einer
// Kante, deren anschließende Strecke eine mathematisch positive Drehung vollführt;
// das Pufferelement wird aus einem Rechteck der Länge der Strecke (lX1,lY1)-(lX2,lY2) und der
// Breite 2*dWidth gebildet, an dessen Querseite bei (lX2,lY2) entsprechend cmMode verschiedene
// Näherungen gewählt werden
EFlaeche* BufferExtension :: BufferElement2 (KoOrd lX1, KoOrd lY1, KoOrd lX2, KoOrd lY2,
										  KoOrd lX3, KoOrd lY3, double dWidth, BuffSide bsSide,
										  ConvexMode cmMode, double dPrec, DoublePair dUF)
{
	_ASSERTE (dWidth > 0);

double dFak = dUF.Y() / dUF.X();	// Relation bei geodätischen Koordinaten
double x1 = lX1 * dFak;
double y1 = lY1;
double x2 = lX2 * dFak;
double y2 = lY2;
double x3 = lX3 * dFak;
double y3 = lY3;
double dLength12 = sqrt ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
double dLength23 = sqrt ((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));

	if (0. == dLength12 || 0. == dLength23)
		return NULL;     // entartetes Pufferelement

double k10 = dWidth / dLength12;	// Hilfswerte
double k11 = k10 * (x2 - x1);
double k12 = k10 * (y2 - y1);
double k20 = dWidth / dLength23;
double k21 = k20 * (x3 - x2);
double k22 = k20 * (y3 - y2);

double xb[7], yb[7];     // Koordinaten des Pufferelementes

	xb[0] = lX1 - k12*dUF.X();	yb[0] = y1 + k11*dUF.Y();	// P0
	xb[1] = lX1 + k12*dUF.X();	yb[1] = y1 - k11*dUF.Y();	// P1
	xb[2] = lX2 + k12*dUF.X();	yb[2] = y2 - k11*dUF.Y();	// P2
	xb[3] = 0.;					yb[3] = 0.;					// P3 wird (evtl.) noch berechnet
	xb[4] = lX2 + k22*dUF.X();	yb[4] = y2 - k21*dUF.Y();	// P4
	xb[5] = lX2 - k12*dUF.X();	yb[5] = y2 + k11*dUF.Y();	// P5
	xb[6] = xb[0];             	yb[6] = yb[0];				// P6

	switch (cmMode)
	{
		case BUFF_ARC:		// quasi-kreisförmig (n-Eck)
			return ArcModePositive (xb, yb, lX2, lY2, dUF, dPrec);

		case BUFF_KITE:		// Drachenviereck
			return KiteModePositive (xb, yb, lX2, lY2, lX3, lY3, k11, k12, dUF);

		case BUFF_TIP:		// spitz
			return TipModePositive (xb, yb, lX3, lY3, k21, k22, dUF);

		case BUFF_PLAIN:	// abgeflacht
			return PlainModePositive (xb, yb, lX2, lY2, lX3, lY3);
	}

	_ASSERTE (false);
	return KiteModePositive (xb, yb, lX2, lY2, lX3, lY3, k11, k12, dUF);

} // BufferElement2


// --------------------------------------------------------------------------------------------
// Pufferelement für Strecke einer Kante, deren anschließende Strecke eine mathematisch
// negative Drehung vollführt;
// das Pufferelement wird aus einem Rechteck der Länge der Strecke (lX1,lY1)-(lX2,lY2) und der
// Breite 2*dWidth gebildet, an dessen Querseite bei (lX2,lY2) entsprechend cmMode verschiedene
// Näherungen gewählt werden
EFlaeche* BufferExtension :: BufferElement3 (KoOrd lX1, KoOrd lY1, KoOrd lX2, KoOrd lY2,
										  KoOrd lX3, KoOrd lY3, double dWidth, BuffSide bsSide,
										  ConvexMode cmMode, double dPrec, DoublePair dUF)
{
	_ASSERTE (dWidth > 0);

double dFak = dUF.Y() / dUF.X();	// Relation bei geodätischen Koordinaten
double x1 = lX1 * dFak;
double y1 = lY1;
double x2 = lX2 * dFak;
double y2 = lY2;
double x3 = lX3 * dFak;
double y3 = lY3;
double dLength12 = sqrt ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
double dLength23 = sqrt ((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));

	if (0. == dLength12 || 0. == dLength23)
		return NULL;     // entartetes Pufferelement

double k10 = dWidth / dLength12;	// Hilfswerte
double k11 = k10 * (x2 - x1);
double k12 = k10 * (y2 - y1);
double k20 = dWidth / dLength23;
double k21 = k20 * (x3 - x2);
double k22 = k20 * (y3 - y2);
double xb[7], yb[7];	// Koordinaten des Pufferelementes

	xb[0] = lX1 - k12*dUF.X();	yb[0] = y1 + k11*dUF.Y();	// P0
	xb[1] = lX1 + k12*dUF.X();	yb[1] = y1 - k11*dUF.Y();	// P1
	xb[2] = lX2 + k12*dUF.X();	yb[2] = y2 - k11*dUF.Y();	// P2
	xb[3] = lX2 - k22*dUF.X();	yb[3] = y2 + k21*dUF.Y();	// P3
	xb[4] = 0.;					yb[4] = 0.;					// P4 wird (evtl.) noch berechnet
	xb[5] = lX2 - k12*dUF.X();	yb[5] = y2 + k11*dUF.Y();	// P5
	xb[6] = xb[0];				yb[6] = yb[0];				// P6

	switch (cmMode)
	{
		case BUFF_ARC:		// quasi-kreisförmig (n-Eck)
			return ArcModeNegative (xb, yb, lX2, lY2, dUF, dPrec);

		case BUFF_KITE:		// Drachenviereck
			return KiteModeNegative (xb, yb, lX2, lY2, lX3, lY3, k11, k12, dUF);

		case BUFF_TIP:		// spitz
			return TipModeNegative (xb, yb, lX3, lY3, k21, k22, dUF);

		case BUFF_PLAIN:	// abgeflacht
			return PlainModeNegative (xb, yb, lX2, lY2, lX3, lY3);
	}

	_ASSERTE (false);
	return KiteModeNegative (xb, yb, lX2, lY2, lX3, lY3, k11, k12, dUF);

} // BufferElement3


// --------------------------------------------------------------------------------------------
// Pufferelement am Beginn einer Kante;
// entsprechend cmMode werden verschiedene Näherungen gewählt
EFlaeche* BufferExtension :: BufferElement4 (KoOrd lX0, KoOrd lY0, KoOrd lX1, KoOrd lY1,
										  KoOrd lX2, KoOrd lY2, double dWidth, BuffSide bsSide,
										  ConvexMode cmMode, double dPrec, DoublePair dUF)
{
	_ASSERTE (dWidth > 0);
	_ASSERTE (cmMode != BUFF_PLAIN); // für cmMode == BUFF_PLAIN ist kein BufferElement4 nötig

double dFak = dUF.Y() / dUF.X();	// Relation bei geodätischen Koordinaten
double x1 = lX1 * dFak;
double y1 = lY1;
double x2 = lX2 * dFak;
double y2 = lY2;
double dLength = sqrt ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

	if (0. == dLength) return NULL;     // entartetes Pufferelement

double k0 = dWidth / dLength;	// Hilfswerte
double k1 = k0 * (x2 - x1);
double k2 = k0 * (y2 - y1);
double xb[5], yb[5];	// Koordinaten des Pufferelementes

	xb[0] = lX1 - k2*dUF.X();	yb[0] = y1 + k1*dUF.Y();
	xb[4] = lX1 + k2*dUF.X();	yb[4] = y1 - k1*dUF.Y();

	switch (cmMode)
	{
		case BUFF_ARC:		// quasi-kreisförmig (n-Eck)
			return ArcModeStart (xb, yb, lX1, lY1, k1, k2, dUF, dPrec);

		case BUFF_KITE:		// Drachenviereck
			return KiteModeStart (xb, yb, lX1, lY1, k1, k2, dUF);

		case BUFF_TIP:		// spitz
			return TipModeStart (xb, yb, lX0, lY0, lX1, lY1, lX2, lY2, dWidth, k1, k2, dUF);
	}

	_ASSERTE (false);
	return KiteModeStart (xb, yb, lX1, lY1, k1, k2, dUF);

} // BufferElement4


// --------------------------------------------------------------------------------------------
// Pufferelement am Ende einer Kante;
// das Pufferelement wird aus einem Rechteck der Länge der Strecke (lX1,lY1)-(lX2,lY2) und der
// Breite 2*dWidth gebildet, an dessen Querseite bei (lX2,lY2) entsprechend cmMode verschiedene
// Näherungen gewählt werden
EFlaeche* BufferExtension :: BufferElement5 (KoOrd lX1, KoOrd lY1, KoOrd lX2, KoOrd lY2,
										  KoOrd lX3, KoOrd lY3, double dWidth, BuffSide bsSide,
										  ConvexMode cmMode, double dPrec, DoublePair dUF)
{
	_ASSERTE (dWidth > 0);

double dFak = dUF.Y() / dUF.X();
double x1 = lX1 * dFak;
double y1 = lY1;
double x2 = lX2 * dFak;
double y2 = lY2;
double dLength = sqrt ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

	if (0. == dLength) return NULL;     // entartetes Pufferelement

double k0 = dWidth / dLength;	// Hilfswerte
double k1 = k0 * (x2 - x1);
double k2 = k0 * (y2 - y1);
double xb[7], yb[7];	// Koordinaten des Pufferelementes

	xb[0] = lX1 - k2*dUF.X();	yb[0] = y1 + k1*dUF.Y();
	xb[1] = lX1 + k2*dUF.X();	yb[1] = y1 - k1*dUF.Y();
	xb[2] = lX2 + k2*dUF.X();	yb[2] = y2 - k1*dUF.Y();
	xb[6] = lX2 - k2*dUF.X();	yb[6] = y2 + k1*dUF.Y();

	switch (cmMode)
	{
		case BUFF_ARC:		// quasi-kreisförmig (n-Eck)
			return ArcModeStop (xb, yb, lX2, lY2, k1, k2, dUF, dPrec);

		case BUFF_KITE:		// Drachenviereck
			return KiteModeStop (xb, yb, lX2, lY2, k1, k2, dUF);

		case BUFF_TIP:		// spitz
			return TipModeStop (xb, yb, k1, k2, dUF);

		case BUFF_PLAIN:	// abgeflacht
			return PlainModeStop (xb, yb, lX1, lY1, lX2, lY2, lX3, lY3, dWidth, dUF);
	}

	_ASSERTE (false);
	return KiteModeStop (xb, yb, lX2, lY2, k1, k2, dUF);

} // BufferElement5


// --------------------------------------------------------------------------------------------
// mathematisch positive konvexe Ecke bei (lX2,lY2) als Quasi-Kreisbogen (n-Eck) ausführen
EFlaeche* ArcModePositive (double* xb, double* yb, KoOrd lX2, KoOrd lY2, DoublePair dUF,
						   double dPrec)
{
KoOrd lxb[7], lyb[7];	// KoOrd-Koordinaten des Pufferelementes

	for (long i = 0; i < 7; i++)
	{
		lxb[i] = DtoL (xb[i]);
		lyb[i] = DtoL (yb[i]);
	}

EFlaeche* pBE = new EFlaeche (lxb, lyb, 3);    // Pufferelement (P0 ... P2)

	if (pBE)
	{
		KreisbogenApprox (pBE, lX2, lY2, xb[2], yb[2], xb[4], yb[4], dUF, dPrec);
		pBE->AddPunkt (&lxb[4], &lyb[4], 1, -1, -1);
		pBE->AddPunkt (&lxb[5], &lyb[5], 1, -1, -1);
//		pBE->AddPunkt (&lxb[6], &lyb[6], 1, -1, -1);
		pBE->AddPunkt (&lxb[0], &lyb[0], 1, -1, -1);

		DoublePointCleaning (&pBE->KA(0));	// 02.03.99
	}
	else
		DEX_Error (RC_Buffering, EC_NOMEMORY);

	return pBE;

} // ArcModePositive


// --------------------------------------------------------------------------------------------
// mathematisch negative konvexe Ecke bei (lX2,lY2) als Quasi-Kreisbogen (n-Eck) ausführen
EFlaeche* ArcModeNegative (double* xb, double* yb, KoOrd lX2, KoOrd lY2, DoublePair dUF,
						   double dPrec)
{
KoOrd lxb[7], lyb[7];	// KoOrd-Koordinaten des Pufferelementes

	for (long i = 0; i < 7; i++)
	{
		lxb[i] = DtoL (xb[i]);
		lyb[i] = DtoL (yb[i]);
	}

EFlaeche* pBE = new EFlaeche (lxb, lyb, 4);    // Pufferelement (P0 ... P3)

	if (pBE)
	{
		KreisbogenApprox (pBE, lX2, lY2, xb[3], yb[3], xb[5], yb[5], dUF, dPrec);
		pBE->AddPunkt (&lxb[5], &lyb[5], 1, -1, -1);
//		pBE->AddPunkt (&lxb[6], &lyb[6], 1, -1, -1);
		pBE->AddPunkt (&lxb[0], &lyb[0], 1, -1, -1);

		DoublePointCleaning (&pBE->KA(0));	// 02.03.99
	}
	else
		DEX_Error (RC_Buffering, EC_NOMEMORY);

	return pBE;

} // ArcModeNegative


// --------------------------------------------------------------------------------------------
// am Beginn einer Kante einen Quasi-Kreisbogen (n-Eck) bilden
EFlaeche* ArcModeStart (double* xb, double* yb, KoOrd lX1, KoOrd lY1, double k1, double k2,
						DoublePair dUF, double dPrec)
{
	_ASSERTE (xb != NULL);
	_ASSERTE (yb != NULL);

KoOrd lxb[5], lyb[5];	// KoOrd-Koordinaten des Pufferelementes

	lxb[0] = DtoL (xb[0]);		lyb[0] = DtoL (yb[0]);
	lxb[4] = DtoL (xb[4]);		lyb[4] = DtoL (yb[4]);

EFlaeche* pBE = new EFlaeche (lxb, lyb, 1);    // Pufferelement (P0)

	if (pBE)
	{
		// wenn pBE durch KreisbogenApprox() keine weiteren Punkte erhalten hat, dann
		// wenigstens noch einen Zusatz-Stützpunkt
		if (! KreisbogenApprox (pBE, lX1, lY1, xb[0], yb[0], xb[4], yb[4], dUF, dPrec) ||
			pBE->ASP() <= 1)
		{
			lxb[1] = DtoL (lX1 - k1*dUF.X());	lyb[1] = DtoL (lY1 - k2*dUF.Y());
			pBE->AddPunkt (&lxb[1], &lyb[1], 1, -1, -1);
		}

		pBE->AddPunkt (&lxb[4], &lyb[4], 1, -1, -1);
		pBE->AddPunkt (&lxb[0], &lyb[0], 1, -1, -1);

		DoublePointCleaning (&pBE->KA(0));	// 02.03.99
	}
	else
		DEX_Error (RC_Buffering, EC_NOMEMORY);

	return pBE;

} // ArcModeStart


// --------------------------------------------------------------------------------------------
// am Ende einer Kante einen Quasi-Kreisbogen (n-Eck) bilden
EFlaeche* ArcModeStop (double* xb, double* yb, KoOrd lX2, KoOrd lY2, double k1, double k2,
					   DoublePair dUF, double dPrec)
{
KoOrd lxb[7], lyb[7];	// KoOrd-Koordinaten des Pufferelementes

	lxb[0] = DtoL (xb[0]);		lyb[0] = DtoL (yb[0]);
	lxb[1] = DtoL (xb[1]);		lyb[1] = DtoL (yb[1]);
	lxb[2] = DtoL (xb[2]);		lyb[2] = DtoL (yb[2]);
	lxb[6] = DtoL (xb[6]);		lyb[6] = DtoL (yb[6]);

EFlaeche* pBE = new EFlaeche (lxb, lyb, 3);    // Pufferelement (P0 ... P2)

	if (pBE)
	{
		// wenn pBE durch KreisbogenApprox() keine weiteren Punkte erhalten hat, dann
		// wenigstens noch einen Zusatz-Stützpunkt
		if (! KreisbogenApprox (pBE, lX2, lY2, xb[2], yb[2], xb[6], yb[6], dUF, dPrec))
		{
			lxb[3] = DtoL (lX2 + k1*dUF.X());	lyb[3] = DtoL (lY2 + k2*dUF.Y());
			pBE->AddPunkt (&lxb[3], &lyb[3], 1, -1, -1);
		}

		pBE->AddPunkt (&lxb[6], &lyb[6], 1, -1, -1);
		pBE->AddPunkt (&lxb[0], &lyb[0], 1, -1, -1);

		DoublePointCleaning (&pBE->KA(0));	// 02.03.99
	}
	else
		DEX_Error (RC_Buffering, EC_NOMEMORY);

	return pBE;

} // ArcModeStop


// --------------------------------------------------------------------------------------------
// mathematisch positive konvexe Ecke bei (lX2,lY2) als Drachenviereck ausführen;
// 2 Punkte dieses Vierecks (P2 und P5) sind die schon vorhandenen Punkte der Querseite des
// Rechtecks, der dritte Punkt (P4) ist ein Eckpunkt des nächsten Rechtecks, das um die Strecke
// (lX2,lY2)-(lX3,lY3) als Pufferelement gelegt wird und der vierte Punkt (P3) hat (wie alle
// anderen Punkte P2, P4 und P5) von dem konvexen Eckpunkt den Abstand "dWidth" und liegt auf
// der Winkelhalbierenden der konvexen Ecke, ist somit von P2 und P4 gleichweit entfernt
EFlaeche* KiteModePositive (double* xb, double* yb, KoOrd lX2, KoOrd lY2, KoOrd lX3, KoOrd lY3,
							double k11, double k12, DoublePair dUF)
{
double dFak = dUF.Y() / dUF.X();	// Relation bei geodätischen Koordinaten
KoOrd lAbst24 = AbstandPktPktM (DtoL(xb[2]), DtoL(yb[2]), DtoL(xb[4]), DtoL(yb[4]));
int n = 7;						// Anzahl der Ecken des Pufferelements

	// Wenn P2 und P4 dichter als iBuEps liegen, wird P3 nicht mehr berechnet und P2 durch
	// Verschieben der Punktefolge gelöscht; außerdem wird (lX3,lY3) eingefügt, um evtl.
	// Rundungsfehlern entgegenzutreten, die eine Lücke zwischen P4(alt)/P2(neu) und dem
	// Pufferelement der nächsten Strecke (lX2,lY2)-(lX3,lY3) zur Folge haben können.
	if (lAbst24 <= iBuEps)
	{
		xb[2] = xb[4];	yb[2] = yb[4];
		xb[3] = lX3;	yb[3] = lY3;	// Ergänzung, um Rundungsfehlern entgegenzutreten
		xb[4] = xb[5];	yb[4] = yb[5];
		xb[5] = xb[0];	yb[5] = yb[0];
		n = 6;
	}

	// Wenn der halbe Abstand zwischen P2 und P4 höchstens iBuEps beträgt, wird P3 nicht mehr
	// berechnet; außerdem wird (lX3,lY3) eingefügt (s.o.).
	else if (lAbst24 / 2 <= iBuEps)
	{
		xb[3] = xb[4];	yb[3] = yb[4];
		xb[4] = lX3;	yb[4] = lY3;	// Ergänzung, um Rundungsfehlern entgegenzutreten
	}

	// Berechnung von P3, wenn der halbe Abstand zwischen P2 und P4 größer als iBuEps ist
	// Berechnung des Winkels an der konvexen Ecke
	else
	{
	double a1 = lY2 - yb[2]; 			// Koeffizient vor x-Glied der Geradengleichung P2-(lX2,lY2)
	double b1 = (xb[2] - lX2) * dFak;	// Koeffizient vor y-Glied der Geradengleichung P2-(lX2,lY2)
	double a2 = lY2 - yb[4];			// Koeffizient vor x-Glied der Geradengleichung (lX2,lY2)-P4
	double b2 = (xb[4] - lX2) * dFak;	// Koeffizient vor y-Glied der Geradengleichung (lX2,lY2)-P4
	double ne = a1*a2 + b1*b2;	// Nenner für Berechnung des Tangens des Winkels
	double wi;      // Winkel an der konvexen Ecke
	double si;      // sin (wi / 2.)
	double co;      // cos (wi / 2.)

		if (ne != 0)
		{
			wi = atan ((a1*b2 - a2*b1) / ne);	// atan liefert Werte zwischen -Pi/2 bis Pi/2
			if (wi < 0) wi += Pi;				// deshalb Transformation bei negativen Winkeln
			si = sin (wi / 2.);					//  mit Pi
			co = cos (wi / 2.);
		}
		else    // Winkel von 90°
		{                        
			si = dTrigonom45;  // sin (45°)
			co = dTrigonom45;  // cos (45°)
		}

		xb[3] = lX2 + (si*k11 + co*k12) * dUF.X();
		yb[3] = lY2 - (co*k11 - si*k12) * dUF.Y();
	}

KoOrd lxb[7], lyb[7];	// KoOrd-Koordinaten des Pufferelementes

	for (long i = 0; i < n; i++)
	{
		lxb[i] = DtoL (xb[i]);
		lyb[i] = DtoL (yb[i]);
	}

EFlaeche* pBE = new EFlaeche (lxb, lyb, n);    // Pufferelement

	if (pBE)
		DoublePointCleaning (&pBE->KA(0));	// 02.03.99
	else
		DEX_Error (RC_Buffering, EC_NOMEMORY);

	return pBE;

} // KiteModePositive


// --------------------------------------------------------------------------------------------
// mathematisch negative konvexe Ecke bei (lX2,lY2) als Drachenviereck ausführen;
// 2 Punkte dieses Vierecks (P2 und P5) sind die schon vorhandenen Punkte der Querseite des
// Rechtecks, der dritte Punkt (P3) ist ein Eckpunkt des nächsten Rechtecks, das um die Strecke
// (lX2,lY2)-(lX3,lY3) als Pufferelement gelegt wird und der vierte Punkt (P4) hat (wie alle
// anderen Punkte P2, P3 und P5) von dem konvexen Eckpunkt den Abstand "dWidth" und liegt auf
// der Winkelhalbierenden der konvexen Ecke, ist somit von P3 und P5 gleichweit entfernt
EFlaeche* KiteModeNegative (double* xb, double* yb, KoOrd lX2, KoOrd lY2, KoOrd lX3, KoOrd lY3,
							double k11, double k12, DoublePair dUF)
{
double dFak = dUF.Y() / dUF.X();	// Relation bei geodätischen Koordinaten
KoOrd lAbst35 = AbstandPktPktM (DtoL(xb[3]), DtoL(yb[3]), DtoL(xb[5]), DtoL(yb[5]));
int n = 7;						// Anzahl der Ecken des Pufferelements

	// Wenn P3 und P5 dichter als iBuEps liegen, wird P4 nicht mehr berechnet und P5 durch
	// Verschieben der Punktefolge gelöscht; außerdem wird (lX3,lY3) eingefügt, um evtl.
	// Rundungsfehlern entgegenzutreten, die eine Lücke zwischen P3(alt)/P4(neu) und dem
	// Pufferelement der nächsten Strecke (lX2,lY2)-(lX3,lY3) zur Folge haben können.
	if (lAbst35 <= iBuEps)
	{
		xb[5] = xb[0];		yb[5] = yb[0];
		xb[4] = xb[3];		yb[4] = yb[3];
		xb[3] = lX3;		yb[3] = lY3;	// Ergänzung, um Rundungsfehlern entgegenzutreten
		n = 6;
	}

	// Wenn der halbe Abstand zwischen P3 und P5 höchstens iBuEps beträgt, wird P4 nicht mehr
	// berechnet; außerdem wird (lX3,lY3) eingefügt (s.o.).
	else if (lAbst35/2 <= iBuEps)
	{
		xb[4] = xb[3];		yb[4] = yb[3];
		xb[3] = lX3;		yb[3] = lY3;	// Ergänzung, um Rundungsfehlern entgegenzutreten
	}

	else
	{
	// Berechnung von P4, wenn der halbe Abstand zwischen P3 und P5 größer als iBuEps ist
	// Berechnung des Winkels an der konvexen Ecke
	double a1 = yb[3] - lY2;			// Koeffizient vor x-Glied der Geradengleichung P3-(lX2,lY2)
	double b1 = (lX2 - xb[3]) * dFak;	// Koeffizient vor y-Glied der Geradengleichung P3-(lX2,lY2)
	double a2 = yb[5] - lY2;			// Koeffizient vor x-Glied der Geradengleichung (lX2,lY2)-P5
	double b2 = (lX2 - xb[5]) * dFak;	// Koeffizient vor y-Glied der Geradengleichung (lX2,lY2)-P5
	double ne = a1*a2 + b1*b2;		// Nenner für Berechnung des Tangens des Winkels
	double wi;      // Winkel am Stützpunkt (lX2,lY2)
	double si;      // sin (wi / 2.)
	double co;      // cos (wi / 2.)

		if (ne != 0)
		{
			wi = atan ((a1*b2 - a2*b1) / ne);	// atan liefert Werte zwischen -90° und +90°
			if (wi < 0) wi += Pi;				// deshalb Transformation bei negativen Winkeln mit 180°
			si = sin (wi / 2.);
			co = cos (wi / 2.);
		}
		else    // Winkel von 90°
		{
			si = dTrigonom45;  // sin (45°)
			co = dTrigonom45;  // cos (45°)
		}

		xb[4] = lX2 - (co*k12 - si*k11)*dUF.X();
		yb[4] = lY2 + (si*k12 + co*k11)*dUF.Y();
	}

KoOrd lxb[7], lyb[7];	// KoOrd-Koordinaten des Pufferelementes

	for (long i = 0; i < n; i++)
	{
		lxb[i] = DtoL (xb[i]);
		lyb[i] = DtoL (yb[i]);
	}

EFlaeche* pBE = new EFlaeche (lxb, lyb, n);    // Pufferelement

	if (pBE)
		DoublePointCleaning (&pBE->KA(0));	// 02.03.99
	else
		DEX_Error (RC_Buffering, EC_NOMEMORY);

	return pBE;

} // KiteModeNegative


// --------------------------------------------------------------------------------------------
// am Beginn einer Kante 2 Drachenvierecke bilden;
// dafür werden die 5 Punkte P0 bei 0°, P1 bei 45°, P2 bei 90°, P3 bei 135° und P4 bei 180°
// verwendet
EFlaeche* KiteModeStart (double* xb, double* yb, KoOrd lX1, KoOrd lY1, double k1, double k2,
						 DoublePair dUF)
{
double k3 = dTrigonom45 * (k1 + k2); // 0.707106781 == cos(45°) == sin(45°)
double k4 = dTrigonom45 * (k1 - k2);
int n = 6;			// Anzahl der Ecken des Pufferelements
KoOrd lxb[6], lyb[6];	// KoOrd-Koordinaten des Pufferelementes

	lxb[0] = DtoL (xb[0]);				lyb[0] = DtoL (yb[0]);
	lxb[1] = DtoL (lX1 - k3*dUF.X());	lyb[1] = DtoL (lY1 + k4*dUF.Y());

	if (AbstandPktPktM (lxb[0], lyb[0], lxb[1], lyb[1]) > iBuEps)
	{
		lxb[2] = DtoL (lX1 - k1*dUF.X());	lyb[2] = DtoL (lY1 - k2*dUF.Y());
		lxb[3] = DtoL (lX1 - k4*dUF.X());	lyb[3] = DtoL (lY1 - k3*dUF.Y());
		lxb[4] = DtoL (xb[4]);				lyb[4] = DtoL (yb[4]);
		lxb[5] = lxb[0];					lyb[5] = lyb[0];
	}
	else
	{
		lxb[1] = DtoL (lX1 - k1*dUF.X());	lyb[1] = DtoL (lY1 - k2*dUF.Y());
		lxb[2] = DtoL (xb[4]);				lyb[2] = DtoL (yb[4]);
		lxb[3] = lxb[0];					lyb[3] = lyb[0];
		n = 4;
	}

EFlaeche* pBE = new EFlaeche (lxb, lyb, n); // Pufferelement

	if (pBE)
		DoublePointCleaning (&pBE->KA(0));	// 02.03.99
	else
		DEX_Error (RC_Buffering, EC_NOMEMORY);

	return pBE;

} // KiteModeStart


// --------------------------------------------------------------------------------------------
// am Ende einer Kante 2 Drachenvierecke bilden;
// zu den beiden Ecken des Rechtecks P0 und P1 werden noch die 5 Punkte P2 bei 0° (= Ecke des
// Rechtecks), P3 bei 45°, P4 bei 90°, P5 bei 135°, P6 bei 180° (= Ecke des Rechtecks)
// verwendet
EFlaeche* KiteModeStop (double* xb, double* yb, KoOrd lX2, KoOrd lY2, double k1, double k2,
						DoublePair dUF)
{
int n = 8;			// Anzahl der Ecken des Pufferelements
KoOrd lxb[8], lyb[8];	// KoOrd-Koordinaten des Pufferelementes
double k3 = dTrigonom45 * (k1 + k2); // 0.707106781 == cos(45°) == sin(45°)
double k4 = dTrigonom45 * (k1 - k2);

	lxb[0] = DtoL (xb[0]);				lyb[0] = DtoL (yb[0]);
	lxb[1] = DtoL (xb[1]);				lyb[1] = DtoL (yb[1]);
	lxb[2] = DtoL (xb[2]);				lyb[2] = DtoL (yb[2]);
	lxb[3] = DtoL (lX2 + k3*dUF.X());	lyb[3] = DtoL (lY2 - k4*dUF.Y());

	if (AbstandPktPktM (lxb[2], lyb[2], lxb[3], lyb[3]) > iBuEps)
	{
		lxb[4] = DtoL (lX2 + k1*dUF.X());	lyb[4] = DtoL (lY2 + k2*dUF.Y());
		lxb[5] = DtoL (lX2 + k4*dUF.X());	lyb[5] = DtoL (lY2 + k3*dUF.Y());
		lxb[6] = DtoL (xb[6]);				lyb[6] = DtoL (yb[6]);
		lxb[7] = lxb[0];					lyb[7] = lyb[0];
	}
	else
	{
		lxb[3] = DtoL (lX2 + k1*dUF.X());	lyb[3] = DtoL (lY2 + k2*dUF.Y());
		lxb[4] = DtoL (xb[6]);				lyb[4] = DtoL (yb[6]);
		lxb[5] = lxb[0];					lyb[5] = lyb[0];
		n = 4;
	}

EFlaeche* pBE = new EFlaeche (lxb, lyb, n); // Pufferelement

	if (pBE)
		DoublePointCleaning (&pBE->KA(0));	// 02.03.99
	else
		DEX_Error (RC_Buffering, EC_NOMEMORY);

	return pBE;

} // KiteModeStop


// --------------------------------------------------------------------------------------------
// Startwerte m_px, m_py und m_bPosTurn ermitteln für Pufferung mit spitzen konvexen Ecken
bool BufferExtension :: StartValuesForTipMode (KoOrd lX1, KoOrd lY1, KoOrd lX2, KoOrd lY2,
										   KoOrd lX3, KoOrd lY3, double dWidth, DoublePair dUF)
{
	_ASSERTE (dUF.X() > 0.);

	if (0. == dUF.X()) return false;

double dFak = dUF.Y() / dUF.X();	// Relation bei geodätischen Koordinaten
double x1 = lX1 * dFak;
double y1 = lY1;
double x2 = lX2 * dFak;
double y2 = lY2;
double x3 = lX3 * dFak;
double y3 = lY3;
double dLength12 = sqrt ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
double dLength23 = sqrt ((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));

	if (0. == dLength12 || 0. == dLength23)
		return false;     // entartetes Pufferelement

double k10 = dWidth / dLength12;	// Hilfswerte
double k11 = k10 * (x2 - x1);
double k12 = k10 * (y2 - y1);
double k20 = dWidth / dLength23;
double k21 = k20 * (x3 - x2);
double k22 = k20 * (y3 - y2);
double xs, ys;

int iBR = TurnDirection (lX1, lY1, lX2, lY2, lX3, lY3);

	_ASSERTE (iBR != 0);

	if (+1 == iBR)	// konvexe Ecke bei (lX2,lY2)
	{
	double x1p = lX1 + k12*dUF.X();
	double y1p = lY1 - k11*dUF.Y();
	double x21p = lX2 + k12*dUF.X();
	double y21p = lY2 - k11*dUF.Y();
	double x23p = lX2 + k22*dUF.X();
	double y23p = lY2 - k21*dUF.Y();
	double x3p = lX3 + k22*dUF.X();
	double y3p = lY3 - k21*dUF.Y();

		GeradenSchnittPunkt (x1p, y1p, x21p, y21p, x23p, y23p, x3p, y3p, xs, ys);

		m_bPosTurn = true;
	}
	else			// konkave Ecke
	{
	double x1n = lX1 - k12*dUF.X();
	double y1n = lY1 + k11*dUF.Y();
	double x21n = lX2 - k12*dUF.X();
	double y21n = lY2 + k11*dUF.Y();
	double x23n = lX2 - k22*dUF.X();
	double y23n = lY2 + k21*dUF.Y();
	double x3n = lX3 - k22*dUF.X();
	double y3n = lY3 + k21*dUF.Y();

		GeradenSchnittPunkt (x1n, y1n, x21n, y21n, x23n, y23n, x3n, y3n, xs, ys);

		m_bPosTurn = false;
	}

	m_px = DtoL (xs);
	m_py = DtoL (ys);

	return true;

} // StartValuesForTipMode


// --------------------------------------------------------------------------------------------
// mathematisch positive konvexe Ecke bei (lX2,lY2) spitz ausführen;
// der Schnittpunkt der beiden Geraden P1-P2 und P4-Verschobener(lX3,lY3) wird berechnet und
// auf P2 gesetzt
EFlaeche* BufferExtension :: TipModePositive (double* xb, double* yb, KoOrd lX3, KoOrd lY3,
											  double k21, double k22, DoublePair dUF)
{
double x3p = lX3 + k22*dUF.X();
double y3p = lY3 - k21*dUF.Y();
double xs, ys;

	GeradenSchnittPunkt (xb[1], yb[1], xb[2], yb[2], xb[4], yb[4], x3p, y3p, xs, ys);

KoOrd lxb[5], lyb[5];	// KoOrd-Koordinaten des Pufferelementes

	if (m_bPosTurn)
	{
		lxb[0] = DtoL (xb[0]);		lyb[0] = DtoL (yb[0]);
		lxb[1] = m_px;				lyb[1] = m_py;
	}
	else
	{
		lxb[0] = m_px;				lyb[0] = m_py;
		lxb[1] = DtoL (xb[1]);		lyb[1] = DtoL (yb[1]);
	}

	lxb[2] = DtoL (xs);			lyb[2] = DtoL (ys);
	lxb[3] = DtoL (xb[5]);		lyb[3] = DtoL (yb[5]);
	lxb[4] = lxb[0];			lyb[4] = lyb[0];

	m_bPosTurn = true;
	m_px = DtoL (xs);
	m_py = DtoL (ys);

EFlaeche* pBE = new EFlaeche (lxb, lyb, 5);    // Pufferelement

	if (pBE)
		DoublePointCleaning (&pBE->KA(0));	// 02.03.99
	else
		DEX_Error (RC_Buffering, EC_NOMEMORY);

	return pBE;

} // TipModePositive


// --------------------------------------------------------------------------------------------
// mathematisch negative konvexe Ecke bei (lX2,lY2) spitz ausführen;
// der Schnittpunkt der beiden Geraden P0-P5 und P3-Verschobener(lX3,lY3) wird berechnet und
// auf P5 gesetzt
EFlaeche* BufferExtension :: TipModeNegative (double* xb, double* yb, KoOrd lX3, KoOrd lY3,
											  double k21, double k22, DoublePair dUF)
{
double x3n = lX3 - k22*dUF.X();
double y3n = lY3 + k21*dUF.Y();
double xs, ys;

	GeradenSchnittPunkt (xb[0], yb[0], xb[5], yb[5], xb[3], yb[3], x3n, y3n, xs, ys);

KoOrd lxb[5], lyb[5];	// KoOrd-Koordinaten des Pufferelementes

	if (m_bPosTurn)
	{
		lxb[0] = DtoL (xb[0]);		lyb[0] = DtoL (yb[0]);
		lxb[1] = m_px;				lyb[1] = m_py;
	}
	else
	{
		lxb[0] = m_px;				lyb[0] = m_py;
		lxb[1] = DtoL (xb[1]);		lyb[1] = DtoL (yb[1]);
	}

	lxb[2] = DtoL (xb[2]);		lyb[2] = DtoL (yb[2]);
	lxb[3] = DtoL (xs);			lyb[3] = DtoL (ys);
	lxb[4] = lxb[0];			lyb[4] = lyb[0];

	m_bPosTurn = false;
	m_px = DtoL (xs);
	m_py = DtoL (ys);

EFlaeche* pBE = new EFlaeche (lxb, lyb, 5);    // Pufferelement

	if (pBE)
		DoublePointCleaning (&pBE->KA(0));	// 02.03.99
	else
		DEX_Error (RC_Buffering, EC_NOMEMORY);

	return pBE;

} // TipModeNegative


// --------------------------------------------------------------------------------------------
// Beginn einer Kante, wenn konvexe Ecken "spitz" ausgebildet werden sollen
EFlaeche* BufferExtension :: TipModeStart (double* xb, double* yb, KoOrd lX0, KoOrd lY0,
										   KoOrd lX1, KoOrd lY1, KoOrd lX2, KoOrd lY2,
										   double dWidth, double k1, double k2, DoublePair dUF)
{
KoOrd lxb[4], lyb[4];	// KoOrd-Koordinaten des Pufferelementes

	if (lX0 <= 0 || lY0 <= 0)	// offene Kante
	{
		lxb[0] = DtoL (xb[0]);				lyb[0] = DtoL (yb[0]);
		lxb[1] = DtoL (xb[0] - k1*dUF.X());	lyb[1] = DtoL (yb[0] - k2*dUF.Y());
		lxb[2] = DtoL (xb[4] - k1*dUF.X());	lyb[2] = DtoL (yb[4] - k2*dUF.Y());
		m_bPosTurn = true;
		m_iKonvex = 0;
		m_sx = -1;
		m_sy = -1;
	}

	else						// geschlossene Kante
	{
	// bei einer geschlossenen Kante wird eigentlich keine Anfangsfläche benötigt; damit aber
	// nachfolgend etwas zum FlächenVereinigen da ist, wird eine Anfangsfläche gebildet;
	// entscheidend ist die Berechnug des Schnittpunktes (xs,ys)
	double dFak = dUF.Y() / dUF.X();	// Relation bei geodätischen Koordinaten
	double x0 = lX0 * dFak;
	double y0 = lY0;
	double x1 = lX1 * dFak;
	double y1 = lY1;
	double dLength = sqrt ((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));

		if (0. == dLength) return NULL;     // entartetes Pufferelement

	double k10 = dWidth / dLength;
	double k11 = k10 * (x1 - x0);
	double k12 = k10 * (y1 - y0);
	double xs, ys;

		m_iKonvex = TurnDirection (lX0, lY0, lX1, lY1, lX2, lY2);

		_ASSERTE (m_iKonvex != 0);

		if (+1 == m_iKonvex)	// konvexe Ecke am Anfangs-/Endpunkt
		{
		double x0p = lX0 + k12*dUF.X();
		double y0p = lY0 - k11*dUF.Y();
		double x10p = lX1 + k12*dUF.X();
		double y10p = lY1 - k11*dUF.Y();
		double x12p = lX1 + k2*dUF.X();
		double y12p = lY1 - k1*dUF.Y();
		double x2p = lX2 + k2*dUF.X();
		double y2p = lY2 - k1*dUF.Y();

			GeradenSchnittPunkt (x0p, y0p, x10p, y10p, x12p, y12p, x2p, y2p, xs, ys);

			lxb[0] = lX1;				lyb[0] = lY1;
			lxb[1] = DtoL (xb[0]);		lyb[1] = DtoL (yb[0]);
			lxb[2] = DtoL (xs);			lyb[2] = DtoL (ys);
			m_bPosTurn = true;
		}
		else			// TurnDirection() == -1, d.h. konkave Ecke
		{
		double x0n = lX0 - k12*dUF.X();
		double y0n = lY0 + k11*dUF.Y();
		double x10n = lX1 - k12*dUF.X();
		double y10n = lY1 + k11*dUF.Y();
		double x12n = lX1 - k2*dUF.X();
		double y12n = lY1 + k1*dUF.Y();
		double x2n = lX2 - k2*dUF.X();
		double y2n = lY2 + k1*dUF.Y();

			GeradenSchnittPunkt (x0n, y0n, x10n, y10n, x12n, y12n, x2n, y2n, xs, ys);

			lxb[0] = DtoL (lX1 + k2*dUF.X());	lyb[0] = DtoL (lY1 - k1*dUF.Y());
			lxb[1] = lX1;						lyb[1] = lY1;
			lxb[2] = DtoL (xs);					lyb[2] = DtoL (ys);
			m_bPosTurn = false;
		}

		m_sx = lxb[2];
		m_sy = lyb[2];
	}

	lxb[3] = lxb[0];		lyb[3] = lyb[0];

	m_px = lxb[2];
	m_py = lyb[2];

EFlaeche* pBE = new EFlaeche (lxb, lyb, 4);    // Pufferelement

	if (pBE)
		DoublePointCleaning (&pBE->KA(0));	// 02.03.99
	else
		DEX_Error (RC_Buffering, EC_NOMEMORY);

	return pBE;

} // TipModeStart


// --------------------------------------------------------------------------------------------
// Ende einer Kante, wenn konvexe Ecken "spitz" ausgebildet werden sollen
EFlaeche* BufferExtension :: TipModeStop (double* xb, double* yb, double k1, double k2,
										  DoublePair dUF)
{
KoOrd lxb[5], lyb[5];	// KoOrd-Koordinaten des Pufferelementes

	if (m_bPosTurn)
	{
		lxb[0] = DtoL (xb[0]);		lyb[0] = DtoL (yb[0]);
		lxb[1] = m_px;				lyb[1] = m_py;
	}
	else
	{
		lxb[0] = m_px;				lyb[0] = m_py;
		lxb[1] = DtoL (xb[1]);		lyb[1] = DtoL (yb[1]);
	}

	if (m_sx <= 0 || m_sy <= 0)	// offene Kante
	{
		_ASSERTE (m_iKonvex == 0);

		lxb[2] = DtoL (xb[2] + k1*dUF.X());	lyb[2] = DtoL (yb[2] + k2*dUF.Y());
		lxb[3] = DtoL (xb[6] + k1*dUF.X());	lyb[3] = DtoL (yb[6] + k2*dUF.Y());
	}
	else				// geschlossene Kante
	{
		_ASSERTE (m_iKonvex != 0);

		if (1 == m_iKonvex)	// Ecke am Anfangs-/Endpunkt ist konvex
		{
			lxb[2] = m_sx;						lyb[2] = m_sy;
			lxb[3] = DtoL (xb[6] + k1*dUF.X());	lyb[3] = DtoL (yb[6] + k2*dUF.Y());
		}
		else				// konkave Ecke
		{
			lxb[2] = DtoL (xb[2] + k1*dUF.X());	lyb[2] = DtoL (yb[2] + k2*dUF.Y());
			lxb[3] = m_sx;						lyb[3] = m_sy;
		}
	}

	lxb[4] = lxb[0];					lyb[4] = lyb[0];

EFlaeche* pBE = new EFlaeche (lxb, lyb, 5);    // Pufferelement

	if (pBE)
		DoublePointCleaning (&pBE->KA(0));	// 02.03.99
	else
		DEX_Error (RC_Buffering, EC_NOMEMORY);

	return pBE;

} // TipModeStop


// --------------------------------------------------------------------------------------------
// mathematisch positive konvexe Ecke bei (lX2,lY2) abgeflacht ausführen;
// um Rundungsfehlern entgegenzutreten, die eine Lücke zum Pufferelement der nächsten Strecke
// (lX2,lY2)-(lX3,lY3) zur Folge haben können, werden (lX2,lY2) und (lX3,lY3) eingefügt
EFlaeche* PlainModePositive (double* xb, double* yb, KoOrd lX2, KoOrd lY2, KoOrd lX3,
							 KoOrd lY3)
{
// da die Reihenfolge beim Einfügen von (lX2,lY2) und (lX3,lY3) vom Winkel bei (lX2,lY2)
// abhängt, werden 2 Teil-Pufferelemente gebildet und diese flächenmäßig vereinigt
KoOrd lxb[6], lyb[6];	// KoOrd-Koordinaten der Teil-Pufferelemente

	lxb[0] = DtoL (xb[0]);		lyb[0] = DtoL (yb[0]);
	lxb[1] = DtoL (xb[1]);		lyb[1] = DtoL (yb[1]);
	lxb[2] = DtoL (xb[2]);		lyb[2] = DtoL (yb[2]);
	lxb[3] = DtoL (xb[5]);		lyb[3] = DtoL (yb[5]);
	lxb[4] = lxb[0];			lyb[4] = lyb[0];

EFlaeche* pBE1 = new EFlaeche (lxb, lyb, 5);    // 1. Teil-Pufferelement

	if (! pBE1)
	{
		DEX_Error (RC_Buffering, EC_NOMEMORY);
		return NULL;
	}

	lxb[0] = lxb[1];			lyb[0] = lyb[1];
	lxb[1] = lxb[2];			lyb[1] = lyb[2];
	lxb[2] = DtoL (xb[4]);		lyb[2] = DtoL (yb[4]);
	lxb[3] = lX3;				lyb[3] = lY3;
	lxb[4] = lX2;				lyb[4] = lY2;
	lxb[5] = lxb[0];			lyb[5] = lyb[0];

EFlaeche* pBE2 = new EFlaeche (lxb, lyb, 6);    // 2. Teil-Pufferelement

	if (pBE2)
		DoublePointCleaning (&pBE2->KA(0));	// 02.03.99
	else
	{
		DEX_Error (RC_Buffering, EC_NOMEMORY);
		return NULL;
	}

bool bAbbr;		// Parameter von FlaechenVereinigung(); wird hier nicht weiter ausgewertet
EFlaeche* pBE = pBE1->FlaechenVereinigung (pBE2, bAbbr, NULL, false);

	PartialCleaningForLines (&pBE->KA(0));		// 28.07.99

	return pBE;

} // PlainModePositive


// --------------------------------------------------------------------------------------------
// mathematisch negative konvexe Ecke bei (lX2,lY2) abgeflacht ausführen;
// um Rundungsfehlern entgegenzutreten, die eine Lücke zum Pufferelement der nächsten Strecke
// (lX2,lY2)-(lX3,lY3) zur Folge haben können, werden (lX2,lY2) und (lX3,lY3) eingefügt
EFlaeche* PlainModeNegative (double* xb, double* yb, KoOrd lX2, KoOrd lY2, KoOrd lX3,
							 KoOrd lY3)
{
// da die Reihenfolge beim Einfügen von (lX2,lY2) und (lX3,lY3) vom Winkel bei (lX2,lY2)
// abhängt, werden 2 Teil-Pufferelemente gebildet und diese flächenmäßig vereinigt
KoOrd lxb[6], lyb[6];	// KoOrd-Koordinaten der Teil-Pufferelemente

	lxb[0] = DtoL (xb[0]);		lyb[0] = DtoL (yb[0]);
	lxb[1] = DtoL (xb[1]);		lyb[1] = DtoL (yb[1]);
	lxb[2] = DtoL (xb[2]);		lyb[2] = DtoL (yb[2]);
	lxb[3] = DtoL (xb[5]);		lyb[3] = DtoL (yb[5]);
	lxb[4] = lxb[0];			lyb[4] = lyb[0];

EFlaeche* pBE1 = new EFlaeche (lxb, lyb, 5);    // 1. Teil-Pufferelement

	if (! pBE1)
	{
		DEX_Error (RC_Buffering, EC_NOMEMORY);
		return NULL;
	}

//	lxb[0] = DtoL (xb[0]);		lyb[0] = DtoL (yb[0]);	// ist umsonst !!
	lxb[1] = lX2;				lyb[1] = lY2;
	lxb[2] = lX3;				lyb[2] = lY3;
	lxb[3] = DtoL (xb[3]);		lyb[3] = DtoL (yb[3]);
	lxb[4] = DtoL (xb[5]);		lyb[4] = DtoL (yb[5]);
	lxb[5] = lxb[0];			lyb[5] = lyb[0];

EFlaeche* pBE2 = new EFlaeche (lxb, lyb, 6);    // 2. Teil-Pufferelement

	if (pBE2)
		DoublePointCleaning (&pBE2->KA(0));	// 02.03.99
	else
	{
		DEX_Error (RC_Buffering, EC_NOMEMORY);
		return NULL;
	}

bool bAbbr;		// Parameter von FlaechenVereinigung(); wird hier nicht weiter ausgewertet
EFlaeche* pBE = pBE1->FlaechenVereinigung (pBE2, bAbbr, NULL, false);

	PartialCleaningForLines (&pBE->KA(0));		// 28.07.99

	return pBE;

} // PlainModeNegative


// --------------------------------------------------------------------------------------------
// am Ende einer Kante den Puffer abgeflacht ausführen
EFlaeche* PlainModeStop (double* xb, double* yb, KoOrd lX1, KoOrd lY1, KoOrd lX2, KoOrd lY2,
						 KoOrd lX3, KoOrd lY3, double dWidth, DoublePair dUF)
{
int n = 6;				// Anzahl der Ecken des Pufferelements
KoOrd lxb[6], lyb[6];	// KoOrd-Koordinaten des Pufferelementes

	lxb[0] = DtoL (xb[0]);		lyb[0] = DtoL (yb[0]);
	lxb[1] = DtoL (xb[1]);		lyb[1] = DtoL (yb[1]);
	lxb[2] = DtoL (xb[2]);		lyb[2] = DtoL (yb[2]);

	if (lX3 <= 0 || lY3 <= 0)	// Kante offen
	{
		lxb[2] = DtoL (xb[2]);		lyb[2] = DtoL (yb[2]);
		lxb[3] = DtoL (xb[6]);		lyb[3] = DtoL (yb[6]);
		lxb[4] = lxb[0];			lyb[4] = lyb[0];
		n = 5;
	}

	else						// Kante geschlossen
	{
	double dFak = dUF.Y() / dUF.X();	// Relation bei geodätischen Koordinaten
	double x2 = lX2 * dFak;
	double y2 = lY2;
	double x3 = lX3 * dFak;
	double y3 = lY3;
	double dLength = sqrt ((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));

		if (0. == dLength) return NULL;     // entartetes Pufferelement

	double k20 = dWidth / dLength;
	double k21 = k20 * (x3 - x2);
	double k22 = k20 * (y3 - y2);

	int iBR = TurnDirection (lX1, lY1, lX2, lY2, lX3, lY3);

		_ASSERTE (iBR != 0);

		if (+1 == iBR)	// konvexe Ecke am Anfangs-/Endpunkt
		{
			lxb[3] = DtoL (lX2 + k22*dUF.X());	lyb[3] = DtoL (lY2 - k21*dUF.Y());
		}
		else			// konkave Ecke
		{
			lxb[3] = DtoL (lX2 - k22*dUF.X());	lyb[3] = DtoL (lY2 + k21*dUF.Y());
		}

		lxb[4] = DtoL (xb[6]);		lyb[4] = DtoL (yb[6]);
		lxb[5] = lxb[0];			lyb[5] = lyb[0];
	}


EFlaeche* pBE = new EFlaeche (lxb, lyb, n);    // Pufferelement

	if (pBE)
		DoublePointCleaning (&pBE->KA(0));	// 02.03.99
	else
		DEX_Error (RC_Buffering, EC_NOMEMORY);

	return pBE;

} // PlainModeStop


// --------------------------------------------------------------------------------------------
// Approximation des Kreisbogens an einer konvexen Ecke bzw. am Anfang und Ende eines
// Kantenpuffers durch ein n-Eck mit der Kantenlänge dPrec;
// Punkt (xm,ym) ist der Mittelpunkt, (x0,y0) der Anfangs- und (x1,y1) der Endpunkt des
// Kreisbogens; (x0,y0) und (x1,y1) sind gleichweit (u.z. die Pufferbreite) von (xm,ym)
// entfernt;
// wurden pBE weitere Stützpunkte hinzugefügt, dann Rückgabe von true, sonst false
bool KreisbogenApprox (EFlaeche* pBE, double xm, double ym, double x0, double y0, double x1,
					   double y1, DoublePair dUF, double dPrec)
{
	_ASSERTE (pBE != NULL);
	_ASSERTE (dPrec > 0);

	if (! pBE || dPrec <= 0) return false;

double dFak = dUF.Y() / dUF.X();	// Relation bei geodätischen Koordinaten

	xm *= dFak;
	x0 *= dFak;
	x1 *= dFak;
	dPrec *= dUF.Y();

double dxa = xm - x1;
double dya = ym - y1;
double dxb = x0 - xm;
double dyb = y0 - ym;
double dxc = x1 - x0;
double dyc = y1 - y0;
double cq = dxc*dxc + dyc*dyc;			// c² (c ist die Basis des gleichschenkligen Dreiecks)
// a und b müßten eigentlich beide gleich der Pufferbreite sein; durch die Digitalgeometrie ist
// dies aber nicht garantiert, deshalb nachfolgend die Mittelbildung
double dWidth = (sqrt(dxa*dxa + dya*dya) + sqrt(dxb*dxb + dyb*dyb)) / 2.;
double dCosSekW = 1. - cq/(2.*dWidth*dWidth);	// Cosinus des Kreisbogenwinkels (mit Kosinussatz)

	if (dCosSekW > 1. ) dCosSekW = 1.;
	if (dCosSekW < -1. ) dCosSekW = -1.;

double dSekW = acos(dCosSekW);		// Sektorwinkel (acos liefert 0 ... Pi)
double dBogLaenge = dSekW * dWidth;	// Länge des Kreisbogens

	if (dBogLaenge <= dPrec) return false;	// hier braucht nichts mehr berechnet zu werden

int iKAnz = (int) floor (dBogLaenge/dPrec);	// Anzahl der Kanten

	if (iKAnz <= 1) return false;	// hier braucht nichts mehr berechnet zu werden

double dSegW = dSekW / iKAnz;		// Winkel eines n-Eck-Segmentes

// Berechnung des Anstiegswinkels der Strecke (xm,ym)-(x0,y0)
double dSinAnstW = (y0 - ym) / dWidth;

	if (dSinAnstW > 1.) dSinAnstW = 1.;
	if (dSinAnstW < -1.) dSinAnstW = -1.;

double dAnstW = asin (dSinAnstW);	// Anstiegswinkels der Strecke (xm,ym)-(x0,y0)

	// asin() liefert Werte zwischen -90° und +90°, deshalb noch evtl. Transformationen entspr.
	// der Quadranten
	if (x0 < xm) dAnstW = Pi - dAnstW;
	else if (y0 < ym) dAnstW = 2.*Pi + dAnstW;	// dAnstW < 0

KoOrd* pX = new KoOrd[iKAnz-1];
KoOrd* pY = new KoOrd[iKAnz-1];

	if (!pX || !pY)
	{
		DELETE_VEC (pX);
		DEX_Error (RC_Buffering, EC_NOMEMORY);
		return false;
	}

double dWi = dAnstW;

	for (int i = 1; i < iKAnz; i++)
	{
		dWi += dSegW;
		pX[i-1] = DtoL ((xm + dWidth*cos(dWi))/dFak);
		pY[i-1] = DtoL (ym + dWidth*sin(dWi));
	}

	pBE->AddPunkt (pX, pY, iKAnz-1, -1, -1); 

	DELETE_VEC (pX);
	DELETE_VEC (pY);
	return true;

} // KreisbogenApprox


// --------------------------------------------------------------------------------------------
// Die zu puffernde Fläche wird durch die vereinigten Pufferelemente geschnitten; als Ergebnis
// wird die Fläche zurückgegeben, die AUßERHALB von den vereinigten Pufferelementen liegt.
EFlaeche* BuildInsideBuffer (EFlaeche* pPartBuff, EFlaeche* pBE)
{
	_ASSERTE (NULL != pPartBuff);
	_ASSERTE (NULL != pBE);

	if (NULL == pPartBuff || NULL == pBE)
		return NULL;

ClipListe CL;	// Ergebnisflächen der Pufferbildung
Posit posLage;	// wird hier nicht ausgewertet
bool bAbbr;		// Pufferbildung wurde (durch Anwender) abgebrochen (true), sonst false

GeoFlaeche GF = GeoFlaeche (0, 0, *pBE);
bool bRet = GF.Clipping (pPartBuff, OT_FLAECHE, LAUSS, CL, 0, posLage, bAbbr, NULL);

	if (! bRet || bAbbr)
		return NULL;

	if (0 == CL.Count())
		return NULL;

	if (CL.Count() > 1)
	{
	char sText[255] = "Es entsteht mehr als nur 1 Puffer!\nSorry - Dieser Fall wurde noch nicht implementiert.";
	ResString resCapt (ResID (IDS_LONGCLASSNAME, pRF), 50);
    	
    	MessageBox (__hWndM, sText, resCapt.Addr(), MB_ICONEXCLAMATION | MB_OK);
    }

EFlaeche* pBFl = NULL;	// zurückzugebende Pufferfläche
CRing ri (CL);			// Navigator für ListContainer ClipListe CL

	for (ri.First(); ri.Valid(); ri.Next())
	{
	GeoObjektLock ml (ri);

		if (! ml) continue;
		if (OT_FLAECHE == ((GeoObjekt*)ml)->isA())
			pBFl = new EFlaeche (*(EFlaeche*)(GeoFlaeche*)(GeoObjekt*)ml);
			return pBFl;
	}
	return NULL;	// hierhin dürfte niemand kommen

} // BuildInsideBuffer
