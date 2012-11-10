// Klassendeklaration der typspezifischen TreeKlasse --------------------------
// Generiert aus CTTREE.CTT
// File UIDOBJ.HXX

#if !defined(_UIDOBJ_HXX)
#define _UIDOBJ_HXX

#include <copttree.hxx>

// Schlüsseltyp ---------------------------------------------------------------
typedef char * LPUIDENT;	// Unique Ident eines Objektes

// Klasse, die im Baum hängen soll --------------------------------------------
class CObjUIdent {
private:
	LPUIDENT m_Key;			// Suchschlüssel (UIdent)
	ULONG m_lONr;			// ObjektNummer
	short m_iOType;			// ObjektTyp

public:
		CObjUIdent (LPUIDENT pUIDent, ULONG lONr, short iOType);
		~CObjUIdent (void);

inline short &OTyp (void) const { return (short &)m_iOType; }
inline ULONG &ObjNr (void) const { return (ULONG &)m_lONr; }

// Funktionen zur SuchSchlüsselVerwaltung
	LPUIDENT & FGetLPUIDENT (void);		// liefert SuchSchlüssel
friend int FCmpLPUIDENT (LPUIDENT &, LPUIDENT &);	// vergleicht 2 Schlüssel
};


// Eigentliche typspezifische TreeKlasse --------------------------------------

// Funktionstypen, die Schlüsselverwaltung realisieren ------------------------
typedef void * (* CTTREEGETKEYFCN) (void *);
typedef int (* CTTREECMPKEYFCN)(void *, void *);
  
typedef bool (* CObjUIdentEnumFunc)(CObjUIdent &, void *);

  
class CUIdentObjects : 
	public COptTree 
{
private:
	CTable *m_pActItem;		// für FindFirst/FindNext
	unsigned int m_fFilled : 1;	// Baum wurde gefüllt
	
protected:
	void UserDelete (void *pObj);

public:
// Konstruktor/Destruktor
		CUIdentObjects (void);
		~CUIdentObjects (void);

// Elementarfunktionen
	bool FAddItem (LPUIDENT pUIDent, ULONG lONr, short iOType);	// Element hinzufügen
	bool FDeleteItem (LPUIDENT &);		// Element löschen
	CObjUIdent *FFindItem (LPUIDENT &);	// Element liefern
	
	CObjUIdent *FFindFirstItem (LPUIDENT &);
	CObjUIdent *FFindNextItem (LPUIDENT &);

	bool FillTree (ULONG lMCode);			// Baum füllen

inline 	bool isFilled (void) const { return m_fFilled ? true : false; }

// SuchSchlüsselVerwaltung
friend LPUIDENT *FCTTreeGetLPUIDENT (CObjUIdent *pObj);
friend int FCTTreeCmpLPUIDENT (LPUIDENT *pObj1, LPUIDENT *pObj2);

friend bool FillTree (HPROJECT hPr, CUIdentObjects *pThis);
};

// KlassenDeklarationen/Definitionen für TypLock und TypCreator
DeclareOptLock (CUIdentObjects, CObjUIdent);

#endif // _UIDOBJ_HXX

