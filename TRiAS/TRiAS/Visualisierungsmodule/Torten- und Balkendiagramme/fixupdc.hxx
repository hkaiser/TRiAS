// Initialisieren und Aufräumen eines hDC -------------------------------------
// File: FIXUPDC.HXX


#if !defined(_FIXUPDC_HXX)
#define _FIXUPDC_HXX

class CFixupDC {
private:
	HDC 		m_hDC;		// zu behandelnder hDC
	HPEN 		m_hPen;
	HBRUSH 		m_hBrush;
	HPALETTE	m_hPal;
	Brush		*m_pBrush;
	Pen		*m_pPen;
	short 		m_iBkMode;	// HinterGrundMode
	
	unsigned short 	m_fSelPal : 1;
		
public:
		CFixupDC (HDC hDC, HPALETTE hPal, FVisInfo *pFVI);
		~CFixupDC (void);
};


#endif // _FIXUPDC_HXX
