// Auswahl von Objekten verschiedener Recherchefenster ------------------------
// File: DSTOBDDLG.HXX

#if !defined(_DSTOBDLG_HXX)
#define _DSTOBDLG_HXX

#pragma warning (disable:4786)	// truncated debug information

typedef map<os_string, HWND, less<os_string> > CObjWnds;

class CDestObjWndDlg : public CPropertyPage { 
private:
	DWORD m_dwFlags;		// erste oder letzte Page im Dlg ?

// Controls der Page
	ListBox m_lbObjWnds;
	CheckBox m_cbRetainSelection;
	CheckBox m_cbSelectNew;
	RadioButton m_rbCreateNew;
	RadioButton m_rbSelectOld;

	CObjWnds m_ObjWnds;		// Liste der Recherchefenster
	HWND m_hWnd;

	bool m_fRetainSelection;	// Bisherige Selektion beibehalten
	bool m_fSelectNew;		// neue Objekte selektieren

protected:
	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);
	void WindowInit (Event);

	int OnSetActive (NotifyEvt);
	int OnWizFinish (NotifyEvt);
	int OnWizNext (NotifyEvt);
	void OnCancel (NotifyEvt);

	void AdjustOK (bool fDisableNext = false);
	void AdjustLB (void);

	bool PrepareResult (void);
	bool FillObjWnds (void);

// Konstruktor nicht direkt rufen
		CDestObjWndDlg (ResID uiRes, LPCSTR pcCaption, DWORD dwFlags);

	bool FInit (ResourceFile &rRF);
	
public:
// Destruktor/Initialisierung
		~CDestObjWndDlg (void);
		
static CDestObjWndDlg *CreateInstance (UINT uiDlg, LPCSTR pcCaption, 
					DWORD dwFlags, ResourceFile &rRF);

// Fordert Dialog auf, die Objekte ins gewünschte Fenster zu schreiben
	HRESULT SetEnumLONG (IEnum<LONG> *ppEnum);
};

#endif // _DSTOBDLG_HXX

