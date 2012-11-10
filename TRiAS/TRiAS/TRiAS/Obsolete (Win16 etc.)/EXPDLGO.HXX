// Dialogbox fuer Auswahl des Exportformates und des Exportdateinamens
// File: EXPDLG.HXX

#if !defined(_EXPDLG_HXX)
#define _EXPDLG_HXX

#define FULLPATHSIZE	_MAX_PATH

// Struktur zur Beschreibung der Filter
typedef struct tagFILTERINFO {
	char *FilterName;	// Bezeichnung des ExportFilters
	char *DLLName;		// Name der FilterDLL
	char *ShortName;	// Kürzel für Namen der DLL Funktionen
	char *FilterExt;	// StandardExtension der Ausgabedatei
} FILTERINFO;

// Dialogbox ------------------------------------------------------------------
class ExportDlg : public DialogWindow {
private:	// Controls
	PushButton OKButton, CancelButton, HelpButton;
	PushButton TransformButton;
	RadioButton OverWriteRButton, ConcatinateRButton;
	ComboBox CBFormats;
	ComboBox CBSights;
	FileListBox LBFiles;
	SingleLineEdit SLEFileName;
	CheckBox CBPosition;

	FILTERINFO *_FilterInfo;
	char _FileName[FULLPATHSIZE+1];
	OutMode _OverWriteFlag;
	short _numFilters;
	Bool _iPos;

	char CurrSight[80];	// ausgewählte Sicht

protected:
	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);
	void ListBoxClk (ControlEvt);

public:
// Konstruktor
		ExportDlg (pWindow pW);

// Memberfunktionen
	ErrCode ReadFormats (void);
	char *GetFileSpec (char *cptr = NULL, short len = 0);
	char *GetDLLName (char *cptr = NULL, short len = 0);
	char *GetShortName (char *cptr = NULL, short len = 0);
	char *GetSight (char *cptr = NULL, short len = 0);
	OutMode OMFlag (void) const { return _OverWriteFlag; };
	void SelectFile (Bool = FALSE);
	Bool ExportPosition (void) { return _iPos; }

// Destruktor
		~ExportDlg (void);
};

#endif	// _EXPDLG_HXX

