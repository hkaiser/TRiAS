// ObjRechteck und Elementarobjekte EPunkt, EKante, EFlaeche
// File: GEO_OBJ.HXX

#ifndef _GEO_OBJ_HXX
#define _GEO_OBJ_HXX

#include "ristypes.hxx"
#include "geo_inl.hxx"
#include "errcodes.hxx"


// Konvertierung von double nach long
inline long DtoL (double D)
{
	if (D > 0)
		return (long)(D + 0.5);
	else
		return (long)(D - 0.5);
}


// Konvertierung von double nach CoOrd
inline CoOrd DtoC (double D)
{
	if (D > 0)
		return (CoOrd)(D + 0.5);
	else
		return (CoOrd)(D - 0.5);
}



class EPunkt;		// Vorabdeklarationen
class EKante;
class EFlaeche;
class Ausdehnung;

#if !defined(NOOBJRECHTECK)
// kleinstes umschließendes Rechteck eines geometrischen Objektes -------------
class _GEOMETR_ENTRY ObjRechteck {
protected:
	KoOrd _XMin, _XMax;
	KoOrd _YMin, _YMax;

public:
// Konstruktoren
		ObjRechteck (KoOrd XMin = 0, KoOrd XMax = 0, KoOrd YMin = 0, KoOrd YMax = 0);
		ObjRechteck (EPunkt Pt, Ausdehnung A);
		ObjRechteck (EPunkt Pt1, EPunkt Pt2);
		ObjRechteck (const ObjRechteck &);

// Memberfunktionen
	KoOrd &XMin (void) { return _XMin; }    // liefert Referenzen auf Attribute
	KoOrd &XMax (void) { return _XMax; }
	KoOrd &YMin (void) { return _YMin; }
	KoOrd &YMax (void) { return _YMax; }

	void SetXMin (const KoOrd xmin) { _XMin = xmin; }
	void SetXMax (const KoOrd xmax) { _XMax = xmax; }
	void SetYMin (const KoOrd ymin) { _YMin = ymin; }
	void SetYMax (const KoOrd ymax) { _YMax = ymax; }

	KoOrd Breite (void) { return (KoOrdAbs (_XMax-_XMin)); }
	KoOrd Hoehe (void) { return (KoOrdAbs (_YMax-_YMin)); }

	ObjRechteck InflateCont (int);       // Container größer/kleiner
	ObjRechteck &ShiftCont (Ausdehnung &); // Container verschieben

	// wenn alle Werte oder die Abmessungen gleich 0 sind, dann ist der OC inValid
	bool isValid (void) { return ( !((_XMax-_XMin==0)&&(_YMax-_YMin==0)) ); }

// Operator testet Verschnitt zweier ObjRechteck
	bool operator ^ (ObjRechteck &);		// Flächeninhalt des Durchschnitts > 0 (true)
	bool Durchschnitt (ObjRechteck& OC);   // mind. 1 Punkt gemeinsam (true)
	bool EpsDurchschnitt (ObjRechteck& OC, KoOrd lEpsX = iCoEps, KoOrd lEpsY = iCoEps);
	bool DurchschnittsCont (ObjRechteck& AC, ObjRechteck& DC);
	ObjRechteck DurchschnittsCont (ObjRechteck* pOC);
//  ObjRechteck operator = (Rectangle &);
	ObjRechteck &operator + (ObjRechteck &);
	void operator += (ObjRechteck &);

friend bool operator > (ObjRechteck &, ObjRechteck &);
friend bool operator >= (ObjRechteck &, ObjRechteck &);
friend bool operator < (ObjRechteck &, ObjRechteck &);
friend bool operator <= (ObjRechteck &, ObjRechteck &);

// Destruktoren
		~ObjRechteck (void) {}
};
#endif // NOOBJRECHTECK


#if !defined(NOEOBJEKT)
// Gemeinsame Basisklasse für ElementarObjekte ------------------------------
class ResourceFile;
class GeoFehlerListe;

class _GEOMETR_ENTRY EObjekt {

protected:
// Konstruktor
		EObjekt (void);

public:
// Destruktor
		virtual ~EObjekt (void);

// rein virtuelle Funktionen
	virtual ObjTyp isA (void) = 0;   // liefert Objekttyp
	virtual Posit EnthaltenIn (EFlaeche*, void* pPSt = 0) = 0;
};
#endif // NOEOBJEKT


