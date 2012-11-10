// Klassendefinitionen fuer ShiftrectangleObject ------------------------------
// File: SHIFT.HXX

#if !defined(_SHIFT_HXX)
#define _SHIFT_HXX

class ShiftRectangleObject : public RectangleObject {
protected:
	Point _Pt;	// Bezugspunkt
	long _ONr;	// ObjektNummer des Textes

	Pen _P;
	Brush _B;
	Rectangle _R;	// altes Rechteck;

	HMENU _hMenu;

public:
// Konstruktor
		ShiftRectangleObject (Point &Pt, long ONr, Point &, Dimension &);

	void Process (Point Pt);
	long ONr (void) { return _ONr; }
	Rectangle oldR (void) { return _R; }	// altes Rechteck
	Point actPt (void) { return _Pt; }	// aktueller BezugsPunkt
	HMENU &hMenu (void) { return _hMenu; }
	Point newPos (void);			// neuer MittelPunkt
	Rectangle newR (void);			// neues umschlieáendes Rechteck
};


#endif // _SHIFT_HXX
