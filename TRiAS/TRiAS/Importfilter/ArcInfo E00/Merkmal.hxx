/*
File: MERKMAL.HXX
realiert die Verwaltung einer Merkmals-Tabelle.

erarbeitet : J. Benkenstein                 Stand vom 12.1.1994
*/

#ifndef _MERKMAL_HXX
#define _MERKMAL_HXX

enum TableTypes { PatTable, AatTable, OtherTable, UnknownTable };

//  Die Klasse speichert alle Informationen zu einem Merkmal.
class Merkmal {
private:
// Attribute
    Bool _Valid;            // Gültigkeitsflag
    long _MK;               // für Merkmal vergebener Kode
    pchar _pName;           // Merkmalsname
    short _La;              // Länge des Merkmals
    short _MaxLa;           // max. Länge
    short _Col;             // Spalte im Merkmalssatz
    Bool _Result;           // Konstruktor-Flag

public:
//  Konstruktor/Destruktor
    Merkmal (long MK, pchar Name, short La, short Col);
    ~ Merkmal (void);

// sonstige Member
    Bool Result (void) { return _Result; }
    long  MerkmalsKode (void) { return _MK; }
    pchar MerkmalsName (void) { return _pName; }
    short &MerkmalsLaenge (void) { return _La; }
    short &MerkmalsSpalte (void) { return _Col; }
    Bool &Valid (void) { return _Valid; }
    short &MaxLa (void) { return _MaxLa; }

//  friend Funktionen
    void* GetMName (void *pObj);            // Get-Key-Funktion
	int CompareNames (void *pObj1, void *pObj2);
};

class Entries;
//  Die Klasse verwaltet Merkmalsbeschreibungen.
class MerkmalsBaum : public CTree {
private:
//  Attribute
    long _Cnt;          // Anzahl der auszugebenden Merkmalssätze
    short _ActCol;      // aktuelle Lesespalte
    Bool _OutTXM;       // Merkmale bereits in PBD ausgegeben ?
    
//	Daten für "sonstige" Tabellen    
    char *_pTableName;	// Tabellen-Name (nur für "sonstige" Tabellen gespeichert)
    OFSTRUCT _of;
    HFILE _fh;
    
public:
	TableTypes _TableType;			// Tabellentyp	    

protected:
    void __export UserDelete (void *pObj);

	// nächsten Merkmalssatz aus Eingabe-Datei lesen
    Bool _ReadNextRecord (pchar pBuffer, short Cnt);
                                
    //	Merkmal in Text-Datei ausgeben
	Bool _OutputMerkmal (char *pMerkmalsWert);    	

public:
//  Konstruktor/Destruktor
    MerkmalsBaum (void);
    ~ MerkmalsBaum (void);      // Tabelleninhalt löschen

// sonstige Member
	// wenn Name gültig, dann neuen Eintrag in Liste erzeugen,
	// sonst nur Spaltenzähler weitersetzen
    Bool AddMerkmal (short La, pchar pMerkmalsName = NULL, Bool UserIDFeld = False);
    
    Bool AddMerkmal (long MKode, pchar pKurzText);

    long &Cnt (void) { return _Cnt; }

	// Merkmale in PBD ausgeben
    Bool OutTXM (void);

	// Merkmale einschließlich Geometrie ausgeben
    Bool OutMerkmale (Entries *pE, Bool CheckUniPoly, Bool Output);

	// interne Werte rücksetzen und Objekte ungültig erklären
    Bool Reset (void);

    Bool ReadMerkmale (void);						// alle Merkmalskodes lesen
    
    Bool StoreTableName (char *);					// Tabellen-Name speichern
    
    Bool DeleteUnvalids (void);					// Ungültige Einträge löschen
};
DeclareLock (MerkmalsBaum, Merkmal);

#endif // _MERKMAL_HXX