#if !defined(NOEKoordinatenPaar)
// EKoordinatenPaar - Grundklasse jedes GeometrieObjektes ----------------------
class _GEOMETR_ENTRY EKoordinatenPaar {
protected:
	KoOrd _X;
	KoOrd _Y;

public:
// Konstruktoren
		EKoordinatenPaar (void) { _X = 0; _Y = 0; }
		EKoordinatenPaar (KoOrd x, KoOrd y) { _X = x; _Y = y; }
};


#if !defined(NOAUSDEHNUNG)
// Ausdehnung -- Größe eines Rechtecks ----------------------------------------
class _GEOMETR_ENTRY Ausdehnung : public EKoordinatenPaar {
public:
// Konstruktoren
		Ausdehnung (void) : EKoordinatenPaar () {}
		Ausdehnung (KoOrd x, KoOrd y) : EKoordinatenPaar (x, y) {}

// Memberfunktionen
	KoOrd &Breite (void) { return _X; }     // liefern Attributwerte
	KoOrd &Hoehe (void) { return _Y; }

// keine Destruktoren
};
#endif // NOAUSDEHNUNG


#if !defined(NOEPUNKT)
// EPunkt --------------------------------------------------------------------------------------
class _GEOMETR_ENTRY EPunkt : public EKoordinatenPaar, public EObjekt {

// friend-Funktionen
// Abstand zwischen den Punkten AP und EP mit Maximum-Norm
_GEOMETR_ENTRY friend KoOrd AbstandPktPktM (EPunkt&, EPunkt&);
_GEOMETR_ENTRY friend KoOrd AbstandPktPktM (KoOrd x1, KoOrd y1, KoOrd x2, KoOrd y2);

// Abstand zwischen den Punkten AP(x1,y1) und EP(x2,y2) mit euklidischer Norm
_GEOMETR_ENTRY friend double AbstandPktPktE (EPunkt& AP, EPunkt& EP);
_GEOMETR_ENTRY friend double AbstandPktPktE (KoOrd x1, KoOrd y1, KoOrd x2, KoOrd y2);

// Kreuzprodukt zweier Vektoren mit Endpunkten Pkt1 und Pkt2
friend double KreuzProd (EPunkt&, EPunkt&);

// Kollinearität von 3 Punkten (true), sonst false
_GEOMETR_ENTRY friend bool Kollinear (EPunkt&, EPunkt&, EPunkt&);
_GEOMETR_ENTRY friend bool Kollinear (KoOrd x1, KoOrd y1, KoOrd x2, KoOrd y2, KoOrd x3,
									  KoOrd y3);

// Epsilon-Kollinearität von 3 Punkten (true), sonst false
_GEOMETR_ENTRY friend bool EpsKollinear (EPunkt& Pkt1, EPunkt& Pkt2, EPunkt& Pkt3,
										 int iEpsilon = iKoEps);

// 3 Punkte sind paarweise eps-verschieden (true), sonst false
friend bool PaarVergl (EPunkt&, EPunkt&, EPunkt&, int eps);

// für 3 Punkte gilt, daß P2 von P1 und P3 eps-verschieden ist (true), sonst false
friend bool MittVergl (EPunkt&, EPunkt&, EPunkt&, int eps);

// Rechteck aus den 2 Punkten Pkt1 und Pkt2 bilden
_GEOMETR_ENTRY friend ObjRechteck BuildRectangle (EPunkt& Pkt1, EPunkt& Pkt2);

// Schwerpunkt des Dreiecks Pkt1-Pkt2-Pkt3
friend DoublePair SchwerPunkt (EPunkt& Pkt1, EPunkt& Pkt2, EPunkt& Pkt3);

public:
// Konstruktoren
		EPunkt (void) : EKoordinatenPaar () {}
		EPunkt (KoOrd x, KoOrd y) : EKoordinatenPaar (x, y) {}

// Memberfunktionen
	KoOrd &X (void) { return _X; }  // liefern Attributwerte
	KoOrd &Y (void) { return _Y; }
	KoOrd GetX (void) const { return _X; }  // liefern Attributwerte
	KoOrd GetY (void) const { return _Y; }
	// Dass sich dieser Fehler auch nur 3 sec halten konnte, ist unfgasslich !?
//	ObjRechteck GetCont (void) { return ObjRechteck (X(), Y(), X(), Y()); }
	ObjRechteck GetCont (void) { return ObjRechteck (X(), X(), Y(), Y()); }	// #WM030224
	bool operator == (const EPunkt& P) const { return (_X == P._X && _Y == P._Y); }
	bool operator != (const EPunkt& P) { return (_X != P._X || _Y != P._Y); }
	bool EpsGleich (EPunkt& P, double dEpsX = dGlEps, double dEpsY = dGlEps,
					bool bEuklid = true);
	bool EpsUngleich (EPunkt& P, double dEpsX = dGlEps, double dEpsY = dGlEps,
					  bool bEuklid = true);
	bool EpsGleich (DoublePair DP, double dEpsX = dGlEps, double dEpsY = dGlEps,
					bool bEuklid = true);
	EPunkt operator - (const EPunkt&);        // Vektordifferenz
	void UnValid (void); // beide Punktkoordinaten auf LONG_MAX setzen

