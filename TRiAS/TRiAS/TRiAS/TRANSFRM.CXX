// Transformation und Projektion beim Zeichnen - Memberfunktionen
// File: TRANSFRM.CXX

#include "triaspre.hxx"

#include <ospace/std/memory>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface2(_DGMPoints, IID__DGMPoints);
DefineSmartInterface(TRiASSimplePoints);
DefineSmartInterface(EnumVARIANT);

///////////////////////////////////////////////////////////////////////////////
// Dateninitialisierung 
CoOrd Transformation::m_EALeft = 0;			// ung¸ltiger Fensterbereich
CoOrd Transformation::m_EATop = 0;
CoOrd Transformation::m_EARight = 0;
CoOrd Transformation::m_EABottom = 0;

KoOrd Transformation::m_EOCXMin = 0;
KoOrd Transformation::m_EOCXMax = 0;
KoOrd Transformation::m_EOCYMin = 0;
KoOrd Transformation::m_EOCYMax = 0;

long Transformation::_ClipRegionObjNr = -1L;

int ExtShapeObject::_FullDCInit = 0;

///////////////////////////////////////////////////////////////////////////////
// Prim‰rdaten
CoOrd Transformation::_xViewportOrg = 0;		// Ursprung des Ausschnittes
CoOrd Transformation::_yViewportOrg = 0;
CoOrd Transformation::_xViewportExt = 1;		// Grˆﬂe des Ausschnittes
CoOrd Transformation::_yViewportExt = 1;
CoOrd Transformation::_xLogPixels = 120;		// AspectRatio des Ger‰tes
CoOrd Transformation::_yLogPixels = 120;
KoOrd Transformation::_xWindowOrg = 0;		// FensterUrsprung
KoOrd Transformation::_yWindowOrg = 0;
KoOrd Transformation::_xWindowExt = 1;		// FensterGrˆﬂe
KoOrd Transformation::_yWindowExt = 1;

double Transformation::_Masstab = 1.0;		// aktueller BildMasstab/Bezugsmasstab

///////////////////////////////////////////////////////////////////////////////
// Sekund‰rdaten
double Transformation::_xK = 1.0;				// Transformationskoeffizient
double Transformation::_yK = 1.0;
double Transformation::_invxK = 1.0;			// inverser T-Koeffizient
double Transformation::_invyK = 1.0;
KoOrd Transformation::_xViewportOffset = 0;	// Transformierter Ausschnitts-
KoOrd Transformation::_yViewportOffset = 0;	// Ursprung
KoOrd Transformation::_xWindowOffset = 0;		// r¸cktransformierter Fenster-
KoOrd Transformation::_yWindowOffset = 0;		// Ursprung

double Transformation::_CTAspect = 1.0;		// AspektRatio des Koordinatensystems

bool Transformation::m_fIsValid = false;		// Transformationsparameter sind g¸ltig
bool Transformation::m_fChanged = false;		// Transformationsparameter wurden ver‰ndert

///////////////////////////////////////////////////////////////////////////////
void (*Transformation::_Prj)(KoOrd *x, KoOrd *y) = DefPrj;
Punkt (*Transformation::_invPrj)(Punkt Pt) = DefInvPrj;

///////////////////////////////////////////////////////////////////////////////
// Einstellen der Transformationsparameter ------------------------------------
// Nullpunkt im Fenster
Punkt Transformation::SetWindowOrg (Punkt &Pt)
{
Punkt oldOrg (_xWindowOrg, _yWindowOrg);

	if (_xWindowOrg != Pt.GetX() || _yWindowOrg != Pt.GetY())
	{
		_xWindowOrg = Pt.GetX();
		_yWindowOrg = Pt.GetY();

		SetTransPars();
	}
	return oldOrg;
}

