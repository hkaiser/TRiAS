
/*
File: FILEPOS.HXX
realisiert die Verwaltung von Datei-Positionen.

erarbeitet : J. Benkenstein                 Stand vom 10.1.1994
*/

#ifndef _FILEPOS_HXX
#define _FILEPOS_HXX

//  Die Klasse verwaltet Punkt-Objekte
class PointEntry {
private:
//  Attribute:
    long _Nr;               // interner Schlüssel
    double _X, _Y;          // Koordinaten des Punktes

public:
//  Konstruktor/Destruktor
    PointEntry (long Nr, double &X, double &Y);
    ~PointEntry (void) {}

//  weitere Member-Funktionen
    long &Nr (void) { return _Nr; }
    double &X (void) { return _X; }
    double &Y (void) { return _Y; }

//  friend-Funktionen
    friend int CompareNrs (void *pObj1, void *pObj2); // KeyCompare-Funktion
    friend void* GetPointNr (void *pObj);             // GetKey-Funktion
};

//  Basisklasse zu Verwaltung von Einträgen
class Entries : public CTree {
protected:
//  Attribute
    long _ActNr;                    // akt. Schlüsselnummer
    void __export UserDelete (void *pObj);
	DWORD _StartTime, _OptmizeTime; // Zeit-Variablen für Baum-Optimierung


public:
//  Konstruktor/Destruktor
    Entries (pGetKeyFcn, pKeyCmpFcn = StrCmp);
    virtual ~Entries (void);

//  virtuelle Funktionen
    virtual Bool OutAllGeo (void);          // Gesamte Geometrie ausgeben

//  reine virtuelle Funktionen
    virtual DGeoTyp isA (void) = 0;         // Typ lesen
    virtual long OutGeo (long Nr) = 0;      // liefert nach Ausgabe
					    // ObjNummer; bei Fehler -1
//  Nachfrage ob Nutzer-Abbruch
    Bool Break (void);

	//  Optimierung des Baumes ggf. durchführen:
	//  Wenn für die letzte Eintragsspeicherung mehr als 10% der Zeit benötigt
	//  wurde, die für eine vollst. Optimierung gebraucht wird.
    void CheckOptimize (void);
};

//  Tabelle zur Verwaltung von "PointEntry"
class PointEntries : public Entries {
protected:
    void __export UserDelete (void *pObj);

public:
//  Konstruktor/Destruktor
    PointEntries (void);
    ~ PointEntries (void);                  // Tabelleninhalt löschen

//  sonstige Member
    DGeoTyp isA (void) { return DGT_Punkt; }
    Bool AddEntry (double &X, double &Y);   // neuen Punkt speichern
    long OutGeo (long Nr);                  // Geometrie ausgeben
};
DeclareLock (PointEntries, PointEntry);

//  Die Klasse verwaltet eine Datei-Referenz auf ein Linien-Objekt
class LinePos {
private:
//  Attribute:
    long _Pos;              // Dateiposition
    long _Nr;               // interner Schlüssel
    long _Cnt;              // Anzahl der Stützpunkte/Einträge

public:
//  Konstruktor/Destruktor
    LinePos (long Nr, long Cnt)
	    { _Nr = Nr; _Cnt = Cnt; _Pos = 0; }
    ~LinePos (void) {}

//  weitere Member-Funktionen
    long &Pos (void) { return _Pos; }
    long &Nr (void) { return _Nr; }
    long &Cnt (void) { return _Cnt; }
//  friend-Funktionen
    friend void* GetLineNr (void *pObj);                  // GetKey-Funktion
};

//  Tabelle zur Verwaltung von "LinePos"
class LineEntries : public Entries {
private:
//  Attribute
    FILE *_pFile;           	// für das Lesen der eigentlichen Koordinaten
    CFileBuffer _FileBuffer; 	// Dateipuffer
    Bool _Result;           	// Konstruktor-Flag

protected:
    void __export UserDelete (void *pObj);

public:
//  Konstruktor/Destruktor
    LineEntries (pchar pFileName);  // Name der Eingabe-Datei
    ~ LineEntries (void);           // Datei schließen, Tabelleninhalt löschen

//  sonstige Member
    DGeoTyp isA (void) { return DGT_Linie; }
    long GetCnt (long Nr);          // Anzahl der Punkte lesen, bei Fehler LONG_MAX
    Bool AddPos (long Pos);         // akt. Datei-Position speichern
    Bool AddNrCnt (long Nr, long Cnt); // Nummer und zugeh. Anz. Stützpunkte speichern
    long OutGeo (long Nr);          // Geometrie ausgeben

    Bool Result (void) { return _Result; }

	// Geometrie in Speicher ausgeben
    Bool OutGeometrie (long Nr, void *pX, void *pY, long &ActIndex, BOOL bHuge);

	// bei 2 identischen aufeinander folgenden Punkt wird der 2. ignoriert
	// "Cnt" wird dekrementiert
    Bool DeleteDoppPkt (double *&pX, double *&pY, long &Cnt);
};
DeclareLock (LineEntries, LinePos);

//  Die Klasse verwaltet Einträge der Pal-Section
class PalPos {
private:
//  Attribute:
    long _Size;             // Anzahl der Einträge
    long *_pArc;            // Arc-IDs
    long _Nr;               // Schlüssel für Baum

public:
//  Konstruktor/Destruktor
    PalPos (long Nr, long Size, long *pArcVec);
    ~ PalPos (void);

//  weitere Member-Funktionen
    long * ArcVektor (void) { return _pArc; }
    long Size (void) { return _Size; }
    long &Nr (void) { return _Nr; }

//  friend-Funktionen
    friend void* GetPalNr (void *pObj);                  // GetKey-Funktion
};

//  Die Klasse verwaltet PalPos-Einträge
class PalEntries : public Entries {
private:
//  Attribute
    Bool _First;                // zu Filterung des universe Polygons
    long _ActInd;               // akt. Eintrags-Index
    long _ActSize;              // akt. Vektorgröße
    long *_pActVec;             // akt. Vektor

protected:
    void __export UserDelete (void *pObj);

public:
//  Konstruktor/Destruktor
    PalEntries (void);
    ~ PalEntries (void);        // Tabelleninhalt löschen

//  sonstige Member
    DGeoTyp isA (void) { return DGT_Flaeche; }
    Bool AddPalVektor (long Size);      // neuen PalVektor erzeugen
    Bool AddPalEntry (long ArcNr);      // Eintrag in akt. Vektor speichern
    long OutGeo (long Nr);              // Geometrie ausgeben
};
DeclareLock (PalEntries, PalPos);

#endif // _FILEPOS_HXX
