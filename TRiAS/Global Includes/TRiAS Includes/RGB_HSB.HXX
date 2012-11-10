// Konvertierung RGB <-> HSB --------------------------------------------------
// File: RGB_HSB.HXX

#if !defined(_RGB_HSB_HXX)
#define _RGB_HSB_HXX

Color HSBtoRGB (unsigned long hsb);
Color HSBtoRGB (short iHue, short iSat, short iBright);
void HSBtoRGBService (double dHue, double dSat, double dBright,
		      double &rdRed, double &rdGreen, double &rdBlue);

unsigned long RGBtoHSB (Color rgbC);
unsigned long RGBtoHSB (short iRed, short iGreen, short iBlue);
void RGBtoHSBService (double dRed, double dGreen, double dBlue,
		      double &rdHue, double &rdSat, double &rdBright);

#if defined(_USE_HSB_MACROS)
#define HSB(s,b,h)          ((unsigned long)(((unsigned char)(s)|((unsigned short)(b)<<8))|(((unsigned long)(unsigned short)(h))<<16)))
#define GetSValue(hsb)	    ((unsigned char)(hsb))
#define GetVValue(hsb)      ((unsigned char)(((unsigned short)(hsb)) >> 8))
#define GetHValue(hsb)	    ((unsigned short)((hsb)>>16))
#else

inline unsigned long HSB (unsigned char s, unsigned char b, unsigned short h)
{
	while (h < 0) 
		h += 360;
	return s | (b << 8) | ((h % 360) << 16);
}

inline unsigned char GetSValue (unsigned long hsb)
{
	return LOBYTE(LOWORD(hsb));
}

inline unsigned char GetVValue (unsigned long hsb)
{
	return HIBYTE(LOWORD(hsb));
}

inline unsigned short GetHValue (unsigned long hsb)
{
	return HIWORD(hsb);
}

#endif // _USE_HSB_MACROS

#endif // _RGB_HSB_HXX
