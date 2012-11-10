// Klassendefinitionen für Objektmerkmale -------------------------------------
// File: MERKMAL.HXX

#if !defined(_MERKMAL_HXX)
#define _MERKMAL_HXX

#if defined(_USE_LEGACY_CODE)

const int MERKMALSINFO = 200;	// Größe eines Merkmalsfeldes

#if !defined(NOTEXTMERKMAL)

// Ein GeoDB-Objekt kann mehrere verschiedene Einzel-Merkmale besitzen --------
class TextMerkmal : public PBD_Merkmal {
private:
	char *_Text;		// Merkmalstext

public:
// Konstruktor
	_TRIAS02_ENTRY EXPORT02 TextMerkmal (PBD_DB *pDB, long Code, char *MText = NULL);
	_TRIAS02_ENTRY EXPORT02 TextMerkmal (TextMerkmal &);
		
// Memberfunktionen
_TRIAS02_ENTRY TextMerkmal &operator= (TextMerkmal &TM);
_TRIAS02_ENTRY char *EXPORT02 GetMerkmalsText (void);
_TRIAS02_ENTRY BOOL EXPORT02 hasTextMerkmal (void);
	
_TRIAS02_ENTRY ErrCode EXPORT02 SaveInDB (long lTarget, short iTyp);	// Datenbankarbeit
_TRIAS02_ENTRY ErrCode EXPORT02 DeleteInDB (long lTarget, short iTyp);

_TRIAS02_ENTRY short EXPORT02 MTyp (void);	// MerkmalsTyp

// Destruktor
	_TRIAS02_ENTRY EXPORT02 ~TextMerkmal (void);

// friend Funktionen
friend class MerkmalsListe;
};

#endif // NOTEXTMERKMAL


#if !defined(NOINTMERKMAL)
class IntMerkmal : public PBD_Merkmal {
private:
	long _IntWert;		// Merkmalswert
	char *_IntText;		// optional für Int-Aufzählungstyp

public:
// Konstruktor
		IntMerkmal (PBD_DB *pDB, long Code, long MInt = 0) 
			: PBD_Merkmal (pDB, Code) 
			{ _IntWert = MInt; _IntText = NULL; }

// Memberfunktionen
_TRIAS02_ENTRY IntMerkmal &operator= (IntMerkmal &);
	long GetMerkmalsInt (void) { return _IntWert; }
_TRIAS02_ENTRY char *GetMerkmalsText (void);

_TRIAS02_ENTRY short MTyp (void);	// MerkmalsTyp

// Destruktor
	_TRIAS02_ENTRY ~IntMerkmal (void);

// friends
friend class MerkmalsListe;
};
#endif // NOINTMERKMAL

#if defined(NOFLOATMERKMAL)
class FloatMerkmal : public PBD_Merkmal {
private:
	float _FloatWert;	// Merkmalswert

public:
// Konstruktor
		FloatMerkmal (PBD_DB *pDB, long Code, float MFloat)
			: PBD_Merkmal (pDB, Code) 
			{ _FloatWert = MFloat; }

// Memberfunktionen
	float GetMerkmalsFloat (void) { return _FloatWert; }
_TRIAS02_ENTRY char *GetMerkmalsText (void);

// Destruktor
		~FloatMerkmal (void) {}

// friends
friend class MerkmalsListe;	
};
#endif // NOFLOATMERKMAL

#if !defined(NODOUBLEMERKMAL)
class DoubleMerkmal : public PBD_Merkmal {
private:
	double _DoubleWert;	// Merkmalswert

public:
// Konstruktor
		DoubleMerkmal (PBD_DB *pDB, long Code, double MDouble = 0.0)
			: PBD_Merkmal (pDB, Code) 
			{ _DoubleWert = MDouble; }

// Memberfunktionen
	double GetMerkmalsDouble (void) { return _DoubleWert; }

_TRIAS02_ENTRY char *GetMerkmalsText (void);
_TRIAS02_ENTRY short MTyp (void);		// MerkmalsTyp

// Destruktor
		~DoubleMerkmal (void) {}

// friends
friend class MerkmalsListe;
};
#endif // NODOUBLEMERKMAL

#if !defined(NOMKLISTE)
// Liste aller Merkmale eines Objektes ----------------------------------------
class MerkmalsListe : public CTree {
private:
_TRIAS02_ENTRY void EXPORT02 UserDelete (void *);	// löschen eines Merkmals
	short m_iTyp;				// Typ der MListe ('a', 'b' oder 'c')
	unsigned short m_fSystem : 1;		// SystemMerkmale mitnehmen
	unsigned short m_fAllFeatures : 1;	// unabhängig vom Typ sammeln

_TRIAS02_ENTRY void FillList (GeoDB *pDB, PBD_DB *pPBD, long lSatzNr, short iTyp);

public:
// Konstruktor
	_TRIAS02_ENTRY EXPORT02 MerkmalsListe (GeoDB *pDB, PBD_DB *pPBD, long lTarget, short iTyp, BOOL fSystem = true, BOOL fAll = false);
	_TRIAS02_ENTRY EXPORT02 MerkmalsListe (GeoDB *pDB, PBD_DB *pPBD, char *pSicht, BOOL fSystem = true, BOOL fAll = false);
	_TRIAS02_ENTRY EXPORT02 MerkmalsListe (BOOL fSystem = true, BOOL fAll = false);	// leere Liste

// Memberfunktionen
_TRIAS02_ENTRY char *EXPORT02 GetMerkmalsText (long);
_TRIAS02_ENTRY long EXPORT02 EnumMerkmale (BOOL (*)(long, BOOL, void *), void *);
_TRIAS02_ENTRY long EXPORT02 EnumMerkmaleEx (BOOL (*)(long, DWORD, void *), void *);

	BOOL isSystem (void) { return m_fSystem; }
	
// Destruktor
	~MerkmalsListe (void) { EveryDelete (); }
};

DeclareLock (MerkmalsListe, PBD_Merkmal);

#endif // NOMKLISTE
#endif // defined(_USE_LEGACY_CODE)

#endif // _MERKMAL_HXX
