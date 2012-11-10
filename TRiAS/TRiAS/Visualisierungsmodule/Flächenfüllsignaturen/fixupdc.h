// Initialisieren und Aufräumen eines hDC -------------------------------------
// File: FIXUPDC.H

#if !defined(_FIXUPDC_H)
#define _FIXUPDC_H

class CFixupDC : public CDC {
private:
	int			m_iSavedDC;		// Wert für RestoreDC
	CPen		m_Pen;			// verwendeter Pen
	CPen *		m_pPen;			// vorheriger Pen
	CBrush		m_Brush;		// verwendeter Brush

	HPALETTE	m_hPal;			// vorherige Palette

	int 		m_iBkMode;		// HinterGrundMode
	unsigned short 	m_fSelPal : 1;
		
public:
		CFixupDC (HDC hDC, HPALETTE hPal, CRgn &rRgn, 
				  FVisInfo *pFVI, CFillParams &rFP);
		~CFixupDC (void);

	void CFixupDC::FillRect (LPCRECT prcRect)
		{ CDC::FillRect (prcRect, &m_Brush); }
};

#endif // _FIXUPDC_H
