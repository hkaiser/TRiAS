// RechtecksFlaeche, auf de Punkt-/Linien ode Flaechenobjekte dargestellt werden
// File: PALRECT.CXX

#include "triaspre.hxx"

#include "clbmpobj.hxx"
#include "palrect.hxx"

#define MYROPCODE		0x00b8074a
#define MYROPCODEINV	0x00e20746

// RectangleObject, welches mit einer vorgegebenen Palette zeichnet -----------
HPALETTE PaletteRectangleObject :: SetPalette (HPALETTE hPal) 
{
HPALETTE oldPal = _hPal;

	_hPal = hPal;

return oldPal;
}

HPALETTE PaletteRectangleObject :: GetPalette (void) 
{
	return _hPal;
}

// Palette neu generieren -----------------------------------------------------
HPALETTE PaletteRectangleObject :: MakePalette (Color MainC, Color FillC) 
{
HPALETTE hPalette;

// Palette neu generieren
// Speicher für Palette anfordern
LOGPALETTE *pPal = (LOGPALETTE *)new char [sizeof(LOGPALETTE) + 
					  2*sizeof(PALETTEENTRY)];

	if (pPal == NULL) return NULL;

// Palette initialisieren
	pPal -> palNumEntries = 2;
	pPal -> palVersion = PALVERSION;

// PaletteEintrag für PenColor
	pPal -> palPalEntry[0].peRed = (BYTE)MainC.Red();
	pPal -> palPalEntry[0].peGreen = (BYTE)MainC.Green();
	pPal -> palPalEntry[0].peBlue = (BYTE)MainC.Blue();
	pPal -> palPalEntry[0].peFlags = (BYTE)0;
// PaletteEintrag für BrushColor
	pPal -> palPalEntry[1].peRed = (BYTE)FillC.Red();
	pPal -> palPalEntry[1].peGreen =(BYTE)FillC.Green();
	pPal -> palPalEntry[1].peBlue = (BYTE)FillC.Blue();
	pPal -> palPalEntry[1].peFlags = (BYTE)0;

	if (GetPalette() != NULL) {
		DeleteObject (GetPalette());
		SetPalette (NULL);
	}

// Palette generieren
	hPalette = CreatePalette (pPal);
/*
	} else {
		SetPaletteEntries (GetPalette(), 0, 2, pPal -> palPalEntry);
		hPalette = GetPalette();
	}
*/
// Speicher wieder freigeben
	if (pPal) {
		delete (char *)pPal;
		pPal = NULL;
	}

return hPalette;
}

// Konstruktoren für PaletteRectangleObjects ----------------------------------
PaletteRectangleObject :: PaletteRectangleObject (pWindow pW, Point P, Dimension D,
						  pPen pP, pBrush pB, HPALETTE hPal)
			: RectangleObject (P, D, pP, pB)
{
	_hPal = hPal;
	_pW = pW;
}

PointPaletteRectObject :: PointPaletteRectObject (pWindow pW, Point P, Dimension D)
			: PaletteRectangleObject (pW, P, D, NULL, NULL, NULL)
{
	_pBM = NULL;
}

LinePaletteRectObject :: LinePaletteRectObject (pWindow pW, Point P, Dimension D)
		       : PaletteRectangleObject (pW, P, D, NULL, NULL, NULL)
{
	// nothing else to do
}

AreaPaletteRectObject :: AreaPaletteRectObject (pWindow pW, Point P, Dimension D)
		       : PaletteRectangleObject (pW, P, D, NULL, NULL, NULL)
{
	m_BkCol = Color ((ColorVal)0, (ColorVal)0, (ColorVal)0);
	m_pBM = NULL;
}

// Destruktoren ---------------------------------------------------------------
PaletteRectangleObject :: ~PaletteRectangleObject (void) {}
PointPaletteRectObject :: ~PointPaletteRectObject (void) {}
LinePaletteRectObject :: ~LinePaletteRectObject (void) {}
AreaPaletteRectObject :: ~AreaPaletteRectObject (void) {}

