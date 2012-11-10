// Klassendefinitionen fuer Objekt-Baum ------------------------------------------
// File: COBJTREE.HXX

#if !defined(_COBJTREE_HXX)
#define _COBJTREE_HXX

//-------------------------Objekte --------------------------------
//-----------------------------------------------------------------
class CTop_Obj {				// TRiAS - Objekte
private:
	long _lPObject;
	long *_plSObject;
	long _lPLaenge;
	long _lSLaenge;
	long _lPFlaeche;
	long _lSFlaeche;
	short _iGiTyp;
	Relat _rRelTyp;
	
public:
// Konstruktor/Destruktor
		CTop_Obj (long Object, short iTyp);

		~CTop_Obj (void);

// ZugriffsFunktionen für OBJBaum
friend void _XTENSN_EXPORT *GetCObj (void *pObj);
friend int _XTENSN_EXPORT CmpCObjs (void *pObj1, void *pObj2);

	long &PObject ( void ) { return _lPObject; };
	long *SObject ( void ) { return _plSObject; };
	long &PLaenge ( void ) { return _lPLaenge; };
	long &SLaenge ( void ) { return _lSLaenge; };
	long &PFlaeche ( void ) { return _lPFlaeche; };
	long &SFlaeche ( void ) { return _lSFlaeche; };
	Relat RelTyp ( void ) { return _rRelTyp; };
	short GiTyp ( void) { return _iGiTyp; };
	void SetSObject ( long *);
	void SetPLaenge ( long );
	void SetSLaenge ( long );
	void SetPFlaeche ( long );
	void SetSFlaeche ( long );
	void SetRelTyp ( Relat);
	void SetGiTyp ( short);
};

class CTop_ObjTree : public CTree {
protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
// Konstruktor/Destruktor 
		CTop_ObjTree (void);
		~CTop_ObjTree (void);
};
DeclareLock (CTop_ObjTree, CTop_Obj);		// notwendige Klassendefinitionen

//--------------------------------------------------------------------------
#endif // _COBJTREE_HXX
