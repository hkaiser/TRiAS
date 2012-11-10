// Deklaration des Geometriefehlers "Insel innerhalb einer anderen Insel"
// File: INSEL_IN.HXX
// W. Mörtl

#ifndef _INSEL_IN_HXX
#define _INSEL_IN_HXX


class InselInInsel : public GeoFehler
{
protected:
	int _iKaNr1;	// Index der Innenkontur, die innerhalb einer anderen liegt
	int _iKaNr2;	// Index der Innenkontur, innerhalb derer eine andere liegt
	EPunkt _AP1;	// Kopie der Koordinaten des Anfangspunktes der inneren Insel
	EPunkt _AP2;	// Kopie der Koordinaten des Anfangspunktes der äußeren Insel

public:
// Konstruktoren/Destruktor
	InselInInsel (EObjekt& GO, int iKaNr1, int iKaNr2);
	InselInInsel (InselInInsel&);
	~InselInInsel (void);

// weitere Elementfunktionen
	int RK (int i) const
		{if (i == 1) return _iKaNr1; else return _iKaNr2;}

	bool AddGeoFehler (GeoFehlerListe&);
	void AnalysePuffern (string& sAnalyseText, CoordTransX* pCT);
	void ZweiKonturen (int&, int&) {};	// nur für Konturinzidenz
	GEOFEHLERTYP GetType (void) { return GFT_InterneInsel; }
};

#endif // _INSEL_IN_HXX
