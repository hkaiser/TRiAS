///////////////////////////////////////////////////////////////////////////
// @doc 
// @module OBJCONTX.HXX | Enthält ObjContainerDeklaration für Erweiterungen

#if !defined(_OBJCONTX_HXX__09B84F74_1BB6_11D2_9E93_006008447800__INCLUDED_)
#define _OBJCONTX_HXX__09B84F74_1BB6_11D2_9E93_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <geo_inl.hxx>

#if _TRiAS_VER >= 0x0300

/////////////////////////////////////////////////////////////////////////////
// GeometrieObjekte
#include <CSPointGeom.h>
#include <CSRectGeom.h>

/////////////////////////////////////////////////////////////////////////////
// Kleinstes umschließendes Rechteck eines geometrischen Objektes
class Punkt;
class ObjContainer 
{
protected:
	CCSRectangleGeometry m_oc;	// Container dieser Kante

public:
// Konstruktoren
	ObjContainer (IDispatch *pOC) : m_oc(pOC) {}
	ObjContainer (KoOrd XMin = 0, KoOrd XMax = 0, KoOrd YMin = 0, KoOrd YMax = 0);
	ObjContainer (Punkt Pt1, Punkt Pt2);
	ObjContainer (const ObjContainer &);

// Memberfunktionen
	KoOrd XMin (void) const { double t; const_cast<ObjContainer *>(this) -> m_oc.get_XMin(&t); return KoOrd(t); }
	KoOrd XMax (void) const { double t; const_cast<ObjContainer *>(this) -> m_oc.get_XMax(&t); return KoOrd(t); }
	KoOrd YMin (void) const { double t; const_cast<ObjContainer *>(this) -> m_oc.get_YMin(&t); return KoOrd(t); }
	KoOrd YMax (void) const { double t; const_cast<ObjContainer *>(this) -> m_oc.get_YMax(&t); return KoOrd(t); }

	void SetXMin (const KoOrd xmin) { m_oc.put_XMin (double(xmin)); }
	void SetXMax (const KoOrd xmax) { m_oc.put_XMax (double(xmax)); }
	void SetYMin (const KoOrd ymin) { m_oc.put_YMin (double(ymin)); }
	void SetYMax (const KoOrd ymax) { m_oc.put_YMax (double(ymax)); }

	KoOrd Breite (void) { return (KoOrdAbs (XMax()-XMin())); }
	KoOrd Hoehe (void) { return (KoOrdAbs (YMax()-YMin())); }

	ObjContainer InflateCont (int);			// Container größer/kleiner

// wenn alle Werte oder die Abmessungen gleich 0 sind, dann ist der OC inValid
	bool isValid (void) { return ( !((XMax()-XMin()==0)&&(YMax()-YMin()==0)) ); }
	void Assign (IDispatch *pIDisp) { m_oc.Assign(pIDisp); }

// Zuweisungsoperator
	ObjContainer &operator = (const ObjContainer &rhs)
		{ if (&rhs != this)  m_oc = const_cast<ObjContainer &>(rhs).m_oc;  return *this; }

// Operator testet Verschnitt zweier ObjeContainer
	bool operator ^ (ObjContainer &);
#if defined(__CV__)
	ObjContainer operator = (Rectangle &);
	operator Rectangle (void);
#else
	ObjContainer operator = (RECT &);
	operator RECT (void);
#endif

	ObjContainer operator + (ObjContainer &) const;
	void operator += (ObjContainer &);
	
	friend bool operator > (ObjContainer &, ObjContainer &);
	friend bool operator < (ObjContainer &, ObjContainer &);
	friend bool operator >= (ObjContainer &, ObjContainer &);
	friend bool operator <= (ObjContainer &, ObjContainer &);

inline friend bool operator < (const ObjContainer &rOC1, const ObjContainer &rOC2)
	{ return (ObjContainer &)rOC1 < (ObjContainer &)rOC2; }

	void CondSwapX()
	{
	KoOrd dXMin = XMin();
	KoOrd dXMax = XMax();

		if (dXMin > dXMax) {
			SetXMin (dXMax);
			SetXMax (dXMin);
		}
	}
	void CondSwapY()
	{
	KoOrd dYMin = YMin();
	KoOrd dYMax = YMax();

		if (dYMin > dYMax) {
			SetYMin (dYMax);
			SetYMax (dYMin);
		}
	}

// Destruktoren
		~ObjContainer (void) {}
};

/////////////////////////////////////////////////////////////////////////////
// KoordinatenPaar - Grundklasse jedes GeometrieObjektes 
class KoordinatenPaar 
{
protected:
	CCSPointGeometry m_pt;

public:
// Konstruktoren
	KoordinatenPaar (void) : m_pt (0.0, 0.0) {}
	KoordinatenPaar (KoOrd x, KoOrd y) : m_pt(double(x), double(y)) {}
	KoordinatenPaar (IDispatch *pIDisp) : m_pt(pIDisp) {}

// Zugriff auf Interface's
	_DGMGeometry *GetGeometry (bool fAddRef = false) 
	{
		if (fAddRef && m_pt.IsValid()) 
			m_pt -> AddRef();
		return m_pt;
	}
	void Assign (IDispatch *pIDisp) { m_pt.Assign(pIDisp); }
	bool IsValid() { return m_pt.IsValid(); }
};

