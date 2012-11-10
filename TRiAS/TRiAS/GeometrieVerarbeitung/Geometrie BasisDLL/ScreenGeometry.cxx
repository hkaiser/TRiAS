// Geometrie auf dem Bildschirm
// File: ScreenGeometry.cxx
// W. Mörtl


#include "GeometrP.hxx"

#include "ScreenGeometry.hxx"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globaler Vergleichsoperator für Point
	bool operator < (const Point& Pt1, const Point& Pt2)
	{
		return max (Pt1.GetX(), Pt1.GetY()) < max (Pt2.GetX(), Pt2.GetY());
	}



///////////////////////////////////////////////////////////////////////////////////////////////
// Berechnung des Schnittpunktes SectPt1 zweier Strecken, die jeweils durch 2 Punkte APt1,EPt1
// und APt2,EPt2 gegeben sind;
// liegen die beiden Strecken teilweise oder vollständig übereinander, dann werden Anfangs- und
// Endpunkt des Überlappungsbereiches in SectPt1 und SectPt2 zurückgegeben;
// return-Werte können sein:
//   INSECT		Schnittpunkt SectPt1 existiert und liegt im Bildschirmbereich
//   OUTSECT	Schnittpunkt SectPt1 existiert und liegt außerhalb des Bildschirms
//   NOSECT		Schnittpunkt existiert nicht, SectPt1 und SectPt2 sind unbestimmt
//   INFISECT	ein eindeutiger Schnittpunkt existiert nicht (die beiden Strecken liegen
//              teilweise oder vollständig übereinander), SectPt1 und SectPt2 sind die
//              Endpunkte des Überlappungsbereiches
//   ERRSECT	Schnittpunkt nicht bestimmbar, da ein (oder beide) Punktepaare zu einem Punkt
//              zusammenfallen
SectScreen _GEOMETR_EXPORT SegmentSegmentIntersection (Point APt1, Point EPt1,
									  Point APt2, Point EPt2, Point& SectPt1, Point& SectPt2)
{
	if ((APt1.X() == EPt1.X() && APt1.Y() == EPt1.Y()) ||
		(APt2.X() == EPt2.X() && APt2.Y() == EPt2.Y()))
		return ERRSECT;		// ein (oder beide) Punktepaare fallen zu einem Punkt zusammen

	if (!Intersection (APt1.X(), APt1.Y(), EPt1.X(), EPt1.Y(), APt2.X(), APt2.Y(),
					   EPt2.X(), EPt2.Y()))
		return NOSECT;		// kein Punkt gemeinsam

// ein oder unendlich viele (teilweise oder vollständige Überlappung) Punkte gemeinsam
SectScreen ssRet = StraightStraightIntersection (APt1, EPt1, APt2, EPt2, SectPt1);

	_ASSERTE (NOSECT != ssRet && ERRSECT != ssRet);

	if (INSECT == ssRet || OUTSECT == ssRet)
		return ssRet;

	// ssRet == INFISECT: die beiden Trägergeraden sind identisch, d.h. es ist für
	// SegmentSegmentIntersection() immer noch INSECT bzw. INFISECT möglich (OUTSECT kann
	// nicht auftreten, weil dann die komplette 2. Strecke außerhalb des Bildschirms liegen
	// müßte)
	if (StraightsOverlapping (APt1, EPt1, APt2, EPt2, SectPt1, SectPt2))
		return INFISECT;
	return INSECT;

} // SegmentSegmentIntersection


