// Routinen für Markierungszeichen
// File: MARKER.CXX
// W. Mörtl


#include "geoeditp.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



// --------------------------------------------------------------------------------------------
// Konstruktor
#if defined (MSCC8)
#pragma warning (disable: 4355)	// Ausschalten von uninteressanten Warnungen
#endif
Marker :: Marker (Point& MPt, short mg, uchar GW, long lONr)
		: _P (SolidLine, 1, Color ((ColorVal)GW, (ColorVal)GW, (ColorVal)GW)),
		  _B (Brush (BLACK)),
		  RectangleObject (Point (MPt.X()-mg/2, MPt.Y()-mg/2), Dimension(mg,mg), &_P, &_B)
{
	_lONr = lONr;	// lONr = 0 ist möglich, wenn eben keine Objektnummer übergeben wird
}
#if defined (MSCC8)
#pragma warning (default: 4355)
#endif


// --------------------------------------------------------------------------------------------
// Destruktor
Marker :: ~Marker (void)
{
}


// --------------------------------------------------------------------------------------------
// Memberfunktionen
void Marker :: Process (Point newPt) 
{
	// pt ist Member von RectangleObject : ShapeObject : DrawObject, u. z. der linke untere
	// Punkt dim ist Member von RectangleObject : ShapeObject
	pt.X() = newPt.X() - dim.Width()/2;
	pt.Y() = newPt.Y() - dim.Height()/2;
}


// --------------------------------------------------------------------------------------------
// Mittelpunkt des Markierungsquadrates
Point Marker :: GetMPoint (void)
{	
	// dim ist Member von RectangleObject : ShapeObject
	return Point (pt.X() + dim.Width()/2, pt.Y() + dim.Height()/2);
}


// --------------------------------------------------------------------------------------------
void Marker :: SetMPoint (Point Pt)
{
	pt.X() = Pt.X() - dim.Width()/2;
	pt.Y() = Pt.Y() - dim.Height()/2;
}


// ------------------------------------------------------------------------------------------------
Rectangle Marker :: newR (void)
{
	return Rectangle (pt.Y()+dim.Height(), pt.X(), pt.Y(), pt.X()+dim.Width());
}
