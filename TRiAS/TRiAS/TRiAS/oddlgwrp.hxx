// DialogWrapper, der eine Message rumschickt, wenn er erzeugt und zerlegt wird
// File: ODDLGWRP.HXX

#if !defined(_ODDLGWRP_HXX)
#define _ODDLGWRP_HXX

#if defined(WIN16)	// __CVNEW__

class OwnerDrawDialogWindow : public OwnerDrawDialogWindow {
private:
	bool m_fSend;

public:
	OwnerDrawDialogWindow (pWindow pW, ResID rscID, 
			bool fModal = true, bool fSend = true)
		: OwnerDrawDialogWindow (pW, rscID, fModal)
	{
		m_fSend = fSend;
		if (fSend) DEXN_DialogBegin (pW -> Handle(API_WINDOW_HWND));
	}
	~OwnerDrawDialogWindow (void)
	{
		if (m_fSend) DEXN_DialogEnd (pW -> Handle(API_WINDOW_HWND));
	}
};

#else

typedef DialogWindow OwnerDrawDialogWindow;

#endif // WIN16

#endif // _ODDLGWRP_HXX