// --------------------------------------------------------------------------------------------
// Berechnung des Schnittpunktes SectPt1 einer Strecke mit einer Geraden, die jeweils durch 2
// Punkte APt1,EPt1 (Strecke) und APt2,EPt2 (Gerade) gegeben sind;
// liegt die Strecke vollständig auf der Geraden, dann werden Anfangs- und Endpunkt des
// Überlappungsbereiches in SectPt1 und SectPt2 zurückgegeben;
// return-Werte können sein:
//   INSECT		Schnittpunkt SectPt1 existiert und liegt im Bildschirmbereich
//   OUTSECT	Schnittpunkt SectPt1 existiert und liegt außerhalb des Bildschirms
//   NOSECT		Schnittpunkt existiert nicht, SectPt1 und SectPt2 sind unbestimmt
//   INFISECT	ein eindeutiger Schnittpunkt existiert nicht (die Strecke liegt vollständig auf
//              der Geraden), SectPt1 und SectPt2 sind die Endpunkte des
//              Überlappungsbereiches
//   ERRSECT	Schnittpunkt nicht bestimmbar, da ein (oder beide) Punktepaare zu einem Punkt
//              zusammenfallen
SectScreen _GEOMETR_EXPORT SegmentStraightIntersection (Point APt1, Point EPt1,
									  Point APt2, Point EPt2, Point& SectPt1, Point& SectPt2)
{
SectScreen ssRet = StraightStraightIntersection (APt1, EPt1, APt2, EPt2, SectPt1);

	// die äußere if-Bedingung gilt möglicherweise nur für die Trägergerade der Strecke und die
	// Gerade, für die Strecke selbst und die Gerade aber u.U. nicht, deshalb noch die innere
	// if-Bedingung
	if (INSECT == ssRet || OUTSECT == ssRet)
	{
		if (IsPointOnStraight (SectPt1.X(), SectPt1.Y(), APt1.X(), APt1.Y(), EPt1.X(),
							   EPt1.Y()))
			return ssRet;
		return NOSECT;
	}

	if (INFISECT == ssRet)
	{
		SectPt1 = APt1;
		SectPt2 = EPt1;
		return INFISECT;
	}

	return ssRet;	// NOSECT, ERRSECT 

} // SegmentStraightIntersection


// --------------------------------------------------------------------------------------------
// Berechnung der Schnittpunkte SectPt1 und SectPt2 einer Strecke und eines Kreises, die durch
// 2 Punkte APt,EPt (Strecke) bzw. Mittelpunkt MPt und Radius iRad (Kreis) gegeben sind;
// return-Werte können sein:
//   INSECT		1 oder 2 Schnittpunkte SectPt1 und SectPt2 bzw. 1 Berührungspunkt SectPt1
//              existieren und liegen im Bildschirmbereich
//   OUTSECT	1 oder 2 Schnittpunkte bzw. 1 Berührungspunkt existieren und liegen alle
//              außerhalb des Bildschirms
//   INOUTSECT	2 Schnittpunkte SectPt1 und SectPt2 existieren, von denen einer innerhalb und
//              einer außerhalb des Bildschirmbereiches liegt
//   NOSECT		Schnittpunkte bzw. Berührungspunkt existieren nicht (SectPt1 und SectPt2 sind
//              unbestimmt)
//   ERRSECT	Schnittpunkt nicht bestimmbar, da das Punktepaar der Strecke zu einem Punkt
//              zusammenfällt bzw. der Radius des Kreises == 0 ist
SectScreen SegmentCircleIntersection (Point APt, Point EPt, Point MPt, int iRad, bool& bTwice,
									  Point& SectPt1, Point& SectPt2)
{
SectScreen ssRet = StraightCircleIntersection (APt, EPt, MPt, iRad, bTwice, SectPt1, SectPt2);

	if (NOSECT == ssRet || ERRSECT == ssRet)
		return ssRet;

// INSECT, OUTSECT bzw. INOUTSECT gilt für die Trägergerade der Strecke mit dem Kreis
bool b1 = IsPointOnStraight (SectPt1.X(), SectPt1.Y(), APt.X(), APt.Y(), EPt.X(), EPt.Y());
bool b2 = false;

	if (bTwice)
		b2 = IsPointOnStraight (SectPt2.X(), SectPt2.Y(), APt.X(), APt.Y(), EPt.X(), EPt.Y());

	(b1 && b2) ? (bTwice = true) : (bTwice = false);

	// wenn nur 1 Punkt auf der Strecke liegt, dann diesen immer über SectPt1 zurückgeben
	if (!b1 && b2)
	{
		SectPt1 = SectPt2;
		b1 = true;
		b2 = false;
	}

	if (INSECT == ssRet || OUTSECT == ssRet)
	{
		if (b1 || b2) return ssRet;
		return NOSECT;
	}

	_ASSERTE (INOUTSECT == ssRet);

	if (b1 && b2) return INOUTSECT;
	if (!b1 && !b2) return NOSECT;

	return IsPointInsideView (SectPt1);

} // SegmentCircleIntersection


