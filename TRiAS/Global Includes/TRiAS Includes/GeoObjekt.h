// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 06/11/1998 09:38:08 PM
//
// @doc
// @module GeoObjekt.h | Elementare Geometrie-Objekte

#if !defined(_GEOOBJEKT_H__BC145183_013F_11D2_864C_00600875138A__INCLUDED_)
#define _GEOOBJEKT_H__BC145183_013F_11D2_864C_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <VisInfo.hxx>

/////////////////////////////////////////////////////////////////////////////
// GeometrieObjekte
#include <CSPoint.h>
#include <CSPointGeom.h>
#include <CSLineGeom.h>
#include <CSRectGeom.h>
#include <CSBoundaryGeom.h>

/////////////////////////////////////////////////////////////////////////////
// Hilfsfunktionen 
inline short shortMin (short x, short y) { return min(x, y); }
inline short shortMax (short x, short y) { return max(x, y); }
inline long longMin (long x, long y) { return min(x, y); }
inline long longMax (long x, long y) { return max(x, y); }

inline KoOrd KoOrdAbs (KoOrd x) { return x >= 0 ? x : -x; }
inline KoOrd KoOrdMin (KoOrd x, KoOrd y) { return min(x, y); }
inline KoOrd KoOrdMax (KoOrd x, KoOrd y) { return max(x, y); }

/////////////////////////////////////////////////////////////////////////////
// Forward declarations
class Punkt;
class Kante;
class Masche; 
class Ausdehnung;

/////////////////////////////////////////////////////////////////////////////
// Kleinstes umschließendes Rechteck eines geometrischen Objektes
class ObjContainer 
{
protected:
	CCSRectangleGeometry m_oc;	// Container dieser Kante

public:
// Konstruktoren
_TRIAS02_ENTRY ObjContainer (IDispatch *pOC) : m_oc(pOC) {}
_TRIAS02_ENTRY ObjContainer (_DGMRectangleGeometry *pOC) : m_oc(pOC) {}		// unnötiges QI vermeiden
_TRIAS02_ENTRY ObjContainer (KoOrd XMin = 0, KoOrd XMax = 0, KoOrd YMin = 0, KoOrd YMax = 0);
_TRIAS02_ENTRY ObjContainer (Punkt Pt, Ausdehnung A);
_TRIAS02_ENTRY ObjContainer (Punkt Pt1, Punkt Pt2);
_TRIAS02_ENTRY ObjContainer (const ObjContainer &);

	ObjContainer (Rectangle &r);

// Memberfunktionen
	KoOrd XMin (void) const { double t; const_cast<ObjContainer *>(this) -> m_oc.get_XMin(&t); return KoOrd(t); }
	KoOrd XMax (void) const { double t; const_cast<ObjContainer *>(this) -> m_oc.get_XMax(&t); return KoOrd(t); }
	KoOrd YMin (void) const { double t; const_cast<ObjContainer *>(this) -> m_oc.get_YMin(&t); return KoOrd(t); }
	KoOrd YMax (void) const { double t; const_cast<ObjContainer *>(this) -> m_oc.get_YMax(&t); return KoOrd(t); }

	void SetXMin (const KoOrd xmin) { m_oc.put_XMin (double(xmin)); }
	void SetXMax (const KoOrd xmax) { m_oc.put_XMax (double(xmax)); }
	void SetYMin (const KoOrd ymin) { m_oc.put_YMin (double(ymin)); }
	void SetYMax (const KoOrd ymax) { m_oc.put_YMax (double(ymax)); }

