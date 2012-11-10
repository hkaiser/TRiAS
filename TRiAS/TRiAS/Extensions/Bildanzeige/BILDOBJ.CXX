// BitmapHandling fuer Bilder
// File: BILDOBJ.CXX

#include "bilderp.hxx"

#include <lzexpand.h>

#if defined(WIN32)
#define __huge
#endif

extern "C" unsigned long PASCAL lread (int fh, void __huge *pv, unsigned long ul);

// Konstruktor -- Einlesen einer DIB, PaletteSetup ----------------------------
BildObjekt :: BildObjekt (pWindow pW, char *pFileName, Point Pt) 
	    : DrawObject (Pt)
{
// Member initialisieren
	_Org = Pt;              // Lage des Bezugspunktes
	{
		_FileName = new char [strlen(pFileName)+1];
		if (_FileName == NULL) {
			_OKFlag = FALSE;
			return;
		}
		strcpy (_FileName, pFileName);
	}
	_hDIB = NULL;
	_hDDB = NULL;
	_hPal = NULL;

// WindowHandle holen
	pWnd = pW;

// Bild einlesen
	_OKFlag = InitDIB (_FileName);
}

// Destruktor 
BildObjekt :: ~BildObjekt (void) 
{
	DELETE_OBJ (_FileName);
	FreeDIB ();     // alles freigeben
}


// Bitmaps einlesen und Paletten initialisieren
Bool BildObjekt :: InitDIB (char *FullName) 
{
int cfh;		/* Dateihandle (evtl. komprimiertes File) */
// int fh;			/* DateiHandle des unkomprimierten Files */
OFSTRUCT of;            /* Dateistruktur */
HPALETTE hPalCurrent;     /* PaletteStruct */
HBITMAP hDIBCurrent;     /* DIB */
HBITMAP hBMCurrent;      /* DDB */

// alte DIB freigeben 
	FreeDIB ();

// Datei eröffnen, Speicherplatz anlegen
	cfh = LZOpenFile (FullName, (OFSTRUCT *)&of, OF_READ);
	if (cfh < 0) return FALSE;

// entkomprimieren vorbereiten
//	fh = LZInit (cfh);		/* interne Strukturen initialisieren */
//	if (fh < 0) 
//		return FALSE;
	hDIBCurrent = ReadDIBitmapInfo (cfh);    /* Farbtabelle lesen */

// Gültigkeit der DIB-Datei prüfen 
	if (hDIBCurrent == NULL) {
		FreeDIB ();
		LZClose (cfh);
		return FALSE;
	}
	_hDIB = hDIBCurrent;                    // im Objekt merken

// PaletteSetup 
	hPalCurrent = CreateDIBPalette ();      /* Palette bilden */
	if (hPalCurrent == NULL) {
		FreeDIB ();
		LZClose (cfh);
		return FALSE;
	}
	_hPal = hPalCurrent;

// DIB einlesen 
	hDIBCurrent = ReadDIB (cfh);
	if (!hDIBCurrent) {
		FreeDIB ();
		LZClose (cfh);
		return FALSE;
	}
	_hDIB = hDIBCurrent;
	LZClose (cfh);

// DDB bilden
	hBMCurrent = DIBToBitmap ();
	if (!hBMCurrent) {
		FreeDIB ();
		return FALSE;
	}
	_hDDB = hBMCurrent;

return TRUE;
}


/* Einlesen der DIB in den Speicher */
HBITMAP BildObjekt :: ReadDIB (unsigned fh) 
{
unsigned long dwBits;   /* Größe der DIB */
unsigned long dwLen;
HBITMAP h;
BITMAPINFOHEADER bi;
BITMAPINFOHEADER *lpbi;

/* Benoetigten Speicherplatz berechnen */
	DIBInfo (&bi);
	dwBits = bi.biSizeImage;
	dwLen = bi.biSize + (unsigned long)(DIBNumColors(&bi)*sizeof(RGBQUAD));
					// PaletteSize (&bi);

/* Vergroessern des Speicherplatzes fuer gesamte Bitmap */
	h = (HBITMAP)GlobalReAlloc (_hDIB, dwLen + dwBits, GHND);
	if (!h) {
	/* gesamten Speicher freigeben */
		GlobalFree (_hDIB);
		_hDIB = NULL;
		return NULL;
	} 

/* DIB-Bits einlesen */
	lpbi = (BITMAPINFOHEADER *)GlobalLock (h);
	if (lread (fh, (char *)lpbi + dwLen, dwBits) != dwBits) {
	// LeseFehler
		GlobalUnlock (h);
		GlobalFree (h);
		GlobalFree (_hDIB);  // bisher angeforderten Speicher freigeben
		_hDIB = NULL;
		return NULL;
	}
	GlobalUnlock (h);

/* Größe der Bitmap merken */
	_Size = Dimension ((int)bi.biWidth, (int)bi.biHeight);

return h;
}


