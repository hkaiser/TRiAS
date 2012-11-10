// BitmapHandling fuer Bilder
// File: BILDOBJ.CXX

#include "triaspre.hxx"

#include <lzexpand.h>

#if !defined(WIN16)
#undef __huge
#define __huge
#endif

#include "bildobj.hxx"

#if defined(_DEBUG) && !defined(WIN16)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Konstruktor -- Einlesen einer DIB, PaletteSetup ----------------------------
CBildObjekt :: CBildObjekt (pWindow pW, Point pt) 
	     : DrawObject (pt)
{
// Member initialisieren
	m_ptOrg = pt;              // Lage des Bezugspunktes
	m_hDIB = NULL;
	m_hDDB = NULL;
	m_hPal = NULL;
	m_fRealizePalette = true;

// WindowHandle holen
	m_pWnd = pW;
}


BOOL CBildObjekt :: FInit (char *pFileName)
{
// DateiNamen merken
	m_pFileName = new char [strlen (pFileName)+1];
	if (m_pFileName == NULL) {
		m_fOKFlag = false;
		return false;
	}
	strcpy (m_pFileName, pFileName);
	
// Bild einlesen
	m_fOKFlag = InitDIB();
	return true;
}

// Destruktor 
CBildObjekt :: ~CBildObjekt (void) 
{
	DELETE_OBJ (m_pFileName);
	FreeDIB ();     // alles freigeben
}


// Bitmaps einlesen und Paletten initialisieren
bool CBildObjekt :: InitDIB (void) 
{
HFILE cfh;		/* Dateihandle (evtl. komprimiertes File) */
OFSTRUCT of;            /* Dateistruktur */
HPALETTE hPalCurrent;	/* PaletteStruct */
HBITMAP hDIBCurrent;	/* DIB */
HBITMAP hBMCurrent;	/* DDB */
CBindLZ32 LZ32;

	if (!LZ32.IsValid()) return false;

// alte DIB freigeben 
	FreeDIB ();

// Datei eröffnen, Speicherplatz anlegen
	cfh = LZ32.LZOpenFile (m_pFileName, (OFSTRUCT *)&of, OF_READ);
	if (cfh < 0) return false;
	hDIBCurrent = ReadDIBitmapInfo (LZ32, cfh);    /* Farbtabelle lesen */

// Gültigkeit der DIB-Datei prüfen 
	if (hDIBCurrent == NULL) {
		FreeDIB ();
		LZ32.LZClose (cfh);
		return false;
	}
	m_hDIB = hDIBCurrent;                    // im Objekt merken

// PaletteSetup 
	hPalCurrent = CreateDIBPalette();      /* Palette bilden */
	if (hPalCurrent == NULL) {
		FreeDIB ();
		LZ32.LZClose (cfh);
		return false;
	}
	m_hPal = hPalCurrent;

// DIB einlesen 
	hDIBCurrent = ReadDIB (LZ32, cfh);
	if (!hDIBCurrent) {
		FreeDIB ();
		LZ32.LZClose (cfh);
		return false;
	}
	m_hDIB = hDIBCurrent;
	LZ32.LZClose (cfh);

// DDB bilden
	hBMCurrent = DIBToBitmap();
	if (!hBMCurrent) {
		FreeDIB();
		return false;
	}
	m_hDDB = hBMCurrent;

return true;
}


/* Einlesen der DIB in den Speicher */
HBITMAP CBildObjekt :: ReadDIB (CBindLZ32 &rLZ32, HFILE fh) 
{
DWORD dwBits;   /* Größe der DIB */
DWORD dwLen;
HBITMAP h;
BITMAPINFOHEADER bi;
BITMAPINFOHEADER *lpbi;

/* Benoetigten Speicherplatz berechnen */
	DIBInfo (&bi);
	dwBits = bi.biSizeImage;
	dwLen = bi.biSize + (unsigned long)(DIBNumColors(&bi)*sizeof(RGBQUAD));
					// PaletteSize (&bi);

/* Vergrößern des Speicherplatzes für gesamte Bitmap */
	h = (HBITMAP)GlobalReAlloc (m_hDIB, dwLen + dwBits, GHND);
	if (!h) {
	/* gesamten Speicher freigeben */
		GlobalFree (m_hDIB);
		m_hDIB = NULL;
		return NULL;
	} 

/* DIB-Bits einlesen */
	lpbi = (BITMAPINFOHEADER *)GlobalLock (h);
	if (rLZ32.LZHugeRead (fh, (char *)lpbi + dwLen, dwBits) != dwBits) {
	// LeseFehler
		GlobalUnlock (h);
		GlobalFree (h);
		GlobalFree (m_hDIB);  // bisher angeforderten Speicher freigeben
		m_hDIB = NULL;
		return NULL;
	}
	GlobalUnlock (h);

/* Größe der Bitmap merken */
	m_dimSize = Dimension ((short)bi.biWidth, (short)bi.biHeight);

return h;
}


