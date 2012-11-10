// Deklaration des Geometriefehlers "Offene Kontur einer Fläche"
// File: OFFEN.HXX
// W. Mörtl

#ifndef _OFFEN_HXX
#define _OFFEN_HXX


class Offen : public GeoFehler
{
protected:
	int _iKaNr;			// Index der Kante mit fehlendem Schlußpunkt
	bool _bDblCoord;	// Koordinaten des Ursprungsobjektes im double- (true) bzw.
						// KoOrd-Format (false)
	EPunkt _OPkt;		// Kopie der Koordinaten des ergänzten Punktes bzw. Verustpunktes

public:
// Konstruktoren/Destruktor
	Offen (EObjekt& GO, int iKaNr, bool bDblCoord);
	Offen (Offen&);
	~Offen (void);

// weitere Elementfunktionen
	int RK (void) const {return _iKaNr;}
	EPunkt ROP (void) const {return _OPkt;}

	bool AddGeoFehler (GeoFehlerListe&);
	void AnalysePuffern (string& sAnalyseText, CoordTransX* pCT);
	void ErrorCorrection (void);
	void ZweiKonturen (int&, int&) {};	// nur für Konturinzidenz
	GEOFEHLERTYP GetType (void) { return GFT_OffeneKontur; }
};

#endif // _OFFEN_HXX
