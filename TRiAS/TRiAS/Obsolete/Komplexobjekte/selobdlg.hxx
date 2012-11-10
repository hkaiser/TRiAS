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

	CObjWnds m_ObjWnds;		// Liste der Recherchefenster
	bool m_fSelected;		// alle oder nur selektierte Objekte

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

	bool FInit (ResourceFile &rRF);
	
public:
// Destruktor/Initialisierung
		~CSelectObjWndDlg (void);
		
static CSelectObjWndDlg *CreateInstance (UINT uiDlg, LPCSTR pcCaption, 
					DWORD dwFlags, ResourceFile &rRF);

// Fragt den Dialog nach seinen Daten 
	HRESULT GetEnumLONG (IEnum<LONG> **ppEnum);
};

#endif // _SELOBDLG_HXX

