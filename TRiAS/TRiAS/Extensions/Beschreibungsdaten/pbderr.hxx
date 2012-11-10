// Dialogfenster, welches hochkommt, wenn PBDFehler gemeldet werden
// File: PBDERR.HXX

#if !defined(_PBDERR_HXX)
#define _PBDERR_HXX

class CPbdError : public DialogWindow {
private:
	PushButton m_DefineButton, m_IgnoreButton;
	PushButton m_pbSelectPbd;
#if !defined(WIN32)
	PushButton m_HelpButton;
#endif // !WIN32
	BitmapBox m_PLogo;
	class CHelpTextX *m_pMessage;

protected:
	void ButtonClick (ControlEvt);
#if defined(WIN32)
	void HelpRequest (HelpRequestEvt e);
#endif // WIN32

public:
		CPbdError (pWindow pW, ResourceFile &RF, ResID res);
		~CPbdError (void);
		
	bool Init (void);
};

#endif 	// _PBDERR_HXX