/* Bestimmen der DIB - Info aus einem CF_DIB Speicherblock */
BOOL CBildObjekt :: DIBInfo (BITMAPINFOHEADER *lpBI) 
{
	if (m_hDIB) {
	/* BitmapInfoHeader kopieren */
		*lpBI = *(BITMAPINFOHEADER *)GlobalLock (m_hDIB);

	/* DefaultWerte setzen */
		if (lpBI->biSizeImage == 0L)
			lpBI->biSizeImage = lpBI->biHeight * 
				WIDTHBYTES ((DWORD)lpBI->biWidth*lpBI->biBitCount);
		if (lpBI->biClrUsed == 0L)
			lpBI->biClrUsed = DIBNumColors (lpBI);
		GlobalUnlock (m_hDIB);
		return true;
	}

return false;
}

/* Liest Dateiheader und Farbtabelle im DIBformat ein */
HBITMAP CBildObjekt :: ReadDIBitmapInfo (CBindLZ32 &rLZ32, HFILE fh) 
{
BITMAPFILEHEADER bf;
BITMAPINFOHEADER bi;
unsigned int iNumColors = 0;
HBITMAP hBI = NULL;		/* Farbtabelle - HANDLE */
BITMAPINFOHEADER *lpBI = NULL;
RGBQUAD *lpRGB;                 /* Farbtabelle */
DWORD dwOffset;			/* Dateiposition */

	if (fh == HFILE_ERROR) return NULL;      /* ungueltige Dateihandle */

/* Dateiheader (BITMAPFILEHEADER) lesen */
	dwOffset = rLZ32.LZSeek (fh, 0L, SEEK_CUR);
	if (rLZ32.LZRead (fh, (char *)&bf, sizeof(bf)) != sizeof(bf))
		return NULL;

/* Not a DIB ? */
	if (!ISDIB (bf.bfType)) return NULL;

/* BitMapHeader (BITMAPINFOHEADER) lesen */
	if (rLZ32.LZRead (fh, (char *)&bi, sizeof(bi)) != sizeof(bi))
		return NULL;	/* LeseFehler */

	iNumColors = DIBNumColors ((BITMAPINFOHEADER *)&bi);
	if (bi.biSize != sizeof(BITMAPINFOHEADER))
		return NULL;	/* falsches Datenformat */

/* Defaultgrößen setzen */
	if (bi.biSizeImage == 0)
		bi.biSizeImage = WIDTHBYTES ((DWORD)bi.biWidth * bi.biBitCount)
						*bi.biHeight;
	if (bi.biClrUsed == 0)
		bi.biClrUsed = iNumColors;

/* Speicher fuer BitMap und Farbtabelle anfordern */
	hBI = (HBITMAP)GlobalAlloc (GHND, (DWORD)bi.biSize + iNumColors * sizeof(RGBQUAD));
	if (!hBI) return NULL;
	lpBI = (BITMAPINFOHEADER *)GlobalLock (hBI);
	*lpBI = bi;
	lpRGB = (RGBQUAD *)((char *)lpBI + bi.biSize);

/* Farbtabelle einlesen */
	if (iNumColors)	rLZ32.LZRead (fh, (char *)lpRGB, iNumColors * sizeof(RGBQUAD));

/* an Anfang der BitMap positionieren */
	if (bf.bfOffBits != 0) rLZ32.LZSeek (fh, dwOffset + bf.bfOffBits, SEEK_SET);

/* Speicher wieder freigeben */
	GlobalUnlock (hBI);

return hBI;
}