	// true, wenn Punkt ungültig, d.h. beide Punktkoordinaten = LONG_MAX, sonst false
	bool operator ! ();

	// true, wenn Punkt gültig, d.h. wenigstens eine Punktkoordinate != LONG_MAX, sonst false
	operator bool ();

	// true, wenn wenigstens eine Punktkoordinate außerhalb des Intervalls <0; MAXKOORD>
	bool isBad (void);

	// Enthaltensein eines Punktes in einem Container
	bool PktInCont (ObjRechteck& OC);
	
	// Enthaltensein eines Punktes in der Fläche, die durch eine geschlossene Kante bzw.
	// eine Flächenkontur gebildet wird
	Posit Position (EKante* pK, double dEps = 0.0);

	// Test, wie der this-EPunkt bez. der EKante pKt liegt
	Posit PunktAufKante (EKante* pKt);
	
// Definition der virtuellen Funktionen der Basisklasse EObjekt
	ObjTyp isA (void) { return OT_PUNKT; }   // liefert ObjektTyp
	Posit EnthaltenIn (EFlaeche* pFS, void* = 0);

// keine Destruktoren
};
#endif // NOEPUNKT
#endif // NOEKoordinatenPaar



#if !defined(NOPUNKTVEC)
// spezieller Punkt
#define SpecPunkt EPunkt


// Punktvektor PUNKTVEC ------------------------------------------------------
class _GEOMETR_ENTRY PunktVec
{
private:
	SpecPunkt* m_pSPF;			// Punktvektor
	long m_lLen;				// Vektorlänge

public:
// Konstruktor/Destruktor
	PunktVec (long lLen);
	~PunktVec (void);


// Funktionen
	// Überladung des Index-Operators
	EPunkt& operator [] (long lInd)
	{
		return (((lInd >= 0) && (lInd < m_lLen)) ? m_pSPF[lInd] : m_pSPF[0]);
	}

	// Vektorlänge liefern
	long VekL (void) { return m_lLen; }

	// Pointer auf Punktfeld liefern
	SpecPunkt* Vektor (void) { return m_pSPF; }
};
#endif // NOPUNKTVEC



#if !defined(NOEKANTE)
// EKante ----------------------------------------------------------------------
class Strecke;
class MarkLine;
class ClipListe;

class _GEOMETR_ENTRY EKante : public EObjekt {
private:
	void AddKantenStueck1 (PunktVec* pPt, long lAnfId, long lEndId, MoveDir MD);
	void AddKantenStueck2 (MarkLine* pML, long lAnfId, long lEndId, MoveDir MD);
	bool OverlapTest (EKante* pKt, long jj, DoublePair GP);
	bool Seitenwechsel (EKante* pKt, long j, long jj, DoublePair GP, SchnittErg& Fo);
	bool Aufbereitung (EKante* pSKt, MarkLine*& pML1, MarkLine*& pML2, bool& bSonst,
				       bool& bSchnitt, bool& bLeer, bool& bAbbr, void* pPSt);

protected:
	PunktVec* _SPF;			// Stützpunktfolge
	long _Size;				// Anzahl der Stützpunkte; überflüssig, da = _SPF->VekL()
	ObjRechteck *_OCont;	// Container dieser Kante

// Konstruktoren
		EKante (long Size, PunktVec* SPF);
public:
		EKante (void) { _SPF = 0; _Size = 0; _OCont = 0; }
		EKante (KoOrd x[], KoOrd y[], long);
		EKante (PunktVec Pt[], long);
		EKante (const EKante &);

// Memberfunktionen
	void operator = (const EKante &);			// Zuweisung überladen

// interne Variablenwerte liefern
	PunktVec* Vektor (void) { return _SPF; }	// Pointer auf Punktfeld liefern
	long ASP (void) const { return _Size; }		// Anzahl der Stützpunkte
	ObjRechteck GetCont (void);
	ObjRechteck maxCont (ObjRechteck &);		// umschließender Cont
	ObjRechteck minCont (ObjRechteck &);		// k.g.Container
//	EPunkt &SP (long n = 0) const;				// Stützpunkt n liefern		16.01.98
	inline EPunkt& SP (long n = 0) const;		// Stützpunkt n liefern		16.01.98
	void GetKante (KoOrd x[], KoOrd y[], long &);	// Geometrie

// interne Werte modifizieren
	// Punkt(e) hinzufügen
	void AddPunkt (const EKante &K, long Anzahl, long Index);

