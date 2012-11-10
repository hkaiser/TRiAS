// Klasse für ein achsenparalleles Kreuz
// File: CrossObject.cpp
// W. Mörtl


#include "GeoEditP.h"

#include "CrossObject.h"


///////////////////////////////////////////////////////////////////////////////////////////////
CrossObject::CrossObject (Point ptCentre, Dimension dim, pPen pen)
{
	pt = ptCentre;
	m_b = dim.Width() / 2;
	m_h = dim.Height() / 2;
	m_pMyPen = pen;
}


///////////////////////////////////////////////////////////////////////////////////////////////
void CrossObject::DrawEx (DWORD dw)
{
LineObject lo1 (Point(pt.X()-m_b, pt.Y()), Point(pt.X()+m_b, pt.Y()), m_pMyPen);
LineObject lo2 (Point(pt.X(), pt.Y()-m_h), Point(pt.X(), pt.Y()+m_h), m_pMyPen);

	if (ROP_Invert == dw)
	{
		lo1.ChangeRop (ROP_Invert);
		lo2.ChangeRop (ROP_Invert);
	}

	g_pTE->MVWind()->Draw (&lo1);
	g_pTE->MVWind()->Draw (&lo2);
    g_pTE->MVWind()->Update();		// sofort zeichnen
}


// --------------------------------------------------------------------------------------------
Rectangle CrossObject::BoundingBox (void)
{
	return Rectangle (pt.Y()+m_h, pt.X()-m_b, pt.Y()-m_h, pt.X()+m_b);
}


// --------------------------------------------------------------------------------------------
Point CrossObject::ChangePosition (Point NewCentr)
{
Point OldCentr = pt;

	pt = NewCentr;

	return OldCentr;
}
