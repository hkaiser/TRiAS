// Klassendefintionen zur fuer FarbComboBox -----------------------------------
// File: DCOLOR.HXX

#if !defined(_DCOLOR_HXX)
#define _DCOLOR_HXX

// Konstantendefinitionen -----------------------------------------------------
#define MAXCOLORVAL	255	// maximale Werte für rot, grün,blau
#define MAXHUE		359	// maximaler Wert für Farbwert
#define MAXSATURATION	100	// maximaler Wert für Farbsättigung
#define MAXBRIGHTNESS	100	// maximaler Wert für Helligkeit

// Eigene NumEditKlasse, die eigene Validierung definiert ---------------------
class ColEdit : public NumEdit {
private:
	short m_iMax;		// maximaler Farbwert
	
public:
// Konstruktor/Destruktor
		ColEdit (pDialogWindow, ResID rsc, short iMax = MAXCOLORVAL);

	int PostValidate (int);
};

// ScrollBar mit EditControl, die in engem Zusammenhang stehen ----------------
class ColorScrollBar {
public:
	enum SB_Mode {
		SB_Fine,	// Feineinstellung (FüllFarbe)
		SB_Coarse,	// Grobeinstellung (RandFarbe)
	};

protected:
	SB_Mode _Mode;		// GenauigkeitsModus
	short m_iMax;		// maximaler Wert

public:
	ScrollBar ColorBar;
	ColEdit ColorEdit;
	
// Konstruktor/Destruktor
		ColorScrollBar (pDialogWindow pW, uint SB, uint SLE, short iMax = MAXCOLORVAL);
		~ColorScrollBar (void);

// sonstige Memberfunktionen
	void SetColor (short);		// setzen des FarbWertes
	short GetColor (void);		// holen des Farbwertes

// Kopieren der Werte vom EditControl in das ScrollBarControl
	short CopyToScrollBar (void);

	SB_Mode SetMode (SB_Mode);	// genauigkeitsmodus einstellen
};

// ListBox, die sich ihre Farbwerte selbst merkt ------------------------------
// DatenTyp, die in OwnerDrawComboBox'en gespeichert werden -------------------
class ColorItem {
public:
// Daten
	char *_Name;
	Color _C;

// Konstruktor/Destruktor
		ColorItem (Color C, char *Name);
		~ColorItem (void);
};

// Funktion, die 2 Farbwerte vergleicht
short CmpColor (Color C1, Color C2);

#include <palchevt.hxx>		// PaletteChangeEvt

class ColorListBox : public OwnerDrawComboBox {
private:
#if defined(_FORCE_LEGACY_CODE)
	char *_InitFile;
#endif // defined(_FORCE_LEGACY_CODE)
	LOGPALETTE *_pPal;	// lokale Palette
	HPALETTE _hPal;		// lokales PalettenHandle
	short _iCurrPalEntry;

public:
	enum ColorSearchMode {
		SM_Color, 	// SuchKriterium: Farbe
		SM_Name,	// Suchkriterium FarbName
	};

private:
	ColorSearchMode _SM;		// aktuelles Suchkriterium

protected:
	void EXPORTTRIAS PaletteChange (PaletteChangeEvt);	// virtual EventHandler

public:
// Konstruktor/Destruktor
		ColorListBox (pDialogWindow, uint);
		~ColorListBox (void);

	bool FInit (Color C, const char *IniFile = NULL);
	
// Memberfunktion
	ColorSearchMode SetSearchMode (ColorSearchMode = SM_Color);
						// SuchKriterium setzen
	ColorSearchMode GetSearchMode (void) { return _SM; }
	HPALETTE CorrectPalette (Color);
	HWND Handle (void) { return GetControl() -> Handle (API_CONTROL_HCONTROL); }
};

// ----------------------------------------------------------------------------
// Anzahl der DarstellungsModi 
#define NUMPOINTSTYLES	253					// PunktSymbole
#define NUMLINESTYLES	15					// LinienTypen
#if defined(_USE_TRANSPARENT_PATTERNS)
#define NUMFILLSTYLES_TRANSPARARENT	70		// Anzahl der Füllmuster
#define NUMFILLSTYLES	56					// Füllmuster
#else
#define NUMFILLSTYLES	56					// Füllmuster
#endif // _USE_TRANSPARENT_PATTERNS

class StyleComboBox : public OwnerDrawComboBox {
public:
	enum SearchMode {
		SM_Style, 	// SuchKriterium: DarstellungsStil
		SM_Name,	// Suchkriterium StilName
	};

private:
	SearchMode _SM;		// aktuelles Suchkriterium
//	char *_InitFile;

public:
// Konstruktor/Destruktor
		StyleComboBox (pDialogWindow, uint);
		~StyleComboBox (void);

	bool FInit (short, uint, short);
	
// Memberfunktionen
	SearchMode SetSearchMode (SearchMode = SM_Style);
						// SuchKriterium setzen
	SearchMode GetSearchMode (void) { return _SM; }
};

class FillStyleComboBox : public StyleComboBox {
public:
// Konstruktor/Destruktor
		FillStyleComboBox (pDialogWindow, uint);
		~FillStyleComboBox (void);
		
	bool FInit (short iStyle /*, char *pIniFile = NULL*/);
};

class LineStyleComboBox : public StyleComboBox {
public:
// Konstruktor/Destruktor
		LineStyleComboBox (pDialogWindow, uint);
		~LineStyleComboBox (void);

	bool FInit (short iStyle /*, char *pIniFile = NULL*/);
};

class PointStyleComboBox : public StyleComboBox {
public:
// Konstruktor/Destruktor
		PointStyleComboBox (pDialogWindow, uint);
		~PointStyleComboBox (void);

	bool FInit (unsigned short iStyle, DatenBasisObjekt &rDBO);
};


#endif	// _DCOLOR_HXX