	KoOrd Breite (void) { return KoOrdAbs(XMax()-XMin()); }
	KoOrd Hoehe (void) { return KoOrdAbs(YMax()-YMin()); }
	KoOrd CentreX () { return KoOrdAbs(XMax()+XMin())/2.0; }
	KoOrd CentreY () { return KoOrdAbs(YMax()+YMin())/2.0; }

_TRIAS02_ENTRY ObjContainer InflateCont (int);			// Container größer/kleiner
_TRIAS02_ENTRY ObjContainer &ShiftCont (Ausdehnung &); // Container verschieben

// wenn alle Werte oder die Abmessungen gleich 0 sind, dann ist der OC inValid
	bool isValid (void) { return ( !( (Breite() == 0.0) && (Hoehe() == 0.0) ) ); }
	bool HasSignificantSize (double dEps = 10.0e8) { return ( !( (Breite() <= (CentreX()/dEps)) && (Hoehe() <= (CentreY()/dEps)) ) ); }

// Zuweisungsoperator
	ObjContainer &operator = (const ObjContainer &rhs)
		{ if (&rhs != this) m_oc = const_cast<ObjContainer &>(rhs).m_oc; return *this; }

// Operator testet Verschnitt zweier ObjeContainer
_TRIAS02_ENTRY bool operator ^ (ObjContainer &);
_TRIAS02_ENTRY ObjContainer operator + (ObjContainer &) const;
_TRIAS02_ENTRY void operator += (ObjContainer &);
_TRIAS02_ENTRY ObjContainer operator & (ObjContainer &) const;
_TRIAS02_ENTRY void operator &= (ObjContainer &);

_TRIAS02_ENTRY Ausdehnung operator - (ObjContainer &OC);
	
_TRIAS02_ENTRY friend bool operator > (ObjContainer &, ObjContainer &);
_TRIAS02_ENTRY friend bool operator < (ObjContainer &, ObjContainer &);
_TRIAS02_ENTRY friend bool operator >= (ObjContainer &, ObjContainer &);
_TRIAS02_ENTRY friend bool operator <= (ObjContainer &, ObjContainer &);

inline friend bool operator < (const ObjContainer &rOC1, const ObjContainer &rOC2)
	{ return (ObjContainer &)rOC1 < (ObjContainer &)rOC2; }

	ObjContainer &operator = (Rectangle &);
	operator _DGMRectangleGeometry *() const { return (_DGMRectangleGeometry *)m_oc; }

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
// Kante 
class Kante 
{
protected:
	CCSLineGeometry m_line;
	CCSRectangleGeometry m_oc;	// Container dieser Kante

public:
// Konstruktoren
	Kante () {}
	Kante (long lCnt, KoOrd *pdX, KoOrd *pdY)
		: m_line(lCnt, pdX, pdY) 
	{
	__Interface<ITRiASSimpleRectangle> cont;

		__Interface<ITRiASCSGeometryProperties>(m_line) -> get_Envelope(cont.ppi());	// Container berechnen
		m_oc.Assign(cont);
	}
	Kante (const Kante &rK) 
		: m_line(const_cast<Kante &>(rK).GetGeometry()), m_oc(const_cast<Kante &>(rK).GetOC()) {}
	Kante (IDispatch *pIDisp, _DGMRectangleGeometry *pICont = NULL) 
		: m_line(pIDisp), m_oc(pICont) 
	{
		if (NULL == pICont) {
		__Interface<ITRiASSimpleRectangle> cont;

			__Interface<ITRiASCSGeometryProperties>(m_line) -> get_Envelope(cont.ppi());	// Container berechnen
			m_oc.Assign(cont);
		}
	}
	Kante (_DGMPolylineGeometry *pIDisp, _DGMRectangleGeometry *pICont = NULL) 
		: m_line(pIDisp), m_oc(pICont) 
	{
		if (NULL == pICont) {
		__Interface<ITRiASSimpleRectangle> cont;

			__Interface<ITRiASCSGeometryProperties>(m_line) -> get_Envelope(cont.ppi());	// Container berechnen
			m_oc.Assign(cont);
		}
	}

// Memberfunktionen
_TRIAS02_ENTRY Kante &operator =(const Kante &);	// Zuweisung überladen

// interne Variablenwerte liefern

_TRIAS02_ENTRY ObjContainer maxCont (const ObjContainer &);		// umschließender Cont
_TRIAS02_ENTRY ObjContainer minCont (const ObjContainer &);		// k.g.Container
_TRIAS02_ENTRY void GetKante (KoOrd x[], KoOrd y[], long &);	// Geometrie

_TRIAS02_ENTRY ObjContainer GetCont (void);
_TRIAS02_ENTRY void SetCont (KoOrd Cont[]);					// OCont setzen

// interne Werte modifizieren Punkt(e) hinzufügen
_TRIAS02_ENTRY void AddPunkt (const Kante &K, long Anzahl, long Index);
_TRIAS02_ENTRY void AddPunkt (KoOrd x[], KoOrd y[], long Len, long Index);

// Destruktoren
	~Kante (void) {}

_TRIAS02_ENTRY long ASP (void) const;				// Anzahl der Stützpunkte
_TRIAS02_ENTRY Punkt SP (long n = 0) const;			// Stützpunkt n liefern

