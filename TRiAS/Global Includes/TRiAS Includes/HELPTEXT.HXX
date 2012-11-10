// Control, welches zur Anzeige eines Hilfetextes in Dialogfenstern 
// eingesetzt werden kann
// File: HELPTEXT.HXX

#if !defined(_HELPTEXT_HXX)
#define _HELPTEXT_HXX

class _TRIAS03_ENTRY CHelpText : 
	public FixedText 
{
private:
	char *m_pBuff;

#if defined(_FORCE_LEGACY_CODE)
	pFont m_pFont;
	unsigned short m_fFontChanged : 1;
#endif // _FORCE_LEGACY_CODE
	
public:
		CHelpText (pDialogWindow pW, ResID resID);
		~CHelpText (void);
		
	bool FInit (bool fChangeFont);
	
static CHelpText *CreateInstance (pDialogWindow, ResID resID, bool fChangeFont = true);

	void SetHelpText (ResID resID);		// nur Text ausgeben
	void SetHelpTextV (ResID resID, ...);	// Text mit Parametern anzeigen
};

#endif // _HELPTEXT_HXX
