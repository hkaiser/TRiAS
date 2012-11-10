/*

 File: GEO_OBJ1.HXX

 Geometrieobjekte (Kreis, Ellipsen)

 erstellt: J. Benkenstein		am: 20.11.91

*/

#if !defined(_GEO_OBJ1_HXX)
#define _GEO_OBJ1_HXX

#if defined(__WATCOMC__)
#pragma warning 004 5;
#endif

#if !defined(NOELLIPSEN)
// Ellipsen -------------------------------------------------------------------
// Plural vermeidet Namenskonflikt mit WINDOWS-Funktion "Ellipse"
class Ellipsen {
private:
	Punkt _MP;	// Schnittpunkt der Halbachsen
	long  _Xa;	// Halbachsen-Größen, x-Achse
	long  _Yb;	//		      y-Achse

// Konstruktoren
public:
	Ellipsen (void) : _MP (0, 0) 	// Mittelpunkt = (0, 0)
			 { _Xa = 0; _Yb = 0; }
	_TRIAS02_ENTRY EXPORT02 Ellipsen (Punkt &Pkt, long a, long b = 0);
	_TRIAS02_ENTRY Ellipsen (KoOrd x, KoOrd y, long a, long b = 0);

// Memberfunktionen
	long &Xa (void)  { return _Xa; }
	long &Xb (void)  { return _Yb; }
	Punkt &MP (void) { return _MP; }

_TRIAS02_ENTRY ObjContainer GetCont (void);

// Destruktor
		// keiner
};
#endif // NOELLIPSEN

#if !defined(NOKREIS)
// Kreis -------------------------------------------------------------------
class Kreis : public Ellipsen {
// keine eigenen Attribute

public:
// Konstruktoren
		Kreis (void) {}
		Kreis (Punkt &Pkt, long Radius)
	      		: Ellipsen(Pkt, Radius) {}
		Kreis (KoOrd Mx, KoOrd My, long Radius) // übergebe Mittelpunkt
			: Ellipsen(Mx, My, Radius) {}

// Memberfunktionen
	long &Radius(void) { return Xa(); }

// Destruktor
		// keiner
};
#endif // NOKREIS

#if !defined(NOGEOKREIS)
// GeoKreis -------------------------------------------------------------------
class GeoKreis : public GeoObjekt, public Kreis {
// keine eigenen Attribute

// Konstruktoren
public:
		GeoKreis (GeoDB &rDB, long ObjNr, long Id = 0)
			: GeoObjekt (rDB, ObjNr, Id) {}
		GeoKreis (GeoDB &rDB, long ObjNr, long Id,	Punkt &Pkt, long Radius)
			: GeoObjekt (rDB, ObjNr, Id), Kreis(Pkt, Radius) {}

// Memberfunktionen
_TRIAS02_ENTRY ObjTyp EXPORT02 isA (void);
_TRIAS02_ENTRY GeoObjekt* EXPORT02 operator+ (long Dehnung); // Buffering

// Destruktor
		~GeoKreis (void) {}
};
#endif // NOGEOKREIS

#if defined(__WATCOMC__)
#pragma warning 004 1;
#endif

#endif // _GEO_OBJ1_HXX

