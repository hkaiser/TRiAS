// Rgb2Hsb.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main(int argc, char* argv[])
{
	CoInitialize(NULL);
	{
	long dRed, dGreen, dBlue;
	double dHue, dSat, dBright;
	char cbBuffer[256];
	IDoubleColorPtr Convert (CLSID_DoubleColor);

		while (NULL != fgets (cbBuffer, sizeof(cbBuffer), stdin)) {
			if (3 != sscanf (cbBuffer, "%d,%d,%d", &dRed, &dGreen, &dBlue)) {
				printf ("Fehlerhaftes Eingabeformat, bitte als R,G,B eingeben!\n");
				continue;
			}

			Convert -> InitRGB (dRed/255.0, dGreen/255.0, dBlue/255.0);

			Convert -> get_Hue (&dHue);
			Convert -> get_Saturation (&dSat);
			Convert -> get_Brightness (&dBright);

			printf ("RGB(%d, %d, %d) --> HSB(%d, %d, %d)\n", 
				dRed, dGreen, dBlue, 
				long(dHue +.5), long(dSat*100.0 +.5), long(dBright*100.0 +.5));
		}
	}
	CoUninitialize();
	return 0;
}
