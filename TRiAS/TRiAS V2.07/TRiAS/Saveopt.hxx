// DialogFenster zur Einstellung der Speicheroptionen -------------------------
// File: SAVEOPT.HXX

#if !defined(_SAVEOPT_HXX)
#define _SAVEOPT_HXX

class CSaveOptionsDlg : public DialogWindow {
private:
#if !defined(WIN32)
	PushButton m_pbHelp;
#endif // WIN32
	SpinControl m_scMinutes;
	CheckBox m_cbAutoSave;
	CheckBox m_cbAutoUpdate;
	CheckBox m_cbAutoUpdateClose;
	CheckBox m_cbAutoRecovery;

	short m_iMinutes;
			
protected:
	void VertScroll (ScrollEvt);
	void ButtonClick (ControlEvt);	
	void EditFocusChg (EditFocusChgEvt);
	
public:
		CSaveOptionsDlg (pWindow);
		~CSaveOptionsDlg (void);

	BOOL Init (void);

static CSaveOptionsDlg *CreateInstance (pWindow pW);

	short SaveDelta (void) { return m_iMinutes; }
};


#endif // _SAVEOPT_HXX


