// Dialogfenster, welches hochkommt, wenn WC_NORELATION gemeldet wird
// File: DEFRKERR.HXX

#if !defined(_DEFRKERR_HXX)
#define _DEFRKERR_HXX

class CDefRCodeError : public DialogWindow {
private:
	PushButton DefineButton, IgnoreButton;
	PushButton CIgnoreButton;
#if !defined(WIN32)
	PushButton HelpButton;
#endif // !WIN32
	class CHelpTextX *m_pMessage;
	BitmapBox m_RLogo;

	long m_lRCode;

protected:
	void ButtonClick (ControlEvt);
#if defined(WIN32)
	void HelpRequest (HelpRequestEvt e);
#endif // WIN32

public:
		CDefRCodeError (pWindow pW, ResourceFile &RF, ResID res, long lRCode);
		~CDefRCodeError (void);
};

#endif 	// _DEFRKERR_HXX
