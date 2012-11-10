// ArrayContainer von ObjektNummern ------------------------------------------
// File: OBJFELD.HXX

#if !defined(_OBJFELD_HXX)
#define _OBJFELD_HXX

#ifndef _TRIAS02_ENTRY
#define _TRIAS02_ENTRY
#endif
#ifndef EXPORT02
#define EXPORT02
#endif

class ObjNummer {
public:
// Member
	long _ON;       // Objektnummer
// Konstruktor
		ObjNummer (long ON) { _ON = ON; }
// Destruktor (muß explizit gegebensein da von UserDelete benötigt)
		~ObjNummer (void) {}
};


// Array von ObjNummern oder ObjRigInfo's
class ObjNummerCreator;		// nur deklarieren
class ObjContainer;

enum ObjFeldTyp { 
	OFTUnknown = 0, 
	OFTObjFeld = 0x01, 
	OFTObjIdFeld = 0x02, 
	OFTDBaseObjFeld = 0x04, 
	OFTObjRelFeld = 0x08,
};

class _TRIAS02_ENTRY ObjFeld : public CListContainer {
protected:
	void UserDelete (void *pItem);

public:
// Konstruktor
		EXPORT02 ObjFeld (void);

// Member
virtual	ObjNummer * EXPORT02 NewObj (ObjNummerCreator &ONC, long ON);
		// anlegen eines neuen Listenelementes
virtual ObjFeldTyp isA (void);

	ObjContainer EXPORT02 CalcCont (void);	// GesamtContainer berechnen
	bool EXPORT02 Enumerate (BOOL (*)(long, BOOL, void *), void *);	// Enumerieren aller Objekte
	bool EXPORT02 DeleteObj (long lONr);

// Destruktor
		EXPORT02 ~ObjFeld (void);
};

// Definition der ObjNummerCreator und ObjNummerLock -Klassen
DeclareLock (ObjFeld, ObjNummer);

#endif // _OBJFELD_HXX