	typedef Point (* CONVERTPROC)(KoOrd x, KoOrd y);			// Prototyp der KOnvertierungsfunktion

_TRIAS02_ENTRY Point SP (CONVERTPROC pFcn, long n = 0) const;	// Stützpunkt n konvertiert liefern

// Zugriff auf Interface's
	_DGMPolylineGeometry *GetGeometry (bool fAddRef = false) 
	{
		if (fAddRef && m_line.IsValid()) 
			m_line -> AddRef();
		return m_line;
	}
	_DGMRectangleGeometry *GetOC (bool fAddRef = false) 
	{
		if (fAddRef && m_oc.IsValid()) 
			m_oc -> AddRef();
		return m_oc;
	}
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
	KoordinatenPaar (_DGMPointGeometry *pIPt) : m_pt(pIPt) {}

// Zugriff auf Interface's
	_DGMPointGeometry *GetGeometry (bool fAddRef = false) 
	{
		if (fAddRef && m_pt.IsValid()) 
			m_pt -> AddRef();
		return m_pt;
	}
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
	Punkt (_DGMPointGeometry *pIPt) : KoordinatenPaar(pIPt) {}
	Punkt (KoOrd x, KoOrd y) : KoordinatenPaar(x, y) {}
	Punkt (const Punkt &rpt) : KoordinatenPaar (rpt.m_pt) {}
	Punkt (const Point &rpt) : KoordinatenPaar (KoOrd(rpt.GetX()), KoOrd(rpt.GetY())) {}

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

/////////////////////////////////////////////////////////////////////////////
// Ausdehnung -- Größe eines Rechtecks 
class Ausdehnung : 
	public KoordinatenPaar 
{
public:
// Konstruktoren
	Ausdehnung (void) : KoordinatenPaar () {}
	Ausdehnung (KoOrd x, KoOrd y) : KoordinatenPaar (x, y) {}
	Ausdehnung (const Ausdehnung &rhs) : KoordinatenPaar (rhs.m_pt) {}

// Memberfunktionen
	KoOrd GetBreite (void) { double x = 0.0; m_pt.get_X(&x); return KoOrd(x); }		// liefern Attributwerte
	KoOrd GetHoehe (void) { double y = 0.0; m_pt.get_Y(&y); return KoOrd(y); }
	HRESULT SetBreite (KoOrd b) { return m_pt.put_X(double(b)); }	// setzen Attributwerte
	HRESULT SetHoehe (KoOrd h) { return m_pt.put_Y(double(h)); }	
};

/////////////////////////////////////////////////////////////////////////////
// Fläche 
class Masche 
{
protected:
	CCSBoundaryGeometry m_area;
	CCSRectangleGeometry m_oc;

public:
// Konstruktoren
	Masche (void) {} 
	Masche (long lCnt, KoOrd *pdX, KoOrd *pdY, bool fIsBoundary = false)
		: m_area (lCnt, pdX, pdY, fIsBoundary) 
	{
	__Interface<ITRiASSimpleRectangle> cont;

		__Interface<ITRiASCSGeometryProperties>(m_area) -> get_Envelope(cont.ppi());	// Container berechnen
		m_oc.Assign(cont);
	}
	Masche (const Masche &rhs)
		: m_area(rhs.m_area), m_oc(rhs.m_oc) {}
	Masche (IDispatch *pIDisp, _DGMRectangleGeometry *pICont, bool fIsBoundary = false) 
		: m_area(pIDisp, fIsBoundary), m_oc(pICont) 
	{
		if (NULL == pICont) {
		__Interface<ITRiASSimpleRectangle> cont;

			__Interface<ITRiASCSGeometryProperties>(m_area) -> get_Envelope(cont.ppi());	// Container berechnen
			m_oc.Assign(cont);
		}
	}
	Masche (_DGMGeometry *pIDisp, _DGMRectangleGeometry *pICont, bool fIsBoundary = false) 
		: m_area(pIDisp, fIsBoundary), m_oc(pICont) 
	{
		if (NULL == pICont) {
		__Interface<ITRiASSimpleRectangle> cont;

			__Interface<ITRiASCSGeometryProperties>(m_area) -> get_Envelope(cont.ppi());	// Container berechnen
			m_oc.Assign(cont);
		}
	}

// Memberfunktionen
_TRIAS02_ENTRY Masche &operator =(const Masche &);	// Zuweisung überladen
_TRIAS02_ENTRY long ASP (long **ppiCnts = NULL);	// liefert Stützpunktanzahl Gesamtanzahl und kantenweise

// ContainerOperationen
_TRIAS02_ENTRY ObjContainer maxCont (const ObjContainer &);	// umschließendes Rechteck
_TRIAS02_ENTRY ObjContainer minCont (const ObjContainer &);	// k.g. Rechteck (Schnitt)

_TRIAS02_ENTRY ObjContainer GetCont (void);
_TRIAS02_ENTRY void SetCont (KoOrd Cont[]);		// Container setzen

// Kante(n) hinzufügen
_TRIAS02_ENTRY HRESULT AddKante (long Len, KoOrd *pdX, KoOrd *pdY, int Index = -1);

// Destruktoren
	~Masche (void) {}

_TRIAS02_ENTRY long KantenAnz (void);			// liefert Kantenanzahl
_TRIAS02_ENTRY Kante KA (long n = 0);			// Kante n liefern

// Zugriff auf Interface's
	_DGMGeometry *GetGeometry (bool fAddRef = false) 
	{
		if (fAddRef && m_area.IsValid()) 
			m_area -> AddRef();
		return m_area;
	}
	_DGMRectangleGeometry *GetOC (bool fAddRef = false) 
	{
		if (fAddRef && m_oc.IsValid()) 
			m_oc -> AddRef();
		return m_oc;
	}
};

/////////////////////////////////////////////////////////////////////////////
// Ellipsen 
// Plural vermeidet Namenskonflikt mit WINDOWS-Funktion "Ellipse"
class Ellipsen 
{
private:
	Punkt _MP;	// Schnittpunkt der Halbachsen
	long  _Xa;	// Halbachsen-Größen, x-Achse, y-Achse
	long  _Yb;

// Konstruktoren
public:
	Ellipsen (void) : _MP (0, 0) 	// Mittelpunkt = (0, 0)
		{ _Xa = 0; _Yb = 0; }
	Ellipsen (Punkt &Pkt, long a, long b = 0)
		: _MP(Pkt), _Xa(a), _Yb(0 != b ? b : a) {}
	Ellipsen (KoOrd x, KoOrd y, long a, long b = 0)
		: _MP(x, y), _Xa(a), _Yb(0 != b ? b : a) {}

// Memberfunktionen
	long &Xa (void)  { return _Xa; }
	long &Xb (void)  { return _Yb; }
	Punkt &MP (void) { return _MP; }

