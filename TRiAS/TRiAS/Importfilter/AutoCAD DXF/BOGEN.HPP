/*
Datei: BOGEN.HPP

Erarbeitet: M. Mörtl				Stand vom 25.August 1995
*/

#ifndef BOGEN_HPP
#define BOGEN_HPP

// Berechnung von Mittelpunkt (MPx, MPy), Radius (Radius), Anfangs- (StartWi) und Endwinkel (StopWi)
// eines Kreisbogens;
// gegeben sind der Anfangs- (P1x, P1y), Endpunkt (P2x, P2y) und Zentriwinkel (Winkel) des Kreisbogens;
// Rückgabe von false, wenn Parameter nicht berechnbar sind
Bool GetBogenParam (double P1x, double P1y, double P2x, double P2y, double Winkel,
					double &MPx, double &MPy, double &Radius, double &StartWi, double &StopWi);

#endif		// BOGEN_HPP


