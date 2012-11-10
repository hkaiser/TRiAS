// Deklaration des Geometriefehlers "falscher Umlaufsinn einer Flächenkontur"
// File: UMLAUF.HXX
// W. Mörtl

#ifndef _UMLAUF_HXX
#define _UMLAUF_HXX


class Umlauf : public GeoFehler
{
protected:
	int _iKaNr;		// Index der Kontur mit fehlerhaftem Umlaufsinn
	double _dFlInh;	// Flächeninhalt der Kontur, dessen Umlaufsinn bestimmt werden soll.
					// Ist Flächeninhalt == 0., kann Umlaufsinn nicht bestimmt werden.

public:
// Konstruktoren/Destruktor
	Umlauf (EObjekt& GO, double& dFlInh, int iKaNr);
	Umlauf (Umlauf&);
	~Umlauf (void);

// weitere Elementfunktionen
	int RK (void) const {return _iKaNr;}
	double RFI (void) const {return _dFlInh;}

	bool AddGeoFehler (GeoFehlerListe&);
	void AnalysePuffern (string& sAnalyseText, CoordTransX*);
	void ErrorCorrection (void);
	void ZweiKonturen (int&, int&) {};	// nur für Konturinzidenz
	GEOFEHLERTYP GetType (void) { return GFT_FalscherUmlauf; }
};

#endif // _UMLAUF_HXX