// Fenstergrˆﬂe
Ausdehnung Transformation::SetWindowExt (Ausdehnung &A)
{
Ausdehnung oldExt (_xWindowExt, _yWindowExt);

	if (_xWindowExt != A.GetBreite() || _yWindowExt != A.GetHoehe())
	{
		_xWindowExt = A.GetBreite();
		_yWindowExt = A.GetHoehe();

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

// Fenstergrˆﬂe
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
// Koordinatentransformation durchf¸hren --------------------------------------
// Device --> Objekt
Punkt DCtoOC (const Point &Pt) 
{
	KoOrd xDC = (KoOrd)(Transformation::_xK * (double)Pt.GetX() + ROUNDING_OFFSET) 
			+ Transformation::_xViewportOffset;
	KoOrd yDC = (KoOrd)(Transformation::_yK * (double)Pt.GetY() + ROUNDING_OFFSET) 
			+ Transformation::_yViewportOffset;

	return Punkt (xDC, yDC);
// return (*Transformation::_invPrj)(Punkt (xDC, yDC));
}

#if defined(_FORCE_LEGACY_CODE)
void DCtoOC (Point *pPt, Punkt *pPkt, long lCnt) 
{
KoOrd xDC, yDC;

#if defined(WIN16)
	if (lCnt > HUGELIMIT) {
		while (lCnt-- > 0) {
			xDC = (KoOrd)(Transformation::_xK * (double)pPt -> X() + ROUNDING_OFFSET) 
					+ Transformation::_xViewportOffset;
			yDC = (KoOrd)(Transformation::_yK * (double)pPt -> Y() + ROUNDING_OFFSET) 
					+ Transformation::_yViewportOffset;
			*pPkt = Punkt (xDC, yDC);
			
		// __huge beachten
			pPt = ((Point __huge *)pPt) + 1;
			pPkt = ((Punkt __huge *)pPkt) + 1;
		}
	} else 
#endif // WIN16
	{
		while (lCnt-- > 0) {
			xDC = (KoOrd)(Transformation::_xK * (double)pPt -> X() + ROUNDING_OFFSET) 
					+ Transformation::_xViewportOffset;
			yDC = (KoOrd)(Transformation::_yK * (double)pPt -> Y() + ROUNDING_OFFSET) 
					+ Transformation::_yViewportOffset;
			pPt++;
			*pPkt++ = Punkt (xDC, yDC);
		}
	}
}
#endif // defined(_FORCE_LEGACY_CODE)

Punkt DCtoOC (CoOrd x, CoOrd y) 
{
	KoOrd xDC = (KoOrd)(Transformation::_xK * (double)x + ROUNDING_OFFSET) 
			+ Transformation::_xViewportOffset;
	KoOrd yDC = (KoOrd)(Transformation::_yK * (double)y + ROUNDING_OFFSET) 
			+ Transformation::_yViewportOffset;

return Punkt (xDC, yDC);
// return (*Transformation::_invPrj)(Punkt (xDC, yDC));
}

KoOrd DCtoOCX (CoOrd x)
{
	return (KoOrd)(Transformation::_xK * double(x) + ROUNDING_OFFSET) +
		       Transformation::_xViewportOffset;
}


KoOrd DCtoOCXDelta (CoOrd x)
{
	return (KoOrd)(Transformation::_xK * double(x) + ((x >= 0) ? ROUNDING_OFFSET : -ROUNDING_OFFSET));
}


KoOrd DCtoOCY (CoOrd y)
{
	return (KoOrd)(Transformation::_yK * double(y) + ROUNDING_OFFSET) +
		       Transformation::_yViewportOffset;
}


KoOrd DCtoOCYDelta (CoOrd y)
{
	return (KoOrd)(Transformation::_yK * double(y) + ((y >= 0) ? ROUNDING_OFFSET : -ROUNDING_OFFSET));
}

///////////////////////////////////////////////////////////////////////////////
// Wert innerhalb des darstellbaren Intervalles ansiedeln ---------------------
inline CoOrd BindWin95 (KoOrd toBind) 
{
CoOrd Result; 

	if (toBind < SHRT_MIN/2)
		Result = SHRT_MIN/2;
	else if (toBind > SHRT_MAX/2) 	
		Result = SHRT_MAX/2;
	else 	
		Result = ToCoOrd(toBind);
	return Result;
}

inline CoOrd BindWin98 (KoOrd toBind) 
{
CoOrd Result; 

	if (toBind < SHRT_MIN+1)
		Result = SHRT_MIN;
	else if (toBind > SHRT_MAX-1) 	
		Result = SHRT_MAX;
	else 	
		Result = ToCoOrd(toBind);
	return Result;
}

inline CoOrd BindEx	(KoOrd toBind)
{
	if (IsWinNT())	// unter NT nichts machen, Koordinaten sind real 32Bit
		return ToCoOrd(toBind);
	
// Win95 hat 16Bit Koordinaten, also ‹berlauf verhindern
// es gab Beschwerden, daﬂ immer noch Objekte verschwinden, die zu groﬂ sind.
// In der Hoffnung, daﬂ Memphis etwas besser ist, hier der folgende hack.
	return IsWin41() ? BindWin98(toBind) : BindWin95(toBind);
}

inline CoOrd Bind9x	(KoOrd toBind)
{
// Win95 hat 16Bit Koordinaten, also ‹berlauf verhindern
// es gab Beschwerden, daﬂ immer noch Objekte verschwinden, die zu groﬂ sind.
// In der Hoffnung, daﬂ Memphis etwas besser ist, hier der folgende hack.
	return IsWin41() ? BindWin98(toBind) : BindWin95(toBind);
}

// Objekt --> Device ----------------------------------------------------------
Point OCtoDC (KoOrd x, KoOrd y) 
{
//	(*Transformation::_Prj)(&x, &y);	// Projektion durchf¸hren
// X-Koordinate behandeln
KoOrd xOC = (KoOrd)(Transformation::_invxK * (double)x + ROUNDING_OFFSET) 
			+ Transformation::_xWindowOffset;

// Y-Koordinate behandlen
KoOrd yOC = (KoOrd)(Transformation::_invyK * (double)y + ROUNDING_OFFSET) 
			+ Transformation::_yWindowOffset;

	return Point (BindEx(xOC), BindEx(yOC));
}

Point OCtoDC (const Punkt &Pt) 
{
//	(*Transformation::_Prj)(&Pt.X(), &Pt.Y());	// Projektion durchf¸hren
// X-Koordinate behandeln
KoOrd xOC = (KoOrd)(Transformation::_invxK * (double)Pt.GetX() + ROUNDING_OFFSET) 
			+ Transformation::_xWindowOffset;

// Y-Koordinate behandlen
KoOrd yOC = (KoOrd)(Transformation::_invyK * (double)Pt.GetY() + ROUNDING_OFFSET) 
			+ Transformation::_yWindowOffset;

	return Point (BindEx(xOC), BindEx(yOC));
}

#if defined(_FORCE_LEGACY_CODE)
void OCtoDC (Punkt *pPkt, Point *pPt, long lCnt) 
{
KoOrd xOC, yOC;

#if defined(WIN16)
	if (lCnt > HUGELIMIT) {
		while (lCnt-- > 0) {
		// X-Koordinate behandeln
			xOC = (KoOrd)(Transformation::_invxK * (double)pPkt -> X() + ROUNDING_OFFSET) 
					+ Transformation::_xWindowOffset;
			ixOC = Bind(xOC);
		// Y-Koordinate behandlen
			yOC = (KoOrd)(Transformation::_invyK * (double)pPkt -> Y() + ROUNDING_OFFSET) 
					+ Transformation::_yWindowOffset;
			iyOC = Bind(yOC);
			*pPt = Point (ixOC, iyOC);
			
		// __huge beachten
			pPt = ((Point __huge *)pPt) + 1;
			pPkt = ((Punkt __huge *)pPkt) + 1;
		}
	} else 
#endif // WIN16
	{
		while (lCnt-- > 0) {
		// X-Koordinate behandeln
			xOC = (KoOrd)(Transformation::_invxK * (double)pPkt -> GetX() + ROUNDING_OFFSET) 
					+ Transformation::_xWindowOffset;

		// Y-Koordinate behandlen
			yOC = (KoOrd)(Transformation::_invyK * (double)pPkt -> GetY() + ROUNDING_OFFSET) 
					+ Transformation::_yWindowOffset;

			*pPt++ = Point (BindEx(xOC), BindEx(yOC));
			pPkt++;
		}
	}
}
#else
// spezielle Behandlung f¸r GeomediaObjekte
HRESULT OCtoDCSupport (_DGMGeometry *pPkt, POINT *pPt, long lCnt)
{
	TX_ASSERT(FALSE);
	return S_OK;
}

#if defined(_NO_ASSEMBLY_OPTIMIZATIONS)
inline CoOrd ToCoOrdCut (KoOrd dVal)
{
	return CoOrd(dVal);
}
#else
inline CoOrd ToCoOrdCut (KoOrd dVal)
{
CoOrd iRes;

	__asm {
		fld	dVal;
//		frndint;		// _nicht_ runden
		fistp iRes;
	}
	return iRes;
}
#endif // defined(_NO_ASSEMBLY_OPTIMIZATIONS)

HRESULT OCtoDC (_DGMGeometry *pPkt, POINT *pPt, long lCnt, CSCOORD *pCoords)
{
	COM_TRY {
	W_DGMPolylineGeometry line(pPkt);
	W_DGMPoints Pts;

		THROW_FAILED_HRESULT(line -> get_Points(Pts.ppi()));

#if defined(_DEBUG)
	long lCount = 0;

		THROW_FAILED_HRESULT(Pts -> get_Count(&lCount));	// Anzahl der Punkte holen
		TX_ASSERT(lCnt == lCount);							// Anzahl muﬂ stimmen
#endif // defined(_DEBUG)

#if defined(_USE_GETPOINT_N)
		if (IsWinNT()) {
			THROW_FAILED_HRESULT(WTRiASSimplePoints(Pts) -> GetPoints (1, lCnt, (double *)pCoords));	// direkt von den Points die Koordinaten abrufen
			for(long lCurrCnt = 0; lCurrCnt < lCnt; ++lCurrCnt)	{			// alle mˆglichen Indizes ablaufen
			// Koordinaten behandeln (f¸rs Zeichnen einfach abschneiden und _nicht_ runden)
				pPt -> x = ToCoOrdCut ((KoOrd)(Transformation::_invxK * pCoords -> X) + Transformation::_xWindowOffset);
				pPt -> y = ToCoOrdCut ((KoOrd)(Transformation::_invyK * pCoords -> Y) + Transformation::_yWindowOffset);
				++pPt;		// n‰chster Punkt
				++pCoords;
			}
			TX_ASSERT(lCnt == lCurrCnt);		// Anzahl muﬂ stimmen
		} 
		else {
			THROW_FAILED_HRESULT(WTRiASSimplePoints(Pts) -> GetPoints (1, lCnt, (double *)pCoords));	// direkt von den Points die Koordinaten abrufen
			for(long lCurrCnt = 0; lCurrCnt < lCnt; ++lCurrCnt)	{		// alle mˆglichen Indizes ablaufen
			// Koordinaten behandeln
				pPt -> x = Bind9x ((KoOrd)(Transformation::_invxK * pCoords -> X + ROUNDING_OFFSET) + Transformation::_xWindowOffset);
				pPt -> y = Bind9x ((KoOrd)(Transformation::_invyK * pCoords -> Y + ROUNDING_OFFSET) + Transformation::_yWindowOffset);
				++pPt;		// n‰chster Punkt
				++pCoords;
			}
			TX_ASSERT(lCnt == lCurrCnt);		// Anzahl muﬂ stimmen
		}
#else 
	double dKoords[3];

		if (IsWinNT()) {
			for(long lCurrCnt = 1; lCurrCnt <= lCnt; ++lCurrCnt) {		// alle mˆglichen Indizes ablaufen
				THROW_FAILED_HRESULT(Pts -> GetPoint (lCurrCnt, dKoords));	// direkt von den Points die Koordinaten abrufen
		
			// Koordinaten behandeln
				pPt -> x = ToCoOrd ((KoOrd)(Transformation::_invxK * dKoords[0] + ROUNDING_OFFSET) + Transformation::_xWindowOffset);
				pPt -> y = ToCoOrd ((KoOrd)(Transformation::_invyK * dKoords[1] + ROUNDING_OFFSET) + Transformation::_yWindowOffset);
				pPt++;		// n‰chster Punkt
			}
			TX_ASSERT(lCnt+1 == lCurrCnt);		// Anzahl muﬂ stimmen
		else {
			for(long lCurrCnt = 1; lCurrCnt <= lCnt; ++lCurrCnt)	{		// alle mˆglichen Indizes ablaufen
				THROW_FAILED_HRESULT(Pts -> GetPoint (lCurrCnt, dKoords));	// direkt von den Points die Koordinaten abrufen
		
			// Koordinaten behandeln
				pPt -> x = Bind9x ((KoOrd)(Transformation::_invxK * dKoords[0] + ROUNDING_OFFSET) + Transformation::_xWindowOffset);
				pPt -> y = Bind9x ((KoOrd)(Transformation::_invyK * dKoords[1] + ROUNDING_OFFSET) + Transformation::_yWindowOffset);
				++pPt;		// n‰chster Punkt
			}
			TX_ASSERT(lCnt+1 == lCurrCnt);		// Anzahl muﬂ stimmen
		}
#endif // defined(_USE_GETPOINT_N)
	} COM_CATCH_OP(OCtoDCSupport(pPkt, pPt, lCnt));
	return S_OK;
}
#endif // _FORCE_LEGACY_CODE

///////////////////////////////////////////////////////////////////////////////
// Koordinaten eines Polygones konvertieren und dabei das umschlieﬂende 
// Rechteck berechnen
#if defined(_FORCE_LEGACY_CODE)
void OCtoDC (Punkt *pPkt, Point *pPt, long lCnt, Rectangle &rrcBound) 
{
KoOrd xOC, yOC;

	while (lCnt-- > 0) {
	CoOrd X = pPkt -> GetX();
	CoOrd Y = pPkt -> GetY();

	// bounding rect bestimmen
		rrcBound.Left() = min(rrcBound.Left(), X);
		rrcBound.Right() = max(rrcBound.Right(), X);
		rrcBound.Top() = min(rrcBound.Top(), Y);
		rrcBound.Bottom() = max(rrcBound.Bottom(), Y);

	// X-Koordinate behandeln
		xOC = (KoOrd)(Transformation::_invxK * (double)X + ROUNDING_OFFSET) 
				+ Transformation::_xWindowOffset;

	// Y-Koordinate behandlen
		yOC = (KoOrd)(Transformation::_invyK * (double)Y + ROUNDING_OFFSET) 
				+ Transformation::_yWindowOffset;

		*pPt++ = Point (BindEx(xOC), BindEx(yOC));
		pPkt++;
	}

// ObjektContainer auch konvertieren
Point ptTL (OCtoDC (Punkt (rrcBound.UpperLeft())));
Point ptBR (OCtoDC (Punkt (rrcBound.LowerRight())));

	rrcBound = Rectangle (ptTL, ptBR);		// tlbr
}
#else
#endif // _FORCE_LEGACY_CODE

CoOrd OCtoDCX (KoOrd x)
{
KoOrd xOC = (KoOrd)(Transformation::_invxK * double(x) + ROUNDING_OFFSET) +
		    Transformation::_xWindowOffset;

	return BindEx(xOC);
}

CoOrd OCtoDCXDelta (KoOrd dX)
{
KoOrd xOC = KoOrd(Transformation::_invxK * double(dX) + ((dX >= 0) ? ROUNDING_OFFSET : -ROUNDING_OFFSET));

	return BindEx(xOC);
}


CoOrd OCtoDCY (KoOrd y)
{
KoOrd yOC = (KoOrd)(Transformation::_invyK * double(y) + ROUNDING_OFFSET) +
		    Transformation::_yWindowOffset;

	return BindEx(yOC);
}

CoOrd OCtoDCYDelta (KoOrd dY)
{
KoOrd yOC = KoOrd (Transformation::_invyK * double(dY) + ((dY >= 0) ? ROUNDING_OFFSET : -ROUNDING_OFFSET));

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
		_y0 = KoOrd((double(_yViewportExt)-(_yWindowExt/_yK))/2.0 + ROUNDING_OFFSET);
	} else {
	// Koeffizienten korrigieren (MM_ISOTROPIC)
	register bool sign = (_xK < 0.0);

		_xK = fabs (_yK / Aspect);
		if (sign) _xK = -_xK;

	// Offset korrigieren (zentrieren des Bildes)
		TX_ASSERT(_xK != 0);

		_x0 = KoOrd((double(_xViewportExt)-(_xWindowExt/_xK))/2.0 + ROUNDING_OFFSET);
		_y0 = 0;
	}

// inverse Transformationskoeffizienten berechnen
	_invxK = 1.0/_xK;	
	_invyK = 1.0/_yK;

// Transformationsoffset berechnen
	_xViewportOffset = (KoOrd)(((_xWindowOrg-(_xK*(double)_xViewportOrg))-(_x0*_xK)) + ROUNDING_OFFSET);
	_yViewportOffset = (KoOrd)(((_yWindowOrg-(_yK*(double)_yViewportOrg))-(_y0*_yK)) + ROUNDING_OFFSET);
	_xWindowOffset = (KoOrd)(((_x0+_xViewportOrg)-(_invxK * (double)_xWindowOrg)) + ROUNDING_OFFSET);
	_yWindowOffset = (KoOrd)(((_y0+_yViewportOrg)-(_invyK * (double)_yWindowOrg)) + ROUNDING_OFFSET);

	SetChanged (true);		// TransformationsParameter ge‰ndert
}

#if defined(__WATCOMC__)
#pragma warning 604 5;		// lookahead required
#pragma warning 594 5;		// resolved as a declaration/type
#pragma warning 595 5;		// resolved as an expression
#endif

// Projektionsfunktionen setzen
void Transformation::SetPrjFcn (void (*F)(KoOrd *x, KoOrd *y), 
				  Punkt (*invF)(Punkt Pt)) 
{
	if (F != NULL) _Prj = F;
	else	       _Prj = DefPrj;

	if (invF != NULL) _invPrj = invF;
	else		  _invPrj = DefInvPrj;
}

///////////////////////////////////////////////////////////////////////////////
// ObjContainer aus einem Rechteck entspr. aktuellem Ausschnitt berechnen -----
#if !defined(WIN16)
#pragma warning (disable: 4273)
#endif

ObjContainer::ObjContainer (Rectangle &R) 
{
Punkt Pt1 = DCtoOC (R.Left(), R.Bottom());
Punkt Pt2 = DCtoOC (R.Right(), R.Top());

	SetXMin(Pt1.GetX());
	SetYMin(Pt1.GetY());
	SetXMax(Pt2.GetX()); 
	SetYMax(Pt2.GetY());
}

ObjContainer &ObjContainer::operator = (Rectangle &R) 
{
Punkt Pt1 = DCtoOC (R.Left(), R.Bottom());
Punkt Pt2 = DCtoOC (R.Right(), R.Top());

	SetXMin(Pt1.GetX());
	SetYMin(Pt1.GetY());
	SetXMax(Pt2.GetX()); 
	SetYMax(Pt2.GetY());
	return *this;
}

#if !defined(WIN16)
#pragma warning (default: 4273)
#endif

///////////////////////////////////////////////////////////////////////////////
// Transformationsparameter initialisieren
void Transformation::InitStaticData (void)
{
	m_fIsValid = false;		// Transformationsparameter sind (un)g¸ltig

// Prim‰rdaten
	_xViewportOrg = 0;		// Ursprung des Ausschnittes
	_yViewportOrg = 0;
	_xViewportExt = 1;		// Grˆﬂe des Ausschnittes
	_yViewportExt = 1;
	_xLogPixels = 120;		// AspectRatio des Ger‰tes
	_yLogPixels = 120;
	_xWindowOrg = 0;		// FensterUrsprung
	_yWindowOrg = 0;
	_xWindowExt = 1;		// FensterGrˆﬂe
	_yWindowExt = 1;

// Sekund‰rdaten
	_xK = 1.0;				// Transformationskoeffizient
	_yK = 1.0;
	_invxK = 1.0;			// inverser T-Koeffizient
	_invyK = 1.0;
	_xViewportOffset = 0;	// Transformierter Ausschnitts-
	_yViewportOffset = 0;	// Ursprung
	_xWindowOffset = 0;		// r¸cktransformierter Fenster-
	_yWindowOffset = 0;		// Ursprung

	_CTAspect = 1.0;		// AspektRatio des Koordinatensystems
}
