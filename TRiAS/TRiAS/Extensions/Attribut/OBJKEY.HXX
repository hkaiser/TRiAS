// Klassendefinitionen fuer IDM-Baum ------------------------------------------
// File: OBJKEY.HXX

#if !defined(_OBJKEY_HXX)
#define _OBJKEY_HXX

class OBJ {
private: 
	long _lObject;
	long _lIdent;
	long _lMCode;
	long _lPartner;
	short _iObjGiTyp;
	short _iFlag;

public:
// Konstruktor/Destruktor
		OBJ (long Object, struct OBJECTTYP *p );

		~OBJ (void);

// ZugriffsFunktionen für Baum
friend void _XTENSN_EXPORT *GetObject (void *pObj);
friend int _XTENSN_EXPORT CmpObjects (void *pObj1, void *pObj2);
                                             
    long &Object ( void ) { return _lObject; }                                         
	long &Ident ( void ) { return _lIdent; };
	long &MCode ( void ) { return _lMCode; };
	short &ObjectTyp ( void ) { return _iObjGiTyp; };
	short ObjFlag (void) { return _iFlag; };
	long &Partner (void) { return _lPartner; };
	void SetFlag ( void);
	void SetPartner ( long);

};

class OBJTree : public CTree {
protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
// Konstruktor/Destruktor 
		OBJTree (void);
		~OBJTree (void);
};
DeclareLock (OBJTree, OBJ);		// notwendige Klassendefinitionen

#endif // _OBJKEY_HXX
