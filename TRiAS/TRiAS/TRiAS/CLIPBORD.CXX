// Funktionen uer die uebergabe eines Bildschirmausschnittes in Clipboard
// File: CLIPBORD.CXX

#include "triaspre.hxx"

#include "Strings.h"
#include "prntpars.hxx"

#define PaletteSize(pv) (DIBNumColors((LPBITMAPINFOHEADER)(pv))*sizeof(RGBQUAD))
#define WIDTHBYTES(i) (((i)+31)/32*4)
#define MF_ISOTROPIC		// isotropisches Metafile

///////////////////////////////////////////////////////////////////////////////
// globale Variablen 
extern HPALETTE hPalette;

///////////////////////////////////////////////////////////////////////////////
// globale Funktionsprototypen 
HENHMETAFILE RetrieveMetaFile (HWND, Rectangle &Rc, RECTL &rclDB, UINT uiMapMode);

///////////////////////////////////////////////////////////////////////////////
// statische Funktionsprototypen 
static Rectangle EvalGeoDBRect (Rectangle &rRc, RECTL &rRcl, ObjContainer &rOC);
static HBITMAP RetrieveBitmap (HWND, CoOrd, CoOrd, CoOrd, CoOrd);
static HPALETTE CopyPalette (HPALETTE);
static HBITMAP DIBFromBitmap (HBITMAP hBM, DWORD biStyle, WORD biBits, HPALETTE hPal);
WORD DIBNumColors (LPBITMAPINFOHEADER lpbi);

///////////////////////////////////////////////////////////////////////////////
// Bildausschnitt ins ClipBoard kopieren 
ErrCode DatenBasisObjekt::CopyToClipBoard (pWindow pW, Rectangle &Rc) 
{
CEierUhr Wait (pW);
HWND hWnd = pW -> Handle (API_CLIENT_HWND);
Rectangle CRc = pW -> CanvasRect();
CoOrd dY = CoOrd(CRc.Bottom() - CRc.Top());

	Point UL = Rc.UpperLeft();
	Point LR = Rc.LowerRight();

// Ausschnitt kopieren
HBITMAP hBM = RetrieveBitmap (hWnd, UL.X(), CoOrd(-(dY + UL.Y())+1), 
				    CoOrd(LR.X()-UL.X()-2), CoOrd(LR.Y()-UL.Y()-2));
// Palette kopieren
HPALETTE hPal = CopyPalette (hPalette);
HBITMAP hDIB = DIBFromBitmap (hBM, BI_RGB, 0, hPalette);

// MetaFile erzeugen

// 
// hier ist ein Bug in DragRectangleObject :: GetRect()
// rRc.Top() ist eigentlich die größere Koordinate und 
// rRc.Bottom() ist um 2 * die Höhe zu groß.
// 
	Rc.Bottom() = CoOrd(2*Rc.Top()-Rc.Bottom());

RECTL rclGeoDB;
long lCont[4];
KoOrd dXMin, dXMax, dYMin, dYMax;

	DEX_GetProjectCont(lCont);
	if (!UnScaleCTF (lCont[0], lCont[2], &dXMin, &dYMin) ||
		!UnScaleCTF (lCont[1], lCont[3], &dXMax, &dYMax))
	{
		return EC_FAIL;
	}

ObjContainer OC (dXMin, dXMax, dYMin, dYMax);
Rectangle rcCorr = EvalGeoDBRect (Rc, rclGeoDB, OC);		// aus CommonVu-Koordinaten
HGLOBAL hMFP = (HGLOBAL)RetrieveMetaFile (hWnd, rcCorr, rclGeoDB, MM_HIMETRIC);

	if (hBM || (hDIB && hPal) || hMFP) {
	// Bitmap, DIB oder Metafile gültig: ClipBoard füllen
		OpenClipboard (hWnd);
		EmptyClipboard ();
		if (NULL != hMFP) SetClipboardData (CF_ENHMETAFILE, (HANDLE)hMFP);
		if (NULL != hDIB) SetClipboardData (CF_DIB, hDIB);
		if (NULL != hBM) SetClipboardData (CF_BITMAP, hBM);
		if (NULL != hPal) SetClipboardData (CF_PALETTE, hPal);
		CloseClipboard ();
	} else
		return (ErrCode)db_error (EC_NOMEMORY, RC_CopyToClipBoard);

	return EC_OKAY;
}

