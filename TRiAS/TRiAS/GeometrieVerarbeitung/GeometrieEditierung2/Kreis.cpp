// Definitionen: Routinen zur Kreis(bogen)berechnung
// File: Kreis.cpp
// W. Mörtl


#include "GeoEditP.h"

#include "BasicFunctions.hxx"	// TurnDirection()


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



// --------------------------------------------------------------------------------------------
// Berechnung von Mittelpunkt und Radius eines Kreises bzw. Kreisbogens (true), der durch 3
// Punkte gegeben ist.
// Ist Mittelpunkt nicht berechenbar bzw. Radius = 0, wird false zurückgegeben.
bool KreisParameter (EPunkt& P0, EPunkt& P1, EPunkt& P2, double& r, double& xm, double& ym)
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


// --------------------------------------------------------------------------------------------
// Berechnung der Koordinaten eines Vollkreises aus 3 Punkten;
// dazu werden die Eckpunkte eines regelmäßigen n-Ecks mit n >= lMinAnz1 ermittelt
bool Vollkreis (IObjektGeometrie* pIOG, EPunkt& P0, EPunkt& P1, EPunkt& P2, pWindow pW)
{
	_ASSERTE (pIOG != NULL);

	if (! pIOG) return false;

short iOTyp;	// Typ des zu editierenden Objektes

	pIOG->GetObjTyp (&iOTyp);

	if (iOTyp != OT_KANTE && iOTyp != OT_FLAECHE)
		return false;
		
// weitere Variablendefinitionen
double r;       // Radius
double xm, ym;	// Mittelpunktskoordinaten
double beta;    // Zentriwinkel der Segmente des n-Ecks (im Bogenmaß)

// Berechnung von Radius und Mittelpunkt des Kreises
	if (KreisParameter (P0, P1, P2, r, xm, ym) == false)
		return false;

	_ASSERTE (r > 0);		// r==0 wird in KreisParameter() abgefangen

// Berechnung des Zentriwinkels der Segmente des n-Ecks
	if (r > 0.5*dKantenL)
		beta = 2.*asin(0.5*dKantenL/r);
	else
	{
		// Bogenmaß für beta bei minimaler Eckenzahl
		if (lMinAnz1 > 0)
			beta = 2.*Pi/lMinAnz1;	// Pi ist in geokonst.hxx definiert
		else
		{
			_ASSERTE (lMinAnz1 > 0);

			beta = 2.*Pi;
		}
	}

EPunkt Pkt1; 	// Anfangspunkt bzw.
EPunkt Pkt2; 	//  Endpunkt für Zeichnen einer n-Eck-Linie auf Bildschirm

long n = DtoL (ceil(2.*Pi/beta));	// Anzahl der Ecken (Stützpunkte)

	if (n > lMaxAnz) n = lMaxAnz;	// maximale Eckenzahl für n-Eck bei Kreisfläche
	if (n < lMinAnz1) n = lMinAnz1;	// minimale Eckenzahl für n-Eck bei Kreisfläche
	beta = 2.*Pi/n;

short iKCnt;	// Anzahl der Konturen von pIOG (für Linienobjekt: 0)

	pIOG->GetKCnt (&iKCnt);

double wi = Pi;		// Startwert für laufenden Winkel bei n-Eck-Berechnung

	for (long ni = 0; ni < n; ni++)
	{ 
	KoOrd x = DtoL (xm + r*cos(wi));
	KoOrd y = DtoL (ym + r*sin(wi));

		pIOG->AddPunkt (x, y, -1, iKCnt-1);
		wi += beta;
		
		// Linie auf Bildschirm zeichnen
		Pkt2.X() = x;	
		Pkt2.Y() = y;	
		if (ni > 0)	// erst zeichnen, wenn mindestens 2 Punkte erzeugt wurden
			DrawLine (Pkt1, Pkt2, false, pW);
		Pkt1 = Pkt2;
	}
	
KoOrd x = DtoL (xm - r);	// Koordinaten für Vollwinkel
KoOrd y = DtoL (ym);

	pIOG->AddPunkt (x, y, -1, iKCnt-1);	// Vollkreis schließen
		
	Pkt2.X() = x;	
	Pkt2.Y() = y;	
	DrawLine (Pkt1, Pkt2, false, pW);
	
	return true;

} // Vollkreis

                   
// --------------------------------------------------------------------------------------------
// Berechnung der Koordinaten eines Kreisbogens aus 3 Punkten; dabei wird der erste
// EPunkt P0 als Anfangspunkt, der dritte P2 als Endpunkt gewertet; der mittlere 
// EPunkt P1 bestimmt die Richtung des Kreisbogens; zwischen Anfangs- und Endpunkt
// werden Punkte eines regelmäßigen n-Ecks mit n >= lMinAnz2 erzeugt
bool Kreisbogen (IObjektGeometrie* pIOG, EPunkt& P0, EPunkt& P1, EPunkt& P2, pWindow pW)
{
	_ASSERTE (pIOG != NULL);

	if (! pIOG) return false;

short iOTyp;	// Typ des zu editierenden Objektes

	pIOG->GetObjTyp (&iOTyp);

	_ASSERTE (iOTyp == OT_KANTE || iOTyp == OT_FLAECHE);

	if (iOTyp != OT_KANTE && iOTyp != OT_FLAECHE)
		return false;
		
// weitere Variablendefinitionen
double r;       // Radius
double xm, ym;	// Mittelpunktskoordinaten
double beta;    // Zentriwinkel der Segmente des n-Ecks (im Bogenmaß)

// Berechnung von Radius und Mittelpunkt des Kreisbogens
	if (KreisParameter (P0, P1, P2, r, xm, ym) == false)
		return false;

	_ASSERTE (r > 0);		// r==0 wird in KreisParameter() abgefangen

// Berechnung des Zentriwinkels der Segmente des n-Ecks
	if (r > 0.5*dKantenL)
		beta = 2.*asin(0.5*dKantenL/r);
	else
	{
		// Bogenmaß für beta bei minimaler Eckenzahl
		if (lMinAnz2 > 0)
			beta = 2.*Pi/lMinAnz2;
		else
		{
			_ASSERTE (lMinAnz2 > 0);

			beta = 2.*Pi;
		}
	}

KoOrd x0 = P0.X();
KoOrd y0 = P0.Y();
KoOrd x1 = P1.X();
KoOrd y1 = P1.Y();
KoOrd x2 = P2.X();
KoOrd y2 = P2.Y();

// Ermittlung der Drehrichtung des Kreisbogens (mathematisch positiv bzw. negativ) iRicht == 0,
// d.h. Kollinearität der 3 Punkte wird schon in Routine KreisParameter() abgefangen
int iRicht = TurnDirection (x0, y0, x1, y1, x2, y2);

// Berechnung des Winkels von Anfangs- und Endpunkt des Kreisbogens unter
// Berücksichtigung der Lage im Quadrant
double hw1 = (y0-ym)/r;
double hw2 = (y2-ym)/r;

	if (hw1 > 1.) hw1 = 1.;		// kann durch Rundung eingetreten sein
	if (hw1 < -1.) hw1 = -1.;
	if (hw2 > 1.) hw2 = 1.;
	if (hw2 < -1.) hw2 = -1.;

double wi1 = asin(hw1);	// Winkel des Anfangspunktes
double wi2 = asin(hw2);	// Winkel des Endpunktes

	// Winkelkorrektur bzgl. der Quadranten
	if (x0 < xm) wi1 = Pi - wi1;
	if (x0 >= xm && y0 < ym) wi1 = 2.*Pi + wi1;
	if (x2 < xm) wi2 = Pi - wi2;
	if (x2 >= xm && y2 < ym) wi2 = 2.*Pi + wi2;
	
// Berechnung des Zentriwinkels des Kreisbogens unter Berücksichtigung der Drehrichtung
// des Kreisbogens (iRicht == 1: mathematisch positiv, iRicht == -1: mathematisch negativ)
double alpha;	// Zentriwinkel des Kreisbogens

	if (iRicht == 1)	// Drehrichtung mathematisch positiv
	{
		alpha = wi2 - wi1;
		if (wi2 < wi1) alpha += 2.*Pi;
	}
	else				// Drehrichtung mathematisch negativ
	{
		alpha = wi1 - wi2;
		if (wi1 < wi2) alpha += 2.*Pi;
	}

long n = DtoL (ceil(alpha/beta));    // Anzahl der Ecken (Stützpunkte)

	if (n > DtoL (lMaxAnz*alpha/(2.*Pi)))
		n = DtoL (lMaxAnz*alpha/(2.*Pi));	// maximale Eckenzahl für n-Eck bei Kreisbogen
	if (n < lMinAnz2) n = lMinAnz2;			// minimale Eckenzahl für n-Eck bei Kreisbogen
	beta = alpha/n;

short iKCnt;	// Anzahl der Konturen von pIOG (für Linienobjekt: 0)

	pIOG->GetKCnt (&iKCnt);
	pIOG->AddPunkt (x0, y0, -1, iKCnt-1);	// Koordinaten für Anfangspunkt
		
EPunkt Pkt1 (x0, y0);	// Anfangspunkt bzw.
EPunkt Pkt2;			//  Endpunkt für Zeichnen einer n-Eck-Linie auf Bildschirm
		
double wi = wi1;		// laufender Winkel

	for (long ni = 1; ni < n; ni++)
	{
		if (iRicht > 0) wi += beta;	// Kreisbogen mit mathematisch positivem
		else wi -= beta;			// bzw. mathematisch negativem Drehsinn

	KoOrd x = DtoL (xm + r*cos(wi));
	KoOrd y = DtoL (ym + r*sin(wi));

		pIOG->AddPunkt (x, y, -1, iKCnt-1);
			
		// Linie auf Bildschirm zeichnen
		Pkt2.X() = x;	
		Pkt2.Y() = y;	
		DrawLine (Pkt1, Pkt2, false, pW);
		Pkt1 = Pkt2;
	}

	pIOG->AddPunkt (x2, y2, -1, iKCnt-1);	// Koordinaten für Endpunkt

	Pkt2.X() = x2;	
	Pkt2.Y() = y2;	
	DrawLine (Pkt1, Pkt2, false, pW);
	
	return true;

} // Kreisbogen
