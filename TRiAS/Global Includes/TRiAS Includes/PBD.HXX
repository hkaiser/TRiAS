// Klassendeklarationen für PBD_DB --------------------------------------------
// File: PBD.HXX

// PBD: %W%	%E%

#if !defined(_PBD_HXX)
#define _PBD_HXX

#include <idtdb.h>	// Für Dateinummern

const int TEXTLEN = 32;		// KurzTextlänge

enum PBDTyp {
	PBD_IDENT = 'i',	// PBD-Satztypen
	PBD_MERKMAL = 'm',
	PBD_MWERT = 'w',
	PBD_RELATION = 'r',
	PBD_SYMBOL = 's',
	PBD_VISUAL = 'u',
};

#if !defined(NOPBDDATA)
class PBD_DB;

class PBD_Data {
public:
// StatusWerte
	enum PBDStatus { 
		PBD_Unmodified, 
		PBD_Modified, 
		PBD_Deleted, 
		PBD_Invalid, 
	};

protected:
	long m_lCode;			// Identifikator
	char m_cbKurzText[TEXTLEN+1];	// KurzText
	char *m_pLangText;		// LangText
	long m_dbaSatz;			// SatzNr
	PBDTyp m_rgTyp;			// DatenTyp
	PBDStatus m_rgStatus;		// Status
	PBD_DB *m_pDB;			// zugehörige PBD-DatenBasis 
	unsigned short m_fTemp : 1;

public:
// Konstruktoren
	_TRIAS02_ENTRY PBD_Data (PBD_DB *pDB, PBDTyp Typ);
	_TRIAS02_ENTRY PBD_Data (PBD_DB *pDB, PBDTyp Typ, long Code, 
			  char * = NULL, BOOL = false);

// Memberfunktionen
_TRIAS02_ENTRY char *EXPORT02 GetLangText (void);

	long & GetCode (void) { return m_lCode; }
	char *GetKurzText (void) { return m_cbKurzText; }
	PBDTyp GetDataType (void) { return m_rgTyp; }
	PBDStatus & Status (void) { return m_rgStatus; }
	BOOL isTemp (void) { return m_fTemp; }
	long Addr (void) { return m_dbaSatz; }

_TRIAS02_ENTRY void SetKurzText (char *);
_TRIAS02_ENTRY char *SetLangText (char *);

	PBD_DB &PBD (void) { return *m_pDB; }
	
public:
// Destruktor
_TRIAS02_ENTRY virtual 	EXPORT02 ~PBD_Data (void);	// virtuell, da typinvalenter Baum
						// aufgebaut wird

_TRIAS02_ENTRY virtual ErrCode EXPORT02 SaveInPBD (void);
_TRIAS02_ENTRY virtual ErrCode EXPORT02 DeleteInPBD (void);

friend class PBDTempTree;
friend class PBD_DB;

friend void *PBD_DataKey (void *pObj);
friend int PBD_DataCmp (void *pObj1, void *pObj2);

friend class CPBDData;
friend class CPBDIdents;
friend class CPBDMCodes;
friend class CPBDRCodes;
};


#if !defined(NOPBDIDENT)
// Identifikatorinformation ---------------------------------------------------
class PBD_Ident : public PBD_Data {
public:
// Konstruktor
	_TRIAS02_ENTRY EXPORT02 PBD_Ident (PBD_DB *pDB);
	_TRIAS02_ENTRY EXPORT02 PBD_Ident (PBD_DB *pDB, long Code, char * = NULL, 
				    BOOL iTemp = false);
// Destruktor
	_TRIAS02_ENTRY EXPORT02 ~PBD_Ident (void);

_TRIAS02_ENTRY ErrCode EXPORT02 SaveInPBD (void);
_TRIAS02_ENTRY ErrCode EXPORT02 DeleteInPBD (void);
};
#endif // NOPBDIDENT

#if !defined(NOPBDMERKMAL)
// Merkmalsklassen ------------------------------------------------------------

