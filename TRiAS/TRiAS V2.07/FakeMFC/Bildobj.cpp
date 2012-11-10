// BildObj.cpp: BitmapHandling 

#include "StdAfx.h"
#include <bildobj.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Konstruktor -- Einlesen einer DIB, PaletteSetup ----------------------------
CBildObjekt :: CBildObjekt (void) 
{
// Member initialisieren
	m_hDIB = NULL;
	m_hDDB = NULL;
	m_hPal = NULL;
}


HBITMAP CBildObjekt::ReadFile (const char *pcFileName)
{
	return InitDIB (pcFileName) ? m_hDDB : NULL;	// Bild einlesen
}

// Destruktor 
CBildObjekt :: ~CBildObjekt (void) 
{
	FreeDIB ();     // alles freigeben
}


// Bitmaps einlesen und Paletten initialisieren
bool CBildObjekt :: InitDIB (const char *pcFullName) 
{
int fh;					/* Dateihandle (evtl. komprimiertes File) */
OFSTRUCT of;            /* Dateistruktur */
HPALETTE hPalCurrent;   /* PaletteStruct */
HBITMAP hDIBCurrent;    /* DIB */
HBITMAP hBMCurrent;     /* DDB */

// alte DIB freigeben 
	FreeDIB ();

// Datei eröffnen, Speicherplatz anlegen
	fh = OpenFile (pcFullName, (OFSTRUCT *)&of, OF_READ);
	if (fh < 0) return false;

	hDIBCurrent = ReadDIBitmapInfo (fh);    // Farbtabelle lesen

// Gültigkeit der DIB-Datei prüfen 
	if (hDIBCurrent == NULL) {
		_lclose (fh);
		return false;
	}
	m_hDIB = hDIBCurrent;					// im Objekt merken

// PaletteSetup 
	hPalCurrent = CreateDIBPalette ();		// Palette bilden
	if (hPalCurrent == NULL) {
		_lclose (fh);
		return false;
	}
	m_hPal = hPalCurrent;

// DIB einlesen 
	hDIBCurrent = ReadDIB (fh);
	if (!hDIBCurrent) {
		_lclose (fh);
		return false;
	}
	m_hDIB = hDIBCurrent;
	_lclose (fh);

// DDB bilden
	hBMCurrent = DIBToBitmap();
	if (!hBMCurrent)
		return false;

	m_hDDB = hBMCurrent;

return true;
}

// Einlesen der DIB in den Speicher 
HBITMAP CBildObjekt :: ReadDIB (unsigned fh) 
{
ULONG dwBits;   // Größe der DIB
ULONG dwLen;
HBITMAP h;
BITMAPINFOHEADER bi;
BITMAPINFOHEADER *lpbi;

// Benoetigten Speicherplatz berechnen 
	DIBInfo (&bi);
	dwBits = bi.biSizeImage;
	dwLen = bi.biSize + (ULONG)(DIBNumColors(&bi)*sizeof(RGBQUAD));
					// PaletteSize (&bi);

// Vergrößern des Speicherplatzes für gesamte Bitmap
	h = (HBITMAP)GlobalReAlloc (m_hDIB, dwLen + dwBits, GHND);
	if (!h) {
	/* gesamten Speicher freigeben */
		GlobalFree (m_hDIB);
		m_hDIB = NULL;
		return NULL;
	} 

// DIB-Bits einlesen
	lpbi = (BITMAPINFOHEADER *)GlobalLock (h);
	if ((DWORD)_hread (fh, (char *)lpbi + dwLen, dwBits) != dwBits) {
	// LeseFehler
		GlobalUnlock (h);
		GlobalFree (h);
		GlobalFree (m_hDIB);  // bisher angeforderten Speicher freigeben
		m_hDIB = NULL;
		return NULL;
	}
	GlobalUnlock (h);

return h;
}


/* Bestimmen der DIB - Info aus einem CF_DIB Speicherblock */
bool CBildObjekt :: DIBInfo (BITMAPINFOHEADER *lpBI) 
{
	if (m_hDIB) {
	// BitmapInfoHeader kopieren 
		*lpBI = *(BITMAPINFOHEADER *)GlobalLock (m_hDIB);

	// DefaultWerte setzen
		if (lpBI->biSizeImage == 0L)
			lpBI->biSizeImage = lpBI->biHeight * 
				WIDTHBYTES ((ULONG)lpBI->biWidth*lpBI->biBitCount);
		if (lpBI->biClrUsed == 0L)
			lpBI->biClrUsed = DIBNumColors (lpBI);
		GlobalUnlock (m_hDIB);
		return true;
	}

return false;
}


