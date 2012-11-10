// Control, welches zur Anzeige eines Hilfetextes in Dialogfenstern 
// eingesetzt werden kann
// File: HELPTEXT.HXX

#if !defined(_HELPTEXT_HXX)
#define _HELPTEXT_HXX

class ResourceFile;

class CHelpText : public FixedText {
private:
	char *m_pBuff;
	pFont m_pFont;
	unsigned short m_fFontChanged : 1;
	ResourceFile* m_pRF;
	
public:
		CHelpText (pDialogWindow pW, ResID resID, ResourceFile *pRF);
		~CHelpText (void);
		
	BOOL FInit (void);
	
// static CHelpText *CreateInstance (pDialogWindow, ResID resID);

	void SetHelpText (uint ID);         	// nur Text ausgeben
	void SetHelpTextV (ResID resID, ...);   // Text mit Parametern anzeigen
};

#endif // _HELPTEXT_HXX
