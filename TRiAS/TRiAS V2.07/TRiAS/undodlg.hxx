// Dialogfenster zur Auswahl mehrer Undo/Redo's -------------------------------
// File: UNDODLG.HXX

#if !defined(_UNDODLG_HXX)
#define _UNDODLG_HXX

class CUndoRedoListBox : public ControlWindow {
protected:
	void MouseButtonDn (MouseEvt);
	void MouseDrag (MouseEvt);

	void HandleMouseEvt (MouseEvt);
	int CalcIndex (CoOrd Y);

public:
		CUndoRedoListBox (DialogWindow *pDlg, ResID uiRes);
		~CUndoRedoListBox (void);

	MultiSelListBox * GetLB (void) { return (MultiSelListBox *)GetControl(); }
	bool isValid (void) { return GetControl() != NULL; }
        HWND GetHandle (void) { return (HWND)GetControl() -> Handle (API_CONTROL_HCONTROL); }
};

class CUndoRedoDlg : public DialogWindow {
private:
#if !defined(WIN32)
	PushButton m_pbHelp;
#endif // WIN32
	CUndoRedoListBox m_mslbUndoRedos;

	string m_strPrefix;
	string m_strOneAction;
	string m_strActions;

	LPENUMUNKNOWN m_pIUndoRedos;
	int m_iActIndex;
	unsigned int m_fUndo : 1;

	void AdjustCaption (int iIndex);

protected:
	void ButtonClick (ControlEvt e);
	long Dispatch (Event e);

public:
		CUndoRedoDlg (pWindow pW, bool fUndo);
		~CUndoRedoDlg (void);

	bool FInit (LPENUMUNKNOWN pIUndoRedos);

static CUndoRedoDlg *CreateInstance (pWindow pW, LPENUMUNKNOWN pIUndoRedos, bool fUndo);
};

#endif // _UNDODLG_HXX
