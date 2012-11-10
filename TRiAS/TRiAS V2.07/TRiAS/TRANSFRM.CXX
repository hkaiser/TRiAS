// Transformation und Projektion beim Zeichnen - Memberfunktionen
// File: TRANSFRM.CXX

#include "triaspre.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Dateninitialisierung -------------------------------------------------------
CoOrd Transformation :: m_EALeft = 0;			// ungültiger Fensterbereich
CoOrd Transformation :: m_EATop = 0;
CoOrd Transformation :: m_EARight = 0;
CoOrd Transformation :: m_EABottom = 0;

KoOrd Transformation :: m_EOCXMin = 0;
KoOrd Transformation :: m_EOCXMax = 0;
KoOrd Transformation :: m_EOCYMin = 0;
KoOrd Transformation :: m_EOCYMax = 0;

long Transformation :: _ClipRegionObjNr = -1L;
short Transformation :: _FullDCInit = 0;

///////////////////////////////////////////////////////////////////////////////
// Primärdaten
CoOrd Transformation :: _xViewportOrg = 0;		// Ursprung des Ausschnittes
CoOrd Transformation :: _yViewportOrg = 0;
CoOrd Transformation :: _xViewportExt = 1;		// Größe des Ausschnittes
CoOrd Transformation :: _yViewportExt = 1;
CoOrd Transformation :: _xLogPixels = 120;		// AspectRatio des Gerätes
CoOrd Transformation :: _yLogPixels = 120;
KoOrd Transformation :: _xWindowOrg = 0;		// FensterUrsprung
KoOrd Transformation :: _yWindowOrg = 0;
KoOrd Transformation :: _xWindowExt = 1;		// FensterGröße
KoOrd Transformation :: _yWindowExt = 1;

double Transformation :: _Masstab = 1.0;		// aktueller BildMasstab/Bezugsmasstab

///////////////////////////////////////////////////////////////////////////////
// Sekundärdaten
double Transformation :: _xK = 1.0;				// Transformationskoeffizient
double Transformation :: _yK = 1.0;
double Transformation :: _invxK = 1.0;			// inverser T-Koeffizient
double Transformation :: _invyK = 1.0;
KoOrd Transformation :: _xViewportOffset = 0;	// Transformierter Ausschnitts-
KoOrd Transformation :: _yViewportOffset = 0;	// Ursprung
KoOrd Transformation :: _xWindowOffset = 0;		// rücktransformierter Fenster-
KoOrd Transformation :: _yWindowOffset = 0;		// Ursprung

double Transformation :: _CTAspect = 1.0;		// AspektRatio des Koordinatensystems

bool Transformation :: m_fIsValid = false;		// Transformationsparameter sind gültig
bool Transformation :: m_fChanged = false;		// Transformationsparameter wurden verändert

///////////////////////////////////////////////////////////////////////////////
void (*Transformation :: _Prj)(KoOrd *x, KoOrd *y) = DefPrj;
Punkt (*Transformation :: _invPrj)(Punkt Pt) = DefInvPrj;

///////////////////////////////////////////////////////////////////////////////
// Einstellen der Transformationsparameter ------------------------------------
// Nullpunkt im Fenster
Punkt Transformation::SetWindowOrg (Punkt &Pt)
{
Punkt oldOrg (_xWindowOrg, _yWindowOrg);

	if (_xWindowOrg != Pt.X() || _yWindowOrg != Pt.Y())
	{
		_xWindowOrg = Pt.X();
		_yWindowOrg = Pt.Y();

		SetTransPars();
	}
	return oldOrg;
}

// Fenstergröße
Ausdehnung Transformation::SetWindowExt (Ausdehnung &A)
{
Ausdehnung oldExt (_xWindowExt, _yWindowExt);

	if (_xWindowExt != A.Breite() || _yWindowExt != A.Hoehe())
	{
		_xWindowExt = A.Breite();
		_yWindowExt = A.Hoehe();

		SetTransPars();
	}
	return oldExt;
}