	ObjContainer GetCont (void)
		{ KoOrd x = _MP.GetX(), y = _MP.GetY(); return ObjContainer(x-_Xa, x+_Xa, y-_Yb, y+_Yb); }

_TRIAS02_ENTRY void GetEllipse (KoOrd x[], KoOrd y[], long &rlCnt);	// Geometrie
};

/////////////////////////////////////////////////////////////////////////////
// Kreis 
class Kreis : 
	public Ellipsen 
{
public:
// Konstruktoren
	Kreis (void) {}
	Kreis (Punkt &Pkt, long Radius) 
		: Ellipsen(Pkt, Radius) {}
	Kreis (KoOrd Mx, KoOrd My, long Radius) // Mittelpunkt/Radius
		: Ellipsen(Mx, My, Radius) {}

// Memberfunktionen
	long &Radius(void) { return Xa(); }
};

/////////////////////////////////////////////////////////////////////////////
// GeoObjekt von diesem allgemeinen GeoObjekt sind alle anderen abgeleitet

typedef struct tagOBJGEOMETRIE OBJGEOMETRIE;
class GeoDB;

class GeoObjekt 
{
protected:
	INT_PTR _ObjNr;	// Objektnummer in der DB
	INT_PTR _Id;	// Objektidentifikator
	GeoDB &m_rDB;

public:
// Konstruktor
	GeoObjekt (GeoDB &rDB, INT_PTR ObjNr, INT_PTR Id = 0)
		: m_rDB(rDB), _ObjNr(ObjNr), _Id(Id) {}

virtual ObjTyp isA (void) = 0;							// liefert Objekttyp
virtual bool GetObjContainer (ObjContainer &rOC) = 0;	// liefert ObjektContainer
virtual long RetrievePureGeometrie (KoOrd **ppX, KoOrd **ppY, long **ppiKCnt = NULL) = 0;
virtual _DGMGeometry *GetGeometry (bool fAddRef = false) = 0;
virtual GEOMETRYTYPE GType() = 0;

// Destruktor
virtual ~GeoObjekt (void) {}

// inlines
	INT_PTR & Id (void) { return _Id; }
	INT_PTR & ObjNr (void) { return _ObjNr; }

