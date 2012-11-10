// DialogBox fÅr Passwordeingabe
// File: PWDIALOG.HXX

#if !defined(_PWDIALOG_HXX)
#define _PWDIALOG_HXX

#if !defined(NOPWDDLG)
class PassWordDlg : public DialogWindow {
// Controls
	PushButton OKButton;
	SingleLineEdit SLE_PassWord;
	FixedText PwdPrompt;

// Feld fÅr eigelesenes Password
	char _PassWord[PASSWDLEN+1];

protected:
	void ButtonClick (ControlEvt);		// EventHandler

public:
// Konstruktor
		PassWordDlg (pWindow pW, uint Res);

// Member 
	char *GetPassWord (void) { return _PassWord; }
};
#endif // NOPWDDLG

#endif // _PWDIALOG_HXX