// Nullpunkt im Fenster
Point Transformation::SetViewportOrg (Point &Pt)
{
Point oldOrg (_xViewportOrg, _yViewportOrg);

	if (_xViewportOrg != Pt.X() || _yViewportOrg != Pt.Y())
	{
		_xViewportOrg = Pt.X();
		_yViewportOrg = Pt.Y();

		SetTransPars ();
	}
	return oldOrg;
}

// Fenstergröße
Dimension Transformation::SetViewportExt (Dimension &D)	
{
Dimension oldExt (_xViewportExt, _yViewportExt);

	if (_xViewportExt != D.Width() || _yViewportExt != D.Height())
	{
		_xViewportExt = D.Width();
		_yViewportExt = D.Height();

		SetTransPars();
	}
	return oldExt;
}

Point Transformation::SetAspectRatio (Point &Aspect, double &CTAspect) 
{
Point oldAspect (_xLogPixels, _yLogPixels);
double oldRatio = _CTAspect;

	if (Aspect.X() != _xLogPixels || Aspect.Y() != _yLogPixels ||
		_CTAspect != CTAspect)
	{
		_xLogPixels = Aspect.X();
		_yLogPixels = Aspect.Y();
		_CTAspect = CTAspect;

		SetTransPars();
	}

	CTAspect = oldRatio;
	return oldAspect;
}

double Transformation::GetAspectRatio()
{
	if (m_fIsValid)
		return _CTAspect;
	return 1.0;
}

///////////////////////////////////////////////////////////////////////////////
// Koordinatentransformation durchführen --------------------------------------
// Device --> Objekt
Punkt DCtoOC (const Point &Pt) 
{
	KoOrd xDC = (KoOrd)(Transformation :: _xK * (double)Pt.GetX() + 0.5) 
			+ Transformation :: _xViewportOffset;
	KoOrd yDC = (KoOrd)(Transformation :: _yK * (double)Pt.GetY() + 0.5) 
			+ Transformation :: _yViewportOffset;

return Punkt (xDC, yDC);
// return (*Transformation :: _invPrj)(Punkt (xDC, yDC));
}

void DCtoOC (Point *pPt, Punkt *pPkt, long lCnt) 
{
KoOrd xDC, yDC;

#if !defined(WIN32)
	if (lCnt > HUGELIMIT) {
		while (lCnt-- > 0) {
			xDC = (KoOrd)(Transformation :: _xK * (double)pPt -> X() + 0.5) 
					+ Transformation :: _xViewportOffset;
			yDC = (KoOrd)(Transformation :: _yK * (double)pPt -> Y() + 0.5) 
					+ Transformation :: _yViewportOffset;
			*pPkt = Punkt (xDC, yDC);
			
		// __huge beachten
			pPt = ((Point __huge *)pPt) + 1;
			pPkt = ((Punkt __huge *)pPkt) + 1;
		}
	} else 
#endif // !WIN32
	{
		while (lCnt-- > 0) {
			xDC = (KoOrd)(Transformation :: _xK * (double)pPt -> X() + 0.5) 
					+ Transformation :: _xViewportOffset;
			yDC = (KoOrd)(Transformation :: _yK * (double)pPt -> Y() + 0.5) 
					+ Transformation :: _yViewportOffset;
			pPt++;
			*pPkt++ = Punkt (xDC, yDC);
		}
	}
}

Punkt DCtoOC (CoOrd x, CoOrd y) 
{
	KoOrd xDC = (KoOrd)(Transformation :: _xK * (double)x + 0.5) 
			+ Transformation :: _xViewportOffset;
	KoOrd yDC = (KoOrd)(Transformation :: _yK * (double)y + 0.5) 
			+ Transformation :: _yViewportOffset;

return Punkt (xDC, yDC);
// return (*Transformation :: _invPrj)(Punkt (xDC, yDC));
}

KoOrd DCtoOCX (CoOrd x)
{
	return (KoOrd)(Transformation :: _xK * double(x) + 0.5) +
		       Transformation :: _xViewportOffset;
}


