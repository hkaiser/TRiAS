// Routinen zur Kreis(bogen)berechnung
// File: KREIS.CXX
// W. Mörtl


#include "geoeditp.hxx"

#include <math.h>		// sqrt, ...

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



// Konstantendefintion
const long MaxAnz = 500;		// max. Eckenzahl des n-Ecks für Kreisfläche
const long MinAnz1 = 60;		// min. Eckenzahl des n-Ecks für Kreisfläche (darf nicht 0 sein !!!)
const long MinAnz2 = 5;			// min. Eckenzahl des n-Ecks für Kreisbogen (darf nicht 0 sein !!!)
const double KantenL = 100.;	// max. Kantenlänge des zu erzeugenden n-Ecks




// ---------------------------------------------------------------------------------------------                   
// Berechnung von Mittelpunkt und Radius eines Kreises bzw. Kreisbogens (true), der durch 3 Punkte
// gegeben ist.
// Ist Mittelpunkt nicht berechenbar bzw. Radius = 0, wird false zurückgegeben.
bool KreisParameter (Punkt& P0, Punkt& P1, Punkt& P2, double& r, double& xm, double& ym)
{
double x0 = P0.X();	// "double" wegen der nachfolgenden Quadrierung
double y0 = P0.Y();
double x1 = P1.X();
double y1 = P1.Y();
double x2 = P2.X();
double y2 = P2.Y();
double x0q = x0*x0;	// Quadrate der Koordinaten
double y0q = y0*y0;
double x1q = x1*x1;
double y1q = y1*y1;
double x2q = x2*x2;
double y2q = y2*y2;
double h1 = x1q - x2q + y1q - y2q;	// Hilfsgrößen
double h2 = x2q - x0q + y2q - y0q;
double h3 = x0q - x1q + y0q - y1q;
double h4 = 2.*(x0*(y1-y2) + x1*(y2-y0) + x2*(y0-y1));
double h5 = sqrt((x2 - x0)*(x2 - x0) + (y2 - y0)*(y2 - y0));

	if (h4 != 0)
	{
		xm = -(y0*h1 + y1*h2 + y2*h3)/h4;
		ym = (x0*h1 + x1*h2 + x2*h3)/h4;
	}
	else
	{
		// Fehlermeldung: Mittelpunktskoordinaten nicht berechenbar, da Punkte kollinear
		DEX_Error (RC_KreisParameter, EC_PKTEKOLLI);
		return false;
	}
	r = sqrt((x0 - xm)*(x0 - xm) + (y0 - ym)*(y0 - ym));
	if (r == 0)
	{
		// Fehlermeldung: Radius = 0
		DEX_Error (RC_KreisParameter, EC_RADIUS0);
		return false;
	}
	return true;
} // KreisParameter


