// Auswahl von Objekten verschiedener Recherchefenster ------------------------
// File: SELOBDDLG.HXX

#if !defined(_SELOBDLG_HXX)
#define _SELOBDLG_HXX

#pragma warning (disable:4786)	// truncated debug information

typedef map<os_string, HWND, less<os_string> > CObjWnds;

class CSelectObjWndDlg : public CPropertyPage { 
private:
	DWORD m_dwFlags;		// erste oder letzte Page im Dlg ?

// Controls der Page
	MultiSelListBox m_mslbObjWnds;
	PushButton m_pbSelAll;
	RadioButton m_rbSelectedObjs;
	RadioButton m_rbAllObjs;
	RadioButton m_rbActivated;

	CObjWnds m_ObjWnds;		// Liste der Recherchefenster
	bool m_fSelected;		// alle oder nur selektierte Objekte
	bool m_fActivated;		// nur markierte Objekte
	bool m_fAllObjects;		// alle Objekte

	HWND m_hORWnd;			// TargetORFenster

protected:
	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);
	void WindowInit (Event);

	int OnSetActive (NotifyEvt);
	int OnWizFinish (NotifyEvt);
	int OnWizNext (NotifyEvt);
	void OnCancel (NotifyEvt);

	void AdjustOK (bool fDisableNext = false);
	bool PrepareResult (void);
	bool FillObjWnds (void);

// Konstruktor nicht direkt rufen
		CSelectObjWndDlg (ResID uiRes, LPCSTR pcCaption, DWORD dwFlags);

	bool FInit (void);
	
public:
// Destruktor/Initialisierung
		~CSelectObjWndDlg (void);
		
static CSelectObjWndDlg *CreateInstance (ResID uiDlg, LPCSTR pcCaption, DWORD dwFlags);

// Fragt den Dialog nach seinen Daten 
	HRESULT GetEnumLONG (IEnum<LONG> **ppEnum);

	void SetHWND (HWND hORWnd) { m_hORWnd = hORWnd; }
};

#endif // _SELOBDLG_HXX