// Zeichenroutinen für Punkt-/Linien- bzw. FlächenMonitoring ------------------
void PointPaletteRectObject :: Draw (void) 
{
HPALETTE hOldPal;

// Palette aktivieren
	if (_hPal != NULL) {
		hOldPal = SelectPalette (_hDC, _hPal, FALSE);
		RealizePalette (_hDC);
	}

// Punktsymbol zeichnen
Rectangle R = BoundingBox();

// erst mal Rechteck löschen
HBRUSH hOldBrush = (HBRUSH)SelectObject (_hDC, GetStockObject (WHITE_BRUSH));
HPEN hOldPen = (HPEN)SelectObject (_hDC, GetStockObject (NULL_PEN));

	DrawRectangle (_hDC, R.Left(), R.Bottom(), R.Right(), R.Top());
	SelectObject (_hDC, hOldPen);
	SelectObject (_hDC, hOldBrush);

// ClippingArea setzen
CoOrd dY = R.Bottom() - R.Top();
HRGN hRgn = CreateRectRgn (R.Left(), -(dY + R.Top()), R.Right(), -(dY + R.Bottom()));

	SelectObject (_hDC, hRgn);
	DeleteObject (hRgn);

	if (NULL == _pBM) return;	// neue Punktsymbole

// Größenverhältnisse bestimmen
// long Arithmetik, da sonst bei hohen Auflösungen Überlauffehler entstehen
#if defined(_FORCE_LEGACY_CODE)
long res = (GetGeoDBVersion() >= VERSION05000004) ? 100L : 10L;	// früher 1/10 mm, jetzt 1/100mm
#else
long res = 100L;
#endif // defined(_FORCE_LEGACY_CODE)
short LogPX = (short)(((long)GetDeviceCaps (_hDC, HORZRES) * (long)_Size.Width()) /
		(res * (long)GetDeviceCaps (_hDC, HORZSIZE)));
short LogPY = (short)(((long)GetDeviceCaps (_hDC, VERTRES) * (long)_Size.Height()) / 
		(res * (long)GetDeviceCaps (_hDC, VERTSIZE)));

// Hintergrundfarbe auf weiß (default setzen)
DWORD oldBkColor = SetBkColor (_hDC, 0x00ffffff);
DWORD oldTextColor = SetTextColor (_hDC, 0);
int oldBkMode = SetBkMode(_hDC, TRANSPARENT);

// Bitmap darstellen
HDC hMemDC = CreateCompatibleDC (_hDC);
Point Pt ((R.Right()-R.Left())/2, (R.Top()-R.Bottom())/2);
HBITMAP hOldBM;

	if (_pBM) {	// alte Punktsymbole
	Dimension BMdim = _pBM -> GetSize();
	HBITMAP hBM = _pBM -> Handle (API_BITMAP_HBITMAP);
		
		hOldBM = (HBITMAP)SelectObject (hMemDC, hBM);
		if (GetBrush() != NULL)
			hOldBrush = (HBRUSH)SelectObject (_hDC, GetBrush() -> Handle());
		else
			hOldBrush = (HBRUSH)SelectObject (_hDC, GetStockObject (NULL_BRUSH));
		StretchBlt (_hDC,   Pt.X()-LogPX/2, Pt.Y()-LogPY/2,
				    LogPX, LogPY,
			    hMemDC, 0, 0, 
				    BMdim.Width(), BMdim.Height(),
			    MYROPCODE);
	
		if (GetBrush() != NULL) SelectObject (_hDC, hOldBrush);
		SelectObject (hMemDC, hOldBM);
	}
/*	else {
#if !defined(WIN32)
	int oldStretchMode = SetStretchBltMode (_hDC, WHITEONBLACK);
#else
	int oldStretchMode = SetStretchBltMode (
			_hDC, m_pCBO -> isColored() ? HALFTONE : WHITEONBLACK);
#endif
	CoOrd iMaskDimX = m_pCBO -> GetHeight();
	CoOrd iMaskDimY = m_pCBO -> GetWidth();

		hOldBM = (HBITMAP)SelectObject (hMemDC, m_pCBO -> WhiteMask());
		hOldBrush = (HBRUSH)SelectObject (_hDC, 
				CreateSolidBrush (RGB (0xff, 0xff, 0xff)));
		StretchBlt (_hDC,	Pt.X()-LogPX/2, Pt.Y()-LogPY/2,
					LogPX, LogPY, 
			    hMemDC, 	m_pCBO -> XOffset(), m_pCBO -> YOffset(), 
			    		iMaskDimX, iMaskDimY,
			    MYROPCODEINV);

		if (GetBrush() != NULL)
			DeleteObject (SelectObject (_hDC, GetBrush() -> Handle()));
		else
			DeleteObject (SelectObject (_hDC, GetStockObject (NULL_BRUSH)));

		SelectObject (hMemDC, m_pCBO -> BlackMask());
		StretchBlt (_hDC,   	Pt.X()-LogPX/2, Pt.Y()-LogPY/2,
					LogPX, LogPY, 
			    hMemDC, 	m_pCBO -> XOffset(), m_pCBO -> YOffset(), 
			    		iMaskDimX, iMaskDimY,
			    MYROPCODEINV);
		SelectObject (_hDC, hOldBrush);
		SetStretchBltMode (_hDC, oldStretchMode);
	}
*/
// Palette wieder herstellen
	if (_hPal != NULL)
		SelectPalette (_hDC, hOldPal, FALSE);
	SetTextColor (_hDC, oldTextColor);
	SetBkMode (_hDC, oldBkMode);
	SetBkColor (_hDC, oldBkColor);

// alten Zustand wieder herstellen
	DeleteDC (hMemDC);
}

