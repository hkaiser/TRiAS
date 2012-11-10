// Einstellen der anzuzeigenden ObjektInformationen nach Recherche ------------
// File RECHRES.HXX

#if !defined(_RECHRES_HXX)
#define _RECHRES_HXX

class CRechResultDlg : public DialogWindow {
private:
	ComboBox m_cmViews;		// Controls der DialogBox
	ComboBox m_cmObjProps;
	CheckBox m_cbObjNr;
	CheckBox m_cbIdent;
	CheckBox m_cb_ObjTyp;
	PushButton m_bHelp;
		
protected:
	void ButtonClick (ControlEvt);
	
	BOOL SaveResultsToView (void);	// Results wegschreiben

public:
		CRechResultDlg (pWindow);
		~CRechResultDlg (void);

	BOOL Init (void);		// Initialisierung
};

#endif // _RECHRES_HXX

