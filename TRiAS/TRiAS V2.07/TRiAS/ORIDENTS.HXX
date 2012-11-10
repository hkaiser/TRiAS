// Klassendeklaration der typspezifischen TreeKlasse --------------------------
// Generiert aus CTTREE.CTT
// File: ORIDENTS.HXX

#if !defined(_ORIDENTS_HXX)
#define _ORIDENTS_HXX

// Klasse, die im Baum h‰ngen soll --------------------------------------------
typedef unsigned long ULONG;
 
class CORIdent {
private:
	ULONG m_Key;				// Suchschl¸ssel
	short m_iOTypes;				// ObjektTypen

public:
		CORIdent (ULONG ulKey, short iOType = 0);
		~CORIdent (void) {}

// Funktionen zur SuchSchl¸sselVerwaltung
	ULONG & FGetULONG (void);		// liefert SuchSchl¸ssel
	short FGetOTypes (void);
	short FMergeOTypes (short iOType);	// fÅgt OTyp hinzu
	
friend int FCmpULONG (ULONG &, ULONG &);	// vergleicht 2 Schl¸ssel
};


// Eigentliche typspezifische TreeKlasse --------------------------------------

// Funktionstypen, die Schl¸sselverwaltung realisieren ------------------------
typedef void * (* CTTREEGETKEYFCN) (void *);
typedef int (* CTTREECMPKEYFCN)(void *, void *);
  
  
class CORIdents : public CTree {
protected:
	void UserDelete (void *pObj);

public:
// Konstruktor/Destruktor
		CORIdents (void);
		~CORIdents (void);

// Elementarfunktionen
	Bool FAddItem (ULONG &, short iOType = 0);	// Element hinzuf¸gen
	CORIdent *FFindItem (ULONG &);			// Element liefern

// SuchSchl¸sselVerwaltung
friend ULONG *FCTTreeGetULONG (CORIdent *pObj);
friend int FCTTreeCmpULONG (ULONG *pObj1, ULONG *pObj2);
};

// KlassenDeklarationen/Definitionen f¸r TypLock und TypCreator
DeclareLock (CORIdents, CORIdent);

#endif // _ORIDENTS_HXX

