// FarbregelungsDialog --------------------------------------------------------
// File: COLCNTRL.HXX

#if !defined(_COLCNTRL_HXX)
#define _COLCNTRL_HXX

extern "C" 
BOOL PASCAL _XTENSN_EXPORT RemapViewEntryColors (long, BOOL, void *);

enum PaletteAction {
	PAL_NOACTION = 0,
	PAL_BEGINANIMATION = 1,
	PAL_COPYPALETTE = 2,
};

typedef struct tagHSBDATA {
	ulong lHSB;	// eigentliche Daten
	bool fControl;	// Sättigung regeln
} HSBDATA;

class CColorControlDlg : public DialogWindow {
private:
	RadioButton m_rbSatAll;
	RadioButton m_rbSatSmaller;
	RadioButton m_rbSatBigger;
	HorizScrollBar m_sbAbsSat;
	RangeNumEdit m_sleAbsSat;
	
	RadioButton m_rbBright;
	RadioButton m_rbInvBright;
	HorizScrollBar m_sbBright;
	RangeNumEdit m_sleBright;

#if !defined(WIN32)
	PushButton m_pbHelp;
#endif //!WIN32
	ResourceFile &m_rRF;
	
	PaletteAction m_enPalAction;
	HPALETTE m_hPal;
	HPALETTE m_hOldPal;
	char *m_pBuff;
	
	int m_nEntries;				// HSB-Werte
	HSBDATA *m_pHSB;
	
	LOGPALETTE *m_pPal;			// RGB-Werte
	
protected:
	void HorizScroll (ScrollEvt);		// ScrollBalken
	void EditFocusChg (EditFocusChgEvt);	// Focus loosed/gained to Edit
	void ButtonClick (ControlEvt);		// ButtonClick
	
public:
		CColorControlDlg (pWindow, ResourceFile *);
		~CColorControlDlg (void);

	bool Init (void);
	bool SetNewPalette (HPALETTE hPal);

	bool SaveNewColors (char *pView = NULL);
	bool RemapEntry (long lIdent, short iVTyp, char *pView);
/*inline*/	void RemapColor (COLORREF &rC);
	
	bool PaletteAnimation (HPALETTE hPal);
	LOGPALETTE *InitPalEntries (HPALETTE hPal);
	HSBDATA *InitHSBValues (void);

//	short GetInitialSat (void);
	void SetSat (short iSat);
//	void ResetSat (void);
	void ControlBright (short iRelBright, bool fDir);
	void ResetBright (void);

	void AnimatePalette (void);
	
friend 	BOOL PASCAL _XTENSN_EXPORT RemapViewEntryColors (long lIdent, BOOL, void *pData);
};

// sonstige Hilfsfunktionen ---------------------------------------------------
HPALETTE CopyPalette (HPALETTE hPal);

#endif // _COLCNTRL_HXX

