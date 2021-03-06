// Klassendeklaration der typspezifischen TreeKlasse --------------------------
// Generiert aus CTTREE.CTT
// File: PBDIDS.HXX

#if !defined(_PBDIDS_HXX)
#define _PBDIDS_HXX

// Eigentliche typspezifische TreeKlasse --------------------------------------
// Funktionstypen, die Schlüsselverwaltung realisieren ------------------------
typedef void * (* CTTREEGETKEYFCN) (void *);
typedef int (* CTTREECMPKEYFCN)(void *, void *);
  
typedef bool (* PBD_DataEnumFunc)(long, bool, void *);

typedef unsigned long ULONG;
  
class CPBDData : public CTree {
private:
	unsigned short m_fIterated : 1;		// Codes vollständig

protected:
	PBDTyp m_rgTyp;
	void UserDelete (void *pObj);

public:
// Konstruktor/Destruktor
		CPBDData (void);
		~CPBDData (void);
		
// Elementarfunktionen
virtual bool FAddItem (PBD_Data *pNewData) = 0;	// Element hinzufügen
virtual bool FAddItem (PBD_DB *pDB, ULONG ulKey) = 0;	// Element hinzufügen
virtual bool FillFromTree (PBD_Data *);		// Element lesen
	
	bool AddToTree (PBD_Data *);		// Element hinzufügen, wenn nicht da
	bool AddToTree (PBD_DB *pDB, ULONG ulKey);

	bool FDeleteItem (ULONG &);		// Element löschen
	PBD_Data *FFindItem (ULONG &);		// Element liefern

	bool FReInsert (ULONG &oldKey, ULONG &newKey);

// EnumerationsFunktionen
	bool FEnumAllItems (PBD_DataEnumFunc pFcn, void *pEData = NULL);
	bool FEnumItems (ULONG &rKey, PBD_DataEnumFunc pFcn, void *pEData = NULL);

	bool fEnumerated (void) { return m_fIterated ? true : false; }
	void fEnumerated (bool fFlag) { m_fIterated = fFlag ? true : false; }

// Update-Funktion
	bool RefreshEntry (const PBD_Data *pData);

// SuchSchlüsselVerwaltung
friend ULONG *FCTTreeGetULONG (PBD_Data *pObj);
friend int FCTTreeCmpULONG (ULONG *pObj1, ULONG *pObj2);
};

// KlassenDeklarationen/Definitionen für TypLock und TypCreator
DeclareLock (CPBDData, PBD_Data);

class CPBDIdents : public CPBDData {
public:
		CPBDIdents (void) : CPBDData () { m_rgTyp = PBD_IDENT; }

	bool FAddItem (PBD_Data *pNewData);	// Element hinzufügen
	bool FAddItem (PBD_DB *pDB, ULONG ulKey);	// Element hinzufügen
};


class CPBDMCodes : public CPBDData {
public:
		CPBDMCodes (void) : CPBDData () { m_rgTyp = PBD_MERKMAL; }

	bool FAddItem (PBD_Data *pNewData);	// Element hinzufügen
	bool FAddItem (PBD_DB *pDB, ULONG ulKey);	// Element hinzufügen
};


class CPBDRCodes : public CPBDData {
public:
		CPBDRCodes (void) : CPBDData () { m_rgTyp = PBD_RELATION; }

	bool FAddItem (PBD_Data *pNewData);	// Element hinzufügen
	bool FAddItem (PBD_DB *pDB, ULONG ulKey);	// Element hinzufügen
};


#endif // _CTTREE_HXX