/* Vereinbaren der logischen Palette */
HPALETTE CBildObjekt :: CreateDIBPalette (void) 
{
HPALETTE hPal = NULL;

	if (!m_hDIB) return NULL;
	hPal = CreateBIPalette ((BITMAPINFOHEADER *)GlobalLock (m_hDIB));
	GlobalUnlock (m_hDIB);

return hPal;
}


/* Bilden der Palette fuer BITMAPINFOSTRUCT */
HPALETTE CBildObjekt :: CreateBIPalette (BITMAPINFOHEADER *lpBI) 
{
RGBQUAD *lpRGB;
unsigned int iNumColors;
LOGPALETTE *pPal;
HPALETTE hPal = NULL;
HGLOBAL h;

/* Anfangstests */
	if (!lpBI) return NULL;
	if (lpBI->biSize != sizeof(BITMAPINFOHEADER)) return NULL;

/* Logische Palette fuellen und vereinbaren */
	lpRGB = (RGBQUAD *)((char *)lpBI + (unsigned int)lpBI->biSize);
	iNumColors = DIBNumColors (lpBI);
	h = (HGLOBAL)GlobalAlloc (GHND, sizeof(LOGPALETTE) +
					iNumColors * sizeof(PALETTEENTRY));
	if (!h) return NULL;

#if !defined(WIN16)
	pPal = (LOGPALETTE *)GlobalLock((void *)h);
#else
	pPal = (LOGPALETTE *)GlobalLock(h);
#endif
	if (!pPal) return NULL;
	/* Palette fuellen */
	pPal->palNumEntries = WORD(iNumColors);
	pPal->palVersion = 0x300;

	for (unsigned short i = 0; i < iNumColors; ++i) {
		pPal->palPalEntry[i].peRed = lpRGB[i].rgbRed;
		pPal->palPalEntry[i].peGreen = lpRGB[i].rgbGreen;
		pPal->palPalEntry[i].peBlue = lpRGB[i].rgbBlue;
		pPal->palPalEntry[i].peFlags = (BYTE)0;
	}
	hPal = CreatePalette (pPal);
#if !defined(WIN16)
	GlobalUnlock ((void *)h);
	GlobalFree ((void *)h);
#else
	GlobalUnlock (h);
	GlobalFree (h);
#endif

return hPal;
}


/* Bestimmen der Anzahl der vertretenen Farben in der BitMap */
unsigned int CBildObjekt :: DIBNumColors (BITMAPINFOHEADER *lpbi) 
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
void CBildObjekt :: FreeDIB (void) 
{
	if (m_hPal) DeleteObject (m_hPal);
	if (m_hDDB) DeleteObject (m_hDDB);
	if (m_hDIB) GlobalFree (m_hDIB);
	m_hPal = NULL;
	m_hDDB = NULL;
	m_hDIB = NULL;
}


/* Umformen einer DIB in eine DDB */
HBITMAP CBildObjekt :: DIBToBitmap (void) 
{
BITMAPINFOHEADER *lpBI;
HPALETTE hPalT;
HDC hDC;
HBITMAP hBM;

	if (!m_hDIB) return NULL;

/* Bitmapheader */
	lpBI = (BITMAPINFOHEADER *)GlobalLock (m_hDIB);
	if (!lpBI) return NULL;

/* Palette realisieren */
	hDC = :: GetDC (NULL);
	if (m_hPal) {
		hPalT = SelectPalette (hDC, m_hPal, false);
		RealizePalette (hDC);
	}

/* device dependent bitmap (DDB) erzeugen */
	hBM = CreateDIBitmap (hDC, lpBI, (long)CBM_INIT,
			(char *)lpBI + lpBI->biSize + 
			DIBNumColors(lpBI)*sizeof(RGBQUAD), //  PaletteSize (lpBI),
			(BITMAPINFO *)lpBI, DIB_RGB_COLORS);

/* alte Palette wiedereinstellen */
	if (m_hPal) SelectPalette (hDC, hPalT, false);

	ReleaseDC (NULL, hDC);
	GlobalUnlock (m_hDIB);

return hBM;
}


