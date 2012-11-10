// Klassendefinitionen fuer IDM-Baum ------------------------------------------
// File: IDKEY.HXX

#if !defined(_IDKEY_HXX)
#define _IDKEY_HXX
class OBJTree;

class IDM {
private:
	long _lIdent;
	long _lMCode;
//---------Counter----------------
	long _lCount;
	long _lPunkt;
	long _lLinie;
	long _lFlaeche;
	long _lText;
	long _lKomplex;
	long _lSonstige;
	short _iIdGiTyp;
//---------Container--------------
	long _lLoHoch;
	long _lLoRechts;
	long _lRuHoch;
	long _lRuRechts;
//----------Parameter-------------
	double _rFlInhalt;
	double _rAreaMax;
	double _rAreaMin;
	double _rAreaMedian;
	double _rAreaMittel;
	double _rLinLaenge;
	double _rPolyLenMax;
	double _rPolyLenMin;
	double _rPolyLenMedian;
	double _rPolyLenMittel; 
	class OBJTree *_pObjects;
public:
// Konstruktor/Destruktor
		IDM (long Ident, struct IDGITYP *p );

		~IDM (void);

// ZugriffsFunktionen für IDBaum
friend void _XTENSN_EXPORT *GetIdent (void *pObj);
friend int _XTENSN_EXPORT CmpIdents (void *pObj1, void *pObj2);

	long &Ident ( void ) { return _lIdent; };
	long &MCode ( void ) { return _lMCode; };
	long &LoHoch ( void ) { return _lLoHoch; };
	long &RuHoch ( void ) { return _lRuHoch; };
	long &LoRechts ( void ) { return _lLoRechts; };
	long &RuRechts ( void ) { return _lRuRechts; };
	long &Count ( void ) { return _lCount; } ;
	long &Punkt ( void ) { return _lPunkt; } ;
	long &Linie ( void ) { return _lLinie; } ;
	long &Flaeche ( void ) { return _lFlaeche; } ;
	long &Text ( void ) { return _lText; } ;
	short &IdentGiTyp ( void ) { return _iIdGiTyp; };
	long &Sonstige ( void ) { return _lSonstige; } ;
	double &FlInhalt ( void ) { return _rFlInhalt; } ;
	double &rAreaMin ( void ) { return _rAreaMin; };
	double &rAreaMax ( void ) { return _rAreaMax; };
	double &rAreaMedian ( void ) { return _rAreaMedian; };
	double &rAreaMittel ( void ) { return _rAreaMittel; };

	double &LinLaenge ( void ) { return _rLinLaenge; } ;
	double &rPolyLenMin ( void ) { return _rPolyLenMin; };
	double &rPolyLenMax ( void ) { return _rPolyLenMax; }; 
	double &rPolyLenMedian ( void ) { return _rPolyLenMedian; }; 
	double &rPolyLenMittel ( void ) { return _rPolyLenMittel; }; 

	OBJTree *pObjects ( void ) { return _pObjects;};
	void StoreObjTree ( OBJTree *pObj);
	void DeleteObjTree ( void);
	void StoreObjParam ( struct IDGITYP *p);

	void SetFlaechenParam ( struct IDGITYP *p);
	void SetLinienParam ( struct IDGITYP *p);
	void StoreMCode ( long);

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

//-------------------ListContainer------------------------------------------

//  class für ObjClass-ListContainer
class OBJCL {
private:
//  Attribute
	long _OCLIdent;
	short _OCLBezugsTyp;
	short _OCLTyp;
	char _OCLLine[128];
public:

//  Konstruktor/Destruktor
	OBJCL ( short Typ, long lIdent,char * pLine);
	~OBJCL (void);

//	Member
	short &OBJCLBezugsTyp ( void ) { return _OCLBezugsTyp; };
	long &OBJCLIdent ( void ) { return _OCLIdent; };
	char &OBJCLLine ( void ) { return _OCLLine[0]; };
	short &OBJCLTyp ( void ) { return _OCLTyp; };
};

//  Verwaltung einer ObjClass-Liste
class OBJCLList : public CListContainer {

protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
//  Konstruktor/Destruktor
	OBJCLList (void);
	~ OBJCLList (void);
};

DeclareLock (OBJCLList, OBJCL);



#endif // _IDKEY_HXX
