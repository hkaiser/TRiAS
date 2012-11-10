// Deklaration des Geometriefehlers "DoppelPunkt"
// File: DOPPUNKT.HXX
// W. Mörtl

#ifndef _DOPPUNKT_HXX
#define _DOPPUNKT_HXX


class DoppelPunkt : public GeoFehler
{
protected:
	long _lSPNr;		// alter Index des doppelten Punktes
	int _iKaNr;			// Index der Kante mit doppeltem Punkt
	bool _bNull;		// Abstand ist exakt 0 m (true)
	EPunkt _DPkt1;		// Kopie der Koordinaten des doppelten Punktes
	EPunkt _DPkt2;		// Kopie der Koordinaten des nahen Punktes
	double m_dSpEps;	// Grenzwert für Test auf "Spitze"

public:
// Konstruktoren/Destruktor
	// SPNr StützpunktIndex, KaNr KantenIndex
	DoppelPunkt (EObjekt& GO, long lSPNr, int iKaNr, bool bNull, double dSpEps);
	DoppelPunkt (DoppelPunkt&);
	~DoppelPunkt (void);

// weitere Elementfunktionen
	long RSN (void) const {return _lSPNr;}
	int RK (void) const {return _iKaNr;}
	EPunkt RDP (int i) const
		{if (i == 1) return _DPkt1; else return _DPkt2;}

	bool AddGeoFehler (GeoFehlerListe&);
	void AnalysePuffern (string& sAnalyseText, CoordTransX* pCT);
	void ErrorCorrection (void);
	void ZweiKonturen (int&, int&) {};	// nur für Konturinzidenz
	GEOFEHLERTYP GetType (void) { return GFT_DoppelterPunkt; }
};

#endif // _DOPPUNKT_HXX
