///////////////////////////////////////////////////////////////////////////
// @doc 
// @module objfeld.hxx | ArrayContainer von ObjektNummern

#if !defined(_OBJFELD_HXX__766329D5_0736_11D2_8657_00600875138A__INCLUDED_)
#define _OBJFELD_HXX__766329D5_0736_11D2_8657_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class ObjNummer 
{
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

class _TRIAS02_ENTRY ObjFeld : 
	public CListContainer 
{
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
	BOOL EXPORT02 Enumerate (BOOL (*)(long, BOOL, void *), void *);	// Enumerieren aller Objekte
	BOOL EXPORT02 DeleteObj (long lONr);
	BOOL ContainsObject (long lONr);

// Destruktor
		EXPORT02 ~ObjFeld (void);
};

// Definition der ObjNummerCreator und ObjNummerLock -Klassen
DeclareLock (ObjFeld, ObjNummer);

#endif // !defined(_OBJFELD_HXX__766329D5_0736_11D2_8657_00600875138A__INCLUDED_)
