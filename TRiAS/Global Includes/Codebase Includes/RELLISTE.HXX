// DatenStrukturen fuer RelationsRecherche
// File: RELLISTE.HXX


#if !defined(_RELLISTE_HXX)
#define _RELLISTE_HXX

class ObjRelNummer : public ObjNummer {
private:
	long _RelCode;		// RelationsCode
	short _RelTyp;		// RelationsTyp

public:
// Konstruktor/Destruktor
		ObjRelNummer (long ONr);
		~ObjRelNummer (void);

	long &RelCode (void) { return _RelCode; }
	short &RelTyp (void) { return _RelTyp; }
};

class _TRIAS02_ENTRY ObjRelFeld : public ObjFeld {
protected:
	void UserDelete (void *pObj);

public:
// Konstruktor/Destruktor
		ObjRelFeld (void);
		~ObjRelFeld (void);

	ObjNummer *NewObj (ObjNummerCreator &ONC, long ON);
	ObjFeldTyp isA (void);
};
DeclareLock (ObjRelFeld, ObjRelNummer);

#endif // _RELLISTE_HXX

