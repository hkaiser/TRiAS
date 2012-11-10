// Konstanten für Pufferbildung
// File: BUFKONST.HXX
// W. Mörtl

#if !defined(_BUFKONST_HXX)
#define _BUFKONST_HXX


// ********************************************************************************************
// Konstantendefinitionen
const double dTrigonom45 = 0.70710678118655;	// sin (45°) bzw. cos (45°)
const double dBuffWidth = 50.;	// default-Wert für Pufferbreite (in Meter)
const int iBuffNum = 1;			// default-Wert für Pufferanzahl
const double dFacEdgeLen = 0.1;	// default-Wert für Faktor, mit dem aus der Pufferbreite die
								// Kantenlänge für Approximation eines Kreisbogens an konvexer
								// Ecke ermittelt wird
const int iZug = 5;				// Zugabe in Bildschirmpixel für Rechteck beim Neuzeichnen

#endif  // _BUFKONST_HXX
