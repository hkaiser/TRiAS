// Headerdatei für HeaderEntry - Klasse
// File: HDENTRY.HXX

#if !defined(_HDENTRY_HXX)
#define _HDENTRY_HXX

const short HDRKEYLENGTH = 16;	// Länge eines Headerkey's
const char ModifiedChar = '*';	// ModifiedFlag für Headereintrag

// Erste Codes, die fortlaufend vergeben werden -------------------------------
const long FIRSTUNIQUEICODE = 1000000000L;	// Identifikator (Dez)
const long FIRSTUNIQUEICODEX = 0xF0000000L;	// Identifikator (Hex)
const long FIRSTUNIQUEMCODE = 1000000000L;	// MerkmalsCode
const long FIRSTUNIQUERCODE = 1000000000L;	// RelationsCode
const long FIRSTUNIQUETEMPON = 10000000L;	// ObjektNummer

const long FIRSTUNIQUESYSMCODE = 2000000000L;	// MerkmalsCode (System)
const long FIRSTUNIQUESYSICODE = 2000000000L;	// Identifikator (System)

// Klasse, die einen Eintrag des GeoDB-Headers enthält ------------------------
enum HeaderEntryStatus { HE_INVALID, HE_DELETED, HE_MODIFIED, HE_UNMODIFIED };

#if !defined(NOHEADERENTRY)

class GeoDB;

class HeaderEntry {
private:
	char _HeaderKey[HDRKEYLENGTH+1];	// Schlüsselwort
	char *_HeaderText;			// HeaderText
	HeaderEntryStatus _Status;	// Status des HeaderSatzes
	GeoDB &_DB;					// DB aus dem Header kommt
	DWORD m_dwFlags;			// Art des HeaderEintrages

public:
// Konstruktoren
	_TRIAS02_ENTRY HeaderEntry (GeoDB &geoDB);
	_TRIAS02_ENTRY EXPORT02 HeaderEntry (GeoDB &geoDB, ResID uiRes);
	_TRIAS02_ENTRY EXPORT02 HeaderEntry (GeoDB &geoDB, const char *Key);
	_TRIAS02_ENTRY EXPORT02 HeaderEntry (GeoDB &geoDB, const char *Key, 
					const char *Text, DWORD dwFlags = HEADER_NORMAL);
	_TRIAS02_ENTRY HeaderEntry (HeaderEntry &);

// Memberfunktionen
	HeaderEntry & operator = (HeaderEntry &);

// liefern Attributwerte
	char *EntryKey (void) { return _HeaderKey; }
	char *EntryText (void) { return Status() != HE_INVALID ? _HeaderText : NULL; }
	HeaderEntryStatus &Status(void) { return _Status; }
	DWORD &Flags (void) { return m_dwFlags; }

_TRIAS02_ENTRY void EXPORT02 SetEntryText (char *_pNewText);
_TRIAS02_ENTRY ErrCode EXPORT02 WriteBack (void);

	int EntryInt (void) { return atoi (_HeaderText); }
_TRIAS02_ENTRY double EXPORT02 EntryDouble (double = 0.0);
_TRIAS02_ENTRY long EXPORT02 EntryLong (long = 0L, int iBase = 10);

	GeoDB &GetGeoDB (void) { return _DB; }

// Destruktor
	_TRIAS02_ENTRY EXPORT02 ~HeaderEntry (void);
};

inline void *GetEntryKey (void *pObj) 	// Extraktion der Vergleichsinformation
{
	return (((HeaderEntry *)pObj) -> EntryKey ());
}

//_TRIAS02_ENTRY bool EXPORT02 EnumHdrData (bool (*pFcn)(char *, bool, void *), void *pData);

#endif // NOHEADERENTRY

#endif // _HDENTRY_HXX
