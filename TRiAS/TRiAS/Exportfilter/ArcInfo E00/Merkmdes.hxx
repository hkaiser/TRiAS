/*
File: MERKMDES.HXX
realiert die Verwaltung eines Merkmal-Beschreibungs-Baumes.

erarbeitet : J. Benkenstein                              Begonnen am 9. Mai 1993
*/

#ifndef _MERKMDES_HXX
#define _MERKMDES_HXX

// Die Klasse ExtMerkmalDescription speichert die "Attribute" eines Merkmals
class ExtMerkmalDescription : public MerkmalDescription
{
private:
//  Attribute
	short _Column;                    // Spalte für Datei-Ausgabe (PAT)
	short _ArcColumn;                  // (AAT)
	pchar _pName;                      // konvertierter Merkmals-Name
	ErrCode _RC;                            // Konstruktor-Flag

public:
//  Konstruktor/Destruktor
	ExtMerkmalDescription (MerkmalDescription &MD, short &Column,
			       short &Unknown);  // _RC wird gesetzt
	~ ExtMerkmalDescription (void);

//  sonstige Member
		// Konstruktor-Flag abfragen
	ErrCode Result (void) { return _RC; }

	short & Column (void) { return _Column; }
	short & ArcColumn (void) { return _ArcColumn; }

		 //  Merkmalsnamen lesen, bei Fehler NULL
	pchar GetName (void);

		//  alten Namen löschen, Zeiger neu setzen
	ErrCode SetName (pchar pNewName);

//  Friend-Funktionen
	friend int CompareMKodes (void *pObj1, void *pObj2);
	friend void* GetMKode (void *pObj);
};

// Die Klasse ExtMerkmalDescriptionTree verwaltet ExtMerkmalDescriptions
// in einem Baum.
class ExtMerkmalDescriptionTree : public CTree
{
private:
// Attribute
	short _ActColumn;        // aktuelle Spalte für Datei-Schreiben (PAT)
	short _ActArcColumn;  // (AAT)
	short _Unknown;    // Anzahl unbekannter Merkmalsnamen                             

protected:
	void EXPORTFLT UserDelete (void *pObj);

public:
//  Konstruktor/Destruktor
	ExtMerkmalDescriptionTree (void);   // Attribute init.
	~ ExtMerkmalDescriptionTree (void); // Bauminhalt löschen

//  sonstige Member
	short & ActColumn (void) { return _ActColumn; }
	short & ActArcColumn (void) { return _ActArcColumn; }

	short FindColumn (long MCode);    // Spalte eines Merkmals über
		  // seinen Kode suchen, die im Fehlerfall 0 ist (für PAT)

	short FindArcColumn (long MCode);   // Spalte eines Merkmals über
		  // seinen Kode suchen, die im Fehlerfall 0 ist (für AAT)

	short FindColumnWidth (long MCode); // Spaltebreite eines Merkmals über
		  // seinen Kode suchen, die im Fehlerfall 0 ist.

	Bool AddMerkmDescr (MerkmalDescription &MD); // neue Beschrbg. in Baum

		//  Zeiger eines Merkmalstextes lesen, der im Fehlerfall NULL ist
	pchar GetMerkmalName (long MCode);  // und über delete freizugeben ist

		//  Neuen Merkmalsnamen speichern
	ErrCode SetMerkmalName (long MCode, pchar pNewName);

		//  True, wenn weiteren Merkmalsnamen gefunden, der nicht
		//  dem übergebenen Objekt (ID) gehört, sonst False
	Bool OtherMerkmalName (long MKode, pchar pMName);

/*
	// alle Merkmalsbeschreibungen mit ungültigen Parametern löschen
	ErrCode DeleteUnvalids (void);
*/
};

DeclareLock (ExtMerkmalDescriptionTree, ExtMerkmalDescription);

#endif // _MERKMDES_HXX
