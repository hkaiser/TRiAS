//////////////////////////////////////////////////////////////
// Zugriff auf Farben

#ifndef	__PRIVATE_PICT_DEFINITIONS__
#define	__PRIVATE_PICT_DEFINITIONS__

#pragma pack(1)

typedef union tagCOLOR {
	DWORD	d;
	BYTE	a[4];
	struct { BYTE b1; BYTE b2; BYTE b3; BYTE b4; } b;
	struct { BYTE m1; WORD w; BYTE m2; } m;
	struct { WORD w1; WORD w2; } w;
} COLOR;

//////////////////////////////////////////////////////////////
// diverse Lookup - Tabellen

extern unsigned char BitRevTable[256];
extern unsigned char NoBitRevTable[256];

//////////////////////////////////////////////////////////////
// TAG - Management

#pragma warning( disable : 4786 )

typedef map< PICT_PROPERTY, TAG, less<DWORD> > CTagMap;
extern CTagMap		tagMasterMap;
#define TAGMAP	(*(CTagMap*)m_pTagMap)

#endif // __PRIVATE_PICT_DEFINITIONS__

//////////////////////////////////////////////////////////////
// Windows-Bitmap

#ifndef	__WINDOWS_BITMAP_DEFINED__
#define	__WINDOWS_BITMAP_DEFINED__

#include	<windows.h>			// sind da drin
#define	BF_BMP	0x4d42

#endif // __WINDOWS_BITMAP_DEFINED__

//////////////////////////////////////////////////////////////
// TIFF-Dateien

#ifndef	__TIFFTAGS_DEFINED__
#define	__TIFFTAGS_DEFINED__

// Konstanen für LZW-Komprimierung
#define CLEAR						256		// Clear-Code
#define EOI							257		// End Of Information-Code
#define NO_LZW_CODE					4096	// Das ist kein gültiger GIF-LZW-Code
#define PREFIXTABLE					12		// Anzahl der Codeeinträge für ein Präfix
											// in der Präfixtabelle

#define BYTEORDER_II	(WORD) 0x4949
#define BYTEORDER_MM	(WORD) 0x4D4D

////////////////////////////////////////////////////////////////////

#define	TIFFhowmany(x, y) ((((DWORD)(x))+(((DWORD)(y))-1))/((DWORD)(y)))
#define	TIFFroundup(x, y) (TIFFhowmany(x,y)*((DWORD)(y)))
#define	isAligned(p,t)	((((DWORD)(p)) & (sizeof (t)-1)) == 0)

#define _countof(array) (sizeof(array)/sizeof(array[0]))

extern TCHAR szUnknown[];

#endif // __TIFFTAGS_DEFINED__
