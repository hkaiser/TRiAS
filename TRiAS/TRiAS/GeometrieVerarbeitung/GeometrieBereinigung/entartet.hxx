// Deklaration des Geometriefehlers "entartetes EObjekt"
// File: ENTARTET.HXX
// W. Mörtl

#ifndef _ENTARTET_HXX
#define _ENTARTET_HXX


class Entartung : public GeoFehler
{
protected:
	int _iKaNr;		// Index der entarteten Kante
	EPunkt _EPkt;	// Anfangspunkt der entarteten Kante
	ObjTyp m_OTAlt;	// ursprünglicher Objekttyp von _GO
	ObjTyp m_OTNeu;	// Objekttyp von _GO NACH einer evtl. Bereinigung (kann sich von dem
					// ursprünglichen Objekttyp unterscheiden)
	int m_iKCntAlt;	// ursprüngliche Konturanzahl (nur für Flächenobjekte)

public:
// Konstruktoren/Destruktor
	Entartung (EObjekt& GO, int iKaNr);
	Entartung (Entartung&);
	~Entartung (void);

// weitere Elementfunktionen
	int RK (void) const {return _iKaNr;}
	EPunkt RAP (void) const {return _EPkt;}
	ObjTyp GetOTAlt (void) const {return m_OTAlt;}
	ObjTyp GetOTNeu (void) const {return m_OTNeu;}

	bool AddGeoFehler (GeoFehlerListe&);
	void AnalysePuffern (string& sAnalyseText, CoordTransX* pCT);
	void ErrorCorrection (void);
	void ZweiKonturen (int&, int&) {};	// nur für Konturinzidenz
	GEOFEHLERTYP GetType (void) { return GFT_Entartung; }
};

#endif // _ENTARTET_HXX