/* Bestimmen der DIB - Info aus einem CF_DIB Speicherblock */
Bool BildObjekt :: DIBInfo (BITMAPINFOHEADER *lpBI) 
{
	if (_hDIB) {
	/* BitmapInfoHeader kopieren */
		*lpBI = *(BITMAPINFOHEADER *)GlobalLock (_hDIB);

	/* DefaultWerte setzen */
		if (lpBI->biSizeImage == 0L)
			lpBI->biSizeImage = lpBI->biHeight * 
				WIDTHBYTES ((unsigned long)lpBI->biWidth*lpBI->biBitCount);
		if (lpBI->biClrUsed == 0L)
			lpBI->biClrUsed = DIBNumColors (lpBI);
		GlobalUnlock (_hDIB);
		return TRUE;
	}

return FALSE;
}


/* Liest Dateiheader und Farbtabelle im DIBformat ein */
HBITMAP BildObjekt :: ReadDIBitmapInfo (unsigned int fh) 
{
BITMAPFILEHEADER bf;
BITMAPINFOHEADER bi;
unsigned int iNumColors = 0;
HBITMAP hBI = NULL;              /* Farbtabelle - HANDLE */
BITMAPINFOHEADER *lpBI = NULL;
RGBQUAD *lpRGB;                 /* Farbtabelle */
unsigned long dwOffset;         /* Dateiposition */

	if (fh == -1) return NULL;      /* ungueltige Dateihandle */

/* Dateiheader (BITMAPFILEHEADER) lesen */
	dwOffset = LZSeek (fh, 0L, SEEK_CUR);
	if (LZRead (fh, (char *)&bf, sizeof(bf)) != sizeof(bf))
		return NULL;

/* Not a DIB ? */
	if (!ISDIB (bf.bfType))
		return NULL;

/* BitMapHeader (BITMAPINFOHEADER) lesen */
	if (LZRead (fh, (char *)&bi, sizeof(bi)) != sizeof(bi))
	/* LeseFehler */
		return NULL;
	iNumColors = DIBNumColors ((BITMAPINFOHEADER *)&bi);
	if (bi.biSize != sizeof(BITMAPINFOHEADER))
	/* falsches Datenformat */
		return NULL;

/* Defaultgrößen setzen */
	if (bi.biSizeImage == 0)
		bi.biSizeImage = WIDTHBYTES ((unsigned long)bi.biWidth * bi.biBitCount)
						*bi.biHeight;
	if (bi.biClrUsed == 0)
		bi.biClrUsed = iNumColors;

/* Speicher fuer BitMap und Farbtabelle anfordern */
	hBI = (HBITMAP)GlobalAlloc (GHND, (unsigned long)bi.biSize + iNumColors * sizeof(RGBQUAD));
	if (!hBI)
		return NULL;
	lpBI = (BITMAPINFOHEADER *)GlobalLock (hBI);
	*lpBI = bi;
	lpRGB = (RGBQUAD *)((char *)lpBI + bi.biSize);

/* Farbtabelle einlesen */
	if (iNumColors)
		LZRead (fh, (char *)lpRGB, iNumColors * sizeof(RGBQUAD));

/* an Anfang der BitMap positionieren */
	if (bf.bfOffBits != 0)
		LZSeek (fh, dwOffset + bf.bfOffBits, SEEK_SET);

/* Speicher wieder freigeben */
	GlobalUnlock (hBI);

return hBI;
}


/* Vereinbaren der logischen Palette */
HPALETTE BildObjekt :: CreateDIBPalette (void) 
{
HPALETTE hPal = NULL;

	if (!_hDIB) return NULL;
	hPal = CreateBIPalette ((BITMAPINFOHEADER *)GlobalLock (_hDIB));
	GlobalUnlock (_hDIB);

return hPal;
}