	// Len > 0 Punkte werden vor Stützpunktnummer -1 <= Index <= _Size eingefügt
	void AddPunkt (KoOrd x[], KoOrd y[], long Len, long Index);
	HRESULT AddPunkt (KoOrd x[], KoOrd y[], long lCnt, long lAnfId, long lEndId, long lIndex);

	// Len > 0 Punkte werden vor Stützpunktnummer -1 <= Index <= _Size eingefügt
	void AddPunkt (PunktVec* pPV, long Len, long Index);

	// Die Punkte vom Anfangsindex lAnfId bis einschließlich zum Endindex lEndId der
	// Kontur pML werden vor Stützpunktnummer -1 <= lIndex <= _Size eingefügt
	void AddKonturTeil (MarkLine* pML, long lAnfId, long lEndId, long lIndex);

	// Punkt(e) löschen
	// Len > 0 Punkte werden ab Stützpunktnummer 0 <= Index < _Size gelöscht
	void SubPunkt (long Len, long Index);

	void SetCont (long Cont[]);          // OCont setzen

// Test auf Geometriefehler
	// Doppelpunkt liegt vor (true), wenn der Abstand zum nachfolgenden Punkt höchstens
	// dEps (in Meter) beträgt
	bool isDoppel (bool& bNull, double dEps, DoublePair dpUF, bool bMetric, long i,
				   long j = -1);

	// 2 hintereinanderliegende Strecken einer Kante bzw. Flächenkontur bilden eine Spitze
	bool isSpitz (bool& bNull, double dSpEps, long i, long j = -1, long k = -1);

	// Kollinearität zwischen 3 aufeinanderfolgenden Punkten (true), sonst false
	bool isKoll (long i, long j = -1, long k = -1);

	// Selbstüberschneidung liegt vor (true), sonst false
	bool isSelbInz (Strecke& S1, EPunkt& AP, EPunkt& EP, long j, long jj, EPunkt& GP1,
					EPunkt& GP2, SchnittErg& Fo);

	// Umlaufsinn einer geschlossenen Kante ermitteln
	bool GetTurning (void);

	// Richtung einer Kante umorientieren
	void OrientDreh (void);

	// Punkt einer Stützpunktfolge mit der kleinsten x-Koordinate unter allen Punkten mit der
	// kleinsten y-Koordinate bestimmen
	long IndTiefsterPunkt (void);

	// Umordnen der Stützpunktfolge einer geschlossenen Kante bzw. Flächenkontur
	bool Umordnen (void);

	// berechnet den vorzeichenbehafteten Inhalt einer geschlossenen Kante
	double PolygonArea (CoordTransX* pCT = 0);

	// Aufbereitung einer Kante, die (evtl.) von einer EKante pSKt geschnitten wird
	bool Aufbereitung0 (EKante* pSKt, MarkLine*& pML, bool& bAbbr, void* pPSt);
	
	// Aufbereitung einer Flächenkontur, die (evtl.) von einer EKante pSKt geschnitten wird
	bool Aufbereitung1 (EKante* pSKt, MarkLine*& pML1, MarkLine*& pML2, bool& bAbbr, void* pPSt);

	// Aufbereitung einer Kante bzw. Flächenkontur, die (evtl.) von einer Fläche (geschlossenen
	// EKante) pFS geschnitten werden
	bool Aufbereitung2 (EKante* pFS, MarkLine*& pML1, MarkLine*& pML2, bool& bLeer, bool& bAbbr,
						void* pPSt);

	// Kante mit weiteren Punkten aus einem offenen MarkVertex-Vektor pML2 ergänzen
	void SpezAddPunkt1 (MarkLine* pML1, MarkLine* pML2, long& i, Mar1 mark);

