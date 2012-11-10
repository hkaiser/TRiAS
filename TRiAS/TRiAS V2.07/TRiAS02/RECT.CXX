// Diverse Operatoren fuer Rechtecke ------------------------------------------
// File: RECT.CXX

#include "trias02p.hxx"

#include <rect.hxx>

bool operator ! (Rectangle &Rc)
{
	if (!Rc.Left() && !Rc.Right() && !Rc.Bottom() && !Rc.Top())
		return true;
	if (Rc.Right() < Rc.Left() || Rc.Top() < Rc.Bottom())
		return true;

return false;
}

bool operator ^ (Rectangle &Rc1, Rectangle &Rc2)
{
	return !((Rc1.Left() > Rc2.Right()) || (Rc1.Right() < Rc2.Left()) ||
		 (abs(Rc1.Bottom()) > abs(Rc2.Top())) || 
		 (abs(Rc1.Top()) < abs(Rc2.Bottom())));
}

Rectangle operator & (Rectangle &Rc1, Rectangle &Rc2)
{
	if (!(Rc1 ^ Rc2)) 
		return Rectangle (0, 0, 0, 0);

CoOrd XMin = max (Rc1.Left(), Rc2.Left());
CoOrd XMax = min (Rc1.Right(), Rc2.Right());
CoOrd YMin = max (Rc1.Bottom(), Rc2.Bottom());
CoOrd YMax = min (Rc1.Top(), Rc2.Top());

	return Rectangle (YMax, XMin, YMin, XMax);
}

Rectangle operator + (Rectangle &Rc1, Rectangle &Rc2)
{
CoOrd XMin = min (Rc1.Left(), Rc2.Left());
CoOrd XMax = max (Rc1.Right(), Rc2.Right());
CoOrd YMin = min (Rc1.Bottom(), Rc2.Bottom());
CoOrd YMax = max (Rc1.Top(), Rc2.Top());

	return Rectangle (YMax, XMin, YMin, XMax);
}

