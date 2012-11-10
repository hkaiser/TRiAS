// Auswahl aller Objekte verschiedener Objektklassen --------------------------
// File: MODIDENT.HXX


#if !defined(_MODIDENT_HXX)
#define _MODIDENT_HXX

class CHelpText;
class CSelIdentList;
class CModifyIdentDlg : public DialogWindow 
{
private:
	PushButton m_pbOK;
#if !defined(WIN32)
	PushButton m_pbHelp;
#endif // WIN32
	PushButton m_pbCancel;
	ComboBox m_cbNewId;
	class CSelIdentList *m_pIdents;
	class CHelpText *m_pHelpText;
		
	short m_iIdBase;
	char *m_pBuff;
	long m_lNewIdent;
		
	void AdjustOK (BOOL fIndex = TRUE);
	long GetIdent (ComboBox *pCB, BOOL fEdit);
	
protected:
	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);
	void EditFocusChg (EditFocusChgEvt e);	// für ComboBoxen
	void EditChange (ControlEvt e);
	
public:
// Konstruktor/Destruktor/Initialisierung
		CModifyIdentDlg (pWindow);
		~CModifyIdentDlg (void);
		
	BOOL FInit (void);
	
static CModifyIdentDlg *CreateInstance (pWindow pW);

// ZugriffsFunktionen auf ausgewählte Identifikatoren
	BOOL GetFirstIdent (long &rlIdent, short &riOTyp);
	BOOL GetNextIdent (long &rlIdent, short &riOTyp);
	long GetNewIdent (void) { return m_lNewIdent; }

friend	BOOL FillNewIdents (ComboBox &rCB, CHelpText *, short iIdBase, char *pBuff);
};


#endif // _SELIDENT_HXX