// Liest Dateiheader und Farbtabelle im DIBformat ein 
HBITMAP CBildObjekt :: ReadDIBitmapInfo (unsigned int fh) 
{
BITMAPFILEHEADER bf;
BITMAPINFOHEADER bi;
unsigned int iNumColors = 0;
HBITMAP hBI = NULL;		// Farbtabelle - HANDLE
BITMAPINFOHEADER *lpBI = NULL;
RGBQUAD *lpRGB;			// Farbtabelle 
ULONG dwOffset;         // Dateiposition

	if (fh == -1) return NULL;      // ungültiges Dateihandle

// Dateiheader (BITMAPFILEHEADER) lesen
	dwOffset = _llseek (fh, 0L, SEEK_CUR);
	if (_hread (fh, &bf, sizeof(bf)) != sizeof(bf))
		return NULL;

// Not a DIB ? 
	if (!ISDIB (bf.bfType))
		return NULL;

// BitMapHeader (BITMAPINFOHEADER) lesen
	if (_hread (fh, &bi, sizeof(bi)) != sizeof(bi))
		return NULL;	// not a DIB

	iNumColors = DIBNumColors ((BITMAPINFOHEADER *)&bi);
	if (bi.biSize != sizeof(BITMAPINFOHEADER))	
		return NULL;	// falsches Datenformat

// Defaultgrößen setzen 
	if (bi.biSizeImage == 0)
		bi.biSizeImage = WIDTHBYTES ((ULONG)bi.biWidth * bi.biBitCount)
						*bi.biHeight;
	if (bi.biClrUsed == 0)
		bi.biClrUsed = iNumColors;

// Speicher für BitMap und Farbtabelle anfordern 
	hBI = (HBITMAP)GlobalAlloc (GHND, (ULONG)bi.biSize + iNumColors * sizeof(RGBQUAD));
	if (!hBI) return NULL;

	lpBI = (BITMAPINFOHEADER *)GlobalLock (hBI);
	*lpBI = bi;
	lpRGB = (RGBQUAD *)((char *)lpBI + bi.biSize);

// Farbtabelle einlesen 
	if (iNumColors)
		_hread (fh, lpRGB, iNumColors * sizeof(RGBQUAD));

// an Anfang der BitMap positionieren 
	if (bf.bfOffBits != 0)
		_llseek (fh, dwOffset + bf.bfOffBits, SEEK_SET);

	m_dim = CSize(bi.biWidth, bi.biHeight);

// Speicher wieder freigeben 
	GlobalUnlock (hBI);

return hBI;
}

// Vereinbaren der logischen Palette
HPALETTE CBildObjekt :: CreateDIBPalette (void) 
{
HPALETTE hPal = NULL;

	if (!m_hDIB) return NULL;
	hPal = CreateBIPalette ((BITMAPINFOHEADER *)GlobalLock (m_hDIB));
	GlobalUnlock (m_hDIB);

return hPal;
}

// Bilden der Palette für BITMAPINFOSTRUCT
HPALETTE CBildObjekt :: CreateBIPalette (BITMAPINFOHEADER *lpBI) 
{
RGBQUAD *lpRGB;
unsigned int iNumColors;
LOGPALETTE *pPal;
HPALETTE hPal = NULL;
HGLOBAL h;

// Anfangstests 
	if (!lpBI) return NULL;
	if (lpBI->biSize != sizeof(BITMAPINFOHEADER)) return NULL;

// Logische Palette füllen und vereinbaren 
	lpRGB = (RGBQUAD *)((char *)lpBI + (unsigned int)lpBI->biSize);
	iNumColors = DIBNumColors (lpBI);
	h = (HGLOBAL)GlobalAlloc (GHND, sizeof(LOGPALETTE) +
					iNumColors * sizeof(PALETTEENTRY));
	if (!h) return NULL;

	pPal = (LOGPALETTE *)GlobalLock(h);
	if (!pPal) return NULL;

// Palette füllen
	pPal->palNumEntries = iNumColors;
	pPal->palVersion = 0x300;

	for (unsigned short i = 0; i < iNumColors; ++i) {
		pPal->palPalEntry[i].peRed = lpRGB[i].rgbRed;
		pPal->palPalEntry[i].peGreen = lpRGB[i].rgbGreen;
		pPal->palPalEntry[i].peBlue = lpRGB[i].rgbBlue;
		pPal->palPalEntry[i].peFlags = (BYTE)0;
	}
	hPal = CreatePalette (pPal);
	GlobalUnlock (h);
	GlobalFree (h);

return hPal;
}


// Bestimmen der Anzahl der vertretenen Farben in der BitMap 
unsigned int CBildObjekt :: DIBNumColors (BITMAPINFOHEADER *lpbi) 
{
	if (lpbi->biClrUsed != 0)
		return ((unsigned int)lpbi->biClrUsed);

	switch (lpbi->biBitCount) {
	case 1: return 2;
	case 4: return 16;
	case 8: return 256;
	default: return 0;		// 24-Bit DIB hat keine Farbtabelle 
	}
}


// Datenstrukturen freigeben, Objekte löschen 
void CBildObjekt :: FreeDIB (void) 
{
	if (m_hPal) DeleteObject (m_hPal);
	if (m_hDDB) DeleteObject (m_hDDB);
	if (m_hDIB) GlobalFree (m_hDIB);
	m_hPal = NULL;
	m_hDDB = NULL;
	m_hDIB = NULL;
}


// Umformen einer DIB in eine DDB 
HBITMAP CBildObjekt :: DIBToBitmap (void) 
{
BITMAPINFOHEADER *lpBI;
HPALETTE hPalT;
HDC hDC;
HBITMAP hBM;

	if (!m_hDIB) return NULL;

// Bitmapheader 
	lpBI = (BITMAPINFOHEADER *)GlobalLock (m_hDIB);
	if (!lpBI) return NULL;

// Palette realisieren 
	hDC = :: GetDC (NULL);
	if (m_hPal) {
		hPalT = SelectPalette (hDC, m_hPal, false);
		RealizePalette (hDC);
	}

// device dependent bitmap (DDB) erzeugen 
	hBM = CreateDIBitmap (hDC, lpBI, (long)CBM_INIT,
			(char *)lpBI + lpBI->biSize + 
			DIBNumColors(lpBI)*sizeof(RGBQUAD), //  PaletteSize (lpBI),
			(BITMAPINFO *)lpBI, DIB_RGB_COLORS);

// alte Palette wiedereinstellen
	if (m_hPal)
		SelectPalette (hDC, hPalT, false);

	ReleaseDC (NULL, hDC);
	GlobalUnlock (m_hDIB);

return hBM;
}


