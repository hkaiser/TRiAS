// Klassen fuer das Monitoring der aktuellen Attribute ------------------------
// File: COLORBOX.CXX

#include "triaspre.hxx"

#if !defined(WIN16)
#include <dirisole.h>
#include "extmain3.hxx"
#endif

#include "clbmpobj.hxx"
#include "palrect.hxx"
#include "colorbox.hxx"
#include "feature.hxx"

// Rechteck, in welchem die aktuelle Farbauswahl anzeigt wird -----------------
ColorBox :: ColorBox (pDialogWindow pW, DatenBasisObjekt &rDBO, 
		      uint ID, ColorBoxMode CBM)
	  : ControlWindow (new FixedText (pW, ID)),
	    m_rDBO (rDBO)
{
	_actCBM = CBM;		// ColorBoxMode setzen	
	_DotsPerMM = GetDotsPerMM();
}

// abgeleitete Klassen für Punkt-/Linien- und Flächenobjekte ------------------
PointColorBox :: PointColorBox (pDialogWindow pW, DatenBasisObjekt &rDBO, 
	uint ID, Color C, Dimension Size, short Style, short iRot, Color SecC)
	       : ColorBox (pW, rDBO, ID, rDBO.FNewPnts() ? ColorBox::CBM_Different : ColorBox::CBM_Equal),
	         _P (pW, CanvasPoint(), CanvasDimension())
{
	_Size = Size;
	_Style = Style;
	m_iRot = iRot;
	SetColor (C);
	if (rDBO.FNewPnts()) 	// nur wenn neue PunktSymbole
		SetColor (SecC, ColorBox :: CT_SecondColor);
}

LineColorBox :: LineColorBox (pDialogWindow pW, DatenBasisObjekt &rDBO, 
			      uint ID, Color C, short Width, short Style)
	       : ColorBox (pW, rDBO, ID, ColorBox :: CBM_Equal),
	         m_L (pW, CanvasPoint(), CanvasDimension())
{
	_Width = Width;
	_Style = Style;
	SetColor (C);
}

AreaColorBox :: AreaColorBox (pDialogWindow pW, DatenBasisObjekt &rDBO, 
			      uint ID, Color C, Color SecC, short Style)
	      : ColorBox (pW, rDBO, ID, ColorBox :: CBM_Different),
	        _R (pW, CanvasPoint(), CanvasDimension())
{
	_Style = short(Style & ~BMOpaque);
	m_fIsOpaque = Style & BMOpaque;
	_pBM = NULL;
	SetColor (C);
	SetColor (SecC, ColorBox :: CT_SecondColor);
}

// Destruktoren ---------------------------------------------------------------
PointColorBox :: ~PointColorBox (void) { ResetAttributes(); }
LineColorBox :: ~LineColorBox (void) { ResetAttributes(); }
AreaColorBox :: ~AreaColorBox (void) { ResetAttributes(); DELETE_OBJ (_pBM); }

// Virtuelle Funktionen -------------------------------------------------------
PaletteRectangleObject &PointColorBox :: R (void) { return _P; }
PaletteRectangleObject &LineColorBox :: R (void) { return m_L; }
PaletteRectangleObject &AreaColorBox :: R (void) { return _R; }

// Funktionen, die die Lage und die Größe dieses Controls liefern -------------
Point ColorBox :: CanvasPoint (void) 
{ 
Rectangle R = CanvasRect();

	return Point (R.Left(), R.Bottom());
}

Dimension ColorBox :: CanvasDimension (void) 
{
Rectangle R = CanvasRect();

	return Dimension (CoOrd(R.Right()-R.Left()), CoOrd(R.Top()-R.Bottom()));
}

// ColorBoxMode setzen, alten Mode liefern
ColorBox::ColorBoxMode ColorBox :: SetMode (ColorBox::ColorBoxMode newMode) 
{
ColorBoxMode oldMode = _actCBM;

	_actCBM = newMode;

return oldMode;
}

