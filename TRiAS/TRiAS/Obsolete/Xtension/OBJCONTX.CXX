// ObjContainer fuer Erweiterungen --------------------------------------------
// File: OBJCONTX.CXX

#include "xtensnp.hxx"

#include <objcontx.hxx>

// Methoden für OBJECTCONTAINER -----------------------------------------------
// Konstruktoren
ObjContainer :: ObjContainer (KoOrd XMin, KoOrd XMax, KoOrd YMin, KoOrd YMax) 
{
	_XMin = XMin; _XMax = XMax;
	_YMin = YMin; _YMax = YMax;
}

ObjContainer :: ObjContainer (Punkt Pt1, Punkt Pt2) 
{
	_XMin = Pt1.X(); _XMax = Pt2.X();
	_YMin = Pt1.Y(); _YMax = Pt2.Y();
}

ObjContainer :: ObjContainer (const ObjContainer &OC) 
{
	_XMin = OC._XMin; _XMax = OC._XMax;
	_YMin = OC._YMin; _YMax = OC._YMax;
}

// Memberfunktionen
ObjContainer ObjContainer :: InflateCont (short Percent) 
{
// Werte, um die Container vergrößert werden soll
	KoOrd dX = ((XMax()-XMin())*Percent)/200;
	KoOrd dY = ((YMax()-YMin())*Percent)/200;

return ObjContainer (XMin()-dX, XMax()+dX, YMin()-dY, YMax()+dY);
}


// Verschnitt zweier ObjContainer testen --------------------------------------
Bool ObjContainer :: operator ^ (ObjContainer &OC) 
{
	if (XMin() > OC.XMax() || XMax() < OC.XMin() ||
	    YMin() > OC.YMax() || YMax() < OC.YMin()) 
	// ObjContainer berschneiden sich nicht
		return FALSE;

return TRUE;
}

// Gemeinsamen Container berechnen --------------------------------------------
ObjContainer &ObjContainer :: operator + (ObjContainer &OC) 
{
	if (XMin() > OC.XMin()) XMin() = OC.XMin();
	if (XMax() < OC.XMax()) XMax() = OC.XMax();
	if (YMin() > OC.YMin()) YMin() = OC.YMin();
	if (YMax() < OC.YMax()) YMax() = OC.YMax();

return *this;
}

void ObjContainer :: operator += (ObjContainer &OC) 
{
	if (XMin() > OC.XMin()) XMin() = OC.XMin();
	if (XMax() < OC.XMax()) XMax() = OC.XMax();
	if (YMin() > OC.YMin()) YMin() = OC.YMin();
	if (YMax() < OC.YMax()) YMax() = OC.YMax();
}

// Liefert, ob der erste der ObjContainer vollständig innerhalb des 
// Zweiten liegt
Bool operator < (ObjContainer &O1, ObjContainer &O2)
{
	return (O1.XMin() > O2.XMin() && O1.XMax() < O2.XMax() &&
		O1.YMin() > O2.YMin() && O1.YMax() < O2.YMax());
}

// Liefert, ob der erste der ObjContainer vollständig außerhalb des 
// Zweiten liegt
Bool operator > (ObjContainer &O1, ObjContainer &O2)
{
	return (O1.XMin() < O2.XMin() && O1.XMax() > O2.XMax() &&
		O1.YMin() < O2.YMin() && O1.YMax() > O2.YMax());
}


// ObjContainer aus einem Rechteck entspr. aktuellem Ausschnitt berechnen -----
ObjContainer ObjContainer :: operator = (Rectangle &R) 
{
COORDCONVERT CC;
Point Pt1 = Point (R.Left(), R.Bottom());
Point Pt2 = Point (R.Right(), R.Top());
Punkt Pkt1, Pkt2;

	CC.lpPt = (POINT *)&Pt1;
	CC.lpPkt = (long *)&Pkt1;
	DEX_DCtoOC (CC);

	CC.lpPt = (POINT *)&Pt2;
	CC.lpPkt = (long *)&Pkt2;
	DEX_DCtoOC (CC);

	XMin() = Pkt1.X(); YMin() = Pkt1.Y();
	XMax() = Pkt2.X(); YMax() = Pkt2.Y();

return *this;
}

// Aus ObjConatiner Rechteck entsprechend aktuellem Ausschnitt berechnen ------
ObjContainer :: operator Rectangle (void) 
{
Punkt Pkt1 = Punkt (XMin(), YMin());
Punkt Pkt2 = Punkt (XMax(), YMax());
Point Pt1, Pt2;
COORDCONVERT CC;

	CC.lpPt = (POINT *)&Pt1;
	CC.lpPkt = (long *)&Pkt1;
	DEX_OCtoDC (CC);

	CC.lpPt = (POINT *)&Pt2;
	CC.lpPkt = (long *)&Pkt2;
	DEX_OCtoDC (CC);

return Rectangle (Pt2.Y(), Pt1.X(), Pt1.Y(), Pt2.X());	// tlbr
}

