// Auswahl von Objekten verschiedener Recherchefenster ------------------------
// File: DSTOBDLG.HXX

#if !defined(_DSTOBDLG_HXX)
#define _DSTOBDLG_HXX

#pragma warning (disable:4786)	// truncated debug information
//#pragma optimize ("", off)			// map nicht optimieren
#include <ospace/std/map>

typedef map<os_string, HWND, less<os_string> > CObjWnds;

class CDestObjWndDlg : public CPropertyPage { 
private:
	DWORD m_dwFlags;		// erste oder letzte Page im Dlg ?
	class CDestObjWndPropAct *m_pParent;

// Controls der Page
	ListBox m_lbObjWnds;
	CheckBox m_cbRetainSelection;
	CheckBox m_cbSelectNew;
	RadioButton m_rbCreateNew;
	RadioButton m_rbSelectOld;

	CObjWnds m_ObjWnds;		// Liste der Recherchefenster
	HWND m_hWnd;

	bool m_fRetainSelection;	// Bisherige Selektion beibehalten
	bool m_fSelectNew;			// neue Objekte selektieren

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
		CDestObjWndDlg (CDestObjWndPropAct *pParent, ResID uiRes, LPCSTR pcCaption);

	bool FInit (void);
	
public:
// Destruktor/Initialisierung
		~CDestObjWndDlg (void);
		
static CDestObjWndDlg *CreateInstance (CDestObjWndPropAct *pParent, 
									   ResID uiRes, LPCSTR pcCaption);

	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }

// Fordert Dialog auf, die Objekte ins gewünschte Fenster zu schreiben
	void SetDirty (bool fDirty = true);

// ResultatsAbfrage
	HWND GetORWindow (void) { return m_hWnd; }
	bool FRetainSel (void) { return m_fRetainSelection ? true : false; }
	bool FSelectNew (void) { return m_fSelectNew ? true : false; }

	HPROPSHEETPAGE CreatePage (void) { return CPropertyPage::CreatePage(); }
};

#endif // _DSTOBDLG_HXX