// --------------------------------------------------------------------------------------------
// Berechnung des Schnittpunktes SectPt zweier Geraden, die jeweils durch 2 Punkte APt1,EPt1
// und APt2,EPt2 gegeben sind;
// return-Werte können sein:
//   INSECT		Schnittpunkt SectPt existiert und liegt im Bildschirmbereich
//   OUTSECT	Schnittpunkt SectPt existiert und liegt außerhalb des Bildschirms
//   NOSECT		Schnittpunkt existiert nicht (die beiden Geraden sind parallel), SectPt ist
//              unbestimmt
//   INFISECT	ein eindeutiger Schnittpunkt existiert nicht (die beiden Geraden sind
//              identisch), SectPt ist unbestimmt
//   ERRSECT	Schnittpunkt nicht bestimmbar, da ein (oder beide) Punktepaare zu einem Punkt
//              zusammenfallen
SectScreen _GEOMETR_EXPORT StraightStraightIntersection (Point APt1, Point EPt1, Point APt2,
														 Point EPt2, Point& SectPt)
{
	if ((APt1.X() == EPt1.X() && APt1.Y() == EPt1.Y()) ||
		(APt2.X() == EPt2.X() && APt2.Y() == EPt2.Y()))
		return ERRSECT;		// ein (oder beide) Punktepaare fallen zu einem Punkt zusammen

double a1 = EPt1.Y() - APt1.Y();
double b1 = APt1.X() - EPt1.X();
double a2 = EPt2.Y() - APt2.Y();
double b2 = APt2.X() - EPt2.X();
double c1 = -APt1.Y()*b1 - APt1.X()*a1;
double c2 = -APt2.Y()*b2 - APt2.X()*a2;

	// Test auf Parallelität
	if (0 != b1 && 0 != b2)			// keine der beiden Geraden senkrecht
	{
		if (a1/b1 == a2/b2)	// gleicher Anstieg
		{
			if (c1 != c2)		// Geraden sind nicht identisch, also echt parallel
				return NOSECT;
			return INFISECT;	// Geraden sind identisch
		}
	}
	else if (0 == b1 && 0 == b2)	// beide Geraden senkrecht
	{
		_ASSERTE (a1 != 0);
		_ASSERTE (a2 != 0);

		if (c1/a1 != c2/a2)		// Geraden sind nicht identisch, also echt parallel
			return NOSECT;
		return INFISECT;		// Geraden sind identisch
	}
	if (0 == a1 && 0 == a2)		// beide Geraden waagerecht
	{
		_ASSERTE (b1 != 0);
		_ASSERTE (b2 != 0);

		if (c1/b1 != c2/b2)		// Geraden sind nicht identisch, also echt parallel
			return NOSECT;
		return INFISECT;		// Geraden sind identisch
	}

double dNenner = a1*b2 - a2*b1;

	_ASSERTE (dNenner != 0);

	SectPt.X() = DtoL ((c2*b1 - c1*b2) / dNenner);
	SectPt.Y() = DtoL ((c1*a2 - c2*a1) / dNenner);

	return IsPointInsideView (SectPt);

} // StraightStraightIntersection


