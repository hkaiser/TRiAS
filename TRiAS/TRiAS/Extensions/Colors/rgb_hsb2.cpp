
#include "stdafx.h"

#include <stdlib.h>
#include <math.h>

#include "rgb_hsb2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef enum tagHIGHLOW {
	HIGHLOW_UNKNOWN,	// unbekannt
	HIGHLOW_LOW,		// war kleiner als untere Grenze
	HIGHLOW_HIGH,		// war größer als obere Grenze
} HIGHLOW;

typedef enum tagTARGETCOLOR {
	TARGETCOLOR_UNKNOWN,
	TARGETCOLOR_RED,
	TARGETCOLOR_GREEN,
	TARGETCOLOR_BLUE,
} TARGETCOLOR;

///////////////////////////////////////////////////////////////////////////////
// Rückrechnung des Farbanteiles aus Einzelreiz-Luminanz
inline double Farbanteil (double dReiz, double dMax)
{
	return pow(dReiz/dMax, 1.0/GAMMA);
}

///////////////////////////////////////////////////////////////////////////////
// Teilsättigung berechnen
double GetHue (double dColor1, double dColor2)
{
	if (dColor1 < dColor2) {
		return 1.0 - dColor1/dColor2;
	} else if (dColor1 > dColor2) {
		return dColor2/dColor1 - 1.0;
	} else
		return 0.0;
}

