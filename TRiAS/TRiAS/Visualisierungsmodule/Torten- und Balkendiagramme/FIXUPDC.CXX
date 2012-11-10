// Initialisieren und Aufräumen eines hDC -------------------------------------
// File: FIXUPDC.CXX

#include "tortenp.hxx"

#include "fixupdc.hxx"


// HilfsFunktion, bildet Farbe über Palette ab --------------------------------
inline void ConvertColor (HPALETTE hPal, Color &C)
{
	if (hPal && C.Reserved() == 0) {
	PALETTEENTRY *pCRef = (PALETTEENTRY *)&C;
	long lIndex = PALETTEINDEX(GetNearestPaletteIndex (hPal, *(COLORREF *)pCRef));
	
		C = *(Color *)&lIndex;
	}
}


CFixupDC :: CFixupDC (HDC hDC, HPALETTE hPal, FVisInfo *pFVI)
{
	m_hDC = hDC;

// Farben über Palette abbilden
	if (hPal) {
		ConvertColor (hPal, pFVI -> PrimColor());
		ConvertColor (hPal, pFVI -> SecColor());
	}
		
// Pen und Brush bilden
	if (pFVI -> Type() > 0) 
		m_pBrush = new Brush (pFVI -> SecColor(), (StdHatchStyle)(pFVI -> Type() -1));
	else
		m_pBrush = new Brush (HollowBrush);
	m_pPen = new Pen (InsideFrameLine, 1, pFVI -> PrimColor());
	
// Palette in hDC abbilden
	if (hPal) {
		m_hPal = SelectPalette (m_hDC, hPal, FALSE);
		m_fSelPal = TRUE;
		RealizePalette (m_hDC);
	} else
		m_fSelPal = FALSE;
		
	if (m_pPen) m_hPen = (HPEN)SelectObject (m_hDC, m_pPen -> Handle());
	if (m_pBrush) m_hBrush = (HBRUSH)SelectObject (m_hDC, m_pBrush -> Handle());
	
// HintergrundMode einstellen
	if (pFVI -> isOpaque())
		m_iBkMode = SetBkMode (m_hDC, OPAQUE);
	else
		m_iBkMode = SetBkMode (m_hDC, TRANSPARENT);
		
}


CFixupDC :: ~CFixupDC (void)
{
// Pen freigeben
	if (m_pPen) {
		SelectObject (m_hDC, m_hPen);
		delete m_pPen;
	}
		
// Brush freigeben
	if (m_pBrush) {
		SelectObject (m_hDC, m_hBrush);
		delete m_pBrush;
	}

// Palette freigeben
	if (m_fSelPal) SelectPalette (m_hDC, m_hPal, FALSE);
	
// HintergrundMode zurücksetzen
	SetBkMode (m_hDC, m_iBkMode);
}

