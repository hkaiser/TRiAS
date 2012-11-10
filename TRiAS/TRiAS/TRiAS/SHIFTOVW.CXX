// ShiftRectangleObject fuer SelektionsRechteck -------------------------------
// File: SHIFTOVW.CXX

#include "triaspre.hxx"

#include "shiftovw.hxx"

// Memberfunktionen für Basisklasse -------------------------------------------
Rectangle SelectionObject :: newRect (void)
{
	if (dim.Width() < 0) {
		pt.X() = pt.X() + dim.Width();
		dim.Width() = -dim.Width();
	}
	if (dim.Height() < 0) {
		pt.Y() = pt.Y() + dim.Height();
		dim.Height() = -dim.Height();
	}
	if (dim.Width() == 0) dim.Width() = 1;
	if (dim.Height() == 0) dim.Height() = 1;
	
	return Rectangle (pt.Y()+dim.Height(), pt.X(), pt.Y(), pt.X()+dim.Width());
}


// Memberfunktionen für SelektionsRahmen --------------------------------------
DragRectangle :: DragRectangle (Point &ptP)
	       : SelectionObject (ptP, Dimension (0, 0))
{
	// nothing else to do
}	       

void DragRectangle :: Process (Point end) 
{
	dim = Dimension (end.X()-pt.X(), end.Y()-pt.Y());
}

void DragRectangle :: Draw (void)
{
HWND hWnd = canvas -> Handle();
HDC hDC = :: GetDC (hWnd);
int iOldRop = SetROP2 (hDC, R2_XORPEN);
HPEN hP = CreatePen (PS_SOLID, 0, RGB (0, 0, 0));
	
	hP = (HPEN)SelectObject (hDC, hP);

	DrawRectangle (hDC, pt.X(), pt.Y(), pt.X()+dim.Width(), pt.Y()+dim.Height());

	DeleteObject (SelectObject (hDC, hP));
	SetROP2 (hDC, iOldRop);
	ReleaseDC (hWnd, hDC);
}


// Memberfunktionen für SelektionsRechteck ------------------------------------
SelectionRectangle :: SelectionRectangle (Point &ptRef, RECT &rc)
		    : SelectionObject (Point (rc.left, rc.bottom), 
							   Dimension (rc.right-rc.left, rc.top-rc.bottom))
{
	m_ptRef = ptRef;	// Bezugspunkt merken
}


void SelectionRectangle :: Process (Point newPt) 
{
	pt.X() += (newPt.X() - m_ptRef.X());
	pt.Y() += (newPt.Y() - m_ptRef.Y());
	m_ptRef = newPt;
}

void SelectionRectangle :: Draw (void)
{
HWND hWnd = canvas -> Handle();
HDC hDC = ::GetDC (hWnd);
int iOldRop = SetROP2 (hDC, R2_XORPEN);
HPEN hP = CreatePen (PS_SOLID, 0, RGB (0, 0, 0));
	
	hP = (HPEN)SelectObject (hDC, hP);
	DrawRectangle (hDC, pt.X(), pt.Y()+dim.Height(), 
			pt.X()+dim.Width(), pt.Y());

	DeleteObject (SelectObject (hDC, hP));
	SetROP2 (hDC, iOldRop);
	ReleaseDC (hWnd, hDC);
}