KoOrd DCtoOCXDelta (CoOrd x)
{
	return (KoOrd)(Transformation :: _xK * double(x) + ((x >= 0) ? 0.5 : -0.5));
}


KoOrd DCtoOCY (CoOrd y)
{
	return (KoOrd)(Transformation :: _yK * double(y) + 0.5) +
		       Transformation :: _yViewportOffset;
}


KoOrd DCtoOCYDelta (CoOrd y)
{
	return (KoOrd)(Transformation :: _yK * double(y) + ((y >= 0) ? 0.5 : -0.5));
}

///////////////////////////////////////////////////////////////////////////////
// Wert innerhalb des darstellbaren Intervalles ansiedeln ---------------------
inline CoOrd Bind (KoOrd toBind) 
{
CoOrd Result; 

#if defined(WIN32)
	if (toBind < SHRT_MIN+1)
		Result = SHRT_MIN;
	else if (toBind > SHRT_MAX-1) 	
		Result = SHRT_MAX;
	else 	
		Result = (CoOrd)toBind;
#else
	if (toBind < SHRT_MIN/2)
		Result = SHRT_MIN/2;
	else if (toBind > SHRT_MAX/2) 	
		Result = SHRT_MAX/2;
	else 	
		Result = (CoOrd)toBind;
#endif // WIN32

	return Result;
}

#if defined(WIN32)
inline CoOrd BindEx	(KoOrd toBind)
{
	if (IsWinNT())	// unter NT nichts machen, Koordinaten sind real 32Bit
		return (CoOrd)toBind;
	
// Win95 hat 16Bit Koordinaten, also Überlauf verhindern
	return Bind (toBind);
}
#else
inline CoOrd BindEx	(KoOrd toBind)
{
	return Bind (toBind);
}
#endif // WIN32

// Objekt --> Device ----------------------------------------------------------
Point OCtoDC (KoOrd x, KoOrd y) 
{
//	(*Transformation :: _Prj)(&x, &y);	// Projektion durchführen
// X-Koordinate behandeln
KoOrd xOC = (KoOrd)(Transformation :: _invxK * (double)x + 0.5) 
			+ Transformation :: _xWindowOffset;

// Y-Koordinate behandlen
KoOrd yOC = (KoOrd)(Transformation :: _invyK * (double)y + 0.5) 
			+ Transformation :: _yWindowOffset;

	return Point (BindEx(xOC), BindEx(yOC));
}

Point OCtoDC (const Punkt &Pt) 
{
//	(*Transformation :: _Prj)(&Pt.X(), &Pt.Y());	// Projektion durchführen
// X-Koordinate behandeln
KoOrd xOC = (KoOrd)(Transformation :: _invxK * (double)Pt.GetX() + 0.5) 
			+ Transformation :: _xWindowOffset;

// Y-Koordinate behandlen
KoOrd yOC = (KoOrd)(Transformation :: _invyK * (double)Pt.GetY() + 0.5) 
			+ Transformation :: _yWindowOffset;

	return Point (BindEx(xOC), BindEx(yOC));
}

