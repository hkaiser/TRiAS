// Initialisieren und Aufräumen eines hDC -------------------------------------
// File: FIXUPDC.CPP

#include "stdafx.h"

#include "fixupdc.h"

// HilfsFunktion, bildet Farbe über Palette ab --------------------------------
inline COLORREF ConvertColor (HPALETTE hPal, COLORREF C)
{
PALETTEENTRY CRef = (PALETTEENTRY &)C;

	if (hPal && CRef.peFlags == 0) 
		return PALETTEINDEX(GetNearestPaletteIndex (hPal, C));

return C;
}

CFixupDC :: CFixupDC (HDC hDC, HPALETTE hPal, CRgn &rRgn, 
					  FVisInfo *pFVI, CFillParams &rFP)
{
// Palette in hDC abbilden
	if (hPal) {
		m_hPal = ::SelectPalette (m_hDC, hPal, FALSE);
		::RealizePalette (m_hDC);
		m_fSelPal = true;
	} else
		m_fSelPal = false;
		
	SetOutputDC (hDC);
	m_iSavedDC = SaveDC();

// Farben über Palette abbilden
COLORREF cr1 = ConvertColor (hPal, pFVI -> PrimColor());
COLORREF cr2 = ConvertColor (hPal, pFVI -> SecColor());
		
// Pen bilden und selektieren
	m_Pen.CreatePen (PS_SOLID, rFP.GetWidthOnDC_X(), 
					 pFVI -> isOpaque() ? cr1 : cr2);
	m_pPen = SelectObject (&m_Pen);

// Brush bilden und selektieren
	m_Brush.CreateSolidBrush (cr2);

// HintergrundMode einstellen
	m_iBkMode = SetBkMode (pFVI -> isOpaque() ? OPAQUE : TRANSPARENT);

// Region selektieren
	SelectClipRgn (&rRgn, RGN_AND);
}


CFixupDC :: ~CFixupDC (void)
{
	SelectObject (m_pPen);		// Pen freigeben

// HintergrundMode zurücksetzen
	SetBkMode (m_iBkMode);

	if (m_iSavedDC) 
		RestoreDC (m_iSavedDC);
	Detach();		// DC nicht freigeben

// Palette freigeben
	if (m_fSelPal) ::SelectPalette (m_hDC, m_hPal, FALSE);
}

