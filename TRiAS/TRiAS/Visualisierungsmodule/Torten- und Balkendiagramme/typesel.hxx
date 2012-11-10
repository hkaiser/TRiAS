// Auswahl des konkreten Torten-/Balken-Typs ----------------------------------
// File: TYPESEL.HXX

#if !defined(_TYPESEL_HXX)
#define _TYPESEL_HXX

extern "C" BOOL _VMD_EXPORT FAR PASCAL FillMCodesListBox (long MCode, BOOL, void *pData);

class CTortenSelDlg : public DialogWindow {
private:
	ComboBox m_cbTypes;
	CheckBox m_chkbShowValues;
	RadioButton m_rbRelValues;
	RadioButton m_rbAbsValues;
	ComboBox m_cbMCodes;
	CPictureBox m_bbPreview;
	CheckBox m_chkbOffset;
	PushButton m_pbOK;
	PushButton m_pbHelp;
	PushButton m_pbColors;
	FixedText m_ftHelpText;
	ComboBox m_chkbPalettes;
	
	ResourceFile &m_rRF;
	class CVisPaletteTree &m_rVPT;
	
	HWND __hWndM;		// wird für DEX_Messages benötigt
	HPALETTE m_hPal;
	
#if defined(_FORCE_LEGACY_CODE)
	pFont m_pFont;
	unsigned short m_fFontChanged : 1;
#endif // _FORCE_LEGACY_CODE

	unsigned short m_fOffset : 1;
	unsigned short m_fRelValues : 1;
	unsigned short m_fAbsValues : 1;
	unsigned short m_fPalTreeChanged : 1;
	
	char *m_pBuff;
	char *m_pInBuff;
	long m_lMCode;
	short m_iType;
	
protected:
	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);
	void EditFocusChg (EditFocusChgEvt);	// für ComboBoxen
	
	void AdjustTypeInfos (short iIndex = -1);
	void SetHelpText (unsigned short uiRes, const char *pStr = NULL);
	BOOL AdjustOKButton (void);

public:
		CTortenSelDlg (pWindow pW, ResourceFile *pRF, 
			       CTortenVisModule *pVM, short iType, long lMCode,
			       HPALETTE hPal, CVisPaletteTree *pVPT);
		~CTortenSelDlg (void);
		
	BOOL FInit (const char *pPName);
	
	void ReadDefinedPalettes (const char *pPName);
	BOOL ModifyVisPalette (void);

	BOOL FPalTreeChanged (void) { return m_fPalTreeChanged != 0; }
		
// AbfrageFunktionen für Nutzerwünsche
	short GetSelectedType (void);
	long GetSelectedMCode (void);
	char *& GetSelectedPalette (void);
	
friend BOOL PASCAL _VMD_EXPORT FillMCodesListBox (long MCode, BOOL, void *pData);
};


#endif // _TYPESEL_HXX
