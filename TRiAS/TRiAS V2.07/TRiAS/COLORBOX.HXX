// Rechteck fuer die Anzeige der aktuellen Farbauswahl ------------------------
// File: COLORBOX.HXX

#if !defined(_COLORBOX_HXX)
#define _COLORBOX_HXX

class ColorBox : 
	public ControlWindow 
{
public:
// lokale enumerators
	enum ColorBoxMode { 	CBM_Equal, 	// Randfarbe immer gleich Füllfarbe
				CBM_Different,	// Randfarbe separat einstellbar
	};
	enum ColorType {	CT_FirstColor,	// RandFarbe etc.
				CT_SecondColor,	// Füllfarbe
	};

private:
	Color _BrushColor;		// Füllfarbe
	ColorBoxMode _actCBM;		// aktueller CBM

protected:
	Color _PenColor;		// RandFarbe
	void ResetAttributes (void);	// alles zurücksetzen

	Point CanvasPoint (void);	// Lage und Größe des Controls
	Dimension CanvasDimension (void);

	short _Style;			// DarstellungsStil
	
	Dimension _DotsPerMM;		// Fensterauflösung

	PAINTSTRUCT _ps;		// PaintStruct für Beginpaint/EndPaint
	DatenBasisObjekt &m_rDBO;	// zugehöriges DatenBasisObjekt
	 
	long EXPORTTRIAS Dispatch (Event);	// zusätzliche Events behandeln

public:
// Konstruktor
		ColorBox (pDialogWindow, DatenBasisObjekt &, uint, 
			  ColorBoxMode = CBM_Equal);

// Memberfunktionen
	ColorBoxMode SetMode (ColorBoxMode newMode);
	void SetColor (Color newC, ColorType CT = CT_FirstColor);

	Color &GetPenColor (void);
	Color &GetBrushColor (void);

	short &GetStyle (void);
	
virtual PaletteRectangleObject &R (void) = 0;	//  liefert zugehöriges DrawObject
#if defined(OLDVISINFO)
virtual pPen MakePen (Color);				// generiert passenden Pen
#else
virtual pPen MakePen (Color, Color);			// generiert passenden Pen
#endif 
virtual pBrush MakeBrush (Color, Color, HPALETTE, Bitmap ** = NULL);	// generiert passenden Brush

	HWND Handle (void) { return GetControl() -> Handle (API_CONTROL_HCONTROL); }

// Destruktor
		~ColorBox (void);
};

// Klassen, die Attributdarstellung von Punkt-/Linien- und Flächenattributen
// übernehmen
class PointColorBox : 
	public ColorBox 
{
protected:
	PointPaletteRectObject _P;	// Punkt im Monitorbereich
	Dimension _Size;		// PunktGröße in 1/100mm
	short m_iRot;			// Drehwinkel;
	Color m_SecC;			// zweite Farbe

	void Expose (ExposeEvt);

public:
// Konstruktor/Destruktor
		PointColorBox (pDialogWindow, DatenBasisObjekt &, 
			       uint, Color, Dimension, short, short, Color);
		~PointColorBox (void);

	Dimension &GetSize (void);
	PaletteRectangleObject &R (void);
	short &GetRotation (void);

	pBrush MakeBrush (Color, Color, HPALETTE, Bitmap ** = NULL);
};

class LineColorBox : 
	public ColorBox 
{
protected:
	LinePaletteRectObject m_L;	// Linie im Monitorbereich
	short _Width;			// LinienDicke

	void Expose (ExposeEvt);

public:
// Konstruktor/Destruktor
		LineColorBox (pDialogWindow, DatenBasisObjekt &, 
			      uint, Color, short, short);
		~LineColorBox (void);

	short &GetWidth (void);
	PaletteRectangleObject &R (void);

#if defined(OLDVISINFO)
	pPen MakePen (Color);
#else
	pPen MakePen (Color, Color);
#endif
};

class AreaColorBox : 
	public ColorBox 
{
protected:
	AreaPaletteRectObject _R;	// Rechteck im Monitorbereich
	Bitmap *_pBM;			// evtl. FüllMuster
	unsigned short m_fIsOpaque : 1;
#if !defined(OLDVISINFO)
	unsigned short m_fBkConture : 1;	// Kontur mit Hintergrundfarbe
#endif
	
	void Expose (ExposeEvt);

public:
// Konstruktor/Destruktor
		AreaColorBox (pDialogWindow, DatenBasisObjekt &, 
			      uint, Color, Color, short);
		~AreaColorBox (void);

	PaletteRectangleObject &R (void);
#if defined(OLDVISINFO)
	pPen MakePen (Color);
#else
	pPen MakePen (Color, Color);
#endif
	pBrush MakeBrush (Color, Color, HPALETTE, Bitmap **ppBmp = NULL);
	
	void SetBkMode (bool fBkMode) { m_fIsOpaque = fBkMode ? true : false; }
#if !defined(OLDVISINFO)
	void SetBkConture (bool fBkConture) { m_fBkConture = fBkConture ? true : false; }
	bool GetBkConture (void) { return m_fBkConture; }
#endif
};

#endif // _COLORBOX_HXX