// ---------------------------------------------------------------------------------------------                   
// Berechnung der Koordinaten eines Vollkreises aus 3 Punkten;
// dazu werden die Eckpunkte eines regelmäßigen n-Ecks mit n >= MinAnz1 ermittelt
bool Vollkreis (EObjekt* pEO, Punkt& P0, Punkt& P1, Punkt& P2, pWindow pW)
{
	TX_ASSERT (pEO != NULL);

ObjTyp OTyp = pEO -> isA ();	// Typ des zu editierenden Objektes

	if (OTyp != OT_KANTE && OTyp != OT_FLAECHE)
		return false;
		
// weitere Variablendefinitionen
double r;       // Radius
double xm, ym;	// Mittelpunktskoordinaten
double beta;    // Zentriwinkel der Segmente des n-Ecks (im Bogenmaß)
long n;			// Anzahl der Ecken (Stützpunkte)

// Berechnung von Radius und Mittelpunkt des Kreises
	if (KreisParameter (P0, P1, P2, r, xm, ym) == false)
		return false;

// Berechnung des Zentriwinkels der Segmente des n-Ecks
	if (r > 0.5*KantenL)
		beta = 2.*asin(0.5*KantenL/r);	// r==0 wird in KreisParameter abgefangen
	else
		// Bogenmaß für beta bei min. Eckenzahl
		beta = 2.*Pi/MinAnz1;	// Pi ist in geokonst.hxx definiert

KoOrd x, y;	// Koordinaten für Vollkreis
double wi;	// laufender Winkel bei n-Eck-Berechnung
Punkt Pt1; 	// Anfangspunkt bzw.
Punkt Pt2; 	//  Endpunkt für Zeichnen einer n-Eck-Linie auf Bildschirm

	n = DtoL (ceil(2.*Pi/beta));	// Anzahl der Ecken (Stützpunkte)
	if (n > MaxAnz) n = MaxAnz;		// max. Eckenzahl für n-Eck bei Kreisfläche
	if (n < MinAnz1) n = MinAnz1;	// min. Eckenzahl für n-Eck bei Kreisfläche
	beta = 2.*Pi/n;
	wi = Pi;
	for (long ni = 0; ni < n; ni++)
	{ 
		x = DtoL (xm + r*cos(wi));
		y = DtoL (ym + r*sin(wi));
		if (OTyp == OT_KANTE)
			((Kante*)pEO) -> AddPunkt (&x, &y, 1, -1);
		else	// Flächenobjekt
			((Masche*)pEO) -> AddPunkt (&x, &y, 1, -1, -1);
		wi += beta;
		
		// Linie auf Bildschirm zeichnen
		Pt2 = Punkt (x, y);	
		if (ni > 0)	// erst zeichnen, wenn mind. 2 Punkte erzeugt wurden
			DrawLine (Pt1, Pt2, false, pW);
		Pt1 = Pt2;
	}
	
	x = DtoL (xm - r);	// Koordinaten für Vollwinkel
	y = DtoL (ym);
	if (OTyp == OT_KANTE)
		((Kante*)pEO) -> AddPunkt (&x, &y, 1, -1);	// Vollkreis schließen
	else		// Flächenobjekt
		((Masche*)pEO) -> AddPunkt (&x, &y, 1, -1, -1);
		
	Pt2 = Punkt (x, y);	
	DrawLine (Pt1, Pt2, false, pW);
	
	return true;
} // Vollkreis

                   
// ---------------------------------------------------------------------------------------------                   
// Berechnung der Koordinaten eines Kreisbogens aus 3 Punkten; dabei wird der erste
// Punkt P0 als Anfangspunkt, der dritte P2 als Endpunkt gewertet; der mittlere 
// Punkt P1 bestimmt die Richtung des Kreisbogens; zwischen Anfangs- und Endpunkt
// werden Punkte eines regelmäßigen n-Ecks mit n >= MinAnz2 erzeugt
bool Kreisbogen (EObjekt* pEO, Punkt& P0, Punkt& P1, Punkt& P2, pWindow pW)
{
	TX_ASSERT (pEO != NULL);

ObjTyp OTyp = pEO -> isA ();	// Typ des zu editierenden Objektes

	TX_ASSERT (OTyp == OT_KANTE || OTyp == OT_FLAECHE);

	if (OTyp != OT_KANTE && OTyp != OT_FLAECHE)
		return false;
		
// weitere Variablendefinitionen
double r;       // Radius
double xm, ym;	// Mittelpunktskoordinaten
double beta;    // Zentriwinkel der Segmente des n-Ecks (im Bogenmaß)
long n;			// Anzahl der Ecken (Stützpunkte)

// Berechnung von Radius und Mittelpunkt des Kreisbogens
	if (KreisParameter (P0, P1, P2, r, xm, ym) == false)
		return false;

// Berechnung des Zentriwinkels der Segmente des n-Ecks
	if (r > 0.5*KantenL)
		beta = 2.*asin(0.5*KantenL/r);	// r==0 wird in KreisParameter abgefangen
	else
		// Bogenmaß für beta bei min. Eckenzahl
		beta = 2.*Pi/MinAnz2;

double wi1, wi2, wi;	// Winkel des Anfangs- bzw. Endpunktes des Kreisbogens bzw. laufender Winkel
double alpha;			// Zentriwinkel des Kreisbogens
KoOrd x0 = P0.X();
KoOrd y0 = P0.Y();
KoOrd x1 = P1.X();
KoOrd y1 = P1.Y();
KoOrd x2 = P2.X();
KoOrd y2 = P2.Y();

// Ermittlung der Drehrichtung des Kreisbogens (math. positiv bzw. negativ) richt == 0,
// d.h. Kollinearität der 3 Punkte wird schon in Routine KreisParameter abgefangen
short richt = BewegRicht (P0, P1, P2);

// Berechnung des Winkels von Anfangs- und Endpunkt des Kreisbogens unter
// Berücksichtigung der Lage im Quadrant
double hw1 = (y0-ym)/r;
double hw2 = (y2-ym)/r;

	if (hw1 > 1.) hw1 = 1.;		// kann durch Rundung eingetreten sein
	if (hw1 < -1.) hw1 = -1.;
	if (hw2 > 1.) hw2 = 1.;
	if (hw2 < -1.) hw2 = -1.;

	wi1 = asin(hw1);	// Winkel des Anfangspunktes
	wi2 = asin(hw2);	// Winkel des Endpunktes

	// Winkelkorrektur bezgl. der Quadranten
	if (x0 < xm) wi1 = Pi - wi1;
	if (x0 >= xm && y0 < ym) wi1 = 2.*Pi + wi1;
	if (x2 < xm) wi2 = Pi - wi2;
	if (x2 >= xm && y2 < ym) wi2 = 2.*Pi + wi2;
	
	// Berechnung des Zentriwinkels des Kreisbogens unter Berücksichtigung der Drehrichtung
	// des Kreisbogens (richt == 1: math. positiv, richt == -1: math. negativ)
	if (richt == 1)	// Drehrichtung math. positiv
	{
		alpha = wi2 - wi1;
		if (wi2 < wi1) alpha += 2.*Pi;
	}
	else			// Drehrichtung math. negativ
	{
		alpha = wi1 - wi2;
		if (wi1 < wi2) alpha += 2.*Pi;
	}

	n = DtoL (ceil(alpha/beta));    // Anzahl der Ecken (Stützpunkte)
	if (n > DtoL (MaxAnz*alpha/(2.*Pi)))
		n = DtoL (MaxAnz*alpha/(2.*Pi));		// max. Eckenzahl für n-Eck bei Kreisbogen
	if (n < MinAnz2) n = MinAnz2;   // min. Eckenzahl für n-Eck bei Kreisbogen
	beta = alpha/n;
	if (OTyp == OT_KANTE)
		((Kante*)pEO) -> AddPunkt (&x0, &y0, 1, -1);	// Koord. f. Anfangspunkt
	else
		((Masche*)pEO) -> AddPunkt (&x0, &y0, 1, -1, -1);
		
Punkt Pt1 (x0, y0);	// Anfangspunkt bzw.
Punkt Pt2;			//   Endpunkt für Zeichnen einer n-Eck-Linie auf Bildschirm
		
	wi = wi1;
	for (long ni = 1; ni < n; ni++)
	{
		if (richt > 0) wi += beta;      // Kreisbogen mit math. pos.
		else wi -= beta;		// bzw. math. neg. Drehsinn
		KoOrd x = DtoL (xm + r*cos(wi));
		KoOrd y = DtoL (ym + r*sin(wi));
		if (OTyp == OT_KANTE)
			((Kante*)pEO) -> AddPunkt (&x, &y, 1, -1);
		else
			((Masche*)pEO) -> AddPunkt (&x, &y, 1, -1, -1);
			
		// Linie auf Bildschirm zeichnen
		Pt2 = Punkt (x, y);	
		DrawLine (Pt1, Pt2, false, pW);
		Pt1 = Pt2;
			
	}
	if (OTyp == OT_KANTE)
		((Kante*)pEO) -> AddPunkt (&x2, &y2, 1, -1);	// Koordinaten für Endpunkt
	else
		((Masche*)pEO) -> AddPunkt (&x2, &y2, 1, -1, -1);

	Pt2 = Punkt (x2, y2);	
	DrawLine (Pt1, Pt2, false, pW);
	
	return true;
} // Kreisbogen
