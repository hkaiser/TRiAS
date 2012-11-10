// Klassendefinition für eine Listbox, die CheckBoxes enthält -----------------
// File: CHECKTREEVIEW.H

#if !defined(CHECKTREEVIEW_H)
#define CHECKTREEVIEW_H

class CCheckTreeView : 
	public ControlWindow
{
private:
	HWND GetHandle (void) { return GetControl() -> Handle(); }

public:
	_TRIAS03_ENTRY CCheckTreeView (pDialogWindow pDW, ResID rsc, bool fUseCheckMarks = true, bool fUsePartialCheckMarks = false);
	_TRIAS03_ENTRY ~CCheckTreeView (void);


_TRIAS03_ENTRY bool FInit(void);
_TRIAS03_ENTRY bool ToggleCheckMark (HTREEITEM hItem);
_TRIAS03_ENTRY void HideStateImage (HTREEITEM hItem);
_TRIAS03_ENTRY UINT GetCheckState (HTREEITEM hItem);
_TRIAS03_ENTRY void SetCheckState (HTREEITEM hItem, UINT uiState, bool fPropagateUp = true, bool fPropagateDown = true);

_TRIAS03_ENTRY HTREEITEM FindString (LPCSTR pcItem);

// Wrapper für direktZugriff auf TreeCtrl
	CTreeViewCtrl *GetTree() { return (CTreeViewCtrl *)GetControl(); }
	CTreeViewCtrl *operator-> () { return GetTree(); }

	bool GetItem (TV_ITEM *pItem) { return GetTree()->GetItem(pItem); }
	bool SetItem (const TV_ITEM *pItem) { return GetTree()->SetItem(pItem); }
	bool DeleteAllItems (void) { return GetTree()->DeleteAllItems(); }
	HTREEITEM HitTest (Point pt, UINT *pFlags = NULL) { return GetTree()->HitTest(pt, pFlags); }
	HTREEITEM HitTest (TV_HITTESTINFO *pHitTestInfo) { return GetTree()->HitTest (pHitTestInfo); }
	bool DeleteItem (HTREEITEM hItem) { return GetTree()->DeleteItem(hItem); }

	HTREEITEM InsertItem (LPCSTR lpszItem, int nImage, int nSelectedImage,
			HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST)
		{ return GetTree()->InsertItem (lpszItem, nImage, nSelectedImage, hParent, hInsertAfter); }
	HTREEITEM InsertItem (LPCSTR lpszItem, HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST)
		{ return GetTree()->InsertItem(lpszItem, hParent, hInsertAfter); }

	HTREEITEM SelectItem (HTREEITEM hItem) { return GetTree()->SelectItem(hItem); }
	HTREEITEM SelectSetFirstVisible (HTREEITEM hItem) { return GetTree() -> SelectSetFirstVisible(hItem); }

	CImageList *SetImageList (CImageList *pImageList, int nImageListType)
		{ return GetTree()->SetImageList (pImageList, nImageListType); }

	HTREEITEM GetNextItem (HTREEITEM hItem, UINT nCode)	{ return GetTree()->GetNextItem (hItem, nCode); }
	HTREEITEM GetChildItem (HTREEITEM hItem) { return GetTree()->GetChildItem (hItem); }
	string GetItemText (HTREEITEM hItem) { return GetTree()->GetItemText (hItem); }
	HTREEITEM GetSelectedItem (void) { return GetTree()->GetSelectedItem(); }
	HTREEITEM GetParentItem(HTREEITEM hItem) { return GetTree() -> GetParentItem(hItem); }

	bool ItemHasChildren (HTREEITEM hItem) { return GetTree()->ItemHasChildren (hItem); }
	UINT GetItemState (HTREEITEM hItem, UINT nStateMask) { return GetTree()->GetItemState (hItem, nStateMask); }
	bool SetItemImage (HTREEITEM hItem, int nImage, int nSelectedImage)
		{ return GetTree()->SetItemImage (hItem, nImage, nSelectedImage); }
	bool Expand (HTREEITEM hItem, UINT nCode) { return GetTree()->Expand (hItem, nCode); }
	bool EnsureVisible (HTREEITEM hItem) { return GetTree()->EnsureVisible (hItem); } 

	bool UseCheckMarks() { return m_fUseCheckMarks; }
	bool UsePartialCheckMarks() { return m_fUsePartialCheckMarks; }

protected:
	void HandleCheckMark(Point point, UINT uiMsg);
	void NotifyChecked (HTREEITEM hNewTarget, UINT uiMsg, UINT uiCheckState);
	UINT ChangingCheckState (HTREEITEM hNewTarget, UINT uiMsg);
	HTREEITEM FindItem (HTREEITEM hItem , LPCSTR pcItem);

	UINT CalcParentCheckState (HTREEITEM hItem);

// EventHandler
	void MouseButtonDn (MouseEvt e);
	void MouseButtonDblClk (MouseEvt e);
	
private:
	CImageList m_CheckMarks;
	bool m_fUseCheckMarks;
	bool m_fUsePartialCheckMarks;
};

/////////////////////////////////////////////////////////////////////////////
// special support for CheckBox's in TreeCtrl's
#define TV_CHECK_NOCHANGE	(UINT)(-1)
#define TV_CHECK_NOMARK		(INDEXTOSTATEIMAGEMASK(0))
#define TV_CHECK_OFF		(INDEXTOSTATEIMAGEMASK(1))
#define TV_CHECK_ON			(INDEXTOSTATEIMAGEMASK(2))
#define TV_CHECK_PASSIVE	(INDEXTOSTATEIMAGEMASK(3))
#define TV_CHECK_PARTIAL_ON	(INDEXTOSTATEIMAGEMASK(4))

#define TVN_CHECKSTATECHANGED	(WM_USER+4321)
#define TVN_CHANGINGCHECKSTATE	(WM_USER+4322)

typedef struct tagNMTREEVIEWCHECK {
    NMHDR hdr;
    UINT action;
    HTREEITEM hItem;
	UINT state;
} NM_TREEVIEWCHECK;

#endif // CHECKTREEVIEW_H
