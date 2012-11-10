// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 12.03.2002 19:49:06 
//
// @doc
// @module pgr.h | Declaration of the <c Cpgr> class

#if !defined(_PGR_H__04F48E20_151B_4C70_AD90_C3C7B042BA0A__INCLUDED_)
#define _PGR_H__04F48E20_151B_4C70_AD90_C3C7B042BA0A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <pshpack1.h>

///////////////////////////////////////////////////////////////////////////////
// PGR Header Struktur  (neu)
// Der folgende Header kommt zum Einsatz, wenn 
// - der erste long Wert der Datei 0x0148 enthält
// - 6 Unterverzeichnisse vorhanden sind (raster1...raster6)
typedef struct tagPGRHEADER {
	long lSizeX;		// Gesamtgröße X
	long lSizeY;		// Gesamtgröße Y
	char Unknown1[1];
	double dXMin;		// Gesamtcontainer (BesselGK3°)
	double dYMin;
	double dXMax;
	double dYMax;
	char Unknown2[20];
} PGRHEADER;
#define MAGIC_PGR 0x0148

///////////////////////////////////////////////////////////////////////////////
// Eine referenzierte Teilkarte (neu)
typedef struct tagCMPKACHEL {
	long dwMagic;		// 0x014d (333) ?
	char Unknown1[9];
	double dXMin;		// Container der Kachel (BesselGK3°)
	double dYMin;
	double dXMax;
	double dYMax;
	long lOffset;		// Offset dieser Kachel 
	long lByteCount;	// Größe der Kachel (Bytes)
	long lSizeX;		// Größe der Kachel X (Pixel)
	long lSizeY;		// Größe der Kachel Y (Pixel)
	long lBitsPerPixel;	// Anzahl der Bits je Pixel
} CMPKACHEL;

///////////////////////////////////////////////////////////////////////////////
// Eine andere Variante des Headers einer PGR-Datei
// Der folgende Header kommt zum Einsatz, wenn
// - der erste long Wert der Datei 0x0000 enthält
// - 5 Unterverzeichnisse vorhanden sind (raster1...raster5)
typedef struct tagPGRHEADEROLD {
	short Unknown1[2];
	short iMagic1;		// immer 0x148 (328) ?
	short iCountX;		// Anzahl der Kacheln X
	short iCountY;		// Anzahl der Kacheln Y
	double dXMin;		// Gesamtcontainer (BesselGK3°)
	double dYMin;
	double dXMax;
	double dYMax;
	char Unknown2[13];
} PGRHEADEROLD;
#define MAGIC_OLD_PGR 0

///////////////////////////////////////////////////////////////////////////////
// Eine referenzierte Teilkarte (neu)
typedef struct tagCMPKACHELOLD {
	char Unknown1[6];
	short Unknown2;
	short iMagic;		// immer 0x014d (333) ?
	long Unknown3;
	double dXMin;		// Container der Kachel (BesselGK3°)
	double dYMin;
	double dXMax;
	double dYMax;
	long lOffset;		// Offset dieser Kachel 
	long lByteCount;	// Größe der Kachel (Bytes)
	short lSizeX;		// Größe der Kachel X (Pixel)
	short lSizeY;		// Größe der Kachel Y (Pixel)
	unsigned char cBitsPerPixel;	// Anzahl der Bits je Pixel
} CMPKACHELOLD;

#include <poppack.h>

#endif // !defined(_PGR_H__04F48E20_151B_4C70_AD90_C3C7B042BA0A__INCLUDED_)
