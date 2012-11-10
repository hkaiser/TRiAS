// Klasse, die erweiterten Pen repraesentiert ---------------------------------
// File: EPEN.HXX

#if !defined(_EPEN_HXX)
#define _EPEN_HXX

enum ExtLineStyle {
	SolidLineEx = 0,		// normale LinienTypen
	DashedEx = 1, 			
	DottedEx = 2, 			
	Dash_DotEx = 3, 		
	Dash_Dot_DotEx = 4, 	
	ClearLineEx = 5,		
	InsideFrameLineEx = 6,

// LinienTypen mit 80% (schwarz+Farbe)
	ExtLineStyle1 = 7,	// sw-col-sw, col = 80%
	ExtLineStyle2 = 8,	// col-sw-col, sw = 80%
	ExtLineStyle3 = 9,	// sw-col-sw-col-sw, col = 80%, sw = 15%

// LinienTypen mit 80% (weiá+Farbe)
	ExtLineStyle4 = 10,	// w-col-w, col = 80%
	ExtLineStyle5 = 11,	// col-w-col, w = 80%
	ExtLineStyle6 = 12,	// w-col-w-col-w, col = 80%, w = 15%

// LinienTypen mit 80% (schwarz+Farbe)
	ExtLineStyle7 = 13,	// col-sw-col-sw-col, col = 100%, sw = 80%, col = 15%
	ExtLineStyle8 = 14,	// col-w-col-w-col, col = 100%, w = 80%, col = 15%
};

// Struktur, die LinienTyp verschlüsselt --------------------------------------
typedef struct tagEPEN {
	short iCnt;	// Anzahl der EinzelLinien
	short *pW;	// Dicken der Linien
	short iAct;	// laufende Nummer der eingefärbten Linie
	COLORREF C;	// Farbe, die nicht geändert werden kann
	short minW;	// min Breite in Pixeln, bis zu der komplexe Darstellung erfolgt
	short fInv;	// alles auáer iAct einfärben
} EPEN;

// eigentliche erweiterte PenKlasse -------------------------------------------
class _TRIAS02_ENTRY ExtPen : public Pen {
private:
	short m_iWidth;	// GesamtBreite
	short m_iCnt;	// Anzahl der Striche übereinander
	short m_iAct;	// lfde. Nummer des gefärbten Striches (0.._iCnt-1)
	ExtLineStyle m_els;	// Typ dieses ExtPens
	short m_fInv;		// alles außer m_iAct einfärben

	pPen m_pBlackPen;	// schwarzer Stift
	Color m_locColor;	// zweite Farbe

	pPen m_pColorPen;	// farbiger Stift
	Color m_C;		// Farbe für farbigen Stift

public:
// Konstruktor
	EXPORT02 ExtPen (StdLineStyle els, short iWidth, Color C);
	EXPORT02 ~ExtPen (void);

	HPEN EXPORT02 GetHandle (short iLayer = 0);	// liefert aktuelles PenHandle
	short EXPORT02 iCnt (void) { return m_iCnt; }
	void EXPORT02 SetSecondColor (Color C) { m_locColor = C; }

	static uint EPenWidth (StdLineStyle els, short &iWidth, short &iCnt);
};

#endif // _EPEN_HXX