// LinienMonitoring -----------------------------------------------------------
void LinePaletteRectObject :: Draw (void) 
{
HPALETTE hOldPal;

// Palette aktivieren
	if (_hPal != NULL) {
		hOldPal = SelectPalette (_hDC, _hPal, FALSE);
		RealizePalette (_hDC);
	}

// Linie zeichnen
Rectangle R = BoundingBox();

// erst mal Rechteck löschen
HBRUSH hOldBrush = (HBRUSH)SelectObject (_hDC, GetStockObject (WHITE_BRUSH));
HPEN hOldPen = (HPEN)SelectObject (_hDC, GetStockObject (NULL_PEN));

	DrawRectangle (_hDC, R.Left(), R.Bottom(), R.Right(), R.Top());
	SelectObject (_hDC, hOldPen);
	SelectObject (_hDC, hOldBrush);

// ClippingArea setzen
CoOrd dY = R.Bottom() - R.Top();
HRGN hRgn = CreateRectRgn (R.Left(), -(dY + R.Top()), R.Right(), -(dY + R.Bottom()));

	SelectObject (_hDC, hRgn);
	DeleteObject (hRgn);

// richtigen Pen einstellen
ExtPen *pEPen = (ExtPen *)GetPen();	// Pen dieses Objektes holen
Point Begin ((R.Right()-R.Left())/2, R.Bottom()+(R.Top()-R.Bottom())/4);
Point End ((R.Right()-R.Left())/2, R.Top()-(R.Top()-R.Bottom())/4);

// alle Linien dieses ExtPens ausgeben
	for (short iCnt = 0; iCnt < pEPen -> iCnt(); iCnt++) {
	// aktuellen Pen selektieren
		if (pEPen != NULL)
			hOldPen = (HPEN)SelectObject (_hDC, pEPen -> GetHandle (iCnt));
		else
			hOldPen = (HPEN)SelectObject (_hDC, GetStockObject (NULL_PEN));

	// Linie zeichnen         
		MoveToEx (_hDC, Begin.X(), Begin.Y(), NULL);
		LineTo (_hDC, End.X(), End.Y());

	// DeviceKontext zurücksetzen
		if (pEPen != NULL) SelectObject (_hDC, hOldPen);
	}

// alte Palette wieder einstellen
	if (_hPal != NULL) SelectPalette (_hDC, hOldPal, FALSE);
}

