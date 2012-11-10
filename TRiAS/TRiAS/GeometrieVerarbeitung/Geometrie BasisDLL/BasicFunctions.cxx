// Grundlegende Funktionen (mit double-Parametern), die für double-, KoOrd- und CoOrd-Parameter
// verwendet werden können
// File: BasicFunctions.cxx
// W. Mörtl


#include "GeometrP.hxx"

#include "BasicFunctions.hxx"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



// --------------------------------------------------------------------------------------------
// Lage des Punktes (x,y) bezüglich des geschlossenen Polygonzuges (pX, pY) der Länge lCnt;
// für bInner == true, liegt der Punkt innerhalb der eingeschlossenen Fläche bzw. auf deren Kontur
// return-Werte sind
//   S_OK     Entscheidung konnte getroffen werden
//   E_FAIL   Polygonzug ist entartet bzw. nicht geschlossen (bInner unbestimmt)

HRESULT _GEOMETR_EXPORT PunktLage (double x, double y, double* pX, double* pY, long lCnt, bool& bInner)
{
	if (!pX || !pY ||
		lCnt <= 3 ||								// Polygonzug ist entartet
		pX[0] != pX[lCnt-1] || pY[0] != pY[lCnt-1])	// Polygonzug ist nicht geschlossen
		return E_FAIL;
	
// Koordinaten der waagerechten Testlinie
double xa = x, ya = y, xe = DBL_MAX, ye = y;

long lCutCnt = 0;	// Zähler für echte Schnitte der Testlinie mit dem Polygonzug
long j = lCnt - 2;	// Index des letzten Polygonpunktes, von dem bekannt ist, daß
					// er nicht auf der Testlinie liegt

	while (0 == TurnDirection (xa, ya, xe, ye, pX[j], pY[j]))
	{
		j--;
		if (j < 0)
			return E_FAIL;	// entarteter Polygonzug, d.h. alle Punkte liegen auf einer Geraden,
	}						// die mit der Trägergeraden der Testlinie identsch ist

int iTD1, iTD2, iTD3;		// return-Werte von TurnDirection()

	for (long k = 0; k < lCnt-1; k++)
	{
		// Test, ob Punkt auf der Kontur der eingeschlossenen Fläche liegt
		if (0 == TurnDirection (pX[k], pY[k], pX[k+1], pY[k+1], x, y))
		{
			bInner = true;
			return S_OK;	// Punkt liegt auf der Kontur
		}

		// Im nachfolgenden if-Zweig wird der Fall behandelt, daß der nächste Punkt P[k] nicht auf
		// der waagerechten Testlinie liegt.
		// Liegt P[k] auf der Testlinie (else-Zweig), wird P[k] i.a. ignoriert.
		// Liegt jedoch der zu testende Punkt im Dreieck P[k-1], P[k], P[k+1], ergibt sich durch das
		// Weglassen von P[k] eine Fehlinterpretation. Deshalb ist dieser Fall gesondert abzutesten.
		if (0 != TurnDirection (xa, ya, xe, ye, pX[k], pY[k]))
		{
			// Zähler lCutCnt inkrementieren, wenn echter Schnitt vorliegt, d. h. P[k] und P[j]
			// auf verschiedenen Seiten der Testlinie liegen
			if (Intersection (pX[k], pY[k], pX[j], pY[j], xa, ya, xe, ye))
				lCutCnt++;
			j = k;
		}
		else    // P[k] liegt auf der Testlinie
		{
			iTD1 = TurnDirection (pX[k], pY[k], pX[k+1], pY[k+1], x, y);

			if (k > 0)
			{
				iTD2 = TurnDirection (pX[k-1], pY[k-1], pX[k], pY[k], x, y);
				iTD3 = TurnDirection (pX[k+1], pY[k+1], pX[k-1], pY[k-1], x, y);
			}
			else    // k == 0
			{
				iTD2 = TurnDirection (pX[lCnt-2], pY[lCnt-2], pX[0], pY[0], x, y);
				iTD3 = TurnDirection (pX[1], pY[1], pX[lCnt-2], pY[lCnt-2], x, y);
			}

			if (iTD1 >= 0 && iTD2 >= 0 && iTD3 >= 0)	// konvexe Ecke des Polygonzuges:
			{
				bInner = true;							// Punkt liegt innerhalb
				return S_OK;
			}

			if (iTD1 <= 0 && iTD2 <= 0 && iTD3 <= 0)	// konkave Ecke des Polygonzuges:
			{
				bInner = false;							// Punkt liegt außerhalb
				return S_OK;
			}
		}
	}

	// ungerade Schnittanzahl bedeutet Enthaltensein
	(lCutCnt & 1) ? (bInner = true) : (bInner = false);

	return S_OK;

} // PunktLage


