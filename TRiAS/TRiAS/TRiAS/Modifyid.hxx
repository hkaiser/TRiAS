// Auswahl aller Objekte verschiedener Objektklassen --------------------------
// File: MODIFYID.HXX

#if !defined(_MODIFYID_HXX)
#define _MODIFYID_HXX

#include <selidlvc.hxx>
#include <helptext.hxx>

class CModifyIdentDlg : public DialogWindow 
{
private:
	PushButton m_pbOK;
	PushButton m_pbCancel;
	PushButton m_pbSelAll;
	ComboBox m_cbNewId;
	CSelIdentListView *m_pIdents;
	CHelpText *m_pHelpText;
		
	short m_iIdBase;
	char *m_pBuff;
	long m_lNewIdent;
		
	void AdjustOK (bool fIndex = TRUE);
	long GetIdent (ComboBox *pCB, bool fEdit);
	
protected:
	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);
	void EditFocusChg (EditFocusChgEvt e);	// für ComboBoxen
	void EditChange (ControlEvt e);
	void OnItemChanged (NotifyEvt);			// ListView
	void HelpRequest(HelpRequestEvt);		// Help gefordert
	void OnDeleteItem (NotifyEvt);
	void OnDeleteAllItems (NotifyEvt);
	
public:
// Konstruktor/Destruktor/Initialisierung
		CModifyIdentDlg (pWindow);
		~CModifyIdentDlg (void);
		
	bool FInit (void);
	
static CModifyIdentDlg *CreateInstance (pWindow pW);

// ZugriffsFunktionen auf ausgewählte Identifikatoren
	bool GetFirstIdent (long &rlIdent, short &riOTyp);
	bool GetNextIdent (long &rlIdent, short &riOTyp);
	long GetNewIdent (void) { return m_lNewIdent; }

friend	bool FillNewIdents (ComboBox &rCB, CHelpText *, short iIdBase, char *pBuff);
};

#endif // _MODIFYID_HXX