	// Punkte der this-Kante, die mit einem pKt-Punkt eps-gleich sind, auf diesen pKt-Punkt
	// setzen
	void DblPointTestBetween2Lines (EKante* pKt);
	
	// Kante mit weiteren Punkten aus einem geschlossenen MarkVertex-Vektor pML2 ergänzen
	void SpezAddPunkt2 (MarkLine* pML1, MarkLine* pML2, long& i, MoveDir MD,
						ulong ulLageAusw);

	// Enthaltensein eines real-Punktes in der Fläche
	Posit Position_real (double x, double y);

	// Lage der this- und der pKt-Kontur zueinander
	Posit LageKonturZuKontur (EKante* pKt, MarkLine*& pML1, MarkLine*& pML2, bool& bOverlap,
							  int& iTouchOut);

	// Punkt (dInX, dInY) zurückgeben, der garantiert innerhalb der geschlossenen this-EKante
	// liegt
	bool InneliegenderPunkt (double& dInX, double& dInY);

	// Lage der this-EKante und der pKt-EKante zueinander
	Posit KantenLage (EKante* pKt);
	OGCPosit LinesLocation (EKante* pKt);
	
// Definition der virtuellen Funktionen der Basisklasse EObjekt
	ObjTyp isA (void) { return OT_KANTE; }		// liefert ObjektTyp
	Posit EnthaltenIn (EFlaeche* pFS, void* pPSt = 0);

	// Verbindung zweier Kanten
	bool LinienVereinigung (EKante* pKt, ulong ulFill = 0);
	bool LinienVereinigung2 (EKante* pKt, ulong ulFillX = 0, ulong ulFillY = 0);

	// Test auf Überschneidung der Strecken zweier Kanten
	SchnittErg KantenSchnitt (EKante* pKt, long j, long jj, DoublePair& GP1, DoublePair& GP2);

	// this-Kontur wird durch pKont-Kontur geschnitten und dabei evtl. neue Flächen erzeugt
	bool SchnittKonturMitKontur (EKante* pKont, int iKI1, int iKI2, ulong ulLageAusw,
								 ClipListe& CL);

	bool GeometricalSameLines (EKante* pKt);

	// Test, ob die Schleife am Ende der Kante eine vorgebbare Mindestanzahl von Stützpunkten hat
	bool IsLoopLarge (KoOrd lXK, KoOrd lYK, long& lPInd);
	
// Destruktoren
		~EKante (void);
};
#endif // NOEKANTE


#if !defined(NOEFLAECHE)
// Fläche ---------------------------------------------------------------------
class _GEOMETR_ENTRY EFlaeche : public EObjekt{
private:
	EFlaeche* FlaechenVereinigung1 (EFlaeche* pFl);
	void AddInseln1 (EFlaeche* pFl1, EFlaeche* pFl2);
	void AddInseln2 (EFlaeche* pFl1, EFlaeche* pFl2);
	void AddInseln3 (EFlaeche* pFl, int i);
	void AddInseln4 (EFlaeche* pFl, int i);
	void AddInseln5 (EFlaeche* pFl);
	void ZweiteFlaeche (MarkLine* pML1, MarkLine* pML2, long& i);
	Posit BeideAussenkonturenIdentisch (EFlaeche* pFl, int iKAnz);
	Posit EnthaltenInWeiter (EFlaeche* pFl, int* piInsel);

protected:
	EKante *_KAF;			// Kantenfolge
	int _Size;				// Anzahl der Kanten
	ObjRechteck *_OCont;	// Container dieser Fläche

// Konstruktoren
		EFlaeche (PunktVec* SPF, long Size); // nur eine Kante

// Memberfunktionen
	bool InselnBeiSchnittMitKante (ClipListe& CL, int iSkip);
	bool InselnAmRand (ClipListe& CL, int iSkip, int* piVbInsel, bool& bModify);

public:
// weitere Konstruktoren
		EFlaeche (void) { _KAF = 0; _Size = 0; _OCont = 0; }
		EFlaeche (KoOrd x[], KoOrd y[], long Len);	// nur eine Kante
		EFlaeche (EKante *Flaeche, int);			// mehrere Kanten
		EFlaeche (EKante** Kontur, int);			// mehrere Kanten
		EFlaeche (const EFlaeche &);				// Copy-Konstruktor

// Memberfunktionen
	void operator = (const EFlaeche &);       // Zuweisung überladen

