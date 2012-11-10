// Details für Undo/Redo (Debug only)
// File: UNDOREDODETAILS.H

#if !defined(_UNDOREDODETAILS_H)
#define _UNDOREDODETAILS_H

class CUndoRedoDetails :
	public DialogWindow 
{
private:
	CTreeViewCtrl m_tvDetails;
	CImageList m_ilDetails;
	bool m_fUndo;

protected:
	bool FillTree (IEnumUnknown *pIEnum, HTREEITEM hParent = TVI_ROOT);
	void AdjustImage (HTREEITEM hItem);

	void OnItemExpanded (NotifyEvt e);
	void ButtonClick (ControlEvt e);

public:
		CUndoRedoDetails (pWindow pW, IEnumUnknown *pIEnum, bool m_fUndo);
		~CUndoRedoDetails (void);
};

#endif // _UNDOREDODETAILS_H
