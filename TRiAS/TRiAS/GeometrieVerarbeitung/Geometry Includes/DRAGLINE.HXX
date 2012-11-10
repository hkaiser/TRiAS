// Klasse für das Nachführen einer Linie
// File: DRAGLINE.HXX
// H. Kaiser

#if !defined(_DRAGLINE_HXX)
#define _DRAGLINE_HXX


class DragLineObject : public LineObject
{
public:
// Konstruktor
		DragLineObject (Point Pt) : LineObject (Pt, Pt, NULL) {}

// Member
	void Process (Point Pt) { end = Pt; }	// end ist Member von LineObject
};

#endif	// _DRAGLINE_HXX
