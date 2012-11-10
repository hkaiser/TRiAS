// RectangleObjekt, welches eigenes Draw besitzt ------------------------------
// File: PALRECT.HXX

#if !defined(_PALRECT_HXX)
#define _PALRECT_HXX

const short PALVERSION = 0x300;

class PaletteRectangleObject : 
	public RectangleObject 
{
protected:
	HPALETTE _hPal;		// Palette, mit der Farben abgeglichen sind
	pWindow _pW;		// ParentWindow

	pPen GetPen (void) { return mypen; }
	pBrush GetBrush (void) { return mybrush; }

	HDC _hDC;		// DeviceContext des Rechtecks

public:
// Konstruktor/Destruktor
		PaletteRectangleObject (pWindow pW, Point P, Dimension D, 
					pPen pP = NULL, pBrush pB = NULL, 
					HPALETTE hPal = NULL);
		~PaletteRectangleObject (void);

// Memberfunktionen
	HPALETTE SetPalette (HPALETTE newPal);
	HPALETTE GetPalette (void);
	HPALETTE MakePalette (Color, Color);

virtual void ChangeBitmap (Bitmap *pBmp) {}

	HDC &GetDC (void) { return _hDC; }
};

class PointPaletteRectObject : 
	public PaletteRectangleObject 
{
protected:
	void Draw (void);
	Dimension _Size;	// PunktSymbolGröße
	pBitmap _pBM;			// aktuelle Bitmap (alte Punktsymbole)
	CColorBitmapObject *m_pCBO;	// Bitmaps für neue Punktsymbole

public:
// Konstruktor/Destruktor
		PointPaletteRectObject (pWindow, Point, Dimension);
		~PointPaletteRectObject (void);

// sonstige Member
	void ChangeDim (Dimension D) { _Size = D; }
	void ChangeStyle (pBitmap pBM) { _pBM = pBM; m_pCBO = NULL; }
	void ChangeStyle (CColorBitmapObject *pCBO) { m_pCBO = pCBO; _pBM = NULL; }
};

class LinePaletteRectObject : 
	public PaletteRectangleObject 
{
protected:
	void Draw (void);

public:
// Konstruktor/Destruktor
		LinePaletteRectObject (pWindow, Point, Dimension);
		~LinePaletteRectObject (void);
};

class AreaPaletteRectObject : 
	public PaletteRectangleObject 
{
private:
	Color m_BkCol;
	Bitmap *m_pBM;
	
protected:
	void Draw (void);
	void DrawTransparentWithPattern (void);
	void DrawNormal (bool fForceHollow = false);

public:
// Konstruktor/Destruktor
		AreaPaletteRectObject (pWindow, Point, Dimension);
		~AreaPaletteRectObject (void);
		
	void SetBkColor (Color C) { m_BkCol = C; }
	Color GetBkColor (void) { return m_BkCol; }
	void ChangeBitmap (Bitmap *pBmp) { m_pBM = pBmp; }
};

#endif	// _PALRECT_HXX