	int KantenAnz (void) const { return _Size; } // liefert Kantenanzahl
	long ASP (void);        // liefert Gesamtanzahl der Stützpunkte
	ObjRechteck GetCont (void);

	// Berechnung des Flächeninhalt einer Flächen unter Berücksichtigung von Innenkonturen
	double AreaSize (CoordTransX* pCT = 0); 
	
	// berechnet Schwerpunkt der Außenkontur (ohne Innenkonturen) und (vorzeichenbehafteten)
	// Flächeninhalt einer Fläche
	double SchwerPunkt (EPunkt &Pt);         
	
	ObjRechteck maxCont (ObjRechteck &);  // umschließendes Rechteck
	ObjRechteck minCont (ObjRechteck &);  // k.g. Rechteck (Schnitt)
	EKante &KA (int n = 0) const {  // EKante n liefern
		return (((n >= 0) && (n < _Size)) ? _KAF[n] : _KAF[0]);
	}

// interne Werte modifizieren
	// Kante(n) hinzufügen
	void AddKante (const EFlaeche &, int Anzahl, int Index);
	void AddKante (KoOrd x[], KoOrd y[], long Len, int Index);

	// Innenkontur(en) einer Fläche löschen
	void SubKante (int Anzahl, int Index);

	// Punkt(e) zu einer der Kanten hinzufügen
	void AddPunkt (const EKante &K, long KAnz, long KIndex, int MIndex);

	// Len > 0 Punkte werden vor Stützpunktnummer -1 <= KIndex <= Konturlänge eingefügt
	void AddPunkt (KoOrd x[], KoOrd y[], long Len, long KIndex, int MIndex);

	// Punkt(e) in einer der Flächenkonturen löschen
	void SubPunkt (long Len, long KIndex, int MIndex);

	// Außenkontur und i-te Innenkontur werden getauscht
	bool TauschKante (int i);

	void SetCont (long Cont[]);     // Container setzen

// Test auf Geometriefehler
	// Kontur einer Fläche ist offen (true), sonst false, 0 <= i < _Size ist der Konturindex
	bool isOffen (int i);

	// Umlaufsinn einer Kontur fehlerhaft (true), sonst false
	bool isWrongTurning (int i);

	// Umlaufsinn einer Kontur umorientieren (0 <= i < _Size ist der Konturindex)
	void OrientDreh (int i);

	// Umlaufsinn aller Konturen einer Fläche prüfen und ggf. richtig drehen
	bool Umlaufsinn (void);
	
	// Test auf Überschneidung zwischen den Konturen (true), sonst false
	bool isKontInz (EPunkt& AP1, EPunkt& EP1, EPunkt& AP2, EPunkt& EP2, int i, int ii,
					long j, long jj, long& KonInzOS, EPunkt& GP1, EPunkt& GP2, SchnittErg& Fo);

	// Test, ob Innenkontur i, die die Außenkontur nicht echt schneidet, außerhalb der
	// Außenkontur liegt (true), sonst false
	bool isAussen (int i);

	// Test, ob Innenkontur i1, die die Innenkontur i2 nicht echt schneidet, innerhalb von i2
	// liegt (true), sonst false
	bool isInnen (int i1, int i2);

// Vereinigung zweier Flächen (this- und pFl-Fläche) mit (bInsel == true) bzw. ohne
// (bInsel == false) Berücksichtigung von Innenkonturen; wenn keine Vereinigung möglich,
// dann Rückgabe von NULL
	EFlaeche* FlaechenVereinigung (EFlaeche* pFl, bool& bAbbr, void* pPSt, bool bInsel = true);
	
// Definition der virtuellen Funktionen der Basisklasse EObjekt
	ObjTyp isA (void)  { return OT_FLAECHE; }    // liefert ObjektTyp
	Posit EnthaltenIn (EFlaeche* pFS, void* pPSt = 0);

	bool InselnBeiSchnittMitFlaeche (EFlaeche* pFl, ClipListe& CL, int iSkip);
	bool InselnInnerhalb (ClipListe& CL, int iSkip, int* piVbInsel = 0);
	bool ContourUnion (MarkLine* pML1, MarkLine* pML2, EFlaeche*& pVFl, bool bInsel);
	bool InneliegenderPunkt (double& dInX, double& dInY);

// Destruktoren
		~EFlaeche (void);
};
#endif // NOEFLAECHE


#if !defined(NOGEOOBJEKT)
// GeoObjekt ------------------------------------------------------------------
// von diesem allgemeinen GeoObjekt sind alle anderen abgeleitet

