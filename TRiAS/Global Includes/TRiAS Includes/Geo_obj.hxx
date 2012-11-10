// Geometrieobjekte (Punkt, Linie, Fläche)
// File: GEO_OBJ.HXX

// IRISWIN: %W%	%E%

#ifndef _GEO_OBJ_HXX
#define _GEO_OBJ_HXX

#undef HUGELIMIT
#define	HUGELIMIT	(64000/sizeof(Punkt))

#include <geo_inl.hxx>

#if !defined(NOOBJCONTAINER)
// Kleinstes umschließendes Rechteck eines geometrischen Objektes -------------
class ObjContainer {
protected:
	KoOrd _XMin, _XMax;
	KoOrd _YMin, _YMax;

public:
// Konstruktoren
	_TRIAS02_ENTRY EXPORT02 ObjContainer (KoOrd XMin = 0, KoOrd XMax = 0, 
				       KoOrd YMin = 0, KoOrd YMax = 0);
	_TRIAS02_ENTRY ObjContainer (Punkt Pt, Ausdehnung A);
	_TRIAS02_ENTRY EXPORT02 ObjContainer (Punkt Pt1, Punkt Pt2);
	_TRIAS02_ENTRY EXPORT02 ObjContainer (const ObjContainer &);
	ObjContainer (Rectangle &r) { *this = r; }

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

_TRIAS02_ENTRY ObjContainer EXPORT02 InflateCont (short);	// Container größer/kleiner
_TRIAS02_ENTRY ObjContainer & ShiftCont (Ausdehnung &);	// Container verschieben

	// wenn alle Werte oder die Abmessungen gleich 0 sind, 
	// dann ist der OC inValid
	bool isValid (void) { return ( !((_XMax-_XMin==0)&&(_YMax-_YMin==0)) ); }
//			|| ((_XMin!=0)||(_XMax!=0)||(_YMin!=0)||(_YMax!=0))); 

// Operator testet Verschnitt zweier ObjeContainer
_TRIAS02_ENTRY bool operator ^ (ObjContainer &);
_TRIAS02_ENTRY ObjContainer operator = (Rectangle &);
_TRIAS02_ENTRY ObjContainer & operator + (ObjContainer &);
_TRIAS02_ENTRY void operator += (ObjContainer &);
_TRIAS02_ENTRY ObjContainer & operator & (ObjContainer &);
_TRIAS02_ENTRY void operator &= (ObjContainer &);

_TRIAS02_ENTRY Ausdehnung operator - (ObjContainer &OC);
	
_TRIAS02_ENTRY friend bool operator > (ObjContainer &, ObjContainer &);
_TRIAS02_ENTRY friend bool operator < (ObjContainer &, ObjContainer &);
_TRIAS02_ENTRY friend bool operator >= (ObjContainer &, ObjContainer &);
_TRIAS02_ENTRY friend bool operator <= (ObjContainer &, ObjContainer &);

#if !defined(WIN16)
inline friend bool operator < (const ObjContainer &rOC1, const ObjContainer &rOC2)
	{ return (ObjContainer &)rOC1 < (ObjContainer &)rOC2; }
#endif // WIN16

// Destruktoren
		~ObjContainer (void) {}
};
#endif // NOOBJCONTAINER

#if defined(__WATCOMC__)
#pragma warning 004 5;
#endif

