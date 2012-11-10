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

#define HSB(s,b,h)          ((unsigned long)(((unsigned char)(s)|((unsigned short)(b)<<8))|(((unsigned long)(unsigned short)(h))<<16)))
#define GetSValue(hsb)	    ((unsigned char)(hsb))
#define GetVValue(hsb)      ((unsigned char)(((unsigned short)(hsb)) >> 8))
#define GetHValue(hsb)	    ((unsigned short)((hsb)>>16))

#endif // _RGB_HSB_HXX
