// Headerdatei für HeaderEntry - Klasse, Variante fuer Extensions
// File: HDENTRY.HXX

#if !defined(_HDENTRX_HXX)
#define _HDENTRX_HXX

#include <pshpack1.h>

extern "C" {
// für atoi() und atof()
	#include <stdlib.h>
}

const short HDRKEYLENGTH 	= 16;	// Länge eines Headerkey's
const short HDRENTRYTEXTLEN	= 255;	// Länge eines Eintrages

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
	HPROJECT m_hPr;

public:
// Konstruktoren
		HeaderEntryX (HPROJECT hPr = NULL);
#if defined(__CV__)
		HeaderEntryX (ResID uiRes, HPROJECT hPr = NULL);
#endif // __CV__
#if defined(__MFC__)
		HeaderEntryX (UINT uiID, HPROJECT hPr = NULL);
#endif // __MFC__
		HeaderEntryX (const char *Key, HPROJECT hPr = NULL);
		HeaderEntryX (const char *Key, const char *Text, DWORD dwFlags = HEADER_NORMAL, HPROJECT hPr = NULL);
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
