// Klassendefinitionen fuer CLS-Baum ------------------------------------------
// File: CLSTREE.HXX

#if !defined(_CLSTREE_HXX)
#define _CLSTREE_HXX

class CLS {
private:
	char *_pMerkmal;
	long _lIdent;
	char *_pKurzText;

public:
// Konstruktor/Destruktor
		CLS (char *pMerkmal, long Ident, char *pKurzText);
		~CLS (void);

// ZugriffsFunktionen für IDBaum
friend void _XTENSN_EXPORT *GetClass (void *pObj);
friend int _XTENSN_EXPORT CmpClasses (void *pObj1, void *pObj2);

	char *Merkmal (void) { return _pMerkmal; };
	long &Ident (void ) { return _lIdent; };
	char *KurzText (void) { return _pKurzText; };
};

class CLSTree : public CTree {
protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
// Konstruktor/Destruktor 
		CLSTree (void);
		~CLSTree (void);
};
DeclareLock (CLSTree, CLS);		// notwendige Klassendefinitionen

//------------------------------------------------------------------

class VClass {
private:
	char *_pMerkmal;
	OBJTree *_pObj;

public:
// Konstruktor/Destruktor
		VClass (char *pMerkmal);
		~VClass (void);

// ZugriffsFunktionen für IDBaum
friend void _XTENSN_EXPORT *GetVClass (void *pObj);
friend int _XTENSN_EXPORT CmpVClasses (void *pObj1, void *pObj2);

	char *Merkmal (void) { return _pMerkmal; };
	OBJTree *Obj (void ) { return _pObj; };
	void StoreObjTree ( OBJTree *pObj);
};

class VClassTree : public CTree {
protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
// Konstruktor/Destruktor 
		VClassTree (void);
		~VClassTree (void);
};
DeclareLock (VClassTree, VClass);		// notwendige Klassendefinitionen

//------------------------------------------------------------------

#endif // _CLSTREE_HXX
