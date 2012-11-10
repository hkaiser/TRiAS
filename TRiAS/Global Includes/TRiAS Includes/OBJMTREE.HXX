// Klassendeklaration der typspezifischen TreeKlasse --------------------------
// Generiert aus CTTREE.CTT, File: OBJMTREE.HXX

#if !defined(_OBJMTREE_HXX)
#define _OBJMTREE_HXX

// SchlüsselTyp ---------------------------------------------------------------
typedef long MCODE;	// schlicht und ergreifend

// Klasse, die im Baum hängen soll --------------------------------------------
class CFeature {
private:
	MCODE m_Key;			// MerkmalsCode
	char *m_pFText;			// MerkmalsText
public:
		CFeature (long lMCode, char *pMText);
		~CFeature (void);

	char *& FText (void) { return m_pFText; }
	
// Funktionen zur SuchSchlüsselVerwaltung
	MCODE & FGetMCODE (void);		// liefert SuchSchlüssel

friend int FCmpMCODE (MCODE &, MCODE &);	// vergleicht 2 Schlüssel
};


// Eigentliche typspezifische TreeKlasse --------------------------------------

// Funktionstypen, die Schlüsselverwaltung realisieren ------------------------
typedef void * (* CTTREEGETKEYFCN) (void *);
typedef int (* CTTREECMPKEYFCN)(void *, void *);
  
typedef Bool (* CFeatureEnumFunc)(CFeature &, void *);

  
class CFeatureTree : public CTree {
protected:
	void UserDelete (void *pObj);

public:
// Konstruktor/Destruktor
		CFeatureTree (void);
		~CFeatureTree (void);

// Elementarfunktionen
	Bool FAddItem (long lMCode, char *pMWert);	// Element hinzufügen
	Bool FDeleteItem (MCODE &);			// Element löschen
	CFeature *FFindItem (MCODE &);	// Element liefern

	Bool FReInsert (MCODE &oldKey, MCODE &newKey);

// EnumerationsFunktionen
	Bool FEnumAllItems (CFeatureEnumFunc pFcn, void *pEData = NULL);
	Bool FEnumItems (MCODE &rKey, CFeatureEnumFunc pFcn, void *pEData = NULL);

// SuchSchlüsselVerwaltung
friend MCODE *FCTTreeGetMCODE (CFeature *pObj);
friend int FCTTreeCmpMCODE (MCODE *pObj1, MCODE *pObj2);
};

// KlassenDeklarationen/Definitionen für TypLock und TypCreator
DeclareLock (CFeatureTree, CFeature);

#endif // _OBJMTREE_HXX

