// Dialogfenster, welches hochkommt, wenn WC_NOIDENT gemeldet wird
// File: DEFIDERR.HXX

#if !defined(_DEFIDERR_HXX)
#define _DEFIDERR_HXX

class DefIdentError : public DialogWindow {
private:
	PushButton DefineButton, IgnoreButton;
	PushButton CIgnoreButton;
#if !defined(WIN32)
	PushButton HelpButton;
#endif // !WIN32
	class CHelpTextX *m_pMessage;
	BitmapBox m_ILogo;
	
	long _Ident;

protected:
	void ButtonClick (ControlEvt);
#if defined(WIN32)
	void HelpRequest (HelpRequestEvt e);
#endif // WIN32

public:
		DefIdentError (pWindow pW, ResourceFile &RF, ResID res, long Id);
		~DefIdentError (void);
};

#endif 	// _DEFIDERR_HXX
