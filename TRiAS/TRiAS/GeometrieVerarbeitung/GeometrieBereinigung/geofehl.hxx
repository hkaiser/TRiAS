// Deklaration eines allgemeinen Geometriefehlers
// File: GEOFEHL.HXX
// W. Mörtl

#ifndef _GEOFEHL_HXX
#define _GEOFEHL_HXX

enum GEOFEHLERTYP {
	GFT_BadPunkt       = 1,
	GFT_DoppelterPunkt = 2,
	GFT_Kollinearitaet = 3,
	GFT_Spitze         = 4,
	GFT_OffeneKontur   = 5,
	GFT_FalscherUmlauf = 6,
	GFT_Selbstinzidenz = 7,
	GFT_Konturinzidenz = 8,
	GFT_Entartung      = 9,
	GFT_ExterneInsel   = 10,
	GFT_InterneInsel   = 11
};

// Basisklasse für alle Geometriefehler
class GeoFehler 
{
protected:
	EObjekt& _GO;		// Verweis auf EObjekt, d.h. auf fehlerhaftes GeometrieObjekt
	bool _isCorrected;	// GeoFehler wurde bereinigt (true), sonst false

public:
// Konstruktoren
	GeoFehler (EObjekt& GO);
	GeoFehler (EObjekt& GO, bool isCorrected);
	GeoFehler (GeoFehler&);

// Destruktor
	virtual	~GeoFehler (void);

// Memberfunktion
	bool WasCorrected (void) const {return _isCorrected;}

// Funktion, die einen 'virtuellen Konstruktor' simuliert
	virtual bool AddGeoFehler (GeoFehlerListe&) = 0;

// rein virtuelle Funktionen
	// Beschreibung eines GeoFehlers in Puffer sAnalyseText eintragen
	virtual void AnalysePuffern (string& sAnalyseText, CoordTransX* pCT) = 0;

// virtuelle Funktion, die den Geometriefehler bereinigt
	virtual void ErrorCorrection (void) { _isCorrected = true; }

	virtual void ZweiKonturen (int& iKNrFL1, int& iKNrFL2) = 0;
	virtual GEOFEHLERTYP GetType () = 0;
};

#endif // _GEOFEHL_HXX
