// Klassendefinition fuer den Zugriff auf die interna der Font-Klasse im CV3B
// File: EFONT.HXX

#if !defined(_EFONT_HXX)
#define _EFONT_HXX

#ifndef NOFONT

// declaration purposes only !!, update when changing cv_imp.hxx
class Font_Imp
{
private:
	HFONT			hFont;
	Dimension		FntSize;

public:
	unsigned char 		IsStdFont : 1;
	unsigned char		StdFontType : 7;
	unsigned char		FntChanged : 4;
	unsigned char		FntTmpLft : 4;
	LOGFONT*		lft;
};														 

class PrinterPars;	// Deklarieren

class _TRIAS02_ENTRY ExtFont : public Font
{
public:
// Konstruktor
	EXPORT02 ExtFont (StdFamily, Dimension, const char * = NULL);
	EXPORT02 ExtFont (StdFont);

// Memberfunktionen
	short EXPORT02 SetOrientation (short);
	short EXPORT02 SetEscapement (short);

	bool EXPORT02 ChooseFont (HWND hWnd, char *lpCaption, 
			 TVisInfo **ppTVI, PrinterPars &PPDev, short = 0);
	bool EXPORT02 FontChanged (void);

// Destruktor
	EXPORT02 ~ExtFont (); 
}; 

// globale Funtkionen ---------------------------------------------------------
_TRIAS02_ENTRY Font * EXPORT02 MakeFont (TVisInfo *, Dimension);

#endif // NOFONT
#endif // _EFONT_HXX
