// Klassendefinitionen fuer SelektionsObjekte ---------------------------------
// File: SHIFTOVW.HXX

#if !defined(_SHIFTOVW_HXX)
#define _SHIFTOVW_HXX

enum SelRectType {
	SELRECT_NEWRECT = 0,
	SELRECT_SHIFTRECT = 1,
};

class SelectionObject : public RectangleObject {
public:
		SelectionObject (Point ptP, Dimension dimD)
			: RectangleObject (ptP, dimD, NULL, NULL) {}
		
virtual SelRectType isA (void) = 0;

	Rectangle newRect (void);
};


class DragRectangle : public SelectionObject {
public:
		DragRectangle (Point &pt);
		
	void Process (Point Pt);
	void Draw (void);
	SelRectType isA (void) { return SELRECT_NEWRECT; }
};


class SelectionRectangle : public SelectionObject {
protected:
	Point m_ptRef;	// Bezugspunkt

public:
// Konstruktor
		SelectionRectangle (Point &ptRef, RECT &rc);

	void Process (Point Pt);
	void Draw (void);
	SelRectType isA (void) { return SELRECT_SHIFTRECT; }
};


#endif // _SHIFTOVW_HXX
