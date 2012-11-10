// Konvertierung RGB <-> HSB --------------------------------------------------
// File: RGB_HSB2.H

#if !defined(_RGB_HSB2_H)
#define _RGB_HSB2_H

#include <math.h>

typedef unsigned char ColorVal;
typedef unsigned long COLORREF;

class Color {
private:
	ColorVal		R;
	ColorVal		G;
	ColorVal		B;
	ColorVal		_reserved;

public:
	Color (void)
		{ R = 0; G = 0; B = 0; _reserved = 0; }
	Color (ColorVal r, ColorVal g, ColorVal b)
		{ R = r; G = g; B = b; _reserved = 0; }

	ColorVal &	Red (void) { return R; }
	ColorVal &	Green (void) { return G; }
	ColorVal &	Blue (void) { return B; }
	ColorVal &	Reserved (void) { return _reserved; }

	operator COLORREF & (void) { return *reinterpret_cast<COLORREF *>(this); }
	operator const COLORREF & (void) const { return *reinterpret_cast<const COLORREF *>(this); }
};

///////////////////////////////////////////////////////////////////////////////
// Funktionsprototypen
Color HSBtoRGB (unsigned long hsb);
Color HSBtoRGB (int iHue, int iSat, int iBright);
void HSBtoRGBService (double dHue, double dSat, double dBright,
		      double &rdRed, double &rdGreen, double &rdBlue);

unsigned long RGBtoHSB (Color rgbC);
unsigned long RGBtoHSB (int iRed, int iGreen, int iBlue);
void RGBtoHSBService (double dRed, double dGreen, double dBlue,
		      double &rdHue, double &rdSat, double &rdBright);

///////////////////////////////////////////////////////////////////////////////
// Zugriffsmakros
#define HSB(s,b,h)          ((unsigned long)(((unsigned char)(s)|(((unsigned short)(b))<<8))|(((unsigned long)(unsigned char)(h))<<24)))
#define GetSValue(hsb)	    ((unsigned char)(hsb))
#define GetVValue(hsb)      ((unsigned short)(((unsigned long)(hsb))>>8))
#define GetHValue(hsb)	    ((unsigned short)(((unsigned long)(hsb))>>24))

///////////////////////////////////////////////////////////////////////////////
// Konstanten
const double BEZUGSWERT_ROT = 0.299;
const double BEZUGSWERT_GRUEN = 0.587;
const double BEZUGSWERT_BLAU = 0.114;
const double GAMMA = 2.5;

const double ITER_STOP = 0.0000001;

///////////////////////////////////////////////////////////////////////////////
// Standardberechnungsfunktionen

///////////////////////////////////////////////////////////////////////////////
// Helligkeit einer Farbe 
inline double HelligkeitRot (double dR)
{
	return BEZUGSWERT_ROT*pow(dR, GAMMA);
}

inline double HelligkeitGruen (double dG)
{
	return BEZUGSWERT_GRUEN*pow(dG, GAMMA);
}

inline double HelligkeitBlau (double dB)
{
	return BEZUGSWERT_BLAU*pow(dB, GAMMA);
}

inline double Helligkeit (double dR, double dG, double dB)
{
	return HelligkeitRot(dR) + HelligkeitGruen(dG) + HelligkeitBlau(dB);
}

///////////////////////////////////////////////////////////////////////////////
// Logarithmische Wahrnehmung des Auges
inline double Wahrnehmung (double dY)
{
double dRes = 116.0*pow (dY, 1.0/3.0) - 16.0;

	return __max(0.0, dRes) / 100.0;
}

///////////////////////////////////////////////////////////////////////////////
// Cube
#define CUBE(x)	((x)*(x)*(x))
inline double cube (double dX) { return CUBE(dX); }

///////////////////////////////////////////////////////////////////////////////
// Luminanz aus Wahrnehmung berechnen
inline double InvWahrnehmung (double dL)
{
	return (dL > CUBE(16.0/116.0)/100.0) ? cube(((dL*100.0)+16.0)/116.0) : 0.0;
}

#endif // _RGB_HSB2_H
