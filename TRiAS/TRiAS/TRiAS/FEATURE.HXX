// OwnerDrawComboBox fuer die DarstellungsStilAuswahl -------------------------
// File: FEATURE.HXX

#if !defined(_FEATURE_HXX)
#define _FEATURE_HXX

// DatenTyp, die in OwnerDrawComboBox gespeichert wird ------------------------
class Feature {
public:
// Daten
	char *_StyleName;
	unsigned int _Style;

// Konstruktor/Destruktor
		Feature (unsigned int Style, char *Name);
		~Feature (void);
};

#if !defined(MARKER1)
#define MARKER1		170
#define FIRSTFILLBMP	1992
#define LASTFILLBMP		2061
#endif

#endif	// _FEATURE_HXX
