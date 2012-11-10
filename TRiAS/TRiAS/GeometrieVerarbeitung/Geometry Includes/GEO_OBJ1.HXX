/*
 File: GEO_OBJ1.HXX

 Geometrieobjekte (Kreis, Ellipsen)

 erstellt: J. Benkenstein               am: 20.11.91

*/


#if !defined(_GEO_OBJ1_HXX)
#define _GEO_OBJ1_HXX


#if !defined(NOELLIPSEN)
// Ellipsen -------------------------------------------------------------------
// Plural vermeidet Namenskonflikt mit WINDOWS-Funktion "Ellipse"
class _GEOMETR_ENTRY Ellipsen {
private:
	EPunkt _MP;      // Schnittpunkt der Halbachsen
	long  _Xa;      // Halbachsen-Größen, x-Achse
	long  _Yb;      //                    y-Achse

// Konstruktoren
public:
		Ellipsen (void) : _MP (0, 0)    // Mittelpunkt = (0, 0)
			 { _Xa = 0; _Yb = 0; }
		Ellipsen (EPunkt &Pkt, long a, long b = 0);
		Ellipsen (KoOrd x, KoOrd y, long a, long b = 0);

// Memberfunktionen
	long &Xa (void)  { return _Xa; }
	long &Xb (void)  { return _Yb; }
	EPunkt &MP (void) { return _MP; }

// Destruktor
		// keiner
};
#endif // NOELLIPSEN



#if !defined(NOKREIS)
// Kreis -------------------------------------------------------------------
class _GEOMETR_ENTRY Kreis : public Ellipsen {
// keine eigenen Attribute

public:
// Konstruktoren
		Kreis (void) {}
		Kreis (EPunkt &Pkt, long Radius)
			: Ellipsen(Pkt, Radius) {}
		Kreis (KoOrd Mx, KoOrd My, long Radius) // übergebe Mittelpunkt
			: Ellipsen(Mx, My, Radius) {}

// Memberfunktionen
	long &Radius(void) { return Xa(); }
	ObjTyp isA (void);

// Destruktor
		// keiner
};
#endif // NOKREIS



#if !defined(NOGEOKREIS)
// GeoKreis -------------------------------------------------------------------
class _GEOMETR_ENTRY GeoKreis : public GeoObjekt, public Kreis {
// keine eigenen Attribute

// Konstruktoren
public:
		GeoKreis (long ObjNr, ulong Id = 0);
		GeoKreis (long ObjNr, ulong Id,  EPunkt &Pkt, long Radius);

// Memberfunktionen
	ObjTyp isA ();

// Destruktor
		// keiner
};
#endif // NOGEOKREIS

#endif // _GEO_OBJ1_HXX
