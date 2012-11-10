// Klassendefinitionen fuer IDM-Baum ------------------------------------------
// File: IDKEY.HXX

#if !defined(_IDKEY_HXX)
#define _IDKEY_HXX

class IDM {
private:
	long _lIdent;
	short _iTyp;
	short _iRTyp;
	short _iModus;
	char *_pText;

public:
// Konstruktor/Destruktor
		IDM (long Ident, short Typ);
		~IDM (void);

// ZugriffsFunktionen für IDBaum
friend void _XTENSN_EXPORT *GetIdent (void *pObj);
friend int _XTENSN_EXPORT CmpIdents (void *pObj1, void *pObj2);

	long &Ident ( void ) { return _lIdent; };
	char *Text (void) { return _pText; };
	void SetText ( char *);
	void SetGiTyp ( short );
	void SetTyp ( short);
	void SetModus ( short);
	void SetTypZero ( void );
	short &Modus ( void ) { return _iModus; };
	short &GiTyp ( void ) { return _iTyp; };
	short &RefTyp ( void ) { return _iRTyp; };
};

class IDMTree : public CTree {
protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
// Konstruktor/Destruktor 
		IDMTree (void);
		~IDMTree (void);
};
DeclareLock (IDMTree, IDM);		// notwendige Klassendefinitionen

#endif // _IDKEY_HXX