/* Bilden der Palette fuer BITMAPINFOSTRUCT */
HPALETTE BildObjekt :: CreateBIPalette (BITMAPINFOHEADER *lpBI) 
{
RGBQUAD *lpRGB;
unsigned int iNumColors;
LOGPALETTE *pPal;
HPALETTE hPal = NULL;
HGLOBAL h;

/* Anfangstests */
	if (!lpBI)
		return NULL;
	if (lpBI->biSize != sizeof(BITMAPINFOHEADER)) return NULL;

/* Logische Palette fuellen und vereinbaren */
	lpRGB = (RGBQUAD *)((char *)lpBI + (unsigned int)lpBI->biSize);
	iNumColors = DIBNumColors (lpBI);
	h = (HGLOBAL)GlobalAlloc (GHND, sizeof(LOGPALETTE) +
					iNumColors * sizeof(PALETTEENTRY));
	if (!h) return NULL;

	pPal = (LOGPALETTE *)GlobalLock(h);
	if (!pPal) return NULL;
	/* Palette fuellen */
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


/* Bestimmen der Anzahl der vertretenen Farben in der BitMap */
unsigned int BildObjekt :: DIBNumColors (BITMAPINFOHEADER *lpbi) 
{
	if (lpbi->biClrUsed != 0)
		return ((unsigned int)lpbi->biClrUsed);

	switch (lpbi->biBitCount) {
	case 1: return 2;
	case 4: return 16;
	case 8: return 256;
	default: return 0; /* 24-Bit DIB hat keine Farbtabelle */
	}
}


/* Datenstrukturen freigeben, Objekte löschen */
void BildObjekt :: FreeDIB (void) 
{
	if (_hPal) DeleteObject (_hPal);
	if (_hDDB) DeleteObject (_hDDB);
	if (_hDIB) GlobalFree (_hDIB);
	_hPal = NULL;
	_hDDB = NULL;
	_hDIB = NULL;
}


/* Umformen einer DIB in eine DDB */
HBITMAP BildObjekt :: DIBToBitmap (void) 
{
BITMAPINFOHEADER *lpBI;
HPALETTE hPalT;
HDC hDC;
HBITMAP hBM;

	if (!_hDIB)
		return NULL;
/* Bitmapheader */
	lpBI = (BITMAPINFOHEADER *)GlobalLock (_hDIB);
	if (!lpBI)
		return NULL;

/* Palette realisieren */
	hDC = :: GetDC (NULL);
	if (_hPal) {
		hPalT = SelectPalette (hDC, _hPal, FALSE);
		RealizePalette (hDC);
	}

/* device dependent bitmap (DDB) erzeugen */
	hBM = CreateDIBitmap (hDC, lpBI, (long)CBM_INIT,
			(char *)lpBI + lpBI->biSize + 
			DIBNumColors(lpBI)*sizeof(RGBQUAD), //  PaletteSize (lpBI),
			(BITMAPINFO *)lpBI, DIB_RGB_COLORS);

/* alte Palette wiedereinstellen */
	if (_hPal)
		SelectPalette (hDC, hPalT, FALSE);

	ReleaseDC (NULL, hDC);
	GlobalUnlock (_hDIB);

return hBM;
}


/* Anzeige einer BitMap im vorgegebenen Fenster */
void _XTENSN_EXPORT BildObjekt :: Draw (void) 
{
// hDC holen
HWND hWnd = ((NakedWindow *)pWnd) -> Handle (API_CLIENT_HWND);
HDC hDC = :: GetDC (hWnd);

// Bildposition festlegen
	SetWindowOrgEx (hDC, _Org.X(), _Org.Y(), NULL);

// Palette aktivieren
	if (!_hPal)
		return;

HPALETTE hPalT = SelectPalette (hDC, _hPal, FALSE);

	RealizePalette (hDC);

// Bitmap zeichnen
BITMAP bm;

	HDC hDCBits = CreateCompatibleDC (hDC);
	GetObject (_hDDB, sizeof(BITMAP), (char *)&bm);
	HBITMAP hOldBM = (HBITMAP)SelectObject (hDCBits, _hDDB);

	if (!IsWinNT())		// unter Win9x muß das Bild auf den Kopf gestellt werden
		StretchBlt (hDC, 0, 0, bm.bmWidth, bm.bmHeight, hDCBits, 0, bm.bmHeight, bm.bmWidth, -bm.bmHeight, SRCCOPY);
	else
		BitBlt (hDC, 0, 0, bm.bmWidth, bm.bmHeight, hDCBits, 0, 0, SRCCOPY);

// alten Zustand wieder einstellen
	SelectPalette (hDC, hPalT, FALSE);
	ReleaseDC (hWnd, hDC);
	SelectObject (hDCBits, hOldBM);
	DeleteDC (hDCBits);     
}


extern "C" {

#define MAXREAD 32767

/* Lesen von Blöcken größer als 64kByte */
unsigned long PASCAL lread (int fh, void __huge *pv, unsigned long ul) 
{

unsigned long ulT = ul;
char __huge *hp = (char __huge *)pv;
int readBytes;
char *tmpBuff = new char [MAXREAD];

	if (tmpBuff == NULL) 
		return 0;
	while (ul > (unsigned long)MAXREAD) {
		if ((readBytes = LZRead (fh, tmpBuff, MAXREAD)) != MAXREAD) {
			delete tmpBuff;
			return 0;
		}
		memcpy (hp, tmpBuff, MAXREAD);
		ul -= MAXREAD;
		hp += MAXREAD;
	}
	if ((readBytes = LZRead (fh, tmpBuff, (int)ul)) != (int)ul) {
		delete tmpBuff;
		return 0;
	}
	memcpy (hp, tmpBuff, (unsigned int)ul);
	delete tmpBuff;

return ulT;
}

} // extern "C"
