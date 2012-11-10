// Auswahl aller Objekte verschiedener Objektklassen --------------------------
// File: SELIDENT.HXX

#if !defined(_SELIDENT_HXX)
#define _SELIDENT_HXX

class CSelIdentList;
class CSelectIdentDlg : public DialogWindow 
{
protected:
	PushButton m_pbOK;

private:
#if !defined(WIN32)
	PushButton m_pbHelp;
#endif // WIN32
	PushButton m_pbSelAll;
	class CSelIdentList *m_pIdents;
	
protected:
	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);
	
virtual	void AdjustOK (void);

public:
// Konstruktor/Destruktor/Initialisierung
		CSelectIdentDlg (pWindow, uint);
		~CSelectIdentDlg (void);
		
	bool FInit (uint);
	
static CSelectIdentDlg *CreateInstance (pWindow pW, uint uiDlg, uint uiList);

// ZugriffsFunktionen auf ausgewählte Identifikatoren
	bool GetFirstIdent (long &rlIdent, short &riOTyp);
	bool GetNextIdent (long &rlIdent, short &riOTyp);

// InitialisierungsFuntkion zur anfänglichen Selektion einzelner Einträge
	bool SelectIdent (long lIdent, short iOTyp, bool fSel = TRUE);
};

#if defined(WIN32)

class CCopyVisInfoDlg : public CSelectIdentDlg {
private:
	RadioButton m_rbDefaultView;
	RadioButton m_rbOtherView;
	ComboBox m_cbViewNames;

protected:
	void ButtonClick (ControlEvt);
	
	void AdjustOK (void);

public:
		CCopyVisInfoDlg (pWindow, uint);
		~CCopyVisInfoDlg (void);

	bool FInit (uint);

static CCopyVisInfoDlg *CreateInstance (pWindow pW, uint uiDlg, uint uiList);

	bool GetViewName (char *pView, int iLen);
	bool isDefaultView (void) { return m_rbDefaultView.GetState(); }
};

#endif // WIN32

#endif // _SELIDENT_HXX