typedef struct tagOBJGEOMETRIE OBJGEOMETRIE;
class CoordTrans;
class ClipListe;

class _GEOMETR_ENTRY GeoObjekt {
private:
	long _ObjNr;	// Objektnummer in der DB

protected:
	long _Id;		// Objektidentifikator

public:
// Konstruktor
		GeoObjekt (long ObjNr, ulong Id = 0);

// pure virtual functions
	virtual ObjTyp isA (void) = 0;  // liefert Objekttyp

// virtual functions 
// Die Pseudorückkehrwerte sind erforderlich, da die Funktionen in der abgeleiteten
// Klasse GeoPunkt nicht redefiniert werden !!!
	virtual bool Clipping (EObjekt*, int, ulong, ClipListe&, int, Posit&, bool&, void*)
						  { return true; }					// Schnitt von Objekten
	virtual bool AddClipObjekt (ClipListe&) { return true; } // Teilobjekt in CL eintragen

// Methoden
	long & Id (void) { return _Id; }
	long & ObjNr (void) { return _ObjNr; }
	long OffsetON (long Offset) { return (_ObjNr += Offset); }
	void SetIdent (long lIdent) { _Id = lIdent; }

	bool RetrieveGeometrie (OBJGEOMETRIE *, CoordTrans *);

// Destruktor
		virtual ~GeoObjekt (void) {}
};
#endif // NOGEOOBJEKT


#if !defined(NOGEOPUNKT)
// GeoPunkt -------------------------------------------------------------------
class _GEOMETR_ENTRY GeoPunkt : public GeoObjekt, public EPunkt {
// keine eigenen Attribute

public:
// Konstruktoren
		GeoPunkt (long ObjNr, ulong Id = 0)
			: GeoObjekt (ObjNr, Id) {};
		GeoPunkt (long ObjNr, ulong Id , const EPunkt &Pkt)
			: GeoObjekt (ObjNr, Id), EPunkt (Pkt) {};
		GeoPunkt (const GeoPunkt &DBP)
			: GeoObjekt (((GeoPunkt &)DBP).ObjNr(), DBP._Id), EPunkt (DBP._X, DBP._Y) {};

// Memberfunktionen
	void operator =(GeoPunkt &);
	ObjTyp isA (void) { return OT_PUNKT; }
};
#endif // NOGEOPUNKT


#if !defined(NOGEOKANTE)
// GeoKante -------------------------------------------------------------------
class _GEOMETR_ENTRY GeoKante : public GeoObjekt, public EKante {
private:
// Memberfunktionen
	bool ClippingMitKante (EKante* pSKt, ClipListe& CL, int iSkip, bool& bAbbr, void* pPSt);
	bool ClippingMitFlaeche (EFlaeche* pSFl, ulong ulLageAusw, ClipListe& CL, int iSkip,
							 Posit& Lage, bool& bAbbr, void* pPSt);

	// Inseln bei Schnitt der this-EKante mit pSFl-Schnittfläche berücksichtigen
	// (ulLageAusw == LINN)
	bool MesserInselnINN0 (EFlaeche* pSFl, ClipListe& CL);
	bool MesserInselnINN1 (EFlaeche* pSFl, ClipListe& CL, int iSkip);
	bool MesserInselnINN (EFlaeche* pSFl, ClipListe& CLZw, bool& bDelThis);

	// Inseln bei Schnitt der this-EKante mit pSFl-Schnittfläche berücksichtigen
	// (ulLageAusw == LAUSS) 
	bool MesserInselnAUSS (EFlaeche* pSFl, ClipListe& CL);

	// Inseln bei Schnitt der this-EKante mit pSFl-Schnittfläche berücksichtigen
	// (ulLageAusw == LKONT) 
	bool MesserInselnKONT (EFlaeche* pSFl, ClipListe& CL);

public:
// Konstruktoren
		GeoKante (long lObjNr, ulong ulIdent = 0)
			: GeoObjekt (lObjNr, ulIdent) {};
		GeoKante (long lObjNr, ulong ulIdent, KoOrd x[], KoOrd y[], long Len)
			: GeoObjekt (lObjNr, ulIdent), EKante (x, y, Len) {};
		GeoKante (long lObjNr, ulong ulIdent, const EKante &Kt)
			: GeoObjekt (lObjNr, ulIdent), EKante (Kt) {};
		GeoKante (const GeoKante &Kt)
			: GeoObjekt (((GeoKante&)Kt).ObjNr(), Kt._Id), EKante (Kt._SPF, Kt._Size) {};
		
// Memberfunktionen
	void operator =(const GeoKante &);
	ObjTyp isA (void) { return OT_KANTE; } // liefert ObjektTyp
	bool Clipping (EObjekt* pEO, int iOT, ulong ulLageAusw, ClipListe& CL, int iSkip,
				   Posit& Lage, bool& bAbbr, void* pPSt);
	bool AddClipObjekt (ClipListe& CL);

// Destruktor
		~GeoKante (void) {};
};
#endif // NOGEOKANTE