// Bitmap von der Größe des geforderten Ausschnittes generieren und
// diesen Bildschirminhalt reinkopieren
static HBITMAP RetrieveBitmap (HWND hWnd, CoOrd xStart, CoOrd yStart, CoOrd xSize, CoOrd ySize) 
{
HDC hDC = :: GetDC (hWnd);	// FensterDC
HDC hDCMem = CreateCompatibleDC (hDC);		// SpeicherDC
HBITMAP hBM = CreateCompatibleBitmap (hDC, xSize, ySize);

	if (hBM) {
	// neue Bitmap selektieren
		SelectObject (hDCMem, hBM);
	
	HPALETTE hPalT = ::SelectPalette(hDCMem, hPalette, false);

		::RealizePalette(hDCMem);

	// Ausschnitt kopieren
		::BitBlt (hDCMem, 0, 0, xSize, ySize, hDC, xStart, yStart, SRCCOPY);
		::SelectPalette (hDCMem, hPalT, false);
	}
// hDCMem freigeben
	DeleteDC (hDCMem);
	ReleaseDC (hWnd, hDC);

return hBM;
}

// Palette kopieren -----------------------------------------------------------
static HPALETTE CopyPalette (HPALETTE hPal) 
{
WORD nNumEntries;

	if (!hPal) 
		return NULL;
// Anzahl der PalettenEinträge holen
	GetObject (hPal, sizeof(WORD), (LPSTR)&nNumEntries);
	if (nNumEntries == 0) 
		return NULL;

// temporär Speicher für Palette anlegen
LOGPALETTE *pPal = (LOGPALETTE *)new char [sizeof(LOGPALETTE) + 
					  nNumEntries*sizeof(PALETTEENTRY)];
	if (!pPal)
		return NULL;

// Palette kopieren
	pPal->palVersion = 0x300;
	pPal->palNumEntries = WORD(nNumEntries);
	GetPaletteEntries (hPal, 0, nNumEntries, pPal->palPalEntry);

// Palette anlegen
	hPal = CreatePalette (pPal);

// Speicher wieder freigeben
	if (pPal) {
		delete (char *)pPal;
		pPal = NULL;
	}

return hPal;
}

