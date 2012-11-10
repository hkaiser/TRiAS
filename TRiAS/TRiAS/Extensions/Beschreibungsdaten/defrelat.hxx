// Dialogfenster zur Definitition einer RelationsBeschreibung in einer PBD
// File: DEFRELAT.HXX

#if !defined(_DEFRELAT_HXX)
#define _DEFRELAT_HXX

class CDefineRelationDlg : public DialogWindow {
private:
	FixedText m_EDRelation;
	SingleLineEdit m_EDKurzText;
	MultiLineEdit m_EDLangText;
	PushButton m_OKButton, m_CancelButton;
#if !defined(WIN32)
	PushButton m_HelpButton;
#endif // !WIN32
	FixedText m_PBDName;
	RadioButton m_RHorizRel, m_RKomplexRel;
	long m_lActRel;
	Bool m_fIsValid;

protected:
	void ButtonClick (ControlEvt);
#if defined(WIN32)
	void HelpRequest (HelpRequestEvt e);
#endif // WIN32

public:
		CDefineRelationDlg (pWindow, ResID, long);
		~CDefineRelationDlg (void) {}
};


#endif 	// _DEFRELAT_HXX
