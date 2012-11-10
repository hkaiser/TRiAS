// Konvertierung RGB <-> HSB --------------------------------------------------
// File: RGB_HSB.CXX

#include "visobjp.hxx"

#include <Colors.h>
#include <Colors_i.c>

#include <math.h>
#include <rgb_hsb.hxx>

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
//
DefineSmartInterface(DoubleColor);		// WDoubleCOlor

///////////////////////////////////////////////////////////////////////////////
// Feststellen, welche Konvertierungsfunktionen genutzt werden sollen
#define RGBHSB_NOTINITIALIZED	0
#define RGBHSB_USEHSB			1
#define RGBHSB_USEHSL			2

static DWORD s_dwUseHSL = RGBHSB_NOTINITIALIZED;

bool UseNewConversion()
{
	if (RGBHSB_NOTINITIALIZED == s_dwUseHSL) {
	// erster Aufruf
	CRegKey regCfg;

		if (ERROR_SUCCESS == regCfg.Open (HKEY_CURRENT_USER, TEXT("Software")) &&
			ERROR_SUCCESS == regCfg.Open (regCfg, TEXT("uve")) &&
			ERROR_SUCCESS == regCfg.Open (regCfg, TEXT("TRiAS")) &&
			ERROR_SUCCESS == regCfg.Open (regCfg, TEXT("Config")))
		{
			regCfg.QueryValue (s_dwUseHSL, TEXT("HSBFlags"));
		}

	// Konsistenz gewährleisten
		if (RGBHSB_USEHSB != s_dwUseHSL && RGBHSB_USEHSL != s_dwUseHSL)
			s_dwUseHSL = RGBHSB_USEHSB;		// normal einstellen
	}
	return (RGBHSB_USEHSL == s_dwUseHSL) ? true : false;
}

///////////////////////////////////////////////////////////////////////////////
// Konvertierung HSB --> RGB 
Color HSBtoRGB (unsigned long hsb) 
{
	return HSBtoRGB (GetHValue (hsb), GetSValue (hsb), GetVValue (hsb));
}

Color HSBtoRGB (short iHue, short iSat, short iBright)
{
double dHue = (double)iHue;
double dSat = (double)iSat / 100.0;
double dBright = (double)iBright / 100.0;
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
	if (UseNewConversion()) {
		try {
		WDoubleColor Color (CLSID_DoubleColor);

			THROW_FAILED_HRESULT(Color -> InitHSB (dHue, dSat, dBright));
			THROW_FAILED_HRESULT(Color -> RetrieveRGB (&rdRed, &rdGreen, &rdBlue));
			return;

		} catch (_com_error &e) {
			e;
//			TX_ASSERT(SUCCEEDED(_COM_ERROR(e)));
		}
	} 

// ansonsten bzw. im Fehlerfall alte Konvertierung verwenden
	{
	double f, j, k, l;
	short i;

		if (dHue == 360.0) dHue = 0.0;
		dHue /= 60.0;

		i = (short)floor (dHue);

		f = dHue - i;			// gebrochener Teil

		j = dBright * (1 - dSat);
		k = dBright * (1 - (dSat * f));
		l = dBright * (1 - (dSat * (1 - f)));

		switch (i) {
		case 0:
			rdRed = dBright; rdGreen = l; rdBlue = j;
			break;

		case 1:
			rdRed = k; rdGreen = dBright; rdBlue = j;
			break;

		case 2:
			rdRed = j; rdGreen = dBright; rdBlue = l;
			break;

		case 3:
			rdRed = j; rdGreen = k; rdBlue = dBright;
			break;

		case 4:
			rdRed = l; rdGreen = j; rdBlue = dBright;
			break;

		case 5:
			rdRed = dBright; rdGreen = j; rdBlue = k;
			break;
		}
	}
}

// Konvertierung RGB --> HSB --------------------------------------------------
unsigned long RGBtoHSB (Color C) 
{
	return RGBtoHSB (C.Red(), C.Green(), C.Blue());
}

unsigned long RGBtoHSB (short iRed, short iGreen, short iBlue)
{
double dHue = 0.0;
double dSat = 0.0;
double dBright = 0.0;
double dRed = (double)iRed / 255.0;
double dGreen = (double)iGreen / 255.0;
double dBlue = (double)iBlue / 255.0;

	RGBtoHSBService (dRed, dGreen, dBlue, dHue, dSat, dBright);

	return HSB ((BYTE)((dSat*100.0)+0.5), (BYTE)((dBright*100.0)+0.5), (WORD)(dHue+0.5));
}

// HilfsFunktionen ------------------------------------------------------------
inline double fmax (double d1, double d2) 
{
	return d1 > d2 ? d1 : d2;
}

inline double fmin (double d1, double d2) 
{
	return d1 < d2 ? d1 : d2;
}

void RGBtoHSBService (double dRed, double dGreen, double dBlue,
		      double &rdHue, double &rdSat, double &rdBright)
{
	if (UseNewConversion()) {
		try {
		WDoubleColor Color (CLSID_DoubleColor);

			THROW_FAILED_HRESULT(Color -> InitRGB (dRed, dGreen, dBlue));
			THROW_FAILED_HRESULT(Color -> RetrieveHSB (&rdHue, &rdSat, &rdBright));
			return;

		} catch (_com_error &e) {
			e;
//			TX_ASSERT(SUCCEEDED(_COM_ERROR(e)));
		}
	} 

// ansonsten bzw. im Fehlerfall alte Konvertierung verwenden
	{
	double min, delta;

		rdBright = fmax (fmax (dRed, dGreen), dBlue);
		min = fmin (fmin (dRed, dGreen), dBlue);
		delta = rdBright - min;

		if (rdBright > 0.0) 
			rdSat = delta / rdBright;
		else
			rdSat = 0.0;

		if (rdSat == 0.0 || delta == 0.0) 
			rdHue = 0.0;
		else {
			if (dRed == rdBright) 
				rdHue = (dGreen - dBlue) / delta;
			else if (dGreen == rdBright) 
				rdHue = (dBlue - dRed) / delta + 2.0;
			else if (dBlue == rdBright)
				rdHue = (dRed - dGreen) / delta + 4.0;
			rdHue *= 60.0;
			if (rdHue < 0) rdHue += 360.0;
		}
	}
}
