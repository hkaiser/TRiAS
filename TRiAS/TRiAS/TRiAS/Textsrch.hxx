// Modelessdialog fuer Textsuche in bestimmter Merkmalsgruppe
// File: TEXTSRCH.HXX

#if !defined(_TEXTSRCH_HXX)
#define _TEXTSRCH_HXX

const int MAXTEXTLEN = 120;

#define	ExactMatch 	1
#define	InexactMatch 	2
#define	SubStringMatch 	3

#if !defined(NOTEXTSEARCHDLG)
class TextRechercheDlg : public ModeLessDialog {
// Controls
	PushButton SuchButton;		// Auslöser
	SingleLineEdit SLE_SuchText;	// Eingabefenster für Suchtext
	char _SuchText[MAXTEXTLEN+1];	// SuchText
	int _SMode;			// aktueller Suchmode
	long _SearchCode;		// aktueller SuchMerkmalsKode

protected:
// EventHandler
	void ButtonClick (ControlEvt);
	Bool QueryClose (Event);

	ErrCode TextRecherche (void);

public:
// Konstruktor
		TextRechercheDlg (pWindow pW, long Code, int Mode);

// Member 
	char *GetSuchText (void) { return _SuchText; }
	void AdjustRechMode (int Mode, long MCode);
};
#endif // NOTEXTSEARCHDLG

#endif // _TEXTSRCH_HXX
