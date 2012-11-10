// Auswahl von Objekten verschiedener Recherchefenster ------------------------
// File: SELOBDDLG.HXX

#if !defined(_SELOBDLG_HXX)
#define _SELOBDLG_HXX

#pragma warning (disable:4786)	// truncated debug information
//#pragma optimize ("", off)			// map nicht optimieren
#include <ospace/std/map>

typedef map<os_string, HWND, less<os_string> > CObjWnds;

#include "propactb.hxx"

///////////////////////////////////////////////////////////////////////////////
// Auswahlmode für ORFenster
typedef enum tagSELECTMODE {
	SELECTMODE_Activated = 0,
	SELECTMODE_Selected = 1,
	SELECTMODE_All = 2
} SELECTMODE;

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
	CheckBox m_cbCloseWhenReady;
	
	CObjWnds m_ObjWnds;		// Liste der Recherchefenster
	CObjWnds::const_iterator m_itcurr;	// aktuelles Recherchefenster

	HWND m_hORWnd;			// TargetORFenster
	SELECTMODE m_rgMode;

	HWND m_hORWndToClose;
	bool m_fCloseWhenReady;
	bool m_fDisableCloseWhenReady;
	bool m_fAllowForOneObjectSelection;
	HWND m_hWndToIgnore;
		
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
			LPCSTR pcCaption, HWND hWndToIgnore);
	bool FInit (void);
	
public:
// Destruktor/Initialisierung
		~CSelectObjWndDlg (void);
		
static CSelectObjWndDlg *CreateInstance (CSelObjWndPropAct *pParent, 
	ResID uiDlg, LPCSTR pcCaption, HWND hWndToIgnore);

	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }

// Fragt den Dialog nach seinen Daten 
	HRESULT GetEnumLONG (IEnum<LONG> **ppEnum);

	void SetHWND (HWND hORWnd) { m_hORWnd = hORWnd; }
	
	void SetMode (SELECTMODE rgMode) { m_rgMode = rgMode; }
	SELECTMODE GetMode() { return m_rgMode; }

	void SetCloseWhenReady (bool fCloseWhenReady) 
	{ m_fCloseWhenReady = fCloseWhenReady; }
	bool GetCloseWhenReady() 
	{ return m_fCloseWhenReady; }
	void SetDisableCloseWhenReady (bool fDisableCloseWhenReady) 
	{ m_fDisableCloseWhenReady = fDisableCloseWhenReady; }
	void SetAllowForOneObjectSelection (bool fAllowForOneObjectSelection) 
	{ m_fAllowForOneObjectSelection = fAllowForOneObjectSelection; }

	void SetDirty (bool fDirty = true);
	int GetCountSelected() { return m_ObjWnds.size(); }

	HPROPSHEETPAGE CreatePage() { return CPropertyPage::CreatePage(); }
};

///////////////////////////////////////////////////////////////////////////////
// Füllen des Enums mit Objekten eines Fensters
bool FillTrees (SELECTMODE rgMode, HWND hORWnd, IEnum<LONG> *pIEnum);

#endif // _SELOBDLG_HXX

