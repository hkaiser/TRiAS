// Berechnung des Offsets für Koordinatenübergang Bessel<-->Krassovsky
// File: EVALOFFSET.CPP
// Adapted from Klaus Kurth's modko_B

// Eingangskoordinaten: Bessel geodätisch
// Ausgangswerte: Offset in [m]

#include "begeodp.hxx"
#include "ctfgeogk.h"

void modko_B (long double B, long double L, long double *dHwert, long double *dRwert)
{
int iDL, iDB;
long double dlh, dlr, dbh, dbr, dH, dR, R, H;

	B /= 3600.0;	// in Grad umrechnen
	L /= 3600.0;

//	Transf. Bessel/Krassowski
long double FL = 4.0;			// Schrittweiten
long double FB = 6.0;

//	Trennlinie bei L=13.5 Grad
	if (L <= 13.5) {
		iDL = (int)((13.5 - L) * FL);
		if (B >= 52.0) {
			dH = 588.1;
			dR = 23.1;
			dlh = 0.2;
			dlr = -0.1;
			dbh = 0.1;
			dbr = 0.2;
			iDB = (int)((B - 52.0) * FB);
		} else {
			dH = 588.0;
			dR = 22.9;
			dlh = 0.2;
			dlr = -0.1;
			dbh = -0.1;
			dbr = -0.2;
			iDB = (int)((52.0 - B) * FB);
		}
	} else {	//	L > 13.5 
		iDL = (int)((L - 13.5) * FL);
		if (B >= 52.0) {
			dH = 587.7;
			dR = -9.8;
			dlh = -0.2;
			dlr = 0.1;
			dbh = 0.1;
			dbr = 0.2;
			iDB = (int)((B - 52.0) * FB);
		} else	{
			dH = 587.6;
			dR = -10.0;
			dlh = -0.2;
			dlr = 0.1;
			dbh = -0.1;
			dbr = -0.2;
			iDB = (int)((52.0 - B) * FB);
		}
	}

// 1.Schritt: Längendifferenz berechnen
double dDL = iDL;

	H = dH + (dDL * dlh);
	R = dR + (dDL * dlr);

// 2.Schritt: Breitendifferenz berechnen
double dDB = iDB;

	H += dDB * dbh;
	R += dDB * dbr;

	*dRwert = R;
	*dHwert = H;
}
