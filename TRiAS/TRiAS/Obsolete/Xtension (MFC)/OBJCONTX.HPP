// Enthaelt ObjContainerDeklaration fuer Erweiterungen
// File: OBJCONTX.HXX

#if !defined(_OBJCONTX_HXX)
#define _OBJCONTX_HXX

typedef long KoOrd;

inline KoOrd KoOrdAbs (KoOrd x) { return (((x) >= 0) ? (x) : -(x)); }
inline KoOrd KoOrdMin (KoOrd x, KoOrd y) { return (((x) < (y)) ? x : y); }
inline KoOrd KoOrdMax (KoOrd x, KoOrd y) { return (((x) > (y)) ? x : y); }

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
	Bool isValid (void) { return ( !((_XMax-_XMin==0)&&(_YMax-_YMin==0)) ); }

// Operator testet Verschnitt zweier ObjeContainer
	Bool operator ^ (ObjContainer &);
	ObjContainer operator = (Rectangle &);
	ObjContainer &operator + (ObjContainer &);
	void operator += (ObjContainer &);

friend Bool operator > (ObjContainer &, ObjContainer &);
friend Bool operator < (ObjContainer &, ObjContainer &);

// Destruktoren
		~ObjContainer (void) {}
};
#endif // NOOBJCONTAINER

#endif // _OBJCONTX_HXX