	INT_PTR GetONr() const { return _ObjNr; }
	INT_PTR GetIdent() const { return _Id; }

	GeoDB &DB() { return m_rDB; }
	const GeoDB &cDB() const { return m_rDB; }
};

/////////////////////////////////////////////////////////////////////////////
// GeoPunkt 
class GeoPunkt : 
	public Punkt, 
	public GeoObjekt 
{
public:
// Konstruktoren
		GeoPunkt (GeoDB &rDB, INT_PTR ObjNr, INT_PTR Id = 0)
			: GeoObjekt (rDB, ObjNr, Id) {}
		GeoPunkt (GeoDB &rDB, INT_PTR ObjNr, INT_PTR Id, const Punkt &Pkt)
			: GeoObjekt (rDB, ObjNr, Id), Punkt (Pkt) {}
		GeoPunkt (const GeoPunkt &DBP)
			: GeoObjekt (const_cast<GeoDB &>(DBP.cDB()), DBP.GetONr(), DBP.GetIdent()), Punkt (DBP) {}

// Memberfunktionen
_TRIAS02_ENTRY GeoPunkt &operator =(const GeoPunkt &);
_TRIAS02_ENTRY ObjTyp isA (void);
_TRIAS02_ENTRY bool GetObjContainer (ObjContainer &rOC);	// liefert ObjektContainer
_TRIAS02_ENTRY long RetrievePureGeometrie (KoOrd **ppX, KoOrd **ppY, long **pKCnt = NULL);
_TRIAS02_ENTRY _DGMGeometry *GetGeometry (bool fAddRef = false);
_TRIAS02_ENTRY GEOMETRYTYPE GType();

	~GeoPunkt (void) {}
};

/////////////////////////////////////////////////////////////////////////////
// GeoKante 
class GeoKante : 
	public Kante, 
	public GeoObjekt 
{
public:
// Konstruktoren
		GeoKante (GeoDB &rDB, INT_PTR ObjNr, INT_PTR Id = 0)
			: GeoObjekt (rDB, ObjNr, Id) {}
		GeoKante (GeoDB &rDB, INT_PTR ObjNr, INT_PTR Id, const Kante &rK)
			: GeoObjekt (rDB, ObjNr, Id), Kante (rK) {}
		GeoKante (const GeoKante &rK)
			: GeoObjekt (const_cast<GeoDB &>(rK.cDB()), const_cast<GeoKante &>(rK).ObjNr(), rK._Id), Kante (rK) {}

// Memberfunktionen
_TRIAS02_ENTRY GeoKante &operator =(const GeoKante &);
_TRIAS02_ENTRY ObjTyp isA (void);
_TRIAS02_ENTRY bool GetObjContainer (ObjContainer &rOC);	// liefert ObjektContainer
_TRIAS02_ENTRY long RetrievePureGeometrie (KoOrd **ppX, KoOrd **ppY, long **pKCnt = NULL);
_TRIAS02_ENTRY _DGMGeometry *GetGeometry (bool fAddRef = false);
_TRIAS02_ENTRY GEOMETRYTYPE GType();

		~GeoKante (void) {}
};

/////////////////////////////////////////////////////////////////////////////
// GeoFläche 
class GeoFlaeche : 
	public Masche, 
	public GeoObjekt 
{
public:
// Konstruktoren
		GeoFlaeche (GeoDB &rDB, INT_PTR ObjNr, INT_PTR Id = 0)
			: GeoObjekt (rDB, ObjNr, Id) {}
		GeoFlaeche (GeoDB &rDB, INT_PTR ObjNr, INT_PTR Id, const Masche &rM)
			: GeoObjekt (rDB, ObjNr, Id), Masche (rM) {}
		GeoFlaeche (const GeoFlaeche &rM)
			: GeoObjekt (const_cast<GeoDB &>(rM.cDB()), rM.GetONr(), rM.GetIdent()), Masche (rM) {}

// Memberfunktionen
_TRIAS02_ENTRY GeoFlaeche &operator =(const GeoFlaeche &);
_TRIAS02_ENTRY ObjTyp isA (void);
_TRIAS02_ENTRY bool GetObjContainer (ObjContainer &rOC);	// liefert ObjektContainer
_TRIAS02_ENTRY long RetrievePureGeometrie (KoOrd **ppX, KoOrd **ppY, long **pKCnt = NULL);
_TRIAS02_ENTRY _DGMGeometry *GetGeometry (bool fAddRef = false);
_TRIAS02_ENTRY GEOMETRYTYPE GType();

		~GeoFlaeche (void) {}
};

/////////////////////////////////////////////////////////////////////////////
//
class GeoKreis : 
	public Kreis,
	public GeoObjekt
{
public:
// Konstruktoren
	GeoKreis (GeoDB &rDB, INT_PTR ObjNr, INT_PTR Id = 0)
		: GeoObjekt (rDB, ObjNr, Id) {}
	GeoKreis (GeoDB &rDB, INT_PTR ObjNr, INT_PTR Id,	Punkt &Pkt, long Radius)
		: GeoObjekt (rDB, ObjNr, Id), Kreis(Pkt, Radius) {}
	GeoKreis (const GeoKreis &rK)
		: GeoObjekt (const_cast<GeoDB &>(rK.cDB()), rK.GetONr(), rK.GetIdent()), Kreis(rK) {}

// Memberfunktionen
_TRIAS02_ENTRY GeoKreis &operator =(const GeoKreis &);
_TRIAS02_ENTRY ObjTyp isA (void);
_TRIAS02_ENTRY bool GetObjContainer (ObjContainer &rOC);	// liefert ObjektContainer
_TRIAS02_ENTRY long RetrievePureGeometrie (KoOrd **ppX, KoOrd **ppY, long **pKCnt = NULL);
_TRIAS02_ENTRY _DGMGeometry *GetGeometry (bool fAddRef = false);
_TRIAS02_ENTRY GEOMETRYTYPE GType();

// Destruktor
		~GeoKreis (void) {}
};

/////////////////////////////////////////////////////////////////////////////
// declarations only 
_TRIAS02_ENTRY VisType OTypToVTyp (ObjTyp iOTyp);
_TRIAS02_ENTRY ObjTyp VTypToOTyp (VisType iVTyp);
_TRIAS02_ENTRY ErrCode FindID (HPROJECT hPr, long ON, long *pID);

#endif // !defined(_GEOOBJEKT_H__BC145183_013F_11D2_864C_00600875138A__INCLUDED_)
