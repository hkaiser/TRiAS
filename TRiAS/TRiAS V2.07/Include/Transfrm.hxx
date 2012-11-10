// Transformation und Projektionsparameter, notwendig fr Zeichnen von DBObj
// File: TRANSFRM.HXX

// IRISWIN: %W% %E%

#ifndef _TRANSFRM_HXX
#define _TRANSFRM_HXX

#if !defined(NOTRANSFORMATION)
// DefaultProjektionsfunktionen -----------------------------------------------
inline void DefPrj (KoOrd * /*x*/, KoOrd * /*y*/) { /* do nothing */ }
inline Punkt DefInvPrj (Punkt Pt) { return Pt; }

// Verschiedene Modi bei der Initialisierung des hDC --------------------------
const short FDC_NoInit 		= 0x00;
const short FDC_FullInit 	= 0x01;
const short FDC_PaletteOnly 	= 0x02;
const short FDC_ActivateOnly	= 0x04;

// Klasse, die Transformation beim Zeichnen definiert
class Transformation 
{
#if !defined(NOTRANSFORM)
private:
// Datenbereich (Daten existieren nur einmal (global))
	static CoOrd m_EALeft;			// einzeln, damit Daten NEAR bleiben
	static CoOrd m_EATop;
	static CoOrd m_EARight;
	static CoOrd m_EABottom;

	static KoOrd m_EOCXMin;			// einzeln, damit Daten NEAR bleiben
	static KoOrd m_EOCXMax;
	static KoOrd m_EOCYMin;
	static KoOrd m_EOCYMax;
	static long _ClipRegionObjNr;	// ObjektNummer, an dem geklippt werden soll
	static short _FullDCInit;		// DC für jedes Objekt vollständig initialisieren

// Primärdaten
	static KoOrd _xWindowOrg;       // NullPunkt im Fenster
	static KoOrd _yWindowOrg;
	static KoOrd _xWindowExt;       // Fenstergröße
	static KoOrd _yWindowExt;
	static CoOrd _xViewportOrg;     // NullPunktkoordinaten des Ausschnittes
	static CoOrd _yViewportOrg;
	static CoOrd _xViewportExt;     // Ausschnittsgröße
	static CoOrd _yViewportExt;
	static CoOrd _xLogPixels;		// AspectRatio
	static CoOrd _yLogPixels;

	static double _Masstab;			// aktueller BildMasstab/Bezugsmasstab

// Sekundärdaten
	static double _xK;              // Skalierungskoeffizienten
	static double _yK;
	static double _invxK;           // inverser Skalierungskoeffizienten
	static double _invyK;
	static KoOrd _xWindowOffset;    // Transformierter Nullpunkt
	static KoOrd _yWindowOffset;
	static KoOrd _xViewportOffset;  // Rücktransformierter Nullpunkt
	static KoOrd _yViewportOffset;

