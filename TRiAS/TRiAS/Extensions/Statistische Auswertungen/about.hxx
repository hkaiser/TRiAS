// Klasse fÅr AboutBox --------------------------------------------------------
// File: ABOUT.HXX

#if !defined(_ABOUT_HXX)
#define _ABOUT_HXX

#if !defined(NOABOUT)
class AboutBox : public DialogWindow {
protected:
	void ButtonClick (ControlEvt) { EndDlg (); }

public:
	AboutBox (pWindow pW, ResID res) : DialogWindow (pW, res) {}
};
#endif // NOABOUT

#endif // _ABOUT_HXX

