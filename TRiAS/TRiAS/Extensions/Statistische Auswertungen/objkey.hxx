// Klassendefinitionen fuer IDM-Baum ------------------------------------------
// File: OBJKEY.HXX

#if !defined(_OBJKEY_HXX)
#define _OBJKEY_HXX

class OBJ {
private: 
	long _lObject;
	long _lIdent;
	long _lMCode;
	long _lIntervall;
	short _iObjGiTyp;
	long _lLoHoch;
	long _lLoRechts;
	long _lRuHoch;
	long _lRuRechts;
	double _rFlInhalt;
	double _rLinLaenge; 

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
	long &Intervall ( void ) { return _lIntervall; };
	long &LoHoch ( void ) { return _lLoHoch; };
	long &RuHoch ( void ) { return _lRuHoch; };
	long &LoRechts ( void ) { return _lLoRechts; };
	long &RuRechts ( void ) { return _lRuRechts; };
	short &ObjectTyp ( void ) { return _iObjGiTyp; };
	double &FlInhalt ( void ) { return _rFlInhalt; } ;
	double &LinLaenge ( void ) { return _rLinLaenge; } ;

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