/* Umwandeln einer Bitmap in eine DIB */
static HBITMAP DIBFromBitmap (HBITMAP hBM, DWORD biStyle, WORD biBits, HPALETTE hPal) 
{
BITMAP bm;
BITMAPINFOHEADER bi;
BITMAPINFOHEADER *lpbi;
DWORD dwLen;
HBITMAP hDIB;
HGLOBAL h;
HDC hDC;

/* Parametertest */
	if (!hBM) return NULL;
	if (!hPal) hPal = (HPALETTE)GetStockObject (DEFAULT_PALETTE);

/* BITMAPINFOHEADER fuellen */
	GetObject (hBM, sizeof(bm), (LPSTR)&bm);

	if (!biBits) 
		biBits = WORD(bm.bmPlanes * bm.bmBitsPixel);

	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bm.bmWidth;
	bi.biHeight = bm.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = biBits;
	bi.biCompression = biStyle;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

/* Neue DIB generieren */
	dwLen = bi.biSize + PaletteSize (&bi);

	hDC = GetDC (NULL);
	hPal = SelectPalette (hDC, hPal, FALSE);
	RealizePalette (hDC);

	hDIB = (HBITMAP)GlobalAlloc (GHND, dwLen);
	if (!hDIB) {
		SelectPalette (hDC, hPal, FALSE);
		ReleaseDC (NULL, hDC);
		return NULL;
	}
	lpbi = (BITMAPINFOHEADER *)GlobalLock (hDIB);

	*lpbi = bi;

/* biSizeImage durch GetDIBits berechnen lassen */
	GetDIBits (hDC, hBM, 0, (WORD)bi.biHeight, NULL,
		(LPBITMAPINFO)lpbi, DIB_RGB_COLORS);
	bi = *lpbi;
	GlobalUnlock (hDIB);

/* evtl bi.biSizeImage default fuellen */
	if (bi.biSizeImage == 0) {
		bi.biSizeImage = WIDTHBYTES ((DWORD)bm.bmWidth * biBits) *
						bm.bmHeight;
		if (biStyle != BI_RGB)
			bi.biSizeImage = (bi.biSizeImage *3) / 2;
	}

/* notwendigen Speicher anfordern */
	dwLen = bi.biSize + PaletteSize (&bi) + bi.biSizeImage;
	if ((h = (HGLOBAL)GlobalReAlloc (hDIB, dwLen, 0)) != 0) 
		hDIB = (HBITMAP)h;
	else {
		GlobalFree (hDIB);
		SelectPalette (hDC, hPal, FALSE);
		ReleaseDC (NULL, hDC);
		return NULL;
	}

/* Bits umkopieren */
	lpbi = (BITMAPINFOHEADER *)GlobalLock (hDIB);
	if (GetDIBits (hDC, hBM, 0, (WORD)bi.biHeight,
			(LPSTR)lpbi + (WORD)lpbi->biSize + PaletteSize(lpbi),
			(LPBITMAPINFO)lpbi, DIB_RGB_COLORS) == 0) {
		GlobalUnlock (hDIB);
		SelectPalette (hDC, hPal, FALSE);
		ReleaseDC (NULL, hDC);
		return NULL;
	}
/* fertig ist das Mondgesicht */
	bi = *lpbi;
	GlobalUnlock (hDIB);
	SelectPalette (hDC, hPal, FALSE);
	ReleaseDC (NULL, hDC);

return hDIB;
}


/* Bestimmen der Anzahl der vertretenen Farben in der BitMap */
WORD DIBNumColors (LPBITMAPINFOHEADER lpbi) 
{
	if (lpbi->biClrUsed != 0) 
		return ((WORD)lpbi->biClrUsed);

	switch (lpbi->biBitCount) {
	case 1:	return 2;
	case 4:	return 16;
	case 8:	return 256;
	default: return 0; /* 24-Bit DIB hat keine Farbtabelle */
	}
}