// --------------------------------------------------------------------------------------------
// Berechnung der Schnittpunkte SectPt1 und SectPt2 einer Geraden und eines Kreises, die durch
// 2 Punkte APt,EPt (Gerade) bzw. Mittelpunkt MPt und Radius iRad (Kreis) gegeben sind;
// return-Werte können sein:
//   INSECT		2 Schnittpunkte SectPt1 und SectPt2 bzw. 1 Berührungspunkt SectPt1
//              existieren und liegen im Bildschirmbereich
//   OUTSECT	2 Schnittpunkte bzw. 1 Berührungspunkt existieren und liegen alle außerhalb des
//              Bildschirms
//   INOUTSECT	2 Schnittpunkte SectPt1 und SectPt2 existieren, von denen einer innerhalb und
//              einer außerhalb des Bildschirmbereiches liegt
//   NOSECT		Schnittpunkte bzw. Berührungspunkt existieren nicht (SectPt1 und SectPt2 sind
//              unbestimmt)
//   ERRSECT	Schnittpunkt nicht bestimmbar, da das Punktepaar der Gerade zu einem Punkt
//              zusammenfällt bzw. der Radius des Kreises == 0 ist
SectScreen _GEOMETR_EXPORT StraightCircleIntersection (Point APt, Point EPt, Point MPt,
									  int iRad, bool& bTwice, Point& SectPt1, Point& SectPt2)
{
	if ((APt.X() == EPt.X() && APt.Y() == EPt.Y()) ||
		0 == iRad)
		return ERRSECT;		// Punktepaar der Gerade fällt zu einem Punkt zusammen bzw. Radius
							// des Kreises == 0
	// Gerade nicht senkrecht
	if (EPt.X() != APt.X())
	{
	// Anstieg und Absolutglied der Geraden
	double dAnst = (double)(EPt.Y() - APt.Y()) / (EPt.X() - APt.X());
	double dAbso = APt.Y() - dAnst*APt.X();

		return NotVerticalStraightCircle (dAnst, dAbso, MPt.X(), MPt.Y(), iRad, bTwice,
										  SectPt1, SectPt2);
	}

	// Gerade senkrecht
	_ASSERTE (APt.X() == EPt.X());

	return VerticalStraightCircle (APt.X(), MPt.X(), MPt.Y(), iRad, bTwice, SectPt1, SectPt2);

} // StraightCircleIntersection


