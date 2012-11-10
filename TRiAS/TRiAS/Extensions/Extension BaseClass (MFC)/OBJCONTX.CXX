// ObjContainer fuer Erweiterungen --------------------------------------------
// File: OBJCONTX.CXX

#include "xtensnp.hxx"

#include <objcontx.hxx>

#if defined(_DEBUG) && defined(WIN32)
#if defined(__MFC__)
#define new DEBUG_NEW
#endif // __MFC__
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if _TRiAS_VER >= 0x0300

///////////////////////////////////////////////////////////////////////////////
// Methoden für OBJECTCONTAINER 

// Konstruktoren
ObjContainer :: ObjContainer (KoOrd XMin, KoOrd XMax, KoOrd YMin, KoOrd YMax) 
{
	if (XMin < XMax) {
		SetXMin(XMin); 
		SetXMax(XMax);
	} else {
		SetXMin(XMax); 
		SetXMax(XMin);
	}
	if (YMin < YMax) {
		SetYMin(YMin); 
		SetYMax(YMax);
	} else {
		SetYMin(YMax); 
		SetYMax(YMin);
	}
}

ObjContainer :: ObjContainer (Punkt Pt1, Punkt Pt2) 
{
KoOrd XMin = Pt1.GetX(); 
KoOrd XMax = Pt2.GetX();
KoOrd YMin = Pt1.GetY(); 
KoOrd YMax = Pt2.GetY();

	if (XMin < XMax) {
		SetXMin(XMin); 
		SetXMax(XMax);
	} else {
		SetXMin(XMax); 
		SetXMax(XMin);
	}
	if (YMin < YMax) {
		SetYMin(YMin); 
		SetYMax(YMax);
	} else {
		SetYMin(YMax); 
		SetYMax(YMin);
	}
}

ObjContainer :: ObjContainer (const ObjContainer &OC) 
{
	SetXMin (OC.XMin()); 
	SetXMax (OC.XMax());
	SetYMin (OC.YMin()); 
	SetYMax (OC.YMax());
}

// Memberfunktionen
ObjContainer ObjContainer :: InflateCont (int iPercent) 
{
// Werte, um die Container vergrößert werden soll 
KoOrd dXMin = XMin();
KoOrd dXMax = XMax();
KoOrd dYMin = YMin();
KoOrd dYMax = YMax();
KoOrd dX = ((dXMax-dXMin)*iPercent)/200;
KoOrd dY = ((dYMax-dYMin)*iPercent)/200;

	return ObjContainer (dXMin-dX, dXMax+dX, dYMin-dY, dYMax+dY);
}


// Verschnitt zweier ObjContainer testen --------------------------------------
bool ObjContainer :: operator ^ (ObjContainer &OC) 
{
	if (XMin() > OC.XMax() || XMax() < OC.XMin() ||
		YMin() > OC.YMax() || YMax() < OC.YMin()) 
	{
	// ObjContainer überschneiden sich nicht
		return false;
	}
	return true;
}

// Gemeinsamen Container berechnen --------------------------------------------
ObjContainer ObjContainer :: operator + (ObjContainer &OC) const
{
KoOrd lXMin = XMin();
KoOrd lXMax = XMax();
KoOrd lYMin = YMin();
KoOrd lYMax = YMax();

	if (XMin() > OC.XMin()) lXMin = OC.XMin();
	if (XMax() < OC.XMax()) lXMax = OC.XMax();
	if (YMin() > OC.YMin()) lYMin = OC.YMin();
	if (YMax() < OC.YMax()) lYMax = OC.YMax();

	return ObjContainer(lXMin, lXMax, lYMin, lYMax);
}

void ObjContainer :: operator += (ObjContainer &OC) 
{
// zuerst die Maximalwerte behandeln (CSRect ist intern Punkt + Ausdehnung)
	if (XMax() < OC.XMax()) SetXMax(OC.XMax());
	if (XMin() > OC.XMin()) SetXMin(OC.XMin());
	if (YMax() < OC.YMax()) SetYMax(OC.YMax());
	if (YMin() > OC.YMin()) SetYMin(OC.YMin());
}

// Liefert, ob der erste der ObjContainer vollständig innerhalb des 
// Zweiten liegt
bool operator < (ObjContainer &O1, ObjContainer &O2)
{
	return (O1.XMin() > O2.XMin() && O1.XMax() < O2.XMax() &&
			O1.YMin() > O2.YMin() && O1.YMax() < O2.YMax());
}

// Liefert, ob der erste der ObjContainer vollständig außerhalb des 
// Zweiten liegt
bool operator > (ObjContainer &O1, ObjContainer &O2)
{
	return (O1.XMin() < O2.XMin() && O1.XMax() > O2.XMax() &&
			O1.YMin() < O2.YMin() && O1.YMax() > O2.YMax());
}

#if defined(__CV__)

// ObjContainer aus einem Rechteck entspr. aktuellem Ausschnitt berechnen -----
ObjContainer ObjContainer :: operator = (Rectangle &R) 
{
COORDCONVERT CC;
POINT Pt1; Pt1.x = R.Left(); Pt1.y = R.Bottom();
POINT Pt2; Pt2.x = R.Right(); Pt2.y = R.Top();
Punkt Pkt1, Pkt2;

	CC.lpPt = &Pt1;
	CC.lpPkt = (long *)&Pkt1;
	DEX_DCtoOC (CC);

	CC.lpPt = &Pt2;
	CC.lpPkt = (long *)&Pkt2;
	DEX_DCtoOC (CC);

	SetXMin(Pkt1.GetX());
	SetYMin(Pkt1.GetY());
	SetXMax(Pkt2.GetX()); 
	SetYMax(Pkt2.GetY());

	return *this;
}

