///////////////////////////////////////////////////////////////////////////
// @doc 
// @module Hdrentry.hxx | Headerdatei für HeaderEntryBase - Klasse

#if !defined(_HDRENTRY_HXX__85245DF4_6CC8_11D1_973E_00A024D6F582__INCLUDED_)
#define _HDRENTRY_HXX__85245DF4_6CC8_11D1_973E_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

const short HDRKEYLENGTH = 16;		// Länge eines Headerkey's
const short HDRENTRYTEXTLEN	= 255;	// Länge eines Eintrages
const char ModifiedChar = '*';		// ModifiedFlag für Headereintrag

// Erste Codes, die fortlaufend vergeben werden -------------------------------
const long FIRSTUNIQUEICODE = 1000000000L;	// Identifikator (Dez)
const long FIRSTUNIQUEICODEX = 0xF0000000L;	// Identifikator (Hex)
const long FIRSTUNIQUEMCODE = 1000000000L;	// MerkmalsCode
const long FIRSTUNIQUERCODE = 1000000000L;	// RelationsCode
const long FIRSTUNIQUETEMPON = 10000000L;	// ObjektNummer

const long FIRSTUNIQUESYSMCODE = 2000000000L;	// MerkmalsCode (System)
const long FIRSTUNIQUESYSICODE = 2000000000L;	// Identifikator (System)

const long FIRSTUNIQUESYSMCODE_PRJ = 3000000000L;	// MerkmalsCode (System) im Projekt
const long FIRSTUNIQUEMCODE_PRJ = 1100000000L;		// MerkmalsCode im Projekt

// Klasse, die einen Eintrag des GeoDB-Headers enthält ------------------------
enum HeaderEntryStatus { HE_INVALID, HE_DELETED, HE_MODIFIED, HE_UNMODIFIED };

class GeoDB;

class HeaderEntryBase 
{
private:
	char _HeaderKey[HDRKEYLENGTH+1];	// Schlüsselwort
	char *_HeaderText;			// HeaderText
	HeaderEntryStatus _Status;	// Status des HeaderSatzes
	GeoDB &_DB;					// DB aus dem Header kommt
	DWORD m_dwFlags;			// Art des HeaderEintrages

protected:
	bool m_fForceNoProject;		// kein hPr in DEX_... Messages angeben
	HPROJECT DBDesc() { return m_fForceNoProject ? HACTPROJECT : _DB.DBDesc(); }

public:
// Konstruktoren
	_TRIAS02_ENTRY HeaderEntryBase (GeoDB &geoDB, bool fForceNoProject);
	_TRIAS02_ENTRY HeaderEntryBase (GeoDB &geoDB, ResID uiRes, bool fForceNoProject);
	_TRIAS02_ENTRY HeaderEntryBase (GeoDB &geoDB, const char *Key, bool fForceNoProject);
	_TRIAS02_ENTRY HeaderEntryBase (GeoDB &geoDB, const char *Key, 
					const char *Text, DWORD dwFlags, bool fForceNoProject);
	_TRIAS02_ENTRY HeaderEntryBase (HeaderEntryBase &);

// Memberfunktionen
	HeaderEntryBase & operator = (HeaderEntryBase &);

// liefern Attributwerte
	char *EntryKey (void) { return _HeaderKey; }
	char *EntryText (void) { return Status() != HE_INVALID ? _HeaderText : NULL; }
	HeaderEntryStatus &Status(void) { return _Status; }
	DWORD &Flags (void) { return m_dwFlags; }
	int EntryInt (void) { return atoi (_HeaderText); }

_TRIAS02_ENTRY void SetEntryText (char *_pNewText);
_TRIAS02_ENTRY ErrCode WriteBack (void);
_TRIAS02_ENTRY ErrCode DeleteEntry (void);

_TRIAS02_ENTRY double EntryDouble (double = 0.0);
_TRIAS02_ENTRY long EntryLong (long = 0L, int iBase = 10);

	GeoDB &GetGeoDB (void) { return _DB; }

// Destruktor
	_TRIAS02_ENTRY ~HeaderEntryBase (void);
};

inline void *GetEntryKey (void *pObj) 	// Extraktion der Vergleichsinformation
{
	return (((HeaderEntryBase *)pObj) -> EntryKey ());
}

///////////////////////////////////////////////////////////////////////////////
// HeaderEntry im Projekt
class HeaderEntry
	: public HeaderEntryBase
{
public:
	_TRIAS02_ENTRY HeaderEntry (GeoDB &geoDB)
		: HeaderEntryBase (geoDB, false) {}
	_TRIAS02_ENTRY HeaderEntry (GeoDB &geoDB, ResID uiRes)
		: HeaderEntryBase (geoDB, uiRes, false) {}
	_TRIAS02_ENTRY HeaderEntry (GeoDB &geoDB, const char *Key)
		: HeaderEntryBase (geoDB, Key, false) {}
	_TRIAS02_ENTRY HeaderEntry (GeoDB &geoDB, const char *Key, 
					const char *Text, DWORD dwFlags = HEADER_NORMAL)
		: HeaderEntryBase (geoDB, Key, Text, dwFlags, false) {}
	_TRIAS02_ENTRY HeaderEntry (HeaderEntry &rHE)
		: HeaderEntryBase (rHE) {}
};

///////////////////////////////////////////////////////////////////////////////
// HeaderEntry im Projekt
class CPrjHeaderEntry
	: public HeaderEntryBase
{
public:
	_TRIAS02_ENTRY CPrjHeaderEntry (GeoDB &geoDB)
		: HeaderEntryBase (geoDB, true) {}
	_TRIAS02_ENTRY CPrjHeaderEntry (GeoDB &geoDB, ResID uiRes)
		: HeaderEntryBase (geoDB, uiRes, true) {}
	_TRIAS02_ENTRY CPrjHeaderEntry (GeoDB &geoDB, const char *Key)
		: HeaderEntryBase (geoDB, Key, true) {}
	_TRIAS02_ENTRY CPrjHeaderEntry (GeoDB &geoDB, const char *Key, 
					const char *Text, DWORD dwFlags = HEADER_NORMAL)
		: HeaderEntryBase (geoDB, Key, Text, dwFlags, true) {}
	_TRIAS02_ENTRY CPrjHeaderEntry (CPrjHeaderEntry &rHE)
		: HeaderEntryBase (rHE) {}
};

#endif // !defined(_HDRENTRY_HXX__85245DF4_6CC8_11D1_973E_00A024D6F582__INCLUDED_)
