// Dialogfenster, welches hochkommt, wenn WC_NOMERKMAL gemeldet wird
// File: DEFMKERR.HXX

#if !defined(_DEFMKERR_HXX)
#define _DEFMKERR_HXX

class DefMCodeError : public DialogWindow {
private:
	PushButton DefineButton, IgnoreButton;
	PushButton CIgnoreButton;
#if !defined(WIN32)
	PushButton HelpButton;
#endif // !WIN32
	class CHelpTextX *m_pMessage;
	BitmapBox m_MLogo;

	long _MCode;

protected:
	void ButtonClick (ControlEvt);
#if defined(WIN32)
	void HelpRequest (HelpRequestEvt e);
#endif // WIN32

public:
		DefMCodeError (pWindow pW, ResourceFile &RF, ResID res, 
			       long MCode, short iMkBase);
		~DefMCodeError (void);
};

#endif 	// _DEFMKERR_HXX
