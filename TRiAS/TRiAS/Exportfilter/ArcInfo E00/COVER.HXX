/*
Datei: COVER.HXX

Basisklassen für die Erzeugung des lesbaren Arc/Info-Austausschformates.
Verwaltung der mölglichen Arc/Info-Covers.

Erarbeitet: J. Benkenstein                  Begonnen am: 3. Mai 1993
*/

#ifndef _COVER_HXX
#define _COVER_HXX

class Section;

//  Basisklasse für das Erzeugen und Verwalten eines "Covers" in Arc/Info.
class Cover {
protected:
    OFSTRUCT _of;                   //  File-Struktur
    ErrCode _RC;                    //  Returnkode

	//  Inhalt der Datei kopieren, _RC wird gesetzt
    ErrCode FileCopy (int FileHandleDest, int FileHandleSource);

	//  Cover erzeugen, of-Struktur füllen
    ErrCode CreateCover (OFSTRUCT &of, pchar pPath, uint ResIDext);


public:
//  Konstruktor/Destruktor
	//  Dateiname muß vollständigen Pfad beinhalten !
    Cover (pchar pCoverName);   // Datei öffnen, Handle und RC setzen
    virtual ~Cover (void) {}

//  weitere Member-Funktionen
	//  Returnkode abfragen
    ErrCode Result (void) { return _RC; }

// KK000403
	// Transformieren in kompr.Form
	ErrCode TransferTempDaten(void);


//  virtuelle Funktionen
	//  Ausgabe :
	//      + InfoSection-Kopf
	//      + TIC- und BND-Datei
	//      + kopiere Inhalt evtl. angeg. Dateien in Main-Cover
	//        Dateien müssen geöffnet und positioniert sein
	//      + InfoSectio-Ende
	//      + CoverSection-Ende
	// _RC setzen
	//  MainCover muß geöffnet und positioniert sein
    virtual ErrCode OutputLastData (int FileHandleMainCover = 0,
				    int FileHandle = 0,
				    Section *pSection = NULL);

	//  Ausgabe der Zeile für den Import des Covers in SML-Makro.
	//  Datei muß geöffnet und positioniert sein.
    virtual ErrCode OutputImportMakro (int FileHandle); // _RC setzen


	//  Ausgabe des Kopfes der CoverSection
    virtual ErrCode OutputFirstData (int FileHandle = 0);

	//  abstrakte Funktion für Ausgabe der Daten
    virtual ErrCode OutputData (GSTRUCT &GS, MFELD *pMF, 
    							char *pIdentKurzText = NULL) = 0;

	//  MainCover löschen
    virtual ErrCode DeleteCover (void); // Cover löschen

	//  True, wenn im Cover Daten speichert wurden, sonst False
    virtual Bool hasData (void) = 0;
};

//  Verwaltung und Ausgabe eines Texte-Covers (ANNOTEXT)
class TexteCover : public Cover {
private:
//  Attribute
    TexteSection _TS;       // Ausgabe der eigentlichen Daten

public:
//  Konstruktor/Destruktor
    TexteCover (pchar pCoverName) : Cover (pCoverName) {}
    ~TexteCover (void) {}

//  weitere Member-Funktionen
	//  Ausgabe
	//      + Kopf der CoverSection
	//      + Kopf der TexteSection
    ErrCode OutputFirstData (int FileHandle = 0);

	//  Ausgabe
	//      + der Ende-Zeile der TexteSection
	//      + Aufruf der korr. Funktion der Basisklasse
    ErrCode OutputLastData (int FileHandleMainCover = 0,
			    int FileHandle = 0,
			    Section *pSection = NULL);

	//  Ausgabe der eigentlichen Daten
    ErrCode OutputData (GSTRUCT &GS, MFELD *pMF, char *pIdentKurzText = NULL);

	//  True, wenn im Cover Daten speichert wurden, sonst False
    Bool hasData (void);
};

//  Verwaltung und Ausgabe eines Punkte-Covers (POINT)
class PointCover : public Cover {
private:
//  Attribute
    LabelSection _LS;       // Ausgabe der eigentlichen Daten
    PatTable _PAT;          // Point-Attribut-Tabelle
    OFSTRUCT _ofp;          // File-Struktur für PAT-File

public:
//  Konstruktor/Destruktor
	//  Main-Cover und PAT anlegen
    PointCover (pchar pCoverName);
    ~PointCover (void) {}

//  weitere Member-Funktionen
	//  Ausgabe
	//      + Kopf der CoverSection
	//      + Kopf der LabelSection
	//      + Kopf unf Format der PAT
    ErrCode OutputFirstData (int FileHandle = 0);

