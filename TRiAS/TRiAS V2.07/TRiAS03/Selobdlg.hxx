// Auswahl von Objekten verschiedener Recherchefenster ------------------------
// File: SELOBDDLG.HXX

#if !defined(_SELOBDLG_HXX)
#define _SELOBDLG_HXX

#pragma warning (disable:4786)	// truncated debug information
//#pragma optimize ("", off)			// map nicht optimieren
#include <ospace/std/map>

typedef map<os_string, HWND, less<os_string> > CObjWnds;

#include "propactb.hxx"

class CSelectObjWndDlg 
	: public CPropertyPage,
	  public CPropertyActionExtUsage	// JG 980916
{ 
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

	class CSelObjWndPropAct *m_pParent;

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
		CSelectObjWndDlg (CSelObjWndPropAct *pParent, ResID uiRes, 
						  LPCSTR pcCaption);
	bool FInit (void);
	
public:
// Destruktor/Initialisierung
		~CSelectObjWndDlg (void);
		
static CSelectObjWndDlg *CreateInstance (
			CSelObjWndPropAct *pParent, ResID uiDlg, LPCSTR pcCaption);

	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }

// Fragt den Dialog nach seinen Daten 
	HRESULT GetEnumLONG (IEnum<LONG> **ppEnum);

	void SetHWND (HWND hORWnd) { m_hORWnd = hORWnd; }

	void SetDirty (bool fDirty = true);
};

///////////////////////////////////////////////////////////////////////////////
// Füllen des Enums mit Objekten eines Fensters
bool FillTrees (bool fSelected, bool fActivated, HWND hORWnd, IEnum<LONG> *pIEnum);

#endif // _SELOBDLG_HXX

