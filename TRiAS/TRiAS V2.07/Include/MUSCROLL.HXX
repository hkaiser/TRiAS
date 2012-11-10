// Klassendefinition fuer MicroScrollControl ----------------------------------
// File: MUSCROLL.HXX

#if !defined(_MUSCROLL_HXX)
#define _MUSCROLL_HXX

enum MSColorDef {		// Bereiche des Controls mit eigenen Farben
	MSColorFace = 0,
	MSColorArrow = 1,
	MSColorShadow = 2,
	MSColorHighlight = 3,
	MSColorFrame = 4,
};

// Horizontaler SpinButton ----------------------------------------------------
class _TRIAS03_ENTRY HorizMicroScroll : public HorizScrollBar {
protected:
	HWND GetHandle (void) { return (HWND)Handle (API_CONTROL_HCONTROL); }

public:
// Konstruktor
	EXPORT03 HorizMicroScroll (pDialogWindow, ResID);

// Memberfunktionen
	Range EXPORT03 SetScrollRange (Range);
	Range EXPORT03 GetScrollRange (void);
	uint EXPORT03 SetCurrPos (uint);
	uint EXPORT03 GetCurrPos (void);
	Bool EXPORT03 SetPegScroll (Bool);
	Bool EXPORT03 GetPegScroll (void);
	Bool EXPORT03 SetInvertRange (Bool);
	Bool EXPORT03 GetInvertRange (void);
	Color EXPORT03 SetColor (MSColorDef, Color);
	Color EXPORT03 GetColor (MSColorDef);
};

// Vertikaler SpinButton ------------------------------------------------------
class _TRIAS03_ENTRY VertMicroScroll : public VertScrollBar {
protected:
	HWND GetHandle (void) { return (HWND)Handle (API_CONTROL_HCONTROL); }

public:
// Konstruktor
	EXPORT03 VertMicroScroll (pDialogWindow, ResID);

// Memberfunktionen
	Range EXPORT03 SetScrollRange (Range);
	Range EXPORT03 GetScrollRange (void);
	uint EXPORT03 SetCurrPos (uint);
	uint EXPORT03 GetCurrPos (void);
	Bool EXPORT03 SetPegScroll (Bool);
	Bool EXPORT03 GetPegScroll (void);
	Bool EXPORT03 SetInvertRange (Bool);
	Bool EXPORT03 GetInvertRange (void);
	Color EXPORT03 SetColor (MSColorDef, Color);
	Color EXPORT03 GetColor (MSColorDef);
};


#endif // _MUSCROLL_HXX
