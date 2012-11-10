// Einstellung einer Farbpalette ----------------------------------------------
// File: CPALETTE.HXX

#if !defined(_CPALETTE_HXX)
#define _CPALETTE_HXX


class CColorBox : public PushButton {
private:
	FVisInfo *m_pFVI;		// lokale Kopie
	short m_iCnt;			// ZählNummer
	HWND m_hWnd;			// ParentHandle
	ResourceFile &m_rRF;		// dieser Modul
	HPALETTE m_hPal;
	
public:
		CColorBox (pDialogWindow pW, short iCnt, 
			   HPALETTE hPal, ResourceFile *pRF);
		~CColorBox (void);
		
	BOOL FInit (FVisInfo *pFVI);
	FVisInfo *GetFVisInfo (BOOL fConvert = FALSE);

friend class CPaletteDlg;
};


class CPaletteDlg : public OwnerDrawDialogWindow {
private:
	PushButton m_pbOK;
	PushButton m_pbHelp;
	PushButton m_pbSelect;
	PushButton m_pbReset;
	SingleLineEdit m_slePaletteName;
	
	NumEditX m_neDigits;
	FixedText m_ftPercents;
	FixedText m_ftDigits;
			
	CColorBox *m_pCB[MAXPIECOLORS];
	CVisPalette &m_rPalette;
	
	short m_iActColor;			// aktive Farbe
	unsigned short m_fIsDirty : 1;		// was geändert
	HPALETTE m_hPal;			// WindowsPalette
	
	ResourceFile &m_rRF;
	HWND __hWndM;				// HauptfensterHandle (für DEX_...)
	
	void AdjustOK (void);

protected:
	void ButtonClick (ControlEvt);
	void ButtonDblClk (ControlEvt);
	void EditChange (ControlEvt);
	
// EventHandler für OwnerDraw-Messages
	BOOL MeasureItem (MeasureItemEvt);	// Größe eines Elements bestimmen
	BOOL DrawEntireItem (DrawItemEvt);	// Element vollständig malen
	BOOL DrawItemFocus (DrawItemEvt);	// Element mit Focus zeichnen

public:
		CPaletteDlg (pWindow pW, HWND hWndM, CVisPalette &rVP, 
			     HPALETTE hPal, ResourceFile *pRF, BOOL fPercent);
		~CPaletteDlg (void);
		
	BOOL FInit (void);
	void Select (short iAct);
		
	CVisPalette *GetVisPalette (void);
	char *GetVisPaletteName (char *pBuffer, short iLen)
		{ m_slePaletteName.GetText (pBuffer, iLen); return pBuffer; }

	class NakedEvt : public Event {
	public:
		UINT wmsg (void) { return wMsg; }
		WPARAM wparam (void) { return wParam; }
	};

static CPaletteDlg *CreateInstance (pWindow pW, HWND hWndM, CVisPalette &rVP, 
				    HPALETTE hPal, ResourceFile *pRF, BOOL fPercent);
};

extern "C" bool WINAPI DrawRectangle (HDC hDC, int x1, int y1, int x2, int y2);

#endif // _CPALETTE_HXX