#if !defined(NOKANTE)
// Kante ----------------------------------------------------------------------
class Kante {
protected:
	Punkt *_SPF;			// Stützpunktfolge
	long _Size;			// Anzahl der Stützpunkte
	ObjContainer *_OCont;		// Container dieser Kante

// Konstruktoren
		Kante (long Size, Punkt* SPF);
public:
		Kante (void) { _SPF = NULL; _Size = 0; _OCont = NULL; }
	_TRIAS02_ENTRY EXPORT02 Kante (KoOrd x[], KoOrd y[], long);
	_TRIAS02_ENTRY EXPORT02 Kante (Punkt Pt[], long);
	_TRIAS02_ENTRY EXPORT02 Kante (const Kante &);

// Memberfunktionen
_TRIAS02_ENTRY void EXPORT02 operator =(const Kante &);	// Zuweisung überladen

// interne Variablenwerte liefern
	long ASP (void) const { return _Size; }	// Anzahl der Stützpunkte
_TRIAS02_ENTRY ObjContainer EXPORT02 GetCont (void);

_TRIAS02_ENTRY ObjContainer EXPORT02 maxCont (ObjContainer &);		// umschließender Cont
_TRIAS02_ENTRY ObjContainer minCont (ObjContainer &);		// k.g.Container
inline 	Punkt &SP (long n = 0) const; 		// Stützpunkt n liefern
_TRIAS02_ENTRY void EXPORT02 GetKante (KoOrd x[], KoOrd y[], long &);	// Geometrie

// interne Werte modifizieren
	// Punkt(e) addieren
_TRIAS02_ENTRY void AddPunkt (const Kante &K, long Anzahl, long Index);
_TRIAS02_ENTRY void AddPunkt (KoOrd x[], KoOrd y[], long Len, long Index);

_TRIAS02_ENTRY void EXPORT02 SetCont (long Cont[]);		// OCont setzen

// Destruktoren
	_TRIAS02_ENTRY EXPORT02 ~Kante (void);
};
#endif // NOKANTE

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
class Punkt : 
	public KoordinatenPaar 
{
public:
// Konstruktoren
		Punkt (void) : KoordinatenPaar () {}
		Punkt (KoOrd x, KoOrd y) :
			KoordinatenPaar (x, y) {}
		Punkt (const Point &rpt) :
			KoordinatenPaar (rpt.GetX(), rpt.GetY()) {}

// Memberfunktionen
	KoOrd &X (void) { return _X; }	// liefern Attributwerte
	KoOrd &Y (void) { return _Y; }
	KoOrd GetX (void) const { return _X; }	// liefern Attributwerte
	KoOrd GetY (void) const { return _Y; }

	int operator== (const Punkt &P) { return ((_X == P._X) && (_Y == P._Y)); }
_TRIAS02_ENTRY bool operator ! ();  // true, wenn Punkt ungültig, sonst false
_TRIAS02_ENTRY operator bool ();    // true, wenn Punkt gültig, sonst false
	ObjContainer GetCont (void) { return ObjContainer (X(), X(), Y(), Y()); }

// Destruktoren
		~Punkt (void) {}
};
#endif // NOPUNKT

#if !defined(NOAUSDEHNUNG)
// Ausdehnung -- Größe eines Rechtecks ----------------------------------------
class Ausdehnung : public KoordinatenPaar {
public:
// Konstruktoren
		Ausdehnung (void) : KoordinatenPaar () {}
		Ausdehnung (KoOrd x, KoOrd y) :
			KoordinatenPaar (x, y) {}

// Memberfunktionen
	KoOrd &Breite (void) { return _X; }	// liefern Attributwerte
	KoOrd &Hoehe (void) { return _Y; }

// Destruktoren
		// keiner
};
#endif // NOAUSDEHNUNG
#endif // NOKOORDINATENPAAR

#if !defined(NOMASCHE)
// Fläche ---------------------------------------------------------------------
class Masche {
protected:
	Kante *_KAF;			// Kantenfolge
	short _Size;			// Anzahl der Kanten
	ObjContainer *_OCont;		// Container dieser Fläche

// Konstruktoren
	_TRIAS02_ENTRY Masche (Punkt* SPF, long Size); // nur eine Kante
public:
		Masche (void) { _KAF = NULL; _Size = 0; _OCont = NULL; }
	_TRIAS02_ENTRY EXPORT02 Masche (KoOrd x[], KoOrd y[], long Len); // nur eine Kante
	_TRIAS02_ENTRY EXPORT02 Masche (Kante *Flaeche, short);	  // mehrere Kanten
	_TRIAS02_ENTRY Masche (const Masche &);		 // Copy-Konstruktor

// Memberfunktionen
_TRIAS02_ENTRY void EXPORT02 operator =(const Masche &);	// Zuweisung überladen

