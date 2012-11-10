// Dialogfenster, welches die Fehlerbehandlungsart abfragt --------------------
// File: VISERRDG.HXX


#if !defined(_VISERRDG_HXX)
#define _VISERRDG_HXX


class CVisErrorDlg : public DialogWindow {
private:
	ResourceFile &m_RF;
#if !defined(WIN32)
	PushButton m_HelpButton;
#endif //!WIN32
	PushButton m_DefineButton;
	FixedText m_Message;
	BitmapBox m_VLogo;
	
	long m_lIdent;
	short m_iVTyp;

protected:
	void ButtonClick (ControlEvt);

public:
	CVisErrorDlg (pWindow pW, ResourceFile &RF,
		      ResID res, long lIdent, short iVTyp);

	bool Init (void);
};


#endif // _VISERRDG_HXX