// --------------------------------------------------------------------------------------------
// Berechnung der Schnittpunkte SectPt1 und SectPt2 zweier Kreises, die	jeweils durch den
// Mittelpunkt MPt und Radius iRad gegeben sind;
// return-Werte können sein:
//   INSECT		2 Schnittpunkte SectPt1 und SectPt2 bzw. 1 Berührungspunkt SectPt1
//              existieren und liegen im Bildschirmbereich
//   OUTSECT	2 Schnittpunkte bzw. 1 Berührungspunkt existieren und liegen alle außerhalb des
//              Bildschirms
//   INOUTSECT	2 Schnittpunkte SectPt1 und SectPt2 existieren, von denen einer innerhalb und
//              einer außerhalb des Bildschirmbereiches liegt
//   NOSECT		Schnittpunkte bzw. Berührungspunkt existieren nicht (SectPt1 und SectPt2 sind
//              unbestimmt)
//   INFISECT	ein eindeutiger Schnittpunkt existiert nicht (die Kreise liegt vollständig
//              aufeinander, SectPt1 und SectPt2 sind unbestimmt
//   ERRSECT	Schnittpunkt nicht bestimmbar, da mindestens ein Radius == 0 ist
SectScreen _GEOMETR_EXPORT CircleCircleIntersection (Point MPt1, int iRad1, Point MPt2,
									   int iRad2, bool& bTwice, Point& SectPt1, Point& SectPt2)
{
	if (0 == iRad1 || 0 == iRad2)
		return ERRSECT;		// mindestens ein Radius == 0

	if (MPt1.X() == MPt2.X() && MPt1.Y() == MPt2.Y() && iRad1 == iRad2)
		return INFISECT;	// beide Kreise sind identisch

	// Potenzlinie steht senkrecht auf der Verbindungsstrecke der beiden Kreismittelpunkte und
	// geht durch die beiden Kreisschnittpunkte, falls solche existieren
	// Potenzlinie nicht senkrecht
	if (MPt1.Y() != MPt2.Y())
	{
	// Anstieg und Absolutglied der Potenzlinie
	double dAnst = (double)(MPt1.X() -  MPt2.X()) / (MPt2.Y() - MPt1.Y());
	double dAbso = (MPt2.X()* MPt2.X() + MPt2.Y()*MPt2.Y() - iRad2*iRad2 - MPt1.X()*MPt1.X()
				   - MPt1.Y()*MPt1.Y() + iRad1*iRad1) / (2.0 * (MPt2.Y() - MPt1.Y()));

		return NotVerticalStraightCircle (dAnst, dAbso, MPt1.X(), MPt1.Y(), iRad1, bTwice,
										  SectPt1, SectPt2);
	}

	// Potenzlinie senkrecht
	_ASSERTE (MPt1.Y() == MPt2.Y());

// x-Koordinate eines Punktes, der auf der Potenzlinie liegt
double x = (MPt2.X()*MPt2.X() - iRad2*iRad2 - MPt1.X()*MPt1.X() + iRad1*iRad1) /
			(2.0 * (MPt1.X() - MPt2.X()));

	return VerticalStraightCircle (x, MPt1.X(), MPt1.Y(), iRad1, bTwice, SectPt1, SectPt2);

} // CircleCircleIntersection


// --------------------------------------------------------------------------------------------
// Test, ob sich 2 Strecken, die mindestens einen Punkt gemeinsam haben und deren Trägergeraden
// identisch sind, überlappen (return-Wert true) oder nur berühren (false);
// im Überlappungsfall werden in SectPt1 und SectPt2 der Anfangs- und Endpunkt des
// Überlappungsbereiches zurückgegeben; im Berührungsfall wird in SectPt1 der eine gemeinsame
// Punkt zurückgegeben
bool StraightsOverlapping (Point APt1, Point EPt1, Point APt2, Point EPt2, Point& SectPt1,
						   Point& SectPt2)
{
typedef list<Point> PointSet;
PointSet::iterator it;	// Iterator
PointSet PtS;			// Liste der Anfangs- und Endpunkte beider Strecken

	PtS.push_back (APt1);	// Punkte am Ende der Liste anfügen
	PtS.push_back (EPt1);
	PtS.push_back (APt2);
	PtS.push_back (EPt2);
	PtS.sort();

	it = PtS.begin();	// Iterator auf Anfang stellen
	it++;				// der zweit-kleinste Punkt

	SectPt1.X() = (*it).X();
	SectPt1.Y() = (*it).Y();
	it++;				// der dritt-kleinste Punkt
	if (SectPt1.X() != (*it).X() && SectPt1.Y() != (*it).Y())
	{
		SectPt2.X() = (*it).X();
		SectPt2.Y() = (*it).Y();
		return true;
	}

	return false;

} // StraightsOverlapping