#if !defined(NOGEOFLAECHE)
// GeoFläche ------------------------------------------------------------------
class _GEOMETR_ENTRY GeoFlaeche : public GeoObjekt, public EFlaeche {
private:
// Memberfunktionen
	bool ClippingMitKante (EKante* pSKt, ClipListe& CL, int iSkip, bool& bAbbr, void* pPSt);
	bool ClippingMitFlaeche (EFlaeche* pSFl, ulong ulLageAusw, ClipListe& CL, int iSkip,
							 Posit& Lage, bool& bAbbr, void* pPSt);
	bool MesserInnerhalb (EFlaeche* pSFl, ulong ulLageAusw, ClipListe& CL, int iSkip,
						  bool bOverlap, int iTouchOut, bool& bEnde);
	bool MesserinselInnerhalb (EKante* pKont, int iKInd, ClipListe& CL, int iSkip);
	bool MesserAusserhalb (EFlaeche* pSFl, ulong ulLageAusw, ClipListe& CL, int iSkip);
	bool MesserAusserhalbWeiter (EFlaeche* pSFl, ulong ulLageAusw, ClipListe& CL, int iSkip,
								 int* piInsel);
	bool InselZweiteFlaecheAUSS (EFlaeche* pSFl, ClipListe& CL);
	bool ZweiInselnVereinigen (ClipListe& CL, EFlaeche*& pNewInsel, MarkLine* pML1,
							   MarkLine* pML2);

public:
// Konstruktoren
		GeoFlaeche (long lObjNr, ulong ulIdent = 0)
			: GeoObjekt (lObjNr, ulIdent) {};
		GeoFlaeche (long lObjNr, ulong ulIdent, KoOrd x[], KoOrd y[], long Len)
			: GeoObjekt (lObjNr, ulIdent), EFlaeche (x, y, Len) {};
		GeoFlaeche (long lObjNr, ulong ulIdent, const EFlaeche& Fl)
			: GeoObjekt (lObjNr, ulIdent), EFlaeche (Fl) {};
		GeoFlaeche (const GeoFlaeche& Fl)
			: GeoObjekt (((GeoFlaeche&)Fl).ObjNr(), Fl._Id), EFlaeche (Fl._KAF, Fl._Size) {};
		GeoFlaeche (long lObjNr, ulong ulIdent, PunktVec* SPF, long Size)
			: GeoObjekt (lObjNr, ulIdent), EFlaeche (SPF, Size) {};

// Memberfunktionen
	void operator = (const GeoFlaeche &);
	ObjTyp isA (void) { return OT_FLAECHE; }    // liefert ObjektTyp
	bool Clipping (EObjekt* pEO, int iOT, ulong ulLageAusw, ClipListe& CL, int iSkip,
				   Posit& Lage, bool& bAbbr, void* pPSt);
	bool AddClipObjekt (ClipListe& CL);
	bool InselnBeiSchnittMitFlaecheAUSS (EFlaeche* pFl, ClipListe& CL, int iSkip);
	bool KonturGemeinsamkeiten (EFlaeche* pFl, ulong ulLageAusw, ClipListe& CL, bool& bAbbr,
								void* pPSt);
	bool InselZweiteFlaeche (ClipListe& CL, EKante* pKont, int iKInd);

// Destruktor
		~GeoFlaeche (void) {};
};
#endif // NOGEOFLAECHE



// --------------------------------------------------------------------------------------------
#if !defined(NOEKANTE)

// Inline - Memberfunktion
inline EPunkt& EKante :: SP (long n) const	// Stützpunkt n liefern
{
	return (((n >= 0) && (n < _Size)) ? _SPF->Vektor()[n] : _SPF->Vektor()[0]);
}

#endif // NOEKANTE


#endif  // _GEO_OBJ_HXX
