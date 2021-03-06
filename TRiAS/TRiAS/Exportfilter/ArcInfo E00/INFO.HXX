/*
Datei: INFO.HXX

Basisklassen f�r die Erzeugung des lesbaren Arc/Info-Austausschformates.
Verwaltung der im Format auftretenden Informations- (Sachdaten-) Dateien.

Erarbeitet: J. Benkenstein                  Begonnen am: 30. April 1993
*/

#ifndef _INFO_HXX
#define _INFO_HXX

enum AttrType { PAT, AAT };
enum FeatureClass { _Arc, _Poly, _Point, _Text };

// struct MFELD;

//  Parameter-Klasse
class Params {
//  Attribute
public:
    MFELD *pMF;
    AttrType Type;
    uint ResourceId;
    short ActOut;           // Parameter f�r Format-Ausgabe
    short LastLen;
    short Count;
    short TotalLen;
    short ActCol;
    char *pIdentKurzText;
    int FileHandle;
    pchar pFileName;

//  Konstruktor/Destruktor
    Params (void);      // alle Parameter r�cksetzen
    ~ Params (void) {}
};

//  Basisklasse f�r die Verwaltung und Ausgabe einer Sachdaten-Datei.
class Info {
private:
//  Attribute
    long _FieldCountPos,        // Dateipositionen von Werten,
	 _RecordLenPos,         // die im Laufe der Konvertierung
	 _DataCountPos;         // evtl. korrigiert werden m�ssen

public:
//  Konstruktor/Destruktor
    Info ();
    virtual ~Info (void) {}

//  weitere Member-Funktionen:
	//  wenn die korrospondierenden Variablen g�ltige Werte besitzen,
	//  werden neuen Werte in die zuge�ffnete Datei geschrieben
    ErrCode SetDataCount (int FileHandle, long NewDataCount);
    ErrCode SetRecordLen (int FileHandle, short NewRekordLen);
    ErrCode SetFieldCount (int FileHandle, short NewFieldCount);

//  Dateien m�ssen zuvor ge�ffnet und positioniert sein
	//  Ausgabe des Formatkopfes - Filename mu� frei von Umlauten sein.
	//  Die Dateipositionen von
	//          - FieldCount (Anzahl der Felder),
	//          - RercordLen (Summe der L�nge aller Felder) und
	//          - DataCount (Summe der Datens�tze) werden gespeichert.
    ErrCode OutputHead (int FileHandle, pchar pFileName, uint FileExtId,
			short FieldCount, short RecordLen, long DataCount);

//  virtuelle Funktionen
	//  Format der Sachdaten aus Resource lesen und ausgeben
    virtual ErrCode OutputFormat (Params *pParams = NULL);

	//  abtrakte Funktion f�r die Ausgabe der Sachdaten
    virtual ErrCode OutputData (int FileHandle, void *pData1,
					void *pData2, void *pData3, void *pData4, void* pData5) = 0;
};

//  Die Klasse realiesiert die Ausgabe der Zeichnungsgrenzen in die BND-Datei.
class Boundaries : public Info {
public:
//  Konstruktor/Destruktor
    Boundaries (void) {}
    ~Boundaries (void) {}

//  weitere Member-Funktionen
	//  Dateiname darf keine Umlaute enthalten.
    ErrCode OutputHead (int FileHandle, pchar pFileName);
	//  Format der Sachdaten aus Resource lesen und ausgeben
    ErrCode OutputFormat (Params *pParams = NULL);
    ErrCode OutputData (int FileHandle, void *pData1, void *pData2,
						void *pData3, void *pData4, void *pData5);
};

//  Die Klasse realisiert die Ausgabe von 4 Passpunkten in die TIC-Datei.
class PassPoints : public Info {
public:
//  Konstruktor/Destruktor
    PassPoints (void) {}
    ~PassPoints (void) {}

//  weitere Member-Funktionen
	//  Dateiname darf keine Umlaute enthalten.
    ErrCode OutputHead (int FileHandle, pchar pFileName);
	//  Format der Sachdaten aus Resource lesen und ausgeben
    ErrCode OutputFormat (Params *pParams = NULL);
    ErrCode OutputData (int FileHandle, void *pData1, void *pData2,
						void *pData3, void *pData4, void *pData5);
};

//  Basisklasse f�r die Verwaltung der Sachdaten in einer Attributtabelle
class AttrTable : public Info {
protected:
//  Attribute
    long _Count;        // akt. Anzahl ausgegebener Merkmalss�tze

public:
//  Konstruktor/Destruktor
    AttrTable (void) { _Count = 0; }
    ~ AttrTable (void) {}

//  weitere Member-Funktionen
    long GetCount (void) { return _Count; }

	//  Format der Sachdaten aus Resource lesen und ausgeben
    ErrCode OutputFormat (Params *pParams = NULL);

	//  Merkmalssatz ausgeben
    ErrCode OutputData (int FileHandle, void *pData1, void *pData2,
						void *pData3, void *pData4, void *pData5);
};

//  Arc-Attribut-Tabelle (AAT)
class AatTable : public AttrTable {
public:
//  Konstruktor/Destruktor
    AatTable (void) {}
    ~ AatTable (void) {}

//  weitere Member-Funktionen
	//  Dateiname darf keine Umlaute enthalten.
    ErrCode OutputHead (int FileHandle, pchar pFileName);

	//  Format der Sachdaten aus Resource lesen und ausgeben
    ErrCode OutputFormat (Params *pParams = NULL);

	//  Merkmalssatz ausgeben
    ErrCode OutputData (int FileHandle, void *pData1, void *pData2,
						void *pData3, void *pData4, void *pData5);
};

//  Point/Polygon-Attribut-Tabelle (PAT)
class PatTable : public AttrTable {
private:
//  Attribute
    long _UniPos;

public:
//  Konstruktor/Destruktor
    PatTable (void) { _UniPos = 0; }
    ~ PatTable (void) {}

//  weitere Member-Funktionen
	//  Dateiname darf keine Umlaute enthalten.
    ErrCode OutputHead (int FileHandle, pchar pFileName);

	//  Format der Sachdaten aus Resource lesen und ausgeben
    ErrCode OutputFormat (Params *pParams = NULL);

	//  Merkmalssatz ausgeben
    ErrCode OutputData (int FileHandle, void *pData1, void *pData2,
						void *pData3, void *pData4, void *pData5);

	//  leeres universe polygon ausgeben
    ErrCode OutputEmptyUniPoly (Params &Par);

	//  universe Polygon vervollst�ndigen
	//  Section beinhaltet Bildma�e
    ErrCode OutputFillUniPoly (int FileHandle, Section &S);
};

#endif  // _INFO_HXX
