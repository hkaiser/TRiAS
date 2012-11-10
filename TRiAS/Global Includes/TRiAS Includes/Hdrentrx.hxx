// Headerdatei für HeaderEntry - Klasse, Variante fuer Extensions
// File: HDENTRY.HXX

#if !defined(_HDENTRX_HXX)
#define _HDENTRX_HXX

#include <pshpack1.h>

extern "C" {
// für atoi() und atof()
	#include <stdlib.h>
}

const int HDRKEYLENGTH 	= 16;	// Länge eines Headerkey's
const int HDRENTRYTEXTLEN	= 255;	// Länge eines Eintrages

// Klasse, die einen Eintrag des GeoDB-Headers enthält ------------------------
enum HeaderEntryStatus { HE_INVALID, HE_DELETED, HE_MODIFIED, HE_UNMODIFIED };

#if !defined(NOHEADERENTRY)

class HeaderEntryX 
{
private:
	char _HeaderKey[HDRKEYLENGTH+1];	// Schlüsselwort
	char *_HeaderText;		// HeaderText
	HeaderEntryStatus _Status;	// Status des HeaderSatzes
	DWORD m_dwFlags;
#if _TRiAS_VER >= 0x0300
	HPROJECT m_hPr;
#endif // _TRiAS_VER >= 0x0300

public:
// Konstruktoren
#if _TRiAS_VER >= 0x0300
		HeaderEntryX (HPROJECT hPr = HACTPROJECT);
#if defined(__CV__)
		HeaderEntryX (ResID uiRes, HPROJECT hPr = HACTPROJECT);
#endif // __CV__
#if defined(__MFC__) || defined(__WTL__)
		HeaderEntryX (UINT uiID, HPROJECT hPr = HACTPROJECT);
#endif // __MFC__
		HeaderEntryX (const char *Key, HPROJECT hPr = HACTPROJECT);
		HeaderEntryX (const char *Key, const char *Text, DWORD dwFlags = HEADER_NORMAL, HPROJECT hPr = HACTPROJECT);
#else
		HeaderEntryX (void);
#if defined(__CV__)
		HeaderEntryX (ResID uiRes);
#endif // __CV__
#if defined(__MFC__) || defined(__WTL__)
		HeaderEntryX (UINT uiID);
#endif // __MFC__
		HeaderEntryX (const char *Key);
		HeaderEntryX (const char *Key, const char *Text, DWORD dwFlags = HEADER_NORMAL);
#endif // _TRiAS_VER >= 0x0300
		HeaderEntryX (HeaderEntryX &);

// Memberfunktionen
	HeaderEntryX & operator = (HeaderEntryX &);

// liefern Attributwerte
	char *EntryKey (void) { return _HeaderKey; }
	char *EntryText (void) { return _HeaderText; }
	HeaderEntryStatus &Status(void) { return _Status; }
	DWORD &Flags (void) { return m_dwFlags; }

	void SetEntryText (char *_pNewText);
	ErrCode WriteBack (void);
	ErrCode DeleteEntry (void);

	int EntryInt (void) { return atoi (_HeaderText); }
	double EntryDouble (double = 0.0);
	long EntryLong (long = 0L);

// Destruktor
		~HeaderEntryX (void);
};

inline void *GetEntryKey (void *pObj)	// Extraktion der Vergleichsinformation
{
	return (((HeaderEntryX *)pObj) -> EntryKey ());
}

#endif // NOHEADERENTRY

#include <poppack.h>

#endif // _HDENTRX_HXX
