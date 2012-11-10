// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 12.03.2002 19:49:06 
//
// @doc
// @module pgr.h | Declaration of the *.pgr structures

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
// - i.a. 6 Unterverzeichnisse vorhanden sind (raster1...raster6)
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

///////////////////////////////////////////////////////////////////////////////
// Eine referenzierte Teilkarte (neu)
typedef struct tagCMPKACHEL {
	long iMagic;		// 0x014d (333) ?
	char Unknown1[6];
	char Unknown2[3];
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
// - i.a. 5 Unterverzeichnisse vorhanden sind (raster1...raster5)
typedef struct tagPGRHEADEROLD {
	short Unknown1[2];
	unsigned short iMagic1;		// immer 0x148 (328) ?
	short iCountX;		// Anzahl der Kacheln X
	short iCountY;		// Anzahl der Kacheln Y
	double dXMin;		// Gesamtcontainer (BesselGK3°)
	double dYMin;
	double dXMax;
	double dYMax;
	char Unknown2[13];
} PGRHEADEROLD;

///////////////////////////////////////////////////////////////////////////////
// Eine referenzierte Teilkarte (neu)
typedef struct tagCMPKACHELOLD {
	char Unknown1[8];
	unsigned short iMagic;		// immer 0x014d (333) ?
	long Unknown2;
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

///////////////////////////////////////////////////////////////////////////////
// Der folgende Header kommt zum Einsatz, wenn
// - der erste long Wert der Datei 0x0000 enthält
// - der nächste short Wert auch 0x0000 enthält
typedef struct tagPGRHEADER2 {
	short Unknown1[1];	// 0x0000 ?
	unsigned short iMagic;		// immer 0xF0BF (49136)
	char iMagic1;		// immer 0x01
	short Unused1[2];
	char iMagic2;		// immer 0x48
	short Unused2[2];
	double dXMin;		// Container der Kachel (BesselGK3°)
	double dYMin;
	short Unused3;
	double dXMax;		// Container der Kachel (BesselGK3°)
	double dYMax;
	char Unused4[266];
} PGRHEADER2;

///////////////////////////////////////////////////////////////////////////////
// Eine referenzierte Teilkarte
typedef struct tagCMPKACHEL2 {
	unsigned short iMagic;		// immer 0xF0BF (49136)
	char iMagic1;		// immer 0x01
	short Unused1[2];	// 
	char iMagic2;		// immer 0x4d
	long lByteCount;	// Größe der Kachel in Bytes
	double dXMin;		// Container der Kachel (BesselGK3°)
	double dYMin;
	short lSizeX;		// Größe der Kachel X (Pixel)
	double dXMax;		// Container der Kachel (BesselGK3°)
	double dYMax;
	short lSizeY;		// Größe der Kachel Y (Pixel)
	char Unused3[264];
} CMPKACHEL2;

///////////////////////////////////////////////////////////////////////////////
// Magic numbers in pgr's
#define MAGIC_PGR			0x0148
#define MAGIC_PGR_KACHEL	0x014d
#define MAGIC_OLD_PGR		0

#define MAGIC_PGR2_BYTE1	0x01
#define MAGIC_PGR2_BYTE2	0x48
#define MAGIC_PGR2			0xbff0

///////////////////////////////////////////////////////////////////////////////
// Kachelgröße (ist immer gleich ?)
#define TILE_SIZE_X		300
#define TILE_SIZE_Y		200

#include <poppack.h>

#endif // !defined(_PGR_H__04F48E20_151B_4C70_AD90_C3C7B042BA0A__INCLUDED_)
