// ShiftRectangleObject fuer SchriftObjekte -----------------------------------
// File: SHIFT.CXX

#include "editobjp.hxx"

#include "shift.hxx"

// Memberfunktionen -----------------------------------------------------------
ShiftRectangleObject :: ShiftRectangleObject (Point &Pt, long ONr, 
					      Point &RcPt, Dimension &RcDim) 
		      : _P (SolidLine, 1, Color ((ColorVal)128, (ColorVal)128, (ColorVal)128)),
			_B (ClearBrush),
			RectangleObject (RcPt, RcDim, &_P, &_B)
{
	_Pt = Pt;			// Bezugspunkt merken
	_ONr = ONr;			// ObjektNummer merken
	_R = Rectangle (RcPt.Y()+RcDim.Height(), RcPt.X(),
			RcPt.Y(), RcPt.X()+RcDim.Width());
	_hMenu = 0;
}


void ShiftRectangleObject :: Process (Point newPt) 
{
	pt.X() += (newPt.X() - _Pt.X());
	pt.Y() += (newPt.Y() - _Pt.Y());
	_Pt = newPt;
}

Point ShiftRectangleObject :: newPos (void)
{
	return Point (pt.X() + dim.Width()/2, pt.Y() + dim.Height()/2);
}

Rectangle ShiftRectangleObject :: newR (void)
{
	return Rectangle (pt.Y()+dim.Height(), pt.X(), pt.Y(), pt.X()+dim.Width());
}