///////////////////////////////////////////////////////////////////////////////
// MetaFile erzeugen, daß den ausgewählten Bildausschnitt enthält
HENHMETAFILE RetrieveMetaFile (
	HWND hWnd, Rectangle &Rc, RECTL &rclDB, UINT uiMapMode)
{
HDC hTargetDC = NULL;
bool fDeleteDC = false;

#if defined(_DEBUG)
	if (GetKeyState (VK_CONTROL) < 0) {
	ActPrinterPars *pAPP = new ActPrinterPars();

		hTargetDC = CreateIC (pAPP -> DriverName(), pAPP -> DeviceName(), 
				      pAPP -> PortName(), pAPP -> DeviceMode());
		DELETE_OBJ (pAPP);
		fDeleteDC = true;
	} else
#endif // _DEBUG
		hTargetDC = ::GetDC (hWnd);

// vorbereitende Maßnahmen
	SaveDC (hTargetDC);
	
// Ausschnittsrechtecke vorbereiten	
RENDERGEODB RDB;
RECT rc;

	RDB.dwSize = sizeof(RENDERGEODB);
	RDB.m_hTargetDC = hTargetDC;
	RDB.m_rclGeoDB = rclDB;

	GetClientRect (hWnd, &rc);

CoOrd dY = CoOrd(rc.top - rc.bottom);

	Rc.Top() = CoOrd(-(dY+Rc.Top())) +2;	// -> MM_TEXT Koordinaten
	Rc.Bottom() = CoOrd(-(dY+Rc.Bottom())) +2;

// ZeichnungsBereich im TargetDC (in HIMETRIC) berechnen
	SetMapMode (hTargetDC, MM_HIMETRIC);		// Bezugsauflösung
	DPtoLP (hTargetDC, (POINT *)&Rc, 2);

	RDB.m_rclFrame.left = 0;	// Rc.Left();
	RDB.m_rclFrame.top = -(Rc.Bottom() - Rc.Top());
	RDB.m_rclFrame.right = Rc.Right() - Rc.Left();
	RDB.m_rclFrame.bottom = 0;	// -Rc.Top();	

// BegrenzungsRechteck des Metafiles berechnen
RECT rcMF;

	rcMF.top = 0;
	rcMF.bottom = -(Rc.Bottom() - Rc.Top()); 
	rcMF.right = Rc.Right() - Rc.Left();
	rcMF.left = 0;

// ClippingRechteck im ZielDC berechnen
	RDB.m_rclClipBox = RDB.m_rclFrame;
	RDB.m_rclClipBox.right += 1;
	RDB.m_rclClipBox.bottom += 1;

HDC hDCMeta = NULL;

// hier geht das rendering los (linke obere Ecke des Ausschnittes liegt
// in linker oberer Ecke des MetaBildes
	if (uiMapMode == MM_ISOTROPIC) {
		hDCMeta = CreateEnhMetaFile (hTargetDC, NULL, (RECT *)&rcMF, g_cbTRiASPict);
		SetMapMode (hDCMeta, MM_ISOTROPIC);	// Bezugsauflösung
		SetWindowOrgEx (hDCMeta, 0, (CoOrd)(RDB.m_rclFrame.top-RDB.m_rclFrame.bottom), NULL);
		SetWindowExtEx (hDCMeta, (CoOrd)(RDB.m_rclFrame.right-RDB.m_rclFrame.left),
								 (CoOrd)(RDB.m_rclFrame.top-RDB.m_rclFrame.bottom),
						NULL);
	} else {
		hDCMeta = CreateEnhMetaFile (hTargetDC, NULL, (RECT *)&rcMF, g_cbTRiASPict);
		SetMapMode (hDCMeta, uiMapMode);	// Bezugsauflösung
		SetWindowOrgEx (hDCMeta, 0, (CoOrd)(RDB.m_rclFrame.top-RDB.m_rclFrame.bottom), NULL);
	}

HENHMETAFILE hMetaF = NULL;

	if (NULL != hDCMeta) {
		RDB.m_hDC = hDCMeta;
		DEX_RenderGeoDB (RDB);					// DB zeichnen
		hMetaF = CloseEnhMetaFile (hDCMeta);	// MetaFile schließen
	}

// alles freigeben
	RestoreDC (hTargetDC, -1);
	if (fDeleteDC) 
		DeleteDC (hTargetDC);
	else 
		ReleaseDC (hWnd, hTargetDC);

// in WIN32 muß lediglich das Handle des Metafiles übergeben werden
	return hMetaF;
}

// Berechnen des entsprechenden GeoDBContainers, im aktuellen DC (Bildschirm) 
inline long ToLong (double d)
{
	return (long)(d + 0.5);
}
 
static 
Rectangle EvalGeoDBRect (Rectangle &rRc, RECTL &rRcl, ObjContainer &rOC)
{
Punkt pkt1 = DCtoOC (rRc.Left(), rRc.Top());
Punkt pkt2 = DCtoOC (rRc.Right(), rRc.Bottom());

	rRcl.left = pkt1.GetX();
	rRcl.top = pkt1.GetY();
	rRcl.right = pkt2.GetX();
	rRcl.bottom = pkt2.GetY();

// Abgleich mit ProjektContainer
	rRcl.left = max (ToLong(rOC.XMin()), rRcl.left);
	rRcl.right = min (ToLong(rOC.XMax()), rRcl.right);
	rRcl.bottom = max (ToLong(rOC.YMin()), rRcl.bottom);
	rRcl.top = min (ToLong(rOC.YMax()), rRcl.top);

// Rückrechnen des BezugsRechteckes
Point pt1 = OCtoDC (rRcl.left, rRcl.top);
Point pt2 = OCtoDC (rRcl.right, rRcl.bottom);

	return Rectangle (pt1.Y(), pt1.X(), pt2.Y(), pt2.X());		// tlbr
}

