// Deklarationen: Markierungsquadrat
// File: Marker.h
// W. Mörtl


#ifndef _MARKER_H
#define _MARKER_H
     

class Marker : public RectangleObject
{
protected:
	long m_lONr;	// Nummer des Objektes,
	Pen m_P;		// die beiden Größen werden für die Initialisierung des
	Brush m_B;		//  Konstruktors in Marker.cpp benötigt

public:
// Konstruktor/Destruktor
		// MPt     Mittelpunkt des Markierungsquadrates
		// mg      Größe (in Pixel) des Markierungsquadrates in beiden Richtungen
		// ulGW    Randfarbe des Markierungsquadrates (nur Grauwerte möglich)
		// lONr    Objektnummer
		// C	   Füllfarbe des Markierungsquadrates
		// BoundC  Randfarbe des Markierungsquadrates
		// iThick  Stärke des (andersfarbigen) Randes		
		Marker (Point& MPt, int mg, ulong ulGW, long lONr = 0);
		Marker (Color BoundC, int iThick, Point& MPt, int mg, long lONr = 0);
		Marker (Color C, Color BoundC, int iThick, Point& MPt, int mg, long lONr = 0);
 		~Marker (void) {};

// Memberfunktionen
	long ONr (void) { return m_lONr; }

	// pt ist Member von RectangleObject : ShapeObject : DrawObject, u. z. der linke untere
	// Punkt des Markierungsquadrates
	Point RecPoint (void) { return pt; }
	Dimension RecDim (void) { return dim; }	// dim ist Member von RectangleObject : ShapeObject
	void Process (Point Pt);
	Point GetMPoint (void);			// MittelPunkt
	void SetMPoint (Point Pt);
	Rectangle newR (void);			// neues umschließendes Rechteck
	void SetFillColor (Color colNewColor);
};

#endif // _MARKER_H
