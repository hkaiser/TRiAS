// Klassendefinitionen fuer ShiftrectangleObject ------------------------------
// File: SHIFT.HXX

#if !defined(_SHIFT_HXX)
#define _SHIFT_HXX

class ShiftRectangleObject : public RectangleObject, public CDragObject {
protected:
	Point _Pt;	// Bezugspunkt
	long _ONr;	// ObjektNummer des Textes

	Pen _P;
	Brush _B;
	Rectangle _R;	// altes Rechteck;

	bool m_fControl;	// letzter Zustand der Strg-Taste
	bool m_fChanged;	// DirtyFlag

#if !defined(WIN16)
	bool m_fAdjustPointer;
	Pointer *m_pOldPtr;
	Pointer *m_pShiftPtr;
	Pointer *m_pCopyPtr;
	Window *m_pW;

public:
	bool AdjustPointer (void);
	bool ResetPointer (void);

#endif // WIN16

public:
// Konstruktor
		ShiftRectangleObject (Point &Pt, long ONr, Rectangle &R, pWindow pW = NULL);
		~ShiftRectangleObject (void);

	void Process (Point Pt);
	void ProcessKey (KeyEvt);			// TastenDruck verarbeiten
	bool ToProcessKey (void);
	bool isDirty (void);

	long ONr (void) { return _ONr; }
	Rectangle oldR (void) { return _R; }
	bool isNull() { return dim.Width() == 0 || dim.Height() == 0; }
	bool isValidDragObject() { return !isNull(); }

	DRAGTYPE isA (void); // { return DT_SHIFTRECTANGLE; }
};

#endif // _SHIFT_HXX
