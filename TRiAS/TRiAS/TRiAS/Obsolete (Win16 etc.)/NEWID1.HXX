// Modifikation des Identifikators
// File: NEWID.HXX

#if !defined(_NEWID_HXX)
#define _NEWID_HXX

class NewIdentDlg : public DialogWindow {
protected:
	PushButton OKButton;
	PushButton CancelButton;
	PushButton HelpButton;
	NumEdit NewId;
	NumEdit OldId;
	FixedText OldText;

	void ButtonClick (ControlEvt e);

	long _NewIdent;
	long _OldIdent;

public:
		NewIdentDlg (pWindow pW, long ON, long newId = -1L, 
			     const char *lpCaption = NULL, short iBase = 10);

	long GetNewIdent (void) { return _NewIdent; }
	long GetOldIdent (void) { return _OldIdent; }
};


#endif // _NEWID_HXX