///////////////////////////////////////////////////////////////////////////////
// (inversen) Sättigungsgrad einer Farbe bestimmen
inline double EvalSatKoeff (double dGrau, double dColor, double dMax, 
							HIGHLOW &rrgStatus)
{
	ASSERT(0.0 < dColor && dColor < dMax);		// darf nicht gesättigt sein

// wenn die Differenz null ist, dann darf dieser Farbanteil keine 
// Berücksichtigung finden
double dDiff = dColor - dGrau;

	if (dDiff >= 0.0) {
		rrgStatus = HIGHLOW_HIGH;
		return dDiff/(dMax - dGrau);
	} else {
		rrgStatus = HIGHLOW_LOW;
		return dDiff/dGrau;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Feststellen, ob Farge gesättigt ist
inline bool IsSaturatedMax (double dColor, double dMax)
{
	return (dMax == dColor) ? true : false;
}

inline bool IsSaturatedMin (double dColor)
{
	return (0.0 == dColor) ? true : false;
}

inline int IsSaturated (double dColor, double dMax)
{
	return IsSaturatedMin(dColor) + (IsSaturatedMax (dColor, dMax) << 1);
}

///////////////////////////////////////////////////////////////////////////////
// Farbwert Skalieren, um gesättigte Farbe zu erhalten
inline double CorrectColor (double dYGrau, double dY, double dKoeff)
{
	ASSERT(0.0 != dKoeff);
	return dYGrau + ((dY - dYGrau) / dKoeff);
}

///////////////////////////////////////////////////////////////////////////////
// RGB --> HSB
///////////////////////////////////////////////////////////////////////////////
unsigned long RGBtoHSB (Color C) 
{
	return RGBtoHSB (C.Red(), C.Green(), C.Blue());
}

unsigned long RGBtoHSB (int iRed, int iGreen, int iBlue)
{
	ASSERT(0 <= iRed && 255 >= iRed);
	ASSERT(0 <= iGreen && 255 >= iGreen);
	ASSERT(0 <= iBlue && 255 >= iBlue);

double dHue = 0.0;
double dSat = 0.0;
double dBright = 0.0;
double dRed = (double)iRed / 255.0;
double dGreen = (double)iGreen / 255.0;
double dBlue = (double)iBlue / 255.0;

	RGBtoHSBService (dRed, dGreen, dBlue, dHue, dSat, dBright);

return HSB((int)((dSat*255.0)+0.5), (int)((dBright*65535.0)+0.5), (int)(((dHue*255.0)/360)+0.5));
}

void RGBtoHSBService (double dRed, double dGreen, double dBlue,
					  double &rdHue, double &rdSat, double &rdBright)
{
// 1. Helligkeit berechnen
double dYR = HelligkeitRot(dRed);
double dYG = HelligkeitGruen(dGreen);
double dYB = HelligkeitBlau(dBlue);
double dY = dYR + dYG + dYB;			// Gesamtluminanz

	rdBright = Wahrnehmung(dY);

// 2. Sättigung berechnen
double dYRGrau = BEZUGSWERT_ROT*dY;		// anteilige Helligkeiten des zugehörigen Grauwertes
double dYGGrau = BEZUGSWERT_GRUEN*dY;
double dYBGrau = BEZUGSWERT_BLAU*dY;

HIGHLOW rgStatus = HIGHLOW_UNKNOWN;
TARGETCOLOR rgTarget = TARGETCOLOR_UNKNOWN;

// 2.1. testen, ob eine der Farbanteile bereits gesättigt ist
double dYRSatt = dYR;
double dYGSatt = dYG;
double dYBSatt = dYB;
int fSaturatedRot = IsSaturated (dYR, BEZUGSWERT_ROT);
int fSaturatedGruen = IsSaturated (dYG, BEZUGSWERT_GRUEN);
int fSaturatedBlau = IsSaturated (dYB, BEZUGSWERT_BLAU);

int fSaturatedSum = fSaturatedRot & fSaturatedGruen;

	fSaturatedSum &= fSaturatedBlau;
	if (fSaturatedSum) {
	// weiß oder schwarz
		rdSat = 0.0;	// Farbe ist vollständig entsättigt
		rdHue = 0.0;	// per Definition
		return;	
	}

	if (fSaturatedRot) {
		rgStatus = (0.0 == dYR) ? HIGHLOW_LOW : HIGHLOW_HIGH;
		rgTarget = TARGETCOLOR_RED;
		rdSat = 1.0;				// volle Sättigung
	} else if (fSaturatedGruen) {
		rgStatus = (0.0 == dYG) ? HIGHLOW_LOW : HIGHLOW_HIGH;
		rgTarget = TARGETCOLOR_GREEN;
		rdSat = 1.0;				// volle Sättigung
	} else if (fSaturatedBlau) {
		rgStatus = (0.0 == dYB) ? HIGHLOW_LOW : HIGHLOW_HIGH;
		rgTarget = TARGETCOLOR_BLUE;
		rdSat = 1.0;				// volle Sättigung
	} else {
	// gesättigte Farbe bestimmen
	HIGHLOW rgRStatus = HIGHLOW_UNKNOWN;
	HIGHLOW rgGStatus = HIGHLOW_UNKNOWN;
	HIGHLOW rgBStatus = HIGHLOW_UNKNOWN;
	double dKR = EvalSatKoeff (dYRGrau, dYR, BEZUGSWERT_ROT, rgRStatus);
	double dKG = EvalSatKoeff (dYGGrau, dYG, BEZUGSWERT_GRUEN, rgGStatus);
	double dKB = EvalSatKoeff (dYBGrau, dYB, BEZUGSWERT_BLAU, rgBStatus);

	// der Farbanteil mit dem maximalen (inversen) Koeffizienten
	// ist die entscheidende
	double dKMax = __max(fabs(dKR), __max(fabs(dKG), fabs(dKB)));

		if (0.0 == dKMax) {
			rdSat = 0.0;	// Farbe ist vollständig entsättigt
			rdHue = 0.0;	// per Definition
			return;	
		} else {
			if (dKMax == fabs(dKR)) {
				rgStatus = rgRStatus;
				rgTarget = TARGETCOLOR_RED;
			} else if (dKMax == fabs(dKG)) {
				rgStatus = rgGStatus;
				rgTarget = TARGETCOLOR_GREEN;
			} else if (dKMax == fabs(dKB)) {
				rgStatus = rgBStatus;
				rgTarget = TARGETCOLOR_BLUE;
			} 

		// gesättigte Farbanteile berechnen
			dYRSatt = CorrectColor (dYRGrau, dYR, dKMax);
			dYGSatt = CorrectColor (dYGGrau, dYG, dKMax);
			dYBSatt = CorrectColor (dYBGrau, dYB, dKMax);

			if (dYRSatt != dYRGrau)
				rdSat = (dYR - dYRGrau)/(dYRSatt - dYRGrau);
			else if (dYGSatt != dYGGrau)
				rdSat = (dYG - dYGGrau)/(dYGSatt - dYGGrau);
			else if (dYBSatt != dYBGrau)
				rdSat = (dYB - dYBGrau)/(dYBSatt - dYBGrau);
			else
				ASSERT(false);
		}
	}

	ASSERT(rgTarget != TARGETCOLOR_UNKNOWN);
	ASSERT(rgStatus != HIGHLOW_UNKNOWN);

// 3. Farbwert bestimmen
double dRSatt = Farbanteil (dYRSatt, BEZUGSWERT_ROT);
double dGSatt = Farbanteil (dYGSatt, BEZUGSWERT_GRUEN);
double dBSatt = Farbanteil (dYBSatt, BEZUGSWERT_BLAU);

	if (HIGHLOW_LOW == rgStatus) {
		switch (rgTarget) {
		case TARGETCOLOR_RED:
			rdHue = GetHue (dGSatt, dBSatt) + 3.0;
			break;

		case TARGETCOLOR_GREEN:
			rdHue = GetHue (dBSatt, dRSatt) + 5.0;
			break;

		case TARGETCOLOR_BLUE:
			rdHue = GetHue (dRSatt, dGSatt) + 1.0;
			break;
		}
	} else {
		switch (rgTarget) {
		case TARGETCOLOR_RED:
			rdHue = GetHue (1.0-dGSatt, 1.0-dBSatt);
			if (rdHue < 0.0) rdHue += 6.0;
			break;

		case TARGETCOLOR_GREEN:
			rdHue = GetHue (1.0-dBSatt, 1.0-dRSatt) + 2.0;
			break;

		case TARGETCOLOR_BLUE:
			rdHue = GetHue (1.0-dRSatt, 1.0-dGSatt) + 4.0;
			break;
		}
	}
	rdHue *= 60.0;
	while (rdHue >= 360.0)
		rdHue -= 360.0;
}

///////////////////////////////////////////////////////////////////////////////
// Helligkeit eines Farbanteiles über Verhältnis zweier anderer berechnen
// geht nur für dunkelklare Farben
inline double InvHelligkeit (double dY, double dK1, double dCol, double dK2)
{
	return pow (dY/(dK1*pow(dCol, GAMMA)+dK2), 1.0/GAMMA);
}

///////////////////////////////////////////////////////////////////////////////
// aus gesättigtem Farbwert Ergebnis finden
inline double InvCorrectColor (
	double dYGrau, double dYColor, double dSat, double /*dKoeff*/)
{
	return (dYGrau + dSat*(dYColor - dYGrau));
}

///////////////////////////////////////////////////////////////////////////////
// Helligkeit eines Farbanteiles über Verhältnis zweier anderer berechnen
// Iterative Berechnung für hellklare Farben
typedef double (* MAPCALC)(double, double);

inline double RotGelb (double dGruen, double dBlau)
	{ return Helligkeit (1.0, dGruen, dBlau); }
inline double GelbGruen (double dRot, double dBlau)
	{ return Helligkeit (dRot, 1.0, dBlau); }
inline double GruenCyan (double dBlau, double dRot)
	{ return Helligkeit (dRot, 1.0, dBlau); }
inline double CyanBlau (double dGruen, double dRot)
	{ return Helligkeit (dRot, dGruen, 1.0); }
inline double BlauMagenta (double dRot, double dGruen)
	{ return Helligkeit (dRot, dGruen, 1.0); }
inline double MagentaRot (double dBlau, double dGruen)
	{ return Helligkeit (1.0, dGruen, dBlau); }

inline double InvHelligkeitIter (
	double dY, double dTarget, MAPCALC Calc, double &rdColor)
{
double dK = 1.0 - dTarget;
double dCurr = 0.5;			// aktueller BezugsFarbAnteil
double dDelta = 0.25;

	while (1) {
	double dColor2 = dCurr;
	double dColor1 = 1.0 - dK*(1.0 - dColor2);
	double dYCurr = Calc (dColor1, dColor2);

		if (fabs(dYCurr - dY) <= ITER_STOP) {
			rdColor = dColor1;
			return dColor2;
		}

		if (dYCurr > dY) 
			dCurr -= dDelta;
		else
			dCurr += dDelta;
		dDelta /= 2;
	}

	ASSERT(false);		// not reachable code
	return 0.0;
}

///////////////////////////////////////////////////////////////////////////////
// HSB --> RGB 
///////////////////////////////////////////////////////////////////////////////
Color HSBtoRGB (unsigned long hsb) 
{
	return HSBtoRGB (GetHValue (hsb), GetSValue (hsb), GetVValue (hsb));
}

Color HSBtoRGB (int iHue, int iSat, int iBright)
{
	ASSERT(0 <= iHue && iHue <= 255);
	ASSERT(0 <= iSat && iSat <= 255);
	ASSERT(0 <= iBright && iBright <= 65535);

double dHue = ((double)iHue*360.0)/255.0;
double dSat = (double)iSat / 255.0;
double dBright = (double)iBright / 65535.0;
double dRed = 0.0;
double dGreen = 0.0;
double dBlue = 0.0;

	HSBtoRGBService (dHue, dSat, dBright, dRed, dGreen, dBlue);

return Color ((ColorVal)((255.0 * dRed)+0.5), (ColorVal)((255.0 * dGreen)+0.5),
		      (ColorVal)((255.0 * dBlue)+0.5));
}

void HSBtoRGBService (double dHue, double dSat, double dBright,
				      double &rdRed, double &rdGreen, double &rdBlue)
{
// Gesamtluminanz aus Helligkeit rückrechnen
double dY = InvWahrnehmung(dBright);
double dRSatt = 0.0, dGSatt = 0.0, dBSatt = 0.0;

// über Farbwert Fallunterscheidung vornehmen und Anteile der 
// gesättigten Farbe bestimmen
	dHue /= 60.0;
	switch ((int)floor(dHue)) {
	case 0:		// rot-gelb
		{
		double dCol = dHue;
		double dYRein = Helligkeit (1.0, dCol, 0.0);

		// gesättigte Farbe bestimmen
			if (dY > dYRein) {
				dRSatt = 1.0;
				dBSatt = InvHelligkeitIter (
							dY, dCol, RotGelb, dGSatt);
			} else {
			// blau ist null
				dBSatt = 0.0;
				dRSatt = InvHelligkeit (dY, BEZUGSWERT_GRUEN, dCol, BEZUGSWERT_ROT);
				dGSatt = dRSatt*dCol;
			}
		}
		break;

	case 1:		// gelb-grün
		{
		double dCol = 2.0 - dHue;
		double dYRein = Helligkeit (dCol, 1.0, 0.0);

			if (dY > dYRein) {
				dGSatt = 1.0;
				dBSatt = InvHelligkeitIter (
							dY, dCol, GelbGruen, dRSatt);
			} else {
			// blau ist null
				dBSatt = 0.0;
				dGSatt = InvHelligkeit (dY, BEZUGSWERT_ROT, dCol, BEZUGSWERT_GRUEN);
				dRSatt = dGSatt*dCol;
			}
		}
		break;

	case 2:		// grün-cyan
		{
		double dCol = dHue - 2.0;
		double dYRein = Helligkeit (0.0, 1.0, dCol);

			if (dY > dYRein) {
				dGSatt = 1.0;
				dRSatt = InvHelligkeitIter (
							dY, dCol, GruenCyan, dBSatt);
			} else {
			// rot ist null
				dRSatt = 0.0;
				dGSatt = InvHelligkeit (dY, BEZUGSWERT_BLAU, dCol, BEZUGSWERT_GRUEN);
				dBSatt = dGSatt*dCol;
			}
		}
		break;

	case 3:		// cyan-blau
		{
		double dCol = 4.0 - dHue;
		double dYRein = Helligkeit(0.0, dCol, 1.0);

			if (dY > dYRein) {
				dBSatt = 1.0;
				dRSatt = InvHelligkeitIter (
							dY, dCol, CyanBlau, dGSatt);
			} else {
			// rot ist null
				dRSatt = 0.0;
				dGSatt = InvHelligkeit (dY, BEZUGSWERT_BLAU, dCol, BEZUGSWERT_GRUEN);
				dBSatt = dGSatt*dCol;
			}
		}
		break;

	case 4:		// blau-magenta
		{
		double dCol = dHue - 4.0;
		double dYRein = Helligkeit(dCol, 0.0, 1.0);

			if (dY > dYRein) {
				dBSatt = 1.0;
				dGSatt = InvHelligkeitIter (
							dY, dCol, BlauMagenta, dRSatt);
			} else {
			// gruen ist null
				dGSatt = 0.0;
				dBSatt = InvHelligkeit (dY, BEZUGSWERT_ROT, dCol, BEZUGSWERT_BLAU);
				dRSatt = dBSatt*dCol;
			}
		}
		break;

	case 5:		// magenta-rot
		{
		double dCol = 6.0 - dHue;
		double dYRein = Helligkeit(1.0, 0.0, dCol);

			if (dY > dYRein) {
				dRSatt = 1.0;
				dGSatt = InvHelligkeitIter (
							dY, dCol, MagentaRot, dBSatt);
			} else {
			// gruen ist null
				dGSatt = 0.0;
				dRSatt = InvHelligkeit (dY, BEZUGSWERT_BLAU, dCol, BEZUGSWERT_ROT);
				dBSatt = dRSatt*dCol;
			}
		}
		break;
	}

// jetzt über Helligkeiten die gesuchten RGB-Werte finden
double dGrau = pow (dY, 1.0/GAMMA);	// Farbanteile des zugehörigen Grauwertes

	rdRed = InvCorrectColor (dGrau, dRSatt, dSat, BEZUGSWERT_ROT);
	rdGreen = InvCorrectColor (dGrau, dGSatt, dSat, BEZUGSWERT_GRUEN);
	rdBlue = InvCorrectColor (dGrau, dBSatt, dSat, BEZUGSWERT_BLAU);
}

///////////////////////////////////////////////////////////////////////////////
