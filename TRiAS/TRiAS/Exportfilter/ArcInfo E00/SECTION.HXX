/*
Datei: SECTION.HXX

Basisklassen für die Erzeugung des lesbaren Arc/Info-Austausschformates.
Verarbeitung der im Format auftretenden Sections.

Erarbeitet: J. Benkenstein                  Begonnen am: 30. April 1993
					      Stand vom:  3. Mai 1993
*/

#ifndef _SECTION_HXX
#define _SECTION_HXX

//  class für Arc-Topologie
class NodePolyNr {
public:
//  Attribute
    long FirstNode, LastNode, LeftPoly, RightPoly, ArcNr;

//  Konstruktor/Destruktor
    NodePolyNr (void) { FirstNode = LastNode = LeftPoly = RightPoly = ArcNr = 0L; }
    NodePolyNr (NodePolyNr &NP);
    ~ NodePolyNr (void) {}
};

//  Verwaltung einer Knoten-Polygon-Nummern-Liste
class NodePolyNrList : public CListContainer {
private:
//  Attribute
    Bool _DrehSinn;     // True: mathemat. positiv, sont Uhrzeigersinn

protected:
    void EXPORTFLT UserDelete (void *pObj);

public:
//  Konstruktor/Destruktor
    NodePolyNrList (Bool DrehSinn);
    ~ NodePolyNrList (void);

//  weitere Member-Funktionen
	// True, wenn neuer Eintrag in Liste gespeichert, sonst False
    Bool Add (NodePolyNr &NP);

    Bool DrehSinn (void) { return _DrehSinn; }
};

DeclareLock (NodePolyNrList, NodePolyNr);

// Basisklasse für die Ausgabe einer Arc/Info-Section.
// Es wird die Ausgabe der Kopf- und Fußzeile einer Section, sowie
// die Ausgabe der eigentlichen Daten geregelt.
class Section {
protected:
    double _Xmin, _Ymin, _Xmax, _Ymax;

public:
//  Konstruktor/Destruktor: Bildmasse init.
    Section (void);
    virtual ~Section (void) {}

//  Member-Funktionen
	// an Hand der veräderten Bildmasse wird entschieden, ob eine
	// Section Daten gespeichert hat
    Bool hasData (void);

	//  Bildmasse ggf. korrigieren
    inline
    void SetXYcon (double &X, double &Y);

	//  Attribute abfragen
    double & XMin (void) { return _Xmin; }
    double & YMin (void) { return _Ymin; }
    double & XMax (void) { return _Xmax; }
    double & YMax (void) { return _Ymax; }

//  virtuelle Funktionen
	//  Fußzeile in zuvor geöffnete und positionierte Datei ausgeben
    virtual ErrCode OutputFoot (int FileHandle);

//  nicht implementierte virtuelle Funktionen
	//  Kopf/Daten in zuvor geöffnete und positionierte Datei ausgeben
    virtual ErrCode OutputHead (int FileHandle) = 0;

//  friend-Klassen
    friend class Cover;
    friend class PatTable;
    friend class PalSection;
    friend class CntSection;
};

//  Ausgabe und Verwaltung einer Arc-Section
class ArcSection : public Section {
private:
//  Attribute
    long _ActNumber;        // akt. Zählnummer

public:
//  Konstruktor/Destruktor
    ArcSection (long ActNr = 1) { _ActNumber = ActNr; }
    ~ArcSection (void) {}

//  weitere Member-Funktionen
    long ActNumber (void) { return _ActNumber; }
    ErrCode OutputHead (int FileHandle);
    ErrCode OutputData (int fh, GSTRUCT &GS, NodePolyNr &NP, long Count,
			long AktIndex = 0);
};

//  Ausgabe und Verwaltung einer Texte-Section
class TexteSection : public Section {
public:
//  Konstruktor/Destruktor
    TexteSection (void) {}
    ~TexteSection (void) {}

//  weitere Member-Funktionen
    ErrCode OutputHead (int FileHandle);
    ErrCode OutputData (int FileHandle, GSTRUCT &GS, pchar pText);
};

