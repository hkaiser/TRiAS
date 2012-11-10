// Definieren, Modifizieren und loeschen von RCodes in der PBD ----------------
// File: NEWRCODE.HXX

#if !defined(_NEWRCODE_HXX)
#define _NEWRCODE_HXX

#define TEXTLEN	_MAX_PATH

// neudefinieren und modifizieren eines Idents in der PBD ---------------------
class NewRCodeDlg : public DialogWindow {
private:
	PushButton OKButton, CancelButton;
#if !defined(WIN32)
	PushButton HelpButton;
#endif // !WIN32
	NumEditX ModRCode;
	ListBox RCodeList;

	long m_lRCode;
	bool m_fCorrected;		// mind. einer wurde geändert

	bool AdjustOK (void);

protected:
	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);
	void ListBoxClk (ControlEvt);
	void EditChange (ControlEvt);
#if defined(WIN32)
	void HelpRequest (HelpRequestEvt e);
#endif

	long GetModRCode (void);
	void CorrectRCode (long lRCode);
	void HandleNewRCode (void);

public:
		NewRCodeDlg (pWindow, ResID);
		~NewRCodeDlg (void) {}

	long GetRCode (void) { return m_lRCode; }
};

// Löschen eines oder mehrer Idents aus der PBD -------------------------------
enum RCItemStatus {
	IDR_InValid,
	IDR_Valid,
	IDR_Deleted,
	IDR_Restored,
};

class RCItem {
protected:
	long m_lRCode;
	char *m_pKText;
	RCItemStatus m_Status;

public:
		RCItem (long lRCode, char *pKText);
		~RCItem (void);

	long FRCode (void) { return m_lRCode; }
	char *GetKurzText (void) { return m_pKText; }
	RCItemStatus &Status (void) { return m_Status; }

friend void *GetLongKey (void *pObj);
friend int CmpLongKey (void *pObj1, void *pObj2);
};


class RCList : public CTree {
protected:
	void UserDelete (void *);
	CTable locTab;

public:
		RCList (void);
		~RCList (void) { EveryDelete(); }

	CTable &Tab (void) { return locTab; }
	bool hasDeleted (void);
	void MarkDeleted (long lRCode);
};
DeclareLock (RCList, RCItem);


class DelRCodeDlg : public DialogWindow {
private:
	PushButton OKButton;
#if !defined(WIN32)
	PushButton HelpButton, RestoreButton, DeleteButton;
#endif // !WIN32
	MultiSelListBox RCodeList;
	CheckBox UnusedRCs;

	RCList *m_pRCodes;

protected:
	void ButtonClick (ControlEvt);	
	void ListBoxSel (ControlEvt);
#if defined(WIN32)
	void HelpRequest (HelpRequestEvt e);
#endif

	Bool isUsedRC (long lRCode);
	RCList &RCodes (void) { return *m_pRCodes; }

public:
		DelRCodeDlg (pWindow, ResID);
		~DelRCodeDlg (void);

	long NextRCode (bool iFirst = FALSE);
	long FirstRCode (void) 		// Iteration der zu löschenden RCode
		{ return NextRCode (TRUE); }

	void BuildList (bool = FALSE);
	bool DeleteRCodes (void);
	void RestoreRCodes (void);
};

#endif 	// _NEWRCODE_HXX


