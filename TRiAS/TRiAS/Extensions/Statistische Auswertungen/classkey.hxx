// Klassendefinitionen fuer IDM-Baum ------------------------------------------
// File: CLASSKEY.HXX

#if !defined(_CLASSKEY_HXX)
#define _CLASSKEY_HXX

class GICLA {
private: 
	long _lGroupNr;
	long _lEinheit;
	short _iGiTyp;
	long _lCount;
	long _lCountM;
	long _lOperate1;
	long _lOperate2;
	double _rVglWert1;
	double _rVglWert2;
	double _rKumul; 
	double _rKumulMin; 
	double _rKumulMax; 
	long _lYmin;
	long _lXmin;
	long _lYmax;
	long _lXmax;
	long _IDNr;
	long _MCode;
	class OBJTree *_pObjects;

public:
// Konstruktor/Destruktor
		GICLA (long Group, struct GICLASS *p );

		~GICLA (void);

// ZugriffsFunktionen für Baum
friend void _XTENSN_EXPORT *GetGroup (void *pGroup);
friend int _XTENSN_EXPORT CmpGroups (void *pGroup1, void *pGroup2);
                                             
    long &Group ( void ) { return _lGroupNr; }                                         
	long &Einheit ( void ) { return _lEinheit; };
	long &Operate1 ( void ) { return _lOperate1; };
	long &Operate2 ( void ) { return _lOperate2; };
	short &GiTyp ( void ) { return _iGiTyp; };
	long &Count ( void ) { return _lCount; };
	long &CountM ( void ) { return _lCountM; };
	double &Kumul ( void ) { return _rKumul; };
	double &KumulMin ( void ) { return _rKumulMin; };
	double &KumulMax ( void ) { return _rKumulMax; };
	double &VglWert1 ( void ) { return _rVglWert1; } ;
	double &VglWert2 ( void ) { return _rVglWert2; } ;
	long &Xmin ( void ) { return _lXmin; };
	long &Xmax ( void ) { return _lXmax; };
	long &Ymin ( void ) { return _lYmin; };
	long &Ymax ( void ) { return _lYmax; };
	long &IDNr ( void ) { return _IDNr; };
	long &MCode ( void ) { return _MCode; };
	OBJTree *pObjects ( void ) { return _pObjects;};
	void StoreObjTree ( OBJTree *pObj);

};

class GICLATree : public CTree {
protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
// Konstruktor/Destruktor 
		GICLATree (void);
		~GICLATree (void);
};
DeclareLock (GICLATree, GICLA);		// notwendige Klassendefinitionen

#endif // _CLASSKEY_HXX