#if !defined(PBDMERKMAL_SYSTEMFLAG)
#define PBDMERKMAL_SYSTEMFLAG	0x80		// Merkmal ist SystemMerkmal
#endif

class PBD_Merkmal : public PBD_Data {
private:
	short m_iMTyp;			// MerkmalsTyp
	unsigned short m_fSystem : 1;	// SystemMerkmal
	unsigned short m_fReadOnly : 1;	// ReadOnly-Merkmal

public:
// Konstruktor
	_TRIAS02_ENTRY EXPORT02 PBD_Merkmal (PBD_DB *);
	_TRIAS02_ENTRY EXPORT02 PBD_Merkmal (PBD_DB *, long Code, char * = NULL, 
				      BOOL iTemp = false);
// Memberfunktionen
virtual char *GetMerkmalsText (void) { return NULL; }
_TRIAS02_ENTRY char *GetMerkmalsWert (long WCode);	// liefert für Int-Aufzählungs-
						// typ den WerteText
_TRIAS02_ENTRY short EXPORT02 GetMLen (void);

	short isA (void) { return m_iMTyp; }
	BOOL isSystem (void) { return m_fSystem; }
	void SetSystem (BOOL fSystem) { m_fSystem = fSystem ? true : false; }

	BOOL isReadOnly (void) { return m_fReadOnly ? true : false; }
	void SetReadOnly (BOOL fReadOnly) { m_fReadOnly = fReadOnly ? true : false; }

_TRIAS02_ENTRY virtual short EXPORT02 MTyp (void);		// liefert Merkmalstyp

friend inline void *GetMCode (void *);		// liefert MerkmalsCode
friend inline int LongCmp (void *, void *);	// Vergleichsfunktion

// DatenBankArbeit
_TRIAS02_ENTRY virtual ErrCode EXPORT02 SaveInDB (long ON, short iTyp);	// Wert abspeichern
_TRIAS02_ENTRY virtual ErrCode EXPORT02 DeleteInDB (long ON, short iTyp);	// Merkmal löschen

_TRIAS02_ENTRY ErrCode EXPORT02 SaveInPBD (void);
_TRIAS02_ENTRY ErrCode EXPORT02 DeleteInPBD (void);

	void SetTyp (short newTyp) { m_iMTyp = newTyp; }

// Destruktor
		~PBD_Merkmal (void) {}
};

// Liefert adresse des MerkmalsCodes
inline void *GetMCode (void *pObj) 
{
	return & (((PBD_Merkmal *)pObj) -> GetCode());
}

#endif // NOPBDMERKMAL

#if !defined(NOPBDRELATION)
class PBD_Relation : public PBD_Data {
private:
	short m_iRelTyp;

public:
// Konstruktor
	_TRIAS02_ENTRY 	EXPORT02 PBD_Relation (PBD_DB *pDB);
	_TRIAS02_ENTRY EXPORT02 PBD_Relation (PBD_DB *pDB, long Code, char * = NULL, 
				       BOOL iTemp = false);
// Member/Friends
friend inline int LongCmp (void *, void *);	// Vergleichsfunktion

_TRIAS02_ENTRY ErrCode EXPORT02 SaveInPBD (void);
_TRIAS02_ENTRY ErrCode EXPORT02 DeleteInPBD (void);

	short FRTyp (void) { return m_iRelTyp; }
	void SetTyp (short newT) { m_iRelTyp = newT; }

// Destruktor
		~PBD_Relation (void) {}
};
#endif // NOPBDRELATION

#if !defined(LONGCOMP)
#define LONGCOMP
// Funktionen für ObjektListe : Tree (Zugriffs- und Vergleichsfunktionen) -----
inline int LongCmp (void *Key1, void *Key2) 
{
long Par1 = *(INT_PTR *)Key1, Par2 = *(INT_PTR *)Key2;

	if (Par1 > Par2) 	return 1;
	else if (Par1 < Par2) 	return -1;
	else 			return 0;
}
#endif // LONGCOMP

#endif // NOPBDDATA

#endif  // _PBD_HXX
