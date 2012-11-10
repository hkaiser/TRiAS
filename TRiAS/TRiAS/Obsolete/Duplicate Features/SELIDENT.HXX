// Auswahl aller Objekte verschiedener Objektklassen --------------------------
// File: SELIDENT.HXX

#if !defined(_SELIDENT_HXX)
#define _SELIDENT_HXX

class CSelIdentList;
class CSelectIdentDlg : public DialogWindow 
{
private:
	PushButton m_pbOK;
	PushButton m_pbHelp;
	PushButton m_pbSelAll;
	class CSelIdentList *m_pIdents;
	ComboBox m_cbFeatures;
	
	void AdjustOK (void);

protected:
	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);
	
	bool FillMerkmale (void);

public:
// Konstruktor/Destruktor/Initialisierung
		CSelectIdentDlg (pWindow, ResID);
		~CSelectIdentDlg (void);
		
	bool FInit (void);
	
static CSelectIdentDlg *CreateInstance (pWindow pW, ResID uiDlg);

// ZugriffsFunktionen auf ausgewählte Identifikatoren
	bool GetFirstIdent (long &rlIdent, short &riOTyp);
	bool GetNextIdent (long &rlIdent, short &riOTyp);
	ULONG GetMCode (void);
	
// InitialisierungsFuntkion zur anfänglichen Selektion einzelner Einträge
	bool SelectIdent (long lIdent, short iOTyp, BOOL fSel = TRUE);
};


#endif // _SELIDENT_HXX

