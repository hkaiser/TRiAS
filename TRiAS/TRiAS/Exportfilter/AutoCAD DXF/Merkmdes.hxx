/*
File: MERKMDES.HXX
realiert die Verwaltung eines Merkmal-Beschreibungs-Baumes.

erarbeitet : J. Benkenstein                 Stand vom 13. April 1994
*/

#ifndef _MERKMDES_HXX
#define _MERKMDES_HXX

//  Darstellungsattribut für Ausgabe in AutoCAD-Datei
    enum OutDescription { visible = 1, invisible = 2, present = 4, not_present = 8};

// Die Klasse ExtMerkmalDescription speichert die "Attribute" eines Merkmals
class ExtMerkmalDescription : public MerkmalDescription
{
private:
//  Attribute
    short _describe;            // Darstellungs-Flag

public:
//  Konstruktor/Destruktor
	ExtMerkmalDescription (MerkmalDescription &MD);
	~ ExtMerkmalDescription (void);

//  sonstige Member
	short Describe (void) { return _describe; }
	Bool isPresent (void) { return _describe & present; }
	Bool isVisible (void) { return _describe & visible; }
	Bool isInVisible (void) { return ! isVisible (); }

//  Friend-Funktionen
	friend int CompareMKodes (void *pObj1, void *pObj2);
	friend void* GetMKode (void *pObj);
};

// Die Klasse ExtMerkmalDescriptionTree verwaltet ExtMerkmalDescriptions
// in einem Baum.
class ExtMerkmalDescriptionTree : public CTree
{
protected:
    void /*XX EXPORTFLT*/ UserDelete (void *pObj);

public:
// Konstruktor/Destruktor
	ExtMerkmalDescriptionTree (void);       // Attribute init.
	~ ExtMerkmalDescriptionTree (void);     // Bauminhalt löschen

// sonstige Member
    Bool AddMerkmDescr (MerkmalDescription &MD); // neue Beschrbg. in Baum
    ErrCode OutputAttrDef (int FileHandle, MFELD *MF); // Attribut-Definitionen ausgeben
    ErrCode OutputAttrVal (int FileHandle, GSTRUCT &GS, MFELD *MF); // akt.
						// Attribut-Werte ausgeben
    ErrCode DeleteUnvalids (void); // alle nicht für den Export vorgesehenen
				  // Merkmalsbeschreibungen löschen

};

DeclareLock (ExtMerkmalDescriptionTree, ExtMerkmalDescription);

#endif // _MERKMDES_HXX
