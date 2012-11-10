// Definieren, Modifizieren und loeschen von MCodes in der PBD ----------------
// File: NEWMCODE.HXX

#if !defined(_NEWMCODE_HXX)
#define _NEWMCODE_HXX

#define TEXTLEN	_MAX_PATH

// neudefinieren und modifizieren eines Idents in der PBD ---------------------
class NewMCodeDlg : 
	public DialogWindow 
{
private:
	PushButton OKButton, CancelButton;
	PushButton SelectNewBttn;
	ListBox MCodeList;
	ComboBox m_cbSelObjClass;

	long _MCode;
	long _lActIdent;
	short m_iMkBase;
	bool m_fCorrected;		// mind. einer wurde geändert
		
	bool AdjustOK (void);

protected:
	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);
	void ListBoxClk (ControlEvt);
	void HelpRequest (HelpRequestEvt e);

	long GetModMCode (LPSTR pBuffer, int iLen);
	void CorrectMCode (long lMCode, bool fNewEntry);
	void HandleExistingMCode (void);
	void HandleNewMCode (void);
	void BuildList (LONG lIdent);

public:
		NewMCodeDlg (pWindow, ResID, short iMkBase);
		~NewMCodeDlg (void);

	long GetMCode (void) { return _MCode; }
};

// Löschen eines oder mehrer MCodes aus der PBD -------------------------------
enum MKItemStatus {
	MKI_InValid,
	MKI_Valid,
	MKI_Deleted,
	MKI_Restored,
};

class MKItem {
protected:
	long _MCode;
	char *_pKText;
	MKItemStatus _Status;

public:
		MKItem (long MCode, char *pKText);
		~MKItem (void);

	long MCode (void) { return _MCode; }
	char *GetKurzText (void) { return _pKText; }
	MKItemStatus &Status (void) { return _Status; }

friend void *GetLongKey (void *pObj);
friend int CmpLongKey (void *pObj1, void *pObj2);
};


class MKList : public CTree {
protected:
	void UserDelete (void *);
	CTable locTab;

public:
		MKList (void);
		~MKList (void) { EveryDelete(); }

	CTable &Tab (void) { return locTab; }
	bool hasDeleted (void);
	void MarkDeleted (long Id);
};
DeclareLock (MKList, MKItem);


class DelMCodeDlg : public DialogWindow {
private:
	PushButton OKButton;
	PushButton CancelBttn;
	PushButton m_pbSelAll;
	MultiSelListBox MCodeList;
	ComboBox m_cbSelObjClass;

	MKList *_pMCodes;
	short m_iMkBase;
	bool m_fMCodesFilled;
	long _lActIdent;

public:
	typedef set<long, less<long> > MCodeSet;

private:
	MCodeSet m_setMCodes;

protected:
	void ButtonClick (ControlEvt);	
	void ListBoxSel (ControlEvt);
	void HelpRequest (HelpRequestEvt e);

	bool isMCodeUsed (long MCode);
	MKList &MCodes (void) { return *_pMCodes; }

public:
		DelMCodeDlg (pWindow, ResID, short);
		~DelMCodeDlg (void);

	long NextMCode (bool iFirst = FALSE);
	long FirstMCode (void) 		// Iteration der zu löschenden Idents
		{ return NextMCode (TRUE); }

	void BuildList (bool = true);
	void FillMCodes (long lIdent);
	bool DeleteMCodes (void);
	bool DelMKList(void);
	long &ActiveID (void) { return _lActIdent; }
};


#endif 	// _NEWMCODE_HXX


