// Definieren, Modifizieren und loeschen von Idents in der PBD ----------------
// File: NEWIDENT.HXX

#if !defined(_NEWIDENT_HXX)
#define _NEWIDENT_HXX

#define TEXTLEN	_MAX_PATH

// neudefinieren und modifizieren eines Idents in der PBD 
class NewIdentDlg : 
	public DialogWindow 
{
private:
	PushButton OKButton, CancelButton;
	PushButton NewEntryBttn;
	ListBox IdentList;

	long _Ident;
	bool m_fCorrected;

	bool AdjustOK (void);

protected:
	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);
	void ListBoxClk (ControlEvt);
	void HelpRequest (HelpRequestEvt e);

	long GetModIdent (char *pBuffer, int iLen);
	void CorrectIdent (long lIdent, bool fNewEntry);
	void HandleNewIdent (void);
	void HandleExistingIdent (void);
	int FindEntryInList (long lIdent);

public:
		NewIdentDlg (pWindow, ResID);
		~NewIdentDlg (void);

	long GetIdent (void) { return _Ident; }
};

// Löschen eines oder mehrer Idents aus der PBD -------------------------------
enum IDItemStatus {
	IDI_InValid,
	IDI_Valid,
	IDI_Deleted,
	IDI_Restored,
};

class IDItem {
protected:
	long _Ident;
	char *_pKText;
	IDItemStatus _Status;

public:
		IDItem (long Ident, char *pKText);
		~IDItem (void);

	long Id (void) { return _Ident; }
	char *GetKurzText (void) { return _pKText; }
	IDItemStatus &Status (void) { return _Status; }

friend void *GetLongKey (void *pObj);
friend int CmpLongKey (void *pObj1, void *pObj2);
};


class IDList : public CTree {
protected:
	void UserDelete (void *);
	CTable locTab;

public:
		IDList (void);
		~IDList (void) { EveryDelete(); }

	CTable &Tab (void) { return locTab; }
	bool hasDeleted (void);
	void MarkDeleted (long Id);
};
DeclareLock (IDList, IDItem);


class DelIdentDlg : 
	public DialogWindow 
{
private:
	PushButton OKButton;
	PushButton m_pbSelAll;
	MultiSelListBox IdentList;

	IDList *_pIdents;

protected:
	void ButtonClick (ControlEvt);	
	void ListBoxSel (ControlEvt);
	void HelpRequest (HelpRequestEvt e);

	Bool isUsedID (long ID);
	IDList &Idents (void) { return *_pIdents; }

public:
		DelIdentDlg (pWindow, ResID);
		~DelIdentDlg (void);

	long NextIdent (Bool iFirst = FALSE);
	long FirstIdent (void) 		// Iteration der zu löschenden Idents
		{ return NextIdent (TRUE); }

	void BuildList (bool = true);
	bool DeleteIdents (void);
};


#endif 	// _NEWIDENT_HXX


