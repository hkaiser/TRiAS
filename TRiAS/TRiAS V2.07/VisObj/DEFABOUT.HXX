// Klasse fÅr AboutBox --------------------------------------------------------
// File: DEFABOUT.HXX

#if !defined(_DEFABOUT_HXX)
#define _DEFABOUT_HXX

#if !defined(NODEFABOUT)
class AboutBox : public DialogWindow {
protected:
	void ButtonClick (ControlEvt) { EndDlg (); }

public:
	AboutBox (pWindow pW, ResID res) : DialogWindow (pW, res) {}
};
#endif // NODEFABOUT

#endif // _DEFABOUT_HXX