/////////////////////////////////////////////////////////////////////////////
// Punkt 
class Punkt : 
	public KoordinatenPaar 
{
public:
// Konstruktoren
	Punkt (void) : KoordinatenPaar () {}
	Punkt (IDispatch *pIDisp) : KoordinatenPaar(pIDisp) {}
	Punkt (KoOrd x, KoOrd y) : KoordinatenPaar(x, y) {}
	Punkt (const Punkt &rpt) : KoordinatenPaar (rpt.m_pt) {}

// Memberfunktionen
	HRESULT SetX (KoOrd x) { return m_pt.put_X(double(x)); } 
	HRESULT SetY (KoOrd y) { return m_pt.put_Y(double(y)); }
	KoOrd GetX (void) const { double x = 0.0; m_pt.get_X(&x); return KoOrd(x); }
	KoOrd GetY (void) const { double y = 0.0; m_pt.get_Y(&y); return KoOrd(y); }

	int operator== (const Punkt &P) { return ((GetX() == P.GetX()) && (GetY() == P.GetY())); }
	ObjContainer GetCont (void) { KoOrd x = GetX(), y = GetY(); return ObjContainer(x, x, y, y); }

// Destruktoren
		~Punkt (void) {}
};

#else // _TRiAS_VER >= 0x0300

#if !defined(NOKOORDINATENPAAR)
// KoordinatenPaar - Grundklasse jedes GeometrieObjektes ----------------------
class KoordinatenPaar {
protected:
	KoOrd _X;
	KoOrd _Y;

public:
// Konstruktoren
		KoordinatenPaar (void) { _X = 0; _Y = 0; }
		KoordinatenPaar (KoOrd x, KoOrd y) { _X = x; _Y = y; }
};

#if !defined(NOPUNKT)
// Punkt ----------------------------------------------------------------------
class Punkt : public KoordinatenPaar {
public:
// Konstruktoren
		Punkt (void) : KoordinatenPaar () {}
		Punkt (KoOrd x, KoOrd y) :
			KoordinatenPaar (x, y) {}

// Memberfunktionen
	KoOrd &X (void) { return _X; }	// liefern Attributwerte
	KoOrd &Y (void) { return _Y; }
	KoOrd GetX (void) const { return _X; }	// liefern Attributwerte
	KoOrd GetY (void) const { return _Y; }
	int operator== (const Punkt &P) { return ((_X == P._X) && (_Y == P._Y)); }

// Destruktoren
		// keiner
};
#endif // NOPUNKT
#endif // NOKOORDINATENPAAR

#if !defined(NOOBJCONTAINER)
// Kleinstes umschlieáendes Rechteck eines geometrischen Objektes -------------
class ObjContainer {
protected:
	KoOrd _XMin, _XMax;
	KoOrd _YMin, _YMax;

public:
// Konstruktoren
		ObjContainer (KoOrd XMin = 0, KoOrd XMax = 0, 
			      KoOrd YMin = 0, KoOrd YMax = 0);
		ObjContainer (Punkt Pt1, Punkt Pt2);
		ObjContainer (const ObjContainer &);

// Memberfunktionen
	KoOrd &XMin (void) { return _XMin; }	// liefert Referenzen auf Attribute
	KoOrd &XMax (void) { return _XMax; }
	KoOrd &YMin (void) { return _YMin; }
	KoOrd &YMax (void) { return _YMax; }

	void SetXMin (const KoOrd xmin) { _XMin = xmin; }
	void SetXMax (const KoOrd xmax) { _XMax = xmax; }
	void SetYMin (const KoOrd ymin) { _YMin = ymin; }
	void SetYMax (const KoOrd ymax) { _YMax = ymax; }

	KoOrd Breite (void) { return (KoOrdAbs (_XMax-_XMin)); }
	KoOrd Hoehe (void) { return (KoOrdAbs (_YMax-_YMin)); }

	ObjContainer InflateCont (short);	// Container gr”áer/kleiner

	// wenn alle Werte oder die Abmessungen gleich 0 sind, 
	// dann ist der OC inValid
	bool isValid (void) { return ( !((_XMax-_XMin==0)&&(_YMax-_YMin==0)) ); }

// Operator testet Verschnitt zweier ObjeContainer
	bool operator ^ (ObjContainer &);
#if defined(__CV__)
	ObjContainer operator = (Rectangle &);
	operator Rectangle (void);
#else
	ObjContainer operator = (RECT &);
	operator RECT (void);
#endif
	ObjContainer &operator + (ObjContainer &);
	void operator += (ObjContainer &);

friend bool operator > (ObjContainer &, ObjContainer &);
friend bool operator < (ObjContainer &, ObjContainer &);

// Destruktoren
		~ObjContainer (void) {}
};
#endif // NOOBJCONTAINER
#endif // _TRiAS_VER >= 0x0300

#endif // !defined(_OBJCONTX_HXX__09B84F74_1BB6_11D2_9E93_006008447800__INCLUDED_)
