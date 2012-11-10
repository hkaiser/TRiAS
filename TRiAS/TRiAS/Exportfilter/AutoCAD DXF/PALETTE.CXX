// File: Palette.c
// Wandelt WINDOWS-Farbe in AutCAD-Farbe
// Stand vom 13. April 1994

#include "stdafx.h"
#include "AcadDXFImpl.h"

//XX	extern "C" {

#define Weiss 7

UINT Farbe = Weiss;
short Ind = 0;
HPALETTE hPal = 0;
short Count = 8;

//  AutoCAD-Farben
PALETTEENTRY Palette [] = {
    0,0,0,	PC_RESERVED,		// black --> keine AutoCAD-Farbe
    255,0,0,	PC_RESERVED,	// rot
    255,255,0,	PC_RESERVED,	// gelb
    0,255,0,	PC_RESERVED,	// grün
    0,255,255,	PC_RESERVED,	// cyan
    0,0,255,	PC_RESERVED,	// blau
    255,0,255,	PC_RESERVED,	// magenta
    255,255,255,PC_RESERVED,	// weiß
};

struct NEWPAL {
    LOGPALETTE LogPal;
    PALETTEENTRY Pal [(sizeof (Palette) / sizeof (Palette [0])) - 1];
} NewPal;

// WINDOWS-Farbe in AutoCAD-Farbe umwandeln
UINT GetAutoCADFarbe (COLORREF clrref) {
//  init.
    if (!hPal) {
		Ind = 0;
		NewPal.LogPal.palPalEntry [Ind] = Palette [Ind];	// 1. Farbe kopiern
    	//	Palette laden
		for (Ind++; Ind < Count; Ind++)
	    	NewPal.Pal [Ind-1] = Palette [Ind];

		NewPal.LogPal.palVersion = 0x300;
		NewPal.LogPal.palNumEntries = Count;

		hPal = CreatePalette ((LOGPALETTE*) &NewPal);
    	}

    if (hPal == NULL) 
		return Weiss;	// mit weiß zurück
    else {
		Farbe = GetNearestPaletteIndex (hPal, clrref);
		if (Farbe == 0) 	// da schwarz nicht vorhanden
	    	Farbe = Weiss;	// weiß auswählen
		if ( Farbe == CLR_INVALID )
	    	Farbe = Weiss;	// weiß auswählen

    }

    return Farbe;		// Index beginnt bei 0
}

void DeletePalette (void) {
    if (hPal) {
		DeleteObject (hPal);
		hPal = 0;
	}

}

//XX	} // extern "C" 
