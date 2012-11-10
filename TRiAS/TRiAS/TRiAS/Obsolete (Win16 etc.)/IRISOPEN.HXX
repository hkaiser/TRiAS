// Dialogfensterklasse fÅr DB erîffnen 
// File: IRISOPEN.HXX

#if !defined(_IRISOPEN_HXX)
#define _IRISOPEN_HXX

// OpenDialogfenster 
class OpenDBDialog : public DialogWindow {
// Buttons
	PushButton	OKButton, CancelButton;
	CheckBox	ROCheckBox;
// FileListBoxes
	FileListBox	FileList;
// EditFenster
	SingleLineEdit	SLE_DBName, SLE_UserName, SLE_PassWord;

// Lokale Routinen
	void SelectFile (void);		// ListBox fÅllen

// EventHandler
	void ListBoxSel (ControlEvt);
	void ListBoxClk (ControlEvt);
	void ButtonClick (ControlEvt);

// Textfelder fÅr eingelesene Strings
	char _DBName[PATHLEN+1];
	char _UserName[USERLEN+1];
	char _PassWord[PASSWDLEN+1];
	Bool _ReadOnlyFlag;

public:
// Konstruktor (Initialisierung des Dialogfensters)
	OpenDBDialog (pWindow);

// Memberfunktionen
	char *GetFileSpec (char *pc = NULL, short = 0) const;	// liefert FileNamen
	char *GetUserName (char *pc = NULL, short = 0) const;	// liefert UserNamen
	char *GetPassWord (char *pc = NULL, short = 0) const;	// liefert Password
	Bool GetROMode (void) { return _ReadOnlyFlag; }
};

#endif // _IRISOPEN_HXX
