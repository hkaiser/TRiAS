// Hsb2Rgb.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main(int argc, char* argv[])
{
	CoInitialize(NULL);
	{
	double dRed, dGreen, dBlue;
	long dHue, dSat, dBright;
	char cbBuffer[256];
	IDoubleColorPtr Convert (CLSID_DoubleColor);

		while (NULL != fgets (cbBuffer, sizeof(cbBuffer), stdin)) {
			if (3 != sscanf (cbBuffer, "%d,%d,%d", &dHue, &dSat, &dBright)) {
				printf ("Fehlerhaftes Eingabeformat, bitte als H,S,B eingeben!\n");
				continue;
			}

			Convert -> InitHSB (dHue, dSat/100.0, dBright/100.0);

			Convert -> get_Red (&dRed);
			Convert -> get_Green (&dGreen);
			Convert -> get_Blue (&dBlue);

			printf ("HSB(%d, %d, %d) --> RGB(%d, %d, %d)\n", 
				dHue, dSat, dBright, 
				long(dRed*255.0 +.5), long(dGreen*255.0 +.5), long(dBlue*255.0 +.5));
		}
	}
	CoUninitialize();
	return 0;
}