// Aus ObjConatiner Rechteck entsprechend aktuellem Ausschnitt berechnen ------
ObjContainer :: operator Rectangle (void) 
{
Punkt Pkt1 = Punkt (XMin(), YMin());
Punkt Pkt2 = Punkt (XMax(), YMax());
POINT Pt1, Pt2;
COORDCONVERT CC;

	CC.lpPt = &Pt1;
	CC.lpPkt = (long *)&Pkt1;
	DEX_OCtoDC (CC);

	CC.lpPt = &Pt2;
	CC.lpPkt = (long *)&Pkt2;
	DEX_OCtoDC (CC);

	return Rectangle (Pt2.y, Pt1.x, Pt1.y, Pt2.x);	// tlbr
}

#else

// Aus ObjConatiner Rechteck entsprechend aktuellem Ausschnitt berechnen ------
ObjContainer :: operator RECT (void) 
{
POINTL Pkt1; Pkt1.x = XMin(); Pkt1.y = YMin();
POINTL Pkt2; Pkt2.x = XMax(); Pkt2.y = YMax();
POINT Pt1, Pt2;
COORDCONVERT CC;

	CC.lpPt = (POINT *)&Pt1;
	CC.lpPkt = (long *)&Pkt1;
	DEX_OCtoDC (CC);

	CC.lpPt = (POINT *)&Pt2;
	CC.lpPkt = (long *)&Pkt2;
	DEX_OCtoDC (CC);

RECT rc;

	SetRect (&rc, Pt1.x, Pt2.y, Pt2.x, Pt1.y);	// ltrb
	return rc;
}

// ObjContainer aus einem Rechteck entspr. aktuellem Ausschnitt berechnen -----
ObjContainer ObjContainer :: operator = (RECT &R) 
{
COORDCONVERT CC;
POINT Pt1; Pt1.x = R.left; Pt1.y = R.bottom;
POINT Pt2; Pt2.x = R.right; Pt2.y = R.top;
POINTL Pkt1, Pkt2;

	CC.lpPt = (POINT *)&Pt1;
	CC.lpPkt = (long *)&Pkt1;
	DEX_DCtoOC (CC);

	CC.lpPt = (POINT *)&Pt2;
	CC.lpPkt = (long *)&Pkt2;
	DEX_DCtoOC (CC);

	SetXMin(Pkt1.x);
	SetYMin(Pkt1.y);
	SetXMax(Pkt2.x); 
	SetYMax(Pkt2.y);

	return *this;
}

#endif // __CV__

#else // _TRiAS_VER >= 0x0300

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
bool ObjContainer :: operator ^ (ObjContainer &OC) 
{
	if (XMin() > OC.XMax() || XMax() < OC.XMin() ||
	    YMin() > OC.YMax() || YMax() < OC.YMin()) 
	// ObjContainer überschneiden sich nicht
		return false;

return true;
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
bool operator < (ObjContainer &O1, ObjContainer &O2)
{
	return (O1.XMin() > O2.XMin() && O1.XMax() < O2.XMax() &&
		O1.YMin() > O2.YMin() && O1.YMax() < O2.YMax());
}

// Liefert, ob der erste der ObjContainer vollständig außerhalb des 
// Zweiten liegt
bool operator > (ObjContainer &O1, ObjContainer &O2)
{
	return (O1.XMin() < O2.XMin() && O1.XMax() > O2.XMax() &&
		O1.YMin() < O2.YMin() && O1.YMax() > O2.YMax());
}

#if defined(__CV__)

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

#else

// Aus ObjConatiner Rechteck entsprechend aktuellem Ausschnitt berechnen ------
ObjContainer :: operator RECT (void) 
{
POINTL Pkt1; Pkt1.x = XMin(); Pkt1.y = YMin();
POINTL Pkt2; Pkt2.x = XMax(); Pkt2.y = YMax();
POINT Pt1, Pt2;
COORDCONVERT CC;

	CC.lpPt = (POINT *)&Pt1;
	CC.lpPkt = (long *)&Pkt1;
	DEX_OCtoDC (CC);

	CC.lpPt = (POINT *)&Pt2;
	CC.lpPkt = (long *)&Pkt2;
	DEX_OCtoDC (CC);

RECT rc;

	SetRect (&rc, Pt1.x, Pt2.y, Pt2.x, Pt1.y);	// ltrb

return rc;
}

// ObjContainer aus einem Rechteck entspr. aktuellem Ausschnitt berechnen -----
ObjContainer ObjContainer :: operator = (RECT &R) 
{
COORDCONVERT CC;
POINT Pt1; Pt1.x = R.left; Pt1.y = R.bottom;
POINT Pt2; Pt2.x = R.right; Pt2.y = R.top;
POINTL Pkt1, Pkt2;

	CC.lpPt = (POINT *)&Pt1;
	CC.lpPkt = (long *)&Pkt1;
	DEX_DCtoOC (CC);

	CC.lpPt = (POINT *)&Pt2;
	CC.lpPkt = (long *)&Pkt2;
	DEX_DCtoOC (CC);

	XMin() = Pkt1.x; YMin() = Pkt1.y;
	XMax() = Pkt2.x; YMax() = Pkt2.y;

return *this;
}

#endif // __CV__
#endif // _TRiAS_VER >= 0x0300