// --------------------------------------------------------------------------------------------
// Bewegungsrichtung, wenn man bei 3 gegebenen Punkten P1(x1,y1), P2(x2,y2) und P3(x3,y3) vom
// ersten, zum zweiten und dann zum dritten geht; return-Werte sind
// +1 bei Drehung im mathem. pos. Sinn (gegen Uhrzeigersinn) bzw. 
//    bei Kollinearität, wenn P2 zwischen P1 und P3 liegt bzw.
//    bei P1 == P2
// -1 bei Drehung im mathem. neg. Sinn (im Uhrzeigersinn) bzw.
//    bei Kollinearität, wenn P1 zwischen P3 und P2 liegt
//  0 bei Kollinearität, wenn P3 zwischen P1 und P2 liegt bzw.
//    bei P1 == P3, P2 == P3, P1 == P2 == P3
int _GEOMETR_EXPORT TurnDirection (double x1, double y1, double x2, double y2, double x3,
								   double y3)
{
double dx1 = x2 - x1;
double dy1 = y2 - y1;
double dx2 = x3 - x1;
double dy2 = y3 - y1;

	if (dx1*dy2 > dy1*dx2)
		return +1;
	if (dx1*dy2 < dy1*dx2)
		return -1;
	if (dx1*dx2 < 0 || dy1*dy2 < 0)
		return -1;
	if (dx1*dx1+dy1*dy1 < dx2*dx2+dy2*dy2)
		return +1;
	return 0;

} // TurnDirection


// --------------------------------------------------------------------------------------------
// 2 Strecken (x11,y11)-(x21,y21) und (x12,y12)-(x22,y22) haben wenigstens einen Punkt
// gemeinsam; dann Rückageb von true, sonst false
bool _GEOMETR_EXPORT Intersection (double x11, double y11, double x21, double y21, double x12,
								   double y12, double x22, double y22)
{
	return ((TurnDirection (x11, y11, x21, y21, x12, y12) *
			 TurnDirection (x11, y11, x21, y21, x22, y22)) <= 0) &&
			((TurnDirection (x12, y12, x22, y22, x11, y11) *
			  TurnDirection (x12, y12, x22, y22, x21, y21)) <= 0);
}


// --------------------------------------------------------------------------------------------
// Test, ob ein Punkt (x,y), der auf der Trägergeraden einer Strecke (x1,y1)-(x2,y2) liegt,
// auch auf der Strecke selbst liegt (einschließlich der beiden Endpunkt); dann ist der
// return-Wert "true"
// die Routine TurnDirection() wird nicht verwendet, da der Punkt (x,y) durch die Rundung von
// double -> KoOrd "leicht" neben der Strecke liegen kann, obwohl er eigentlich drauf liegen
// müßte
bool IsPointOnStraight (double x, double y, double x1, double y1, double x2, double y2)
{
	if ((x == x1 && y == y1) || (x == x2 && y == y2))
		return true;

	if (x1 == x2 &&		// senkrechte Strecke
		min (y1, y2) <= y && y <= max (y1, y2))
		return true;

	if (y1 == y2 &&		// waagrechte Strecke
		min (x1, x2) <= x && x <= max (x1, x2))
		return true;

	// Normalfall (schräge Strecke)
	if (min (x1, x2) <= x && x <= max (x1, x2) &&
		min (y1, y2) <= y && y <= max (y1, y2))
		return true;
	return false;

} // IsPointOnStraight
