// Dialogfenster zur Einstellung der Darstellungsreihenfolge ------------------
// File: PRIORITY.HXX


#if !defined(_PRIORITY_HXX)
#define _PRIORITY_HXX

#if !defined(NOPRIORITYENTRY)
class PriorityEntry {
private:
	short m_Priority;
	long m_Ident;
	char *m_pMText;
	VisType m_iVTyp;

public:
		PriorityEntry (short Priority, long Ident, VisType iVTyp, 
							char *MText = NULL);
		~PriorityEntry (void);

	short &Priority (void) { return m_Priority; }
	long &Ident (void) { return m_Ident; }
	char *GetString (char *pBuff = NULL, short len = 0);
	VisType FVisTyp (void) { return m_iVTyp; }

friend void *EntryIdent (void *pObj);
};

#endif // NOPRIORITYENTRY

#if !defined(NOPRIORITYTREE)

class PriorityTree : public CTree {
protected:
	void UserDelete (void *pObj);

public:
		PriorityTree (void);
		~PriorityTree (void);
};
DeclareLock (PriorityTree, PriorityEntry);

#endif // NOPRIORITYTREE

class PriorityTree;

class PrioritySelDlg : public DialogWindow {
private:
	ListBox Priorities;
	PushButton OKButton, CancelButton, TestButton;
	SpinControl PrioritySel;
	Bool _newPriority;
	short _iOldIndex;
	CIdTree &_Idents;
	Bool iChanged;

protected:
	PriorityTree *pPT;
	PriorityTree *pPTRes;

	void ButtonClick (ControlEvt e);
	void ListBoxSel (ControlEvt e);
	void VertScroll (ScrollEvt e); 
	void EditFocusChg (EditFocusChgEvt e);

	short ApplyPriorities (Bool iRestore = FALSE);
	short ReInsertEntry (short iOldIndex);
	short doWork (void);

public:
		PrioritySelDlg (pWindow, CIdTree &);
		~PrioritySelDlg (void);

	Bool SpinHasChanged (void) { return _newPriority || PrioritySel.isModified(); }
	void SpinHasChanged (Bool iFlag) { _newPriority = iFlag; }
	short &OldIndex (void) { return _iOldIndex; }
	CIdTree &Idents (void) { return _Idents; }

friend bool EXPORTTRIAS FillWithPriorities (void *pObj, void *pData);
friend bool EXPORTTRIAS FillResPrioTree (void *pObj, void *pData);
};


#endif // _PRIORITY_HXX
