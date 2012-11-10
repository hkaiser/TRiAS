// Deklaration des Geometriefehlers "Ungültige Koordinaten"
// File: BADPUNKT.HXX
// W. Mörtl

#ifndef _BADPUNKT_HXX
#define _BADPUNKT_HXX


class BadPunkt : public GeoFehler
{
protected:
	long _lSPNr;	// alter Index des ungültigen Stützpunktes
	int _iKaNr;		// Index der Kante mit ungültigem Punkt
	EPunkt _BPkt;	// Kopie der Koordinaten des ungültigen Punktes

public:
// Konstruktoren/Destruktor
	BadPunkt (EObjekt& GO, long lSPNr, int iKaNr);
	BadPunkt (BadPunkt&);
	~BadPunkt (void);

// weitere Elementfunktionen
	long RSN (void) const {return _lSPNr;}
	int RK (void) const {return _iKaNr;}
	EPunkt RBP (void) const {return _BPkt;}

	bool AddGeoFehler (GeoFehlerListe&);
	void AnalysePuffern (string& sAnalyseText, CoordTransX* pCT);
	void ErrorCorrection (void);
	void ZweiKonturen (int&, int&) {};	// nur für Konturinzidenz
	GEOFEHLERTYP GetType (void) { return GFT_BadPunkt; }
};

#endif // _BADPUNKT_HXX
