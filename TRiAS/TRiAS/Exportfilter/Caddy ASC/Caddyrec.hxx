/*
File: CADDYREC.HXX
realiert die Verwaltung eines Caddy-Rekord-Beschreibungs-Baumes.

Das Modul beinhaltet die eigentliche Konvertierung der TRIAS-Elemente
in entsprechende CADdy-Objekte.

erarbeitet : J. Benkenstein                 Stand vom 18. November 1992
*/

#ifndef _CADDYREC_HXX
#define _CADDYREC_HXX

// Die Klasse dient zur Verwaltung der Parameter, die für die Ausgabe eines
// kompletten Caddy-Rekords benötigt werden.
class OutputParams {
public:
//  Attribute
    int _FH;            // File-Handle
    GSTRUCT *_pGS;      // Geometrie-Struktur
    MFELD *_pMFeld;     // Merkmals-Feld
    long _Ind;          // aktueller Punkte-Index bei Folgen

    //  Konstruktor/Destruktor
	OutputParams (int FH, GSTRUCT *pGS, long Ind = 0, MFELD *pMFeld = NULL)
	{ _FH = FH; _pGS = pGS; _pMFeld = pMFeld; _Ind = Ind; }

	~OutputParams (void) {}
};

// Die Klasse dient zur Verwaltung der Basis-Attribute eines Caddy-Rekords.
class CaddyRekord {
private:
//  Attribute
    StringDup _Farbe;   // Farbe
    StringDup _Ebene;   // Ebenen-Nummer

    long _ID;           // Identfikator (Baum-Schlüssel)

protected:
    Bool _Result;       // Ergebnis der Operation
    StringDup _Kennung; // Kennbuchstabe

	// Visualisierungs-Information in VisInfo-Datei ausgeben
    ErrCode OutputVisInfo (int cfh, Color& Farbe, short CaddyFarbe,
			   short Eb, short Prio, pchar pKurzText);
	//  CADdy-Farbe bilden
    short CreateCaddyFarbe (Color Farbe);

public:
    // Konstruktor/Destruktor
	CaddyRekord (IdentDescription &ID, pchar pKennung, int FileHandle);
	virtual ~CaddyRekord (void) {}

	long & ID (void)       { return _ID; }

	Bool operator ! (void) { return _Result == False; }
	operator Bool (void)   { return _Result == True; }

		// kompletten Caddy-Rekord in Datei ausgeben
	virtual ErrCode Output (OutputParams &OP, pchar pMerkmal,
				pchar pFolge = NULL, pchar pEbene = NULL) = 0;
		// komplette Folge eines best. Caddy-Objektes ausgeben
	virtual ErrCode OutputFolge (OutputParams &, pchar) { return EC_OKAY; }

		// vollständigen Rekord-Vorspann in Datei ausgeben
	ErrCode ExportRecordHeader (int FileHandle, pchar pMerkmal,
				    pchar pFolge, pchar pEbene = NULL);

		// Typ zurückgeben
	virtual short isA (void) = 0;
};

// Die Klasse dient zur Verwaltung eines Caddy-Symbol-Rekords.
class CaddySymbol : public CaddyRekord {
private:
//  Attribute
    StringDup _Name;            // Symolname
    StringDup _DrehWinkel;      // Drehwinkel eines Symbols
    StringDup _SkalierungX;     // Skalierungs-Faktor in X-Richtung
    StringDup _SkalierungY;     // Skalierungs-Faktor in Y-Richtung

public:
//  Konstruktor/Destruktor
	CaddySymbol (IdentDescription &ID, int FileHandle);
	~CaddySymbol (void) {}

//  sonstige Member
	    // Symbol-Rekord ausgeben
	ErrCode Output (OutputParams &OP, pchar pMerkmal,
			pchar pFolge = NULL, pchar pEbene = NULL);

       short isA (void) { return OT_PUNKT; }
};

// Die Klasse dient zur Verwaltung eines CADdy-Linien-Rekords.
class CaddyLinie : public CaddyRekord {
private:
//  Attribute
    StringDup _Breite;          // Breite in 1/1000 Einheiten
    StringDup _Typ;             // Linientyp
    StringDup _iEbene;          // Ebenen-Nummer für Innenflächen
    short _TTyp;                // TRIAS-Typ

public:
//  Konstruktor/Destruktor
	CaddyLinie (IdentDescription &ID, int FileHandle);
	~ CaddyLinie (void) {}

//  sonstige Member
	    // Linien-Rekord ausgeben
	ErrCode Output (OutputParams &OP, pchar pMerkmal,
			pchar pFolge = NULL, pchar pEbene = NULL);
	ErrCode OutputFolge (OutputParams &OP, pchar pMerkmal); // komplette PolyLinien,
			// Flächen (einschl. Innenflächen) als Folge ausgeben

	short isA (void) { return _TTyp; }
};

// Die Klasse dient zur Verwaltung eines Text-Rekords.
class CaddyText : public CaddyRekord {
private:
//  Attribute
    StringDup _Hoehe, _Breite, _Abstand, _DrehWinkel,
	      _SchriftSatz, _RefPunkt, _Zusatz,
	      _Proportional, _Kursiv, _Richtung;

public:
//  Konstruktor/Destruktor
	CaddyText (IdentDescription &ID, int FileHandle);
	~CaddyText (void) {}

//  sonstige Member
	    // Text-Rekord ausgeben
	ErrCode Output (OutputParams &OP, pchar pMerkmal,
			pchar pFolge = NULL, pchar pEbene = NULL);

	short isA (void) { return OT_TEXT; }
};

// Die Klasse ElementeBaum verwaltet Caddy-Objekte in einem Baum.
class CaddyRekordBaum : public CTree {
protected:
	void __export UserDelete (void *pObj);

public:
//  Konstruktor/Destruktor
	CaddyRekordBaum (void);
	~ CaddyRekordBaum (void);

//  sonstige Member
	    // neuen Rekord erzeugen und in Baum einfügen,
	    // VisInfo-Datei ergänzen
	ErrCode AddCaddyRekord (IdentDescription &ID, int FilHandle);
	    // über Identifikator selektierten Rekord in Datei ausgegeben
	ErrCode OuputCaddyRekord (OutputParams &OP, MFELD *pMF);
	    // Ebenen-Tabelle ausgeben
};

DeclareLock (CaddyRekordBaum, CaddyRekord);

#endif // _CADDYREC_HXX
