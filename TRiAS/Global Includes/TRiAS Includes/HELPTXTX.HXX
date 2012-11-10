// Control, welches zur Anzeige eines Hilfetextes in Dialogfenstern 
// eingesetzt werden kann
// File: HELPTEXT.HXX

#if !defined(_HELPTXTX_HXX)
#define _HELPTXTX_HXX

class CHelpTextX : public FixedText {
private:
	char *m_pBuff;

#if _TRiAS_VER < 0x0300
	pFont m_pFont;
	unsigned short m_fFontChanged : 1;
#endif // _TRiAS_VER < 0x0300

public:
		CHelpTextX (pDialogWindow pW, ResID resID);
		~CHelpTextX (void);
		
	bool FInit (void);
	
static CHelpTextX *CreateInstance (pDialogWindow, ResID resID);

	void SetHelpText (ResID resID);		// nur Text ausgeben
	void SetHelpTextV (ResID resID, ...);	// Text mit Parametern anzeigen
};

#endif // _HELPTXTX_HXX
