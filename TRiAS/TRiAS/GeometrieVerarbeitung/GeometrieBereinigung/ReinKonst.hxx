// Konstanten für GeometrieBereinigung
// File: REINKONST.HXX
// W. Mörtl

#if !defined(_REINKONST_HXX)
#define _REINKONST_HXX


// ********************************************************************************************
// Konstantendefinitionen
const bool bClear = true;		// automatisch bereinigbare GeometrieFehler werden auch
								// automatisch bereinigt (true) bzw. nicht (false)
const double dRedEps = 0.0;		// Wert (0.00 ... 1.00) für die Reduzierung der
								// Stützpunktanzahl bei der Polygonapproximation, d.h. im
								// default-Fall keine Polygonapproximation
const int k0 = 5;				// Anzahl der auf Kollinearität untersuchten Strecken (typisch für
								// k0 sind Werte zwischen 5 und 10)

#endif  // _REINKONST_HXX
