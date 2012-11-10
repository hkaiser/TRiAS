// Klassendeklaration der typspezifischen TreeKlasse --------------------------
// Generiert aus TTREE.CTT

#if !defined(_VISERROR_HXX)
#define _VISERROR_HXX

// SchlüsselKlasse ------------------------------------------------------------
class CVisError {
public:
	long m_lIdent;	// Identifikator
	short m_iVTyp;	// Visualisierungstyp
	char *m_pView;	// SichtName
	
	void SetViewName (char *pView)
	{
		if (pView == NULL) {
			m_pView = NULL;
			return;
		}
		m_pView = new char [strlen (pView) +1];
		if (m_pView) strcpy (m_pView, pView);
	}


// Konstruktoren
		CVisError (long lIdent, short iVTyp, char *pView = NULL)
			: m_lIdent (lIdent), m_iVTyp (iVTyp) 
		{
			SetViewName (pView);
		}
		~CVisError (void)
		{
			if (m_pView) delete m_pView;
		}
};

// Klasse, die im Baum hängen soll --------------------------------------------
class CVisErrorItem {
public:
	CVisError m_Key;				// Suchschlüssel

	inline CVisErrorItem (long lIdent, short iVTyp, char *pView = NULL);
	inline ~CVisErrorItem (void);

// Funktionen zur SuchSchlüsselVerwaltung
inline	CVisError & FGetVisError (void);			// liefert SuchSchlüssel

friend inline int FCmpVisError (CVisError &, CVisError &);	// vergleicht 2 Schlüssel
};


// Eigentliche typspezifische TreeKlasse --------------------------------------

// Funktionstypen, die Schlüsselverwaltung realisieren ------------------------
typedef void * (* TTREEGETKEYFCN) (void *);
typedef int (* TTREECMPKEYFCN)(void *, void *);
  
typedef bool (* VisErrorItemEnumFunc)(CVisErrorItem &, void *);

  
class _TRIAS02_ENTRY CIgnoreVisErrorTree :		
	public CTree 
{
protected:
	void UserDelete (void *pObj);

public:
// Konstruktor/Destruktor
		CIgnoreVisErrorTree (void);
		~CIgnoreVisErrorTree (void);

// Elementarfunktionen
	BOOL FAddItem (long lIdent, short iVTyp, char *pView = NULL);	// Element hinzufügen
	BOOL FDeleteItem (CVisError &);			// Element löschen
// Element liefern
	CVisErrorItem *FFindItem (long lIdent, short iVTyp, char *pView = NULL);

	BOOL FReInsert (CVisError &oldKey, CVisError &newKey);

// EnumerationsFunktionen
	BOOL FEnumAllItems (VisErrorItemEnumFunc pFcn, void *pEData = NULL);
	BOOL FEnumItems (CVisError &rKey, VisErrorItemEnumFunc pFcn, void *pEData = NULL);

// SuchSchlüsselVerwaltung
friend CVisError *FTTreeGetVisError (CVisErrorItem *pObj);
friend int FTTreeCmpVisError (CVisError *pObj1, CVisError *pObj2);
};

// KlassenDeklarationen/Definitionen für TypLock und TypCreator
DeclareLock (CIgnoreVisErrorTree, CVisErrorItem);

#include <viserror.inl>		// zugehörige Inline-Funktionen 

#endif // _VISERROR_HXX

