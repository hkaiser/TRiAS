// Liste der aufgetretenen Geometriefehler
// File: GERRLIST.HXX

#ifndef _GERRLIST_HXX
#define _GERRLIST_HXX


class GeoFehler;	// vollst. Definition in GEOFEHL.HXX
class EObjekt;		// vollst. Definition in GEO_OBJ.HXX

class GeoFehlerListe : public CListContainer 
{
protected:
	void UserDelete (void* pObj);	// virt. Funkt. in Container-Klasse

	EObjekt& _GO;	// Verweis auf das geschädigte Originalobjekt

public:
// Konstruktor/Destruktor
	GeoFehlerListe (EObjekt& GO);
	~GeoFehlerListe (void);

// Beschreibung aller (bereinigten) GeoFehler in Puffer sAnalyseText eintragen
	void GesamtAnalysePuffern (string& sAnalyseText, CoordTransX* pCT);

// Testen, ob Konturinzidenz zwischen den Konturen iKNr1 und iKNr2 diagnostiziert wurde
	bool DieseZweiKonturen (int iKNr1, int iKNr2);

// Testen, ob GeoFehler erkannt und (wenn ja) bereinigt wurden oder nicht
	int BeseitigungsArt (void);

// Zugriffsfunktion zu AusgangsGeometrieObjekt
	EObjekt& GO (void) { return _GO; }

	bool EndLoopCorrection (void);
};


	// das nachfolgende Makro 'DeclarLock' generiert zwei zusätzliche Klassen:
	// GeoFehlerCreator - für das Neueintragen eines GeoFehlers in die Liste
	// GeoFehlerLock    - für den typsicheren Zugriff auf ein Element der Liste
	DeclareLock (GeoFehlerListe, GeoFehler);

#endif  // _GERRLIST_HXX
