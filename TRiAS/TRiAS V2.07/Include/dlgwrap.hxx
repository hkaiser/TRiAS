// DialogWrapper, der eine Message rumschickt, wenn er erzeugt und zerlegt wird
// File: DLGWRAP.HXX

#if !defined(_DLGWRAP_HXX)
#define _DLGWRAP_HXX

class CWrapperDialog : public DialogWindow {
private:
	bool m_fSend;

public:
	CWrapperDialog (pWindow pW, ResID rscID, 
			bool fModal = true, bool fSend = true)
		: DialogWindow (pW, rscID, fModal)
	{
		m_fSend = fSend;
		if (fSend) DEXN_DialogBegin (Handle(API_WINDOW_HWND));
	}
	~CWrapperDialog (void)
	{
		if (m_fSend) DEXN_DialogEnd (Handle(API_WINDOW_HWND));
	}
};

#endif // _DLGWRAP_HXX