// --------------------------------------------------------------------------------------------
// Berechnung der Schnittpunkte SectPt1 und SectPt2 einer NICHT senkrechten Geraden und eines
// Kreises, die durch Anstieg m und Absolutglied n (Gerade) bzw. Mittelpunkt (c,d) und Radius r
// (Kreis) gegeben sind
SectScreen NotVerticalStraightCircle (double m, double n, double c, double d, double r,
									  bool& bTwice, Point& SectPt1, Point& SectPt2)
{
double h1 = 1 + m*m;		// Hilfswerte 
double h2 = d - n - m*c;
// Radikant für Koordinaten der Schnitt(Berührungs)Punkte
double dRadik = r*r*h1 - h2*h2;

	if (dRadik > 0)		// 2 Schnittpunkte der Geraden mit dem Kreis
	{
		bTwice = true;

	double h3 = m*(d - n) + c;
	double h4 = sqrt (dRadik);
	double h5 = (h3 + h4) / h1;
	double h6 = (h3 - h4) / h1;

		SectPt1.X() = DtoL(h5);
		SectPt1.Y() = DtoL(m*h5 + n);
		SectPt2.X() = DtoL(h6);
		SectPt2.Y() = DtoL(m*h6 + n);

	SectScreen ss1 = IsPointInsideView (SectPt1);
	SectScreen ss2 = IsPointInsideView (SectPt2);

		if (ss1 == ss2) return ss1;
		if ((INSECT == ss1 && OUTSECT == ss2) || (OUTSECT == ss1 && INSECT == ss2))
			return INOUTSECT;
		return ERRSECT;
	}

	if (0 == dRadik)	// 1 Berührungspunkt
	{
		bTwice = false;

	double h3 = m*(d - n) + c;
	double h4 = h3 / h1;

		SectPt1.X() = DtoL(h4);
		SectPt1.Y() = DtoL(m*h4 + n);
		return IsPointInsideView (SectPt1);
	}

	return NOSECT;		// keine Schnitt- bzw. Berührungspunkte

} // NotVerticalStraightCircle


// --------------------------------------------------------------------------------------------
// Berechnung der Schnittpunkte SectPt1 und SectPt2 einer senkrechten Geraden und eines
// Kreises, die durch eine x-Koordinate (Gerade) bzw. Mittelpunkt (c,d) und Radius r (Kreis)
// gegeben sind
SectScreen VerticalStraightCircle (double x, double c, double d, double r, bool& bTwice,
								   Point& SectPt1, Point& SectPt2)
{
double h1 = x - c;
CoOrd diff = abs (h1);

	if (diff < r)	// 2 Schnittpunkte
	{
		bTwice = true;

	double h2 = sqrt (r*r + h1*h1);

		SectPt1.X() = x;
		SectPt1.Y() = d + h2;
		SectPt2.X() = x;
		SectPt2.Y() = d - h2;

	SectScreen ss1 = IsPointInsideView (SectPt1);
	SectScreen ss2 = IsPointInsideView (SectPt2);

		if (ss1 == ss2) return ss1;
		if ((INSECT == ss1 && OUTSECT == ss2) || (OUTSECT == ss1 && INSECT == ss2))
			return INOUTSECT;
		return ERRSECT;
	}

	if (diff == r)	// 1 Berührungspunkte
	{
		bTwice = true;
		SectPt1.X() = x;
		SectPt1.Y() = d;
		return INSECT;
	}

	return NOSECT;		// keine Schnitt- bzw. Berührungspunkte

} // VerticalStraightCircle


// --------------------------------------------------------------------------------------------
// Test, ob Pt innerhalb (return-Wert: true) oder außerhalb (false) des TRiAS-ViewFenster liegt
SectScreen IsPointInsideView (Point Pt)
{
HWND hWndV = ::GetDlgItem (__hWndM, VIEWCHILDID);	// VIEWCHILDID: Child-ID vom ViewFenster

	if (0 == hWndV)	// Projekt wird geschlossen oder kein Projekt geöffnet
		return ERRSECT;

Window Wnd(hWndV);	// TRiAS-ViewFenster
Rectangle CRc = Wnd.CanvasRect();

	if (Pt.X() >= 0 && Pt.X() <= CRc.Right() &&
		Pt.Y() >= 0 && Pt.Y() <= CRc.Top())
		return INSECT;		// Punkt innerhalb des TRiAS-ViewFenster
	return OUTSECT;

} // IsPointInsideView

/*
// --------------------------------------------------------------------------------------------
SectScreen _GEOMETR_EXPORT GeradenLotPunkt
bool _GEOMETR_EXPORT StreckenLotPunkt
*/