	//  Ausgabe
	//      + Ende-Zeile der LabelSection
	//      + Aufruf der korr. Funktion der Basisklasse
    ErrCode OutputLastData (int FileHandleMainCover = 0,
			    int FileHandle = 0,
			    Section *pSection = NULL);

	//  Ausgabe der eigentlichen Daten
    ErrCode OutputData (GSTRUCT &GS, MFELD *pMF, char *pIdentKurzText = NULL);

	//  alle zugeh. Coverages löschen
    ErrCode DeleteCover (void);

	//  True, wenn im Cover Daten speichert wurden, sonst False
    Bool hasData (void);
};

//  Verwaltung und Ausgabe eines Flächen-Covers (POLYS)
class PolyCover : public Cover {
private:
//  Attribute
    ArcSection _AS;         // Ausgabe der eigentlichen Daten
    PalSection _PS;         // Ausgabe der Polygon-Topologie
    CntSection _CS;         // Ausgabe der Centroid-Punkte
    LabelSection _LS;       // Ausgabe der Label-Punkte
    PatTable _PAT;          // Polygon-Attribut-Tabelle
    long _NodeNr, _ArcNr,   // akt. Knoten- u. Arc-Nr.
	 _PolyNr;           // akt. Polygon-Nummer
    OFSTRUCT _ofpm,         // File-Strukturen für PAL-Dateien
	     _ofpu,         // für universe Polygon
	     _ofp,          // File-Struktur für PAT-File
	     _ofc,          // File-Struktur für Centroid-Section
	     _ofl;          // File-Struktur für Label-Section

public:
//  Konstruktor/Destruktor
	//  MainCover, PalSection und PAT anlegen
    PolyCover (pchar pCoverName);
    ~PolyCover (void) {}

//  weitere Member-Funktionen
    //  Ausgabe
	//      + Kopf der ArcSection
	//      + Kopf unf Format der PAT
	//      + leeres universe polygon ausgeben
    ErrCode OutputFirstData (int FileHandle = 0);

	//  Ausgabe
	//      + Ende-Zeile der ArcSection
	//      + komplette CNT-Section
	//      + komplette Label-Section
	//      + Kopf der PalSection
	//      + kopiere PalCoverages in MainCover
	//      + lösche PalCoverages
	//      + vervollständige universe Polygon
	//      + Anzahl Datensätze in PAT
	//      + Aufruf der korr. Funktion der Basisklasse
	//        dabei: PAT in MainCover kopieren
	//      + lösche PAT
    ErrCode OutputLastData (int FileHandleMainCover = 0,
			    int FileHandle = 0,
			    Section *pSection = NULL);

	//  Ausgabe der eigentlichen Daten
    ErrCode OutputData (GSTRUCT &GS, MFELD *pMF, char *pIdentKurzText = NULL);
	ErrCode OutputDataExt (GSTRUCT &GS, MFELD *pMF, char *pKurzText);

	//  alle zugeh. Coverages löschen
    ErrCode DeleteCover (void);

	//  True, wenn im Cover Daten speichert wurden, sonst False
    Bool hasData (void);
};

//  Verwaltung und Ausgabe eines Linien-Covers (ARCS)
class ArcCover : public Cover {
private:
//  Attribute
    ArcSection _AS;         // Ausgabe der eigentlichen Daten
    AatTable _AAT;          // Arc-Attribute-Table
    OFSTRUCT _ofa;

public:
//  Konstruktor/Destruktor
	//  MainCover und AAT erzeugen
    ArcCover (pchar pCoverName);
    ~ArcCover (void) {}

//  weitere Member-Funktionen
	//  Ausgabe
	//      + Kopf der ArcSection
	//      + Kopf unf Format der AAT
    ErrCode OutputFirstData (int FileHandle = 0);

	//  Ausgabe
	//      + Ende-Zeile der ArcSection
	//      + setze DataCount in AAT
	//      + Aufruf der korr. Funktion der Basisklasse
	//        kopiere Dabei AAT in MainCover
	//      + lösche AAT
    ErrCode OutputLastData (int FileHandleMainCover = 0,
			    int FileHandle = 0,
			    Section *pSection = NULL);

	//  Ausgabe der eigentlichen Daten
    ErrCode OutputData (GSTRUCT &GS, MFELD *pMF, char *pIdentKurzText = NULL);

	//  alle Coverages löschen
    ErrCode DeleteCover (void);

	//  True, wenn im Cover Daten speichert wurden, sonst False
    Bool hasData (void);
};

#endif  // _COVER_HXX
