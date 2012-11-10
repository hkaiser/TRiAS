// Objekt, welches die Füllparameter verwaltet --------------------------------
// File: FILLPARM.H

#if !defined(_FILLPARM_H)
#define _FILLPARM_H

const long DEFAULT_STEP = 200;		// Standard: 2mm Schrittweite

class CFillParams {
private:
	HDC m_hDC;			// TargetDC, auf dem ausgegeben wird
	long m_lOffset;		// Offset zum Bezugspunkt
	long m_lStep;		// Schrittweite zwischen Schraffurlinien
	long m_lWidth;		// SchraffurLinienBreite

	CSize m_sizeDots;
	double m_dScale;

public:
// Konstruktor/Destruktor
	CFillParams (HDC hDC);
	~CFillParams (void);

public:
// Implementation
	HRESULT ParseVisString (LPCSTR pVisStr);

// Umrechnen eines Maßes bezogen auf hDC und Maßstab
inline long ScaleX (long lToScale)
	{ return (long)((m_sizeDots.cx * lToScale) / (100 * m_dScale)); }
inline long ScaleY (long lToScale)
	{ return (long)((m_sizeDots.cy * lToScale) / (100 * m_dScale)); }

// Liefert Parameter in Pixel des aktuellen DC's bezogen auf X-Richtung
	long GetStepOnDC_X (void);
inline long GetOffsetOnDC_X (void) { return ScaleX (m_lOffset); }
inline long GetWidthOnDC_X (void) { return ScaleX (m_lWidth); }

// Liefert Parameter in Pixel des aktuellen DC's bezogen auf Y-Richtung
	long GetStepOnDC_Y (void);
inline long GetOffsetOnDC_Y (void) { return ScaleY (m_lOffset); }
inline long GetWidthOnDC_Y (void) { return ScaleY (m_lWidth); }
};

#endif // _FILLPARM_H