	short KantenAnz (void) const { return _Size; } // liefert Kantenanzahl
_TRIAS02_ENTRY long EXPORT02 ASP (void);	// liefert Gesamtanzahl der Stützpunkte
_TRIAS02_ENTRY ObjContainer EXPORT02 GetCont (void);

_TRIAS02_ENTRY double FlInhalt (Kante& K, class CoordTrans *pCTF); // berechnet den vorzeichenbehafteten
	// Inhalt einer geschlossenen Kante (Fläche), der bei einem
	// Fehler gleich 0 ist
_TRIAS02_ENTRY double EXPORT02 Inhalt (CoordTrans *pCTF); 
	// berechnet den Flächeninhalt aller in einer Masche
	// enthaltenen Flächen, der bei einem Fehler gleich 0 ist
_TRIAS02_ENTRY double EXPORT02 SchwerPunkt (Punkt &Pt); // berechnet den Flächeninhalt (vor-
	// zeichenbehaftet) und Schwerpunkt der äußeren Masche (ohne 
	// Löcher) einer Fläche.
_TRIAS02_ENTRY ObjContainer EXPORT02 maxCont (ObjContainer &);	// umschließendes Rechteck
_TRIAS02_ENTRY ObjContainer minCont (ObjContainer &);	// k.g. Rechteck (Schnitt)
	Kante &KA (short n = 0) const {		// Kante n liefern
		return (((n >= 0) && (n < _Size)) ? _KAF[n] : _KAF[0]);
	}

// Kante(n) hinzufügen
_TRIAS02_ENTRY void AddKante (const Masche &, short Anzahl, short Index);
_TRIAS02_ENTRY void EXPORT02 AddKante (KoOrd x[], KoOrd y[], long Len, short Index);

// Punkt(e) zu einer der Kanten hinzufügen
_TRIAS02_ENTRY void AddPunkt (const Kante &K, long KAnz, long KIndex, short MIndex);
_TRIAS02_ENTRY void AddPunkt (KoOrd x[], KoOrd y[], long Len, long KIndex, short MIndex);

// Container setzen
_TRIAS02_ENTRY void EXPORT02 SetCont (long Cont[]);

// Destruktoren
	_TRIAS02_ENTRY EXPORT02 ~Masche (void);
};
#endif // NOMASCHE


#if !defined(NOGEOOBJEKT)
// FunktionsDeklarationen -----------------------------------------------------
_TRIAS02_ENTRY bool EXPORT02 GetObjContainer (GeoObjekt *, ObjContainer &);

// GeoObjekt ------------------------------------------------------------------
// von diesem allgemeinen GeoObjekt sind alle anderen abgeleitet

typedef struct tagOBJGEOMETRIE OBJGEOMETRIE;
class CoordTrans;

class GeoObjekt {
private:
	long _ObjNr;	// Objektnummer in der DB

protected:
	long _Id;	// Objektidentifikator
	GeoDB &m_rDB;

public:
// Konstruktor
	_TRIAS02_ENTRY EXPORT02 GeoObjekt (GeoDB &rDB, long ObjNr, long Id = 0);

// pure virtual functions
virtual	ObjTyp	isA (void) = 0;			  // liefert Objekttyp
virtual GeoObjekt* operator+ (long Dehnung) = 0;  // Buffering

// Methoden
	long & Id (void) { return _Id; }
	long & ObjNr (void) { return _ObjNr; }
	long GetONr() const { return _ObjNr; }
	long OffsetON (long Offset) { return (_ObjNr += Offset); }
	GeoDB &DB() { return m_rDB; }
	const GeoDB &cDB() const { return m_rDB; }

	bool RetrieveGeometrie (OBJGEOMETRIE *, CoordTrans *);
_TRIAS02_ENTRY long EXPORT02 RetrievePureGeometrie (long **, long **, long ** = NULL);

// Destruktor
virtual	~GeoObjekt (void) {}
};
#endif // NOGEOOBJEKT

#if !defined(NOGEOPUNKT)
// GeoPunkt -------------------------------------------------------------------
class GeoPunkt : public Punkt, public GeoObjekt {
// keine eigenen Attribute

public:
// Konstruktoren
		GeoPunkt (GeoDB &rDB, long ObjNr, long Id = 0)
			: GeoObjekt (rDB, ObjNr, Id) {}
		GeoPunkt (GeoDB &rDB, long ObjNr, long Id , const Punkt &Pkt)
			: GeoObjekt (rDB, ObjNr, Id), Punkt (Pkt) {}
		GeoPunkt (const GeoPunkt &DBP)
			: GeoObjekt ((GeoDB &)DBP.cDB(), ((GeoPunkt &)DBP).ObjNr(), DBP._Id), Punkt (DBP._X, DBP._Y) {}

// Memberfunktionen
_TRIAS02_ENTRY void EXPORT02 operator =(GeoPunkt &);
_TRIAS02_ENTRY GeoObjekt* EXPORT02 operator+ (long Dehnung); // Buffering
_TRIAS02_ENTRY ObjTyp EXPORT02 isA (void);

