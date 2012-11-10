// Headerdatei fÅr HeaderEntry - Klasse, Variante fuer Extensions
// File: HDENTRY.HXX

#if !defined(_HDENTRX_HXX)
#define _HDENTRX_HXX

extern "C" {
// fÅr atoi() und atof()
	#include <stdlib.h>
}

const short HDRKEYLENGTH = 16;		// LÑnge eines Headerkey's
const short HDRENTRYTEXTLEN	= 128;	// LÑnge eines Eintrages

// Klasse, die einen Eintrag des GeoDB-Headers enthÑlt ------------------------
enum HeaderEntryStatus { HE_INVALID, HE_DELETED, HE_MODIFIED, HE_UNMODIFIED };

#if !defined(NOHEADERENTRY)

class HeaderEntryX {
private:
	char _HeaderKey[HDRKEYLENGTH+1];	// SchlÅsselwort
	char *_HeaderText;		// HeaderText
	HeaderEntryStatus _Status;	// Status des HeaderSatzes

public:
// Konstruktoren
		HeaderEntryX (void);
		HeaderEntryX (const char *Key);
		HeaderEntryX (const char *Key, const char *Text);
		HeaderEntryX (HeaderEntryX &);

// Memberfunktionen
	HeaderEntryX & operator = (HeaderEntryX &);

// liefern Attributwerte
	char *EntryKey (void) { return _HeaderKey; }
	char *EntryText (void) { return _HeaderText; }
	HeaderEntryStatus &Status(void) { return _Status; }

	void SetEntryText (char *_pNewText);
	ErrCode WriteBack (void);

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

#endif // _HDENTRX_HXX
