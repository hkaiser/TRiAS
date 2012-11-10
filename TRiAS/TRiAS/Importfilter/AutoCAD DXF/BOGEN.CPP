// Parameter für Kreisbogen
// File: BOGEN.CPP
/*
	Erarbeitet: W. Mörtl 						Stand vom 30. August 1995
*/


#include "pheader.hpp"
// #include "toporelp.hxx"

#include <math.h>			// tan(), ...
#include "bogen.hpp"		// zugeh. Header


// ---------------------------------------------------------------------------------------------------                   
// Berechnung von Mittelpunkt (MPx, MPy), Radius (Radius), Anfangs- (StartWi) und Endwinkel (StopWi)
// eines Kreisbogens;
// gegeben sind der Anfangs- (P1x, P1y), Endpunkt (P2x, P2y) und Zentriwinkel (Winkel) des Kreisbogens;
// Rückgabe von false, wenn Parameter nicht berechnbar sind
Bool GetBogenParam (double P1x, double P1y, double P2x, double P2y, double Winkel,
					double &MPx, double &MPy, double &Radius, double &StartWi, double &StopWi)
{
double pi = 2. * asin (1.);			// Pi = 3.14...
Bool bTan = fabs (Winkel) != pi;	// tan (Winkel/2.) ist für fabs (Winkel) == pi nicht berechenbar
double tw2;							// 2. * tan (Winkel/2.);

	if (bTan)
		tw2 = 2. * tan (Winkel / 2.);

	if ((P1x == P2x && P1y == P2y) ||	// Anfangs- und Endpunkt sind identisch, kein Kreisbogen
		(bTan && tw2 == 0))				// bedeutet: kein Kreisbogen
		return false;					// keine Parameter berechenbar

// 1. Schritt: Berechnung des Mittelpunktes (xm, ym) der Verbindungsstrecke zwischen dem
//             Anfangs- (P1x, P1y) und Endpunkt (P2x, P2y) des Kreisbogens
double xm = (P1x + P2x) / 2.;
double ym = (P1y + P2y) / 2.;

// 2. Schritt: Berechnung des Mittelpunktes (MPx, MPy) aus der
//             Punkt-Richtungs-Gleichung MPy - ym = mr * (MPx - xm) und dem
//             Abstand h² = (MPy - ym)² + (MPx - xm)²
//             Dabei gilt mr = -dx / dy und h = a / tw2 mit a = sqrt (dx*dx + dy*dy)
double dx = P2x - P1x;
double dy = P2y - P1y;

	if (bTan)
	{
		MPx = xm - dy / tw2;	// tw2 == 0 wird schon am Beginn der Routine abgefangen
		MPy = ym + dx / tw2;
	}
	else
	{
		MPx = xm;
		MPy = ym;
	}

// 3. Schritt: Berechnung des Radius des Kreisbogens aus
//             Radius = sqrt (h*h + a*a/4.)
	if (bTan)
		Radius = sqrt ((dx*dx + dy*dy) * (tw2*tw2/4. + 1.)) / tw2;
	else
		Radius = sqrt (dx*dx + dy*dy) / 2.;
	Radius = fabs (Radius);

// 4. Schritt: Berechnung von Anfangs- (StartWi) und Endwinkel (StopWi) des Kreisbogens
//             Radius = 0 kann kann nur dann auftreten, wenn P1 == P2 gilt; dieser Fall wurde
//             schon am Beginn der Routine abgefangen.
double hw1 = (P1y - MPy) / Radius;	// Hilfswerte
double hw2 = (P2y - MPy) / Radius;

	if (hw1 > 1.) hw1 = 1.;		// kann durch Rundung eingetreten sein
	if (hw1 < -1.) hw1 = -1.;
	if (hw2 > 1.) hw2 = 1.;
	if (hw2 < -1.) hw2 = -1.;

	StartWi = asin (hw1);
	StopWi = asin (hw2);

	// evtl. Winkelkorrektur bezgl. der Lage in den Quadranten
	if (P1x < MPx)
		StartWi = pi - StartWi;
	if (P1x >= MPx && P1y < MPy)
		StartWi += 2.*pi;
	if (P2x < MPx)
		StopWi = pi - StopWi;
	if (P2x >= MPx && P2y < MPy)
		StopWi = 2.*pi + StopWi;
	if (Winkel > 0 && StartWi > StopWi)
		StartWi -= 2.*pi;
	if (Winkel < 0 && StartWi < StopWi)
		StopWi -= 2.*pi;

	return true;
}