	virtual	~GeoPunkt (void) {}
};
#endif // NOGEOPUNKT

#if !defined(NOGEOKANTE)
// GeoKante -------------------------------------------------------------------
class GeoKante : public Kante, public GeoObjekt {
// keine eigenen Attribute

private:
// true, wenn alle Zwischenpunkte für Buffering-Operator OK, sonst false
	bool _ZwischenPunkte (Punkt* PV, long Dehnung, long);

public:
// Konstruktoren
		GeoKante (GeoDB &rDB, long ObjNr, long Id = 0)
			: GeoObjekt (rDB, ObjNr, Id) {}
		GeoKante (GeoDB &rDB, long ObjNr, long Id, KoOrd x[], KoOrd y[], long Len)
			: GeoObjekt (rDB, ObjNr, Id), Kante (x, y, Len) {}
		GeoKante (GeoDB &rDB, long ObjNr, long Id, const Kante &K)
			: GeoObjekt (rDB, ObjNr, Id), Kante (K) {}
		GeoKante (const GeoKante &K)
			: GeoObjekt ((GeoDB &)K.cDB(), ((GeoKante &)K).ObjNr(), K._Id), Kante (K._SPF, K._Size) {}
// Memberfunktionen
_TRIAS02_ENTRY void EXPORT02 operator =(const GeoKante &);
_TRIAS02_ENTRY GeoObjekt* EXPORT02 operator+ (long Dehnung);   // Buffering
_TRIAS02_ENTRY ObjTyp EXPORT02 isA (void);

		~GeoKante (void) {}
};
#endif // NOGEOKANTE

#if !defined(NOGEOFLAECHE)
// GeoFläche ------------------------------------------------------------------
class GeoFlaeche : public Masche, public GeoObjekt {
// keine eigenen Attribute

public:
// Konstruktoren
		GeoFlaeche (GeoDB &rDB, long ObjNr, long Id = 0)
			: GeoObjekt (rDB, ObjNr, Id) {}
		GeoFlaeche (GeoDB &rDB, long ObjNr, long Id, KoOrd x[], KoOrd y[], long Len)
			: GeoObjekt (rDB, ObjNr, Id), Masche (x, y, Len) {}
		GeoFlaeche (GeoDB &rDB, long ObjNr, long Id, const Masche &M)
			: GeoObjekt (rDB, ObjNr, Id), Masche (M) {}
		GeoFlaeche (const GeoFlaeche &M)
			: GeoObjekt ((GeoDB &)M.cDB(), ((GeoFlaeche &)M).ObjNr(), M._Id), Masche (M._KAF, M._Size) {}
		GeoFlaeche (GeoDB &rDB, long ObjNr, long Id, Punkt* SPF, long Size)
			: GeoObjekt (rDB, ObjNr, Id), Masche (SPF, Size) {}

// Memberfunktionen
//	void operator =(const GeoFlaeche &);
_TRIAS02_ENTRY GeoObjekt* EXPORT02 operator + (long Dehnung);		// Buffering
_TRIAS02_ENTRY ObjTyp EXPORT02 isA (void);

		~GeoFlaeche (void) {}
};
#endif // NOGEOFLAECHE

#if defined(__WATCOMC__)
#pragma warning 004 1;
#endif

#if !defined(NOKANTE)
// Inline - Memberfunktionen ------------------------------------------------
// Kante
inline Punkt &Kante :: SP (long n) const 
{	// Stützpunkt n liefern
//	return (((n >= 0) && (n < _Size)) ? _SPF[n] : _SPF[0]);
#if defined(WIN16)
	if (_Size > HUGELIMIT)
		return *(((Punkt __huge *)_SPF) + n);
#endif
	return *(_SPF + n);
}

// declarations only -------------------------------------------------------
_TRIAS02_ENTRY VisType EXPORT02 OTypToVTyp (ObjTyp iOTyp);
_TRIAS02_ENTRY ObjTyp EXPORT02 VTypToOTyp (VisType iVTyp);
_TRIAS02_ENTRY ErrCode EXPORT02 FindID (HPROJECT hPr, long ON, long *pID);

#endif // NOKANTE

#endif	// _GEO_OBJ_HXX
