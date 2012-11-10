// KlassenBaum -------------------------------------------------------------
// File: PolygisTree.HXX

#if !defined(_POLYGISTREE_HXX)
#define _POLYGISTREE_HXX

//////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////
//-------------------------Objekte --------------------------------
//-----------------------------------------------------------------
class TR_OBJ {				// TRiAS - Objekte
private:
	long _lIdent;
	char *_pKurzText;
	char *_pRefText;
	short _iTyp[7];
	short _iFirstTyp;
	
public:
// Konstruktor/Destruktor
		TR_OBJ (long lIdent, const char *pKurzText, short iTyp);

		~TR_OBJ (void);

// ZugriffsFunktionen für OBJBaum
friend void _XTENSN_EXPORT *GetObject (void *pObj);
friend int _XTENSN_EXPORT CmpObjects (void *pObj1, void *pObj2);

	long &Ident ( void ) { return _lIdent; };
	char *KurzText ( void ) { return _pKurzText; };
	void SetTyp( short iTyp); 
	char *GetLayerText(short iTyp);
};

class TR_OBJTree : public CTree {
protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
// Konstruktor/Destruktor 
		TR_OBJTree (void);
		~TR_OBJTree (void);
};
DeclareLock (TR_OBJTree, TR_OBJ);		// notwendige Klassendefinitionen

/////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
#endif // _POLYGISTREE_HXX
