// Auswahl aller Objekte verschiedener Objektklassen --------------------------
// File: SELECTID.HXX

#if !defined(_SELECTID_HXX)
#define _SELECTID_HXX

#include <selidlvc.hxx>

class CSelectIdentDlg : 
	public DialogWindow 
{
protected:
	PushButton m_pbOK;

private:
	PushButton m_pbSelAll;
	CSelIdentListViewWindow *m_pIdents;
	
protected:
	void ButtonClick (ControlEvt);
	void OnItemChanged (NotifyEvt);		// ListView
	void HelpRequest(HelpRequestEvt);	// Help gefordert
	void OnDeleteItem (NotifyEvt);
	void OnDeleteAllItems (NotifyEvt);

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
	UINT GetNoSelected (void) { return (*m_pIdents)->GetSelectedCount(); }

// InitialisierungsFuntkion zur anfänglichen Selektion einzelner Einträge
	bool SelectIdent (long lIdent, short iOTyp, bool fSel = TRUE);
};

class CCopyVisInfoDlg : 
	public CSelectIdentDlg 
{
private:
	RadioButton m_rbDefaultView;
	RadioButton m_rbOtherView;
	ComboBox m_cbViewNames;

protected:
	void ButtonClick (ControlEvt);
	void HelpRequest (HelpRequestEvt);
	void ListBoxSel (ControlEvt);

	void AdjustOK (void);

public:
		CCopyVisInfoDlg (pWindow, uint);
		~CCopyVisInfoDlg (void);

	bool FInit (uint);

static CCopyVisInfoDlg *CreateInstance (pWindow pW, uint uiDlg, uint uiList);

	bool GetViewName (char *pView, int iLen);
	bool isDefaultView (void) { return m_rbDefaultView.GetState(); }
};

#endif // _SELECTID_HXX