// anzuzeigende Farbe (Rand-/FüllFarbe setzen)
void ColorBox :: SetColor (Color newColor, ColorType CT) 
{
// Bool BrushChanged = FALSE;

// ReservedByte der Farbe nullsetzen
	newColor.Reserved() = 0;

// neue Farben setzen
	switch (_actCBM) {
	case CBM_Equal:
	// Gesamtes Rechteck mit neuer Farbe neu zeichnen
		_PenColor = newColor;
		_BrushColor = newColor;
//		BrushChanged = TRUE;
		break;

	case CBM_Different:
		switch (CT) {
		case CT_FirstColor:
		// Rand mit neuer Farbe zeichnen
			_PenColor = newColor;
			break;

		case CT_SecondColor:
		// Recheck mit neuer Farbe füllen
			_BrushColor = newColor;
//			BrushChanged = TRUE;
			break;
		}
		break;
	}

// neue Palette bilden
HPALETTE hPal = R().MakePalette(_PenColor, _BrushColor);

Color CvtBrushColor;	// PaletteIndex für Füllfarbe
Color CvtPenColor;

// neue Farbe auf Palette abbilden
	if (hPal != NULL) {
	// neue Palette setzen
	HPALETTE hOldPal = R().SetPalette (hPal);
	// alte Palette freigeben
		
		if (hOldPal != NULL && hOldPal != hPal)
			DeleteObject (hOldPal);

	// Füllfarbe über Palette abbilden
	long pIndex = PALETTEINDEX (GetNearestPaletteIndex (hPal, 
						(COLORREF &)_BrushColor));
		CvtBrushColor = (Color &)pIndex;

	// Randfarbe über Palette abbilden
		pIndex = PALETTEINDEX (GetNearestPaletteIndex (hPal, 
						(COLORREF &)_PenColor));
		CvtPenColor = (Color &)pIndex;
	}

	{
	pPen pP = MakePen (CvtPenColor, CvtBrushColor);
	pPen oldP = R().ChangePen (pP);

		if (oldP) {
			delete (ExtPen *)oldP;
			oldP = NULL;
		}

	pBitmap pBmp = NULL;
	pBrush pB = MakeBrush (CvtBrushColor, CvtPenColor, hPal, &pBmp);
	pBrush oldB = R().ChangeBrush (pB);

		R().ChangeBitmap (pBmp);
		if (oldB) DELETE_OBJ (oldB);
	}

// Rechteck neu zeichnen
	RePaint();	// neu zeichnen
}

Color &ColorBox :: GetPenColor (void) { return _PenColor; }
Color &ColorBox :: GetBrushColor (void) { return _BrushColor; }
short &ColorBox :: GetStyle (void) { return _Style; }

short &LineColorBox :: GetWidth (void) { return _Width; }
Dimension &PointColorBox :: GetSize (void) { return _Size; }
short &PointColorBox :: GetRotation (void) { return m_iRot; }


// Bereich neu zeichnen -------------------------------------------------------
// Die folgenden Funktionen müssen BeginPaint() und EndPaint() selbst besorgen,
// da im CommonVu für ein ControlWindow diese Funktionen nicht gerufen werden.
void PointColorBox :: Expose (ExposeEvt) 
{
// Begin der ZeichenAktion
	_P.GetDC() = :: BeginPaint (Handle(), &_ps);

// eigentliche Zeichenaktion
	_P.ChangeDim (_Size);

	if (!m_rDBO.FNewPnts()) {
	Bitmap BM (ResID (GetStyle() + MARKER1 -1));

		_P.ChangeStyle (&BM);
		Draw (&_P);
	} else {
	unsigned int uiMarker = m_rDBO.FGetIndex (GetStyle());
	CBitmapBar *pBmp = m_rDBO.GetBmp (uiMarker, _Size);
	Rectangle R = _P.BoundingBox();
	Point pt ((R.Right()-R.Left())/2, (R.Top()-R.Bottom())/2);
	// long Arithmetik, da sonst bei hohen Auflösungen Überlauffehler entstehen
#if defined(_FORCE_LEGACY_CODE)
	long res = (m_rDBO.DB().GetDBVersion() >= VERSION05000004) ? 100L : 10L;	// früher 1/10 mm, jetzt 1/100mm
#else
	long res = 100L;
#endif // defined(_FORCE_LEGACY_CODE)

	CoOrd LogPX = (CoOrd)(((long)GetDeviceCaps (_P.GetDC(), HORZRES) * (long)_Size.Width()) /
			(res * (long)GetDeviceCaps (_P.GetDC(), HORZSIZE)));
	CoOrd LogPY = (CoOrd)(((long)GetDeviceCaps (_P.GetDC(), VERTRES) * (long)_Size.Height()) / 
			(res * (long)GetDeviceCaps (_P.GetDC(), VERTSIZE)));

	long pIndex1 = PALETTEINDEX (GetNearestPaletteIndex (_P.GetPalette(), 
					(COLORREF &)GetBrushColor()));
	long pIndex2 = PALETTEINDEX (GetNearestPaletteIndex (_P.GetPalette(), 
					(COLORREF &)GetPenColor()));

	CColorBitmapObject CBMO (pt, Dimension (LogPX, LogPY), *pBmp, (Color &)pIndex2, 
				 (Color &)pIndex1, uiMarker, GetRotation());
		
//		_P.ChangeStyle (&CBMO);
		Draw (&_P);		// Hintergrund zeichnen 
		DrawEx (&CBMO, (DWORD)(void *)_P.GetPalette());
	}

// Ende der ZeichenAktion
	:: EndPaint (Handle(), &_ps);
}