void OCtoDC (Punkt *pPkt, Point *pPt, long lCnt) 
{
KoOrd xOC, yOC;

#if !defined(WIN32)
	if (lCnt > HUGELIMIT) {
		while (lCnt-- > 0) {
		// X-Koordinate behandeln
			xOC = (KoOrd)(Transformation :: _invxK * (double)pPkt -> X() + 0.5) 
					+ Transformation :: _xWindowOffset;
			ixOC = Bind(xOC);
		// Y-Koordinate behandlen
			yOC = (KoOrd)(Transformation :: _invyK * (double)pPkt -> Y() + 0.5) 
					+ Transformation :: _yWindowOffset;
			iyOC = Bind(yOC);
			*pPt = Point (ixOC, iyOC);
			
		// __huge beachten
			pPt = ((Point __huge *)pPt) + 1;
			pPkt = ((Punkt __huge *)pPkt) + 1;
		}
	} else 
#endif // !WIN32
	{
		while (lCnt-- > 0) {
		// X-Koordinate behandeln
			xOC = (KoOrd)(Transformation :: _invxK * (double)pPkt -> X() + 0.5) 
					+ Transformation :: _xWindowOffset;

		// Y-Koordinate behandlen
			yOC = (KoOrd)(Transformation :: _invyK * (double)pPkt -> Y() + 0.5) 
					+ Transformation :: _yWindowOffset;

			*pPt++ = Point (BindEx(xOC), BindEx(yOC));
			pPkt++;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// Koordinaten eines Polygones konvertieren und dabei das umschließende 
// Rechteck berechnen
void OCtoDC (Punkt *pPkt, Point *pPt, long lCnt, Rectangle &rrcBound) 
{
KoOrd xOC, yOC;

	while (lCnt-- > 0) {
	CoOrd X = pPkt -> X();
	CoOrd Y = pPkt -> Y();

	// bounding rect bestimmen
		rrcBound.Left() = min(rrcBound.Left(), X);
		rrcBound.Right() = max(rrcBound.Right(), X);
		rrcBound.Top() = min(rrcBound.Top(), Y);
		rrcBound.Bottom() = max(rrcBound.Bottom(), Y);

	// X-Koordinate behandeln
		xOC = (KoOrd)(Transformation :: _invxK * (double)X + 0.5) 
				+ Transformation :: _xWindowOffset;

	// Y-Koordinate behandlen
		yOC = (KoOrd)(Transformation :: _invyK * (double)Y + 0.5) 
				+ Transformation :: _yWindowOffset;

		*pPt++ = Point (BindEx(xOC), BindEx(yOC));
		pPkt++;
	}

// ObjektContainer auch konvertieren
Point ptTL (OCtoDC (Punkt (rrcBound.UpperLeft())));
Point ptBR (OCtoDC (Punkt (rrcBound.LowerRight())));

	rrcBound = Rectangle (ptTL, ptBR);		// tlbr
}

CoOrd OCtoDCX (KoOrd x)
{
KoOrd xOC = (KoOrd)(Transformation :: _invxK * double(x) + 0.5) +
		    Transformation :: _xWindowOffset;

	return BindEx(xOC);
}

CoOrd OCtoDCXDelta (KoOrd dX)
{
KoOrd xOC = KoOrd(Transformation :: _invxK * double(dX) + ((dX >= 0) ? 0.5 : -0.5));

	return BindEx(xOC);
}


CoOrd OCtoDCY (KoOrd y)
{
KoOrd yOC = (KoOrd)(Transformation :: _invyK * double(y) + 0.5) +
		    Transformation :: _yWindowOffset;

	return BindEx(yOC);
}

CoOrd OCtoDCYDelta (KoOrd dY)
{
KoOrd yOC = KoOrd (Transformation :: _invyK * double(dY) + ((dY >= 0) ? 0.5 : -0.5));

	return BindEx(yOC);
}

///////////////////////////////////////////////////////////////////////////////
// Transformationsparameter berechnen -----------------------------------------
void Transformation::SetTransPars (void) 
{
KoOrd _x0, _y0;

	TX_ASSERT(_yLogPixels != 0);

double Aspect = (double)_xLogPixels/(double)_yLogPixels * _CTAspect;

	TX_ASSERT(Aspect != 0.0);

// Transformationskoeffizienten berechnen
	TX_ASSERT(_xViewportExt != 0);
	TX_ASSERT(_yViewportExt != 0);

	_xK = (double)_xWindowExt/(double)_xViewportExt;
	_yK = (double)_yWindowExt/(double)_yViewportExt;

// Isotropische Korrektur
	if (fabs (_xK * Aspect) > fabs (_yK)) {
	// Koeffizienten korrigieren (MM_ISOTROPIC)
	register bool sign = (_yK < 0.0);

		_yK = fabs (_xK * Aspect);
		if (sign) _yK = -_yK;

	// Offset korrigieren (zentrieren des Bildes)
		TX_ASSERT(_yK != 0);

		_x0 = 0;
		_y0 = KoOrd((double(_yViewportExt)-(_yWindowExt/_yK))/2.0 + 0.5);
	} else {
	// Koeffizienten korrigieren (MM_ISOTROPIC)
	register bool sign = (_xK < 0.0);

		_xK = fabs (_yK / Aspect);
		if (sign) _xK = -_xK;

	// Offset korrigieren (zentrieren des Bildes)
		TX_ASSERT(_xK != 0);

		_x0 = KoOrd((double(_xViewportExt)-(_xWindowExt/_xK))/2.0 + 0.5);
		_y0 = 0;
	}

// inverse Transformationskoeffizienten berechnen
	_invxK = 1.0/_xK;	
	_invyK = 1.0/_yK;

// Transformationsoffset berechnen
	_xViewportOffset = (KoOrd)(((_xWindowOrg-(_xK*(double)_xViewportOrg))-(_x0*_xK)) + 0.5);
	_yViewportOffset = (KoOrd)(((_yWindowOrg-(_yK*(double)_yViewportOrg))-(_y0*_yK)) + 0.5);
	_xWindowOffset = (KoOrd)(((_x0+_xViewportOrg)-(_invxK * (double)_xWindowOrg)) + 0.5);
	_yWindowOffset = (KoOrd)(((_y0+_yViewportOrg)-(_invyK * (double)_yWindowOrg)) + 0.5);

	SetChanged (true);		// TransformationsParameter geändert
}

#if defined(__WATCOMC__)
#pragma warning 604 5;		// lookahead required
#pragma warning 594 5;		// resolved as a declaration/type
#pragma warning 595 5;		// resolved as an expression
#endif

// Projektionsfunktionen setzen
void Transformation :: SetPrjFcn (void (*F)(KoOrd *x, KoOrd *y), 
				  Punkt (*invF)(Punkt Pt)) 
{
	if (F != NULL) _Prj = F;
	else	       _Prj = DefPrj;

	if (invF != NULL) _invPrj = invF;
	else		  _invPrj = DefInvPrj;
}

///////////////////////////////////////////////////////////////////////////////
// ObjContainer aus einem Rechteck entspr. aktuellem Ausschnitt berechnen -----
#if defined(WIN32)
#pragma warning (disable: 4273)
#endif

ObjContainer ObjContainer :: operator = (Rectangle &R) 
{
Punkt Pt1 = DCtoOC (R.Left(), R.Bottom());
Punkt Pt2 = DCtoOC (R.Right(), R.Top());

	XMin() = Pt1.X(); YMin() = Pt1.Y();
	XMax() = Pt2.X(); YMax() = Pt2.Y();

return *this;
}

#if defined(WIN32)
#pragma warning (default: 4273)
#endif

///////////////////////////////////////////////////////////////////////////////
// Transformationsparameter initialisieren
void Transformation :: InitStaticData (void)
{
	m_fIsValid = false;		// Transformationsparameter sind (un)gültig

// Primärdaten
	_xViewportOrg = 0;		// Ursprung des Ausschnittes
	_yViewportOrg = 0;
	_xViewportExt = 1;		// Größe des Ausschnittes
	_yViewportExt = 1;
	_xLogPixels = 120;		// AspectRatio des Gerätes
	_yLogPixels = 120;
	_xWindowOrg = 0;		// FensterUrsprung
	_yWindowOrg = 0;
	_xWindowExt = 1;		// FensterGröße
	_yWindowExt = 1;

// Sekundärdaten
	_xK = 1.0;				// Transformationskoeffizient
	_yK = 1.0;
	_invxK = 1.0;			// inverser T-Koeffizient
	_invyK = 1.0;
	_xViewportOffset = 0;	// Transformierter Ausschnitts-
	_yViewportOffset = 0;	// Ursprung
	_xWindowOffset = 0;		// rücktransformierter Fenster-
	_yWindowOffset = 0;		// Ursprung

	_CTAspect = 1.0;		// AspektRatio des Koordinatensystems
}
