// Klassendefinitionen fuer das Zusammensuchen der Palette einer Sicht --------
// File: PALETTE.HXX

#if !defined(_PALETTE_HXX)
#define _PALETTE_HXX

class _TRIAS02_ENTRY CmpColor 
{
private:
	Color _C;

public:
// Konstruktor/Destruktor
		CmpColor (Color C) { _C = C; }
		~CmpColor (void) {}

	BYTE Red (void) { return _C.Red(); }
	BYTE Green (void) { return _C.Green(); }
	BYTE Blue (void) { return _C.Blue(); }

// Vergleichsfunktion
friend int CmpColors (void *, void *);
friend void *ColorValue (void *);
};

class _TRIAS02_ENTRY CmpColorCreator;	// nur deklarieren

class _TRIAS02_ENTRY SightPalette : 
	public CTree 
{
protected:
	void UserDelete (void *);

public:
// Konstruktor/Destruktor
		SightPalette (void);
		~SightPalette (void);

// sonstige Member
	HPALETTE GetPalette (void);
	void AddToSightPalette (CTable &, CmpColorCreator &, VisInfo *);
};
DeclareLock (SightPalette, CmpColor);

#endif // _PALETTE_HXX

