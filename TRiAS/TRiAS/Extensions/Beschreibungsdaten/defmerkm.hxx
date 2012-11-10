// Dialogfenster zur Definitition einer MerkmalsBeschreibung in einer PBD
// File: DEFMERKM.HXX

#if !defined(_DEFMERKM_HXX)
#define _DEFMERKM_HXX

class DefineMerkmalDlg : 
	public DialogWindow 
{
private:
	SingleLineEdit EDKurzText;	// KurzText
	MultiLineEdit EDLangText;	// LangText
	PushButton OKButton, CancelButton;
	FixedText PBDName;			// Anzeige der Bezugsobjektklasse
	CheckBox m_cbSystemFlag;
	CheckBox m_cbReadOnly;

	RadioButton m_rbObject;
	RadioButton m_rbView;
	RadioButton m_rbClass;

	long _actMC;
	long _actID;
	int m_rgType;
	bool isValid;
	bool m_fIsSystem;
	bool m_fShowAdminDlg;

protected:
	void ButtonClick (ControlEvt);
	void HelpRequest (HelpRequestEvt e);
	void EditChange (ControlEvt e);

	void AdjustOK();
	void AdjustRadios (int rgType);

public:
		DefineMerkmalDlg (pWindow, ResID, long, long, LPCSTR, LPCSTR, bool fShowAdminDlg = false);
		~DefineMerkmalDlg (void) {}

	long GetMCode() { return _actMC; }		// evtl. modifizierter MCode
};

#endif 	// _DEFMERKM_HXX