// Flächenmonitoring ----------------------------------------------------------
void AreaPaletteRectObject::Draw (void) 
{
HPALETTE hOldPal;
int i = 0;

// Palette aktivieren
	if (_hPal != NULL) {
		hOldPal = SelectPalette (_hDC, _hPal, FALSE);
		i = RealizePalette (_hDC);
	}

	if (NULL != m_pBM) {
		DrawTransparentWithPattern();	// transparente Patterns
		DrawNormal(true);				// nur Kontur zeichnen
	} else
		DrawNormal();					// normales zeichnen

// alte Palette wieder einstellen
	if (_hPal != NULL) 
		SelectPalette (_hDC, hOldPal, FALSE);
}

void AreaPaletteRectObject::DrawTransparentWithPattern (void)
{
// jetzt zeichnen
HDC hDCSrc = ::CreateCompatibleDC (_hDC);
HBITMAP hOldBmp = (HBITMAP)::SelectObject (hDCSrc, m_pBM -> Handle());
HBRUSH hOldBrush;

	if (NULL != GetBrush())	
		hOldBrush = (HBRUSH)::SelectObject (_hDC, GetBrush() -> Handle());

COLORREF crOldBkColor = ::SetBkColor (_hDC, RGB(255, 255, 255));
COLORREF crOldTextColor = ::SetTextColor (_hDC, RGB(0, 0, 0));
Rectangle R = BoundingBox();
Dimension dim = m_pBM -> GetSize();

	FillRect (_hDC, (RECT *)&R, (HBRUSH)GetStockObject(WHITE_BRUSH));
	for (long y = R.Bottom(); y <= R.Top(); y += dim.Height()) {
		for (long x = R.Left(); x <= R.Right(); x += dim.Width()) {
		long dX = min(x+dim.Width(), R.Right()-R.Left()) - x;
		long dY = min(y+dim.Height(), R.Top()-R.Bottom()) - y;

			BitBlt (_hDC, x, y, dX, dY, hDCSrc, 0, 0, MYROPCODE);
		}
	}

	::SetTextColor (_hDC, crOldTextColor);
	::SetBkColor (_hDC, crOldBkColor);

	if (NULL != GetBrush()) ::SelectObject (_hDC, hOldBrush);

	::SelectObject (hDCSrc, hOldBmp);
	::DeleteDC (hDCSrc);
}

void AreaPaletteRectObject::DrawNormal (bool fForceHollow)
{
// Pinsel einstellen
HBRUSH hOldBrush;

	if (GetBrush() != NULL && !fForceHollow)
		hOldBrush = (HBRUSH)SelectObject (_hDC, GetBrush() -> Handle());
	else
		hOldBrush = (HBRUSH)SelectObject (_hDC, GetStockObject (NULL_BRUSH));

// Pen einstellen
HPEN hOldPen;

	if (GetPen() != NULL)
		hOldPen = (HPEN)SelectObject (_hDC, GetPen() -> Handle());
	else
		hOldPen = (HPEN)SelectObject (_hDC, GetStockObject (NULL_PEN));

// HintergrundFarbe einstellen
COLORREF crOldBkCol = ::SetBkColor (_hDC, (COLORREF &)GetBkColor());

// Rechteck zeichnen
Rectangle R = BoundingBox();

	// 'DrawRectangle' ist ein Alias für die Windows-Funktion 'Rectangle'
	DrawRectangle (_hDC, R.Left(), R.Bottom(), R.Right(), R.Top());

// alles andere wieder einstellen
	::SetBkColor (_hDC, crOldBkCol);
	::SelectObject (_hDC, hOldPen);
	::SelectObject (_hDC, hOldBrush);
}