//  Ausgabe und Verwaltung einer Label-Section
class LabelSection : public Section {
private:
//  Attribute
    long _ActNumber;        // akt. Zählnummer

public:
//  Konstruktor/Destruktor
    LabelSection (long ActNr = 1) { _ActNumber = ActNr; }
    ~LabelSection (void) {}

//  weitere Member-Funktionen
    long ActNumber (void) { return _ActNumber; }
    ErrCode OutputHead (int FileHandle);
    ErrCode OutputFoot (int FileHandle);
    ErrCode OutputData (int FileHandle, double &X, double &Y,
			short Offset = 0);
};

//  Ausgabe und Verwaltung einer Info-Section
class InfoSection : public Section {
public:
//  Konstruktor/Destruktor
    InfoSection (void) {}
    ~InfoSection (void) {}

//  weitere Member-Funktionen
    ErrCode OutputHead (int FileHandle);
    ErrCode OutputFoot (int FileHandle);
};

//  Ausgabe und Verwaltung einer Cover-Section
class CoverSection : public Section {
public:
//  Konstruktor/Destruktor
    CoverSection (void) {}
    ~CoverSection (void) {}

//  weitere Member-Funktionen
    ErrCode OutputHead (int FileHandle);
    ErrCode OutputFoot (int FileHandle);
};

class NodePolyNrList;

//  Realisierung einer Polygon-Topologie
class PalSection : public Section {
private:
//  Attribute
    long _PolyCnt;      // Anzahl ausgeg. Polygone für universe Polygon
    short _UniCnt,      // Ausgabe-Zähler
		  _MainCnt,		// normale Fläche mit Inseln
		  _IslandCnt;	// Anzahl Inseleinträge

protected:
	//  Zeilenvorschub ausgeben, Zeilen-Zähler erhöhen
    ErrCode _OutputCR (int FileHandle, short &Cnt);

	//  ggf. Zeilenvorschub
    ErrCode _OutputLastCR (int FileHandle, short &Count);

	//  Insel ausgeben
    ErrCode _OutputIsland (int FileHandle, NodePolyNrList *pNL,
			   short &RowCnt);

public:
//  Konstruktor/Destruktor
    PalSection (void) { _PolyCnt = 0; _UniCnt = _MainCnt = _IslandCnt = 0;}
    ~ PalSection (void) {}

//  weitere Member-Funktionen
    ErrCode OutputHead (int FileHandle);

	//	Datenkopf ausgeben
    ErrCode OutputDataHead (int FileHandle, Section &Sec, long Count);

	//  Datenkopf ausgeben: Anzahl wird über "GS" berechnet
    ErrCode OutputDataHead (int FileHandle, GSTRUCT &GS);

	//	Datenkopf ausgeben: Für Inseln
	ErrCode OutputDataHead (int fh, double *pX, double *pY, long lCnt, BOOL bIsland = FALSE);

	//  Insel für universe polygon ausgeben
    ErrCode OutputUniIsland (int FileHandle, NodePolyNrList *pNL);

	//  "normale" Insel ausgeben
    ErrCode OutputMainIsland (int FileHandle, NodePolyNrList *pNL);

	//  äußere Masche ausgeben
    ErrCode OutputAussMasche (int FileHandle, NodePolyNrList *pNL, BOOL bIsland = FALSE);

	//  ggf. Zeilenvorschub
    ErrCode OutputLastCR (int FileHandle, short &Count);

	//	Inseltopologie ausgeben
	ErrCode OutputTopologie (int fhd, int fhs);

    long PolyCount (void) { return _PolyCnt; }
    short UniCount  (void) { return _UniCnt; }
    short MainCount (void) { return _MainCnt; }
};

//  Ausgabe und Verwaltung einer Centroid-Section
class CntSection : public Section {
public:
//  Konstruktor/Destruktor
    CntSection (void) {}
    ~CntSection (void) {}

//  weitere Member-Funktionen
    ErrCode OutputHead (int FileHandle);

	//  Schwerpunkt-Koordinaten der Fläche ausgeben
    ErrCode OutputData (int FileHandle, double &Xs, double &Ys);

	//  Schwerpunkt-Koordinaten aus übergebenem Container berechnen
	//  und ausgeben
    ErrCode OutputData (int FileHandle, Section &Sec);
};

#endif  // _SECTION_HXX
