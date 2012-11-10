// Klassendefinition für eine Listbox, die CheckBoxes enthält -----------------
// File: CHECKTREEVIEW.CPP

#include "trias03p.hxx"
#include "trias03.h"

#include <containr.hxx>

#include <CheckTreeView.h>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern char g_pDLLName[_MAX_PATH];

// Konstruktoren --------------------------------------------------------------
CCheckTreeView::CCheckTreeView (pDialogWindow pDW, ResID rsc) 
	: ControlWindow (new CTreeViewCtrl (pDW, rsc))
{
	if (GetControl() == NULL)
		db_error (EC_NOMEMORY, RC_ctOwnerDrawListBox);
}

CCheckTreeView::~CCheckTreeView (void) 
{
CImageList *pIList = SetImageList (NULL, TVSIL_STATE);

	DELETE_OBJ (pIList);
	DeleteAllItems();
	if (GetTree()) delete GetTree();
}

bool CCheckTreeView::FInit (void)
{
	if (NULL == GetTree() || !GetTree()->FInit())
		return false;

UINT uiRes = IsWin40() ? IDB_CHECKMARKS_40 : IDB_CHECKMARKS_NT;
ResourceFile RF (g_pDLLName);

	if (!m_CheckMarks.CreateList (ResID(uiRes, &RF), 15, 0, RGB(255, 255, 255))) {
		TX_TRACE("Couldn't create state imagelist");
		return false;
	}

CImageList *pIList = SetImageList (&m_CheckMarks, TVSIL_STATE);

	DELETE_OBJ(pIList);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Memberfunktionen
bool CCheckTreeView::ToggleCheckMark (HTREEITEM hItem)
{
bool fWasOn = false;
TV_ITEM tvi;

	tvi.hItem = hItem;
	tvi.mask = TVIF_STATE;
	if (GetItem (&tvi)) {
		fWasOn = ((tvi.state & TVIS_STATEIMAGEMASK) == TV_CHECK_ON);
		tvi.state = (fWasOn ? TV_CHECK_OFF : TV_CHECK_ON);
		tvi.stateMask = TVIS_STATEIMAGEMASK;
		SetItem (&tvi);
	}
	return fWasOn;
}

void CCheckTreeView::HideStateImage (HTREEITEM hItem)
{
	SetCheckState (hItem, TV_CHECK_NOMARK);
}

UINT CCheckTreeView::GetCheckState (HTREEITEM hItem)
{
TV_ITEM tvi;

	tvi.hItem = hItem;
	tvi.mask = TVIF_STATE;
	if (GetItem (&tvi)) 
		return tvi.state & TVIS_STATEIMAGEMASK;
	return TV_CHECK_NOMARK;
}

void CCheckTreeView::SetCheckState (HTREEITEM hItem, UINT uiState)
{
TV_ITEM tvi;

	tvi.hItem = hItem;
	tvi.mask = TVIF_STATE;
	tvi.state = uiState;
	tvi.stateMask = TVIS_STATEIMAGEMASK;
	SetItem (&tvi);
}

HTREEITEM CCheckTreeView::FindItem (HTREEITEM hItem, LPCSTR pcItem)
{
	if (NULL == hItem) return NULL;

// wenn's das RootItem ist, dann erstes Child geben lassen
HTREEITEM hChildItem = NULL;

	if (TVI_ROOT == hItem)
		hChildItem = GetNextItem (NULL, TVGN_CHILD);
	else {
	// zuerst dieses Item testen (die Root kann's nicht sein)
	string strItem = GetItemText (hItem);

		if (strItem == pcItem)
			return hItem;

		hChildItem = GetChildItem (hItem);
	}

// anschließen alle Childs abtesten
	while (NULL != hChildItem) {
	HTREEITEM hReturn = FindItem (hChildItem, pcItem);

		if (NULL != hReturn)
			return hReturn;
		hChildItem = GetNextItem (hChildItem, TVGN_NEXT);
	}
	return NULL;	// nichts gefunden
}

HTREEITEM CCheckTreeView::FindString (LPCSTR pcItem)
{
	return FindItem (TVI_ROOT, pcItem);
}

///////////////////////////////////////////////////////////////////////////////
// EventHandler
void CCheckTreeView::MouseButtonDn (MouseEvt e)
{
	if (e.isLeftButton()) 
		HandleCheckMark (e.Where(), WM_LBUTTONDOWN);
	ControlWindow::MouseButtonDn (e);
}

void CCheckTreeView::MouseButtonDblClk (MouseEvt e)
{
	if (e.isLeftButton()) 
		HandleCheckMark (e.Where(), WM_LBUTTONDOWN);
	ControlWindow::MouseButtonDblClk (e);
}

void CCheckTreeView::HandleCheckMark(Point point, UINT uiMsg)
{
Rectangle rc = CanvasRect();
CoOrd dY = rc.Top()-rc.Bottom();
TV_HITTESTINFO ht;

	ht.pt.x = point.X();
	ht.pt.y = dY-point.Y();

HTREEITEM hNewTarget = HitTest (&ht);

	if (hNewTarget && (ht.flags & TVHT_ONITEMSTATEICON)) {
	UINT uiState = ChangingCheckState (hNewTarget, uiMsg);

		if (TV_CHECK_NOCHANGE != uiState) {
			if (TV_CHECK_NOMARK != uiState)
				SetCheckState (hNewTarget, uiState);
			else
				ToggleCheckMark (hNewTarget);
			NotifyChecked (hNewTarget, uiMsg, GetCheckState(hNewTarget));
		}
	}
}

void CCheckTreeView::NotifyChecked (HTREEITEM hNewTarget, UINT uiMsg, UINT uiCheckState)
{
NM_TREEVIEWCHECK nmCheck;

	nmCheck.hdr.hwndFrom = Handle();
	nmCheck.hdr.idFrom = GetDlgCtrlID(nmCheck.hdr.hwndFrom);
	nmCheck.hdr.code = TVN_CHECKSTATECHANGED;
	nmCheck.hItem = hNewTarget;
	nmCheck.action = uiMsg;
	nmCheck.state = uiCheckState;
	SendMessage(GetParent()->Handle(), WM_NOTIFY, nmCheck.hdr.idFrom, (LPARAM)&nmCheck);
}

UINT CCheckTreeView::ChangingCheckState (HTREEITEM hNewTarget, UINT uiMsg)
{
NM_TREEVIEWCHECK nmCheck;

	nmCheck.hdr.hwndFrom = Handle();
	nmCheck.hdr.idFrom = GetDlgCtrlID(nmCheck.hdr.hwndFrom);
	nmCheck.hdr.code = TVN_CHANGINGCHECKSTATE;
	nmCheck.hItem = hNewTarget;
	nmCheck.action = uiMsg;
	nmCheck.state = TV_CHECK_NOMARK;
	SendMessage(GetParent()->Handle(), WM_NOTIFY, nmCheck.hdr.idFrom, (LPARAM)&nmCheck);

	return nmCheck.state;
}