	static double _CTAspect;		// AspektRatio des Koordinatensystems
#endif // NOTRANSFORM

// private Memberfunktionen
	void SetTransPars (void);       // Transformationsparameter berechnen

protected:
// Funktionen, die zur Berechnung der Projektion verwendet wird
	static void (*_Prj)(KoOrd *x, KoOrd *y);	// HinProjektion
	static Punkt (*_invPrj)(Punkt Pt);			// Rückprojektion

#if !defined(NOTRANSFORM)
	static bool m_fIsValid;		// Transformationsparameter sind gültig
	static bool m_fChanged;		// Transformationsparameter wurden verändert
#endif // NOTRANSFORM
		
public:
// Konstruktoren
		// keine 
		// (Daten sind statisch und werden statisch initialisiert)

// Transformationsfunktionen
friend  Point OCtoDC (KoOrd x, KoOrd y);        // Objekt --> Device
friend	Point OCtoDC (const Punkt &);
friend	void OCtoDC (Punkt *, Point *, long);
friend  void OCtoDC (Punkt *pPkt, Point *pPt, long lCnt, Rectangle &rrcBound);
friend	CoOrd OCtoDCX (KoOrd x);
friend	CoOrd OCtoDCXDelta (KoOrd dX);
friend	CoOrd OCtoDCY (KoOrd y);
friend	CoOrd OCtoDCYDelta (KoOrd dY);

friend  Punkt DCtoOC (const Point &);                 // Device --> Objekt
friend 	void DCtoOC (Point *, Punkt *, long);
friend 	Punkt DCtoOC (CoOrd x, CoOrd y);
friend	KoOrd DCtoOCX (CoOrd x);
friend	KoOrd DCtoOCXDelta (CoOrd dX);
friend	KoOrd DCtoOCY (CoOrd y);
friend	KoOrd DCtoOCYDelta (CoOrd dY);

// Einstellen der Transformationsparameter
	Punkt SetWindowOrg (Punkt &);           // Ausschnitt
	Ausdehnung SetWindowExt (Ausdehnung &);
	Point SetViewportOrg (Point &);         // Bezugsfenster
	Dimension SetViewportExt (Dimension &);
	Point SetAspectRatio (Point &, double &);
	double GetAspectRatio();

// Einstellen der Projektionsfunktionen
	void SetPrjFcn (void (*F)(KoOrd *x, KoOrd *y), Punkt (*invF)(Punkt Pt));

// Initialisierungsfunktion
static void InitStaticData (void);

#if !defined(NOTRANSFORM)
static bool IsValid (void) { return m_fIsValid ? true : false; }
static void SetValid (bool fValid = true) { m_fIsValid = fValid ? true : false; }

static bool IsChanged (void) { return m_fChanged ? true : false; }
static void SetChanged (bool fChanged = true) { m_fChanged = fChanged ? true : false; }

// Abfragen der aktuellen Parameter
	Dimension GetViewportExt (void) 
		{ return Dimension (_xViewportExt, _yViewportExt); }
	Point GetViewportOrg (void) 
		{ return Point (_xViewportOrg, _yViewportOrg); }

// Zugriff auf den ungültigen FensterBereich
	Rectangle EA (void) 
		{ return Rectangle (m_EATop, m_EALeft, m_EABottom, m_EARight); }
	void SetEA (Rectangle &rc) 
		{ m_EATop = rc.Top(); m_EALeft = rc.Left(), m_EABottom = rc.Bottom(); m_EARight = rc.Right(); }
	ObjContainer ExpOC (void) 
		{ return ObjContainer (m_EOCXMin, m_EOCXMax, m_EOCYMin, m_EOCYMax); }
	void SetExpOC (ObjContainer &oc) 
		{ m_EOCXMin = oc.XMin(); m_EOCXMax = oc.XMax(); m_EOCYMin = oc.YMin(); m_EOCYMax = oc.YMax(); }
	long &ClipRegionONr (void) { return _ClipRegionObjNr; }
	short &FullDCInit (void) { return _FullDCInit; }

	double &M (void) { return _Masstab; }
#endif // NOTRANSFORM
// Destruktoren
		// ebenfalls keine
};
#else // NOTRANSFORMATION

// Transformationsfunktionen
Point OCtoDC (Punkt &);			// Objekt --> Device
Point OCtoDC (KoOrd x, KoOrd y);
CoOrd OCtoDCX (KoOrd x);
CoOrd OCtoDCXDelta (KoOrd dX);
CoOrd OCtoDCY (KoOrd y);
CoOrd OCtoDCYDelta (KoOrd dY);

Punkt DCtoOC (Point &);                 // Device --> Objekt
Punkt DCtoOC (CoOrd x, CoOrd y);
KoOrd DCtoOCX (CoOrd x);
KoOrd DCtoOCXDelta (CoOrd dX);
KoOrd DCtoOCY (CoOrd y);
KoOrd DCtoOCYDelta (CoOrd dY);

#endif // NOTRANSFORMATION

#endif // TRANSFRM_HXX