void LineColorBox :: Expose (ExposeEvt) 
{
	m_L.GetDC() = :: BeginPaint (Handle(), &_ps);
	Draw (&m_L);
	:: EndPaint (Handle(), &_ps);
}

void AreaColorBox :: Expose (ExposeEvt) 
{
	_R.GetDC() = :: BeginPaint (Handle(), &_ps);

	if (m_fIsOpaque) {
	// Füllfarbe über Palette abbilden
	long pIndex = PALETTEINDEX (GetNearestPaletteIndex (_R.GetPalette(), 
							    (COLORREF &)GetBrushColor()));
		_R.SetBkColor ((Color &)pIndex);
	} else
		_R.SetBkColor (Color ((ColorVal)255, (ColorVal)255, (ColorVal)255));
		
	Draw (&_R);
	:: EndPaint (Handle(), &_ps);
}


// Passenden Pen/Brush generieren ---------------------------------------------
pPen ColorBox :: MakePen (Color, Color) 
{
	return NULL;	// standardmäßig kein eigener Pen
}

#if defined(OLDVISINFO)
pPen LineColorBox :: MakePen (Color C) 
#else
pPen LineColorBox :: MakePen (Color C, Color)
#endif // OLDVISINFO
{
short locWidth = _Width;

#if defined(_FORCE_LEGACY_CODE)
	if (m_rDBO.DB().GetDBVersion() >= VERSION05000004)
#endif // defined(_FORCE_LEGACY_CODE)
	// LinienDicke in 1/100 mm
		locWidth = (short)( ( (long)locWidth * (long)_DotsPerMM.Width() ) / 100L );

	if (locWidth > 1 && _Style == SolidLine)
		_Style = InsideFrameLine;

	if (_Style < (short)InsideFrameLine)
		C = _PenColor;		// NormalFarbe

	return new ExtPen ((StdLineStyle)_Style, locWidth, C);
}

#if defined(OLDVISINFO)
pPen AreaColorBox :: MakePen (Color CPen) 
#else
pPen AreaColorBox :: MakePen (Color CPen, Color colBrsh) 
#endif
{
#if defined(_FORCE_LEGACY_CODE)
	if (m_rDBO.DB().GetDBVersion() < VERSION05000004) 
		return new ExtPen (InsideFrameLine, 1, _PenColor);
	else
#endif // defined(_FORCE_LEGACY_CODE)
	{
	int locWidth = (int)( ( (long)(_Style/100) * (long)_DotsPerMM.Width() ) / 100L );
	
#if !defined(OLDVISINFO)
		if (GetBkConture()) 
			return new ExtPen (InsideFrameLine, locWidth, colBrsh);
		else
#endif // OLDVISINFO
			return new ExtPen (InsideFrameLine, locWidth, CPen);
	} 
}

pBrush ColorBox :: MakeBrush (Color, Color, HPALETTE, Bitmap **) 
{
	return NULL;	// standardmäßig kein eigener Brush
}

pBrush PointColorBox :: MakeBrush (Color C, Color, HPALETTE, Bitmap **) 
{
	return new Brush (C, SolidHatch);
}


pBitmap CreateColorPattern (HDC, HPALETTE, uint, Color, Color);

