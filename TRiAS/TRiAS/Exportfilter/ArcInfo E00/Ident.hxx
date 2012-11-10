/*
File: IDENT.HXX
realiert die Verwaltung einer Identifikator-Beschreibungs-Baumes
für den Arc/Info-Filter.

erarbeitet : J. Benkenstein                 Begonnen am 4. Mai 1993
*/

#ifndef _IDENT_HXX
#define _IDENT_HXX

class Cover;

//  erweiterte Identifikator-Beschreibungsklasse
class ExtIdentDescription : public IdentDescription {
private:
//  Attribute
    Cover *_pCover;         // Zeiger aus zugeh. Arc/Info-Objekt
    pchar _pFileName;       // Zeiger auf Dateinamen, der aus dem
			    			// Kurztext des IDs gebildet wird
	char *_pKurzText;		// ID-KurzText			    			
    ErrCode _RC;            // Returnkode
    char _Typ;              // Darstellungs-Typ ('P', 'L', 'F', 'T')

//  Konstruktor/Destruktor
public:
	//  Filenamen bilden und speichern, _RC setzen
    ExtIdentDescription (IdentDescription &IDD);
	//  interne Variablen freigeben
    ~ ExtIdentDescription (void);

//  weitere Member
    ErrCode Result (void) { return _RC; }
	//  zugehörige Arc/Info-Cover erzeugen, _RC setzen
    ErrCode CreateCover (pchar pPath);

	//  lesen des Covernamens (_RC setzen), Zeiger mit Suchstring muß über
    pchar GetCoverName (void);      // delete freigegeben werden !

	//  Covernamen neu setzen, _RC setzen
    pchar SetCoverName (pchar pNewCoverName);

	//  eigentlichen Daten ausgeben
    ErrCode OutputData (GSTRUCT &GS, MFELD *pMF);

	//  Coverages-Initialisierung
    ErrCode OutputFirstData (void);

	//  abschl. Infos in Coverages ausgeben
    ErrCode OutputLastData (void);

	//  Cover löschen
    ErrCode DeleteFile (void);

	//  ImportMakro ausgeben
    ErrCode OutputImportMakro (int FileHandle);

	//  True, wenn Cover Daten gespeichert hat, sonst False
    Bool hasData (void);

	//  Darstellungstyp Typ lesen
    char IntTyp (void) { return _Typ; }

	//	KurzText des Identifikators lesen    
    char * IdentKurzText (void) { return _pKurzText; }
};
                
class PolyCover;
class ArcCover;
class PointCover;
class TexteCover;                
                
// Die Klasse ExtIdentDescriptionTree verwaltet erweiterte Identifikator-
// Beschreibungen in einem Baum.
class ExtIdentDescriptionTree : public CTree {
private:
	PolyCover* _pPolyCover;		// Ausgabe in diese 4 Coverages
	ArcCover* _pArcCover;  
	PointCover* _pPointCover;
	TexteCover* _pTexteCover;
	

protected:
    void EXPORTFLT UserDelete (void *pObj);

public:
//  Konstruktor/Destruktor
    ExtIdentDescriptionTree (void);
    ~ ExtIdentDescriptionTree (void);

//  weitere Member
	// neue ID-Beschr. in Baum
    ErrCode AddIDD (IdentDescription &IDD);

	// Import-Makro ausgeben
    ErrCode OutputImportMakro (int FileHandle);

	// Covernamen im Dialog prüfen
    ErrCode CheckCoverNameDialog (BOOL);

	//  eigentlichen Daten ausgeben
    ErrCode OutputData (GSTRUCT &GS, MFELD *pMF);

	//  Coverages erzeugen und initialisieren
    ErrCode OutputFirstData (pchar pPath);

	//  abschl. Infos in Coverages ausgeben
    ErrCode OutputLastData (void);

	//  alle Dateien löschen
    ErrCode DeleteAllFiles (void);

	//  True, wenn noch ein weiteres Objekt den gesuchten Namen
	//  enthält, sonst False
    Bool OtherCoverName (long ID, pchar pSearchName, char Typ);

	//  Zeiger eines Covernamens lesen, der im Fehlerfall NULL ist
    pchar GetCoverName (long ID, char Typ); // und über delete freizugeben ist

	//  Neuen Covernamen speichern
    ErrCode SetCoverName (long ID, pchar pNewCoverName, char Typ);

	// zu einem Text-Objekt über seinen ID die Höhe lesen
    ErrCode FindTextHoehe (long ID, double &Hoehe);

	// zu einem Text-Objekt über seinen ID den Drehwinkel bestimmen,
    ErrCode FindTextDrehWinkel (long ID, double &Winkel);

//  Baum-Zugriffsfunktionen
    friend int CompareExtIDs (void *Obj1, void *Obj2);
    friend void* GetExtID (void *Obj);
};
DeclareLock (ExtIdentDescriptionTree, ExtIdentDescription);

#endif // _IDENT_HXX
