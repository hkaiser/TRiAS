/*
File: MERKMAL.HPP
realiert die Verwaltung einer Merkmals-Tabelle.

erarbeitet : J. Benkenstein                 Stand vom 28.08.1995
*/

#ifndef _MERKMAL_HPP
#define _MERKMAL_HPP

//  Die Klasse speichert alle Informationen zu einem Merkmal.
class Merkmal 
{
private:
// 	Attribute
    ulong m_ulMKode;               	// für Merkmal vergebener Kode
    char * m_pMName;           		// Merkmalsname

public:
//  Konstruktor/Destruktor
	Merkmal (void) { m_pMName = NULL; m_ulMKode = 0; }
    ~ Merkmal (void);

// 	weitere Member
	Bool Init (char *pName, ulong ulMK);
    ulong  MerkmalsKode (void) { return m_ulMKode; }
    char *MerkmalsName (void) { return m_pMName; }

//  friend Funktionen
    friend void* GetMName (void *pObj);            // Get-Key-Funktion
	friend int CompareNames (void *pObj1, void *pObj2);
};

class TextMerkmalsListe;
//  Die Klasse verwaltet Merkmalsbeschreibungen.
class MerkmalsBaum : public CTree 
{
protected:
#ifdef WIN32
	void UserDelete (void *pObj);
#else
	void __export UserDelete (void *pObj);
#endif

public:
//  Konstruktor/Destruktor
    MerkmalsBaum (void);
    ~ MerkmalsBaum (void);      // Tabelleninhalt löschen

// 	weitere Member

// 	alle Merkmalskodes der PBD einlesen		
	Bool Init (void);				

// 	alle Merkmale des übergebenen Objekts ausgeben				
    Bool OutputMerkmale (long ObjNr, TextMerkmalsListe* MerkmalsListe);	

// 	neues Merkmal im Baum speichern	
	Bool AddMerkmal (char *pKurzText, ulong MKode);	

protected:
	// 	lese Merkmalskode aus dem Baum wenn nicht vorhanden, einen neuen von 
	// 	Trias holen und diesen in der PBD speichern
//	Bool GetMerkmalsKode (char *pMName, ulong &MKode); 
// KK990927
	Bool GetMerkmalsKode (char *pMName, ulong &MKode, long lONr); 
};
DeclareLock (MerkmalsBaum, Merkmal);

#endif // _MERKMAL_HPP