/* Anzeige einer BitMap im vorgegebenen Fenster */
void EXPORTTRIAS CBildObjekt :: Draw (void) 
{
// hDC holen
HWND hWnd = m_pWnd -> Handle (API_CLIENT_HWND);
HDC hDC = ::GetDC (hWnd);

// Bildposition festlegen
	::SetWindowOrgEx (hDC, m_ptOrg.X(), m_ptOrg.Y(), NULL);

// evtl. Palette aktivieren
HPALETTE hPalT = NULL;

	if (m_fRealizePalette && NULL != m_hPal) {
		hPalT = ::SelectPalette (hDC, m_hPal, false);
		::RealizePalette (hDC);
	}

// Bitmap zeichnen
HDC hDCBits = CreateCompatibleDC (hDC);
BITMAP bm;

	::GetObject (m_hDDB, sizeof(BITMAP), (char *)&bm);

HBITMAP hOldBM = (HBITMAP)SelectObject (hDCBits, m_hDDB);

	::BitBlt (hDC, 0, 0, bm.bmWidth, bm.bmHeight, hDCBits, 0, 0, SRCCOPY);

// alten Zustand wieder einstellen
	if (m_fRealizePalette && NULL != m_hPal)
		::SelectPalette (hDC, hPalT, false);

	::ReleaseDC (hWnd, hDC);
	::SelectObject (hDCBits, hOldBM);
	::DeleteDC (hDCBits);
}

///////////////////////////////////////////////////////////////////////////////
// Dynamisches Binden der LZ32.DLL
CBindLZ32::CBindLZ32 (void)
	: DLLBind (TEXT("LZ32.DLL")), m_fIsValid(false)
{
	if (NULL == hLib()) return;		// Initialisierungs-Fehler

	m_pLZOpenFile = (LZOPENFILEPROC)GetProcAddress (TEXT("LZOpenFileA"));
	m_pLZSeek = (LZSSEEKPROC)GetProcAddress (TEXT("LZSeek"));
	m_pLZRead = (LZRREADPROC)GetProcAddress (TEXT("LZRead"));
	m_pLZClose = (LZCLOSEPROC)GetProcAddress (TEXT("LZClose"));

	if (NULL != m_pLZOpenFile && NULL != m_pLZSeek &&
		NULL != m_pLZRead && NULL != m_pLZClose)
	{
		m_fIsValid = true;
	}
}

INT CBindLZ32::LZOpenFile (LPSTR pName, LPOFSTRUCT pOF, WORD wMode)
{
	TX_ASSERT(NULL != m_pLZOpenFile);
	return m_pLZOpenFile(pName, pOF, wMode);
}

LONG CBindLZ32::LZSeek (HFILE fh, LONG lOffset, INT iOrigin)
{
	TX_ASSERT(NULL != m_pLZSeek);
	return m_pLZSeek (fh, lOffset, iOrigin);
}

INT CBindLZ32::LZRead (HFILE fh, LPSTR lpBuffer, INT cbRead)
{
	TX_ASSERT(NULL != m_pLZRead);
	return m_pLZRead (fh, lpBuffer, cbRead);
}

VOID CBindLZ32::LZClose (HFILE fh)
{
	TX_ASSERT(NULL != m_pLZClose);
	m_pLZClose (fh);
}

///////////////////////////////////////////////////////////////////////////////
// Lesen von Blöcken größer als 64kByte
#define MAXREAD 32767

DWORD CBindLZ32::LZHugeRead (HFILE fh, void *pv, ULONG ul)
{
DWORD ulT = ul;
char __huge *hp = (char __huge *)pv;
int readBytes;
char *tmpBuff = new char [MAXREAD];

	if (tmpBuff == NULL) return 0;
	while (ul > (DWORD)MAXREAD) {
		if ((readBytes = LZRead (fh, tmpBuff, MAXREAD)) != MAXREAD) {
			delete [] tmpBuff;
			return 0;
		}
		memcpy (hp, tmpBuff, MAXREAD);
		ul -= MAXREAD;
		hp += MAXREAD;
	}
	if ((readBytes = LZRead (fh, tmpBuff, (int)ul)) != (int)ul) {
		delete [] tmpBuff;
		return 0;
	}
	memcpy (hp, tmpBuff, (unsigned int)ul);
	delete [] tmpBuff;

return ulT;
}

