/*
Datei: COVER.HXX

Basisklassen f�r die Erzeugung des lesbaren Arc/Info-Austausschformates.
Verwaltung der m�lglichen Arc/Info-Covers.

Erarbeitet: J. Benkenstein                  Begonnen am: 3. Mai 1993
*/

#ifndef _COVER_HXX
#define _COVER_HXX

class Section;

//  Basisklasse f�r das Erzeugen und Verwalten eines "Covers" in Arc/Info.
class Cover {
protected:
    OFSTRUCT _of;                   //  File-Struktur
    ErrCode _RC;                    //  Returnkode

	//  Inhalt der Datei kopieren, _RC wird gesetzt
    ErrCode FileCopy (int FileHandleDest, int FileHandleSource);

	//  Cover erzeugen, of-Struktur f�llen
    ErrCode CreateCover (OFSTRUCT &of, pchar pPath, uint ResIDext);


public:
//  Konstruktor/Destruktor
	//  Dateiname mu� vollst�ndigen Pfad beinhalten !
    Cover (pchar pCoverName);   // Datei �ffnen, Handle und RC setzen
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
	//        Dateien m�ssen ge�ffnet und positioniert sein
	//      + InfoSectio-Ende
	//      + CoverSection-Ende
	// _RC setzen
	//  MainCover mu� ge�ffnet und positioniert sein
    virtual ErrCode OutputLastData (int FileHandleMainCover = 0,
				    int FileHandle = 0,
				    Section *pSection = NULL);

	//  Ausgabe der Zeile f�r den Import des Covers in SML-Makro.
	//  Datei mu� ge�ffnet und positioniert sein.
    virtual ErrCode OutputImportMakro (int FileHandle); // _RC setzen


	//  Ausgabe des Kopfes der CoverSection
    virtual ErrCode OutputFirstData (int FileHandle = 0);

	//  abstrakte Funktion f�r Ausgabe der Daten
    virtual ErrCode OutputData (GSTRUCT &GS, MFELD *pMF, 
    							char *pIdentKurzText = NULL) = 0;

	//  MainCover l�schen
    virtual ErrCode DeleteCover (void); // Cover l�schen

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
    OFSTRUCT _ofp;          // File-Struktur f�r PAT-File

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

	//  alle zugeh. Coverages l�schen
    ErrCode DeleteCover (void);

	//  True, wenn im Cover Daten speichert wurden, sonst False
    Bool hasData (void);
};

//  Verwaltung und Ausgabe eines Fl�chen-Covers (POLYS)
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
    OFSTRUCT _ofpm,         // File-Strukturen f�r PAL-Dateien
	     _ofpu,         // f�r universe Polygon
	     _ofp,          // File-Struktur f�r PAT-File
	     _ofc,          // File-Struktur f�r Centroid-Section
	     _ofl;          // File-Struktur f�r Label-Section

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
	//      + l�sche PalCoverages
	//      + vervollst�ndige universe Polygon
	//      + Anzahl Datens�tze in PAT
	//      + Aufruf der korr. Funktion der Basisklasse
	//        dabei: PAT in MainCover kopieren
	//      + l�sche PAT
    ErrCode OutputLastData (int FileHandleMainCover = 0,
			    int FileHandle = 0,
			    Section *pSection = NULL);

	//  Ausgabe der eigentlichen Daten
    ErrCode OutputData (GSTRUCT &GS, MFELD *pMF, char *pIdentKurzText = NULL);
	ErrCode OutputDataExt (GSTRUCT &GS, MFELD *pMF, char *pKurzText);

	//  alle zugeh. Coverages l�schen
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
	//      + l�sche AAT
    ErrCode OutputLastData (int FileHandleMainCover = 0,
			    int FileHandle = 0,
			    Section *pSection = NULL);

	//  Ausgabe der eigentlichen Daten
    ErrCode OutputData (GSTRUCT &GS, MFELD *pMF, char *pIdentKurzText = NULL);

	//  alle Coverages l�schen
    ErrCode DeleteCover (void);

	//  True, wenn im Cover Daten speichert wurden, sonst False
    Bool hasData (void);
};

#endif  // _COVER_HXX