pBrush AreaColorBox :: MakeBrush (Color CBr, Color CPen, HPALETTE hPal, Bitmap **ppBmp) 
{
short iStyle = short(_Style % 100);
Brush *pBrush = NULL;

	if (NULL != ppBmp) 
		*ppBmp = NULL;		// erst mal null setzen
	if (iStyle > 0) {
		DELETE_OBJ (_pBM);		// für alle Fälle freigeben
		
		if ((StdHatchStyle)(iStyle-1) > DiagonalCrossHatch) {

			if (m_fIsOpaque) {
			HWND hWnd = Handle ();
			HDC hDC = GetDC (hWnd);
			HPALETTE hOldPal;

				if (hPal) {
					hOldPal = SelectPalette (hDC, hPal, FALSE);
					RealizePalette (hDC);
				}

				_pBM = CreateColorPattern (hDC, hPal, iStyle + FIRSTFILLBMP, CPen, CBr);

				if (hPal) SelectPalette (hDC, hOldPal, FALSE);
				ReleaseDC (hWnd, hDC);

			// resultierenden Pinsel erstellen
				if (NULL != _pBM) {
					TX_TRY(pBrush = new Brush (_pBM));
				}
	
			} else {
				TX_TRY(_pBM = new Bitmap(ResID(iStyle + FIRSTFILLBMP)));

			// resultierenden Pinsel erstellen (hier: Füllfarbe)
				if (NULL != _pBM) {
					TX_TRY(pBrush = new Brush (CBr, SolidHatch));
					if (NULL != ppBmp) 
						*ppBmp = _pBM;
				}
			}

			if (_pBM == NULL) return NULL;

		} else {
			TX_TRY(pBrush = new Brush (m_fIsOpaque ? CPen : CBr, (StdHatchStyle)(iStyle -1)));
		}
	} else {
		DELETE_OBJ(_pBM);
		TX_TRY(pBrush = new Brush (WhiteBrush));
	}

	return pBrush;
}


// Destruktor -----------------------------------------------------------------
void ColorBox :: ResetAttributes (void) 
{
// ZeichenAttribute freigeben
pPen pP = R().ChangePen (NULL);		// eingestellten Pen holen

	if (pP) {
		delete (ExtPen *)pP;		// und freigeben
		pP = NULL;
	}

pBrush pB = R().ChangeBrush (NULL);	// eingestellten Brush holen

	DELETE_OBJ (pB);		// freigeben

HPALETTE hOldPal = R().SetPalette (NULL);	// Palette wieder freigeben

	if (hOldPal != NULL)
		DeleteObject (hOldPal);
}

ColorBox :: ~ColorBox (void) 
{
// Control freigeben
	delete (FixedText *)GetControl ();
}


// EventDispatcher für ColorBox -----------------------------------------------

#include <palchevt.hxx>		// PaletteChangeEvt

long EXPORTTRIAS ColorBox :: Dispatch (Event e) 
{
HWND hWnd = Handle();	// FensterHandle
int i = 0;

	switch (e.Msg()) {
	case WM_PALETTEISCHANGING:
		return FALSE;

	case WM_PALETTECHANGED:
		{
		HPALETTE hPal = R().GetPalette();

			if (hPal != NULL && hWnd != ((PaletteChangeEvt &)e).hPalChgWnd()) {
			HDC hDC = GetDC (hWnd);
			HPALETTE hOldPal = SelectPalette (hDC, hPal, 0);
			
				i = RealizePalette (hDC);
				if (i) 
					UpdateColors (hDC);
				SelectPalette (hDC, hOldPal, 0);
				ReleaseDC (hWnd, hDC);
				return TRUE;
			}
		}	
		return FALSE;

	case WM_QUERYNEWPALETTE:
		{
		HPALETTE hPal = R().GetPalette();

			if (hPal == NULL) return FALSE;

		HDC hDC = GetDC (hWnd);
		HPALETTE hOldPal = SelectPalette (hDC, hPal, 0);
			
			i = RealizePalette (hDC);
			SelectPalette (hDC, hOldPal, 0);
			ReleaseDC (hWnd, hDC);
			if (i) InvalidateRect (hWnd, (LPRECT)NULL, 1);
		}	
		break;

	default:
		return ControlWindow :: Dispatch (e);
	}

return TRUE;
}
